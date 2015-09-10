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
#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <sys/time.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <loc_cfg.h>
#include "loc_api_v02_client.h"
#include "loc_api_sync_req.h"

/* Logging */
// Uncomment to log verbose logs
#define LOG_NDEBUG 1

// log debug logs
#define LOG_NDDEBUG 1
#define LOG_TAG "LocSvc_api_v02"
#include "loc_util_log.h"

#define LOC_SYNC_REQ_BUFFER_SIZE 8
#define GPS_CONF_FILE "/etc/gps.conf"
pthread_mutex_t  loc_sync_call_mutex = PTHREAD_MUTEX_INITIALIZER;

static bool loc_sync_call_initialized = false;

typedef struct {
   pthread_mutex_t         sync_req_lock;

   /* Client ID */
   locClientHandleType     client_handle;

   /*  waiting conditional variable */
   pthread_cond_t          ind_arrived_cond;

   /* Callback waiting data block, protected by loc_cb_data_mutex */
   bool                    ind_is_selected;              /* is cb selected? */
   bool                    ind_is_waiting;               /* is waiting?     */
   bool                    ind_has_arrived;              /* callback has arrived */
   uint32_t                req_id;                    /*  sync request */
   void                    *recv_ind_payload_ptr; /* received  payload */
   uint32_t                recv_ind_id;      /* received  ind   */

} loc_sync_req_data_s_type;

typedef struct {
   bool                        in_use;  /* at least one sync call is active */
   bool                        slot_in_use[LOC_SYNC_REQ_BUFFER_SIZE];
   loc_sync_req_data_s_type    slots[LOC_SYNC_REQ_BUFFER_SIZE];
} loc_sync_req_array_s_type;

/***************************************************************************
 *                 DATA FOR ASYNCHRONOUS RPC PROCESSING
 **************************************************************************/
loc_sync_req_array_s_type loc_sync_array;

/*===========================================================================

FUNCTION   loc_sync_req_init

DESCRIPTION
   Initialize this module

DEPENDENCIES
   N/A

RETURN VALUE
   none

SIDE EFFECTS
   N/A

===========================================================================*/
void loc_sync_req_init()
{
   LOC_LOGV(" %s:%d]:\n", __func__, __LINE__);
   UTIL_READ_CONF_DEFAULT(GPS_CONF_FILE);
   pthread_mutex_lock(&loc_sync_call_mutex);
   if(true == loc_sync_call_initialized)
   {
      LOC_LOGD("%s:%d]:already initialized\n", __func__, __LINE__);
      pthread_mutex_unlock(&loc_sync_call_mutex);
      return;
   }

   loc_sync_array.in_use = false;

   memset(loc_sync_array.slot_in_use, 0, sizeof(loc_sync_array.slot_in_use));

   int i;
   for (i = 0; i < LOC_SYNC_REQ_BUFFER_SIZE; i++)
   {
      loc_sync_req_data_s_type *slot = &loc_sync_array.slots[i];

      pthread_mutex_init(&slot->sync_req_lock, NULL);
      pthread_cond_init(&slot->ind_arrived_cond, NULL);

      slot->client_handle = LOC_CLIENT_INVALID_HANDLE_VALUE;
      slot->ind_is_selected = false;       /* is ind selected? */
      slot->ind_is_waiting  = false;       /* is waiting?     */
      slot->ind_has_arrived = false;       /* callback has arrived */
      slot->recv_ind_id = 0;       /* ind to wait for   */
      slot->recv_ind_payload_ptr = NULL;
      slot->req_id =  0;   /* req id   */
   }

   loc_sync_call_initialized = true;
   pthread_mutex_unlock(&loc_sync_call_mutex);
}


/*===========================================================================

FUNCTION    loc_sync_process_ind

DESCRIPTION
   Wakes up blocked API calls to check if the needed callback has arrived

DEPENDENCIES
   N/A

RETURN VALUE
   none

SIDE EFFECTS
   N/A

===========================================================================*/
void loc_sync_process_ind(
      locClientHandleType    client_handle, /* handle of the client */
      uint32_t               ind_id ,      /* ind id */
      void                   *ind_payload_ptr /* payload              */
)
{

   LOC_LOGV("%s:%d]: received indication, handle = %p ind_id = %u \n",
                 __func__,__LINE__, client_handle, ind_id);

   pthread_mutex_lock(&loc_sync_call_mutex);

   if (!loc_sync_array.in_use)
   {
      LOC_LOGD("%s:%d]: loc_sync_array not in use \n",
                    __func__, __LINE__);
      pthread_mutex_unlock(&loc_sync_call_mutex);
      return;
   }

   bool in_use = false, consumed = false;
   int i;

   for (i = 0; i < LOC_SYNC_REQ_BUFFER_SIZE && !consumed; i++)
   {
      loc_sync_req_data_s_type *slot = &loc_sync_array.slots[i];

      in_use |= loc_sync_array.slot_in_use[i];

      pthread_mutex_lock(&slot->sync_req_lock);

      if ( (loc_sync_array.slot_in_use[i]) && (slot->client_handle == client_handle)
            && (ind_id == slot->recv_ind_id) && (!slot->ind_has_arrived))
      {
         // copy the payload to the slot waiting for this ind
         size_t payload_size = 0;

         LOC_LOGV("%s:%d]: found slot %d selected for ind %u \n",
                       __func__, __LINE__, i, ind_id);

         if(true == locClientGetSizeByRespIndId(ind_id, &payload_size) &&
            NULL != slot->recv_ind_payload_ptr && NULL != ind_payload_ptr)
         {
            LOC_LOGV("%s:%d]: copying ind payload size = %u \n",
                          __func__, __LINE__, payload_size);

            memcpy(slot->recv_ind_payload_ptr, ind_payload_ptr, payload_size);

            consumed = true;

         }
         /* Received a callback while waiting, wake up thread to check it */
         if (slot->ind_is_waiting)
         {
            slot->recv_ind_id = ind_id;

            pthread_cond_signal(&slot->ind_arrived_cond);
         }
         else
         {
            /* If callback arrives before wait, remember it */
            LOC_LOGV("%s:%d]: ind %u arrived before wait was called \n",
                          __func__, __LINE__, ind_id);

            slot->ind_has_arrived = true;
         }
      }
      pthread_mutex_unlock(&slot->sync_req_lock);
   }

   if (!in_use) {
      loc_sync_array.in_use = false;
   }

   pthread_mutex_unlock(&loc_sync_call_mutex);
}

/*===========================================================================

FUNCTION    loc_alloc_slot

DESCRIPTION
   Allocates a buffer slot for the synchronous API call

DEPENDENCIES
   N/A

RETURN VALUE
   Select ID (>=0)     : successful
   -1                  : buffer full

SIDE EFFECTS
   N/A

===========================================================================*/
static int loc_alloc_slot()
{
   int i, select_id = -1; /* no free buffer */

   pthread_mutex_lock(&loc_sync_call_mutex);

   for (i = 0; i < LOC_SYNC_REQ_BUFFER_SIZE; i++)
   {
      if (!loc_sync_array.slot_in_use[i])
      {
         select_id = i;
         loc_sync_array.slot_in_use[i] = 1;
         loc_sync_array.in_use = true;
         break;
      }
   }

   pthread_mutex_unlock(&loc_sync_call_mutex);
   LOC_LOGV("%s:%d]: returning slot %d\n",
                 __func__, __LINE__, select_id);
   return select_id;
}

/*===========================================================================

FUNCTION    loc_free_slot

DESCRIPTION
   Frees a buffer slot after the synchronous API call

DEPENDENCIES
   N/A

RETURN VALUE
   None

SIDE EFFECTS
   N/A

===========================================================================*/
static void loc_free_slot(int select_id)
{
   int i;
   loc_sync_req_data_s_type *slot;

   pthread_mutex_lock(&loc_sync_call_mutex);

   LOC_LOGD("%s:%d]: freeing slot %d\n", __func__, __LINE__, select_id);

   loc_sync_array.slot_in_use[select_id] = 0;

   slot = &loc_sync_array.slots[select_id];

   slot->client_handle = LOC_CLIENT_INVALID_HANDLE_VALUE;
   slot->ind_is_selected = false;       /* is ind selected? */
   slot->ind_is_waiting  = false;       /* is waiting?     */
   slot->ind_has_arrived = false;       /* callback has arrived */
   slot->recv_ind_id = 0;       /* ind to wait for   */
   slot->recv_ind_payload_ptr = NULL;
   slot->req_id =  0;

   // check if all slots are now free
   for (i = 0; i < LOC_SYNC_REQ_BUFFER_SIZE; i++)
   {
      if (loc_sync_array.slot_in_use[i]) break;
   }

   if (i >= LOC_SYNC_REQ_BUFFER_SIZE)
   {
      loc_sync_array.in_use = false;
   }

   pthread_mutex_unlock(&loc_sync_call_mutex);
}

/*===========================================================================

FUNCTION    loc_sync_select_ind

DESCRIPTION
   Selects which indication to wait for.


DEPENDENCIES
   N/A

RETURN VALUE
   Select ID (>=0)     : successful
   -ENOMEM                  : out of buffer

SIDE EFFECTS
   N/A

===========================================================================*/
static int loc_sync_select_ind(
      locClientHandleType       client_handle,   /* Client handle */
      uint32_t                  ind_id,  /* ind Id wait for */
      uint32_t                  req_id,   /* req id */
      void *                    ind_payload_ptr /* ptr where payload should be copied to*/
)
{
   int select_id = loc_alloc_slot();

   LOC_LOGV("%s:%d]: client handle %p, ind_id %u, req_id %u \n",
                 __func__, __LINE__, client_handle, ind_id, req_id);

   if (select_id < 0)
   {
      LOC_LOGE("%s:%d]: buffer full for this synchronous req %s \n",
                 __func__, __LINE__, loc_get_v02_event_name(req_id));
      return -ENOMEM;
   }

   loc_sync_req_data_s_type *slot = &loc_sync_array.slots[select_id];

   pthread_mutex_lock(&slot->sync_req_lock);

   slot->client_handle = client_handle;
   slot->ind_is_selected = true;
   slot->ind_is_waiting = false;
   slot->ind_has_arrived = false;

   slot->recv_ind_id = ind_id;
   slot->req_id      = req_id;
   slot->recv_ind_payload_ptr = ind_payload_ptr; //store the payload ptr

   pthread_mutex_unlock(&slot->sync_req_lock);

   return select_id;
}


/*===========================================================================

FUNCTION    loc_sync_wait_for_ind

DESCRIPTION
   Waits for a selected indication. The wait expires in timeout_seconds seconds.
   If the function is called before an existing wait has finished, it will
   immediately return error.

DEPENDENCIES
   N/A

RETURN VALUE
  0 on SUCCESS, -ve value on failure

SIDE EFFECTS
   N/A

===========================================================================*/
static int loc_sync_wait_for_ind(
      int select_id,        /* ID from loc_sync_select_ind() */
      int timeout_seconds,  /* Timeout in this number of seconds  */
      uint32_t ind_id
)
{
   if (select_id < 0 || select_id >= LOC_SYNC_REQ_BUFFER_SIZE || !loc_sync_array.slot_in_use[select_id])
   {
      LOC_LOGE("%s:%d]: invalid select_id: %d \n",
                    __func__, __LINE__, select_id);

      return (-EINVAL);
   }

   loc_sync_req_data_s_type *slot = &loc_sync_array.slots[select_id];

   int ret_val = 0;  /* the return value of this function: 0 = no error */
   int rc;          /* return code from pthread calls */

   struct timeval present_time;
   struct timespec expire_time;

   pthread_mutex_lock(&slot->sync_req_lock);

  do
  {
      if (slot->ind_has_arrived)
      {
         ret_val = 0;    /* success */
         break;
      }

      if (slot->ind_is_waiting)
      {
         LOC_LOGW("%s:%d]: already waiting in this slot %d\n", __func__,
                       __LINE__, select_id);
         ret_val = -EBUSY; // busy
         break;
      }

      /* Calculate absolute expire time */
      gettimeofday(&present_time, NULL);
      expire_time.tv_sec  = present_time.tv_sec;
      expire_time.tv_nsec = present_time.tv_usec * 1000;
      expire_time.tv_sec += timeout_seconds;

      /* Take new wait request */
      slot->ind_is_waiting = true;

      /* Waiting */
      rc = pthread_cond_timedwait(&slot->ind_arrived_cond,
            &slot->sync_req_lock, &expire_time);

      slot->ind_is_waiting = false;

      if(rc == ETIMEDOUT)
      {
         LOC_LOGE("%s:%d]: slot %d, timed out for ind_id %s\n",
                    __func__, __LINE__, select_id, loc_get_v02_event_name(ind_id));
         ret_val = -ETIMEDOUT; //time out
      }

  } while (0);

   pthread_mutex_unlock(&slot->sync_req_lock);
   loc_free_slot(select_id);

   return ret_val;
}

/*===========================================================================

FUNCTION    loc_sync_send_req

DESCRIPTION
   Synchronous req call (thread safe)

DEPENDENCIES
   N/A

RETURN VALUE
   Loc API 2.0 status

SIDE EFFECTS
   N/A

===========================================================================*/
locClientStatusEnumType loc_sync_send_req
(
      locClientHandleType       client_handle,
      uint32_t                  req_id,        /* req id */
      locClientReqUnionType     req_payload,
      uint32_t                  timeout_msec,
      uint32_t                  ind_id,  //ind ID to block for, usually the same as req_id */
      void                      *ind_payload_ptr /* can be NULL*/
)
{
   locClientStatusEnumType status = eLOC_CLIENT_SUCCESS ;
   int select_id;
   int rc = 0;

   // Select the callback we are waiting for
   select_id = loc_sync_select_ind(client_handle, ind_id, req_id,
                                   ind_payload_ptr);

   if (select_id >= 0)
   {
      status =  locClientSendReq (client_handle, req_id, req_payload);
      LOC_LOGV("%s:%d]: select_id = %d,locClientSendReq returned %d\n",
                    __func__, __LINE__, select_id, status);

      if (status != eLOC_CLIENT_SUCCESS )
      {
         loc_free_slot(select_id);
      }
      else
      {
         // Wait for the indication callback
         if (( rc = loc_sync_wait_for_ind( select_id,
                                           timeout_msec / 1000,
                                           ind_id) ) < 0)
         {
            if ( rc == -ETIMEDOUT)
               status = eLOC_CLIENT_FAILURE_TIMEOUT;
            else
               status = eLOC_CLIENT_FAILURE_INTERNAL;

            // Callback waiting failed
            LOC_LOGE("%s:%d]: loc_api_wait_for_ind failed, err %d, "
                     "select id %d, status %s", __func__, __LINE__, rc ,
                     select_id, loc_get_v02_client_status_name(status));
         }
         else
         {
            status =  eLOC_CLIENT_SUCCESS;
            LOC_LOGV("%s:%d]: success (select id %d)\n",
                          __func__, __LINE__, select_id);
         }
      }
   } /* select id */

   return status;
}


