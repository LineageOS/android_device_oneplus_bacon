/* Copyright (c) 2011-2015, The Linux Foundation. All rights reserved.
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

#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include <stdbool.h>
#include <stdint.h>

#include "qmi_client.h"
#include "qmi_idl_lib.h"
#include "qmi_cci_target_ext.h"

#if defined( _ANDROID_)
#include "qmi_cci_target.h"
#include "qmi_cci_common.h"
#define LOG_NDEBUG 0
#define LOG_TAG "LocSvc_api_v02"
#endif //_ANDROID_


#include "loc_api_v02_client.h"
#include "loc_util_log.h"

#ifdef LOC_UTIL_TARGET_OFF_TARGET

// timeout in ms before send_msg_sync should return
#define LOC_CLIENT_ACK_TIMEOUT (5000)

#else

// timeout in ms before send_msg_sync should return
#define LOC_CLIENT_ACK_TIMEOUT (1000)

#endif //LOC_UTIL_TARGET_OFF_TARGET

#define LOC_CLIENT_MAX_OPEN_RETRIES (20)
#define LOC_CLIENT_TIME_BETWEEN_OPEN_RETRIES (1)

enum
{
  //! Special value for selecting any available service
  /** This value enables selection of any available service */
  eLOC_CLIENT_INSTANCE_ID_ANY = -1,
  //! qca1530 service id value
  /** qca1530 service daemon uses service id value 1 */
  eLOC_CLIENT_INSTANCE_ID_QCA1530 = 1,
  //! GSS service id value
  /* GSS service id value is 0, but here it is set to -1 for compatibitily */
  eLOC_CLIENT_INSTANCE_ID_GSS = eLOC_CLIENT_INSTANCE_ID_ANY,
  //! MSM service id value
  /** MSM service id value is 0, but here it is set to -1 for compatibitily */
  eLOC_CLIENT_INSTANCE_ID_MSM = eLOC_CLIENT_INSTANCE_ID_ANY,
  //! MDM service id value
  /** MDM connects using QMUXD and assigned a value of
      QMI_CLIENT_QMUX_RMNET_USB_INSTANCE_0 ("qmi_client_instance_defs.h", 37).
      -1 for compatibility */
  eLOC_CLIENT_INSTANCE_ID_MDM = eLOC_CLIENT_INSTANCE_ID_ANY,
  /*  GSS service id value is 0, for auto config  */
  eLOC_CLIENT_INSTANCE_ID_GSS_AUTO = 0
};

/* Table to relate eventId, size and mask value used to enable the event*/
typedef struct
{
  uint32_t               eventId;
  size_t                 eventSize;
  locClientEventMaskType eventMask;
}locClientEventIndTableStructT;


static locClientEventIndTableStructT locClientEventIndTable[]= {

  // position report ind
  { QMI_LOC_EVENT_POSITION_REPORT_IND_V02,
    sizeof(qmiLocEventPositionReportIndMsgT_v02),
    QMI_LOC_EVENT_MASK_POSITION_REPORT_V02 },

  // satellite report ind
  { QMI_LOC_EVENT_GNSS_SV_INFO_IND_V02,
    sizeof(qmiLocEventGnssSvInfoIndMsgT_v02),
    QMI_LOC_EVENT_MASK_GNSS_SV_INFO_V02 },

  // NMEA report ind
  { QMI_LOC_EVENT_NMEA_IND_V02,
    sizeof(qmiLocEventNmeaIndMsgT_v02),
    QMI_LOC_EVENT_MASK_NMEA_V02 },

  //NI event ind
  { QMI_LOC_EVENT_NI_NOTIFY_VERIFY_REQ_IND_V02,
    sizeof(qmiLocEventNiNotifyVerifyReqIndMsgT_v02),
    QMI_LOC_EVENT_MASK_NI_NOTIFY_VERIFY_REQ_V02 },

  //Time Injection Request Ind
  { QMI_LOC_EVENT_INJECT_TIME_REQ_IND_V02,
    sizeof(qmiLocEventInjectTimeReqIndMsgT_v02),
    QMI_LOC_EVENT_MASK_INJECT_TIME_REQ_V02 },

  //Predicted Orbits Injection Request
  { QMI_LOC_EVENT_INJECT_PREDICTED_ORBITS_REQ_IND_V02,
    sizeof(qmiLocEventInjectPredictedOrbitsReqIndMsgT_v02),
    QMI_LOC_EVENT_MASK_INJECT_PREDICTED_ORBITS_REQ_V02 },

  //Position Injection Request Ind
  { QMI_LOC_EVENT_INJECT_POSITION_REQ_IND_V02,
    sizeof(qmiLocEventInjectPositionReqIndMsgT_v02),
    QMI_LOC_EVENT_MASK_INJECT_POSITION_REQ_V02 } ,

  //Engine State Report Ind
  { QMI_LOC_EVENT_ENGINE_STATE_IND_V02,
    sizeof(qmiLocEventEngineStateIndMsgT_v02),
    QMI_LOC_EVENT_MASK_ENGINE_STATE_V02 },

  //Fix Session State Report Ind
  { QMI_LOC_EVENT_FIX_SESSION_STATE_IND_V02,
    sizeof(qmiLocEventFixSessionStateIndMsgT_v02),
    QMI_LOC_EVENT_MASK_FIX_SESSION_STATE_V02 },

  //Wifi Request Indication
  { QMI_LOC_EVENT_WIFI_REQ_IND_V02,
    sizeof(qmiLocEventWifiReqIndMsgT_v02),
    QMI_LOC_EVENT_MASK_WIFI_REQ_V02 },

  //Sensor Streaming Ready Status Ind
  { QMI_LOC_EVENT_SENSOR_STREAMING_READY_STATUS_IND_V02,
    sizeof(qmiLocEventSensorStreamingReadyStatusIndMsgT_v02),
    QMI_LOC_EVENT_MASK_SENSOR_STREAMING_READY_STATUS_V02 },

  // Time Sync Request Indication
  { QMI_LOC_EVENT_TIME_SYNC_REQ_IND_V02,
    sizeof(qmiLocEventTimeSyncReqIndMsgT_v02),
    QMI_LOC_EVENT_MASK_TIME_SYNC_REQ_V02 },

  //Set Spi Streaming Report Event
  { QMI_LOC_EVENT_SET_SPI_STREAMING_REPORT_IND_V02,
    sizeof(qmiLocEventSetSpiStreamingReportIndMsgT_v02),
    QMI_LOC_EVENT_MASK_SET_SPI_STREAMING_REPORT_V02 },

  //Location Server Connection Request event
  { QMI_LOC_EVENT_LOCATION_SERVER_CONNECTION_REQ_IND_V02,
    sizeof(qmiLocEventLocationServerConnectionReqIndMsgT_v02),
    QMI_LOC_EVENT_MASK_LOCATION_SERVER_CONNECTION_REQ_V02 },

  // NI Geofence Event
  { QMI_LOC_EVENT_NI_GEOFENCE_NOTIFICATION_IND_V02,
    sizeof(qmiLocEventNiGeofenceNotificationIndMsgT_v02),
    QMI_LOC_EVENT_MASK_NI_GEOFENCE_NOTIFICATION_V02},

  // Geofence General Alert Event
  { QMI_LOC_EVENT_GEOFENCE_GEN_ALERT_IND_V02,
    sizeof(qmiLocEventGeofenceGenAlertIndMsgT_v02),
    QMI_LOC_EVENT_MASK_GEOFENCE_GEN_ALERT_V02},

  //Geofence Breach event
  { QMI_LOC_EVENT_GEOFENCE_BREACH_NOTIFICATION_IND_V02,
    sizeof(qmiLocEventGeofenceBreachIndMsgT_v02),
    QMI_LOC_EVENT_MASK_GEOFENCE_BREACH_NOTIFICATION_V02},

  //Geofence Batched Breach event
  { QMI_LOC_EVENT_GEOFENCE_BATCHED_BREACH_NOTIFICATION_IND_V02,
    sizeof(qmiLocEventGeofenceBatchedBreachIndMsgT_v02),
    QMI_LOC_EVENT_MASK_GEOFENCE_BATCH_BREACH_NOTIFICATION_V02},

  //Pedometer Control event
  { QMI_LOC_EVENT_PEDOMETER_CONTROL_IND_V02,
    sizeof(qmiLocEventPedometerControlIndMsgT_v02),
    QMI_LOC_EVENT_MASK_PEDOMETER_CONTROL_V02 },

  //Motion Data Control event
  { QMI_LOC_EVENT_MOTION_DATA_CONTROL_IND_V02,
    sizeof(qmiLocEventMotionDataControlIndMsgT_v02),
    QMI_LOC_EVENT_MASK_MOTION_DATA_CONTROL_V02 },

  //Wifi AP data request event
  { QMI_LOC_EVENT_INJECT_WIFI_AP_DATA_REQ_IND_V02,
    sizeof(qmiLocEventInjectWifiApDataReqIndMsgT_v02),
    QMI_LOC_EVENT_MASK_INJECT_WIFI_AP_DATA_REQ_V02 },

  //Get Batching On Fix Event
  { QMI_LOC_EVENT_LIVE_BATCHED_POSITION_REPORT_IND_V02,
    sizeof(qmiLocEventLiveBatchedPositionReportIndMsgT_v02),
    QMI_LOC_EVENT_MASK_LIVE_BATCHED_POSITION_REPORT_V02 },

  //Get Batching On Full Event
  { QMI_LOC_EVENT_BATCH_FULL_NOTIFICATION_IND_V02,
    sizeof(qmiLocEventBatchFullIndMsgT_v02),
    QMI_LOC_EVENT_MASK_BATCH_FULL_NOTIFICATION_V02 },

   //Vehicle Data Readiness event
   { QMI_LOC_EVENT_VEHICLE_DATA_READY_STATUS_IND_V02,
     sizeof(qmiLocEventVehicleDataReadyIndMsgT_v02),
     QMI_LOC_EVENT_MASK_VEHICLE_DATA_READY_STATUS_V02 },

  //Geofence Proximity event
  { QMI_LOC_EVENT_GEOFENCE_PROXIMITY_NOTIFICATION_IND_V02,
    sizeof(qmiLocEventGeofenceProximityIndMsgT_v02),
    QMI_LOC_EVENT_MASK_GEOFENCE_PROXIMITY_NOTIFICATION_V02},

  // for GDT
  { QMI_LOC_EVENT_GDT_UPLOAD_BEGIN_STATUS_REQ_IND_V02,
    sizeof(qmiLocEventGdtUploadBeginStatusReqIndMsgT_v02),
    QMI_LOC_EVENT_MASK_GDT_UPLOAD_BEGIN_REQ_V02,
  },

  { QMI_LOC_EVENT_GDT_UPLOAD_END_REQ_IND_V02,
    sizeof(qmiLocEventGdtUploadEndReqIndMsgT_v02),
    QMI_LOC_EVENT_MASK_GDT_UPLOAD_END_REQ_V02,
  },

   //GNSS measurement event
  { QMI_LOC_EVENT_GNSS_MEASUREMENT_REPORT_IND_V02 ,
    sizeof(qmiLocEventGnssSvMeasInfoIndMsgT_v02),
    QMI_LOC_EVENT_MASK_GNSS_MEASUREMENT_REPORT_V02},

  { QMI_LOC_EVENT_DBT_POSITION_REPORT_IND_V02,
    sizeof(qmiLocEventDbtPositionReportIndMsgT_v02),
    0},

  { QMI_LOC_EVENT_GEOFENCE_BATCHED_DWELL_NOTIFICATION_IND_V02,
    sizeof(qmiLocEventGeofenceBatchedDwellIndMsgT_v02),
    QMI_LOC_EVENT_MASK_GEOFENCE_BATCH_DWELL_NOTIFICATION_V02},

  { QMI_LOC_EVENT_GET_TIME_ZONE_INFO_IND_V02,
    sizeof(qmiLocEventGetTimeZoneReqIndMsgT_v02),
    QMI_LOC_EVENT_MASK_GET_TIME_ZONE_REQ_V02},

  // Batching Status event
  { QMI_LOC_EVENT_BATCHING_STATUS_IND_V02,
    sizeof(qmiLocEventBatchingStatusIndMsgT_v02),
    QMI_LOC_EVENT_MASK_BATCHING_STATUS_V02}
};

/* table to relate the respInd Id with its size */
typedef struct
{
  uint32_t respIndId;
  size_t   respIndSize;
}locClientRespIndTableStructT;

static locClientRespIndTableStructT locClientRespIndTable[]= {

  // get service revision ind
  { QMI_LOC_GET_SERVICE_REVISION_IND_V02,
    sizeof(qmiLocGetServiceRevisionIndMsgT_v02)},

  // Get Fix Criteria Resp Ind
  { QMI_LOC_GET_FIX_CRITERIA_IND_V02,
     sizeof(qmiLocGetFixCriteriaIndMsgT_v02)},

  // NI User Resp In
  { QMI_LOC_NI_USER_RESPONSE_IND_V02,
    sizeof(qmiLocNiUserRespIndMsgT_v02)},

  //Inject Predicted Orbits Data Resp Ind
  { QMI_LOC_INJECT_PREDICTED_ORBITS_DATA_IND_V02,
    sizeof(qmiLocInjectPredictedOrbitsDataIndMsgT_v02)},

  //Get Predicted Orbits Data Src Resp Ind
  { QMI_LOC_GET_PREDICTED_ORBITS_DATA_SOURCE_IND_V02,
    sizeof(qmiLocGetPredictedOrbitsDataSourceIndMsgT_v02)},

  // Get Predicted Orbits Data Validity Resp Ind
   { QMI_LOC_GET_PREDICTED_ORBITS_DATA_VALIDITY_IND_V02,
     sizeof(qmiLocGetPredictedOrbitsDataValidityIndMsgT_v02)},

   // Inject UTC Time Resp Ind
   { QMI_LOC_INJECT_UTC_TIME_IND_V02,
     sizeof(qmiLocInjectUtcTimeIndMsgT_v02)},

   //Inject Position Resp Ind
   { QMI_LOC_INJECT_POSITION_IND_V02,
     sizeof(qmiLocInjectPositionIndMsgT_v02)},

   //Set Engine Lock Resp Ind
   { QMI_LOC_SET_ENGINE_LOCK_IND_V02,
     sizeof(qmiLocSetEngineLockIndMsgT_v02)},

   //Get Engine Lock Resp Ind
   { QMI_LOC_GET_ENGINE_LOCK_IND_V02,
     sizeof(qmiLocGetEngineLockIndMsgT_v02)},

   //Set SBAS Config Resp Ind
   { QMI_LOC_SET_SBAS_CONFIG_IND_V02,
     sizeof(qmiLocSetSbasConfigIndMsgT_v02)},

   //Get SBAS Config Resp Ind
   { QMI_LOC_GET_SBAS_CONFIG_IND_V02,
     sizeof(qmiLocGetSbasConfigIndMsgT_v02)},

   //Set NMEA Types Resp Ind
   { QMI_LOC_SET_NMEA_TYPES_IND_V02,
     sizeof(qmiLocSetNmeaTypesIndMsgT_v02)},

   //Get NMEA Types Resp Ind
   { QMI_LOC_GET_NMEA_TYPES_IND_V02,
     sizeof(qmiLocGetNmeaTypesIndMsgT_v02)},

   //Set Low Power Mode Resp Ind
   { QMI_LOC_SET_LOW_POWER_MODE_IND_V02,
     sizeof(qmiLocSetLowPowerModeIndMsgT_v02)},

   //Get Low Power Mode Resp Ind
   { QMI_LOC_GET_LOW_POWER_MODE_IND_V02,
     sizeof(qmiLocGetLowPowerModeIndMsgT_v02)},

   //Set Server Resp Ind
   { QMI_LOC_SET_SERVER_IND_V02,
     sizeof(qmiLocSetServerIndMsgT_v02)},

   //Get Server Resp Ind
   { QMI_LOC_GET_SERVER_IND_V02,
     sizeof(qmiLocGetServerIndMsgT_v02)},

    //Delete Assist Data Resp Ind
   { QMI_LOC_DELETE_ASSIST_DATA_IND_V02,
     sizeof(qmiLocDeleteAssistDataIndMsgT_v02)},

   //Set AP cache injection Resp Ind
   { QMI_LOC_INJECT_APCACHE_DATA_IND_V02,
     sizeof(qmiLocInjectApCacheDataIndMsgT_v02)},

   //Set No AP cache injection Resp Ind
   { QMI_LOC_INJECT_APDONOTCACHE_DATA_IND_V02,
     sizeof(qmiLocInjectApDoNotCacheDataIndMsgT_v02)},

   //Set XTRA-T Session Control Resp Ind
   { QMI_LOC_SET_XTRA_T_SESSION_CONTROL_IND_V02,
     sizeof(qmiLocSetXtraTSessionControlIndMsgT_v02)},

   //Get XTRA-T Session Control Resp Ind
   { QMI_LOC_GET_XTRA_T_SESSION_CONTROL_IND_V02,
     sizeof(qmiLocGetXtraTSessionControlIndMsgT_v02)},

   //Inject Wifi Position Resp Ind
   { QMI_LOC_INJECT_WIFI_POSITION_IND_V02,
     sizeof(qmiLocInjectWifiPositionIndMsgT_v02)},

   //Notify Wifi Status Resp Ind
   { QMI_LOC_NOTIFY_WIFI_STATUS_IND_V02,
     sizeof(qmiLocNotifyWifiStatusIndMsgT_v02)},

   //Get Registered Events Resp Ind
   { QMI_LOC_GET_REGISTERED_EVENTS_IND_V02,
     sizeof(qmiLocGetRegisteredEventsIndMsgT_v02)},

   //Set Operation Mode Resp Ind
   { QMI_LOC_SET_OPERATION_MODE_IND_V02,
     sizeof(qmiLocSetOperationModeIndMsgT_v02)},

   //Get Operation Mode Resp Ind
   { QMI_LOC_GET_OPERATION_MODE_IND_V02,
     sizeof(qmiLocGetOperationModeIndMsgT_v02)},

   //Set SPI Status Resp Ind
   { QMI_LOC_SET_SPI_STATUS_IND_V02,
     sizeof(qmiLocSetSpiStatusIndMsgT_v02)},

   //Inject Sensor Data Resp Ind
   { QMI_LOC_INJECT_SENSOR_DATA_IND_V02,
     sizeof(qmiLocInjectSensorDataIndMsgT_v02)},

   //Inject Time Sync Data Resp Ind
   { QMI_LOC_INJECT_TIME_SYNC_DATA_IND_V02,
     sizeof(qmiLocInjectTimeSyncDataIndMsgT_v02)},

   //Set Cradle Mount config Resp Ind
   { QMI_LOC_SET_CRADLE_MOUNT_CONFIG_IND_V02,
     sizeof(qmiLocSetCradleMountConfigIndMsgT_v02)},

   //Get Cradle Mount config Resp Ind
   { QMI_LOC_GET_CRADLE_MOUNT_CONFIG_IND_V02,
     sizeof(qmiLocGetCradleMountConfigIndMsgT_v02)},

   //Set External Power config Resp Ind
   { QMI_LOC_SET_EXTERNAL_POWER_CONFIG_IND_V02,
     sizeof(qmiLocSetExternalPowerConfigIndMsgT_v02)},

   //Get External Power config Resp Ind
   { QMI_LOC_GET_EXTERNAL_POWER_CONFIG_IND_V02,
     sizeof(qmiLocGetExternalPowerConfigIndMsgT_v02)},

   //Location server connection status
   { QMI_LOC_INFORM_LOCATION_SERVER_CONN_STATUS_IND_V02,
     sizeof(qmiLocInformLocationServerConnStatusIndMsgT_v02)},

   //Set Protocol Config Parameters
   { QMI_LOC_SET_PROTOCOL_CONFIG_PARAMETERS_IND_V02,
     sizeof(qmiLocSetProtocolConfigParametersIndMsgT_v02)},

   //Get Protocol Config Parameters
   { QMI_LOC_GET_PROTOCOL_CONFIG_PARAMETERS_IND_V02,
     sizeof(qmiLocGetProtocolConfigParametersIndMsgT_v02)},

   //Set Sensor Control Config
   { QMI_LOC_SET_SENSOR_CONTROL_CONFIG_IND_V02,
     sizeof(qmiLocSetSensorControlConfigIndMsgT_v02)},

   //Get Sensor Control Config
   { QMI_LOC_GET_SENSOR_CONTROL_CONFIG_IND_V02,
     sizeof(qmiLocGetSensorControlConfigIndMsgT_v02)},

   //Set Sensor Properties
   { QMI_LOC_SET_SENSOR_PROPERTIES_IND_V02,
     sizeof(qmiLocSetSensorPropertiesIndMsgT_v02)},

   //Get Sensor Properties
   { QMI_LOC_GET_SENSOR_PROPERTIES_IND_V02,
     sizeof(qmiLocGetSensorPropertiesIndMsgT_v02)},

   //Set Sensor Performance Control Config
   { QMI_LOC_SET_SENSOR_PERFORMANCE_CONTROL_CONFIGURATION_IND_V02,
     sizeof(qmiLocSetSensorPerformanceControlConfigIndMsgT_v02)},

   //Get Sensor Performance Control Config
   { QMI_LOC_GET_SENSOR_PERFORMANCE_CONTROL_CONFIGURATION_IND_V02,
     sizeof(qmiLocGetSensorPerformanceControlConfigIndMsgT_v02)},
   //Inject SUPL certificate
   { QMI_LOC_INJECT_SUPL_CERTIFICATE_IND_V02,
     sizeof(qmiLocInjectSuplCertificateIndMsgT_v02) },

   //Delete SUPL certificate
   { QMI_LOC_DELETE_SUPL_CERTIFICATE_IND_V02,
     sizeof(qmiLocDeleteSuplCertificateIndMsgT_v02) },

   // Set Position Engine Config
   { QMI_LOC_SET_POSITION_ENGINE_CONFIG_PARAMETERS_IND_V02,
     sizeof(qmiLocSetPositionEngineConfigParametersIndMsgT_v02)},

   // Get Position Engine Config
   { QMI_LOC_GET_POSITION_ENGINE_CONFIG_PARAMETERS_IND_V02,
     sizeof(qmiLocGetPositionEngineConfigParametersIndMsgT_v02)},

   //Add a Circular Geofence
   { QMI_LOC_ADD_CIRCULAR_GEOFENCE_IND_V02,
     sizeof(qmiLocAddCircularGeofenceIndMsgT_v02)},

   //Delete a Geofence
   { QMI_LOC_DELETE_GEOFENCE_IND_V02,
     sizeof(qmiLocDeleteGeofenceIndMsgT_v02)} ,

   //Query a Geofence
   { QMI_LOC_QUERY_GEOFENCE_IND_V02,
     sizeof(qmiLocQueryGeofenceIndMsgT_v02)},

   //Edit a Geofence
   { QMI_LOC_EDIT_GEOFENCE_IND_V02,
     sizeof(qmiLocEditGeofenceIndMsgT_v02)},

   //Get best available position
   { QMI_LOC_GET_BEST_AVAILABLE_POSITION_IND_V02,
     sizeof(qmiLocGetBestAvailablePositionIndMsgT_v02)},

   //Secure Get available position
   { QMI_LOC_SECURE_GET_AVAILABLE_POSITION_IND_V02,
     sizeof(qmiLocSecureGetAvailablePositionIndMsgT_v02)},

   //Inject motion data
   { QMI_LOC_INJECT_MOTION_DATA_IND_V02,
     sizeof(qmiLocInjectMotionDataIndMsgT_v02)},

   //Get NI Geofence list
   { QMI_LOC_GET_NI_GEOFENCE_ID_LIST_IND_V02,
     sizeof(qmiLocGetNiGeofenceIdListIndMsgT_v02)},

   //Inject GSM Cell Info
   { QMI_LOC_INJECT_GSM_CELL_INFO_IND_V02,
     sizeof(qmiLocInjectGSMCellInfoIndMsgT_v02)},

   //Inject Network Initiated Message
   { QMI_LOC_INJECT_NETWORK_INITIATED_MESSAGE_IND_V02,
     sizeof(qmiLocInjectNetworkInitiatedMessageIndMsgT_v02)},

   //WWAN Out of Service Notification
   { QMI_LOC_WWAN_OUT_OF_SERVICE_NOTIFICATION_IND_V02,
     sizeof(qmiLocWWANOutOfServiceNotificationIndMsgT_v02)},

   //Pedomete Report
   { QMI_LOC_PEDOMETER_REPORT_IND_V02,
     sizeof(qmiLocPedometerReportIndMsgT_v02)},

   { QMI_LOC_INJECT_WCDMA_CELL_INFO_IND_V02,
     sizeof(qmiLocInjectWCDMACellInfoIndMsgT_v02)},

   { QMI_LOC_INJECT_TDSCDMA_CELL_INFO_IND_V02,
     sizeof(qmiLocInjectTDSCDMACellInfoIndMsgT_v02)},

   { QMI_LOC_INJECT_SUBSCRIBER_ID_IND_V02,
     sizeof(qmiLocInjectSubscriberIDIndMsgT_v02)},

   //Inject Wifi AP data Resp Ind
   { QMI_LOC_INJECT_WIFI_AP_DATA_IND_V02,
     sizeof(qmiLocInjectWifiApDataIndMsgT_v02)},

   { QMI_LOC_START_BATCHING_IND_V02,
     sizeof(qmiLocStartBatchingIndMsgT_v02)},

   { QMI_LOC_STOP_BATCHING_IND_V02,
     sizeof(qmiLocStopBatchingIndMsgT_v02)},

   { QMI_LOC_GET_BATCH_SIZE_IND_V02,
     sizeof(qmiLocGetBatchSizeIndMsgT_v02)},

   { QMI_LOC_EVENT_LIVE_BATCHED_POSITION_REPORT_IND_V02,
     sizeof(qmiLocEventPositionReportIndMsgT_v02)},

   { QMI_LOC_EVENT_BATCH_FULL_NOTIFICATION_IND_V02,
     sizeof(qmiLocEventBatchFullIndMsgT_v02)},

   { QMI_LOC_READ_FROM_BATCH_IND_V02,
     sizeof(qmiLocReadFromBatchIndMsgT_v02)},

   { QMI_LOC_RELEASE_BATCH_IND_V02,
     sizeof(qmiLocReleaseBatchIndMsgT_v02)},

   { QMI_LOC_SET_XTRA_VERSION_CHECK_IND_V02,
     sizeof(qmiLocSetXtraVersionCheckIndMsgT_v02)},

    //Vehicle Sensor Data
    { QMI_LOC_INJECT_VEHICLE_SENSOR_DATA_IND_V02,
      sizeof(qmiLocInjectVehicleSensorDataIndMsgT_v02)},

   { QMI_LOC_NOTIFY_WIFI_ATTACHMENT_STATUS_IND_V02,
     sizeof(qmiLocNotifyWifiAttachmentStatusIndMsgT_v02)},

   { QMI_LOC_NOTIFY_WIFI_ENABLED_STATUS_IND_V02,
     sizeof(qmiLocNotifyWifiEnabledStatusIndMsgT_v02)},

   { QMI_LOC_SET_PREMIUM_SERVICES_CONFIG_IND_V02,
     sizeof(qmiLocSetPremiumServicesCfgReqMsgT_v02)},

   { QMI_LOC_GET_AVAILABLE_WWAN_POSITION_IND_V02,
     sizeof(qmiLocGetAvailWwanPositionIndMsgT_v02)},

   // for TDP
   { QMI_LOC_INJECT_GTP_CLIENT_DOWNLOADED_DATA_IND_V02,
     sizeof(qmiLocInjectGtpClientDownloadedDataIndMsgT_v02) },

   // for GDT
   { QMI_LOC_GDT_UPLOAD_BEGIN_STATUS_IND_V02,
     sizeof(qmiLocGdtUploadBeginStatusIndMsgT_v02) },

   { QMI_LOC_GDT_UPLOAD_END_IND_V02,
     sizeof(qmiLocGdtUploadEndIndMsgT_v02) },

   { QMI_LOC_SET_GNSS_CONSTELL_REPORT_CONFIG_IND_V02,
     sizeof(qmiLocSetGNSSConstRepConfigIndMsgT_v02)},

   { QMI_LOC_START_DBT_IND_V02,
     sizeof(qmiLocStartDbtIndMsgT_v02)},

   { QMI_LOC_STOP_DBT_IND_V02,
     sizeof(qmiLocStopDbtIndMsgT_v02)},

   { QMI_LOC_INJECT_TIME_ZONE_INFO_IND_V02,
     sizeof(qmiLocInjectTimeZoneInfoIndMsgT_v02)},

   { QMI_LOC_QUERY_AON_CONFIG_IND_V02,
     sizeof(qmiLocQueryAonConfigIndMsgT_v02)}
};


/** whether indication is an event or a response */
typedef enum { eventIndType =0, respIndType = 1 } locClientIndEnumT;


/** @struct locClientInternalState
 */

typedef struct locClientCbDataStructT locClientCallbackDataType;

struct locClientCbDataStructT
{
 // client cookie
  void *pClientCookie;
  //QCCI handle for this control point
  qmi_client_type userHandle;

  // callbacks registered by the clients
  locClientEventIndCbType eventCallback;
  locClientRespIndCbType respCallback;
  locClientErrorCbType   errorCallback;

  // the event mask the client has registered for
  locClientEventMaskType eventRegMask;

  //pointer to itself for checking consistency data
   locClientCallbackDataType *pMe;
};


/*===========================================================================
 *
 *                          FUNCTION DECLARATION
 *
 *==========================================================================*/

/** locClientGetSizeAndTypeByIndId
 *  @brief this function gets the size and the type (event,
 *         response)of the indication structure from its ID
 *  @param [in]  indId  ID of the indication
 *  @param [out] type   event or response indication
 *  @param [out] size   size of the indications
 *
 *  @return true if the ID was found, false otherwise */

static bool locClientGetSizeAndTypeByIndId (uint32_t indId, size_t *pIndSize,
                                         locClientIndEnumT *pIndType)
{
  // look in the event table
  if(true == locClientGetSizeByEventIndId(indId, pIndSize))
  {
    *pIndType = eventIndType;

    LOC_LOGV("%s:%d]: indId %d is an event size = %d\n", __func__, __LINE__,
                  indId, (uint32_t)*pIndSize);
    return true;
  }

  //else look in response table
  if(true == locClientGetSizeByRespIndId(indId, pIndSize))
  {
    *pIndType = respIndType;

    LOC_LOGV("%s:%d]: indId %d is a resp size = %d\n", __func__, __LINE__,
                  indId, (uint32_t)*pIndSize);
    return true;
  }

  // Id not found
  LOC_LOGW("%s:%d]: indId %d not found\n", __func__, __LINE__, indId);
  return false;
}

/** checkQmiMsgsSupported
 @brief check the qmi service is supported or not.
 @param [in] pResponse  pointer to the response received from
        QMI_LOC service.
*/
static void checkQmiMsgsSupported(
  uint32_t*                reqIdArray,
  int                      reqIdArrayLength,
  qmiLocGetSupportMsgT_v02 *pResponse,
  uint64_t*                supportedMsg)
{
    uint64_t result = 0;
    if (pResponse->resp.supported_msgs_valid) {

        /* For example, if a service supports exactly four messages with
        IDs 0, 1, 30, and 31 (decimal), the array (in hexadecimal) is
        4 bytes [03 00 00 c0]. */

        size_t idx = 0;
        uint32_t reqId = 0;
        uint32_t length = 0;
        uint32_t supportedMsgsLen = pResponse->resp.supported_msgs_len;

        // every bit saves a checked message result
        uint32_t maxCheckedMsgsSavedNum = sizeof(result)<<3;

        uint32_t loopSize = reqIdArrayLength;
        loopSize =
            loopSize < supportedMsgsLen ? loopSize : supportedMsgsLen;
        loopSize =
            loopSize < maxCheckedMsgsSavedNum ? loopSize : maxCheckedMsgsSavedNum;

        for (idx = 0; idx < loopSize; idx++) {
            reqId = reqIdArray[idx];
            length = reqId >> 3;
            if(supportedMsgsLen > length) {
                uint32_t bit = reqId & ((uint32_t)7);
                if (pResponse->resp.supported_msgs[length] & (1<<bit)) {
                    result |= ( 1 << idx ) ;
                }
            }
        }
    } else {
        LOC_LOGE("%s:%d] Invalid supported message list.\n", __func__, __LINE__);
    }
    *supportedMsg = result;
}

/** convertQmiResponseToLocStatus
 @brief converts a qmiLocGenRespMsgT to locClientStatusEnumType*
 @param [in] pResponse; pointer to the response received from
        QMI_LOC service.
 @return locClientStatusEnumType corresponding to the
         response.
*/

static locClientStatusEnumType convertQmiResponseToLocStatus(
  qmiLocGenRespMsgT_v02 *pResponse)
{
  locClientStatusEnumType status =  eLOC_CLIENT_FAILURE_INTERNAL;

  // if result == SUCCESS don't look at error code
  if(pResponse->resp.result == QMI_RESULT_SUCCESS_V01 )
  {
    status  = eLOC_CLIENT_SUCCESS;
  }
  else
  {
    switch(pResponse->resp.error)
    {
      case QMI_ERR_MALFORMED_MSG_V01:
      case QMI_ERR_INVALID_ARG_V01:
        status = eLOC_CLIENT_FAILURE_INVALID_PARAMETER;
        break;

      case QMI_ERR_DEVICE_IN_USE_V01:
        status = eLOC_CLIENT_FAILURE_ENGINE_BUSY;
        break;

      case QMI_ERR_NOT_SUPPORTED_V01:
        status = eLOC_CLIENT_FAILURE_UNSUPPORTED;
        break;

      default:
        status = eLOC_CLIENT_FAILURE_INTERNAL;
        break;
    }
  }
  LOC_LOGV("%s:%d]: result = %d, error = %d, status = %d\n",
                __func__, __LINE__, pResponse->resp.result,
                pResponse->resp.error, status);
  return status;
}

/** convertQmiErrorToLocError
 @brief converts a qmi service error type to
        locClientErrorEnumType
 @param [in] error received QMI service.
 @return locClientErrorEnumType corresponding to the error.
*/

static locClientErrorEnumType convertQmiErrorToLocError(
  qmi_client_error_type error)
{
  locClientErrorEnumType locError ;
  switch(error)
  {
    case QMI_SERVICE_ERR:
      locError = eLOC_CLIENT_ERROR_SERVICE_UNAVAILABLE;
      break;

    default:
      locError = eLOC_CLIENT_ERROR_SERVICE_UNAVAILABLE;
      break;
  }
  LOC_LOGV("%s:%d]: qmi error = %d, loc error = %d\n",
                __func__, __LINE__, error, locError);
  return locError;
}

/** locClientErrorCb
 *  @brief handles the QCCI error events, this is called by the
 *         QCCI infrastructure when the service is no longer
 *         available.
 *  @param [in] user handle
 *  @param [in] error
 *  @param [in] *err_cb_data
 */

static void locClientErrorCb
(
  qmi_client_type user_handle,
  qmi_client_error_type error,
  void *err_cb_data
)
{
  locClientCallbackDataType* pCallbackData =
        (locClientCallbackDataType *)err_cb_data;
  locClientErrorCbType localErrorCallback = NULL;

  /* copy the errorCallback function pointer from the callback
   * data to local variable. This is to protect against the race
   * condition between open/close and error callback.
   */
  if(NULL != pCallbackData)
  {
    localErrorCallback = pCallbackData->errorCallback;
  }

  LOC_LOGD("%s:%d]: Service Error %d received, pCallbackData = %p\n",
      __func__, __LINE__, error, err_cb_data);

  /* call the error callback
   * To avoid calling the errorCallback after locClientClose
   * is called, check pCallbackData->errorCallback again here
   */

  if( (NULL != pCallbackData) &&
      (NULL != localErrorCallback) &&
      (NULL != pCallbackData->errorCallback) &&
      (pCallbackData == pCallbackData->pMe)  )
  {
    //invoke the error callback for the corresponding client
    localErrorCallback(
        (locClientHandleType)pCallbackData,
        convertQmiErrorToLocError(error),
        pCallbackData->pClientCookie);
  }
}


/** locClientIndCb
 *  @brief handles the indications sent from the service, if a
 *         response indication was received then the it is sent
 *         to the response callback. If a event indication was
 *         received then it is sent to the event callback
 *  @param [in] user handle
 *  @param [in] msg_id
 *  @param [in] ind_buf
 *  @param [in] ind_buf_len
 *  @param [in] ind_cb_data */

static void locClientIndCb
(
 qmi_client_type                user_handle,
 unsigned int                   msg_id,
 void                           *ind_buf,
 unsigned int                   ind_buf_len,
 void                           *ind_cb_data
)
{
  locClientIndEnumT indType;
  size_t indSize = 0;
  qmi_client_error_type rc ;
  locClientCallbackDataType* pCallbackData =
      (locClientCallbackDataType *)ind_cb_data;

  LOC_LOGV("%s:%d]: Indication: msg_id=%d buf_len=%d pCallbackData = %p\n",
                __func__, __LINE__, (uint32_t)msg_id, ind_buf_len,
                pCallbackData);

  // check callback data
  if(NULL == pCallbackData ||(pCallbackData != pCallbackData->pMe))
  {
    LOC_LOGE("%s:%d]: invalid callback data", __func__, __LINE__);
    return;
  }

  // check user handle
  if(memcmp(&pCallbackData->userHandle, &user_handle, sizeof(user_handle)))
  {
    LOC_LOGE("%s:%d]: invalid user_handle got %p expected %p\n",
        __func__, __LINE__,
        user_handle, pCallbackData->userHandle);
    return;
  }
  // Get the indication size and type ( eventInd or respInd)
  if( true == locClientGetSizeAndTypeByIndId(msg_id, &indSize, &indType))
  {
    void *indBuffer = NULL;

    // decode the indication
    indBuffer = malloc(indSize);

    if(NULL == indBuffer)
    {
      LOC_LOGE("%s:%d]: memory allocation failed\n", __func__, __LINE__);
      return;
    }

    rc = QMI_NO_ERR;

    if (ind_buf_len > 0)
    {
        // decode the indication
        rc = qmi_client_message_decode(
            user_handle,
            QMI_IDL_INDICATION,
            msg_id,
            ind_buf,
            ind_buf_len,
            indBuffer,
            indSize);
    }

    if( rc == QMI_NO_ERR )
    {
      if(eventIndType == indType)
      {
        locClientEventIndUnionType eventIndUnion;

        /* copy the eventCallback function pointer from the callback
         * data to local variable. This is to protect against the race
         * condition between open/close and indication callback.
         */
        locClientEventIndCbType localEventCallback =
            pCallbackData->eventCallback;

        // dummy event
        eventIndUnion.pPositionReportEvent =
            (qmiLocEventPositionReportIndMsgT_v02 *)indBuffer;

        /* call the event callback
         * To avoid calling the eventCallback after locClientClose
         * is called, check pCallbackData->eventCallback again here
         */
        if((NULL != localEventCallback) &&
           (NULL != pCallbackData->eventCallback))
        {
          localEventCallback(
              (locClientHandleType)pCallbackData,
              msg_id,
              eventIndUnion,
              pCallbackData->pClientCookie);
        }
      }
      else if(respIndType == indType)
      {
        locClientRespIndUnionType respIndUnion;

        /* copy the respCallback function pointer from the callback
         * data to local variable. This is to protect against the race
         * condition between open/close and indication callback.
         */
        locClientRespIndCbType localRespCallback =
            pCallbackData->respCallback;

        // dummy to suppress compiler warnings
        respIndUnion.pDeleteAssistDataInd =
            (qmiLocDeleteAssistDataIndMsgT_v02 *)indBuffer;

        /* call the response callback
         * To avoid calling the respCallback after locClientClose
         * is called, check pCallbackData->respCallback again here
         */
        if((NULL != localRespCallback) &&
           (NULL != pCallbackData->respCallback))
        {
          localRespCallback(
              (locClientHandleType)pCallbackData,
              msg_id,
              respIndUnion,
              pCallbackData->pClientCookie);
        }
      }
    }
    else
    {
      LOC_LOGE("%s:%d]: Error decoding indication %d\n",
                    __func__, __LINE__, rc);
    }
    if(indBuffer)
    {
      free (indBuffer);
    }
  }
  else // Id not found
  {
    LOC_LOGE("%s:%d]: Error indication not found %d\n",
                  __func__, __LINE__,(uint32_t)msg_id);
  }
  return;
}


/** locClientRegisterEventMask
 *  @brief registers the event mask with loc service
 *  @param [in] clientHandle
 *  @param [in] eventRegMask
 *  @return true if indication was validated; else false */

bool locClientRegisterEventMask(
    locClientHandleType clientHandle,
    locClientEventMaskType eventRegMask)
{
  locClientStatusEnumType status = eLOC_CLIENT_SUCCESS;
  locClientReqUnionType reqUnion;
  qmiLocRegEventsReqMsgT_v02 regEventsReq;

  memset(&regEventsReq, 0, sizeof(regEventsReq));

  regEventsReq.eventRegMask = eventRegMask;
  reqUnion.pRegEventsReq = &regEventsReq;

  status = locClientSendReq(clientHandle,
                            QMI_LOC_REG_EVENTS_REQ_V02,
                            reqUnion);

  if(eLOC_CLIENT_SUCCESS != status )
  {
    LOC_LOGE("%s:%d] status %s\n", __func__, __LINE__,
             loc_get_v02_client_status_name(status) );
    return false;
  }

  return true;
}

/**  validateRequest
  @brief validates the input request
  @param [in] reqId       request ID
  @param [in] reqPayload  Union of pointers to message payload
  @param [out] ppOutData  Pointer to void *data if successful
  @param [out] pOutLen    Pointer to length of data if succesful.
  @return false on failure, true on Success
*/

static bool validateRequest(
  uint32_t                    reqId,
  const locClientReqUnionType reqPayload,
  void                        **ppOutData,
  uint32_t                    *pOutLen )

{
  bool noPayloadFlag = false;

  LOC_LOGV("%s:%d]: reqId = %d\n", __func__, __LINE__, reqId);
  switch(reqId)
  {
    case QMI_LOC_INFORM_CLIENT_REVISION_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocInformClientRevisionReqMsgT_v02);
      break;
    }

    case QMI_LOC_REG_EVENTS_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocRegEventsReqMsgT_v02);
       break;
    }

    case QMI_LOC_START_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocStartReqMsgT_v02);
       break;
    }

    case QMI_LOC_STOP_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocStopReqMsgT_v02);
       break;
    }

    case QMI_LOC_NI_USER_RESPONSE_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocNiUserRespReqMsgT_v02);
       break;
    }

    case QMI_LOC_INJECT_PREDICTED_ORBITS_DATA_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocInjectPredictedOrbitsDataReqMsgT_v02);
      break;
    }

    case QMI_LOC_INJECT_UTC_TIME_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocInjectUtcTimeReqMsgT_v02);
      break;
    }

    case QMI_LOC_INJECT_POSITION_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocInjectPositionReqMsgT_v02);
      break;
    }

    case QMI_LOC_SET_ENGINE_LOCK_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocSetEngineLockReqMsgT_v02);
      break;
    }

    case QMI_LOC_SET_SBAS_CONFIG_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocSetSbasConfigReqMsgT_v02);
      break;
    }

    case QMI_LOC_SET_NMEA_TYPES_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocSetNmeaTypesReqMsgT_v02);
      break;
    }

    case QMI_LOC_SET_LOW_POWER_MODE_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocSetLowPowerModeReqMsgT_v02);
      break;
    }

    case QMI_LOC_SET_SERVER_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocSetServerReqMsgT_v02);
      break;
    }

    case QMI_LOC_DELETE_ASSIST_DATA_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocDeleteAssistDataReqMsgT_v02);
      break;
    }

    case QMI_LOC_INJECT_APCACHE_DATA_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocInjectApCacheDataReqMsgT_v02);
      break;
    }

    case QMI_LOC_INJECT_APDONOTCACHE_DATA_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocInjectApDoNotCacheDataReqMsgT_v02);
      break;
    }

    case QMI_LOC_SET_XTRA_T_SESSION_CONTROL_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocSetXtraTSessionControlReqMsgT_v02);
      break;
    }

    case QMI_LOC_INJECT_WIFI_POSITION_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocInjectWifiPositionReqMsgT_v02);
      break;
    }

    case QMI_LOC_NOTIFY_WIFI_STATUS_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocNotifyWifiStatusReqMsgT_v02);
      break;
    }

    case QMI_LOC_SET_OPERATION_MODE_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocSetOperationModeReqMsgT_v02);
      break;
    }

    case QMI_LOC_SET_SPI_STATUS_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocSetSpiStatusReqMsgT_v02);
      break;
    }

    case QMI_LOC_INJECT_SENSOR_DATA_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocInjectSensorDataReqMsgT_v02);
      break;
    }

    case QMI_LOC_INJECT_TIME_SYNC_DATA_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocInjectTimeSyncDataReqMsgT_v02);
      break;
    }

    case QMI_LOC_SET_CRADLE_MOUNT_CONFIG_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocSetCradleMountConfigReqMsgT_v02);
      break;
    }

    case QMI_LOC_SET_EXTERNAL_POWER_CONFIG_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocSetExternalPowerConfigReqMsgT_v02);
      break;
    }

    case QMI_LOC_INFORM_LOCATION_SERVER_CONN_STATUS_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocInformLocationServerConnStatusReqMsgT_v02);
      break;
    }

    case QMI_LOC_SET_PROTOCOL_CONFIG_PARAMETERS_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocSetProtocolConfigParametersReqMsgT_v02);
      break;
    }

    case QMI_LOC_GET_PROTOCOL_CONFIG_PARAMETERS_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocGetProtocolConfigParametersReqMsgT_v02);
      break;
    }

    case QMI_LOC_SET_SENSOR_CONTROL_CONFIG_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocSetSensorControlConfigReqMsgT_v02);
      break;
    }

    case QMI_LOC_GET_SENSOR_PROPERTIES_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocGetSensorPropertiesReqMsgT_v02);
      break;
    }

    case QMI_LOC_SET_SENSOR_PROPERTIES_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocSetSensorPropertiesReqMsgT_v02);
      break;
    }

    case QMI_LOC_SET_SENSOR_PERFORMANCE_CONTROL_CONFIGURATION_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocSetSensorPerformanceControlConfigReqMsgT_v02);
      break;
    }

    case QMI_LOC_INJECT_SUPL_CERTIFICATE_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocInjectSuplCertificateReqMsgT_v02);
      break;
    }
    case QMI_LOC_DELETE_SUPL_CERTIFICATE_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocDeleteSuplCertificateReqMsgT_v02);
      break;
    }
    case QMI_LOC_SET_POSITION_ENGINE_CONFIG_PARAMETERS_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocSetPositionEngineConfigParametersReqMsgT_v02);
      break;
    }
    case QMI_LOC_GET_POSITION_ENGINE_CONFIG_PARAMETERS_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocGetPositionEngineConfigParametersReqMsgT_v02);
      break;
    }
    case QMI_LOC_ADD_CIRCULAR_GEOFENCE_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocAddCircularGeofenceReqMsgT_v02);
      break;
    }
    case QMI_LOC_DELETE_GEOFENCE_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocDeleteGeofenceReqMsgT_v02);
      break;
    }
    case QMI_LOC_QUERY_GEOFENCE_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocQueryGeofenceReqMsgT_v02);
      break;
    }
    case QMI_LOC_EDIT_GEOFENCE_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocEditGeofenceReqMsgT_v02);
      break;
    }
    case QMI_LOC_GET_BEST_AVAILABLE_POSITION_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocGetBestAvailablePositionReqMsgT_v02);
      break;
    }

    case QMI_LOC_SECURE_GET_AVAILABLE_POSITION_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocSecureGetAvailablePositionReqMsgT_v02);
      break;
    }

    case QMI_LOC_INJECT_MOTION_DATA_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocInjectMotionDataReqMsgT_v02);
      break;
    }

    case QMI_LOC_GET_NI_GEOFENCE_ID_LIST_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocGetNiGeofenceIdListReqMsgT_v02);
      break;
    }

    case QMI_LOC_INJECT_GSM_CELL_INFO_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocInjectGSMCellInfoReqMsgT_v02);
      break;
    }

    case QMI_LOC_INJECT_NETWORK_INITIATED_MESSAGE_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocInjectNetworkInitiatedMessageReqMsgT_v02);
      break;
    }

    case QMI_LOC_PEDOMETER_REPORT_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocPedometerReportReqMsgT_v02);
      break;
    }

    case QMI_LOC_INJECT_WCDMA_CELL_INFO_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocInjectWCDMACellInfoReqMsgT_v02);
      break;
    }

    case QMI_LOC_INJECT_TDSCDMA_CELL_INFO_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocInjectTDSCDMACellInfoReqMsgT_v02);
      break;
    }

    case QMI_LOC_INJECT_SUBSCRIBER_ID_IND_V02:
    {
      *pOutLen = sizeof(qmiLocInjectSubscriberIDReqMsgT_v02);
      break;
    }

    case QMI_LOC_INJECT_WIFI_AP_DATA_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocInjectWifiApDataReqMsgT_v02);
      break;
    }

    case QMI_LOC_GET_BATCH_SIZE_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocGetBatchSizeReqMsgT_v02);
      break;
    }

    case QMI_LOC_START_BATCHING_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocStartBatchingReqMsgT_v02);
      break;
    }

    case QMI_LOC_READ_FROM_BATCH_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocReadFromBatchReqMsgT_v02);
      break;
    }

    case QMI_LOC_STOP_BATCHING_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocStopBatchingReqMsgT_v02);
      break;
    }

    case QMI_LOC_RELEASE_BATCH_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocReleaseBatchReqMsgT_v02);
      break;
    }

    case QMI_LOC_SET_XTRA_VERSION_CHECK_REQ_V02:
    {
        *pOutLen = sizeof(qmiLocSetXtraVersionCheckReqMsgT_v02);
        break;
    }

    case QMI_LOC_INJECT_VEHICLE_SENSOR_DATA_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocInjectVehicleSensorDataReqMsgT_v02);
      break;
    }

    case QMI_LOC_NOTIFY_WIFI_ATTACHMENT_STATUS_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocNotifyWifiAttachmentStatusReqMsgT_v02);
      break;
    }

    case QMI_LOC_NOTIFY_WIFI_ENABLED_STATUS_REQ_V02:
    {
      *pOutLen = sizeof(qmiLocNotifyWifiEnabledStatusReqMsgT_v02);
      break;
    }

    case QMI_LOC_SET_PREMIUM_SERVICES_CONFIG_REQ_V02:
    {
        *pOutLen = sizeof(qmiLocSetPremiumServicesCfgReqMsgT_v02);
        break;
    }

    case QMI_LOC_GET_AVAILABLE_WWAN_POSITION_REQ_V02:
    {
        *pOutLen = sizeof(qmiLocGetAvailWwanPositionReqMsgT_v02);
        break;
    }

    case QMI_LOC_INJECT_GTP_CLIENT_DOWNLOADED_DATA_REQ_V02:
    {
        *pOutLen = sizeof(qmiLocInjectGtpClientDownloadedDataReqMsgT_v02);
        break;
    }

    case QMI_LOC_GDT_UPLOAD_BEGIN_STATUS_REQ_V02:
    {
        *pOutLen = sizeof(qmiLocGdtUploadBeginStatusReqMsgT_v02);
        break;
    }

    case QMI_LOC_GDT_UPLOAD_END_REQ_V02:
    {
        *pOutLen = sizeof(qmiLocGdtUploadEndReqMsgT_v02);
        break;
    }

    case QMI_LOC_SET_GNSS_CONSTELL_REPORT_CONFIG_V02:
    {
        *pOutLen = sizeof(qmiLocSetGNSSConstRepConfigReqMsgT_v02);
        break;
    }

    case QMI_LOC_START_DBT_REQ_V02:
    {
        *pOutLen = sizeof(qmiLocStartDbtReqMsgT_v02);
        break;
    }

    case QMI_LOC_STOP_DBT_REQ_V02:
    {
        *pOutLen = sizeof(qmiLocStopDbtReqMsgT_v02);
        break;
    }

    case QMI_LOC_INJECT_TIME_ZONE_INFO_REQ_V02:
    {
        *pOutLen = sizeof(qmiLocInjectTimeZoneInfoReqMsgT_v02);
        break;
    }

    case QMI_LOC_QUERY_AON_CONFIG_REQ_V02:
    {
        *pOutLen = sizeof(qmiLocQueryAonConfigReqMsgT_v02);
        break;
    }

    // ALL requests with no payload
    case QMI_LOC_GET_SERVICE_REVISION_REQ_V02:
    case QMI_LOC_GET_FIX_CRITERIA_REQ_V02:
    case QMI_LOC_GET_PREDICTED_ORBITS_DATA_SOURCE_REQ_V02:
    case QMI_LOC_GET_PREDICTED_ORBITS_DATA_VALIDITY_REQ_V02:
    case QMI_LOC_GET_ENGINE_LOCK_REQ_V02:
    case QMI_LOC_GET_SBAS_CONFIG_REQ_V02:
    case QMI_LOC_GET_NMEA_TYPES_REQ_V02:
    case QMI_LOC_GET_LOW_POWER_MODE_REQ_V02:
    case QMI_LOC_GET_SERVER_REQ_V02:
    case QMI_LOC_GET_XTRA_T_SESSION_CONTROL_REQ_V02:
    case QMI_LOC_GET_REGISTERED_EVENTS_REQ_V02:
    case QMI_LOC_GET_OPERATION_MODE_REQ_V02:
    case QMI_LOC_GET_CRADLE_MOUNT_CONFIG_REQ_V02:
    case QMI_LOC_GET_EXTERNAL_POWER_CONFIG_REQ_V02:
    case QMI_LOC_GET_SENSOR_CONTROL_CONFIG_REQ_V02:
    case QMI_LOC_GET_SENSOR_PERFORMANCE_CONTROL_CONFIGURATION_REQ_V02:
    case QMI_LOC_WWAN_OUT_OF_SERVICE_NOTIFICATION_REQ_V02:
    case QMI_LOC_GET_SUPPORTED_MSGS_REQ_V02:
    case QMI_LOC_GET_SUPPORTED_FIELDS_REQ_V02:
    {
      noPayloadFlag = true;
      break;
    }

    default:
      LOC_LOGW("%s:%d]: Error unknown reqId=%d\n", __func__, __LINE__,
                    reqId);
      return false;
  }
  if(true == noPayloadFlag)
  {
    *ppOutData = NULL;
    *pOutLen = 0;
  }
  else
  {
    //set dummy pointer for request union
    *ppOutData = (void*) reqPayload.pInformClientRevisionReq;
  }
  LOC_LOGV("%s:%d]: reqId=%d, len = %d\n", __func__, __LINE__,
                reqId, *pOutLen);
  return true;
}

/** locClientQmiCtrlPointInit
 @brief wait for the service to come up or timeout; when the
        service comes up initialize the control point and set
        internal handle and indication callback.
 @param pQmiClient,
*/

static locClientStatusEnumType locClientQmiCtrlPointInit(
    locClientCallbackDataType *pLocClientCbData,
    int instanceId)
{
  qmi_client_type clnt, notifier;
  bool notifierInitFlag = false;
  locClientStatusEnumType status = eLOC_CLIENT_SUCCESS;
  // os_params must stay in the same scope as notifier
  // because when notifier is initialized, the pointer
  // of os_params is retained in QMI framework, and it
  // used when notifier is released.
  qmi_client_os_params os_params;
  // instances of this service
  qmi_service_info serviceInfo;

  do
  {
    qmi_client_error_type rc = QMI_NO_ERR;

    // Get the service object for the qmiLoc Service
    qmi_idl_service_object_type locClientServiceObject =
      loc_get_service_object_v02();

    // Verify that qmiLoc_get_service_object did not return NULL
    if (NULL == locClientServiceObject)
    {
        LOC_LOGE("%s:%d]: qmiLoc_get_service_object_v02 failed\n" ,
                    __func__, __LINE__ );
       status = eLOC_CLIENT_FAILURE_INTERNAL;
       break;
    }

    // register for service notification
    rc = qmi_client_notifier_init(locClientServiceObject, &os_params, &notifier);
    notifierInitFlag = (NULL != notifier);

    if (rc != QMI_NO_ERR) {
        LOC_LOGE("%s:%d]: qmi_client_notifier_init failed %d\n",
                 __func__, __LINE__, rc);
        status = eLOC_CLIENT_FAILURE_INTERNAL;
        break;
    }

    while (1) {
        QMI_CCI_OS_SIGNAL_CLEAR(&os_params);

        if (instanceId >= 0) {
            // use instance-specific lookup
            rc = qmi_client_get_service_instance(locClientServiceObject, instanceId, &serviceInfo);
        } else {
            // lookup service with any instance id
            rc = qmi_client_get_any_service(locClientServiceObject, &serviceInfo);
        }

        // get the service addressing information
        LOC_LOGV("%s:%d]: qmi_client_get_service() rc: %d ", __func__, __LINE__, rc);

        if(rc == QMI_NO_ERR)
            break;

        QMI_CCI_OS_SIGNAL_WAIT(&os_params, 0);
    }

    LOC_LOGV("%s:%d]: passing the pointer %p to qmi_client_init \n",
                      __func__, __LINE__, pLocClientCbData);

    // initialize the client
    //sent the address of the first service found
    // if IPC router is present, this will go to the service instance
    // enumerated over IPC router, else it will go over the next transport where
    // the service was enumerated.
    rc = qmi_client_init(&serviceInfo, locClientServiceObject,
                         locClientIndCb, (void *) pLocClientCbData,
                         NULL, &clnt);

    if(rc != QMI_NO_ERR)
    {
      LOC_LOGE("%s:%d]: qmi_client_init error %d\n",
                    __func__, __LINE__, rc);

      status = eLOC_CLIENT_FAILURE_INTERNAL;
      break;
    }

    LOC_LOGV("%s:%d]: passing the pointer %p to"
                  "qmi_client_register_error_cb \n",
                   __func__, __LINE__, pLocClientCbData);

    // register error callback
    rc  = qmi_client_register_error_cb(clnt,
        locClientErrorCb, (void *) pLocClientCbData);

    if( QMI_NO_ERR != rc)
    {
      LOC_LOGE("%s:%d]: could not register QCCI error callback error:%d\n",
                    __func__, __LINE__, rc);

      status = eLOC_CLIENT_FAILURE_INTERNAL;
      break;
    }

    // copy the clnt handle returned in qmi_client_init
    memcpy(&(pLocClientCbData->userHandle), &clnt, sizeof(qmi_client_type));

    status = eLOC_CLIENT_SUCCESS;

  } while(0);

  /* release the notifier handle */
  if(true == notifierInitFlag)
  {
    qmi_client_release(notifier);
  }

  return status;
}
//----------------------- END INTERNAL FUNCTIONS ----------------------------------------

/** locClientOpenInstance
  @brief Connects a location client to the location engine. If the connection
         is successful, returns a handle that the location client uses for
         future location operations.

  @param [in] eventRegMask     Mask of asynchronous events the client is
                               interested in receiving
  @param [in] instanceId       Value of QMI service instance id to use.
  @param [in] eventIndCb       Function to be invoked to handle an event.
  @param [in] respIndCb        Function to be invoked to handle a response
                               indication.
  @param [out] locClientHandle Handle to be used by the client
                               for any subsequent requests.

  @return
  One of the following error codes:
  - eLOC_CLIENT_SUCCESS  -- If the connection is opened.
  - non-zero error code(see locClientStatusEnumType)--  On failure.
*/
locClientStatusEnumType locClientOpenInstance (
  locClientEventMaskType         eventRegMask,
  int                            instanceId,
  const locClientCallbacksType*  pLocClientCallbacks,
  locClientHandleType*           pLocClientHandle,
  const void*                    pClientCookie)
{
  locClientStatusEnumType status = eLOC_CLIENT_SUCCESS;
  locClientCallbackDataType *pCallbackData = NULL;

  // check input parameters
  if( (NULL == pLocClientCallbacks) || (NULL == pLocClientHandle)
      || (NULL == pLocClientCallbacks->respIndCb) ||
      (pLocClientCallbacks->size != sizeof(locClientCallbacksType)))
  {
    LOC_LOGE("%s:%d]: Invalid parameters in locClientOpen\n",
             __func__, __LINE__);
    return eLOC_CLIENT_FAILURE_INVALID_PARAMETER;
  }

  do
  {
    // Allocate memory for the callback data
    pCallbackData =
        ( locClientCallbackDataType*)calloc(
            1, sizeof(locClientCallbackDataType));

    if(NULL == pCallbackData)
    {
      LOC_LOGE("%s:%d]: Could not allocate memory for callback data \n",
                        __func__, __LINE__);
      status = eLOC_CLIENT_FAILURE_INTERNAL;
      break;
    }

    /* Initialize the QMI control point; this function will block
     * until a service is up or a timeout occurs. If the connection to
     * the service succeeds the callback data will be filled in with
     * a qmi_client value.
     */


    EXIT_LOG_CALLFLOW(%s, "loc client open");
    status = locClientQmiCtrlPointInit(pCallbackData, instanceId);

    LOC_LOGV ("%s:%d] locClientQmiCtrlPointInit returned %d\n",
                    __func__, __LINE__, status);

    if(status != eLOC_CLIENT_SUCCESS)
    {
      free(pCallbackData);
      pCallbackData = NULL;
      LOC_LOGE ("%s:%d] locClientQmiCtrlPointInit returned %d\n",
                    __func__, __LINE__, status);
      break;
    }
     // set the self pointer
    pCallbackData->pMe = pCallbackData;
     // set the handle to the callback data
    *pLocClientHandle = (locClientHandleType)pCallbackData;

    if(true != locClientRegisterEventMask(*pLocClientHandle,eventRegMask))
    {
      LOC_LOGE("%s:%d]: Error sending registration mask\n",
                  __func__, __LINE__);

      // release the client
      locClientClose(pLocClientHandle);

      status = eLOC_CLIENT_FAILURE_INTERNAL;
      break;
    }

    /* Initialize rest of the client structure now that the connection
     * to the service has been created successfully.
     */

    //fill in the event callback
     pCallbackData->eventCallback = pLocClientCallbacks->eventIndCb;

     //fill in the response callback
     pCallbackData->respCallback = pLocClientCallbacks->respIndCb;

     //fill in the error callback
     pCallbackData->errorCallback = pLocClientCallbacks->errorCb;

     //set the client event registration mask
     pCallbackData->eventRegMask = eventRegMask;

     // set the client cookie
     pCallbackData->pClientCookie = (void *)pClientCookie;

  }while(0);

  if(eLOC_CLIENT_SUCCESS != status)
  {
    *pLocClientHandle = LOC_CLIENT_INVALID_HANDLE_VALUE;
    LOC_LOGE("%s:%d]: Error! status = %d\n", __func__, __LINE__,status);
  }

  else
  {
    LOC_LOGD("%s:%d]: returning handle = %p, user_handle=%p, status = %d\n",
                __func__, __LINE__, *pLocClientHandle,
                pCallbackData->userHandle, status);
  }

  return(status);
}

/** locClientOpen
  @brief Connects a location client to the location engine. If the connection
         is successful, returns a handle that the location client uses for
         future location operations.

  @param [in] eventRegMask     Mask of asynchronous events the client is
                               interested in receiving
  @param [in] eventIndCb       Function to be invoked to handle an event.
  @param [in] respIndCb        Function to be invoked to handle a response
                               indication.
  @param [out] locClientHandle Handle to be used by the client
                               for any subsequent requests.

  @return
  One of the following error codes:
  - eLOC_CLIENT_SUCCESS  -- If the connection is opened.
  - non-zero error code(see locClientStatusEnumType)--  On failure.
*/

locClientStatusEnumType locClientOpen (
  locClientEventMaskType         eventRegMask,
  const locClientCallbacksType*  pLocClientCallbacks,
  locClientHandleType*           pLocClientHandle,
  const void*                    pClientCookie)
{
  int instanceId;
  locClientStatusEnumType status;
  int tries = 1;
#ifdef _ANDROID_
  switch (getTargetGnssType(loc_get_target()))
  {
  case GNSS_GSS:
    instanceId = eLOC_CLIENT_INSTANCE_ID_GSS;
    break;
  case GNSS_QCA1530:
    instanceId = eLOC_CLIENT_INSTANCE_ID_QCA1530;
    break;
  case GNSS_MSM:
    instanceId = eLOC_CLIENT_INSTANCE_ID_MSM;
    break;
  case GNSS_MDM:
    instanceId = eLOC_CLIENT_INSTANCE_ID_MDM;
    break;
  case GNSS_AUTO:
    instanceId = eLOC_CLIENT_INSTANCE_ID_GSS_AUTO;
    break;
  default:
    instanceId = eLOC_CLIENT_INSTANCE_ID_ANY;
    break;
  }

  LOC_LOGI("%s:%d]: Service instance id is %d\n",
             __func__, __LINE__, instanceId);
#else
  instanceId = eLOC_CLIENT_INSTANCE_ID_ANY;
#endif

  while ((status = locClientOpenInstance(eventRegMask, instanceId, pLocClientCallbacks,
          pLocClientHandle, pClientCookie)) != eLOC_CLIENT_SUCCESS) {
    if (tries <= LOC_CLIENT_MAX_OPEN_RETRIES) {
      LOC_LOGE("%s:%d]: failed with status=%d on try %d",
               __func__, __LINE__, status, tries);
      tries++;
      sleep(LOC_CLIENT_TIME_BETWEEN_OPEN_RETRIES);
    } else {
      LOC_LOGE("%s:%d]: failed with status=%d Aborting...",
               __func__, __LINE__, status);
      break;
    }
  }

  return status;
}

/** locClientClose
  @brief Disconnects a client from the location engine.
  @param [in] pLocClientHandle  Pointer to the handle returned by the
                                locClientOpen() function.
  @return
  One of the following error codes:
  - 0 (eLOC_CLIENT_SUCCESS) - On success.
  - non-zero error code(see locClientStatusEnumType) - On failure.
*/

locClientStatusEnumType locClientClose(
  locClientHandleType* pLocClientHandle)
{
  // convert handle to callback data
  locClientCallbackDataType *pCallbackData;
  qmi_client_error_type rc = QMI_NO_ERR; //No error

  if(NULL == pLocClientHandle)
  {
    // invalid handle
    LOC_LOGE("%s:%d]: invalid pointer to handle \n",
                  __func__, __LINE__);

    return(eLOC_CLIENT_FAILURE_INVALID_PARAMETER);
  }

  pCallbackData = (locClientCallbackDataType *)(*pLocClientHandle);

  // check the input handle for sanity
  if(NULL == pCallbackData ||
     NULL == pCallbackData->userHandle ||
     pCallbackData != pCallbackData->pMe )
  {
    // invalid handle
    LOC_LOGE("%s:%d]: invalid handle \n",
                  __func__, __LINE__);

    return(eLOC_CLIENT_FAILURE_INVALID_HANDLE);
  }

  LOC_LOGV("locClientClose releasing handle %p, user handle %p\n",
      *pLocClientHandle, pCallbackData->userHandle );

  // NEXT call goes out to modem. We log the callflow before it
  // actually happens to ensure the this comes before resp callflow
  // back from the modem, to avoid confusing log order. We trust
  // that the QMI framework is robust.
  EXIT_LOG_CALLFLOW(%s, "loc client close");

  // release the handle
  rc = qmi_client_release(pCallbackData->userHandle);
  if(QMI_NO_ERR != rc )
  {
    LOC_LOGW("%s:%d]: qmi_client_release error %d for client %p\n",
                   __func__, __LINE__, rc, pCallbackData->userHandle);
    return(eLOC_CLIENT_FAILURE_INTERNAL);
  }

  /* clear the memory allocated to callback data to minimize the chances
   *  of a race condition occurring between close and the indication
   *  callback
   */
  memset(pCallbackData, 0, sizeof(*pCallbackData));

  // free the memory assigned in locClientOpen
  free(pCallbackData);
  pCallbackData= NULL;

  // set the handle to invalid value
  *pLocClientHandle = LOC_CLIENT_INVALID_HANDLE_VALUE;
  return eLOC_CLIENT_SUCCESS;
}

/** locClientSendReq
  @brief Sends a message to the location engine. If the locClientSendMsg()
         function is successful, the client should expect an indication
         (except start, stop, event reg and sensor injection messages),
         through the registered callback in the locOpen() function. The
         indication will contain the status of the request and if status is a
         success, indication also contains the payload
         associated with response.
  @param [in] handle Handle returned by the locClientOpen()
              function.
  @param [in] reqId         message ID of the request
  @param [in] reqPayload   Payload of the request, can be NULL
                            if request has no payload

  @return
  One of the following error codes:
  - 0 (eLOC_CLIENT_SUCCESS ) - On success.
  - non-zero error code (see locClientStatusEnumType) - On failure.
*/

locClientStatusEnumType locClientSendReq(
  locClientHandleType      handle,
  uint32_t                 reqId,
  locClientReqUnionType    reqPayload )
{
  locClientStatusEnumType status = eLOC_CLIENT_SUCCESS;
  qmi_client_error_type rc = QMI_NO_ERR; //No error
  qmiLocGenRespMsgT_v02 resp;
  uint32_t reqLen = 0;
  void *pReqData = NULL;
  locClientCallbackDataType *pCallbackData =
        (locClientCallbackDataType *)handle;

  // check the input handle for sanity
   if(NULL == pCallbackData ||
      NULL == pCallbackData->userHandle ||
      pCallbackData != pCallbackData->pMe )
   {
     // did not find the handle in the client List
     LOC_LOGE("%s:%d]: invalid handle \n",
                   __func__, __LINE__);

     return(eLOC_CLIENT_FAILURE_INVALID_HANDLE);
   }

  // validate that the request is correct
  if (validateRequest(reqId, reqPayload, &pReqData, &reqLen) == false)
  {

    LOC_LOGE("%s:%d] error invalid request\n", __func__,
                __LINE__);

    return(eLOC_CLIENT_FAILURE_INVALID_PARAMETER);
  }

  LOC_LOGV("%s:%d] sending reqId= %d, len = %d\n", __func__,
                __LINE__, reqId, reqLen);

  // NEXT call goes out to modem. We log the callflow before it
  // actually happens to ensure the this comes before resp callflow
  // back from the modem, to avoid confusing log order. We trust
  // that the QMI framework is robust.
  EXIT_LOG_CALLFLOW(%s, loc_get_v02_event_name(reqId));
  rc = qmi_client_send_msg_sync(
      pCallbackData->userHandle,
      reqId,
      pReqData,
      reqLen,
      &resp,
      sizeof(resp),
      LOC_CLIENT_ACK_TIMEOUT);

  LOC_LOGV("%s:%d] qmi_client_send_msg_sync returned %d\n", __func__,
                __LINE__, rc);

  if (QMI_SERVICE_ERR == rc)
  {
    LOC_LOGE("%s:%d]: send_msg_sync error: QMI_SERVICE_ERR\n",__func__, __LINE__);
    return(eLOC_CLIENT_FAILURE_PHONE_OFFLINE);
  }
  else if (rc != QMI_NO_ERR)
  {
    LOC_LOGE("%s:%d]: send_msg_sync error: %d\n",__func__, __LINE__, rc);
    return(eLOC_CLIENT_FAILURE_INTERNAL);
  }

  // map the QCCI response to Loc API v02 status
  status = convertQmiResponseToLocStatus(&resp);

  // if the request is to change registered events, update the
  // loc api copy of that
  if(eLOC_CLIENT_SUCCESS == status &&
      QMI_LOC_REG_EVENTS_REQ_V02 == reqId)
  {
    if(NULL != reqPayload.pRegEventsReq )
    {
      pCallbackData->eventRegMask =
        (locClientEventMaskType)(reqPayload.pRegEventsReq->eventRegMask);
    }
  }
  return(status);
}

/** locClientSupportMsgCheck
  @brief Sends a QMI_LOC_GET_SUPPORTED_MSGS_REQ_V02 message to the
         location engine, and then receives a list of all services supported
         by the engine. This function will check if the input service(s) form
         the client is in the list or not. If the locClientSupportMsgCheck()
         function is successful, the client should expect an result of
         the service is supported or not recorded in supportedMsg.
  @param [in] handle Handle returned by the locClientOpen()
              function.
  @param [in] supportedMsg   an integer used to record which
                             message is supported

  @return
  One of the following error codes:
  - 0 (eLOC_CLIENT_SUCCESS) -- On success.
  - Non-zero error code (see \ref locClientStatusEnumType) -- On failure.
*/

locClientStatusEnumType locClientSupportMsgCheck(
     locClientHandleType      handle,
     const uint32_t*          msgArray,
     uint32_t                 msgArrayLength,
     uint64_t*                supportedMsg)
{

  // set to true if one client has checked the modem capability.
  static bool isCheckedAlready = false;
  /*
  The 1st bit in supportedMsgChecked indicates if
      QMI_LOC_EVENT_GEOFENCE_BATCHED_BREACH_NOTIFICATION_IND_V02
      is supported or not;
  The 2ed bit in supportedMsgChecked indicates if
      QMI_LOC_GET_BATCH_SIZE_REQ_V02
      is supported or not;
  */
  static uint64_t supportedMsgChecked = 0;

  if (isCheckedAlready) {
    // already checked modem
    LOC_LOGV("%s:%d]: Already checked. The supportedMsgChecked is %lld\n",
             __func__, __LINE__, supportedMsgChecked);
    *supportedMsg = supportedMsgChecked;
    return eLOC_CLIENT_SUCCESS;
  }

  locClientStatusEnumType status = eLOC_CLIENT_SUCCESS;
  qmi_client_error_type rc = QMI_NO_ERR; //No error
  qmiLocGetSupportMsgT_v02 resp;

  uint32_t reqLen = 0;
  void *pReqData = NULL;
  locClientCallbackDataType *pCallbackData =
        (locClientCallbackDataType *)handle;

  // check the input handle for sanity
   if( NULL == pCallbackData ||
       NULL == pCallbackData->userHandle ||
       pCallbackData != pCallbackData->pMe ) {
     // did not find the handle in the client List
     LOC_LOGE("%s:%d]: invalid handle \n",
                   __func__, __LINE__);

     return eLOC_CLIENT_FAILURE_GENERAL;
   }

  // NEXT call goes out to modem. We log the callflow before it
  // actually happens to ensure the this comes before resp callflow
  // back from the modem, to avoid confusing log order. We trust
  // that the QMI framework is robust.

  EXIT_LOG_CALLFLOW(%s, loc_get_v02_event_name(QMI_LOC_GET_SUPPORTED_MSGS_REQ_V02));
  rc = qmi_client_send_msg_sync(
      pCallbackData->userHandle,
      QMI_LOC_GET_SUPPORTED_MSGS_REQ_V02,
      pReqData,
      reqLen,
      &resp,
      sizeof(resp),
      LOC_CLIENT_ACK_TIMEOUT);

  LOC_LOGV("%s:%d] qmi_client_send_msg_sync returned %d\n", __func__,
                __LINE__, rc);

  if (rc != QMI_NO_ERR)
  {
    LOC_LOGE("%s:%d]: send_msg_sync error: %d\n",__func__, __LINE__, rc);
    return eLOC_CLIENT_FAILURE_GENERAL;
  }

  // map the QCCI response to Loc API v02 status
  status = convertQmiResponseToLocStatus(&resp);

  if(eLOC_CLIENT_SUCCESS == status)
  {
    LOC_LOGV("%s:%d]eLOC_CLIENT_SUCCESS == status\n", __func__, __LINE__);

    // check every message listed in msgArray supported by modem or not
    checkQmiMsgsSupported(msgArray, msgArrayLength, &resp, &supportedMsgChecked);

    LOC_LOGV("%s:%d]: supportedMsgChecked is %lld\n",
             __func__, __LINE__, supportedMsgChecked);
    *supportedMsg = supportedMsgChecked;
    isCheckedAlready = true;
    return status;
  } else {

    LOC_LOGE("%s:%d]: convertQmiResponseToLocStatus error: %d\n",
            __func__, __LINE__, status);
    return eLOC_CLIENT_FAILURE_GENERAL;
  }
}

/** locClientGetSizeByRespIndId
 *  @brief Get the size of the response indication structure,
 *         from a specified id
 *  @param [in]  respIndId
 *  @param [out] pRespIndSize
 *  @return true if resp ID was found; else false
*/

bool locClientGetSizeByRespIndId(uint32_t respIndId, size_t *pRespIndSize)
{
  size_t idx = 0, respIndTableSize = 0;
  respIndTableSize = (sizeof(locClientRespIndTable)/sizeof(locClientRespIndTableStructT));
  for(idx=0; idx<respIndTableSize; idx++ )
  {
    if(respIndId == locClientRespIndTable[idx].respIndId)
    {
      // found
      *pRespIndSize = locClientRespIndTable[idx].respIndSize;

      LOC_LOGV("%s:%d]: resp ind Id %d size = %d\n", __func__, __LINE__,
                    respIndId, (uint32_t)*pRespIndSize);
      return true;
    }
  }

  //not found
  return false;
}


/** locClientGetSizeByEventIndId
 *  @brief Gets the size of the event indication structure, from
 *         a specified id
 *  @param [in]  eventIndId
 *  @param [out] pEventIndSize
 *  @return true if event ID was found; else false
*/
bool locClientGetSizeByEventIndId(uint32_t eventIndId, size_t *pEventIndSize)
{
  size_t idx = 0, eventIndTableSize = 0;

  // look in the event table
  eventIndTableSize =
    (sizeof(locClientEventIndTable)/sizeof(locClientEventIndTableStructT));

  for(idx=0; idx<eventIndTableSize; idx++ )
  {
    if(eventIndId == locClientEventIndTable[idx].eventId)
    {
      // found
      *pEventIndSize = locClientEventIndTable[idx].eventSize;

      LOC_LOGV("%s:%d]: event ind Id %d size = %d\n", __func__, __LINE__,
                    eventIndId, (uint32_t)*pEventIndSize);
      return true;
    }
  }
  // not found
  return false;
}
