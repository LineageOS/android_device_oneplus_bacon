/* Copyright (c) 2013, 2015, The Linux Foundation. All rights reserved.
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

#define LOG_NDEBUG 0
#define LOG_TAG "LocSvc_ds_client"

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <wireless_data_service_v01.h>
#include <utils/Log.h>
#include <log_util.h>
#include <loc_log.h>
#include <qmi_client.h>
#include <qmi_idl_lib.h>
#include <qmi_cci_target_ext.h>
#include <qmi_cci_target.h>
#include <qmi_cci_common.h>
#include <dsi_netctrl.h>
#include <ds_client.h>

#include<sys/time.h>

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

//Timeout to wait for wds service notification from qmi
#define DS_CLIENT_SERVICE_TIMEOUT (4000)
//Max timeout for the service to come up
#define DS_CLIENT_SERVICE_TIMEOUT_TOTAL (40000)
//Timeout for the service to respond to sync msg
#define DS_CLIENT_SYNC_MSG_TIMEOUT (5000)
/*Request messages the WDS client can send to the WDS service*/
typedef union
{
    /*Requests the service for a list of all profiles present*/
    wds_get_profile_list_req_msg_v01 *p_get_profile_list_req;
    /*Requests the service for a profile's settings*/
    wds_get_profile_settings_req_msg_v01 *p_get_profile_settings_req;
}ds_client_req_union_type;

/*Response indications that are sent by the WDS service*/
typedef union
{
    wds_get_profile_list_resp_msg_v01 *p_get_profile_list_resp;
    wds_get_profile_settings_resp_msg_v01 *p_get_profile_setting_resp;
}ds_client_resp_union_type;

static const loc_name_val_s_type event_string_tbl[DSI_EVT_MAX] =
{
    NAME_VAL(DSI_EVT_INVALID),
    NAME_VAL(DSI_EVT_NET_IS_CONN),
    NAME_VAL(DSI_EVT_NET_NO_NET),
    NAME_VAL(DSI_EVT_PHYSLINK_DOWN_STATE),
    NAME_VAL(DSI_EVT_PHYSLINK_UP_STATE),
    NAME_VAL(DSI_EVT_NET_RECONFIGURED),
    NAME_VAL(DSI_EVT_WDS_CONNECTED)
};

typedef struct
{
  ds_client_event_ind_cb_type *event_cb;
  void                        *caller_cookie;
}ds_caller_data;

typedef struct {
    //Global dsi handle
    dsi_hndl_t dsi_net_handle;
    //Handle to caller's data
    ds_caller_data caller_data;
} ds_client_session_data;

static void net_ev_cb
(
  dsi_hndl_t handle,
  void* user_data,
  dsi_net_evt_t evt,
  dsi_evt_payload_t *payload_ptr
)
{
    int i;
    (void)handle;
    (void)user_data;
    (void)payload_ptr;
    ds_caller_data *callback_data = (ds_caller_data *)user_data;

    LOC_LOGD("%s:%d]: Enter. Callback data: %p\n", __func__, __LINE__, callback_data);
    if(evt > DSI_EVT_INVALID && evt < DSI_EVT_MAX)
    {
        LOC_LOGE("%s:%d]: Callback received: %s",
                 __func__, __LINE__,
                 loc_get_name_from_val(event_string_tbl, DSI_EVT_MAX, evt));

        switch(evt) {
        case DSI_EVT_NET_IS_CONN:
        case DSI_EVT_WDS_CONNECTED:
        {
            LOC_LOGD("%s:%d]: Emergency call started\n", __func__, __LINE__);
            callback_data->event_cb(E_DS_CLIENT_DATA_CALL_CONNECTED,
                                    callback_data->caller_cookie);
            break;
        }
        case DSI_EVT_NET_NO_NET:
        {
            LOC_LOGD("%s:%d]: Emergency call stopped\n", __func__, __LINE__);
            callback_data->event_cb(E_DS_CLIENT_DATA_CALL_DISCONNECTED,
                                    callback_data->caller_cookie);
            break;
        }
        default:
            LOC_LOGD("%s:%d]: uninteresting event\n", __func__, __LINE__);
        }
    }
    LOC_LOGD("%s:%d]:Exit\n", __func__, __LINE__);
}

/*This function is called to obtain a handle to the QMI WDS service*/
static ds_client_status_enum_type
ds_client_qmi_ctrl_point_init(qmi_client_type *p_wds_qmi_client)
{
    qmi_client_type wds_qmi_client, notifier = NULL;
    ds_client_status_enum_type status = E_DS_CLIENT_SUCCESS;
    qmi_service_info *p_service_info = NULL;
    uint32_t num_services = 0, num_entries = 0;
    qmi_client_error_type ret = QMI_NO_ERR;
    unsigned char no_signal = 0;
    qmi_client_os_params os_params;
    int timeout = 0;

    LOC_LOGD("%s:%d]:Enter\n", __func__, __LINE__);

    //Get service object for QMI_WDS service
    qmi_idl_service_object_type ds_client_service_object =
        wds_get_service_object_v01();
    if(ds_client_service_object == NULL) {
        LOC_LOGE("%s:%d]: wds_get_service_object_v01 failed\n" ,
                    __func__, __LINE__);
        status  = E_DS_CLIENT_FAILURE_INTERNAL;
        goto err;
    }

    //get service addressing information
    ret = qmi_client_get_service_list(ds_client_service_object, NULL, NULL,
                                      &num_services);
    LOC_LOGD("%s:%d]: qmi_client_get_service_list() first try ret %d, "
                   "num_services %d]\n", __func__, __LINE__, ret, num_services);
    if(ret != QMI_NO_ERR) {
        //Register for service notification
        ret = qmi_client_notifier_init(ds_client_service_object, &os_params, &notifier);
        if (ret != QMI_NO_ERR) {
            LOC_LOGE("%s:%d]: qmi_client_notifier_init failed %d\n",
                              __func__, __LINE__, ret);
            status = E_DS_CLIENT_FAILURE_INTERNAL;
            goto err;
        }

        do {
            QMI_CCI_OS_SIGNAL_CLEAR(&os_params);
            ret = qmi_client_get_service_list(ds_client_service_object, NULL,
                                              NULL, &num_services);
            if(ret != QMI_NO_ERR) {
                QMI_CCI_OS_SIGNAL_WAIT(&os_params, DS_CLIENT_SERVICE_TIMEOUT);
                no_signal = QMI_CCI_OS_SIGNAL_TIMED_OUT(&os_params);
                if(!no_signal)
                    ret = qmi_client_get_service_list(ds_client_service_object, NULL,
                                                      NULL, &num_services);
            }
            timeout += DS_CLIENT_SERVICE_TIMEOUT;
            LOC_LOGV("%s:%d]: qmi_client_get_service_list() returned ret: %d,"
                     "no_signal: %d, total timeout: %d\n", __func__, __LINE__,
                     ret, no_signal, timeout);
        } while( (timeout < DS_CLIENT_SERVICE_TIMEOUT_TOTAL) &&
                 no_signal &&
                 (ret != QMI_NO_ERR) );
    }

    //Handle failure cases
    if(num_services == 0 || ret != QMI_NO_ERR) {
        if(!no_signal) {
            LOC_LOGE("%s:%d]: qmi_client_get_service_list failed even though"
                     "service is up!  Error: %d \n", __func__, __LINE__, ret);
            status = E_DS_CLIENT_FAILURE_INTERNAL;
        }
        else {
            LOC_LOGE("%s:%d]: qmi_client_get_service_list failed after retries"
                     "Error: %d \n", __func__, __LINE__, ret);
            status = E_DS_CLIENT_FAILURE_TIMEOUT;
        }
        goto err;
    }

    LOC_LOGD("%s:%d]: qmi_client_get_service_list succeeded\n", __func__, __LINE__);

    //Success
    p_service_info = (qmi_service_info *)malloc(num_services * sizeof(qmi_service_info));
    if(p_service_info == NULL) {
        LOC_LOGE("%s:%d]: could not allocate memory for serviceInfo !!\n",
               __func__, __LINE__);
        status = E_DS_CLIENT_FAILURE_INTERNAL;
        goto err;
    }
    num_entries = num_services;

    //Populate service info
    ret = qmi_client_get_service_list(ds_client_service_object, p_service_info,
                                     &num_entries, &num_services);
    if(ret != QMI_NO_ERR) {
        LOC_LOGE("%s:%d]: qmi_client_get_service_list failed. ret: %d \n",
                 __func__, __LINE__, ret);
        status = E_DS_CLIENT_FAILURE_INTERNAL;
        goto err;
    }

    //Initialize wds_qmi_client
    LOC_LOGD("%s:%d]: Initializing WDS client with qmi_client_init\n", __func__,
             __LINE__);
    ret = qmi_client_init(&p_service_info[0], ds_client_service_object,
                          NULL, NULL, NULL, &wds_qmi_client);
    if(ret != QMI_NO_ERR) {
        LOC_LOGE("%s:%d]: qmi_client_init Error. ret: %d\n", __func__, __LINE__, ret);
        status = E_DS_CLIENT_FAILURE_INTERNAL;
        goto err;
    }
    LOC_LOGD("%s:%d]: WDS client initialized with qmi_client_init\n", __func__,
         __LINE__);

    //Store WDS QMI client handle in the parameter passed in
    *p_wds_qmi_client = wds_qmi_client;

    status = E_DS_CLIENT_SUCCESS;
    LOC_LOGD("%s:%d]: init success\n", __func__, __LINE__);

    if(notifier)
        qmi_client_release(notifier);

err:
    if(p_service_info)
        free(p_service_info);

    LOC_LOGD("%s:%d]:Exit\n", __func__, __LINE__);
    return status;
}

/*This function reads the error code from within the response struct*/
static ds_client_status_enum_type ds_client_convert_qmi_response(
    uint32_t req_id,
    ds_client_resp_union_type *resp_union)
{
    ds_client_status_enum_type ret = E_DS_CLIENT_FAILURE_GENERAL;
    LOC_LOGD("%s:%d]:Enter\n", __func__, __LINE__);
    switch(req_id)
    {
    case QMI_WDS_GET_PROFILE_LIST_REQ_V01 :
    {
        if(resp_union->p_get_profile_list_resp->resp.error !=
           QMI_ERR_NONE_V01) {
            LOC_LOGE("%s:%d]: Response error: %d", __func__, __LINE__,
                     resp_union->p_get_profile_list_resp->resp.error);
        }
        else
            ret = E_DS_CLIENT_SUCCESS;
    }
    break;

    case QMI_WDS_GET_PROFILE_SETTINGS_REQ_V01 :
    {
        if(resp_union->p_get_profile_setting_resp->resp.error !=
           QMI_ERR_NONE_V01) {
            LOC_LOGE("%s:%d]: Response error: %d", __func__, __LINE__,
                     resp_union->p_get_profile_setting_resp->resp.error);
        }
        else
            ret = E_DS_CLIENT_SUCCESS;
    }
    break;

    default:
        LOC_LOGE("%s:%d]: Unknown request ID\n", __func__, __LINE__);
    }
    LOC_LOGD("%s:%d]:Exit\n", __func__, __LINE__);
    return ret;
}


static ds_client_status_enum_type ds_client_send_qmi_sync_req(
    qmi_client_type *ds_client_handle,
    uint32_t req_id,
    ds_client_resp_union_type *resp_union,
    ds_client_req_union_type *req_union)
{
    uint32_t req_len = 0;
    uint32_t resp_len = 0;
    ds_client_status_enum_type ret = E_DS_CLIENT_SUCCESS;
    qmi_client_error_type qmi_ret = QMI_NO_ERR;
    LOC_LOGD("%s:%d]:Enter\n", __func__, __LINE__);
    switch(req_id)
    {
    case QMI_WDS_GET_PROFILE_LIST_REQ_V01 :
    {
        req_len = sizeof(wds_get_profile_list_req_msg_v01);
        resp_len = sizeof(wds_get_profile_list_resp_msg_v01);
        LOC_LOGD("%s:%d]: req_id = GET_PROFILE_LIST_REQ\n",
                       __func__, __LINE__);
    }
    break;

    case QMI_WDS_GET_PROFILE_SETTINGS_REQ_V01 :
    {
        req_len = sizeof(wds_get_profile_settings_req_msg_v01);
        resp_len = sizeof(wds_get_profile_settings_resp_msg_v01);
        LOC_LOGD("%s:%d]: req_id = GET_PROFILE_SETTINGS_REQ\n",
                       __func__, __LINE__);
    }
    break;

    default:
        LOC_LOGE("%s:%d]: Error unknown req_id=%d\n", __func__, __LINE__,
                       req_id);
        ret = E_DS_CLIENT_FAILURE_INVALID_PARAMETER;
        goto err;
    }

    LOC_LOGD("%s:%d]: req_id=%d, len = %d; resp_len= %d\n", __func__, __LINE__,
             req_id, req_len, resp_len);
    //Send msg through QCCI
    qmi_ret = qmi_client_send_msg_sync(
        *ds_client_handle,
        req_id,
        (void *)req_union->p_get_profile_list_req,
        req_len,
        (void *)resp_union->p_get_profile_list_resp,
        resp_len,
        DS_CLIENT_SYNC_MSG_TIMEOUT);
    LOC_LOGD("%s:%d]: qmi_client_send_msg_sync returned: %d", __func__, __LINE__, qmi_ret);

    if(qmi_ret != QMI_NO_ERR) {
        ret = E_DS_CLIENT_FAILURE_INTERNAL;
        goto err;
    }

    ret = ds_client_convert_qmi_response(req_id, resp_union);

err:
    LOC_LOGD("%s:%d]:Exit\n", __func__, __LINE__);
    return ret;
}

/*This function obtains the list of supported profiles*/
static ds_client_status_enum_type ds_client_get_profile_list(
    qmi_client_type *ds_client_handle,
    ds_client_resp_union_type *profile_list_resp_msg,
    wds_profile_type_enum_v01 profile_type)
{
    ds_client_status_enum_type ret = E_DS_CLIENT_SUCCESS;
    ds_client_req_union_type req_union;
    LOC_LOGD("%s:%d]:Enter\n", __func__, __LINE__);

    req_union.p_get_profile_list_req = NULL;
    req_union.p_get_profile_list_req = (wds_get_profile_list_req_msg_v01 *)
        calloc(1, sizeof(wds_get_profile_list_req_msg_v01));
    if(req_union.p_get_profile_list_req == NULL) {
        LOC_LOGE("%s:%d]: Could not allocate memory for"
                 "wds_get_profile_list_req_msg_v01\n", __func__, __LINE__);
        goto err;
    }
    //Populate required members of the request structure
    req_union.p_get_profile_list_req->profile_type_valid = 1;
    req_union.p_get_profile_list_req->profile_type = profile_type;
    ret = ds_client_send_qmi_sync_req(ds_client_handle,
                                       QMI_WDS_GET_PROFILE_LIST_REQ_V01,
                                       profile_list_resp_msg, &req_union);
    if(ret != E_DS_CLIENT_SUCCESS) {
        LOC_LOGE("%s:%d]: ds_client_send_qmi_req failed. ret: %d\n",
                 __func__, __LINE__, ret);
        goto err;
    }
err:
    LOC_LOGD("%s:%d]:Exit\n", __func__, __LINE__);
    if(req_union.p_get_profile_list_req)
        free(req_union.p_get_profile_list_req);
    return ret;
}

/*This function obtains settings for the profile specified by
 the profile_identifier*/
static ds_client_status_enum_type ds_client_get_profile_settings(
    qmi_client_type *ds_client_handle,
    ds_client_resp_union_type *profile_settings_resp_msg,
    wds_profile_identifier_type_v01 *profile_identifier)
{
    ds_client_status_enum_type ret = E_DS_CLIENT_SUCCESS;
    ds_client_req_union_type req_union;

    LOC_LOGD("%s:%d]:Enter\n", __func__, __LINE__);
    //Since it's a union containing a pointer to a structure,
    //following entities have the same address
    //- req_union
    //- req_union.p_get_profile_settings_req
    //- req_union.p_get_profile_settings_req->profile
    //so we can very well assign req_union = profile_identifier
    req_union.p_get_profile_settings_req =
        (wds_get_profile_settings_req_msg_v01 *)profile_identifier;
    ret = ds_client_send_qmi_sync_req(ds_client_handle,
                                       QMI_WDS_GET_PROFILE_SETTINGS_REQ_V01,
                                       profile_settings_resp_msg, &req_union);
    if(ret != E_DS_CLIENT_SUCCESS) {
        LOC_LOGE("%s:%d]: ds_client_send_qmi_req failed. ret: %d\n",
                 __func__, __LINE__, ret);
        goto err;
    }
err:
    LOC_LOGD("%s:%d]:Exit\n", __func__, __LINE__);
    return ret;
}

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
static ds_client_status_enum_type ds_client_start_call
(
  dsClientHandleType client_handle,
  int profile_index,
  int pdp_type
)
{
    ds_client_status_enum_type ret = E_DS_CLIENT_FAILURE_GENERAL;
    dsi_call_param_value_t param_info;
    dsi_hndl_t dsi_handle;
    ds_client_session_data *ds_global_data = (ds_client_session_data *)client_handle;
    LOC_LOGD("%s:%d]:Enter\n", __func__, __LINE__);
    if(ds_global_data == NULL) {
        LOC_LOGE("%s:%d]: Null callback parameter\n", __func__, __LINE__);
        goto err;
    }
    dsi_handle = ds_global_data->dsi_net_handle;
    //Set profile index as call parameter
    param_info.buf_val = NULL;
    param_info.num_val = profile_index;
    dsi_set_data_call_param(dsi_handle,
                            DSI_CALL_INFO_UMTS_PROFILE_IDX,
                            &param_info);

    //Set IP Version as call parameter
    param_info.buf_val = NULL;
    param_info.num_val = pdp_type;
    dsi_set_data_call_param(dsi_handle,
                            DSI_CALL_INFO_IP_VERSION,
                            &param_info);
    LOC_LOGD("%s:%d]: Starting emergency call with profile index %d; pdp_type:%d\n",
             __func__, __LINE__, profile_index, pdp_type);
    if(dsi_start_data_call(dsi_handle) == DSI_SUCCESS) {
        LOC_LOGD("%s:%d]: Sent request to start data call\n",
                 __func__, __LINE__);
        ret = E_DS_CLIENT_SUCCESS;
    }
    else {
        LOC_LOGE("%s:%d]: Could not send req to start data call \n", __func__, __LINE__);
        ret = E_DS_CLIENT_FAILURE_GENERAL;
        goto err;
    }

err:
    LOC_LOGD("%s:%d]:Exit\n", __func__, __LINE__);
    return ret;

}

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
static  ds_client_status_enum_type ds_client_open_call
(
  dsClientHandleType *client_handle,
  const ds_client_cb_data *callback,
  void *cookie,
  int *profile_index,
  int *pdp_type
)
{
    ds_client_status_enum_type ret = E_DS_CLIENT_FAILURE_GENERAL;
    ds_client_resp_union_type profile_list_resp_msg;
    ds_client_resp_union_type profile_settings_resp_msg;
    wds_profile_identifier_type_v01 profile_identifier;
    uint32_t i=0;
    dsi_hndl_t dsi_handle;
    ds_client_session_data **ds_global_data = (ds_client_session_data **)client_handle;
    unsigned char call_profile_index_found = 0;
    uint32_t emergency_profile_index=0;
    qmi_client_type wds_qmi_client;

    profile_list_resp_msg.p_get_profile_list_resp = NULL;
    profile_settings_resp_msg.p_get_profile_setting_resp = NULL;

    LOC_LOGD("%s:%d]:Enter\n", __func__, __LINE__);
    if(callback == NULL || ds_global_data == NULL) {
        LOC_LOGE("%s:%d]: Null callback parameter\n", __func__, __LINE__);
        goto err;
    }

    ret = ds_client_qmi_ctrl_point_init(&wds_qmi_client);
    if(ret != E_DS_CLIENT_SUCCESS) {
        LOC_LOGE("%s:%d]: ds_client_qmi_ctrl_point_init failed. ret: %d\n",
                 __func__, __LINE__, ret);
        goto err;
    }

    //Allocate memory for the response msg to obtain a list of profiles
    profile_list_resp_msg.p_get_profile_list_resp = (wds_get_profile_list_resp_msg_v01 *)
        calloc(1, sizeof(wds_get_profile_list_resp_msg_v01));
    if(profile_list_resp_msg.p_get_profile_list_resp == NULL) {
        LOC_LOGE("%s:%d]: Could not allocate memory for"
                 "p_get_profile_list_resp\n", __func__, __LINE__);
        ret = E_DS_CLIENT_FAILURE_NOT_ENOUGH_MEMORY;
        goto err;
    }

    LOC_LOGD("%s:%d]: Getting profile list\n", __func__, __LINE__);
    ret = ds_client_get_profile_list(&wds_qmi_client,
                                      &profile_list_resp_msg,
                                      WDS_PROFILE_TYPE_3GPP_V01);
    if(ret != E_DS_CLIENT_SUCCESS) {
        LOC_LOGE("%s:%d]: ds_client_get_profile_list failed. ret: %d\n",
                 __func__, __LINE__, ret);
        goto err;
    }
    LOC_LOGD("%s:%d]: Got profile list; length = %d\n", __func__, __LINE__,
             profile_list_resp_msg.p_get_profile_list_resp->profile_list_len);

    //Allocate memory for the response msg to obtain profile settings
    //We allocate memory for only one response msg and keep re-using it
    profile_settings_resp_msg.p_get_profile_setting_resp =
        (wds_get_profile_settings_resp_msg_v01 *)
        calloc(1, sizeof(wds_get_profile_settings_resp_msg_v01));
    if(profile_settings_resp_msg.p_get_profile_setting_resp == NULL) {
        LOC_LOGE("%s:%d]: Could not allocate memory for"
                 "p_get_profile_setting_resp\n", __func__, __LINE__);
        ret = E_DS_CLIENT_FAILURE_NOT_ENOUGH_MEMORY;
        goto err;
    }

    //Loop over the list of profiles to find a profile that supports
    //emergency calls
    for(i=0; i < profile_list_resp_msg.p_get_profile_list_resp->profile_list_len; i++) {
        /*QMI_WDS_GET_PROFILE_SETTINGS_REQ requires an input data
          structure that is of type wds_profile_identifier_type_v01
          We have to fill that structure for each profile from the
          info obtained from the profile list*/
        //copy profile type
        profile_identifier.profile_type =
            profile_list_resp_msg.p_get_profile_list_resp->profile_list[i].profile_type;
        //copy profile index
        profile_identifier.profile_index =
            profile_list_resp_msg.p_get_profile_list_resp->profile_list[i].profile_index;

        ret = ds_client_get_profile_settings(&wds_qmi_client,
                                             &profile_settings_resp_msg,
                                             &profile_identifier);
        if(ret != E_DS_CLIENT_SUCCESS) {
            LOC_LOGE("%s:%d]: ds_client_get_profile_settings failed. ret: %d\n",
                     __func__, __LINE__, ret);
            goto err;
        }
        LOC_LOGD("%s:%d]: Got profile setting for profile %d; name: %s\n",
                 __func__, __LINE__, i,
                 profile_settings_resp_msg.p_get_profile_setting_resp->profile_name);

        if(profile_settings_resp_msg.p_get_profile_setting_resp->support_emergency_calls_valid) {
            if(profile_settings_resp_msg.p_get_profile_setting_resp->support_emergency_calls) {
                LOC_LOGD("%s:%d]: Found emergency profile in profile %d"
                         , __func__, __LINE__, i);
                call_profile_index_found = 1;
                emergency_profile_index = profile_identifier.profile_index;

                if(profile_settings_resp_msg.p_get_profile_setting_resp->pdp_type_valid) {
                    *pdp_type = (int)profile_settings_resp_msg.p_get_profile_setting_resp->pdp_type;
                    LOC_LOGD("%s:%d]: pdp_type: %d\n", __func__, __LINE__, *pdp_type);
                    switch(*pdp_type) {
                    case WDS_PDP_TYPE_PDP_IPV4_V01:
                        *pdp_type = DSI_IP_VERSION_4;
                        break;
                    case WDS_PDP_TYPE_PDP_IPV6_V01:
                        *pdp_type = DSI_IP_VERSION_6;
                        break;
                    case WDS_PDP_TYPE_PDP_IPV4V6_V01:
                        *pdp_type = DSI_IP_VERSION_4_6;
                        break;
                    default:
                        LOC_LOGE("%s:%d]: pdp_type unknown. Setting default as ipv4/v6\n",
                                 __func__, __LINE__);
                        *pdp_type = DSI_IP_VERSION_4;

                    }
                }
                else {
                    LOC_LOGD("%s:%d]: pdp type not valid in profile setting. Default ipv4\n",
                             __func__, __LINE__);
                    *pdp_type = DSI_IP_VERSION_4;
                }
                //Break out of for loop since we found the emergency profile
                break;
            }
            else
                LOC_LOGE("%s:%d]: Emergency profile valid but not supported in profile: %d "
                         , __func__, __LINE__, i);
        }
        //Since this struct is loaded with settings for the next profile,
        //it is important to clear out the memory to avoid values/flags
        //from being carried over
        memset((void *)profile_settings_resp_msg.p_get_profile_setting_resp,
               0, sizeof(wds_get_profile_settings_resp_msg_v01));
    }

    //Release qmi client handle
    if(qmi_client_release(wds_qmi_client) != QMI_NO_ERR) {
        LOC_LOGE("%s:%d]: Could not release qmi client handle\n",
                 __func__, __LINE__);
        ret = E_DS_CLIENT_FAILURE_GENERAL;
    }

    if(call_profile_index_found) {
        *profile_index = emergency_profile_index;
        *ds_global_data = (ds_client_session_data *)calloc(1, sizeof(ds_client_session_data));
        if(*ds_global_data == NULL) {
            LOC_LOGE("%s:%d]: Could not allocate memory for ds_global_data. Failing\n",
                     __func__, __LINE__);
            ret = E_DS_CLIENT_FAILURE_NOT_ENOUGH_MEMORY;
            goto err;
        }

        (*ds_global_data)->caller_data.event_cb = callback->event_cb;
        (*ds_global_data)->caller_data.caller_cookie = cookie;
        dsi_handle = dsi_get_data_srvc_hndl(net_ev_cb, &(*ds_global_data)->caller_data);
        if(dsi_handle == NULL) {
            LOC_LOGE("%s:%d]: Could not get data handle. Retry Later\n",
                     __func__, __LINE__);
            ret = E_DS_CLIENT_RETRY_LATER;
            goto err;
        }
        else
            (*ds_global_data)->dsi_net_handle = dsi_handle;
    }
    else {
        LOC_LOGE("%s:%d]: Could not find a profile that supports emergency calls",
                 __func__, __LINE__);
        ret = E_DS_CLIENT_FAILURE_GENERAL;
    }
err:
    if(profile_list_resp_msg.p_get_profile_list_resp)
        free(profile_list_resp_msg.p_get_profile_list_resp);
    if(profile_settings_resp_msg.p_get_profile_setting_resp)
        free(profile_settings_resp_msg.p_get_profile_setting_resp);
    LOC_LOGD("%s:%d]:Exit\n", __func__, __LINE__);
    return ret;
}

/**
 * @brief Stops a data call associated with the handle
 *
 * @param[in] client_handle Client handle
 *
 * @return Operation result
 * @retval E_DS_CLIENT_SUCCESS    On success.
 * @retval E_DS_CLIENT_FAILURE... On error.
 */
static ds_client_status_enum_type ds_client_stop_call(dsClientHandleType client_handle)
{
    ds_client_status_enum_type ret = E_DS_CLIENT_SUCCESS;
    ds_client_session_data *p_ds_global_data = (ds_client_session_data *)client_handle;
    LOC_LOGD("%s:%d]:Enter\n", __func__, __LINE__);

    if(client_handle == NULL) {
        LOC_LOGE("%s:%d]: Null argument received. Failing\n", __func__, __LINE__);
        ret = E_DS_CLIENT_FAILURE_GENERAL;
        goto err;
    }

    if(dsi_stop_data_call(p_ds_global_data->dsi_net_handle) == DSI_SUCCESS) {
        LOC_LOGD("%s:%d]: Sent request to stop data call\n", __func__, __LINE__);
    }
    else {
        LOC_LOGE("%s:%d]: Could not send request to stop data call\n",
                 __func__, __LINE__);
        ret = E_DS_CLIENT_FAILURE_GENERAL;
        goto err;
    }

err:
    LOC_LOGD("%s:%d]:Exit\n", __func__, __LINE__);
    return ret;
}

/**
 * @brief Releases the handle used for making data calls
 *
 * @param[in,out] client_handle Client handle pointer
 *
 * @return None
 */
static void ds_client_close_call(dsClientHandleType *client_handle)
{
    ds_client_session_data **ds_global_data = (ds_client_session_data **)client_handle;
    LOC_LOGD("%s:%d]:Enter\n", __func__, __LINE__);
    if(client_handle == NULL || *client_handle == NULL) {
        LOC_LOGE("%s:%d]: Null argument received. Failing\n", __func__, __LINE__);
        goto err;
    }
    dsi_rel_data_srvc_hndl((*ds_global_data)->dsi_net_handle);
    (*ds_global_data)->dsi_net_handle = NULL;
    free(*ds_global_data);
    *ds_global_data = NULL;
    LOC_LOGD("%s:%d]: Released Data handle\n", __func__, __LINE__);
err:
    LOC_LOGD("%s:%d]:Exit\n", __func__, __LINE__);
    return;
}

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
static ds_client_status_enum_type ds_client_init()
{
  ds_client_status_enum_type ret = E_DS_CLIENT_SUCCESS;
  LOC_LOGD("%s:%d]:Enter", __func__, __LINE__);
  if(DSI_SUCCESS != dsi_init(DSI_MODE_GENERAL))
  {
    LOC_LOGE("%s:%d]:dsi_init failed", __func__, __LINE__);
    ret = E_DS_CLIENT_FAILURE_GENERAL;
  }
  LOC_LOGD("%s:%d]:Exit", __func__, __LINE__);
  return ret;
}

/**
 * @brief DS client function interface table definition.
 */
static const ds_client_iface_type iface =
{
  .pfn_init       = ds_client_init,
  .pfn_open_call  = ds_client_open_call,
  .pfn_start_call = ds_client_start_call,
  .pfn_stop_call  = ds_client_stop_call,
  .pfn_close_call = ds_client_close_call
};

/**
 * @brief Function for accessing DS client functional interface
 *
 * @return Pointer to interface structure.
 */
const ds_client_iface_type *ds_client_get_interface()
{
  return &iface;
}

/**
 * @}
 */
