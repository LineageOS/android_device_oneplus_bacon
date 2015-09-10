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
 */

#ifndef _DS_CLIENT_H_
#define _DS_CLIENT_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef void* dsClientHandleType;

typedef enum
{
  E_DS_CLIENT_SUCCESS                              = 0,
  /**< Request was successful. */

  E_DS_CLIENT_FAILURE_GENERAL                      = 1,
  /**< Failed because of a general failure. */

  E_DS_CLIENT_FAILURE_UNSUPPORTED                  = 2,
  /**< Failed because the service does not support the command. */

  E_DS_CLIENT_FAILURE_INVALID_PARAMETER            = 3,
  /**< Failed because the request contained invalid parameters. */

  E_DS_CLIENT_FAILURE_ENGINE_BUSY                  = 4,
  /**< Failed because the engine is busy. */

  E_DS_CLIENT_FAILURE_PHONE_OFFLINE                = 5,
  /**< Failed because the phone is offline. */

  E_DS_CLIENT_FAILURE_TIMEOUT                      = 6,
  /**< Failed because of a timeout. */

  E_DS_CLIENT_FAILURE_SERVICE_NOT_PRESENT          = 7,
  /**< Failed because the service is not present. */

  E_DS_CLIENT_FAILURE_SERVICE_VERSION_UNSUPPORTED  = 8,
  /**< Failed because the service version is unsupported. */

  E_DS_CLIENT_FAILURE_CLIENT_VERSION_UNSUPPORTED  =  9,
  /**< Failed because the service does not support client version. */

  E_DS_CLIENT_FAILURE_INVALID_HANDLE               = 10,
  /**< Failed because an invalid handle was specified. */

  E_DS_CLIENT_FAILURE_INTERNAL                     = 11,
  /**< Failed because of an internal error in the service. */

  E_DS_CLIENT_FAILURE_NOT_INITIALIZED              = 12,
  /**< Failed because the service has not been initialized. */

  E_DS_CLIENT_FAILURE_NOT_ENOUGH_MEMORY             = 13,
  /**< Failed because not rnough memory to do the operation.*/

  E_DS_CLIENT_SERVICE_ALREADY_STARTED               = 14,
  /*Service is already started*/

  E_DS_CLIENT_DATA_CALL_CONNECTED                   = 15,

  E_DS_CLIENT_DATA_CALL_DISCONNECTED                = 16,

  E_DS_CLIENT_RETRY_LATER                           = 17
}ds_client_status_enum_type;

typedef enum {
    DATA_CALL_NONE = 0,
    DATA_CALL_OPEN,
    DATA_CALL_CLOSE
}data_call_request_enum_type;

typedef void (*ds_client_event_ind_cb_type)(ds_client_status_enum_type result,
                                             void* loc_adapter_cookie);
typedef struct {
    ds_client_event_ind_cb_type event_cb;
}ds_client_cb_data;

/*
  This function is to be called as a first step by each process that
  needs to use data services. This call internally calls dsi_init()
  and prepares the module for making data calls.
  Needs to be called once for every process
*/
int ds_client_init();

/*
  Obtains a handle to the dsi_netctrl layer and looks up the profile
  to make the call. As of now. It only searches for profiles that
  support emergency calls
 */
ds_client_status_enum_type ds_client_open_call(dsClientHandleType *client_handle,
                                               ds_client_cb_data *callback,
                                               void *loc_adapter_cookie,
                                               int *profile_index,
                                               int *pdp_type);

/*
  Starts a data call using the profile number provided
 */
ds_client_status_enum_type ds_client_start_call(dsClientHandleType client_handle,
                                                int profile_index,
                                                int pdp_type);

/*
  Stops a data call associated with the handle
*/
ds_client_status_enum_type ds_client_stop_call(dsClientHandleType client_handle);

/*
  Releases the handle used for making data calls
*/
void ds_client_close_call(dsClientHandleType *client_handle);

#ifdef __cplusplus
}
#endif

#endif
