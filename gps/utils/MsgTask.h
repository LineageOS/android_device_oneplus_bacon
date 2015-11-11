/* Copyright (c) 2011-2013,2015 The Linux Foundation. All rights reserved.
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
#ifndef __MSG_TASK__
#define __MSG_TASK__

#include <LocThread.h>

struct LocMsg {
    inline LocMsg() {}
    inline virtual ~LocMsg() {}
    virtual void proc() const = 0;
    inline virtual void log() const {}
};

class MsgTask : public LocRunnable {
    const void* mQ;
    LocThread* mThread;
    friend class LocThreadDelegate;
protected:
    virtual ~MsgTask();
public:
    MsgTask(LocThread::tCreate tCreator, const char* threadName = NULL, bool joinable = true);
    MsgTask(const char* threadName = NULL, bool joinable = true);
    // this obj will be deleted once thread is deleted
    void destroy();
    void sendMsg(const LocMsg* msg) const;
    // Overrides of LocRunnable methods
    // This method will be repeated called until it returns false; or
    // until thread is stopped.
    virtual bool run();

    // The method to be run before thread loop (conditionally repeatedly)
    // calls run()
    virtual void prerun();

    // The method to be run after thread loop (conditionally repeatedly)
    // calls run()
    inline virtual void postrun() {}
};

#endif //__MSG_TASK__
