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

#ifndef __LOC_TIMER_CPP_H__
#define __LOC_TIMER_CPP_H__

#include <stddef.h>
#include <log_util.h>

// opaque class to provide service implementation.
class LocTimerDelegate;
class LocSharedLock;

// LocTimer client must extend this class and implementthe callback.
// start() / stop() methods are to arm / disarm timer.
class LocTimer
{
    LocTimerDelegate* mTimer;
    LocSharedLock* mLock;
    // don't really want mLock to be manipulated by clients, yet LocTimer
    // has to have a reference to the lock so that the delete of LocTimer
    // and LocTimerDelegate can work together on their share resources.
    friend class LocTimerDelegate;

public:
    LocTimer();
    virtual ~LocTimer();

    // timeOutInMs:  timeout delay in ms
    // wakeOnExpire: true if to wake up CPU (if sleeping) upon timer
    //                        expiration and notify the client.
    //               false if to wait until next time CPU wakes up (if
    //                        sleeping) and then notify the client.
    // return:       true on success;
    //               false on failure, e.g. timer is already running.
    bool start(uint32_t timeOutInMs, bool wakeOnExpire);

    // return:       true on success;
    //               false on failure, e.g. timer is not running.
    bool stop();

    //  LocTimer client Should implement this method.
    //  This method is used for timeout calling back to client. This method
    //  should be short enough (eg: send a message to your own thread).
    virtual void timeOutCallback() = 0;
};

#endif //__LOC_DELAY_H__
