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
#ifndef __MSG_TASK__
#define __MSG_TASK__

#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <pthread.h>

namespace loc_core {

struct LocMsg {
    inline LocMsg() {}
    inline virtual ~LocMsg() {}
    virtual void proc() const = 0;
    inline virtual void log() const {}
};

class MsgTask {
public:
    typedef void* (*tStart)(void*);
    typedef pthread_t (*tCreate)(const char* name, tStart start, void* arg);
    typedef int (*tAssociate)();
    MsgTask(tCreate tCreator, const char* threadName);
    MsgTask(tAssociate tAssociator, const char* threadName);
    ~MsgTask();
    void sendMsg(const LocMsg* msg) const;
    void associate(tAssociate tAssociator) const;

private:
    const void* mQ;
    tAssociate mAssociator;
    MsgTask(const void* q, tAssociate associator);
    static void* loopMain(void* copy);
    void createPThread(const char* name);
};

} // namespace loc_core

#endif //__MSG_TASK__
