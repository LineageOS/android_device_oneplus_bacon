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
#ifndef __LOC_SHARED_LOCK__
#define __LOC_SHARED_LOCK__

#include <stddef.h>
#include <cutils/atomic.h>
#include <pthread.h>

// This is a utility created for use cases such that there are more than
// one client who need to share the same lock, but it is not predictable
// which of these clients is to last to go away. This shared lock deletes
// itself when the last client calls its drop() method. To add a cient,
// this share lock's share() method has to be called, so that the obj
// can maintain an accurate client count.
class LocSharedLock {
    volatile int32_t mRef;
    pthread_mutex_t mMutex;
    inline ~LocSharedLock() { pthread_mutex_destroy(&mMutex); }
public:
    // first client to create this LockSharedLock
    inline LocSharedLock() : mRef(1) { pthread_mutex_init(&mMutex, NULL); }
    // following client(s) are to *share()* this lock created by the first client
    inline LocSharedLock* share() { android_atomic_inc(&mRef); return this; }
    // whe a client no longer needs this shared lock, drop() shall be called.
    inline void drop() { if (1 == android_atomic_dec(&mRef)) delete this; }
    // locking the lock to enter critical section
    inline void lock() { pthread_mutex_lock(&mMutex); }
    // unlocking the lock to leave the critical section
    inline void unlock() { pthread_mutex_unlock(&mMutex); }
};

#endif //__LOC_SHARED_LOCK__
