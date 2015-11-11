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
#ifndef __LOC_THREAD__
#define __LOC_THREAD__

#include <stddef.h>
#include <pthread.h>

// abstract class to be implemented by client to provide a runnable class
// which gets scheduled by LocThread
class LocRunnable {
public:
    inline LocRunnable() {}
    inline virtual ~LocRunnable() {}

    // The method to be implemented by thread clients
    // and be scheduled by LocThread
    // This method will be repeated called until it returns false; or
    // until thread is stopped.
    virtual bool run() = 0;

    // The method to be run before thread loop (conditionally repeatedly)
    // calls run()
    inline virtual void prerun() {}

    // The method to be run after thread loop (conditionally repeatedly)
    // calls run()
    inline virtual void postrun() {}
};

// opaque class to provide service implementation.
class LocThreadDelegate;

// A utility class to create a thread and run LocRunnable
// caller passes in.
class LocThread {
    LocThreadDelegate* mThread;
public:
    inline LocThread() : mThread(NULL) {}
    virtual ~LocThread();

    typedef pthread_t (*tCreate)(const char* name, void* (*start)(void*), void* arg);
    // client starts thread with a runnable, which implements
    // the logics to fun in the created thread context.
    // The thread could be either joinable or detached.
    // runnable is an obj managed by client. Client creates and
    //          frees it (but must be after stop() is called, or
    //          this LocThread obj is deleted).
    //          The obj will be deleted by LocThread if start()
    //          returns true. Else it is client's responsibility
    //          to delete the object
    // Returns 0 if success; false if failure.
    bool start(tCreate creator, const char* threadName, LocRunnable* runnable, bool joinable = true);
    inline bool start(const char* threadName, LocRunnable* runnable, bool joinable = true) {
        return start(NULL, threadName, runnable, joinable);
    }

    // NOTE: if this is a joinable thread, this stop may block
    // for a while until the thread is joined.
    void stop();

    // thread status check
    inline bool isRunning() { return NULL != mThread; }
};

#endif //__LOC_THREAD__
