/* Copyright (c) 2009-2014, The Linux Foundation. All rights reserved.
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

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>
#include <MsgTask.h>

#include <loc_eng.h>

#include "log_util.h"
#include "platform_lib_includes.h"

using namespace loc_core;

/*=============================================================================
 *
 *                             DATA DECLARATION
 *
 *============================================================================*/

/*=============================================================================
 *
 *                             FUNCTION DECLARATIONS
 *
 *============================================================================*/
static void* ni_thread_proc(void *args);

struct LocEngInformNiResponse : public LocMsg {
    LocEngAdapter* mAdapter;
    const GpsUserResponseType mResponse;
    const void *mPayload;
    inline LocEngInformNiResponse(LocEngAdapter* adapter,
                                  GpsUserResponseType resp,
                                  const void* data) :
        LocMsg(), mAdapter(adapter),
        mResponse(resp), mPayload(data)
    {
        locallog();
    }
    inline ~LocEngInformNiResponse()
    {
        // this is a bit weird since mPayload is not
        // allocated by this class.  But there is no better way.
        // mPayload actually won't be NULL here.
        free((void*)mPayload);
    }
    inline virtual void proc() const
    {
        mAdapter->informNiResponse(mResponse, mPayload);
    }
    inline void locallog() const
    {
        LOC_LOGV("LocEngInformNiResponse - "
                 "response: %s\n  mPayload: %p",
                 loc_get_ni_response_name(mResponse),
                 mPayload);
    }
    inline virtual void log() const
    {
        locallog();
    }
};

/*===========================================================================

FUNCTION loc_eng_ni_request_handler

DESCRIPTION
   Displays the NI request and awaits user input. If a previous request is
   in session, it is ignored.

RETURN VALUE
   none

===========================================================================*/
void loc_eng_ni_request_handler(loc_eng_data_s_type &loc_eng_data,
                            const GpsNiNotification *notif,
                            const void* passThrough)
{
    ENTRY_LOG();
    char lcs_addr[32]; // Decoded LCS address for UMTS CP NI
    loc_eng_ni_data_s_type* loc_eng_ni_data_p = &loc_eng_data.loc_eng_ni_data;
    loc_eng_ni_session_s_type* pSession = NULL;

    if (NULL == loc_eng_data.ni_notify_cb) {
        EXIT_LOG(%s, "loc_eng_ni_init hasn't happened yet.");
        return;
    }

    if (notif->ni_type == GPS_NI_TYPE_EMERGENCY_SUPL) {
        if (NULL != loc_eng_ni_data_p->sessionEs.rawRequest) {
            LOC_LOGW("loc_eng_ni_request_handler, supl es NI in progress, new supl es NI ignored, type: %d",
                     notif->ni_type);
            if (NULL != passThrough) {
                free((void*)passThrough);
            }
        } else {
            pSession = &loc_eng_ni_data_p->sessionEs;
        }
    } else {
        if (NULL != loc_eng_ni_data_p->session.rawRequest ||
            NULL != loc_eng_ni_data_p->sessionEs.rawRequest) {
            LOC_LOGW("loc_eng_ni_request_handler, supl NI in progress, new supl NI ignored, type: %d",
                     notif->ni_type);
            if (NULL != passThrough) {
                free((void*)passThrough);
            }
        } else {
            pSession = &loc_eng_ni_data_p->session;
        }
    }


    if (pSession) {
        /* Save request */
        pSession->rawRequest = (void*)passThrough;
        pSession->reqID = ++loc_eng_ni_data_p->reqIDCounter;
        pSession->adapter = loc_eng_data.adapter;

        /* Fill in notification */
        ((GpsNiNotification*)notif)->notification_id = pSession->reqID;

        if (notif->notify_flags == GPS_NI_PRIVACY_OVERRIDE)
        {
            loc_eng_mute_one_session(loc_eng_data);
        }

        /* Log requestor ID and text for debugging */
        LOC_LOGI("Notification: notif_type: %d, timeout: %d, default_resp: %d", notif->ni_type, notif->timeout, notif->default_response);
        LOC_LOGI("              requestor_id: %s (encoding: %d)", notif->requestor_id, notif->requestor_id_encoding);
        LOC_LOGI("              text: %s text (encoding: %d)", notif->text, notif->text_encoding);
        if (notif->extras[0])
        {
            LOC_LOGI("              extras: %s", notif->extras);
        }

        /* For robustness, spawn a thread at this point to timeout to clear up the notification status, even though
         * the OEM layer in java does not do so.
         **/
        pSession->respTimeLeft = 5 + (notif->timeout != 0 ? notif->timeout : LOC_NI_NO_RESPONSE_TIME);
        LOC_LOGI("Automatically sends 'no response' in %d seconds (to clear status)\n", pSession->respTimeLeft);

        int rc = 0;
        rc = pthread_create(&pSession->thread, NULL, ni_thread_proc, pSession);
        if (rc)
        {
            LOC_LOGE("Loc NI thread is not created.\n");
        }
        rc = pthread_detach(pSession->thread);
        if (rc)
        {
            LOC_LOGE("Loc NI thread is not detached.\n");
        }

        CALLBACK_LOG_CALLFLOW("ni_notify_cb - id", %d, notif->notification_id);
        loc_eng_data.ni_notify_cb((GpsNiNotification*)notif);
    }
    EXIT_LOG(%s, VOID_RET);
}

/*===========================================================================

FUNCTION ni_thread_proc

===========================================================================*/
static void* ni_thread_proc(void *args)
{
    ENTRY_LOG();

    loc_eng_ni_session_s_type* pSession = (loc_eng_ni_session_s_type*)args;
    int rc = 0;          /* return code from pthread calls */

    struct timeval present_time;
    struct timespec expire_time;

    LOC_LOGD("Starting Loc NI thread...\n");
    pthread_mutex_lock(&pSession->tLock);
    /* Calculate absolute expire time */
    gettimeofday(&present_time, NULL);
    expire_time.tv_sec  = present_time.tv_sec + pSession->respTimeLeft;
    expire_time.tv_nsec = present_time.tv_usec * 1000;
    LOC_LOGD("ni_thread_proc-Time out set for abs time %ld with delay %d sec\n",
             (long) expire_time.tv_sec, pSession->respTimeLeft );

    while (!pSession->respRecvd)
    {
        rc = pthread_cond_timedwait(&pSession->tCond,
                                    &pSession->tLock,
                                    &expire_time);
        if (rc == ETIMEDOUT)
        {
            pSession->resp = GPS_NI_RESPONSE_NORESP;
            LOC_LOGD("ni_thread_proc-Thread time out after valting for specified time. Ret Val %d\n",rc );
            break;
        }
    }
    LOC_LOGD("ni_thread_proc-Java layer has sent us a user response and return value from "
             "pthread_cond_timedwait = %d\n",rc );
    pSession->respRecvd = FALSE; /* Reset the user response flag for the next session*/

    LOC_LOGD("pSession->resp is %d\n",pSession->resp);

    // adding this check to support modem restart, in which case, we need the thread
    // to exit without calling sending data. We made sure that rawRequest is NULL in
    // loc_eng_ni_reset_on_engine_restart()
    LocEngAdapter* adapter = pSession->adapter;
    LocEngInformNiResponse *msg = NULL;

    if (NULL != pSession->rawRequest) {
        if (pSession->resp != GPS_NI_RESPONSE_IGNORE) {
            LOC_LOGD("pSession->resp != GPS_NI_RESPONSE_IGNORE \n");
            msg = new LocEngInformNiResponse(adapter,
                                             pSession->resp,
                                             pSession->rawRequest);
        } else {
            LOC_LOGD("this is the ignore reply for SUPL ES\n");
            free(pSession->rawRequest);
        }
        pSession->rawRequest = NULL;
    }
    pthread_mutex_unlock(&pSession->tLock);

    pSession->respTimeLeft = 0;
    pSession->reqID = 0;

    if (NULL != msg) {
        LOC_LOGD("ni_thread_proc: adapter->sendMsg(msg)\n");
        adapter->sendMsg(msg);
    }

    EXIT_LOG(%s, VOID_RET);
    return NULL;
}

void loc_eng_ni_reset_on_engine_restart(loc_eng_data_s_type &loc_eng_data)
{
    ENTRY_LOG();
    loc_eng_ni_data_s_type* loc_eng_ni_data_p = &loc_eng_data.loc_eng_ni_data;

    if (NULL == loc_eng_data.ni_notify_cb) {
        EXIT_LOG(%s, "loc_eng_ni_init hasn't happened yet.");
        return;
    }

    // only if modem has requested but then died.
    if (NULL != loc_eng_ni_data_p->sessionEs.rawRequest) {
        free(loc_eng_ni_data_p->sessionEs.rawRequest);
        loc_eng_ni_data_p->sessionEs.rawRequest = NULL;

        pthread_mutex_lock(&loc_eng_ni_data_p->sessionEs.tLock);
        // the goal is to wake up ni_thread_proc
        // and let it exit.
        loc_eng_ni_data_p->sessionEs.respRecvd = TRUE;
        pthread_cond_signal(&loc_eng_ni_data_p->sessionEs.tCond);
        pthread_mutex_unlock(&loc_eng_ni_data_p->sessionEs.tLock);
    }

    if (NULL != loc_eng_ni_data_p->session.rawRequest) {
        free(loc_eng_ni_data_p->session.rawRequest);
        loc_eng_ni_data_p->session.rawRequest = NULL;

        pthread_mutex_lock(&loc_eng_ni_data_p->session.tLock);
        // the goal is to wake up ni_thread_proc
        // and let it exit.
        loc_eng_ni_data_p->session.respRecvd = TRUE;
        pthread_cond_signal(&loc_eng_ni_data_p->session.tCond);
        pthread_mutex_unlock(&loc_eng_ni_data_p->session.tLock);
    }

    EXIT_LOG(%s, VOID_RET);
}

/*===========================================================================
FUNCTION    loc_eng_ni_init

DESCRIPTION
   This function initializes the NI interface

DEPENDENCIES
   NONE

RETURN VALUE
   None

SIDE EFFECTS
   N/A

===========================================================================*/
void loc_eng_ni_init(loc_eng_data_s_type &loc_eng_data, GpsNiExtCallbacks *callbacks)
{
    ENTRY_LOG_CALLFLOW();

    if(callbacks == NULL)
        EXIT_LOG(%s, "loc_eng_ni_init: failed, cb is NULL");
    else if (NULL == callbacks->notify_cb) {
        EXIT_LOG(%s, "loc_eng_ni_init: failed, no cb.");
    } else if (NULL != loc_eng_data.ni_notify_cb) {
        EXIT_LOG(%s, "loc_eng_ni_init: already inited.");
    } else {
        loc_eng_ni_data_s_type* loc_eng_ni_data_p = &loc_eng_data.loc_eng_ni_data;
        loc_eng_ni_data_p->sessionEs.respTimeLeft = 0;
        loc_eng_ni_data_p->sessionEs.respRecvd = FALSE;
        loc_eng_ni_data_p->sessionEs.rawRequest = NULL;
        loc_eng_ni_data_p->sessionEs.reqID = 0;
        pthread_cond_init(&loc_eng_ni_data_p->sessionEs.tCond, NULL);
        pthread_mutex_init(&loc_eng_ni_data_p->sessionEs.tLock, NULL);

        loc_eng_ni_data_p->session.respTimeLeft = 0;
        loc_eng_ni_data_p->session.respRecvd = FALSE;
        loc_eng_ni_data_p->session.rawRequest = NULL;
        loc_eng_ni_data_p->session.reqID = 0;
        pthread_cond_init(&loc_eng_ni_data_p->session.tCond, NULL);
        pthread_mutex_init(&loc_eng_ni_data_p->session.tLock, NULL);

        loc_eng_data.ni_notify_cb = callbacks->notify_cb;
        EXIT_LOG(%s, VOID_RET);
    }
}

/*===========================================================================
FUNCTION    loc_eng_ni_respond

DESCRIPTION
   This function receives user response from upper layer framework

DEPENDENCIES
   NONE

RETURN VALUE
   None

SIDE EFFECTS
   N/A

===========================================================================*/
void loc_eng_ni_respond(loc_eng_data_s_type &loc_eng_data,
                        int notif_id, GpsUserResponseType user_response)
{
    ENTRY_LOG_CALLFLOW();
    loc_eng_ni_data_s_type* loc_eng_ni_data_p = &loc_eng_data.loc_eng_ni_data;
    loc_eng_ni_session_s_type* pSession = NULL;

    if (NULL == loc_eng_data.ni_notify_cb) {
        EXIT_LOG(%s, "loc_eng_ni_init hasn't happened yet.");
        return;
    }

    if (notif_id == loc_eng_ni_data_p->sessionEs.reqID &&
        NULL != loc_eng_ni_data_p->sessionEs.rawRequest) {
        pSession = &loc_eng_ni_data_p->sessionEs;
        // ignore any SUPL NI non-Es session if a SUPL NI ES is accepted
        if (user_response == GPS_NI_RESPONSE_ACCEPT &&
            NULL != loc_eng_ni_data_p->session.rawRequest) {
                pthread_mutex_lock(&loc_eng_ni_data_p->session.tLock);
                loc_eng_ni_data_p->session.resp = GPS_NI_RESPONSE_IGNORE;
                loc_eng_ni_data_p->session.respRecvd = TRUE;
                pthread_cond_signal(&loc_eng_ni_data_p->session.tCond);
                pthread_mutex_unlock(&loc_eng_ni_data_p->session.tLock);
        }
    } else if (notif_id == loc_eng_ni_data_p->session.reqID &&
        NULL != loc_eng_ni_data_p->session.rawRequest) {
        pSession = &loc_eng_ni_data_p->session;
    }

    if (pSession) {
        LOC_LOGI("loc_eng_ni_respond: send user response %d for notif %d", user_response, notif_id);
        pthread_mutex_lock(&pSession->tLock);
        pSession->resp = user_response;
        pSession->respRecvd = TRUE;
        pthread_cond_signal(&pSession->tCond);
        pthread_mutex_unlock(&pSession->tLock);
    }
    else {
        LOC_LOGE("loc_eng_ni_respond: notif_id %d not an active session", notif_id);
    }

    EXIT_LOG(%s, VOID_RET);
}
