/* Copyright (c) 2011-2012, The Linux Foundation. All rights reserved.
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
 */
#ifndef LOC_UTIL_LOG_H
#define LOC_UTIL_LOG_H

#if defined(_ANDROID_)
#include "loc_api_v02_log.h"
#include <log_util.h>

#else // no _ANDROID_

#if defined(__LOC_API_V02_LOG_SILENT__)
#define MSG_LOG
#define LOC_LOGE(...) MSG_LOG(__VA_ARGS__);
#define LOC_LOGW(...) MSG_LOG(__VA_ARGS__);
#define LOC_LOGD(...) MSG_LOG(__VA_ARGS__);
#define LOC_LOGI(...) MSG_LOG(__VA_ARGS__);
#define LOC_LOGV(...) MSG_LOG(__VA_ARGS__);
#else

// common for QNX and Griffon

//error logs
#define LOC_LOGE(...) printf(__VA_ARGS__)
//warning logs
#define LOC_LOGW(...) printf(__VA_ARGS__)
// debug logs
#define LOC_LOGD(...) printf(__VA_ARGS__)
//info logs
#define LOC_LOGI(...) printf(__VA_ARGS__)
//verbose logs
#define LOC_LOGV(...) printf(__VA_ARGS__)
#endif //__LOC_API_V02_LOG_SILENT__

#define MODEM_LOG_CALLFLOW(SPEC, VAL)
#define EXIT_LOG_CALLFLOW(SPEC, VAL)

#define loc_get_v02_event_name(X) #X
#define loc_get_v02_client_status_name(X) #X

#define loc_get_v02_qmi_status_name(X)  #X

//specific to OFF TARGET
#ifdef LOC_UTIL_TARGET_OFF_TARGET

#include <stdio.h>
# include <asm/errno.h>
# include <sys/time.h>

// get around strl*: not found in glibc
// TBD:look for presence of eglibc other libraries
// with strlcpy supported.
#define strlcpy(X,Y,Z) strcpy(X,Y)
#define strlcat(X,Y,Z) strcat(X,Y)

#endif //LOC_UTIL_TARGET_OFF_TARGET

#endif //_ANDROID_

#endif //LOC_UTIL_LOG_H
