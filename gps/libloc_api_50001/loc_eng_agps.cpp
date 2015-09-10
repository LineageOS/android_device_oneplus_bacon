/* Copyright (c) 2011-2013, The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of The Linux Foundation, nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#define LOG_NDDEBUG 0
#define LOG_TAG "LocSvc_eng"

#include <loc_eng_agps.h>
#include <loc_eng_log.h>
#include <log_util.h>
#include <platform_lib_includes.h>
#include <loc_eng_dmn_conn_handler.h>
#include <loc_eng_dmn_conn.h>
#include <sys/time.h>

//======================================================================
// C callbacks
//======================================================================

// This is given to linked_list_add as the dealloc callback
// data -- an instance of Subscriber
static void deleteObj(void* data)
{
    delete (Subscriber*)data;
}

// This is given to linked_list_search() as the comparison callback
// when the state manchine needs to process for particular subscriber
// fromCaller -- caller provides this obj
// fromList -- linked_list_search() function take this one from list
static bool hasSubscriber(void* fromCaller, void* fromList)
{
    Notification* notification = (Notification*)fromCaller;
    Subscriber* s1 = (Subscriber*)fromList;

    return s1->forMe(*notification);
}

// This is gvien to linked_list_search() to notify subscriber objs
// when the state machine needs to inform all subscribers of resource
// status changes, e.g. when resource is GRANTED.
// fromCaller -- caller provides this ptr to a Notification obj.
// fromList -- linked_list_search() function take this one from list
static bool notifySubscriber(void* fromCaller, void* fromList)
{
    Notification* notification = (Notification*)fromCaller;
    Subscriber* s1 = (Subscriber*)fromList;

    // we notify every subscriber indiscriminatively
    // each subscriber decides if this notification is interesting.
    return s1->notifyRsrcStatus(*notification) &&
           // if we do not want to delete the subscriber from the
           // the list, we must set this to false so this function
           // returns false
           notification->postNotifyDelete;
}

//======================================================================
// Notification
//======================================================================
const int Notification::BROADCAST_ALL = 0x80000000;
const int Notification::BROADCAST_ACTIVE = 0x80000001;
const int Notification::BROADCAST_INACTIVE = 0x80000002;
const unsigned char DSStateMachine::MAX_START_DATA_CALL_RETRIES = 4;
const unsigned int DSStateMachine::DATA_CALL_RETRY_DELAY_MSEC = 500;
//======================================================================
// Subscriber:  BITSubscriber / ATLSubscriber / WIFISubscriber
//======================================================================
bool Subscriber::forMe(Notification &notification)
{
    if (NULL != notification.rcver) {
        return equals(notification.rcver);
    } else {
        return Notification::BROADCAST_ALL == notification.groupID ||
            (Notification::BROADCAST_ACTIVE == notification.groupID &&
             !isInactive()) ||
            (Notification::BROADCAST_INACTIVE == notification.groupID &&
             isInactive());
    }
}
bool BITSubscriber::equals(const Subscriber *s) const
{
    BITSubscriber* bitS = (BITSubscriber*)s;

    return (ID == bitS->ID &&
            (INADDR_NONE != (unsigned int)ID ||
             0 == strncmp(mIPv6Addr, bitS->mIPv6Addr, sizeof(mIPv6Addr))));
}

bool BITSubscriber::notifyRsrcStatus(Notification &notification)
{
    bool notify = forMe(notification);

    if (notify) {
        switch(notification.rsrcStatus)
        {
        case RSRC_UNSUBSCRIBE:
        case RSRC_RELEASED:
            loc_eng_dmn_conn_loc_api_server_data_conn(
                LOC_ENG_IF_REQUEST_SENDER_ID_GPSONE_DAEMON,
                GPSONE_LOC_API_IF_RELEASE_SUCCESS);
            break;
        case RSRC_DENIED:
            loc_eng_dmn_conn_loc_api_server_data_conn(
                LOC_ENG_IF_REQUEST_SENDER_ID_GPSONE_DAEMON,
                GPSONE_LOC_API_IF_FAILURE);
            break;
        case RSRC_GRANTED:
            loc_eng_dmn_conn_loc_api_server_data_conn(
                LOC_ENG_IF_REQUEST_SENDER_ID_GPSONE_DAEMON,
                GPSONE_LOC_API_IF_REQUEST_SUCCESS);
            break;
        default:
            notify = false;
        }
    }

    return notify;
}

bool ATLSubscriber::notifyRsrcStatus(Notification &notification)
{
    bool notify = forMe(notification);

    if (notify) {
        switch(notification.rsrcStatus)
        {
        case RSRC_UNSUBSCRIBE:
        case RSRC_RELEASED:
            ((LocEngAdapter*)mLocAdapter)->atlCloseStatus(ID, 1);
            break;
        case RSRC_DENIED:
        {
            AGpsExtType type = mBackwardCompatibleMode ?
                              AGPS_TYPE_INVALID : mStateMachine->getType();
            ((LocEngAdapter*)mLocAdapter)->atlOpenStatus(ID, 0,
                                            (char*)mStateMachine->getAPN(),
                                            mStateMachine->getBearer(),
                                            type);
        }
            break;
        case RSRC_GRANTED:
        {
            AGpsExtType type = mBackwardCompatibleMode ?
                              AGPS_TYPE_INVALID : mStateMachine->getType();
            ((LocEngAdapter*)mLocAdapter)->atlOpenStatus(ID, 1,
                                            (char*)mStateMachine->getAPN(),
                                            mStateMachine->getBearer(),
                                            type);
        }
            break;
        default:
            notify = false;
        }
    }

    return notify;
}

bool WIFISubscriber::notifyRsrcStatus(Notification &notification)
{
    bool notify = forMe(notification);

    if (notify) {
        switch(notification.rsrcStatus)
        {
        case RSRC_UNSUBSCRIBE:
            break;
        case RSRC_RELEASED:
            loc_eng_dmn_conn_loc_api_server_data_conn(
                senderId,
                GPSONE_LOC_API_IF_RELEASE_SUCCESS);
            break;
        case RSRC_DENIED:
            loc_eng_dmn_conn_loc_api_server_data_conn(
                senderId,
                GPSONE_LOC_API_IF_FAILURE);
            break;
        case RSRC_GRANTED:
            loc_eng_dmn_conn_loc_api_server_data_conn(
                senderId,
                GPSONE_LOC_API_IF_REQUEST_SUCCESS);
            break;
        default:
            notify = false;
        }
    }

    return notify;
}
bool DSSubscriber::notifyRsrcStatus(Notification &notification)
{
    bool notify = forMe(notification);
    LOC_LOGD("DSSubscriber::notifyRsrcStatus. notify:%d \n",(int)(notify));
    if(notify) {
        switch(notification.rsrcStatus) {
        case RSRC_UNSUBSCRIBE:
        case RSRC_RELEASED:
        case RSRC_DENIED:
        case RSRC_GRANTED:
            ((DSStateMachine *)mStateMachine)->informStatus(notification.rsrcStatus, ID);
            break;
        default:
            notify = false;
        }
    }
    return notify;
}
void DSSubscriber :: setInactive()
{
    mIsInactive = true;
    ((DSStateMachine *)mStateMachine)->informStatus(RSRC_UNSUBSCRIBE, ID);
}
//======================================================================
// AgpsState:  AgpsReleasedState / AgpsPendingState / AgpsAcquiredState
//======================================================================

// AgpsReleasedState
class AgpsReleasedState : public AgpsState
{
    friend class AgpsStateMachine;

    inline AgpsReleasedState(AgpsStateMachine* stateMachine) :
        AgpsState(stateMachine)
    { mReleasedState = this; }

    inline ~AgpsReleasedState() {}
public:
    virtual AgpsState* onRsrcEvent(AgpsRsrcStatus event, void* data);
    inline virtual char* whoami() {return (char*)"AgpsReleasedState";}
};

AgpsState* AgpsReleasedState::onRsrcEvent(AgpsRsrcStatus event, void* data)
{
    LOC_LOGD("AgpsReleasedState::onRsrcEvent; event:%d\n", (int)event);
    if (mStateMachine->hasSubscribers()) {
        LOC_LOGE("Error: %s subscriber list not empty!!!", whoami());
        // I don't know how to recover from it.  I am adding this rather
        // for debugging purpose.
    }

    AgpsState* nextState = this;
    switch (event)
    {
    case RSRC_SUBSCRIBE:
    {
        // no notification until we get RSRC_GRANTED
        // but we need to add subscriber to the list
        mStateMachine->addSubscriber((Subscriber*)data);
        // request from connecivity service for NIF
        //The if condition is added so that if the data call setup fails
        //for DS State Machine, we want to retry in released state.
        //for AGps State Machine, sendRsrcRequest() will always return success
        if(!mStateMachine->sendRsrcRequest(GPS_REQUEST_AGPS_DATA_CONN)) {
            // move the state to PENDING
            nextState = mPendingState;
        }
    }
    break;

    case RSRC_UNSUBSCRIBE:
    {
        // the list should really be empty, nothing to remove.
        // but we might as well just tell the client it is
        // unsubscribed.  False tolerance, right?
        Subscriber* subscriber = (Subscriber*) data;
        Notification notification(subscriber, event, false);
        subscriber->notifyRsrcStatus(notification);
    }
        // break;
    case RSRC_GRANTED:
    case RSRC_RELEASED:
    case RSRC_DENIED:
    default:
        LOC_LOGW("%s: unrecognized event %d", whoami(), event);
        // no state change.
        break;
    }

    LOC_LOGD("onRsrcEvent, old state %s, new state %s, event %d",
             whoami(), nextState->whoami(), event);
    return nextState;
}

// AgpsPendingState
class AgpsPendingState : public AgpsState
{
    friend class AgpsStateMachine;

    inline AgpsPendingState(AgpsStateMachine* stateMachine) :
        AgpsState(stateMachine)
    { mPendingState = this; }

    inline ~AgpsPendingState() {}
public:
    virtual AgpsState* onRsrcEvent(AgpsRsrcStatus event, void* data);
    inline virtual char* whoami() {return (char*)"AgpsPendingState";}
};

AgpsState* AgpsPendingState::onRsrcEvent(AgpsRsrcStatus event, void* data)
{
    AgpsState* nextState = this;;
    LOC_LOGD("AgpsPendingState::onRsrcEvent; event:%d\n", (int)event);
    switch (event)
    {
    case RSRC_SUBSCRIBE:
    {
        // already requested for NIF resource,
        // do nothing until we get RSRC_GRANTED indication
        // but we need to add subscriber to the list
        mStateMachine->addSubscriber((Subscriber*)data);
        // no state change.
    }
        break;

    case RSRC_UNSUBSCRIBE:
    {
        Subscriber* subscriber = (Subscriber*) data;
        if (subscriber->waitForCloseComplete()) {
            subscriber->setInactive();
        } else {
            // auto notify this subscriber of the unsubscribe
            Notification notification(subscriber, event, true);
            mStateMachine->notifySubscribers(notification);
        }

        // now check if there is any subscribers left
        if (!mStateMachine->hasSubscribers()) {
            // no more subscribers, move to RELEASED state
            nextState = mReleasedState;

            // tell connecivity service we can release NIF
            mStateMachine->sendRsrcRequest(GPS_RELEASE_AGPS_DATA_CONN);
        } else if (!mStateMachine->hasActiveSubscribers()) {
            // only inactive subscribers, move to RELEASING state
            nextState = mReleasingState;

            // tell connecivity service we can release NIF
            mStateMachine->sendRsrcRequest(GPS_RELEASE_AGPS_DATA_CONN);
        }
    }
    break;

    case RSRC_GRANTED:
    {
        nextState = mAcquiredState;
        Notification notification(Notification::BROADCAST_ACTIVE, event, false);
        // notify all subscribers NIF resource GRANTED
        // by setting false, we keep subscribers on the linked list
        mStateMachine->notifySubscribers(notification);
    }
        break;

    case RSRC_RELEASED:
        // no state change.
        // we are expecting either GRANTED or DENIED.  Handling RELEASED
        // may like break our state machine in race conditions.
        break;

    case RSRC_DENIED:
    {
        nextState = mReleasedState;
        Notification notification(Notification::BROADCAST_ALL, event, true);
        // notify all subscribers NIF resource RELEASED or DENIED
        // by setting true, we remove subscribers from the linked list
        mStateMachine->notifySubscribers(notification);
    }
        break;

    default:
        LOC_LOGE("%s: unrecognized event %d", whoami(), event);
        // no state change.
    }

    LOC_LOGD("onRsrcEvent, old state %s, new state %s, event %d",
             whoami(), nextState->whoami(), event);
    return nextState;
}


class AgpsAcquiredState : public AgpsState
{
    friend class AgpsStateMachine;

    inline AgpsAcquiredState(AgpsStateMachine* stateMachine) :
        AgpsState(stateMachine)
    { mAcquiredState = this; }

    inline ~AgpsAcquiredState() {}
public:
    virtual AgpsState* onRsrcEvent(AgpsRsrcStatus event, void* data);
    inline virtual char* whoami() { return (char*)"AgpsAcquiredState"; }
};


AgpsState* AgpsAcquiredState::onRsrcEvent(AgpsRsrcStatus event, void* data)
{
    AgpsState* nextState = this;
    LOC_LOGD("AgpsAcquiredState::onRsrcEvent; event:%d\n", (int)event);
    switch (event)
    {
    case RSRC_SUBSCRIBE:
    {
        // we already have the NIF resource, simply notify subscriber
        Subscriber* subscriber = (Subscriber*) data;
        // we have rsrc in hand, so grant it right away
        Notification notification(subscriber, RSRC_GRANTED, false);
        subscriber->notifyRsrcStatus(notification);
        // add subscriber to the list
        mStateMachine->addSubscriber(subscriber);
        // no state change.
    }
        break;

    case RSRC_UNSUBSCRIBE:
    {
        Subscriber* subscriber = (Subscriber*) data;
        if (subscriber->waitForCloseComplete()) {
            subscriber->setInactive();
        } else {
            // auto notify this subscriber of the unsubscribe
            Notification notification(subscriber, event, true);
            mStateMachine->notifySubscribers(notification);
        }

        // now check if there is any subscribers left
        if (!mStateMachine->hasSubscribers()) {
            // no more subscribers, move to RELEASED state
            nextState = mReleasedState;

            // tell connecivity service we can release NIF
            mStateMachine->sendRsrcRequest(GPS_RELEASE_AGPS_DATA_CONN);
        } else if (!mStateMachine->hasActiveSubscribers()) {
            // only inactive subscribers, move to RELEASING state
            nextState = mReleasingState;

            // tell connecivity service we can release NIF
            mStateMachine->sendRsrcRequest(GPS_RELEASE_AGPS_DATA_CONN);
        }
    }
        break;

    case RSRC_GRANTED:
        LOC_LOGW("%s: %d, RSRC_GRANTED already received", whoami(), event);
        // no state change.
        break;

    case RSRC_RELEASED:
    {
        LOC_LOGW("%s: %d, a force rsrc release", whoami(), event);
        nextState = mReleasedState;
        Notification notification(Notification::BROADCAST_ALL, event, true);
        // by setting true, we remove subscribers from the linked list
        mStateMachine->notifySubscribers(notification);
    }
        break;

    case RSRC_DENIED:
        // no state change.
        // we are expecting RELEASED.  Handling DENIED
        // may like break our state machine in race conditions.
        break;

    default:
        LOC_LOGE("%s: unrecognized event %d", whoami(), event);
        // no state change.
    }

    LOC_LOGD("onRsrcEvent, old state %s, new state %s, event %d",
             whoami(), nextState->whoami(), event);
    return nextState;
}

// AgpsPendingState
class AgpsReleasingState : public AgpsState
{
    friend class AgpsStateMachine;

    inline AgpsReleasingState(AgpsStateMachine* stateMachine) :
        AgpsState(stateMachine)
    { mReleasingState = this; }

    inline ~AgpsReleasingState() {}
public:
    virtual AgpsState* onRsrcEvent(AgpsRsrcStatus event, void* data);
    inline virtual char* whoami() {return (char*)"AgpsReleasingState";}
};

AgpsState* AgpsReleasingState::onRsrcEvent(AgpsRsrcStatus event, void* data)
{
    AgpsState* nextState = this;;
    LOC_LOGD("AgpsReleasingState::onRsrcEvent; event:%d\n", (int)event);

   switch (event)
    {
    case RSRC_SUBSCRIBE:
    {
        // already requested for NIF resource,
        // do nothing until we get RSRC_GRANTED indication
        // but we need to add subscriber to the list
        mStateMachine->addSubscriber((Subscriber*)data);
        // no state change.
    }
        break;

    case RSRC_UNSUBSCRIBE:
    {
        Subscriber* subscriber = (Subscriber*) data;
        if (subscriber->waitForCloseComplete()) {
            subscriber->setInactive();
        } else {
            // auto notify this subscriber of the unsubscribe
            Notification notification(subscriber, event, true);
            mStateMachine->notifySubscribers(notification);
        }

        // now check if there is any subscribers left
        if (!mStateMachine->hasSubscribers()) {
            // no more subscribers, move to RELEASED state
            nextState = mReleasedState;
        }
    }
        break;

    case RSRC_DENIED:
        // A race condition subscriber unsubscribes before AFW denies resource.
    case RSRC_RELEASED:
    {
        nextState = mAcquiredState;
        Notification notification(Notification::BROADCAST_INACTIVE, event, true);
        // notify all subscribers that are active NIF resource RELEASE
        // by setting false, we keep subscribers on the linked list
        mStateMachine->notifySubscribers(notification);

        if (mStateMachine->hasActiveSubscribers()) {
            nextState = mPendingState;
            // request from connecivity service for NIF
            mStateMachine->sendRsrcRequest(GPS_REQUEST_AGPS_DATA_CONN);
        } else {
            nextState = mReleasedState;
        }
    }
        break;

    case RSRC_GRANTED:
    default:
        LOC_LOGE("%s: unrecognized event %d", whoami(), event);
        // no state change.
    }

    LOC_LOGD("onRsrcEvent, old state %s, new state %s, event %d",
             whoami(), nextState->whoami(), event);
    return nextState;
}
//======================================================================
//Servicer
//======================================================================
Servicer* Servicer :: getServicer(servicerType type, void *cb_func)
{
    LOC_LOGD(" Enter getServicer type:%d\n", (int)type);
    switch(type) {
    case servicerTypeNoCbParam:
        return (new Servicer(cb_func));
    case servicerTypeExt:
        return (new ExtServicer(cb_func));
    case servicerTypeAgps:
        return (new AGpsServicer(cb_func));
    default:
        return NULL;
    }
}

int Servicer :: requestRsrc(void *cb_data)
{
    callback();
    return 0;
}

int ExtServicer :: requestRsrc(void *cb_data)
{
    int ret=-1;
    LOC_LOGD("Enter ExtServicer :: requestRsrc\n");
    ret = callbackExt(cb_data);
    LOC_LOGD("Exit ExtServicer :: requestRsrc\n");
    return(ret);
}

int AGpsServicer :: requestRsrc(void *cb_data)
{
    callbackAGps((AGpsStatus *)cb_data);
    return 0;
}

//======================================================================
// AgpsStateMachine
//======================================================================

AgpsStateMachine::AgpsStateMachine(servicerType servType,
                                   void *cb_func,
                                   AGpsExtType type,
                                   bool enforceSingleSubscriber) :
    mStatePtr(new AgpsReleasedState(this)),mType(type),
    mAPN(NULL),
    mAPNLen(0),
    mBearer(AGPS_APN_BEARER_INVALID),
    mEnforceSingleSubscriber(enforceSingleSubscriber),
    mServicer(Servicer :: getServicer(servType, (void *)cb_func))
{
    linked_list_init(&mSubscribers);

    // setting up mReleasedState
    mStatePtr->mPendingState = new AgpsPendingState(this);
    mStatePtr->mAcquiredState = new AgpsAcquiredState(this);
    mStatePtr->mReleasingState = new AgpsReleasingState(this);

    // setting up mAcquiredState
    mStatePtr->mAcquiredState->mReleasedState = mStatePtr;
    mStatePtr->mAcquiredState->mPendingState = mStatePtr->mPendingState;
    mStatePtr->mAcquiredState->mReleasingState = mStatePtr->mReleasingState;

    // setting up mPendingState
    mStatePtr->mPendingState->mAcquiredState = mStatePtr->mAcquiredState;
    mStatePtr->mPendingState->mReleasedState = mStatePtr;
    mStatePtr->mPendingState->mReleasingState = mStatePtr->mReleasingState;

    // setting up mReleasingState
    mStatePtr->mReleasingState->mReleasedState = mStatePtr;
    mStatePtr->mReleasingState->mPendingState = mStatePtr->mPendingState;
    mStatePtr->mReleasingState->mAcquiredState = mStatePtr->mAcquiredState;
}

AgpsStateMachine::~AgpsStateMachine()
{
    dropAllSubscribers();

    // free the 3 states.  We must read out all 3 pointers first.
    // Otherwise we run the risk of getting pointers from already
    // freed memory.
    AgpsState* acquiredState = mStatePtr->mAcquiredState;
    AgpsState* releasedState = mStatePtr->mReleasedState;
    AgpsState* pendindState = mStatePtr->mPendingState;
    AgpsState* releasingState = mStatePtr->mReleasingState;

    delete acquiredState;
    delete releasedState;
    delete pendindState;
    delete releasingState;
    delete mServicer;
    linked_list_destroy(&mSubscribers);

    if (NULL != mAPN) {
        delete[] mAPN;
        mAPN = NULL;
    }
}

void AgpsStateMachine::setAPN(const char* apn, unsigned int len)
{
    if (NULL != mAPN) {
        delete mAPN;
    }

    if (NULL != apn) {
        mAPN = new char[len+1];
        memcpy(mAPN, apn, len);
        mAPN[len] = NULL;

        mAPNLen = len;
    } else {
        mAPN = NULL;
        mAPNLen = 0;
    }
}

void AgpsStateMachine::onRsrcEvent(AgpsRsrcStatus event)
{
    switch (event)
    {
    case RSRC_GRANTED:
    case RSRC_RELEASED:
    case RSRC_DENIED:
        mStatePtr = mStatePtr->onRsrcEvent(event, NULL);
        break;
    default:
        LOC_LOGW("AgpsStateMachine: unrecognized event %d", event);
        break;
    }
}

void AgpsStateMachine::notifySubscribers(Notification& notification) const
{
    if (notification.postNotifyDelete) {
        // just any non NULL value to get started
        Subscriber* s = (Subscriber*)~0;
        while (NULL != s) {
            s = NULL;
            // if the last param sets to true, _search will delete
            // the node from the list for us.  But the problem is
            // once that is done, _search returns, leaving the
            // rest of the list unprocessed.  So we need a loop.
            linked_list_search(mSubscribers, (void**)&s, notifySubscriber,
                               (void*)&notification, true);
            delete s;
        }
    } else {
        // no loop needed if it the last param sets to false, which
        // mean nothing gets deleted from the list.
        linked_list_search(mSubscribers, NULL, notifySubscriber,
                           (void*)&notification, false);
    }
}

void AgpsStateMachine::addSubscriber(Subscriber* subscriber) const
{
    Subscriber* s = NULL;
    Notification notification((const Subscriber*)subscriber);
    linked_list_search(mSubscribers, (void**)&s,
                       hasSubscriber, (void*)&notification, false);

    if (NULL == s) {
        linked_list_add(mSubscribers, subscriber->clone(), deleteObj);
    }
}

int AgpsStateMachine::sendRsrcRequest(AGpsStatusValue action) const
{
    Subscriber* s = NULL;
    Notification notification(Notification::BROADCAST_ACTIVE);
    linked_list_search(mSubscribers, (void**)&s, hasSubscriber,
                       (void*)&notification, false);

    if ((NULL == s) == (GPS_RELEASE_AGPS_DATA_CONN == action)) {
        AGpsExtStatus nifRequest;
        nifRequest.size = sizeof(nifRequest);
        nifRequest.type = mType;
        nifRequest.status = action;

        if (s == NULL) {
            nifRequest.ipv4_addr = INADDR_NONE;
            nifRequest.ipv6_addr[0] = 0;
            nifRequest.ssid[0] = '\0';
            nifRequest.password[0] = '\0';
        } else {
            s->setIPAddresses(nifRequest.ipv4_addr, (char*)nifRequest.ipv6_addr);
            s->setWifiInfo(nifRequest.ssid, nifRequest.password);
        }

        CALLBACK_LOG_CALLFLOW("agps_cb", %s, loc_get_agps_status_name(action));
        mServicer->requestRsrc((void *)&nifRequest);
    }
    return 0;
}

void AgpsStateMachine::subscribeRsrc(Subscriber *subscriber)
{
  if (mEnforceSingleSubscriber && hasSubscribers()) {
      Notification notification(Notification::BROADCAST_ALL, RSRC_DENIED, true);
      notifySubscriber(&notification, subscriber);
  } else {
      mStatePtr = mStatePtr->onRsrcEvent(RSRC_SUBSCRIBE, (void*)subscriber);
  }
}

bool AgpsStateMachine::unsubscribeRsrc(Subscriber *subscriber)
{
    Subscriber* s = NULL;
    Notification notification((const Subscriber*)subscriber);
    linked_list_search(mSubscribers, (void**)&s,
                       hasSubscriber, (void*)&notification, false);

    if (NULL != s) {
        mStatePtr = mStatePtr->onRsrcEvent(RSRC_UNSUBSCRIBE, (void*)s);
        return true;
    }
    return false;
}

bool AgpsStateMachine::hasActiveSubscribers() const
{
    Subscriber* s = NULL;
    Notification notification(Notification::BROADCAST_ACTIVE);
    linked_list_search(mSubscribers, (void**)&s,
                       hasSubscriber, (void*)&notification, false);
    return NULL != s;
}

//======================================================================
// DSStateMachine
//======================================================================
void delay_callback(void *callbackData, int result)
{
    if(callbackData) {
        DSStateMachine *DSSMInstance = (DSStateMachine *)callbackData;
        DSSMInstance->retryCallback();
    }
    else {
        LOC_LOGE(" NULL argument received. Failing.\n");
        goto err;
    }
err:
    return;
}

DSStateMachine :: DSStateMachine(servicerType type, void *cb_func,
                                 LocEngAdapter* adapterHandle):
    AgpsStateMachine(type, cb_func, AGPS_TYPE_INVALID,false),
    mLocAdapter(adapterHandle)
{
    LOC_LOGD("%s:%d]: New DSStateMachine\n", __func__, __LINE__);
    mRetries = 0;
}

void DSStateMachine :: retryCallback(void)
{
    DSSubscriber *subscriber = NULL;
    Notification notification(Notification::BROADCAST_ACTIVE);
    linked_list_search(mSubscribers, (void**)&subscriber, hasSubscriber,
                       (void*)&notification, false);
    if(subscriber)
        mLocAdapter->requestSuplES(subscriber->ID);
    else
        LOC_LOGE("DSStateMachine :: retryCallback: No subscriber found." \
                 "Cannot retry data call\n");
    return;
}

int DSStateMachine :: sendRsrcRequest(AGpsStatusValue action) const
{
    DSSubscriber* s = NULL;
    dsCbData cbData;
    int ret=-1;
    int connHandle=-1;
    LOC_LOGD("Enter DSStateMachine :: sendRsrcRequest\n");
    Notification notification(Notification::BROADCAST_ACTIVE);
    linked_list_search(mSubscribers, (void**)&s, hasSubscriber,
                       (void*)&notification, false);
    if(s) {
        connHandle = s->ID;
        LOC_LOGD("DSStateMachine :: sendRsrcRequest - subscriber found\n");
    }
    else
        LOC_LOGD("DSStateMachine :: sendRsrcRequest - No subscriber found\n");

    cbData.action = action;
    cbData.mAdapter = mLocAdapter;
    ret = mServicer->requestRsrc((void *)&cbData);
    //Only the request to start data call returns a success/failure
    //The request to stop data call will always succeed
    //Hence, the below block will only be executed when the
    //request to start the data call fails
    switch(ret) {
    case LOC_API_ADAPTER_ERR_ENGINE_BUSY:
        LOC_LOGD("DSStateMachine :: sendRsrcRequest - Failure returned: %d\n",ret);
        ((DSStateMachine *)this)->incRetries();
        if(mRetries > MAX_START_DATA_CALL_RETRIES) {
            LOC_LOGE(" Failed to start Data call. Fallback to normal ATL SUPL\n");
            informStatus(RSRC_DENIED, connHandle);
        }
        else {
            if(loc_timer_start(DATA_CALL_RETRY_DELAY_MSEC, delay_callback, (void *)this)) {
                LOC_LOGE("Error: Could not start delay thread\n");
                ret = -1;
                goto err;
            }
        }
        break;
    case LOC_API_ADAPTER_ERR_UNSUPPORTED:
        LOC_LOGE("No profile found for emergency call. Fallback to normal SUPL ATL\n");
        informStatus(RSRC_DENIED, connHandle);
        break;
    case LOC_API_ADAPTER_ERR_SUCCESS:
        LOC_LOGD("%s:%d]: Request to start data call sent\n", __func__, __LINE__);
        break;
    case -1:
        //One of the ways this case can be encountered is if the callback function
        //receives a null argument, it just exits with -1 error
        LOC_LOGE("Error: Something went wrong somewhere. Falling back to normal SUPL ATL\n");
        informStatus(RSRC_DENIED, connHandle);
        break;
    default:
        LOC_LOGE("%s:%d]: Unrecognized return value\n", __func__, __LINE__);
    }
err:
    LOC_LOGD("EXIT DSStateMachine :: sendRsrcRequest; ret = %d\n", ret);
    return ret;
}

void DSStateMachine :: onRsrcEvent(AgpsRsrcStatus event)
{
    void* currState = (void *)mStatePtr;
    LOC_LOGD("Enter DSStateMachine :: onRsrcEvent. event = %d\n", (int)event);
    switch (event)
    {
    case RSRC_GRANTED:
        LOC_LOGD("DSStateMachine :: onRsrcEvent RSRC_GRANTED\n");
        mStatePtr = mStatePtr->onRsrcEvent(event, NULL);
        break;
    case RSRC_RELEASED:
        LOC_LOGD("DSStateMachine :: onRsrcEvent RSRC_RELEASED\n");
        mStatePtr = mStatePtr->onRsrcEvent(event, NULL);
        //To handle the case where we get a RSRC_RELEASED in
        //pending state, we translate that to a RSRC_DENIED state
        //since the callback from DSI is either RSRC_GRANTED or RSRC_RELEASED
        //for when the call is connected or disconnected respectively.
        if((void *)mStatePtr != currState)
            break;
        else {
            event = RSRC_DENIED;
            LOC_LOGE(" Switching event to RSRC_DENIED\n");
        }
    case RSRC_DENIED:
        mStatePtr = mStatePtr->onRsrcEvent(event, NULL);
        break;
    default:
        LOC_LOGW("AgpsStateMachine: unrecognized event %d", event);
        break;
    }
    LOC_LOGD("Exit DSStateMachine :: onRsrcEvent. event = %d\n", (int)event);
}

void DSStateMachine :: informStatus(AgpsRsrcStatus status, int ID) const
{
    LOC_LOGD("DSStateMachine :: informStatus. Status=%d\n",(int)status);
    switch(status) {
    case RSRC_UNSUBSCRIBE:
        mLocAdapter->atlCloseStatus(ID, 1);
        break;
    case RSRC_RELEASED:
        mLocAdapter->closeDataCall();
        break;
    case RSRC_DENIED:
        ((DSStateMachine *)this)->mRetries = 0;
        mLocAdapter->requestATL(ID, AGPS_TYPE_SUPL);
        break;
    case RSRC_GRANTED:
        mLocAdapter->atlOpenStatus(ID, 1,
                                                     NULL,
                                                     AGPS_APN_BEARER_INVALID,
                                                     AGPS_TYPE_INVALID);
        break;
    default:
        LOC_LOGW("DSStateMachine :: informStatus - unknown status");
    }
    return;
}
