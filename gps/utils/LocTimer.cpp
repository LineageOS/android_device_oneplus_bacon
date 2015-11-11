/* Copyright (c) 2015, The Linux Foundation. All rights reserved.
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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <loc_timer.h>
#include <sys/timerfd.h>
#include <sys/epoll.h>
#include <LocTimer.h>
#include <LocHeap.h>
#include <LocThread.h>
#include <LocSharedLock.h>
#include <MsgTask.h>

#ifdef __HOST_UNIT_TEST__
#define EPOLLWAKEUP 0
#define CLOCK_BOOTTIME CLOCK_MONOTONIC
#define CLOCK_BOOTTIME_ALARM CLOCK_MONOTONIC
#endif

/*
There are implementations of 5 classes in this file:
LocTimer, LocTimerDelegate, LocTimerContainer, LocTimerPollTask, LocTimerWrapper

LocTimer - client front end, interface for client to start / stop timers, also
           to provide a callback.
LocTimerDelegate - an internal timer entity, which also is a LocRankable obj.
                   Its life cycle is different than that of LocTimer. It gets
                   created when LocTimer::start() is called, and gets deleted
                   when it expires or clients calls the hosting LocTimer obj's
                   stop() method. When a LocTimerDelegate obj is ticking, it
                   stays in the corresponding LocTimerContainer. When expired
                   or stopped, the obj is removed from the container. Since it
                   is also a LocRankable obj, and LocTimerContainer also is a
                   heap, its ranks() implementation decides where it is placed
                   in the heap.
LocTimerContainer - core of the timer service. It is a container (derived from
                    LocHeap) for LocTimerDelegate (implements LocRankable) objs.
                    There are 2 of such containers, one for sw timers (or Linux
                    timers) one for hw timers (or Linux alarms). It adds one of
                    each (those that expire the soonest) to kernel via services
                    provided by LocTimerPollTask. All the heap management on the
                    LocTimerDelegate objs are done in the MsgTask context, such
                    that synchronization is ensured.
LocTimerPollTask - is a class that wraps timerfd and epoll POXIS APIs. It also
                   both implements LocRunnalbe with epoll_wait() in the run()
                   method. It is also a LocThread client, so as to loop the run
                   method.
LocTimerWrapper - a LocTimer client itself, to implement the existing C API with
                  APIs, loc_timer_start() and loc_timer_stop().

*/

class LocTimerPollTask;

// This is a multi-functaional class that:
// * extends the LocHeap class for the detection of head update upon add / remove
//   events. When that happens, soonest time out changes, so timerfd needs update.
// * contains the timers, and add / remove them into the heap
// * provides and maps 2 of such containers, one for timers (or  mSwTimers), one
//   for alarms (or mHwTimers);
// * provides a polling thread;
// * provides a MsgTask thread for synchronized add / remove / timer client callback.
class LocTimerContainer : public LocHeap {
    // mutex to synchronize getters of static members
    static pthread_mutex_t mMutex;
    // Container of timers
    static LocTimerContainer* mSwTimers;
    // Container of alarms
    static LocTimerContainer* mHwTimers;
    // Msg task to provider msg Q, sender and reader.
    static MsgTask* mMsgTask;
    // Poll task to provide epoll call and threading to poll.
    static LocTimerPollTask* mPollTask;
    // timer / alarm fd
    int mDevFd;
    // ctor
    LocTimerContainer(bool wakeOnExpire);
    // dtor
    ~LocTimerContainer();
    static MsgTask* getMsgTaskLocked();
    static LocTimerPollTask* getPollTaskLocked();
    // extend LocHeap and pop if the top outRanks input
    LocTimerDelegate* popIfOutRanks(LocTimerDelegate& timer);
    // update the timer POSIX calls with updated soonest timer spec
    void updateSoonestTime(LocTimerDelegate* priorTop);

public:
    // factory method to control the creation of mSwTimers / mHwTimers
    static LocTimerContainer* get(bool wakeOnExpire);

    LocTimerDelegate* getSoonestTimer();
    int getTimerFd();
    // add a timer / alarm obj into the container
    void add(LocTimerDelegate& timer);
    // remove a timer / alarm obj from the container
    void remove(LocTimerDelegate& timer);
    // handling of timer / alarm expiration
    void expire();
};

// This class implements the polling thread that epolls imer / alarm fds.
// The LocRunnable::run() contains the actual polling.  The other methods
// will be run in the caller's thread context to add / remove timer / alarm
// fds the kernel, while the polling is blocked on epoll_wait() call.
// Since the design is that we have maximally 2 polls, one for all the
// timers; one for all the alarms, we will poll at most on 2 fds.  But it
// is possile that all we have are only timers or alarms at one time, so we
// allow dynamically add / remove fds we poll on. The design decision of
// having 1 fd per container of timer / alarm is such that, we may not need
// to make a system call each time a timer / alarm is added / removed, unless
// that changes the "soonest" time out of that of all the timers / alarms.
class LocTimerPollTask : public LocRunnable {
    // the epoll fd
    const int mFd;
    // the thread that calls run() method
    LocThread* mThread;
    friend class LocThreadDelegate;
    // dtor
    ~LocTimerPollTask();
public:
    // ctor
    LocTimerPollTask();
    // this obj will be deleted once thread is deleted
    void destroy();
    // add a container of timers. Each contain has a unique device fd, i.e.
    // either timer or alarm fd, and a heap of timers / alarms. It is expected
    // that container would have written to the device fd with the soonest
    // time out value in the heap at the time of calling this method. So all
    // this method does is to add the fd of the input container to the poll
    // and also add the pointer of the container to the event data ptr, such
    // when poll_wait wakes up on events, we know who is the owner of the fd.
    void addPoll(LocTimerContainer& timerContainer);
    // remove a fd that is assciated with a container. The expectation is that
    // the atual timer would have been removed from the container.
    void removePoll(LocTimerContainer& timerContainer);
    // The polling thread context will call this method. This is where
    // epoll_wait() is blocking and waiting for events..
    virtual bool run();
};

// Internal class of timer obj. It gets born when client calls LocTimer::start();
// and gets deleted when client calls LocTimer::stop() or when the it expire()'s.
// This class implements LocRankable::ranks() so that when an obj is added into
// the container (of LocHeap), it gets placed in sorted order.
class LocTimerDelegate : public LocRankable {
    friend class LocTimerContainer;
    friend class LocTimer;
    LocTimer* mClient;
    LocSharedLock* mLock;
    struct timespec mFutureTime;
    LocTimerContainer* mContainer;
    // not a complete obj, just ctor for LocRankable comparisons
    inline LocTimerDelegate(struct timespec& delay)
        : mClient(NULL), mLock(NULL), mFutureTime(delay), mContainer(NULL) {}
    inline ~LocTimerDelegate() { if (mLock) { mLock->drop(); mLock = NULL; } }
public:
    LocTimerDelegate(LocTimer& client, struct timespec& futureTime, bool wakeOnExpire);
    void destroyLocked();
    // LocRankable virtual method
    virtual int ranks(LocRankable& rankable);
    void expire();
    inline struct timespec getFutureTime() { return mFutureTime; }
};

/***************************LocTimerContainer methods***************************/

// Most of these static recources are created on demand. They however are never
// destoyed. The theory is that there are processes that link to this util lib
// but never use timer, then these resources would never need to be created.
// For those processes that do use timer, it will likely also need to every
// once in a while. It might be cheaper keeping them around.
pthread_mutex_t LocTimerContainer::mMutex = PTHREAD_MUTEX_INITIALIZER;
LocTimerContainer* LocTimerContainer::mSwTimers = NULL;
LocTimerContainer* LocTimerContainer::mHwTimers = NULL;
MsgTask* LocTimerContainer::mMsgTask = NULL;
LocTimerPollTask* LocTimerContainer::mPollTask = NULL;

// ctor - initialize timer heaps
// A container for swTimer (timer) is created, when wakeOnExpire is true; or
// HwTimer (alarm), when wakeOnExpire is false.
LocTimerContainer::LocTimerContainer(bool wakeOnExpire) :
    mDevFd(timerfd_create(wakeOnExpire ? CLOCK_BOOTTIME_ALARM : CLOCK_BOOTTIME, 0)) {

    if ((-1 == mDevFd) && (errno == EINVAL)) {
        LOC_LOGW("%s: timerfd_create failure, fallback to CLOCK_MONOTONIC - %s",
            __FUNCTION__, strerror(errno));
        mDevFd = timerfd_create(CLOCK_MONOTONIC, 0);
    }

    if (-1 != mDevFd) {
        // ensure we have the necessary resources created
        LocTimerContainer::getPollTaskLocked();
        LocTimerContainer::getMsgTaskLocked();
    } else {
        LOC_LOGE("%s: timerfd_create failure - %s", __FUNCTION__, strerror(errno));
    }
}

// dtor
// we do not ever destroy the static resources.
inline
LocTimerContainer::~LocTimerContainer() {
    close(mDevFd);
}

LocTimerContainer* LocTimerContainer::get(bool wakeOnExpire) {
    // get the reference of either mHwTimer or mSwTimers per wakeOnExpire
    LocTimerContainer*& container = wakeOnExpire ? mHwTimers : mSwTimers;
    // it is cheap to check pointer first than locking mutext unconditionally
    if (!container) {
        pthread_mutex_lock(&mMutex);
        // let's check one more time to be safe
        if (!container) {
            container = new LocTimerContainer(wakeOnExpire);
            // timerfd_create failure
            if (-1 == container->getTimerFd()) {
                delete container;
                container = NULL;
            }
        }
        pthread_mutex_unlock(&mMutex);
    }
    return container;
}

MsgTask* LocTimerContainer::getMsgTaskLocked() {
    // it is cheap to check pointer first than locking mutext unconditionally
    if (!mMsgTask) {
        mMsgTask = new MsgTask("LocTimerMsgTask", false);
    }
    return mMsgTask;
}

LocTimerPollTask* LocTimerContainer::getPollTaskLocked() {
    // it is cheap to check pointer first than locking mutext unconditionally
    if (!mPollTask) {
        mPollTask = new LocTimerPollTask();
    }
    return mPollTask;
}

inline
LocTimerDelegate* LocTimerContainer::getSoonestTimer() {
    return (LocTimerDelegate*)(peek());
}

inline
int LocTimerContainer::getTimerFd() {
    return mDevFd;
}

void LocTimerContainer::updateSoonestTime(LocTimerDelegate* priorTop) {
    LocTimerDelegate* curTop = getSoonestTimer();

    // check if top has changed
    if (curTop != priorTop) {
        struct itimerspec delay = {0};
        bool toSetTime = false;
        // if tree is empty now, we remove poll and disarm timer
        if (!curTop) {
            mPollTask->removePoll(*this);
            // setting the values to disarm timer
            delay.it_value.tv_sec = 0;
            delay.it_value.tv_nsec = 0;
            toSetTime = true;
        } else if (!priorTop || curTop->outRanks(*priorTop)) {
            // do this first to avoid race condition, in case settime is called
            // with too small an interval
            mPollTask->addPoll(*this);
            delay.it_value = curTop->getFutureTime();
            toSetTime = true;
        }
        if (toSetTime) {
            timerfd_settime(getTimerFd(), TFD_TIMER_ABSTIME, &delay, NULL);
        }
    }
}

// all the heap management is done in the MsgTask context.
inline
void LocTimerContainer::add(LocTimerDelegate& timer) {
    struct MsgTimerPush : public LocMsg {
        LocTimerContainer* mTimerContainer;
        LocHeapNode* mTree;
        LocTimerDelegate* mTimer;
        inline MsgTimerPush(LocTimerContainer& container, LocTimerDelegate& timer) :
            LocMsg(), mTimerContainer(&container), mTimer(&timer) {}
        inline virtual void proc() const {
            LocTimerDelegate* priorTop = mTimerContainer->getSoonestTimer();
            mTimerContainer->push((LocRankable&)(*mTimer));
            mTimerContainer->updateSoonestTime(priorTop);
        }
    };

    mMsgTask->sendMsg(new MsgTimerPush(*this, timer));
}

// all the heap management is done in the MsgTask context.
void LocTimerContainer::remove(LocTimerDelegate& timer) {
    struct MsgTimerRemove : public LocMsg {
        LocTimerContainer* mTimerContainer;
        LocTimerDelegate* mTimer;
        inline MsgTimerRemove(LocTimerContainer& container, LocTimerDelegate& timer) :
            LocMsg(), mTimerContainer(&container), mTimer(&timer) {}
        inline virtual void proc() const {
            LocTimerDelegate* priorTop = mTimerContainer->getSoonestTimer();

            // update soonest timer only if mTimer is actually removed from
            // mTimerContainer AND mTimer is not priorTop.
            if (priorTop == ((LocHeap*)mTimerContainer)->remove((LocRankable&)*mTimer)) {
                // if passing in NULL, we tell updateSoonestTime to update
                // kernel with the current top timer interval.
                mTimerContainer->updateSoonestTime(NULL);
            }
            // all timers are deleted here, and only here.
            delete mTimer;
        }
    };

    mMsgTask->sendMsg(new MsgTimerRemove(*this, timer));
}

// all the heap management is done in the MsgTask context.
// Upon expire, we check and continuously pop the heap until
// the top node's timeout is in the future.
void LocTimerContainer::expire() {
    struct MsgTimerExpire : public LocMsg {
        LocTimerContainer* mTimerContainer;
        inline MsgTimerExpire(LocTimerContainer& container) :
            LocMsg(), mTimerContainer(&container) {}
        inline virtual void proc() const {
            struct timespec now;
            // get time spec of now
            clock_gettime(CLOCK_BOOTTIME, &now);
            LocTimerDelegate timerOfNow(now);
            // pop everything in the heap that outRanks now, i.e. has time older than now
            // and then call expire() on that timer.
            for (LocTimerDelegate* timer = (LocTimerDelegate*)mTimerContainer->pop();
                 NULL != timer;
                 timer = mTimerContainer->popIfOutRanks(timerOfNow)) {
                // the timer delegate obj will be deleted before the return of this call
                timer->expire();
            }
            mTimerContainer->updateSoonestTime(NULL);
        }
    };

    struct itimerspec delay = {0};
    timerfd_settime(getTimerFd(), TFD_TIMER_ABSTIME, &delay, NULL);
    mPollTask->removePoll(*this);
    mMsgTask->sendMsg(new MsgTimerExpire(*this));
}

LocTimerDelegate* LocTimerContainer::popIfOutRanks(LocTimerDelegate& timer) {
    LocTimerDelegate* poppedNode = NULL;
    if (mTree && !timer.outRanks(*peek())) {
        poppedNode = (LocTimerDelegate*)(pop());
    }

    return poppedNode;
}


/***************************LocTimerPollTask methods***************************/

inline
LocTimerPollTask::LocTimerPollTask()
    : mFd(epoll_create(2)), mThread(new LocThread()) {
    // before a next call returens, a thread will be created. The run() method
    // could already be running in parallel. Also, since each of the objs
    // creates a thread, the container will make sure that there will be only
    // one of such obj for our timer implementation.
    if (!mThread->start("LocTimerPollTask", this)) {
        delete mThread;
        mThread = NULL;
    }
}

inline
LocTimerPollTask::~LocTimerPollTask() {
    // when fs is closed, epoll_wait() should fail run() should return false
    // and the spawned thread should exit.
    close(mFd);
}

void LocTimerPollTask::destroy() {
    if (mThread) {
        LocThread* thread = mThread;
        mThread = NULL;
        delete thread;
    } else {
        delete this;
    }
}

void LocTimerPollTask::addPoll(LocTimerContainer& timerContainer) {
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));

    ev.events = EPOLLIN | EPOLLWAKEUP;
    ev.data.fd = timerContainer.getTimerFd();
    // it is important that we set this context pointer with the input
    // timer container this is how we know which container should handle
    // which expiration.
    ev.data.ptr = &timerContainer;

    epoll_ctl(mFd, EPOLL_CTL_ADD, timerContainer.getTimerFd(), &ev);
}

inline
void LocTimerPollTask::removePoll(LocTimerContainer& timerContainer) {
    epoll_ctl(mFd, EPOLL_CTL_DEL, timerContainer.getTimerFd(), NULL);
}

// The polling thread context will call this method. If run() method needs to
// be repetitvely called, it must return true from the previous call.
bool LocTimerPollTask::run() {
    struct epoll_event ev[2];

    // we have max 2 descriptors to poll from
    int fds = epoll_wait(mFd, ev, 2, -1);

    // we pretty much want to continually poll until the fd is closed
    bool rerun = (fds > 0) || (errno == EINTR);

    if (fds > 0) {
        // we may have 2 events
        for (int i = 0; i < fds; i++) {
            // each fd has a context pointer associated with the right timer container
            LocTimerContainer* container = (LocTimerContainer*)(ev[i].data.ptr);
            if (container) {
                container->expire();
            } else {
                epoll_ctl(mFd, EPOLL_CTL_DEL, ev[i].data.fd, NULL);
            }
        }
    }

    // if rerun is true, we are requesting to be scheduled again
    return rerun;
}

/***************************LocTimerDelegate methods***************************/

inline
LocTimerDelegate::LocTimerDelegate(LocTimer& client, struct timespec& futureTime, bool wakeOnExpire)
    : mClient(&client),
      mLock(mClient->mLock->share()),
      mFutureTime(futureTime),
      mContainer(LocTimerContainer::get(wakeOnExpire)) {
    // adding the timer into the container
    mContainer->add(*this);
}

inline
void LocTimerDelegate::destroyLocked() {
    // client handle will likely be deleted soon after this
    // method returns. Nulling this handle so that expire()
    // won't call the callback on the dead handle any more.
    mClient = NULL;

    if (mContainer) {
        LocTimerContainer* container = mContainer;
        mContainer = NULL;
        if (container) {
            container->remove(*this);
        }
    } // else we do not do anything. No such *this* can be
      // created and reached here with mContainer ever been
      // a non NULL. So *this* must have reached the if clause
      // once, and we want it reach there only once.
}

int LocTimerDelegate::ranks(LocRankable& rankable) {
    int rank = -1;
    LocTimerDelegate* timer = (LocTimerDelegate*)(&rankable);
    if (timer) {
        // larger time ranks lower!!!
        // IOW, if input obj has bigger tv_sec, this obj outRanks higher
        rank = timer->mFutureTime.tv_sec - mFutureTime.tv_sec;
    }
    return rank;
}

inline
void LocTimerDelegate::expire() {
    // keeping a copy of client pointer to be safe
    // when timeOutCallback() is called at the end of this
    // method, *this* obj may be already deleted.
    LocTimer* client = mClient;
    // force a stop, which will lead to delete of this obj
    if (client && client->stop()) {
        // calling client callback with a pointer save on the stack
        // only if stop() returns true, i.e. it hasn't been stopped
        // already.
        client->timeOutCallback();
    }
}


/***************************LocTimer methods***************************/
LocTimer::LocTimer() : mTimer(NULL), mLock(new LocSharedLock()) {
}

LocTimer::~LocTimer() {
    stop();
    if (mLock) {
        mLock->drop();
        mLock = NULL;
    }
}

bool LocTimer::start(unsigned int timeOutInMs, bool wakeOnExpire) {
    bool success = false;
    mLock->lock();
    if (!mTimer) {
        struct timespec futureTime;
        clock_gettime(CLOCK_BOOTTIME, &futureTime);
        futureTime.tv_sec += timeOutInMs / 1000;
        futureTime.tv_nsec += (timeOutInMs % 1000) * 1000000;
        if (futureTime.tv_nsec >= 1000000000) {
            futureTime.tv_sec += futureTime.tv_nsec / 1000000000;
            futureTime.tv_nsec %= 1000000000;
        }
        mTimer = new LocTimerDelegate(*this, futureTime, wakeOnExpire);
        // if mTimer is non 0, success should be 0; or vice versa
        success = (NULL != mTimer);
    }
    mLock->unlock();
    return success;
}

bool LocTimer::stop() {
    bool success = false;
    mLock->lock();
    if (mTimer) {
        LocTimerDelegate* timer = mTimer;
        mTimer = NULL;
        if (timer) {
            timer->destroyLocked();
            success = true;
        }
    }
    mLock->unlock();
    return success;
}

/***************************LocTimerWrapper methods***************************/
//////////////////////////////////////////////////////////////////////////
// This section below wraps for the C style APIs
//////////////////////////////////////////////////////////////////////////
class LocTimerWrapper : public LocTimer {
    loc_timer_callback mCb;
    void* mCallerData;
    LocTimerWrapper* mMe;
    static pthread_mutex_t mMutex;
    inline ~LocTimerWrapper() { mCb = NULL; mMe = NULL; }
public:
    inline LocTimerWrapper(loc_timer_callback cb, void* callerData) :
        mCb(cb), mCallerData(callerData), mMe(this) {
    }
    void destroy() {
        pthread_mutex_lock(&mMutex);
        if (NULL != mCb && this == mMe) {
            delete this;
        }
        pthread_mutex_unlock(&mMutex);
    }
    virtual void timeOutCallback() {
        loc_timer_callback cb = mCb;
        void* callerData = mCallerData;
        if (cb) {
            cb(callerData, 0);
        }
        destroy();
    }
};

pthread_mutex_t LocTimerWrapper::mMutex = PTHREAD_MUTEX_INITIALIZER;

void* loc_timer_start(uint64_t msec, loc_timer_callback cb_func,
                      void *caller_data, bool wake_on_expire)
{
    LocTimerWrapper* locTimerWrapper = NULL;

    if (cb_func) {
        locTimerWrapper = new LocTimerWrapper(cb_func, caller_data);

        if (locTimerWrapper) {
            locTimerWrapper->start(msec, wake_on_expire);
        }
    }

    return locTimerWrapper;
}

void loc_timer_stop(void*&  handle)
{
    if (handle) {
        LocTimerWrapper* locTimerWrapper = (LocTimerWrapper*)(handle);
        locTimerWrapper->destroy();
        handle = NULL;
    }
}

//////////////////////////////////////////////////////////////////////////
// This section above wraps for the C style APIs
//////////////////////////////////////////////////////////////////////////

#ifdef __LOC_DEBUG__

double getDeltaSeconds(struct timespec from, struct timespec to) {
    return (double)to.tv_sec + (double)to.tv_nsec / 1000000000
        - from.tv_sec - (double)from.tv_nsec / 1000000000;
}

struct timespec getNow() {
    struct timespec now;
    clock_gettime(CLOCK_BOOTTIME, &now);
    return now;
}

class LocTimerTest : public LocTimer, public LocRankable {
    int mTimeOut;
    const struct timespec mTimeOfBirth;
    inline struct timespec getTimerWrapper(int timeout) {
        struct timespec now;
        clock_gettime(CLOCK_BOOTTIME, &now);
        now.tv_sec += timeout;
        return now;
    }
public:
    inline LocTimerTest(int timeout) : LocTimer(), LocRankable(),
            mTimeOut(timeout), mTimeOfBirth(getTimerWrapper(0)) {}
    inline virtual int ranks(LocRankable& rankable) {
        LocTimerTest* timer = dynamic_cast<LocTimerTest*>(&rankable);
        return timer->mTimeOut - mTimeOut;
    }
    inline virtual void timeOutCallback() {
        printf("timeOutCallback() - ");
        deviation();
    }
    double deviation() {
        struct timespec now = getTimerWrapper(0);
        double delta = getDeltaSeconds(mTimeOfBirth, now);
        printf("%lf: %lf\n", delta, delta * 100 / mTimeOut);
        return delta / mTimeOut;
    }
};

// For Linux command line testing:
// compilation:
//     g++ -D__LOC_HOST_DEBUG__ -D__LOC_DEBUG__ -g -I. -I../../../../system/core/include -o LocHeap.o LocHeap.cpp
//     g++ -D__LOC_HOST_DEBUG__ -D__LOC_DEBUG__ -g -std=c++0x -I. -I../../../../system/core/include -lpthread -o LocThread.o LocThread.cpp
//     g++ -D__LOC_HOST_DEBUG__ -D__LOC_DEBUG__ -g -I. -I../../../../system/core/include -o LocTimer.o LocTimer.cpp
int main(int argc, char** argv) {
    struct timespec timeOfStart=getNow();
    srand(time(NULL));
    int tries = atoi(argv[1]);
    int checks = tries >> 3;
    LocTimerTest** timerArray = new LocTimerTest*[tries];
    memset(timerArray, NULL, tries);

    for (int i = 0; i < tries; i++) {
        int r = rand() % tries;
        LocTimerTest* timer = new LocTimerTest(r);
        if (timerArray[r]) {
            if (!timer->stop()) {
                printf("%lf:\n", getDeltaSeconds(timeOfStart, getNow()));
                printf("ERRER: %dth timer, id %d, not running when it should be\n", i, r);
                exit(0);
            } else {
                printf("stop() - %d\n", r);
                delete timer;
                timerArray[r] = NULL;
            }
        } else {
            if (!timer->start(r, false)) {
                printf("%lf:\n", getDeltaSeconds(timeOfStart, getNow()));
                printf("ERRER: %dth timer, id %d, running when it should not be\n", i, r);
                exit(0);
            } else {
                printf("stop() - %d\n", r);
                timerArray[r] = timer;
            }
        }
    }

    for (int i = 0; i < tries; i++) {
        if (timerArray[i]) {
            if (!timerArray[i]->stop()) {
                printf("%lf:\n", getDeltaSeconds(timeOfStart, getNow()));
                printf("ERRER: %dth timer, not running when it should be\n", i);
                exit(0);
            } else {
                printf("stop() - %d\n", i);
                delete timerArray[i];
                timerArray[i] = NULL;
            }
        }
    }

    delete[] timerArray;

    return 0;
}

#endif
