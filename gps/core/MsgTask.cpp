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
#define LOG_TAG "LocSvc_MsgTask"

#include <cutils/sched_policy.h>
#include <unistd.h>
#include <MsgTask.h>
#include <msg_q.h>
#include <log_util.h>
#include <loc_log.h>

namespace loc_core {

#define MAX_TASK_COMM_LEN 15

static void LocMsgDestroy(void* msg) {
    delete (LocMsg*)msg;
}

MsgTask::MsgTask(tCreate tCreator, const char* threadName) :
    mQ(msg_q_init2()), mAssociator(NULL){
    if (tCreator) {
        tCreator(threadName, loopMain,
                 (void*)new MsgTask(mQ, mAssociator));
    } else {
        createPThread(threadName);
    }
}

MsgTask::MsgTask(tAssociate tAssociator, const char* threadName) :
    mQ(msg_q_init2()), mAssociator(tAssociator){
    createPThread(threadName);
}

inline
MsgTask::MsgTask(const void* q, tAssociate associator) :
    mQ(q), mAssociator(associator){
}

MsgTask::~MsgTask() {
    msg_q_unblock((void*)mQ);
}

void MsgTask::associate(tAssociate tAssociator) const {
    struct LocAssociateMsg : public LocMsg {
        tAssociate mAssociator;
        inline LocAssociateMsg(tAssociate associator) :
            LocMsg(), mAssociator(associator) {}
        inline virtual void proc() const {
            if (mAssociator) {
                LOC_LOGD("MsgTask::associate");
                mAssociator();
            }
        }
    };
    sendMsg(new LocAssociateMsg(tAssociator));
}

void MsgTask::createPThread(const char* threadName) {
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    pthread_t tid;
    // create the thread here, then if successful
    // and a name is given, we set the thread name
    if (!pthread_create(&tid, &attr, loopMain,
                        (void*)new MsgTask(mQ, mAssociator)) &&
        NULL != threadName) {
        char lname[MAX_TASK_COMM_LEN+1];
        memcpy(lname, threadName, MAX_TASK_COMM_LEN);
        lname[MAX_TASK_COMM_LEN] = 0;
        pthread_setname_np(tid, lname);
    }
}

void MsgTask::sendMsg(const LocMsg* msg) const {
    msg_q_snd((void*)mQ, (void*)msg, LocMsgDestroy);
}

void* MsgTask::loopMain(void* arg) {
    MsgTask* copy = (MsgTask*)arg;

    // make sure we do not run in background scheduling group
    set_sched_policy(gettid(), SP_FOREGROUND);

    if (NULL != copy->mAssociator) {
        copy->mAssociator();
    }

    LocMsg* msg;
    int cnt = 0;

    while (1) {
        LOC_LOGD("MsgTask::loop() %d listening ...\n", cnt++);

        msq_q_err_type result = msg_q_rcv((void*)copy->mQ, (void **)&msg);

        if (eMSG_Q_SUCCESS != result) {
            LOC_LOGE("%s:%d] fail receiving msg: %s\n", __func__, __LINE__,
                     loc_get_msg_q_status(result));
            // destroy the Q and exit
            msg_q_destroy((void**)&(copy->mQ));
            delete copy;
            return NULL;
        }

        msg->log();
        // there is where each individual msg handling is invoked
        msg->proc();

        delete msg;
    }

    delete copy;

    return NULL;
}

}
