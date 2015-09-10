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
 *     * Neither the name of The Linux Foundation nor the names of its
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

#ifndef __PLATFORM_LIB_MACROS_H__
#define __PLATFORM_LIB_MACROS_H__

#include <sys/time.h>

#define TS_PRINTF(format, x...)                                \
{                                                              \
  struct timeval tv;                                           \
  struct timezone tz;                                          \
  int hh, mm, ss;                                              \
  gettimeofday(&tv, &tz);                                      \
  hh = tv.tv_sec/3600%24;                                      \
  mm = (tv.tv_sec%3600)/60;                                    \
  ss = tv.tv_sec%60;                                           \
  fprintf(stdout,"%02d:%02d:%02d.%06ld]" format "\n", hh, mm, ss, tv.tv_usec,##x);    \
}


#ifdef USE_GLIB

#define strlcat g_strlcat
#define strlcpy g_strlcpy

#define ALOGE(format, x...) TS_PRINTF("E/%s (%d): " format , LOG_TAG, getpid(), ##x)
#define ALOGW(format, x...) TS_PRINTF("W/%s (%d): " format , LOG_TAG, getpid(), ##x)
#define ALOGI(format, x...) TS_PRINTF("I/%s (%d): " format , LOG_TAG, getpid(), ##x)
#define ALOGD(format, x...) TS_PRINTF("D/%s (%d): " format , LOG_TAG, getpid(), ##x)
#define ALOGV(format, x...) TS_PRINTF("V/%s (%d): " format , LOG_TAG, getpid(), ##x)

#define GETTID_PLATFORM_LIB_ABSTRACTION (syscall(SYS_gettid))

#define LOC_EXT_CREATE_THREAD_CB_PLATFORM_LIB_ABSTRACTION createPthread
#define ELAPSED_MILLIS_SINCE_BOOT_PLATFORM_LIB_ABSTRACTION (elapsedMillisSinceBoot())


#else

#ifdef __cplusplus
extern "C" {
#endif
pid_t gettid(void);

#ifdef __cplusplus
}
#endif

#define GETTID_PLATFORM_LIB_ABSTRACTION (gettid())
#define LOC_EXT_CREATE_THREAD_CB_PLATFORM_LIB_ABSTRACTION android::AndroidRuntime::createJavaThread
#define ELAPSED_MILLIS_SINCE_BOOT_PLATFORM_LIB_ABSTRACTION  (android::elapsedRealtime())

#endif

#endif
