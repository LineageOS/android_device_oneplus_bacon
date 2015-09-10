/* Copyright (c) 2013, The Linux Foundation. All rights reserved.
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

#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include "loc_timer.h"
#include<time.h>
#include<errno.h>

enum timer_state {
    READY = 100,
    WAITING,
    DONE,
    ABORT
};

typedef struct {
    loc_timer_callback callback_func;
    void *user_data;
    unsigned int time_msec;
    pthread_cond_t timer_cond;
    pthread_mutex_t timer_mutex;
    enum timer_state state;
}timer_data;

static void *timer_thread(void *thread_data)
{
    int ret = -ETIMEDOUT;
    struct timespec ts;
    struct timeval tv;
    timer_data* t = (timer_data*)thread_data;

    LOC_LOGD("%s:%d]: Enter. Delay = %d\n", __func__, __LINE__, t->time_msec);

    gettimeofday(&tv, NULL);
    clock_gettime(CLOCK_REALTIME, &ts);
    if(t->time_msec >= 1000) {
        ts.tv_sec += t->time_msec/1000;
        t->time_msec = t->time_msec % 1000;
    }
    if(t->time_msec)
        ts.tv_nsec += t->time_msec * 1000000;
    if(ts.tv_nsec > 999999999) {
        LOC_LOGD("%s:%d]: Large nanosecs\n", __func__, __LINE__);
        ts.tv_sec += 1;
        ts.tv_nsec -= 1000000000;
    }
    LOC_LOGD("%s:%d]: ts.tv_sec:%d; ts.tv_nsec:%d\n"
             "\t Current time: %d sec; %d nsec",
             __func__, __LINE__, (int)ts.tv_sec, (int)ts.tv_nsec,
             (int)tv.tv_sec, (int)tv.tv_usec*1000);

    pthread_mutex_lock(&(t->timer_mutex));
    if (READY == t->state) {
        t->state = WAITING;
        ret = pthread_cond_timedwait(&t->timer_cond, &t->timer_mutex, &ts);
        t->state = DONE;
    }
    pthread_mutex_unlock(&(t->timer_mutex));

    switch (ret) {
    case ETIMEDOUT:
        LOC_LOGV("%s:%d]: loc_timer timed out",  __func__, __LINE__);
        break;
    case 0:
        LOC_LOGV("%s:%d]: loc_timer stopped",  __func__, __LINE__);
        break;
    case -ETIMEDOUT:
        LOC_LOGV("%s:%d]: loc_timer cancelled",  __func__, __LINE__);
        break;
    default:
        LOC_LOGE("%s:%d]: Call to pthread timedwait failed; ret=%d\n",
                 __func__, __LINE__, ret);
        break;
    }

    if(ETIMEDOUT == ret)
        t->callback_func(t->user_data, ret);

    // A (should be rare) race condition is that, when the loc_time_stop is called
    // and acquired mutex, we reach here.  pthread_mutex_destroy will fail with
    // error code EBUSY.  We give it 6 tries in 5 seconds.  Should be eanough time
    // for loc_timer_stop to complete.  With the 7th try, we also perform unlock
    // prior to destroy.
    {
        int i;
        for (i = 0; EBUSY == pthread_mutex_destroy(&t->timer_mutex) && i <= 5; i++) {
            if (i < 5) {
                sleep(1);
            } else {
                // nah, forget it, something is seriously wrong.  Mutex has been
                // held too long.  Unlock the mutext here.
                pthread_mutex_unlock(&t->timer_mutex);
            }
        }
    }
    pthread_cond_destroy(&t->timer_cond);

    free(t);
    LOC_LOGD("%s:%d]: Exit\n", __func__, __LINE__);
    return NULL;
}

void* loc_timer_start(unsigned int msec, loc_timer_callback cb_func,
                      void* caller_data)
{
    timer_data *t=NULL;
    pthread_attr_t tattr;
    pthread_t id;
    LOC_LOGD("%s:%d]: Enter\n", __func__, __LINE__);
    if(cb_func == NULL || msec == 0) {
        LOC_LOGE("%s:%d]: Error: Wrong parameters\n", __func__, __LINE__);
        goto _err;
    }
    t = (timer_data *)calloc(1, sizeof(timer_data));
    if(t == NULL) {
        LOC_LOGE("%s:%d]: Could not allocate memory. Failing.\n",
                 __func__, __LINE__);
        goto _err;
    }

    if(pthread_cond_init(&(t->timer_cond), NULL)) {
        LOC_LOGE("%s:%d]: Pthread cond init failed\n", __func__, __LINE__);
        goto t_err;
    }
    if(pthread_mutex_init(&(t->timer_mutex), NULL)) {
        LOC_LOGE("%s:%d]: Pthread mutex init failed\n", __func__, __LINE__);
        goto cond_err;
    }

    t->callback_func = cb_func;
    t->user_data = caller_data;
    t->time_msec = msec;
    t->state = READY;

    if (pthread_attr_init(&tattr)) {
        LOC_LOGE("%s:%d]: Pthread mutex init failed\n", __func__, __LINE__);
        goto mutex_err;
    }
    pthread_attr_setdetachstate(&tattr, PTHREAD_CREATE_DETACHED);

    if(pthread_create(&(id), &tattr, timer_thread, (void *)t)) {
        LOC_LOGE("%s:%d]: Could not create thread\n", __func__, __LINE__);
        goto attr_err;
    }

    LOC_LOGD("%s:%d]: Created thread with id: %d\n",
             __func__, __LINE__, (int)id);
    goto _err;

attr_err:
    pthread_attr_destroy(&tattr);
mutex_err:
    pthread_mutex_destroy(&t->timer_mutex);
cond_err:
    pthread_cond_destroy(&t->timer_cond);
t_err:
    free(t);
_err:
    LOC_LOGD("%s:%d]: Exit\n", __func__, __LINE__);
    return t;
}

void loc_timer_stop(void* handle) {
    timer_data* t = (timer_data*)handle;

    if (NULL != t && (READY == t->state || WAITING == t->state) &&
        pthread_mutex_lock(&(t->timer_mutex)) == 0) {
        if (READY == t->state || WAITING == t->state) {
            pthread_cond_signal(&t->timer_cond);
            t->state = ABORT;
        }
        pthread_mutex_unlock(&(t->timer_mutex));
    }
}
