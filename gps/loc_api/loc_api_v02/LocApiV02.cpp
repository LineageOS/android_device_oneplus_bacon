/* Copyright (c) 2011-2014, The Linux Foundation. All rights reserved.
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
 *     * Neither the name of The Linux Foundatoin, nor the names of its
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
#define LOG_TAG "LocSvc_ApiV02"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <hardware/gps.h>

#ifndef USE_GLIB
#include <utils/SystemClock.h>
#endif /* USE_GLIB */
#include <LocApiV02.h>
#include <loc_api_v02_log.h>
#include <loc_api_sync_req.h>
#include <loc_util_log.h>
#include <gps_extended.h>
#include "platform_lib_includes.h"

using namespace loc_core;

/* Default session id ; TBD needs incrementing for each */
#define LOC_API_V02_DEF_SESSION_ID (1)

/* UMTS CP Address key*/
#define LOC_NI_NOTIF_KEY_ADDRESS           "Address"

/* GPS SV Id offset */
#define GPS_SV_ID_OFFSET        (1)

/* GLONASS SV Id offset */
#define GLONASS_SV_ID_OFFSET    (65)

/* SV ID range */
#define SV_ID_RANGE             (32)

#define BDS_SV_ID_OFFSET         (201)

/* BeiDou SV ID RANGE*/
#define BDS_SV_ID_RANGE          QMI_LOC_DELETE_MAX_BDS_SV_INFO_LENGTH_V02

/* GPS week unknown*/
#define C_GPS_WEEK_UNKNOWN      (65535)

/* seconds per week*/
#define WEEK_MSECS              (60*60*24*7*1000)

/* number of QMI_LOC messages that need to be checked*/
#define NUMBER_OF_MSG_TO_BE_CHECKED        (3)

/* static event callbacks that call the LocApiV02 callbacks*/

/* global event callback, call the eventCb function in loc api adapter v02
   instance */
static void globalEventCb(locClientHandleType clientHandle,
                          uint32_t eventId,
                          const locClientEventIndUnionType eventPayload,
                          void*  pClientCookie)
{
  MODEM_LOG_CALLFLOW(%s, loc_get_v02_event_name(eventId));
  LocApiV02 *locApiV02Instance =
      (LocApiV02 *)pClientCookie;

  LOC_LOGV ("%s:%d] client = %p, event id = %d, client cookie ptr = %p\n",
                  __func__,  __LINE__,  clientHandle, eventId, pClientCookie);

  // return if null is passed
  if( NULL == locApiV02Instance)
  {
    LOC_LOGE ("%s:%d] NULL object passed : client = %p, event id = %d\n",
                  __func__,  __LINE__,  clientHandle, eventId);
    return;
  }
  locApiV02Instance->eventCb(clientHandle, eventId, eventPayload);
}

/* global response callback, it calls the sync request process
   indication function to unblock the request that is waiting on this
   response indication*/
static void globalRespCb(locClientHandleType clientHandle,
                         uint32_t respId,
                         const locClientRespIndUnionType respPayload,
                         void*  pClientCookie)
{
  MODEM_LOG_CALLFLOW(%s, loc_get_v02_event_name(respId));
  LocApiV02 *locApiV02Instance =
        (LocApiV02 *)pClientCookie;


  LOC_LOGV ("%s:%d] client = %p, resp id = %d, client cookie ptr = %p\n",
                  __func__,  __LINE__,  clientHandle, respId, pClientCookie);

  if( NULL == locApiV02Instance)
  {
    LOC_LOGE ("%s:%d] NULL object passed : client = %p, resp id = %d\n",
                  __func__,  __LINE__,  clientHandle, respId);
    return;
  }
    // process the sync call
    // use pDeleteAssistDataInd as a dummy pointer
  loc_sync_process_ind(clientHandle, respId,
                       (void *)respPayload.pDeleteAssistDataInd);
}

/* global error callback, it will call the handle service down
   function in the loc api adapter instance. */
static void globalErrorCb (locClientHandleType clientHandle,
                           locClientErrorEnumType errorId,
                           void *pClientCookie)
{
  LocApiV02 *locApiV02Instance =
          (LocApiV02 *)pClientCookie;

  LOC_LOGV ("%s:%d] client = %p, error id = %d\n, client cookie ptr = %p\n",
                  __func__,  __LINE__,  clientHandle, errorId, pClientCookie);
  if( NULL == locApiV02Instance)
  {
    LOC_LOGE ("%s:%d] NULL object passed : client = %p, error id = %d\n",
                  __func__,  __LINE__,  clientHandle, errorId);
    return;
  }
  locApiV02Instance->errorCb(clientHandle, errorId);
}

/* global structure containing the callbacks */
locClientCallbacksType globalCallbacks =
{
    sizeof(locClientCallbacksType),
    globalEventCb,
    globalRespCb,
    globalErrorCb
};

/* Constructor for LocApiV02 */
LocApiV02 :: LocApiV02(const MsgTask* msgTask,
                       LOC_API_ADAPTER_EVENT_MASK_T exMask,
                       ContextBase* context):
    LocApiBase(msgTask, exMask, context),
    clientHandle(LOC_CLIENT_INVALID_HANDLE_VALUE),
    dsClientHandle(NULL), mGnssMeasurementSupported(sup_unknown),
    mQmiMask(0), mInSession(false), mEngineOn(false)
{
  // initialize loc_sync_req interface
  loc_sync_req_init();
}

/* Destructor for LocApiV02 */
LocApiV02 :: ~LocApiV02()
{
    close();
}

LocApiBase* getLocApi(const MsgTask *msgTask,
                      LOC_API_ADAPTER_EVENT_MASK_T exMask,
                      ContextBase* context)
{
    LOC_LOGD("%s:%d]: Creating new LocApiV02", __func__, __LINE__);
    return new LocApiV02(msgTask, exMask, context);
}

/* Initialize a loc api v02 client AND
   check which loc message are supported by modem */
enum loc_api_adapter_err
LocApiV02 :: open(LOC_API_ADAPTER_EVENT_MASK_T mask)
{
  enum loc_api_adapter_err rtv = LOC_API_ADAPTER_ERR_SUCCESS;
  LOC_API_ADAPTER_EVENT_MASK_T newMask = mMask | (mask & ~mExcludedMask);
  locClientEventMaskType qmiMask = convertMask(newMask);
  LOC_LOGD("%s:%d]: Enter mMask: %x; mask: %x; newMask: %x mQmiMask: %lld qmiMask: %lld",
           __func__, __LINE__, mMask, mask, newMask, mQmiMask, qmiMask);
  /* If the client is already open close it first */
  if(LOC_CLIENT_INVALID_HANDLE_VALUE == clientHandle)
  {
    locClientStatusEnumType status = eLOC_CLIENT_SUCCESS;

    LOC_LOGV ("%s:%d]: reference to this = %p passed in \n",
              __func__, __LINE__, this);
    /* initialize the loc api v02 interface, note that
       the locClientOpen() function will block if the
       service is unavailable for a fixed time out */

    // it is important to cap the mask here, because not all LocApi's
    // can enable the same bits, e.g. foreground and bckground.
    status = locClientOpen(adjustMaskForNoSession(qmiMask), &globalCallbacks,
                           &clientHandle, (void *)this);
    mMask = newMask;
    mQmiMask = qmiMask;
    if (eLOC_CLIENT_SUCCESS != status ||
        clientHandle == LOC_CLIENT_INVALID_HANDLE_VALUE )
    {
      mMask = 0;
      mQmiMask = 0;
      LOC_LOGE ("%s:%d]: locClientOpen failed, status = %s\n", __func__,
                __LINE__, loc_get_v02_client_status_name(status));
      rtv = LOC_API_ADAPTER_ERR_FAILURE;
    } else {
        uint64_t supportedMsgList = 0;
        const uint32_t msgArray[NUMBER_OF_MSG_TO_BE_CHECKED] =
        {
            // For - LOC_API_ADAPTER_MESSAGE_LOCATION_BATCHING
            QMI_LOC_GET_BATCH_SIZE_REQ_V02,

            // For - LOC_API_ADAPTER_MESSAGE_BATCHED_GENFENCE_BREACH
            QMI_LOC_EVENT_GEOFENCE_BATCHED_BREACH_NOTIFICATION_IND_V02,

            // For - LOC_API_ADAPTER_MESSAGE_DISTANCE_BASE_TRACKING
            QMI_LOC_START_DBT_REQ_V02
        };

        // check the modem
        status = locClientSupportMsgCheck(clientHandle,
                                          msgArray,
                                          NUMBER_OF_MSG_TO_BE_CHECKED,
                                          &supportedMsgList);
        if (eLOC_CLIENT_SUCCESS != status) {
            LOC_LOGE("%s:%d]: Failed to checking QMI_LOC message supported. \n",
                     __func__, __LINE__);
        }

        /** if batching is supported , check if the adaptive batching or
            distance-based batching is supported. */
        uint32_t messageChecker = 1 << LOC_API_ADAPTER_MESSAGE_LOCATION_BATCHING;
        if ((messageChecker & supportedMsgList) == messageChecker) {
            locClientReqUnionType req_union;
            locClientStatusEnumType status = eLOC_CLIENT_SUCCESS;
            qmiLocQueryAonConfigReqMsgT_v02 queryAonConfigReq;
            qmiLocQueryAonConfigIndMsgT_v02 queryAonConfigInd;

            memset(&queryAonConfigReq, 0, sizeof(queryAonConfigReq));
            memset(&queryAonConfigInd, 0, sizeof(queryAonConfigInd));
            queryAonConfigReq.transactionId = LOC_API_V02_DEF_SESSION_ID;

            req_union.pQueryAonConfigReq = &queryAonConfigReq;
            status = loc_sync_send_req(clientHandle,
                                       QMI_LOC_QUERY_AON_CONFIG_REQ_V02,
                                       req_union,
                                       LOC_ENGINE_SYNC_REQUEST_TIMEOUT,
                                       QMI_LOC_QUERY_AON_CONFIG_IND_V02,
                                       &queryAonConfigInd);

            if (status == eLOC_CLIENT_FAILURE_UNSUPPORTED) {
                LOC_LOGE("%s:%d]: Query AON config is not supported.\n", __func__, __LINE__);
            } else {
                if (status != eLOC_CLIENT_SUCCESS ||
                    queryAonConfigInd.status != eQMI_LOC_SUCCESS_V02) {
                    LOC_LOGE("%s:%d]: Query AON config failed."
                             " status: %s, ind status:%s\n",
                             __func__, __LINE__,
                             loc_get_v02_client_status_name(status),
                             loc_get_v02_qmi_status_name(queryAonConfigInd.status));
                } else {
                    LOC_LOGD("%s:%d]: Query AON config succeeded.\n", __func__, __LINE__);
                    if (queryAonConfigInd.aonCapability_valid) {
                        if (queryAonConfigInd.aonCapability |
                            QMI_LOC_MASK_AON_TIME_BASED_BATCHING_SUPPORTED_V02) {
                            LOC_LOGD("%s:%d]: LB 1.0 is supported.\n", __func__, __LINE__);
                        }
                        if (queryAonConfigInd.aonCapability |
                            QMI_LOC_MASK_AON_AUTO_BATCHING_SUPPORTED_V02) {
                            LOC_LOGD("%s:%d]: LB 1.5 is supported.\n", __func__, __LINE__);
                            supportedMsgList |=
                                (1 << LOC_API_ADAPTER_MESSAGE_ADAPTIVE_LOCATION_BATCHING);
                        }
                        if (queryAonConfigInd.aonCapability |
                            QMI_LOC_MASK_AON_DISTANCE_BASED_BATCHING_SUPPORTED_V02) {
                            LOC_LOGD("%s:%d]: LB 2.0 is supported.\n", __func__, __LINE__);
                            supportedMsgList |=
                                (1 << LOC_API_ADAPTER_MESSAGE_DISTANCE_BASE_LOCATION_BATCHING);
                        }
                        if (queryAonConfigInd.aonCapability |
                            QMI_LOC_MASK_AON_DISTANCE_BASED_TRACKING_SUPPORTED_V02) {
                            LOC_LOGD("%s:%d]: DBT 2.0 is supported.\n", __func__, __LINE__);
                        }
                    } else {
                        LOC_LOGE("%s:%d]: AON capability is invalid.\n", __func__, __LINE__);
                    }
                }
            }
        }
        LOC_LOGV("%s:%d]: supportedMsgList is %lld. \n",
                 __func__, __LINE__, supportedMsgList);
        // save the supported message list
        saveSupportedMsgList(supportedMsgList);
    }
  } else if (newMask != mMask) {
    // it is important to cap the mask here, because not all LocApi's
    // can enable the same bits, e.g. foreground and background.
    if (!registerEventMask(qmiMask)) {
      // we do not update mMask here, because it did not change
      // as the mask update has failed.
      rtv = LOC_API_ADAPTER_ERR_FAILURE;
    }
    else {
        mMask = newMask;
        mQmiMask = qmiMask;
    }
  }
  LOC_LOGD("%s:%d]: Exit mMask: %x; mask: %x mQmiMask: %llx qmiMask: %llx",
           __func__, __LINE__, mMask, mask, mQmiMask, qmiMask);

  if (LOC_API_ADAPTER_ERR_SUCCESS == rtv) {
      cacheGnssMeasurementSupport();
  }

  return rtv;
}

bool LocApiV02 :: registerEventMask(locClientEventMaskType qmiMask)
{
    if (!mInSession) {
        qmiMask = adjustMaskForNoSession(qmiMask);
    }
    LOC_LOGD("%s:%d]: mQmiMask=%lld qmiMask=%lld",
             __func__, __LINE__, mQmiMask, qmiMask);
    return locClientRegisterEventMask(clientHandle, qmiMask);
}

locClientEventMaskType LocApiV02 :: adjustMaskForNoSession(locClientEventMaskType qmiMask)
{
    LOC_LOGD("%s:%d]: before qmiMask=%lld",
             __func__, __LINE__, qmiMask);
    locClientEventMaskType clearMask = QMI_LOC_EVENT_MASK_POSITION_REPORT_V02 |
                                       QMI_LOC_EVENT_MASK_GNSS_SV_INFO_V02 |
                                       QMI_LOC_EVENT_MASK_NMEA_V02 |
                                       QMI_LOC_EVENT_MASK_ENGINE_STATE_V02 |
                                       QMI_LOC_EVENT_MASK_GNSS_MEASUREMENT_REPORT_V02;

    qmiMask = qmiMask & ~clearMask;
    LOC_LOGD("%s:%d]: after qmiMask=%lld",
             __func__, __LINE__, qmiMask);
    return qmiMask;
}

enum loc_api_adapter_err LocApiV02 :: close()
{
  enum loc_api_adapter_err rtv =
      // success if either client is already invalid, or
      // we successfully close the handle
      (LOC_CLIENT_INVALID_HANDLE_VALUE == clientHandle ||
       eLOC_CLIENT_SUCCESS == locClientClose(&clientHandle)) ?
      LOC_API_ADAPTER_ERR_SUCCESS : LOC_API_ADAPTER_ERR_FAILURE;

  mMask = 0;
  clientHandle = LOC_CLIENT_INVALID_HANDLE_VALUE;

  return rtv;
}

/* start positioning session */
enum loc_api_adapter_err LocApiV02 :: startFix(const LocPosMode& fixCriteria)
{
  locClientStatusEnumType status;
  locClientReqUnionType req_union;

  qmiLocStartReqMsgT_v02 start_msg;

  qmiLocSetOperationModeReqMsgT_v02 set_mode_msg;
  qmiLocSetOperationModeIndMsgT_v02 set_mode_ind;

    // clear all fields, validity masks
  memset (&start_msg, 0, sizeof(start_msg));
  memset (&set_mode_msg, 0, sizeof(set_mode_msg));
  memset (&set_mode_ind, 0, sizeof(set_mode_ind));

  LOC_LOGV("%s:%d]: start \n", __func__, __LINE__);
  fixCriteria.logv();

  mInSession = true;
  registerEventMask(mQmiMask);

  // fill in the start request
  switch(fixCriteria.mode)
  {
    case LOC_POSITION_MODE_MS_BASED:
      set_mode_msg.operationMode = eQMI_LOC_OPER_MODE_MSB_V02;
      break;

    case LOC_POSITION_MODE_MS_ASSISTED:
      set_mode_msg.operationMode = eQMI_LOC_OPER_MODE_MSA_V02;
      break;

    case LOC_POSITION_MODE_RESERVED_4:
      set_mode_msg.operationMode = eQMI_LOC_OPER_MODE_CELL_ID_V02;
        break;

    case LOC_POSITION_MODE_RESERVED_5:
      set_mode_msg.operationMode = eQMI_LOC_OPER_MODE_WWAN_V02;
        break;

    default:
      set_mode_msg.operationMode = eQMI_LOC_OPER_MODE_STANDALONE_V02;
      break;
  }

  req_union.pSetOperationModeReq = &set_mode_msg;

  // send the mode first, before the start message.
  status = loc_sync_send_req(clientHandle,
                             QMI_LOC_SET_OPERATION_MODE_REQ_V02,
                             req_union, LOC_ENGINE_SYNC_REQUEST_TIMEOUT,
                             QMI_LOC_SET_OPERATION_MODE_IND_V02,
                             &set_mode_ind); // NULL?
   //When loc_sync_send_req status is time out, more likely the response was lost.
   //startFix will continue as though it is succeeded.
  if ((status != eLOC_CLIENT_SUCCESS && status != eLOC_CLIENT_FAILURE_TIMEOUT) ||
       eQMI_LOC_SUCCESS_V02 != set_mode_ind.status)
  {
    LOC_LOGE ("%s:%d]: set opertion mode failed status = %s, "
                   "ind..status = %s\n", __func__, __LINE__,
              loc_get_v02_client_status_name(status),
              loc_get_v02_qmi_status_name(set_mode_ind.status));
  } else {
      if (status == eLOC_CLIENT_FAILURE_TIMEOUT)
      {
          LOC_LOGE ("%s:%d]: set operation mode timed out\n", __func__, __LINE__);
      }
      start_msg.minInterval_valid = 1;
      start_msg.minInterval = fixCriteria.min_interval;

      if (fixCriteria.preferred_accuracy >= 0) {
          start_msg.horizontalAccuracyLevel_valid = 1;

          if (fixCriteria.preferred_accuracy <= 100)
          {
              // fix needs high accuracy
              start_msg.horizontalAccuracyLevel =  eQMI_LOC_ACCURACY_HIGH_V02;
          }
          else if (fixCriteria.preferred_accuracy <= 1000)
          {
              //fix needs med accuracy
              start_msg.horizontalAccuracyLevel =  eQMI_LOC_ACCURACY_MED_V02;
          }
          else
          {
              //fix needs low accuracy
              start_msg.horizontalAccuracyLevel =  eQMI_LOC_ACCURACY_LOW_V02;
          }
      }

      start_msg.fixRecurrence_valid = 1;
      if(GPS_POSITION_RECURRENCE_SINGLE == fixCriteria.recurrence)
      {
          start_msg.fixRecurrence = eQMI_LOC_RECURRENCE_SINGLE_V02;
      }
      else
      {
          start_msg.fixRecurrence = eQMI_LOC_RECURRENCE_PERIODIC_V02;
      }

      //dummy session id
      // TBD: store session ID, check for session id in pos reports.
      start_msg.sessionId = LOC_API_V02_DEF_SESSION_ID;

      if (fixCriteria.credentials[0] != 0) {
          int size1 = sizeof(start_msg.applicationId.applicationName);
          int size2 = sizeof(fixCriteria.credentials);
          int len = ((size1 < size2) ? size1 : size2) - 1;
          memcpy(start_msg.applicationId.applicationName,
                 fixCriteria.credentials,
                 len);

          size1 = sizeof(start_msg.applicationId.applicationProvider);
          size2 = sizeof(fixCriteria.provider);
          len = ((size1 < size2) ? size1 : size2) - 1;
          memcpy(start_msg.applicationId.applicationProvider,
                 fixCriteria.provider,
                 len);

          start_msg.applicationId_valid = 1;
      }

      // config Altitude Assumed
      start_msg.configAltitudeAssumed_valid = 1;
      start_msg.configAltitudeAssumed = eQMI_LOC_ALTITUDE_ASSUMED_IN_GNSS_SV_INFO_DISABLED_V02;

      req_union.pStartReq = &start_msg;

      status = locClientSendReq (clientHandle, QMI_LOC_START_REQ_V02,
                                 req_union );
  }

  return convertErr(status);
}

/* stop a positioning session */
enum loc_api_adapter_err LocApiV02 :: stopFix()
{
  locClientStatusEnumType status;
  locClientReqUnionType req_union;

  qmiLocStopReqMsgT_v02 stop_msg;

  LOC_LOGD(" %s:%d]: stop called \n", __func__, __LINE__);

  memset(&stop_msg, 0, sizeof(stop_msg));

  // dummy session id
  stop_msg.sessionId = LOC_API_V02_DEF_SESSION_ID;

  req_union.pStopReq = &stop_msg;

  status = locClientSendReq(clientHandle,
                            QMI_LOC_STOP_REQ_V02,
                            req_union);

  mInSession = false;
  // if engine on never happend, deregister events
  // without waiting for Engine Off
  if (!mEngineOn) {
      registerEventMask(mQmiMask);
  }

  if( eLOC_CLIENT_SUCCESS != status)
  {
      LOC_LOGE("%s:%d]: error = %s\n",__func__, __LINE__,
               loc_get_v02_client_status_name(status));
  }

  return convertErr(status);
}

/* set the positioning fix criteria */
enum loc_api_adapter_err LocApiV02 :: setPositionMode(
  const LocPosMode& posMode)
{
    if(isInSession())
    {
        //fix is in progress, send a restart
        LOC_LOGD ("%s:%d]: fix is in progress restarting the fix with new "
                  "criteria\n", __func__, __LINE__);

        return( startFix(posMode));
    }

    return LOC_API_ADAPTER_ERR_SUCCESS;
}

/* inject time into the position engine */
enum loc_api_adapter_err LocApiV02 ::
    setTime(GpsUtcTime time, int64_t timeReference, int uncertainty)
{
  locClientReqUnionType req_union;
  locClientStatusEnumType status;
  qmiLocInjectUtcTimeReqMsgT_v02  inject_time_msg;
  qmiLocInjectUtcTimeIndMsgT_v02 inject_time_ind;

  memset(&inject_time_msg, 0, sizeof(inject_time_msg));

  inject_time_ind.status = eQMI_LOC_GENERAL_FAILURE_V02;

  inject_time_msg.timeUtc = time;

  inject_time_msg.timeUtc += (int64_t)(ELAPSED_MILLIS_SINCE_BOOT_PLATFORM_LIB_ABSTRACTION - timeReference);

  inject_time_msg.timeUnc = uncertainty;

  req_union.pInjectUtcTimeReq = &inject_time_msg;

  LOC_LOGV ("%s:%d]: uncertainty = %d\n", __func__, __LINE__,
                 uncertainty);

  status = loc_sync_send_req(clientHandle,
                             QMI_LOC_INJECT_UTC_TIME_REQ_V02,
                             req_union, LOC_ENGINE_SYNC_REQUEST_TIMEOUT,
                             QMI_LOC_INJECT_UTC_TIME_IND_V02,
                             &inject_time_ind);

  if (status != eLOC_CLIENT_SUCCESS ||
      eQMI_LOC_SUCCESS_V02 != inject_time_ind.status)
  {
    LOC_LOGE ("%s:%d] status = %s, ind..status = %s\n", __func__,  __LINE__,
              loc_get_v02_client_status_name(status),
              loc_get_v02_qmi_status_name(inject_time_ind.status));
  }

  return convertErr(status);
}

/* inject position into the position engine */
enum loc_api_adapter_err LocApiV02 ::
    injectPosition(double latitude, double longitude, float accuracy)
{
  locClientReqUnionType req_union;
  locClientStatusEnumType status;
  qmiLocInjectPositionReqMsgT_v02 inject_pos_msg;
  qmiLocInjectPositionIndMsgT_v02 inject_pos_ind;

  memset(&inject_pos_msg, 0, sizeof(inject_pos_msg));

  inject_pos_msg.latitude_valid = 1;
  inject_pos_msg.latitude = latitude;

  inject_pos_msg.longitude_valid = 1;
  inject_pos_msg.longitude = longitude;

  inject_pos_msg.horUncCircular_valid = 1;

  inject_pos_msg.horUncCircular = accuracy; //meters assumed
  if (inject_pos_msg.horUncCircular < 1000) {
      inject_pos_msg.horUncCircular = 1000;
  }

  inject_pos_msg.horConfidence_valid = 1;

  inject_pos_msg.horConfidence = 68; //1 std dev assumed as specified by API

  inject_pos_msg.rawHorUncCircular_valid = 1;

  inject_pos_msg.rawHorUncCircular = accuracy; //meters assumed

  inject_pos_msg.rawHorConfidence_valid = 1;

  inject_pos_msg.rawHorConfidence = 68; //1 std dev assumed as specified by API

    /* Log */
  LOC_LOGD("%s:%d]: Lat=%lf, Lon=%lf, Acc=%.2lf rawAcc=%.2lf", __func__, __LINE__,
                inject_pos_msg.latitude, inject_pos_msg.longitude,
                inject_pos_msg.horUncCircular, inject_pos_msg.rawHorUncCircular);

  req_union.pInjectPositionReq = &inject_pos_msg;

  status = loc_sync_send_req(clientHandle,
                             QMI_LOC_INJECT_POSITION_REQ_V02,
                             req_union, LOC_ENGINE_SYNC_REQUEST_TIMEOUT,
                             QMI_LOC_INJECT_POSITION_IND_V02,
                             &inject_pos_ind);

  if (status != eLOC_CLIENT_SUCCESS ||
      eQMI_LOC_SUCCESS_V02 != inject_pos_ind.status)
  {
    LOC_LOGE ("%s:%d]: error! status = %s, inject_pos_ind.status = %s\n",
              __func__, __LINE__,
              loc_get_v02_client_status_name(status),
              loc_get_v02_qmi_status_name(inject_pos_ind.status));
  }

  return convertErr(status);
}

/* delete assistance date */
enum loc_api_adapter_err LocApiV02 ::  deleteAidingData(GpsAidingData f)
{
  locClientReqUnionType req_union;
  locClientStatusEnumType status;
  qmiLocDeleteAssistDataReqMsgT_v02 delete_req;
  qmiLocDeleteAssistDataIndMsgT_v02 delete_resp;

  memset(&delete_req, 0, sizeof(delete_req));
  memset(&delete_resp, 0, sizeof(delete_resp));

  if( f == GPS_DELETE_ALL )
  {
    delete_req.deleteAllFlag = true;
  }

  else
  {
    /* to keep track of svInfoList for GPS and GLO*/
    uint32_t curr_sv_len = 0;
    uint32_t curr_sv_idx = 0;
    uint32_t sv_id =  0;

    if((f & GPS_DELETE_EPHEMERIS ) || ( f & GPS_DELETE_ALMANAC ))
    {
      /* do delete for all GPS SV's */

      curr_sv_len += SV_ID_RANGE;

      sv_id = GPS_SV_ID_OFFSET;

      delete_req.deleteSvInfoList_valid = 1;

      delete_req.deleteSvInfoList_len = curr_sv_len;

      LOC_LOGV("%s:%d]: Delete GPS SV info for index %d to %d"
                    "and sv id %d to %d \n",
                    __func__, __LINE__, curr_sv_idx, curr_sv_len - 1,
                    sv_id, sv_id+SV_ID_RANGE-1);

      for( uint32_t i = curr_sv_idx; i< curr_sv_len ; i++, sv_id++ )
      {
        delete_req.deleteSvInfoList[i].gnssSvId = sv_id;

        delete_req.deleteSvInfoList[i].system = eQMI_LOC_SV_SYSTEM_GPS_V02;

        if(f & GPS_DELETE_EPHEMERIS )
        {
          // set ephemeris mask for all GPS SV's
          delete_req.deleteSvInfoList[i].deleteSvInfoMask |=
            QMI_LOC_MASK_DELETE_EPHEMERIS_V02;
        }

        if( f & GPS_DELETE_ALMANAC )
        {
          delete_req.deleteSvInfoList[i].deleteSvInfoMask |=
            QMI_LOC_MASK_DELETE_ALMANAC_V02;
        }
      }
      // increment the current index
      curr_sv_idx += SV_ID_RANGE;

    }

    if(f & GPS_DELETE_POSITION )
    {
      delete_req.deleteGnssDataMask_valid = 1;
      delete_req.deleteGnssDataMask |= QMI_LOC_MASK_DELETE_POSITION_V02;
    }

    if(f & GPS_DELETE_TIME )
    {
      delete_req.deleteGnssDataMask_valid = 1;
      delete_req.deleteGnssDataMask |= QMI_LOC_MASK_DELETE_TIME_V02;
    }

    if(f & GPS_DELETE_IONO )
    {
      delete_req.deleteGnssDataMask_valid = 1;
      delete_req.deleteGnssDataMask |= QMI_LOC_MASK_DELETE_IONO_V02;
    }

    if(f & GPS_DELETE_UTC )
    {
      delete_req.deleteGnssDataMask_valid = 1;
      delete_req.deleteGnssDataMask |= QMI_LOC_MASK_DELETE_UTC_V02;
    }

    if(f & GPS_DELETE_HEALTH )
    {
      delete_req.deleteGnssDataMask_valid = 1;
      delete_req.deleteGnssDataMask |= QMI_LOC_MASK_DELETE_HEALTH_V02;
    }

    if(f & GPS_DELETE_SVDIR )
    {
      delete_req.deleteGnssDataMask_valid = 1;
      delete_req.deleteGnssDataMask |= QMI_LOC_MASK_DELETE_GPS_SVDIR_V02;
    }
    if(f & GPS_DELETE_SADATA )
    {
      delete_req.deleteGnssDataMask_valid = 1;
      delete_req.deleteGnssDataMask |= QMI_LOC_MASK_DELETE_SADATA_V02;
    }
    if(f & GPS_DELETE_RTI )
    {
      delete_req.deleteGnssDataMask_valid = 1;
      delete_req.deleteGnssDataMask |= QMI_LOC_MASK_DELETE_RTI_V02;
    }
    if(f & GPS_DELETE_CELLDB_INFO )
    {
      delete_req.deleteCellDbDataMask_valid = 1;
      delete_req.deleteCellDbDataMask =
        ( QMI_LOC_MASK_DELETE_CELLDB_POS_V02 |
          QMI_LOC_MASK_DELETE_CELLDB_LATEST_GPS_POS_V02 |
          QMI_LOC_MASK_DELETE_CELLDB_OTA_POS_V02 |
          QMI_LOC_MASK_DELETE_CELLDB_EXT_REF_POS_V02 |
          QMI_LOC_MASK_DELETE_CELLDB_TIMETAG_V02 |
          QMI_LOC_MASK_DELETE_CELLDB_CELLID_V02 |
          QMI_LOC_MASK_DELETE_CELLDB_CACHED_CELLID_V02 |
          QMI_LOC_MASK_DELETE_CELLDB_LAST_SRV_CELL_V02 |
          QMI_LOC_MASK_DELETE_CELLDB_CUR_SRV_CELL_V02 |
          QMI_LOC_MASK_DELETE_CELLDB_NEIGHBOR_INFO_V02) ;

    }
#ifndef PDK_FEATURE_SET
#endif

  }

  req_union.pDeleteAssistDataReq = &delete_req;

  status = loc_sync_send_req(clientHandle,
                             QMI_LOC_DELETE_ASSIST_DATA_REQ_V02,
                             req_union, LOC_ENGINE_SYNC_REQUEST_TIMEOUT,
                             QMI_LOC_DELETE_ASSIST_DATA_IND_V02,
                             &delete_resp);

  if (status != eLOC_CLIENT_SUCCESS ||
      eQMI_LOC_SUCCESS_V02 != delete_resp.status)
  {
    LOC_LOGE ("%s:%d]: error! status = %s, delete_resp.status = %s\n",
              __func__, __LINE__,
              loc_get_v02_client_status_name(status),
              loc_get_v02_qmi_status_name(delete_resp.status));
  }

  return convertErr(status);
}

/* send NI user repsonse to the engine */
enum loc_api_adapter_err LocApiV02 ::
    informNiResponse(GpsUserResponseType userResponse,
                     const void* passThroughData)
{
  locClientReqUnionType req_union;
  locClientStatusEnumType status;

  qmiLocNiUserRespReqMsgT_v02 ni_resp;
  qmiLocNiUserRespIndMsgT_v02 ni_resp_ind;

  qmiLocEventNiNotifyVerifyReqIndMsgT_v02 *request_pass_back =
    (qmiLocEventNiNotifyVerifyReqIndMsgT_v02 *)passThroughData;

  memset(&ni_resp,0, sizeof(ni_resp));

  memset(&ni_resp_ind,0, sizeof(ni_resp_ind));

  switch (userResponse)
  {
    case GPS_NI_RESPONSE_ACCEPT:
      ni_resp.userResp = eQMI_LOC_NI_LCS_NOTIFY_VERIFY_ACCEPT_V02;
      break;
   case GPS_NI_RESPONSE_DENY:
      ni_resp.userResp = eQMI_LOC_NI_LCS_NOTIFY_VERIFY_DENY_V02;
      break;
   case GPS_NI_RESPONSE_NORESP:
      ni_resp.userResp = eQMI_LOC_NI_LCS_NOTIFY_VERIFY_NORESP_V02;
      break;
   default:
      return LOC_API_ADAPTER_ERR_INVALID_PARAMETER;
  }

  LOC_LOGV(" %s:%d]: NI response: %d\n", __func__, __LINE__,
                ni_resp.userResp);

  ni_resp.notificationType = request_pass_back->notificationType;

  // copy SUPL payload from request
  if(request_pass_back->NiSuplInd_valid == 1)
  {
     ni_resp.NiSuplPayload_valid = 1;
     memcpy(&(ni_resp.NiSuplPayload), &(request_pass_back->NiSuplInd),
            sizeof(qmiLocNiSuplNotifyVerifyStructT_v02));

  }
  // should this be an "else if"?? we don't need to decide

  // copy UMTS-CP payload from request
  if( request_pass_back->NiUmtsCpInd_valid == 1 )
  {
     ni_resp.NiUmtsCpPayload_valid = 1;
     memcpy(&(ni_resp.NiUmtsCpPayload), &(request_pass_back->NiUmtsCpInd),
            sizeof(qmiLocNiUmtsCpNotifyVerifyStructT_v02));
  }

  //copy Vx payload from the request
  if( request_pass_back->NiVxInd_valid == 1)
  {
     ni_resp.NiVxPayload_valid = 1;
     memcpy(&(ni_resp.NiVxPayload), &(request_pass_back->NiVxInd),
            sizeof(qmiLocNiVxNotifyVerifyStructT_v02));
  }

  // copy Vx service interaction payload from the request
  if(request_pass_back->NiVxServiceInteractionInd_valid == 1)
  {
     ni_resp.NiVxServiceInteractionPayload_valid = 1;
     memcpy(&(ni_resp.NiVxServiceInteractionPayload),
            &(request_pass_back->NiVxServiceInteractionInd),
            sizeof(qmiLocNiVxServiceInteractionStructT_v02));
  }

  // copy Network Initiated SUPL Version 2 Extension
  if (request_pass_back->NiSuplVer2ExtInd_valid == 1)
  {
     ni_resp.NiSuplVer2ExtPayload_valid = 1;
     memcpy(&(ni_resp.NiSuplVer2ExtPayload),
            &(request_pass_back->NiSuplVer2ExtInd),
            sizeof(qmiLocNiSuplVer2ExtStructT_v02));
  }

  // copy SUPL Emergency Notification
  if(request_pass_back->suplEmergencyNotification_valid)
  {
     ni_resp.suplEmergencyNotification_valid = 1;
     memcpy(&(ni_resp.suplEmergencyNotification),
            &(request_pass_back->suplEmergencyNotification),
            sizeof(qmiLocEmergencyNotificationStructT_v02));
  }

  req_union.pNiUserRespReq = &ni_resp;

  status = loc_sync_send_req (
     clientHandle, QMI_LOC_NI_USER_RESPONSE_REQ_V02,
     req_union, LOC_ENGINE_SYNC_REQUEST_TIMEOUT,
     QMI_LOC_NI_USER_RESPONSE_IND_V02, &ni_resp_ind);

  if (status != eLOC_CLIENT_SUCCESS ||
      eQMI_LOC_SUCCESS_V02 != ni_resp_ind.status)
  {
    LOC_LOGE ("%s:%d]: error! status = %s, ni_resp_ind.status = %s\n",
              __func__, __LINE__,
              loc_get_v02_client_status_name(status),
              loc_get_v02_qmi_status_name(ni_resp_ind.status));
  }

  return convertErr(status);
}

/* Set UMTs SLP server URL */
enum loc_api_adapter_err LocApiV02 :: setServer(
  const char* url, int len)
{
  locClientReqUnionType req_union;
  locClientStatusEnumType status;
  qmiLocSetServerReqMsgT_v02 set_server_req;
  qmiLocSetServerIndMsgT_v02 set_server_ind;

  if(len < 0 || len > sizeof(set_server_req.urlAddr))
  {
    LOC_LOGE("%s:%d]: len = %d greater than max allowed url length\n",
                  __func__, __LINE__, len);

    return LOC_API_ADAPTER_ERR_INVALID_PARAMETER;
  }

  memset(&set_server_req, 0, sizeof(set_server_req));

  LOC_LOGD("%s:%d]:, url = %s, len = %d\n", __func__, __LINE__, url, len);

  set_server_req.serverType = eQMI_LOC_SERVER_TYPE_UMTS_SLP_V02;

  set_server_req.urlAddr_valid = 1;

  strlcpy(set_server_req.urlAddr, url, sizeof(set_server_req.urlAddr));

  req_union.pSetServerReq = &set_server_req;

  status = loc_sync_send_req(clientHandle,
                             QMI_LOC_SET_SERVER_REQ_V02,
                             req_union, LOC_ENGINE_SYNC_REQUEST_TIMEOUT,
                             QMI_LOC_SET_SERVER_IND_V02,
                             &set_server_ind);

  if (status != eLOC_CLIENT_SUCCESS ||
         eQMI_LOC_SUCCESS_V02 != set_server_ind.status)
  {
    LOC_LOGE ("%s:%d]: error status = %s, set_server_ind.status = %s\n",
              __func__,__LINE__,
              loc_get_v02_client_status_name(status),
              loc_get_v02_qmi_status_name(set_server_ind.status));
  }

  return convertErr(status);
}

enum loc_api_adapter_err LocApiV02 ::
    setServer(unsigned int ip, int port, LocServerType type)
{
  locClientReqUnionType req_union;
  locClientStatusEnumType status;
  qmiLocSetServerReqMsgT_v02 set_server_req;
  qmiLocSetServerIndMsgT_v02 set_server_ind;
  qmiLocServerTypeEnumT_v02 set_server_cmd;

  switch (type) {
  case LOC_AGPS_MPC_SERVER:
      set_server_cmd = eQMI_LOC_SERVER_TYPE_CDMA_MPC_V02;
      break;
  case LOC_AGPS_CUSTOM_PDE_SERVER:
      set_server_cmd = eQMI_LOC_SERVER_TYPE_CUSTOM_PDE_V02;
      break;
  default:
      set_server_cmd = eQMI_LOC_SERVER_TYPE_CDMA_PDE_V02;
      break;
  }

  memset(&set_server_req, 0, sizeof(set_server_req));

  LOC_LOGD("%s:%d]:, ip = %u, port = %d\n", __func__, __LINE__, ip, port);

  set_server_req.serverType = set_server_cmd;
  set_server_req.ipv4Addr_valid = 1;
  set_server_req.ipv4Addr.addr = ip;
  set_server_req.ipv4Addr.port = port;

  req_union.pSetServerReq = &set_server_req;

  status = loc_sync_send_req(clientHandle,
                             QMI_LOC_SET_SERVER_REQ_V02,
                             req_union, LOC_ENGINE_SYNC_REQUEST_TIMEOUT,
                             QMI_LOC_SET_SERVER_IND_V02,
                             &set_server_ind);

  if (status != eLOC_CLIENT_SUCCESS ||
      eQMI_LOC_SUCCESS_V02 != set_server_ind.status)
  {
    LOC_LOGE ("%s:%d]: error status = %s, set_server_ind.status = %s\n",
              __func__,__LINE__,
              loc_get_v02_client_status_name(status),
              loc_get_v02_qmi_status_name(set_server_ind.status));
  }

  return convertErr(status);
}

/* Inject XTRA data, this module breaks down the XTRA
   file into "chunks" and injects them one at a time */
enum loc_api_adapter_err LocApiV02 :: setXtraData(
  char* data, int length)
{
  locClientStatusEnumType status = eLOC_CLIENT_SUCCESS;
  int     total_parts;
  uint8_t   part;
  uint16_t  len_injected;

  locClientReqUnionType req_union;
  qmiLocInjectPredictedOrbitsDataReqMsgT_v02 inject_xtra;
  qmiLocInjectPredictedOrbitsDataIndMsgT_v02 inject_xtra_ind;

  req_union.pInjectPredictedOrbitsDataReq = &inject_xtra;

  LOC_LOGD("%s:%d]: xtra size = %d\n", __func__, __LINE__, length);

  inject_xtra.formatType_valid = 1;
  inject_xtra.formatType = eQMI_LOC_PREDICTED_ORBITS_XTRA_V02;
  inject_xtra.totalSize = length;

  total_parts = ((length - 1) / QMI_LOC_MAX_PREDICTED_ORBITS_PART_LEN_V02) + 1;

  inject_xtra.totalParts = total_parts;

  len_injected = 0; // O bytes injected

  // XTRA injection starts with part 1
  for (part = 1; part <= total_parts; part++)
  {
    inject_xtra.partNum = part;

    if (QMI_LOC_MAX_PREDICTED_ORBITS_PART_LEN_V02 > (length - len_injected))
    {
      inject_xtra.partData_len = length - len_injected;
    }
    else
    {
      inject_xtra.partData_len = QMI_LOC_MAX_PREDICTED_ORBITS_PART_LEN_V02;
    }

    // copy data into the message
    memcpy(inject_xtra.partData, data+len_injected, inject_xtra.partData_len);

    LOC_LOGD("[%s:%d] part %d/%d, len = %d, total injected = %d\n",
                  __func__, __LINE__,
                  inject_xtra.partNum, total_parts, inject_xtra.partData_len,
                  len_injected);

    status = loc_sync_send_req( clientHandle,
                                QMI_LOC_INJECT_PREDICTED_ORBITS_DATA_REQ_V02,
                                req_union, LOC_ENGINE_SYNC_REQUEST_TIMEOUT,
                                QMI_LOC_INJECT_PREDICTED_ORBITS_DATA_IND_V02,
                                &inject_xtra_ind);

    if (status != eLOC_CLIENT_SUCCESS ||
        eQMI_LOC_SUCCESS_V02 != inject_xtra_ind.status ||
        inject_xtra.partNum != inject_xtra_ind.partNum)
    {
      LOC_LOGE ("%s:%d]: failed status = %s, inject_pos_ind.status = %s,"
                     " part num = %d, ind.partNum = %d\n", __func__, __LINE__,
                loc_get_v02_client_status_name(status),
                loc_get_v02_qmi_status_name(inject_xtra_ind.status),
                inject_xtra.partNum, inject_xtra_ind.partNum);
    } else {
      len_injected += inject_xtra.partData_len;
      LOC_LOGD("%s:%d]: XTRA injected length: %d\n", __func__, __LINE__,
               len_injected);
    }
  }

  return convertErr(status);
}

/* Request the Xtra Server Url from the modem */
enum loc_api_adapter_err LocApiV02 :: requestXtraServer()
{
  locClientStatusEnumType status = eLOC_CLIENT_SUCCESS;

  locClientReqUnionType req_union;
  qmiLocGetPredictedOrbitsDataSourceIndMsgT_v02 request_xtra_server_ind;

  status = loc_sync_send_req( clientHandle,
                              QMI_LOC_GET_PREDICTED_ORBITS_DATA_SOURCE_REQ_V02,
                              req_union, LOC_ENGINE_SYNC_REQUEST_TIMEOUT,
                              QMI_LOC_GET_PREDICTED_ORBITS_DATA_SOURCE_IND_V02,
                              &request_xtra_server_ind);

  if (status == eLOC_CLIENT_SUCCESS &&
      eQMI_LOC_SUCCESS_V02 == request_xtra_server_ind.status &&
      false != request_xtra_server_ind.serverList_valid &&
      0 != request_xtra_server_ind.serverList.serverList_len)
  {
    if (request_xtra_server_ind.serverList.serverList_len == 1)
    {
      reportXtraServer(request_xtra_server_ind.serverList.serverList[0].serverUrl,
                       "",
                       "",
                       QMI_LOC_MAX_SERVER_ADDR_LENGTH_V02);
    }
    else if (request_xtra_server_ind.serverList.serverList_len == 2)
    {
      reportXtraServer(request_xtra_server_ind.serverList.serverList[0].serverUrl,
                       request_xtra_server_ind.serverList.serverList[1].serverUrl,
                       "",
                       QMI_LOC_MAX_SERVER_ADDR_LENGTH_V02);
    }
    else
    {
      reportXtraServer(request_xtra_server_ind.serverList.serverList[0].serverUrl,
                       request_xtra_server_ind.serverList.serverList[1].serverUrl,
                       request_xtra_server_ind.serverList.serverList[2].serverUrl,
                       QMI_LOC_MAX_SERVER_ADDR_LENGTH_V02);
    }
  }

  return convertErr(status);
}

enum loc_api_adapter_err LocApiV02 :: atlOpenStatus(
  int handle, int is_succ, char* apn, AGpsBearerType bear,
  AGpsType agpsType)
{
  locClientStatusEnumType result = eLOC_CLIENT_SUCCESS;
  locClientReqUnionType req_union;
  qmiLocInformLocationServerConnStatusReqMsgT_v02 conn_status_req;
  qmiLocInformLocationServerConnStatusIndMsgT_v02 conn_status_ind;


  LOC_LOGD("%s:%d]: ATL open handle = %d, is_succ = %d, "
                "APN = [%s], bearer = %d \n",  __func__, __LINE__,
                handle, is_succ, apn, bear);

  memset(&conn_status_req, 0, sizeof(conn_status_req));
  memset(&conn_status_ind, 0, sizeof(conn_status_ind));

        // Fill in data
  conn_status_req.connHandle = handle;

  conn_status_req.requestType = eQMI_LOC_SERVER_REQUEST_OPEN_V02;

  if(is_succ)
  {
    conn_status_req.statusType = eQMI_LOC_SERVER_REQ_STATUS_SUCCESS_V02;

    if(apn != NULL)
        strlcpy(conn_status_req.apnProfile.apnName, apn,
                sizeof(conn_status_req.apnProfile.apnName) );

    switch(bear)
    {
    case AGPS_APN_BEARER_IPV4:
        conn_status_req.apnProfile.pdnType =
            eQMI_LOC_APN_PROFILE_PDN_TYPE_IPV4_V02;
        conn_status_req.apnProfile_valid = 1;
        break;

    case AGPS_APN_BEARER_IPV6:
        conn_status_req.apnProfile.pdnType =
            eQMI_LOC_APN_PROFILE_PDN_TYPE_IPV6_V02;
        conn_status_req.apnProfile_valid = 1;
        break;

    case AGPS_APN_BEARER_IPV4V6:
        conn_status_req.apnProfile.pdnType =
            eQMI_LOC_APN_PROFILE_PDN_TYPE_IPV4V6_V02;
        conn_status_req.apnProfile_valid = 1;
        break;

    case AGPS_APN_BEARER_INVALID:
        conn_status_req.apnProfile_valid = 0;
        break;

    default:
        LOC_LOGE("%s:%d]:invalid bearer type\n",__func__,__LINE__);
        conn_status_req.apnProfile_valid = 0;
        return LOC_API_ADAPTER_ERR_INVALID_HANDLE;
    }

  }
  else
  {
    conn_status_req.statusType = eQMI_LOC_SERVER_REQ_STATUS_FAILURE_V02;
  }

  req_union.pInformLocationServerConnStatusReq = &conn_status_req;

  result = loc_sync_send_req(clientHandle,
                             QMI_LOC_INFORM_LOCATION_SERVER_CONN_STATUS_REQ_V02,
                             req_union, LOC_ENGINE_SYNC_REQUEST_TIMEOUT,
                             QMI_LOC_INFORM_LOCATION_SERVER_CONN_STATUS_IND_V02,
                             &conn_status_ind);

  if(result != eLOC_CLIENT_SUCCESS ||
     eQMI_LOC_SUCCESS_V02 != conn_status_ind.status)
  {
    LOC_LOGE ("%s:%d]: Error status = %s, ind..status = %s ",
              __func__, __LINE__,
              loc_get_v02_client_status_name(result),
              loc_get_v02_qmi_status_name(conn_status_ind.status));
  }

  return convertErr(result);

}


/* close atl connection */
enum loc_api_adapter_err LocApiV02 :: atlCloseStatus(
  int handle, int is_succ)
{
  locClientStatusEnumType result = eLOC_CLIENT_SUCCESS;
  locClientReqUnionType req_union;
  qmiLocInformLocationServerConnStatusReqMsgT_v02 conn_status_req;
  qmiLocInformLocationServerConnStatusIndMsgT_v02 conn_status_ind;

  LOC_LOGD("%s:%d]: ATL close handle = %d, is_succ = %d\n",
                 __func__, __LINE__,  handle, is_succ);

  memset(&conn_status_req, 0, sizeof(conn_status_req));
  memset(&conn_status_ind, 0, sizeof(conn_status_ind));

        // Fill in data
  conn_status_req.connHandle = handle;

  conn_status_req.requestType = eQMI_LOC_SERVER_REQUEST_CLOSE_V02;

  if(is_succ)
  {
    conn_status_req.statusType = eQMI_LOC_SERVER_REQ_STATUS_SUCCESS_V02;
  }
  else
  {
    conn_status_req.statusType = eQMI_LOC_SERVER_REQ_STATUS_FAILURE_V02;
  }

  req_union.pInformLocationServerConnStatusReq = &conn_status_req;

  result = loc_sync_send_req(clientHandle,
                             QMI_LOC_INFORM_LOCATION_SERVER_CONN_STATUS_REQ_V02,
                             req_union, LOC_ENGINE_SYNC_REQUEST_TIMEOUT,
                             QMI_LOC_INFORM_LOCATION_SERVER_CONN_STATUS_IND_V02,
                             &conn_status_ind);

  if(result != eLOC_CLIENT_SUCCESS ||
     eQMI_LOC_SUCCESS_V02 != conn_status_ind.status)
  {
    LOC_LOGE ("%s:%d]: Error status = %s, ind..status = %s ",
              __func__, __LINE__,
              loc_get_v02_client_status_name(result),
              loc_get_v02_qmi_status_name(conn_status_ind.status));
  }

  return convertErr(result);
}

/* set the SUPL version */
enum loc_api_adapter_err LocApiV02 :: setSUPLVersion(uint32_t version)
{
  locClientStatusEnumType result = eLOC_CLIENT_SUCCESS;
  locClientReqUnionType req_union;

  qmiLocSetProtocolConfigParametersReqMsgT_v02 supl_config_req;
  qmiLocSetProtocolConfigParametersIndMsgT_v02 supl_config_ind;

  LOC_LOGD("%s:%d]: supl version = %d\n",  __func__, __LINE__, version);


  memset(&supl_config_req, 0, sizeof(supl_config_req));
  memset(&supl_config_ind, 0, sizeof(supl_config_ind));

   supl_config_req.suplVersion_valid = 1;
   // SUPL version from MSByte to LSByte:
   // (reserved)(major version)(minor version)(serviceIndicator)

   supl_config_req.suplVersion = (version == 0x00020000)?
     eQMI_LOC_SUPL_VERSION_2_0_V02 : eQMI_LOC_SUPL_VERSION_1_0_V02;

  req_union.pSetProtocolConfigParametersReq = &supl_config_req;

  result = loc_sync_send_req(clientHandle,
                             QMI_LOC_SET_PROTOCOL_CONFIG_PARAMETERS_REQ_V02,
                             req_union, LOC_ENGINE_SYNC_REQUEST_TIMEOUT,
                             QMI_LOC_SET_PROTOCOL_CONFIG_PARAMETERS_IND_V02,
                             &supl_config_ind);

  if(result != eLOC_CLIENT_SUCCESS ||
     eQMI_LOC_SUCCESS_V02 != supl_config_ind.status)
  {
    LOC_LOGE ("%s:%d]: Error status = %s, ind..status = %s ",
              __func__, __LINE__,
              loc_get_v02_client_status_name(result),
              loc_get_v02_qmi_status_name(supl_config_ind.status));
  }

  return convertErr(result);
}

/* set the configuration for LTE positioning profile (LPP) */
enum loc_api_adapter_err LocApiV02 :: setLPPConfig(uint32_t profile)
{
  locClientStatusEnumType result = eLOC_CLIENT_SUCCESS;
  locClientReqUnionType req_union;
  qmiLocSetProtocolConfigParametersReqMsgT_v02 lpp_config_req;
  qmiLocSetProtocolConfigParametersIndMsgT_v02 lpp_config_ind;

  LOC_LOGD("%s:%d]: lpp profile = %d\n",  __func__, __LINE__, profile);

  memset(&lpp_config_req, 0, sizeof(lpp_config_req));
  memset(&lpp_config_ind, 0, sizeof(lpp_config_ind));

  lpp_config_req.lppConfig_valid = 1;

  lpp_config_req.lppConfig = profile;

  req_union.pSetProtocolConfigParametersReq = &lpp_config_req;

  result = loc_sync_send_req(clientHandle,
                             QMI_LOC_SET_PROTOCOL_CONFIG_PARAMETERS_REQ_V02,
                             req_union, LOC_ENGINE_SYNC_REQUEST_TIMEOUT,
                             QMI_LOC_SET_PROTOCOL_CONFIG_PARAMETERS_IND_V02,
                             &lpp_config_ind);

  if(result != eLOC_CLIENT_SUCCESS ||
     eQMI_LOC_SUCCESS_V02 != lpp_config_ind.status)
  {
    LOC_LOGE ("%s:%d]: Error status = %s, ind..status = %s ",
              __func__, __LINE__,
              loc_get_v02_client_status_name(result),
              loc_get_v02_qmi_status_name(lpp_config_ind.status));
  }

  return convertErr(result);
}

/* set the Sensor Configuration */
enum loc_api_adapter_err LocApiV02 :: setSensorControlConfig(
    int sensorsDisabled, int sensorProvider)
{
  locClientStatusEnumType result = eLOC_CLIENT_SUCCESS;
  locClientReqUnionType req_union;

  qmiLocSetSensorControlConfigReqMsgT_v02 sensor_config_req;
  qmiLocSetSensorControlConfigIndMsgT_v02 sensor_config_ind;

  LOC_LOGD("%s:%d]: sensors disabled = %d\n",  __func__, __LINE__, sensorsDisabled);

  memset(&sensor_config_req, 0, sizeof(sensor_config_req));
  memset(&sensor_config_ind, 0, sizeof(sensor_config_ind));

  sensor_config_req.sensorsUsage_valid = 1;
  sensor_config_req.sensorsUsage = (sensorsDisabled == 1) ? eQMI_LOC_SENSOR_CONFIG_SENSOR_USE_DISABLE_V02
                                    : eQMI_LOC_SENSOR_CONFIG_SENSOR_USE_ENABLE_V02;

  sensor_config_req.sensorProvider_valid = 1;
  sensor_config_req.sensorProvider = (sensorProvider == 1 || sensorProvider == 4) ?
      eQMI_LOC_SENSOR_CONFIG_USE_PROVIDER_SSC_V02 :
      eQMI_LOC_SENSOR_CONFIG_USE_PROVIDER_NATIVE_V02;

  req_union.pSetSensorControlConfigReq = &sensor_config_req;

  result = loc_sync_send_req(clientHandle,
                             QMI_LOC_SET_SENSOR_CONTROL_CONFIG_REQ_V02,
                             req_union, LOC_ENGINE_SYNC_REQUEST_TIMEOUT,
                             QMI_LOC_SET_SENSOR_CONTROL_CONFIG_IND_V02,
                             &sensor_config_ind);

  if(result != eLOC_CLIENT_SUCCESS ||
     eQMI_LOC_SUCCESS_V02 != sensor_config_ind.status)
  {
    LOC_LOGE ("%s:%d]: Error status = %s, ind..status = %s ",
              __func__, __LINE__,
              loc_get_v02_client_status_name(result),
              loc_get_v02_qmi_status_name(sensor_config_ind.status));
  }

  return convertErr(result);
}

/* set the Sensor Properties */
enum loc_api_adapter_err LocApiV02 :: setSensorProperties(bool gyroBiasVarianceRandomWalk_valid, float gyroBiasVarianceRandomWalk,
                            bool accelBiasVarianceRandomWalk_valid, float accelBiasVarianceRandomWalk,
                            bool angleBiasVarianceRandomWalk_valid, float angleBiasVarianceRandomWalk,
                            bool rateBiasVarianceRandomWalk_valid, float rateBiasVarianceRandomWalk,
                            bool velocityBiasVarianceRandomWalk_valid, float velocityBiasVarianceRandomWalk)
{
  locClientStatusEnumType result = eLOC_CLIENT_SUCCESS;
  locClientReqUnionType req_union;

  qmiLocSetSensorPropertiesReqMsgT_v02 sensor_prop_req;
  qmiLocSetSensorPropertiesIndMsgT_v02 sensor_prop_ind;

  LOC_LOGI("%s:%d]: sensors prop: gyroBiasRandomWalk = %f, accelRandomWalk = %f, "
           "angleRandomWalk = %f, rateRandomWalk = %f, velocityRandomWalk = %f\n",
                 __func__, __LINE__, gyroBiasVarianceRandomWalk, accelBiasVarianceRandomWalk,
           angleBiasVarianceRandomWalk, rateBiasVarianceRandomWalk, velocityBiasVarianceRandomWalk);

  memset(&sensor_prop_req, 0, sizeof(sensor_prop_req));
  memset(&sensor_prop_ind, 0, sizeof(sensor_prop_ind));

  /* Set the validity bit and value for each sensor property */
  sensor_prop_req.gyroBiasVarianceRandomWalk_valid = gyroBiasVarianceRandomWalk_valid;
  sensor_prop_req.gyroBiasVarianceRandomWalk = gyroBiasVarianceRandomWalk;

  sensor_prop_req.accelerationRandomWalkSpectralDensity_valid = accelBiasVarianceRandomWalk_valid;
  sensor_prop_req.accelerationRandomWalkSpectralDensity = accelBiasVarianceRandomWalk;

  sensor_prop_req.angleRandomWalkSpectralDensity_valid = angleBiasVarianceRandomWalk_valid;
  sensor_prop_req.angleRandomWalkSpectralDensity = angleBiasVarianceRandomWalk;

  sensor_prop_req.rateRandomWalkSpectralDensity_valid = rateBiasVarianceRandomWalk_valid;
  sensor_prop_req.rateRandomWalkSpectralDensity = rateBiasVarianceRandomWalk;

  sensor_prop_req.velocityRandomWalkSpectralDensity_valid = velocityBiasVarianceRandomWalk_valid;
  sensor_prop_req.velocityRandomWalkSpectralDensity = velocityBiasVarianceRandomWalk;

  req_union.pSetSensorPropertiesReq = &sensor_prop_req;

  result = loc_sync_send_req(clientHandle,
                             QMI_LOC_SET_SENSOR_PROPERTIES_REQ_V02,
                             req_union, LOC_ENGINE_SYNC_REQUEST_TIMEOUT,
                             QMI_LOC_SET_SENSOR_PROPERTIES_IND_V02,
                             &sensor_prop_ind);

  if(result != eLOC_CLIENT_SUCCESS ||
     eQMI_LOC_SUCCESS_V02 != sensor_prop_ind.status)
  {
    LOC_LOGE ("%s:%d]: Error status = %s, ind..status = %s ",
              __func__, __LINE__,
              loc_get_v02_client_status_name(result),
              loc_get_v02_qmi_status_name(sensor_prop_ind.status));
  }

  return convertErr(result);
}

/* set the Sensor Performance Config */
enum loc_api_adapter_err LocApiV02 :: setSensorPerfControlConfig(int controlMode,
                                                                        int accelSamplesPerBatch, int accelBatchesPerSec,
                                                                        int gyroSamplesPerBatch, int gyroBatchesPerSec,
                                                                        int accelSamplesPerBatchHigh, int accelBatchesPerSecHigh,
                                                                        int gyroSamplesPerBatchHigh, int gyroBatchesPerSecHigh,
                                                                        int algorithmConfig)
{
  locClientStatusEnumType result = eLOC_CLIENT_SUCCESS;
  locClientReqUnionType req_union;

  qmiLocSetSensorPerformanceControlConfigReqMsgT_v02 sensor_perf_config_req;
  qmiLocSetSensorPerformanceControlConfigIndMsgT_v02 sensor_perf_config_ind;

  LOC_LOGD("%s:%d]: Sensor Perf Control Config (performanceControlMode)(%u) "
                "accel(#smp,#batches) (%u,%u) gyro(#smp,#batches) (%u,%u) "
                "accel_high(#smp,#batches) (%u,%u) gyro_high(#smp,#batches) (%u,%u) "
                "algorithmConfig(%u)\n",
                __FUNCTION__,
                __LINE__,
                controlMode,
                accelSamplesPerBatch,
                accelBatchesPerSec,
                gyroSamplesPerBatch,
                gyroBatchesPerSec,
                accelSamplesPerBatchHigh,
                accelBatchesPerSecHigh,
                gyroSamplesPerBatchHigh,
                gyroBatchesPerSecHigh,
                algorithmConfig
                );

  memset(&sensor_perf_config_req, 0, sizeof(sensor_perf_config_req));
  memset(&sensor_perf_config_ind, 0, sizeof(sensor_perf_config_ind));

  sensor_perf_config_req.performanceControlMode_valid = 1;
  sensor_perf_config_req.performanceControlMode = (qmiLocSensorPerformanceControlModeEnumT_v02)controlMode;
  sensor_perf_config_req.accelSamplingSpec_valid = 1;
  sensor_perf_config_req.accelSamplingSpec.batchesPerSecond = accelBatchesPerSec;
  sensor_perf_config_req.accelSamplingSpec.samplesPerBatch = accelSamplesPerBatch;
  sensor_perf_config_req.gyroSamplingSpec_valid = 1;
  sensor_perf_config_req.gyroSamplingSpec.batchesPerSecond = gyroBatchesPerSec;
  sensor_perf_config_req.gyroSamplingSpec.samplesPerBatch = gyroSamplesPerBatch;
  sensor_perf_config_req.accelSamplingSpecHigh_valid = 1;
  sensor_perf_config_req.accelSamplingSpecHigh.batchesPerSecond = accelBatchesPerSecHigh;
  sensor_perf_config_req.accelSamplingSpecHigh.samplesPerBatch = accelSamplesPerBatchHigh;
  sensor_perf_config_req.gyroSamplingSpecHigh_valid = 1;
  sensor_perf_config_req.gyroSamplingSpecHigh.batchesPerSecond = gyroBatchesPerSecHigh;
  sensor_perf_config_req.gyroSamplingSpecHigh.samplesPerBatch = gyroSamplesPerBatchHigh;
  sensor_perf_config_req.algorithmConfig_valid = 1;
  sensor_perf_config_req.algorithmConfig = algorithmConfig;

  req_union.pSetSensorPerformanceControlConfigReq = &sensor_perf_config_req;

  result = loc_sync_send_req(clientHandle,
                             QMI_LOC_SET_SENSOR_PERFORMANCE_CONTROL_CONFIGURATION_REQ_V02,
                             req_union, LOC_ENGINE_SYNC_REQUEST_TIMEOUT,
                             QMI_LOC_SET_SENSOR_PERFORMANCE_CONTROL_CONFIGURATION_IND_V02,
                             &sensor_perf_config_ind);

  if(result != eLOC_CLIENT_SUCCESS ||
     eQMI_LOC_SUCCESS_V02 != sensor_perf_config_ind.status)
  {
    LOC_LOGE ("%s:%d]: Error status = %s, ind..status = %s ",
              __func__, __LINE__,
              loc_get_v02_client_status_name(result),
              loc_get_v02_qmi_status_name(sensor_perf_config_ind.status));
  }

  return convertErr(result);
}

/* set the External Power Config */
enum loc_api_adapter_err LocApiV02 :: setExtPowerConfig(int isBatteryCharging)
{
  locClientStatusEnumType result = eLOC_CLIENT_SUCCESS;
  locClientReqUnionType req_union;

  qmiLocSetExternalPowerConfigReqMsgT_v02 ext_pwr_req;
  qmiLocGetExternalPowerConfigIndMsgT_v02 ext_pwr_ind;

  LOC_LOGI("%s:%d]: Ext Pwr Config (isBatteryCharging)(%u)",
                __FUNCTION__,
                __LINE__,
                isBatteryCharging
                );

  memset(&ext_pwr_req, 0, sizeof(ext_pwr_req));
  memset(&ext_pwr_ind, 0, sizeof(ext_pwr_ind));

  switch(isBatteryCharging)
  {
    /* Charging */
    case 1:
      ext_pwr_req.externalPowerState = eQMI_LOC_EXTERNAL_POWER_CONNECTED_V02;
      break;

    /* Not charging */
    case 0:
      ext_pwr_req.externalPowerState = eQMI_LOC_EXTERNAL_POWER_NOT_CONNECTED_V02;
      break;

    default:
      LOC_LOGE("%s:%d]: Invalid ext power state = %d!",
                    __FUNCTION__,
                    __LINE__,
                    isBatteryCharging);
      return LOC_API_ADAPTER_ERR_INVALID_PARAMETER;
      break;
  }

  req_union.pSetExternalPowerConfigReq = &ext_pwr_req;

  result = loc_sync_send_req(clientHandle,
                             QMI_LOC_SET_EXTERNAL_POWER_CONFIG_REQ_V02,
                             req_union, LOC_ENGINE_SYNC_REQUEST_TIMEOUT,
                             QMI_LOC_SET_EXTERNAL_POWER_CONFIG_IND_V02,
                             &ext_pwr_ind);

  if(result != eLOC_CLIENT_SUCCESS ||
     eQMI_LOC_SUCCESS_V02 != ext_pwr_ind.status)
  {
    LOC_LOGE ("%s:%d]: Error status = %d, ind..status = %d ",
                    __func__, __LINE__, result, ext_pwr_ind.status);
  }

  return convertErr(result);
}

/* set the Positioning Protocol on A-GLONASS system */
enum loc_api_adapter_err LocApiV02 :: setAGLONASSProtocol(unsigned long aGlonassProtocol)
{
  locClientStatusEnumType result = eLOC_CLIENT_SUCCESS;
  locClientReqUnionType req_union;
  qmiLocSetProtocolConfigParametersReqMsgT_v02 aGlonassProtocol_req;
  qmiLocSetProtocolConfigParametersIndMsgT_v02 aGlonassProtocol_ind;

  memset(&aGlonassProtocol_req, 0, sizeof(aGlonassProtocol_req));
  memset(&aGlonassProtocol_ind, 0, sizeof(aGlonassProtocol_ind));

  aGlonassProtocol_req.assistedGlonassProtocolMask_valid = 1;
  aGlonassProtocol_req.assistedGlonassProtocolMask = aGlonassProtocol;

  req_union.pSetProtocolConfigParametersReq = &aGlonassProtocol_req;

  LOC_LOGD("%s:%d]: aGlonassProtocolMask = 0x%x\n",  __func__, __LINE__,
                             aGlonassProtocol_req.assistedGlonassProtocolMask);

  result = loc_sync_send_req(clientHandle,
                             QMI_LOC_SET_PROTOCOL_CONFIG_PARAMETERS_REQ_V02,
                             req_union, LOC_ENGINE_SYNC_REQUEST_TIMEOUT,
                             QMI_LOC_SET_PROTOCOL_CONFIG_PARAMETERS_IND_V02,
                             &aGlonassProtocol_ind);

  if(result != eLOC_CLIENT_SUCCESS ||
     eQMI_LOC_SUCCESS_V02 != aGlonassProtocol_ind.status)
  {
    LOC_LOGE ("%s:%d]: Error status = %s, ind..status = %s ",
              __func__, __LINE__,
              loc_get_v02_client_status_name(result),
              loc_get_v02_qmi_status_name(aGlonassProtocol_ind.status));
  }

  return convertErr(result);
}

/* Convert event mask from loc eng to loc_api_v02 format */
locClientEventMaskType LocApiV02 :: convertMask(
  LOC_API_ADAPTER_EVENT_MASK_T mask)
{
  locClientEventMaskType eventMask = 0;
  LOC_LOGD("%s:%d]: adapter mask = %u\n", __func__, __LINE__, mask);

  if (mask & LOC_API_ADAPTER_BIT_PARSED_POSITION_REPORT)
      eventMask |= QMI_LOC_EVENT_MASK_POSITION_REPORT_V02;

  if (mask & LOC_API_ADAPTER_BIT_SATELLITE_REPORT)
      eventMask |= QMI_LOC_EVENT_MASK_GNSS_SV_INFO_V02;

  /* treat NMEA_1Hz and NMEA_POSITION_REPORT the same*/
  if ((mask & LOC_API_ADAPTER_BIT_NMEA_POSITION_REPORT) ||
      (mask & LOC_API_ADAPTER_BIT_NMEA_1HZ_REPORT) )
      eventMask |= QMI_LOC_EVENT_MASK_NMEA_V02;

  if (mask & LOC_API_ADAPTER_BIT_NI_NOTIFY_VERIFY_REQUEST)
      eventMask |= QMI_LOC_EVENT_MASK_NI_NOTIFY_VERIFY_REQ_V02;

  if (mask & LOC_API_ADAPTER_BIT_ASSISTANCE_DATA_REQUEST)
  {
    // TBD: This needs to be decoupled in the HAL
    eventMask |= QMI_LOC_EVENT_MASK_INJECT_PREDICTED_ORBITS_REQ_V02;
    eventMask |= QMI_LOC_EVENT_MASK_INJECT_TIME_REQ_V02;
    eventMask |= QMI_LOC_EVENT_MASK_INJECT_POSITION_REQ_V02;
  }

  if (mask & LOC_API_ADAPTER_BIT_STATUS_REPORT)
  {
      eventMask |= (QMI_LOC_EVENT_MASK_ENGINE_STATE_V02);
  }

  if (mask & LOC_API_ADAPTER_BIT_LOCATION_SERVER_REQUEST)
      eventMask |= QMI_LOC_EVENT_MASK_LOCATION_SERVER_CONNECTION_REQ_V02;

  if (mask & LOC_API_ADAPTER_REQUEST_WIFI)
      eventMask |= QMI_LOC_EVENT_MASK_WIFI_REQ_V02;

  if (mask & LOC_API_ADAPTER_SENSOR_STATUS)
      eventMask |= QMI_LOC_EVENT_MASK_SENSOR_STREAMING_READY_STATUS_V02;

  if (mask & LOC_API_ADAPTER_REQUEST_TIME_SYNC)
      eventMask |= QMI_LOC_EVENT_MASK_TIME_SYNC_REQ_V02;

  if (mask & LOC_API_ADAPTER_REPORT_SPI)
      eventMask |= QMI_LOC_EVENT_MASK_SET_SPI_STREAMING_REPORT_V02;

  if (mask & LOC_API_ADAPTER_REPORT_NI_GEOFENCE)
      eventMask |= QMI_LOC_EVENT_MASK_NI_GEOFENCE_NOTIFICATION_V02;

  if (mask & LOC_API_ADAPTER_GEOFENCE_GEN_ALERT)
      eventMask |= QMI_LOC_EVENT_MASK_GEOFENCE_GEN_ALERT_V02;

  if (mask & LOC_API_ADAPTER_REPORT_GENFENCE_BREACH)
      eventMask |= QMI_LOC_EVENT_MASK_GEOFENCE_BREACH_NOTIFICATION_V02;

  if (mask & LOC_API_ADAPTER_BATCHED_GENFENCE_BREACH_REPORT)
      eventMask |= QMI_LOC_EVENT_MASK_GEOFENCE_BATCH_BREACH_NOTIFICATION_V02;

  if (mask & LOC_API_ADAPTER_PEDOMETER_CTRL)
      eventMask |= QMI_LOC_EVENT_MASK_PEDOMETER_CONTROL_V02;

  if (mask & LOC_API_ADAPTER_MOTION_CTRL)
      eventMask |= QMI_LOC_EVENT_MASK_MOTION_DATA_CONTROL_V02;

  if (mask & LOC_API_ADAPTER_REQUEST_WIFI_AP_DATA)
      eventMask |= QMI_LOC_EVENT_MASK_INJECT_WIFI_AP_DATA_REQ_V02;

  if(mask & LOC_API_ADAPTER_BIT_BATCH_FULL)
      eventMask |= QMI_LOC_EVENT_MASK_BATCH_FULL_NOTIFICATION_V02;

  if(mask & LOC_API_ADAPTER_BIT_BATCHED_POSITION_REPORT)
      eventMask |= QMI_LOC_EVENT_MASK_LIVE_BATCHED_POSITION_REPORT_V02;

  // for GDT
  if(mask & LOC_API_ADAPTER_BIT_GDT_UPLOAD_BEGIN_REQ)
      eventMask |= QMI_LOC_EVENT_MASK_GDT_UPLOAD_BEGIN_REQ_V02;

  if(mask & LOC_API_ADAPTER_BIT_GDT_UPLOAD_END_REQ)
      eventMask |= QMI_LOC_EVENT_MASK_GDT_UPLOAD_END_REQ_V02;

  if (mask & LOC_API_ADAPTER_BIT_GNSS_MEASUREMENT)
      eventMask |= QMI_LOC_EVENT_MASK_GNSS_MEASUREMENT_REPORT_V02;

  if(mask & LOC_API_ADAPTER_BIT_REQUEST_TIMEZONE)
      eventMask |= QMI_LOC_EVENT_MASK_GET_TIME_ZONE_REQ_V02;
  return eventMask;
}

qmiLocLockEnumT_v02 LocApiV02 :: convertGpsLockMask(LOC_GPS_LOCK_MASK lockMask)
{
    /* GPS HAL uses power voting through GPS Lock mask.
       When QCA1530 daemon is present two values are used: 101 and 103.*/
    if ( 101 == lockMask || 103 == lockMask )
    {
        return (qmiLocLockEnumT_v02)lockMask;
    }
    if (isGpsLockAll(lockMask))
        return eQMI_LOC_LOCK_ALL_V02;
    if (isGpsLockMO(lockMask))
        return eQMI_LOC_LOCK_MI_V02;
    if (isGpsLockMT(lockMask))
        return eQMI_LOC_LOCK_MT_V02;
    if (isGpsLockNone(lockMask))
        return eQMI_LOC_LOCK_NONE_V02;
    return (qmiLocLockEnumT_v02)lockMask;
}

/* Convert error from loc_api_v02 to loc eng format*/
enum loc_api_adapter_err LocApiV02 :: convertErr(
  locClientStatusEnumType status)
{
  switch( status)
  {
    case eLOC_CLIENT_SUCCESS:
      return LOC_API_ADAPTER_ERR_SUCCESS;

    case eLOC_CLIENT_FAILURE_GENERAL:
      return LOC_API_ADAPTER_ERR_GENERAL_FAILURE;

    case eLOC_CLIENT_FAILURE_UNSUPPORTED:
      return LOC_API_ADAPTER_ERR_UNSUPPORTED;

    case eLOC_CLIENT_FAILURE_INVALID_PARAMETER:
      return LOC_API_ADAPTER_ERR_INVALID_PARAMETER;

    case eLOC_CLIENT_FAILURE_ENGINE_BUSY:
      return LOC_API_ADAPTER_ERR_ENGINE_BUSY;

    case eLOC_CLIENT_FAILURE_PHONE_OFFLINE:
      return LOC_API_ADAPTER_ERR_PHONE_OFFLINE;

    case eLOC_CLIENT_FAILURE_TIMEOUT:
      return LOC_API_ADAPTER_ERR_TIMEOUT;

    case eLOC_CLIENT_FAILURE_INVALID_HANDLE:
      return LOC_API_ADAPTER_ERR_INVALID_HANDLE;

    case eLOC_CLIENT_FAILURE_SERVICE_NOT_PRESENT:
      return LOC_API_ADAPTER_ERR_SERVICE_NOT_PRESENT;

    case eLOC_CLIENT_FAILURE_INTERNAL:
      return LOC_API_ADAPTER_ERR_INTERNAL;

    default:
      return LOC_API_ADAPTER_ERR_FAILURE;
  }
}

/* convert position report to loc eng format and send the converted
   position to loc eng */

void LocApiV02 :: reportPosition (
  const qmiLocEventPositionReportIndMsgT_v02 *location_report_ptr)
{
    UlpLocation location;
    LocPosTechMask tech_Mask = LOC_POS_TECH_MASK_DEFAULT;
    LOC_LOGD("Reporting postion from V2 Adapter\n");
    memset(&location, 0, sizeof (UlpLocation));
    location.size = sizeof(location);
    GpsLocationExtended locationExtended;
    memset(&locationExtended, 0, sizeof (GpsLocationExtended));
    locationExtended.size = sizeof(locationExtended);
    // Process the position from final and intermediate reports

    if( (location_report_ptr->sessionStatus == eQMI_LOC_SESS_STATUS_SUCCESS_V02) ||
        (location_report_ptr->sessionStatus == eQMI_LOC_SESS_STATUS_IN_PROGRESS_V02)
        )
    {
        // Latitude & Longitude
        if( (location_report_ptr->latitude_valid == 1 ) &&
            (location_report_ptr->longitude_valid == 1)  &&
            (location_report_ptr->latitude != 0 ||
             location_report_ptr->longitude!= 0))
        {
            location.gpsLocation.flags  |= GPS_LOCATION_HAS_LAT_LONG;
            location.gpsLocation.latitude  = location_report_ptr->latitude;
            location.gpsLocation.longitude = location_report_ptr->longitude;

            // Time stamp (UTC)
            if(location_report_ptr->timestampUtc_valid == 1)
            {
                location.gpsLocation.timestamp = location_report_ptr->timestampUtc;
            }

            // Altitude
            if(location_report_ptr->altitudeWrtEllipsoid_valid == 1  )
            {
                location.gpsLocation.flags  |= GPS_LOCATION_HAS_ALTITUDE;
                location.gpsLocation.altitude = location_report_ptr->altitudeWrtEllipsoid;
            }

            // Speed
            if(location_report_ptr->speedHorizontal_valid == 1)
            {
                location.gpsLocation.flags  |= GPS_LOCATION_HAS_SPEED;
                location.gpsLocation.speed = location_report_ptr->speedHorizontal;
            }

            // Heading
            if(location_report_ptr->heading_valid == 1)
            {
                location.gpsLocation.flags  |= GPS_LOCATION_HAS_BEARING;
                location.gpsLocation.bearing = location_report_ptr->heading;
            }

            // Uncertainty (circular)
            if (location_report_ptr->horUncCircular_valid) {
                location.gpsLocation.flags |= GPS_LOCATION_HAS_ACCURACY;
                location.gpsLocation.accuracy = location_report_ptr->horUncCircular;
            } else if (location_report_ptr->horUncEllipseSemiMinor_valid &&
                       location_report_ptr->horUncEllipseSemiMajor_valid) {
                location.gpsLocation.flags |= GPS_LOCATION_HAS_ACCURACY;
                location.gpsLocation.accuracy =
                    sqrt((location_report_ptr->horUncEllipseSemiMinor *
                          location_report_ptr->horUncEllipseSemiMinor) +
                         (location_report_ptr->horUncEllipseSemiMajor *
                          location_report_ptr->horUncEllipseSemiMajor));
            }

            // Technology Mask
            tech_Mask |= location_report_ptr->technologyMask;

            //Mark the location source as from GNSS
            location.gpsLocation.flags |= LOCATION_HAS_SOURCE_INFO;
            location.position_source = ULP_LOCATION_IS_FROM_GNSS;
            if (location_report_ptr->magneticDeviation_valid)
            {
                locationExtended.flags |= GPS_LOCATION_EXTENDED_HAS_MAG_DEV;
                locationExtended.magneticDeviation = location_report_ptr->magneticDeviation;
            }

            if (location_report_ptr->DOP_valid)
            {
                locationExtended.flags |= GPS_LOCATION_EXTENDED_HAS_DOP;
                locationExtended.pdop = location_report_ptr->DOP.PDOP;
                locationExtended.hdop = location_report_ptr->DOP.HDOP;
                locationExtended.vdop = location_report_ptr->DOP.VDOP;
            }

            if (location_report_ptr->altitudeWrtMeanSeaLevel_valid)
            {
                locationExtended.flags |= GPS_LOCATION_EXTENDED_HAS_ALTITUDE_MEAN_SEA_LEVEL;
                locationExtended.altitudeMeanSeaLevel = location_report_ptr->altitudeWrtMeanSeaLevel;
            }

            if (location_report_ptr->vertUnc_valid)
            {
               locationExtended.flags |= GPS_LOCATION_EXTENDED_HAS_VERT_UNC;
               locationExtended.vert_unc = location_report_ptr->vertUnc;
            }

            if (location_report_ptr->speedUnc_valid)
            {
               locationExtended.flags |= GPS_LOCATION_EXTENDED_HAS_SPEED_UNC;
               locationExtended.speed_unc = location_report_ptr->speedUnc;
            }
            if (location_report_ptr->headingUnc_valid)
            {
               locationExtended.flags |= GPS_LOCATION_EXTENDED_HAS_BEARING_UNC;
               locationExtended.bearing_unc = location_report_ptr->headingUnc;
            }
            if (location_report_ptr->horReliability_valid)
            {
               locationExtended.flags |= GPS_LOCATION_EXTENDED_HAS_HOR_RELIABILITY;
               switch(location_report_ptr->horReliability)
               {
                  case eQMI_LOC_RELIABILITY_NOT_SET_V02 :
                    locationExtended.horizontal_reliability = LOC_RELIABILITY_NOT_SET;
                    break;
                  case eQMI_LOC_RELIABILITY_VERY_LOW_V02 :
                    locationExtended.horizontal_reliability = LOC_RELIABILITY_VERY_LOW;
                    break;
                  case eQMI_LOC_RELIABILITY_LOW_V02 :
                    locationExtended.horizontal_reliability = LOC_RELIABILITY_LOW;
                    break;
                  case eQMI_LOC_RELIABILITY_MEDIUM_V02 :
                    locationExtended.horizontal_reliability = LOC_RELIABILITY_MEDIUM;
                    break;
                  case eQMI_LOC_RELIABILITY_HIGH_V02 :
                    locationExtended.horizontal_reliability = LOC_RELIABILITY_HIGH;
                    break;
                  default:
                    locationExtended.horizontal_reliability = LOC_RELIABILITY_NOT_SET;
                    break;
               }
            }
            if (location_report_ptr->vertReliability_valid)
            {
               locationExtended.flags |= GPS_LOCATION_EXTENDED_HAS_VERT_RELIABILITY;
               switch(location_report_ptr->vertReliability)
               {
                  case eQMI_LOC_RELIABILITY_NOT_SET_V02 :
                    locationExtended.vertical_reliability = LOC_RELIABILITY_NOT_SET;
                    break;
                  case eQMI_LOC_RELIABILITY_VERY_LOW_V02 :
                    locationExtended.vertical_reliability = LOC_RELIABILITY_VERY_LOW;
                    break;
                  case eQMI_LOC_RELIABILITY_LOW_V02 :
                    locationExtended.vertical_reliability = LOC_RELIABILITY_LOW;
                    break;
                  case eQMI_LOC_RELIABILITY_MEDIUM_V02 :
                    locationExtended.vertical_reliability = LOC_RELIABILITY_MEDIUM;
                    break;
                  case eQMI_LOC_RELIABILITY_HIGH_V02 :
                    locationExtended.vertical_reliability = LOC_RELIABILITY_HIGH;
                    break;
                  default:
                    locationExtended.vertical_reliability = LOC_RELIABILITY_NOT_SET;
                    break;
               }
            }
            LocApiBase::reportPosition( location,
                            locationExtended,
                            (void*)location_report_ptr,
                            (location_report_ptr->sessionStatus
                             == eQMI_LOC_SESS_STATUS_IN_PROGRESS_V02 ?
                             LOC_SESS_INTERMEDIATE : LOC_SESS_SUCCESS),
                            tech_Mask);
        }
    }
    else
    {
        LocApiBase::reportPosition(location,
                                   locationExtended,
                                   NULL,
                                   LOC_SESS_FAILURE);

        LOC_LOGD("%s:%d]: Ignoring position report with sess status = %d, "
                      "fix id = %u\n", __func__, __LINE__,
                      location_report_ptr->sessionStatus,
                      location_report_ptr->fixId );
    }
}

/* convert satellite report to loc eng format and  send the converted
   report to loc eng */
void  LocApiV02 :: reportSv (
  const qmiLocEventGnssSvInfoIndMsgT_v02 *gnss_report_ptr)
{
  GnssSvStatus      SvStatus;
  GpsLocationExtended locationExtended;
  int              num_svs_max, i;
  const qmiLocSvInfoStructT_v02 *sv_info_ptr;

  LOC_LOGV ("%s:%d]: num of sv = %d, validity = %d, altitude assumed = %u \n",
            __func__, __LINE__, gnss_report_ptr->svList_len,
            gnss_report_ptr->svList_valid,
            gnss_report_ptr->altitudeAssumed);

  num_svs_max = 0;
  memset (&SvStatus, 0, sizeof (GnssSvStatus));
  memset(&locationExtended, 0, sizeof (GpsLocationExtended));
  locationExtended.size = sizeof(locationExtended);
  if(gnss_report_ptr->svList_valid == 1)
  {
    num_svs_max = gnss_report_ptr->svList_len;
    if(num_svs_max > GPS_MAX_SVS)
    {
      num_svs_max = GPS_MAX_SVS;
    }
    SvStatus.num_svs = 0;
    for(i = 0; i < num_svs_max; i++)
    {
      sv_info_ptr = &(gnss_report_ptr->svList[i]);
      if((sv_info_ptr->validMask & QMI_LOC_SV_INFO_MASK_VALID_SYSTEM_V02) &&
         (sv_info_ptr->validMask & QMI_LOC_SV_INFO_MASK_VALID_GNSS_SVID_V02)
         && (sv_info_ptr->gnssSvId != 0 ))
      {
        if(sv_info_ptr->system == eQMI_LOC_SV_SYSTEM_GPS_V02)
        {
          SvStatus.sv_list[SvStatus.num_svs].size = sizeof(GpsSvInfo);
          SvStatus.sv_list[SvStatus.num_svs].prn = (int)sv_info_ptr->gnssSvId;

          // We only have the data field to report gps eph and alm mask
          if(sv_info_ptr->validMask &
             QMI_LOC_SV_INFO_MASK_VALID_SVINFO_MASK_V02)
          {
            if(sv_info_ptr->svInfoMask &
               QMI_LOC_SVINFO_MASK_HAS_EPHEMERIS_V02)
            {
              SvStatus.ephemeris_mask |= (1 << (sv_info_ptr->gnssSvId-1));
            }
            if(sv_info_ptr->svInfoMask &
               QMI_LOC_SVINFO_MASK_HAS_ALMANAC_V02)
            {
              SvStatus.almanac_mask |= (1 << (sv_info_ptr->gnssSvId-1));
            }
          }

          if((sv_info_ptr->validMask &
              QMI_LOC_SV_INFO_MASK_VALID_PROCESS_STATUS_V02)
             &&
             (sv_info_ptr->svStatus == eQMI_LOC_SV_STATUS_TRACK_V02))
          {
            SvStatus.gps_used_in_fix_mask |= (1 << (sv_info_ptr->gnssSvId-1));
          }
        }
        // SBAS: GPS PRN: 120-151,
        // In exteneded measurement report, we follow nmea standard,
        // which is from 33-64.
        else if(sv_info_ptr->system == eQMI_LOC_SV_SYSTEM_SBAS_V02)
        {
          SvStatus.sv_list[SvStatus.num_svs].prn =
            sv_info_ptr->gnssSvId + 33 - 120;
        }
        // Gloness: Slot id: 1-32
        // In extended measurement report, we follow nmea standard,
        // which is 65-96
        else if(sv_info_ptr->system == eQMI_LOC_SV_SYSTEM_GLONASS_V02)
        {
          if((sv_info_ptr->validMask &
              QMI_LOC_SV_INFO_MASK_VALID_PROCESS_STATUS_V02)
             &&
             (sv_info_ptr->svStatus == eQMI_LOC_SV_STATUS_TRACK_V02))
          {
            SvStatus.glo_used_in_fix_mask |= (1 << (sv_info_ptr->gnssSvId-1));
          }

          SvStatus.sv_list[SvStatus.num_svs].prn =
            sv_info_ptr->gnssSvId + (65-1);
        }
        //BeiDou: Slot id: 1-37
        //In extended measurement report, we follow nmea standard,
        //which is 201-237
        else if(sv_info_ptr->system == eQMI_LOC_SV_SYSTEM_BDS_V02)
        {
          if((sv_info_ptr->validMask &
              QMI_LOC_SV_INFO_MASK_VALID_PROCESS_STATUS_V02)
             &&
             (sv_info_ptr->svStatus == eQMI_LOC_SV_STATUS_TRACK_V02))
          {
            SvStatus.bds_used_in_fix_mask |= (1 << (sv_info_ptr->gnssSvId-1-200));
          }
            SvStatus.sv_list[SvStatus.num_svs].prn =
                sv_info_ptr->gnssSvId;
        }
        // Unsupported SV system
        else
        {
          continue;
        }
      }

      if(sv_info_ptr->validMask & QMI_LOC_SV_INFO_MASK_VALID_SNR_V02 )
      {
        SvStatus.sv_list[SvStatus.num_svs].snr = sv_info_ptr->snr;
      }

      if(sv_info_ptr->validMask & QMI_LOC_SV_INFO_MASK_VALID_ELEVATION_V02)
      {
        SvStatus.sv_list[SvStatus.num_svs].elevation = sv_info_ptr->elevation;
      }

      if(sv_info_ptr->validMask & QMI_LOC_SV_INFO_MASK_VALID_AZIMUTH_V02)
      {
        SvStatus.sv_list[SvStatus.num_svs].azimuth = sv_info_ptr->azimuth;
      }

      SvStatus.num_svs++;
    }
  }

  if (SvStatus.num_svs >= 0)
  {
    LOC_LOGV ("%s:%d]: firing SV callback\n", __func__, __LINE__);
    LocApiBase::reportSv(SvStatus,
                         locationExtended,
                         (void*)gnss_report_ptr);
  }
}

/* convert engine state report to loc eng format and send the converted
   report to loc eng */
void LocApiV02 :: reportEngineState (
    const qmiLocEventEngineStateIndMsgT_v02 *engine_state_ptr)
{

  LOC_LOGV("%s:%d]: state = %d\n", __func__, __LINE__,
                 engine_state_ptr->engineState);

  struct MsgUpdateEngineState : public LocMsg {
      LocApiV02* mpLocApiV02;
      bool mEngineOn;
      inline MsgUpdateEngineState(LocApiV02* pLocApiV02, bool engineOn) :
                 LocMsg(), mpLocApiV02(pLocApiV02), mEngineOn(engineOn) {}
      inline virtual void proc() const {
          // If EngineOn is true and InSession is false and Engine is just turned off,
          // then unregister the gps tracking specific event masks
          if (mpLocApiV02->mEngineOn && !mpLocApiV02->mInSession && !mEngineOn) {
              mpLocApiV02->registerEventMask(mpLocApiV02->mQmiMask);
          }
          mpLocApiV02->mEngineOn = mEngineOn;

          if (mEngineOn) {
              // if EngineOn and not InSession, then we have already stopped
              // the fix, so do not send ENGINE_ON
              if (mpLocApiV02->mInSession) {
                  mpLocApiV02->reportStatus(GPS_STATUS_ENGINE_ON);
                  mpLocApiV02->reportStatus(GPS_STATUS_SESSION_BEGIN);
              }
          } else {
              mpLocApiV02->reportStatus(GPS_STATUS_SESSION_END);
              mpLocApiV02->reportStatus(GPS_STATUS_ENGINE_OFF);
          }
      }
  };

  if (engine_state_ptr->engineState == eQMI_LOC_ENGINE_STATE_ON_V02)
  {
    sendMsg(new MsgUpdateEngineState(this, true));
  }
  else if (engine_state_ptr->engineState == eQMI_LOC_ENGINE_STATE_OFF_V02)
  {
    sendMsg(new MsgUpdateEngineState(this, false));
  }
  else
  {
    reportStatus(GPS_STATUS_NONE);
  }

}

/* convert fix session state report to loc eng format and send the converted
   report to loc eng */
void LocApiV02 :: reportFixSessionState (
    const qmiLocEventFixSessionStateIndMsgT_v02 *fix_session_state_ptr)
{
  GpsStatusValue status;
  LOC_LOGD("%s:%d]: state = %d\n", __func__, __LINE__,
                fix_session_state_ptr->sessionState);

  status = GPS_STATUS_NONE;
  if (fix_session_state_ptr->sessionState == eQMI_LOC_FIX_SESSION_STARTED_V02)
  {
    status = GPS_STATUS_SESSION_BEGIN;
  }
  else if (fix_session_state_ptr->sessionState
           == eQMI_LOC_FIX_SESSION_FINISHED_V02)
  {
    status = GPS_STATUS_SESSION_END;
  }
  reportStatus(status);
}

/* convert NMEA report to loc eng format and send the converted
   report to loc eng */
void LocApiV02 :: reportNmea (
  const qmiLocEventNmeaIndMsgT_v02 *nmea_report_ptr)
{

  LocApiBase::reportNmea(nmea_report_ptr->nmea,
                         strlen(nmea_report_ptr->nmea));

  LOC_LOGD("NMEA <%s", nmea_report_ptr->nmea);
}

/* convert and report an ATL request to loc engine */
void LocApiV02 :: reportAtlRequest(
  const qmiLocEventLocationServerConnectionReqIndMsgT_v02 * server_request_ptr)
{
  uint32_t connHandle = server_request_ptr->connHandle;
  // service ATL open request; copy the WWAN type
  if(server_request_ptr->requestType == eQMI_LOC_SERVER_REQUEST_OPEN_V02 )
  {
    AGpsType agpsType;
    switch(server_request_ptr->wwanType)
    {
    case eQMI_LOC_WWAN_TYPE_INTERNET_V02:
      agpsType = AGPS_TYPE_WWAN_ANY;
      requestATL(connHandle, agpsType);
      break;
    case eQMI_LOC_WWAN_TYPE_AGNSS_V02:
      agpsType = AGPS_TYPE_SUPL;
      requestATL(connHandle, agpsType);
      break;
    case eQMI_LOC_WWAN_TYPE_AGNSS_EMERGENCY_V02:
      requestSuplES(connHandle);
      break;
    default:
      agpsType = AGPS_TYPE_WWAN_ANY;
      requestATL(connHandle, agpsType);
      break;
    }
  }
  // service the ATL close request
  else if (server_request_ptr->requestType == eQMI_LOC_SERVER_REQUEST_CLOSE_V02)
  {
    releaseATL(connHandle);
  }
}

/* conver the NI report to loc eng format and send t loc engine */
void LocApiV02 :: reportNiRequest(
    const qmiLocEventNiNotifyVerifyReqIndMsgT_v02 *ni_req_ptr)
{
  GpsNiNotification notif;

  /* initialize the notification*/
  memset(notif.extras, 0, sizeof notif.extras);
  memset(notif.text, 0, sizeof notif.text);
  memset(notif.requestor_id, 0, sizeof notif.requestor_id);

  /* NI timeout gets overwritten in LocApiEngAdapter,
     initializing to 0 here */
  notif.timeout     = 0;

  notif.text_encoding = GPS_ENC_NONE ;

  notif.requestor_id_encoding = GPS_ENC_UNKNOWN;

  notif.notify_flags       = 0;

  notif.default_response   = GPS_NI_RESPONSE_NORESP;

  /*Handle Vx request */
  if(ni_req_ptr->NiVxInd_valid == 1)
  {
     const qmiLocNiVxNotifyVerifyStructT_v02 *vx_req = &(ni_req_ptr->NiVxInd);

     notif.ni_type     = GPS_NI_TYPE_VOICE;

     // Requestor ID, the requestor id recieved is NULL terminated
     hexcode(notif.requestor_id, sizeof notif.requestor_id,
             (char *)vx_req->requestorId, vx_req->requestorId_len );
  }

  /* Handle UMTS CP request*/
  else if(ni_req_ptr->NiUmtsCpInd_valid == 1)
  {
    const qmiLocNiUmtsCpNotifyVerifyStructT_v02 *umts_cp_req =
       &ni_req_ptr->NiUmtsCpInd;

    notif.ni_type     = GPS_NI_TYPE_UMTS_CTRL_PLANE;

    /* notificationText should always be a NULL terminated string */
    hexcode(notif.text, sizeof notif.text,
            (char *)umts_cp_req->notificationText,
            umts_cp_req->notificationText_len);

    /* Store requestor ID */
    hexcode(notif.requestor_id, sizeof(notif.requestor_id),
            (char *)umts_cp_req->requestorId.codedString,
            umts_cp_req->requestorId.codedString_len);

   /* convert encodings */
    notif.text_encoding = convertNiEncoding(umts_cp_req->dataCodingScheme);

    notif.requestor_id_encoding =
      convertNiEncoding(umts_cp_req->requestorId.dataCodingScheme);

    /* LCS address (using extras field) */
    if ( umts_cp_req->clientAddress_len != 0)
    {
      char lcs_addr[32]; // Decoded LCS address for UMTS CP NI

      // Copy LCS Address into notif.extras in the format: Address = 012345
      strlcat(notif.extras, LOC_NI_NOTIF_KEY_ADDRESS, sizeof (notif.extras));
      strlcat(notif.extras, " = ", sizeof notif.extras);
      int addr_len = 0;
      const char *address_source = NULL;
      address_source = (char *)umts_cp_req->clientAddress;
      // client Address is always NULL terminated
      addr_len = decodeAddress(lcs_addr, sizeof(lcs_addr), address_source,
                               umts_cp_req->clientAddress_len);

      // The address is ASCII string
      if (addr_len)
      {
        strlcat(notif.extras, lcs_addr, sizeof notif.extras);
      }
    }

  }
  else if(ni_req_ptr->NiSuplInd_valid == 1)
  {
    const qmiLocNiSuplNotifyVerifyStructT_v02 *supl_req =
      &ni_req_ptr->NiSuplInd;

    notif.ni_type     = GPS_NI_TYPE_UMTS_SUPL;

    // Client name
    if (supl_req->valid_flags & QMI_LOC_SUPL_CLIENT_NAME_MASK_V02)
    {
      hexcode(notif.text, sizeof(notif.text),
              (char *)supl_req->clientName.formattedString,
              supl_req->clientName.formattedString_len);
      LOC_LOGV("%s:%d]: SUPL NI: client_name: %s \n", __func__, __LINE__,
          notif.text);
    }
    else
    {
      LOC_LOGV("%s:%d]: SUPL NI: client_name not present.",
          __func__, __LINE__);
    }

    // Requestor ID
    if (supl_req->valid_flags & QMI_LOC_SUPL_REQUESTOR_ID_MASK_V02)
    {
      hexcode(notif.requestor_id, sizeof notif.requestor_id,
              (char*)supl_req->requestorId.formattedString,
              supl_req->requestorId.formattedString_len );

      LOC_LOGV("%s:%d]: SUPL NI: requestor_id: %s \n", __func__, __LINE__,
          notif.requestor_id);
    }
    else
    {
      LOC_LOGV("%s:%d]: SUPL NI: requestor_id not present.",
          __func__, __LINE__);
    }

    // Encoding type
    if (supl_req->valid_flags & QMI_LOC_SUPL_DATA_CODING_SCHEME_MASK_V02)
    {
      notif.text_encoding = convertNiEncoding(supl_req->dataCodingScheme);

      notif.requestor_id_encoding = convertNiEncoding(supl_req->dataCodingScheme);
    }
    else
    {
      notif.text_encoding = notif.requestor_id_encoding = GPS_ENC_UNKNOWN;
    }

    // ES SUPL
    if(ni_req_ptr->suplEmergencyNotification_valid ==1)
    {
        const qmiLocEmergencyNotificationStructT_v02 *supl_emergency_request =
        &ni_req_ptr->suplEmergencyNotification;

        notif.ni_type = GPS_NI_TYPE_EMERGENCY_SUPL;
    }

  } //ni_req_ptr->NiSuplInd_valid == 1
  else
  {
    LOC_LOGE("%s:%d]: unknown request event \n",__func__, __LINE__);
    return;
  }

  // Set default_response & notify_flags
  convertNiNotifyVerifyType(&notif, ni_req_ptr->notificationType);

  qmiLocEventNiNotifyVerifyReqIndMsgT_v02 *ni_req_copy_ptr =
    (qmiLocEventNiNotifyVerifyReqIndMsgT_v02 *)malloc(sizeof(*ni_req_copy_ptr));

  if( NULL != ni_req_copy_ptr)
  {
    memcpy(ni_req_copy_ptr, ni_req_ptr, sizeof(*ni_req_copy_ptr));

    requestNiNotify(notif, (const void*)ni_req_copy_ptr);
  }
  else
  {
    LOC_LOGE("%s:%d]: Error copying NI request\n", __func__, __LINE__);
  }

}

/* Report the Xtra Server Url from the modem to HAL*/
void LocApiV02 :: reportXtraServerUrl(
                const qmiLocEventInjectPredictedOrbitsReqIndMsgT_v02*
                server_request_ptr)
{

  if (server_request_ptr->serverList.serverList_len == 1)
  {
    reportXtraServer(server_request_ptr->serverList.serverList[0].serverUrl,
                     "",
                     "",
                     QMI_LOC_MAX_SERVER_ADDR_LENGTH_V02);
  }
  else if (server_request_ptr->serverList.serverList_len == 2)
  {
    reportXtraServer(server_request_ptr->serverList.serverList[0].serverUrl,
                     server_request_ptr->serverList.serverList[1].serverUrl,
                     "",
                     QMI_LOC_MAX_SERVER_ADDR_LENGTH_V02);
  }
  else
  {
    reportXtraServer(server_request_ptr->serverList.serverList[0].serverUrl,
                     server_request_ptr->serverList.serverList[1].serverUrl,
                     server_request_ptr->serverList.serverList[2].serverUrl,
                     QMI_LOC_MAX_SERVER_ADDR_LENGTH_V02);
  }

}

/* convert Ni Encoding type from QMI_LOC to loc eng format */
GpsNiEncodingType LocApiV02 ::convertNiEncoding(
  qmiLocNiDataCodingSchemeEnumT_v02 loc_encoding)
{
   GpsNiEncodingType enc = GPS_ENC_UNKNOWN;

   switch (loc_encoding)
   {
     case eQMI_LOC_NI_SUPL_UTF8_V02:
       enc = GPS_ENC_SUPL_UTF8;
       break;
     case eQMI_LOC_NI_SUPL_UCS2_V02:
       enc = GPS_ENC_SUPL_UCS2;
       break;
     case eQMI_LOC_NI_SUPL_GSM_DEFAULT_V02:
       enc = GPS_ENC_SUPL_GSM_DEFAULT;
       break;
     case eQMI_LOC_NI_SS_LANGUAGE_UNSPEC_V02:
       enc = GPS_ENC_SUPL_GSM_DEFAULT; // SS_LANGUAGE_UNSPEC = GSM
       break;
     default:
       break;
   }

   return enc;
}

/*convert NI notify verify type from QMI LOC to loc eng format*/
bool LocApiV02 :: convertNiNotifyVerifyType (
  GpsNiNotification *notif,
  qmiLocNiNotifyVerifyEnumT_v02 notif_priv)
{
  switch (notif_priv)
   {
   case eQMI_LOC_NI_USER_NO_NOTIFY_NO_VERIFY_V02:
      notif->notify_flags = 0;
      break;

   case eQMI_LOC_NI_USER_NOTIFY_ONLY_V02:
      notif->notify_flags = GPS_NI_NEED_NOTIFY;
      break;

   case eQMI_LOC_NI_USER_NOTIFY_VERIFY_ALLOW_NO_RESP_V02:
      notif->notify_flags = GPS_NI_NEED_NOTIFY | GPS_NI_NEED_VERIFY;
      notif->default_response = GPS_NI_RESPONSE_ACCEPT;
      break;

   case eQMI_LOC_NI_USER_NOTIFY_VERIFY_NOT_ALLOW_NO_RESP_V02:
      notif->notify_flags = GPS_NI_NEED_NOTIFY | GPS_NI_NEED_VERIFY;
      notif->default_response = GPS_NI_RESPONSE_DENY;
      break;

   case eQMI_LOC_NI_USER_NOTIFY_VERIFY_PRIVACY_OVERRIDE_V02:
      notif->notify_flags = GPS_NI_PRIVACY_OVERRIDE;
      break;

   default:
      return false;
   }

   return true;
}

/* convert and report GNSS measurement data to loc eng */
void LocApiV02 :: reportGnssMeasurementData(
  const qmiLocEventGnssSvMeasInfoIndMsgT_v02& gnss_measurement_report_ptr)
{
    LOC_LOGV ("%s:%d]: entering\n", __func__, __LINE__);

    GpsData gpsMeasurementData;
    memset (&gpsMeasurementData, 0, sizeof(GpsData));

    int svMeasurment_len = 0;

    // size
    gpsMeasurementData.size = sizeof(GpsData);

    // number of measurements
    if (gnss_measurement_report_ptr.svMeasurement_valid) {
        svMeasurment_len =
            gnss_measurement_report_ptr.svMeasurement_len;
        gpsMeasurementData.measurement_count = svMeasurment_len;
        LOC_LOGV ("%s:%d]: there are %d SV measurements\n",
                  __func__, __LINE__, svMeasurment_len);
    } else {
        LOC_LOGV ("%s:%d]: there is no valid SV measurements\n",
                  __func__, __LINE__);
    }

    if (svMeasurment_len != 0 &&
        gnss_measurement_report_ptr.system == eQMI_LOC_SV_SYSTEM_GPS_V02) {

        // the array of measurements
        int index = 0;
        while(svMeasurment_len > 0) {
            convertGpsMeasurements(gpsMeasurementData.measurements[index],
                                   gnss_measurement_report_ptr.svMeasurement[index]);
            index++;
            svMeasurment_len--;
        }

        // the GPS clock time reading
        convertGpsClock(gpsMeasurementData.clock,
                        gnss_measurement_report_ptr);

        // calling the base
        LOC_LOGV ("%s:%d]: calling LocApiBase::reportGpsMeasurementData.\n",
                  __func__, __LINE__);
        LocApiBase::reportGpsMeasurementData(gpsMeasurementData);
    } else {
        LOC_LOGV ("%s:%d]: There is no GPS measurement.\n",
                  __func__, __LINE__);
    }
}

/*convert GpsMeasurement type from QMI LOC to loc eng format*/
void LocApiV02 :: convertGpsMeasurements (GpsMeasurement& gpsMeasurement,
    const qmiLocSVMeasurementStructT_v02& gnss_measurement_info)
{
    LOC_LOGV ("%s:%d]: entering\n", __func__, __LINE__);

    // size
    gpsMeasurement.size = sizeof(GpsMeasurement);

    // flag initiation
    int flags = 0;

    // prn
    gpsMeasurement.prn = gnss_measurement_info.gnssSvId;

    // time_offset_ns
    gpsMeasurement.time_offset_ns = 0;

    // state & received_gps_tow_ns & received_gps_tow_uncertainty_ns
    uint64_t validMask = gnss_measurement_info.measurementStatus &
                         gnss_measurement_info.validMeasStatusMask;
    uint64_t bitSynMask = QMI_LOC_MASK_MEAS_STATUS_BE_CONFIRM_V02 |
                          QMI_LOC_MASK_MEAS_STATUS_SB_VALID_V02;
    double gpsTowUncNs = (double)gnss_measurement_info.svTimeSpeed.svTimeUncMs * 1e6;

    if (validMask & QMI_LOC_MASK_MEAS_STATUS_MS_VALID_V02) {
        /* sub-frame decode & TOW decode */
        gpsMeasurement.state = GPS_MEASUREMENT_STATE_SUBFRAME_SYNC |
                                GPS_MEASUREMENT_STATE_TOW_DECODED |
                                GPS_MEASUREMENT_STATE_BIT_SYNC |
                                GPS_MEASUREMENT_STATE_CODE_LOCK;
        gpsMeasurement.received_gps_tow_ns =
            ((double)gnss_measurement_info.svTimeSpeed.svTimeMs +
             (double)gnss_measurement_info.svTimeSpeed.svTimeSubMs) * 1e6;
        gpsMeasurement.received_gps_tow_uncertainty_ns = gpsTowUncNs;

    } else if ((validMask & bitSynMask) == bitSynMask) {
        /* bit sync */
        gpsMeasurement.state = GPS_MEASUREMENT_STATE_BIT_SYNC |
                                GPS_MEASUREMENT_STATE_CODE_LOCK;
        gpsMeasurement.received_gps_tow_ns =
            fmod(((double)gnss_measurement_info.svTimeSpeed.svTimeMs +
                  (double)gnss_measurement_info.svTimeSpeed.svTimeSubMs), 20) * 1e6;
        gpsMeasurement.received_gps_tow_uncertainty_ns = gpsTowUncNs;

    } else if (validMask & QMI_LOC_MASK_MEAS_STATUS_SM_VALID_V02) {
        /* code lock */
        gpsMeasurement.state = GPS_MEASUREMENT_STATE_CODE_LOCK;
        gpsMeasurement.received_gps_tow_ns =
             (double)gnss_measurement_info.svTimeSpeed.svTimeSubMs * 1e6;
        gpsMeasurement.received_gps_tow_uncertainty_ns = gpsTowUncNs;

    } else {
        /* by default */
        gpsMeasurement.state = GPS_MEASUREMENT_STATE_UNKNOWN;
        gpsMeasurement.received_gps_tow_ns = 0;
        gpsMeasurement.received_gps_tow_uncertainty_ns = 0;
    }

    // c_n0_dbhz
    gpsMeasurement.c_n0_dbhz = gnss_measurement_info.CNo/10.0;

    // pseudorange_rate_mps
    gpsMeasurement.pseudorange_rate_mps =
        gnss_measurement_info.svTimeSpeed.dopplerShift;

    // pseudorange_rate_uncertainty_mps
    gpsMeasurement.pseudorange_rate_uncertainty_mps =
        gnss_measurement_info.svTimeSpeed.dopplerShiftUnc;

    // accumulated_delta_range_state
    gpsMeasurement.accumulated_delta_range_state = GPS_ADR_STATE_UNKNOWN;

    gpsMeasurement.flags = flags;

    LOC_LOGV(" %s:%d]: GNSS measurement raw data received form modem: \n"
             " Input => gnssSvId | CNo "
             "| measurementStatus | dopplerShift |"
             " dopplerShiftUnc| svTimeMs | svTimeSubMs | svTimeUncMs"
             " | validMeasStatusMask | \n"
             " Input => %d | %d | 0x%04x%04x | %f | %f | %u | %f | %f | 0x%04x%04x |\n",
             __func__, __LINE__,
             gnss_measurement_info.gnssSvId,                                    // %d
             gnss_measurement_info.CNo,                                         // %d
             (uint32_t)(gnss_measurement_info.measurementStatus >> 32),         // %04x Upper 32
             (uint32_t)(gnss_measurement_info.measurementStatus & 0xFFFFFFFF),  // %04x Lower 32
             gnss_measurement_info.svTimeSpeed.dopplerShift,                    // %f
             gnss_measurement_info.svTimeSpeed.dopplerShiftUnc,                 // %f
             gnss_measurement_info.svTimeSpeed.svTimeMs,                        // %u
             gnss_measurement_info.svTimeSpeed.svTimeSubMs,                     // %f
             gnss_measurement_info.svTimeSpeed.svTimeUncMs,                     // %f
             (uint32_t)(gnss_measurement_info.validMeasStatusMask >> 32),       // %04x Upper 32
             (uint32_t)(gnss_measurement_info.validMeasStatusMask & 0xFFFFFFFF) // %04x Lower 32
            );

    LOC_LOGV(" %s:%d]: GNSS measurement data after conversion: \n"
             " Output => size | prn | time_offset_ns | state |"
             " received_gps_tow_ns| received_gps_tow_uncertainty_ns |c_n0_dbhz |"
             " pseudorange_rate_mps | pseudorange_rate_uncertainty_mps |"
             " accumulated_delta_range_state | flags \n"
             " Output => %d | %d | %f | %d | %lld | %lld | %f | %f | %f | %d | %d \n",
             __func__, __LINE__,
             gpsMeasurement.size,                              // %d
             gpsMeasurement.prn,                               // %d
             gpsMeasurement.time_offset_ns,                    // %f
             gpsMeasurement.state,                             // %d
             gpsMeasurement.received_gps_tow_ns,               // %lld
             gpsMeasurement.received_gps_tow_uncertainty_ns,   // %lld
             gpsMeasurement.c_n0_dbhz,                         // %f
             gpsMeasurement.pseudorange_rate_mps,              // %f
             gpsMeasurement.pseudorange_rate_uncertainty_mps,  // %f
             gpsMeasurement.accumulated_delta_range_state,     // %d
             gpsMeasurement.flags                              // %d
            );
}

/*convert GpsClock type from QMI LOC to loc eng format*/
void LocApiV02 :: convertGpsClock (GpsClock& gpsClock,
    const qmiLocEventGnssSvMeasInfoIndMsgT_v02& gnss_measurement_info)
{
    LOC_LOGV ("%s:%d]: entering\n", __func__, __LINE__);

    // size
    gpsClock.size = sizeof(GpsClock);

    // flag initiation
    int flags = 0;

    // type & time_ns & time_uncertainty_ns
    if (gnss_measurement_info.systemTime_valid &&
        gnss_measurement_info.systemTimeExt_valid) {

        uint16_t systemWeek = gnss_measurement_info.systemTime.systemWeek;
        uint32_t systemMsec = gnss_measurement_info.systemTime.systemMsec;
        float sysClkBias = gnss_measurement_info.systemTime.systemClkTimeBias;
        float sysClkUncMs = gnss_measurement_info.systemTime.systemClkTimeUncMs;
        int sourceOfTime = gnss_measurement_info.systemTimeExt.sourceOfTime;
        bool isTimeValid = (sysClkUncMs <= 15.0f); // 15ms

        if(systemWeek != C_GPS_WEEK_UNKNOWN && isTimeValid) {
            gpsClock.type = GPS_CLOCK_TYPE_GPS_TIME;
            double temp = (double)(systemWeek) * (double)WEEK_MSECS + (double)systemMsec;
            gpsClock.time_ns = (double)temp*1e6 -
                               (double)((int)(sysClkBias*1e6));
            flags |= GPS_CLOCK_HAS_TIME_UNCERTAINTY;
            gpsClock.time_uncertainty_ns = (double)sysClkUncMs * 1e6;

        } else {
            gpsClock.type = GPS_CLOCK_TYPE_UNKNOWN;
        }
    } else {
        gpsClock.type = GPS_CLOCK_TYPE_UNKNOWN;
    }

    LOC_LOGV(" %s:%d]: GNSS measurement clock data received form modem: \n"
             " Input => systemTime_valid | systemTimeExt_valid | systemWeek"
             " | systemMsec | systemClkTimeBias"
             " | systemClkTimeUncMs | sourceOfTime \n"
             " Input => %d | %d | %d | %d | %f | %f | %d \n",
             __func__, __LINE__,
             gnss_measurement_info.systemTime_valid,                      // %d
             gnss_measurement_info.systemTimeExt_valid,                   // %d
             gnss_measurement_info.systemTime.systemWeek,                 // %d
             gnss_measurement_info.systemTime.systemMsec,                 // %d
             gnss_measurement_info.systemTime.systemClkTimeBias,          // %f
             gnss_measurement_info.systemTime.systemClkTimeUncMs,         // %f
             gnss_measurement_info.systemTimeExt.sourceOfTime);           // %d

    LOC_LOGV(" %s:%d]: GNSS measurement clock after conversion: \n"
             " Output => type | time_ns | time_uncertainty_ns\n"
             " Output => %d | %lld | %f \n", __func__, __LINE__,
             gpsClock.type,                                               // %d
             gpsClock.time_ns,                                            // %lld
             gpsClock.time_uncertainty_ns);                               // %f

    gpsClock.flags = flags;
}

/* event callback registered with the loc_api v02 interface */
void LocApiV02 :: eventCb(locClientHandleType clientHandle,
  uint32_t eventId, locClientEventIndUnionType eventPayload)
{
  LOC_LOGD("%s:%d]: event id = %d\n", __func__, __LINE__,
                eventId);

  switch(eventId)
  {
    //Position Report
    case QMI_LOC_EVENT_POSITION_REPORT_IND_V02:
      reportPosition(eventPayload.pPositionReportEvent);
      break;

    // Satellite report
    case QMI_LOC_EVENT_GNSS_SV_INFO_IND_V02:
      reportSv(eventPayload.pGnssSvInfoReportEvent);
      break;

    // Status report
    case QMI_LOC_EVENT_ENGINE_STATE_IND_V02:
      reportEngineState(eventPayload.pEngineState);
      break;

    case QMI_LOC_EVENT_FIX_SESSION_STATE_IND_V02:
      reportFixSessionState(eventPayload.pFixSessionState);
      break;

    // NMEA
    case QMI_LOC_EVENT_NMEA_IND_V02:
      reportNmea(eventPayload.pNmeaReportEvent);
      break;

    // XTRA request
    case QMI_LOC_EVENT_INJECT_PREDICTED_ORBITS_REQ_IND_V02:
      LOC_LOGD("%s:%d]: XTRA download request\n", __func__,
                    __LINE__);
      reportXtraServerUrl(eventPayload.pInjectPredictedOrbitsReqEvent);
      requestXtraData();
      break;

    // time request
    case QMI_LOC_EVENT_INJECT_TIME_REQ_IND_V02:
      LOC_LOGD("%s:%d]: Time request\n", __func__,
                    __LINE__);
      requestTime();
      break;

    //position request
    case QMI_LOC_EVENT_INJECT_POSITION_REQ_IND_V02:
      LOC_LOGD("%s:%d]: Position request\n", __func__,
                    __LINE__);
      requestLocation();
      break;

    // NI request
    case QMI_LOC_EVENT_NI_NOTIFY_VERIFY_REQ_IND_V02:
      reportNiRequest(eventPayload.pNiNotifyVerifyReqEvent);
      break;

    // AGPS connection request
    case QMI_LOC_EVENT_LOCATION_SERVER_CONNECTION_REQ_IND_V02:
      reportAtlRequest(eventPayload.pLocationServerConnReqEvent);
      break;

    // GNSS Measurement Report
    case QMI_LOC_EVENT_GNSS_MEASUREMENT_REPORT_IND_V02:
      reportGnssMeasurementData(*eventPayload.pGnssSvRawInfoEvent);
      break;
  }
}

/* Call the service LocAdapterBase down event*/
void LocApiV02 :: errorCb(locClientHandleType handle,
                             locClientErrorEnumType errorId)
{
  if(errorId == eLOC_CLIENT_ERROR_SERVICE_UNAVAILABLE)
  {
    LOC_LOGE("%s:%d]: Service unavailable error\n",
                  __func__, __LINE__);

    handleEngineDownEvent();

    /* immediately send the engine up event so that
    the loc engine re-initializes the adapter and the
    loc-api_v02 interface */

    handleEngineUpEvent();
  }
}

static void ds_client_global_event_cb(ds_client_status_enum_type result,
                                       void *loc_adapter_cookie)
{
    LocApiV02 *locApiV02Instance =
        (LocApiV02 *)loc_adapter_cookie;
    locApiV02Instance->ds_client_event_cb(result);
    return;
}

void LocApiV02::ds_client_event_cb(ds_client_status_enum_type result)
{
    if(result == E_DS_CLIENT_DATA_CALL_CONNECTED) {
        LOC_LOGD("%s:%d]: Emergency call is up", __func__, __LINE__);
        reportDataCallOpened();
    }
    else if(result == E_DS_CLIENT_DATA_CALL_DISCONNECTED) {
        LOC_LOGE("%s:%d]: Emergency call is stopped", __func__, __LINE__);
        reportDataCallClosed();
    }
    return;
}

ds_client_cb_data ds_client_cb = {
    ds_client_global_event_cb
};

int LocApiV02 :: initDataServiceClient()
{
    int ret=0;
    ret = ds_client_init();
    LOC_LOGD("%s:%d]: ret = %d\n", __func__, __LINE__,ret);
    return ret;
}

int LocApiV02 :: openAndStartDataCall()
{
    enum loc_api_adapter_err ret;
    int profile_index;
    int pdp_type;
    ds_client_status_enum_type result = ds_client_open_call(&dsClientHandle,
                                                            &ds_client_cb,
                                                            (void *)this,
                                                            &profile_index,
                                                            &pdp_type);
    if(result == E_DS_CLIENT_SUCCESS) {
        result = ds_client_start_call(dsClientHandle, profile_index, pdp_type);

        if(result == E_DS_CLIENT_SUCCESS) {
            LOC_LOGD("%s:%d]: Request to start Emergency call sent\n",
                 __func__, __LINE__);
        ret = LOC_API_ADAPTER_ERR_SUCCESS;
        }
        else {
            LOC_LOGE("%s:%d]: Unable to bring up emergency call using DS. result = %d",
                 __func__, __LINE__, (int)result);
            ret = LOC_API_ADAPTER_ERR_UNSUPPORTED;
        }
    }
    else if(result == E_DS_CLIENT_RETRY_LATER) {
        LOC_LOGE("%s:%d]: Could not start emergency call. Retry after delay\n",
                 __func__, __LINE__);
        ret = LOC_API_ADAPTER_ERR_ENGINE_BUSY;
    }
    else {
        LOC_LOGE("%s:%d]: Unable to bring up emergency call using DS. ret = %d",
                 __func__, __LINE__, (int)ret);
        ret = LOC_API_ADAPTER_ERR_UNSUPPORTED;
    }

    return (int)ret;
}

void LocApiV02 :: stopDataCall()
{
    ds_client_status_enum_type ret =
        ds_client_stop_call(dsClientHandle);
    if (ret == E_DS_CLIENT_SUCCESS) {
        LOC_LOGD("%s:%d]: Request to Close SUPL ES call sent\n", __func__, __LINE__);
    }
    else {
        if (ret == E_DS_CLIENT_FAILURE_INVALID_HANDLE) {
            LOC_LOGE("%s:%d]: Conn handle not found for SUPL ES",
                     __func__, __LINE__);
        }
        LOC_LOGE("%s:%d]: Could not close SUPL ES call. Ret: %d\n"
                 ,__func__, __LINE__, ret);
    }
    return;
}

void LocApiV02 :: closeDataCall()
{
    ds_client_close_call(&dsClientHandle);
    LOC_LOGD("%s:%d]: Release data client handle\n", __func__, __LINE__);
    return;
}

enum loc_api_adapter_err LocApiV02 ::
getWwanZppFix(GpsLocation &zppLoc)
{
    locClientReqUnionType req_union;
    qmiLocGetAvailWwanPositionReqMsgT_v02 zpp_req;
    qmiLocGetAvailWwanPositionIndMsgT_v02 zpp_ind;
    memset(&zpp_ind, 0, sizeof(zpp_ind));
    memset(&zpp_req, 0, sizeof(zpp_req));
    memset(&zppLoc, 0, sizeof(zppLoc));

    req_union.pGetAvailWwanPositionReq = &zpp_req;

    LOC_LOGD("%s:%d]: Get ZPP Fix from available wwan position\n", __func__, __LINE__);

    locClientStatusEnumType status =
        loc_sync_send_req(clientHandle,
                          QMI_LOC_GET_AVAILABLE_WWAN_POSITION_REQ_V02,
                          req_union, LOC_ENGINE_SYNC_REQUEST_TIMEOUT,
                          QMI_LOC_GET_AVAILABLE_WWAN_POSITION_IND_V02,
                          &zpp_ind);

    if (status != eLOC_CLIENT_SUCCESS ||
        eQMI_LOC_SUCCESS_V02 != zpp_ind.status) {
        LOC_LOGD ("%s:%d]: getWwanZppFix may not be supported by modem"
                  " so will fallback to getBestAvailableZppFix"
                  " status = %s, zpp_ind.status = %s ",
                  __func__, __LINE__,
                  loc_get_v02_client_status_name(status),
                  loc_get_v02_qmi_status_name(zpp_ind.status));

        LocPosTechMask tech_mask;
        loc_api_adapter_err ret;
        ret = getBestAvailableZppFix(zppLoc, tech_mask);
        if (ret == LOC_API_ADAPTER_ERR_SUCCESS &&
            tech_mask != LOC_POS_TECH_MASK_DEFAULT &&
            tech_mask & LOC_POS_TECH_MASK_CELLID) {
            return LOC_API_ADAPTER_ERR_SUCCESS;
        } else {
            LOC_LOGD ("%s:%d]: getBestAvailableZppFix failed or"
                  " technoloy source includes GNSS that is not allowed"
                  " ret = %u, tech_mask = 0x%X ",
                  __func__, __LINE__, ret, tech_mask);
            return LOC_API_ADAPTER_ERR_GENERAL_FAILURE;
        }
    }

    LOC_LOGD("Got Zpp fix location validity (lat:%d, lon:%d, timestamp:%d accuracy:%d)",
             zpp_ind.latitude_valid,
             zpp_ind.longitude_valid,
             zpp_ind.timestampUtc_valid,
             zpp_ind.horUncCircular_valid);

    LOC_LOGD("(%.7f, %.7f), timestamp %llu, accuracy %f",
             zpp_ind.latitude,
             zpp_ind.longitude,
             zpp_ind.timestampUtc,
             zpp_ind.horUncCircular);

    zppLoc.size = sizeof(GpsLocation);
    if (zpp_ind.timestampUtc_valid) {
        zppLoc.timestamp = zpp_ind.timestampUtc;
    }
    else {
        /* The UTC time from modem is not valid.
        In this case, we use current system time instead.*/

        struct timespec time_info_current;
        clock_gettime(CLOCK_REALTIME,&time_info_current);
        zppLoc.timestamp = (time_info_current.tv_sec)*1e3 +
                           (time_info_current.tv_nsec)/1e6;
        LOC_LOGD("zpp timestamp got from system: %llu", zppLoc.timestamp);
    }

    if ((zpp_ind.latitude_valid == false) ||
        (zpp_ind.longitude_valid == false) ||
        (zpp_ind.horUncCircular_valid == false)) {
        return LOC_API_ADAPTER_ERR_GENERAL_FAILURE;
    }

    zppLoc.flags = GPS_LOCATION_HAS_LAT_LONG | GPS_LOCATION_HAS_ACCURACY;
    zppLoc.latitude = zpp_ind.latitude;
    zppLoc.longitude = zpp_ind.longitude;
    zppLoc.accuracy = zpp_ind.horUncCircular;

    if (zpp_ind.altitudeWrtEllipsoid_valid) {
        zppLoc.flags |= GPS_LOCATION_HAS_ALTITUDE;
        zppLoc.altitude = zpp_ind.altitudeWrtEllipsoid;
    }

    return LOC_API_ADAPTER_ERR_SUCCESS;
}

enum loc_api_adapter_err LocApiV02 :: getBestAvailableZppFix(GpsLocation & zppLoc)
{
    LocPosTechMask tech_mask;
    return getBestAvailableZppFix(zppLoc, tech_mask);
}

enum loc_api_adapter_err LocApiV02 ::
getBestAvailableZppFix(GpsLocation &zppLoc, LocPosTechMask &tech_mask)
{
    locClientReqUnionType req_union;

    qmiLocGetBestAvailablePositionIndMsgT_v02 zpp_ind;
    qmiLocGetBestAvailablePositionReqMsgT_v02 zpp_req;

    memset(&zpp_ind, 0, sizeof(zpp_ind));
    memset(&zpp_req, 0, sizeof(zpp_req));
    memset(&zppLoc, 0, sizeof(zppLoc));
    tech_mask = LOC_POS_TECH_MASK_DEFAULT;

    req_union.pGetBestAvailablePositionReq = &zpp_req;

    LOC_LOGD("%s:%d]: Get ZPP Fix from best available source\n", __func__, __LINE__);

    locClientStatusEnumType status =
        loc_sync_send_req(clientHandle,
                          QMI_LOC_GET_BEST_AVAILABLE_POSITION_REQ_V02,
                          req_union, LOC_ENGINE_SYNC_REQUEST_TIMEOUT,
                          QMI_LOC_GET_BEST_AVAILABLE_POSITION_IND_V02,
                          &zpp_ind);

    if (status != eLOC_CLIENT_SUCCESS ||
        eQMI_LOC_SUCCESS_V02 != zpp_ind.status) {
        LOC_LOGE ("%s:%d]: error! status = %s, zpp_ind.status = %s\n",
                  __func__, __LINE__,
                  loc_get_v02_client_status_name(status),
                  loc_get_v02_qmi_status_name(zpp_ind.status));
    } else {
        LOC_LOGD("Got Zpp fix location validity (lat:%d, lon:%d, timestamp:%d accuracy:%d)"
                 " (%.7f, %.7f), timestamp %llu, accuracy %f",
                 zpp_ind.latitude_valid,
                 zpp_ind.longitude_valid,
                 zpp_ind.timestampUtc_valid,
                 zpp_ind.horUncCircular_valid,
                 zpp_ind.latitude,
                 zpp_ind.longitude,
                 zpp_ind.timestampUtc,
                 zpp_ind.horUncCircular);

        zppLoc.size = sizeof(GpsLocation);
        if (zpp_ind.timestampUtc_valid) {
            zppLoc.timestamp = zpp_ind.timestampUtc;
        }
        else {
            /* The UTC time from modem is not valid.
            In this case, we use current system time instead.*/

            struct timespec time_info_current;
            clock_gettime(CLOCK_REALTIME,&time_info_current);
            zppLoc.timestamp = (time_info_current.tv_sec)*1e3 +
                               (time_info_current.tv_nsec)/1e6;
            LOC_LOGD("zpp timestamp got from system: %llu", zppLoc.timestamp);
        }

        if (zpp_ind.latitude_valid &&
            zpp_ind.longitude_valid &&
            zpp_ind.horUncCircular_valid ) {
            zppLoc.flags = GPS_LOCATION_HAS_LAT_LONG | GPS_LOCATION_HAS_ACCURACY;
            zppLoc.latitude = zpp_ind.latitude;
            zppLoc.longitude = zpp_ind.longitude;
            zppLoc.accuracy = zpp_ind.horUncCircular;

            if (zpp_ind.altitudeWrtEllipsoid_valid) {
                zppLoc.flags |= GPS_LOCATION_HAS_ALTITUDE;
                zppLoc.altitude = zpp_ind.altitudeWrtEllipsoid;
            }

            if (zpp_ind.horSpeed_valid) {
                zppLoc.flags |= GPS_LOCATION_HAS_SPEED;
                zppLoc.speed = zpp_ind.horSpeed;
            }

            if (zpp_ind.heading_valid) {
                zppLoc.flags |= GPS_LOCATION_HAS_BEARING;
                zppLoc.bearing = zpp_ind.heading;
            }

            if (zpp_ind.technologyMask_valid) {
                tech_mask = zpp_ind.technologyMask;
            }
        }
    }

    return convertErr(status);
}

/*Values for lock
  1 = Do not lock any position sessions
  2 = Lock MI position sessions
  3 = Lock MT position sessions
  4 = Lock all position sessions

  Returns values:
  zero on success; non-zero on failure
*/
int LocApiV02 :: setGpsLock(LOC_GPS_LOCK_MASK lockMask)
{
    qmiLocSetEngineLockReqMsgT_v02 setEngineLockReq;
    qmiLocSetEngineLockIndMsgT_v02 setEngineLockInd;
    locClientStatusEnumType status;
    locClientReqUnionType req_union;
    int ret=0;

    LOC_LOGD("%s:%d]: Set Gps Lock: %x\n", __func__, __LINE__, lockMask);
    setEngineLockReq.lockType = convertGpsLockMask(lockMask);
    req_union.pSetEngineLockReq = &setEngineLockReq;
    memset(&setEngineLockInd, 0, sizeof(setEngineLockInd));
    status = loc_sync_send_req(clientHandle,
                               QMI_LOC_SET_ENGINE_LOCK_REQ_V02,
                               req_union, LOC_ENGINE_SYNC_REQUEST_TIMEOUT,
                               QMI_LOC_SET_ENGINE_LOCK_IND_V02,
                               &setEngineLockInd);

    if(status != eLOC_CLIENT_SUCCESS || setEngineLockInd.status != eQMI_LOC_SUCCESS_V02) {
        LOC_LOGE("%s:%d]: Set engine lock failed. status: %s, ind status:%s\n",
                 __func__, __LINE__,
                 loc_get_v02_client_status_name(status),
                 loc_get_v02_qmi_status_name(setEngineLockInd.status));
        ret = -1;
    }
    LOC_LOGD("%s:%d]: exit\n", __func__, __LINE__);
    return ret;
}
/*
  Returns
  Current value of GPS Lock on success
  -1 on failure
*/
int LocApiV02 :: getGpsLock()
{
    qmiLocGetEngineLockReqMsgT_v02 getEngineLockReq;
    qmiLocGetEngineLockIndMsgT_v02 getEngineLockInd;
    locClientStatusEnumType status;
    locClientReqUnionType req_union;
    int ret=0;
    LOC_LOGD("%s:%d]: Enter\n", __func__, __LINE__);
    memset(&getEngineLockInd, 0, sizeof(getEngineLockInd));

    //Passing req_union as a parameter even though this request has no payload
    //since NULL or 0 gives an error during compilation
    status = loc_sync_send_req(clientHandle,
                               QMI_LOC_GET_ENGINE_LOCK_REQ_V02,
                               req_union, LOC_ENGINE_SYNC_REQUEST_TIMEOUT,
                               QMI_LOC_GET_ENGINE_LOCK_IND_V02,
                               &getEngineLockInd);
    if(status != eLOC_CLIENT_SUCCESS || getEngineLockInd.status != eQMI_LOC_SUCCESS_V02) {
        LOC_LOGE("%s:%d]: Set engine lock failed. status: %s, ind status:%s\n",
                 __func__, __LINE__,
                 loc_get_v02_client_status_name(status),
                 loc_get_v02_qmi_status_name(getEngineLockInd.status));
        ret = -1;
    }
    else {
        if(getEngineLockInd.lockType_valid) {
            ret = (int)getEngineLockInd.lockType;
            LOC_LOGD("%s:%d]: Lock Type: %d\n", __func__, __LINE__, ret);
        }
        else {
            LOC_LOGE("%s:%d]: Lock Type not valid\n", __func__, __LINE__);
            ret = -1;
        }
    }
    LOC_LOGD("%s:%d]: Exit\n", __func__, __LINE__);
    return ret;
}

enum loc_api_adapter_err LocApiV02:: setXtraVersionCheck(enum xtra_version_check check)
{
    qmiLocSetXtraVersionCheckReqMsgT_v02 req;
    qmiLocSetXtraVersionCheckIndMsgT_v02 ind;
    locClientStatusEnumType status;
    locClientReqUnionType req_union;
    enum loc_api_adapter_err ret = LOC_API_ADAPTER_ERR_SUCCESS;

    LOC_LOGD("%s:%d]: Enter. check: %d", __func__, __LINE__, check);
    memset(&req, 0, sizeof(req));
    memset(&ind, 0, sizeof(ind));
    switch (check) {
    case DISABLED:
        req.xtraVersionCheckMode = eQMI_LOC_XTRA_VERSION_CHECK_DISABLE_V02;
        break;
    case AUTO:
        req.xtraVersionCheckMode = eQMI_LOC_XTRA_VERSION_CHECK_AUTO_V02;
        break;
    case XTRA2:
        req.xtraVersionCheckMode = eQMI_LOC_XTRA_VERSION_CHECK_XTRA2_V02;
        break;
    case XTRA3:
        req.xtraVersionCheckMode = eQMI_LOC_XTRA_VERSION_CHECK_XTRA3_V02;
        break;
    default:
        req.xtraVersionCheckMode = eQMI_LOC_XTRA_VERSION_CHECK_DISABLE_V02;
        break;
    }

    req_union.pSetXtraVersionCheckReq = &req;
    status = loc_sync_send_req(clientHandle,
                               QMI_LOC_SET_XTRA_VERSION_CHECK_REQ_V02,
                               req_union, LOC_ENGINE_SYNC_REQUEST_TIMEOUT,
                               QMI_LOC_SET_XTRA_VERSION_CHECK_IND_V02,
                               &ind);
    if(status != eLOC_CLIENT_SUCCESS || ind.status != eQMI_LOC_SUCCESS_V02) {
        LOC_LOGE("%s:%d]: Set xtra version check failed. status: %s, ind status:%s\n",
                 __func__, __LINE__,
                 loc_get_v02_client_status_name(status),
                 loc_get_v02_qmi_status_name(ind.status));
        ret = LOC_API_ADAPTER_ERR_GENERAL_FAILURE;
    }

    LOC_LOGD("%s:%d]: Exit. ret: %d", __func__, __LINE__, (int)ret);
    return ret;
}

void LocApiV02 :: installAGpsCert(const DerEncodedCertificate* pData,
                                  size_t numberOfCerts,
                                  uint32_t slotBitMask)
{
    LOC_LOGD("%s:%d]:, slot mask=%u number of certs=%u",
            __func__, __LINE__, slotBitMask, numberOfCerts);

    uint8_t certIndex = 0;
    for (uint8_t slot = 0; slot <= AGPS_CERTIFICATE_MAX_SLOTS-1; slot++, slotBitMask >>= 1)
    {
        if (slotBitMask & 1) //slot is writable
        {
            if (certIndex < numberOfCerts && pData[certIndex].data && pData[certIndex].length > 0)
            {
                LOC_LOGD("%s:%d]:, Inject cert#%u slot=%u length=%u",
                         __func__, __LINE__, certIndex, slot, pData[certIndex].length);

                locClientReqUnionType req_union;
                locClientStatusEnumType status;
                qmiLocInjectSuplCertificateReqMsgT_v02 injectCertReq;
                qmiLocInjectSuplCertificateIndMsgT_v02 injectCertInd;

                memset(&injectCertReq, 0, sizeof(injectCertReq));
                injectCertReq.suplCertId = slot;
                injectCertReq.suplCertData_len = pData[certIndex].length;
                memcpy(injectCertReq.suplCertData, pData[certIndex].data, pData[certIndex].length);

                req_union.pInjectSuplCertificateReq = &injectCertReq;

                status = loc_sync_send_req(clientHandle,
                                           QMI_LOC_INJECT_SUPL_CERTIFICATE_REQ_V02,
                                           req_union, LOC_ENGINE_SYNC_REQUEST_TIMEOUT,
                                           QMI_LOC_INJECT_SUPL_CERTIFICATE_IND_V02,
                                           &injectCertInd);

                if (status != eLOC_CLIENT_SUCCESS ||
                    eQMI_LOC_SUCCESS_V02 != injectCertInd.status)
                {
                    LOC_LOGE ("%s:%d]: inject-error status = %s, set_server_ind.status = %s",
                              __func__,__LINE__,
                              loc_get_v02_client_status_name(status),
                              loc_get_v02_qmi_status_name(injectCertInd.status));
                }

                certIndex++; //move to next cert

            } else {

                LOC_LOGD("%s:%d]:, Delete slot=%u",
                         __func__, __LINE__, slot);

                // A fake cert is injected first before delete is called to workaround
                // an issue that is seen with trying to delete an empty slot.
                {
                    locClientReqUnionType req_union;
                    locClientStatusEnumType status;
                    qmiLocInjectSuplCertificateReqMsgT_v02 injectFakeCertReq;
                    qmiLocInjectSuplCertificateIndMsgT_v02 injectFakeCertInd;

                    memset(&injectFakeCertReq, 0, sizeof(injectFakeCertReq));
                    injectFakeCertReq.suplCertId = slot;
                    injectFakeCertReq.suplCertData_len = 1;
                    injectFakeCertReq.suplCertData[0] = 1;

                    req_union.pInjectSuplCertificateReq = &injectFakeCertReq;

                    status = loc_sync_send_req(clientHandle,
                                       QMI_LOC_INJECT_SUPL_CERTIFICATE_REQ_V02,
                                       req_union, LOC_ENGINE_SYNC_REQUEST_TIMEOUT,
                                       QMI_LOC_INJECT_SUPL_CERTIFICATE_IND_V02,
                                       &injectFakeCertInd);

                    if (status != eLOC_CLIENT_SUCCESS ||
                        eQMI_LOC_SUCCESS_V02 != injectFakeCertInd.status)
                    {
                        LOC_LOGE ("%s:%d]: inject-fake-error status = %s, set_server_ind.status = %s",
                                  __func__,__LINE__,
                                  loc_get_v02_client_status_name(status),
                                  loc_get_v02_qmi_status_name(injectFakeCertInd.status));
                    }
                }

                locClientReqUnionType req_union;
                locClientStatusEnumType status;
                qmiLocDeleteSuplCertificateReqMsgT_v02 deleteCertReq;
                qmiLocDeleteSuplCertificateIndMsgT_v02 deleteCertInd;

                memset(&deleteCertReq, 0, sizeof(deleteCertReq));
                deleteCertReq.suplCertId = slot;
                deleteCertReq.suplCertId_valid = 1;

                req_union.pDeleteSuplCertificateReq = &deleteCertReq;

                status = loc_sync_send_req(clientHandle,
                                           QMI_LOC_DELETE_SUPL_CERTIFICATE_REQ_V02,
                                           req_union, LOC_ENGINE_SYNC_REQUEST_TIMEOUT,
                                           QMI_LOC_DELETE_SUPL_CERTIFICATE_IND_V02,
                                           &deleteCertInd);

                if (status != eLOC_CLIENT_SUCCESS ||
                    eQMI_LOC_SUCCESS_V02 != deleteCertInd.status)
                {
                    LOC_LOGE("%s:%d]: delete-error status = %s, set_server_ind.status = %s",
                              __func__,__LINE__,
                              loc_get_v02_client_status_name(status),
                              loc_get_v02_qmi_status_name(deleteCertInd.status));
                }
            }
        } else {
            LOC_LOGD("%s:%d]:, Not writable slot=%u",
                     __func__, __LINE__, slot);
        }
    }
}

/*
  Returns
  0: update the gps reporting event successfully
  -1: on failure
*/
int LocApiV02 :: updateRegistrationMask(LOC_API_ADAPTER_EVENT_MASK_T event,
                                        loc_registration_mask_status isEnabled)
{
    LOC_LOGD("%s:%d]: Enter\n", __func__, __LINE__);

    return open((isEnabled == LOC_REGISTRATION_MASK_ENABLED)?(mMask|event):(mMask&~event));
}

bool LocApiV02 :: gnssConstellationConfig()
{
    return mGnssMeasurementSupported == sup_yes;
}

void LocApiV02 :: cacheGnssMeasurementSupport()
{
    if (sup_unknown == mGnssMeasurementSupported) {
        if ((mQmiMask & QMI_LOC_EVENT_MASK_POSITION_REPORT_V02) ==
            QMI_LOC_EVENT_MASK_POSITION_REPORT_V02) {
            /*for GNSS Measurement service, use
              QMI_LOC_SET_GNSS_CONSTELL_REPORT_CONFIG_V02
              to check if modem support this feature or not*/
            LOC_LOGD("%s:%d]: set GNSS measurement to report gps measurement only.\n",
                     __func__, __LINE__);

            qmiLocSetGNSSConstRepConfigReqMsgT_v02 setGNSSConstRepConfigReq;
            qmiLocSetGNSSConstRepConfigIndMsgT_v02 setGNSSConstRepConfigInd;
            memset(&setGNSSConstRepConfigReq, 0, sizeof(setGNSSConstRepConfigReq));
            memset(&setGNSSConstRepConfigInd, 0, sizeof(setGNSSConstRepConfigInd));

            locClientStatusEnumType status;
            locClientReqUnionType req_union;

            setGNSSConstRepConfigReq.measReportConfig_valid = true;
            setGNSSConstRepConfigReq.measReportConfig = eQMI_SYSTEM_GPS_V02;
            req_union.pSetGNSSConstRepConfigReq = &setGNSSConstRepConfigReq;

            status = loc_sync_send_req(clientHandle,
                                       QMI_LOC_SET_GNSS_CONSTELL_REPORT_CONFIG_V02,
                                       req_union,
                                       LOC_ENGINE_SYNC_REQUEST_TIMEOUT,
                                       QMI_LOC_SET_GNSS_CONSTELL_REPORT_CONFIG_IND_V02,
                                       &setGNSSConstRepConfigInd);

            if(status != eLOC_CLIENT_SUCCESS ||
               setGNSSConstRepConfigInd.status != eQMI_LOC_SUCCESS_V02) {
                LOC_LOGD("%s:%d]: Set GNSS constellation failed."
                         " status: %s, ind status:%s\n",
                         __func__, __LINE__,
                         loc_get_v02_client_status_name(status),
                         loc_get_v02_qmi_status_name(setGNSSConstRepConfigInd.status));
                mGnssMeasurementSupported = sup_no;
            } else {
                LOC_LOGD("%s:%d]: Set GNSS constellation succeeded.\n",
                         __func__, __LINE__);
                mGnssMeasurementSupported = sup_yes;
            }
        }
    }

    LOC_LOGV("%s:%d]: mGnssMeasurementSupported is %d\n", __func__, __LINE__, mGnssMeasurementSupported);
}
