/* Copyright (c) 2013,2015 The Linux Foundation. All rights reserved.
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

#ifndef __LOC_DELAY_H__
#define __LOC_DELAY_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#include <stddef.h>

/*
    user_data: client context pointer, passthrough. Originally received
               from calling client when loc_timer_start() is called.
    result:    0 if timer successfully timed out; else timer failed.
*/
typedef void (*loc_timer_callback)(void *user_data, int32_t result);


/*
    delay_msec:         timeout value for the timer.
    cb_func:            callback function pointer, implemented by client.
                        Can not be NULL.
    user_data:          client context pointer, passthrough.  Will be
                        returned when loc_timer_callback() is called.
    wakeOnExpire:       true if to wake up CPU (if sleeping) upon timer
                                expiration and notify the client.
                        false if to wait until next time CPU wakes up (if
                                 sleeping) and then notify the client.
    Returns the handle, which can be used to stop the timer
                        NULL, if timer start fails (e.g. if cb_func is NULL).
*/
void* loc_timer_start(uint64_t delay_msec,
                      loc_timer_callback cb_func,
                      void *user_data,
                      bool wake_on_expire=false);

/*
    handle becomes invalid upon the return of the callback
*/
void loc_timer_stop(void*& handle);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //__LOC_DELAY_H__
