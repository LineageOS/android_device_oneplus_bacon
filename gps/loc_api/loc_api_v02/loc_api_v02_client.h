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

/** @file loc_api_v02_client.h
*/

#ifndef LOC_API_V02_CLIENT_H
#define LOC_API_V02_CLIENT_H


#ifdef __cplusplus
extern "C" {
#endif


/*=============================================================================
 *
 *                             DATA DECLARATION
 *
 *============================================================================*/
#include <stdbool.h>
#include <stdint.h>

#include "location_service_v02.h"  //QMI LOC Service data types definitions

#include <stddef.h>

/******************************************************************************
 *  Constants and configuration
 *****************************************************************************/

/** @ingroup constants_macros
  Specific value of #locClientHandleType, indicating an invalid handle. */
#define LOC_CLIENT_INVALID_HANDLE_VALUE (NULL)


/** @addtogroup data_types
@{ */

/** Location client handle used to represent a specific client. Negative values
    are invalid handles.
*/
typedef void* locClientHandleType;

/** Data type for events and event masks. */
typedef uint64_t locClientEventMaskType;

/** Location client status values.
*/
typedef enum
{
  eLOC_CLIENT_SUCCESS                              = 0,
  /**< Request was successful. */

  eLOC_CLIENT_FAILURE_GENERAL                      = 1,
  /**< Failed because of a general failure. */

  eLOC_CLIENT_FAILURE_UNSUPPORTED                  = 2,
  /**< Failed because the service does not support the command. */

  eLOC_CLIENT_FAILURE_INVALID_PARAMETER            = 3,
  /**< Failed because the request contained invalid parameters. */

  eLOC_CLIENT_FAILURE_ENGINE_BUSY                  = 4,
  /**< Failed because the engine is busy. */

  eLOC_CLIENT_FAILURE_PHONE_OFFLINE                = 5,
  /**< Failed because the phone is offline. */

  eLOC_CLIENT_FAILURE_TIMEOUT                      = 6,
  /**< Failed because of a timeout. */

  eLOC_CLIENT_FAILURE_SERVICE_NOT_PRESENT          = 7,
  /**< Failed because the service is not present. */

  eLOC_CLIENT_FAILURE_SERVICE_VERSION_UNSUPPORTED  = 8,
  /**< Failed because the service version is unsupported. */

  eLOC_CLIENT_FAILURE_CLIENT_VERSION_UNSUPPORTED  =  9,
  /**< Failed because the service does not support client version. */

  eLOC_CLIENT_FAILURE_INVALID_HANDLE               = 10,
  /**< Failed because an invalid handle was specified. */

  eLOC_CLIENT_FAILURE_INTERNAL                     = 11,
  /**< Failed because of an internal error in the service. */

  eLOC_CLIENT_FAILURE_NOT_INITIALIZED              = 12,
  /**< Failed because the service has not been initialized. */

  eLOC_CLIENT_FAILURE_NOT_ENOUGH_MEMORY             = 13
  /**< Failed because there is not enough memory to do the operation. */

}locClientStatusEnumType;

/** Location client error values
*/
typedef enum
{
  eLOC_CLIENT_ERROR_SERVICE_UNAVAILABLE            = 1
  /**< Service is no longer available. Upon getting this error, the client
       must close the existing connection and reopen the connection. */

}locClientErrorEnumType;


/** Request messages the client can send to the location engine.

  The following requests do not have any data associated, so they do not have a
  payload structure defined:

  - GetServiceRevision
  - GetFixCriteria
  - GetPredictedOrbitsDataSource
  - GetPredictedOrbitsDataValidity
  - GetEngineLock
  - GetSbasConfigReq
  - GetRegisteredEvents
  - GetNmeaTypes
  - GetLowPowerMode
  - GetXtraTSessionControl
  - GetRegisteredEvents
  - GetOperationMode
  - GetCradleMountConfig
  - GetExternalPowerConfig
  - GetSensorControlConfig
  - GetSensorPerformanceControlConfiguration
  - WWANOutOfServiceNotification
*/
typedef union
{
   const qmiLocInformClientRevisionReqMsgT_v02* pInformClientRevisionReq;
   /**< Notifies the service about the revision the client is using.

        The client does not receive any indications corresponding to this
        request.

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_INFORM_CLIENT_REVISION_REQ_V02. */

   const qmiLocRegEventsReqMsgT_v02* pRegEventsReq;
   /**< Changes the events the client is interested in receiving.

        The client does not receive any indications corresponding to this
        request.

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_REG_EVENTS_REQ_V02. */

   const qmiLocStartReqMsgT_v02* pStartReq;
   /**< Starts a positioning session.

        The client receives the following indications: position report,
        satellite report, fix session report, and NMEA report (if applicable).

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_START_REQ_V02. */

   const qmiLocStopReqMsgT_v02* pStopReq;
   /**< Stops a positioning session. The client receives a fix session report
        denoting that the fix session ended after this message was sent.

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_STOP_REQ_V02. */

   const qmiLocNiUserRespReqMsgT_v02* pNiUserRespReq;
   /**< Informs the service about the user response for a network-initiated call.

        If the request is accepted by the service, the client receives the
        following indication containing a response:
        QMI_LOC_NI_USER_RESPONSE_IND_V02.

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_NI_USER_RESPONSE_REQ_V02. */

   const qmiLocInjectPredictedOrbitsDataReqMsgT_v02* pInjectPredictedOrbitsDataReq;
   /**< Injects the predicted orbits data into the service.

        When all predicted orbits data parts have been injected, the client
        receives the following indication containing a response:
        QMI_LOC_INJECT_PREDICTED_ORBITS_DATA_IND_V02.

        The client injects successive data parts without waiting for this
        indication as long as locClientSendReq() returns successfully.

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_INJECT_PREDICTED_ORBITS_DATA_REQ_V02. */

   const qmiLocInjectUtcTimeReqMsgT_v02* pInjectUtcTimeReq;
   /**< Injects UTC time into the service.

        If the request is accepted by the service, the client receives the
        following indication containing a response:
        QMI_LOC_INJECT_UTC_TIME_IND_V02.

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_INJECT_UTC_TIME_REQ_V02. */

   const qmiLocInjectPositionReqMsgT_v02* pInjectPositionReq;
   /**< Injects a position into the service.

        If the request is accepted by the service, the client receives the
        following indication containing a response:
        QMI_LOC_INJECT_POSITION_IND_V02.

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_INJECT_POSITION_REQ_V02. */

   const qmiLocSetEngineLockReqMsgT_v02* pSetEngineLockReq;
   /**< Sets the location engine lock.

        If the request is accepted by the service, the client receives the
        following indication containing a response:
        QMI_LOC_SET_ENGINE_LOCK_IND_V02.

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_SET_ENGINE_LOCK_REQ_V02. */

   const qmiLocSetSbasConfigReqMsgT_v02* pSetSbasConfigReq;
   /**< Sets the SBAS configuration.

        If the request is accepted by the service, the client receives the
        following indication containing a response:
        QMI_LOC_SET_SBAS_CONFIG_IND_V02.

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_SET_SBAS_CONFIG_REQ_V02 . */

   const qmiLocSetNmeaTypesReqMsgT_v02* pSetNmeaTypesReq;
   /**< Sets the NMEA types configuration.

        If the request is accepted by the service, the client receives the
        following indication containing a response:
        QMI_LOC_SET_NMEA_TYPES_IND_V02.

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_SET_NMEA_TYPES_REQ_V02. */

   const qmiLocSetLowPowerModeReqMsgT_v02* pSetLowPowerModeReq;
   /**< Sets the Low Power mode configuration.

        If the request is accepted by the service, the client receives the
        following indication containing a response:
        QMI_LOC_SET_LOW_POWER_MODE_IND_V02.

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_SET_LOW_POWER_MODE_REQ_V02. */

   const qmiLocSetServerReqMsgT_v02* pSetServerReq;
   /**< Sets the A-GPS server type and address.

        If the request is accepted by the service, the client receives the
        following indication containing a response:
        QMI_LOC_SET_SERVER_IND_V02.

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_SET_SERVER_REQ_V02. */

   const qmiLocGetServerReqMsgT_v02* pGetServerReq;
   /**< Gets the A-GPS server type and address.

        If the request is accepted by the service, the client receives the
        following indication containing a response:
        QMI_LOC_GET_SERVER_IND_V02.

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_GET_SERVER_REQ_V02. */

   const qmiLocDeleteAssistDataReqMsgT_v02* pDeleteAssistDataReq;
   /**< Deletes the aiding data from the engine.

        If the request is accepted by the service, the client receives the
        following indication containing a response:
        QMI_LOC_DELETE_ASSIST_DATA_IND_V02.

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_DELETE_ASSIST_DATA_REQ_V02. */

   const qmiLocInjectApCacheDataReqMsgT_v02 *pInjectApCacheDataReq;
   /**< Inject APcache data into the engine

        If the request is accepted by the service, the client receives the
        following indication containing a response:
        QMI_LOC_INJECT_APCACHE_DATA_IND_V02.

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_INJECT_APCACHE_DATA_REQ_V02. */

   const qmiLocInjectApDoNotCacheDataReqMsgT_v02 *pInjectApDoNotCacheDataReq;
   /**< Inject blacklist-Apcache data into the engine

        If the request is accepted by the service, the client receives the
        following indication containing a response:
        QMI_LOC_INJECT_DONOTAPCACHE_DATA_IND_V02.

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_INJECT_DONOTAPCACHE_DATA_REQ_V02. */


   const qmiLocSetXtraTSessionControlReqMsgT_v02* pSetXtraTSessionControlReq;
   /**< Sets XTRA-T session control in the engine.

        If the request is accepted by the service, the client receives the
        following indication containing a response:
        QMI_LOC_SET_XTRA_T_SESSION_CONTROL_IND_V02.

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_SET_XTRA_T_SESSION_CONTROL_REQ_V02. */

   const qmiLocInjectWifiPositionReqMsgT_v02* pInjectWifiPositionReq;
   /**< Injects a WiFi position into the engine.

        If the request is accepted by the service, the client receives the
        following indication containing a response:
        QMI_LOC_INJECT_WIFI_POSITION_IND_V02.

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_INJECT_WIFI_POSITION_REQ_V02. */

   const qmiLocNotifyWifiStatusReqMsgT_v02* pNotifyWifiStatusReq;
   /**< Notifies the engine about the WiFi status.

        If the request is accepted by the service, the client receives the
        following indication containing a response:
        QMI_LOC_NOTIFY_WIFI_STATUS_IND_V02.

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_NOTIFY_WIFI_STATUS_REQ_V02. */

   const qmiLocSetOperationModeReqMsgT_v02* pSetOperationModeReq;
   /**< Sets the engine Operation mode.

        If the request is accepted by the service, the client receives the
        following indication containing a response:
        QMI_LOC_SET_OPERATION_MODE_IND_V02.

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_SET_OPERATION_MODE_REQ_V02. */

   const qmiLocSetSpiStatusReqMsgT_v02* pSetSpiStatusReq;
   /**< Sends the stationary position status to the engine.

        If the request is accepted by the service, the client receives the
        following indication containing a response:
        QMI_LOC_SET_SPI_STATUS_IND_V02.

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_SET_SPI_STATUS_REQ_V02. */

   const qmiLocInjectSensorDataReqMsgT_v02* pInjectSensorDataReq;
   /**< Injects sensor data into the engine.

        If the request is accepted by the service, the client receives the
        following indication containing a response:
        QMI_LOC_INJECT_SENSOR_DATA_IND_V02.

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_INJECT_SENSOR_DATA_REQ_V02. */

   const qmiLocInjectTimeSyncDataReqMsgT_v02* pInjectTimeSyncReq;
   /**< Injects time synchronization information into the engine.

        If the request is accepted by the service, the client receives the
        following indication containing a response:
        QMI_LOC_INJECT_TIME_SYNC_DATA_IND_V02.

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_INJECT_TIME_SYNC_DATA_REQ_V02. */

   const qmiLocSetCradleMountConfigReqMsgT_v02* pSetCradleMountConfigReq;
   /**< Sets the cradle mount state information in the engine.

        If the request is accepted by the service, the client receives the
        following indication containing a response:
        SET_CRADLE_MOUNT_CONFIG_REQ_V02.

        To send this request, set the reqId field in locClientSendReq() to
        SET_CRADLE_MOUNT_CONFIG_IND_V02. */

   const qmiLocSetExternalPowerConfigReqMsgT_v02* pSetExternalPowerConfigReq;
   /**< Sets external power configuration state in the engine.

        If the request is accepted by the service, the client receives the
        following indication containing a response:
        QMI_LOC_SET_EXTERNAL_POWER_CONFIG_IND_V02.

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_SET_EXTERNAL_POWER_CONFIG_REQ_V02. */

   const qmiLocInformLocationServerConnStatusReqMsgT_v02*
     pInformLocationServerConnStatusReq;
   /**< Informs the engine about the connection status to the location server.

        This can be sent in response to a
        QMI_LOC_EVENT_LOCATION_SERVER_CONNECTION_REQ_IND_V02 request. The
        service sends back a QMI_LOC_INFORM_LOCATION_SERVER_CONN_STATUS_IND_V02
        response indication for this request.

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_INFORM_LOCATION_SERVER_CONN_STATUS_REQ_V02. */

   const qmiLocSetProtocolConfigParametersReqMsgT_v02*
     pSetProtocolConfigParametersReq;
   /**< Sets the protocol configuration parameters in the engine.

        If the request is accepted by the service, the client receives the
        following indication containing a response:
        QMI_LOC_SET_PROTOCOL_CONFIG_PARAMETERS_IND_V02.

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_SET_PROTOCOL_CONFIG_PARAMETERS_REQ_V02. */

   const qmiLocGetProtocolConfigParametersReqMsgT_v02*
     pGetProtocolConfigParametersReq;
   /**< Retrieves protocol configuration parameters from the engine.

        If the request is accepted by the service, the client receives the
        following indication containing a response:
        QMI_LOC_GET_PROTOCOL_CONFIG_PARAMETERS_IND_V02.

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_GET_PROTOCOL_CONFIG_PARAMETERS_REQ_V02. */

   const qmiLocSetSensorControlConfigReqMsgT_v02*
     pSetSensorControlConfigReq;
   /**< Sets the sensor control configuration parameters in the engine.

        If the request is accepted by the service, the client receives the
        following indication containing a response:
        QMI_LOC_SET_SENSOR_CONTROL_CONFIG_IND_V02.

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_SET_SENSOR_CONTROL_CONFIG_REQ_V02. */

   const qmiLocSetSensorPerformanceControlConfigReqMsgT_v02*
      pSetSensorPerformanceControlConfigReq;
   /**< Sets the sensor performance configuration parameters in the engine.

        If the request is accepted by the service, the client receives the
        following indication containing a response:
        QMI_LOC_SET_SENSOR_PERFORMANCE_CONTROL_CONFIGURATION_IND_V02.

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_SET_SENSOR_PERFORMANCE_CONTROL_CONFIGURATION_REQ_V02. */

   const qmiLocGetSensorPropertiesReqMsgT_v02* pGetSensorPropertiesReq;
   /**< Retrieves the sensor properties from the engine.

        If the request is accepted by the service, the client receives the
        following indication containing a response:
        QMI_LOC_GET_SENSOR_PROPERTIES_IND_V02.

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_GET_SENSOR_PROPERTIES_REQ_V02. */

   const qmiLocSetSensorPropertiesReqMsgT_v02* pSetSensorPropertiesReq;
   /**< Sets the sensor properties in the engine.

        If the request is accepted by the service, the client receives the
        following indication containing a response:
        QMI_LOC_SET_SENSOR_PROPERTIES_IND_V02.

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_SET_SENSOR_PROPERTIES_REQ_V02. */

   const qmiLocInjectSuplCertificateReqMsgT_v02* pInjectSuplCertificateReq;
   /**< Injects a SUPL certificate into the engine.

        If the request is accepted by the service, the client receives the
        following indication containing a response:
        QMI_LOC_INJECT_SUPL_CERTIFICATE_IND_V02.

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_INJECT_SUPL_CERTIFICATE_REQ_V02. */

   const qmiLocDeleteSuplCertificateReqMsgT_v02* pDeleteSuplCertificateReq;
   /**< Deletes a SUPL certificate from the engine.

        If the request is accepted by the service, the client receives the
        following indication containing a response:
        QMI_LOC_DELETE_SUPL_CERTIFICATE_IND_V02.

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_DELETE_SUPL_CERTIFICATE_REQ_V02. */

   const qmiLocSetPositionEngineConfigParametersReqMsgT_v02*
     pSetPositionEngineConfigParametersReq;
   /**< Sets position engine configuration.

        If the request is accepted by the service, the client receives the
        following indication containing a response:
        QMI_LOC_SET_POSITION_ENGINE_CONFIG_PARAMETERS_IND _V02.

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_SET_POSITION_ENGINE_CONFIG_PARAMETERS_REQ_V02. */

   const qmiLocGetPositionEngineConfigParametersReqMsgT_v02*
     pGetPositionEngineConfigParametersReq;
   /**< Gets position engine configuration.

         If the request is accepted by the service, the client receives the
         following indication containing a response:
         QMI_LOC_GET_POSITION_ENGINE_CONFIG_PARAMETERS_IND_V02.

         To send this request, set the reqId field in locClientSendReq() to
         QMI_LOC_GET_POSITION_ENGINE_CONFIG_PARAMETERS_REQ_V02. */

   const qmiLocAddCircularGeofenceReqMsgT_v02* pAddCircularGeofenceReq;
   /**< Adds a circular geofence.

        If the request is accepted by the service, the client receives the
        following indication containing a response:
        QMI_LOC_ADD_CIRCULAR_GEOFENCE_IND_V02.

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_ADD_CIRCULAR_GEOFENCE_REQ_V02 */

   const qmiLocDeleteGeofenceReqMsgT_v02* pDeleteGeofenceReq;
   /**< Deletes a geofence.

        If the request is accepted by the service, the client receives the
        following indication containing a response:
        QMI_LOC_DELETE_GEOFENCE_IND_V02.

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_DELETE_GEOFENCE_REQ_V02 */

   const qmiLocQueryGeofenceReqMsgT_v02* pQueryGeofenceReq;
   /**< Queries a geofence.

        If the request is accepted by the service, the client receives the
        following indication containing a response:
        QMI_LOC_QUERY_GEOFENCE_IND_V02

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_QUERY_GEOFENCE_REQ_V02. */

    const qmiLocEditGeofenceReqMsgT_v02* pEditGeofenceReq;
    /**< Edits geofence parameters.

        If the request is accepted by the service, the client receives the
        following indication containing a response:
        QMI_LOC_EDIT_GEOFENCE_IND_V02

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_EDIT_GEOFENCE_REQ_V02. */

    const qmiLocGetBestAvailablePositionReqMsgT_v02*
      pGetBestAvailablePositionReq;
    /**< Get the best available position from location engine

        If the request is accepted by the service, the client receives the
        following indication containing a response:
        QMI_LOC_GET_BEST_AVAILABLE_POSITION_IND_V02

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_GET_BEST_AVAILABLE_POSITION_REQ_V02. @newpagetable */

    const qmiLocSecureGetAvailablePositionReqMsgT_v02*
         pSecureGetBestAvailablePositionReq;
       /**< Get the best available position from location engine

           If the request is accepted by the service, the client receives the
           following indication containing a response:
           QMI_LOC_GET_BEST_AVAILABLE_POSITION_IND_V02

           To send this request, set the reqId field in locClientSendReq() to
           QMI_LOC_GET_BEST_AVAILABLE_POSITION_REQ_V02. @newpagetable */

    const qmiLocInjectMotionDataReqMsgT_v02* pInjectMotionDataReq;
    /**< Inject motion data in the location engine

        If the request is accepted by the service, the client receives the
        following indication containing a response:
        QMI_LOC_INJECT_MOTION_DATA_IND_V02

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_INJECT_MOTION_DATA_REQ_V02 */

    const qmiLocGetNiGeofenceIdListReqMsgT_v02* pGetNiGeofenceIdListReq;
    /**< Get the list of Network Initiated Geofences from the location engine.

        If the request is accepted by the service, the client receives the
        following indication containing a response:
        QMI_LOC_GET_NI_GEOFENCE_ID_LIST_IND_V02

        To send this request, set the reqId field in locClientSendReq() to
        QMI_LOC_GET_NI_GEOFENCE_ID_LIST_REQ_V02 */

    const qmiLocInjectGSMCellInfoReqMsgT_v02 *pInjectGSMCellInfoReq;
    /**< Inject GSM Cell Information into the location engine.
         If the request is accepted by the service, the client receives the
         following indication containing a response:
         QMI_LOC_INJECT_GSM_CELL_INFO_IND_V02

         To send this request, set the reqId field in locClientSendReq() to
         QMI_LOC_INJECT_GSM_CELL_INFO_REQ_V02 */

    const qmiLocInjectNetworkInitiatedMessageReqMsgT_v02
      *pInjectNetworkInitiatedMessageReq;
    /**< Inject Network Initiated Message into the location engine.
         If the request is accepted by the service, the client receives the
         following indication containing a response:
         QMI_LOC_INJECT_NETWORK_INITIATED_MESSAGE_IND_V02

         To send this request, set the reqId field in locClientSendReq() to
         QMI_LOC_INJECT_NETWORK_INITIATED_MESSAGE_REQ_V02 */

    const void *pWWANOutOfServiceNotificationReq;

    const qmiLocPedometerReportReqMsgT_v02 *pPedometerReportReq;
    /**< Send pedometer data to the location engine. If the request is
         accepted by the service, the client receives the following
         indication containing a response:
         QMI_LOC_PEDOMETER_REPORT_IND_V02

         To send this request, set the reqId field in locClientSendReq() to
         QMI_LOC_PEDOMETER_REPORT_REQ_V02 */

    const qmiLocInjectWCDMACellInfoReqMsgT_v02 *pInjectWCDMACellInfoReq;
    const qmiLocInjectTDSCDMACellInfoReqMsgT_v02 *pInjectTDSCDMACellInfoReq;
    const qmiLocInjectSubscriberIDReqMsgT_v02 *pInjectSubscriberIDReq;
    const qmiLocInjectWifiApDataReqMsgT_v02 *pInjectWifiApDataReq;
    const qmiLocNotifyWifiAttachmentStatusReqMsgT_v02 *pNotifyWifiAttachmentStatusReq;
    const qmiLocNotifyWifiEnabledStatusReqMsgT_v02 *pNotifyWifiEnabledStatusReq;

    const qmiLocReadFromBatchReqMsgT_v02 *pReadFromBatchReq;
    const qmiLocGetBatchSizeReqMsgT_v02 *pGetBatchSizeReq;
    const qmiLocStartBatchingReqMsgT_v02 *pStartBatchingReq;
    const qmiLocStopBatchingReqMsgT_v02 *pStopBatchingReq;
    const qmiLocReleaseBatchReqMsgT_v02 *pReleaseBatchReq;

    const qmiLocInjectVehicleSensorDataReqMsgT_v02 *pInjectVehicleSensorDataReq;

    /**< Send vehicle sensor data to the location engine. If the request is
         accepted by the service, the client receives the following
         indication containing a response:
         QMI_LOC_INJECT_VEHICLE_SENSOR_DATA_IND_V02

         To send this request, set the reqId field in locClientSendReq() to
         QMI_LOC_INJECT_VEHICLE_SENSOR_DATA_REQ_V02 */

    const qmiLocSetPremiumServicesCfgReqMsgT_v02 *pSetPremiumServicesCfgReq;
    /*QMI_LOC_SET_PREMIUM_SERVICES_CONFIG_REQ_V02*/

    const qmiLocGetAvailWwanPositionReqMsgT_v02 *pGetAvailWwanPositionReq;
    /*QMI_LOC_GET_AVAILABLE_WWAN_POSITION_REQ_V02*/

    const qmiLocSetXtraVersionCheckReqMsgT_v02 *pSetXtraVersionCheckReq;

    const qmiLocGdtUploadBeginStatusReqMsgT_v02* pGdtUploadBeginStatusReq;
    /* QMI_LOC_GDT_UPLOAD_BEGIN_STATUS_REQ_V02 */

    const qmiLocGdtUploadEndReqMsgT_v02* pGdtUploadEndReq;
    /* QMI_LOC_GDT_UPLOAD_END_REQ_V02*/

    const qmiLocInjectGtpClientDownloadedDataReqMsgT_v02 *pInjectGtpClientDownloadedDataReq;
    /* QMI_LOC_INJECT_GTP_CLIENT_DOWNLOADED_DATA_REQ_V02 */

    const qmiLocSetGNSSConstRepConfigReqMsgT_v02 *pSetGNSSConstRepConfigReq;
    /*QMI_LOC_SET_GNSS_CONSTELL_REPORT_CONFIG_V02*/

    const qmiLocStartDbtReqMsgT_v02 *pStartDbtReq;
    /*QMI_LOC_START_DBT_REQ_V02*/

    const qmiLocStopDbtReqMsgT_v02 *pStopDbtReq;
    /*QMI_LOC_STOP_DBT_REQ_V02*/

    const qmiLocInjectTimeZoneInfoReqMsgT_v02 *pInjectTimeZoneInfoReq;
    /*QMI_LOC_INJECT_TIME_ZONE_INFO*/

    const qmiLocQueryAonConfigReqMsgT_v02 *pQueryAonConfigReq;
    /*QMI_LOC_QUERY_AON_CONFIG_REQ_V02*/
}locClientReqUnionType;


/** Event indications that are sent by the service.
*/
typedef union
{
   const qmiLocEventPositionReportIndMsgT_v02* pPositionReportEvent;
   /**< Contains the position information.

        This event is generated after QMI_LOC_START_REQ_V02 is sent. If
        periodic fix criteria is specified, this event is generated multiple
        times periodically at the specified rate until QMI_LOC_STOP_REQ_V02 is
        sent.

        The eventIndId field in the event indication callback is set to
        QMI_LOC_EVENT_POSITION_REPORT_IND_V02. */

   const qmiLocEventGnssSvInfoIndMsgT_v02* pGnssSvInfoReportEvent;
   /**< Contains the GNSS satellite information.

        This event is generated after QMI_LOC_START_REQ_V02 is sent. This event
        is generated at 1 Hz if the location engine is tracking satellites to
        make a location fix.

        The eventIndId field in the event indication callback is set to
        QMI_LOC_EVENT_GNSS_INFO_IND_V02. */

   const qmiLocEventNmeaIndMsgT_v02* pNmeaReportEvent;
   /**< Contains an NMEA report sentence.

        The entire NMEA report consisting of multiple sentences is sent at a
        1 Hz rate. This event is generated after QMI_LOC_START_REQ_V02 is sent.

        The eventIndId field in the event indication callback is set to
        QMI_LOC_EVENT_NMEA_IND_V02. */

   const qmiLocEventNiNotifyVerifyReqIndMsgT_v02* pNiNotifyVerifyReqEvent;
   /**< Notifies a location client when the network triggers a positioning
        request to the mobile.

        Upon getting this event, the location client displays the
        network-initiated fix request in a dialog and prompts the user to
        accept or deny the request. The client responds to this request with
        the message QMI_LOC_NI_USER_RESPONSE_REQ_V02.

        The eventIndId field in the event indication callback is set to
        QMI_LOC_EVENT_NI_NOTIFY_VERIFY_REQ_IND_V02. */

   const qmiLocEventInjectTimeReqIndMsgT_v02* pInjectTimeReqEvent;
   /**< Asks the client for time assistance.

        The client responds to this request with the message
        QMI_LOC_INJECT_UTC_TIME_REQ_V02.

        The eventIndId field in the event indication callback is
        set to QMI_LOC_EVENT_INJECT_TIME_REQ_IND_V02. */

   const qmiLocEventInjectPredictedOrbitsReqIndMsgT_v02*
         pInjectPredictedOrbitsReqEvent;
   /**< Asks the client for predicted orbits data assistance.

        The client responds to this request with the message
        QMI_LOC_INJECT_PREDICTED_ORBITS_DATA_REQ_V02.

        The eventIndId field in the event indication callback is set to
        QMI_LOC_EVENT_INJECT_PREDICTED_ORBITS_REQ_IND_V02. */

   const qmiLocEventInjectPositionReqIndMsgT_v02* pInjectPositionReqEvent;
   /**< Asks the client for position assistance.

        The client responds to this request with the message
        QMI_LOC_INJECT_POSITION_REQ_V02.

        The eventIndId field in the event indication callback is set to
        QMI_LOC_EVENT_INJECT_POSITION_REQ_IND_V02. */

   const qmiLocEventEngineStateIndMsgT_v02* pEngineState;
   /**< Sent by the engine whenever it turns on or off.

        The eventIndId field in the event indication callback is set to
        QMI_LOC_EVENT_ENGINE_STATE_IND_V02. */

   const qmiLocEventFixSessionStateIndMsgT_v02* pFixSessionState;
   /**< Sent by the engine when a location session begins or ends.

        The eventIndId field in the event indication callback is set to
        QMI_LOC_EVENT_FIX_SESSION_STATE_IND_V02. */

   const qmiLocEventWifiReqIndMsgT_v02* pWifiReqEvent;
   /**< Sent by the engine when it needs WiFi support.

        The eventIndId field in the event indication callback is set to
        QMI_LOC_EVENT_WIFI_REQ_IND_V02. */

   const qmiLocEventSensorStreamingReadyStatusIndMsgT_v02*
          pSensorStreamingReadyStatusEvent;
   /**< Notifies the client that the engine is ready to accept sensor data.

        The eventIndId field in the event indication callback is set to
        QMI_LOC_EVENT_SENSOR_STREAMING_READY_STATUS_IND_V02. */

   const qmiLocEventTimeSyncReqIndMsgT_v02* pTimeSyncReqEvent;
   /**< Sent by the engine when it needs to synchronize its time with the sensor
        processor time.

        The eventIndId field in the event indication callback is set to
        QMI_LOC_EVENT_TIME_SYNC_REQ_IND_V02. */

   const qmiLocEventSetSpiStreamingReportIndMsgT_v02*
     pSetSpiStreamingReportEvent;
   /**< Asks the client to start/stop sending a Stationary Position Indicator
        (SPI) stream.

        The eventIndId field in the event indication callback is set to
        QMI_LOC_SET_SPI_STREAMING_REPORT_IND_V02. */

   const qmiLocEventLocationServerConnectionReqIndMsgT_v02*
      pLocationServerConnReqEvent;
   /**< Sent by the engine to ask the client to open or close a connection to
        a location server.

        The client responds to this request by sending the
        QMI_LOC_INFORM_LOCATION_SERVER_CONN_STATUS_REQ_V02 message.

        The eventIndId field in the event indication callback is set to
        QMI_LOC_EVENT_LOCATION_SERVER_CONNECTION_REQ_IND_V02. */

   const qmiLocEventNiGeofenceNotificationIndMsgT_v02*
     pNiGeofenceNotificationEvent;
   /**< Sent by the engine to notify the client about changes to a
        network-initiated geofence.

        The eventIndId field in the event indication callback is set to
        QMI_LOC_EVENT_NI_GEOFENCE_NOTIFICATION_IND_V02. */

   const qmiLocEventGeofenceGenAlertIndMsgT_v02* pGeofenceGenAlertEvent;
   /**< Sent by the engine to notify the client about updates that may
        affect a geofence operation.

        The eventIndId field in the event indication callback is set to
        QMI_LOC_EVENT_GEOFENCE_GEN_ALERT_IND_V02. */

   const qmiLocEventGeofenceBreachIndMsgT_v02* pGeofenceBreachEvent;
   /**< Sent by the engine to notify the client about a geofence breach
        event.

        The eventIndId field in the event indication callback is set to
        QMI_LOC_EVENT_GEOFENCE_BREACH_NOTIFICATION_IND_V02. @newpagetable */

   const qmiLocEventGeofenceBatchedBreachIndMsgT_v02* pGeofenceBatchedBreachEvent;
   /**< Sent by the engine to notify the client about a geofence breach
        event.

        The eventIndId field in the event indication callback is set to
        QMI_LOC_EVENT_GEOFENCE_BATCHED_BREACH_NOTIFICATION_IND_V02. @newpagetable */

   const qmiLocEventPedometerControlIndMsgT_v02* pPedometerControlEvent;
   /**< Sent by the engine to recommend how pedometer data is sent to the
        location engine.
        The eventIndId field in the event indication callback is set to
        QMI_LOC_EVENT_PEDOMETER_CONTROL_IND_V02. @newpagetable */

   const qmiLocEventMotionDataControlIndMsgT_v02* pMotionDataControlEvent;
   /**< Sent by the engine to recommend how motion data is sent to the
        location engine.
        The eventIndId field in the event indication callback is set to
        QMI_LOC_EVENT_MOTION_DATA_CONTROL_IND_V02. @newpagetable */

   const qmiLocEventInjectWifiApDataReqIndMsgT_v02* pWifiApDataReqEvent;
   const qmiLocEventLiveBatchedPositionReportIndMsgT_v02* pBatchPositionReportEvent;
   /**< Sent by the engine to notify the client that live batch location
        is ready, and the location info.

        The eventIndId field in the event indication callback is set to
        QMI_LOC_EVENT_LIVE_BATCHED_POSITION_REPORT_IND_V02. */

   const qmiLocEventBatchFullIndMsgT_v02* pBatchCount;
   /**< Sent by the engine to notify the client that batch location is
        full, and how many location are available to read.

        The eventIndId field in the event indication callback is set to
        QMI_LOC_EVENT_BATCH_FULL_IND_V02. */

   const qmiLocEventVehicleDataReadyIndMsgT_v02* pVehicleDataReadyEvent;
   /**< Sent by the engine to recommend how vehicle sensor data is
        sent to the location engine.
        The eventIndId field in the event indication callback is set to
        QMI_LOC_EVENT_VEHICLE_DATA_READY_STATUS_IND_V02. @newpagetable */

   const qmiLocEventGeofenceProximityIndMsgT_v02* pGeofenceProximityEvent;
   /**< Sent by the engine to notify the client about a geofence proximity
        event.

        The eventIndId field in the event indication callback is set to
        QMI_LOC_EVENT_GEOFENCE_PROXIMITY_NOTIFICATION_IND_V02. @newpagetable */

   const qmiLocEventGdtUploadBeginStatusReqIndMsgT_v02* pGdtUploadBeginEvent;
   /**< Sent by the engine to notify the client about a GDT upload
        begine event.

       The eventIndId field in the event indication callback is set to
       QMI_LOC_EVENT_GDT_UPLOAD_BEGIN_STATUS_REQ_IND_V02. @newpagetable */

   const qmiLocEventGdtUploadEndReqIndMsgT_v02* pGdtUploadEndEvent;
   /**< Sent by the engine to notify the client about a GDT upload
        end event.

       The eventIndId field in the event indication callback is set to
       QMI_LOC_EVENT_GDT_UPLOAD_END_REQ_IND_V02. @newpagetable */

   const qmiLocEventGnssSvMeasInfoIndMsgT_v02* pGnssSvRawInfoEvent;
   /**< Sent by the engine to report GNSS measurement.
        The eventIndId field in the event indication callback is set to
        QMI_LOC_EVENT_GNSS_MEASUREMENT_REPORT_IND_V02. @newpagetable */

   const qmiLocEventDbtPositionReportIndMsgT_v02 *pDbtPositionReportEvent;
   /**< Sent by the engine to notify the client of a distance based
        tracking position report.
        QMI_LOC_EVENT_DBT_POSITION_REPORT_IND_V02*/

   const qmiLocEventDbtSessionStatusIndMsgT_v02 *pDbtSessionStatusEvent;
   /**< Sent by the engine to notify the client of the status of the
      DBT session.
      QMI_LOC_EVENT_DBT_SESSION_STATUS_IND_V02*/

   const qmiLocEventGeofenceBatchedDwellIndMsgT_v02 *pGeofenceBatchedDwellEvent;
   /**< Sent by the engine to notify the client of the dwell time inside
      or outside of a Geofence for a specified time.
      QMI_LOC_EVENT_GEOFENCE_BATCHED_DWELL_NOTIFICATION_IND_V02*/

   const qmiLocEventGetTimeZoneReqIndMsgT_v02 *pGetTimeZoneReqEvent;
   /**< Sent by the engine to request injection of time zone info
      QMI_LOC_EVENT_GET_TIME_ZONE_INFO_IND_V02>*/

   const qmiLocEventBatchingStatusIndMsgT_v02* pBatchingStatusEvent;
   /**< Sent by the engine to notify the control point of the batching status.
        The eventIndId field in the event indication callback is set to
        QMI_LOC_EVENT_BATCHING_STATUS_IND_V02. */
}locClientEventIndUnionType;


/** Response indications that are sent by the service.
*/
typedef union
{
   const qmiLocGetServiceRevisionIndMsgT_v02* pGetServiceRevisionInd;
   /**< Response to the QMI_LOC_GET_SERVICE_REVISION_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_GET_SERVICE_REVISION_IND_V02. */

   const qmiLocGetFixCriteriaIndMsgT_v02* pGetFixCriteriaInd;
   /**< Response to the QMI_LOC_GET_FIX_CRITERIA_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_GET_FIX_CRITERIA_IND_V02. */

   const qmiLocNiUserRespIndMsgT_v02* pNiUserRespInd;
   /**< Response to the QMI_LOC_NI_USER_RESPONSE_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_NI_USER_RESPONSE_IND_V02. */

   const qmiLocInjectPredictedOrbitsDataIndMsgT_v02*
     pInjectPredictedOrbitsDataInd;
   /**< Sent after a predicted orbits data part has been successfully injected.

        The client waits for this indication before injecting the next part.
        This indication is sent in response to
        QMI_LOC_INJECT_PREDICTED_ORBITS_DATA_REQ_V02.

        The respIndId field in the response indication callback is set to
        QMI_LOC_INJECT_PREDICTED_ORBITS_DATA_IND_V02. */

   const qmiLocGetPredictedOrbitsDataSourceIndMsgT_v02*
      pGetPredictedOrbitsDataSourceInd;
   /**< Response to the QMI_LOC_GET_PREDICTED_ORBITS_DATA_SOURCE_REQ_V02
        request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_GET_PREDICTED_ORBITS_DATA_SOURCE_IND_V02. */

   const qmiLocGetPredictedOrbitsDataValidityIndMsgT_v02*
     pGetPredictedOrbitsDataValidityInd;
   /**< Response to the QMI_LOC_GET_PREDICTED_ORBITS_DATA_VALIDITY_REQ_V02
        request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_GET_PREDICTED_ORBITS_DATA_VALIDITY_IND_V02. */

   const qmiLocInjectUtcTimeIndMsgT_v02* pInjectUtcTimeInd;
   /**< Response to the QMI_LOC_INJECT_UTC_TIME_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_INJECT_UTC_TIME_IND_V02. */

   const qmiLocInjectPositionIndMsgT_v02* pInjectPositionInd;
   /**< Response to the QMI_LOC_INJECT_POSITION_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_INJECT_POSITION_IND_V02. */

   const qmiLocSetEngineLockIndMsgT_v02* pSetEngineLockInd;
   /**< Response to the QMI_LOC_SET_ENGINE_LOCK_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_SET_ENGINE_LOCK_IND_V02. */

   const qmiLocGetEngineLockIndMsgT_v02* pGetEngineLockInd;
   /**< Response to the QMI_LOC_GET_ENGINE_LOCK_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_GET_ENGINE_LOCK_IND_V02. */

   const qmiLocSetSbasConfigIndMsgT_v02* pSetSbasConfigInd;
   /**< Response to the QMI_LOC_SET_SBAS_CONFIG_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_SET_SBAS_CONFIG_IND_V02. */

   const qmiLocGetSbasConfigIndMsgT_v02* pGetSbasConfigInd;
   /**< Response to the QMI_LOC_GET_SBAS_CONFIG_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_GET_SBAS_CONFIG_IND_V02. */

   const qmiLocSetNmeaTypesIndMsgT_v02* pSetNmeaTypesInd;
   /**< Response to the QMI_LOC_SET_NMEA_TYPES_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_SET_NMEA_TYPES_IND_V02. */

   const qmiLocGetNmeaTypesIndMsgT_v02* pGetNmeaTypesInd;
   /**< Response to the QMI_LOC_GET_NMEA_TYPES_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_GET_NMEA_TYPES_IND_V02. */

   const qmiLocSetLowPowerModeIndMsgT_v02* pSetLowPowerModeInd;
   /**< Response to the QMI_LOC_SET_LOW_POWER_MODE_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_SET_LOW_POWER_MODE_IND_V02. */

   const qmiLocGetLowPowerModeIndMsgT_v02* pGetLowPowerModeInd;
   /**< Response to the QMI_LOC_GET_LOW_POWER_MODE_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_GET_LOW_POWER_MODE_IND_V02. */

   const qmiLocSetServerIndMsgT_v02* pSetServerInd;
   /**< Response to the QMI_LOC_SET_SERVER_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_SET_SERVER_IND_V02. */

   const qmiLocGetServerIndMsgT_v02* pGetServerInd;
   /**< Response to the QMI_LOC_GET_SERVER_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_GET_SERVER_IND_V02. */

   const qmiLocDeleteAssistDataIndMsgT_v02* pDeleteAssistDataInd;
   /**< Response to the QMI_LOC_DELETE_ASSIST_DATA_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_DELETE_ASSIST_DATA_IND_V02. */

   const qmiLocInjectApCacheDataIndMsgT_v02 *pInjectApCacheDataInd;
   /**< Response to the QMI_LOC_INJECT_APCACHE_DATA_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_INJECT_APCACHE_DATA_IND_V02. */

   const qmiLocInjectApDoNotCacheDataIndMsgT_v02 *pInjectApDoNotCacheDataInd;
   /**< Response to the QMI_LOC_INJECT_DONOTAPCACHE_DATA_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_INJECT_DONOTAPCACHE_DATA_IND_V02. */

   const qmiLocSetXtraTSessionControlIndMsgT_v02* pSetXtraTSessionControlInd;
   /**< Response to the QMI_LOC_SET_XTRA_T_SESSION_CONTROL_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_SET_XTRA_T_SESSION_CONTROL_IND_V02. */

   const qmiLocGetXtraTSessionControlIndMsgT_v02* pGetXtraTSessionControlInd;
   /**< Response to the QMI_LOC_GET_XTRA_T_SESSION_CONTROL_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_GET_XTRA_T_SESSION_CONTROL_IND_V02. */

   const qmiLocInjectWifiPositionIndMsgT_v02* pInjectWifiPositionInd;
   /**< Response to the QMI_LOC_INJECT_WIFI_POSITION_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_INJECT_WIFI_POSITION_IND_V02. */

   const qmiLocNotifyWifiStatusIndMsgT_v02* pNotifyWifiStatusInd;
   /**< Response to the QMI_LOC_NOTIFY_WIFI_STATUS_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_NOTIFY_WIFI_STATUS_IND_V02. */

   const qmiLocGetRegisteredEventsIndMsgT_v02* pGetRegisteredEventsInd;
   /**< Response to the QMI_LOC_GET_REGISTERED_EVENTS_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_GET_REGISTERED_EVENTS_IND_V02. */

   const qmiLocSetOperationModeIndMsgT_v02* pSetOperationModeInd;
   /**< Response to the QMI_LOC_SET_OPERATION_MODE_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_SET_OPERATION_MODE_IND_V02. */

   const qmiLocGetOperationModeIndMsgT_v02* pGetOperationModeInd;
   /**< Response to the QMI_LOC_GET_OPERATION_MODE_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_GET_OPERATION_MODE_IND_V02. */

   const qmiLocSetSpiStatusIndMsgT_v02* pSetSpiStatusInd;
   /**< Response to the QMI_LOC_SET_SPI_STATUS_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_SET_SPI_STATUS_IND_V02. */

   const qmiLocInjectSensorDataIndMsgT_v02* pInjectSensorDataInd;
   /**< Response to the QMI_LOC_INJECT_SENSOR_DATA_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_INJECT_SENSOR_DATA_IND_V02. */

   const qmiLocInjectTimeSyncDataIndMsgT_v02* pInjectTimeSyncDataInd;
   /**< Response to the QMI_LOC_INJECT_TIME_SYNC_DATA_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_INJECT_TIME_SYNC_DATA_IND_V02. */

   const qmiLocSetCradleMountConfigIndMsgT_v02* pSetCradleMountConfigInd;
   /**< Response to the QMI_LOC_SET_CRADLE_MOUNT_CONFIG_IND_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_SET_CRADLE_MOUNT_CONFIG_REQ_V02. */

   const qmiLocGetCradleMountConfigIndMsgT_v02* pGetCradleMountConfigInd;
   /**< Response to the QMI_LOC_GET_CRADLE_MOUNT_CONFIG_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_GET_CRADLE_MOUNT_CONFIG_IND_V02. */

   const qmiLocSetExternalPowerConfigIndMsgT_v02* pSetExternalPowerConfigInd;
   /**< Response to the QMI_LOC_SET_EXTERNAL_POWER_CONFIG_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_SET_EXTERNAL_POWER_CONFIG_IND_V02. */

   const qmiLocGetExternalPowerConfigIndMsgT_v02* pGetExternalPowerConfigInd;
   /**< Response to the QMI_LOC_GET_EXTERNAL_POWER_CONFIG_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_GET_EXTERNAL_POWER_CONFIG_IND_V02. */

   const qmiLocInformLocationServerConnStatusIndMsgT_v02*
     pInformLocationServerConnStatusInd;
   /**< Response to the QMI_LOC_INFORM_LOCATION_SERVER_CONN_STATUS_REQ_V02
        request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_INFORM_LOCATION_SERVER_CONN_STATUS_IND_V02.*/

   const qmiLocSetProtocolConfigParametersIndMsgT_v02*
     pSetProtocolConfigParametersInd;
   /**< Response to the QMI_LOC_SET_PROTOCOL_CONFIG_PARAMETERS_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_SET_PROTOCOL_CONFIG_PARAMETERS_IND_V02. */

   const qmiLocGetProtocolConfigParametersIndMsgT_v02*
     pGetProtocolConfigParametersInd;
   /**< Response to the QMI_LOC_GET_PROTOCOL_CONFIG_PARAMETERS_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_GET_PROTOCOL_CONFIG_PARAMETERS_IND_V02. */

   const qmiLocSetSensorControlConfigIndMsgT_v02* pSetSensorControlConfigInd;
   /**< Response to the QMI_LOC_SET_SENSOR_CONTROL_CONFIG_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_SET_SENSOR_CONTROL_CONFIG_IND_V02.
         */

   const qmiLocGetSensorControlConfigIndMsgT_v02* pGetSensorControlConfigInd;
   /**< Response to the QMI_LOC_GET_SENSOR_CONTROL_CONFIG_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_GET_SENSOR_CONTROL_CONFIG_IND_V02.
         */

   const qmiLocSetSensorPropertiesIndMsgT_v02* pSetSensorPropertiesInd;
   /**< Response to the QMI_LOC_SET_SENSOR_PROPERTIES_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_SET_SENSOR_PROPERTIES_IND_V02.
         */

   const qmiLocGetSensorPropertiesIndMsgT_v02* pGetSensorPropertiesInd;
   /**< Response to the QMI_LOC_GET_SENSOR_PROPERTIES_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_GET_SENSOR_PROPERTIES_IND_V02.
         */

   const qmiLocSetSensorPerformanceControlConfigIndMsgT_v02*
     pSetSensorPerformanceControlConfigInd;
   /**< Response to the
        QMI_LOC_SET_SENSOR_PERFORMANCE_CONTROL_CONFIGURATION_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_SET_SENSOR_PERFORMANCE_CONTROL_CONFIGURATION_IND_V02. */

   const qmiLocGetSensorPerformanceControlConfigIndMsgT_v02*
     pGetSensorPerformanceControlConfigInd;
   /**< Response to the
        QMI_LOC_GET_SENSOR_PERFORMANCE_CONTROL_CONFIGURATION_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_GET_SENSOR_PERFORMANCE_CONTROL_CONFIGURATION_IND_V02. */

   const qmiLocInjectSuplCertificateIndMsgT_v02* pInjectSuplCertificateInd;
   /**< Response to the QMI_LOC_INJECT_SUPL_CERTIFICATE_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_INJECT_SUPL_CERTIFICATE_IND_V02. */

   const qmiLocDeleteSuplCertificateIndMsgT_v02* pDeleteSuplCertificateInd;
   /**< Response to the QMI_LOC_DELETE_SUPL_CERTIFICATE_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_DELETE_SUPL_CERTIFICATE_IND_V02. */

   const qmiLocSetPositionEngineConfigParametersIndMsgT_v02*
     pSetPositionEngineConfigParametersInd;
   /**< Response to the QMI_LOC_SET_POSITION_ENGINE_CONFIG_PARAMETERS_REQ_V02
        request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_SET_POSITION_ENGINE_CONFIG_PARAMETERS_IND_V02. */

   const qmiLocGetPositionEngineConfigParametersIndMsgT_v02*
     pGetPositionEngineConfigParametersInd;
    /**< Response to the QMI_LOC_GET_POSITION_ENGINE_CONFIG_PARAMETERS_REQ_V02
         request.

         The respIndId field in the response indication callback is set to
         QMI_LOC_GET_POSITION_ENGINE_CONFIG_PARAMETERS_IND_V02. */

   const qmiLocAddCircularGeofenceIndMsgT_v02* pAddCircularGeofenceInd;
   /**< Response to the QMI_LOC_ADD_CIRCULAR_GEOFENCE_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_ADD_CIRCULAR_GEOFENCE_IND_V02. */

   const qmiLocDeleteGeofenceIndMsgT_v02* pDeleteGeofenceInd;
   /**< Response to the QMI_LOC_DELETE_GEOFENCE_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_DELETE_GEOFENCE_IND_V02. */

   const qmiLocQueryGeofenceIndMsgT_v02* pQueryGeofenceInd;
    /**< Response to the QMI_LOC_QUERY_GEOFENCE_REQ_V02 request.

         The respIndId field in the response indication callback is set to
         QMI_LOC_QUERY_GEOFENCE_IND_V02. */

   const qmiLocEditGeofenceIndMsgT_v02* pEditGeofenceInd;
   /**< Response to the QMI_LOC_EDIT_GEOFENCE_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_EDIT_GEOFENCE_IND_V02. */

   const qmiLocGetBestAvailablePositionIndMsgT_v02*
      pGetBestAvailablePositionInd;
   /**< Response to the QMI_LOC_GET_BEST_AVAILABLE_POSITION_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_GET_BEST_AVAILABLE_POSITION_IND_V02. */

   const qmiLocSecureGetAvailablePositionIndMsgT_v02*
      pSecureGetBestAvailablePositionInd;
   /**< Response to the QMI_LOC_SECURE_GET_AVAILABLE_POSITION_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_SECURE_GET_AVAILABLE_POSITION_IND_V02. */

   const qmiLocInjectMotionDataIndMsgT_v02* pInjectMotionDataInd;
   /**< Response to the QMI_LOC_INJECT_MOTION_DATA_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_INJECT_MOTION_DATA_IND_V02. */

   const qmiLocGetNiGeofenceIdListIndMsgT_v02* pGetNiGeofenceIdListInd;
   /**< Response to the QMI_LOC_GET_NI_GEOFENCE_ID_LIST_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_GET_NI_GEOFENCE_ID_LIST_IND_V02. */

   const qmiLocInjectGSMCellInfoIndMsgT_v02* pInjectGSMCellInfoInd;
    /**< Response to the QMI_LOC_INJECT_GSM_CELL_INFO_REQ_V02 request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_INJECT_GSM_CELL_INFO_IND_V02. */

   const qmiLocInjectNetworkInitiatedMessageIndMsgT_v02*
     pInjectNetworkInitiatedMessageInd;

   /**< Response to the QMI_LOC_INJECT_NETWORK_INITIATED_MESSAGE_REQ_V02
        request.

        The respIndId field in the response indication callback is set to
        QMI_LOC_INJECT_NETWORK_INITIATED_MESSAGE_IND_V02. */

   const qmiLocWWANOutOfServiceNotificationIndMsgT_v02*
     pWWANOutOfServiceNotificationInd;

   /**< Response to the QMI_LOC_WWAN_OUT_OF_SERVICE_NOTIFICATION_REQ_V02
        request.
        The respIndId field in the response indication callback is set to
        QMI_LOC_WWAN_OUT_OF_SERVICE_NOTIFICATION_IND_V02. */

   const qmiLocPedometerReportIndMsgT_v02* pPedometerReportInd;

   /**< Response to the QMI_LOC_PEDOMETER_REPORT_REQ_V02 request.
        The respIndId field in the response indication callback is set to
        QMI_LOC_PEDOMETER_REPORT_IND_V02. */

    const qmiLocInjectWCDMACellInfoIndMsgT_v02 *pInjectWCDMACellInfoInd;
    const qmiLocInjectTDSCDMACellInfoIndMsgT_v02 *pInjectTDSCDMACellInfoInd;
    const qmiLocInjectSubscriberIDIndMsgT_v02 *pInjectSubscriberIDInd;
    const qmiLocInjectWifiApDataIndMsgT_v02 *pInjectWifiApDataInd;
    const qmiLocNotifyWifiAttachmentStatusIndMsgT_v02 *pNotifyWifiAttachmentStatusInd;
    const qmiLocNotifyWifiEnabledStatusIndMsgT_v02 *pNotifyWifiEnabledStatusInd;

    const qmiLocInjectVehicleSensorDataIndMsgT_v02 *pInjectVehicleSensorDataInd;

    /**< Response to the QMI_LOC_INJECT_VEHICLE_SENSOR_DATA_REQ_V02 request.
        The respIndId field in the response indication callback is set to
        QMI_LOC_INJECT_VEHICLE_SENSOR_DATA_IND_V02. */

    const qmiLocGetAvailWwanPositionIndMsgT_v02 *pGetAvailWwanPositionInd;
    /*QMI_LOC_GET_AVAILABLE_WWAN_POSITION_IND_V02*/

    const qmiLocSetXtraVersionCheckIndMsgT_v02 *pSetXtraVersionCheckInd;
    /*QMI_LOC_SET_XTRA_VERSION_CHECK_IND_V02*/

    const qmiLocSetGNSSConstRepConfigIndMsgT_v02 *pSetGNSSConstRepConfigInd;
    /*QMI_LOC_SET_GNSS_CONSTELL_REPORT_CONFIG_IND_V02*/

    const qmiLocStartDbtIndMsgT_v02 *pStartDbtInd;
    /*QMI_LOC_START_DBT_IND_V02*/

    const qmiLocStopDbtIndMsgT_v02 *pStopDbtInd;
    /*QMI_LOC_STOP_DBT_IND_V02*/

    const qmiLocInjectTimeZoneInfoIndMsgT_v02 *pInjectTimeZoneInfoInd;
    /*QMI_LOC_INJECT_TIME_ZONE_INFO_IND_V02*/

    const qmiLocQueryAonConfigIndMsgT_v02 *pQueryAonConfigInd;
    /*QMI_LOC_QUERY_AON_CONFIG_IND_V02*/
}locClientRespIndUnionType;

/** @} */ /* end_addtogroup data_types */

/** @addtogroup callback_functions
@{ */
/**
  Location event indication callback function type. The Location service can
  generate two types of indications:

  - Asynchronous events indications, such as time injection request and satellite
    reports. The client specifies the asynchronous events it is interested in
    receiving through the event mask (see locClientOpen()).
  - Response indications that are generated as a response to a request. For
    example, the QMI_LOC_GET_FIX_CRITERIA_REQ_V02 request generates the
    indication, QMI_LOC_GET_FIX_CRITERIA_IND_V02.

  This callback handles the asynchronous event indications.

  @datatypes
  #locClientHandleType \n
  #locClientEventIndUnionType

  @param handle            Location client for this event. Only the client who
                           registered for the corresponding event receives
                           this callback.
  @param eventIndId        ID of the event indication.
  @param eventIndPayload   Event indication payload.
  @param pClientCookie     Pointer to the cookie the client specified during
                           registration.

  @return
  None.

  @dependencies
  None. @newpage
*/
typedef void (*locClientEventIndCbType)(
      locClientHandleType handle,
      uint32_t eventIndId,
      const locClientEventIndUnionType eventIndPayload,
      void *pClientCookie
);

/**
  Location response indication callback function type. The Location service can
  generate two types of indications:

  - Asynchronous events indications, such as time injection request and satellite
    reports. The client specifies the asynchronous events it is interested in
    receiving through the event mask (see locClientOpen()).
  - Response indications that are generated as a response to a request. For
    example, the QMI_LOC_GET_FIX_CRITERIA_REQ_V02 request generates the
    indication, QMI_LOC_GET_FIX_CRITERIA_IND_V02.

  This callback handles the response indications.

  @datatypes
  #locClientHandleType \n
  #locClientRespIndUnionType

  @param handle           Location client who sent the request for which this
                          response indication is generated.
  @param respIndId        ID of the response. It is the same value as the ID
                          of request sent to the engine.
  @param respIndPayload   Payload of the response indication.
  @param pClientCookie    Pointer to the cookie the client specified during
                          registration.

  @return
  None.

  @dependencies
  None. @newpage
*/
typedef void  (*locClientRespIndCbType)(
      locClientHandleType handle,
      uint32_t respIndId,
      const locClientRespIndUnionType respIndPayload,
      void *pClientCookie
);

/**
  Location error callback function type. This function is called to inform
  the client that the service is no longer available. When the client
  receives this callback, it must close the existing connection and reopen
  the client connection.

  @datatypes
  #locClientHandleType \n
  #locClientErrorEnumType

  @param handle           Location client who sent the request for which this
                          error indication is generated.
  @param errorId          Error ID.
  @param pClientCookie    Payload associated with the error indication.

  @return
  None.

  @dependencies
  None.
*/
typedef void  (*locClientErrorCbType)(
      locClientHandleType handle,
      locClientErrorEnumType errorId,
      void* pClientCookie
 );
/** @} */ /* end_addtogroup callback_functions */


/** @ingroup data_types
  Callback functions to be registered during locClientOpen().
*/
typedef struct
{
    uint32_t size;                       /**< Size of the structure. */
    locClientEventIndCbType eventIndCb;  /**< Event indication callback. */
    locClientRespIndCbType respIndCb;    /**< Response indication callback. */
    locClientErrorCbType errorCb;        /**< Error indication callback.
                                              @newpagetable */
}locClientCallbacksType;

/**
  Response for getting qmi service list
*/
typedef struct
{
    qmi_get_supported_msgs_resp_v01 resp; /**< Response */
}qmiLocGetSupportMsgT_v02;

/*===========================================================================
 *
 *                          FUNCTION DECLARATION
 *
 *==========================================================================*/
/** @addtogroup operation_functions
@{ */
/*==========================================================================
    locClientOpen */
/** @xreflabel{hdr:locClientOpenFunction}
  Connects a location client to the location engine. If the connection is
  successful, this function returns a handle that the location client uses for
  future location operations.

  @datatypes
  #locClientStatusEnumType \n
  #locClientEventMaskType \n
  #locClientCallbacksType \n
  #locClientHandleType

  @param[in]  eventRegMask          Mask of asynchronous events the client is
                                    interested in receiving.
  @param[in]  pLocClientCallbacks   Pointer to structure containing the
                                    callbacks.
  @param[out] pLocClientHandle      Pointer to the handle to be used by the
                                    client for any subsequent requests.
  @param[in]  pLocClientCookie      Pointer to a cookie to be returned to the
                                    client along with the callbacks.

  @return
  One of the following error codes:
  - eLOC_CLIENT_SUCCESS -- If the connection is opened.
  - Non-zero error code (see #locClientStatusEnumType) -- On failure.

  @dependencies
  None. @newpage
*/
extern locClientStatusEnumType locClientOpen (
      locClientEventMaskType            eventRegMask,
      const locClientCallbacksType*     pLocClientCallbacks,
      locClientHandleType*              pLocClientHandle,
      const void*                       pLocClientCookie
);


/*==========================================================================
    locClientClose */
/** @xreflabel{hdr:locClientCloseFunction}
  Disconnects a client from the location engine and sets the handle to
  LOC_CLIENT_INVALID_HANDLE_VALUE.

  @datatypes
  #locClientStatusEnumType \n
  #locClientHandleType

  @param[in] pLocClientHandle  Pointer to the handle returned by the
                               locClientOpen() function.

  @return
  One of the following error codes:
  - 0 (eLOC_CLIENT_SUCCESS) -- On success.
  - Non-zero error code (see \ref locClientStatusEnumType) -- On failure.

  @dependencies
  None. @newpage
*/
extern locClientStatusEnumType locClientClose (
      locClientHandleType* pLocClientHandle
);

/*=============================================================================
    locClientSendReq */
/** @xreflabel{hdr:locClientSendReqFunction}
  Sends a message to the location engine. If this function is successful, the
  client expects an indication (except start, stop, event registration, and
  sensor injection messages) through the registered callback in the
  locClientOpen() function.

  The indication contains the status of the request. If the status is a success,
  the indication also contains the payload associated with response.

  @datatypes
  #locClientStatusEnumType \n
  #locClientHandleType \n
  #locClientReqUnionType

  @param[in] handle        Handle returned by the locClientOpen() function.
  @param[in] reqId         QMI_LOC service message ID of the request.
  @param[in] reqPayload    Payload of the request. This can be NULL if the
                           request has no payload.

  @return
  One of the following error codes:
  - 0 (eLOC_CLIENT_SUCCESS) -- On success.
  - Non-zero error code (see \ref locClientStatusEnumType) -- On failure.

  @dependencies
  None. @newpage
*/
extern locClientStatusEnumType locClientSendReq(
     locClientHandleType       handle,
     uint32_t                  reqId,
     locClientReqUnionType     reqPayload
);

/*=============================================================================
    locClientSupportMsgCheck */
/**
  @brief Sends a QMI_LOC_GET_SUPPORTED_MSGS_REQ_V02 message to the
         location engine, and then receives a list of all services supported
         by the engine. This function will check if the input service(s) form
         the client is in the list or not. If the locClientSupportMsgCheck()
         function is successful, the client should expect an result of
         the service is supported or not recorded in supportedMsg.
  @param [in] handle Handle returned by the locClientOpen()
              function.
  @param [in] supportedMsg   a integer used to record which
                             message is supported

  @return
  One of the following error codes:
  - 0 (eLOC_CLIENT_SUCCESS) -- On success.
  - Non-zero error code (see \ref locClientStatusEnumType) -- On failure.

  @dependencies
  None. @newpage
*/
extern locClientStatusEnumType locClientSupportMsgCheck(
     locClientHandleType      handle,
     const uint32_t*          msgArray,
     uint32_t                 msgArrayLength,
     uint64_t*                supportedMsg
);

/*=============================================================================
    locClientGetSizeByEventIndId */
/** Gets the size of the event indication structure from a specified ID.

  @param[in]  eventIndId      Event indicator ID.
  @param[out] pEventIndSize   Pointer to the size of the structure.

  @return
  TRUE -- The event ID was found. \n
  FALSE -- Otherwise.

  @dependencies
  None. @newpage
*/
extern bool locClientGetSizeByEventIndId(
  uint32_t eventIndId,
  size_t *pEventIndSize);


/*=============================================================================
    locClientGetSizeByRespIndId */
/** Gets the size of the response indication structure from a specified ID.

  @param[in]  respIndId      Response indicator ID.
  @param[out] pRespIndSize   Pointer to the size of the structure.

  @return
  TRUE -- The response ID was found. \n
  FALSE -- Otherwise.

  @dependencies
  None.
*/
extern bool locClientGetSizeByRespIndId(
  uint32_t respIndId,
  size_t *pRespIndSize);

/** locClientRegisterEventMask
 *  @brief registers the event mask with loc service
 *  @param [in] clientHandle
 *  @param [in] eventRegMask
 *  @return true if indication was validated; else false */

extern bool locClientRegisterEventMask(
    locClientHandleType clientHandle,
    locClientEventMaskType eventRegMask);

/*=============================================================================*/
/** @} */ /* end_addtogroup operation_functions */

#ifdef __cplusplus
}
#endif

#endif /* LOC_API_V02_CLIENT_H*/
