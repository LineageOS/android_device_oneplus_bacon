/* Copyright (c) 2011, The Linux Foundation. All rights reserved.
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

#ifndef LOC_SYNC_REQ_H
#define LOC_SYNC_REQ_H

#ifdef __cplusplus
extern "C"
{
#endif
#include <stdbool.h>
#include <stdint.h>
#include "loc_api_v02_client.h"

#define LOC_ENGINE_SYNC_REQUEST_TIMEOUT  (1000) // 1 second

#define LOC_SEND_SYNC_REQ(NAME, ID, REQ, HANDLE)  \
    int rv = true; \
    locClientStatusEnumType st; \
    locClientReqUnionType reqUnion; \
    qmiLoc##NAME##IndMsgT_v02 ind; \
\
    reqUnion.p##NAME##Req = &REQ; \
\
    st = loc_sync_send_req(HANDLE,                          \
                           QMI_LOC_##ID##_REQ_V02,          \
                           reqUnion,                        \
                           LOC_ENGINE_SYNC_REQUEST_TIMEOUT, \
                           QMI_LOC_##ID##_IND_V02,          \
                           &ind);                           \
\
    if (st != eLOC_CLIENT_SUCCESS || \
        eQMI_LOC_SUCCESS_V02 != ind.status) { \
        LOC_LOGE ("%s:%d]: Error : st = %d, ind.status = %d", \
                  __func__, __LINE__,  st, ind.status); \
        rv = false; \
    }

/* Init function */
extern void loc_sync_req_init();


/* Process Loc API indications to wake up blocked user threads */
extern void loc_sync_process_ind(
      locClientHandleType     client_handle,     /* handle of the client */
      uint32_t                ind_id ,      /* respInd id */
      void                    *ind_payload_ptr /* payload              */
);

/* Thread safe synchronous request,  using Loc API status return code */
extern locClientStatusEnumType loc_sync_send_req
(
      locClientHandleType       client_handle,
      uint32_t                  req_id,        /* req id */
      locClientReqUnionType     req_payload,
      uint32_t                  timeout_msec,
      uint32_t                  ind_id,  //ind ID to block for, usually the same as req_id */
      void                      *ind_payload_ptr /* can be NULL*/
);

#ifdef __cplusplus
}
#endif

#endif /* LOC_SYNC_REQ_H */
