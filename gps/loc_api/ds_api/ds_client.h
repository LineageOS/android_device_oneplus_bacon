/* Copyright (c) 2013, 2015 The Linux Foundation. All rights reserved.
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

/**
 * @file
 * @brief DS client API declaration.
 *
 * @ingroup loc_ds_api
 */

/**
 * @addtogroup loc_ds_api DS client support for location
 * @{
 */

/**
 * @brief Function name for DS client interface query.
 *
 * @sa ds_client_get_interface
 */
#define DS_CLIENT_GET_INTERFACE_FN "ds_client_get_interface"
/**
 * @brief Library name for loading DS client
 */
#define DS_CLIENT_LIB_NAME "libloc_ds_api.so"

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
} ds_client_status_enum_type;

/**
 * @brief Callback function interface for handling DS service indications
 *
 * @param[in] result Operation result (error code).
 * @param[in] cookie Client cookie provided when call is opened.
 *
 * @sa ds_client_cb_data
 */
typedef void ds_client_event_ind_cb_type
(
  ds_client_status_enum_type result,
  void* loc_adapter_cookie
);

/**
 * @brief Client callback function table
 *
 * This structure contains callback functions provided by client of DS client
 * API for delivering event notifications.
 *
 * @sa ds_client_open_call_type
 */
typedef struct {
  ds_client_event_ind_cb_type *event_cb;
} ds_client_cb_data;

/**
 * @brief Initialize the DS client service
 *
 * This function is to be called as a first step by each process that
 * needs to use data services. This call internally calls dsi_init()
 * and prepares the module for making data calls.
 * Needs to be called once for every process
 *
 * @return Operation result
 * @retval E_DS_CLIENT_SUCCESS    On success.
 * @retval E_DS_CLIENT_FAILURE... On error.
 */
typedef ds_client_status_enum_type ds_client_init_type();

/**
 * @brief Prepares for call.
 *
 * Obtains a handle to the dsi_netctrl layer and looks up the profile
 * to make the call. As of now. It only searches for profiles that
 * support emergency calls.
 *
 * Function to open an emergency call. Does the following things:
 * - Obtains a handle to the WDS service
 * - Obtains a list of profiles configured in the modem
 * - Queries each profile and obtains settings to check if emergency calls
 *   are supported
 * - Returns the profile index that supports emergency calls
 * - Returns handle to dsi_netctrl
 *
 * @param[out] client_handle Client handle to initialize.
 * @param[in]  callback      Pointer to callback function table.
 * @param[in]  cookie        Client's cookie for using with callback calls.
 * @param[out] profile_index Pointer to profile index number.
 * @param[out] pdp_type      Pointer to PDP type.
 *
 * @return Operation result
 * @retval E_DS_CLIENT_SUCCESS    On success. Output parameters are initialized.
 * @retval E_DS_CLIENT_FAILURE... On error.
 */
typedef ds_client_status_enum_type ds_client_open_call_type
(
  dsClientHandleType *client_handle,
  const ds_client_cb_data *callback,
  void *cookie,
  int *profile_index,
  int *pdp_type
);

/**
 * @brief Starts a data call using the profile number provided
 *
 * The function uses parameters provided from @a ds_client_open_call_type
 * call result.
 *
 * @param[in] client_handle Client handle
 * @param[in] profile_index Profile index
 * @param[in] pdp_type      PDP type
 *
 * @return Operation result
 * @retval E_DS_CLIENT_SUCCESS    On success.
 * @retval E_DS_CLIENT_FAILURE... On error.
 */
typedef ds_client_status_enum_type ds_client_start_call_type
(
  dsClientHandleType client_handle,
  int profile_index,
  int pdp_type
);

/**
 * @brief Stops a data call associated with the handle
 *
 * @param[in] client_handle Client handle
 *
 * @return Operation result
 * @retval E_DS_CLIENT_SUCCESS    On success.
 * @retval E_DS_CLIENT_FAILURE... On error.
 */
typedef ds_client_status_enum_type ds_client_stop_call_type
(
  dsClientHandleType client_handle
);

/**
 * @brief Releases the handle used for making data calls
 *
 * @param[in,out] client_handle Client handle pointer
 *
 * @return None
 */
typedef void ds_client_close_call_type
(
  dsClientHandleType *client_handle
);

/**
 * @brief DS client functional interface table
 *
 * This table contains all supported DS client operations. If the operation
 * is not supported, the corresponding entry is NULL.
 *
 * @sa ds_client_get_interface
 */
typedef struct
{
  ds_client_init_type       *pfn_init;
  ds_client_open_call_type  *pfn_open_call;
  ds_client_start_call_type *pfn_start_call;
  ds_client_stop_call_type  *pfn_stop_call;
  ds_client_close_call_type *pfn_close_call;
} ds_client_iface_type;

/**
 * @brief Function for accessing DS client functional interface
 *
 * @return Pointer to interface structure.
 */
typedef const ds_client_iface_type *ds_client_get_iface_fn();

/**
 * @brief Function for accessing DS client functional interface
 *
 * @return Pointer to interface structure.
 */
ds_client_get_iface_fn ds_client_get_interface;

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* _DS_CLIENT_H_ */
