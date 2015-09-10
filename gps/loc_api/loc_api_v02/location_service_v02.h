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
#ifndef LOC_SERVICE_02_H
#define LOC_SERVICE_02_H
/**
  @file location_service_v02.h

  @brief This is the public header file which defines the loc service Data structures.

  This header file defines the types and structures that were defined in
  loc. It contains the constant values defined, enums, structures,
  messages, and service message IDs (in that order) Structures that were
  defined in the IDL as messages contain mandatory elements, optional
  elements, a combination of mandatory and optional elements (mandatory
  always come before optionals in the structure), or nothing (null message)

  An optional element in a message is preceded by a uint8_t value that must be
  set to true if the element is going to be included. When decoding a received
  message, the uint8_t values will be set to true or false by the decode
  routine, and should be checked before accessing the values that they
  correspond to.

  Variable sized arrays are defined as static sized arrays with an unsigned
  integer (32 bit) preceding it that must be set to the number of elements
  in the array that are valid. For Example:

  uint32_t test_opaque_len;
  uint8_t test_opaque[16];

  If only 4 elements are added to test_opaque[] then test_opaque_len must be
  set to 4 before sending the message.  When decoding, the _len value is set
  by the decode routine and should be checked so that the correct number of
  elements in the array will be accessed.

*/
/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*
 *THIS IS AN AUTO GENERATED FILE. DO NOT ALTER IN ANY WAY
 *====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/* This file was generated with Tool version 6.14.2
   It was generated on: Fri Nov  7 2014 (Spin 0)
   From IDL File: location_service_v02.idl */

/** @defgroup loc_qmi_consts Constant values defined in the IDL */
/** @defgroup loc_qmi_msg_ids Constant values for QMI message IDs */
/** @defgroup loc_qmi_enums Enumerated types used in QMI messages */
/** @defgroup loc_qmi_messages Structures sent as QMI messages */
/** @defgroup loc_qmi_aggregates Aggregate types used in QMI messages */
/** @defgroup loc_qmi_accessor Accessor for QMI service object */
/** @defgroup loc_qmi_version Constant values for versioning information */

#include <stdint.h>
#include "qmi_idl_lib.h"
#include "common_v01.h"


#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup loc_qmi_version
    @{
  */
/** Major Version Number of the IDL used to generate this file */
#define LOC_V02_IDL_MAJOR_VERS 0x02
/** Revision Number of the IDL used to generate this file */
#define LOC_V02_IDL_MINOR_VERS 0x23
/** Major Version Number of the qmi_idl_compiler used to generate this file */
#define LOC_V02_IDL_TOOL_VERS 0x06
/** Maximum Defined Message ID */
#define LOC_V02_MAX_MESSAGE_ID 0x0091
/**
    @}
  */


/** @addtogroup loc_qmi_consts
    @{
  */

/**  Maximum string length for the Provider field in the application ID.  */
#define QMI_LOC_MAX_APP_ID_PROVIDER_LENGTH_V02 24

/**  Maximum string length for the Name field in the application ID.  */
#define QMI_LOC_MAX_APP_ID_NAME_LENGTH_V02 32

/**  Maximum string length for the Version field in the application ID.  */
#define QMI_LOC_MAX_APP_ID_VERSION_LENGTH_V02 8

/**  Maximum length of the list containing the SVs that were used to generate
     a position report.  */
#define QMI_LOC_MAX_SV_USED_LIST_LENGTH_V02 80

/**  Maximum number of satellites in the satellite report.  */
#define QMI_LOC_SV_INFO_LIST_MAX_SIZE_V02 80

/**  Maximum NMEA string length.  */
#define QMI_LOC_NMEA_STRING_MAX_LENGTH_V02 200

/**  Maximum length of the requestor ID string.  */
#define QMI_LOC_NI_MAX_REQUESTOR_ID_LENGTH_V02 200

/**  Session ID byte length.  */
#define QMI_LOC_NI_SUPL_SLP_SESSION_ID_BYTE_LENGTH_V02 4

/**  Maximum client name length allowed.  */
#define QMI_LOC_NI_MAX_CLIENT_NAME_LENGTH_V02 64

/**  Maximum URL length accepted by the location engine.  */
#define QMI_LOC_MAX_SERVER_ADDR_LENGTH_V02 255

/**  IPv6 address length in bytes.  */
#define QMI_LOC_IPV6_ADDR_LENGTH_V02 8

/**  SUPL hash length.  */
#define QMI_LOC_NI_SUPL_HASH_LENGTH_V02 8

/**  Maximum client address length allowed.  */
#define QMI_LOC_NI_MAX_EXT_CLIENT_ADDRESS_V02 20

/**  Maximum codeword length allowed.  */
#define QMI_LOC_NI_CODEWORD_MAX_LENGTH_V02 20

/**  Maximum number of NTP Servers sent out with this event. */
#define QMI_LOC_MAX_NTP_SERVERS_V02 3

/**  Maximum number of predicted orbits servers supported in the location
     engine.  */
#define QMI_LOC_MAX_PREDICTED_ORBITS_SERVERS_V02 3

/**  Maximum length of the list, where each element of the list contains the
     continuous range of Geofences that were breached at a given position.  */
#define QMI_LOC_MAX_GEOFENCE_ID_CONTINUOUS_LIST_LENGTH_V02 80

/**  Maximum length of the list that contains a discrete number Geofences that
     were breached at a given position.  */
#define QMI_LOC_MAX_GEOFENCE_ID_DISCRETE_LIST_LENGTH_V02 80

/**  Maximum length that can be injected.   */
#define QMI_LOC_MAX_GDT_PATH_LEN_V02 255

/**  Maximum GNSS Measurement Engine Firmware Version String length.  */
#define QMI_LOC_GNSS_ME_VERSION_STRING_MAX_LENGTH_V02 127

/**  Maximum GNSS Measurement Engine Hosted Software Version String length.  */
#define QMI_LOC_GNSS_HOSTED_SW_VERSION_STRING_MAX_LENGTH_V02 127

/**  Maximum GNSS Measurement Engine Full Version String length.  */
#define QMI_LOC_GNSS_SW_VERSION_STRING_MAX_LENGTH_V02 255

/**  Maximum part length that can be injected. The client should
     also look at the maxPartSize field in the predicted orbits injection
     request indication and pick the minimum of the two.  */
#define QMI_LOC_MAX_PREDICTED_ORBITS_PART_LEN_V02 1024

/**  Maximum length of the delete SV information list  */
#define QMI_LOC_DELETE_MAX_SV_INFO_LENGTH_V02 128

/**  Maximum length of the Delete BDS SV Information list.  */
#define QMI_LOC_DELETE_MAX_BDS_SV_INFO_LENGTH_V02 37

/**  MAC address length in bytes.  */
#define QMI_LOC_WIFI_MAC_ADDR_LENGTH_V02 6

/**  Wi-Fi SSID string maximum length.   */
#define QMI_LOC_MAX_WIFI_AP_SSID_STR_LENGTH_V02 32

/**  Maximum number of APs that the sender can report.  */
#define QMI_LOC_WIFI_MAX_REPORTED_APS_PER_MSG_V02 50

/**  Maximum number of samples that can be injected in a TLV.  */
#define QMI_LOC_SENSOR_DATA_MAX_SAMPLES_V02 50

/**  Maximum APN string length allowed.  */
#define QMI_LOC_MAX_APN_NAME_LENGTH_V02 100

/**  Maximum APN profiles supported. */
#define QMI_LOC_MAX_APN_PROFILES_V02 6

/**  Maximum length of the SUPL certificate. */
#define QMI_LOC_MAX_SUPL_CERT_LENGTH_V02 2000

/**  Maximum number of motion states used by the Geofence engine.  */
#define QMI_LOC_GEOFENCE_MAX_MOTION_STATES_V02 20

/**  Maximum length of the network-initiated Geofence ID
     list.  */
#define QMI_LOC_MAX_NI_GEOFENCE_ID_LIST_LENGTH_V02 16

/**  Maximum value of WDMA frequency for injection of WCDMA cell
     information.  */
#define QMI_LOC_MAX_WCDMA_FREQ_V02 16383

/**  Maximum value of PSC for injection of WCDMA cell information.  */
#define QMI_LOC_MAX_WCDMA_PSC_V02 511

/**  Maximum value of TDSCDMA frequency for injection of TDSCDMA cell
     information.  */
#define QMI_LOC_MAX_TDSCDMA_FREQ_V02 16383

/**  Maximum length of the injected network-initiated message.  */
#define QMI_LOC_MAX_INJECTED_NETWORK_INITIATED_MESSAGE_LENGTH_V02 1024

/**  Maximum number of entries returned from a batch in each indication.  */
#define QMI_LOC_READ_FROM_BATCH_MAX_SIZE_V02 5

/**  Maximum number of vehicle sensor samples that can be injected.  */
#define QMI_LOC_VEHICLE_SENSOR_DATA_MAX_SAMPLES_V02 65

/**  Maximum number of axes that can be provided in each sample.  */
#define QMI_LOC_VEHICLE_SENSOR_DATA_MAX_AXES_V02 3

/**  Maximum number of measurements from an odometer.  */
#define QMI_LOC_VEHICLE_ODOMETRY_MAX_MEASUREMENTS_V02 3
#define QMI_LOC_MEAS_STATUS_DONT_USE_BITS_V02 0xFFC0000000000000

/**  Maximum number of satellites in a measurement block for a given system.  */
#define QMI_LOC_SV_MEAS_LIST_MAX_SIZE_V02 16
#define QMI_LOC_SV_POLY_VELOCITY_COEF_SIZE_V02 12
#define QMI_LOC_SV_POLY_XYZ_0_TH_ORDER_COEFF_SIZE_V02 3
#define QMI_LOC_SV_POLY_XYZ_N_TH_ORDER_COEFF_SIZE_V02 9
#define QMI_LOC_SV_POLY_SV_CLKBIAS_COEFF_SIZE_V02 4

/**  IBeacon string maximum length.   */
#define QMI_LOC_MAX_IBEACON_UUID_STR_LENGTH_V02 32

/**  Wi-Fi area ID list length.  */
#define QMI_LOC_WIFI_AREA_ID_LIST_LENGTH_V02 20

/**  Cell ID list length.   */
#define QMI_LOC_CELL_ID_LIST_LENGTH_V02 20

/**   IBeacon list length.   */
#define QMI_LOC_IBEACON_LIST_LENGTH_V02 20

/**  Maximum length that can be injected.   */
#define QMI_LOC_MAX_GTP_WWAN_CLIENT_DOWNLOADED_DATA_LEN_V02 512
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Response Message; Generic response definition. This message is used to tell
                    clients whether their message was accepted for further
                    processing or rejected. */
typedef struct {

  /* Mandatory */
  /*  Result Code */
  qmi_response_type_v01 resp;
}qmiLocGenRespMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Informs the service of the minor revision of the interface
                    definition that the control point implements. */
typedef struct {

  /* Mandatory */
  /*  Revision */
  uint32_t revision;
  /**<   Revision that the control point is using. */
}qmiLocInformClientRevisionReqMsgT_v02;  /* Message */
/**
    @}
  */

typedef uint64_t qmiLocEventRegMaskT_v02;
#define QMI_LOC_EVENT_MASK_POSITION_REPORT_V02 ((qmiLocEventRegMaskT_v02)0x00000001ull) /**<  The control point must enable this mask to receive position report
       event indications.  */
#define QMI_LOC_EVENT_MASK_GNSS_SV_INFO_V02 ((qmiLocEventRegMaskT_v02)0x00000002ull) /**<  The control point must enable this mask to receive satellite report
       event indications. These reports are sent at a 1 Hz rate.  */
#define QMI_LOC_EVENT_MASK_NMEA_V02 ((qmiLocEventRegMaskT_v02)0x00000004ull) /**<  The control point must enable this mask to receive NMEA reports for
       position and satellites in view. The report is at a 1 Hz rate.  */
#define QMI_LOC_EVENT_MASK_NI_NOTIFY_VERIFY_REQ_V02 ((qmiLocEventRegMaskT_v02)0x00000008ull) /**<  The control point must enable this mask to receive NI Notify/Verify request
       event indications.  */
#define QMI_LOC_EVENT_MASK_INJECT_TIME_REQ_V02 ((qmiLocEventRegMaskT_v02)0x00000010ull) /**<  The control point must enable this mask to receive time injection request
       event indications.  */
#define QMI_LOC_EVENT_MASK_INJECT_PREDICTED_ORBITS_REQ_V02 ((qmiLocEventRegMaskT_v02)0x00000020ull) /**<  The control point must enable this mask to receive predicted orbits request
       event indications.  */
#define QMI_LOC_EVENT_MASK_INJECT_POSITION_REQ_V02 ((qmiLocEventRegMaskT_v02)0x00000040ull) /**<  The control point must enable this mask to receive position injection request
       event indications.  */
#define QMI_LOC_EVENT_MASK_ENGINE_STATE_V02 ((qmiLocEventRegMaskT_v02)0x00000080ull) /**<  The control point must enable this mask to receive engine state report
       event indications.  */
#define QMI_LOC_EVENT_MASK_FIX_SESSION_STATE_V02 ((qmiLocEventRegMaskT_v02)0x00000100ull) /**<  The control point must enable this mask to receive fix session status report
       event indications.  */
#define QMI_LOC_EVENT_MASK_WIFI_REQ_V02 ((qmiLocEventRegMaskT_v02)0x00000200ull) /**<  The control point must enable this mask to receive Wi-Fi position request
       event indications.  */
#define QMI_LOC_EVENT_MASK_SENSOR_STREAMING_READY_STATUS_V02 ((qmiLocEventRegMaskT_v02)0x00000400ull) /**<  The control point must enable this mask to receive notifications from the
       location engine indicating its readiness to accept data from the
       sensors (accelerometer, gyroscope, etc.).  */
#define QMI_LOC_EVENT_MASK_TIME_SYNC_REQ_V02 ((qmiLocEventRegMaskT_v02)0x00000800ull) /**<  The control point must enable this mask to receive time sync requests
       from the GPS engine. Time sync enables the GPS engine to synchronize
       its clock with the sensor processor's clock.  */
#define QMI_LOC_EVENT_MASK_SET_SPI_STREAMING_REPORT_V02 ((qmiLocEventRegMaskT_v02)0x00001000ull) /**<  The control point must enable this mask to receive Stationary Position
       Indicator (SPI) streaming report indications.  */
#define QMI_LOC_EVENT_MASK_LOCATION_SERVER_CONNECTION_REQ_V02 ((qmiLocEventRegMaskT_v02)0x00002000ull) /**<  The control point must enable this mask to receive location server
       requests. These requests are generated when the service wishes to
       establish a connection with a location server. */
#define QMI_LOC_EVENT_MASK_NI_GEOFENCE_NOTIFICATION_V02 ((qmiLocEventRegMaskT_v02)0x00004000ull) /**<  The control point must enable this mask to receive notifications
       related to network-initiated Geofences. These events notify the client
       when a network-initiated Geofence is added, deleted, or edited.  */
#define QMI_LOC_EVENT_MASK_GEOFENCE_GEN_ALERT_V02 ((qmiLocEventRegMaskT_v02)0x00008000ull) /**<  The control point must enable this mask to receive Geofence alerts.
       These alerts are generated to inform the client of the changes that may
       affect a Geofence, e.g., if GPS is turned off or if the network is
       unavailable.  */
#define QMI_LOC_EVENT_MASK_GEOFENCE_BREACH_NOTIFICATION_V02 ((qmiLocEventRegMaskT_v02)0x00010000ull) /**<  The control point must enable this mask to receive notifications when
       a Geofence is breached. These events are generated when a UE enters
       or leaves the perimeter of a Geofence. This breach report is for a single
       Geofence . */
#define QMI_LOC_EVENT_MASK_PEDOMETER_CONTROL_V02 ((qmiLocEventRegMaskT_v02)0x00020000ull) /**<  The control point must enable this mask to register for pedometer
       control requests from the location engine. The location engine sends
       this event to control the injection of pedometer reports.  */
#define QMI_LOC_EVENT_MASK_MOTION_DATA_CONTROL_V02 ((qmiLocEventRegMaskT_v02)0x00040000ull) /**<  The control point must enable this mask to register for motion data
       control requests from the location engine. The location engine sends
       this event to control the injection of motion data.  */
#define QMI_LOC_EVENT_MASK_BATCH_FULL_NOTIFICATION_V02 ((qmiLocEventRegMaskT_v02)0x00080000ull) /**<  The control point must enable this mask to receive notification when
       a batch is full. The location engine sends this event to notify of Batch Full
       for ongoing batching session.  */
#define QMI_LOC_EVENT_MASK_LIVE_BATCHED_POSITION_REPORT_V02 ((qmiLocEventRegMaskT_v02)0x00100000ull) /**<  The control point must enable this mask to receive position report
       indications along with an ongoing batching session. The location engine sends
       this event to notify the batched position report while a batching session
       is ongoing.  */
#define QMI_LOC_EVENT_MASK_INJECT_WIFI_AP_DATA_REQ_V02 ((qmiLocEventRegMaskT_v02)0x00200000ull) /**<  The control point must enable this mask to receive Wi-Fi AP data inject request
       event indications.  */
#define QMI_LOC_EVENT_MASK_GEOFENCE_BATCH_BREACH_NOTIFICATION_V02 ((qmiLocEventRegMaskT_v02)0x00400000ull) /**<  The control point must enable this mask to receive notifications when
       a Geofence is breached. These events are generated when a UE enters
       or leaves the perimeter of a Geofence. This breach notification is for
       multiple Geofences. Breaches from multiple Geofences are all batched and
       sent in the same notification .    */
#define QMI_LOC_EVENT_MASK_VEHICLE_DATA_READY_STATUS_V02 ((qmiLocEventRegMaskT_v02)0x00800000ull) /**<  The control point must enable this mask to receive notifications from the
       location engine indicating its readiness to accept vehicle data (vehicle
       accelerometer, vehicle angular rate, vehicle odometry, etc.). */
#define QMI_LOC_EVENT_MASK_GNSS_MEASUREMENT_REPORT_V02 ((qmiLocEventRegMaskT_v02)0x01000000ull) /**<  The control point must enable this mask to receive system clock and satellite
       measurement report events (system clock, SV time, Doppler, etc.). Reports are
       generated only for the GNSS satellite constellations that are enabled using
       QMI_LOC_SET_GNSS_CONSTELL_REPORT_CONFIG.   */
#define QMI_LOC_EVENT_MASK_GNSS_SV_POLYNOMIAL_REPORT_V02 ((qmiLocEventRegMaskT_v02)0x02000000ull) /**<  The control point must enable this mask to receive satellite position
        reports as polynomials. Reports are generated only for the GNSS satellite
        constellations that are enabled using QMI_LOC_SET_GNSS_CONSTELL_REPORT_CONFIG.  */
#define QMI_LOC_EVENT_MASK_GEOFENCE_PROXIMITY_NOTIFICATION_V02 ((qmiLocEventRegMaskT_v02)0x04000000ull) /**<  The control point must enable this mask to receive notifications when a Geofence proximity is entered
  and exited.  The proximity of a geofence may be due to different contexts . These contexts are identified
  using the context id in this indication. The context of a geofence may contain Wifi area ID lists, IBeacon lists,
  Cell-Id list etc.    */
#define QMI_LOC_EVENT_MASK_GDT_UPLOAD_BEGIN_REQ_V02 ((qmiLocEventRegMaskT_v02)0x08000000ull) /**<  The control point must enable this mask to receive GDT (Generic Data Transport )
        session begin request event indications.  */
#define QMI_LOC_EVENT_MASK_GDT_UPLOAD_END_REQ_V02 ((qmiLocEventRegMaskT_v02)0x10000000ull) /**<  The control point must enable this mask to receive GDT (Generic Data Transport )
        session end request
        event indications.  */
/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Used by the control point to register for events from the
                    location subsystem. */
typedef struct {

  /* Mandatory */
  /*  Event Registration Mask */
  qmiLocEventRegMaskT_v02 eventRegMask;
  /**<   Specifies the events that the control point is interested in receiving.
 Valid bitmasks:
      - QMI_LOC_EVENT_MASK_POSITION_REPORT (0x00000001) --  The control point must enable this mask to receive position report
       event indications.
      - QMI_LOC_EVENT_MASK_GNSS_SV_INFO (0x00000002) --  The control point must enable this mask to receive satellite report
       event indications. These reports are sent at a 1 Hz rate.
      - QMI_LOC_EVENT_MASK_NMEA (0x00000004) --  The control point must enable this mask to receive NMEA reports for
       position and satellites in view. The report is at a 1 Hz rate.
      - QMI_LOC_EVENT_MASK_NI_NOTIFY_VERIFY_REQ (0x00000008) --  The control point must enable this mask to receive NI Notify/Verify request
       event indications.
      - QMI_LOC_EVENT_MASK_INJECT_TIME_REQ (0x00000010) --  The control point must enable this mask to receive time injection request
       event indications.
      - QMI_LOC_EVENT_MASK_INJECT_PREDICTED_ORBITS_REQ (0x00000020) --  The control point must enable this mask to receive predicted orbits request
       event indications.
      - QMI_LOC_EVENT_MASK_INJECT_POSITION_REQ (0x00000040) --  The control point must enable this mask to receive position injection request
       event indications.
      - QMI_LOC_EVENT_MASK_ENGINE_STATE (0x00000080) --  The control point must enable this mask to receive engine state report
       event indications.
      - QMI_LOC_EVENT_MASK_FIX_SESSION_STATE (0x00000100) --  The control point must enable this mask to receive fix session status report
       event indications.
      - QMI_LOC_EVENT_MASK_WIFI_REQ (0x00000200) --  The control point must enable this mask to receive Wi-Fi position request
       event indications.
      - QMI_LOC_EVENT_MASK_SENSOR_STREAMING_READY_STATUS (0x00000400) --  The control point must enable this mask to receive notifications from the
       location engine indicating its readiness to accept data from the
       sensors (accelerometer, gyroscope, etc.).
      - QMI_LOC_EVENT_MASK_TIME_SYNC_REQ (0x00000800) --  The control point must enable this mask to receive time sync requests
       from the GPS engine. Time sync enables the GPS engine to synchronize
       its clock with the sensor processor's clock.
      - QMI_LOC_EVENT_MASK_SET_SPI_STREAMING_REPORT (0x00001000) --  The control point must enable this mask to receive Stationary Position
       Indicator (SPI) streaming report indications.
      - QMI_LOC_EVENT_MASK_LOCATION_SERVER_CONNECTION_REQ (0x00002000) --  The control point must enable this mask to receive location server
       requests. These requests are generated when the service wishes to
       establish a connection with a location server.
      - QMI_LOC_EVENT_MASK_NI_GEOFENCE_NOTIFICATION (0x00004000) --  The control point must enable this mask to receive notifications
       related to network-initiated Geofences. These events notify the client
       when a network-initiated Geofence is added, deleted, or edited.
      - QMI_LOC_EVENT_MASK_GEOFENCE_GEN_ALERT (0x00008000) --  The control point must enable this mask to receive Geofence alerts.
       These alerts are generated to inform the client of the changes that may
       affect a Geofence, e.g., if GPS is turned off or if the network is
       unavailable.
      - QMI_LOC_EVENT_MASK_GEOFENCE_BREACH_NOTIFICATION (0x00010000) --  The control point must enable this mask to receive notifications when
       a Geofence is breached. These events are generated when a UE enters
       or leaves the perimeter of a Geofence. This breach report is for a single
       Geofence .
      - QMI_LOC_EVENT_MASK_PEDOMETER_CONTROL (0x00020000) --  The control point must enable this mask to register for pedometer
       control requests from the location engine. The location engine sends
       this event to control the injection of pedometer reports.
      - QMI_LOC_EVENT_MASK_MOTION_DATA_CONTROL (0x00040000) --  The control point must enable this mask to register for motion data
       control requests from the location engine. The location engine sends
       this event to control the injection of motion data.
      - QMI_LOC_EVENT_MASK_BATCH_FULL_NOTIFICATION (0x00080000) --  The control point must enable this mask to receive notification when
       a batch is full. The location engine sends this event to notify of Batch Full
       for ongoing batching session.
      - QMI_LOC_EVENT_MASK_LIVE_BATCHED_POSITION_REPORT (0x00100000) --  The control point must enable this mask to receive position report
       indications along with an ongoing batching session. The location engine sends
       this event to notify the batched position report while a batching session
       is ongoing.
      - QMI_LOC_EVENT_MASK_INJECT_WIFI_AP_DATA_REQ (0x00200000) --  The control point must enable this mask to receive Wi-Fi AP data inject request
       event indications.
      - QMI_LOC_EVENT_MASK_GEOFENCE_BATCH_BREACH_NOTIFICATION (0x00400000) --  The control point must enable this mask to receive notifications when
       a Geofence is breached. These events are generated when a UE enters
       or leaves the perimeter of a Geofence. This breach notification is for
       multiple Geofences. Breaches from multiple Geofences are all batched and
       sent in the same notification .
      - QMI_LOC_EVENT_MASK_VEHICLE_DATA_READY_STATUS (0x00800000) --  The control point must enable this mask to receive notifications from the
       location engine indicating its readiness to accept vehicle data (vehicle
       accelerometer, vehicle angular rate, vehicle odometry, etc.).
      - QMI_LOC_EVENT_MASK_GNSS_MEASUREMENT_REPORT (0x01000000) --  The control point must enable this mask to receive system clock and satellite
       measurement report events (system clock, SV time, Doppler, etc.). Reports are
       generated only for the GNSS satellite constellations that are enabled using
       QMI_LOC_SET_GNSS_CONSTELL_REPORT_CONFIG.
      - QMI_LOC_EVENT_MASK_GNSS_SV_POLYNOMIAL_REPORT (0x02000000) --  The control point must enable this mask to receive satellite position
        reports as polynomials. Reports are generated only for the GNSS satellite
        constellations that are enabled using QMI_LOC_SET_GNSS_CONSTELL_REPORT_CONFIG.
      - QMI_LOC_EVENT_MASK_GEOFENCE_PROXIMITY_NOTIFICATION (0x04000000) --  The control point must enable this mask to receive notifications when a Geofence proximity is entered
  and exited.  The proximity of a geofence may be due to different contexts . These contexts are identified
  using the context id in this indication. The context of a geofence may contain Wifi area ID lists, IBeacon lists,
  Cell-Id list etc.
      - QMI_LOC_EVENT_MASK_GDT_UPLOAD_BEGIN_REQ (0x08000000) --  The control point must enable this mask to receive GDT (Generic Data Transport )
        session begin request event indications.
      - QMI_LOC_EVENT_MASK_GDT_UPLOAD_END_REQ (0x10000000) --  The control point must enable this mask to receive GDT (Generic Data Transport )
        session end request
        event indications.

 Multiple events can be registered by ORing the individual masks and
 sending them in this TLV. All unused bits in this mask must be set to 0.
 */
}qmiLocRegEventsReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCFIXRECURRENCEENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_RECURRENCE_PERIODIC_V02 = 1, /**<  Request periodic position fixes  */
  eQMI_LOC_RECURRENCE_SINGLE_V02 = 2, /**<  Request a single position fix  */
  QMILOCFIXRECURRENCEENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocFixRecurrenceEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCACCURACYLEVELENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_ACCURACY_LOW_V02 = 1, /**<  Low accuracy  */
  eQMI_LOC_ACCURACY_MED_V02 = 2, /**<  Medium accuracy  */
  eQMI_LOC_ACCURACY_HIGH_V02 = 3, /**<  High accuracy  */
  QMILOCACCURACYLEVELENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocAccuracyLevelEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCINTERMEDIATEREPORTSTATEENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_INTERMEDIATE_REPORTS_ON_V02 = 1, /**<  Intermediate reports are turned on  */
  eQMI_LOC_INTERMEDIATE_REPORTS_OFF_V02 = 2, /**<  Intermediate reports are turned off  */
  QMILOCINTERMEDIATEREPORTSTATEENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocIntermediateReportStateEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCCONFIGINCLUDEALTITUDEASSUMEDINGNSSSVINFOENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_ALTITUDE_ASSUMED_IN_GNSS_SV_INFO_ENABLED_V02 = 1, /**<  Enable Altitude Assumed information in GNSS SV Info Event.  */
  eQMI_LOC_ALTITUDE_ASSUMED_IN_GNSS_SV_INFO_DISABLED_V02 = 2, /**<  Disable Altitude Assumed information in GNSS SV Info Event.  */
  QMILOCCONFIGINCLUDEALTITUDEASSUMEDINGNSSSVINFOENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocConfigIncludeAltitudeAssumedInGnssSvInfoEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  char applicationProvider[QMI_LOC_MAX_APP_ID_PROVIDER_LENGTH_V02 + 1];
  /**<   Application provider. */

  char applicationName[QMI_LOC_MAX_APP_ID_NAME_LENGTH_V02 + 1];
  /**<   Application name. */

  uint8_t applicationVersion_valid;
  /**<   Specifies whether the application version string contains
        a valid value: \begin{itemize1}
       \item    0x00 (FALSE) -- Application version string is invalid
       \item    0x01 (TRUE) -- Application version string is valid
       \vspace{-0.18in} \end{itemize1} */

  char applicationVersion[QMI_LOC_MAX_APP_ID_VERSION_LENGTH_V02 + 1];
  /**<   Application version. */
}qmiLocApplicationIdStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Used by the control point to initiate a GPS session. */
typedef struct {

  /* Mandatory */
  /*  Session ID */
  uint8_t sessionId;
  /**<   ID of the session as identified by the control point. The session ID
       is reported back in the position reports. The control point must
       specify the same session ID in the QMI_LOC_STOP_REQ message. \n
       - Range: 0 to 255
  */

  /* Optional */
  /*  Recurrence Type */
  uint8_t fixRecurrence_valid;  /**< Must be set to true if fixRecurrence is being passed */
  qmiLocFixRecurrenceEnumT_v02 fixRecurrence;
  /**<   Specifies the type of session in which the control point is interested.
 If this TLV is not specified, recurrence defaults to SINGLE.

 Valid values: \n
      - eQMI_LOC_RECURRENCE_PERIODIC (1) --  Request periodic position fixes
      - eQMI_LOC_RECURRENCE_SINGLE (2) --  Request a single position fix
 */

  /* Optional */
  /*  Horizontal Accuracy */
  uint8_t horizontalAccuracyLevel_valid;  /**< Must be set to true if horizontalAccuracyLevel is being passed */
  qmiLocAccuracyLevelEnumT_v02 horizontalAccuracyLevel;
  /**<   Specifies the horizontal accuracy level required by the control point.
 If not specified, accuracy defaults to LOW.

 Valid values: \n
      - eQMI_LOC_ACCURACY_LOW (1) --  Low accuracy
      - eQMI_LOC_ACCURACY_MED (2) --  Medium accuracy
      - eQMI_LOC_ACCURACY_HIGH (3) --  High accuracy
 */

  /* Optional */
  /*  Enable/Disable Intermediate Reports */
  uint8_t intermediateReportState_valid;  /**< Must be set to true if intermediateReportState is being passed */
  qmiLocIntermediateReportStateEnumT_v02 intermediateReportState;
  /**<   Specifies if the control point is interested in receiving intermediate
 reports. The control point must explicitly set this field to OFF if it
 does not wish to receive intermediate position reports. Intermediate
 position reports are generated at 1 Hz and are ON by default. If
 intermediate reports are turned ON, the client receives position reports
 even if the accuracy criteria are not met. The status in such a position
 report is set to IN_PROGRESS in order for the control point to identify
 intermediate reports.

 Valid values: \n
      - eQMI_LOC_INTERMEDIATE_REPORTS_ON (1) --  Intermediate reports are turned on
      - eQMI_LOC_INTERMEDIATE_REPORTS_OFF (2) --  Intermediate reports are turned off
 */

  /* Optional */
  /*  Minimum Interval Between Position Reports */
  uint8_t minInterval_valid;  /**< Must be set to true if minInterval is being passed */
  uint32_t minInterval;
  /**<   Minimum time interval, specified by the control point, that must elapse between
       position reports. \n
       - Units: Milliseconds \n
       - Default: 1000 ms
  */

  /* Optional */
  /*  ID of the Application that Sent this Request */
  uint8_t applicationId_valid;  /**< Must be set to true if applicationId is being passed */
  qmiLocApplicationIdStructT_v02 applicationId;
  /**<   \n Application provider, name, and version.*/

  /* Optional */
  /*  Configuration for Altitude Assumed Info in GNSS SV Info Event */
  uint8_t configAltitudeAssumed_valid;  /**< Must be set to true if configAltitudeAssumed is being passed */
  qmiLocConfigIncludeAltitudeAssumedInGnssSvInfoEnumT_v02 configAltitudeAssumed;
  /**<   Specifies the configuration to include Altitude Assumed information in the GNSS SV Info Event.
 When enabled, an additional GNSS SV Info event indication is sent to the control
 point that also includes the altitude assumed information.

 If not specified, the configuration defaults to ENABLED.

 Valid values: \n
      - eQMI_LOC_ALTITUDE_ASSUMED_IN_GNSS_SV_INFO_ENABLED (1) --  Enable Altitude Assumed information in GNSS SV Info Event.
      - eQMI_LOC_ALTITUDE_ASSUMED_IN_GNSS_SV_INFO_DISABLED (2) --  Disable Altitude Assumed information in GNSS SV Info Event.
 */
}qmiLocStartReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Used by the control point to stop a GPS session. */
typedef struct {

  /* Mandatory */
  /*   Session ID */
  uint8_t sessionId;
  /**<   ID of the session that was specified in the Start request
       (QMI_LOC_START_REQ).\n
       - Range: 0 to 255 */
}qmiLocStopReqMsgT_v02;  /* Message */
/**
    @}
  */

typedef uint32_t qmiLocPosTechMaskT_v02;
#define QMI_LOC_POS_TECH_MASK_SATELLITE_V02 ((qmiLocPosTechMaskT_v02)0x00000001) /**<  Satellites were used to generate the fix  */
#define QMI_LOC_POS_TECH_MASK_CELLID_V02 ((qmiLocPosTechMaskT_v02)0x00000002) /**<  Cell towers were used to generate the fix  */
#define QMI_LOC_POS_TECH_MASK_WIFI_V02 ((qmiLocPosTechMaskT_v02)0x00000004) /**<  Wi-Fi access points were used to generate the fix  */
#define QMI_LOC_POS_TECH_MASK_SENSORS_V02 ((qmiLocPosTechMaskT_v02)0x00000008) /**<  Sensors were used to generate the fix  */
#define QMI_LOC_POS_TECH_MASK_REFERENCE_LOCATION_V02 ((qmiLocPosTechMaskT_v02)0x00000010) /**<  Reference Location was used to generate the fix  */
#define QMI_LOC_POS_TECH_MASK_INJECTED_COARSE_POSITION_V02 ((qmiLocPosTechMaskT_v02)0x00000020) /**<  Coarse position injected into the location engine was used to
        generate the fix  */
#define QMI_LOC_POS_TECH_MASK_AFLT_V02 ((qmiLocPosTechMaskT_v02)0x00000040) /**<  AFLT was used to generate the fix  */
#define QMI_LOC_POS_TECH_MASK_HYBRID_V02 ((qmiLocPosTechMaskT_v02)0x00000080) /**<  GNSS and network-provided measurements were used to
        generate the fix  */
/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCSESSIONSTATUSENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_SESS_STATUS_SUCCESS_V02 = 0, /**<  Session was successful  */
  eQMI_LOC_SESS_STATUS_IN_PROGRESS_V02 = 1, /**<  Session is still in progress; further position reports will be generated
       until either the fix criteria specified by the client are met or the
       client response timeout occurs  */
  eQMI_LOC_SESS_STATUS_GENERAL_FAILURE_V02 = 2, /**<  Session failed  */
  eQMI_LOC_SESS_STATUS_TIMEOUT_V02 = 3, /**<  Fix request failed because the session timed out  */
  eQMI_LOC_SESS_STATUS_USER_END_V02 = 4, /**<  Fix request failed because the session was ended by the user  */
  eQMI_LOC_SESS_STATUS_BAD_PARAMETER_V02 = 5, /**<  Fix request failed due to bad parameters in the request  */
  eQMI_LOC_SESS_STATUS_PHONE_OFFLINE_V02 = 6, /**<  Fix request failed because the phone is offline  */
  eQMI_LOC_SESS_STATUS_ENGINE_LOCKED_V02 = 7, /**<  Fix request failed because the engine is locked  */
  QMILOCSESSIONSTATUSENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocSessionStatusEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  uint16_t gpsWeek;
  /**<   Current GPS week as calculated from midnight, Jan. 6, 1980. \n
       - Units: Weeks */

  uint32_t gpsTimeOfWeekMs;
  /**<   Amount of time into the current GPS week. \n
       - Units: Milliseconds */
}qmiLocGPSTimeStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  float PDOP;
  /**<   Position dilution of precision.
       \begin{itemize1}
       \item    Range: 1 (highest accuracy) to 50 (lowest accuracy)
       \item    PDOP = square root of (HDOP^2 + VDOP^2)
       \vspace{-0.18in} \end{itemize1} */

  float HDOP;
  /**<   Horizontal dilution of precision.
       \begin{itemize1}
       \item    Range: 1 (highest accuracy) to 50 (lowest accuracy)
       \vspace{-0.18in} \end{itemize1} */

  float VDOP;
  /**<   Vertical dilution of precision.
       \begin{itemize1}
       \item    Range: 1 (highest accuracy) to 50 (lowest accuracy)
       \vspace{-0.18in} \end{itemize1} */
}qmiLocDOPStructT_v02;  /* Type */
/**
    @}
  */

typedef uint32_t qmiLocSensorUsageMaskT_v02;
#define QMI_LOC_SENSOR_MASK_USED_ACCEL_V02 ((qmiLocSensorUsageMaskT_v02)0x00000001) /**<  Bitmask to specify whether an accelerometer was used.  */
#define QMI_LOC_SENSOR_MASK_USED_GYRO_V02 ((qmiLocSensorUsageMaskT_v02)0x00000002) /**<  Bitmask to specify whether a gyroscope was used.  */
typedef uint32_t qmiLocSensorAidedMaskT_v02;
#define QMI_LOC_SENSOR_AIDED_MASK_HEADING_V02 ((qmiLocSensorAidedMaskT_v02)0x00000001) /**<  Bitmask to specify whether a sensor was used to calculate heading.  */
#define QMI_LOC_SENSOR_AIDED_MASK_SPEED_V02 ((qmiLocSensorAidedMaskT_v02)0x00000002) /**<  Bitmask to specify whether a sensor was used to calculate speed.  */
#define QMI_LOC_SENSOR_AIDED_MASK_POSITION_V02 ((qmiLocSensorAidedMaskT_v02)0x00000004) /**<  Bitmask to specify whether a sensor was used to calculate position.  */
#define QMI_LOC_SENSOR_AIDED_MASK_VELOCITY_V02 ((qmiLocSensorAidedMaskT_v02)0x00000008) /**<  Bitmask to specify whether a sensor was used to calculate velocity.  */
/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  qmiLocSensorUsageMaskT_v02 usageMask;
  /**<   Specifies which sensors were used in calculating the position in the
       position report.

       Valid bitmasks: \begin{itemize1}
       \item    0x00000001 -- SENSOR_USED_ ACCEL
       \item    0x00000002 -- SENSOR_USED_ GYRO
       \vspace{-0.18in} \end{itemize1} */

  qmiLocSensorAidedMaskT_v02 aidingIndicatorMask;
  /**<   Specifies which results were aided by sensors.

       Valid bitmasks: \n
         - 0x00000001 -- AIDED_HEADING \n
         - 0x00000002 -- AIDED_SPEED \n
         - 0x00000004 -- AIDED_POSITION \n
         - 0x00000008 -- AIDED_VELOCITY */
}qmiLocSensorUsageIndicatorStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCTIMESOURCEENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_TIME_SRC_INVALID_V02 = 0, /**<  Invalid time.  */
  eQMI_LOC_TIME_SRC_NETWORK_TIME_TRANSFER_V02 = 1, /**<  Time is set by the 1X system  */
  eQMI_LOC_TIME_SRC_NETWORK_TIME_TAGGING_V02 = 2, /**<  Time is set by WCDMA/GSM time tagging (i.e.,
       associating network time with GPS time)  */
  eQMI_LOC_TIME_SRC_EXTERNAL_INPUT_V02 = 3, /**<  Time is set by an external injection  */
  eQMI_LOC_TIME_SRC_TOW_DECODE_V02 = 4, /**<  Time is set after decoding over-the-air GPS navigation data
       from one GPS satellite  */
  eQMI_LOC_TIME_SRC_TOW_CONFIRMED_V02 = 5, /**<  Time is set after decoding over-the-air GPS navigation data
       from multiple satellites  */
  eQMI_LOC_TIME_SRC_TOW_AND_WEEK_CONFIRMED_V02 = 6, /**<  Both time of the week and the GPS week number are known  */
  eQMI_LOC_TIME_SRC_NAV_SOLUTION_V02 = 7, /**<  Time is set by the position engine after the fix is obtained  */
  eQMI_LOC_TIME_SRC_SOLVE_FOR_TIME_V02 = 8, /**<  Time is set by the position engine after performing SFT;
       this is done when the clock time uncertainty is large  */
  eQMI_LOC_TIME_SRC_GLO_TOW_DECODE_V02 = 9, /**<  Time is set after decoding GLO satellites  */
  eQMI_LOC_TIME_SRC_TIME_TRANSFORM_V02 = 10, /**<  Time is set after transforming the GPS to GLO time  */
  eQMI_LOC_TIME_SRC_WCDMA_SLEEP_TIME_TAGGING_V02 = 11, /**<  Time is set by the sleep time tag provided by the WCDMA network  */
  eQMI_LOC_TIME_SRC_GSM_SLEEP_TIME_TAGGING_V02 = 12, /**<  Time is set by the sleep time tag provided by the GSM network  */
  eQMI_LOC_TIME_SRC_UNKNOWN_V02 = 13, /**<  Source of the time is unknown  */
  eQMI_LOC_TIME_SRC_SYSTEM_TIMETICK_V02 = 14, /**<  Time is derived from the system clock (better known as the slow clock);
       GNSS time is maintained irrespective of the GNSS receiver state  */
  eQMI_LOC_TIME_SRC_QZSS_TOW_DECODE_V02 = 15, /**<  Time is set after decoding QZSS satellites  */
  eQMI_LOC_TIME_SRC_BDS_TOW_DECODE_V02 = 16, /**<  Time is set after decoding BDS satellites  */
  QMILOCTIMESOURCEENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocTimeSourceEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCRELIABILITYENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_RELIABILITY_NOT_SET_V02 = 0, /**<  Location reliability is not set  */
  eQMI_LOC_RELIABILITY_VERY_LOW_V02 = 1, /**<  Location reliability is very low; use it at your own risk  */
  eQMI_LOC_RELIABILITY_LOW_V02 = 2, /**<  Location reliability is low; little or no cross-checking is possible  */
  eQMI_LOC_RELIABILITY_MEDIUM_V02 = 3, /**<  Location reliability is medium; limited cross-check passed   */
  eQMI_LOC_RELIABILITY_HIGH_V02 = 4, /**<  Location reliability is high; strong cross-check passed  */
  QMILOCRELIABILITYENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocReliabilityEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Sends the position report to the control point. */
typedef struct {

  /* Mandatory */
  /*   Session Status */
  qmiLocSessionStatusEnumT_v02 sessionStatus;
  /**<   Session status.

 Valid values: \n
      - eQMI_LOC_SESS_STATUS_SUCCESS (0) --  Session was successful
      - eQMI_LOC_SESS_STATUS_IN_PROGRESS (1) --  Session is still in progress; further position reports will be generated
       until either the fix criteria specified by the client are met or the
       client response timeout occurs
      - eQMI_LOC_SESS_STATUS_GENERAL_FAILURE (2) --  Session failed
      - eQMI_LOC_SESS_STATUS_TIMEOUT (3) --  Fix request failed because the session timed out
      - eQMI_LOC_SESS_STATUS_USER_END (4) --  Fix request failed because the session was ended by the user
      - eQMI_LOC_SESS_STATUS_BAD_PARAMETER (5) --  Fix request failed due to bad parameters in the request
      - eQMI_LOC_SESS_STATUS_PHONE_OFFLINE (6) --  Fix request failed because the phone is offline
      - eQMI_LOC_SESS_STATUS_ENGINE_LOCKED (7) --  Fix request failed because the engine is locked
 */

  /* Mandatory */
  /*   Session ID */
  uint8_t sessionId;
  /**<    ID of the session that was specified in the Start request
        QMI_LOC_START_REQ. \n
        - Range: 0 to 255 */

  /* Optional */
  /*  Latitude */
  uint8_t latitude_valid;  /**< Must be set to true if latitude is being passed */
  double latitude;
  /**<   Latitude (specified in WGS84 datum).
       \begin{itemize1}
       \item    Type: Floating point
       \item    Units: Degrees
       \item    Range: -90.0 to 90.0   \begin{itemize1}
         \item    Positive values indicate northern latitude
         \item    Negative values indicate southern latitude
       \vspace{-0.18in} \end{itemize1} \end{itemize1} */

  /* Optional */
  /*   Longitude */
  uint8_t longitude_valid;  /**< Must be set to true if longitude is being passed */
  double longitude;
  /**<   Longitude (specified in WGS84 datum).
       \begin{itemize1}
       \item    Type: Floating point
       \item    Units: Degrees
       \item    Range: -180.0 to 180.0   \begin{itemize1}
         \item    Positive values indicate eastern longitude
         \item    Negative values indicate western longitude
       \vspace{-0.18in} \end{itemize1} \end{itemize1} */

  /* Optional */
  /*   Circular Horizontal Position Uncertainty */
  uint8_t horUncCircular_valid;  /**< Must be set to true if horUncCircular is being passed */
  float horUncCircular;
  /**<   Horizontal position uncertainty (circular).\n
       - Units: Meters */

  /* Optional */
  /*  Horizontal Elliptical Uncertainty (Semi-Minor Axis) */
  uint8_t horUncEllipseSemiMinor_valid;  /**< Must be set to true if horUncEllipseSemiMinor is being passed */
  float horUncEllipseSemiMinor;
  /**<   Semi-minor axis of horizontal elliptical uncertainty.\n
       - Units: Meters */

  /* Optional */
  /*  Horizontal Elliptical Uncertainty (Semi-Major Axis) */
  uint8_t horUncEllipseSemiMajor_valid;  /**< Must be set to true if horUncEllipseSemiMajor is being passed */
  float horUncEllipseSemiMajor;
  /**<   Semi-major axis of horizontal elliptical uncertainty.\n
       - Units: Meters */

  /* Optional */
  /*  Elliptical Horizontal Uncertainty Azimuth */
  uint8_t horUncEllipseOrientAzimuth_valid;  /**< Must be set to true if horUncEllipseOrientAzimuth is being passed */
  float horUncEllipseOrientAzimuth;
  /**<   Elliptical horizontal uncertainty azimuth of orientation.\n
       - Units: Decimal degrees \n
       - Range: 0 to 180 */

  /* Optional */
  /*  Horizontal Confidence */
  uint8_t horConfidence_valid;  /**< Must be set to true if horConfidence is being passed */
  uint8_t horConfidence;
  /**<   Horizontal uncertainty confidence.
       If both elliptical and horizontal uncertainties are specified in this message,
       the confidence corresponds to the elliptical uncertainty. \n
       - Units: Percent \n
       - Range: 0 to 99 */

  /* Optional */
  /*  Horizontal Reliability */
  uint8_t horReliability_valid;  /**< Must be set to true if horReliability is being passed */
  qmiLocReliabilityEnumT_v02 horReliability;
  /**<   Specifies the reliability of the horizontal position.
 Valid values: \n
      - eQMI_LOC_RELIABILITY_NOT_SET (0) --  Location reliability is not set
      - eQMI_LOC_RELIABILITY_VERY_LOW (1) --  Location reliability is very low; use it at your own risk
      - eQMI_LOC_RELIABILITY_LOW (2) --  Location reliability is low; little or no cross-checking is possible
      - eQMI_LOC_RELIABILITY_MEDIUM (3) --  Location reliability is medium; limited cross-check passed
      - eQMI_LOC_RELIABILITY_HIGH (4) --  Location reliability is high; strong cross-check passed
 */

  /* Optional */
  /*  Horizontal Speed */
  uint8_t speedHorizontal_valid;  /**< Must be set to true if speedHorizontal is being passed */
  float speedHorizontal;
  /**<   Horizontal speed.\n
       - Units: Meters/second */

  /* Optional */
  /*  Speed Uncertainty */
  uint8_t speedUnc_valid;  /**< Must be set to true if speedUnc is being passed */
  float speedUnc;
  /**<   3-D Speed uncertainty.\n
       - Units: Meters/second */

  /* Optional */
  /*  Altitude With Respect to Ellipsoid */
  uint8_t altitudeWrtEllipsoid_valid;  /**< Must be set to true if altitudeWrtEllipsoid is being passed */
  float altitudeWrtEllipsoid;
  /**<   Altitude with respect to the WGS84 ellipsoid.\n
       - Units: Meters \n
       - Range: -500 to 15883 */

  /* Optional */
  /*  Altitude With Respect to Sea Level */
  uint8_t altitudeWrtMeanSeaLevel_valid;  /**< Must be set to true if altitudeWrtMeanSeaLevel is being passed */
  float altitudeWrtMeanSeaLevel;
  /**<   Altitude with respect to mean sea level.\n
       - Units: Meters */

  /* Optional */
  /*  Vertical Uncertainty */
  uint8_t vertUnc_valid;  /**< Must be set to true if vertUnc is being passed */
  float vertUnc;
  /**<   Vertical uncertainty.\n
       - Units: Meters */

  /* Optional */
  /*  Vertical Confidence */
  uint8_t vertConfidence_valid;  /**< Must be set to true if vertConfidence is being passed */
  uint8_t vertConfidence;
  /**<   Vertical uncertainty confidence.\n
       - Units: Percent \n
       - Range: 0 to 99 */

  /* Optional */
  /*  Vertical Reliability */
  uint8_t vertReliability_valid;  /**< Must be set to true if vertReliability is being passed */
  qmiLocReliabilityEnumT_v02 vertReliability;
  /**<   Specifies the reliability of the vertical position.
 Valid values: \n
      - eQMI_LOC_RELIABILITY_NOT_SET (0) --  Location reliability is not set
      - eQMI_LOC_RELIABILITY_VERY_LOW (1) --  Location reliability is very low; use it at your own risk
      - eQMI_LOC_RELIABILITY_LOW (2) --  Location reliability is low; little or no cross-checking is possible
      - eQMI_LOC_RELIABILITY_MEDIUM (3) --  Location reliability is medium; limited cross-check passed
      - eQMI_LOC_RELIABILITY_HIGH (4) --  Location reliability is high; strong cross-check passed
 */

  /* Optional */
  /*  Vertical Speed */
  uint8_t speedVertical_valid;  /**< Must be set to true if speedVertical is being passed */
  float speedVertical;
  /**<   Vertical speed.\n
         - Units: Meters/second */

  /* Optional */
  /*  Heading */
  uint8_t heading_valid;  /**< Must be set to true if heading is being passed */
  float heading;
  /**<   Heading.\n
         - Units: Degrees \n
         - Range: 0 to 359.999  */

  /* Optional */
  /*  Heading Uncertainty */
  uint8_t headingUnc_valid;  /**< Must be set to true if headingUnc is being passed */
  float headingUnc;
  /**<   Heading uncertainty.\n
       - Units: Degrees \n
       - Range: 0 to 359.999 */

  /* Optional */
  /*  Magnetic Deviation */
  uint8_t magneticDeviation_valid;  /**< Must be set to true if magneticDeviation is being passed */
  float magneticDeviation;
  /**<   Difference between the bearing to true north and the bearing shown
      on a magnetic compass. The deviation is positive when the magnetic
      north is east of true north. */

  /* Optional */
  /*  Technology Used */
  uint8_t technologyMask_valid;  /**< Must be set to true if technologyMask is being passed */
  qmiLocPosTechMaskT_v02 technologyMask;
  /**<   Technology used in computing this fix.
 Valid bitmasks: \n
      - QMI_LOC_POS_TECH_MASK_SATELLITE (0x00000001) --  Satellites were used to generate the fix
      - QMI_LOC_POS_TECH_MASK_CELLID (0x00000002) --  Cell towers were used to generate the fix
      - QMI_LOC_POS_TECH_MASK_WIFI (0x00000004) --  Wi-Fi access points were used to generate the fix
      - QMI_LOC_POS_TECH_MASK_SENSORS (0x00000008) --  Sensors were used to generate the fix
      - QMI_LOC_POS_TECH_MASK_REFERENCE_LOCATION (0x00000010) --  Reference Location was used to generate the fix
      - QMI_LOC_POS_TECH_MASK_INJECTED_COARSE_POSITION (0x00000020) --  Coarse position injected into the location engine was used to
        generate the fix
      - QMI_LOC_POS_TECH_MASK_AFLT (0x00000040) --  AFLT was used to generate the fix
      - QMI_LOC_POS_TECH_MASK_HYBRID (0x00000080) --  GNSS and network-provided measurements were used to
        generate the fix
 */

  /* Optional */
  /*  Dilution of Precision */
  uint8_t DOP_valid;  /**< Must be set to true if DOP is being passed */
  qmiLocDOPStructT_v02 DOP;
  /**<   \vspace{0.06in} \n Dilution of precision associated with this position. */

  /* Optional */
  /*  UTC Timestamp */
  uint8_t timestampUtc_valid;  /**< Must be set to true if timestampUtc is being passed */
  uint64_t timestampUtc;
  /**<   UTC timestamp. \n
       - Units: Milliseconds since Jan. 1, 1970 */

  /* Optional */
  /*  Leap Seconds */
  uint8_t leapSeconds_valid;  /**< Must be set to true if leapSeconds is being passed */
  uint8_t leapSeconds;
  /**<   Leap second information. If leapSeconds is not available,
         timestampUtc is calculated based on a hard-coded value
         for leap seconds. \n
         - Units: Seconds */

  /* Optional */
  /*  GPS Time */
  uint8_t gpsTime_valid;  /**< Must be set to true if gpsTime is being passed */
  qmiLocGPSTimeStructT_v02 gpsTime;
  /**<   \vspace{0.06in} \n The number of weeks since Jan. 5, 1980, and
       milliseconds into the current week. */

  /* Optional */
  /*  Time Uncertainty */
  uint8_t timeUnc_valid;  /**< Must be set to true if timeUnc is being passed */
  float timeUnc;
  /**<   Time uncertainty. \n
       - Units: Milliseconds */

  /* Optional */
  /*  Time Source */
  uint8_t timeSrc_valid;  /**< Must be set to true if timeSrc is being passed */
  qmiLocTimeSourceEnumT_v02 timeSrc;
  /**<   Time source. Valid values: \n
      - eQMI_LOC_TIME_SRC_INVALID (0) --  Invalid time.
      - eQMI_LOC_TIME_SRC_NETWORK_TIME_TRANSFER (1) --  Time is set by the 1X system
      - eQMI_LOC_TIME_SRC_NETWORK_TIME_TAGGING (2) --  Time is set by WCDMA/GSM time tagging (i.e.,
       associating network time with GPS time)
      - eQMI_LOC_TIME_SRC_EXTERNAL_INPUT (3) --  Time is set by an external injection
      - eQMI_LOC_TIME_SRC_TOW_DECODE (4) --  Time is set after decoding over-the-air GPS navigation data
       from one GPS satellite
      - eQMI_LOC_TIME_SRC_TOW_CONFIRMED (5) --  Time is set after decoding over-the-air GPS navigation data
       from multiple satellites
      - eQMI_LOC_TIME_SRC_TOW_AND_WEEK_CONFIRMED (6) --  Both time of the week and the GPS week number are known
      - eQMI_LOC_TIME_SRC_NAV_SOLUTION (7) --  Time is set by the position engine after the fix is obtained
      - eQMI_LOC_TIME_SRC_SOLVE_FOR_TIME (8) --  Time is set by the position engine after performing SFT;
       this is done when the clock time uncertainty is large
      - eQMI_LOC_TIME_SRC_GLO_TOW_DECODE (9) --  Time is set after decoding GLO satellites
      - eQMI_LOC_TIME_SRC_TIME_TRANSFORM (10) --  Time is set after transforming the GPS to GLO time
      - eQMI_LOC_TIME_SRC_WCDMA_SLEEP_TIME_TAGGING (11) --  Time is set by the sleep time tag provided by the WCDMA network
      - eQMI_LOC_TIME_SRC_GSM_SLEEP_TIME_TAGGING (12) --  Time is set by the sleep time tag provided by the GSM network
      - eQMI_LOC_TIME_SRC_UNKNOWN (13) --  Source of the time is unknown
      - eQMI_LOC_TIME_SRC_SYSTEM_TIMETICK (14) --  Time is derived from the system clock (better known as the slow clock);
       GNSS time is maintained irrespective of the GNSS receiver state
      - eQMI_LOC_TIME_SRC_QZSS_TOW_DECODE (15) --  Time is set after decoding QZSS satellites
      - eQMI_LOC_TIME_SRC_BDS_TOW_DECODE (16) --  Time is set after decoding BDS satellites  */

  /* Optional */
  /*  Sensor Data Usage */
  uint8_t sensorDataUsage_valid;  /**< Must be set to true if sensorDataUsage is being passed */
  qmiLocSensorUsageIndicatorStructT_v02 sensorDataUsage;
  /**<   \vspace{0.06in} \n Indicates whether sensor data was used in computing the position in this
       position report. */

  /* Optional */
  /*  Fix Count for This Session */
  uint8_t fixId_valid;  /**< Must be set to true if fixId is being passed */
  uint32_t fixId;
  /**<   Fix count for the session. Starts with 0 and increments by one
       for each successive position report for a particular session. */

  /* Optional */
  /*  SVs Used to Calculate the Fix */
  uint8_t gnssSvUsedList_valid;  /**< Must be set to true if gnssSvUsedList is being passed */
  uint32_t gnssSvUsedList_len;  /**< Must be set to # of elements in gnssSvUsedList */
  uint16_t gnssSvUsedList[QMI_LOC_MAX_SV_USED_LIST_LENGTH_V02];
  /**<   Each entry in the list contains the SV ID of a satellite
      used for calculating this position report. The following
      information is associated with each SV ID: \n
      Range: \n
      - For GPS:     1 to 32 \n
      - For SBAS:    33 to 64 \n
      - For GLONASS: 65 to 96 \n
      - For QZSS:    193 to 197 \n
      - For BDS:     201 to 237
      */

  /* Optional */
  /*  Altitude Assumed */
  uint8_t altitudeAssumed_valid;  /**< Must be set to true if altitudeAssumed is being passed */
  uint8_t altitudeAssumed;
  /**<   Indicates whether altitude is assumed or calculated: \begin{itemize1}
         \item    0x00 (FALSE) -- Altitude is calculated
         \item    0x01 (TRUE) -- Altitude is assumed; there may not be enough
                                 satellites to determine the precise altitude
        \vspace{-0.18in} \end{itemize1}*/
}qmiLocEventPositionReportIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCSVSYSTEMENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_SV_SYSTEM_GPS_V02 = 1, /**<  GPS satellite  */
  eQMI_LOC_SV_SYSTEM_GALILEO_V02 = 2, /**<  GALILEO satellite  */
  eQMI_LOC_SV_SYSTEM_SBAS_V02 = 3, /**<  SBAS satellite  */
  eQMI_LOC_SV_SYSTEM_COMPASS_V02 = 4, /**<  COMPASS satellite  */
  eQMI_LOC_SV_SYSTEM_GLONASS_V02 = 5, /**<  GLONASS satellite  */
  eQMI_LOC_SV_SYSTEM_BDS_V02 = 6, /**<  BDS satellite  */
  QMILOCSVSYSTEMENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocSvSystemEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCSVSTATUSENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_SV_STATUS_IDLE_V02 = 1, /**<  SV is not being actively processed  */
  eQMI_LOC_SV_STATUS_SEARCH_V02 = 2, /**<  The system is searching for this SV  */
  eQMI_LOC_SV_STATUS_TRACK_V02 = 3, /**<  SV is being tracked  */
  QMILOCSVSTATUSENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocSvStatusEnumT_v02;
/**
    @}
  */

typedef uint32_t qmiLocSvInfoValidMaskT_v02;
#define QMI_LOC_SV_INFO_MASK_VALID_SYSTEM_V02 ((qmiLocSvInfoValidMaskT_v02)0x00000001) /**<  System field is valid in SV information  */
#define QMI_LOC_SV_INFO_MASK_VALID_GNSS_SVID_V02 ((qmiLocSvInfoValidMaskT_v02)0x00000002) /**<  gnssSvId field is valid in SV information  */
#define QMI_LOC_SV_INFO_MASK_VALID_HEALTH_STATUS_V02 ((qmiLocSvInfoValidMaskT_v02)0x00000004) /**<  healthStatus field is valid in SV information  */
#define QMI_LOC_SV_INFO_MASK_VALID_PROCESS_STATUS_V02 ((qmiLocSvInfoValidMaskT_v02)0x00000008) /**<  processStatus field is valid in SV information  */
#define QMI_LOC_SV_INFO_MASK_VALID_SVINFO_MASK_V02 ((qmiLocSvInfoValidMaskT_v02)0x00000010) /**<  svInfoMask field is valid in SV information  */
#define QMI_LOC_SV_INFO_MASK_VALID_ELEVATION_V02 ((qmiLocSvInfoValidMaskT_v02)0x00000020) /**<  Elevation field is valid in SV information  */
#define QMI_LOC_SV_INFO_MASK_VALID_AZIMUTH_V02 ((qmiLocSvInfoValidMaskT_v02)0x00000040) /**<  Azimuth field is valid in SV information  */
#define QMI_LOC_SV_INFO_MASK_VALID_SNR_V02 ((qmiLocSvInfoValidMaskT_v02)0x00000080) /**<  SNR field is valid in SV information  */
typedef uint8_t qmiLocSvInfoMaskT_v02;
#define QMI_LOC_SVINFO_MASK_HAS_EPHEMERIS_V02 ((qmiLocSvInfoMaskT_v02)0x01) /**<  Ephemeris is available for this SV  */
#define QMI_LOC_SVINFO_MASK_HAS_ALMANAC_V02 ((qmiLocSvInfoMaskT_v02)0x02) /**<  Almanac is available for this SV  */
/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  qmiLocSvInfoValidMaskT_v02 validMask;
  /**<   Bitmask indicating which of the fields in this TLV are valid.

         Valid bitmasks: \begin{itemize1}
         \item    0x00000001 -- VALID_SYSTEM
         \item    0x00000002 -- VALID_GNSS_SVID
         \item    0x00000004 -- VALID_HEALTH_ STATUS
         \item    0x00000008 -- VALID_PROCESS_ STATUS
         \item    0x00000010 -- VALID_SVINFO_ MASK
         \item    0x00000020 -- VALID_ELEVATION
         \item    0x00000040 -- VALID_AZIMUTH
         \item    0x00000080 -- VALID_SNR
         \vspace{-0.18in} \end{itemize1}  */

  qmiLocSvSystemEnumT_v02 system;
  /**<   Indicates to which constellation this SV belongs.

 Valid values: \n
      - eQMI_LOC_SV_SYSTEM_GPS (1) --  GPS satellite
      - eQMI_LOC_SV_SYSTEM_GALILEO (2) --  GALILEO satellite
      - eQMI_LOC_SV_SYSTEM_SBAS (3) --  SBAS satellite
      - eQMI_LOC_SV_SYSTEM_COMPASS (4) --  COMPASS satellite
      - eQMI_LOC_SV_SYSTEM_GLONASS (5) --  GLONASS satellite
      - eQMI_LOC_SV_SYSTEM_BDS (6) --  BDS satellite
 */

  uint16_t gnssSvId;
  /**<   GNSS SV ID.
         \begin{itemize1}
         \item Range:  \begin{itemize1}
           \item For GPS:      1 to 32
           \item For GLONASS:  1 to 32
           \item For SBAS:     120 to 151
           \item For BDS:      201 to 237
         \end{itemize1} \end{itemize1}

        The GPS and GLONASS SVs can be disambiguated using the system field. */

  uint8_t healthStatus;
  /**<   Health status.
         \begin{itemize1}
         \item    Range: 0 to 1; 0 = unhealthy, \n 1 = healthy
         \vspace{-0.18in} \end{itemize1}*/

  qmiLocSvStatusEnumT_v02 svStatus;
  /**<   SV processing status.

 Valid values: \n
      - eQMI_LOC_SV_STATUS_IDLE (1) --  SV is not being actively processed
      - eQMI_LOC_SV_STATUS_SEARCH (2) --  The system is searching for this SV
      - eQMI_LOC_SV_STATUS_TRACK (3) --  SV is being tracked
 */

  qmiLocSvInfoMaskT_v02 svInfoMask;
  /**<   Indicates whether almanac and ephemeris information is available. \n
         Valid bitmasks:

           - 0x01 -- SVINFO_HAS_EPHEMERIS \n
           - 0x02 -- SVINFO_HAS_ALMANAC
    */

  float elevation;
  /**<   SV elevation angle.\n
         - Units: Degrees \n
         - Range: 0 to 90 */

  float azimuth;
  /**<   SV azimuth angle.\n
         - Units: Degrees \n
         - Range: 0 to 360 */

  float snr;
  /**<   SV signal-to-noise ratio. \n
         - Units: dB-Hz */
}qmiLocSvInfoStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Sends a satellite report to the control point. */
typedef struct {

  /* Mandatory */
  /*  Altitude Assumed */
  uint8_t altitudeAssumed;
  /**<   Indicates whether altitude is assumed or calculated: \begin{itemize1}
         \item    0x00 (FALSE) -- Valid altitude is calculated
         \item    0x01 (TRUE) -- Valid altitude is assumed; there may not be
                                 enough satellites to determine precise altitude
          \vspace{-0.18in} \end{itemize1}*/

  /* Optional */
  /*  Satellite Info */
  uint8_t svList_valid;  /**< Must be set to true if svList is being passed */
  uint32_t svList_len;  /**< Must be set to # of elements in svList */
  qmiLocSvInfoStructT_v02 svList[QMI_LOC_SV_INFO_LIST_MAX_SIZE_V02];
  /**<   \vspace{0.06in} \n SV information list. */
}qmiLocEventGnssSvInfoIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Sends NMEA sentences to the control point */
typedef struct {

  /* Mandatory */
  /*  NMEA String */
  char nmea[QMI_LOC_NMEA_STRING_MAX_LENGTH_V02 + 1];
  /**<   NMEA string.
       \begin{itemize1}
       \item    Type: NULL-terminated string
       \item    Maximum string length (including NULL terminator): 201
       \vspace{-0.18in} \end{itemize1}*/
}qmiLocEventNmeaIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCNINOTIFYVERIFYENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_NI_USER_NO_NOTIFY_NO_VERIFY_V02 = 1, /**<  No notification and no verification required  */
  eQMI_LOC_NI_USER_NOTIFY_ONLY_V02 = 2, /**<  Notify only; no verification required  */
  eQMI_LOC_NI_USER_NOTIFY_VERIFY_ALLOW_NO_RESP_V02 = 3, /**<  Notify and verify, but no response required.  */
  eQMI_LOC_NI_USER_NOTIFY_VERIFY_NOT_ALLOW_NO_RESP_V02 = 4, /**<  Notify and verify, and require a response  */
  eQMI_LOC_NI_USER_NOTIFY_VERIFY_PRIVACY_OVERRIDE_V02 = 5, /**<  Notify and verify; privacy override  */
  QMILOCNINOTIFYVERIFYENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocNiNotifyVerifyEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCNIVXPOSMODEENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_NI_VX_MS_ASSISTED_ONLY_V02 = 1, /**<  MS-assisted only allowed  */
  eQMI_LOC_NI_VX_MS_BASED_ONLY_V02 = 2, /**<  MS-based only allowed  */
  eQMI_LOC_NI_VX_MS_ASSISTED_PREFERRED_MS_BASED_ALLOWED_V02 = 3, /**<  MS-assisted preferred, but MS-based allowed  */
  eQMI_LOC_NI_VX_MS_BASED_PREFERRED_MS_ASSISTED_ALLOWED_V02 = 4, /**<  MS-based preferred, but MS-assisted allowed  */
  QMILOCNIVXPOSMODEENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocNiVxPosModeEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCNIVXREQUESTORIDENCODINGSCHEMEENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_NI_VX_OCTET_V02 = 0, /**<  Encoding is Octet  */
  eQMI_LOC_NI_VX_EXN_PROTOCOL_MSG_V02 = 1, /**<  Encoding is EXN protocol message  */
  eQMI_LOC_NI_VX_ASCII_V02 = 2, /**<  Encoding is ASCII  */
  eQMI_LOC_NI_VX_IA5_V02 = 3, /**<  Encoding is IA5  */
  eQMI_LOC_NI_VX_UNICODE_V02 = 4, /**<  Encoding is Unicode  */
  eQMI_LOC_NI_VX_SHIFT_JIS_V02 = 5, /**<  Encoding is Shift JIS  */
  eQMI_LOC_NI_VX_KOREAN_V02 = 6, /**<  Encoding is Korean  */
  eQMI_LOC_NI_VX_LATIN_HEBREW_V02 = 7, /**<  Encoding is Latin Hebrew  */
  eQMI_LOC_NI_VX_LATIN_V02 = 8, /**<  Encoding is Latin  */
  eQMI_LOC_NI_VX_GSM_V02 = 9, /**<  Encoding is GSM  */
  QMILOCNIVXREQUESTORIDENCODINGSCHEMEENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocNiVxRequestorIdEncodingSchemeEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  uint8_t posQosIncl;
  /**<   Indicates whether quality of service is included:\n
         - 0x01 (TRUE) --  QoS is included \n
         - 0x00 (FALSE) -- QoS is not included */

  uint8_t posQos;
  /**<   Position QoS timeout. \n
         - Units: Seconds \n
         - Range: 0 to 255 */

  uint32_t numFixes;
  /**<   Number of fixes allowed. */

  uint32_t timeBetweenFixes;
  /**<   Time between fixes. \n
         - Units: Seconds */

  qmiLocNiVxPosModeEnumT_v02 posMode;
  /**<   Position mode.
 Valid values:

      - eQMI_LOC_NI_VX_MS_ASSISTED_ONLY (1) --  MS-assisted only allowed
      - eQMI_LOC_NI_VX_MS_BASED_ONLY (2) --  MS-based only allowed
      - eQMI_LOC_NI_VX_MS_ASSISTED_PREFERRED_MS_BASED_ALLOWED (3) --  MS-assisted preferred, but MS-based allowed
      - eQMI_LOC_NI_VX_MS_BASED_PREFERRED_MS_ASSISTED_ALLOWED (4) --  MS-based preferred, but MS-assisted allowed
 */

  qmiLocNiVxRequestorIdEncodingSchemeEnumT_v02 encodingScheme;
  /**<   VX encoding scheme.

 Valid values:

      - eQMI_LOC_NI_VX_OCTET (0) --  Encoding is Octet
      - eQMI_LOC_NI_VX_EXN_PROTOCOL_MSG (1) --  Encoding is EXN protocol message
      - eQMI_LOC_NI_VX_ASCII (2) --  Encoding is ASCII
      - eQMI_LOC_NI_VX_IA5 (3) --  Encoding is IA5
      - eQMI_LOC_NI_VX_UNICODE (4) --  Encoding is Unicode
      - eQMI_LOC_NI_VX_SHIFT_JIS (5) --  Encoding is Shift JIS
      - eQMI_LOC_NI_VX_KOREAN (6) --  Encoding is Korean
      - eQMI_LOC_NI_VX_LATIN_HEBREW (7) --  Encoding is Latin Hebrew
      - eQMI_LOC_NI_VX_LATIN (8) --  Encoding is Latin
      - eQMI_LOC_NI_VX_GSM (9) --  Encoding is GSM
 */

  uint32_t requestorId_len;  /**< Must be set to # of elements in requestorId */
  uint8_t requestorId[QMI_LOC_NI_MAX_REQUESTOR_ID_LENGTH_V02];
  /**<   Requestor ID. \n
       - Type:  Array of bytes \n
       - Maximum array length: 200
  */

  uint16_t userRespTimerInSeconds;
  /**<   Time to wait for the user to respond. \n
         - Units: Seconds */
}qmiLocNiVxNotifyVerifyStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCNISUPLPOSMETHODENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_NI_SUPL_POSMETHOD_AGPS_SETASSISTED_V02 = 1, /**<  Set assisted  */
  eQMI_LOC_NI_SUPL_POSMETHOD_AGPS_SETBASED_V02 = 2, /**<  Set based  */
  eQMI_LOC_NI_SUPL_POSMETHOD_AGPS_SETASSISTED_PREF_V02 = 3, /**<  Set assisted preferred  */
  eQMI_LOC_NI_SUPL_POSMETHOD_AGPS_SETBASED_PREF_V02 = 4, /**<  Set based preferred  */
  eQMI_LOC_NI_SUPL_POSMETHOD_AUTONOMOUS_GPS_V02 = 5, /**<  Standalone GPS  */
  eQMI_LOC_NI_SUPL_POSMETHOD_AFLT_V02 = 6, /**<  Advanced forward link trilateration  */
  eQMI_LOC_NI_SUPL_POSMETHOD_ECID_V02 = 7, /**<  Exclusive chip ID  */
  eQMI_LOC_NI_SUPL_POSMETHOD_EOTD_V02 = 8, /**<  Enhnaced observed time difference  */
  eQMI_LOC_NI_SUPL_POSMETHOD_OTDOA_V02 = 9, /**<  Observed time delay of arrival  */
  eQMI_LOC_NI_SUPL_POSMETHOD_NO_POSITION_V02 = 10, /**<  No position  */
  QMILOCNISUPLPOSMETHODENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocNiSuplPosMethodEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCNIDATACODINGSCHEMEENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_NI_SS_GERMAN_V02 = 12, /**<  Language is German  */
  eQMI_LOC_NI_SS_ENGLISH_V02 = 13, /**<  Language is English  */
  eQMI_LOC_NI_SS_ITALIAN_V02 = 14, /**<  Language is Italian  */
  eQMI_LOC_NI_SS_FRENCH_V02 = 15, /**<  Language is French  */
  eQMI_LOC_NI_SS_SPANISH_V02 = 16, /**<  Language is Spanish  */
  eQMI_LOC_NI_SS_DUTCH_V02 = 17, /**<  Language is Dutch  */
  eQMI_LOC_NI_SS_SWEDISH_V02 = 18, /**<  Language is Swedish  */
  eQMI_LOC_NI_SS_DANISH_V02 = 19, /**<  Language is Danish  */
  eQMI_LOC_NI_SS_PORTUGUESE_V02 = 20, /**<  Language is Portuguese  */
  eQMI_LOC_NI_SS_FINNISH_V02 = 21, /**<  Language is Finnish  */
  eQMI_LOC_NI_SS_NORWEGIAN_V02 = 22, /**<  Language is Norwegian  */
  eQMI_LOC_NI_SS_GREEK_V02 = 23, /**<  Language is Greek  */
  eQMI_LOC_NI_SS_TURKISH_V02 = 24, /**<  Language is Turkish  */
  eQMI_LOC_NI_SS_HUNGARIAN_V02 = 25, /**<  Language is Hungarian  */
  eQMI_LOC_NI_SS_POLISH_V02 = 26, /**<  Language is Polish  */
  eQMI_LOC_NI_SS_LANGUAGE_UNSPEC_V02 = 27, /**<  Language is unspecified  */
  eQMI_LOC_NI_SUPL_UTF8_V02 = 28, /**<  Encoding is UTF 8  */
  eQMI_LOC_NI_SUPL_UCS2_V02 = 29, /**<  Encoding is UCS 2  */
  eQMI_LOC_NI_SUPL_GSM_DEFAULT_V02 = 30, /**<  Encoding is GSM default  */
  QMILOCNIDATACODINGSCHEMEENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocNiDataCodingSchemeEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCNISUPLFORMATENUMTYPE_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_NI_SUPL_FORMAT_LOGICAL_NAME_V02 = 0, /**<  SUPL logical name format  */
  eQMI_LOC_NI_SUPL_FORMAT_EMAIL_ADDRESS_V02 = 1, /**<  SUPL email address format  */
  eQMI_LOC_NI_SUPL_FORMAT_MSISDN_V02 = 2, /**<  SUPL MS-ISDN format  */
  eQMI_LOC_NI_SUPL_FORMAT_URL_V02 = 3, /**<  SUPL URL format  */
  eQMI_LOC_NI_SUPL_FORMAT_SIP_URL_V02 = 4, /**<  SUPL SIP URL format  */
  eQMI_LOC_NI_SUPL_FORMAT_MIN_V02 = 5, /**<  SUPL MIN format  */
  eQMI_LOC_NI_SUPL_FORMAT_MDN_V02 = 6, /**<  SUPL MDN format  */
  eQMI_LOC_NI_SUPL_FORMAT_IMSPUBLIC_IDENTITY_V02 = 7, /**<  SUPL IMS public identity  */
  eQMI_LOC_NI_SUPL_FORMAT_OSS_UNKNOWN_V02 = 2147483647, /**<  SUPL unknown format  */
  QMILOCNISUPLFORMATENUMTYPE_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocNiSuplFormatEnumType_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  qmiLocNiSuplFormatEnumType_v02 formatType;
  /**<   Format of the formatted string.

 Valid values: \n
      - eQMI_LOC_NI_SUPL_FORMAT_LOGICAL_NAME (0) --  SUPL logical name format
      - eQMI_LOC_NI_SUPL_FORMAT_EMAIL_ADDRESS (1) --  SUPL email address format
      - eQMI_LOC_NI_SUPL_FORMAT_MSISDN (2) --  SUPL MS-ISDN format
      - eQMI_LOC_NI_SUPL_FORMAT_URL (3) --  SUPL URL format
      - eQMI_LOC_NI_SUPL_FORMAT_SIP_URL (4) --  SUPL SIP URL format
      - eQMI_LOC_NI_SUPL_FORMAT_MIN (5) --  SUPL MIN format
      - eQMI_LOC_NI_SUPL_FORMAT_MDN (6) --  SUPL MDN format
      - eQMI_LOC_NI_SUPL_FORMAT_IMSPUBLIC_IDENTITY (7) --  SUPL IMS public identity
      - eQMI_LOC_NI_SUPL_FORMAT_OSS_UNKNOWN (2147483647) --  SUPL unknown format
 */

  uint32_t formattedString_len;  /**< Must be set to # of elements in formattedString */
  uint8_t formattedString[QMI_LOC_NI_MAX_CLIENT_NAME_LENGTH_V02];
  /**<   Formatted string. \n
        - Type: Byte array \n
        - Maximum string length: 64
   */
}qmiLocNiSuplFormattedStringStructT_v02;  /* Type */
/**
    @}
  */

typedef uint8_t qmiLocSuplQopValidMaskT_v02;
#define QMI_LOC_NI_SUPL_MASK_QOP_HORZ_ACC_VALID_V02 ((qmiLocSuplQopValidMaskT_v02)0x01) /**<  Horizontal accuracy is valid in the Quality of Position (QoP)  */
#define QMI_LOC_NI_SUPL_MASK_QOP_VER_ACC_VALID_V02 ((qmiLocSuplQopValidMaskT_v02)0x02) /**<  Vertical accuracy is valid in the QoP  */
#define QMI_LOC_NI_SUPL_MASK_QOP_MAXAGE_VALID_V02 ((qmiLocSuplQopValidMaskT_v02)0x04) /**<  Vertical accuracy is valid in the QoP  */
#define QMI_LOC_NI_SUPL_MASK_QOP_DELAY_VALID_V02 ((qmiLocSuplQopValidMaskT_v02)0x08) /**<  Vertical accuracy is valid in the QoP  */
/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  qmiLocSuplQopValidMaskT_v02 validMask;
  /**<   Bit field indicating which fields are valid in this value.

        Valid bitmasks: \n
          - 0x01 -- QOP_HORZ_ACC_VALID \n
          - 0x02 -- QOP_VER_ACC_VALID \n
          - 0x04 -- QOP_MAXAGE_VALID \n
          - 0x08 -- QOP_DELAY_VALID*/

  uint8_t horizontalAccuracy;
  /**<   Horizontal accuracy. \n
        - Units: Meters */

  uint8_t verticalAccuracy;
  /**<   Vertical accuracy. \n
        - Units: Meters */

  uint16_t maxLocAge;
  /**<   Maximum age of the location if the engine sends a previously
        computed position. \n
        - Units: Seconds */

  uint8_t delay;
  /**<   Delay the server is willing to tolerate for the fix. \n
        - Units: Seconds */
}qmiLocNiSuplQopStructT_v02;  /* Type */
/**
    @}
  */

typedef uint8_t qmiLocServerAddrTypeMaskT_v02;
#define QMI_LOC_SERVER_ADDR_TYPE_IPV4_MASK_V02 ((qmiLocServerAddrTypeMaskT_v02)0x01) /**<  IPv4 server address type  */
#define QMI_LOC_SERVER_ADDR_TYPE_IPV6_MASK_V02 ((qmiLocServerAddrTypeMaskT_v02)0x02) /**<  IPv6 server address type  */
#define QMI_LOC_SERVER_ADDR_TYPE_URL_MASK_V02 ((qmiLocServerAddrTypeMaskT_v02)0x04) /**<  URL server address type  */
/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  uint32_t addr;
  /**<   IPv4 address. */

  uint16_t port;
  /**<   IPv4 port. */
}qmiLocIpV4AddrStructType_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  uint16_t addr[QMI_LOC_IPV6_ADDR_LENGTH_V02];
  /**<   IPv6 address. \n
       - Type: Array of unsigned integers \n
       - Maximum length of the array: 8 */

  uint32_t port;
  /**<   IPv6 port. */
}qmiLocIpV6AddrStructType_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  qmiLocServerAddrTypeMaskT_v02 suplServerAddrTypeMask;
  /**<   Mask specifying the valid fields in this value.

       Valid bitmasks: \n
         - 0x01 -- IPv4 \n
         - 0x02 -- IPv6 \n
         - 0x04 -- URL
  */

  qmiLocIpV4AddrStructType_v02 ipv4Addr;
  /**<   IPv4 address and port. */

  qmiLocIpV6AddrStructType_v02 ipv6Addr;
  /**<   IPv6 address and port. */

  char urlAddr[QMI_LOC_MAX_SERVER_ADDR_LENGTH_V02 + 1];
  /**<   URL.
       \begin{itemize1}
       \item    Type: NULL-terminated string
       \item    Maximum string length (including NULL terminator): 256
       \vspace{-0.18in} \end{itemize1}
        */
}qmiLocNiSuplServerInfoStructT_v02;  /* Type */
/**
    @}
  */

typedef uint32_t qmiLocNiSuplNotifyVerifyValidMaskT_v02;
#define QMI_LOC_SUPL_SERVER_INFO_MASK_V02 ((qmiLocNiSuplNotifyVerifyValidMaskT_v02)0x00000001) /**<  Mask to denote that the server information
      is present in an NI SUPL Notify/Verify request event. This mask is set in
     the valid_flags field of a Notify/Verify structure.  */
#define QMI_LOC_SUPL_SESSION_ID_MASK_V02 ((qmiLocNiSuplNotifyVerifyValidMaskT_v02)0x00000002) /**<  Mask to denote that the SUPL session ID
       is present in an NI SUPL Notify/Verify request event.
      This mask is set in the valid_flags field of a
      Notify/Verify structure.   */
#define QMI_LOC_SUPL_HASH_MASK_V02 ((qmiLocNiSuplNotifyVerifyValidMaskT_v02)0x00000004) /**<  Mask to denote that the SUPL hash is present
       in an NI Notify/Verify request event.
      This mask is set in the valid_flags field of a
      Notify/Verify structure.   */
#define QMI_LOC_SUPL_POS_METHOD_MASK_V02 ((qmiLocNiSuplNotifyVerifyValidMaskT_v02)0x00000008) /**<  Mask to denote that the position method is present
       in an NI SUPL Notify/Verify request event.
      This mask is set in the valid_flags field of a
      Notify/Verify structure.  */
#define QMI_LOC_SUPL_DATA_CODING_SCHEME_MASK_V02 ((qmiLocNiSuplNotifyVerifyValidMaskT_v02)0x00000010) /**<  Mask to denote that the data coding scheme
       is present in an NI SUPL Notify/Verify request event.
      This mask is set in the valid_flags field of a
      Notify/Verify structure.  */
#define QMI_LOC_SUPL_REQUESTOR_ID_MASK_V02 ((qmiLocNiSuplNotifyVerifyValidMaskT_v02)0x00000020) /**<  Mask to denote that the requestor ID
       is present in an NI Notify/Verify request event.
      This mask is set in the valid_flags field of a
      Notify/Verify structure.  */
#define QMI_LOC_SUPL_CLIENT_NAME_MASK_V02 ((qmiLocNiSuplNotifyVerifyValidMaskT_v02)0x00000040) /**<  Mask to denote that the requestor ID
       is present in an NI Notify/Verify request event.
       This mask is set in the valid_flags field of a
       Notify/Verify structure.  */
#define QMI_LOC_SUPL_QOP_MASK_V02 ((qmiLocNiSuplNotifyVerifyValidMaskT_v02)0x00000080) /**<  Mask to denote that the quality of position
       is present in an NI Notify/Verify request event.
       This mask is set in the valid_flags field of a
       Notify/Verify structure.  */
#define QMI_LOC_SUPL_USER_RESP_TIMER_MASK_V02 ((qmiLocNiSuplNotifyVerifyValidMaskT_v02)0x00000100) /**<  Mask to denote that the user response timer
       is present in an NI Notify/Verify request event.
       This mask is set in the valid_flags field of a
       Notify/Verify structure.  */
/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  qmiLocNiSuplNotifyVerifyValidMaskT_v02 valid_flags;
  /**<   Indicates which of the following fields are present in this value.

        Valid bitmasks: \begin{itemize1}
        \item    0x00000001 -- SUPL_SERVER_INFO
        \item    0x00000002 -- SUPL_SESSION_ID
        \item    0x00000004 -- SUPL_HASH
        \item    0x00000008 -- SUPL_POS_METHOD
        \item    0x00000010 -- SUPL_DATA_ CODING_SCHEME
        \item    0x00000020 -- SUPL_REQUESTOR_ ID
        \item    0x00000040 -- SUPL_CLIENT_ NAME
        \item    0x00000080 -- SUPL_QOP
        \item    0x00000100 -- SUPL_USER_RESP_ TIMER
        \vspace{-0.18in} \end{itemize1}
  */

  qmiLocNiSuplServerInfoStructT_v02 suplServerInfo;
  /**<   SUPL server information. */

  uint8_t suplSessionId[QMI_LOC_NI_SUPL_SLP_SESSION_ID_BYTE_LENGTH_V02];
  /**<   SUPL session ID. \n
       - Type: Array of unsigned integers \n
       - Maximum length of the array: 4 */

  uint8_t suplHash[QMI_LOC_NI_SUPL_HASH_LENGTH_V02];
  /**<   Hash for SUPL_INIT; used to validate that the message was not
       corrupted. \n
       - Type: Array of unsigned integers \n
       - Length of the array: 8 */

  qmiLocNiSuplPosMethodEnumT_v02 posMethod;
  /**<   GPS mode to be used for the fix.
 Valid values:

      - eQMI_LOC_NI_SUPL_POSMETHOD_AGPS_SETASSISTED (1) --  Set assisted
      - eQMI_LOC_NI_SUPL_POSMETHOD_AGPS_SETBASED (2) --  Set based
      - eQMI_LOC_NI_SUPL_POSMETHOD_AGPS_SETASSISTED_PREF (3) --  Set assisted preferred
      - eQMI_LOC_NI_SUPL_POSMETHOD_AGPS_SETBASED_PREF (4) --  Set based preferred
      - eQMI_LOC_NI_SUPL_POSMETHOD_AUTONOMOUS_GPS (5) --  Standalone GPS
      - eQMI_LOC_NI_SUPL_POSMETHOD_AFLT (6) --  Advanced forward link trilateration
      - eQMI_LOC_NI_SUPL_POSMETHOD_ECID (7) --  Exclusive chip ID
      - eQMI_LOC_NI_SUPL_POSMETHOD_EOTD (8) --  Enhnaced observed time difference
      - eQMI_LOC_NI_SUPL_POSMETHOD_OTDOA (9) --  Observed time delay of arrival
      - eQMI_LOC_NI_SUPL_POSMETHOD_NO_POSITION (10) --  No position
 */

  qmiLocNiDataCodingSchemeEnumT_v02 dataCodingScheme;
  /**<   Data coding scheme applies to both the requestor ID and the client
 name.

 Valid values: \n
      - eQMI_LOC_NI_SS_GERMAN (12) --  Language is German
      - eQMI_LOC_NI_SS_ENGLISH (13) --  Language is English
      - eQMI_LOC_NI_SS_ITALIAN (14) --  Language is Italian
      - eQMI_LOC_NI_SS_FRENCH (15) --  Language is French
      - eQMI_LOC_NI_SS_SPANISH (16) --  Language is Spanish
      - eQMI_LOC_NI_SS_DUTCH (17) --  Language is Dutch
      - eQMI_LOC_NI_SS_SWEDISH (18) --  Language is Swedish
      - eQMI_LOC_NI_SS_DANISH (19) --  Language is Danish
      - eQMI_LOC_NI_SS_PORTUGUESE (20) --  Language is Portuguese
      - eQMI_LOC_NI_SS_FINNISH (21) --  Language is Finnish
      - eQMI_LOC_NI_SS_NORWEGIAN (22) --  Language is Norwegian
      - eQMI_LOC_NI_SS_GREEK (23) --  Language is Greek
      - eQMI_LOC_NI_SS_TURKISH (24) --  Language is Turkish
      - eQMI_LOC_NI_SS_HUNGARIAN (25) --  Language is Hungarian
      - eQMI_LOC_NI_SS_POLISH (26) --  Language is Polish
      - eQMI_LOC_NI_SS_LANGUAGE_UNSPEC (27) --  Language is unspecified
      - eQMI_LOC_NI_SUPL_UTF8 (28) --  Encoding is UTF 8
      - eQMI_LOC_NI_SUPL_UCS2 (29) --  Encoding is UCS 2
      - eQMI_LOC_NI_SUPL_GSM_DEFAULT (30) --  Encoding is GSM default
 */

  qmiLocNiSuplFormattedStringStructT_v02 requestorId;
  /**<   Requestor ID. The encoding scheme for requestor_id is specified in
       the dataCodingScheme field. */

  qmiLocNiSuplFormattedStringStructT_v02 clientName;
  /**<   Client name. The encoding scheme for client_name is specified in
       the dataCodingScheme field. */

  qmiLocNiSuplQopStructT_v02 suplQop;
  /**<   SUPL QoP. */

  uint16_t userResponseTimer;
  /**<   Time to wait for the user to respond. \n
       - Units: Seconds*/
}qmiLocNiSuplNotifyVerifyStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCNILOCATIONTYPEENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_NI_LOCATIONTYPE_CURRENT_LOCATION_V02 = 1, /**<  Current location  */
  eQMI_LOC_NI_LOCATIONTYPE_CURRENT_OR_LAST_KNOWN_LOCATION_V02 = 2, /**<  Last known location; may be the current location  */
  eQMI_LOC_NI_LOCATIONTYPE_INITIAL_LOCATION_V02 = 3, /**<  Initial location  */
  QMILOCNILOCATIONTYPEENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocNiLocationTypeEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  qmiLocNiDataCodingSchemeEnumT_v02 dataCodingScheme;
  /**<   Identifies the coding scheme of the coded string.

 Valid values: \n
      - eQMI_LOC_NI_SS_GERMAN (12) --  Language is German
      - eQMI_LOC_NI_SS_ENGLISH (13) --  Language is English
      - eQMI_LOC_NI_SS_ITALIAN (14) --  Language is Italian
      - eQMI_LOC_NI_SS_FRENCH (15) --  Language is French
      - eQMI_LOC_NI_SS_SPANISH (16) --  Language is Spanish
      - eQMI_LOC_NI_SS_DUTCH (17) --  Language is Dutch
      - eQMI_LOC_NI_SS_SWEDISH (18) --  Language is Swedish
      - eQMI_LOC_NI_SS_DANISH (19) --  Language is Danish
      - eQMI_LOC_NI_SS_PORTUGUESE (20) --  Language is Portuguese
      - eQMI_LOC_NI_SS_FINNISH (21) --  Language is Finnish
      - eQMI_LOC_NI_SS_NORWEGIAN (22) --  Language is Norwegian
      - eQMI_LOC_NI_SS_GREEK (23) --  Language is Greek
      - eQMI_LOC_NI_SS_TURKISH (24) --  Language is Turkish
      - eQMI_LOC_NI_SS_HUNGARIAN (25) --  Language is Hungarian
      - eQMI_LOC_NI_SS_POLISH (26) --  Language is Polish
      - eQMI_LOC_NI_SS_LANGUAGE_UNSPEC (27) --  Language is unspecified
      - eQMI_LOC_NI_SUPL_UTF8 (28) --  Encoding is UTF 8
      - eQMI_LOC_NI_SUPL_UCS2 (29) --  Encoding is UCS 2
      - eQMI_LOC_NI_SUPL_GSM_DEFAULT (30) --  Encoding is GSM default
 */

  uint32_t codedString_len;  /**< Must be set to # of elements in codedString */
  uint8_t codedString[QMI_LOC_NI_CODEWORD_MAX_LENGTH_V02];
  /**<   Coded string. \n
       - Type: Array of bytes \n
       - Maximum string length: 20 */
}qmiLocNiUmtsCpCodedStringStructT_v02;  /* Type */
/**
    @}
  */

typedef uint16_t qmiLocNiUmtsCpNotifyVerifyValidMaskT_v02;
#define QMI_LOC_UMTS_CP_INVOKE_ID_MASK_V02 ((qmiLocNiUmtsCpNotifyVerifyValidMaskT_v02)0x0001) /**<  Mask to denote that the invoke ID
       is present in an NI Notify/Verify request event.
      This mask is set in the valid flags field of a
       Notify/Verify structure.  */
#define QMI_LOC_UMTS_CP_DATA_CODING_SCHEME_MASK_V02 ((qmiLocNiUmtsCpNotifyVerifyValidMaskT_v02)0x0002) /**<  Mask to denote that the data coding scheme
       is present in an NI Notify/Verify request event.
       This mask is set in the valid flags field of a
       Notify/Verify structure.  */
#define QMI_LOC_UMTS_CP_NOTIFICATION_TEXT_MASK_V02 ((qmiLocNiUmtsCpNotifyVerifyValidMaskT_v02)0x0004) /**<  Mask to denote that the notification text
       is present in an NI Notify/Verify request event.
      This mask is set in the valid flags field of a
       Notify/Verify structure.  */
#define QMI_LOC_UMTS_CP_CLIENT_ADDRESS_MASK_V02 ((qmiLocNiUmtsCpNotifyVerifyValidMaskT_v02)0x0008) /**<  Mask to denote that the client address
       is present in an NI Notify/Verify request event.
      This mask is set in the valid flags field of a
       Notify/Verify structure.  */
#define QMI_LOC_UMTS_CP_LOCATION_TYPE_MASK_V02 ((qmiLocNiUmtsCpNotifyVerifyValidMaskT_v02)0x0010) /**<  Mask to denote that the location type
       is present in an NI Notify/Verify request event.
       This mask is set in the valid flags field of a
       Notify/Verify structure.  */
#define QMI_LOC_UMTS_CP_REQUESTOR_ID_MASK_V02 ((qmiLocNiUmtsCpNotifyVerifyValidMaskT_v02)0x0020) /**<  Mask to denote that the requestor ID
       is present in an NI Notify/Verify request event.
       This mask is set in the valid flags field of a
       Notify/Verify structure.  */
#define QMI_LOC_UMTS_CP_CODEWORD_STRING_MASK_V02 ((qmiLocNiUmtsCpNotifyVerifyValidMaskT_v02)0x0040) /**<  Mask to denote that the code word string
       is present in an NI Notify/Verify request event.
       This mask is set in the valid flags field of a
       Notify/Verify structure.  */
#define QMI_LOC_UMTS_CP_SERVICE_TYPE_MASK_V02 ((qmiLocNiUmtsCpNotifyVerifyValidMaskT_v02)0x0080) /**<  Mask to denote that the service type
       is present in an NI Notify/Verify request event.
       This mask is set in the valid flags field of a
       Notify/Verify structure.  */
#define QMI_LOC_UMTS_CP_USER_RESP_TIMER_MASK_V02 ((qmiLocNiUmtsCpNotifyVerifyValidMaskT_v02)0x0100) /**<  Mask to denote that the user response timer
       is present in an NI Notify/Verify request event.
       This mask is set in the valid flags field of a
       Notify/Verify structure.  */
/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  qmiLocNiUmtsCpNotifyVerifyValidMaskT_v02 valid_flags;
  /**<   Fields that are valid in this value.

       Valid bitmasks: \begin{itemize1}
       \item    0x0001 -- INVOKE_ID_MASK
       \item    0x0002 -- DATA_CODING_ SCHEME_MASK
       \item    0x0004 -- NOTIFICATION_TEXT_ MASK
       \item    0x0008 -- CLIENT_ADDRESS_ MASK
       \item    0x0010 -- LOCATION_TYPE_ MASK
       \item    0x0020 -- REQUESTOR_ID_MASK
       \item    0x0040 -- CODEWORD_STRING_ MASK
       \item    0x0080 -- SERVICE_TYPE_MASK
       \item    0x0100 -- USER_RESP_TIMER_ MASK
       \vspace{-0.18in} \end{itemize1}
  */

  uint8_t invokeId;
  /**<   Supplementary Services invoke ID. */

  qmiLocNiDataCodingSchemeEnumT_v02 dataCodingScheme;
  /**<   Type of data encoding scheme for the text.
 Applies to both the notification text and the client address.

 Valid values: \n
      - eQMI_LOC_NI_SS_GERMAN (12) --  Language is German
      - eQMI_LOC_NI_SS_ENGLISH (13) --  Language is English
      - eQMI_LOC_NI_SS_ITALIAN (14) --  Language is Italian
      - eQMI_LOC_NI_SS_FRENCH (15) --  Language is French
      - eQMI_LOC_NI_SS_SPANISH (16) --  Language is Spanish
      - eQMI_LOC_NI_SS_DUTCH (17) --  Language is Dutch
      - eQMI_LOC_NI_SS_SWEDISH (18) --  Language is Swedish
      - eQMI_LOC_NI_SS_DANISH (19) --  Language is Danish
      - eQMI_LOC_NI_SS_PORTUGUESE (20) --  Language is Portuguese
      - eQMI_LOC_NI_SS_FINNISH (21) --  Language is Finnish
      - eQMI_LOC_NI_SS_NORWEGIAN (22) --  Language is Norwegian
      - eQMI_LOC_NI_SS_GREEK (23) --  Language is Greek
      - eQMI_LOC_NI_SS_TURKISH (24) --  Language is Turkish
      - eQMI_LOC_NI_SS_HUNGARIAN (25) --  Language is Hungarian
      - eQMI_LOC_NI_SS_POLISH (26) --  Language is Polish
      - eQMI_LOC_NI_SS_LANGUAGE_UNSPEC (27) --  Language is unspecified
      - eQMI_LOC_NI_SUPL_UTF8 (28) --  Encoding is UTF 8
      - eQMI_LOC_NI_SUPL_UCS2 (29) --  Encoding is UCS 2
      - eQMI_LOC_NI_SUPL_GSM_DEFAULT (30) --  Encoding is GSM default
 */

  uint32_t notificationText_len;  /**< Must be set to # of elements in notificationText */
  uint8_t notificationText[QMI_LOC_NI_MAX_CLIENT_NAME_LENGTH_V02];
  /**<   Notification text; the encoding method is specified in
       dataCodingScheme. \n
       - Type: Array of bytes \n
       - Maximum array length: 64 */

  uint32_t clientAddress_len;  /**< Must be set to # of elements in clientAddress */
  uint8_t clientAddress[QMI_LOC_NI_MAX_EXT_CLIENT_ADDRESS_V02];
  /**<   Client address; the encoding method is specified in
       dataCodingScheme. \n
       - Maximum array length: 20 */

  qmiLocNiLocationTypeEnumT_v02 locationType;
  /**<   Location type.

 Valid values: \n
      - eQMI_LOC_NI_LOCATIONTYPE_CURRENT_LOCATION (1) --  Current location
      - eQMI_LOC_NI_LOCATIONTYPE_CURRENT_OR_LAST_KNOWN_LOCATION (2) --  Last known location; may be the current location
      - eQMI_LOC_NI_LOCATIONTYPE_INITIAL_LOCATION (3) --  Initial location
 */

  qmiLocNiUmtsCpCodedStringStructT_v02 requestorId;
  /**<   Requestor ID; the encoding method is specified in the
       qmiLocNiUmtsCpCodedStringStructT.dataCodingScheme field. */

  qmiLocNiUmtsCpCodedStringStructT_v02 codewordString;
  /**<   Codeword string; the encoding method is specified in the
       qmiLocNiUmtsCpCodedStringStructT.dataCodingScheme field. */

  uint8_t lcsServiceTypeId;
  /**<   Service type ID. */

  uint16_t userResponseTimer;
  /**<   Time to wait for the user to respond. \n
       - Units: Seconds */
}qmiLocNiUmtsCpNotifyVerifyStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCNISERVICEINTERACTIONENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_NI_SERVICE_INTERACTION_ONGOING_NI_INCOMING_MO_V02 = 1, /**<  Service interaction between ongoing NI and incoming MO sessions.  */
  QMILOCNISERVICEINTERACTIONENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocNiServiceInteractionEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  qmiLocNiVxNotifyVerifyStructT_v02 niVxReq;
  /**<   Ongoing NI session request; this information is currently not filled. */

  qmiLocNiServiceInteractionEnumT_v02 serviceInteractionType;
  /**<   Service interaction type specified in qmiLocNiServiceInteractionEnumT.

 Valid values: \n
      - eQMI_LOC_NI_SERVICE_INTERACTION_ONGOING_NI_INCOMING_MO (1) --  Service interaction between ongoing NI and incoming MO sessions.
 */
}qmiLocNiVxServiceInteractionStructT_v02;  /* Type */
/**
    @}
  */

typedef uint16_t qmiLocNiSuplVer2ExtSupportedNetworksMaskT_v02;
#define QMI_LOC_SUPL_VER_2_EXT_MASK_SUPPORTED_NETWORK_WLAN_V02 ((qmiLocNiSuplVer2ExtSupportedNetworksMaskT_v02)0x0001) /**<  Denotes that WLAN measurements are allowed as part of location ID
       and multiple location IDs in the SUPL_POS_INIT message.  */
#define QMI_LOC_SUPL_VER_2_EXT_MASK_SUPPORTED_NETWORK_GSM_V02 ((qmiLocNiSuplVer2ExtSupportedNetworksMaskT_v02)0x0002) /**<  Denotes that GSM measurements are allowed as part of location ID
       and multiple location ID in the SUPL_POS_INIT message.  */
#define QMI_LOC_SUPL_VER_2_EXT_MASK_SUPPORTED_NETWORK_WCDMA_V02 ((qmiLocNiSuplVer2ExtSupportedNetworksMaskT_v02)0x0004) /**<  Denotes that WCDMA measurements are allowed as part of location ID
       and multiple location ID in the SUPL_POS_INIT message.  */
#define QMI_LOC_SUPL_VER_2_EXT_MASK_SUPPORTED_NETWORK_CDMA_V02 ((qmiLocNiSuplVer2ExtSupportedNetworksMaskT_v02)0x0008) /**<  Denotes that CDMA measurements are allowed as part of location ID
       and multiple location ID in the SUPL_POS_INIT message.  */
#define QMI_LOC_SUPL_VER_2_EXT_MASK_SUPPORTED_NETWORK_HRDP_V02 ((qmiLocNiSuplVer2ExtSupportedNetworksMaskT_v02)0x0010) /**<  Denotes that HRDP measurements are allowed as part of location ID
       and multiple location ID in the SUPL_POS_INIT message.  */
#define QMI_LOC_SUPL_VER_2_EXT_MASK_SUPPORTED_NETWORK_UMB_V02 ((qmiLocNiSuplVer2ExtSupportedNetworksMaskT_v02)0x0020) /**<  Denotes that UMB measurements are allowed as part of location ID
       and multiple location ID in the SUPL_POS_INIT message.  */
#define QMI_LOC_SUPL_VER_2_EXT_MASK_SUPPORTED_NETWORK_LTE_V02 ((qmiLocNiSuplVer2ExtSupportedNetworksMaskT_v02)0x0040) /**<  Denotes that LTE measurements are allowed as part of location ID
       and multiple location ID in the SUPL_POS_INIT message.  */
#define QMI_LOC_SUPL_VER_2_EXT_MASK_SUPPORTED_NETWORK_WIMAX_V02 ((qmiLocNiSuplVer2ExtSupportedNetworksMaskT_v02)0x0080) /**<  Denotes that WIMAX measurements are allowed as part of location ID
       and multiple location ID in the SUPL_POS_INIT message.  */
#define QMI_LOC_SUPL_VER_2_EXT_MASK_SUPPORTED_NETWORK_HISTORIC_V02 ((qmiLocNiSuplVer2ExtSupportedNetworksMaskT_v02)0x0100) /**<  Denotes that historical information is allowed as part of
       multiple location ID in the SUPL_POS_INIT message.  */
#define QMI_LOC_SUPL_VER_2_EXT_MASK_SUPPORTED_NETWORK_NONSVRV_V02 ((qmiLocNiSuplVer2ExtSupportedNetworksMaskT_v02)0x0200) /**<  Denotes that information about nonserving cells is allowed
       as part of multiple location ID in the SUPL_POS_INIT message.  */
/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCNISUPLVER2EXTTRIGGERTYPEENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_SUPL_VER_2_EXT_TRIGGER_TYPE_SINGLE_SHOT_V02 = -1, /**<  SUPL INIT message indicates a request for a single shot
       triggered session  */
  eQMI_LOC_SUPL_VER_2_EXT_TRIGGER_TYPE_PERIODIC_V02 = 0, /**<  SUPL INIT message indicates a request for a periodic
       triggered session  */
  eQMI_LOC_SUPL_VER_2_EXT_TRIGGER_TYPE_AREA_EVENT_V02 = 1, /**<  SUPL INIT message indicates a request for an area event
       triggered session  */
  QMILOCNISUPLVER2EXTTRIGGERTYPEENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocNiSuplVer2ExtTriggerTypeEnumT_v02;
/**
    @}
  */

typedef uint16_t qmiLocNiSuplVer2ExtGnssTypeMaskT_v02;
#define QMI_LOC_SUPL_VER_2_EXT_MASK_GNSS_GPS_V02 ((qmiLocNiSuplVer2ExtGnssTypeMaskT_v02)0x0001) /**<  GPS is allowed to be used as the positioning technology  */
#define QMI_LOC_SUPL_VER_2_EXT_MASK_GNSS_GLONASS_V02 ((qmiLocNiSuplVer2ExtGnssTypeMaskT_v02)0x0002) /**<  GLONASS is allowed to be used as the positioning technology  */
#define QMI_LOC_SUPL_VER_2_EXT_MASK_GNSS_GALILEO_V02 ((qmiLocNiSuplVer2ExtGnssTypeMaskT_v02)0x0004) /**<  Galileo is allowed to be used as the positioning technology  */
#define QMI_LOC_SUPL_VER_2_EXT_MASK_GNSS_SBAS_V02 ((qmiLocNiSuplVer2ExtGnssTypeMaskT_v02)0x0008) /**<  SBAS is allowed to be used as the positioning technology  */
#define QMI_LOC_SUPL_VER_2_EXT_MASK_GNSS_QZSS_V02 ((qmiLocNiSuplVer2ExtGnssTypeMaskT_v02)0x0010) /**<  QZSS is allowed to be used as the positioning technology  */
#define QMI_LOC_SUPL_VER_2_EXT_MASK_GNSS_MODERN_GPS_V02 ((qmiLocNiSuplVer2ExtGnssTypeMaskT_v02)0x0020) /**<  Modern GPS is allowed to be used as the positioning technology  */
/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  qmiLocNiSuplVer2ExtSupportedNetworksMaskT_v02 supportedNetworksMask;
  /**<   Specifies which type of network measurements are allowed to be sent as
       part of the Location ID or Multiple Location IDs parameter in the
       SUPL_POS_INIT message (see \hyperref[S4]{[S4]}).

       Valid bitmasks: \begin{itemize1}
       \item    0x0001 -- SUPPORTED_NETWORK_ WLAN
       \item    0x0002 -- SUPPORTED_NETWORK_ GSM
       \item    0x0004 -- SUPPORTED_NETWORK_ WCDMA
       \item    0x0008 -- SUPPORTED_NETWORK_ CDMA
       \item    0x0010 -- SUPPORTED_NETWORK_ HRDP
       \item    0x0020 -- SUPPORTED_NETWORK_ UMB
       \item    0x0040 -- SUPPORTED_NETWORK_ LTE
       \item    0x0080 -- SUPPORTED_NETWORK_ WIMAX
       \item    0x0100 -- SUPPORTED_NETWORK_ HISTORIC
       \item    0x0200 -- SUPPORTED_NETWORK_ NONSVRV
       \vspace{-0.18in} \end{itemize1}
   */

  qmiLocNiSuplVer2ExtTriggerTypeEnumT_v02 triggerType;
  /**<   Specifies the type of session trigger requested in the
 SUPL_POS_INIT message (refer to \hyperref[S4]{[S4]}).

 Valid values: \n
      - eQMI_LOC_SUPL_VER_2_EXT_TRIGGER_TYPE_SINGLE_SHOT (-1) --  SUPL INIT message indicates a request for a single shot
       triggered session
      - eQMI_LOC_SUPL_VER_2_EXT_TRIGGER_TYPE_PERIODIC (0) --  SUPL INIT message indicates a request for a periodic
       triggered session
      - eQMI_LOC_SUPL_VER_2_EXT_TRIGGER_TYPE_AREA_EVENT (1) --  SUPL INIT message indicates a request for an area event
       triggered session
 */

  qmiLocNiSuplVer2ExtGnssTypeMaskT_v02 gnssType;
  /**<   Specifies which GNSS technologies are allowed as positioning
       technologies.

       Valid bitmasks: \n
        - 0x0001 -- GNSS_GPS \n
        - 0x0002 -- GNSS_GLONASS \n
        - 0x0004 -- GNSS_GALILEO \n
        - 0x0008 -- GNSS_SBAS \n
        - 0x0010 -- GNSS_QZSS \n
        - 0x0020 -- GNSS_MODERN_GPS
  */
}qmiLocNiSuplVer2ExtStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  char eslpUrl[QMI_LOC_MAX_SERVER_ADDR_LENGTH_V02 + 1];
  /**<   ESLP URL. \n
       Maximum length: 255 bytes */
}qmiLocEmergencyNotificationStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Indicates an NI Notify/Verify request to the control point. */
typedef struct {

  /* Mandatory */
  /*  Notification Type */
  qmiLocNiNotifyVerifyEnumT_v02 notificationType;
  /**<   Type of notification/verification performed.

 Valid values: \n
      - eQMI_LOC_NI_USER_NO_NOTIFY_NO_VERIFY (1) --  No notification and no verification required
      - eQMI_LOC_NI_USER_NOTIFY_ONLY (2) --  Notify only; no verification required
      - eQMI_LOC_NI_USER_NOTIFY_VERIFY_ALLOW_NO_RESP (3) --  Notify and verify, but no response required.
      - eQMI_LOC_NI_USER_NOTIFY_VERIFY_NOT_ALLOW_NO_RESP (4) --  Notify and verify, and require a response
      - eQMI_LOC_NI_USER_NOTIFY_VERIFY_PRIVACY_OVERRIDE (5) --  Notify and verify; privacy override
 */

  /* Optional */
  /*  Network Initiated Vx Request */
  uint8_t NiVxInd_valid;  /**< Must be set to true if NiVxInd is being passed */
  qmiLocNiVxNotifyVerifyStructT_v02 NiVxInd;
  /**<   \vspace{0.06in} \n Optional NI Vx request payload. */

  /* Optional */
  /*  Network Initiated SUPL Request */
  uint8_t NiSuplInd_valid;  /**< Must be set to true if NiSuplInd is being passed */
  qmiLocNiSuplNotifyVerifyStructT_v02 NiSuplInd;
  /**<   \vspace{0.06in} \n Optional NI SUPL request payload. */

  /* Optional */
  /*  Network Initiated UMTS Control Plane Request */
  uint8_t NiUmtsCpInd_valid;  /**< Must be set to true if NiUmtsCpInd is being passed */
  qmiLocNiUmtsCpNotifyVerifyStructT_v02 NiUmtsCpInd;
  /**<   \vspace{0.06in} \n Optional NI UMTS-CP request payload. */

  /* Optional */
  /*  Network Initiated Service Interaction Request */
  uint8_t NiVxServiceInteractionInd_valid;  /**< Must be set to true if NiVxServiceInteractionInd is being passed */
  qmiLocNiVxServiceInteractionStructT_v02 NiVxServiceInteractionInd;
  /**<   \vspace{0.06in} \n Optional NI service interaction payload. */

  /* Optional */
  /*  Network Initiated SUPL Version 2 Extension */
  uint8_t NiSuplVer2ExtInd_valid;  /**< Must be set to true if NiSuplVer2ExtInd is being passed */
  qmiLocNiSuplVer2ExtStructT_v02 NiSuplVer2ExtInd;
  /**<   \vspace{0.06in} \n Optional NI SUPL Version 2 Extension payload. When present,
          this payload is to be used in conjunction with the SUPL
          indication payload. */

  /* Optional */
  /*  SUPL Emergency Notification */
  uint8_t suplEmergencyNotification_valid;  /**< Must be set to true if suplEmergencyNotification is being passed */
  qmiLocEmergencyNotificationStructT_v02 suplEmergencyNotification;
  /**<   \vspace{0.06in} \n This specifies that the corresponding NI notification is an
        emergency notification. Emergency notification
        can be given even without an Emergency SUPL Location Platform (ESLP)
        address. */
}qmiLocEventNiNotifyVerifyReqIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  char serverUrl[QMI_LOC_MAX_SERVER_ADDR_LENGTH_V02 + 1];
  /**<   Assistance server URL.
       \begin{itemize1}
       \item    Type: NULL-terminated string
       \item    Maximum string length (including NULL terminator): 256
       \vspace{-0.18in} \end{itemize1} */
}qmiLocAssistanceServerUrlStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  uint32_t delayThreshold;
  /**<   The time server is to be skipped if a one-way delay to the server
       exceeds this threshold. \n
       - Units: Milliseconds */

  uint32_t timeServerList_len;  /**< Must be set to # of elements in timeServerList */
  qmiLocAssistanceServerUrlStructT_v02 timeServerList[QMI_LOC_MAX_NTP_SERVERS_V02];
  /**<   List of Time Server URL's that are recommended by the service for time
       information, the list is ordered, the client is to use the first
       server specified in the list as the primary URL to fetch NTP time,
       the second one as secondary, and so on. \n
       - Maximum server list items: 3 */
}qmiLocTimeServerListStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Requests the control point to inject time information. */
typedef struct {

  /* Optional */
  /*  Time Server Info */
  uint8_t timeServerInfo_valid;  /**< Must be set to true if timeServerInfo is being passed */
  qmiLocTimeServerListStructT_v02 timeServerInfo;
  /**<   \vspace{0.06in} \n Contains information about the time servers recommended by the
       location service for NTP time. */
}qmiLocEventInjectTimeReqIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  uint32_t maxFileSizeInBytes;
  /**<   Maximum allowable predicted orbits file size (in bytes). */

  uint32_t maxPartSize;
  /**<   Maximum allowable predicted orbits file chunk size (in bytes). */
}qmiLocPredictedOrbitsAllowedSizesStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  uint32_t serverList_len;  /**< Must be set to # of elements in serverList */
  qmiLocAssistanceServerUrlStructT_v02 serverList[QMI_LOC_MAX_PREDICTED_ORBITS_SERVERS_V02];
  /**<   List of predicted orbits URLs. The list is ordered, so the client
       must use the first server specified in the list as the primary URL
       from which to download predicted orbits data, the second one as
       secondary, and so on. \n
       - Maximum number of servers that can be specified: 3 */
}qmiLocPredictedOrbitsServerListStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Requests the control point to inject predicted orbits data. */
typedef struct {

  /* Mandatory */
  /*  Allowed Sizes */
  qmiLocPredictedOrbitsAllowedSizesStructT_v02 allowedSizes;
  /**<   \vspace{0.06in} \n Maximum part and file size allowed to be injected in the engine. */

  /* Optional */
  /*  Server List */
  uint8_t serverList_valid;  /**< Must be set to true if serverList is being passed */
  qmiLocPredictedOrbitsServerListStructT_v02 serverList;
  /**<   \vspace{0.06in} \n List of servers that can be used by the client to download
       predicted orbits data. */
}qmiLocEventInjectPredictedOrbitsReqIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Requests the control point to inject a position. */
typedef struct {

  /* Mandatory */
  /*  Latitude */
  double latitude;
  /**<   Latitude (specified in WGS84 datum).
       \begin{itemize1}
       \item    Type: Floating point
       \item    Units: Degrees
       \item    Range: -90.0 to 90.0      \begin{itemize1}
         \item    Positive values indicate northern latitude
         \item    Negative values indicate southern latitude
       \vspace{-0.18in} \end{itemize1} \end{itemize1} */

  /* Mandatory */
  /*  Longitude */
  double longitude;
  /**<   Longitude (specified in WGS84 datum).
       \begin{itemize1}
       \item    Type: Floating point
       \item    Units: Degrees
       \item    Range: -180.0 to 180.0     \begin{itemize1}
         \item    Positive values indicate eastern longitude
         \item    Negative values indicate western longitude
       \vspace{-0.18in} \end{itemize1} \end{itemize1} */

  /* Mandatory */
  /*  Circular Horizontal Uncertainty */
  float horUncCircular;
  /**<   Horizontal position uncertainty (circular).\n
       - Units: Meters */

  /* Mandatory */
  /*  UTC Timestamp */
  uint64_t timestampUtc;
  /**<   UTC timestamp.
       \begin{itemize1}
       \item    Units: Milliseconds since Jan. 1, 1970
       \vspace{-0.18in} \end{itemize1} */
}qmiLocEventInjectPositionReqIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCENGINESTATEENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_ENGINE_STATE_ON_V02 = 1, /**<  Location engine is on  */
  eQMI_LOC_ENGINE_STATE_OFF_V02 = 2, /**<  Location engine is off  */
  QMILOCENGINESTATEENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocEngineStateEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Sends the engine state to the control point. */
typedef struct {

  /* Mandatory */
  /*  Engine State */
  qmiLocEngineStateEnumT_v02 engineState;
  /**<   Location engine state.

 Valid values: \n
      - eQMI_LOC_ENGINE_STATE_ON (1) --  Location engine is on
      - eQMI_LOC_ENGINE_STATE_OFF (2) --  Location engine is off
 */
}qmiLocEventEngineStateIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCFIXSESSIONSTATEENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_FIX_SESSION_STARTED_V02 = 1, /**<  Location fix session has started  */
  eQMI_LOC_FIX_SESSION_FINISHED_V02 = 2, /**<  Location fix session has ended  */
  QMILOCFIXSESSIONSTATEENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocFixSessionStateEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Sends the fix session state to the control point. */
typedef struct {

  /* Mandatory */
  /*  Session State */
  qmiLocFixSessionStateEnumT_v02 sessionState;
  /**<   LOC fix session state.

 Valid values: \n
      - eQMI_LOC_FIX_SESSION_STARTED (1) --  Location fix session has started
      - eQMI_LOC_FIX_SESSION_FINISHED (2) --  Location fix session has ended
 */

  /* Optional */
  /*  Session ID */
  uint8_t sessionId_valid;  /**< Must be set to true if sessionId is being passed */
  uint8_t sessionId;
  /**<   ID of the session that was specified in the Start request.
    This may not be specified for a fix session corresponding to
    a network-initiated request. \n
    - Range: 0 to 255 */
}qmiLocEventFixSessionStateIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCWIFIREQUESTENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_WIFI_START_PERIODIC_HI_FREQ_FIXES_V02 = 0, /**<  Start periodic fixes with high frequency  */
  eQMI_LOC_WIFI_START_PERIODIC_KEEP_WARM_V02 = 1, /**<  Keep warm for low frequency fixes without data downloads  */
  eQMI_LOC_WIFI_STOP_PERIODIC_FIXES_V02 = 2, /**<  Stop periodic fixes request  */
  QMILOCWIFIREQUESTENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocWifiRequestEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Sends a Wi-Fi request to the control point. */
typedef struct {

  /* Mandatory */
  /*  Request Type */
  qmiLocWifiRequestEnumT_v02 requestType;
  /**<   Request type.

 Valid values: \n
      - eQMI_LOC_WIFI_START_PERIODIC_HI_FREQ_FIXES (0) --  Start periodic fixes with high frequency
      - eQMI_LOC_WIFI_START_PERIODIC_KEEP_WARM (1) --  Keep warm for low frequency fixes without data downloads
      - eQMI_LOC_WIFI_STOP_PERIODIC_FIXES (2) --  Stop periodic fixes request
 */

  /* Optional */
  /*  Time Between Fixes */
  uint8_t tbfInMs_valid;  /**< Must be set to true if tbfInMs is being passed */
  uint16_t tbfInMs;
  /**<   Time between fixes for a periodic request.\n
        - Units: Milliseconds */
}qmiLocEventWifiReqIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  uint16_t samplesPerBatch;
  /**<   Specifies the number of samples per batch the GNSS location engine is to
       receive. The sensor sampling frequency can be computed as follows: \vspace{-0.06in} \n

       samplingFrequency = samplesPerBatch * batchesPerSecond  \vspace{-0.06in} \n

       samplesPerBatch must be a nonzero positive value.
  */

  uint16_t batchesPerSecond;
  /**<   Number of sensor-data batches the GNSS location engine is to receive
       per second. The rate is specified in an integral number of batches per
       second (Hz).  \vspace{-0.06in} \n

       batchesPerSecond must be a nonzero positive value.
  */
}qmiLocSensorControlConfigSamplingSpecStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  uint8_t injectEnable;
  /**<   Indicates whether the GNSS location engine is ready to accept data from this
       sensor.

       Valid values: \begin{itemize1}
       \item    0x01 (TRUE)  -- GNSS location engine is ready to accept sensor
                                data
       \item    0x00 (FALSE) -- GNSS location engine is not ready to accept
                                sensor data
        \vspace{-0.18in} \end{itemize1}
  */

  qmiLocSensorControlConfigSamplingSpecStructT_v02 dataFrequency;
  /**<   Rate at which the GNSS engine would like the sensor to be sampled. \n
       The rate is specified in integral number of samples per second (Hz)\n
       and batches per second.
  */
}qmiLocSensorReadyStatusStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Notifies the control point if the GNSS location engine is
                    ready to accept sensor data. */
typedef struct {

  /* Optional */
  /*  Accelerometer Accept Ready */
  uint8_t accelReady_valid;  /**< Must be set to true if accelReady is being passed */
  qmiLocSensorReadyStatusStructT_v02 accelReady;
  /**<   \vspace{0.06in} \n Indicates whether the GNSS location engine is ready
         to accept accelerometer sensor data.
   */

  /* Optional */
  /*  Gyroscope Accept Ready */
  uint8_t gyroReady_valid;  /**< Must be set to true if gyroReady is being passed */
  qmiLocSensorReadyStatusStructT_v02 gyroReady;
  /**<   \vspace{0.06in} \n Indicates whether the GNSS location engine is ready
         to accept gyroscope sensor data.
   */

  /* Optional */
  /*  Accelerometer Temperature Accept Ready */
  uint8_t accelTemperatureReady_valid;  /**< Must be set to true if accelTemperatureReady is being passed */
  qmiLocSensorReadyStatusStructT_v02 accelTemperatureReady;
  /**<   \vspace{0.06in} \n Indicates whether the GNSS location engine is ready
        to accept accelerometer temperature data.
   */

  /* Optional */
  /*  Gyroscope Temperature Accept Ready */
  uint8_t gyroTemperatureReady_valid;  /**< Must be set to true if gyroTemperatureReady is being passed */
  qmiLocSensorReadyStatusStructT_v02 gyroTemperatureReady;
  /**<   \vspace{0.06in} \n Indicates whether the GNSS location engine is ready
         to accept gyroscope temperature data.
   */

  /* Optional */
  /*  Calibrated Magnetometer Accept Ready */
  uint8_t calibratedMagReady_valid;  /**< Must be set to true if calibratedMagReady is being passed */
  qmiLocSensorReadyStatusStructT_v02 calibratedMagReady;
  /**<   \vspace{0.06in} \n Indicates whether the GNSS location engine is ready
         to accept calibrated magnetometer data.
   */

  /* Optional */
  /*  Uncalibrated Magnetometer Accept Ready */
  uint8_t uncalibratedMagReady_valid;  /**< Must be set to true if uncalibratedMagReady is being passed */
  qmiLocSensorReadyStatusStructT_v02 uncalibratedMagReady;
  /**<   \vspace{0.06in} \n Indicates whether the GNSS location engine is ready
         to accept uncalibrated magnetometer data.
   */
}qmiLocEventSensorStreamingReadyStatusIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Notifies the control point to inject time synchronization
                    data. */
typedef struct {

  /* Mandatory */
  /*  Opaque Time Sync Reference Counter */
  uint32_t refCounter;
  /**<   This TLV is sent to registered control points. It is sent by
        the location engine when it needs to synchronize location engine and
        control point (sensor processor) times.
        This TLV must be echoed back in the Time Sync Inject request. */
}qmiLocEventTimeSyncReqIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Requests the control point to enable Stationary Position
                    Indicator (SPI) streaming reports. */
typedef struct {

  /* Mandatory */
  /*  Enable/Disable SPI Requests */
  uint8_t enable;
  /**<   Indicates whether the client is to start or stop sending an SPI status stream.
       \begin{itemize1}
       \item    0x01 (TRUE)  -- Client is to start sending an SPI status stream
       \item    0x00 (FALSE) -- Client is to stop sending an SPI status stream
       \vspace{-0.18in} \end{itemize1}*/
}qmiLocEventSetSpiStreamingReportIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCWWANTYPEENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_WWAN_TYPE_INTERNET_V02 = 0, /**<  Bring up the WWAN type used for an Internet connection  */
  eQMI_LOC_WWAN_TYPE_AGNSS_V02 = 1, /**<  Bring up the WWAN type used for AGNSS connections  */
  eQMI_LOC_WWAN_TYPE_AGNSS_EMERGENCY_V02 = 2, /**<  Bring up the WWAN type used for AGNSS Emergency connections  */
  QMILOCWWANTYPEENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocWWANTypeEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCSERVERREQUESTENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_SERVER_REQUEST_OPEN_V02 = 1, /**<  Open a connection to the location server  */
  eQMI_LOC_SERVER_REQUEST_CLOSE_V02 = 2, /**<  Close a connection to the location server  */
  QMILOCSERVERREQUESTENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocServerRequestEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Requests the client to open or close a connection
                    to the assisted GPS location server. */
typedef struct {

  /* Mandatory */
  /*  Connection Handle */
  uint32_t connHandle;
  /**<   Identifies a connection across Open and Close request events. */

  /* Mandatory */
  /*  Request Type */
  qmiLocServerRequestEnumT_v02 requestType;
  /**<   Open or close a connection to the location server.

 Valid values: \n
      - eQMI_LOC_SERVER_REQUEST_OPEN (1) --  Open a connection to the location server
      - eQMI_LOC_SERVER_REQUEST_CLOSE (2) --  Close a connection to the location server
 */

  /* Mandatory */
  /*  WWAN Type */
  qmiLocWWANTypeEnumT_v02 wwanType;
  /**<   Identifies the WWAN type for this request.
 Valid values: \n
      - eQMI_LOC_WWAN_TYPE_INTERNET (0) --  Bring up the WWAN type used for an Internet connection
      - eQMI_LOC_WWAN_TYPE_AGNSS (1) --  Bring up the WWAN type used for AGNSS connections
      - eQMI_LOC_WWAN_TYPE_AGNSS_EMERGENCY (2) --  Bring up the WWAN type used for AGNSS Emergency connections
 */
}qmiLocEventLocationServerConnectionReqIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCNIGEOFENCEOPERATIONENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_NI_GEOFENCE_ADDED_V02 = 1, /**<  An NI Geofence was added  */
  eQMI_LOC_NI_GEOFENCE_DELETED_V02 = 2, /**<  An NI Geofence was deleted  */
  eQMI_LOC_NI_GEOFENCE_EDITED_V02 = 3, /**<  An NI Geofence was edited; the control point can query the
       Geofence to find the its current state  */
  QMILOCNIGEOFENCEOPERATIONENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocNiGeofenceOperationEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Informs the control point about
                    network-initiated Geofences. */
typedef struct {

  /* Mandatory */
  /*  Geofence ID */
  uint32_t geofenceId;
  /**<   ID of the Geofence for which this
       notification was generated. */

  /* Mandatory */
  /*  Operation Type */
  qmiLocNiGeofenceOperationEnumT_v02 operationType;
  /**<   Operation for which this notification was generated.

 Valid values: \n
      - eQMI_LOC_NI_GEOFENCE_ADDED (1) --  An NI Geofence was added
      - eQMI_LOC_NI_GEOFENCE_DELETED (2) --  An NI Geofence was deleted
      - eQMI_LOC_NI_GEOFENCE_EDITED (3) --  An NI Geofence was edited; the control point can query the
       Geofence to find the its current state
 */
}qmiLocEventNiGeofenceNotificationIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCGEOFENCEGENALERTENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_GEOFENCE_GEN_ALERT_GNSS_UNAVAILABLE_V02 = 1, /**<  GNSS is unavailable and GNSS position fixes
       cannot be used to monitor Geofences  */
  eQMI_LOC_GEOFENCE_GEN_ALERT_GNSS_AVAILABLE_V02 = 2, /**<  GNSS is now available and GNSS postion fixes can
       be used to monitor Geofences  */
  eQMI_LOC_GEOFENCE_GEN_ALERT_OOS_V02 = 3, /**<  The engine is out of service and no cell ID coverage
       information is available  */
  eQMI_LOC_GEOFENCE_GEN_ALERT_TIME_INVALID_V02 = 4, /**<  The engine has an invalid time  */
  QMILOCGEOFENCEGENALERTENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocGeofenceGenAlertEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Notifies the control point of the
                    Geofence status. */
typedef struct {

  /* Mandatory */
  /*  Geofence General Alert */
  qmiLocGeofenceGenAlertEnumT_v02 geofenceAlert;
  /**<   Specifies the Geofence general alert type.

 Valid values: \n
      - eQMI_LOC_GEOFENCE_GEN_ALERT_GNSS_UNAVAILABLE (1) --  GNSS is unavailable and GNSS position fixes
       cannot be used to monitor Geofences
      - eQMI_LOC_GEOFENCE_GEN_ALERT_GNSS_AVAILABLE (2) --  GNSS is now available and GNSS postion fixes can
       be used to monitor Geofences
      - eQMI_LOC_GEOFENCE_GEN_ALERT_OOS (3) --  The engine is out of service and no cell ID coverage
       information is available
      - eQMI_LOC_GEOFENCE_GEN_ALERT_TIME_INVALID (4) --  The engine has an invalid time
 */
}qmiLocEventGeofenceGenAlertIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCGEOFENCEBREACHTYPEENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_GEOFENCE_BREACH_TYPE_ENTERING_V02 = 1, /**<  Denotes that a client entered the Geofence  */
  eQMI_LOC_GEOFENCE_BREACH_TYPE_LEAVING_V02 = 2, /**<  Denotes that a client left the Geofence  */
  QMILOCGEOFENCEBREACHTYPEENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocGeofenceBreachTypeEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  /*  UTC Timestamp */
  uint64_t timestampUtc;
  /**<   UTC timestamp.
       \begin{itemize1}
       \item    Units: Milliseconds since Jan. 1, 1970
       \vspace{-0.18in} \end{itemize1} */

  /*  Latitude */
  double latitude;
  /**<   Latitude (specified in WGS84 datum).
       \begin{itemize1}
       \item    Type: Floating point
       \item    Units: Degrees
       \item    Range: -90.0 to 90.0       \begin{itemize1}
         \item    Positive values indicate northern latitude
         \item    Negative values indicate southern latitude
       \vspace{-0.18in} \end{itemize1} \end{itemize1} */

  /*   Longitude */
  double longitude;
  /**<   Longitude (specified in WGS84 datum).
       \begin{itemize1}
       \item    Type: Floating point
       \item    Units: Degrees
       \item    Range: -180.0 to 180.0     \begin{itemize1}
         \item    Positive values indicate eastern longitude
         \item    Negative values indicate western longitude
       \vspace{-0.18in} \end{itemize1} \end{itemize1} */

  /*  Horizontal Elliptical Uncertainty (Semi-Minor Axis) */
  float horUncEllipseSemiMinor;
  /**<   Semi-minor axis of horizontal elliptical uncertainty.\n
       - Units: Meters */

  /*  Horizontal Elliptical Uncertainty (Semi-Major Axis) */
  float horUncEllipseSemiMajor;
  /**<   Semi-major axis of horizontal elliptical uncertainty.\n
       - Units: Meters */

  /*  Elliptical Horizontal Uncertainty Azimuth */
  float horUncEllipseOrientAzimuth;
  /**<   Elliptical horizontal uncertainty azimuth of orientation.\n
       - Units: Decimal degrees \n
       - Range: 0 to 180 */

  /*  Horizontal Speed validity bit */
  uint8_t speedHorizontal_valid;
  /**<   Indicates whether the Horizontal speed field contains valid
       information.
       \begin{itemize1}
       \item    0x01 (TRUE)  --  Horizontal speed is valid
       \item    0x00 (FALSE) --  Horizontal speed is invalid
                                 and is to be ignored
       \vspace{-0.18in} \end{itemize1} */

  /*  Horizontal Speed */
  float speedHorizontal;
  /**<   Horizontal speed.\n
       - Units: Meters/second */

  /*  Altitude validity bit */
  uint8_t altitudeWrtEllipsoid_valid;
  /**<   Indicates whether the altitude field contains valid
       information.
       \begin{itemize1}
       \item    0x01 (TRUE)  --  Altitude field is valid
       \item    0x00 (FALSE) --  Altitude field is invalid
                                 and is to be ignored
       \vspace{-0.18in} \end{itemize1}
       */

  /*  Altitude With Respect to Ellipsoid */
  float altitudeWrtEllipsoid;
  /**<   Altitude with respect to the WGS84 ellipsoid.\n
       - Units: Meters \n
       - Range: -500 to 15883 */

  /*  Vertical Uncertainty validity bit */
  uint8_t vertUnc_valid;
  /**<   Indicates whether the Vertical Uncertainty field contains valid
       information.
       \begin{itemize1}
       \item    0x01 (TRUE)  --  Vertical Uncertainty field is valid
       \item    0x00 (FALSE) --  Vertical Uncertainty field is invalid
                                 and is to be ignored
       \vspace{-0.18in} \end{itemize1} */

  /*  Vertical Uncertainty */
  float vertUnc;
  /**<   Vertical uncertainty.\n
       - Units: Meters */

  /*  Vertical Speed validity bit */
  uint8_t speedVertical_valid;
  /**<   Indicates whether the Vertical Speed field contains valid
       information.
       \begin{itemize1}
       \item    0x01 (TRUE)  --  Vertical Speed field is valid
       \item    0x00 (FALSE) --  Vertical Speed field is invalid
                                 and is to be ignored
       \vspace{-0.18in} \end{itemize1} */

  /*  Vertical Speed */
  float speedVertical;
  /**<   Vertical speed.\n
       - Units: Meters/second */

  /*  heading validity bit */
  uint8_t heading_valid;
  /**<   Indicates whether the Heading field contains valid
       information.
       \begin{itemize1}
       \item    0x01 (TRUE)  --  Heading field is valid
       \item    0x00 (FALSE) --  Heading field is invalid
                                 and is to be ignored
       \vspace{-0.18in} \end{itemize1} */

  /*  Heading */
  float heading;
  /**<   Heading.\n
        - Units: Degrees \n
        - Range: 0 to 359.999  */
}qmiLocGeofencePositionStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCGEOFENCECONFIDENCEENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_GEOFENCE_CONFIDENCE_LOW_V02 = 0x01, /**<  Geofence engine indicates a breach with
       low confidence; this setting results in lower
       power usage, and it can impact the yield because
       incorrect breach events may be sent  */
  eQMI_LOC_GEOFENCE_CONFIDENCE_MED_V02 = 0x02, /**<  (Default) Geofence engine indicates a breach with
       medium confidence  */
  eQMI_LOC_GEOFENCE_CONFIDENCE_HIGH_V02 = 0x03, /**<  Geofence engine indicates a breach with
       high confidence; this setting results in higher
       power usage  */
  QMILOCGEOFENCECONFIDENCEENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocGeofenceConfidenceEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Notifies the control point of
                    a Geofence breach event. */
typedef struct {

  /* Mandatory */
  /*  Geofence ID */
  uint32_t geofenceId;
  /**<   ID of the Geofence for which this
       notification was generated. */

  /* Mandatory */
  /*  Geofence Breach Type */
  qmiLocGeofenceBreachTypeEnumT_v02 breachType;
  /**<   The type of breach that generated this event.

 Valid values: \n
      - eQMI_LOC_GEOFENCE_BREACH_TYPE_ENTERING (1) --  Denotes that a client entered the Geofence
      - eQMI_LOC_GEOFENCE_BREACH_TYPE_LEAVING (2) --  Denotes that a client left the Geofence
 */

  /* Optional */
  /*  Geofence Position */
  uint8_t geofencePosition_valid;  /**< Must be set to true if geofencePosition is being passed */
  qmiLocGeofencePositionStructT_v02 geofencePosition;
  /**<   \vspace{0.06in} \n Position of the client when it breached the Geofence.
       This TLV is included if the client configures the
       Geofence to report position. The position is reported
       at the same confidence level that was specified in the
       Add Circular Geofence request. */

  /* Optional */
  /*  Geofence Breach Confidence */
  uint8_t breachConfidence_valid;  /**< Must be set to true if breachConfidence is being passed */
  qmiLocGeofenceConfidenceEnumT_v02 breachConfidence;
  /**<   \vspace{0.06in} \n
 Given a breach event, the confidence determines the probability
 that the breach happened at the Geofence boundary.
 Valid values: \n
      - eQMI_LOC_GEOFENCE_CONFIDENCE_LOW (0x01) --  Geofence engine indicates a breach with
       low confidence; this setting results in lower
       power usage, and it can impact the yield because
       incorrect breach events may be sent
      - eQMI_LOC_GEOFENCE_CONFIDENCE_MED (0x02) --  (Default) Geofence engine indicates a breach with
       medium confidence
      - eQMI_LOC_GEOFENCE_CONFIDENCE_HIGH (0x03) --  Geofence engine indicates a breach with
       high confidence; this setting results in higher
       power usage
 */
}qmiLocEventGeofenceBreachIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Recommends how pedometer reports are to be
                    sent to the location engine. */
typedef struct {

  /* Mandatory */
  /*  Request Pedometer Data */
  uint8_t requestPedometerData;
  /**<   Indicates whether the GNSS location engine is requesting the client to
          send pedometer data.
       \begin{itemize1}
       \item    0x01 (TRUE)  -- GNSS location engine is requesting
                                pedometer data
       \item    0x00 (FALSE) -- GNSS location engine is not requesting
                                pedometer data
       \vspace{-0.18in} \end{itemize1}
  */

  /* Optional */
  /*  Reset Step Count */
  uint8_t resetStepCount_valid;  /**< Must be set to true if resetStepCount is being passed */
  uint8_t resetStepCount;
  /**<   Indicates whether the location engine is to reset the step count.
       \begin{itemize1}
       \item    0x01 (TRUE)  -- Pedometer step count is to be reset
       \item    0x00 (FALSE) -- Pedometer step count is not to be reset
       \vspace{-0.18in} \end{itemize1} */

  /* Optional */
  /*  Step Count Threshold */
  uint8_t stepCountThreshold_valid;  /**< Must be set to true if stepCountThreshold is being passed */
  uint32_t stepCountThreshold;
  /**<   Specifies the number of steps to be sampled in a pedometer report,
       as recommended by the the location engine. If the threshold is set to 0,
       the location engine wants a pedometer report at every step event.
  */
}qmiLocEventPedometerControlIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Recommends how motion data reports are to be
                    sent to the location engine. */
typedef struct {

  /* Mandatory */
  /*  Request Motion Data */
  uint8_t requestMotionData;
  /**<   Indicates whether the GNSS location engine is requesting
       the client to send motion data.
       \begin{itemize1}
       \item    0x01 (TRUE)  -- GNSS location engine is requesting
                                motion data
       \item    0x00 (FALSE) -- GNSS location engine is not requesting
                                motion data
       \vspace{-0.18in} \end{itemize1}
  */
}qmiLocEventMotionDataControlIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  /*  Low Geofence ID */
  uint32_t idLow;
  /**<   Contains the starting ID of the Geofence in the range of the continuous
       range of Geofences that were breached at the same position. */

  /*  High Geofence ID */
  uint32_t idHigh;
  /**<   Contains the ending ID of the Geofence in the range of the continuous
         range of Geofences that were breached at the same position. */
}qmiLocGeofenceIdContinuousStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Notifies the control point of a Geofence breach event by
                    batching all the Geofences that were breached. */
typedef struct {

  /* Mandatory */
  /*  Geofence Breach Type */
  qmiLocGeofenceBreachTypeEnumT_v02 breachType;
  /**<   Type of breach that generated this event.

 Valid values: \n
      - eQMI_LOC_GEOFENCE_BREACH_TYPE_ENTERING (1) --  Denotes that a client entered the Geofence
      - eQMI_LOC_GEOFENCE_BREACH_TYPE_LEAVING (2) --  Denotes that a client left the Geofence
 */

  /* Optional */
  /*  Geofence ID Continuous */
  uint8_t geofenceIdContinuousList_valid;  /**< Must be set to true if geofenceIdContinuousList is being passed */
  uint32_t geofenceIdContinuousList_len;  /**< Must be set to # of elements in geofenceIdContinuousList */
  qmiLocGeofenceIdContinuousStructT_v02 geofenceIdContinuousList[QMI_LOC_MAX_GEOFENCE_ID_CONTINUOUS_LIST_LENGTH_V02];
  /**<   \vspace{0.06in} \n Each entry in the list contains the continuous range of Geofence IDs that were breached
      at the same position. This list does not overlap with the discrete Geofence ID list. */

  /* Optional */
  /*  Geofence ID Discrete */
  uint8_t geofenceIdDiscreteList_valid;  /**< Must be set to true if geofenceIdDiscreteList is being passed */
  uint32_t geofenceIdDiscreteList_len;  /**< Must be set to # of elements in geofenceIdDiscreteList */
  uint32_t geofenceIdDiscreteList[QMI_LOC_MAX_GEOFENCE_ID_DISCRETE_LIST_LENGTH_V02];
  /**<   This list contains the Geofence IDs that were breached at the same position.
       This list does not overlap with the continuous Geofence ID list. */

  /* Optional */
  /*  Geofence Position */
  uint8_t geofencePosition_valid;  /**< Must be set to true if geofencePosition is being passed */
  qmiLocGeofencePositionStructT_v02 geofencePosition;
  /**<   \vspace{0.06in} \n Position of the client when it breached the Geofence.
       This TLV is included if the client configures the
       Geofence to report its position. The position is reported
       at the same confidence level that was specified in the
       Add Circular Geofence request. */

  /* Optional */
  /*  Geofence Breach Confidence */
  uint8_t breachConfidence_valid;  /**< Must be set to true if breachConfidence is being passed */
  qmiLocGeofenceConfidenceEnumT_v02 breachConfidence;
  /**<   \vspace{0.06in} \n
 Given a breach event, the confidence determines the probability
 that the breach happened at the Geofence boundary.
 Valid values: \n
      - eQMI_LOC_GEOFENCE_CONFIDENCE_LOW (0x01) --  Geofence engine indicates a breach with
       low confidence; this setting results in lower
       power usage, and it can impact the yield because
       incorrect breach events may be sent
      - eQMI_LOC_GEOFENCE_CONFIDENCE_MED (0x02) --  (Default) Geofence engine indicates a breach with
       medium confidence
      - eQMI_LOC_GEOFENCE_CONFIDENCE_HIGH (0x03) --  Geofence engine indicates a breach with
       high confidence; this setting results in higher
       power usage
 */

  /* Optional */
  /*  Heading Uncertainty */
  uint8_t headingUnc_valid;  /**< Must be set to true if headingUnc is being passed */
  float headingUnc;
  /**<   Heading uncertainty.\n
       - Units: Degrees \n
       - Range: 0 to 359.999 */

  /* Optional */
  /*  Vertical Uncertainty */
  uint8_t vertUnc_valid;  /**< Must be set to true if vertUnc is being passed */
  float vertUnc;
  /**<   Vertical uncertainty.\n
       - Units: Meters */

  /* Optional */
  /*  Speed Uncertainty */
  uint8_t speedUnc_valid;  /**< Must be set to true if speedUnc is being passed */
  float speedUnc;
  /**<   3-D speed uncertainty.\n
       - Units: Meters/second */

  /* Optional */
  /*  Horizontal Confidence */
  uint8_t horConfidence_valid;  /**< Must be set to true if horConfidence is being passed */
  uint8_t horConfidence;
  /**<   Horizontal uncertainty confidence.\n
       - Units: Percent \n
       - Range: 0 to 99 */

  /* Optional */
  /*  Vertical Confidence */
  uint8_t vertConfidence_valid;  /**< Must be set to true if vertConfidence is being passed */
  uint8_t vertConfidence;
  /**<   Vertical uncertainty confidence.\n
       - Units: Percent \n
       - Range: 0 to 99 */

  /* Optional */
  /*  Dilution of Precision */
  uint8_t DOP_valid;  /**< Must be set to true if DOP is being passed */
  qmiLocDOPStructT_v02 DOP;
  /**<   \vspace{0.06in} \n Dilution of precision associated with this position. */

  /* Optional */
  /*  SVs Used to Calculate the Fix */
  uint8_t gnssSvUsedList_valid;  /**< Must be set to true if gnssSvUsedList is being passed */
  uint32_t gnssSvUsedList_len;  /**< Must be set to # of elements in gnssSvUsedList */
  uint16_t gnssSvUsedList[QMI_LOC_MAX_SV_USED_LIST_LENGTH_V02];
  /**<   Each entry in the list contains the SV ID of a satellite
      used for calculating this position report. The following
      information is associated with each SV ID: \n
         Range:    \n
         - For GPS:     1 to 32 \n
         - For SBAS:    33 to 64 \n
         - For GLONASS: 65 to 96 \n
         - For QZSS:    193 to 197 \n
         - For BDS:     201 to 237
        */
}qmiLocEventGeofenceBatchedBreachIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCGEOFENCEPROXIMITYTYPEENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_GEOFENCE_PROXIMITY_TYPE_IN_V02 = 1, /**<  Denotes that a client is in proximity of the Geofence \n  */
  eQMI_LOC_GEOFENCE_PROXIMITY_TYPE_OUT_V02 = 2, /**<  Denotes that a client is out of proximity of the Geofence  */
  QMILOCGEOFENCEPROXIMITYTYPEENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocGeofenceProximityTypeEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Notifies the control point of a Geofence proximity event. */
typedef struct {

  /* Mandatory */
  /*  Geofence Breach Type */
  qmiLocGeofenceProximityTypeEnumT_v02 proximityType;
  /**<   Valid values: \n
      - eQMI_LOC_GEOFENCE_PROXIMITY_TYPE_IN (1) --  Denotes that a client is in proximity of the Geofence \n
      - eQMI_LOC_GEOFENCE_PROXIMITY_TYPE_OUT (2) --  Denotes that a client is out of proximity of the Geofence
 */

  /* Mandatory */
  /*  Geofence ID */
  uint32_t geofenceId;
  /**<   Identifier of the Geofence that is in proximity to the handset.
  */

  /* Optional */
  /*  Geofence Context ID */
  uint8_t contextId_valid;  /**< Must be set to true if contextId is being passed */
  uint32_t contextId;
  /**<    Identifier for the context of the Geofence to which the handset is in proximity.
        A single Geofence may be associated with different contexts.
  */
}qmiLocEventGeofenceProximityIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCGDTSERVICEIDENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_GDT_SERVICE_WWAN_V02 = 1, /**<  GDT Service for WWAN   */
  QMILOCGDTSERVICEIDENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocGdtServiceIdEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCGDTACCESSSTATUSENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_GDT_ACCESS_ALLOWED_V02 = 1, /**<  GDT ACCESS to the service is allowed   */
  eQMI_LOC_GDT_ACCESS_FAILED_V02 = 2, /**<  Any type of GDT access error   */
  eQMI_LOC_GDT_ACCESS_NOT_ALLOWED_V02 = 3, /**<  GDT ACCESS to the service is not allowed   */
  QMILOCGDTACCESSSTATUSENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocGdtAccessStatusEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Requests the control point to transfer data. */
typedef struct {

  /* Mandatory */
  /*  GDT service ID */
  qmiLocGdtServiceIdEnumT_v02 serviceId;

  /* Mandatory */
  /*  Session ID */
  uint32_t sessionId;

  /* Mandatory */
  /*  Data */
  uint32_t filePath_len;  /**< Must be set to # of elements in filePath */
  char filePath[QMI_LOC_MAX_GDT_PATH_LEN_V02];
  /**<   file path to the data. \n
         - Type: Array of bytes \n
         - Maximum length of the array: 255
    */
}qmiLocEventGdtUploadBeginStatusReqIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCGDTENDSTATUSENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_GDT_SUCCESS_V02 = 1, /**<  The sent data is accepeted   */
  eQMI_LOC_GDT_FAILED_V02 = 2, /**<  The sent data was not accepted   */
  eQMI_LOC_GDT_INVALID_V02 = 3, /**<  General error in received data  */
  QMILOCGDTENDSTATUSENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocGdtEndStatusEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Requests the control point to report the status of the
                    transfered data. */
typedef struct {

  /* Mandatory */
  /*  GDT service ID */
  qmiLocGdtServiceIdEnumT_v02 serviceId;

  /* Mandatory */
  /*  Session ID */
  uint32_t sessionId;

  /* Mandatory */
  /*  GDT End status */
  qmiLocGdtEndStatusEnumT_v02 endStatus;
}qmiLocEventGdtUploadEndReqIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCSTATUSENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_SUCCESS_V02 = 0, /**<  Request was completed successfully \n  */
  eQMI_LOC_GENERAL_FAILURE_V02 = 1, /**<  Request failed because of a general failure \n  */
  eQMI_LOC_UNSUPPORTED_V02 = 2, /**<  Request failed because it is not supported \n  */
  eQMI_LOC_INVALID_PARAMETER_V02 = 3, /**<  Request failed because it contained invalid parameters \n  */
  eQMI_LOC_ENGINE_BUSY_V02 = 4, /**<  Request failed because the engine is busy \n  */
  eQMI_LOC_PHONE_OFFLINE_V02 = 5, /**<  Request failed because the phone is offline \n  */
  eQMI_LOC_TIMEOUT_V02 = 6, /**<  Request failed because it timed out \n  */
  eQMI_LOC_CONFIG_NOT_SUPPORTED_V02 = 7, /**<  Request failed because an undefined configuration was requested \n  */
  eQMI_LOC_INSUFFICIENT_MEMORY_V02 = 8, /**<  Request failed because the engine could not allocate sufficient memory for the request \n  */
  eQMI_LOC_MAX_GEOFENCE_PROGRAMMED_V02 = 9, /**<  Request failed because the maximum number of Geofences are already programmed \n  */
  eQMI_LOC_XTRA_VERSION_CHECK_FAILURE_V02 = 10, /**<  Location service failed because of an XTRA version-based file format check failure  */
  QMILOCSTATUSENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocStatusEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Client can query the service revision using this message. */
typedef struct {
  /* This element is a placeholder to prevent the declaration of
     an empty struct.  DO NOT USE THIS FIELD UNDER ANY CIRCUMSTANCE */
  char __placeholder;
}qmiLocGetServiceRevisionReqMsgT_v02;

  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Client can query the service revision using this message. */
typedef struct {

  /* Mandatory */
  /*  Get Revision Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Get Revision request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */

  /* Mandatory */
  /*  Interface Definition Minor Revision */
  uint32_t revision;
  /**<   Revision of the service. This is the minor revision of the interface that
       the service implements. Minor revision updates of the service are always
       backward compatible. */

  /* Optional */
  /*  GNSS Measurement Engine Firmware Version String */
  uint8_t gnssMeFWVerString_valid;  /**< Must be set to true if gnssMeFWVerString is being passed */
  char gnssMeFWVerString[QMI_LOC_GNSS_ME_VERSION_STRING_MAX_LENGTH_V02 + 1];
  /**<   Version of the GNSS measurement engine software running under the LOC API.
       \begin{itemize1}
       \item    Type: NULL-terminated string
       \item    Maximum string length (including NULL terminator): 128
       \vspace{0.1in} \end{itemize1}

       \textbf{Note:} This string is only provided on platforms that have
       a measurement engine that supports this version string. On all other
       platforms, this optional TLV is not provided. */

  /* Optional */
  /*  GNSS Hosted Software Version String */
  uint8_t gnssHostSWVerString_valid;  /**< Must be set to true if gnssHostSWVerString is being passed */
  char gnssHostSWVerString[QMI_LOC_GNSS_HOSTED_SW_VERSION_STRING_MAX_LENGTH_V02 + 1];
  /**<   Version of the GNSS hosted software running under the LOC API.
       \begin{itemize1}
       \item    Type: NULL-terminated string
       \item    Maximum string length (including NULL terminator): 128
       \vspace{0.1in}\end{itemize1}

       \textbf{Note:} This string is only provided on hosted architectures
       (measurement and position engine running on different processors) that
       support this version string. On all other platforms, this optional TLV
       is not provided. */

  /* Optional */
  /*  GNSS Software Version String */
  uint8_t gnssSWVerString_valid;  /**< Must be set to true if gnssSWVerString is being passed */
  char gnssSWVerString[QMI_LOC_GNSS_SW_VERSION_STRING_MAX_LENGTH_V02 + 1];
  /**<   Aggregate version of the GNSS software.
       \begin{itemize1}
       \item    Type: NULL-terminated string
       \item    Maximum string length (including NULL terminator): 256
       \vspace{-0.18in} \end{itemize1} */
}qmiLocGetServiceRevisionIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Gets the fix criteria from the location engine. */
typedef struct {
  /* This element is a placeholder to prevent the declaration of
     an empty struct.  DO NOT USE THIS FIELD UNDER ANY CIRCUMSTANCE */
  char __placeholder;
}qmiLocGetFixCriteriaReqMsgT_v02;

  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Gets the fix criteria from the location engine. */
typedef struct {

  /* Mandatory */
  /*  Get Fix Criteria Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Get Fix Criteria request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */

  /* Optional */
  /*  Horizontal Accuracy */
  uint8_t horizontalAccuracyLevel_valid;  /**< Must be set to true if horizontalAccuracyLevel is being passed */
  qmiLocAccuracyLevelEnumT_v02 horizontalAccuracyLevel;
  /**<   Horizontal accuracy level.

 Valid values: \n
      - eQMI_LOC_ACCURACY_LOW (1) --  Low accuracy
      - eQMI_LOC_ACCURACY_MED (2) --  Medium accuracy
      - eQMI_LOC_ACCURACY_HIGH (3) --  High accuracy
 */

  /* Optional */
  /*  Enable/Disable Intermediate Fixes */
  uint8_t intermediateReportState_valid;  /**< Must be set to true if intermediateReportState is being passed */
  qmiLocIntermediateReportStateEnumT_v02 intermediateReportState;
  /**<   Intermediate Report state (ON, OFF).\n
 The client must explicitly set this field to OFF to stop receiving
 intermediate position reports. Intermediate position reports are
 generated at 1 Hz and are ON by default. If intermediate reports
 are turned ON, the client receives position reports even if the
 accuracy criteria is not met. The status in the position report is
 set to IN_PROGRESS for intermediate reports.

 Valid values: \n
      - eQMI_LOC_INTERMEDIATE_REPORTS_ON (1) --  Intermediate reports are turned on
      - eQMI_LOC_INTERMEDIATE_REPORTS_OFF (2) --  Intermediate reports are turned off
 */

  /* Optional */
  /*  Minimum Interval Between Fixes */
  uint8_t minInterval_valid;  /**< Must be set to true if minInterval is being passed */
  uint32_t minInterval;
  /**<   Time that must elapse before alerting the client. \n
       - Units: Milliseconds */

  /* Optional */
  /*  ID of the Application that Sent the Position Request */
  uint8_t applicationId_valid;  /**< Must be set to true if applicationId is being passed */
  qmiLocApplicationIdStructT_v02 applicationId;
  /**<   \vspace{0.06in} \n Application provider, name, and version.*/
}qmiLocGetFixCriteriaIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCNIUSERRESPENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_NI_LCS_NOTIFY_VERIFY_ACCEPT_V02 = 1, /**<  User accepted the Notify/Verify request  */
  eQMI_LOC_NI_LCS_NOTIFY_VERIFY_DENY_V02 = 2, /**<  User denied the Notify/Verify request  */
  eQMI_LOC_NI_LCS_NOTIFY_VERIFY_NORESP_V02 = 3, /**<  User did not respond to the Notify/Verify request  */
  QMILOCNIUSERRESPENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocNiUserRespEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Sends the NI user response back to the engine; success or
                    failure is reported in a separate indication. */
typedef struct {

  /* Mandatory */
  /*  User Response */
  qmiLocNiUserRespEnumT_v02 userResp;
  /**<   User accepted or denied.

 Valid values: \n
      - eQMI_LOC_NI_LCS_NOTIFY_VERIFY_ACCEPT (1) --  User accepted the Notify/Verify request
      - eQMI_LOC_NI_LCS_NOTIFY_VERIFY_DENY (2) --  User denied the Notify/Verify request
      - eQMI_LOC_NI_LCS_NOTIFY_VERIFY_NORESP (3) --  User did not respond to the Notify/Verify request
 */

  /* Mandatory */
  /*  Notification Type */
  qmiLocNiNotifyVerifyEnumT_v02 notificationType;
  /**<   Type of notification/verification performed.

 Valid values: \n
      - eQMI_LOC_NI_USER_NO_NOTIFY_NO_VERIFY (1) --  No notification and no verification required
      - eQMI_LOC_NI_USER_NOTIFY_ONLY (2) --  Notify only; no verification required
      - eQMI_LOC_NI_USER_NOTIFY_VERIFY_ALLOW_NO_RESP (3) --  Notify and verify, but no response required.
      - eQMI_LOC_NI_USER_NOTIFY_VERIFY_NOT_ALLOW_NO_RESP (4) --  Notify and verify, and require a response
      - eQMI_LOC_NI_USER_NOTIFY_VERIFY_PRIVACY_OVERRIDE (5) --  Notify and verify; privacy override
 */

  /* Optional */
  /*  Network Initiated Vx Request */
  uint8_t NiVxPayload_valid;  /**< Must be set to true if NiVxPayload is being passed */
  qmiLocNiVxNotifyVerifyStructT_v02 NiVxPayload;
  /**<   \vspace{0.06in} \n Optional NI VX request payload. */

  /* Optional */
  /*  Network Initiated SUPL Request */
  uint8_t NiSuplPayload_valid;  /**< Must be set to true if NiSuplPayload is being passed */
  qmiLocNiSuplNotifyVerifyStructT_v02 NiSuplPayload;
  /**<   \vspace{0.06in} \n Optional NI SUPL request payload. */

  /* Optional */
  /*  Network Initiated UMTS Control Plane Request */
  uint8_t NiUmtsCpPayload_valid;  /**< Must be set to true if NiUmtsCpPayload is being passed */
  qmiLocNiUmtsCpNotifyVerifyStructT_v02 NiUmtsCpPayload;
  /**<   \vspace{0.06in} \n Optional NI UMTS-CP request payload. */

  /* Optional */
  /*  Network Initiated Service Interaction Request */
  uint8_t NiVxServiceInteractionPayload_valid;  /**< Must be set to true if NiVxServiceInteractionPayload is being passed */
  qmiLocNiVxServiceInteractionStructT_v02 NiVxServiceInteractionPayload;
  /**<   \vspace{0.06in} \n Optional NI service interaction payload. */

  /* Optional */
  /*  Network Initiated SUPL Version 2 Extension */
  uint8_t NiSuplVer2ExtPayload_valid;  /**< Must be set to true if NiSuplVer2ExtPayload is being passed */
  qmiLocNiSuplVer2ExtStructT_v02 NiSuplVer2ExtPayload;
  /**<   \vspace{0.06in} \n Optional SUPL Version 2 Extension payload. */

  /* Optional */
  /*  SUPL Emergency Notification */
  uint8_t suplEmergencyNotification_valid;  /**< Must be set to true if suplEmergencyNotification is being passed */
  qmiLocEmergencyNotificationStructT_v02 suplEmergencyNotification;
  /**<    \vspace{0.06in} \n SUPL emergency notification payload. Emergency notification
        can be given even without an ESLP address */
}qmiLocNiUserRespReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Sends the NI user response back to the engine; success or
                    failure is reported in a separate indication. */
typedef struct {

  /* Mandatory */
  /*  NI User Response Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the NI User Response request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */
}qmiLocNiUserRespIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCPREDICTEDORBITSDATAFORMATENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_PREDICTED_ORBITS_XTRA_V02 = 0, /**<  Default is QCOM-XTRA format.  */
  QMILOCPREDICTEDORBITSDATAFORMATENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocPredictedOrbitsDataFormatEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Injects predicted orbits data. */
typedef struct {

  /* Mandatory */
  /*  Total Size */
  uint32_t totalSize;
  /**<   Total size of the predicted orbits data to be injected. \n
        - Units: Bytes */

  /* Mandatory */
  /*  Total Parts */
  uint16_t totalParts;
  /**<   Total number of parts into which the predicted orbits data is
        divided. */

  /* Mandatory */
  /*  Part Number */
  uint16_t partNum;
  /**<   Number of the current predicted orbits data part; starts at 1. */

  /* Mandatory */
  /*  Data */
  uint32_t partData_len;  /**< Must be set to # of elements in partData */
  char partData[QMI_LOC_MAX_PREDICTED_ORBITS_PART_LEN_V02];
  /**<   Predicted orbits data. \n
         - Type: Array of bytes \n
         - Maximum length of the array: 1024
    */

  /* Optional */
  /*  Format Type */
  uint8_t formatType_valid;  /**< Must be set to true if formatType is being passed */
  qmiLocPredictedOrbitsDataFormatEnumT_v02 formatType;
  /**<   Predicted orbits data format. \n
 Valid values: \n
      - eQMI_LOC_PREDICTED_ORBITS_XTRA (0) --  Default is QCOM-XTRA format.
 */
}qmiLocInjectPredictedOrbitsDataReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Injects predicted orbits data. */
typedef struct {

  /* Mandatory */
  /*  Data Injection Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Data Injection request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */

  /* Optional */
  /*  Part Number */
  uint8_t partNum_valid;  /**< Must be set to true if partNum is being passed */
  uint16_t partNum;
  /**<   Number of the predicted orbits data part for which this indication
      is sent; starts at 1. */
}qmiLocInjectPredictedOrbitsDataIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Gets the predicted orbits data source. */
typedef struct {
  /* This element is a placeholder to prevent the declaration of
     an empty struct.  DO NOT USE THIS FIELD UNDER ANY CIRCUMSTANCE */
  char __placeholder;
}qmiLocGetPredictedOrbitsDataSourceReqMsgT_v02;

  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Gets the predicted orbits data source. */
typedef struct {

  /* Mandatory */
  /*  Predicted Orbits Data Source Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the query request for a predicted orbits data source.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */

  /* Optional */
  /*  Allowed Sizes */
  uint8_t allowedSizes_valid;  /**< Must be set to true if allowedSizes is being passed */
  qmiLocPredictedOrbitsAllowedSizesStructT_v02 allowedSizes;
  /**<   \n Maximum part and file size allowed to be injected in the engine. */

  /* Optional */
  /*  Server List */
  uint8_t serverList_valid;  /**< Must be set to true if serverList is being passed */
  qmiLocPredictedOrbitsServerListStructT_v02 serverList;
  /**<   \n List of servers that can be used by the client to download
       predicted orbits data. */
}qmiLocGetPredictedOrbitsDataSourceIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Gets the predicted orbits data validity. */
typedef struct {
  /* This element is a placeholder to prevent the declaration of
     an empty struct.  DO NOT USE THIS FIELD UNDER ANY CIRCUMSTANCE */
  char __placeholder;
}qmiLocGetPredictedOrbitsDataValidityReqMsgT_v02;

  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  uint64_t startTimeInUTC;
  /**<   Predicted orbits data is valid starting from this time. \n
       - Units: Seconds (since Jan. 1, 1970)
        */

  uint16_t durationHours;
  /**<   Duration from the start time for which the data is valid.\n
       - Units: Hours
        */
}qmiLocPredictedOrbitsDataValidityStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Gets the predicted orbits data validity. */
typedef struct {

  /* Mandatory */
  /*  Predicted Orbits Data Validity Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the query request for predicted orbits data validity.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */

  /* Optional */
  /*  Validity Info */
  uint8_t validityInfo_valid;  /**< Must be set to true if validityInfo is being passed */
  qmiLocPredictedOrbitsDataValidityStructT_v02 validityInfo;
}qmiLocGetPredictedOrbitsDataValidityIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Injects UTC time in the location engine. */
typedef struct {

  /* Mandatory */
  /*  UTC Time */
  uint64_t timeUtc;
  /**<   UTC time since Jan. 1, 1970.\n
       - Units: Milliseconds */

  /* Mandatory */
  /*  Time Uncertainty */
  uint32_t timeUnc;
  /**<   Time uncertainty.\n
       - Units: Milliseconds */
}qmiLocInjectUtcTimeReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Injects UTC time in the location engine. */
typedef struct {

  /* Mandatory */
  /*  UTC Time Injection Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the UTC Time Injection request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */
}qmiLocInjectUtcTimeIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCALTSRCENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_ALT_SRC_UNKNOWN_V02 = 0, /**<  Source is unknown  */
  eQMI_LOC_ALT_SRC_GPS_V02 = 1, /**<  GPS is the source  */
  eQMI_LOC_ALT_SRC_CELL_ID_V02 = 2, /**<  Cell ID provided the source  */
  eQMI_LOC_ALT_SRC_ENHANCED_CELL_ID_V02 = 3, /**<  Source is enhanced cell ID  */
  eQMI_LOC_ALT_SRC_WIFI_V02 = 4, /**<  Wi-Fi is the source  */
  eQMI_LOC_ALT_SRC_TERRESTRIAL_V02 = 5, /**<  Terrestrial source  */
  eQMI_LOC_ALT_SRC_TERRESTRIAL_HYBRID_V02 = 6, /**<  Hybrid terrestrial source  */
  eQMI_LOC_ALT_SRC_ALTITUDE_DATABASE_V02 = 7, /**<  Altitude database is the source  */
  eQMI_LOC_ALT_SRC_BAROMETRIC_ALTIMETER_V02 = 8, /**<  Barometric altimeter is the source  */
  eQMI_LOC_ALT_SRC_OTHER_V02 = 9, /**<  Other sources  */
  QMILOCALTSRCENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocAltSrcEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCALTSRCLINKAGEENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_ALT_SRC_LINKAGE_NOT_SPECIFIED_V02 = 0, /**<  Not specified  */
  eQMI_LOC_ALT_SRC_LINKAGE_FULLY_INTERDEPENDENT_V02 = 1, /**<  Fully interdependent  */
  eQMI_LOC_ALT_SRC_LINKAGE_DEPENDS_ON_LAT_LONG_V02 = 2, /**<  Depends on latitude and longitude  */
  eQMI_LOC_ALT_SRC_LINKAGE_FULLY_INDEPENDENT_V02 = 3, /**<  Fully independent  */
  QMILOCALTSRCLINKAGEENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocAltSrcLinkageEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCALTSRCUNCERTAINTYCOVERAGEENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_ALT_UNCERTAINTY_NOT_SPECIFIED_V02 = 0, /**<  Not specified  */
  eQMI_LOC_ALT_UNCERTAINTY_POINT_V02 = 1, /**<  Altitude uncertainty is valid at the injected horizontal
       position coordinates only  */
  eQMI_LOC_ALT_UNCERTAINTY_FULL_V02 = 2, /**<  Altitude uncertainty applies to the position of the device
       regardless of horizontal position (within the horizontal
       uncertainty region, if provided)  */
  QMILOCALTSRCUNCERTAINTYCOVERAGEENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocAltSrcUncertaintyCoverageEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  qmiLocAltSrcEnumT_v02 source;
  /**<   Specifies the source of the altitude.

 Valid values: \n
      - eQMI_LOC_ALT_SRC_UNKNOWN (0) --  Source is unknown
      - eQMI_LOC_ALT_SRC_GPS (1) --  GPS is the source
      - eQMI_LOC_ALT_SRC_CELL_ID (2) --  Cell ID provided the source
      - eQMI_LOC_ALT_SRC_ENHANCED_CELL_ID (3) --  Source is enhanced cell ID
      - eQMI_LOC_ALT_SRC_WIFI (4) --  Wi-Fi is the source
      - eQMI_LOC_ALT_SRC_TERRESTRIAL (5) --  Terrestrial source
      - eQMI_LOC_ALT_SRC_TERRESTRIAL_HYBRID (6) --  Hybrid terrestrial source
      - eQMI_LOC_ALT_SRC_ALTITUDE_DATABASE (7) --  Altitude database is the source
      - eQMI_LOC_ALT_SRC_BAROMETRIC_ALTIMETER (8) --  Barometric altimeter is the source
      - eQMI_LOC_ALT_SRC_OTHER (9) --  Other sources
 */

  qmiLocAltSrcLinkageEnumT_v02 linkage;
  /**<   Specifies the dependency between the horizontal and
 altitude position components.

 Valid values: \n
      - eQMI_LOC_ALT_SRC_LINKAGE_NOT_SPECIFIED (0) --  Not specified
      - eQMI_LOC_ALT_SRC_LINKAGE_FULLY_INTERDEPENDENT (1) --  Fully interdependent
      - eQMI_LOC_ALT_SRC_LINKAGE_DEPENDS_ON_LAT_LONG (2) --  Depends on latitude and longitude
      - eQMI_LOC_ALT_SRC_LINKAGE_FULLY_INDEPENDENT (3) --  Fully independent
 */

  qmiLocAltSrcUncertaintyCoverageEnumT_v02 coverage;
  /**<   Specifies the region of uncertainty.

 Valid values: \n
      - eQMI_LOC_ALT_UNCERTAINTY_NOT_SPECIFIED (0) --  Not specified
      - eQMI_LOC_ALT_UNCERTAINTY_POINT (1) --  Altitude uncertainty is valid at the injected horizontal
       position coordinates only
      - eQMI_LOC_ALT_UNCERTAINTY_FULL (2) --  Altitude uncertainty applies to the position of the device
       regardless of horizontal position (within the horizontal
       uncertainty region, if provided)
 */
}qmiLocAltitudeSrcInfoStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCPOSITIONSRCENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_POSITION_SRC_GNSS_V02 = 0, /**<  Position source is GNSS  */
  eQMI_LOC_POSITION_SRC_CELLID_V02 = 1, /**<  Position source is Cell ID  */
  eQMI_LOC_POSITION_SRC_ENH_CELLID_V02 = 2, /**<  Position source is Enhanced Cell ID  */
  eQMI_LOC_POSITION_SRC_WIFI_V02 = 3, /**<  Position source is Wi-Fi  */
  eQMI_LOC_POSITION_SRC_TERRESTRIAL_V02 = 4, /**<  Position source is Terrestrial  */
  eQMI_LOC_POSITION_SRC_GNSS_TERRESTRIAL_HYBRID_V02 = 5, /**<  Position source is GNSS Terrestrial Hybrid  */
  eQMI_LOC_POSITION_SRC_OTHER_V02 = 6, /**<  Other sources  */
  QMILOCPOSITIONSRCENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocPositionSrcEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Injects a position to the location engine. */
typedef struct {

  /* Optional */
  /*  Latitude */
  uint8_t latitude_valid;  /**< Must be set to true if latitude is being passed */
  double latitude;
  /**<   Latitude (specified in WGS84 datum).
       \begin{itemize1}
       \item    Type: Floating point
       \item    Units: Degrees
       \item    Range: -90.0 to 90.0       \begin{itemize1}
         \item    Positive values indicate northern latitude
         \item    Negative values indicate southern latitude
       \vspace{-0.18in} \end{itemize1} \end{itemize1}
    */

  /* Optional */
  /*  Longitude */
  uint8_t longitude_valid;  /**< Must be set to true if longitude is being passed */
  double longitude;
  /**<   Longitude (specified in WGS84 datum).
       \begin{itemize1}
       \item    Type: Floating point
       \item    Units: Degrees
       \item    Range: -180.0 to 180.0     \begin{itemize1}
         \item    Positive values indicate eastern longitude
         \item    Negative values indicate western longitude
       \vspace{-0.18in} \end{itemize1} \end{itemize1}
   */

  /* Optional */
  /*  Circular Horizontal Uncertainty */
  uint8_t horUncCircular_valid;  /**< Must be set to true if horUncCircular is being passed */
  float horUncCircular;
  /**<   Horizontal position uncertainty (circular).\n
        - Units: Meters */

  /* Optional */
  /*  Horizontal Confidence */
  uint8_t horConfidence_valid;  /**< Must be set to true if horConfidence is being passed */
  uint8_t horConfidence;
  /**<   Horizontal confidence, as defined by ETSI TS 101 109 (\hyperref[S4]{[S4]}).
        \begin{itemize1}
        \item    Units: Percent (1 to 99)
        \item    0, 101 to 255 -- invalid value
        \item    If 100 is received, reinterpret to 99
        \end{itemize1}
        This field must be specified together with horizontal uncertainty.
        If not specified when horUncCircular is set, the default value is 50. */

  /* Optional */
  /*  Horizontal Reliability */
  uint8_t horReliability_valid;  /**< Must be set to true if horReliability is being passed */
  qmiLocReliabilityEnumT_v02 horReliability;
  /**<   Specifies the reliability of the horizontal position.

 Valid values: \n
      - eQMI_LOC_RELIABILITY_NOT_SET (0) --  Location reliability is not set
      - eQMI_LOC_RELIABILITY_VERY_LOW (1) --  Location reliability is very low; use it at your own risk
      - eQMI_LOC_RELIABILITY_LOW (2) --  Location reliability is low; little or no cross-checking is possible
      - eQMI_LOC_RELIABILITY_MEDIUM (3) --  Location reliability is medium; limited cross-check passed
      - eQMI_LOC_RELIABILITY_HIGH (4) --  Location reliability is high; strong cross-check passed
 */

  /* Optional */
  /*  Altitude With Respect to Ellipsoid */
  uint8_t altitudeWrtEllipsoid_valid;  /**< Must be set to true if altitudeWrtEllipsoid is being passed */
  float altitudeWrtEllipsoid;
  /**<   Altitude with respect to the WGS84 ellipsoid.
        \begin{itemize1}
        \item    Units: Meters    \begin{itemize1}
          \item    Positive = height
          \item    Negative = depth
        \vspace{-0.18in} \end{itemize1} \end{itemize1}*/

  /* Optional */
  /*  Altitude With Respect to Sea Level */
  uint8_t altitudeWrtMeanSeaLevel_valid;  /**< Must be set to true if altitudeWrtMeanSeaLevel is being passed */
  float altitudeWrtMeanSeaLevel;
  /**<   Altitude with respect to mean sea level.\n
       - Units: Meters */

  /* Optional */
  /*  Vertical Uncertainty */
  uint8_t vertUnc_valid;  /**< Must be set to true if vertUnc is being passed */
  float vertUnc;
  /**<   Vertical uncertainty. This is mandatory if either altitudeWrtEllipsoid
        or altitudeWrtMeanSeaLevel is specified.\n
        - Units: Meters */

  /* Optional */
  /*  Vertical Confidence */
  uint8_t vertConfidence_valid;  /**< Must be set to true if vertConfidence is being passed */
  uint8_t vertConfidence;
  /**<   Vertical confidence, as defined by  ETSI TS 101 109 (\hyperref[S4]{[S4]}).
        \begin{itemize1}
        \item    Units: Percent (0-99)
        \item    0 -- invalid value
        \item    100 to 256 -- not used
        \item    If 100 is received, reinterpret to 99
        \end{itemize1}
        This field must be specified together with the vertical uncertainty.
        If not specified, the default value will be 50. */

  /* Optional */
  /*  Vertical Reliability */
  uint8_t vertReliability_valid;  /**< Must be set to true if vertReliability is being passed */
  qmiLocReliabilityEnumT_v02 vertReliability;
  /**<   Specifies the reliability of the vertical position.

 Valid values: \n
      - eQMI_LOC_RELIABILITY_NOT_SET (0) --  Location reliability is not set
      - eQMI_LOC_RELIABILITY_VERY_LOW (1) --  Location reliability is very low; use it at your own risk
      - eQMI_LOC_RELIABILITY_LOW (2) --  Location reliability is low; little or no cross-checking is possible
      - eQMI_LOC_RELIABILITY_MEDIUM (3) --  Location reliability is medium; limited cross-check passed
      - eQMI_LOC_RELIABILITY_HIGH (4) --  Location reliability is high; strong cross-check passed
 */

  /* Optional */
  /*  Altitude Source Info */
  uint8_t altSourceInfo_valid;  /**< Must be set to true if altSourceInfo is being passed */
  qmiLocAltitudeSrcInfoStructT_v02 altSourceInfo;
  /**<   \vspace{0.06in} \n Specifies information regarding the altitude source. */

  /* Optional */
  /*  UTC Timestamp */
  uint8_t timestampUtc_valid;  /**< Must be set to true if timestampUtc is being passed */
  uint64_t timestampUtc;
  /**<   UTC timestamp. \n
        - Units: Milliseconds (since Jan. 1, 1970) */

  /* Optional */
  /*  Position Age */
  uint8_t timestampAge_valid;  /**< Must be set to true if timestampAge is being passed */
  int32_t timestampAge;
  /**<   Position age, which is an estimate of how long ago this fix was made. \n
        - Units: Milliseconds */

  /* Optional */
  /*  Position Source */
  uint8_t positionSrc_valid;  /**< Must be set to true if positionSrc is being passed */
  qmiLocPositionSrcEnumT_v02 positionSrc;
  /**<   Source from which this position was obtained.

 Valid values: \n
      - eQMI_LOC_POSITION_SRC_GNSS (0) --  Position source is GNSS
      - eQMI_LOC_POSITION_SRC_CELLID (1) --  Position source is Cell ID
      - eQMI_LOC_POSITION_SRC_ENH_CELLID (2) --  Position source is Enhanced Cell ID
      - eQMI_LOC_POSITION_SRC_WIFI (3) --  Position source is Wi-Fi
      - eQMI_LOC_POSITION_SRC_TERRESTRIAL (4) --  Position source is Terrestrial
      - eQMI_LOC_POSITION_SRC_GNSS_TERRESTRIAL_HYBRID (5) --  Position source is GNSS Terrestrial Hybrid
      - eQMI_LOC_POSITION_SRC_OTHER (6) --  Other sources

 If altitude is specified and the altitude source is not specified, the engine
 assumes that the altitude was obtained using the specified position source. \n
 If both altitude and altitude source are specified, the engine assumes
 that only latitude and longitude were obtained using the specified position
 source.
 */

  /* Optional */
  /*  Raw Circular Horizontal Uncertainty */
  uint8_t rawHorUncCircular_valid;  /**< Must be set to true if rawHorUncCircular is being passed */
  float rawHorUncCircular;
  /**<   Horizontal position uncertainty (circular) without any optimization.\n
        - Units: Meters */

  /* Optional */
  /*  Raw Horizontal Confidence */
  uint8_t rawHorConfidence_valid;  /**< Must be set to true if rawHorConfidence is being passed */
  uint8_t rawHorConfidence;
  /**<   Horizontal confidence associated with raw horizontal uncertainty,
        as defined by ETSI TS 101 109 (\hyperref[S4]{[S4]}).
        \begin{itemize1}
        \item    Units: Percent (1 to 99)
        \item    0, 101 to 255 -- invalid value
        \item    If 100 is received, reinterpret to 99
        \end{itemize1}
        This field must be specified together with raw horizontal uncertainty.
        If not specified when rawHorUncCircular is set, the default value is 50. */
}qmiLocInjectPositionReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Injects a position to the location engine. */
typedef struct {

  /* Mandatory */
  /*  UTC Position Injection Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the UTC Position Injection request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */
}qmiLocInjectPositionIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCLOCKENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_LOCK_NONE_V02 = 1, /**<  Do not lock any position sessions  */
  eQMI_LOC_LOCK_MI_V02 = 2, /**<  Lock mobile-initiated position sessions  */
  eQMI_LOC_LOCK_MT_V02 = 3, /**<  Lock mobile-terminated position sessions  */
  eQMI_LOC_LOCK_ALL_V02 = 4, /**<  Lock all position sessions  */
  QMILOCLOCKENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocLockEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Sets the location engine lock. */
typedef struct {

  /* Mandatory */
  /*  Lock Type */
  qmiLocLockEnumT_v02 lockType;
  /**<   Type of lock.

 Valid values: \n
      - eQMI_LOC_LOCK_NONE (1) --  Do not lock any position sessions
      - eQMI_LOC_LOCK_MI (2) --  Lock mobile-initiated position sessions
      - eQMI_LOC_LOCK_MT (3) --  Lock mobile-terminated position sessions
      - eQMI_LOC_LOCK_ALL (4) --  Lock all position sessions
 */
}qmiLocSetEngineLockReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Sets the location engine lock. */
typedef struct {

  /* Mandatory */
  /*  Set Engine Lock Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Set Engine Lock request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */
}qmiLocSetEngineLockIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Gets the location engine lock. */
typedef struct {
  /* This element is a placeholder to prevent the declaration of
     an empty struct.  DO NOT USE THIS FIELD UNDER ANY CIRCUMSTANCE */
  char __placeholder;
}qmiLocGetEngineLockReqMsgT_v02;

  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Gets the location engine lock. */
typedef struct {

  /* Mandatory */
  /*  Get Engine Lock Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Get Engine Lock request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */

  /* Optional */
  /*  Lock Type */
  uint8_t lockType_valid;  /**< Must be set to true if lockType is being passed */
  qmiLocLockEnumT_v02 lockType;
  /**<   Type of lock.

 Valid values: \n
      - eQMI_LOC_LOCK_NONE (1) --  Do not lock any position sessions
      - eQMI_LOC_LOCK_MI (2) --  Lock mobile-initiated position sessions
      - eQMI_LOC_LOCK_MT (3) --  Lock mobile-terminated position sessions
      - eQMI_LOC_LOCK_ALL (4) --  Lock all position sessions
 */
}qmiLocGetEngineLockIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Sets the SBAS configuration. */
typedef struct {

  /* Mandatory */
  /*  SBAS Config */
  uint8_t sbasConfig;
  /**<   Indicates whether SBAS configuration is enabled.
       \begin{itemize1}
       \item    0x01 (TRUE) -- SBAS configuration is enabled
       \item    0x00 (FALSE) -- SBAS configuration is disabled
       \vspace{-0.18in} \end{itemize1}*/
}qmiLocSetSbasConfigReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Sets the SBAS configuration. */
typedef struct {

  /* Mandatory */
  /*  Set SBAS Config Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Set SBAS Configuration request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */
}qmiLocSetSbasConfigIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Gets the SBAS configuration from the location engine. */
typedef struct {
  /* This element is a placeholder to prevent the declaration of
     an empty struct.  DO NOT USE THIS FIELD UNDER ANY CIRCUMSTANCE */
  char __placeholder;
}qmiLocGetSbasConfigReqMsgT_v02;

  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Gets the SBAS configuration from the location engine. */
typedef struct {

  /* Mandatory */
  /*  Get SBAS Config Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Get SBAS Configuration request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */

  /* Optional */
  /*  SBAS Config */
  uint8_t sbasConfig_valid;  /**< Must be set to true if sbasConfig is being passed */
  uint8_t sbasConfig;
  /**<   Indicates whether SBAS configuration is enabled.
       \begin{itemize1}
       \item    0x01 (TRUE) -- SBAS configuration is enabled
       \item    0x00 (FALSE) -- SBAS configuration is disabled
       \vspace{-0.18in} \end{itemize1}*/
}qmiLocGetSbasConfigIndMsgT_v02;  /* Message */
/**
    @}
  */

typedef uint32_t qmiLocNmeaSentenceMaskT_v02;
#define QMI_LOC_NMEA_MASK_GGA_V02 ((qmiLocNmeaSentenceMaskT_v02)0x00000001) /**<  Enable GGA type  */
#define QMI_LOC_NMEA_MASK_RMC_V02 ((qmiLocNmeaSentenceMaskT_v02)0x00000002) /**<  Enable RMC type  */
#define QMI_LOC_NMEA_MASK_GSV_V02 ((qmiLocNmeaSentenceMaskT_v02)0x00000004) /**<  Enable GSV type  */
#define QMI_LOC_NMEA_MASK_GSA_V02 ((qmiLocNmeaSentenceMaskT_v02)0x00000008) /**<  Enable GSA type  */
#define QMI_LOC_NMEA_MASK_VTG_V02 ((qmiLocNmeaSentenceMaskT_v02)0x00000010) /**<  Enable VTG type  */
#define QMI_LOC_NMEA_MASK_PQXFI_V02 ((qmiLocNmeaSentenceMaskT_v02)0x00000020) /**<  Enable PQXFI type  */
#define QMI_LOC_NMEA_MASK_PSTIS_V02 ((qmiLocNmeaSentenceMaskT_v02)0x00000040) /**<  Enable PSTIS type  */
#define QMI_LOC_NMEA_MASK_GLGSV_V02 ((qmiLocNmeaSentenceMaskT_v02)0x00000080) /**<  Enable GLGSV type  */
#define QMI_LOC_NMEA_MASK_GNGSA_V02 ((qmiLocNmeaSentenceMaskT_v02)0x00000100) /**<  Enable GNGSA type  */
#define QMI_LOC_NMEA_MASK_GNGNS_V02 ((qmiLocNmeaSentenceMaskT_v02)0x00000200) /**<  Enable GNGNS type  */
/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Sets the NMEA types. */
typedef struct {

  /* Mandatory */
  /*  NMEA Sentence Types */
  qmiLocNmeaSentenceMaskT_v02 nmeaSentenceType;
  /**<   Bitmasks of NMEA types to enable.

 Valid bitmasks: \n
      - QMI_LOC_NMEA_MASK_GGA (0x00000001) --  Enable GGA type
      - QMI_LOC_NMEA_MASK_RMC (0x00000002) --  Enable RMC type
      - QMI_LOC_NMEA_MASK_GSV (0x00000004) --  Enable GSV type
      - QMI_LOC_NMEA_MASK_GSA (0x00000008) --  Enable GSA type
      - QMI_LOC_NMEA_MASK_VTG (0x00000010) --  Enable VTG type
      - QMI_LOC_NMEA_MASK_PQXFI (0x00000020) --  Enable PQXFI type
      - QMI_LOC_NMEA_MASK_PSTIS (0x00000040) --  Enable PSTIS type
      - QMI_LOC_NMEA_MASK_GLGSV (0x00000080) --  Enable GLGSV type
      - QMI_LOC_NMEA_MASK_GNGSA (0x00000100) --  Enable GNGSA type
      - QMI_LOC_NMEA_MASK_GNGNS (0x00000200) --  Enable GNGNS type
 */
}qmiLocSetNmeaTypesReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Sets the NMEA types. */
typedef struct {

  /* Mandatory */
  /*  Set NMEA Types Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of Set NMEA Types request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */
}qmiLocSetNmeaTypesIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Gets the NMEA types from the location engine. */
typedef struct {
  /* This element is a placeholder to prevent the declaration of
     an empty struct.  DO NOT USE THIS FIELD UNDER ANY CIRCUMSTANCE */
  char __placeholder;
}qmiLocGetNmeaTypesReqMsgT_v02;

  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Gets the NMEA types from the location engine. */
typedef struct {

  /* Mandatory */
  /*  Get NMEA Types Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Get NMEA Types request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */

  /* Optional */
  /*  NMEA Sentence Types */
  uint8_t nmeaSentenceType_valid;  /**< Must be set to true if nmeaSentenceType is being passed */
  qmiLocNmeaSentenceMaskT_v02 nmeaSentenceType;
  /**<   NMEA types to enable.

 Valid bitmasks: \n
      - QMI_LOC_NMEA_MASK_GGA (0x00000001) --  Enable GGA type
      - QMI_LOC_NMEA_MASK_RMC (0x00000002) --  Enable RMC type
      - QMI_LOC_NMEA_MASK_GSV (0x00000004) --  Enable GSV type
      - QMI_LOC_NMEA_MASK_GSA (0x00000008) --  Enable GSA type
      - QMI_LOC_NMEA_MASK_VTG (0x00000010) --  Enable VTG type
      - QMI_LOC_NMEA_MASK_PQXFI (0x00000020) --  Enable PQXFI type
      - QMI_LOC_NMEA_MASK_PSTIS (0x00000040) --  Enable PSTIS type
      - QMI_LOC_NMEA_MASK_GLGSV (0x00000080) --  Enable GLGSV type
      - QMI_LOC_NMEA_MASK_GNGSA (0x00000100) --  Enable GNGSA type
      - QMI_LOC_NMEA_MASK_GNGNS (0x00000200) --  Enable GNGNS type
 */
}qmiLocGetNmeaTypesIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Enables/disables Low Power Mode (LPM) configuration. */
typedef struct {

  /* Mandatory */
  /*  Enable Low Power Mode */
  uint8_t lowPowerMode;
  /**<   Indicates whether to enable Low Power mode:\n
       - 0x01 (TRUE) -- Enable LPM \n
       - 0x00 (FALSE) -- Disable LPM */
}qmiLocSetLowPowerModeReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Enables/disables Low Power Mode (LPM) configuration. */
typedef struct {

  /* Mandatory */
  /*  Set LPM Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Set Low Power Mode request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */
}qmiLocSetLowPowerModeIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Gets the LPM status from the location engine. */
typedef struct {
  /* This element is a placeholder to prevent the declaration of
     an empty struct.  DO NOT USE THIS FIELD UNDER ANY CIRCUMSTANCE */
  char __placeholder;
}qmiLocGetLowPowerModeReqMsgT_v02;

  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Gets the LPM status from the location engine. */
typedef struct {

  /* Mandatory */
  /*  Get LPM Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Get LPM request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */

  /* Optional */
  /*  Enable/Disable LPM */
  uint8_t lowPowerMode_valid;  /**< Must be set to true if lowPowerMode is being passed */
  uint8_t lowPowerMode;
  /**<   Indicates whether to enable Low Power mode:\n
       - 0x01 (TRUE) -- Enable LPM \n
       - 0x00 (FALSE) -- Disable LPM */
}qmiLocGetLowPowerModeIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCSERVERTYPEENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_SERVER_TYPE_CDMA_PDE_V02 = 1, /**<  Server type is CDMA PDE  */
  eQMI_LOC_SERVER_TYPE_CDMA_MPC_V02 = 2, /**<  Server type is CDMA MPC  */
  eQMI_LOC_SERVER_TYPE_UMTS_SLP_V02 = 3, /**<  Server type is UMTS SLP  */
  eQMI_LOC_SERVER_TYPE_CUSTOM_PDE_V02 = 4, /**<  Server type is custom PDE  */
  QMILOCSERVERTYPEENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocServerTypeEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Specifies the A-GPS server type and address. */
typedef struct {

  /* Mandatory */
  /*  Server Type */
  qmiLocServerTypeEnumT_v02 serverType;
  /**<   Type of server.

 Valid values: \n
      - eQMI_LOC_SERVER_TYPE_CDMA_PDE (1) --  Server type is CDMA PDE
      - eQMI_LOC_SERVER_TYPE_CDMA_MPC (2) --  Server type is CDMA MPC
      - eQMI_LOC_SERVER_TYPE_UMTS_SLP (3) --  Server type is UMTS SLP
      - eQMI_LOC_SERVER_TYPE_CUSTOM_PDE (4) --  Server type is custom PDE
 */

  /* Optional */
  /*  IPv4 Address */
  uint8_t ipv4Addr_valid;  /**< Must be set to true if ipv4Addr is being passed */
  qmiLocIpV4AddrStructType_v02 ipv4Addr;
  /**<   \vspace{0.06in} \n IPv4 address and port. */

  /* Optional */
  /*  IPv6 Address */
  uint8_t ipv6Addr_valid;  /**< Must be set to true if ipv6Addr is being passed */
  qmiLocIpV6AddrStructType_v02 ipv6Addr;
  /**<   \vspace{0.06in} \n IPv6 address and port. */

  /* Optional */
  /*  Uniform Resource Locator */
  uint8_t urlAddr_valid;  /**< Must be set to true if urlAddr is being passed */
  char urlAddr[QMI_LOC_MAX_SERVER_ADDR_LENGTH_V02 + 1];
  /**<   URL address.
       \begin{itemize1}
       \item    Type: NULL-terminated string
       \item    Maximum string length (including NULL terminator): 256
       \vspace{-0.18in} \end{itemize1}
  */
}qmiLocSetServerReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Specifies the A-GPS server type and address. */
typedef struct {

  /* Mandatory */
  /*  Set Server Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Set Server request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */
}qmiLocSetServerIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Gets the location server from the location engine. */
typedef struct {

  /* Mandatory */
  /*  Server Type */
  qmiLocServerTypeEnumT_v02 serverType;
  /**<   Type of server.

 Valid values: \n
      - eQMI_LOC_SERVER_TYPE_CDMA_PDE (1) --  Server type is CDMA PDE
      - eQMI_LOC_SERVER_TYPE_CDMA_MPC (2) --  Server type is CDMA MPC
      - eQMI_LOC_SERVER_TYPE_UMTS_SLP (3) --  Server type is UMTS SLP
      - eQMI_LOC_SERVER_TYPE_CUSTOM_PDE (4) --  Server type is custom PDE
 */

  /* Optional */
  /*  Server Address Type */
  uint8_t serverAddrTypeMask_valid;  /**< Must be set to true if serverAddrTypeMask is being passed */
  qmiLocServerAddrTypeMaskT_v02 serverAddrTypeMask;
  /**<   Type of address the client wants. If unspecified, the
       indication will contain all the types of addresses
       it has for the specified server type.

       Valid bitmasks: \n
         - 0x01 -- IPv4 \n
         - 0x02 -- IPv6 \n
         - 0x04 -- URL
  */
}qmiLocGetServerReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Gets the location server from the location engine. */
typedef struct {

  /* Mandatory */
  /*  Get Server Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Get Server request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */

  /* Mandatory */
  /*  Server Type */
  qmiLocServerTypeEnumT_v02 serverType;
  /**<   Type of server.

 Valid values: \n
      - eQMI_LOC_SERVER_TYPE_CDMA_PDE (1) --  Server type is CDMA PDE
      - eQMI_LOC_SERVER_TYPE_CDMA_MPC (2) --  Server type is CDMA MPC
      - eQMI_LOC_SERVER_TYPE_UMTS_SLP (3) --  Server type is UMTS SLP
      - eQMI_LOC_SERVER_TYPE_CUSTOM_PDE (4) --  Server type is custom PDE
 */

  /* Optional */
  /*  IPv4 Address */
  uint8_t ipv4Addr_valid;  /**< Must be set to true if ipv4Addr is being passed */
  qmiLocIpV4AddrStructType_v02 ipv4Addr;
  /**<   \vspace{0.06in} \n IPv4 address and port. */

  /* Optional */
  /*  IPv6 Address */
  uint8_t ipv6Addr_valid;  /**< Must be set to true if ipv6Addr is being passed */
  qmiLocIpV6AddrStructType_v02 ipv6Addr;
  /**<   \vspace{0.06in} \n IPv6 address and port. */

  /* Optional */
  /*  Uniform Resource Locator */
  uint8_t urlAddr_valid;  /**< Must be set to true if urlAddr is being passed */
  char urlAddr[QMI_LOC_MAX_SERVER_ADDR_LENGTH_V02 + 1];
  /**<   URL.
       \begin{itemize1}
       \item    Type: NULL-terminated string
       \item    Maximum string length (including NULL terminator): 256
       \vspace{-0.18in} \end{itemize1}
  */
}qmiLocGetServerIndMsgT_v02;  /* Message */
/**
    @}
  */

typedef uint64_t qmiLocDeleteGnssDataMaskT_v02;
#define QMI_LOC_MASK_DELETE_GPS_SVDIR_V02 ((qmiLocDeleteGnssDataMaskT_v02)0x00000001ull) /**<  Mask to delete GPS SVDIR  */
#define QMI_LOC_MASK_DELETE_GPS_SVSTEER_V02 ((qmiLocDeleteGnssDataMaskT_v02)0x00000002ull) /**<  Mask to delete GPS SVSTEER  */
#define QMI_LOC_MASK_DELETE_GPS_TIME_V02 ((qmiLocDeleteGnssDataMaskT_v02)0x00000004ull) /**<  Mask to delete GPS time  */
#define QMI_LOC_MASK_DELETE_GPS_ALM_CORR_V02 ((qmiLocDeleteGnssDataMaskT_v02)0x00000008ull) /**<  Mask to delete almanac correlation  */
#define QMI_LOC_MASK_DELETE_GLO_SVDIR_V02 ((qmiLocDeleteGnssDataMaskT_v02)0x00000010ull) /**<  Mask to delete GLONASS SVDIR  */
#define QMI_LOC_MASK_DELETE_GLO_SVSTEER_V02 ((qmiLocDeleteGnssDataMaskT_v02)0x00000020ull) /**<  Mask to delete GLONASS SVSTEER  */
#define QMI_LOC_MASK_DELETE_GLO_TIME_V02 ((qmiLocDeleteGnssDataMaskT_v02)0x00000040ull) /**<  Mask to delete GLONASS time  */
#define QMI_LOC_MASK_DELETE_GLO_ALM_CORR_V02 ((qmiLocDeleteGnssDataMaskT_v02)0x00000080ull) /**<  Mask to delete GLONASS almanac correlation  */
#define QMI_LOC_MASK_DELETE_SBAS_SVDIR_V02 ((qmiLocDeleteGnssDataMaskT_v02)0x00000100ull) /**<  Mask to delete SBAS SVDIR  */
#define QMI_LOC_MASK_DELETE_SBAS_SVSTEER_V02 ((qmiLocDeleteGnssDataMaskT_v02)0x00000200ull) /**<  Mask to delete SBAS SVSTEER  */
#define QMI_LOC_MASK_DELETE_POSITION_V02 ((qmiLocDeleteGnssDataMaskT_v02)0x00000400ull) /**<  Mask to delete position estimate  */
#define QMI_LOC_MASK_DELETE_TIME_V02 ((qmiLocDeleteGnssDataMaskT_v02)0x00000800ull) /**<  Mask to delete time estimate  */
#define QMI_LOC_MASK_DELETE_IONO_V02 ((qmiLocDeleteGnssDataMaskT_v02)0x00001000ull) /**<  Mask to delete IONO  */
#define QMI_LOC_MASK_DELETE_UTC_V02 ((qmiLocDeleteGnssDataMaskT_v02)0x00002000ull) /**<  Mask to delete UTC estimate  */
#define QMI_LOC_MASK_DELETE_HEALTH_V02 ((qmiLocDeleteGnssDataMaskT_v02)0x00004000ull) /**<  Mask to delete SV health record  */
#define QMI_LOC_MASK_DELETE_SADATA_V02 ((qmiLocDeleteGnssDataMaskT_v02)0x00008000ull) /**<  Mask to delete SADATA  */
#define QMI_LOC_MASK_DELETE_RTI_V02 ((qmiLocDeleteGnssDataMaskT_v02)0x00010000ull) /**<  Mask to delete RTI  */
#define QMI_LOC_MASK_DELETE_SV_NO_EXIST_V02 ((qmiLocDeleteGnssDataMaskT_v02)0x00020000ull) /**<  Mask to delete SV_NO_EXIST  */
#define QMI_LOC_MASK_DELETE_FREQ_BIAS_EST_V02 ((qmiLocDeleteGnssDataMaskT_v02)0x00040000ull) /**<  Mask to delete frequency bias estimate  */
#define QMI_LOC_MASK_DELETE_BDS_SVDIR_V02 ((qmiLocDeleteGnssDataMaskT_v02)0x00080000ull) /**<  Mask to delete BDS SVDIR  */
#define QMI_LOC_MASK_DELETE_BDS_SVSTEER_V02 ((qmiLocDeleteGnssDataMaskT_v02)0x00100000ull) /**<  Mask to delete BDS SVSTEER  */
#define QMI_LOC_MASK_DELETE_BDS_TIME_V02 ((qmiLocDeleteGnssDataMaskT_v02)0x00200000ull) /**<  Mask to delete BDS time  */
#define QMI_LOC_MASK_DELETE_BDS_ALM_CORR_V02 ((qmiLocDeleteGnssDataMaskT_v02)0x00400000ull) /**<  Mask to delete BDS almanac correlation  */
#define QMI_LOC_MASK_DELETE_GNSS_SV_BLACKLIST_GPS_V02 ((qmiLocDeleteGnssDataMaskT_v02)0x00800000ull) /**<  Mask to delete GNSS SV blacklist GPS   */
#define QMI_LOC_MASK_DELETE_GNSS_SV_BLACKLIST_GLO_V02 ((qmiLocDeleteGnssDataMaskT_v02)0x01000000ull) /**<  Mask to delete GNSS SV blacklist GLO   */
#define QMI_LOC_MASK_DELETE_GNSS_SV_BLACKLIST_BDS_V02 ((qmiLocDeleteGnssDataMaskT_v02)0x02000000ull) /**<  Mask to delete GNSS SV blacklist BDS   */
typedef uint32_t qmiLocDeleteCelldbDataMaskT_v02;
#define QMI_LOC_MASK_DELETE_CELLDB_POS_V02 ((qmiLocDeleteCelldbDataMaskT_v02)0x00000001) /**<  Mask to delete cell database position  */
#define QMI_LOC_MASK_DELETE_CELLDB_LATEST_GPS_POS_V02 ((qmiLocDeleteCelldbDataMaskT_v02)0x00000002) /**<  Mask to delete cell database latest GPS position  */
#define QMI_LOC_MASK_DELETE_CELLDB_OTA_POS_V02 ((qmiLocDeleteCelldbDataMaskT_v02)0x00000004) /**<  Mask to delete cell database OTA position  */
#define QMI_LOC_MASK_DELETE_CELLDB_EXT_REF_POS_V02 ((qmiLocDeleteCelldbDataMaskT_v02)0x00000008) /**<  Mask to delete cell database external reference position  */
#define QMI_LOC_MASK_DELETE_CELLDB_TIMETAG_V02 ((qmiLocDeleteCelldbDataMaskT_v02)0x00000010) /**<  Mask to delete cell database time tag  */
#define QMI_LOC_MASK_DELETE_CELLDB_CELLID_V02 ((qmiLocDeleteCelldbDataMaskT_v02)0x00000020) /**<  Mask to delete cell database cell ID  */
#define QMI_LOC_MASK_DELETE_CELLDB_CACHED_CELLID_V02 ((qmiLocDeleteCelldbDataMaskT_v02)0x00000040) /**<  Mask to delete cell database cached cell ID  */
#define QMI_LOC_MASK_DELETE_CELLDB_LAST_SRV_CELL_V02 ((qmiLocDeleteCelldbDataMaskT_v02)0x00000080) /**<  Mask to delete cell database last service cell  */
#define QMI_LOC_MASK_DELETE_CELLDB_CUR_SRV_CELL_V02 ((qmiLocDeleteCelldbDataMaskT_v02)0x00000100) /**<  Mask to delete cell database current service cell  */
#define QMI_LOC_MASK_DELETE_CELLDB_NEIGHBOR_INFO_V02 ((qmiLocDeleteCelldbDataMaskT_v02)0x00000200) /**<  Mask to delete cell database neighbor information  */
typedef uint32_t qmiLocDeleteClockInfoMaskT_v02;
#define QMI_LOC_MASK_DELETE_CLOCK_INFO_TIME_EST_V02 ((qmiLocDeleteClockInfoMaskT_v02)0x00000001) /**<  Mask to delete time estimate from clock information  */
#define QMI_LOC_MASK_DELETE_CLOCK_INFO_FREQ_EST_V02 ((qmiLocDeleteClockInfoMaskT_v02)0x00000002) /**<  Mask to delete frequency estimate from clock information  */
#define QMI_LOC_MASK_DELETE_CLOCK_INFO_WEEK_NUMBER_V02 ((qmiLocDeleteClockInfoMaskT_v02)0x00000004) /**<  Mask to delete week number from clock information  */
#define QMI_LOC_MASK_DELETE_CLOCK_INFO_RTC_TIME_V02 ((qmiLocDeleteClockInfoMaskT_v02)0x00000008) /**<  Mask to delete RTC time from clock information  */
#define QMI_LOC_MASK_DELETE_CLOCK_INFO_TIME_TRANSFER_V02 ((qmiLocDeleteClockInfoMaskT_v02)0x00000010) /**<  Mask to delete time transfer from clock information  */
#define QMI_LOC_MASK_DELETE_CLOCK_INFO_GPSTIME_EST_V02 ((qmiLocDeleteClockInfoMaskT_v02)0x00000020) /**<  Mask to delete GPS time estimate from clock information  */
#define QMI_LOC_MASK_DELETE_CLOCK_INFO_GLOTIME_EST_V02 ((qmiLocDeleteClockInfoMaskT_v02)0x00000040) /**<  Mask to delete GLONASS time estimate from clock information  */
#define QMI_LOC_MASK_DELETE_CLOCK_INFO_GLODAY_NUMBER_V02 ((qmiLocDeleteClockInfoMaskT_v02)0x00000080) /**<  Mask to delete GLONASS day number from clock information  */
#define QMI_LOC_MASK_DELETE_CLOCK_INFO_GLO4YEAR_NUMBER_V02 ((qmiLocDeleteClockInfoMaskT_v02)0x00000100) /**<  Mask to delete GLONASS four year number from clock information  */
#define QMI_LOC_MASK_DELETE_CLOCK_INFO_GLO_RF_GRP_DELAY_V02 ((qmiLocDeleteClockInfoMaskT_v02)0x00000200) /**<  Mask to delete GLONASS RF GRP delay from clock information  */
#define QMI_LOC_MASK_DELETE_CLOCK_INFO_DISABLE_TT_V02 ((qmiLocDeleteClockInfoMaskT_v02)0x00000400) /**<  Mask to delete disable TT from clock information  */
#define QMI_LOC_MASK_DELETE_CLOCK_INFO_GG_LEAPSEC_V02 ((qmiLocDeleteClockInfoMaskT_v02)0x00000800) /**<  Mask to delete a BDS time estimate from the clock information  */
#define QMI_LOC_MASK_DELETE_CLOCK_INFO_GG_GGTB_V02 ((qmiLocDeleteClockInfoMaskT_v02)0x00001000) /**<  Mask to delete a BDS time estimate from the clock information  */
#define QMI_LOC_MASK_DELETE_CLOCK_INFO_BDSTIME_EST_V02 ((qmiLocDeleteClockInfoMaskT_v02)0x00002000) /**<  Mask to delete a BDS time estimate from the clock information  */
#define QMI_LOC_MASK_DELETE_CLOCK_INFO_GB_GBTB_V02 ((qmiLocDeleteClockInfoMaskT_v02)0x00004000) /**<  Mask to delete Glonass-to-BDS time bias-related information from the
      clock information  */
#define QMI_LOC_MASK_DELETE_CLOCK_INFO_BG_BGTB_V02 ((qmiLocDeleteClockInfoMaskT_v02)0x00008000) /**<  Mask to delete BDS-to-GLONASS time bias-related information from the
       clock information  */
#define QMI_LOC_MASK_DELETE_CLOCK_INFO_BDSWEEK_NUMBER_V02 ((qmiLocDeleteClockInfoMaskT_v02)0x00010000) /**<  Mask to delete the BDS week number from the clock information  */
#define QMI_LOC_MASK_DELETE_CLOCK_INFO_BDS_RF_GRP_DELAY_V02 ((qmiLocDeleteClockInfoMaskT_v02)0x00020000) /**<  Mask to delete the BDS RF GRP delay from the clock information  */
typedef uint8_t qmiLocDeleteSvInfoMaskT_v02;
#define QMI_LOC_MASK_DELETE_EPHEMERIS_V02 ((qmiLocDeleteSvInfoMaskT_v02)0x01) /**<  Delete ephemeris for the satellite  */
#define QMI_LOC_MASK_DELETE_ALMANAC_V02 ((qmiLocDeleteSvInfoMaskT_v02)0x02) /**<  Delete almanac for the satellite  */
/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  uint16_t gnssSvId;
  /**<   SV ID of the satellite whose data is to be deleted.
       \begin{itemize1}
       \item    Range:    \begin{itemize1}
         \item    For GPS:     1 to 32
         \item    For SBAS:    33 to 64
         \item    For GLONASS: 65 to 96
       \vspace{-0.18in} \end{itemize1} \end{itemize1} */

  qmiLocSvSystemEnumT_v02 system;
  /**<   Indicates to which constellation this SV belongs.

 Valid values: \n
      - eQMI_LOC_SV_SYSTEM_GPS (1) --  GPS satellite
      - eQMI_LOC_SV_SYSTEM_GALILEO (2) --  GALILEO satellite
      - eQMI_LOC_SV_SYSTEM_SBAS (3) --  SBAS satellite
      - eQMI_LOC_SV_SYSTEM_COMPASS (4) --  COMPASS satellite
      - eQMI_LOC_SV_SYSTEM_GLONASS (5) --  GLONASS satellite
      - eQMI_LOC_SV_SYSTEM_BDS (6) --  BDS satellite
 */

  qmiLocDeleteSvInfoMaskT_v02 deleteSvInfoMask;
  /**<   Indicates if the ephemeris or almanac for a satellite
       is to be deleted. \n
       Valid values: \n
       - 0x01 -- DELETE_EPHEMERIS \n
       - 0x02 -- DELETE_ALMANAC
  */
}qmiLocDeleteSvInfoStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  uint16_t gnssSvId;
  /**<   SV ID of the satellite whose data is to be deleted. \n
       Range for BDS:     201 to 237 */

  qmiLocDeleteSvInfoMaskT_v02 deleteSvInfoMask;
  /**<   Indicates if the ephemeris or almanac for a satellite
 is to be deleted. \n
 Valid values: \n
      - QMI_LOC_MASK_DELETE_EPHEMERIS (0x01) --  Delete ephemeris for the satellite
      - QMI_LOC_MASK_DELETE_ALMANAC (0x02) --  Delete almanac for the satellite
 */
}qmiLocDeleteBDSSvInfoStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; This command is used to delete the location engine
                    assistance data */
typedef struct {

  /* Mandatory */
  /*  Delete All */
  uint8_t deleteAllFlag;
  /**<   Indicates whether all assistance data is to be deleted.

       Valid values: \begin{itemize1}
       \item    0x01 (TRUE)  -- All assistance data is to be deleted; if
                                this flag is set, all the other information
                         contained in the optional fields for this
                                message are ignored
       \item    0x00 (FALSE) -- The optional fields in the message are to be
                                used to determine which data is to be deleted
       \vspace{-0.18in} \end{itemize1} */

  /* Optional */
  /*  Delete SV Info */
  uint8_t deleteSvInfoList_valid;  /**< Must be set to true if deleteSvInfoList is being passed */
  uint32_t deleteSvInfoList_len;  /**< Must be set to # of elements in deleteSvInfoList */
  qmiLocDeleteSvInfoStructT_v02 deleteSvInfoList[QMI_LOC_DELETE_MAX_SV_INFO_LENGTH_V02];
  /**<   \vspace{0.06in} \n List of satellites for which the assistance data is to be deleted.
  */

  /* Optional */
  /*  Delete GNSS Data */
  uint8_t deleteGnssDataMask_valid;  /**< Must be set to true if deleteGnssDataMask is being passed */
  qmiLocDeleteGnssDataMaskT_v02 deleteGnssDataMask;
  /**<   Mask for the GNSS data that is to be deleted.

 Valid values: \n
      - QMI_LOC_MASK_DELETE_GPS_SVDIR (0x00000001) --  Mask to delete GPS SVDIR
      - QMI_LOC_MASK_DELETE_GPS_SVSTEER (0x00000002) --  Mask to delete GPS SVSTEER
      - QMI_LOC_MASK_DELETE_GPS_TIME (0x00000004) --  Mask to delete GPS time
      - QMI_LOC_MASK_DELETE_GPS_ALM_CORR (0x00000008) --  Mask to delete almanac correlation
      - QMI_LOC_MASK_DELETE_GLO_SVDIR (0x00000010) --  Mask to delete GLONASS SVDIR
      - QMI_LOC_MASK_DELETE_GLO_SVSTEER (0x00000020) --  Mask to delete GLONASS SVSTEER
      - QMI_LOC_MASK_DELETE_GLO_TIME (0x00000040) --  Mask to delete GLONASS time
      - QMI_LOC_MASK_DELETE_GLO_ALM_CORR (0x00000080) --  Mask to delete GLONASS almanac correlation
      - QMI_LOC_MASK_DELETE_SBAS_SVDIR (0x00000100) --  Mask to delete SBAS SVDIR
      - QMI_LOC_MASK_DELETE_SBAS_SVSTEER (0x00000200) --  Mask to delete SBAS SVSTEER
      - QMI_LOC_MASK_DELETE_POSITION (0x00000400) --  Mask to delete position estimate
      - QMI_LOC_MASK_DELETE_TIME (0x00000800) --  Mask to delete time estimate
      - QMI_LOC_MASK_DELETE_IONO (0x00001000) --  Mask to delete IONO
      - QMI_LOC_MASK_DELETE_UTC (0x00002000) --  Mask to delete UTC estimate
      - QMI_LOC_MASK_DELETE_HEALTH (0x00004000) --  Mask to delete SV health record
      - QMI_LOC_MASK_DELETE_SADATA (0x00008000) --  Mask to delete SADATA
      - QMI_LOC_MASK_DELETE_RTI (0x00010000) --  Mask to delete RTI
      - QMI_LOC_MASK_DELETE_SV_NO_EXIST (0x00020000) --  Mask to delete SV_NO_EXIST
      - QMI_LOC_MASK_DELETE_FREQ_BIAS_EST (0x00040000) --  Mask to delete frequency bias estimate
      - QMI_LOC_MASK_DELETE_BDS_SVDIR (0x00080000) --  Mask to delete BDS SVDIR
      - QMI_LOC_MASK_DELETE_BDS_SVSTEER (0x00100000) --  Mask to delete BDS SVSTEER
      - QMI_LOC_MASK_DELETE_BDS_TIME (0x00200000) --  Mask to delete BDS time
      - QMI_LOC_MASK_DELETE_BDS_ALM_CORR (0x00400000) --  Mask to delete BDS almanac correlation
      - QMI_LOC_MASK_DELETE_GNSS_SV_BLACKLIST_GPS (0x00800000) --  Mask to delete GNSS SV blacklist GPS
      - QMI_LOC_MASK_DELETE_GNSS_SV_BLACKLIST_GLO (0x01000000) --  Mask to delete GNSS SV blacklist GLO
      - QMI_LOC_MASK_DELETE_GNSS_SV_BLACKLIST_BDS (0x02000000) --  Mask to delete GNSS SV blacklist BDS
 */

  /* Optional */
  /*  Delete Cell Database */
  uint8_t deleteCellDbDataMask_valid;  /**< Must be set to true if deleteCellDbDataMask is being passed */
  qmiLocDeleteCelldbDataMaskT_v02 deleteCellDbDataMask;
  /**<   Mask for the cell database assistance data that is to be deleted.

       Valid values: \begin{itemize1}
       \item    0x00000001 -- DELETE_CELLDB_ POS
       \item    0x00000002 -- DELETE_CELLDB_ LATEST_GPS_POS
       \item    0x00000004 -- DELETE_CELLDB_ OTA_POS
       \item    0x00000008 -- DELETE_CELLDB_ EXT_REF_POS
       \item    0x00000010 -- DELETE_CELLDB_ TIMETAG
       \item    0x00000020 -- DELETE_CELLDB_ CELLID
       \item    0x00000040 -- DELETE_CELLDB_ CACHED_CELLID
       \item    0x00000080 -- DELETE_CELLDB_ LAST_SRV_CELL
       \item    0x00000100 -- DELETE_CELLDB_ CUR_SRV_CELL
       \item    0x00000200 -- DELETE_CELLDB_ NEIGHBOR_INFO
       \vspace{-0.18in} \end{itemize1}
  */

  /* Optional */
  /*  Delete Clock Info */
  uint8_t deleteClockInfoMask_valid;  /**< Must be set to true if deleteClockInfoMask is being passed */
  qmiLocDeleteClockInfoMaskT_v02 deleteClockInfoMask;
  /**<   Mask for the clock information assistance data that is to be deleted.

 Valid bitmasks: \n
      - QMI_LOC_MASK_DELETE_CLOCK_INFO_TIME_EST (0x00000001) --  Mask to delete time estimate from clock information
      - QMI_LOC_MASK_DELETE_CLOCK_INFO_FREQ_EST (0x00000002) --  Mask to delete frequency estimate from clock information
      - QMI_LOC_MASK_DELETE_CLOCK_INFO_WEEK_NUMBER (0x00000004) --  Mask to delete week number from clock information
      - QMI_LOC_MASK_DELETE_CLOCK_INFO_RTC_TIME (0x00000008) --  Mask to delete RTC time from clock information
      - QMI_LOC_MASK_DELETE_CLOCK_INFO_TIME_TRANSFER (0x00000010) --  Mask to delete time transfer from clock information
      - QMI_LOC_MASK_DELETE_CLOCK_INFO_GPSTIME_EST (0x00000020) --  Mask to delete GPS time estimate from clock information
      - QMI_LOC_MASK_DELETE_CLOCK_INFO_GLOTIME_EST (0x00000040) --  Mask to delete GLONASS time estimate from clock information
      - QMI_LOC_MASK_DELETE_CLOCK_INFO_GLODAY_NUMBER (0x00000080) --  Mask to delete GLONASS day number from clock information
      - QMI_LOC_MASK_DELETE_CLOCK_INFO_GLO4YEAR_NUMBER (0x00000100) --  Mask to delete GLONASS four year number from clock information
      - QMI_LOC_MASK_DELETE_CLOCK_INFO_GLO_RF_GRP_DELAY (0x00000200) --  Mask to delete GLONASS RF GRP delay from clock information
      - QMI_LOC_MASK_DELETE_CLOCK_INFO_DISABLE_TT (0x00000400) --  Mask to delete disable TT from clock information
      - QMI_LOC_MASK_DELETE_CLOCK_INFO_GG_LEAPSEC (0x00000800) --  Mask to delete a BDS time estimate from the clock information
      - QMI_LOC_MASK_DELETE_CLOCK_INFO_GG_GGTB (0x00001000) --  Mask to delete a BDS time estimate from the clock information
      - QMI_LOC_MASK_DELETE_CLOCK_INFO_BDSTIME_EST (0x00002000) --  Mask to delete a BDS time estimate from the clock information
      - QMI_LOC_MASK_DELETE_CLOCK_INFO_GB_GBTB (0x00004000) --  Mask to delete Glonass-to-BDS time bias-related information from the
      clock information
      - QMI_LOC_MASK_DELETE_CLOCK_INFO_BG_BGTB (0x00008000) --  Mask to delete BDS-to-GLONASS time bias-related information from the
       clock information
      - QMI_LOC_MASK_DELETE_CLOCK_INFO_BDSWEEK_NUMBER (0x00010000) --  Mask to delete the BDS week number from the clock information
      - QMI_LOC_MASK_DELETE_CLOCK_INFO_BDS_RF_GRP_DELAY (0x00020000) --  Mask to delete the BDS RF GRP delay from the clock information
 */

  /* Optional */
  /*  Delete BDS SV Info */
  uint8_t deleteBdsSvInfoList_valid;  /**< Must be set to true if deleteBdsSvInfoList is being passed */
  uint32_t deleteBdsSvInfoList_len;  /**< Must be set to # of elements in deleteBdsSvInfoList */
  qmiLocDeleteBDSSvInfoStructT_v02 deleteBdsSvInfoList[QMI_LOC_DELETE_MAX_BDS_SV_INFO_LENGTH_V02];
  /**<   \vspace{0.06in} \n List of BDS satellites for which the assistance data is to be deleted.
  */
}qmiLocDeleteAssistDataReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; This command is used to delete the location engine
                    assistance data */
typedef struct {

  /* Mandatory */
  /*  Delete Assist Data Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Delete Assist Data request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */
}qmiLocDeleteAssistDataIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Enables/disables XTRA-T session control. */
typedef struct {

  /* Mandatory */
  /*  Enable XTRA-T */
  uint8_t xtraTSessionControl;
  /**<   Indicates whether to enable XTRA-T:\n
       - 0x01 (TRUE) -- Enable XTRA-T \n
       - 0x00 (FALSE) -- Disable XTRA-T */
}qmiLocSetXtraTSessionControlReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Enables/disables XTRA-T session control. */
typedef struct {

  /* Mandatory */
  /*  Set XTRA-T Session Control Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Set XTRA-T Session Control request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */
}qmiLocSetXtraTSessionControlIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Gets the XTRA-T session control value from the location
                    engine. */
typedef struct {
  /* This element is a placeholder to prevent the declaration of
     an empty struct.  DO NOT USE THIS FIELD UNDER ANY CIRCUMSTANCE */
  char __placeholder;
}qmiLocGetXtraTSessionControlReqMsgT_v02;

  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Gets the XTRA-T session control value from the location
                    engine. */
typedef struct {

  /* Mandatory */
  /*  Get XTRA-T Session Control Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Get XTRA-T Session Control request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */

  /* Optional */
  /*  Enable/Disable XTRA-T */
  uint8_t xtraTSessionControl_valid;  /**< Must be set to true if xtraTSessionControl is being passed */
  uint8_t xtraTSessionControl;
  /**<   Indicates whether to enable XTRA-T:\n
       - 0x01 (TRUE) -- Enable XTRA-T \n
       - 0x00 (FALSE) -- Disable XTRA-T */
}qmiLocGetXtraTSessionControlIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  uint32_t wifiPositionTime;
  /**<   Common counter (typically, the number of milliseconds since bootup).
        This field is only to be provided if the modem and host processors are
        synchronized. */
}qmiLocWifiFixTimeStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCWIFIFIXERRORCODEENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_WIFI_FIX_ERROR_SUCCESS_V02 = 0, /**<  Wi-Fi fix is successful. */
  eQMI_LOC_WIFI_FIX_ERROR_WIFI_NOT_AVAILABLE_V02 = 1, /**<  Wi-Fi fix failed because Wi-Fi is not available on the device.  */
  eQMI_LOC_WIFI_FIX_ERROR_NO_AP_FOUND_V02 = 2, /**<  Wi-Fi fix failed because no access points were found.  */
  eQMI_LOC_WIFI_FIX_ERROR_UNAUTHORIZED_V02 = 3, /**<  Wi-Fi fix failed because the server denied access due to bad authorization
   code.  */
  eQMI_LOC_WIFI_FIX_ERROR_SERVER_UNAVAILABLE_V02 = 4, /**<  Wi-Fi fix failed because the Wi-Fi server was unavailable.  */
  eQMI_LOC_WIFI_FIX_ERROR_LOCATION_CANNOT_BE_DETERMINED_V02 = 5, /**<  Wi-Fi fix failed even though APs were found and the server could be reached.
   This may be because the APs found are not in the database.  */
  eQMI_LOC_WIFI_FIX_ERROR_UNKNOWN_V02 = 6, /**<  Wi-Fi fix failed, but the cause could not be determined.  */
  QMILOCWIFIFIXERRORCODEENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocWifiFixErrorCodeEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  double lat;
  /**<   Wi-Fi position latitude. \n
        - Type: Floating point \n
        - Units: Degrees */

  double lon;
  /**<   Wi-Fi position longitude. \n
        - Type: Floating point \n
        - Units: Degrees */

  uint16_t hepe;
  /**<   Wi-Fi position HEPE.\n
        - Units: Meters */

  uint8_t numApsUsed;
  /**<   Number of Access Points (AP) used to generate a fix. */

  qmiLocWifiFixErrorCodeEnumT_v02 fixErrorCode;
  /**<   Wi-Fi position error code; set to 0 if the fix succeeds. This position
 is only used by a module if the value is 0. If there was a failure,
 the error code provided by the Wi-Fi positioning system can be provided
 here.

 Valid values: \n
      - eQMI_LOC_WIFI_FIX_ERROR_SUCCESS (0) --  Wi-Fi fix is successful.
      - eQMI_LOC_WIFI_FIX_ERROR_WIFI_NOT_AVAILABLE (1) --  Wi-Fi fix failed because Wi-Fi is not available on the device.
      - eQMI_LOC_WIFI_FIX_ERROR_NO_AP_FOUND (2) --  Wi-Fi fix failed because no access points were found.
      - eQMI_LOC_WIFI_FIX_ERROR_UNAUTHORIZED (3) --  Wi-Fi fix failed because the server denied access due to bad authorization
   code.
      - eQMI_LOC_WIFI_FIX_ERROR_SERVER_UNAVAILABLE (4) --  Wi-Fi fix failed because the Wi-Fi server was unavailable.
      - eQMI_LOC_WIFI_FIX_ERROR_LOCATION_CANNOT_BE_DETERMINED (5) --  Wi-Fi fix failed even though APs were found and the server could be reached.
   This may be because the APs found are not in the database.
      - eQMI_LOC_WIFI_FIX_ERROR_UNKNOWN (6) --  Wi-Fi fix failed, but the cause could not be determined.
 */
}qmiLocWifiFixPosStructT_v02;  /* Type */
/**
    @}
  */

typedef uint8_t qmiLocWifiApQualifierMaskT_v02;
#define QMI_LOC_WIFI_AP_QUALIFIER_BEING_USED_V02 ((qmiLocWifiApQualifierMaskT_v02)0x01) /**<  Access point is being used by the WPS.  */
#define QMI_LOC_WIFI_AP_QUALIFIER_HIDDEN_SSID_V02 ((qmiLocWifiApQualifierMaskT_v02)0x02) /**<  AP does not broadcast SSID.  */
#define QMI_LOC_WIFI_AP_QUALIFIER_PRIVATE_V02 ((qmiLocWifiApQualifierMaskT_v02)0x04) /**<  AP has encryption turned on.  */
#define QMI_LOC_WIFI_AP_QUALIFIER_INFRASTRUCTURE_MODE_V02 ((qmiLocWifiApQualifierMaskT_v02)0x08) /**<  AP is in infrastructure mode and not in ad-hoc/unknown mode.  */
/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  uint8_t macAddr[QMI_LOC_WIFI_MAC_ADDR_LENGTH_V02];
  /**<   Associated MAC address of the AP. \n
        - Type: Array of unsigned integers \n
        - Address length: 6
   */

  int32_t rssi;
  /**<   Receive signal strength indicator.\n
        - Units: dBm (offset with +100 dB) */

  uint16_t channel;
  /**<   Wi-Fi channel on which a beacon was received. */

  qmiLocWifiApQualifierMaskT_v02 apQualifier;
  /**<   A bitmask of Boolean qualifiers for APs.
        All unused bits in this mask must be set to 0.

        Valid values: \n
          - 0x01 -- BEING_USED \n
          - 0x02 -- HIDDEN_SSID \n
          - 0x04 -- PRIVATE \n
          - 0x08 -- INFRASTRUCTURE_MODE
         */
}qmiLocWifiApInfoStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  char ssid[QMI_LOC_MAX_WIFI_AP_SSID_STR_LENGTH_V02 + 1];
  /**<   NULL-terminated SSID string of the Wi-Fi AP. Its maximum length according to the ASCII standard is 32 octets. */
}qmiLocWifiApSsidStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Injects the Wi-Fi position. */
typedef struct {

  /* Optional */
  /*  Wi-Fi Fix Time */
  uint8_t wifiFixTime_valid;  /**< Must be set to true if wifiFixTime is being passed */
  qmiLocWifiFixTimeStructT_v02 wifiFixTime;
  /**<   \vspace{0.06in} \n Time of Wi-Fi position fix. */

  /* Optional */
  /*  Wi-Fi Position */
  uint8_t wifiFixPosition_valid;  /**< Must be set to true if wifiFixPosition is being passed */
  qmiLocWifiFixPosStructT_v02 wifiFixPosition;
  /**<   \vspace{0.06in} \n Wi-Fi position fix. */

  /* Optional */
  /*  Wi-Fi Access Point Information */
  uint8_t apInfo_valid;  /**< Must be set to true if apInfo is being passed */
  uint32_t apInfo_len;  /**< Must be set to # of elements in apInfo */
  qmiLocWifiApInfoStructT_v02 apInfo[QMI_LOC_WIFI_MAX_REPORTED_APS_PER_MSG_V02];
  /**<   \vspace{0.06in} \n AP scan list.
        SSID of the Wi-Fi AP.
        The ordering of the Wi-Fi AP SSID list should matchthe Wi-Fi AP MAC address list if both are provided,
        i.e., the first element of the Wi-Fi AP SSID list must be the SSID of the AP whose MAC
        address is in the first element in the Wi-Fi AP Info MAC Address, and so on. */

  /* Optional */
  /*  Horizontal Reliability */
  uint8_t horizontalReliability_valid;  /**< Must be set to true if horizontalReliability is being passed */
  qmiLocReliabilityEnumT_v02 horizontalReliability;
  /**<   Specifies the reliability of the horizontal position.

 Valid values: \n
      - eQMI_LOC_RELIABILITY_NOT_SET (0) --  Location reliability is not set
      - eQMI_LOC_RELIABILITY_VERY_LOW (1) --  Location reliability is very low; use it at your own risk
      - eQMI_LOC_RELIABILITY_LOW (2) --  Location reliability is low; little or no cross-checking is possible
      - eQMI_LOC_RELIABILITY_MEDIUM (3) --  Location reliability is medium; limited cross-check passed
      - eQMI_LOC_RELIABILITY_HIGH (4) --  Location reliability is high; strong cross-check passed
 */

  /* Optional */
  /*  Raw HEPE */
  uint8_t rawHepe_valid;  /**< Must be set to true if rawHepe is being passed */
  uint16_t rawHepe;
  /**<   Wi-Fi position raw HEPE, which has no optimization.\n
        - Units: Meters */

  /* Optional */
  /*  Wi-Fi AP SSID String */
  uint8_t wifiApSsidInfo_valid;  /**< Must be set to true if wifiApSsidInfo is being passed */
  uint32_t wifiApSsidInfo_len;  /**< Must be set to # of elements in wifiApSsidInfo */
  qmiLocWifiApSsidStructT_v02 wifiApSsidInfo[QMI_LOC_WIFI_MAX_REPORTED_APS_PER_MSG_V02];
  /**<   \vspace{0.04in} \n
        The ordering of the Wi-Fi AP SSID list should match the Wi-Fi AP MAC address list if both are provided,
        i.e., the first element of the Wi-Fi AP SSID list must be the SSID of the AP whose MAC
        address is in the first element in the Wi-Fi AP Info MAC address, and so on.*/
}qmiLocInjectWifiPositionReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Injects the Wi-Fi position. */
typedef struct {

  /* Mandatory */
  /*  Inject Wi-Fi Position Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Inject Wi-Fi Position request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */
}qmiLocInjectWifiPositionIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCWIFISTATUSENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_WIFI_STATUS_AVAILABLE_V02 = 1, /**<  Wi-Fi is available  */
  eQMI_LOC_WIFI_STATUS_UNAVAILABLE_V02 = 2, /**<  Wi-Fi is not available  */
  QMILOCWIFISTATUSENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocWifiStatusEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Notifies the location engine of the Wi-Fi status. */
typedef struct {

  /* Mandatory */
  /*  Availablility of Wi-Fi */
  qmiLocWifiStatusEnumT_v02 wifiStatus;
  /**<   Wi-Fi status information.

 Valid values: \n
      - eQMI_LOC_WIFI_STATUS_AVAILABLE (1) --  Wi-Fi is available
      - eQMI_LOC_WIFI_STATUS_UNAVAILABLE (2) --  Wi-Fi is not available
 */
}qmiLocNotifyWifiStatusReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Notifies the location engine of the Wi-Fi status. */
typedef struct {

  /* Mandatory */
  /*  Status of Notify Wi-Fi Status Request */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Notify Wi-Fi Status request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */
}qmiLocNotifyWifiStatusIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Gets the mask of the events for which a client has
                    registered. */
typedef struct {
  /* This element is a placeholder to prevent the declaration of
     an empty struct.  DO NOT USE THIS FIELD UNDER ANY CIRCUMSTANCE */
  char __placeholder;
}qmiLocGetRegisteredEventsReqMsgT_v02;

  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Gets the mask of the events for which a client has
                    registered. */
typedef struct {

  /* Mandatory */
  /*  Get Registered Events Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Get Registered Events request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */

  /* Optional */
  /*  Event Registration Mask */
  uint8_t eventRegMask_valid;  /**< Must be set to true if eventRegMask is being passed */
  qmiLocEventRegMaskT_v02 eventRegMask;
  /**<   Event registration mask.
 Valid bitmasks: \n
      - QMI_LOC_EVENT_MASK_POSITION_REPORT (0x00000001) --  The control point must enable this mask to receive position report
       event indications.
      - QMI_LOC_EVENT_MASK_GNSS_SV_INFO (0x00000002) --  The control point must enable this mask to receive satellite report
       event indications. These reports are sent at a 1 Hz rate.
      - QMI_LOC_EVENT_MASK_NMEA (0x00000004) --  The control point must enable this mask to receive NMEA reports for
       position and satellites in view. The report is at a 1 Hz rate.
      - QMI_LOC_EVENT_MASK_NI_NOTIFY_VERIFY_REQ (0x00000008) --  The control point must enable this mask to receive NI Notify/Verify request
       event indications.
      - QMI_LOC_EVENT_MASK_INJECT_TIME_REQ (0x00000010) --  The control point must enable this mask to receive time injection request
       event indications.
      - QMI_LOC_EVENT_MASK_INJECT_PREDICTED_ORBITS_REQ (0x00000020) --  The control point must enable this mask to receive predicted orbits request
       event indications.
      - QMI_LOC_EVENT_MASK_INJECT_POSITION_REQ (0x00000040) --  The control point must enable this mask to receive position injection request
       event indications.
      - QMI_LOC_EVENT_MASK_ENGINE_STATE (0x00000080) --  The control point must enable this mask to receive engine state report
       event indications.
      - QMI_LOC_EVENT_MASK_FIX_SESSION_STATE (0x00000100) --  The control point must enable this mask to receive fix session status report
       event indications.
      - QMI_LOC_EVENT_MASK_WIFI_REQ (0x00000200) --  The control point must enable this mask to receive Wi-Fi position request
       event indications.
      - QMI_LOC_EVENT_MASK_SENSOR_STREAMING_READY_STATUS (0x00000400) --  The control point must enable this mask to receive notifications from the
       location engine indicating its readiness to accept data from the
       sensors (accelerometer, gyroscope, etc.).
      - QMI_LOC_EVENT_MASK_TIME_SYNC_REQ (0x00000800) --  The control point must enable this mask to receive time sync requests
       from the GPS engine. Time sync enables the GPS engine to synchronize
       its clock with the sensor processor's clock.
      - QMI_LOC_EVENT_MASK_SET_SPI_STREAMING_REPORT (0x00001000) --  The control point must enable this mask to receive Stationary Position
       Indicator (SPI) streaming report indications.
      - QMI_LOC_EVENT_MASK_LOCATION_SERVER_CONNECTION_REQ (0x00002000) --  The control point must enable this mask to receive location server
       requests. These requests are generated when the service wishes to
       establish a connection with a location server.
      - QMI_LOC_EVENT_MASK_NI_GEOFENCE_NOTIFICATION (0x00004000) --  The control point must enable this mask to receive notifications
       related to network-initiated Geofences. These events notify the client
       when a network-initiated Geofence is added, deleted, or edited.
      - QMI_LOC_EVENT_MASK_GEOFENCE_GEN_ALERT (0x00008000) --  The control point must enable this mask to receive Geofence alerts.
       These alerts are generated to inform the client of the changes that may
       affect a Geofence, e.g., if GPS is turned off or if the network is
       unavailable.
      - QMI_LOC_EVENT_MASK_GEOFENCE_BREACH_NOTIFICATION (0x00010000) --  The control point must enable this mask to receive notifications when
       a Geofence is breached. These events are generated when a UE enters
       or leaves the perimeter of a Geofence. This breach report is for a single
       Geofence .
      - QMI_LOC_EVENT_MASK_PEDOMETER_CONTROL (0x00020000) --  The control point must enable this mask to register for pedometer
       control requests from the location engine. The location engine sends
       this event to control the injection of pedometer reports.
      - QMI_LOC_EVENT_MASK_MOTION_DATA_CONTROL (0x00040000) --  The control point must enable this mask to register for motion data
       control requests from the location engine. The location engine sends
       this event to control the injection of motion data.
      - QMI_LOC_EVENT_MASK_BATCH_FULL_NOTIFICATION (0x00080000) --  The control point must enable this mask to receive notification when
       a batch is full. The location engine sends this event to notify of Batch Full
       for ongoing batching session.
      - QMI_LOC_EVENT_MASK_LIVE_BATCHED_POSITION_REPORT (0x00100000) --  The control point must enable this mask to receive position report
       indications along with an ongoing batching session. The location engine sends
       this event to notify the batched position report while a batching session
       is ongoing.
      - QMI_LOC_EVENT_MASK_INJECT_WIFI_AP_DATA_REQ (0x00200000) --  The control point must enable this mask to receive Wi-Fi AP data inject request
       event indications.
      - QMI_LOC_EVENT_MASK_GEOFENCE_BATCH_BREACH_NOTIFICATION (0x00400000) --  The control point must enable this mask to receive notifications when
       a Geofence is breached. These events are generated when a UE enters
       or leaves the perimeter of a Geofence. This breach notification is for
       multiple Geofences. Breaches from multiple Geofences are all batched and
       sent in the same notification .
      - QMI_LOC_EVENT_MASK_VEHICLE_DATA_READY_STATUS (0x00800000) --  The control point must enable this mask to receive notifications from the
       location engine indicating its readiness to accept vehicle data (vehicle
       accelerometer, vehicle angular rate, vehicle odometry, etc.).
      - QMI_LOC_EVENT_MASK_GNSS_MEASUREMENT_REPORT (0x01000000) --  The control point must enable this mask to receive system clock and satellite
       measurement report events (system clock, SV time, Doppler, etc.). Reports are
       generated only for the GNSS satellite constellations that are enabled using
       QMI_LOC_SET_GNSS_CONSTELL_REPORT_CONFIG.
      - QMI_LOC_EVENT_MASK_GNSS_SV_POLYNOMIAL_REPORT (0x02000000) --  The control point must enable this mask to receive satellite position
        reports as polynomials. Reports are generated only for the GNSS satellite
        constellations that are enabled using QMI_LOC_SET_GNSS_CONSTELL_REPORT_CONFIG.
      - QMI_LOC_EVENT_MASK_GEOFENCE_PROXIMITY_NOTIFICATION (0x04000000) --  The control point must enable this mask to receive notifications when a Geofence proximity is entered
  and exited.  The proximity of a geofence may be due to different contexts . These contexts are identified
  using the context id in this indication. The context of a geofence may contain Wifi area ID lists, IBeacon lists,
  Cell-Id list etc.
      - QMI_LOC_EVENT_MASK_GDT_UPLOAD_BEGIN_REQ (0x08000000) --  The control point must enable this mask to receive GDT (Generic Data Transport )
        session begin request event indications.
      - QMI_LOC_EVENT_MASK_GDT_UPLOAD_END_REQ (0x10000000) --  The control point must enable this mask to receive GDT (Generic Data Transport )
        session end request
        event indications.
 */
}qmiLocGetRegisteredEventsIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCOPERATIONMODEENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_OPER_MODE_DEFAULT_V02 = 1, /**<  Use the default engine mode  */
  eQMI_LOC_OPER_MODE_MSB_V02 = 2, /**<  Use the MS-based mode  */
  eQMI_LOC_OPER_MODE_MSA_V02 = 3, /**<  Use the MS-assisted mode  */
  eQMI_LOC_OPER_MODE_STANDALONE_V02 = 4, /**<  Use Standalone mode  */
  eQMI_LOC_OPER_MODE_CELL_ID_V02 = 5, /**<  Use cell ID; this mode is only valid for GSM/UMTS networks  */
  eQMI_LOC_OPER_MODE_WWAN_V02 = 6, /**<  Use WWAN measurements to calculate the position; if this mode is
       set, AFLT will be used for 1X networks and OTDOA will be used
       for LTE networks  */
  QMILOCOPERATIONMODEENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocOperationModeEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Tells the engine to use the specified operation mode while
                    making the position fixes. */
typedef struct {

  /* Mandatory */
  /*  Operation Mode */
  qmiLocOperationModeEnumT_v02 operationMode;
  /**<   Preferred operation mode.

 Valid values: \n
      - eQMI_LOC_OPER_MODE_DEFAULT (1) --  Use the default engine mode
      - eQMI_LOC_OPER_MODE_MSB (2) --  Use the MS-based mode
      - eQMI_LOC_OPER_MODE_MSA (3) --  Use the MS-assisted mode
      - eQMI_LOC_OPER_MODE_STANDALONE (4) --  Use Standalone mode
      - eQMI_LOC_OPER_MODE_CELL_ID (5) --  Use cell ID; this mode is only valid for GSM/UMTS networks
      - eQMI_LOC_OPER_MODE_WWAN (6) --  Use WWAN measurements to calculate the position; if this mode is
       set, AFLT will be used for 1X networks and OTDOA will be used
       for LTE networks
 */
}qmiLocSetOperationModeReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Tells the engine to use the specified operation mode while
                    making the position fixes. */
typedef struct {

  /* Mandatory */
  /*  Set Operation Mode Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Set Operation Mode request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */
}qmiLocSetOperationModeIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Gets the current operation mode from the engine. */
typedef struct {
  /* This element is a placeholder to prevent the declaration of
     an empty struct.  DO NOT USE THIS FIELD UNDER ANY CIRCUMSTANCE */
  char __placeholder;
}qmiLocGetOperationModeReqMsgT_v02;

  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Gets the current operation mode from the engine. */
typedef struct {

  /* Mandatory */
  /*  Get Operation Mode Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Get Operation Mode request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */

  /* Optional */
  /*  Operation Mode */
  uint8_t operationMode_valid;  /**< Must be set to true if operationMode is being passed */
  qmiLocOperationModeEnumT_v02 operationMode;
  /**<   Current operation mode.

 Valid values: \n
      - eQMI_LOC_OPER_MODE_DEFAULT (1) --  Use the default engine mode
      - eQMI_LOC_OPER_MODE_MSB (2) --  Use the MS-based mode
      - eQMI_LOC_OPER_MODE_MSA (3) --  Use the MS-assisted mode
      - eQMI_LOC_OPER_MODE_STANDALONE (4) --  Use Standalone mode
      - eQMI_LOC_OPER_MODE_CELL_ID (5) --  Use cell ID; this mode is only valid for GSM/UMTS networks
      - eQMI_LOC_OPER_MODE_WWAN (6) --  Use WWAN measurements to calculate the position; if this mode is
       set, AFLT will be used for 1X networks and OTDOA will be used
       for LTE networks
 */
}qmiLocGetOperationModeIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Used by the control point to set the SPI status, which
                    indicates whether the device is stationary. */
typedef struct {

  /* Mandatory */
  /*  Stationary Status */
  uint8_t stationary;
  /**<   Indicates whether the device is stationary:
       \begin{itemize1}
       \item    0x00 (FALSE) -- Device is not stationary
       \item    0x01 (TRUE)  -- Device is stationary
       \vspace{-0.18in} \end{itemize1}*/

  /* Optional */
  /*  Confidence */
  uint8_t confidenceStationary_valid;  /**< Must be set to true if confidenceStationary is being passed */
  uint8_t confidenceStationary;
  /**<   Confidence in the Stationary state expressed as a percentage.\n
       - Range: 0 to 100 */
}qmiLocSetSpiStatusReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Used by the control point to set the SPI status, which
                    indicates whether the device is stationary. */
typedef struct {

  /* Mandatory */
  /*  Status of SPI Status Request */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the SPI Status request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */
}qmiLocSetSpiStatusIndMsgT_v02;  /* Message */
/**
    @}
  */

typedef uint8_t qmiLocSensorDataFlagMaskT_v02;
#define QMI_LOC_SENSOR_DATA_FLAG_SIGN_REVERSAL_V02 ((qmiLocSensorDataFlagMaskT_v02)0x01) /**<  Bitmask to specify that a sign reversal is required while interpreting
     the sensor data; only applies to the accelerometer samples  */
#define QMI_LOC_SENSOR_DATA_FLAG_SENSOR_TIME_IS_MODEM_TIME_V02 ((qmiLocSensorDataFlagMaskT_v02)0x02) /**<  Bitmask to specify that the sensor time stamp is the same as the modem
       time stamp  */
#define QMI_LOC_SENSOR_DATA_FLAG_CALIBRATED_DATA_V02 ((qmiLocSensorDataFlagMaskT_v02)0x04) /**<  Bitmask to specify that the injected sensor data is calibrated  */
/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCSENSORDATATIMESOURCEENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_SENSOR_TIME_SOURCE_UNSPECIFIED_V02 = 0, /**<  Sensor time source is unspecified  */
  eQMI_LOC_SENSOR_TIME_SOURCE_COMMON_V02 = 1, /**<  Time source is common between the sensors and
       the location engine  */
  QMILOCSENSORDATATIMESOURCEENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocSensorDataTimeSourceEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  uint16_t timeOffset;
  /**<   Sample time offset. This time offset must be
       relative to the timestamp of the first sensor data sample.\n
       - Units: Milliseconds */

  float xAxis;
  /**<   Sensor x-axis sample. \n
       - Units Accelerometer: Meters/seconds^2 \n
       - Units Gyroscope:     Radians/second \n
       - Units Magnetometer:  microTesla */

  float yAxis;
  /**<   Sensor y-axis sample. \n
       - Units Accelerometer: Meters/seconds^2 \n
       - Units Gyroscope:     Radians/second \n
       - Units Magnetometer:  microTesla */

  float zAxis;
  /**<   Sensor z-axis sample. \n
       - Units Accelerometer: Meters/seconds^2 ) \n
       - Units Gyroscope:     Radians/second \n
       - Units Magnetometer:  microTesla */
}qmiLoc3AxisSensorSampleStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  uint32_t timeOfFirstSample;
  /**<   Denotes a full 32-bit timestamp of the first (oldest) sample in this
       message.The timestamp is in the time reference scale that is
       used by the sensor time source.\n
       - Units: Milliseconds */

  qmiLocSensorDataFlagMaskT_v02 flags;
  /**<   Flags to indicate any deviation from the default measurement
 assumptions. All unused bits in this field must be set to 0.

 Valid bitmasks:
      - QMI_LOC_SENSOR_DATA_FLAG_SIGN_REVERSAL (0x01) --  Bitmask to specify that a sign reversal is required while interpreting
     the sensor data; only applies to the accelerometer samples
      - QMI_LOC_SENSOR_DATA_FLAG_SENSOR_TIME_IS_MODEM_TIME (0x02) --  Bitmask to specify that the sensor time stamp is the same as the modem
       time stamp
      - QMI_LOC_SENSOR_DATA_FLAG_CALIBRATED_DATA (0x04) --  Bitmask to specify that the injected sensor data is calibrated  */

  uint32_t sensorData_len;  /**< Must be set to # of elements in sensorData */
  qmiLoc3AxisSensorSampleStructT_v02 sensorData[QMI_LOC_SENSOR_DATA_MAX_SAMPLES_V02];
  /**<   Variable length array to specify sensor samples. \n
       - Maximum length of the array: 50 */
}qmiLoc3AxisSensorSampleListStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  uint16_t timeOffset;
  /**<   Sample time offset. This time offset must be
       relative to the timestamp of the first sensor sample.\n
       - Units: Milliseconds */

  float temperature;
  /**<   Sensor temperature. \n
       - Type: Floating point \n
       - Units: Degrees Celsius \n
       - Range: -50 to +100.00 */
}qmiLocSensorTemperatureSampleStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  qmiLocSensorDataTimeSourceEnumT_v02 timeSource;
  /**<   Denotes the time source of the sensor data. Location service will use
 this field to identify the time reference used in the
 sensor data timestamps.

 Valid values: \n
      - eQMI_LOC_SENSOR_TIME_SOURCE_UNSPECIFIED (0) --  Sensor time source is unspecified
      - eQMI_LOC_SENSOR_TIME_SOURCE_COMMON (1) --  Time source is common between the sensors and
       the location engine
 */

  uint32_t timeOfFirstSample;
  /**<   Denotes a full 32-bit timestamp of the first (oldest) sample in this
       message. The timestamp is in the time reference scale that is
       used by the sensor time source.\n
       - Units: Milliseconds */

  uint32_t temperatureData_len;  /**< Must be set to # of elements in temperatureData */
  qmiLocSensorTemperatureSampleStructT_v02 temperatureData[QMI_LOC_SENSOR_DATA_MAX_SAMPLES_V02];
  /**<   Variable length array to specify sensor temperature samples. \n
       - Maximum length of the array: 50 */
}qmiLocSensorTemperatureSampleListStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Used by the control point to inject sensor data into the
                    GNSS location engine. */
typedef struct {

  /* Optional */
  /*  Opaque Identifier */
  uint8_t opaqueIdentifier_valid;  /**< Must be set to true if opaqueIdentifier is being passed */
  uint32_t opaqueIdentifier;
  /**<   An opaque identifier that is sent in by the client that will be echoed
       in the indication so the client can relate the indication to the
       request. */

  /* Optional */
  /*  3-Axis Accelerometer Data */
  uint8_t threeAxisAccelData_valid;  /**< Must be set to true if threeAxisAccelData is being passed */
  qmiLoc3AxisSensorSampleListStructT_v02 threeAxisAccelData;
  /**<   \vspace{0.06in} \n Accelerometer sensor samples. */

  /* Optional */
  /*  3-Axis Gyroscope Data */
  uint8_t threeAxisGyroData_valid;  /**< Must be set to true if threeAxisGyroData is being passed */
  qmiLoc3AxisSensorSampleListStructT_v02 threeAxisGyroData;
  /**<   \vspace{0.06in} \n Gyroscope sensor samples. */

  /* Optional */
  /*  3-Axis Accelerometer Data Time Source */
  uint8_t threeAxisAccelDataTimeSource_valid;  /**< Must be set to true if threeAxisAccelDataTimeSource is being passed */
  qmiLocSensorDataTimeSourceEnumT_v02 threeAxisAccelDataTimeSource;
  /**<   Time source for the 3-axis accelerometer data. The location service uses
 this field to identify the time reference used in the accelerometer data
 timestamps. If not specified, the location service assumes that the
 time source for the accelereometer data is unknown. \n
 Values: \n
      - eQMI_LOC_SENSOR_TIME_SOURCE_UNSPECIFIED (0) --  Sensor time source is unspecified
      - eQMI_LOC_SENSOR_TIME_SOURCE_COMMON (1) --  Time source is common between the sensors and
       the location engine
 */

  /* Optional */
  /*  3-Axis Gyroscope Data Time Source */
  uint8_t threeAxisGyroDataTimeSource_valid;  /**< Must be set to true if threeAxisGyroDataTimeSource is being passed */
  qmiLocSensorDataTimeSourceEnumT_v02 threeAxisGyroDataTimeSource;
  /**<   Time source for the 3-axis gyroscope data. The location service uses
 this field to identify the time reference used in the gyroscope data
 timestamps. If not specified, the location service assumes that the
 time source for the gyroscope data is unknown. \n
 Values: \n
      - eQMI_LOC_SENSOR_TIME_SOURCE_UNSPECIFIED (0) --  Sensor time source is unspecified
      - eQMI_LOC_SENSOR_TIME_SOURCE_COMMON (1) --  Time source is common between the sensors and
       the location engine
 */

  /* Optional */
  /*  Accelerometer Temperature Data */
  uint8_t accelTemperatureData_valid;  /**< Must be set to true if accelTemperatureData is being passed */
  qmiLocSensorTemperatureSampleListStructT_v02 accelTemperatureData;
  /**<   \vspace{0.06in}  \nAccelerometer temperature samples. This data is optional and does not
       have to be included in the message along with accelerometer data. */

  /* Optional */
  /*  Gyroscope Temperature Data */
  uint8_t gyroTemperatureData_valid;  /**< Must be set to true if gyroTemperatureData is being passed */
  qmiLocSensorTemperatureSampleListStructT_v02 gyroTemperatureData;
  /**<   \vspace{0.06in} \n Gyroscope temperature samples. This data is optional and does not
       have to be included in the message along with gyroscope data. */

  /* Optional */
  /*  3-Axis Magnetometer Data */
  uint8_t threeAxisMagData_valid;  /**< Must be set to true if threeAxisMagData is being passed */
  qmiLoc3AxisSensorSampleListStructT_v02 threeAxisMagData;
  /**<   \vspace{0.06in} \n Magnetometer sensor samples. */

  /* Optional */
  /*  3-Axis Magnetometer Data Time Source */
  uint8_t threeAxisMagDataTimeSource_valid;  /**< Must be set to true if threeAxisMagDataTimeSource is being passed */
  qmiLocSensorDataTimeSourceEnumT_v02 threeAxisMagDataTimeSource;
  /**<   Time source for the 3-axis magnetometer data. The location service uses
 this field to identify the time reference used in the magnetometer data
 timestamps. If not specified, the location service assumes that the
 time source for the magnetometer data is unknown. \n
 Values: \n
      - eQMI_LOC_SENSOR_TIME_SOURCE_UNSPECIFIED (0) --  Sensor time source is unspecified
      - eQMI_LOC_SENSOR_TIME_SOURCE_COMMON (1) --  Time source is common between the sensors and
       the location engine
 */
}qmiLocInjectSensorDataReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Used by the control point to inject sensor data into the
                    GNSS location engine. */
typedef struct {

  /* Mandatory */
  /*  Inject Sensor Data Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Inject Sensor Data request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */

  /* Optional */
  /*  Opaque Identifier */
  uint8_t opaqueIdentifier_valid;  /**< Must be set to true if opaqueIdentifier is being passed */
  uint32_t opaqueIdentifier;
  /**<   Opaque identifier that was sent in by the client echoed
       so the client can relate the indication to the request. */

  /* Optional */
  /*  Accelerometer Samples Accepted */
  uint8_t threeAxisAccelSamplesAccepted_valid;  /**< Must be set to true if threeAxisAccelSamplesAccepted is being passed */
  uint8_t threeAxisAccelSamplesAccepted;
  /**<   Lets the client know how many 3-axis accelerometer samples
       were accepted. This field is present only if the accelerometer
       samples were sent in the request. */

  /* Optional */
  /*  Gyroscope Samples Accepted */
  uint8_t threeAxisGyroSamplesAccepted_valid;  /**< Must be set to true if threeAxisGyroSamplesAccepted is being passed */
  uint8_t threeAxisGyroSamplesAccepted;
  /**<   Lets the client know how many 3-axis gyroscope samples were
       accepted. This field is present only if the gyroscope
       samples were sent in the request. */

  /* Optional */
  /*  Accelerometer Temperature Samples Accepted */
  uint8_t accelTemperatureSamplesAccepted_valid;  /**< Must be set to true if accelTemperatureSamplesAccepted is being passed */
  uint8_t accelTemperatureSamplesAccepted;
  /**<   Lets the client know how many accelerometer temperature
       samples were accepted. This field is present only if the accelerometer
       temperature samples were sent in the request. */

  /* Optional */
  /*  Gyroscope Temperature Samples Accepted */
  uint8_t gyroTemperatureSamplesAccepted_valid;  /**< Must be set to true if gyroTemperatureSamplesAccepted is being passed */
  uint8_t gyroTemperatureSamplesAccepted;
  /**<   Lets the client know how many gyroscope temperature samples
       were accepted. This field is present only if the gyroscope
       temperature samples were sent in the request. */

  /* Optional */
  /*  Magnetometer Samples Accepted */
  uint8_t threeAxisMagSamplesAccepted_valid;  /**< Must be set to true if threeAxisMagSamplesAccepted is being passed */
  uint8_t threeAxisMagSamplesAccepted;
  /**<   Lets the client know how many 3-axis magnetometer samples
       were accepted. This field is present only if the magnetometer
       samples were sent in the request. */
}qmiLocInjectSensorDataIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Used by the control point to inject time sync data. */
typedef struct {

  /* Mandatory */
  /*  Reference Time Sync Counter */
  uint32_t refCounter;
  /**<   Must be set to the value that was sent to the control point when the
       GNSS location engine requested time sync injection. */

  /* Mandatory */
  /*  Sensor Receive Time */
  uint32_t sensorProcRxTime;
  /**<   Value of the sensor time when the control point received the
       Time Sync Inject request from the GNSS location engine.

       Must be monotonically increasing, jitter @latexonly $\leq$ @endlatexonly 1
       millisecond, never stopping until the process is rebooted.\n
       - Units: Milliseconds */

  /* Mandatory */
  /*  Sensor Transmit Time */
  uint32_t sensorProcTxTime;
  /**<   Value of the sensor time when the control point injects this message
       for use by the GNSS location engine.

       Must be monotonically increasing, jitter @latexonly $\leq$ @endlatexonly 1
       millisecond, never stopping until the process is rebooted.\n
       - Units: Milliseconds */
}qmiLocInjectTimeSyncDataReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Used by the control point to inject time sync data. */
typedef struct {

  /* Mandatory */
  /*  Inject Time Sync Data Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Inject Time Sync Data request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */
}qmiLocInjectTimeSyncDataIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCCRADLEMOUNTSTATEENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_CRADLE_STATE_NOT_MOUNTED_V02 = 0, /**<  Device is mounted on the cradle */
  eQMI_LOC_CRADLE_STATE_MOUNTED_V02 = 1, /**<  Device is not mounted on the cradle */
  eQMI_LOC_CRADLE_STATE_UNKNOWN_V02 = 2, /**<  Unknown cradle mount state */
  QMILOCCRADLEMOUNTSTATEENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocCradleMountStateEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Used by the control point to get the current
                    cradle mount configuration. */
typedef struct {
  /* This element is a placeholder to prevent the declaration of
     an empty struct.  DO NOT USE THIS FIELD UNDER ANY CIRCUMSTANCE */
  char __placeholder;
}qmiLocGetCradleMountConfigReqMsgT_v02;

  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Used by the control point to get the current
                    cradle mount configuration. */
typedef struct {

  /* Mandatory */
  /*  Get Cradle Mount Config Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Get Cradle Mount Configuration request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */

  /* Optional */
  /*  Cradle Mount State */
  uint8_t cradleMountState_valid;  /**< Must be set to true if cradleMountState is being passed */
  qmiLocCradleMountStateEnumT_v02 cradleMountState;
  /**<   Cradle Mount state set by the control point.

 Valid values: \n
      - eQMI_LOC_CRADLE_STATE_NOT_MOUNTED (0) --  Device is mounted on the cradle
      - eQMI_LOC_CRADLE_STATE_MOUNTED (1) --  Device is not mounted on the cradle
      - eQMI_LOC_CRADLE_STATE_UNKNOWN (2) --  Unknown cradle mount state
 */

  /* Optional */
  /*  Cradle Mount Confidence */
  uint8_t confidenceCradleMountState_valid;  /**< Must be set to true if confidenceCradleMountState is being passed */
  uint8_t confidenceCradleMountState;
  /**<   Confidence of the Cradle Mount state expressed as a percentage.\n
       - Range: 0 to 100 */
}qmiLocGetCradleMountConfigIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Used by the control point to set the current
                    cradle mount configuration. */
typedef struct {

  /* Mandatory */
  /*  Cradle Mount State */
  qmiLocCradleMountStateEnumT_v02 cradleMountState;
  /**<   Cradle Mount state set by the control point.

 Valid values: \n
      - eQMI_LOC_CRADLE_STATE_NOT_MOUNTED (0) --  Device is mounted on the cradle
      - eQMI_LOC_CRADLE_STATE_MOUNTED (1) --  Device is not mounted on the cradle
      - eQMI_LOC_CRADLE_STATE_UNKNOWN (2) --  Unknown cradle mount state
 */

  /* Optional */
  /*  Cradle Mount Confidence */
  uint8_t confidenceCradleMountState_valid;  /**< Must be set to true if confidenceCradleMountState is being passed */
  uint8_t confidenceCradleMountState;
  /**<   Confidence in the Cradle Mount state expressed as a percentage.\n
       - Range: 0 to 100 */
}qmiLocSetCradleMountConfigReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Used by the control point to set the current
                    cradle mount configuration. */
typedef struct {

  /* Mandatory */
  /*  Set Cradle Mount Config Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Set Cradle Mount Configuration request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */
}qmiLocSetCradleMountConfigIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCEXTERNALPOWERCONFIGENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_EXTERNAL_POWER_NOT_CONNECTED_V02 = 0, /**<  Device is not connected to an external power source  */
  eQMI_LOC_EXTERNAL_POWER_CONNECTED_V02 = 1, /**<  Device is connected to an external power source  */
  eQMI_LOC_EXTERNAL_POWER_UNKNOWN_V02 = 2, /**<  Unknown external power state  */
  QMILOCEXTERNALPOWERCONFIGENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocExternalPowerConfigEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Used by the control point to get the current
                    external power configuration. */
typedef struct {
  /* This element is a placeholder to prevent the declaration of
     an empty struct.  DO NOT USE THIS FIELD UNDER ANY CIRCUMSTANCE */
  char __placeholder;
}qmiLocGetExternalPowerConfigReqMsgT_v02;

  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Used by the control point to get the current
                    external power configuration. */
typedef struct {

  /* Mandatory */
  /*  Get Ext Power Config Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Get External Power Configuration request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */

  /* Optional */
  /*  External Power State */
  uint8_t externalPowerState_valid;  /**< Must be set to true if externalPowerState is being passed */
  qmiLocExternalPowerConfigEnumT_v02 externalPowerState;
  /**<   Power state; injected by the control point.

 Valid values: \n
      - eQMI_LOC_EXTERNAL_POWER_NOT_CONNECTED (0) --  Device is not connected to an external power source
      - eQMI_LOC_EXTERNAL_POWER_CONNECTED (1) --  Device is connected to an external power source
      - eQMI_LOC_EXTERNAL_POWER_UNKNOWN (2) --  Unknown external power state
 */
}qmiLocGetExternalPowerConfigIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Used by the control point to set the current
                    external power configuration. */
typedef struct {

  /* Mandatory */
  /*  External Power State */
  qmiLocExternalPowerConfigEnumT_v02 externalPowerState;
  /**<   Power state; injected by the control point.

 Valid values: \n
      - eQMI_LOC_EXTERNAL_POWER_NOT_CONNECTED (0) --  Device is not connected to an external power source
      - eQMI_LOC_EXTERNAL_POWER_CONNECTED (1) --  Device is connected to an external power source
      - eQMI_LOC_EXTERNAL_POWER_UNKNOWN (2) --  Unknown external power state
 */
}qmiLocSetExternalPowerConfigReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Used by the control point to set the current
                    external power configuration. */
typedef struct {

  /* Mandatory */
  /*  Set Ext Power Config Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Set External Power Configuration request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */
}qmiLocSetExternalPowerConfigIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCSERVERPDNENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_APN_PROFILE_PDN_TYPE_IPV4_V02 = 0x01, /**<  IPv4 PDN type  */
  eQMI_LOC_APN_PROFILE_PDN_TYPE_IPV6_V02 = 0x02, /**<  IPv6 PDN type  */
  eQMI_LOC_APN_PROFILE_PDN_TYPE_IPV4V6_V02 = 0x03, /**<  IPv4v6 PDN type  */
  eQMI_LOC_APN_PROFILE_PDN_TYPE_PPP_V02 = 0x04, /**<  PPP PDN type  */
  QMILOCSERVERPDNENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocServerPDNEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  qmiLocServerPDNEnumT_v02 pdnType;
  /**<   PDN type of the APN profile.

 Valid values: \n
      - eQMI_LOC_APN_PROFILE_PDN_TYPE_IPV4 (0x01) --  IPv4 PDN type
      - eQMI_LOC_APN_PROFILE_PDN_TYPE_IPV6 (0x02) --  IPv6 PDN type
      - eQMI_LOC_APN_PROFILE_PDN_TYPE_IPV4V6 (0x03) --  IPv4v6 PDN type
      - eQMI_LOC_APN_PROFILE_PDN_TYPE_PPP (0x04) --  PPP PDN type
 */

  char apnName[QMI_LOC_MAX_APN_NAME_LENGTH_V02 + 1];
  /**<   APN name.
       \begin{itemize1}
       \item    Type: NULL-terminated string
       \item    Maximum string length (including NULL terminator): 101
       \vspace{-0.18in} \end{itemize1}
  */
}qmiLocApnProfilesStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCSERVERREQSTATUSENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_SERVER_REQ_STATUS_SUCCESS_V02 = 1, /**<  Location server request was successful  */
  eQMI_LOC_SERVER_REQ_STATUS_FAILURE_V02 = 2, /**<  Location server request failed  */
  QMILOCSERVERREQSTATUSENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocServerReqStatusEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Used by the control point to inform the service about the
                    status of the location server connection request that the
                    service may have sent via the
                    QMI_LOC_EVENT_LOCATION_SERVER_CONNECTION_REQ_IND event. */
typedef struct {

  /* Mandatory */
  /*  Connection Handle */
  uint32_t connHandle;
  /**<   Connection handle that the service specified in the
       Location Server Connection request event. */

  /* Mandatory */
  /*  Request Type */
  qmiLocServerRequestEnumT_v02 requestType;
  /**<   Type of connection request service that was specified in the
 Location Server Connection Request event.

 Valid values: \n
      - eQMI_LOC_SERVER_REQUEST_OPEN (1) --  Open a connection to the location server
      - eQMI_LOC_SERVER_REQUEST_CLOSE (2) --  Close a connection to the location server
 */

  /* Mandatory */
  /*  Connection Status */
  qmiLocServerReqStatusEnumT_v02 statusType;
  /**<   Status of the Connection request.

 Valid values: \n
      - eQMI_LOC_SERVER_REQ_STATUS_SUCCESS (1) --  Location server request was successful
      - eQMI_LOC_SERVER_REQ_STATUS_FAILURE (2) --  Location server request failed
 */

  /* Optional */
  /*  APN Profile */
  uint8_t apnProfile_valid;  /**< Must be set to true if apnProfile is being passed */
  qmiLocApnProfilesStructT_v02 apnProfile;
  /**<   \vspace{0.06in} \n Access Point Name (APN) profile information is present only when
       requestType is OPEN and statusType is SUCCESS. */
}qmiLocInformLocationServerConnStatusReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Used by the control point to inform the service about the
                    status of the location server connection request that the
                    service may have sent via the
                    QMI_LOC_EVENT_LOCATION_SERVER_CONNECTION_REQ_IND event. */
typedef struct {

  /* Mandatory */
  /*  Status of Inform Loc Server Conn Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Inform Location Server Connection Status request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */
}qmiLocInformLocationServerConnStatusIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCVXVERSIONENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_VX_VERSION_V1_ONLY_V02 = 1, /**<  V1 VX version  */
  eQMI_LOC_VX_VERSION_V2_ONLY_V02 = 2, /**<  V2 VX version  */
  QMILOCVXVERSIONENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocVxVersionEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCSUPLVERSIONENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_SUPL_VERSION_1_0_V02 = 1, /**<  SUPL version 1.0  */
  eQMI_LOC_SUPL_VERSION_2_0_V02 = 2, /**<  SUPL version 2.0  */
  QMILOCSUPLVERSIONENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocSuplVersionEnumT_v02;
/**
    @}
  */

typedef uint32_t qmiLocLppConfigMaskT_v02;
#define QMI_LOC_LPP_CONFIG_ENABLE_USER_PLANE_V02 ((qmiLocLppConfigMaskT_v02)0x00000001) /**<  Enable user plane configuration for LTE Positioning Profile (LPP)  */
#define QMI_LOC_LPP_CONFIG_ENABLE_CONTROL_PLANE_V02 ((qmiLocLppConfigMaskT_v02)0x00000002) /**<  Enable control plane configuration for LPP  */
typedef uint32_t qmiLocAssistedGlonassProtocolMaskT_v02;
#define QMI_LOC_ASSISTED_GLONASS_PROTOCOL_MASK_RRC_CP_V02 ((qmiLocAssistedGlonassProtocolMaskT_v02)0x00000001) /**<  Assisted GLONASS is supported over RRC in the control plane  */
#define QMI_LOC_ASSISTED_GLONASS_PROTOCOL_MASK_RRLP_UP_V02 ((qmiLocAssistedGlonassProtocolMaskT_v02)0x00000002) /**<  Assisted GLONASS is supported over RRLP in the user plane  */
#define QMI_LOC_ASSISTED_GLONASS_PROTOCOL_MASK_LPP_UP_V02 ((qmiLocAssistedGlonassProtocolMaskT_v02)0x00000004) /**<  Assisted GLONASS is supported over LPP in the user plane;
       QMI_LOC_LPP_CONFIG_ENABLE_USER_PLANE must be set
       in the LPP configuration for this to take effect  */
#define QMI_LOC_ASSISTED_GLONASS_PROTOCOL_MASK_LPP_CP_V02 ((qmiLocAssistedGlonassProtocolMaskT_v02)0x00000008) /**<  Assisted GLONASS is supported over LPP in the control plane;
       QMI_LOC_LPP_CONFIG_ENABLE_CONTROL_PLANE must be set
       in the LPP configuration for this to take effect  */
/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCSUPLHASHALGOENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_SUPL_HASH_ALGO_SHA1_V02 = 0, /**<  SHA-1 hash algorithm for SUPL version 2.0 or later  */
  eQMI_LOC_SUPL_HASH_ALGO_SHA256_V02 = 1, /**<  SHA-256 hash algorithm for SUPL version 2.0 or later  */
  QMILOCSUPLHASHALGOENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocSuplHashAlgoEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCSUPLTLSVERSIONENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_SUPL_TLS_VERSION_1_0_V02 = 0, /**<  SUPL TLS version 1.0  */
  eQMI_LOC_SUPL_TLS_VERSION_1_1_V02 = 1, /**<  SUPL TLS version 1.1  */
  QMILOCSUPLTLSVERSIONENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocSuplTlsVersionEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCEMERGENCYPROTOCOLENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_EMERGENCY_PROTOCOL_WCDMA_CP_V02 = 0, /**<  Use Control Plane Protocol during an emergency while on WCDMA  */
  eQMI_LOC_EMERGENCY_PROTOCOL_WCDMA_UP_V02 = 1, /**<  Use SUPL 2.0 emergency services during an emergency while on WCDMA  */
  QMILOCEMERGENCYPROTOCOLENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocEmergencyProtocolEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Used by the control point to configure parameters stored
                    in the nonvolatile memory. */
typedef struct {

  /* Optional */
  /*  SUPL Security */
  uint8_t suplSecurity_valid;  /**< Must be set to true if suplSecurity is being passed */
  uint8_t suplSecurity;
  /**<   Indicates whether SUPL security is enabled.
       \begin{itemize1}
       \item    0x01 (TRUE) -- SUPL security is enabled
       \item    0x00 (FALSE) -- SUPL security is disabled
       \vspace{-0.18in} \end{itemize1} */

  /* Optional */
  /*  VX Version */
  uint8_t vxVersion_valid;  /**< Must be set to true if vxVersion is being passed */
  qmiLocVxVersionEnumT_v02 vxVersion;
  /**<   VX version.

 Valid values: \n
      - eQMI_LOC_VX_VERSION_V1_ONLY (1) --  V1 VX version
      - eQMI_LOC_VX_VERSION_V2_ONLY (2) --  V2 VX version
 */

  /* Optional */
  /*  SUPL Version */
  uint8_t suplVersion_valid;  /**< Must be set to true if suplVersion is being passed */
  qmiLocSuplVersionEnumT_v02 suplVersion;
  /**<   SUPL version.

 Valid values: \n
      - eQMI_LOC_SUPL_VERSION_1_0 (1) --  SUPL version 1.0
      - eQMI_LOC_SUPL_VERSION_2_0 (2) --  SUPL version 2.0
 */

  /* Optional */
  /*  LPP Configuration */
  uint8_t lppConfig_valid;  /**< Must be set to true if lppConfig is being passed */
  qmiLocLppConfigMaskT_v02 lppConfig;
  /**<   LTE Positioning Profile (LPP) configuration.

      Valid bitmasks: \begin{itemize1}
      \item    0x00000001 -- LPP_CONFIG_ ENABLE_USER_PLANE
      \item    0x00000002 -- LPP_CONFIG_ ENABLE_CONTROL_PLANE
      \vspace{-0.18in} \end{itemize1}
  */

  /* Optional */
  /*  Assisted GLONASS Protocol Mask */
  uint8_t assistedGlonassProtocolMask_valid;  /**< Must be set to true if assistedGlonassProtocolMask is being passed */
  qmiLocAssistedGlonassProtocolMaskT_v02 assistedGlonassProtocolMask;
  /**<   Configures the protocols that the location service supports
 for assisted GLONASS.

 Valid bitmasks: \n
      - QMI_LOC_ASSISTED_GLONASS_PROTOCOL_MASK_RRC_CP (0x00000001) --  Assisted GLONASS is supported over RRC in the control plane
      - QMI_LOC_ASSISTED_GLONASS_PROTOCOL_MASK_RRLP_UP (0x00000002) --  Assisted GLONASS is supported over RRLP in the user plane
      - QMI_LOC_ASSISTED_GLONASS_PROTOCOL_MASK_LPP_UP (0x00000004) --  Assisted GLONASS is supported over LPP in the user plane;
       QMI_LOC_LPP_CONFIG_ENABLE_USER_PLANE must be set
       in the LPP configuration for this to take effect
      - QMI_LOC_ASSISTED_GLONASS_PROTOCOL_MASK_LPP_CP (0x00000008) --  Assisted GLONASS is supported over LPP in the control plane;
       QMI_LOC_LPP_CONFIG_ENABLE_CONTROL_PLANE must be set
       in the LPP configuration for this to take effect
 */

  /* Optional */
  /*  SUPL Hash Algorithm */
  uint8_t suplHashAlgo_valid;  /**< Must be set to true if suplHashAlgo is being passed */
  qmiLocSuplHashAlgoEnumT_v02 suplHashAlgo;
  /**<   SUPL hash algorithm to be used.

 Valid values: \n
      - eQMI_LOC_SUPL_HASH_ALGO_SHA1 (0) --  SHA-1 hash algorithm for SUPL version 2.0 or later
      - eQMI_LOC_SUPL_HASH_ALGO_SHA256 (1) --  SHA-256 hash algorithm for SUPL version 2.0 or later
 */

  /* Optional */
  /*  SUPL TLS Version */
  uint8_t suplTlsVersion_valid;  /**< Must be set to true if suplTlsVersion is being passed */
  qmiLocSuplTlsVersionEnumT_v02 suplTlsVersion;
  /**<   SUPL Transport Layer Security (TLS) version. This configuration is only
 applicable to SUPL 2.0 or later, as SUPL 1.0 always uses TLS version 1.0.

 Valid values: \n
      - eQMI_LOC_SUPL_TLS_VERSION_1_0 (0) --  SUPL TLS version 1.0
      - eQMI_LOC_SUPL_TLS_VERSION_1_1 (1) --  SUPL TLS version 1.1
 */

  /* Optional */
  /*  Emergency Protocol */
  uint8_t emergencyProtocol_valid;  /**< Must be set to true if emergencyProtocol is being passed */
  qmiLocEmergencyProtocolEnumT_v02 emergencyProtocol;
  /**<   Configures the protocol to be used during an emergency. \n
 \textbf{Note:} Currently, this can only be selected on WCDMA. For GSM
 and 1X, the UE only allows a control plane NI trigger for positioning.
 For LTE, the UE allows either a SUPL or a control plane NI trigger.

 Valid values: \n
      - eQMI_LOC_EMERGENCY_PROTOCOL_WCDMA_CP (0) --  Use Control Plane Protocol during an emergency while on WCDMA
      - eQMI_LOC_EMERGENCY_PROTOCOL_WCDMA_UP (1) --  Use SUPL 2.0 emergency services during an emergency while on WCDMA
 */

  /* Optional */
  /*  Wi-Fi Scan Injection Timeout Period */
  uint8_t wifiScanInjectTimeout_valid;  /**< Must be set to true if wifiScanInjectTimeout is being passed */
  uint8_t wifiScanInjectTimeout;
  /**<   Configures the timeout duration that the service waits for scan results
  injection from the control point after the event notification is sent. \n
       \textbf{Note:} The timeout value is in seconds. \n
         Values: \n
       0 to 10 seconds \n
       The minimum value (0 seconds) is the default. At this value, the service
       disables sending the Wi-Fi scan injection notification and ignores any
       scan results injection request.
  */
}qmiLocSetProtocolConfigParametersReqMsgT_v02;  /* Message */
/**
    @}
  */

typedef uint64_t qmiLocProtocolConfigParamMaskT_v02;
#define QMI_LOC_PROTOCOL_CONFIG_PARAM_MASK_SUPL_SECURITY_V02 ((qmiLocProtocolConfigParamMaskT_v02)0x0000000000000001ull) /**<  Mask for the SUPL security configuration parameter  */
#define QMI_LOC_PROTOCOL_CONFIG_PARAM_MASK_VX_VERSION_V02 ((qmiLocProtocolConfigParamMaskT_v02)0x0000000000000002ull) /**<  Mask for the VX version configuration parameter  */
#define QMI_LOC_PROTOCOL_CONFIG_PARAM_MASK_SUPL_VERSION_V02 ((qmiLocProtocolConfigParamMaskT_v02)0x0000000000000004ull) /**<  Mask for the SUPL version configuration parameter  */
#define QMI_LOC_PROTOCOL_CONFIG_PARAM_MASK_LPP_CONFIG_V02 ((qmiLocProtocolConfigParamMaskT_v02)0x0000000000000008ull) /**<  Mask for the LPP configuration parameter  */
#define QMI_LOC_PROTOCOL_CONFIG_PARAM_MASK_ASSISTED_GLONASS_PROTOCOL_V02 ((qmiLocProtocolConfigParamMaskT_v02)0x0000000000000010ull) /**<  Mask for the assisted GLONASS configuration parameter  */
#define QMI_LOC_PROTOCOL_CONFIG_PARAM_MASK_SUPL_HASH_ALGO_V02 ((qmiLocProtocolConfigParamMaskT_v02)0x0000000000000020ull) /**<  Mask for the SUPL hash algorithm configuration parameter  */
#define QMI_LOC_PROTOCOL_CONFIG_PARAM_MASK_SUPL_TLS_VERSION_V02 ((qmiLocProtocolConfigParamMaskT_v02)0x0000000000000040ull) /**<  Mask for the SUPL TLS version configuration parameter  */
#define QMI_LOC_PROTOCOL_CONFIG_PARAM_MASK_EMERGENCY_PROTOCOL_V02 ((qmiLocProtocolConfigParamMaskT_v02)0x0000000000000080ull) /**<  Mask for the emergency protocol configuration parameter  */
#define QMI_LOC_PROTOCOL_CONFIG_PARAM_MASK_WIFI_SCAN_INJECT_TIMEOUT_V02 ((qmiLocProtocolConfigParamMaskT_v02)0x0000000000000100ull) /**<  Mask for the Wi-Fi scan injection timeout configuration parameter  */
/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Used by the control point to configure parameters stored
                    in the nonvolatile memory. */
typedef struct {

  /* Mandatory */
  /*  Set Config Params Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Set Configuration Parameters request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */

  /* Optional */
  /*  Failed Parameters */
  uint8_t failedProtocolConfigParamMask_valid;  /**< Must be set to true if failedProtocolConfigParamMask is being passed */
  qmiLocProtocolConfigParamMaskT_v02 failedProtocolConfigParamMask;
  /**<   Identifies parameters that were not set successfully. This field
 is sent only if the status is not SUCCESS.

 Valid bitmasks: \n
      - QMI_LOC_PROTOCOL_CONFIG_PARAM_MASK_SUPL_SECURITY (0x0000000000000001) --  Mask for the SUPL security configuration parameter
      - QMI_LOC_PROTOCOL_CONFIG_PARAM_MASK_VX_VERSION (0x0000000000000002) --  Mask for the VX version configuration parameter
      - QMI_LOC_PROTOCOL_CONFIG_PARAM_MASK_SUPL_VERSION (0x0000000000000004) --  Mask for the SUPL version configuration parameter
      - QMI_LOC_PROTOCOL_CONFIG_PARAM_MASK_LPP_CONFIG (0x0000000000000008) --  Mask for the LPP configuration parameter
      - QMI_LOC_PROTOCOL_CONFIG_PARAM_MASK_ASSISTED_GLONASS_PROTOCOL (0x0000000000000010) --  Mask for the assisted GLONASS configuration parameter
      - QMI_LOC_PROTOCOL_CONFIG_PARAM_MASK_SUPL_HASH_ALGO (0x0000000000000020) --  Mask for the SUPL hash algorithm configuration parameter
      - QMI_LOC_PROTOCOL_CONFIG_PARAM_MASK_SUPL_TLS_VERSION (0x0000000000000040) --  Mask for the SUPL TLS version configuration parameter
      - QMI_LOC_PROTOCOL_CONFIG_PARAM_MASK_EMERGENCY_PROTOCOL (0x0000000000000080) --  Mask for the emergency protocol configuration parameter
      - QMI_LOC_PROTOCOL_CONFIG_PARAM_MASK_WIFI_SCAN_INJECT_TIMEOUT (0x0000000000000100) --  Mask for the Wi-Fi scan injection timeout configuration parameter
 */
}qmiLocSetProtocolConfigParametersIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Used by the control point to get the configuration
                    parameters stored in the nonvolatile memory. */
typedef struct {

  /* Mandatory */
  /*  Config Parameters */
  qmiLocProtocolConfigParamMaskT_v02 getProtocolConfigParamMask;
  /**<   Mask denoting the configuration parameters to be retrieved.

 Valid bitmasks: \n
      - QMI_LOC_PROTOCOL_CONFIG_PARAM_MASK_SUPL_SECURITY (0x0000000000000001) --  Mask for the SUPL security configuration parameter
      - QMI_LOC_PROTOCOL_CONFIG_PARAM_MASK_VX_VERSION (0x0000000000000002) --  Mask for the VX version configuration parameter
      - QMI_LOC_PROTOCOL_CONFIG_PARAM_MASK_SUPL_VERSION (0x0000000000000004) --  Mask for the SUPL version configuration parameter
      - QMI_LOC_PROTOCOL_CONFIG_PARAM_MASK_LPP_CONFIG (0x0000000000000008) --  Mask for the LPP configuration parameter
      - QMI_LOC_PROTOCOL_CONFIG_PARAM_MASK_ASSISTED_GLONASS_PROTOCOL (0x0000000000000010) --  Mask for the assisted GLONASS configuration parameter
      - QMI_LOC_PROTOCOL_CONFIG_PARAM_MASK_SUPL_HASH_ALGO (0x0000000000000020) --  Mask for the SUPL hash algorithm configuration parameter
      - QMI_LOC_PROTOCOL_CONFIG_PARAM_MASK_SUPL_TLS_VERSION (0x0000000000000040) --  Mask for the SUPL TLS version configuration parameter
      - QMI_LOC_PROTOCOL_CONFIG_PARAM_MASK_EMERGENCY_PROTOCOL (0x0000000000000080) --  Mask for the emergency protocol configuration parameter
      - QMI_LOC_PROTOCOL_CONFIG_PARAM_MASK_WIFI_SCAN_INJECT_TIMEOUT (0x0000000000000100) --  Mask for the Wi-Fi scan injection timeout configuration parameter
 */
}qmiLocGetProtocolConfigParametersReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Used by the control point to get the configuration
                    parameters stored in the nonvolatile memory. */
typedef struct {

  /* Mandatory */
  /*  Get Config Params Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Get Configuration Parameters request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */

  /* Optional */
  /*  SUPL Security */
  uint8_t suplSecurity_valid;  /**< Must be set to true if suplSecurity is being passed */
  uint8_t suplSecurity;
  /**<   Indicates whether SUPL security is enabled.
       \begin{itemize1}
       \item    0x01 (TRUE) -- SUPL security is enabled
       \item    0x00 (FALSE) -- SUPL security is disabled
       \vspace{-0.18in} \end{itemize1}*/

  /* Optional */
  /*  VX Version */
  uint8_t vxVersion_valid;  /**< Must be set to true if vxVersion is being passed */
  qmiLocVxVersionEnumT_v02 vxVersion;
  /**<   VX version.

 Valid values: \n
      - eQMI_LOC_VX_VERSION_V1_ONLY (1) --  V1 VX version
      - eQMI_LOC_VX_VERSION_V2_ONLY (2) --  V2 VX version
 */

  /* Optional */
  /*  SUPL Version */
  uint8_t suplVersion_valid;  /**< Must be set to true if suplVersion is being passed */
  qmiLocSuplVersionEnumT_v02 suplVersion;
  /**<   SUPL version.

 Valid values: \n
      - eQMI_LOC_SUPL_VERSION_1_0 (1) --  SUPL version 1.0
      - eQMI_LOC_SUPL_VERSION_2_0 (2) --  SUPL version 2.0
 */

  /* Optional */
  /*  LPP Configuration */
  uint8_t lppConfig_valid;  /**< Must be set to true if lppConfig is being passed */
  qmiLocLppConfigMaskT_v02 lppConfig;
  /**<   LTE Positioning Profile (LPP) configuration.

      Valid bitmasks: \begin{itemize1}
      \item    0x00000001 -- LPP_CONFIG_ ENABLE_USER_PLANE
      \item    0x00000002 -- LPP_CONFIG_ ENABLE_CONTROL_PLANE
      \vspace{-0.18in} \end{itemize1}
  */

  /* Optional */
  /*  Assisted GLONASS Protocol Mask */
  uint8_t assistedGlonassProtocolMask_valid;  /**< Must be set to true if assistedGlonassProtocolMask is being passed */
  qmiLocAssistedGlonassProtocolMaskT_v02 assistedGlonassProtocolMask;
  /**<   Assisted GLONASS Protocol mask.

 Valid bitmasks: \n
      - QMI_LOC_ASSISTED_GLONASS_PROTOCOL_MASK_RRC_CP (0x00000001) --  Assisted GLONASS is supported over RRC in the control plane
      - QMI_LOC_ASSISTED_GLONASS_PROTOCOL_MASK_RRLP_UP (0x00000002) --  Assisted GLONASS is supported over RRLP in the user plane
      - QMI_LOC_ASSISTED_GLONASS_PROTOCOL_MASK_LPP_UP (0x00000004) --  Assisted GLONASS is supported over LPP in the user plane;
       QMI_LOC_LPP_CONFIG_ENABLE_USER_PLANE must be set
       in the LPP configuration for this to take effect
      - QMI_LOC_ASSISTED_GLONASS_PROTOCOL_MASK_LPP_CP (0x00000008) --  Assisted GLONASS is supported over LPP in the control plane;
       QMI_LOC_LPP_CONFIG_ENABLE_CONTROL_PLANE must be set
       in the LPP configuration for this to take effect
 */

  /* Optional */
  /*  SUPL Hash Algorithm */
  uint8_t suplHashAlgo_valid;  /**< Must be set to true if suplHashAlgo is being passed */
  qmiLocSuplHashAlgoEnumT_v02 suplHashAlgo;
  /**<   SUPL hash algorithm to be used.

 Valid values: \n
      - eQMI_LOC_SUPL_HASH_ALGO_SHA1 (0) --  SHA-1 hash algorithm for SUPL version 2.0 or later
      - eQMI_LOC_SUPL_HASH_ALGO_SHA256 (1) --  SHA-256 hash algorithm for SUPL version 2.0 or later
 */

  /* Optional */
  /*  SUPL TLS Version */
  uint8_t suplTlsVersion_valid;  /**< Must be set to true if suplTlsVersion is being passed */
  qmiLocSuplTlsVersionEnumT_v02 suplTlsVersion;
  /**<   SUPL TLS version. This configuration is only
 applicable to SUPL 2.0 or later, as SUPL 1.0 always uses TLS version 1.0.

 Valid values: \n
      - eQMI_LOC_SUPL_TLS_VERSION_1_0 (0) --  SUPL TLS version 1.0
      - eQMI_LOC_SUPL_TLS_VERSION_1_1 (1) --  SUPL TLS version 1.1
 */

  /* Optional */
  /*  Emergency Protocol */
  uint8_t emergencyProtocol_valid;  /**< Must be set to true if emergencyProtocol is being passed */
  qmiLocEmergencyProtocolEnumT_v02 emergencyProtocol;
  /**<   Protocol to be used during emergency.

 Valid values: \n
      - eQMI_LOC_EMERGENCY_PROTOCOL_WCDMA_CP (0) --  Use Control Plane Protocol during an emergency while on WCDMA
      - eQMI_LOC_EMERGENCY_PROTOCOL_WCDMA_UP (1) --  Use SUPL 2.0 emergency services during an emergency while on WCDMA
 */

  /* Optional */
  /*  Wi-Fi Scan Injection Timeout Period */
  uint8_t wifiScanInjectTimeout_valid;  /**< Must be set to true if wifiScanInjectTimeout is being passed */
  uint8_t wifiScanInjectTimeout;
  /**<   Timeout duration that the service waits for a scan results
  injection from the control point after the event notification is sent. \n
       Values: \n
       0 to 10 seconds
  */
}qmiLocGetProtocolConfigParametersIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCSENSORSCONTROLCONFIGSENSORUSEENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_SENSOR_CONFIG_SENSOR_USE_ENABLE_V02 = 0, /**<  Sensors data should be requested whenever a position request is
       received. If sensor data are injected, the positioning engine
       attempts to improve the heading and positioning performance using sensors.
       This is the default.
  */
  eQMI_LOC_SENSOR_CONFIG_SENSOR_USE_DISABLE_V02 = 1, /**<  Inertial sensors are not to be used to aid heading and position
       improvement.  */
  QMILOCSENSORSCONTROLCONFIGSENSORUSEENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocSensorsControlConfigSensorUseEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCSENSORSCONTROLCONFIGSENSORPROVIDERENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_SENSOR_CONFIG_USE_PROVIDER_SSC_V02 = 0, /**<  Sensors data provider is Snapdragon Sensor Core (SSC);
       this is the default
   */
  eQMI_LOC_SENSOR_CONFIG_USE_PROVIDER_NATIVE_V02 = 1, /**<  Sensors data provider is on the host processor  */
  QMILOCSENSORSCONTROLCONFIGSENSORPROVIDERENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocSensorsControlConfigSensorProviderEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Sets the sensor control configuration. */
typedef struct {

  /* Optional */
  /*  Sensors Usage */
  uint8_t sensorsUsage_valid;  /**< Must be set to true if sensorsUsage is being passed */
  qmiLocSensorsControlConfigSensorUseEnumT_v02 sensorsUsage;
  /**<   Controls how sensors are used to aid heading and positioning
 performance.

 Valid values: \n
      - eQMI_LOC_SENSOR_CONFIG_SENSOR_USE_ENABLE (0) --  Sensors data should be requested whenever a position request is
       received. If sensor data are injected, the positioning engine
       attempts to improve the heading and positioning performance using sensors.
       This is the default.

      - eQMI_LOC_SENSOR_CONFIG_SENSOR_USE_DISABLE (1) --  Inertial sensors are not to be used to aid heading and position
       improvement.
 */

  /* Optional */
  /*  Sensors Provider */
  uint8_t sensorProvider_valid;  /**< Must be set to true if sensorProvider is being passed */
  qmiLocSensorsControlConfigSensorProviderEnumT_v02 sensorProvider;
  /**<   Controls which sensors data provider is to be used.

 Valid values: \n
      - eQMI_LOC_SENSOR_CONFIG_USE_PROVIDER_SSC (0) --  Sensors data provider is Snapdragon Sensor Core (SSC);
       this is the default

      - eQMI_LOC_SENSOR_CONFIG_USE_PROVIDER_NATIVE (1) --  Sensors data provider is on the host processor
 */
}qmiLocSetSensorControlConfigReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Sets the sensor control configuration. */
typedef struct {

  /* Mandatory */
  /*  Set Sensor Control Config Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Set Sensor Control Configuration request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */
}qmiLocSetSensorControlConfigIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Retrieves the current sensor control configuration. */
typedef struct {
  /* This element is a placeholder to prevent the declaration of
     an empty struct.  DO NOT USE THIS FIELD UNDER ANY CIRCUMSTANCE */
  char __placeholder;
}qmiLocGetSensorControlConfigReqMsgT_v02;

  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Retrieves the current sensor control configuration. */
typedef struct {

  /* Mandatory */
  /*  Get Sensor Control Config Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Get Sensors Control Configuration request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */

  /* Optional */
  /*  Sensors Usage */
  uint8_t sensorsUsage_valid;  /**< Must be set to true if sensorsUsage is being passed */
  qmiLocSensorsControlConfigSensorUseEnumT_v02 sensorsUsage;
  /**<   Controls how sensors are used to aid the heading and positioning
 performance.

 Valid values: \n
      - eQMI_LOC_SENSOR_CONFIG_SENSOR_USE_ENABLE (0) --  Sensors data should be requested whenever a position request is
       received. If sensor data are injected, the positioning engine
       attempts to improve the heading and positioning performance using sensors.
       This is the default.

      - eQMI_LOC_SENSOR_CONFIG_SENSOR_USE_DISABLE (1) --  Inertial sensors are not to be used to aid heading and position
       improvement.
 */

  /* Optional */
  /*  Sensors Provider */
  uint8_t sensorProvider_valid;  /**< Must be set to true if sensorProvider is being passed */
  qmiLocSensorsControlConfigSensorProviderEnumT_v02 sensorProvider;
  /**<   Controls which sensors data provider to be used.

 Valid values: \n
      - eQMI_LOC_SENSOR_CONFIG_USE_PROVIDER_SSC (0) --  Sensors data provider is Snapdragon Sensor Core (SSC);
       this is the default

      - eQMI_LOC_SENSOR_CONFIG_USE_PROVIDER_NATIVE (1) --  Sensors data provider is on the host processor
 */
}qmiLocGetSensorControlConfigIndMsgT_v02;  /* Message */
/**
    @}
  */

typedef uint32_t qmiLocSensorPropertiesMaskT_v02;
#define QMI_LOC_SENSOR_PROPERTIES_MASK_GYRO_BIAS_VARIANCE_RANDOM_WALK_V02 ((qmiLocSensorPropertiesMaskT_v02)0x00000001) /**<  Denotes the gyro bias variance random walk parameter  */
#define QMI_LOC_SENSOR_PROPERTIES_MASK_VELOCITY_RANDOM_WALK_SPECTRAL_DENSITY_V02 ((qmiLocSensorPropertiesMaskT_v02)0x00000002) /**<  Denotes the velocity random walk spectral density parameter  */
#define QMI_LOC_SENSOR_PROPERTIES_MASK_ACCELERATION_RANDOM_WALK_SPECTRAL_DENSITY_V02 ((qmiLocSensorPropertiesMaskT_v02)0x00000004) /**<  Denotes the acceleration random walk spectral density parameter  */
#define QMI_LOC_SENSOR_PROPERTIES_MASK_ANGLE_RANDOM_WALK_SPECTRAL_DENSITY_V02 ((qmiLocSensorPropertiesMaskT_v02)0x00000008) /**<  Denotes the angle random walk spectral density parameter  */
#define QMI_LOC_SENSOR_PROPERTIES_MASK_RATE_RANDOM_WALK_SPECTRAL_DENSITY_V02 ((qmiLocSensorPropertiesMaskT_v02)0x00000010) /**<  Denotes the rate random walk spectral density parameter  */
#define QMI_LOC_SENSOR_PROPERTIES_MASK_VEHICLE_DATA_USE_CONTROL_V02 ((qmiLocSensorPropertiesMaskT_v02)0x00000020) /**<  Denotes the vehicle data use control parameter  */
#define QMI_LOC_SENSOR_PROPERTIES_MASK_VEHICLE_VELOCITY_RWSD_V02 ((qmiLocSensorPropertiesMaskT_v02)0x00000040) /**<  Denotes the vehicle velocity random walk spectral density  */
#define QMI_LOC_SENSOR_PROPERTIES_MASK_VEHICLE_ACCEL_RWSD_V02 ((qmiLocSensorPropertiesMaskT_v02)0x00000080) /**<  Denotes the vehicle accelerometer random walk spectral density  */
#define QMI_LOC_SENSOR_PROPERTIES_MASK_VEHICLE_ANGLE_RWSD_V02 ((qmiLocSensorPropertiesMaskT_v02)0x00000100) /**<  Denotes the vehicle angle random walk spectral density   */
#define QMI_LOC_SENSOR_PROPERTIES_MASK_VEHICLE_ANGULAR_RATE_RWSD_V02 ((qmiLocSensorPropertiesMaskT_v02)0x00000200) /**<  Denotes the vehicle angular rate random walk spectral density   */
#define QMI_LOC_SENSOR_PROPERTIES_MASK_VEHICLE_ODOMETRY_SCALE_RWSD_V02 ((qmiLocSensorPropertiesMaskT_v02)0x00000400) /**<  Denotes the vehicle odometry scale random walk spectral density   */
#define QMI_LOC_SENSOR_PROPERTIES_MASK_VEHICLE_ODOMETRY_VARIANCE_V02 ((qmiLocSensorPropertiesMaskT_v02)0x00000800) /**<  Denotes the vehicle odometry variance   */
typedef uint64_t qmiLocVehicleDataUseControlMaskT_v02;
#define QMI_LOC_VEHICLE_DATA_ENABLE_USE_MASK_ACCEL_X_AXIS_V02 ((qmiLocVehicleDataUseControlMaskT_v02)0x0000000000000001ull) /**<  Enable use of X-axis vehicle acceleration sensor data  */
#define QMI_LOC_VEHICLE_DATA_ENABLE_USE_MASK_ACCEL_Y_AXIS_V02 ((qmiLocVehicleDataUseControlMaskT_v02)0x0000000000000002ull) /**<  Enable use of Y-axis vehicle acceleration sensor data  */
#define QMI_LOC_VEHICLE_DATA_ENABLE_USE_MASK_ACCEL_Z_AXIS_V02 ((qmiLocVehicleDataUseControlMaskT_v02)0x0000000000000004ull) /**<  Enable use of Z-axis vehicle acceleration sensor data  */
#define QMI_LOC_VEHICLE_DATA_ENABLE_USE_MASK_GYRO_X_AXIS_V02 ((qmiLocVehicleDataUseControlMaskT_v02)0x0000000000000010ull) /**<  Enable use of X-axis vehicle gyroscope data  */
#define QMI_LOC_VEHICLE_DATA_ENABLE_USE_MASK_GYRO_Y_AXIS_V02 ((qmiLocVehicleDataUseControlMaskT_v02)0x0000000000000020ull) /**<  Enable use of Y-axis vehicle gyroscope data  */
#define QMI_LOC_VEHICLE_DATA_ENABLE_USE_MASK_GYRO_Z_AXIS_V02 ((qmiLocVehicleDataUseControlMaskT_v02)0x0000000000000040ull) /**<  Enable use of Z-axis vehicle gyroscope data  */
#define QMI_LOC_VEHICLE_DATA_ENABLE_USE_MASK_ODOMETRY_V02 ((qmiLocVehicleDataUseControlMaskT_v02)0x0000000000000100ull) /**<  Enable use of odometry data  */
/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Sets the properties specific to the type of sensor used.
                    The control point must set sensor properties before they can be
                    used to aid in heading and positioning performance improvement.
   */
typedef struct {

  /* Optional */
  /*  Gyro Bias Random Walk Variance */
  uint8_t gyroBiasVarianceRandomWalk_valid;  /**< Must be set to true if gyroBiasVarianceRandomWalk is being passed */
  float gyroBiasVarianceRandomWalk;
  /**<   Specifies the gyro bias random walk variance parameter as a positive
       floating-point value. This value has internal default value 1.0e-5 radian^2/second^4.
       The gyro bias variance random walk parameter is derived from either the
       sensors data sheet or a sensors conformance test. \n
       - Units: Radians^2/seconds^4

  */

  /* Optional */
  /*  Velocity Random Walk Spectral Density */
  uint8_t velocityRandomWalkSpectralDensity_valid;  /**< Must be set to true if velocityRandomWalkSpectralDensity is being passed */
  float velocityRandomWalkSpectralDensity;
  /**<   Specifies the velocity random walk spectral density parameter as a positive
       floating-point value. This value does not have any internal defaults.
       The velocity random walk spectral density parameter is derived from either the
       sensors data sheet or a sensors conformance test. \n
       - Units: Meters/seconds^2/Hertz^0.5

  */

  /* Optional */
  /*  Acceleration Random Walk Spectral Density */
  uint8_t accelerationRandomWalkSpectralDensity_valid;  /**< Must be set to true if accelerationRandomWalkSpectralDensity is being passed */
  float accelerationRandomWalkSpectralDensity;
  /**<   Specifies the acceleration random walk spectral density parameter as a positive
       floating-point value. This value does not have any internal defaults.
       The acceleration random walk spectral density parameter is derived from either the
       sensors data sheet or a sensors conformance test. \n
       - Units: Meters/seconds^3/Hertz^0.5

  */

  /* Optional */
  /*  Angle Random Walk Spectral Density */
  uint8_t angleRandomWalkSpectralDensity_valid;  /**< Must be set to true if angleRandomWalkSpectralDensity is being passed */
  float angleRandomWalkSpectralDensity;
  /**<   Specifies the angle random walk spectral density parameter as a positive
       floating-point value. This value does not have any internal defaults.
       The angle random walk spectral density parameter is derived from either the
       sensors data sheet or a sensors conformance test. \n
       - Units: Radians/seconds/Hertz^0.5

  */

  /* Optional */
  /*  Rate Random Walk Spectral Density */
  uint8_t rateRandomWalkSpectralDensity_valid;  /**< Must be set to true if rateRandomWalkSpectralDensity is being passed */
  float rateRandomWalkSpectralDensity;
  /**<   Specifies the rate random walk spectral density parameter as a positive
       floating-point value. This value does not have any internal defaults.
       The rate random walk spectral density parameter is derived from either the
       sensors data sheet or a sensors conformance test. \n
       - Units: Radians/seconds^2/Hertz^0.5

  */

  /* Optional */
  /*  Vehicle Data Use Control */
  uint8_t vehicleDataUse_valid;  /**< Must be set to true if vehicleDataUse is being passed */
  qmiLocVehicleDataUseControlMaskT_v02 vehicleDataUse;
  /**<   Identifies which portions of the vehicle data to use in location
 estimation (information provided by the message
 QMI_LOC_INJECT_VEHICLE_SENSOR_DATA). Valid bitmasks: \n
      - QMI_LOC_VEHICLE_DATA_ENABLE_USE_MASK_ACCEL_X_AXIS (0x0000000000000001) --  Enable use of X-axis vehicle acceleration sensor data
      - QMI_LOC_VEHICLE_DATA_ENABLE_USE_MASK_ACCEL_Y_AXIS (0x0000000000000002) --  Enable use of Y-axis vehicle acceleration sensor data
      - QMI_LOC_VEHICLE_DATA_ENABLE_USE_MASK_ACCEL_Z_AXIS (0x0000000000000004) --  Enable use of Z-axis vehicle acceleration sensor data
      - QMI_LOC_VEHICLE_DATA_ENABLE_USE_MASK_GYRO_X_AXIS (0x0000000000000010) --  Enable use of X-axis vehicle gyroscope data
      - QMI_LOC_VEHICLE_DATA_ENABLE_USE_MASK_GYRO_Y_AXIS (0x0000000000000020) --  Enable use of Y-axis vehicle gyroscope data
      - QMI_LOC_VEHICLE_DATA_ENABLE_USE_MASK_GYRO_Z_AXIS (0x0000000000000040) --  Enable use of Z-axis vehicle gyroscope data
      - QMI_LOC_VEHICLE_DATA_ENABLE_USE_MASK_ODOMETRY (0x0000000000000100) --  Enable use of odometry data
 \b Note: All other bits are reserved for future use and are to be set to 0. */

  /* Optional */
  /*  Vehicle Velocity Random Walk Spectral Density */
  uint8_t vehicleVelocityRandomWalkSpectralDensity_valid;  /**< Must be set to true if vehicleVelocityRandomWalkSpectralDensity is being passed */
  float vehicleVelocityRandomWalkSpectralDensity;
  /**<   Vehicle velocity random walk spectral density. \n
       - Type: 32-bit float    \n
       - Units: Meters/seconds^2/Hz^0.5     \n
       - Valid values: Positive values  \n
       - Default: None
  */

  /* Optional */
  /*  Vehicle Acceleration Random Walk Spectral Density */
  uint8_t vehicleAccelRandomWalkSpectralDensity_valid;  /**< Must be set to true if vehicleAccelRandomWalkSpectralDensity is being passed */
  float vehicleAccelRandomWalkSpectralDensity;
  /**<   Vehicle accelerometer random walk spectral density. \n
       - Type: 32-bit float    \n
       - Units: Meters/seconds^3/Hz^0.5     \n
       - Valid values: Positive values  \n
       - Default: None
  */

  /* Optional */
  /*  Vehicle Angle Random Walk Spectral Density */
  uint8_t vehicleAngleRandomWalkSpectralDensity_valid;  /**< Must be set to true if vehicleAngleRandomWalkSpectralDensity is being passed */
  float vehicleAngleRandomWalkSpectralDensity;
  /**<   Vehicle angle random walk spectral density. \n
       - Type: 32-bit float    \n
       - Units: Radians/seconds/Hz^0.5     \n
       - Valid values: Positive values  \n
       - Default: None
  */

  /* Optional */
  /*  Vehicle Angular Rate Random Walk Spectral Density */
  uint8_t vehicleAngularRateRandomWalkSpectralDensity_valid;  /**< Must be set to true if vehicleAngularRateRandomWalkSpectralDensity is being passed */
  float vehicleAngularRateRandomWalkSpectralDensity;
  /**<   Vehicle angular rate random walk spectral density. \n
       - Type: 32-bit float    \n
       - Units: Radians/seconds^2/Hz^0.5 \n
       - Valid values: Positive values  \n
       - Default: None
  */

  /* Optional */
  /*  Vehicle Odometry Scale Factor Random Walk Spectral Density */
  uint8_t vehicleOdometryScaleFactorRandomWalkSpectralDensity_valid;  /**< Must be set to true if vehicleOdometryScaleFactorRandomWalkSpectralDensity is being passed */
  float vehicleOdometryScaleFactorRandomWalkSpectralDensity;
  /**<   Vehicle odometry scale factor random walk spectral density. \n
       - Type: 32-bit float    \n
       - Units: (1/seconds)/Hz^0.5      \n
       - Range: Approximately 0.0001 to 0.001 \n
       - Default: 0.001 (actual calibration recommended)
  */

  /* Optional */
  /*  Vehicle Odometry Variance */
  uint8_t vehicleOdometryVariance_valid;  /**< Must be set to true if vehicleOdometryVariance is being passed */
  float vehicleOdometryVariance;
  /**<   Vehicle odometry variance of each odometry sample
      (coarseness of measurement). \n
       - Type: 32-bit float    \n
       - Units: Meters^2    \n
       - Valid values: Positive values  \n
       - Default: None
  */
}qmiLocSetSensorPropertiesReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Sets the properties specific to the type of sensor used.
                    The control point must set sensor properties before they can be
                    used to aid in heading and positioning performance improvement.
   */
typedef struct {

  /* Mandatory */
  /*  Set Sensor Properties Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Set Sensor Properties request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure  */

  /* Optional */
  /*  Failed Set Sensor Properties */
  uint8_t failedSensorPropertiesMask_valid;  /**< Must be set to true if failedSensorPropertiesMask is being passed */
  qmiLocSensorPropertiesMaskT_v02 failedSensorPropertiesMask;
  /**<   This field is sent only if the status is not SUCCESS.
 Identifies the parameters that were not set successfully.

 Valid bitmasks:
      - QMI_LOC_SENSOR_PROPERTIES_MASK_GYRO_BIAS_VARIANCE_RANDOM_WALK (0x00000001) --  Denotes the gyro bias variance random walk parameter
      - QMI_LOC_SENSOR_PROPERTIES_MASK_VELOCITY_RANDOM_WALK_SPECTRAL_DENSITY (0x00000002) --  Denotes the velocity random walk spectral density parameter
      - QMI_LOC_SENSOR_PROPERTIES_MASK_ACCELERATION_RANDOM_WALK_SPECTRAL_DENSITY (0x00000004) --  Denotes the acceleration random walk spectral density parameter
      - QMI_LOC_SENSOR_PROPERTIES_MASK_ANGLE_RANDOM_WALK_SPECTRAL_DENSITY (0x00000008) --  Denotes the angle random walk spectral density parameter
      - QMI_LOC_SENSOR_PROPERTIES_MASK_RATE_RANDOM_WALK_SPECTRAL_DENSITY (0x00000010) --  Denotes the rate random walk spectral density parameter
      - QMI_LOC_SENSOR_PROPERTIES_MASK_VEHICLE_DATA_USE_CONTROL (0x00000020) --  Denotes the vehicle data use control parameter
      - QMI_LOC_SENSOR_PROPERTIES_MASK_VEHICLE_VELOCITY_RWSD (0x00000040) --  Denotes the vehicle velocity random walk spectral density
      - QMI_LOC_SENSOR_PROPERTIES_MASK_VEHICLE_ACCEL_RWSD (0x00000080) --  Denotes the vehicle accelerometer random walk spectral density
      - QMI_LOC_SENSOR_PROPERTIES_MASK_VEHICLE_ANGLE_RWSD (0x00000100) --  Denotes the vehicle angle random walk spectral density
      - QMI_LOC_SENSOR_PROPERTIES_MASK_VEHICLE_ANGULAR_RATE_RWSD (0x00000200) --  Denotes the vehicle angular rate random walk spectral density
      - QMI_LOC_SENSOR_PROPERTIES_MASK_VEHICLE_ODOMETRY_SCALE_RWSD (0x00000400) --  Denotes the vehicle odometry scale random walk spectral density
      - QMI_LOC_SENSOR_PROPERTIES_MASK_VEHICLE_ODOMETRY_VARIANCE (0x00000800) --  Denotes the vehicle odometry variance
 \vspace{-0.18in} \end{itemize1}
 */
}qmiLocSetSensorPropertiesIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Retrieves the current sensor properties. */
typedef struct {

  /* Mandatory */
  /*  Sensor Properties Config Parameters */
  qmiLocSensorPropertiesMaskT_v02 getSensorPropertiesMask;
  /**<   Mask denoting the sensor properties parameters to be retrieved.

 Valid bitmasks:
      - QMI_LOC_SENSOR_PROPERTIES_MASK_GYRO_BIAS_VARIANCE_RANDOM_WALK (0x00000001) --  Denotes the gyro bias variance random walk parameter
      - QMI_LOC_SENSOR_PROPERTIES_MASK_VELOCITY_RANDOM_WALK_SPECTRAL_DENSITY (0x00000002) --  Denotes the velocity random walk spectral density parameter
      - QMI_LOC_SENSOR_PROPERTIES_MASK_ACCELERATION_RANDOM_WALK_SPECTRAL_DENSITY (0x00000004) --  Denotes the acceleration random walk spectral density parameter
      - QMI_LOC_SENSOR_PROPERTIES_MASK_ANGLE_RANDOM_WALK_SPECTRAL_DENSITY (0x00000008) --  Denotes the angle random walk spectral density parameter
      - QMI_LOC_SENSOR_PROPERTIES_MASK_RATE_RANDOM_WALK_SPECTRAL_DENSITY (0x00000010) --  Denotes the rate random walk spectral density parameter
      - QMI_LOC_SENSOR_PROPERTIES_MASK_VEHICLE_DATA_USE_CONTROL (0x00000020) --  Denotes the vehicle data use control parameter
      - QMI_LOC_SENSOR_PROPERTIES_MASK_VEHICLE_VELOCITY_RWSD (0x00000040) --  Denotes the vehicle velocity random walk spectral density
      - QMI_LOC_SENSOR_PROPERTIES_MASK_VEHICLE_ACCEL_RWSD (0x00000080) --  Denotes the vehicle accelerometer random walk spectral density
      - QMI_LOC_SENSOR_PROPERTIES_MASK_VEHICLE_ANGLE_RWSD (0x00000100) --  Denotes the vehicle angle random walk spectral density
      - QMI_LOC_SENSOR_PROPERTIES_MASK_VEHICLE_ANGULAR_RATE_RWSD (0x00000200) --  Denotes the vehicle angular rate random walk spectral density
      - QMI_LOC_SENSOR_PROPERTIES_MASK_VEHICLE_ODOMETRY_SCALE_RWSD (0x00000400) --  Denotes the vehicle odometry scale random walk spectral density
      - QMI_LOC_SENSOR_PROPERTIES_MASK_VEHICLE_ODOMETRY_VARIANCE (0x00000800) --  Denotes the vehicle odometry variance
 */
}qmiLocGetSensorPropertiesReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Retrieves the current sensor properties. */
typedef struct {

  /* Mandatory */
  /*  Get Sensor Properties Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Get Sensors Properties request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */

  /* Optional */
  /*  Gyro Bias Random Walk Variance */
  uint8_t gyroBiasVarianceRandomWalk_valid;  /**< Must be set to true if gyroBiasVarianceRandomWalk is being passed */
  float gyroBiasVarianceRandomWalk;
  /**<   Specifies the gyro bias random walk variance parameter as a positive
       floating-point value. This value has internal default value 1.0e-5 radian^2/second^4.
       The gyro bias variance random walk parameter is derived from either the
       sensors data sheet or a sensors conformance test. \n
       - Units: Radians^2/seconds^4

  */

  /* Optional */
  /*  Velocity Random Walk Spectral Density */
  uint8_t velocityRandomWalkSpectralDensity_valid;  /**< Must be set to true if velocityRandomWalkSpectralDensity is being passed */
  float velocityRandomWalkSpectralDensity;
  /**<   Specifies the velocity random walk spectral density parameter as a positive
       floating-point value. This value does not have any internal defaults.
       The velocity random walk spectral density parameter is derived from either the
       sensors data sheet or a sensors conformance test. \n
       - Units: Meters/seconds^2/Hertz^0.5

  */

  /* Optional */
  /*  Acceleration Random Walk Spectral Density */
  uint8_t accelerationRandomWalkSpectralDensity_valid;  /**< Must be set to true if accelerationRandomWalkSpectralDensity is being passed */
  float accelerationRandomWalkSpectralDensity;
  /**<   Specifies the acceleration random walk spectral density parameter as a positive
       floating-point value. This value does not have any internal defaults.
       The acceleration random walk spectral density parameter is derived from either the
       sensors data sheet or a sensors conformance test. \n
       - Units: Meters/seconds^3/Hertz^0.5

  */

  /* Optional */
  /*  Angle Random Walk Spectral Density */
  uint8_t angleRandomWalkSpectralDensity_valid;  /**< Must be set to true if angleRandomWalkSpectralDensity is being passed */
  float angleRandomWalkSpectralDensity;
  /**<   Specifies the angle random walk spectral density parameter as a positive
       floating-point value. This value does not have any internal defaults.
       The angle random walk spectral density parameter is derived from either the
       sensors data sheet or a sensors conformance test. \n
       - Units: Radians/seconds/Hertz^0.5

  */

  /* Optional */
  /*  Rate Random Walk Spectral Density */
  uint8_t rateRandomWalkSpectralDensity_valid;  /**< Must be set to true if rateRandomWalkSpectralDensity is being passed */
  float rateRandomWalkSpectralDensity;
  /**<   Specifies the rate random walk spectral density parameter as a positive
       floating-point value. This value does not have any internal defaults.
       The rate random walk spectral density parameter is derived from either the
       sensors data sheet or a sensors conformance test. \n
       - Units: Radians/seconds^2/Hertz^0.5

  */

  /* Optional */
  /*  Vehicle Data Use Control */
  uint8_t vehicleDataUse_valid;  /**< Must be set to true if vehicleDataUse is being passed */
  qmiLocVehicleDataUseControlMaskT_v02 vehicleDataUse;
  /**<   Identifies which portions of the vehicle data to use in location
 estimation (information provided by message
 QMI_LOC_INJECT_VEHICLE_SENSOR_DATA). Valid bitmasks: \n
      - QMI_LOC_VEHICLE_DATA_ENABLE_USE_MASK_ACCEL_X_AXIS (0x0000000000000001) --  Enable use of X-axis vehicle acceleration sensor data
      - QMI_LOC_VEHICLE_DATA_ENABLE_USE_MASK_ACCEL_Y_AXIS (0x0000000000000002) --  Enable use of Y-axis vehicle acceleration sensor data
      - QMI_LOC_VEHICLE_DATA_ENABLE_USE_MASK_ACCEL_Z_AXIS (0x0000000000000004) --  Enable use of Z-axis vehicle acceleration sensor data
      - QMI_LOC_VEHICLE_DATA_ENABLE_USE_MASK_GYRO_X_AXIS (0x0000000000000010) --  Enable use of X-axis vehicle gyroscope data
      - QMI_LOC_VEHICLE_DATA_ENABLE_USE_MASK_GYRO_Y_AXIS (0x0000000000000020) --  Enable use of Y-axis vehicle gyroscope data
      - QMI_LOC_VEHICLE_DATA_ENABLE_USE_MASK_GYRO_Z_AXIS (0x0000000000000040) --  Enable use of Z-axis vehicle gyroscope data
      - QMI_LOC_VEHICLE_DATA_ENABLE_USE_MASK_ODOMETRY (0x0000000000000100) --  Enable use of odometry data
 @note1 All other bits are reserved for future use and are to be set to 0. */

  /* Optional */
  /*  Vehicle Velocity Random Walk Spectral Density */
  uint8_t vehicleVelocityRandomWalkSpectralDensity_valid;  /**< Must be set to true if vehicleVelocityRandomWalkSpectralDensity is being passed */
  float vehicleVelocityRandomWalkSpectralDensity;
  /**<   Vehicle velocity random walk spectral density. \n
       - Type: 32-bit float    \n
       - Units: Meters/seconds^2/Hz^0.5     \n
       - Valid values: Positive values  \n
       - Default: None
  */

  /* Optional */
  /*  Vehicle Acceleration Random Walk Spectral Density */
  uint8_t vehicleAccelRandomWalkSpectralDensity_valid;  /**< Must be set to true if vehicleAccelRandomWalkSpectralDensity is being passed */
  float vehicleAccelRandomWalkSpectralDensity;
  /**<   Vehicle accelerometer random walk spectral density. \n
       - Type: 32-bit float    \n
       - Units: Meters/seconds^3/Hz^0.5     \n
       - Valid values: Positive values  \n
       - Default: None
  */

  /* Optional */
  /*  Vehicle Angle Random Walk Spectral Density */
  uint8_t vehicleAngleRandomWalkSpectralDensity_valid;  /**< Must be set to true if vehicleAngleRandomWalkSpectralDensity is being passed */
  float vehicleAngleRandomWalkSpectralDensity;
  /**<   Vehicle angle random walk spectral density. \n
       - Type: 32-bit float    \n
       - Units: Radians/seconds/Hz^0.5     \n
       - Valid values: Positive values  \n
       - Default: None
  */

  /* Optional */
  /*  Vehicle Angular Rate Random Walk Spectral Density */
  uint8_t vehicleAngularRateRandomWalkSpectralDensity_valid;  /**< Must be set to true if vehicleAngularRateRandomWalkSpectralDensity is being passed */
  float vehicleAngularRateRandomWalkSpectralDensity;
  /**<   Vehicle angular rate random walk spectral density. \n
       - Type: 32-bit float    \n
       - Units: Radians/seconds^2/Hz^0.5 \n
       - Valid values: Positive values  \n
       - Default: None
  */

  /* Optional */
  /*  Vehicle Odometry Scale Factor Random Walk Spectral Density */
  uint8_t vehicleOdometryScaleFactorRandomWalkSpectralDensity_valid;  /**< Must be set to true if vehicleOdometryScaleFactorRandomWalkSpectralDensity is being passed */
  float vehicleOdometryScaleFactorRandomWalkSpectralDensity;
  /**<   Vehicle odometry scale factor random walk spectral density. \n
       - Type: 32-bit float    \n
       - Units: (1/seconds)/Hz^0.5      \n
       - Range: Approximately 0.0001 to 0.001 \n
       - Default: 0.001 (actual calibration recommended)
  */

  /* Optional */
  /*  Vehicle Odometry Variance */
  uint8_t vehicleOdometryVariance_valid;  /**< Must be set to true if vehicleOdometryVariance is being passed */
  float vehicleOdometryVariance;
  /**<   Vehicle odometry variance of each odometry sample
      (coarseness of measurement). \n
       - Type: 32-bit float    \n
       - Units: Meters^2    \n
       - Valid values: Positive values  \n
       - Default: None
  */
}qmiLocGetSensorPropertiesIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCSENSORPERFORMANCECONTROLMODEENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_SENSOR_PERFORMANCE_CONTROL_MODE_AUTO_V02 = 0, /**<  Sensors usage is to be determined by the GNSS location engine.
       This mode can optimize power consumption and give a
       power-balanced positioning and heading enhancement using
       inertial sensors  */
  eQMI_LOC_SENSOR_PERFORMANCE_CONTROL_MODE_FORCED_V02 = 1, /**<  Sensors usage is to be forced ON.
       This mode can be requested by the control point when
       power consumption is not a restriction to the use of
       inertial sensors.  */
  QMILOCSENSORPERFORMANCECONTROLMODEENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocSensorPerformanceControlModeEnumT_v02;
/**
    @}
  */

typedef uint32_t qmiLocSensorAlgorithmMaskT_v02;
#define QMI_LOC_SENSOR_ALGORITHM_MASK_DISABLE_INS_POSITIONING_FILTER_V02 ((qmiLocSensorAlgorithmMaskT_v02)0x00000001) /**<  Inertial sensors are not to be used in Accelerometer-integrated fashion with
       GNSS. They can still be used for aiding in heading improvements.  */
/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Provides fine-grained control of sensor based positioning
                    performance. */
typedef struct {

  /* Optional */
  /*  Sensor Performance Control Mode */
  uint8_t performanceControlMode_valid;  /**< Must be set to true if performanceControlMode is being passed */
  qmiLocSensorPerformanceControlModeEnumT_v02 performanceControlMode;
  /**<   Controls when sensors data is requested during GNSS fix processing.
 This field is relevant only when sensors have been enabled using the
 sensors control configuration.

 Valid values: \n
      - eQMI_LOC_SENSOR_PERFORMANCE_CONTROL_MODE_AUTO (0) --  Sensors usage is to be determined by the GNSS location engine.
       This mode can optimize power consumption and give a
       power-balanced positioning and heading enhancement using
       inertial sensors
      - eQMI_LOC_SENSOR_PERFORMANCE_CONTROL_MODE_FORCED (1) --  Sensors usage is to be forced ON.
       This mode can be requested by the control point when
       power consumption is not a restriction to the use of
       inertial sensors.
 */

  /* Optional */
  /*  Accelerometer Sampling Specification */
  uint8_t accelSamplingSpec_valid;  /**< Must be set to true if accelSamplingSpec is being passed */
  qmiLocSensorControlConfigSamplingSpecStructT_v02 accelSamplingSpec;
  /**<   \vspace{0.06in} \n Sets the nominal rate at which the GNSS location
       engine is to request acceleration data to be used by the low data rate
       filter. The sensor data rate is specified in terms of the nominal number
       of samples per batch and the number of batches per second.
       However, the final control of the actual requested rate resides with
       the Sensors Manager Module/GNSS location engine. \n
       Default: 10 Hz sampling rate and 2 Hz batching rate.
  */

  /* Optional */
  /*  Gyroscope Sampling Specification */
  uint8_t gyroSamplingSpec_valid;  /**< Must be set to true if gyroSamplingSpec is being passed */
  qmiLocSensorControlConfigSamplingSpecStructT_v02 gyroSamplingSpec;
  /**<   \vspace{0.06in} \n Sets the nominal rate at which the GNSS location
       engine is to request gyro data to be used by the high data rate filter.
       The sensor data rate is specified in terms of the nominal number of
       samples per batch and the number of batches per second.
       However, the final control of the actual requested rate resides with
       the Sensors Manager Module/GNSS location engine. \n
       Default: 10 Hz sampling rate and 2 Hz batching rate.
  */

  /* Optional */
  /*  Algorithm Configuration */
  uint8_t algorithmConfig_valid;  /**< Must be set to true if algorithmConfig is being passed */
  qmiLocSensorAlgorithmMaskT_v02 algorithmConfig;
  /**<   Sets which sensor algorithms are to be used when processing sensor data.

       Valid bitmasks: \begin{itemize1}
       \item    0x00000001 -- DISABLE_INS_ POSITIONING_FILTER
       \vspace{-0.18in} \end{itemize1}
  */

  /* Optional */
  /*  High Data Rate Filter Accelerometer Sampling Specification */
  uint8_t accelSamplingSpecHigh_valid;  /**< Must be set to true if accelSamplingSpecHigh is being passed */
  qmiLocSensorControlConfigSamplingSpecStructT_v02 accelSamplingSpecHigh;
  /**<   \vspace{0.06in} \n Sets the nominal rate at which the GNSS location engine is to request
       acceleration data to be used by the high data rate filter. The sensor
       data rate is specified in terms of the nominal number of samples per
       batch and the number of batches per second.
       However, the final control of the actual requested rate resides with
       the Sensors Manager Module/GNSS location engine. \n
       Default: 100 Hz sampling rate and 4 Hz batching rate.
  */

  /* Optional */
  /*  High Data Rate Filter Gyroscope Sampling Specification */
  uint8_t gyroSamplingSpecHigh_valid;  /**< Must be set to true if gyroSamplingSpecHigh is being passed */
  qmiLocSensorControlConfigSamplingSpecStructT_v02 gyroSamplingSpecHigh;
  /**<   \vspace{0.06in} \n Sets the nominal rate at which the GNSS location engine is to request
       gyro data to be used by the high data rate filter. The sensor data rate
       is specified in terms of the nominal number of samples per batch and the
       number of batches per second.
       However, the final control of the actual requested rate resides with
       the Sensors Manager Module/GNSS location engine. \n
       Default: 100 Hz sampling rate and 4 Hz batching rate.
  */
}qmiLocSetSensorPerformanceControlConfigReqMsgT_v02;  /* Message */
/**
    @}
  */

typedef uint32_t qmiLocSensorPerformanceControlConfigFailureMaskT_v02;
#define QMI_LOC_SENSOR_PERFORMANCE_CONTROL_CONFIG_PARAM_MASK_PERFORMANCE_MODE_V02 ((qmiLocSensorPerformanceControlConfigFailureMaskT_v02)0x00000001) /**<  Failed to set the performance mode  */
#define QMI_LOC_SENSOR_PERFORMANCE_CONTROL_CONFIG_PARAM_MASK_ACCEL_SAMPLING_SPEC_V02 ((qmiLocSensorPerformanceControlConfigFailureMaskT_v02)0x00000002) /**<  Failed to set the accelerometer sampling specification  */
#define QMI_LOC_SENSOR_PERFORMANCE_CONTROL_CONFIG_PARAM_MASK_GYRO_SAMPLING_SPEC_V02 ((qmiLocSensorPerformanceControlConfigFailureMaskT_v02)0x00000004) /**<  Failed to set the gyroscope sampling specification  */
#define QMI_LOC_SENSOR_PERFORMANCE_CONTROL_CONFIG_PARAM_MASK_ALGORITHM_CONFIG_V02 ((qmiLocSensorPerformanceControlConfigFailureMaskT_v02)0x00000008) /**<  Failed to set the algorithm configuration  */
#define QMI_LOC_SENSOR_PERFORMANCE_CONTROL_CONFIG_PARAM_MASK_ACCEL_SAMPLING_SPEC_HIGH_V02 ((qmiLocSensorPerformanceControlConfigFailureMaskT_v02)0x00000010) /**<  Failed to set the accelerometer sampling specification  */
#define QMI_LOC_SENSOR_PERFORMANCE_CONTROL_CONFIG_PARAM_MASK_GYRO_SAMPLING_SPEC_HIGH_V02 ((qmiLocSensorPerformanceControlConfigFailureMaskT_v02)0x00000020) /**<  Failed to set the gyroscope sampling specification  */
/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Provides fine-grained control of sensor based positioning
                    performance. */
typedef struct {

  /* Mandatory */
  /*  Set Sensor Perf Control Config Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Set Sensor Performance Control Configuration request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */

  /* Optional */
  /*  Failed Configuration */
  uint8_t failedConfiguration_valid;  /**< Must be set to true if failedConfiguration is being passed */
  qmiLocSensorPerformanceControlConfigFailureMaskT_v02 failedConfiguration;
  /**<   Identifies parameters that were not configured successfully. This field
       is sent only if the status is not a success.


       Valid bitmasks: \begin{itemize1}
       \item    0x00000001 -- PERFORMANCE_ MODE
       \item    0x00000002 -- ACCEL_SAMPLING_ SPEC
       \item    0x00000004 -- GYRO_SAMPLING_ SPEC
       \item    0x00000008 -- ALGORITHM_ CONFIG
       \item    0x00000010 -- ACCEL_SAMPLING_ SPEC_HIGH
       \item    0x00000020 -- GYRO_SAMPLING_ SPEC_HIGH
       \vspace{-0.18in} \end{itemize1}
  */
}qmiLocSetSensorPerformanceControlConfigIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Retrieves the current sensor performance control
                    configuration. */
typedef struct {
  /* This element is a placeholder to prevent the declaration of
     an empty struct.  DO NOT USE THIS FIELD UNDER ANY CIRCUMSTANCE */
  char __placeholder;
}qmiLocGetSensorPerformanceControlConfigReqMsgT_v02;

  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Retrieves the current sensor performance control
                    configuration. */
typedef struct {

  /* Mandatory */
  /*  Get Sensor Perf Control Config Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Get Sensor Performance Control Configuration request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */

  /* Optional */
  /*  Performance Control Mode */
  uint8_t performanceControlMode_valid;  /**< Must be set to true if performanceControlMode is being passed */
  qmiLocSensorPerformanceControlModeEnumT_v02 performanceControlMode;
  /**<   Controls when sensor data is requested during GNSS fix processing.
 This field is relevant only when sensors have been enabled using the
 sensor control configuration.

 Valid values: \n
      - eQMI_LOC_SENSOR_PERFORMANCE_CONTROL_MODE_AUTO (0) --  Sensors usage is to be determined by the GNSS location engine.
       This mode can optimize power consumption and give a
       power-balanced positioning and heading enhancement using
       inertial sensors
      - eQMI_LOC_SENSOR_PERFORMANCE_CONTROL_MODE_FORCED (1) --  Sensors usage is to be forced ON.
       This mode can be requested by the control point when
       power consumption is not a restriction to the use of
       inertial sensors.
 */

  /* Optional */
  /*  Accelerometer Sampling Specification */
  uint8_t accelSamplingSpec_valid;  /**< Must be set to true if accelSamplingSpec is being passed */
  qmiLocSensorControlConfigSamplingSpecStructT_v02 accelSamplingSpec;
  /**<   \vspace{0.06in} \n Sets the nominal rate at which the GNSS location engine is to request
       acceleration data to be used by the high data rate filter. The sensor
       data rate is specified in terms of the nominal number of samples per
       batch and the number of batches per second.
       However, the final control of the actual requested rate resides with
       the Sensors Manager Module/GNSS location engine. \n
       Default: 10 Hz sampling rate and 2 Hz batching rate.
  */

  /* Optional */
  /*  Gyroscope Sampling Specification */
  uint8_t gyroSamplingSpec_valid;  /**< Must be set to true if gyroSamplingSpec is being passed */
  qmiLocSensorControlConfigSamplingSpecStructT_v02 gyroSamplingSpec;
  /**<   \vspace{0.06in} \n Sets the nominal rate at which the GNSS location engine is to request
       gyro data to be used by the high data rate filter. The sensor data
       rate is specified in terms of the nominal number of samples per batch
       and the number of batches per second.
       However, the final control of the actual requested rate resides with
       the Sensors Manager Module/GNSS location engine. \n
       Default: 10 Hz sampling rate and 2 Hz batching rate.
  */

  /* Optional */
  /*  Algorithm Configuration */
  uint8_t algorithmConfig_valid;  /**< Must be set to true if algorithmConfig is being passed */
  qmiLocSensorAlgorithmMaskT_v02 algorithmConfig;
  /**<   Informs which sensor algorithms are currently set.

       Valid bitmasks: \begin{itemize1}
       \item    0x00000001 -- DISABLE_INS_ POSITIONING_FILTER
       \vspace{-0.18in} \end{itemize1}
  */

  /* Optional */
  /*  High Data Rate Filter Accelerometer Sampling Specification */
  uint8_t accelSamplingSpecHigh_valid;  /**< Must be set to true if accelSamplingSpecHigh is being passed */
  qmiLocSensorControlConfigSamplingSpecStructT_v02 accelSamplingSpecHigh;
  /**<   \vspace{0.06in} \n Sets the nominal rate at which the GNSS location engine is to request
       acceleration data to be used by the high data rate filter. The sensor
       data rate is specified in terms of the nominal number of samples per
       batch and the number of batches per second.
       However, the final control of the actual requested rate resides with
       the Sensors Manager Module/GNSS location engine. \n
       Default: 100 Hz sampling rate and 4 Hz batching rate.
  */

  /* Optional */
  /*  High Data Rate Filter Gyroscope Sampling Specification */
  uint8_t gyroSamplingSpecHigh_valid;  /**< Must be set to true if gyroSamplingSpecHigh is being passed */
  qmiLocSensorControlConfigSamplingSpecStructT_v02 gyroSamplingSpecHigh;
  /**<   \vspace{0.06in} \n Sets the nominal rate at which the GNSS location engine is to request
       gyro data to be used by the high data rate filter. The sensor data rate
       is specified in terms of the nominal number of samples per batch and the
       number of batches per second.
       However, the final control of the actual requested rate resides with
       the Sensors Manager Module/GNSS location engine. \n
       Default: 100 Hz sampling rate and 4 Hz batching rate.
  */
}qmiLocGetSensorPerformanceControlConfigIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Injects a SUPL certificate to be used in AGNSS sessions. */
typedef struct {

  /* Mandatory */
  /*  SUPL Certificate ID */
  uint8_t suplCertId;
  /**<   Certificate ID of the SUPL certificate. \n
       - Units: Bytes \n
       - Range: 0 to 9  */

  /* Mandatory */
  /*  SUPL Certificate Data */
  uint32_t suplCertData_len;  /**< Must be set to # of elements in suplCertData */
  uint8_t suplCertData[QMI_LOC_MAX_SUPL_CERT_LENGTH_V02];
  /**<   SUPL certificate contents. \n
       - Type: Array of bytes \n
       - Maximum certificate size: 2000 bytes */
}qmiLocInjectSuplCertificateReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Injects a SUPL certificate to be used in AGNSS sessions. */
typedef struct {

  /* Mandatory */
  /*  SUPL Certificate Injection Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Inject SUPL Certificate request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */
}qmiLocInjectSuplCertificateIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Deletes a SUPL certificate. */
typedef struct {

  /* Optional */
  /*  SUPL Certificate ID */
  uint8_t suplCertId_valid;  /**< Must be set to true if suplCertId is being passed */
  uint8_t suplCertId;
  /**<   Certificate ID of the SUPL certificate to be deleted. \n
       - Units: Bytes \n
       - Range: 0 to 9 \n
       If suplCertId is not specified,
       all SUPL certificates are deleted. */
}qmiLocDeleteSuplCertificateReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Deletes a SUPL certificate. */
typedef struct {

  /* Mandatory */
  /*  SUPL Certificate Deletion Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Delete SUPL Certificate request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */
}qmiLocDeleteSuplCertificateIndMsgT_v02;  /* Message */
/**
    @}
  */

typedef uint32_t qmiLocPositionEngineConfigParamMaskT_v02;
#define QMI_LOC_POSITION_ENGINE_CONFIG_PARAM_MASK_INJECTED_POSITION_CONTROL_V02 ((qmiLocPositionEngineConfigParamMaskT_v02)0x00000001) /**<  Denotes whether the position engine uses the
       injected position in a direct position calculation.  */
#define QMI_LOC_POSITION_ENGINE_CONFIG_PARAM_MASK_FILTER_SV_USAGE_V02 ((qmiLocPositionEngineConfigParamMaskT_v02)0x00000002) /**<  Denotes whether the position engine filters the
       SV usage in the fix.  */
#define QMI_LOC_POSITION_ENGINE_CONFIG_PARAM_MASK_STORE_ASSIST_DATA_V02 ((qmiLocPositionEngineConfigParamMaskT_v02)0x00000004) /**<  Denotes whether the position engine stores assistance data
       in persistent memory.  */
#define QMI_LOC_POSITION_ENGINE_CONFIG_PARAM_MASK_ENABLE_FASTER_TTFF_V02 ((qmiLocPositionEngineConfigParamMaskT_v02)0x00000008) /**<  Denotes whether the position engine stays on to optimize
       the TTFF for the subsequent position fix.  */
/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Used by the control point to configure position engine
                    functionality. */
typedef struct {

  /* Optional */
  /*  Injected Position Control */
  uint8_t injectedPositionControl_valid;  /**< Must be set to true if injectedPositionControl is being passed */
  uint8_t injectedPositionControl;
  /**<   Controls how the injected position is used in the position engine.

       Valid values: \begin{itemize1}
       \item    0x01 (TRUE) -- Use the injected position in a direct position
                               calculation
       \item    0x00 (FALSE) -- Do not use the injected position in a direct
                                position calculation
       \end{itemize1}
       The default value is TRUE.
  */

  /* Optional */
  /*  Filter SV Usage */
  uint8_t filterSvUsage_valid;  /**< Must be set to true if filterSvUsage is being passed */
  uint8_t filterSvUsage;
  /**<   Controls whether SV usage is filtered in a position fix.

       Valid values: \begin{itemize1}
       \item    0x01 (TRUE) -- Filter the usage of SVs in the fix
       \item    0x00 (FALSE) -- Do not filter the usage of SVs in the fix
       \end{itemize1}
       The default value is FALSE.
  */

  /* Optional */
  /*  Store Assist Data */
  uint8_t storeAssistData_valid;  /**< Must be set to true if storeAssistData is being passed */
  uint8_t storeAssistData;
  /**<   Controls whether assistance data is to be stored in
       persistent memory.

       Valid values: \begin{itemize1}
       \item    0x01 (TRUE) -- Store assistance data in persistent memory
       \item    0x00 (FALSE) -- Do not store assistance data in persistent memory
       \end{itemize1}
       The default value is TRUE.
  */

  /* Optional */
  /*  Enable Faster TTFF */
  uint8_t enableFasterTTFF_valid;  /**< Must be set to true if enableFasterTTFF is being passed */
  uint8_t enableFasterTTFF;
  /**<   Allows the receiver to stay on after a position session in order to
       collect information that will help reduce the Time To First Fix (TTFF)
       when the next position request is made. The receiver will stay
       on only if  the engine determines that it needs to collect some
       information. The receiver will stay on for the duration needed to
       collect the information.
       If enabled, the clients may see a delay in receiving the Engine Off
       event after the position session ends.

       Valid values: \begin{itemize1}
       \item    0x01 (TRUE) -- Allow the engine to stay on for reduced TTFF
       \item    0x00 (FALSE) -- Do not allow the engine to stay on for reduced
                               TTFF
       \end{itemize1}
       The default value is TRUE.*/
}qmiLocSetPositionEngineConfigParametersReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Used by the control point to configure position engine
                    functionality. */
typedef struct {

  /* Mandatory */
  /*  Set Position Engine Configuration Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Set Configuration Parameters request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */

  /* Optional */
  /*  Failed Parameters */
  uint8_t failedPositionEngineConfigParamMask_valid;  /**< Must be set to true if failedPositionEngineConfigParamMask is being passed */
  qmiLocPositionEngineConfigParamMaskT_v02 failedPositionEngineConfigParamMask;
  /**<   Identifies the parameters that were not set successfully.
 This field is sent only if the status is other than SUCCESS.

 Valid bitmasks:\n
      - QMI_LOC_POSITION_ENGINE_CONFIG_PARAM_MASK_INJECTED_POSITION_CONTROL (0x00000001) --  Denotes whether the position engine uses the
       injected position in a direct position calculation.
      - QMI_LOC_POSITION_ENGINE_CONFIG_PARAM_MASK_FILTER_SV_USAGE (0x00000002) --  Denotes whether the position engine filters the
       SV usage in the fix.
      - QMI_LOC_POSITION_ENGINE_CONFIG_PARAM_MASK_STORE_ASSIST_DATA (0x00000004) --  Denotes whether the position engine stores assistance data
       in persistent memory.
      - QMI_LOC_POSITION_ENGINE_CONFIG_PARAM_MASK_ENABLE_FASTER_TTFF (0x00000008) --  Denotes whether the position engine stays on to optimize
       the TTFF for the subsequent position fix.
 */
}qmiLocSetPositionEngineConfigParametersIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Used by the control point to get the position engine
                    configuration parameters. */
typedef struct {

  /* Mandatory */
  /*  Config Parameters */
  qmiLocPositionEngineConfigParamMaskT_v02 getPositionEngineConfigParamMask;
  /**<   Mask denoting the configuration parameters to be retrieved.

 Valid bitmasks:
      - QMI_LOC_POSITION_ENGINE_CONFIG_PARAM_MASK_INJECTED_POSITION_CONTROL (0x00000001) --  Denotes whether the position engine uses the
       injected position in a direct position calculation.
      - QMI_LOC_POSITION_ENGINE_CONFIG_PARAM_MASK_FILTER_SV_USAGE (0x00000002) --  Denotes whether the position engine filters the
       SV usage in the fix.
      - QMI_LOC_POSITION_ENGINE_CONFIG_PARAM_MASK_STORE_ASSIST_DATA (0x00000004) --  Denotes whether the position engine stores assistance data
       in persistent memory.
      - QMI_LOC_POSITION_ENGINE_CONFIG_PARAM_MASK_ENABLE_FASTER_TTFF (0x00000008) --  Denotes whether the position engine stays on to optimize
       the TTFF for the subsequent position fix.
 */
}qmiLocGetPositionEngineConfigParametersReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Used by the control point to get the position engine
                    configuration parameters. */
typedef struct {

  /* Mandatory */
  /*  Get Position Engine Configuration Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Get Configuration Parameters request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */

  /* Optional */
  /*  Injected Position Control */
  uint8_t injectedPositionControl_valid;  /**< Must be set to true if injectedPositionControl is being passed */
  uint8_t injectedPositionControl;
  /**<   Specifies whether the injected position is used for a direct calculation
       in the position engine.

       Valid values: \begin{itemize1}
       \item    0x01 (TRUE) -- The injected position is used in a direct
                               position calculation
       \item    0x00 (FALSE) -- The injected position is not used in a direct
                                position calculation
       \end{itemize1}
       The default value is TRUE.
  */

  /* Optional */
  /*  Filter SV Usage */
  uint8_t filterSvUsage_valid;  /**< Must be set to true if filterSvUsage is being passed */
  uint8_t filterSvUsage;
  /**<   Specifies whether SV usage is filtered in a position fix.

       Valid values: \begin{itemize1}
       \item    0x01 (TRUE) -- SV usage is filtered in the fix
       \item    0x00 (FALSE) -- SV usage is not filtered in the fix
       \end{itemize1}
       The default value is FALSE.
  */

  /* Optional */
  /*  Store Assist Data */
  uint8_t storeAssistData_valid;  /**< Must be set to true if storeAssistData is being passed */
  uint8_t storeAssistData;
  /**<   Specifies whether assistance data is stored in persistent memory.

       Valid values: \begin{itemize1}
       \item    0x01 (TRUE) -- Assistance data is stored in persistent memory
       \item    0x00 (FALSE) -- Assistance data is not stored in persistent
                                memory
       \end{itemize1}
       The default value is TRUE.
  */

  /* Optional */
  /*  Enable Faster TTFF */
  uint8_t enableFasterTTFF_valid;  /**< Must be set to true if enableFasterTTFF is being passed */
  uint8_t enableFasterTTFF;
  /**<   Allows the receiver to stay on after a position session in order to
       collect information that will help reduce the TTFF
       when the next position request is made. The receiver will stay
       on only if  the engine determines that it needs to collect some
       information. The receiver will stay on for the duration needed to
       collect the information.
       If enabled, the clients may see a delay in receiving the Engine Off
       event after the position session ends.

       Valid values: \begin{itemize1}
       \item    0x01 (TRUE) -- Allow the engine to stay on for reduced TTFF
       \item    0x00 (FALSE) -- Do not allow the engine to stay on for reduced
                               TTFF
       \end{itemize1}
        The default value is TRUE.*/
}qmiLocGetPositionEngineConfigParametersIndMsgT_v02;  /* Message */
/**
    @}
  */

typedef uint8_t qmiLocGeofenceBreachMaskT_v02;
#define QMI_LOC_GEOFENCE_BREACH_ENTERING_MASK_V02 ((qmiLocGeofenceBreachMaskT_v02)0x01) /**<  If this mask is set, a breach event is reported
       when the Geofence is entered  */
#define QMI_LOC_GEOFENCE_BREACH_LEAVING_MASK_V02 ((qmiLocGeofenceBreachMaskT_v02)0x02) /**<  If this mask is set, a breach event is reported
       when the Geofence is exited  */
/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCGEOFENCERESPONSIVENESSENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_GEOFENCE_RESPONSIVENESS_LOW_V02 = 0x01, /**<  The Geofence is monitored for a breach at a
       low rate of 15 minutes. The gap between the actual breach and
       the time it is reported is higher. This
       setting results in lower power usage.  */
  eQMI_LOC_GEOFENCE_RESPONSIVENESS_MED_V02 = 0x02, /**<  The Geofence is monitored for a breach at a
       medium rate of 2 minutes. This is the default setting.  */
  eQMI_LOC_GEOFENCE_RESPONSIVENESS_HIGH_V02 = 0x03, /**<  The Geofence is monitored for a breach at a
       high rate of 10 seconds. The gap between the actual breach and
       the time it is reported is low. This results
       in higher power usage.  */
  eQMI_LOC_GEOFENCE_RESPONSIVENESS_ULTRA_HIGH_V02 = 0x04, /**<  The Geofence is monitored for a breach at a
       very high rate of 1 second. The gap between the actual breach and
       the time it is reported is very low. This results
       in very high power usage. This setting must be avoided whenever
       possible because of the drastic power implications.  */
  QMILOCGEOFENCERESPONSIVENESSENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocGeofenceResponsivenessEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  double latitude;
  /**<   Latitude of the center of the Geofence.*/

  double longitude;
  /**<   Longitude of the center of the Geofence.*/

  uint32_t radius;
  /**<   Radius of the circular Geofence in meters. */
}qmiLocCircularGeofenceArgsStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCGEOFENCEPOSITIONENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_GEOFENCE_POSITION_INSIDE_V02 = 0x01, /**<  Position is inside a Geofence  */
  eQMI_LOC_GEOFENCE_POSITION_OUTSIDE_V02 = 0x02, /**<  Position is outside a Geofence  */
  QMILOCGEOFENCEPOSITIONENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocGeofencePositionEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Used by the control point to add a circular Geofence. */
typedef struct {

  /* Mandatory */
  /*  Transaction ID */
  uint32_t transactionId;
  /**<   Identifies the transaction. The transaction ID
       is returned in the Add Circular Geofence
       indication. */

  /* Mandatory */
  /*  Circular Geofence Arguments */
  qmiLocCircularGeofenceArgsStructT_v02 circularGeofenceArgs;

  /* Mandatory */
  /*  Breach Event Mask */
  qmiLocGeofenceBreachMaskT_v02 breachMask;
  /**<   Specifies the breach events in which the client is interested.

       Valid values: \begin{itemize1}
       \item    0x01 -- GEOFENCE_BREACH_ ENTERING_MASK
       \item    0x02 -- GEOFENCE_BREACH_ LEAVING_MASK
       \vspace{-0.18in} \end{itemize1} */

  /* Mandatory */
  /*  Include Position in Breach Event */
  uint8_t includePosition;
  /**<   Specifies whether the Geofence engine is to include the position
       in a breach event.

       Valid values: \begin{itemize1}
       \item    0x01 (TRUE) -- Position will be reported with the breach event
       \item    0x00 (FALSE) -- Position will not be reported with the breach
                                event
       \vspace{-0.18in} \end{itemize1} */

  /* Optional */
  /*  Responsiveness */
  uint8_t responsiveness_valid;  /**< Must be set to true if responsiveness is being passed */
  qmiLocGeofenceResponsivenessEnumT_v02 responsiveness;
  /**<   Specifies the rate of detection for a Geofence breach.
 This may impact the time lag between the actual breach event and
 when it is reported. This parameter has power implications
 and is to be fine-tuned to optimize power savings.

 Valid values: \n
      - eQMI_LOC_GEOFENCE_RESPONSIVENESS_LOW (0x01) --  The Geofence is monitored for a breach at a
       low rate of 15 minutes. The gap between the actual breach and
       the time it is reported is higher. This
       setting results in lower power usage.
      - eQMI_LOC_GEOFENCE_RESPONSIVENESS_MED (0x02) --  The Geofence is monitored for a breach at a
       medium rate of 2 minutes. This is the default setting.
      - eQMI_LOC_GEOFENCE_RESPONSIVENESS_HIGH (0x03) --  The Geofence is monitored for a breach at a
       high rate of 10 seconds. The gap between the actual breach and
       the time it is reported is low. This results
       in higher power usage.
      - eQMI_LOC_GEOFENCE_RESPONSIVENESS_ULTRA_HIGH (0x04) --  The Geofence is monitored for a breach at a
       very high rate of 1 second. The gap between the actual breach and
       the time it is reported is very low. This results
       in very high power usage. This setting must be avoided whenever
       possible because of the drastic power implications.
 */

  /* Optional */
  /*  Confidence */
  uint8_t confidence_valid;  /**< Must be set to true if confidence is being passed */
  qmiLocGeofenceConfidenceEnumT_v02 confidence;
  /**<   Given a breach event, the confidence determines the probability
 that the breach happened at the Geofence boundary.
 This parameter has power implications and
 is to be fine-tuned to optimize power savings.

 Valid values: \n
      - eQMI_LOC_GEOFENCE_CONFIDENCE_LOW (0x01) --  Geofence engine indicates a breach with
       low confidence; this setting results in lower
       power usage, and it can impact the yield because
       incorrect breach events may be sent
      - eQMI_LOC_GEOFENCE_CONFIDENCE_MED (0x02) --  (Default) Geofence engine indicates a breach with
       medium confidence
      - eQMI_LOC_GEOFENCE_CONFIDENCE_HIGH (0x03) --  Geofence engine indicates a breach with
       high confidence; this setting results in higher
       power usage
 */
}qmiLocAddCircularGeofenceReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Used by the control point to add a circular Geofence. */
typedef struct {

  /* Mandatory */
  /*  Add Circular Geofence Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Add Circular Geofence request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */

  /* Optional */
  /*  Transaction ID */
  uint8_t transactionId_valid;  /**< Must be set to true if transactionId is being passed */
  uint32_t transactionId;
  /**<   Transaction ID that was specified in the Add Circular
       Geofence request. This parameter will always be present
       if the status field is set to SUCCESS. */

  /* Optional */
  /*  Geofence ID */
  uint8_t geofenceId_valid;  /**< Must be set to true if geofenceId is being passed */
  uint32_t geofenceId;
  /**<   Geofence identifier allocated by the engine.
       The client must include this identifier in all transactions
       pertaining to this Geofence. */
}qmiLocAddCircularGeofenceIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Used by the control point to delete a Geofence. */
typedef struct {

  /* Mandatory */
  /*  Geofence ID */
  uint32_t geofenceId;
  /**<   Identifier for the Geofence that is to be deleted. */

  /* Mandatory */
  /*  Transaction ID */
  uint32_t transactionId;
  /**<   Identifies the transaction. The transaction ID
       is returned in the Delete Geofence
       indication. */
}qmiLocDeleteGeofenceReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Used by the control point to delete a Geofence. */
typedef struct {

  /* Mandatory */
  /*  Delete Geofence Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Delete Geofence request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */

  /* Optional */
  /*  Geofence ID */
  uint8_t geofenceId_valid;  /**< Must be set to true if geofenceId is being passed */
  uint32_t geofenceId;
  /**<   Identifier for the Geofence that was deleted. */

  /* Optional */
  /*  Transaction ID */
  uint8_t transactionId_valid;  /**< Must be set to true if transactionId is being passed */
  uint32_t transactionId;
  /**<   Transaction ID that was specified in the Delete
       Geofence request. This parameter will always be present
       if the status field is set to SUCCESS. */
}qmiLocDeleteGeofenceIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCGEOFENCEORIGINENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_GEOFENCE_ORIGIN_NETWORK_V02 = 1, /**<  Geofence was initiated by a network-initiated client  */
  eQMI_LOC_GEOFENCE_ORIGIN_DEVICE_V02 = 2, /**<  Geofence was initiated by the device  */
  QMILOCGEOFENCEORIGINENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocGeofenceOriginEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCGEOFENCESTATEENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_GEOFENCE_STATE_ACTIVE_V02 = 1, /**<  Geofence is being actively monitored  */
  eQMI_LOC_GEOFENCE_STATE_SUSPEND_V02 = 2, /**<  Geofence monitoring is suspended  */
  QMILOCGEOFENCESTATEENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocGeofenceStateEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Used by the control point to query a Geofence. */
typedef struct {

  /* Mandatory */
  /*  Geofence ID */
  uint32_t geofenceId;
  /**<   Identifier for the Geofence that is to be queried. */

  /* Mandatory */
  /*  Transaction ID */
  uint32_t transactionId;
  /**<   Identifies the transaction. The transaction ID
       is returned with the Query Geofence
       indication. */
}qmiLocQueryGeofenceReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Used by the control point to query a Geofence. */
typedef struct {

  /* Mandatory */
  /*  Query Geofence Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Query Geofence request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */

  /* Optional */
  /*  Geofence ID */
  uint8_t geofenceId_valid;  /**< Must be set to true if geofenceId is being passed */
  uint32_t geofenceId;
  /**<   Identifier for the Geofence that was queried. */

  /* Optional */
  /*  Transaction ID */
  uint8_t transactionId_valid;  /**< Must be set to true if transactionId is being passed */
  uint32_t transactionId;
  /**<   Transaction ID that was specified in the Query
       Geofence request. This parameter will always be present
       if the status field is set to SUCCESS. */

  /* Optional */
  /*  Geofence Origin */
  uint8_t geofenceOrigin_valid;  /**< Must be set to true if geofenceOrigin is being passed */
  qmiLocGeofenceOriginEnumT_v02 geofenceOrigin;
  /**<   Originator of the Geofence.

 Valid values: \n
      - eQMI_LOC_GEOFENCE_ORIGIN_NETWORK (1) --  Geofence was initiated by a network-initiated client
      - eQMI_LOC_GEOFENCE_ORIGIN_DEVICE (2) --  Geofence was initiated by the device
 */

  /* Optional */
  /*  Position with Respect to Geofence */
  uint8_t posWrtGeofence_valid;  /**< Must be set to true if posWrtGeofence is being passed */
  qmiLocGeofencePositionEnumT_v02 posWrtGeofence;
  /**<   Indicates if the client is currently inside or outside
 the Geofence.

 Valid values: \n
      - eQMI_LOC_GEOFENCE_POSITION_INSIDE (0x01) --  Position is inside a Geofence
      - eQMI_LOC_GEOFENCE_POSITION_OUTSIDE (0x02) --  Position is outside a Geofence
 */

  /* Optional */
  /*  Circular Geofence Parameters */
  uint8_t circularGeofenceArgs_valid;  /**< Must be set to true if circularGeofenceArgs is being passed */
  qmiLocCircularGeofenceArgsStructT_v02 circularGeofenceArgs;

  /* Optional */
  /*  Geofence State */
  uint8_t geofenceState_valid;  /**< Must be set to true if geofenceState is being passed */
  qmiLocGeofenceStateEnumT_v02 geofenceState;
  /**<   Specifies whether the Geofence is to be actively monitored.

 Valid values: \n
      - eQMI_LOC_GEOFENCE_STATE_ACTIVE (1) --  Geofence is being actively monitored
      - eQMI_LOC_GEOFENCE_STATE_SUSPEND (2) --  Geofence monitoring is suspended
 */
}qmiLocQueryGeofenceIndMsgT_v02;  /* Message */
/**
    @}
  */

typedef uint32_t qmiLocMotionDetectionSourceMaskT_v02;
#define QMI_LOC_MOTION_DETECTION_SOURCE_SENSORS_V02 ((qmiLocMotionDetectionSourceMaskT_v02)0x00000001) /**<  Sensors are used for motion detection  */
#define QMI_LOC_MOTION_DETECTION_SOURCE_WIFI_V02 ((qmiLocMotionDetectionSourceMaskT_v02)0x00000002) /**<  Wi-Fi is used for motion detection  */
#define QMI_LOC_MOTION_DETECTION_SOURCE_WWAN_V02 ((qmiLocMotionDetectionSourceMaskT_v02)0x00000004) /**<  Wireless WAN is used for motion detection  */
/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCGEOFENCEMOTIONSTATESENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_GEOFENCE_MOTION_STATE_STATIONARY_V02 = 0, /**<  Motion state Stationary -- Handset is completely stationary  */
  eQMI_LOC_GEOFENCE_MOTION_STATE_FIDDLE_V02 = 1, /**<  Motion state Fiddle -- Handset is not in motion but is being "fiddled" with  */
  eQMI_LOC_GEOFENCE_MOTION_STATE_WALK_V02 = 2, /**<  Motion state Walk -- User is walking with the handset  */
  eQMI_LOC_GEOFENCE_MOTION_STATE_RUN_V02 = 3, /**<  Motion state Run -- User is running with the handset  */
  eQMI_LOC_GEOFENCE_MOTION_STATE_DRIVE_V02 = 4, /**<  Motion state Drive -- User is driving with the handset    */
  QMILOCGEOFENCEMOTIONSTATESENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocGeofenceMotionStatesEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  qmiLocGeofenceMotionStatesEnumT_v02 motionState;
  /**<   Motion state for which information is being configured. */

  float motionStateSpeed;
  /**<    Motion state speed in milliseconds.

           These are positive floating values.
           The state speed must be configured carefully. Very low speed
           configuration for a state may result in missing Geofence
           breaches in some scenarios.

           Typical motion state speeds: \n
           - Stationary speed -- 0 meters/sec
           - Fiddle speed -- 0 meters/sec \n
           - Walk speed -- 3 meters/sec    \n
           - Run speed -- 8 meters/sec \n
           - Drive speed -- 56 meters/sec
  */
}qmiLocGeofenceMotionStateConfigStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Used by the control point to set the Geofence engine configuration. */
typedef struct {

  /* Mandatory */
  /*  Transaction ID */
  uint32_t transactionId;
  /**<   Identifies the transaction. The transaction ID
       is returned with the Set Geofence Configuration
       indication. */

  /* Optional */
  /*  GNSS Unavailable Indication Timeout */
  uint8_t gnssUnavailableIndicationTimeout_valid;  /**< Must be set to true if gnssUnavailableIndicationTimeout is being passed */
  uint32_t gnssUnavailableIndicationTimeout;
  /**<   In a bad GNSS environment, this is the timeout after which the Geofence
       engine sends out a GNSS Unavailable indication. The GNSS Unavailable
       indication is sent under the following conditions: \begin{itemize1}
       \item If gnssUnavailableIndicationTimeout is less than
             gnssPositionSessionTimeout, the GNSS
             Unavailable timeout indication is sent after
             gnssPositionSessionTimeout expires
       \item If gnssPositionSessionTimeout is less than
             gnssUnavailableIndicationTimeout, the
             GNSS Unavailable timeout indication is sent after
             gnssUnavailableIndicationTimeout expires
        \vspace{-0.18in} \end{itemize1} */

  /* Optional */
  /*  Max Geofences */
  uint8_t maxGeofences_valid;  /**< Must be set to true if maxGeofences is being passed */
  uint32_t maxGeofences;
  /**<   Identifies the maximum number of Geofences that can be supported by
       the Geofence engine. If this number is less than the currently deployed
       Geofences, this command fails.

       If the command succeeds, the engine supports the maximum number of
       Geofences requested, provided there is enough memory to support that
       many Geofences. Increasing this value to a very large number in a
       constrained memory environment might affect other modules negatively.
       This value is determined by phone manufacturers. The default value
       is 200. */

  /* Optional */
  /*  Enable Motion Detection Sources */
  uint8_t enableMotionDetectionSources_valid;  /**< Must be set to true if enableMotionDetectionSources is being passed */
  qmiLocMotionDetectionSourceMaskT_v02 enableMotionDetectionSources;
  /**<   Identifies the sources that can be enabled for motion detection by
 the Geofence engine. The sources of motion detection that are enabled
 by the Geofence engine are dependent on the platform.
 These sources can only be set once at boot time and they are not expected to be changed after that.
 Any attempt to set the value of the motion detection sources at runtime results in an undefined behavior.
 Valid values: \n
      - QMI_LOC_MOTION_DETECTION_SOURCE_SENSORS (0x00000001) --  Sensors are used for motion detection
      - QMI_LOC_MOTION_DETECTION_SOURCE_WIFI (0x00000002) --  Wi-Fi is used for motion detection
      - QMI_LOC_MOTION_DETECTION_SOURCE_WWAN (0x00000004) --  Wireless WAN is used for motion detection  */

  /* Optional */
  /*  Enable Coarse Position Injection Usage */
  uint8_t enableCpiUsage_valid;  /**< Must be set to true if enableCpiUsage is being passed */
  uint8_t enableCpiUsage;
  /**<   Indicates whether external Coarse Position Injection (CPI) is used
       by the Geofence engine.
       \begin{itemize1}
       \item    0x01 (TRUE)  -- CPI is enabled (default)
       \item    0x00 (FALSE) -- CPI is disabled
       \vspace{-0.18in} \end{itemize1}*/

  /* Optional */
  /*  GNSS Position QOS Session Timeout */
  uint8_t gnssPositionSessionTimeout_valid;  /**< Must be set to true if gnssPositionSessionTimeout is being passed */
  uint32_t gnssPositionSessionTimeout;
  /**<   Identifies the session timeout value (in seconds) for requesting a
         position in a bad GNSS environment.

         Valid values: \begin{itemize1}
   \item If the gnssUnavailableIndicationTimeout value is less than
         gnssPositionSessionTimeout, in a bad GNSS environment, the GNSS
         Unavailable timeout indication is sent after
         gnssPositionSessionTimeout expires.
   \item If gnssPositionSessionTimeout is less than gnssUnavailableIndicationTimeout,
         in a bad GNSS environment, the GNSS Unavailable timeout indication
         is sent after gnssUnavailableIndicationTimeout expires. \vspace{-0.18in} \end{itemize1}
    */

  /* Optional */
  /*  GNSS Position Maximum Position Uncertainity Acceptable */
  uint8_t gnssPositionMaxPuncAcceptable_valid;  /**< Must be set to true if gnssPositionMaxPuncAcceptable is being passed */
  uint32_t gnssPositionMaxPuncAcceptable;
  /**<   GNSS maximum position uncertainity in meters acceptable by
         the Geofence engine.

         Valid values: \n
         - All positive values
    */

  /* Optional */
  /*  Medium Responsiveness Value */
  uint8_t mediumResponsivenessValue_valid;  /**< Must be set to true if mediumResponsivenessValue is being passed */
  uint32_t mediumResponsivenessValue;
  /**<   Medium responsiveness value in seconds that the Geofence engine
         uses for all medium responsiveness Geofences in the Geofence engine.

         Valid values: \begin{itemize1}
         \item Positive values (in seconds)
         \item If the value is configured for less than 30 sec, the value is
               set at 30 sec
         \item If the value is configured for more than 600 sec, the value is
               set at 600 sec
         \item Default -- The Geofence engine uses 120 sec as the medium
                          responsiveness value
         \end{itemize1}

         If the medium responsiveness value is changed, the responsiveness
         of the existing medium responsiveness Geofence does not change until the next
         position fix, which is based on the previous medium responsiveness
         setting.
    */

  /* Optional */
  /*  Challenging GNSS Environment Minimmum CPI Wait Interval */
  uint8_t chalGnssEnvMinCpiWaitInterval_valid;  /**< Must be set to true if chalGnssEnvMinCpiWaitInterval is being passed */
  uint32_t chalGnssEnvMinCpiWaitInterval;
  /**<   Number of seconds that the Geofence engine is to wait between
         CPI requests in challenging a GNSS environment.

         Valid values: \n
         - Positive values (in seconds)
     */

  /* Optional */
  /*  Geofence Motion State Information */
  uint8_t motionStateInfo_valid;  /**< Must be set to true if motionStateInfo is being passed */
  uint32_t motionStateInfo_len;  /**< Must be set to # of elements in motionStateInfo */
  qmiLocGeofenceMotionStateConfigStructT_v02 motionStateInfo[QMI_LOC_GEOFENCE_MAX_MOTION_STATES_V02];
  /**<   \vspace{4pt} \n  Motion state informatino (e.g., motion state speed) that the
         Geofence engine is to use.
   */
}qmiLocSetGeofenceEngineConfigReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Used by the control point to set the Geofence engine configuration. */
typedef struct {

  /* Mandatory */
  /*  Set Geofence Engine Configuration Status. */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Set Geofence Engine Configuration request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure  */

  /* Optional */
  /*  Transaction ID */
  uint8_t transactionId_valid;  /**< Must be set to true if transactionId is being passed */
  uint32_t transactionId;
  /**<   Transaction ID that was specified in the Set Geofence Configuration
       request. This parameter is always present if the status
       field is set to SUCCESS. */
}qmiLocSetGeofenceEngineConfigIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Used by the control point to get the Geofence engine configuration. */
typedef struct {

  /* Mandatory */
  /*  Transaction ID */
  uint32_t transactionId;
  /**<   Identifies the transaction. The transaction ID
       is returned with the Get Geofence Engine Configuration
       indication. */
}qmiLocGetGeofenceEngineConfigReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Used by the control point to get the Geofence engine configuration. */
typedef struct {

  /* Mandatory */
  /*  Get Geofence Engine Configuration Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Get Geofence Engine Configuration request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure  */

  /* Optional */
  /*  Transaction ID */
  uint8_t transactionId_valid;  /**< Must be set to true if transactionId is being passed */
  uint32_t transactionId;
  /**<   Transaction ID that was specified in the Get Geofence Engine Configuration
       request. This parameter is always present
       if the status field is set to SUCCESS. */

  /* Optional */
  /*  GPS Unavailable Indication Timeout */
  uint8_t gnssUnavailableIndicationTimeout_valid;  /**< Must be set to true if gnssUnavailableIndicationTimeout is being passed */
  uint32_t gnssUnavailableIndicationTimeout;
  /**<   In a bad GNSS environment, the timeout after which the Geofence engine
       sends out a GNSS unavailable indication. */

  /* Optional */
  /*  Max Geofences */
  uint8_t maxGeofences_valid;  /**< Must be set to true if maxGeofences is being passed */
  uint32_t maxGeofences;
  /**<   Identifies the maximum number of Geofences that are currently supported
       in the Geofence engine.  */

  /* Optional */
  /*  Enabled Motion Detection Sources */
  uint8_t enabledMotionDetectionSources_valid;  /**< Must be set to true if enabledMotionDetectionSources is being passed */
  qmiLocMotionDetectionSourceMaskT_v02 enabledMotionDetectionSources;
  /**<   Identifies the sources that are currently enabled for motion detection
 by the Geofence engine.

 Valid values: \n
      - QMI_LOC_MOTION_DETECTION_SOURCE_SENSORS (0x00000001) --  Sensors are used for motion detection
      - QMI_LOC_MOTION_DETECTION_SOURCE_WIFI (0x00000002) --  Wi-Fi is used for motion detection
      - QMI_LOC_MOTION_DETECTION_SOURCE_WWAN (0x00000004) --  Wireless WAN is used for motion detection  */

  /* Optional */
  /*  Enabled for CPI Position Injection Usage */
  uint8_t enabledCpiUsage_valid;  /**< Must be set to true if enabledCpiUsage is being passed */
  uint8_t enabledCpiUsage;
  /**<   Indicates whether CPI usage is enabled.
       \begin{itemize1}
       \item    0x01 (TRUE)  -- CPI usage is enabled
       \item    0x00 (FALSE) -- CPI usage is disabled
       \vspace{-0.18in} \end{itemize1}*/
}qmiLocGetGeofenceEngineConfigIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Used by the control point to edit a Geofence. */
typedef struct {

  /* Mandatory */
  /*  Geofence ID */
  uint32_t geofenceId;
  /**<   Identifier for the Geofence to be edited. */

  /* Mandatory */
  /*  Transaction ID */
  uint32_t transactionId;
  /**<   Transaction ID that was specified in the Edit Geofence
       request. This parameter will always be present if the
       status field is set to SUCCESS.
 */

  /* Optional */
  /*  Geofence State */
  uint8_t geofenceState_valid;  /**< Must be set to true if geofenceState is being passed */
  qmiLocGeofenceStateEnumT_v02 geofenceState;
  /**<   Specifies whether the Geofence is to be actively monitored.

 Valid values: \n
      - eQMI_LOC_GEOFENCE_STATE_ACTIVE (1) --  Geofence is being actively monitored
      - eQMI_LOC_GEOFENCE_STATE_SUSPEND (2) --  Geofence monitoring is suspended
 */

  /* Optional */
  /*  Breach Event Mask */
  uint8_t breachMask_valid;  /**< Must be set to true if breachMask is being passed */
  qmiLocGeofenceBreachMaskT_v02 breachMask;
  /**<   Specifies the breach events in which the client is interested.

       Valid values: \begin{itemize1}
       \item    0x01 -- GEOFENCE_BREACH_ ENTERING_MASK
       \item    0x02 -- GEOFENCE_BREACH_ LEAVING_MASK
       \vspace{-0.18in} \end{itemize1} */

  /* Optional */
  /*  Responsiveness */
  uint8_t responsiveness_valid;  /**< Must be set to true if responsiveness is being passed */
  qmiLocGeofenceResponsivenessEnumT_v02 responsiveness;
  /**<   Specifies the rate of detection for a Geofence breach.
 This may impact the time lag between the actual breach event and
 when it is reported. This parameter has power implications
 and is to be fine-tuned to optimize power savings.

 Valid values: \n
      - eQMI_LOC_GEOFENCE_RESPONSIVENESS_LOW (0x01) --  The Geofence is monitored for a breach at a
       low rate of 15 minutes. The gap between the actual breach and
       the time it is reported is higher. This
       setting results in lower power usage.
      - eQMI_LOC_GEOFENCE_RESPONSIVENESS_MED (0x02) --  The Geofence is monitored for a breach at a
       medium rate of 2 minutes. This is the default setting.
      - eQMI_LOC_GEOFENCE_RESPONSIVENESS_HIGH (0x03) --  The Geofence is monitored for a breach at a
       high rate of 10 seconds. The gap between the actual breach and
       the time it is reported is low. This results
       in higher power usage.
      - eQMI_LOC_GEOFENCE_RESPONSIVENESS_ULTRA_HIGH (0x04) --  The Geofence is monitored for a breach at a
       very high rate of 1 second. The gap between the actual breach and
       the time it is reported is very low. This results
       in very high power usage. This setting must be avoided whenever
       possible because of the drastic power implications.
 */
}qmiLocEditGeofenceReqMsgT_v02;  /* Message */
/**
    @}
  */

typedef uint32_t qmiLocGeofenceConfigParamMaskT_v02;
#define QMI_LOC_GEOFENCE_PARAM_MASK_GEOFENCE_STATE_V02 ((qmiLocGeofenceConfigParamMaskT_v02)0x00000001) /**<  Mask for the Geofence state parameter.  */
#define QMI_LOC_GEOFENCE_PARAM_MASK_BREACH_MASK_V02 ((qmiLocGeofenceConfigParamMaskT_v02)0x00000002) /**<  Mask for Geofence breach mask parameter.  */
/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Used by the control point to edit a Geofence. */
typedef struct {

  /* Mandatory */
  /*  Edit Geofence Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Edit Geofence request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure  */

  /* Optional */
  /*  Geofence ID */
  uint8_t geofenceId_valid;  /**< Must be set to true if geofenceId is being passed */
  uint32_t geofenceId;
  /**<   Identifier for the Geofence that was edited. */

  /* Optional */
  /*  Transaction ID */
  uint8_t transactionId_valid;  /**< Must be set to true if transactionId is being passed */
  uint32_t transactionId;
  /**<   Identifies the transaction. The transaction ID
       is specified in the Edit Geofence request. */

  /* Optional */
  /*  Failed Parameters */
  uint8_t failedParams_valid;  /**< Must be set to true if failedParams is being passed */
  qmiLocGeofenceConfigParamMaskT_v02 failedParams;
  /**<   Specified only when the status is not set to SUCCESS. If
       the mask corresponding to a field is set, it indicates that
       the Geofence parameter could not be edited.

       Valid values: \begin{itemize1}
       \item    0x00000001 -- GEOFENCE_PARAM_ MASK_GEOFENCE_STATE
       \item    0x00000002 -- GEOFENCE_PARAM_ MASK_BREACH_MASK
       \vspace{-0.18in} \end{itemize1} */
}qmiLocEditGeofenceIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Used by the control point to get the best available
                    position estimate from the location engine. */
typedef struct {

  /* Mandatory */
  /*  Transaction ID */
  uint32_t transactionId;
  /**<   Identifies the transaction. The transaction ID
       is returned in the Get Best Available Position indication. */
}qmiLocGetBestAvailablePositionReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Used by the control point to get the best available
                    position estimate from the location engine. */
typedef struct {

  /* Mandatory */
  /*  Get Best Available Position Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Get Best Available Position request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure  */

  /* Optional */
  /*  Transaction ID */
  uint8_t transactionId_valid;  /**< Must be set to true if transactionId is being passed */
  uint32_t transactionId;
  /**<   Transaction ID that was specified in the Get Best
       Available Position request. This parameter will
       always be present if the status field is set to
       SUCCESS. */

  /* Optional */
  /*  Latitude */
  uint8_t latitude_valid;  /**< Must be set to true if latitude is being passed */
  double latitude;
  /**<   Latitude (specified in WGS84 datum).
       \begin{itemize1}
       \item    Type: Floating point
       \item    Units: Degrees
       \item     Range: -90.0 to 90.0      \begin{itemize1}
         \item    Positive values indicate northern latitude
         \item    Negative values indicate southern latitude
       \vspace{-0.18in} \end{itemize1} \end{itemize1} */

  /* Optional */
  /*   Longitude */
  uint8_t longitude_valid;  /**< Must be set to true if longitude is being passed */
  double longitude;
  /**<   Longitude (specified in WGS84 datum).
       \begin{itemize1}
       \item    Type: Floating point
       \item    Units: Degrees
       \item    Range: -180.0 to 180.0     \begin{itemize1}
         \item    Positive values indicate eastern longitude
         \item    Negative values indicate western longitude
       \vspace{-0.18in} \end{itemize1} \end{itemize1} */

  /* Optional */
  /*   Circular Horizontal Position Uncertainty */
  uint8_t horUncCircular_valid;  /**< Must be set to true if horUncCircular is being passed */
  float horUncCircular;
  /**<   Horizontal position uncertainty (circular).\n
       - Units: Meters */

  /* Optional */
  /*  Altitude With Respect to Ellipsoid */
  uint8_t altitudeWrtEllipsoid_valid;  /**< Must be set to true if altitudeWrtEllipsoid is being passed */
  float altitudeWrtEllipsoid;
  /**<   Altitude with respect to the WGS84 ellipsoid.\n
       - Units: Meters \n
       - Range: -500 to 15883 */

  /* Optional */
  /*  Vertical Uncertainty */
  uint8_t vertUnc_valid;  /**< Must be set to true if vertUnc is being passed */
  float vertUnc;
  /**<   Vertical uncertainty.\n
       - Units: Meters */

  /* Optional */
  /*  UTC Timestamp */
  uint8_t timestampUtc_valid;  /**< Must be set to true if timestampUtc is being passed */
  uint64_t timestampUtc;
  /**<   UTC timestamp.
       \begin{itemize1}
       \item Units: Milliseconds since Jan. 1, 1970
       \vspace{-0.18in} \end{itemize1} */

  /* Optional */
  /*  Time Uncertainty */
  uint8_t timeUnc_valid;  /**< Must be set to true if timeUnc is being passed */
  float timeUnc;
  /**<   Time uncertainty. \n
       - Units: Milliseconds */

  /* Optional */
  /*  Horizontal Elliptical Uncertainty Semi-Minor Axis */
  uint8_t horUncEllipseSemiMinor_valid;  /**< Must be set to true if horUncEllipseSemiMinor is being passed */
  float horUncEllipseSemiMinor;
  /**<   Semi-minor axis of horizontal elliptical uncertainty. \n
       - Units: Meters */

  /* Optional */
  /*  Horizontal Elliptical Uncertainty Semi-Major Axis */
  uint8_t horUncEllipseSemiMajor_valid;  /**< Must be set to true if horUncEllipseSemiMajor is being passed */
  float horUncEllipseSemiMajor;
  /**<   Semi-major axis of horizontal elliptical uncertainty. \n
       - Units: Meters */

  /* Optional */
  /*  Horizontal Elliptical Uncertainty Azimuth */
  uint8_t horUncEllipseOrientAzimuth_valid;  /**< Must be set to true if horUncEllipseOrientAzimuth is being passed */
  float horUncEllipseOrientAzimuth;
  /**<   Elliptical horizontal uncertainty azimuth of orientation. \n
       - Units: Decimal degrees \n
       - Range: 0 to 180 */

  /* Optional */
  /*  Horizontal Circular Confidence */
  uint8_t horCircularConfidence_valid;  /**< Must be set to true if horCircularConfidence is being passed */
  uint8_t horCircularConfidence;
  /**<   Horizontal circular uncertainty confidence. \n
       - Units: Percent \n
       - Range: 0 to 99 */

  /* Optional */
  /*  Horizontal Elliptical Confidence */
  uint8_t horEllipticalConfidence_valid;  /**< Must be set to true if horEllipticalConfidence is being passed */
  uint8_t horEllipticalConfidence;
  /**<   Horizontal elliptical uncertainty confidence. \n
       - Units: Percent \n
       - Range: 0 to 99 */

  /* Optional */
  /*  Horizontal Reliability */
  uint8_t horReliability_valid;  /**< Must be set to true if horReliability is being passed */
  qmiLocReliabilityEnumT_v02 horReliability;
  /**<   Specifies the reliability of the horizontal position.

 Valid values: \n
      - eQMI_LOC_RELIABILITY_NOT_SET (0) --  Location reliability is not set
      - eQMI_LOC_RELIABILITY_VERY_LOW (1) --  Location reliability is very low; use it at your own risk
      - eQMI_LOC_RELIABILITY_LOW (2) --  Location reliability is low; little or no cross-checking is possible
      - eQMI_LOC_RELIABILITY_MEDIUM (3) --  Location reliability is medium; limited cross-check passed
      - eQMI_LOC_RELIABILITY_HIGH (4) --  Location reliability is high; strong cross-check passed
 */

  /* Optional */
  /*  Horizontal Speed */
  uint8_t horSpeed_valid;  /**< Must be set to true if horSpeed is being passed */
  float horSpeed;
  /**<   Horizontal speed. \n
       - Units: Meters/second */

  /* Optional */
  /*  Horizontal Speed Uncertainty */
  uint8_t horSpeedUnc_valid;  /**< Must be set to true if horSpeedUnc is being passed */
  float horSpeedUnc;
  /**<   Horizontal speed uncertainty. \n
       - Units: Meters/second */

  /* Optional */
  /*  Altitude With Respect to Sea Level */
  uint8_t altitudeWrtMeanSeaLevel_valid;  /**< Must be set to true if altitudeWrtMeanSeaLevel is being passed */
  float altitudeWrtMeanSeaLevel;
  /**<   Altitude with respect to mean sea level. \n
       - Units: Meters */

  /* Optional */
  /*  Vertical Confidence */
  uint8_t vertConfidence_valid;  /**< Must be set to true if vertConfidence is being passed */
  uint8_t vertConfidence;
  /**<   Vertical uncertainty confidence. \n
       - Units: Percent \n
       - Range: 0 to 99 */

  /* Optional */
  /*  Vertical Reliability */
  uint8_t vertReliability_valid;  /**< Must be set to true if vertReliability is being passed */
  qmiLocReliabilityEnumT_v02 vertReliability;
  /**<   Specifies the reliability of the vertical position.

 Valid values: \n
      - eQMI_LOC_RELIABILITY_NOT_SET (0) --  Location reliability is not set
      - eQMI_LOC_RELIABILITY_VERY_LOW (1) --  Location reliability is very low; use it at your own risk
      - eQMI_LOC_RELIABILITY_LOW (2) --  Location reliability is low; little or no cross-checking is possible
      - eQMI_LOC_RELIABILITY_MEDIUM (3) --  Location reliability is medium; limited cross-check passed
      - eQMI_LOC_RELIABILITY_HIGH (4) --  Location reliability is high; strong cross-check passed
 */

  /* Optional */
  /*  Vertical Speed */
  uint8_t vertSpeed_valid;  /**< Must be set to true if vertSpeed is being passed */
  float vertSpeed;
  /**<   Vertical speed. \n
         - Units: Meters/second */

  /* Optional */
  /*  Vertical Speed Uncertainty */
  uint8_t vertSpeedUnc_valid;  /**< Must be set to true if vertSpeedUnc is being passed */
  float vertSpeedUnc;
  /**<   Vertical speed uncertainty. \n
       - Units: Meters/second */

  /* Optional */
  /*  Heading */
  uint8_t heading_valid;  /**< Must be set to true if heading is being passed */
  float heading;
  /**<   Heading. \n
         - Units: Degrees \n
         - Range: 0 to 359.999  */

  /* Optional */
  /*  Heading Uncertainty */
  uint8_t headingUnc_valid;  /**< Must be set to true if headingUnc is being passed */
  float headingUnc;
  /**<   Heading uncertainty. \n
       - Type: Floating point \n
       - Range: 0 to 359.999 */

  /* Optional */
  /*  Magnetic Deviation */
  uint8_t magneticDeviation_valid;  /**< Must be set to true if magneticDeviation is being passed */
  float magneticDeviation;
  /**<   Difference between the bearing to true north and the bearing shown
      on a magnetic compass. The deviation is positive when the magnetic
      north is east of true north. */

  /* Optional */
  /*  Technology Used Mask */
  uint8_t technologyMask_valid;  /**< Must be set to true if technologyMask is being passed */
  qmiLocPosTechMaskT_v02 technologyMask;
  /**<   Technology used in computing this fix.
 Valid bitmasks: \n
      - QMI_LOC_POS_TECH_MASK_SATELLITE (0x00000001) --  Satellites were used to generate the fix
      - QMI_LOC_POS_TECH_MASK_CELLID (0x00000002) --  Cell towers were used to generate the fix
      - QMI_LOC_POS_TECH_MASK_WIFI (0x00000004) --  Wi-Fi access points were used to generate the fix
      - QMI_LOC_POS_TECH_MASK_SENSORS (0x00000008) --  Sensors were used to generate the fix
      - QMI_LOC_POS_TECH_MASK_REFERENCE_LOCATION (0x00000010) --  Reference Location was used to generate the fix
      - QMI_LOC_POS_TECH_MASK_INJECTED_COARSE_POSITION (0x00000020) --  Coarse position injected into the location engine was used to
        generate the fix
      - QMI_LOC_POS_TECH_MASK_AFLT (0x00000040) --  AFLT was used to generate the fix
      - QMI_LOC_POS_TECH_MASK_HYBRID (0x00000080) --  GNSS and network-provided measurements were used to
        generate the fix
 */

  /* Optional */
  /*  Dilution of Precision */
  uint8_t DOP_valid;  /**< Must be set to true if DOP is being passed */
  qmiLocDOPStructT_v02 DOP;

  /* Optional */
  /*  GPS Time */
  uint8_t gpsTime_valid;  /**< Must be set to true if gpsTime is being passed */
  qmiLocGPSTimeStructT_v02 gpsTime;

  /* Optional */
  /*  Time Source */
  uint8_t timeSrc_valid;  /**< Must be set to true if timeSrc is being passed */
  qmiLocTimeSourceEnumT_v02 timeSrc;
  /**<   Time source.
 Valid values: \n
      - eQMI_LOC_TIME_SRC_INVALID (0) --  Invalid time.
      - eQMI_LOC_TIME_SRC_NETWORK_TIME_TRANSFER (1) --  Time is set by the 1X system
      - eQMI_LOC_TIME_SRC_NETWORK_TIME_TAGGING (2) --  Time is set by WCDMA/GSM time tagging (i.e.,
       associating network time with GPS time)
      - eQMI_LOC_TIME_SRC_EXTERNAL_INPUT (3) --  Time is set by an external injection
      - eQMI_LOC_TIME_SRC_TOW_DECODE (4) --  Time is set after decoding over-the-air GPS navigation data
       from one GPS satellite
      - eQMI_LOC_TIME_SRC_TOW_CONFIRMED (5) --  Time is set after decoding over-the-air GPS navigation data
       from multiple satellites
      - eQMI_LOC_TIME_SRC_TOW_AND_WEEK_CONFIRMED (6) --  Both time of the week and the GPS week number are known
      - eQMI_LOC_TIME_SRC_NAV_SOLUTION (7) --  Time is set by the position engine after the fix is obtained
      - eQMI_LOC_TIME_SRC_SOLVE_FOR_TIME (8) --  Time is set by the position engine after performing SFT;
       this is done when the clock time uncertainty is large
      - eQMI_LOC_TIME_SRC_GLO_TOW_DECODE (9) --  Time is set after decoding GLO satellites
      - eQMI_LOC_TIME_SRC_TIME_TRANSFORM (10) --  Time is set after transforming the GPS to GLO time
      - eQMI_LOC_TIME_SRC_WCDMA_SLEEP_TIME_TAGGING (11) --  Time is set by the sleep time tag provided by the WCDMA network
      - eQMI_LOC_TIME_SRC_GSM_SLEEP_TIME_TAGGING (12) --  Time is set by the sleep time tag provided by the GSM network
      - eQMI_LOC_TIME_SRC_UNKNOWN (13) --  Source of the time is unknown
      - eQMI_LOC_TIME_SRC_SYSTEM_TIMETICK (14) --  Time is derived from the system clock (better known as the slow clock);
       GNSS time is maintained irrespective of the GNSS receiver state
      - eQMI_LOC_TIME_SRC_QZSS_TOW_DECODE (15) --  Time is set after decoding QZSS satellites
      - eQMI_LOC_TIME_SRC_BDS_TOW_DECODE (16) --  Time is set after decoding BDS satellites
 */

  /* Optional */
  /*  Sensor Data Usage */
  uint8_t sensorDataUsage_valid;  /**< Must be set to true if sensorDataUsage is being passed */
  qmiLocSensorUsageIndicatorStructT_v02 sensorDataUsage;

  /* Optional */
  /*  SVs Used to Calculate the Fix */
  uint8_t gnssSvUsedList_valid;  /**< Must be set to true if gnssSvUsedList is being passed */
  uint32_t gnssSvUsedList_len;  /**< Must be set to # of elements in gnssSvUsedList */
  uint16_t gnssSvUsedList[QMI_LOC_MAX_SV_USED_LIST_LENGTH_V02];
  /**<   Each entry in the list contains the SV ID of a satellite
       used for calculating this position report. The following
       information is associated with each SV ID: \n
       Range: \n
       - For GPS:     1 to 32 \n
       - For SBAS:    33 to 64 \n
       - For GLONASS: 65 to 96 \n
       - For QZSS:    193 to 197 \n
       - For BDS:     201 to 237
    */
}qmiLocGetBestAvailablePositionIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCMOTIONSTATEENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_MOTION_STATE_UNKNOWN_V02 = 0, /**<  Device state is not known  */
  eQMI_LOC_MOTION_STATE_STATIONARY_V02 = 1, /**<  Device state is Stationary  */
  eQMI_LOC_MOTION_STATE_IN_MOTION_V02 = 2, /**<  Device state is In Motion  */
  QMILOCMOTIONSTATEENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocMotionStateEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCMOTIONMODEENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_MOTION_MODE_UNKNOWN_V02 = 0, /**<  Device movement is not known  */
  eQMI_LOC_MOTION_MODE_STATIONARY_V02 = 1, /**<  Device is not moving  */
  eQMI_LOC_MOTION_MODE_PEDESTRIAN_UNKNOWN_V02 = 200, /**<  Device movement is in Pedestrian mode; nothing else is known about the movement  */
  eQMI_LOC_MOTION_MODE_PEDESTRIAN_WALKING_V02 = 201, /**<  Device movement is in pedestrian Walking mode  */
  eQMI_LOC_MOTION_MODE_PEDESTRIAN_RUNNING_V02 = 202, /**<  Device movement is in pedestrian Running mode  */
  eQMI_LOC_MOTION_MODE_VEHICLE_UNKNOWN_V02 = 300, /**<  Device movement is in Vehicular mode; nothing else is known about the movement  */
  QMILOCMOTIONMODEENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocMotionModeEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  qmiLocMotionStateEnumT_v02 motion_state;
  /**<   Current motion state of the user.

 Valid values: \n
      - eQMI_LOC_MOTION_STATE_UNKNOWN (0) --  Device state is not known
      - eQMI_LOC_MOTION_STATE_STATIONARY (1) --  Device state is Stationary
      - eQMI_LOC_MOTION_STATE_IN_MOTION (2) --  Device state is In Motion
 */

  qmiLocMotionModeEnumT_v02 motion_mode;
  /**<   Modes of user motion.

 Valid values: \n
      - eQMI_LOC_MOTION_MODE_UNKNOWN (0) --  Device movement is not known
      - eQMI_LOC_MOTION_MODE_STATIONARY (1) --  Device is not moving
      - eQMI_LOC_MOTION_MODE_PEDESTRIAN_UNKNOWN (200) --  Device movement is in Pedestrian mode; nothing else is known about the movement
      - eQMI_LOC_MOTION_MODE_PEDESTRIAN_WALKING (201) --  Device movement is in pedestrian Walking mode
      - eQMI_LOC_MOTION_MODE_PEDESTRIAN_RUNNING (202) --  Device movement is in pedestrian Running mode
      - eQMI_LOC_MOTION_MODE_VEHICLE_UNKNOWN (300) --  Device movement is in Vehicular mode; nothing else is known about the movement
 */

  float probability_of_state;
  /**<   Probability that the device is actually undergoing the motion state
       specified by the combination of the values of motion_state, motion_mode,
       and motion_sub_mode. \vspace{0.1in}

       This value is a floating point number in the range of 0 to 100, in
       units of percent probability. Any value greater than 99.9999 is
       applied as 99.9999. \vspace{0.1in}

       It is recommended that if a particular combination of motion_state and
       motion_mode cannot be determined with more than 50 percent confidence,
       that a more general statement of user motion be made.
       For example, if the mode of In-Motion + Pedestrian-Running can only be
       determined with 50 percent probability, and the simpler statement of In-Motion
       can be determined with 90 percent probability, it is recommended that this field
       be used to simply state In-Motion with 90 percent probability. \vspace{0.1in}

       If the motion_state is not known, the value in this field is not used.
  */

  uint16_t age;
  /**<   Age of the motion data in milliseconds at the time of injection.
  */

  uint16_t timeout;
  /**<   If the age of the motion data input exceeds the timeout value, the data
       will no longer be used. The timeout value is in units of milliseconds.
       Values in the range of 0 to 10000 are accepted. If 65535 is provided,
       the motion data input is applied until the next input is
       received. \n

       If the determination of motion data is an instantaneous observation
       and no notice is guaranteed to be given via the QMI on a change in the
       state of the motion data, it is recommended that this field be set to 0. \vspace{0.1in}

       If the determination of motion data is continuously monitored
       external to the QMI and an update is always applied to the QMI upon any
       change in state, a value of 65535 is used for this field.
       Note that in this case, if a certain mode is set and is not later
       unset (e.g., by sending in the request message with a user motion
       state of Unknown), the value is applied indefinitely.
  */
}qmiLocMotionDataStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Injects motion data for MSM GPS service use. */
typedef struct {

  /* Mandatory */
  /*  Motion Data */
  qmiLocMotionDataStructT_v02 motion_data;
}qmiLocInjectMotionDataReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Injects motion data for MSM GPS service use. */
typedef struct {

  /* Mandatory */
  /*  Inject Motion Data Request Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Inject Motion Data request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */
}qmiLocInjectMotionDataIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Used by the control point to retrieve the list of network
                    initiated Geofence IDs. */
typedef struct {

  /* Mandatory */
  /*  Transaction ID */
  uint32_t transactionId;
  /**<   Identifies the transaction. The same transaction ID
       will be returned in the Get NI Geofence ID List indication. */
}qmiLocGetNiGeofenceIdListReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Used by the control point to retrieve the list of network
                    initiated Geofence IDs. */
typedef struct {

  /* Mandatory */
  /*  Get NI Geofence ID List Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Get NI Geofence ID List request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure  */

  /* Optional */
  /*  Transaction ID */
  uint8_t transactionId_valid;  /**< Must be set to true if transactionId is being passed */
  uint32_t transactionId;
  /**<   Transaction ID that was specified in the Get NI
       Geofence ID List request. */

  /* Optional */
  /*  NI Geofence ID List */
  uint8_t niGeofenceIdList_valid;  /**< Must be set to true if niGeofenceIdList is being passed */
  uint32_t niGeofenceIdList_len;  /**< Must be set to # of elements in niGeofenceIdList */
  uint32_t niGeofenceIdList[QMI_LOC_MAX_NI_GEOFENCE_ID_LIST_LENGTH_V02];
  /**<   List containing the NI Geofence IDs.
       - Type: Array of unsigned 32-bit integers \n
       - Maximum NI Geofence ID List length: 16 */
}qmiLocGetNiGeofenceIdListIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  uint32_t MCC;
  /**<   GSM mobile country code. Refer to ITU-T E.212 \hyperref[S6]{[S6]}. */

  uint32_t MNC;
  /**<   GSM mobile network code. Refer to \hyperref[S6]{[S6]}. */

  uint32_t LAC;
  /**<   GSM location area code. Refer to \hyperref[S6]{[S6]}. */

  uint32_t CID;
  /**<   GSM cell identification. Refer to \hyperref[S6]{[S6]}. */
}qmiLocGSMCellIdStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Injects GSM cell information into the location
                    engine. */
typedef struct {

  /* Mandatory */
  /*  GSM Cell ID */
  qmiLocGSMCellIdStructT_v02 gsmCellId;
  /**<   \vspace{0.06in} \n Identifies the GSM cell on which the device is currently camped. */

  /* Mandatory */
  /*  Roaming Status */
  uint8_t roamingStatus;
  /**<   Indicates whether the device is roaming.
       \begin{itemize1}
       \item    0x01 (TRUE)  -- Device is roaming
       \item    0x00 (FALSE) -- Device is not roaming
       \vspace{-0.18in} \end{itemize1}*/

  /* Optional */
  /*  Timing Advance */
  uint8_t timingAdvance_valid;  /**< Must be set to true if timingAdvance is being passed */
  uint32_t timingAdvance;
  /**<   Round trip delay between the MS and the BS, in units of 3.69 microseconds.
       Refer to 3GPP TS 05.10 and TS 45.010. */
}qmiLocInjectGSMCellInfoReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Injects GSM cell information into the location
                    engine. */
typedef struct {

  /* Mandatory */
  /*  Inject GSM Cell Info Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Inject GSM Cell Info request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure  */
}qmiLocInjectGSMCellInfoIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCROAMINGSTATUSENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_PHONE_NOT_ROAMING_V02 = 1, /**<  Modem is camped on a home network  */
  eQMI_LOC_PHONE_ROAMING_V02 = 2, /**<  Modem is camped on a roaming network  */
  QMILOCROAMINGSTATUSENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocRoamingStatusEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  uint32_t mcc;
  /**<   WCDMA mobile country code. Refer to ITU-T E.212 \hyperref[S6]{[S6]}. */

  uint32_t mnc;
  /**<   WCDMA mobile network code. Refer to \hyperref[S6]{[S6]}. */

  uint32_t cid;
  /**<   WCDMA cell identity. Refer to \hyperref[S6]{[S6]}. */
}qmiLocWCDMACellIdStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Injects WCDMA cell information into the location
                    engine. */
typedef struct {

  /* Mandatory */
  /*  WCDMA Cell ID */
  qmiLocWCDMACellIdStructT_v02 wcdmaCellId;
  /**<   \n Identifies the WCDMA cell on which the device is currently camped. */

  /* Mandatory */
  /*  Roaming Status */
  qmiLocRoamingStatusEnumT_v02 roamingStatus;
  /**<   Indicates whether the device is roaming.

 Valid values: \n
      - eQMI_LOC_PHONE_NOT_ROAMING (1) --  Modem is camped on a home network
      - eQMI_LOC_PHONE_ROAMING (2) --  Modem is camped on a roaming network
 */

  /* Optional */
  /*  Cell Frequency */
  uint8_t freq_valid;  /**< Must be set to true if freq is being passed */
  uint32_t freq;
  /**<   Frequency information of the serving cell. \n
       Valid range: 0 to 16383 \n
       Refer to TS 25.331 \hyperref[S7]{[S7]}. */

  /* Optional */
  /*  Primary Scrambling Code */
  uint8_t psc_valid;  /**< Must be set to true if psc is being passed */
  uint32_t psc;
  /**<   Primary scrambling code of the serving cell. \n
       Valid range: 0 to 511 \n
       Refer to \hyperref[S7]{[S7]}. */
}qmiLocInjectWCDMACellInfoReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Injects WCDMA cell information into the location
                    engine. */
typedef struct {

  /* Mandatory */
  /*  Inject WCDMA Cell Info Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Inject WCDMA Cell Info request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure  */
}qmiLocInjectWCDMACellInfoIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  uint32_t mcc;
  /**<   TDSCDMA mobile country code. Refer to ITU-T E.212 \hyperref[S6]{[S6]}. */

  uint32_t mnc;
  /**<   TDSCDMA mobile network code. Refer to \hyperref[S6]{[S6]}. */

  uint32_t cid;
  /**<   TDSCDMA cell identity. Refer to TS 25.331 \hyperref[S7]{[S7]}. */

  uint32_t lac;
  /**<   TDSCDMA location area code. Refer to \hyperref[S6]{[S6]}. */
}qmiLocTDSCDMACellIdStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Injects TDSCDMA cell information into the location
                    engine. */
typedef struct {

  /* Mandatory */
  /*  TDSCDMA Cell ID */
  qmiLocTDSCDMACellIdStructT_v02 tdscdmaCellId;
  /**<   \n Identifies the TDSCDMA cell on which the device is currently camped. */

  /* Mandatory */
  /*  Roaming Status */
  qmiLocRoamingStatusEnumT_v02 roamingStatus;
  /**<   Indicates whether the device is roaming.

 Valid values: \n
      - eQMI_LOC_PHONE_NOT_ROAMING (1) --  Modem is camped on a home network
      - eQMI_LOC_PHONE_ROAMING (2) --  Modem is camped on a roaming network
 */

  /* Optional */
  /*  Cell Frequency */
  uint8_t freq_valid;  /**< Must be set to true if freq is being passed */
  uint32_t freq;
  /**<   Frequency information of the serving cell. \n
       Valid range: 0 to 16383 \n
       Refer to \hyperref[S7]{[S7]}. */
}qmiLocInjectTDSCDMACellInfoReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Injects TDSCDMA cell information into the location
                    engine. */
typedef struct {

  /* Mandatory */
  /*  Inject TDSCDMA Cell Info Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Inject TDSCDMA Cell Info request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure  */
}qmiLocInjectTDSCDMACellInfoIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Injects the phone's subscriber ID into the location engine. */
typedef struct {

  /* Optional */
  /*  Preferred IMSI */
  uint8_t preferredIMSI_valid;  /**< Must be set to true if preferredIMSI is being passed */
  uint64_t preferredIMSI;
  /**<   IMSI number of the preferred RAT. Refer to \hyperref[S6]{[S6]}.*/

  /* Optional */
  /*  Preferred MSISDN */
  uint8_t preferredMSISDN_valid;  /**< Must be set to true if preferredMSISDN is being passed */
  uint64_t preferredMSISDN;
  /**<   MSISDN number of the preferred RAT. Refer to \hyperref[S6]{[S6]}.*/
}qmiLocInjectSubscriberIDReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Injects the phone's subscriber ID into the location engine. */
typedef struct {

  /* Mandatory */
  /*  Inject Subscriber ID Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Inject Subscriber ID request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure  */
}qmiLocInjectSubscriberIDIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCINJECTEDNETWORKINITIATEDMESSAGETYPEENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_INJECTED_NETWORK_INITIATED_MESSAGE_TYPE_SUPL_V02 = 0, /**<  SUPL network-initiated message is being injected.  */
  QMILOCINJECTEDNETWORKINITIATEDMESSAGETYPEENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocInjectedNetworkInitiatedMessageTypeEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Injects a network-initiated message into the location
                    engine. */
typedef struct {

  /* Mandatory */
  /*  Injected Network Initiated Message Type */
  qmiLocInjectedNetworkInitiatedMessageTypeEnumT_v02 injectedNIMessageType;
  /**<   Type of the network-initiated message being injected.

 Valid values: \n
      - eQMI_LOC_INJECTED_NETWORK_INITIATED_MESSAGE_TYPE_SUPL (0) --  SUPL network-initiated message is being injected.  */

  /* Mandatory */
  /*  Injected Network Initiated Message */
  uint32_t injectedNIMessage_len;  /**< Must be set to # of elements in injectedNIMessage */
  uint8_t injectedNIMessage[QMI_LOC_MAX_INJECTED_NETWORK_INITIATED_MESSAGE_LENGTH_V02];
  /**<   Network-initiated message body.
       If the inject NI message type is TYPE_SUPL, the message contains
       a SUPL INIT message as defined in OMA-TS-ULP-V2_0-20110527-C \hyperref[S5]{[S5]}. */
}qmiLocInjectNetworkInitiatedMessageReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Injects a network-initiated message into the location
                    engine. */
typedef struct {

  /* Mandatory */
  /*  Inject Network Initiated Message Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Inject Network Initiated Message request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure  */
}qmiLocInjectNetworkInitiatedMessageIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Notifies the location engine that the device is out of
                    service. */
typedef struct {
  /* This element is a placeholder to prevent the declaration of
     an empty struct.  DO NOT USE THIS FIELD UNDER ANY CIRCUMSTANCE */
  char __placeholder;
}qmiLocWWANOutOfServiceNotificationReqMsgT_v02;

  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Notifies the location engine that the device is out of
                    service. */
typedef struct {

  /* Mandatory */
  /*  Notify WWAN Out of Service Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Notify WWAN Out of Service request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */
}qmiLocWWANOutOfServiceNotificationIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Used by the control point to inject pedometer data
                    into the location engine. */
typedef struct {

  /* Mandatory */
  /*  Time Source */
  qmiLocSensorDataTimeSourceEnumT_v02 timeSource;
  /**<   Time source for the pedometer. The location service uses
 this field to identify the time reference used in the
 pedometer data time stamp.

 Valid values: \n
      - eQMI_LOC_SENSOR_TIME_SOURCE_UNSPECIFIED (0) --  Sensor time source is unspecified
      - eQMI_LOC_SENSOR_TIME_SOURCE_COMMON (1) --  Time source is common between the sensors and
       the location engine
 */

  /* Mandatory */
  /*  Pedometer Report Timestamp */
  uint32_t timestamp;
  /**<   Time stamp of the last step event in this report, i.e., the time stamp
       of the step event that caused this report to be generated.
       The time stamp is in the time reference scale that is
       used by the pedometer time source. \n
       - Units: Milliseconds */

  /* Mandatory */
  /*  Time Interval */
  uint32_t timeInterval;
  /**<   Time interval during which the step count was calculated. Subtracting
       timeInterval from the timestamp field yields the time when
       the step detection for the first step in this report started. \n
       - Units: Milliseconds */

  /* Mandatory */
  /*  Step Count */
  uint32_t stepCount;
  /**<   Number of steps counted during the time interval. */

  /* Optional */
  /*  Step Confidence */
  uint8_t stepConfidence_valid;  /**< Must be set to true if stepConfidence is being passed */
  uint8_t stepConfidence;
  /**<   Confidence associated with the step. This field is only applicable
       for a single step report, i.e., if the step count is one. \n
       - Range: 0 to 100 \n
       \textbf{Note:} The report is ignored if confidence is 0. */

  /* Optional */
  /*  Step Count Uncertainty */
  uint8_t stepCountUncertainty_valid;  /**< Must be set to true if stepCountUncertainty is being passed */
  float stepCountUncertainty;
  /**<   Uncertainty (in steps) associated with the step count. */

  /* Optional */
  /*  Step Rate */
  uint8_t stepRate_valid;  /**< Must be set to true if stepRate is being passed */
  float stepRate;
  /**<   Current estimate for the rate of steps per second. \n
       - Units: steps/second \n
       - Range: >= 0.0 */
}qmiLocPedometerReportReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Used by the control point to inject pedometer data
                    into the location engine. */
typedef struct {

  /* Mandatory */
  /*  Status of Pedometer Report Request */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Pedometer Report request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */
}qmiLocPedometerReportIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Used by the control point to get the batching size. */
typedef struct {

  /* Mandatory */
  /*  Transaction ID */
  uint32_t transactionId;
  /**<   Identifies the transaction. The transaction ID is returned in the Get
       Batch Size indication. */

  /* Mandatory */
  /*  Requested Batch Size */
  uint32_t batchSize;
  /**<   Request the service with the number of location fixes to be batched. */
}qmiLocGetBatchSizeReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Used by the control point to get the batching size. */
typedef struct {

  /* Mandatory */
  /*  Get Batch Size Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Get Batch Size request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */

  /* Mandatory */
  /*  Transaction ID */
  uint32_t transactionId;
  /**<   Transaction ID that was specified in the Get Batch
       Size request.
       */

  /* Mandatory */
  /*  Batch Size Supported */
  uint32_t batchSize;
  /**<   Number of location fixes that the service is able to batch.
       The batch size value is returned as 0 in the case of a failure status.
  */
}qmiLocGetBatchSizeIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Used by the control point to initiate a batching session. */
typedef struct {

  /* Optional */
  /*  Minimum Interval Between Position Reports */
  uint8_t minInterval_valid;  /**< Must be set to true if minInterval is being passed */
  uint32_t minInterval;
  /**<   Minimum time interval, specified by the control point, that must elapse between
       position reports. \n
       - Units: milliseconds \n
       - Default: 60000 ms
  */

  /* Optional */
  /*  Horizontal Accuracy Level */
  uint8_t horizontalAccuracyLevel_valid;  /**< Must be set to true if horizontalAccuracyLevel is being passed */
  qmiLocAccuracyLevelEnumT_v02 horizontalAccuracyLevel;
  /**<   Specifies the horizontal accuracy level required by the control point.
 If not specified, accuracy defaults to LOW.

 Valid values: \n
      - eQMI_LOC_ACCURACY_LOW (1) --  Low accuracy
      - eQMI_LOC_ACCURACY_MED (2) --  Medium accuracy
      - eQMI_LOC_ACCURACY_HIGH (3) --  High accuracy
 */

  /* Optional */
  /*  Fix Session Timeout Period */
  uint8_t fixSessionTimeout_valid;  /**< Must be set to true if fixSessionTimeout is being passed */
  uint32_t fixSessionTimeout;
  /**<   Configures the fix session timeout duration. \n
       - Units: Milliseconds \n
       - Default: 20,000 ms
  */
}qmiLocStartBatchingReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Used by the control point to initiate a batching session. */
typedef struct {

  /* Mandatory */
  /*  Start Batching Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Start Batching request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */
}qmiLocStartBatchingIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Used to notify the control point that the batched buffer is full. */
typedef struct {

  /* Mandatory */
  /*  Number of Entries in the Batch During Full Event */
  uint32_t batchCount;
  /**<   Number of entries in the batch during a full event.
  */
}qmiLocEventBatchFullIndMsgT_v02;  /* Message */
/**
    @}
  */

typedef uint64_t qmiLocBatchedReportValidFieldsMaskT_v02;
#define QMI_LOC_BATCHED_REPORT_MASK_VALID_LATITUDE_V02 ((qmiLocBatchedReportValidFieldsMaskT_v02)0x00000001ull) /**<  Latitude field is valid for this fix  */
#define QMI_LOC_BATCHED_REPORT_MASK_VALID_LONGITUDE_V02 ((qmiLocBatchedReportValidFieldsMaskT_v02)0x00000002ull) /**<  Longitude field is valid for this fix  */
#define QMI_LOC_BATCHED_REPORT_MASK_VALID_HOR_CIR_UNC_V02 ((qmiLocBatchedReportValidFieldsMaskT_v02)0x00000004ull) /**<  Horizontal circular uncertainty field is valid for this fix  */
#define QMI_LOC_BATCHED_REPORT_MASK_VALID_SPEED_HOR_V02 ((qmiLocBatchedReportValidFieldsMaskT_v02)0x00000008ull) /**<  Horizontal speed field is valid for this fix  */
#define QMI_LOC_BATCHED_REPORT_MASK_VALID_SPEED_UNC_V02 ((qmiLocBatchedReportValidFieldsMaskT_v02)0x00000010ull) /**<  Speed uncertainty field is valid for this fix  */
#define QMI_LOC_BATCHED_REPORT_MASK_VALID_ALT_WRT_ELP_V02 ((qmiLocBatchedReportValidFieldsMaskT_v02)0x00000020ull) /**<  Altitude with respect to ellipsoid field is valid for this fix  */
#define QMI_LOC_BATCHED_REPORT_MASK_VALID_SPEED_VER_V02 ((qmiLocBatchedReportValidFieldsMaskT_v02)0x00000040ull) /**<  Vertical speed field is valid for this fix  */
#define QMI_LOC_BATCHED_REPORT_MASK_VALID_HEADING_V02 ((qmiLocBatchedReportValidFieldsMaskT_v02)0x00000080ull) /**<  Heading field is valid for this fix  */
#define QMI_LOC_BATCHED_REPORT_MASK_VALID_HEADING_UNC_V02 ((qmiLocBatchedReportValidFieldsMaskT_v02)0x00000100ull) /**<  Heading uncertainty field is valid for this fix  */
#define QMI_LOC_BATCHED_REPORT_MASK_VALID_TECH_MASK_V02 ((qmiLocBatchedReportValidFieldsMaskT_v02)0x00000200ull) /**<  Technology source mask field is valid for this fix  */
#define QMI_LOC_BATCHED_REPORT_MASK_VALID_TIMESTAMP_UTC_V02 ((qmiLocBatchedReportValidFieldsMaskT_v02)0x00000400ull) /**<  UTC timestamp field is valid for this fix  */
#define QMI_LOC_BATCHED_REPORT_MASK_VALID_TIME_UNC_V02 ((qmiLocBatchedReportValidFieldsMaskT_v02)0x00000800ull) /**<  Time uncertainty field is valid for this fix  */
#define QMI_LOC_BATCHED_REPORT_MASK_VALID_MAGNETIC_DEV_V02 ((qmiLocBatchedReportValidFieldsMaskT_v02)0x00001000ull) /**<  Magnetic deviation field is valid for this fix  */
#define QMI_LOC_BATCHED_REPORT_MASK_VALID_VERT_UNC_V02 ((qmiLocBatchedReportValidFieldsMaskT_v02)0x00002000ull) /**<  Vertical uncertainty field is valid for this fix  */
#define QMI_LOC_BATCHED_REPORT_MASK_VALID_HOR_CONF_V02 ((qmiLocBatchedReportValidFieldsMaskT_v02)0x00004000ull) /**<  Horizontal confidence field is valid for this fix  */
#define QMI_LOC_BATCHED_REPORT_MASK_VALID_TIMESTAMP_GPS_V02 ((qmiLocBatchedReportValidFieldsMaskT_v02)0x00008000ull) /**<  GPS timestamp field is valid for this fix  */
/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  uint32_t fixId;
  /**<   Fix count for the session. The count starts at 0 and increments by one for
  each successive batched position report for a particular session. */

  qmiLocBatchedReportValidFieldsMaskT_v02 validFields;
  /**<   Mask of all valid fields for this fix.
 Valid bitmasks: \n
      - QMI_LOC_BATCHED_REPORT_MASK_VALID_LATITUDE (0x00000001) --  Latitude field is valid for this fix
      - QMI_LOC_BATCHED_REPORT_MASK_VALID_LONGITUDE (0x00000002) --  Longitude field is valid for this fix
      - QMI_LOC_BATCHED_REPORT_MASK_VALID_HOR_CIR_UNC (0x00000004) --  Horizontal circular uncertainty field is valid for this fix
      - QMI_LOC_BATCHED_REPORT_MASK_VALID_SPEED_HOR (0x00000008) --  Horizontal speed field is valid for this fix
      - QMI_LOC_BATCHED_REPORT_MASK_VALID_SPEED_UNC (0x00000010) --  Speed uncertainty field is valid for this fix
      - QMI_LOC_BATCHED_REPORT_MASK_VALID_ALT_WRT_ELP (0x00000020) --  Altitude with respect to ellipsoid field is valid for this fix
      - QMI_LOC_BATCHED_REPORT_MASK_VALID_SPEED_VER (0x00000040) --  Vertical speed field is valid for this fix
      - QMI_LOC_BATCHED_REPORT_MASK_VALID_HEADING (0x00000080) --  Heading field is valid for this fix
      - QMI_LOC_BATCHED_REPORT_MASK_VALID_HEADING_UNC (0x00000100) --  Heading uncertainty field is valid for this fix
      - QMI_LOC_BATCHED_REPORT_MASK_VALID_TECH_MASK (0x00000200) --  Technology source mask field is valid for this fix
      - QMI_LOC_BATCHED_REPORT_MASK_VALID_TIMESTAMP_UTC (0x00000400) --  UTC timestamp field is valid for this fix
      - QMI_LOC_BATCHED_REPORT_MASK_VALID_TIME_UNC (0x00000800) --  Time uncertainty field is valid for this fix
      - QMI_LOC_BATCHED_REPORT_MASK_VALID_MAGNETIC_DEV (0x00001000) --  Magnetic deviation field is valid for this fix
      - QMI_LOC_BATCHED_REPORT_MASK_VALID_VERT_UNC (0x00002000) --  Vertical uncertainty field is valid for this fix
      - QMI_LOC_BATCHED_REPORT_MASK_VALID_HOR_CONF (0x00004000) --  Horizontal confidence field is valid for this fix
      - QMI_LOC_BATCHED_REPORT_MASK_VALID_TIMESTAMP_GPS (0x00008000) --  GPS timestamp field is valid for this fix
 */

  double latitude;
  /**<   Latitude (specified in WGS84 datum).
       \begin{itemize1}
       \item    Type: Floating point
       \item    Units: Degrees
       \item    Range: -90.0 to 90.0   \begin{itemize1}
         \item    Positive values indicate northern latitude
         \item    Negative values indicate southern latitude
       \vspace{-0.18in} \end{itemize1} \end{itemize1} */

  double longitude;
  /**<   Longitude (specified in WGS84 datum).
       \begin{itemize1}
       \item    Type: Floating point
       \item    Units: Degrees
       \item    Range: -180.0 to 180.0   \begin{itemize1}
         \item    Positive values indicate eastern longitude
         \item    Negative values indicate western longitude
       \vspace{-0.18in} \end{itemize1} \end{itemize1} */

  float horUncCircular;
  /**<   Horizontal position uncertainty (circular).\n
       - Units: Meters */

  float speedHorizontal;
  /**<   Horizontal speed.\n
       - Units: Meters/second */

  float speedUnc;
  /**<   3-D Speed uncertainty.\n
       - Units: Meters/second */

  float altitudeWrtEllipsoid;
  /**<   Altitude with respect to the WGS84 ellipsoid.\n
       - Units: Meters \n
       - Range: -500 to 15883 */

  float speedVertical;
  /**<   Vertical speed.\n
         - Units: Meters/second */

  float heading;
  /**<   Heading.\n
         - Units: Degrees \n
         - Range: 0 to 359.999  */

  float headingUnc;
  /**<   Heading uncertainty.\n
       - Units: Degrees \n
       - Range: 0 to 359.999 */

  qmiLocPosTechMaskT_v02 technologyMask;
  /**<   Technology used in computing this fix.
 Valid bitmasks: \n
      - QMI_LOC_POS_TECH_MASK_SATELLITE (0x00000001) --  Satellites were used to generate the fix
      - QMI_LOC_POS_TECH_MASK_CELLID (0x00000002) --  Cell towers were used to generate the fix
      - QMI_LOC_POS_TECH_MASK_WIFI (0x00000004) --  Wi-Fi access points were used to generate the fix
      - QMI_LOC_POS_TECH_MASK_SENSORS (0x00000008) --  Sensors were used to generate the fix
      - QMI_LOC_POS_TECH_MASK_REFERENCE_LOCATION (0x00000010) --  Reference Location was used to generate the fix
      - QMI_LOC_POS_TECH_MASK_INJECTED_COARSE_POSITION (0x00000020) --  Coarse position injected into the location engine was used to
        generate the fix
      - QMI_LOC_POS_TECH_MASK_AFLT (0x00000040) --  AFLT was used to generate the fix
      - QMI_LOC_POS_TECH_MASK_HYBRID (0x00000080) --  GNSS and network-provided measurements were used to
        generate the fix
 */

  uint64_t timestampUtc;
  /**<   UTC timestamp. \n
       - Units: Milliseconds since Jan. 1, 1970 */

  float timeUnc;
  /**<   Time uncertainty. \n
       - Units: Milliseconds */

  float magneticDeviation;
  /**<   Difference between the bearing to true north and the bearing shown
      on a magnetic compass. The deviation is positive when the magnetic
      north is east of true north. */

  float vertUnc;
  /**<   Vertical uncertainty.\n
       - Units: Meters */

  uint8_t horConfidence;
  /**<   Horizontal confidence.
       - Units: Percent
       - Range: 0 to 99 */

  qmiLocGPSTimeStructT_v02 gpsTime;
  /**<   Number of weeks since Jan. 5, 1980, and milliseconds into the current week. */
}qmiLocBatchedReportStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Used to notify the control point with the live batched
                    position report. */
typedef struct {

  /* Mandatory */
  /*  Batched Position Report */
  qmiLocBatchedReportStructT_v02 liveBatchedReport;
  /**<   \n Live position report that is also batched. */
}qmiLocEventLiveBatchedPositionReportIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Used by the control point to retrieve fixes from the batch. */
typedef struct {

  /* Mandatory */
  /*  Number of Fix Entries to be Retrieved from the Batch */
  uint32_t numberOfEntries;
  /**<   Number of fix entries to be retrieved from the batch. \n
  Maximum limit -- QMI_LOC_READ_FROM_BATCH_MAX_SIZE.
  */

  /* Mandatory */
  /*  Transaction ID */
  uint32_t transactionId;
  /**<   Identifies the transaction. The transaction ID is returned in the Read
       from Batch indication. */
}qmiLocReadFromBatchReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Used by the control point to retrieve fixes from the batch. */
typedef struct {

  /* Mandatory */
  /*  Read from Batch Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Read from Batch request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */

  /* Mandatory */
  /*  Transaction ID */
  uint32_t transactionId;
  /**<   Transaction ID that was specified in the Read from Batch
       request.
       */

  /* Optional */
  /*  Number of Fix Entries Returned from the Batch */
  uint8_t numberOfEntries_valid;  /**< Must be set to true if numberOfEntries is being passed */
  uint32_t numberOfEntries;
  /**<   Number of fix entries returned from the batch. */

  /* Optional */
  /*  List of Batched Position Reports Returned */
  uint8_t batchedReportList_valid;  /**< Must be set to true if batchedReportList is being passed */
  uint32_t batchedReportList_len;  /**< Must be set to # of elements in batchedReportList */
  qmiLocBatchedReportStructT_v02 batchedReportList[QMI_LOC_READ_FROM_BATCH_MAX_SIZE_V02];
  /**<   \n List of fix reports returned from the batch. */
}qmiLocReadFromBatchIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Used by the control point to stop an ongoing batching session. */
typedef struct {

  /* Mandatory */
  /*  Transaction ID */
  uint32_t transactionId;
  /**<   Transaction ID of the request. */
}qmiLocStopBatchingReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Used by the control point to stop an ongoing batching session. */
typedef struct {

  /* Mandatory */
  /*  Stop Batching Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Stop Batching request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */

  /* Mandatory */
  /*  Transaction ID */
  uint32_t transactionId;
  /**<   Transaction ID that was specified in the Stop Batching request.
  */
}qmiLocStopBatchingIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Used by the control point to release the batching buffer. */
typedef struct {

  /* Mandatory */
  /*  Transaction ID */
  uint32_t transactionId;
  /**<   Identifies the transaction. */
}qmiLocReleaseBatchReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Used by the control point to release the batching buffer. */
typedef struct {

  /* Mandatory */
  /*  Release Batch Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Release Batch request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */

  /* Mandatory */
  /*  Transaction ID */
  uint32_t transactionId;
  /**<   Transaction ID that was specified in the Release Batch request.
  */
}qmiLocReleaseBatchIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Requests the control point to inject Wi-Fi AP data. */
typedef struct {
  /* This element is a placeholder to prevent the declaration of
     an empty struct.  DO NOT USE THIS FIELD UNDER ANY CIRCUMSTANCE */
  char __placeholder;
}qmiLocEventInjectWifiApDataReqIndMsgT_v02;

  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCWIFIAPDATADEVICETYPEENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_WIFI_AP_DATA_DEVICE_TYPE_WLAN_802_11_A_V02 = 0, /**<  Wi-Fi AP device is 802.11a.  */
  eQMI_LOC_WIFI_AP_DATA_DEVICE_TYPE_WLAN_802_11_B_V02 = 1, /**<  Wi-Fi AP device is 802.11b.  */
  eQMI_LOC_WIFI_AP_DATA_DEVICE_TYPE_WLAN_802_11_G_V02 = 2, /**<  Wi-Fi AP device is 802.11g.  */
  QMILOCWIFIAPDATADEVICETYPEENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocWifiApDataDeviceTypeEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCWIFIAPDATARTDUNITTYPEENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_WIFI_AP_DATA_RTD_UNIT_MICROSEC_V02 = 0, /**<  Wi-Fi AP data Round-trip Delay (RTD) is in microseconds.  */
  eQMI_LOC_WIFI_AP_DATA_RTD_UNIT_HUNDREDS_OF_NANOSEC_V02 = 1, /**<  Wi-Fi AP data RTD is in hundreds of nanoseconds.  */
  eQMI_LOC_WIFI_AP_DATA_RTD_UNIT_TENS_OF_NANOSEC_V02 = 2, /**<  Wi-Fi AP data RTD is in tens of nanoseconds.  */
  eQMI_LOC_WIFI_AP_DATA_RTD_UNIT_NANOSEC_V02 = 3, /**<  Wi-Fi AP data RTD is in nanoseconds.  */
  eQMI_LOC_WIFI_AP_DATA_RTD_UNIT_TENTH_OF_NANOSEC_V02 = 4, /**<  Wi-Fi AP data RTD is in tenths of nanoseconds.  */
  QMILOCWIFIAPDATARTDUNITTYPEENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocWifiApDataRtdUnitTypeEnumT_v02;
/**
    @}
  */

typedef uint32_t qmiLocWifiApDataMaskT_v02;
#define QMI_LOC_WIFI_APDATA_MASK_AP_TRANSMIT_POWER_V02 ((qmiLocWifiApDataMaskT_v02)0x00000001) /**<  AP transmit power is valid  */
#define QMI_LOC_WIFI_APDATA_MASK_AP_ANTENNA_GAIN_V02 ((qmiLocWifiApDataMaskT_v02)0x00000002) /**<  AP antenna gain is valid  */
#define QMI_LOC_WIFI_APDATA_MASK_AP_SNR_V02 ((qmiLocWifiApDataMaskT_v02)0x00000004) /**<  AP signal-to-noise ratio is valid  */
#define QMI_LOC_WIFI_APDATA_MASK_AP_DEVICE_TYPE_V02 ((qmiLocWifiApDataMaskT_v02)0x00000008) /**<  AP device type is valid  */
#define QMI_LOC_WIFI_APDATA_MASK_AP_RSSI_V02 ((qmiLocWifiApDataMaskT_v02)0x00000010) /**<  AP RSSI is valid  */
#define QMI_LOC_WIFI_APDATA_MASK_AP_CHANNEL_V02 ((qmiLocWifiApDataMaskT_v02)0x00000020) /**<  AP channel is valid    */
#define QMI_LOC_WIFI_APDATA_MASK_AP_ROUNDTRIP_DELAY_V02 ((qmiLocWifiApDataMaskT_v02)0x00000040) /**<  AP roundtrip delay is valid    */
#define QMI_LOC_WIFI_APDATA_MASK_AP_ROUNDTRIP_DELAY_ACCURACY_V02 ((qmiLocWifiApDataMaskT_v02)0x00000080) /**<  AP roundtrip delay accuracy is valid   */
#define QMI_LOC_WIFI_APDATA_MASK_MOBILE_SNR_V02 ((qmiLocWifiApDataMaskT_v02)0x00000100) /**<  Mobile signal-to-noise ratio is valid   */
#define QMI_LOC_WIFI_APDATA_MASK_MOBILE_RSSI_V02 ((qmiLocWifiApDataMaskT_v02)0x00000200) /**<  Mobile RSSI is valid  */
/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  qmiLocWifiApDataMaskT_v02 wifiApDataMask;
  /**<   Specifies which Wi-Fi AP scan information types are being used.

 Valid values: \n
      - QMI_LOC_WIFI_APDATA_MASK_AP_TRANSMIT_POWER (0x00000001) --  AP transmit power is valid
      - QMI_LOC_WIFI_APDATA_MASK_AP_ANTENNA_GAIN (0x00000002) --  AP antenna gain is valid
      - QMI_LOC_WIFI_APDATA_MASK_AP_SNR (0x00000004) --  AP signal-to-noise ratio is valid
      - QMI_LOC_WIFI_APDATA_MASK_AP_DEVICE_TYPE (0x00000008) --  AP device type is valid
      - QMI_LOC_WIFI_APDATA_MASK_AP_RSSI (0x00000010) --  AP RSSI is valid
      - QMI_LOC_WIFI_APDATA_MASK_AP_CHANNEL (0x00000020) --  AP channel is valid
      - QMI_LOC_WIFI_APDATA_MASK_AP_ROUNDTRIP_DELAY (0x00000040) --  AP roundtrip delay is valid
      - QMI_LOC_WIFI_APDATA_MASK_AP_ROUNDTRIP_DELAY_ACCURACY (0x00000080) --  AP roundtrip delay accuracy is valid
      - QMI_LOC_WIFI_APDATA_MASK_MOBILE_SNR (0x00000100) --  Mobile signal-to-noise ratio is valid
      - QMI_LOC_WIFI_APDATA_MASK_MOBILE_RSSI (0x00000200) --  Mobile RSSI is valid  */

  uint8_t macAddress[QMI_LOC_WIFI_MAC_ADDR_LENGTH_V02];
  /**<   MAC address. \n
  Each address is of length QMI_LOC_WIFI_MAC_ADDR_LENGTH.
  */

  int32_t apTransmitPower;
  /**<   AP transmit power in dBm.  */

  int32_t apAntennaGain;
  /**<   AP antenna gain in dBI. */

  int32_t apSignalToNoise;
  /**<   AP SNR received at the mobile device. */

  qmiLocWifiApDataDeviceTypeEnumT_v02 apDeviceType;
  /**<   List of AP device types. */

  int32_t apRssi;
  /**<   AP signal strength indicator in dBm. */

  uint16_t apChannel;
  /**<   AP Wi-Fi channel on which a beacon was received. */

  uint32_t apRoundTripDelay;
  /**<   Round trip delay between the mobile device and the AP, in units of
       apRoundTripDelayUnit. */

  qmiLocWifiApDataRtdUnitTypeEnumT_v02 apRoundTripDelayUnit;
  /**<   Units of apRoundTripDelay and its accuracy; mandatory if apRoundTripDelay
       is present. */

  uint8_t apRoundTripDelayAccuracy;
  /**<   AP's accuracy of round trip delay apRoundTripDelay, in units of
       apRoundTripDelayUnit. */

  int32_t mobileSignalToNoise;
  /**<   Mobile SNR received at the AP. */

  int32_t mobileRssi;
  /**<   Mobile signal strength at the AP. */
}qmiLocWifiApDataStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Injects Wi-Fi AP data. */
typedef struct {

  /* Mandatory */
  /*  Wi-Fi AP Scan Data */
  uint32_t wifiApInfo_len;  /**< Must be set to # of elements in wifiApInfo */
  qmiLocWifiApDataStructT_v02 wifiApInfo[QMI_LOC_WIFI_MAX_REPORTED_APS_PER_MSG_V02];
  /**<   \n List of Wi-Fi AP scan information entered by the control point. */
}qmiLocInjectWifiApDataReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Injects Wi-Fi AP data. */
typedef struct {

  /* Mandatory */
  /*  Wi-Fi AP Scan Information Injection Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Inject Wi-Fi AP Scan Information request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure  */
}qmiLocInjectWifiApDataIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCWIFIACCESSPOINTATTACHSTATESENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_WIFI_ACCESS_POINT_ATTACHED_V02 = 0, /**<  Attached to an access point  */
  eQMI_LOC_WIFI_ACCESS_POINT_DETACHED_V02 = 1, /**<  Detached from an access point  */
  eQMI_LOC_WIFI_ACCESS_POINT_HANDOVER_V02 = 2, /**<  Handed over to another access point  */
  QMILOCWIFIACCESSPOINTATTACHSTATESENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocWifiAccessPointAttachStatesEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Used by the control point to inject the Wi-Fi attachment status. */
typedef struct {

  /* Mandatory */
  /*  Attach State */
  qmiLocWifiAccessPointAttachStatesEnumT_v02 attachState;
  /**<   Wi.Fi access point attach state.

 Valid values: \n
      - eQMI_LOC_WIFI_ACCESS_POINT_ATTACHED (0) --  Attached to an access point
      - eQMI_LOC_WIFI_ACCESS_POINT_DETACHED (1) --  Detached from an access point
      - eQMI_LOC_WIFI_ACCESS_POINT_HANDOVER (2) --  Handed over to another access point  */

  /* Optional */
  /*  Access Point MAC Address */
  uint8_t accessPointMacAddress_valid;  /**< Must be set to true if accessPointMacAddress is being passed */
  uint8_t accessPointMacAddress[QMI_LOC_WIFI_MAC_ADDR_LENGTH_V02];
  /**<   MAC address of the access point to which the Wi-Fi is attached.
        This must always be specified if the attach state is Handover.
        */

  /* Optional */
  /*  Wi-Fi AP SSID String */
  uint8_t wifiApSsid_valid;  /**< Must be set to true if wifiApSsid is being passed */
  char wifiApSsid[QMI_LOC_MAX_WIFI_AP_SSID_STR_LENGTH_V02 + 1];
  /**<   The NULL-terminated SSID of the Wi-Fi AP. Its maximum length according to the ASCII standard is 32 octets. */
}qmiLocNotifyWifiAttachmentStatusReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Used by the control point to inject the Wi-Fi attachment status. */
typedef struct {

  /* Mandatory */
  /*  Status of Wi-Fi Attachment Status Request */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of Wi-Fi Attachment Status request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure  */
}qmiLocNotifyWifiAttachmentStatusIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCWIFIENABLEDSTATUSENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_WIFI_ENABLED_FALSE_V02 = 0, /**<  Wi-Fi is disabled on the device  */
  eQMI_LOC_WIFI_ENABLED_TRUE_V02 = 1, /**<  Wi-Fi is enabled on the device  */
  QMILOCWIFIENABLEDSTATUSENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocWifiEnabledStatusEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Used by the control point to inject the Wi-Fi enabled status. */
typedef struct {

  /* Mandatory */
  /*  Enabled Status */
  qmiLocWifiEnabledStatusEnumT_v02 enabledStatus;
  /**<   Wi-Fi enabled status on the device.

 Valid values: \n
      - eQMI_LOC_WIFI_ENABLED_FALSE (0) --  Wi-Fi is disabled on the device
      - eQMI_LOC_WIFI_ENABLED_TRUE (1) --  Wi-Fi is enabled on the device  */
}qmiLocNotifyWifiEnabledStatusReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Used by the control point to inject the Wi-Fi enabled status. */
typedef struct {

  /* Mandatory */
  /*  Status of Wi-Fi Enabled Status Request */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Wi-Fi Enabled Status request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure  */
}qmiLocNotifyWifiEnabledStatusIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Notifies the control point whether the GNSS location engine is
                    ready to accept vehicle data. */
typedef struct {

  /* Optional */
  /*  Vehicle Accelerometer Ready Status */
  uint8_t vehicleAccelReadyStatus_valid;  /**< Must be set to true if vehicleAccelReadyStatus is being passed */
  uint8_t vehicleAccelReadyStatus;
  /**<   The location service uses this TLV to let a control point know when it is
       ready or not ready to receive vehicle accelerometer data input.
       Values: \n
       - 0x00 -- Not ready  \n
       - 0x01 -- Ready */

  /* Optional */
  /*  Vehicle Angular Rate Ready Status */
  uint8_t vehicleAngularRateReadyStatus_valid;  /**< Must be set to true if vehicleAngularRateReadyStatus is being passed */
  uint8_t vehicleAngularRateReadyStatus;
  /**<   The location service uses this TLV to let a control point know when it is
       ready or not ready to receive vehicle angular rate data input.
       Values: \n
       - 0x00 -- Not ready \n
       - 0x01 -- Ready */

  /* Optional */
  /*  Vehicle Odometry Ready Status */
  uint8_t vehicleOdometryReadyStatus_valid;  /**< Must be set to true if vehicleOdometryReadyStatus is being passed */
  uint8_t vehicleOdometryReadyStatus;
  /**<   The location service uses this TLV to let a control point know when it is
       ready or not ready to receive vehicle odometry data input.
       Values: \n
       - 0x00 -- Not ready \n
       - 0x01 -- Ready*/
}qmiLocEventVehicleDataReadyIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  uint32_t timeOffset;
  /**<   Sample time offset. This time offset must be
       relative to the vehicle sensor time of the first sample. \n
       - Units: Microseconds \n
       - Range: Up to over 4000 seconds */

  uint32_t axisSample_len;  /**< Must be set to # of elements in axisSample */
  float axisSample[QMI_LOC_VEHICLE_SENSOR_DATA_MAX_AXES_V02];
  /**<   Sensor axis sample.        \n
       - Type: Floating point     \n
       - Units accelerometer: Meters/seconds^2 \n
       - Units gyroscope: Radians/seconds \vspace{4pt}

       Note: The axes samples must be in the following order: \n
             1. X-Axis \n
             2. Y-Axis \n
             3. Z-Axis */
}qmiLocVehicleSensorSampleStructT_v02;  /* Type */
/**
    @}
  */

typedef uint8_t qmiLocAxesMaskT_v02;
#define QMI_LOC_MASK_X_AXIS_V02 ((qmiLocAxesMaskT_v02)0x01) /**<  X-axis is valid  */
#define QMI_LOC_MASK_Y_AXIS_V02 ((qmiLocAxesMaskT_v02)0x02) /**<  Y-axis is valid  */
#define QMI_LOC_MASK_Z_AXIS_V02 ((qmiLocAxesMaskT_v02)0x04) /**<  Z-axis is valid  */
/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  uint32_t sampleTimeBase;
  /**<   Denotes a 32-bit time tag of the reference time from which
       all samples in this message are offset. This time must
       be the same as or (slightly) earlier than the first (oldest)
       sample in this message. \n
       - Units: Milliseconds \n
       - Range: ~4 million seconds, or almost 50 days between rollovers */

  qmiLocAxesMaskT_v02 axesValidity;
  /**<   Identifies the axes that are valid for all sensor samples.

 Valid values: \n
      - QMI_LOC_MASK_X_AXIS (0x01) --  X-axis is valid
      - QMI_LOC_MASK_Y_AXIS (0x02) --  Y-axis is valid
      - QMI_LOC_MASK_Z_AXIS (0x04) --  Z-axis is valid  */

  uint32_t sensorData_len;  /**< Must be set to # of elements in sensorData */
  qmiLocVehicleSensorSampleStructT_v02 sensorData[QMI_LOC_VEHICLE_SENSOR_DATA_MAX_SAMPLES_V02];
}qmiLocVehicleSensorSampleListStructType_v02;  /* Type */
/**
    @}
  */

typedef uint32_t qmiLocVehicleOdometryMeasDeviationMaskType_v02;
#define QMI_LOC_MASK_VEHICLE_ODOMETRY_REVERSE_MOVEMENT_V02 ((qmiLocVehicleOdometryMeasDeviationMaskType_v02)0x00000001) /**<  Odometry data in this message includes at least some data where
       the vehicle may have been moving in the reverse direction; this
       bit must be set if odometry data may be in reverse, and should
       not be set if odometry data is all in the forward direction  */
#define QMI_LOC_MASK_VEHICLE_ODOMETRY_AFFECTED_BY_ERRORS_V02 ((qmiLocVehicleOdometryMeasDeviationMaskType_v02)0x00000002) /**<  Odometry data in this message includes at least some data affected
       by a major error source affecting distance-travelled accuracy,
       such as wheel slippage due to skidding, gravel, snow, or ice, as
       detected by the vehicle, e.g., via an ABS or other system  */
#define QMI_LOC_MASK_VEHICLE_ODOMETRY_ABSOLUTE_MEASUREMENT_V02 ((qmiLocVehicleOdometryMeasDeviationMaskType_v02)0x00000004) /**<  Odometry data in this message is an absolute amount since the vehicle
       began service, and is the same vehicle that is regularly used with
       this device (so that the offset of this value, since the last time
       this measurement was used by the location engine, can safely be used
       as a likely correct estimate of distance travelled since last
       use)  */
typedef uint32_t qmiLocVehicleOdometryWheelFlagsMaskT_v02;
#define QMI_LOC_MASK_VEHICLE_ODOMETRY_LEFT_AND_RIGHT_AVERAGE_V02 ((qmiLocVehicleOdometryWheelFlagsMaskT_v02)0x00000001) /**<  Average of left and right non-turning wheels  */
#define QMI_LOC_MASK_VEHICLE_ODOMETRY_LEFT_V02 ((qmiLocVehicleOdometryWheelFlagsMaskT_v02)0x00000002) /**<  Left side, non-turning wheel  */
#define QMI_LOC_MASK_VEHICLE_ODOMETRY_RIGHT_V02 ((qmiLocVehicleOdometryWheelFlagsMaskT_v02)0x00000004) /**<  Right side, non-turning wheel  */
/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  uint32_t timeOffset;
  /**<   Sample time offset. This time offset must be
       relative to the sensor time of the first sample. \n
       - Units: Microseconds \n
       - Range: Up to over 4000 seconds */

  uint32_t distanceTravelled_len;  /**< Must be set to # of elements in distanceTravelled */
  uint32_t distanceTravelled[QMI_LOC_VEHICLE_ODOMETRY_MAX_MEASUREMENTS_V02];
  /**<    Distance travelled (odometry) sample offset. \n
        - Units of accumulated distance: Millimeters \n
        - Range: Over 4000 kilometers

        This measurement (with units in millimeters) is added to
        the distance_travelled_base measurement (in meters) to
        get the total distance travelled sample value.

        Note: The order of measurements must be as follows: \n
        1. Left and right average \n
        2. Left \n
        3. Right
   */
}qmiLocVehicleOdometrySampleStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  uint32_t sampleTimeBase;
  /**<   Denotes a 32-bit time tag of a reference time, from which
       all samples in this message are offset.  Note this time must
       be the same or (slightly) earlier than the first (oldest)
       sample in this message. \n
       - Units: 1 millisecond \n
       - Range: ~4 million seconds, or almost 50 days between rollovers */

  qmiLocVehicleOdometryMeasDeviationMaskType_v02 flags;
  /**<   Flags to indicate any deviation from the default measurement
 assumptions. Valid bitmasks: \n
      - QMI_LOC_MASK_VEHICLE_ODOMETRY_REVERSE_MOVEMENT (0x00000001) --  Odometry data in this message includes at least some data where
       the vehicle may have been moving in the reverse direction; this
       bit must be set if odometry data may be in reverse, and should
       not be set if odometry data is all in the forward direction
      - QMI_LOC_MASK_VEHICLE_ODOMETRY_AFFECTED_BY_ERRORS (0x00000002) --  Odometry data in this message includes at least some data affected
       by a major error source affecting distance-travelled accuracy,
       such as wheel slippage due to skidding, gravel, snow, or ice, as
       detected by the vehicle, e.g., via an ABS or other system
      - QMI_LOC_MASK_VEHICLE_ODOMETRY_ABSOLUTE_MEASUREMENT (0x00000004) --  Odometry data in this message is an absolute amount since the vehicle
       began service, and is the same vehicle that is regularly used with
       this device (so that the offset of this value, since the last time
       this measurement was used by the location engine, can safely be used
       as a likely correct estimate of distance travelled since last
       use)  */

  qmiLocVehicleOdometryWheelFlagsMaskT_v02 wheelFlags;
  /**<   Delineates for which wheels measurements are being provided
 in the following samples, where one or more of the following
 bits must be set, and data samples aligned with these axes must
 appear in groups, in this order.

 Valid bitmasks: \n
      - QMI_LOC_MASK_VEHICLE_ODOMETRY_LEFT_AND_RIGHT_AVERAGE (0x00000001) --  Average of left and right non-turning wheels
      - QMI_LOC_MASK_VEHICLE_ODOMETRY_LEFT (0x00000002) --  Left side, non-turning wheel
      - QMI_LOC_MASK_VEHICLE_ODOMETRY_RIGHT (0x00000004) --  Right side, non-turning wheel  */

  uint32_t distanceTravelledBase;
  /**<   Distance traveled base. \n
        - Units of accumulated distance: Meters \n
        - Range: Over 4,000,0000 kilometers \vspace{0.06in} \n

        Distance travelled (odometry) is to be reported in a continuously
        accumulating way from device power up. It may be incremental distance
        starting at 0, or another arbitrary point, from device power up, or the
        absolute distance traveled by the vehicle
        (and if so, set QMI_LOC_MASK_VEHICLE_ODOMETRY_ABSOLUTE_MEASUREMENT),
        as long as it grows incrementally from device power up.

        This distance_travelled_base is added to the distrance_travelled_offset
        of each sample (below) to get the absolute distance of each sample
        point.

        Distance travelled errors are expected to be primarily due to the
        scale factor, with some allowance for noise due to minor slippage
        events (e.g., gravel.)
        Major wheel slippage events that affect odometry
        must be flagged -- see the flags field.

        Note that other events, such as a vehicle travelling in reverse, may
        also affect the available accuracy of this information, and notification
        of those events must be provided -- see the flags field. */

  uint32_t odometryData_len;  /**< Must be set to # of elements in odometryData */
  qmiLocVehicleOdometrySampleStructT_v02 odometryData[QMI_LOC_VEHICLE_SENSOR_DATA_MAX_SAMPLES_V02];
  /**<   Variable length array to specify the odometry samples.
       Maximum length of the array is 50. */
}qmiLocVehicleOdometrySampleListStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Injects on-vehicle sensor data into the location engine. */
typedef struct {

  /* Optional */
  /*  On-Vehicle Accelerometer Data */
  uint8_t accelData_valid;  /**< Must be set to true if accelData is being passed */
  qmiLocVehicleSensorSampleListStructType_v02 accelData;
  /**<   \vspace{0.06in} \n Vehicle accelerometer sensor samples. */

  /* Optional */
  /*  On-Vehicle Angular Rotation Data */
  uint8_t angRotationData_valid;  /**< Must be set to true if angRotationData is being passed */
  qmiLocVehicleSensorSampleListStructType_v02 angRotationData;
  /**<   \vspace{0.06in} \n Vehicle angular rotation data sensor samples. */

  /* Optional */
  /*  Odometry Data */
  uint8_t odometryData_valid;  /**< Must be set to true if odometryData is being passed */
  qmiLocVehicleOdometrySampleListStructT_v02 odometryData;
  /**<   \vspace{0.06in} \n Odometer sensor samples. */

  /* Optional */
  /*  External Time Sync Information */
  uint8_t changeInTimeScales_valid;  /**< Must be set to true if changeInTimeScales is being passed */
  int32_t changeInTimeScales;
  /**<   This field is to be used in conjunction with an external
       time-sync mechanism that is aligning the vehicle sensor time scale
       with the on-device sensor time scale to ensure that updates in
       that time offset do not appear as jumps in the relative sensor time
       of the samples provided in this message. If there is no such sync
       mechanism, e.g., if only the vehicle time is provided, this field
       may be left at 0.

       This field is defined as the change from the previously-sent QMI
       message with similar TLVs 0x10, 0x11, or 0x12 in it, to this QMI
       message in the amount that the sensor_time is ahead of an
       external vehicle time. \n

       - Units: Microseconds \n
       - Range: Approximately -2100 seconds to + 2100 seconds, where
                full-scale (minimum and maximum value) is interpreted
                as equal to or greater than this value of an offset change
                (unlikely to be reached in practice, unless there is a
                startup, major resync, or some other rollover event). */
}qmiLocInjectVehicleSensorDataReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Injects on-vehicle sensor data into the location engine. */
typedef struct {

  /* Mandatory */
  /*  Inject Vehicle Sensor Data Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Inject Vehicle Sensor Data request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure  */
}qmiLocInjectVehicleSensorDataIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Used by the control point to get the first available WWAN
                    position from the location engine. */
typedef struct {

  /* Mandatory */
  /*  Transaction ID */
  uint32_t transactionId;
  /**<   Identifies the transaction. The transaction ID
       is returned in the Get Available WWAN Position indication. */
}qmiLocGetAvailWwanPositionReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Used by the control point to get the first available WWAN
                    position from the location engine. */
typedef struct {

  /* Mandatory */
  /*  Get Available WWAN Position Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Get Available WWAN Position request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure  */

  /* Optional */
  /*  Transaction ID */
  uint8_t transactionId_valid;  /**< Must be set to true if transactionId is being passed */
  uint32_t transactionId;
  /**<   Transaction ID that was specified in the Get Available
       WWAN Position request. This parameter will
       always be present if the status field is set to
       SUCCESS. */

  /* Optional */
  /*  Latitude */
  uint8_t latitude_valid;  /**< Must be set to true if latitude is being passed */
  double latitude;
  /**<   Latitude (specified in WGS84 datum).
       \begin{itemize1}
       \item    Type: Floating point
       \item    Units: Degrees
       \item     Range: -90.0 to 90.0      \begin{itemize1}
         \item    Positive values indicate northern latitude
         \item    Negative values indicate southern latitude
       \vspace{-0.18in} \end{itemize1} \end{itemize1} */

  /* Optional */
  /*  Longitude */
  uint8_t longitude_valid;  /**< Must be set to true if longitude is being passed */
  double longitude;
  /**<   Longitude (specified in WGS84 datum).
       \begin{itemize1}
       \item    Type: Floating point
       \item    Units: Degrees
       \item    Range: -180.0 to 180.0     \begin{itemize1}
         \item    Positive values indicate eastern longitude
         \item    Negative values indicate western longitude
       \vspace{-0.18in} \end{itemize1} \end{itemize1} */

  /* Optional */
  /*  Circular Horizontal Position Uncertainty */
  uint8_t horUncCircular_valid;  /**< Must be set to true if horUncCircular is being passed */
  float horUncCircular;
  /**<   Horizontal position uncertainty (circular).\n
       - Units: Meters */

  /* Optional */
  /*  Altitude With Respect to Ellipsoid */
  uint8_t altitudeWrtEllipsoid_valid;  /**< Must be set to true if altitudeWrtEllipsoid is being passed */
  float altitudeWrtEllipsoid;
  /**<   Altitude with respect to the WGS84 ellipsoid.\n
       - Units: Meters \n
       - Range: -500 to 15883 */

  /* Optional */
  /*  Vertical Uncertainty */
  uint8_t vertUnc_valid;  /**< Must be set to true if vertUnc is being passed */
  float vertUnc;
  /**<   Vertical uncertainty.\n
       - Units: Meters */

  /* Optional */
  /*  UTC Timestamp */
  uint8_t timestampUtc_valid;  /**< Must be set to true if timestampUtc is being passed */
  uint64_t timestampUtc;
  /**<   UTC timestamp. \n
       - Units: Milliseconds since Jan. 1, 1970 */

  /* Optional */
  /*  Time Uncertainty */
  uint8_t timeUnc_valid;  /**< Must be set to true if timeUnc is being passed */
  float timeUnc;
  /**<   Time uncertainty. \n
       - Units: Milliseconds */

  /* Optional */
  /*  Horizontal Elliptical Uncertainty Semi-Minor Axis */
  uint8_t horUncEllipseSemiMinor_valid;  /**< Must be set to true if horUncEllipseSemiMinor is being passed */
  float horUncEllipseSemiMinor;
  /**<   Semi-minor axis of horizontal elliptical uncertainty. \n
       - Units: Meters */

  /* Optional */
  /*  Horizontal Elliptical Uncertainty Semi-Major Axis */
  uint8_t horUncEllipseSemiMajor_valid;  /**< Must be set to true if horUncEllipseSemiMajor is being passed */
  float horUncEllipseSemiMajor;
  /**<   Semi-major axis of horizontal elliptical uncertainty. \n
       - Units: Meters */

  /* Optional */
  /*  Horizontal Elliptical Uncertainty Azimuth */
  uint8_t horUncEllipseOrientAzimuth_valid;  /**< Must be set to true if horUncEllipseOrientAzimuth is being passed */
  float horUncEllipseOrientAzimuth;
  /**<   Elliptical horizontal uncertainty azimuth of orientation. \n
       - Units: Decimal degrees \n
       - Range: 0 to 180 */

  /* Optional */
  /*  Horizontal Circular Confidence */
  uint8_t horCircularConfidence_valid;  /**< Must be set to true if horCircularConfidence is being passed */
  uint8_t horCircularConfidence;
  /**<   Horizontal circular uncertainty confidence. \n
       - Units: Percent \n
       - Range: 0 to 99 */

  /* Optional */
  /*  Horizontal Elliptical Confidence */
  uint8_t horEllipticalConfidence_valid;  /**< Must be set to true if horEllipticalConfidence is being passed */
  uint8_t horEllipticalConfidence;
  /**<   Horizontal elliptical uncertainty confidence. \n
       - Units: Percent \n
       - Range: 0 to 99 */

  /* Optional */
  /*  Horizontal Reliability */
  uint8_t horReliability_valid;  /**< Must be set to true if horReliability is being passed */
  qmiLocReliabilityEnumT_v02 horReliability;
  /**<   Specifies the reliability of the horizontal position.
 Valid values: \n
      - eQMI_LOC_RELIABILITY_NOT_SET (0) --  Location reliability is not set
      - eQMI_LOC_RELIABILITY_VERY_LOW (1) --  Location reliability is very low; use it at your own risk
      - eQMI_LOC_RELIABILITY_LOW (2) --  Location reliability is low; little or no cross-checking is possible
      - eQMI_LOC_RELIABILITY_MEDIUM (3) --  Location reliability is medium; limited cross-check passed
      - eQMI_LOC_RELIABILITY_HIGH (4) --  Location reliability is high; strong cross-check passed
 */

  /* Optional */
  /*  Altitude With Respect to Sea Level */
  uint8_t altitudeWrtMeanSeaLevel_valid;  /**< Must be set to true if altitudeWrtMeanSeaLevel is being passed */
  float altitudeWrtMeanSeaLevel;
  /**<   Altitude with respect to mean sea level. \n
       - Units: Meters */

  /* Optional */
  /*  Vertical Confidence */
  uint8_t vertConfidence_valid;  /**< Must be set to true if vertConfidence is being passed */
  uint8_t vertConfidence;
  /**<   Vertical uncertainty confidence. \n
       - Units: Percent \n
       - Range: 0 to 99 */

  /* Optional */
  /*  Vertical Reliability */
  uint8_t vertReliability_valid;  /**< Must be set to true if vertReliability is being passed */
  qmiLocReliabilityEnumT_v02 vertReliability;
  /**<   Specifies the reliability of the vertical position.

 Valid values: \n
      - eQMI_LOC_RELIABILITY_NOT_SET (0) --  Location reliability is not set
      - eQMI_LOC_RELIABILITY_VERY_LOW (1) --  Location reliability is very low; use it at your own risk
      - eQMI_LOC_RELIABILITY_LOW (2) --  Location reliability is low; little or no cross-checking is possible
      - eQMI_LOC_RELIABILITY_MEDIUM (3) --  Location reliability is medium; limited cross-check passed
      - eQMI_LOC_RELIABILITY_HIGH (4) --  Location reliability is high; strong cross-check passed
 */

  /* Optional */
  /*  GPS Time */
  uint8_t gpsTime_valid;  /**< Must be set to true if gpsTime is being passed */
  qmiLocGPSTimeStructT_v02 gpsTime;

  /* Optional */
  /*  Time Source */
  uint8_t timeSrc_valid;  /**< Must be set to true if timeSrc is being passed */
  qmiLocTimeSourceEnumT_v02 timeSrc;
  /**<   Time source.

 Valid values: \n
      - eQMI_LOC_TIME_SRC_INVALID (0) --  Invalid time.
      - eQMI_LOC_TIME_SRC_NETWORK_TIME_TRANSFER (1) --  Time is set by the 1X system
      - eQMI_LOC_TIME_SRC_NETWORK_TIME_TAGGING (2) --  Time is set by WCDMA/GSM time tagging (i.e.,
       associating network time with GPS time)
      - eQMI_LOC_TIME_SRC_EXTERNAL_INPUT (3) --  Time is set by an external injection
      - eQMI_LOC_TIME_SRC_TOW_DECODE (4) --  Time is set after decoding over-the-air GPS navigation data
       from one GPS satellite
      - eQMI_LOC_TIME_SRC_TOW_CONFIRMED (5) --  Time is set after decoding over-the-air GPS navigation data
       from multiple satellites
      - eQMI_LOC_TIME_SRC_TOW_AND_WEEK_CONFIRMED (6) --  Both time of the week and the GPS week number are known
      - eQMI_LOC_TIME_SRC_NAV_SOLUTION (7) --  Time is set by the position engine after the fix is obtained
      - eQMI_LOC_TIME_SRC_SOLVE_FOR_TIME (8) --  Time is set by the position engine after performing SFT;
       this is done when the clock time uncertainty is large
      - eQMI_LOC_TIME_SRC_GLO_TOW_DECODE (9) --  Time is set after decoding GLO satellites
      - eQMI_LOC_TIME_SRC_TIME_TRANSFORM (10) --  Time is set after transforming the GPS to GLO time
      - eQMI_LOC_TIME_SRC_WCDMA_SLEEP_TIME_TAGGING (11) --  Time is set by the sleep time tag provided by the WCDMA network
      - eQMI_LOC_TIME_SRC_GSM_SLEEP_TIME_TAGGING (12) --  Time is set by the sleep time tag provided by the GSM network
      - eQMI_LOC_TIME_SRC_UNKNOWN (13) --  Source of the time is unknown
      - eQMI_LOC_TIME_SRC_SYSTEM_TIMETICK (14) --  Time is derived from the system clock (better known as the slow clock);
       GNSS time is maintained irrespective of the GNSS receiver state
      - eQMI_LOC_TIME_SRC_QZSS_TOW_DECODE (15) --  Time is set after decoding QZSS satellites
      - eQMI_LOC_TIME_SRC_BDS_TOW_DECODE (16) --  Time is set after decoding BDS satellites
 */
}qmiLocGetAvailWwanPositionIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCPREMIUMSERVICEENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_PREMIUM_SERVICE_GTP_CELL_V02 = 0, /**<  Premium service -- Global terrestrial positioning for the cell  */
  eQMI_LOC_PREMIUM_SERVICE_SAP_V02 = 1, /**<  Premium service -- Sensor-assisted positioning  */
  eQMI_LOC_PREMIUM_SERVICE_GTP_ENH_CELL_V02 = 2, /**<  Premium service -- Global terrestrial positioning enhanced cell  */
  QMILOCPREMIUMSERVICEENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocPremiumServiceEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCPREMIUMSERVICECFGENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_PREMIUM_SERVICE_DISABLED_V02 = 0, /**<  Premium service disabled  */
  eQMI_LOC_PREMIUM_SERVICE_ENABLED_BASIC_V02 = 1, /**<  Premium service enabled for basic  */
  eQMI_LOC_PREMIUM_SERVICE_ENABLED_PREMIUM_V02 = 2, /**<  Premium service enabled for premium  */
  QMILOCPREMIUMSERVICECFGENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocPremiumServiceCfgEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Used by the control point to set the configuration
                    information for all iZat premium services to the location
                    engine. */
typedef struct {

  /* Mandatory */
  /*  Set Premium Service Type */
  qmiLocPremiumServiceEnumT_v02 premiumServiceType;
  /**<   Specifies the premium service to configure.

 Valid values: \n
      - eQMI_LOC_PREMIUM_SERVICE_GTP_CELL (0) --  Premium service -- Global terrestrial positioning for the cell
      - eQMI_LOC_PREMIUM_SERVICE_SAP (1) --  Premium service -- Sensor-assisted positioning
      - eQMI_LOC_PREMIUM_SERVICE_GTP_ENH_CELL (2) --  Premium service -- Global terrestrial positioning enhanced cell
 */

  /* Mandatory */
  /*  Set Premium Service Configuration */
  qmiLocPremiumServiceCfgEnumT_v02 premiumServiceCfg;
  /**<   Specifies the premium service configuration mode.

 Valid values: \n
      - eQMI_LOC_PREMIUM_SERVICE_DISABLED (0) --  Premium service disabled
      - eQMI_LOC_PREMIUM_SERVICE_ENABLED_BASIC (1) --  Premium service enabled for basic
      - eQMI_LOC_PREMIUM_SERVICE_ENABLED_PREMIUM (2) --  Premium service enabled for premium
 */
}qmiLocSetPremiumServicesCfgReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Used by the control point to set the configuration
                    information for all iZat premium services to the location
                    engine. */
typedef struct {

  /* Mandatory */
  /*  Set Premium Service Configuration Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Set Premium Services Configuration request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure  */
}qmiLocSetPremiumServicesCfgIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCXTRAVERSIONCHECKENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_XTRA_VERSION_CHECK_DISABLE_V02 = 0, /**<  XTRA file version check is not required   */
  eQMI_LOC_XTRA_VERSION_CHECK_AUTO_V02 = 1, /**<  XTRA file version check is required; the Location service decides the 'expected version' based on the preprovisioned XTRA version configuration  */
  eQMI_LOC_XTRA_VERSION_CHECK_XTRA2_V02 = 2, /**<  Check the XTRA file against XTRA2 format  */
  eQMI_LOC_XTRA_VERSION_CHECK_XTRA3_V02 = 3, /**<  Check the XTRA file against XTRA3 format  */
  QMILOCXTRAVERSIONCHECKENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocXtraVersionCheckEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Used by the control point to enable or disable XTRA version
                    verification. */
typedef struct {

  /* Mandatory */
  /*  Set XTRA Version Check Mode */
  qmiLocXtraVersionCheckEnumT_v02 xtraVersionCheckMode;
  /**<   Specifies XTRA version check mode.

 Valid values: \n
      - eQMI_LOC_XTRA_VERSION_CHECK_DISABLE (0) --  XTRA file version check is not required
      - eQMI_LOC_XTRA_VERSION_CHECK_AUTO (1) --  XTRA file version check is required; the Location service decides the 'expected version' based on the preprovisioned XTRA version configuration
      - eQMI_LOC_XTRA_VERSION_CHECK_XTRA2 (2) --  Check the XTRA file against XTRA2 format
      - eQMI_LOC_XTRA_VERSION_CHECK_XTRA3 (3) --  Check the XTRA file against XTRA3 format
 */
}qmiLocSetXtraVersionCheckReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Used by the control point to enable or disable XTRA version
                    verification. */
typedef struct {

  /* Mandatory */
  /*  Set XTRA Version Check Mode Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Set XTRA version check request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure  */
}qmiLocSetXtraVersionCheckIndMsgT_v02;  /* Message */
/**
    @}
  */

typedef uint64_t qmiLocGNSSConstellEnumT_v02;
#define eQMI_SYSTEM_GPS_V02 ((qmiLocGNSSConstellEnumT_v02)0x01ull) /**<  Enable GPS \n  */
#define eQMI_SYSTEM_GLO_V02 ((qmiLocGNSSConstellEnumT_v02)0x02ull) /**<  Enable GLONASS \n  */
#define eQMI_SYSTEM_BDS_V02 ((qmiLocGNSSConstellEnumT_v02)0x04ull) /**<  Enable BDS \n  */
#define eQMI_SYSTEM_GAL_V02 ((qmiLocGNSSConstellEnumT_v02)0x08ull) /**<  Enable Galileo  */
/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Sets satellite constellations of interest for reporting. */
typedef struct {

  /* Optional */
  /*  GNSS Measurement Report Constellation Control */
  uint8_t measReportConfig_valid;  /**< Must be set to true if measReportConfig is being passed */
  qmiLocGNSSConstellEnumT_v02 measReportConfig;
  /**<   GNSS measurement report constellation control. \n
 Valid values: \n
      - eQMI_SYSTEM_GPS (0x01) --  Enable GPS \n
      - eQMI_SYSTEM_GLO (0x02) --  Enable GLONASS \n
      - eQMI_SYSTEM_BDS (0x04) --  Enable BDS \n
      - eQMI_SYSTEM_GAL (0x08) --  Enable Galileo
 */

  /* Optional */
  /*  SV Polynomial Report Constellation Control */
  uint8_t svPolyReportConfig_valid;  /**< Must be set to true if svPolyReportConfig is being passed */
  qmiLocGNSSConstellEnumT_v02 svPolyReportConfig;
  /**<   SV polynomial report constellation control. \n
 Valid values: \n
      - eQMI_SYSTEM_GPS (0x01) --  Enable GPS \n
      - eQMI_SYSTEM_GLO (0x02) --  Enable GLONASS \n
      - eQMI_SYSTEM_BDS (0x04) --  Enable BDS \n
      - eQMI_SYSTEM_GAL (0x08) --  Enable Galileo
 */
}qmiLocSetGNSSConstRepConfigReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Sets satellite constellations of interest for reporting. */
typedef struct {

  /* Mandatory */
  /*  Set GNSS Constellation Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the GNSS constellation.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */
}qmiLocSetGNSSConstRepConfigIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCSOURCEOFFREQENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_FREQ_SOURCE_INVALID_V02 = 0, /**<  Source of the frequency is invalid  */
  eQMI_LOC_FREQ_SOURCE_EXTERNAL_V02 = 1, /**<  Source of the frequency is from an external injection  */
  eQMI_LOC_FREQ_SOURCE_PE_CLK_REPORT_V02 = 2, /**<  Source of the frequency is from the GNSS navigation engine  */
  eQMI_LOC_FREQ_SOURCE_UNKNOWN_V02 = 3, /**<  Source of the frequency is unknown  */
  QMILOCSOURCEOFFREQENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocSourceofFreqEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  float clockDrift;
  /**<   Receiver clock drift. \n
         - Units: Meters per second
    */

  float clockDriftUnc;
  /**<   Receiver clock frift uncertainty. \n
         - Units: Meters per second
    */

  qmiLocSourceofFreqEnumT_v02 sourceOfFreq;
  /**<   Source of the clock frequency information.

 Valid values: \n
      - eQMI_LOC_FREQ_SOURCE_INVALID (0) --  Source of the frequency is invalid
      - eQMI_LOC_FREQ_SOURCE_EXTERNAL (1) --  Source of the frequency is from an external injection
      - eQMI_LOC_FREQ_SOURCE_PE_CLK_REPORT (2) --  Source of the frequency is from the GNSS navigation engine
      - eQMI_LOC_FREQ_SOURCE_UNKNOWN (3) --  Source of the frequency is unknown
 */
}qmiLocRcvrClockFrequencyInfoStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  uint8_t leapSec;
  /**<   GPS time leap second delta to UTC time.  \n
         For nonzero values of leapSecUnc, leapSec must be treated as unknown. \n
             - Units: Seconds
    */

  uint8_t leapSecUnc;
  /**<   Uncertainty for the GPS leap second. \n
             - Units: Seconds
    */
}qmiLocLeapSecondInfoStructT_v02;  /* Type */
/**
    @}
  */

typedef uint8_t qmiLocInterSystemBiasValidMaskT_v02;
#define QMI_LOC_SYS_TIME_BIAS_VALID_V02 ((qmiLocInterSystemBiasValidMaskT_v02)0x01) /**<  System time bias is valid \n  */
#define QMI_LOC_SYS_TIME_BIAS_UNC_VALID_V02 ((qmiLocInterSystemBiasValidMaskT_v02)0x02) /**<  System time bias uncertainty is valid  */
/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  qmiLocInterSystemBiasValidMaskT_v02 validMask;
  /**<   Fields that are valid. \n
 Valid values: \n
      - QMI_LOC_SYS_TIME_BIAS_VALID (0x01) --  System time bias is valid \n
      - QMI_LOC_SYS_TIME_BIAS_UNC_VALID (0x02) --  System time bias uncertainty is valid  \n
 */

  float timeBias;
  /**<   System 1 to System 2 time bias.  \n
             - Units: Milliseconds
    */

  float timeBiasUnc;
  /**<   System 1 to System 2 time bias uncertainty.  \n
             - Units: Milliseconds
    */
}qmiLocInterSystemBiasStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  qmiLocSvSystemEnumT_v02 system;
  /**<   Specifies the satellite system constellation. */

  uint16_t systemWeek;
  /**<   Current system week. \n
      - For GPS: Calculated from midnight, Jan. 6, 1980 \n
      - For BDS: Calculated from 00:00:00 on January 1, 2006 of Coordinated Universal Time (UTC) \n
      - For GAL: Calculated from 00:00 UT on Sunday August 22, 1999 (midnight between August 21 and August 22) \n
      If the week is unknown, set this value to 65535. \n
       - Units: Weeks */

  uint32_t systemMsec;
  /**<   Amount of time into the current week. \n
       - Units: Milliseconds */

  float systemClkTimeBias;
  /**<   System clock time bias (submilliseconds). \n
            - Units: Milliseconds
        (system time = systemMsec - systemClkTimeBias)
    */

  float systemClkTimeUncMs;
  /**<   Single-sided maximum time bias uncertainty. \n
                - Units: Milliseconds
    */
}qmiLocGnssTimeStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  uint8_t gloFourYear;
  /**<   GLONASS four year number from 1996. Refer to GLONASS ICD. \n
        Applicable only for GLONASS and is to be ignored for other constellations. \n
        If unknown, set this value to 255.
    */

  uint16_t gloDays;
  /**<   GLONASS day number in four years. Refer to GLONASS ICD. \n
        Applicable only for GLONASS and is to be ignored for other constellations. \n
        If unknown, set this value to 65535.
    */

  uint32_t gloMsec;
  /**<   GLONASS time of day in msec. Refer to GLONASS ICD.    \n
        - Units: Milliseconds
    */

  float gloClkTimeBias;
  /**<   System clock time bias (submillisecond). \n
            - Units: Milliseconds
        (system time = systemMsec - systemClkTimeBias)
    */

  float gloClkTimeUncMs;
  /**<   Single-sided maximum time bias uncertainty. \n
                - Units: Milliseconds
    */
}qmiLocGloTimeStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  uint32_t refFCount;
  /**<   Receiver frame counter value at a reference tick. */

  uint8_t systemRtc_valid;
  /**<   Validity indicator for the system RTC. */

  uint64_t systemRtcMs;
  /**<   Platform system RTC value. \n
        - Units: Milliseconds
    */

  qmiLocTimeSourceEnumT_v02 sourceOfTime;
  /**<   Source of the time information.

 Valid values: \n
      - eQMI_LOC_TIME_SRC_INVALID (0) --  Invalid time.
      - eQMI_LOC_TIME_SRC_NETWORK_TIME_TRANSFER (1) --  Time is set by the 1X system
      - eQMI_LOC_TIME_SRC_NETWORK_TIME_TAGGING (2) --  Time is set by WCDMA/GSM time tagging (i.e.,
       associating network time with GPS time)
      - eQMI_LOC_TIME_SRC_EXTERNAL_INPUT (3) --  Time is set by an external injection
      - eQMI_LOC_TIME_SRC_TOW_DECODE (4) --  Time is set after decoding over-the-air GPS navigation data
       from one GPS satellite
      - eQMI_LOC_TIME_SRC_TOW_CONFIRMED (5) --  Time is set after decoding over-the-air GPS navigation data
       from multiple satellites
      - eQMI_LOC_TIME_SRC_TOW_AND_WEEK_CONFIRMED (6) --  Both time of the week and the GPS week number are known
      - eQMI_LOC_TIME_SRC_NAV_SOLUTION (7) --  Time is set by the position engine after the fix is obtained
      - eQMI_LOC_TIME_SRC_SOLVE_FOR_TIME (8) --  Time is set by the position engine after performing SFT;
       this is done when the clock time uncertainty is large
      - eQMI_LOC_TIME_SRC_GLO_TOW_DECODE (9) --  Time is set after decoding GLO satellites
      - eQMI_LOC_TIME_SRC_TIME_TRANSFORM (10) --  Time is set after transforming the GPS to GLO time
      - eQMI_LOC_TIME_SRC_WCDMA_SLEEP_TIME_TAGGING (11) --  Time is set by the sleep time tag provided by the WCDMA network
      - eQMI_LOC_TIME_SRC_GSM_SLEEP_TIME_TAGGING (12) --  Time is set by the sleep time tag provided by the GSM network
      - eQMI_LOC_TIME_SRC_UNKNOWN (13) --  Source of the time is unknown
      - eQMI_LOC_TIME_SRC_SYSTEM_TIMETICK (14) --  Time is derived from the system clock (better known as the slow clock);
       GNSS time is maintained irrespective of the GNSS receiver state
      - eQMI_LOC_TIME_SRC_QZSS_TOW_DECODE (15) --  Time is set after decoding QZSS satellites
      - eQMI_LOC_TIME_SRC_BDS_TOW_DECODE (16) --  Time is set after decoding BDS satellites
 */
}qmiLocGnssTimeExtStructT_v02;  /* Type */
/**
    @}
  */

typedef uint64_t qmiLocSvMeasStatusValidMaskT_v02;
#define QMI_LOC_MASK_MEAS_STATUS_SM_STAT_BIT_VALID_V02 ((qmiLocSvMeasStatusValidMaskT_v02)0x00000001ull) /**<  Satellite time in submilliseconds (code-phase)  */
#define QMI_LOC_MASK_MEAS_STATUS_SB_STAT_BIT_VALID_V02 ((qmiLocSvMeasStatusValidMaskT_v02)0x00000002ull) /**<  Satellite sub-bit time  */
#define QMI_LOC_MASK_MEAS_STATUS_MS_STAT_BIT_VALID_V02 ((qmiLocSvMeasStatusValidMaskT_v02)0x00000004ull) /**<  Satellite time in milliseconds  */
#define QMI_LOC_MASK_MEAS_STATUS_BE_CONFIRM_STAT_BIT_VALID_V02 ((qmiLocSvMeasStatusValidMaskT_v02)0x00000008ull) /**<  Signal bit edge is confirmed  */
#define QMI_LOC_MASK_MEAS_STATUS_VEL_STAT_BIT_VALID_V02 ((qmiLocSvMeasStatusValidMaskT_v02)0x00000010ull) /**<  Satellite Doppler is measured  */
#define QMI_LOC_MASK_MEAS_STATUS_VEL_FINE_STAT_BIT_VALID_V02 ((qmiLocSvMeasStatusValidMaskT_v02)0x00000020ull) /**<  Fine/coarse Doppler measurement indicator  */
#define QMI_LOC_MASK_MEAS_STATUS_FROM_RNG_DIFF_STAT_BIT_VALID_V02 ((qmiLocSvMeasStatusValidMaskT_v02)0x00000200ull) /**<  Range update from satellite differences  */
#define QMI_LOC_MASK_MEAS_STATUS_FROM_VE_DIFF_STAT_BIT_VALID_V02 ((qmiLocSvMeasStatusValidMaskT_v02)0x00000400ull) /**<  Doppler update from satellite differences  */
typedef uint64_t qmiLocSvMeasStatusMaskT_v02;
#define QMI_LOC_MASK_MEAS_STATUS_SM_VALID_V02 ((qmiLocSvMeasStatusMaskT_v02)0x00000001ull) /**<  Satellite time in submilliseconds (code phase) is known  */
#define QMI_LOC_MASK_MEAS_STATUS_SB_VALID_V02 ((qmiLocSvMeasStatusMaskT_v02)0x00000002ull) /**<  Satellite sub-bit time is known  */
#define QMI_LOC_MASK_MEAS_STATUS_MS_VALID_V02 ((qmiLocSvMeasStatusMaskT_v02)0x00000004ull) /**<  Satellite time in milliseconds is known  */
#define QMI_LOC_MASK_MEAS_STATUS_BE_CONFIRM_V02 ((qmiLocSvMeasStatusMaskT_v02)0x00000008ull) /**<  Signal bit edge is confirmed   */
#define QMI_LOC_MASK_MEAS_STATUS_VELOCITY_VALID_V02 ((qmiLocSvMeasStatusMaskT_v02)0x00000010ull) /**<  Satellite Doppler is measured  */
#define QMI_LOC_MASK_MEAS_STATUS_VELOCITY_FINE_V02 ((qmiLocSvMeasStatusMaskT_v02)0x00000020ull) /**<  TRUE: Fine Doppler is measured, FALSE: Coarse Doppler is measured  */
#define QMI_LOC_MASK_MEAS_STATUS_FROM_RNG_DIFF_V02 ((qmiLocSvMeasStatusMaskT_v02)0x00000200ull) /**<  Range update from satellite differences is measured  */
#define QMI_LOC_MASK_MEAS_STATUS_FROM_VE_DIFF_V02 ((qmiLocSvMeasStatusMaskT_v02)0x00000400ull) /**<  Doppler update from satellite differences is measured  */
/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  uint32_t svTimeMs;
  /**<       Satellite time in milliseconds. \n
            - For GPS, BDS, and GAL: Range is 0 thru (604800000-1) \n
            - For GLONASS: Range is 0 thru (86400000-1) \n
            - Units: Milliseconds \vspace{4pt} \n

            This is valid when the QMI_LOC_MEAS_STATUS_MS_VALID bit is set
            in the measurement status. \vspace{4pt} \n

            @note1hang All SV times in the current measurement block are
            alredy propagated to a common reference time epoch. \n
    */

  float svTimeSubMs;
  /**<       Satellite time in submilliseconds. \n
            Total SV Time = svMs + svSubMs \n
                - Units: Milliseconds
    */

  float svTimeUncMs;
  /**<    Satellite time uncertainty. \n
                - Units: Milliseconds
    */

  float dopplerShift;
  /**<   Satellite Doppler. \n
             - Units: Meters per second
    */

  float dopplerShiftUnc;
  /**<   Satellite Doppler uncertainty. \n
             - Units: Meters per second
    */

  uint8_t dopplerAccel_valid;
  /**<   Validity for Doppler acceleration. */

  float dopplerAccel;
  /**<   Satellite Doppler acceleration. \n
             - Units: Hz/second
    */
}qmiLocSVTimeSpeedStructT_v02;  /* Type */
/**
    @}
  */

typedef uint16_t qmiLocMeasFieldsValidMaskT_v02;
#define QMI_LOC_SV_HEALTH_VALID_V02 ((qmiLocMeasFieldsValidMaskT_v02)0x01) /**<  SV health information is valid  */
#define QMI_LOC_SV_MULTIPATH_EST_VALID_V02 ((qmiLocMeasFieldsValidMaskT_v02)0x02) /**<  Multipath estimate for SV is valid  */
#define QMI_LOC_SV_FINE_SPEED_VALID_V02 ((qmiLocMeasFieldsValidMaskT_v02)0x04) /**<  Fine speed for SV is valid  */
#define QMI_LOC_SV_FINE_SPEED_UNC_VALID_V02 ((qmiLocMeasFieldsValidMaskT_v02)0x08) /**<  Fine speed uncertainty for SV is valid  */
#define QMI_LOC_SV_CARRIER_PHASE_VALID_V02 ((qmiLocMeasFieldsValidMaskT_v02)0x10) /**<  Carrier phase for SV is valid  */
#define QMI_LOC_SV_SV_DIRECTION_VALID_V02 ((qmiLocMeasFieldsValidMaskT_v02)0x20) /**<  SV direction information for SV is valid  */
#define QMI_LOC_SV_CYCLESLIP_COUNT_VALID_V02 ((qmiLocMeasFieldsValidMaskT_v02)0x40) /**<  Cycle slip count information is valid  */
#define QMI_LOC_SV_LOSSOFLOCK_VALID_V02 ((qmiLocMeasFieldsValidMaskT_v02)0x80) /**<  Loss of lock information is valid  */
/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  uint16_t gnssSvId;
  /**<   GNSS SV ID.
       \begin{itemize1}
       \item    Range: \begin{itemize1}
         \item    For GPS:     1 to 32
         \item    For SBAS:    33 to 64
         \item    For GLONASS: 65 to 96. When slot-number to SV ID mapping is unknown, set as 255.
         \item    For BDS:     201 to 237
       \vspace{-0.18in} \end{itemize1} \end{itemize1} */

  uint8_t gloFrequency;
  /**<   GLONASS frequency number + 7. \n
         Valid only for a GLONASS system and
         is to be ignored for all other systems. \n
             - Range: 1 to 14
    */

  qmiLocSvStatusEnumT_v02 svStatus;
  /**<   Satellite search state.

 Valid values: \n
      - eQMI_LOC_SV_STATUS_IDLE (1) --  SV is not being actively processed
      - eQMI_LOC_SV_STATUS_SEARCH (2) --  The system is searching for this SV
      - eQMI_LOC_SV_STATUS_TRACK (3) --  SV is being tracked
 */

  qmiLocMeasFieldsValidMaskT_v02 validMask;
  /**<   Validity mask (0 = Not valid; 1 = Valid). \n

      - QMI_LOC_SV_HEALTH_VALID (0x01) --  SV health information is valid
      - QMI_LOC_SV_MULTIPATH_EST_VALID (0x02) --  Multipath estimate for SV is valid
      - QMI_LOC_SV_FINE_SPEED_VALID (0x04) --  Fine speed for SV is valid
      - QMI_LOC_SV_FINE_SPEED_UNC_VALID (0x08) --  Fine speed uncertainty for SV is valid
      - QMI_LOC_SV_CARRIER_PHASE_VALID (0x10) --  Carrier phase for SV is valid
      - QMI_LOC_SV_SV_DIRECTION_VALID (0x20) --  SV direction information for SV is valid
      - QMI_LOC_SV_CYCLESLIP_COUNT_VALID (0x40) --  Cycle slip count information is valid
      - QMI_LOC_SV_LOSSOFLOCK_VALID (0x80) --  Loss of lock information is valid
 */

  uint8_t healthStatus;
  /**<   Health status. \n
         \begin{itemize1}
         - Range: 0 to 1, where  0 = unhealthy, 1 = healthy
    */

  qmiLocSvInfoMaskT_v02 svInfoMask;
  /**<   Indicates whether almanac and ephemeris information is available.

 Valid values: \n
      - QMI_LOC_SVINFO_MASK_HAS_EPHEMERIS (0x01) --  Ephemeris is available for this SV
      - QMI_LOC_SVINFO_MASK_HAS_ALMANAC (0x02) --  Almanac is available for this SV
 */

  qmiLocSvMeasStatusValidMaskT_v02 validMeasStatusMask;
  /**<   Validity mask for measurement status information. \n
 A set bit in validMeasStatusMask indicates that the corresponding bit
 in measurementStatus has valid status information: \n
 Valid masks: \n
      - QMI_LOC_MASK_MEAS_STATUS_SM_STAT_BIT_VALID (0x00000001) --  Satellite time in submilliseconds (code-phase)
      - QMI_LOC_MASK_MEAS_STATUS_SB_STAT_BIT_VALID (0x00000002) --  Satellite sub-bit time
      - QMI_LOC_MASK_MEAS_STATUS_MS_STAT_BIT_VALID (0x00000004) --  Satellite time in milliseconds
      - QMI_LOC_MASK_MEAS_STATUS_BE_CONFIRM_STAT_BIT_VALID (0x00000008) --  Signal bit edge is confirmed
      - QMI_LOC_MASK_MEAS_STATUS_VEL_STAT_BIT_VALID (0x00000010) --  Satellite Doppler is measured
      - QMI_LOC_MASK_MEAS_STATUS_VEL_FINE_STAT_BIT_VALID (0x00000020) --  Fine/coarse Doppler measurement indicator
      - QMI_LOC_MASK_MEAS_STATUS_FROM_RNG_DIFF_STAT_BIT_VALID (0x00000200) --  Range update from satellite differences
      - QMI_LOC_MASK_MEAS_STATUS_FROM_VE_DIFF_STAT_BIT_VALID (0x00000400) --  Doppler update from satellite differences
\vspace{4pt}
 Additionally, MSB 0xFFC0000000000000 bits indicate the validity of DONT_USE bits. \n

 */

  qmiLocSvMeasStatusMaskT_v02 measurementStatus;
  /**<   Bitmask indicating the SV measurement status.

 Valid bitmasks: \n
      - QMI_LOC_MASK_MEAS_STATUS_SM_VALID (0x00000001) --  Satellite time in submilliseconds (code phase) is known
      - QMI_LOC_MASK_MEAS_STATUS_SB_VALID (0x00000002) --  Satellite sub-bit time is known
      - QMI_LOC_MASK_MEAS_STATUS_MS_VALID (0x00000004) --  Satellite time in milliseconds is known
      - QMI_LOC_MASK_MEAS_STATUS_BE_CONFIRM (0x00000008) --  Signal bit edge is confirmed
      - QMI_LOC_MASK_MEAS_STATUS_VELOCITY_VALID (0x00000010) --  Satellite Doppler is measured
      - QMI_LOC_MASK_MEAS_STATUS_VELOCITY_FINE (0x00000020) --  TRUE: Fine Doppler is measured, FALSE: Coarse Doppler is measured
      - QMI_LOC_MASK_MEAS_STATUS_FROM_RNG_DIFF (0x00000200) --  Range update from satellite differences is measured
      - QMI_LOC_MASK_MEAS_STATUS_FROM_VE_DIFF (0x00000400) --  Doppler update from satellite differences is measured

 If any MSB bit in 0xFFC0000000000000 DONT_USE is set, the measurement
 must not be used by the client.
 */

  uint16_t CNo;
  /**<   Carrier to noise ratio.  \n
             - Units: dBHz \n
             - Scale: 0.1
    */

  uint16_t gloRfLoss;
  /**<   GLONASS RF loss reference to the antenna. \n
                 - Units: dB \n
                 - Scale: 0.1
    */

  int32_t measLatency;
  /**<   Age of the measurement. A positive value means the measurement precedes the reference time. \n
                 - Units: Milliseconds
    */

  qmiLocSVTimeSpeedStructT_v02 svTimeSpeed;
  /**<   SV time and speed information. */

  uint8_t lossOfLock;
  /**<   Loss of signal lock indicator.  \n
             - 0: Signal is in continuous track \n
             - 1: Signal is not in track
    */

  float multipathEstimate;
  /**<   Estimate of multipath in a measurement. \n
             - Units: Meters
    */

  float fineSpeed;
  /**<   Carrier phase derived speed. \n
             - Units: Meters per second
    */

  float fineSpeedUnc;
  /**<   Carrier phase derived speed uncertainty. \n
             - Units: Meters per second
    */

  double carrierPhase;
  /**<   Carrier phase measurement (L1 cycles).
    */

  uint8_t cycleSlipCount;
  /**<   Increments when a cycle slip is detected. */

  float svAzimuth;
  /**<   Satellite azimuth. \n
                - Units: Radians \n
                - Range: 0 to 2*pi()
    */

  float svElevation;
  /**<   Satellite elevation. \n
                - Units: Radians \n
                - Range: 0 to pi()/2
    */
}qmiLocSVMeasurementStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Sends a satellite measurement report to the control point. */
typedef struct {

  /* Mandatory */
  /*  Current Message Sequence Number  */
  uint8_t seqNum;
  /**<   Current message number. Used for segmentation/assembly of measurement reports. */

  /* Mandatory */
  /*  Maximum Number of Messages to be Sent for Present Time Epoch */
  uint8_t maxMessageNum;
  /**<   Maximum number of messages that are to be sent for the present time epoch. */

  /* Mandatory */
  /*   Specifies Satellite System Constellation of This Report */
  qmiLocSvSystemEnumT_v02 system;
  /**<   Specifies the satellite system constellation of this report.

 Valid values: \n
      - eQMI_LOC_SV_SYSTEM_GPS (1) --  GPS satellite
      - eQMI_LOC_SV_SYSTEM_GALILEO (2) --  GALILEO satellite
      - eQMI_LOC_SV_SYSTEM_SBAS (3) --  SBAS satellite
      - eQMI_LOC_SV_SYSTEM_COMPASS (4) --  COMPASS satellite
      - eQMI_LOC_SV_SYSTEM_GLONASS (5) --  GLONASS satellite
      - eQMI_LOC_SV_SYSTEM_BDS (6) --  BDS satellite
 */

  /* Optional */
  /*  GNSS Receiver Clock Frequency Information */
  uint8_t rcvrClockFrequencyInfo_valid;  /**< Must be set to true if rcvrClockFrequencyInfo is being passed */
  qmiLocRcvrClockFrequencyInfoStructT_v02 rcvrClockFrequencyInfo;

  /* Optional */
  /*  Leap Second Information */
  uint8_t leapSecondInfo_valid;  /**< Must be set to true if leapSecondInfo is being passed */
  qmiLocLeapSecondInfoStructT_v02 leapSecondInfo;

  /* Optional */
  /*  GPS to GLONASS Intersystem Time Bias */
  uint8_t gpsGloInterSystemBias_valid;  /**< Must be set to true if gpsGloInterSystemBias is being passed */
  qmiLocInterSystemBiasStructT_v02 gpsGloInterSystemBias;
  /**<   \vspace{4pt} \n
       This is reported if both GPS and GLONASS system
       information reporting are enabled. \n
       - System 1: GPS \n
       - System 2: GLONASS
  */

  /* Optional */
  /*  GPS to BDS Intersystem Time Bias */
  uint8_t gpsBdsInterSystemBias_valid;  /**< Must be set to true if gpsBdsInterSystemBias is being passed */
  qmiLocInterSystemBiasStructT_v02 gpsBdsInterSystemBias;
  /**<   \vspace{4pt} \n
       This is reported if both GPS and BDS system
       information reporting are enabled. \n
       - System 1: GPS \n
       - System 2: BDS
  */

  /* Optional */
  /*  GPS to GALILEO Intersystem Time Bias */
  uint8_t gpsGalInterSystemBias_valid;  /**< Must be set to true if gpsGalInterSystemBias is being passed */
  qmiLocInterSystemBiasStructT_v02 gpsGalInterSystemBias;
  /**<   \vspace{4pt} \n
       This is reported if both GPS and GALILEO system
       information reporting are enabled. \n
       - System 1: GPS \n
       - System 2: GALILEO
  */

  /* Optional */
  /*  BDS to GLONASS Intersystem Time Bias */
  uint8_t bdsGloInterSystemBias_valid;  /**< Must be set to true if bdsGloInterSystemBias is being passed */
  qmiLocInterSystemBiasStructT_v02 bdsGloInterSystemBias;
  /**<   \vspace{4pt} \n
       This is reported if both BDS and GLONASS system
       information reporting are enabled. \n
       - System 1: BDS \n
       - System 2: GLONASS
  */

  /* Optional */
  /*  GAL to GLONASS Intersystem Time Bias */
  uint8_t galGloInterSystemBias_valid;  /**< Must be set to true if galGloInterSystemBias is being passed */
  qmiLocInterSystemBiasStructT_v02 galGloInterSystemBias;
  /**<   \vspace{4pt} \n
       This is reported if both GAL and GLONASS system
       information reporting are enabled. \n
       - System 1: GAL \n
       - System 2: GLONASS
  */

  /* Optional */
  /*  GAL to BDS Intersystem Time Bias */
  uint8_t galBdsInterSystemBias_valid;  /**< Must be set to true if galBdsInterSystemBias is being passed */
  qmiLocInterSystemBiasStructT_v02 galBdsInterSystemBias;
  /**<   \vspace{4pt} \n
       This is reported if both GAL and BDS system
       information reporting are enabled. \n
       - System 1: GAL \n
       - System 2: BDS
  */

  /* Optional */
  /*  Satellite System Time Information for GPS, BDS, GAL Constellation */
  uint8_t systemTime_valid;  /**< Must be set to true if systemTime is being passed */
  qmiLocGnssTimeStructT_v02 systemTime;

  /* Optional */
  /*  GLONASS System Time Information */
  uint8_t gloTime_valid;  /**< Must be set to true if gloTime is being passed */
  qmiLocGloTimeStructT_v02 gloTime;

  /* Optional */
  /*  Extended Time Information */
  uint8_t systemTimeExt_valid;  /**< Must be set to true if systemTimeExt is being passed */
  qmiLocGnssTimeExtStructT_v02 systemTimeExt;

  /* Optional */
  /*  Satellite System Measurement Report for Enabled Constellation */
  uint8_t svMeasurement_valid;  /**< Must be set to true if svMeasurement is being passed */
  uint32_t svMeasurement_len;  /**< Must be set to # of elements in svMeasurement */
  qmiLocSVMeasurementStructT_v02 svMeasurement[QMI_LOC_SV_MEAS_LIST_MAX_SIZE_V02];
}qmiLocEventGnssSvMeasInfoIndMsgT_v02;  /* Message */
/**
    @}
  */

typedef uint16_t qmiLocSvPolyStatusMaskT_v02;
#define QMI_LOC_SV_POLY_SRC_ALM_CORR_V02 ((qmiLocSvPolyStatusMaskT_v02)0x01) /**<  Polynomials based on XTRA  */
#define QMI_LOC_SV_POLY_GLO_STR4_V02 ((qmiLocSvPolyStatusMaskT_v02)0x02) /**<  GLONASS string 4 has been received  */
typedef uint16_t qmiLocSvPolyStatusMaskValidityT_v02;
#define QMI_LOC_SV_POLY_SRC_ALM_CORR_VALID_V02 ((qmiLocSvPolyStatusMaskValidityT_v02)0x01) /**<  Validity status for QMI_LOC_SV_POLY_SRC_ALM_CORR  */
#define QMI_LOC_SV_POLY_GLO_STR4_VALID_V02 ((qmiLocSvPolyStatusMaskValidityT_v02)0x02) /**<  Validity status for QMI_LOC_SV_POLY_GLO_STR4   */
/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Sends a satellite polynomial report to the control point. */
typedef struct {

  /* Mandatory */
  /*  GNSS SV Polynomial Report */
  uint16_t gnssSvId;
  /**<   GNSS SV ID. \begin{itemize1}
       \item    Range:    \begin{itemize1}
         \item    For GPS:     1 to 32
         \item    For SBAS:    33 to 64
         \item    For GLONASS: 65 to 96 (when the slot number to SV ID mapping is unknown, set to 255)
         \item    For BDS:     201 to 237
       \vspace{-0.18in} \end{itemize1} \end{itemize1} */

  /* Mandatory */
  /*  Reference Time for Polynomial Calculations */
  double T0;
  /**<    Reference time for polynomial calculations. \n
           - GPS: Seconds in the week \n
           - GLO: Full seconds since Jan. 1, 1996 \n
           - BDS: Full seconds since Jan. 1, 2006
    */

  /* Mandatory */
  /*  SV Polynomial Validity Status */
  qmiLocSvPolyStatusMaskValidityT_v02 svPolyFlagValid;
  /**<   Validity mask for bits in svPolyFlags. A set bit in svPolyFlagValid indicates that a
 corresponding bit in svPolyFlags has valid status information.

 Valid bitmasks: \n
      - QMI_LOC_SV_POLY_SRC_ALM_CORR_VALID (0x01) --  Validity status for QMI_LOC_SV_POLY_SRC_ALM_CORR
      - QMI_LOC_SV_POLY_GLO_STR4_VALID (0x02) --  Validity status for QMI_LOC_SV_POLY_GLO_STR4   */

  /* Mandatory */
  /*  SV Polynomial Report Status */
  qmiLocSvPolyStatusMaskT_v02 svPolyFlags;
  /**<   Flags indicating the status of a polynomial report.

 Valid bitmasks: \n
      - QMI_LOC_SV_POLY_SRC_ALM_CORR (0x01) --  Polynomials based on XTRA
      - QMI_LOC_SV_POLY_GLO_STR4 (0x02) --  GLONASS string 4 has been received  */

  /* Optional */
  /*  Polynomial Coefficient's 0th Term for X, Y, and Z Coordinates */
  uint8_t polyCoeffXYZ0_valid;  /**< Must be set to true if polyCoeffXYZ0 is being passed */
  double polyCoeffXYZ0[QMI_LOC_SV_POLY_XYZ_0_TH_ORDER_COEFF_SIZE_V02];
  /**<   Polynomial coefficient's 0th term for X, Y, and Z coordinates (C0X, C0Y, C0Z). \n
             - Units: Meters
    */

  /* Optional */
  /*  Polynomial Coefficient's 1st, 2nd, and 3rd Terms for X, Y, and Z Coordinates */
  uint8_t polyCoefXYZN_valid;  /**< Must be set to true if polyCoefXYZN is being passed */
  double polyCoefXYZN[QMI_LOC_SV_POLY_XYZ_N_TH_ORDER_COEFF_SIZE_V02];
  /**<    Polynomial coefficient's 1st, 2nd, and 3rd terms for X, Y, and Z coordinates (C1X, C2X,... C2Z, C3Z). \begin{itemize1}
          \item Units: \begin{itemize1}
             \item 1st term -- Meters/second
             \item 2nd term -- Meters/second^2
             \item 3rd term -- Meters/seconds^3 \vspace{-0.18in} \end{itemize1} end{itemize1}
    */

  /* Optional */
  /*  Polynomial Coefficients for Satellite Clock Bias Correction */
  uint8_t polyCoefClockBias_valid;  /**< Must be set to true if polyCoefClockBias is being passed */
  float polyCoefClockBias[QMI_LOC_SV_POLY_SV_CLKBIAS_COEFF_SIZE_V02];
  /**<    Polynomial coefficients for satellite clock bias correction (C0T, C1T, C2T, C3T). \begin{itemize1}
          \item Units: \begin{itemize1}
             \item 0th term -- Milliseconds/second
             \item 1st term -- Milliseconds/second^2
             \item 2nd term -- Milliseconds/second^3
             \item 3rd term -- Milliseconds/second^4 \vspace{-0.18in} \end{itemize1} end{itemize1}
    */

  /* Optional */
  /*  GLONASS Frequency Number */
  uint8_t gloFrequency_valid;  /**< Must be set to true if gloFrequency is being passed */
  uint8_t gloFrequency;
  /**<   GLONASS frequency number + 7. \n
         Valid only for GLONASS systems and
         must be ignored for all other systems. \n
             - Range: 1 to 14
    */

  /* Optional */
  /*  Ephemeris Reference Time */
  uint8_t IODE_valid;  /**< Must be set to true if IODE is being passed */
  uint16_t IODE;
  /**<   Ephemeris reference time. \n
         - GPS -- Issue of data ephemeris used (unitless) \n
         - GLONASS -- Tb 7-bit
    */

  /* Optional */
  /*  Enhanced Reference Time */
  uint8_t enhancedIOD_valid;  /**< Must be set to true if enhancedIOD is being passed */
  uint32_t enhancedIOD;
  /**<   For BDS ephemeris, this is TOE.
    */

  /* Optional */
  /*  SV Position Uncertainty */
  uint8_t svPosUnc_valid;  /**< Must be set to true if svPosUnc is being passed */
  float svPosUnc;
  /**<    SV position uncertainty. \n
             - Units: Meters
    */

  /* Optional */
  /*  Iono Delay */
  uint8_t ionoDelay_valid;  /**< Must be set to true if ionoDelay is being passed */
  float ionoDelay;
  /**<   Ionospheric delay at T0. \n
             - Units: Meters
    */

  /* Optional */
  /*  Iono Delay Rate */
  uint8_t ionoDot_valid;  /**< Must be set to true if ionoDot is being passed */
  float ionoDot;
  /**<   Ionospheric delay rate. \n
             - Units: Meters/second
    */

  /* Optional */
  /*  SBAS Iono Delay */
  uint8_t sbasIonoDelay_valid;  /**< Must be set to true if sbasIonoDelay is being passed */
  float sbasIonoDelay;
  /**<   SBAS ionospheric delay at T0. \n
             - Units: Meters
    */

  /* Optional */
  /*  SBAS Iono Delay Rate */
  uint8_t sbasIonoDot_valid;  /**< Must be set to true if sbasIonoDot is being passed */
  float sbasIonoDot;
  /**<   SBAS ionospheric delay rate. \n
             - Units: Meters/second
    */

  /* Optional */
  /*  Tropospheric Delay */
  uint8_t tropoDelay_valid;  /**< Must be set to true if tropoDelay is being passed */
  float tropoDelay;
  /**<   Tropospheric delay. \n
             - Units: Meters
    */

  /* Optional */
  /*  Satellite Elevation */
  uint8_t elevation_valid;  /**< Must be set to true if elevation is being passed */
  float elevation;
  /**<   Satellite elevation at T0. \n
             - Units: Radians
    */

  /* Optional */
  /*  Satellite Elevation Rate */
  uint8_t elevationDot_valid;  /**< Must be set to true if elevationDot is being passed */
  float elevationDot;
  /**<   Satellite elevation rate. \n
             - Units: Radians/second
    */

  /* Optional */
  /*  Satellite Elevation Uncertainty */
  uint8_t elenationUnc_valid;  /**< Must be set to true if elenationUnc is being passed */
  float elenationUnc;
  /**<   SV elevation uncertainty. \n
             - Units: Radians
    */

  /* Optional */
  /*  Polynomial Coefficients for SV Velocity */
  uint8_t velCoef_valid;  /**< Must be set to true if velCoef is being passed */
  double velCoef[QMI_LOC_SV_POLY_VELOCITY_COEF_SIZE_V02];
  /**<   Polynomial coefficients for SV velocity (C0X, C1X, C2X, C3X,... C2Z, C3Z). \begin{itemize1}
         \item Units: \begin{itemize1}
            \item 0th term -- Meters/second
            \item 1st term -- Meters/second^2
            \item 2nd term -- Meters/second^3
            \item 3rd term -- Meters/second^4 \vspace{-0.18in} \end{itemize1} end{itemize1}
    */
}qmiLocEventGnssSvPolyIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  uint8_t wifiApMacAddress[QMI_LOC_WIFI_MAC_ADDR_LENGTH_V02];
  /**<   MAC address of the Wi-Fi AP. */
}qmiLocWifiApMacAddressStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_aggregates
    @{
  */
typedef struct {

  char uuid[QMI_LOC_MAX_IBEACON_UUID_STR_LENGTH_V02 + 1];
  /**<   NULL-terminated IBeacon identifier string; a 128-bit value. */

  uint32_t majorNumber;
  /**<   IBeacon major number.*/

  uint32_t minorNumber;
  /**<   IBeacon minor number.*/
}qmiLocIBeaconIdStructT_v02;  /* Type */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Used by the control point to inject the Geofence context. */
typedef struct {

  /* Mandatory */
  /*  Transaction ID */
  uint32_t transactionId;
  /**<   Identifies the transaction. The transaction ID
       is returned in the Add Geofence Context indication. */

  /* Optional */
  /*  Geofence ID */
  uint8_t geofenceId_valid;  /**< Must be set to true if geofenceId is being passed */
  uint32_t geofenceId;
  /**<   Geofence identifier allocated by the engine.    \n
       If the Geofence ID is not provided, a Geofence is created with an Area ID
       list only (e.g., Wi-Fi only list Geofence). \n
       If the Geofence ID is provided, the added list is used as assistance data
       to the existing Geofence. */

  /* Optional */
  /*  Wi-Fi AP SSID String */
  uint8_t wifiApSsidInfo_valid;  /**< Must be set to true if wifiApSsidInfo is being passed */
  uint32_t wifiApSsidInfo_len;  /**< Must be set to # of elements in wifiApSsidInfo */
  qmiLocWifiApSsidStructT_v02 wifiApSsidInfo[QMI_LOC_WIFI_AREA_ID_LIST_LENGTH_V02];
  /**<   \vspace{4pt} \n The ordering of the Wi-Fi AP SSID list should match the Wi-Fi AP MAC address
       list when both are provided,
       i.e., the first element of the Wi-Fi AP SSID list must be the SSID of the AP whose MAC
       address is in the first element in the Wi-Fi AP MAC address, etc.  */

  /* Optional */
  /*  Wi-Fi AP MAC Address List for the Geofence */
  uint8_t wifiApMacAddressList_valid;  /**< Must be set to true if wifiApMacAddressList is being passed */
  uint32_t wifiApMacAddressList_len;  /**< Must be set to # of elements in wifiApMacAddressList */
  qmiLocWifiApMacAddressStructT_v02 wifiApMacAddressList[QMI_LOC_WIFI_AREA_ID_LIST_LENGTH_V02];
  /**<   The ordering of the Wi-Fi AP SSID list should match the Wi-Fi AP MAC address
       list when both are provided,
       i.e., the first element of the Wi-Fi AP SSID list must be the SSID of the AP whose MAC
       address is in the first element in the Wi-Fi AP MAC address, etc.  */

  /* Optional */
  /*  TDSCDMA Cell ID List for the Geofence */
  uint8_t tdsCdmaCellIDList_valid;  /**< Must be set to true if tdsCdmaCellIDList is being passed */
  qmiLocTDSCDMACellIdStructT_v02 tdsCdmaCellIDList[QMI_LOC_CELL_ID_LIST_LENGTH_V02];
  /**<   \n Identifies the TDSCDMA cell on which the device is currently camped. */

  /* Optional */
  /*  WCDMA Cell ID List for the Geofence */
  uint8_t wcdmaCellIDList_valid;  /**< Must be set to true if wcdmaCellIDList is being passed */
  uint32_t wcdmaCellIDList_len;  /**< Must be set to # of elements in wcdmaCellIDList */
  qmiLocWCDMACellIdStructT_v02 wcdmaCellIDList[QMI_LOC_CELL_ID_LIST_LENGTH_V02];
  /**<   \n Identifies the WCDMA cell on which the device is currently camped. */

  /* Optional */
  /*  GSM Cell ID List for the Geofence */
  uint8_t gsmCellIDList_valid;  /**< Must be set to true if gsmCellIDList is being passed */
  uint32_t gsmCellIDList_len;  /**< Must be set to # of elements in gsmCellIDList */
  qmiLocGSMCellIdStructT_v02 gsmCellIDList[QMI_LOC_CELL_ID_LIST_LENGTH_V02];
  /**<   \n Identifies the GSM cell on which the device is currently camped. */

  /* Optional */
  /*  IBeacon List of the Geofence */
  uint8_t iBeaconList_valid;  /**< Must be set to true if iBeaconList is being passed */
  uint32_t iBeaconList_len;  /**< Must be set to # of elements in iBeaconList */
  qmiLocIBeaconIdStructT_v02 iBeaconList[QMI_LOC_IBEACON_LIST_LENGTH_V02];
}qmiLocAddGeofenceContextReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Used by the control point to inject the Geofence context. */
typedef struct {

  /* Mandatory */
  /*  Status of the Add Geofence Context Request */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Add Geofence Context request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */

  /* Optional */
  /*  Transaction ID */
  uint8_t transactionId_valid;  /**< Must be set to true if transactionId is being passed */
  uint32_t transactionId;
  /**<   Transaction ID that was specified in the Add Geofence Context
       request. This parameter is always present
       if the status field is set to SUCCESS. */

  /* Optional */
  /*  Geofence ID */
  uint8_t geofenceId_valid;  /**< Must be set to true if geofenceId is being passed */
  uint32_t geofenceId;
  /**<   Geofence identifier allocated by the engine.    \n
       If the client specifies the Geofence ID during the Add Geofence Context request,
       the same ID is returned.    \n
       If the client does not specify the Geofence ID during the Add Geofence Context request,
       a new Geofence ID is created by the Geofence engine and returned. */

  /* Optional */
  /*  Context ID */
  uint8_t contextId_valid;  /**< Must be set to true if contextId is being passed */
  uint32_t contextId;
  /**<   Geofence context ID allocated by the engine.
       The context ID is generated by the Geofence engine to identify the context
       for a particular Geofence ID.
       The same Geofence ID may be associated with multiple contexts.  */
}qmiLocAddGeofenceContextIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Used by the control point to inject the Geofence engine context. */
typedef struct {

  /* Mandatory */
  /*  Transaction ID */
  uint32_t transactionId;
  /**<   Identifies the transaction. The transaction ID
       is returned in the Set Geofence Engine Context indication. */

  /* Optional */
  /*  UTC Timestamp of the Day */
  uint8_t utcTimeOfDay_valid;  /**< Must be set to true if utcTimeOfDay is being passed */
  uint64_t utcTimeOfDay;
  /**<   The UTC time of the day.  */

  /* Optional */
  /*  Temperature of the Day in Fahrenheit */
  uint8_t temperature_valid;  /**< Must be set to true if temperature is being passed */
  int32_t temperature;
  /**<   The temperature of the day in degrees Fahrenheit.  */
}qmiLocSetGeofenceEngineContextReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Used by the control point to inject the Geofence engine context. */
typedef struct {

  /* Mandatory */
  /*  Status of the Set Geofence Engine Context Request */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Set Geofence Engine Context request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */

  /* Optional */
  /*  Transaction ID */
  uint8_t transactionId_valid;  /**< Must be set to true if transactionId is being passed */
  uint32_t transactionId;
  /**<   Transaction ID that was specified in the Set Geofence Engine Context
       request. This parameter will always be present
       if the status field is set to SUCCESS. */
}qmiLocSetGeofenceEngineContextIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Used by the control point to Delete the geofence context. */
typedef struct {

  /* Mandatory */
  /*  Transaction ID */
  uint32_t transactionId;
  /**<   Identifies the transaction. The transaction ID
       is returned in the Delete Geofence Context indication. */

  /* Mandatory */
  /*  Geofence ID */
  uint32_t geofenceId;
  /**<   Identifies the Geofence whose context is to be deleted.  */

  /* Optional */
  /*  Context ID */
  uint8_t contextId_valid;  /**< Must be set to true if contextId is being passed */
  uint32_t contextId;
  /**<   Identifies the context associated with the Geofence to be deleted.
       If not specified, all contexts associated with this Geofence are deleted. */
}qmiLocDeleteGeofenceContextReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Used by the control point to Delete the geofence context. */
typedef struct {

  /* Mandatory */
  /*  Status of the Delete Geofence Context Request */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the Delete Geofence Context request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */

  /* Optional */
  /*  Transaction ID */
  uint8_t transactionId_valid;  /**< Must be set to true if transactionId is being passed */
  uint32_t transactionId;
  /**<   Transaction ID that was specified in the Delete Geofence Context request.
       This parameter will always be present
       if the status field is set to SUCCESS. */

  /* Optional */
  /*  Geofence ID */
  uint8_t geofenceId_valid;  /**< Must be set to true if geofenceId is being passed */
  uint32_t geofenceId;
  /**<   Identifier for the Geofence whose context was deleted. */

  /* Optional */
  /*  Context ID */
  uint8_t contextId_valid;  /**< Must be set to true if contextId is being passed */
  uint32_t contextId;
  /**<   Identifier for the context of the Geofence that was deleted. */
}qmiLocDeleteGeofenceContextIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Injects GTP WWAN client downloaded data. */
typedef struct {

  /* Mandatory */
  /*  Data */
  uint32_t ClientDownloadedData_len;  /**< Must be set to # of elements in ClientDownloadedData */
  char ClientDownloadedData[QMI_LOC_MAX_GTP_WWAN_CLIENT_DOWNLOADED_DATA_LEN_V02];
  /**<   WWAN client downloaded data. \n
         - Type: Array of bytes \n
         - Maximum length of the array: 512
    */
}qmiLocInjectGtpClientDownloadedDataReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Injects GTP WWAN client downloaded data. */
typedef struct {

  /* Mandatory */
  /*  GTP client downloaded data injection Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the GTP client downloaded data injection.
 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */
}qmiLocInjectGtpClientDownloadedDataIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Sends a GDT upload begin response to GDT MP. */
typedef struct {

  /* Mandatory */
  /*  GDT service ID */
  qmiLocGdtServiceIdEnumT_v02 serviceId;

  /* Mandatory */
  /*  Session ID */
  uint32_t sessionId;

  /* Mandatory */
  /*  Access status to GDT */
  qmiLocGdtAccessStatusEnumT_v02 gdtAccessStatus;
  /**<   GDT status information for this serviceId.

 Valid values: \n
      - eQMI_LOC_GDT_ACCESS_ALLOWED (1) --  GDT ACCESS to the service is allowed
      - eQMI_LOC_GDT_ACCESS_FAILED (2) --  Any type of GDT access error
      - eQMI_LOC_GDT_ACCESS_NOT_ALLOWED (3) --  GDT ACCESS to the service is not allowed
 */
}qmiLocGdtUploadBeginStatusReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Sends a GDT upload begin response to GDT MP. */
typedef struct {

  /* Mandatory */
  /*  GDT upload begin Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the GDT begin request.
 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */
}qmiLocGdtUploadBeginStatusIndMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_enums
    @{
  */
typedef enum {
  QMILOCGDTENDACKENUMT_MIN_ENUM_VAL_V02 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  eQMI_LOC_GDT_ACK_SUCCESS_V02 = 1, /**<  The sent data is accepeted   */
  eQMI_LOC_GDT_ACK_FAILED_V02 = 2, /**<  The sent data was not accepted   */
  eQMI_LOC_GDT_ACK_INVALID_V02 = 3, /**<  General error in received data  */
  QMILOCGDTENDACKENUMT_MAX_ENUM_VAL_V02 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}qmiLocGdtEndAckEnumT_v02;
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Request Message; Sends a GDT upload end response to GDT MP. */
typedef struct {

  /* Mandatory */
  /*  GDT service ID */
  qmiLocGdtServiceIdEnumT_v02 serviceId;

  /* Mandatory */
  /*  Session ID */
  uint32_t sessionId;

  /* Mandatory */
  /*  Access status to GDT */
  qmiLocGdtEndAckEnumT_v02 gdtEndStatus;
  /**<   GDT end status information for this serviceId.

 Valid values: \n
      - eQMI_LOC_GDT_ACK_SUCCESS (1) --  The sent data is accepeted
      - eQMI_LOC_GDT_ACK_FAILED (2) --  The sent data was not accepted
      - eQMI_LOC_GDT_ACK_INVALID (3) --  General error in received data
 */
}qmiLocGdtUploadEndReqMsgT_v02;  /* Message */
/**
    @}
  */

/** @addtogroup loc_qmi_messages
    @{
  */
/** Indication Message; Sends a GDT upload end response to GDT MP. */
typedef struct {

  /* Mandatory */
  /*  UTC GDP upload end Status */
  qmiLocStatusEnumT_v02 status;
  /**<   Status of the GDT upload end request.

 Valid values: \n
      - eQMI_LOC_SUCCESS (0) --  Request was completed successfully \n
      - eQMI_LOC_GENERAL_FAILURE (1) --  Request failed because of a general failure \n
      - eQMI_LOC_UNSUPPORTED (2) --  Request failed because it is not supported \n
      - eQMI_LOC_INVALID_PARAMETER (3) --  Request failed because it contained invalid parameters \n
      - eQMI_LOC_ENGINE_BUSY (4) --  Request failed because the engine is busy \n
      - eQMI_LOC_PHONE_OFFLINE (5) --  Request failed because the phone is offline \n
      - eQMI_LOC_TIMEOUT (6) --  Request failed because it timed out \n
      - eQMI_LOC_CONFIG_NOT_SUPPORTED (7) --  Request failed because an undefined configuration was requested \n
      - eQMI_LOC_INSUFFICIENT_MEMORY (8) --  Request failed because the engine could not allocate sufficient memory for the request \n
      - eQMI_LOC_MAX_GEOFENCE_PROGRAMMED (9) --  Request failed because the maximum number of Geofences are already programmed \n
      - eQMI_LOC_XTRA_VERSION_CHECK_FAILURE (10) --  Location service failed because of an XTRA version-based file format check failure
 */
}qmiLocGdtUploadEndIndMsgT_v02;  /* Message */
/**
    @}
  */

/* Conditional compilation tags for message removal */
//#define REMOVE_QMI_LOC_ADD_CIRCULAR_GEOFENCE_V02
//#define REMOVE_QMI_LOC_ADD_GEOFENCE_CONTEXT_V02
//#define REMOVE_QMI_LOC_DELETE_ASSIST_DATA_V02
//#define REMOVE_QMI_LOC_DELETE_GEOFENCE_V02
//#define REMOVE_QMI_LOC_DELETE_GEOFENCE_CONTEXT_V02
//#define REMOVE_QMI_LOC_DELETE_SUPL_CERTIFICATE_V02
//#define REMOVE_QMI_LOC_EDIT_GEOFENCE_V02
//#define REMOVE_QMI_LOC_EVENT_BATCH_FULL_NOTIFICATION_V02
//#define REMOVE_QMI_LOC_EVENT_ENGINE_STATE_V02
//#define REMOVE_QMI_LOC_EVENT_FIX_SESSION_STATE_V02
//#define REMOVE_QMI_LOC_EVENT_GDT_UPLOAD_BEGIN_STATUS_REQ_V02
//#define REMOVE_QMI_LOC_EVENT_GDT_UPLOAD_END_REQ_V02
//#define REMOVE_QMI_LOC_EVENT_GEOFENCE_BATCHED_BREACH_NOTIFICATION_V02
//#define REMOVE_QMI_LOC_EVENT_GEOFENCE_BREACH_NOTIFICATION_V02
//#define REMOVE_QMI_LOC_EVENT_GEOFENCE_GEN_ALERT_V02
//#define REMOVE_QMI_LOC_EVENT_GEOFENCE_PROXIMITY_NOTIFICATION_V02
//#define REMOVE_QMI_LOC_EVENT_GNSS_MEASUREMENT_REPORT_IND_V02
//#define REMOVE_QMI_LOC_EVENT_GNSS_SV_INFO_V02
//#define REMOVE_QMI_LOC_EVENT_INJECT_POSITION_REQ_V02
//#define REMOVE_QMI_LOC_EVENT_INJECT_PREDICTED_ORBITS_REQ_V02
//#define REMOVE_QMI_LOC_EVENT_INJECT_TIME_REQ_V02
//#define REMOVE_QMI_LOC_EVENT_INJECT_WIFI_AP_DATA_REQ_V02
//#define REMOVE_QMI_LOC_EVENT_LIVE_BATCHED_POSITION_REPORT_V02
//#define REMOVE_QMI_LOC_EVENT_LOCATION_SERVER_CONNECTION_REQ_V02
//#define REMOVE_QMI_LOC_EVENT_MOTION_DATA_CONTROL_V02
//#define REMOVE_QMI_LOC_EVENT_NI_GEOFENCE_NOTIFICATION_V02
//#define REMOVE_QMI_LOC_EVENT_NI_NOTIFY_VERIFY_REQ_V02
//#define REMOVE_QMI_LOC_EVENT_NMEA_V02
//#define REMOVE_QMI_LOC_EVENT_PEDOMETER_CONTROL_V02
//#define REMOVE_QMI_LOC_EVENT_POSITION_REPORT_V02
//#define REMOVE_QMI_LOC_EVENT_SENSOR_STREAMING_READY_STATUS_V02
//#define REMOVE_QMI_LOC_EVENT_SET_SPI_STREAMING_REPORT_V02
//#define REMOVE_QMI_LOC_EVENT_SV_POLYNOMIAL_REPORT_IND_V02
//#define REMOVE_QMI_LOC_EVENT_TIME_SYNC_REQ_V02
//#define REMOVE_QMI_LOC_EVENT_VEHICLE_DATA_READY_STATUS_V02
//#define REMOVE_QMI_LOC_EVENT_WIFI_REQ_V02
//#define REMOVE_QMI_LOC_GDT_UPLOAD_BEGIN_STATUS_V02
//#define REMOVE_QMI_LOC_GDT_UPLOAD_END_V02
//#define REMOVE_QMI_LOC_GET_AVAILABLE_WWAN_POSITION_V02
//#define REMOVE_QMI_LOC_GET_BATCH_SIZE_V02
//#define REMOVE_QMI_LOC_GET_BEST_AVAILABLE_POSITION_V02
//#define REMOVE_QMI_LOC_GET_CRADLE_MOUNT_CONFIG_V02
//#define REMOVE_QMI_LOC_GET_ENGINE_LOCK_V02
//#define REMOVE_QMI_LOC_GET_EXTERNAL_POWER_CONFIG_V02
//#define REMOVE_QMI_LOC_GET_FIX_CRITERIA_V02
//#define REMOVE_QMI_LOC_GET_GEOFENCE_ENGINE_CONFIG_V02
//#define REMOVE_QMI_LOC_GET_LOW_POWER_MODE_V02
//#define REMOVE_QMI_LOC_GET_NI_GEOFENCE_ID_LIST_V02
//#define REMOVE_QMI_LOC_GET_NMEA_TYPES_V02
//#define REMOVE_QMI_LOC_GET_OPERATION_MODE_V02
//#define REMOVE_QMI_LOC_GET_POSITION_ENGINE_CONFIG_PARAMETERS_V02
//#define REMOVE_QMI_LOC_GET_PREDICTED_ORBITS_DATA_SOURCE_V02
//#define REMOVE_QMI_LOC_GET_PREDICTED_ORBITS_DATA_VALIDITY_V02
//#define REMOVE_QMI_LOC_GET_PROTOCOL_CONFIG_PARAMETERS_V02
//#define REMOVE_QMI_LOC_GET_REGISTERED_EVENTS_V02
//#define REMOVE_QMI_LOC_GET_SBAS_CONFIG_V02
//#define REMOVE_QMI_LOC_GET_SENSOR_CONTROL_CONFIG_V02
//#define REMOVE_QMI_LOC_GET_SENSOR_PERFORMANCE_CONTROL_CONFIGURATION_V02
//#define REMOVE_QMI_LOC_GET_SENSOR_PROPERTIES_V02
//#define REMOVE_QMI_LOC_GET_SERVER_V02
//#define REMOVE_QMI_LOC_GET_SERVICE_REVISION_V02
//#define REMOVE_QMI_LOC_GET_SUPPORTED_FIELDS_V02
//#define REMOVE_QMI_LOC_GET_SUPPORTED_MSGS_V02
//#define REMOVE_QMI_LOC_GET_XTRA_T_SESSION_CONTROL_V02
//#define REMOVE_QMI_LOC_INFORM_CLIENT_REVISION_V02
//#define REMOVE_QMI_LOC_INFORM_LOCATION_SERVER_CONN_STATUS_V02
//#define REMOVE_QMI_LOC_INFORM_NI_USER_RESPONSE_V02
//#define REMOVE_QMI_LOC_INJECT_GSM_CELL_INFO_V02
//#define REMOVE_QMI_LOC_INJECT_GTP_CLIENT_DOWNLOADED_DATA_V02
//#define REMOVE_QMI_LOC_INJECT_MOTION_DATA_V02
//#define REMOVE_QMI_LOC_INJECT_NETWORK_INITIATED_MESSAGE_V02
//#define REMOVE_QMI_LOC_INJECT_POSITION_V02
//#define REMOVE_QMI_LOC_INJECT_PREDICTED_ORBITS_DATA_V02
//#define REMOVE_QMI_LOC_INJECT_SENSOR_DATA_V02
//#define REMOVE_QMI_LOC_INJECT_SUBSCRIBER_ID_V02
//#define REMOVE_QMI_LOC_INJECT_SUPL_CERTIFICATE_V02
//#define REMOVE_QMI_LOC_INJECT_TDSCDMA_CELL_INFO_V02
//#define REMOVE_QMI_LOC_INJECT_TIME_SYNC_DATA_V02
//#define REMOVE_QMI_LOC_INJECT_UTC_TIME_V02
//#define REMOVE_QMI_LOC_INJECT_VEHICLE_SENSOR_DATA_V02
//#define REMOVE_QMI_LOC_INJECT_WCDMA_CELL_INFO_V02
//#define REMOVE_QMI_LOC_INJECT_WIFI_AP_DATA_V02
//#define REMOVE_QMI_LOC_INJECT_WIFI_POSITION_V02
//#define REMOVE_QMI_LOC_NOTIFY_WIFI_ATTACHMENT_STATUS_V02
//#define REMOVE_QMI_LOC_NOTIFY_WIFI_ENABLED_STATUS_V02
//#define REMOVE_QMI_LOC_NOTIFY_WIFI_STATUS_V02
//#define REMOVE_QMI_LOC_PEDOMETER_REPORT_V02
//#define REMOVE_QMI_LOC_QUERY_GEOFENCE_V02
//#define REMOVE_QMI_LOC_READ_FROM_BATCH_V02
//#define REMOVE_QMI_LOC_REG_EVENTS_V02
//#define REMOVE_QMI_LOC_RELEASE_BATCH_V02
//#define REMOVE_QMI_LOC_SET_CRADLE_MOUNT_CONFIG_V02
//#define REMOVE_QMI_LOC_SET_ENGINE_LOCK_V02
//#define REMOVE_QMI_LOC_SET_EXTERNAL_POWER_CONFIG_V02
//#define REMOVE_QMI_LOC_SET_GEOFENCE_ENGINE_CONFIG_V02
//#define REMOVE_QMI_LOC_SET_GEOFENCE_ENGINE_CONTEXT_V02
//#define REMOVE_QMI_LOC_SET_GNSS_CONSTELL_REPORT_CONFIG_V02
//#define REMOVE_QMI_LOC_SET_LOW_POWER_MODE_V02
//#define REMOVE_QMI_LOC_SET_NMEA_TYPES_V02
//#define REMOVE_QMI_LOC_SET_OPERATION_MODE_V02
//#define REMOVE_QMI_LOC_SET_POSITION_ENGINE_CONFIG_PARAMETERS_V02
//#define REMOVE_QMI_LOC_SET_PREMIUM_SERVICES_CONFIG_V02
//#define REMOVE_QMI_LOC_SET_PROTOCOL_CONFIG_PARAMETERS_V02
//#define REMOVE_QMI_LOC_SET_SBAS_CONFIG_V02
//#define REMOVE_QMI_LOC_SET_SENSOR_CONTROL_CONFIG_V02
//#define REMOVE_QMI_LOC_SET_SENSOR_PERFORMANCE_CONTROL_CONFIGURATION_V02
//#define REMOVE_QMI_LOC_SET_SENSOR_PROPERTIES_V02
//#define REMOVE_QMI_LOC_SET_SERVER_V02
//#define REMOVE_QMI_LOC_SET_SPI_STATUS_V02
//#define REMOVE_QMI_LOC_SET_XTRA_T_SESSION_CONTROL_V02
//#define REMOVE_QMI_LOC_SET_XTRA_VERSION_CHECK_V02
//#define REMOVE_QMI_LOC_START_V02
//#define REMOVE_QMI_LOC_START_BATCHING_V02
//#define REMOVE_QMI_LOC_STOP_V02
//#define REMOVE_QMI_LOC_STOP_BATCHING_V02
//#define REMOVE_QMI_LOC_WWAN_OUT_OF_SERVICE_NOTIFICATION_V02

/*Service Message Definition*/
/** @addtogroup loc_qmi_msg_ids
    @{
  */
#define QMI_LOC_GET_SUPPORTED_MSGS_REQ_V02 0x001E
#define QMI_LOC_GET_SUPPORTED_MSGS_RESP_V02 0x001E
#define QMI_LOC_GET_SUPPORTED_FIELDS_REQ_V02 0x001F
#define QMI_LOC_GET_SUPPORTED_FIELDS_RESP_V02 0x001F
#define QMI_LOC_INFORM_CLIENT_REVISION_REQ_V02 0x0020
#define QMI_LOC_INFORM_CLIENT_REVISION_RESP_V02 0x0020
#define QMI_LOC_REG_EVENTS_REQ_V02 0x0021
#define QMI_LOC_REG_EVENTS_RESP_V02 0x0021
#define QMI_LOC_START_REQ_V02 0x0022
#define QMI_LOC_START_RESP_V02 0x0022
#define QMI_LOC_STOP_REQ_V02 0x0023
#define QMI_LOC_STOP_RESP_V02 0x0023
#define QMI_LOC_EVENT_POSITION_REPORT_IND_V02 0x0024
#define QMI_LOC_EVENT_GNSS_SV_INFO_IND_V02 0x0025
#define QMI_LOC_EVENT_NMEA_IND_V02 0x0026
#define QMI_LOC_EVENT_NI_NOTIFY_VERIFY_REQ_IND_V02 0x0027
#define QMI_LOC_EVENT_INJECT_TIME_REQ_IND_V02 0x0028
#define QMI_LOC_EVENT_INJECT_PREDICTED_ORBITS_REQ_IND_V02 0x0029
#define QMI_LOC_EVENT_INJECT_POSITION_REQ_IND_V02 0x002A
#define QMI_LOC_EVENT_ENGINE_STATE_IND_V02 0x002B
#define QMI_LOC_EVENT_FIX_SESSION_STATE_IND_V02 0x002C
#define QMI_LOC_EVENT_WIFI_REQ_IND_V02 0x002D
#define QMI_LOC_EVENT_SENSOR_STREAMING_READY_STATUS_IND_V02 0x002E
#define QMI_LOC_EVENT_TIME_SYNC_REQ_IND_V02 0x002F
#define QMI_LOC_EVENT_SET_SPI_STREAMING_REPORT_IND_V02 0x0030
#define QMI_LOC_EVENT_LOCATION_SERVER_CONNECTION_REQ_IND_V02 0x0031
#define QMI_LOC_GET_SERVICE_REVISION_REQ_V02 0x0032
#define QMI_LOC_GET_SERVICE_REVISION_RESP_V02 0x0032
#define QMI_LOC_GET_SERVICE_REVISION_IND_V02 0x0032
#define QMI_LOC_GET_FIX_CRITERIA_REQ_V02 0x0033
#define QMI_LOC_GET_FIX_CRITERIA_RESP_V02 0x0033
#define QMI_LOC_GET_FIX_CRITERIA_IND_V02 0x0033
#define QMI_LOC_NI_USER_RESPONSE_REQ_V02 0x0034
#define QMI_LOC_NI_USER_RESPONSE_RESP_V02 0x0034
#define QMI_LOC_NI_USER_RESPONSE_IND_V02 0x0034
#define QMI_LOC_INJECT_PREDICTED_ORBITS_DATA_REQ_V02 0x0035
#define QMI_LOC_INJECT_PREDICTED_ORBITS_DATA_RESP_V02 0x0035
#define QMI_LOC_INJECT_PREDICTED_ORBITS_DATA_IND_V02 0x0035
#define QMI_LOC_GET_PREDICTED_ORBITS_DATA_SOURCE_REQ_V02 0x0036
#define QMI_LOC_GET_PREDICTED_ORBITS_DATA_SOURCE_RESP_V02 0x0036
#define QMI_LOC_GET_PREDICTED_ORBITS_DATA_SOURCE_IND_V02 0x0036
#define QMI_LOC_GET_PREDICTED_ORBITS_DATA_VALIDITY_REQ_V02 0x0037
#define QMI_LOC_GET_PREDICTED_ORBITS_DATA_VALIDITY_RESP_V02 0x0037
#define QMI_LOC_GET_PREDICTED_ORBITS_DATA_VALIDITY_IND_V02 0x0037
#define QMI_LOC_INJECT_UTC_TIME_REQ_V02 0x0038
#define QMI_LOC_INJECT_UTC_TIME_RESP_V02 0x0038
#define QMI_LOC_INJECT_UTC_TIME_IND_V02 0x0038
#define QMI_LOC_INJECT_POSITION_REQ_V02 0x0039
#define QMI_LOC_INJECT_POSITION_RESP_V02 0x0039
#define QMI_LOC_INJECT_POSITION_IND_V02 0x0039
#define QMI_LOC_SET_ENGINE_LOCK_REQ_V02 0x003A
#define QMI_LOC_SET_ENGINE_LOCK_RESP_V02 0x003A
#define QMI_LOC_SET_ENGINE_LOCK_IND_V02 0x003A
#define QMI_LOC_GET_ENGINE_LOCK_REQ_V02 0x003B
#define QMI_LOC_GET_ENGINE_LOCK_RESP_V02 0x003B
#define QMI_LOC_GET_ENGINE_LOCK_IND_V02 0x003B
#define QMI_LOC_SET_SBAS_CONFIG_REQ_V02 0x003C
#define QMI_LOC_SET_SBAS_CONFIG_RESP_V02 0x003C
#define QMI_LOC_SET_SBAS_CONFIG_IND_V02 0x003C
#define QMI_LOC_GET_SBAS_CONFIG_REQ_V02 0x003D
#define QMI_LOC_GET_SBAS_CONFIG_RESP_V02 0x003D
#define QMI_LOC_GET_SBAS_CONFIG_IND_V02 0x003D
#define QMI_LOC_SET_NMEA_TYPES_REQ_V02 0x003E
#define QMI_LOC_SET_NMEA_TYPES_RESP_V02 0x003E
#define QMI_LOC_SET_NMEA_TYPES_IND_V02 0x003E
#define QMI_LOC_GET_NMEA_TYPES_REQ_V02 0x003F
#define QMI_LOC_GET_NMEA_TYPES_RESP_V02 0x003F
#define QMI_LOC_GET_NMEA_TYPES_IND_V02 0x003F
#define QMI_LOC_SET_LOW_POWER_MODE_REQ_V02 0x0040
#define QMI_LOC_SET_LOW_POWER_MODE_RESP_V02 0x0040
#define QMI_LOC_SET_LOW_POWER_MODE_IND_V02 0x0040
#define QMI_LOC_GET_LOW_POWER_MODE_REQ_V02 0x0041
#define QMI_LOC_GET_LOW_POWER_MODE_RESP_V02 0x0041
#define QMI_LOC_GET_LOW_POWER_MODE_IND_V02 0x0041
#define QMI_LOC_SET_SERVER_REQ_V02 0x0042
#define QMI_LOC_SET_SERVER_RESP_V02 0x0042
#define QMI_LOC_SET_SERVER_IND_V02 0x0042
#define QMI_LOC_GET_SERVER_REQ_V02 0x0043
#define QMI_LOC_GET_SERVER_RESP_V02 0x0043
#define QMI_LOC_GET_SERVER_IND_V02 0x0043
#define QMI_LOC_DELETE_ASSIST_DATA_REQ_V02 0x0044
#define QMI_LOC_DELETE_ASSIST_DATA_RESP_V02 0x0044
#define QMI_LOC_DELETE_ASSIST_DATA_IND_V02 0x0044
#define QMI_LOC_SET_XTRA_T_SESSION_CONTROL_REQ_V02 0x0045
#define QMI_LOC_SET_XTRA_T_SESSION_CONTROL_RESP_V02 0x0045
#define QMI_LOC_SET_XTRA_T_SESSION_CONTROL_IND_V02 0x0045
#define QMI_LOC_GET_XTRA_T_SESSION_CONTROL_REQ_V02 0x0046
#define QMI_LOC_GET_XTRA_T_SESSION_CONTROL_RESP_V02 0x0046
#define QMI_LOC_GET_XTRA_T_SESSION_CONTROL_IND_V02 0x0046
#define QMI_LOC_INJECT_WIFI_POSITION_REQ_V02 0x0047
#define QMI_LOC_INJECT_WIFI_POSITION_RESP_V02 0x0047
#define QMI_LOC_INJECT_WIFI_POSITION_IND_V02 0x0047
#define QMI_LOC_NOTIFY_WIFI_STATUS_REQ_V02 0x0048
#define QMI_LOC_NOTIFY_WIFI_STATUS_RESP_V02 0x0048
#define QMI_LOC_NOTIFY_WIFI_STATUS_IND_V02 0x0048
#define QMI_LOC_GET_REGISTERED_EVENTS_REQ_V02 0x0049
#define QMI_LOC_GET_REGISTERED_EVENTS_RESP_V02 0x0049
#define QMI_LOC_GET_REGISTERED_EVENTS_IND_V02 0x0049
#define QMI_LOC_SET_OPERATION_MODE_REQ_V02 0x004A
#define QMI_LOC_SET_OPERATION_MODE_RESP_V02 0x004A
#define QMI_LOC_SET_OPERATION_MODE_IND_V02 0x004A
#define QMI_LOC_GET_OPERATION_MODE_REQ_V02 0x004B
#define QMI_LOC_GET_OPERATION_MODE_RESP_V02 0x004B
#define QMI_LOC_GET_OPERATION_MODE_IND_V02 0x004B
#define QMI_LOC_SET_SPI_STATUS_REQ_V02 0x004C
#define QMI_LOC_SET_SPI_STATUS_RESP_V02 0x004C
#define QMI_LOC_SET_SPI_STATUS_IND_V02 0x004C
#define QMI_LOC_INJECT_SENSOR_DATA_REQ_V02 0x004D
#define QMI_LOC_INJECT_SENSOR_DATA_RESP_V02 0x004D
#define QMI_LOC_INJECT_SENSOR_DATA_IND_V02 0x004D
#define QMI_LOC_INJECT_TIME_SYNC_DATA_REQ_V02 0x004E
#define QMI_LOC_INJECT_TIME_SYNC_DATA_RESP_V02 0x004E
#define QMI_LOC_INJECT_TIME_SYNC_DATA_IND_V02 0x004E
#define QMI_LOC_SET_CRADLE_MOUNT_CONFIG_REQ_V02 0x004F
#define QMI_LOC_SET_CRADLE_MOUNT_CONFIG_RESP_V02 0x004F
#define QMI_LOC_SET_CRADLE_MOUNT_CONFIG_IND_V02 0x004F
#define QMI_LOC_GET_CRADLE_MOUNT_CONFIG_REQ_V02 0x0050
#define QMI_LOC_GET_CRADLE_MOUNT_CONFIG_RESP_V02 0x0050
#define QMI_LOC_GET_CRADLE_MOUNT_CONFIG_IND_V02 0x0050
#define QMI_LOC_SET_EXTERNAL_POWER_CONFIG_REQ_V02 0x0051
#define QMI_LOC_SET_EXTERNAL_POWER_CONFIG_RESP_V02 0x0051
#define QMI_LOC_SET_EXTERNAL_POWER_CONFIG_IND_V02 0x0051
#define QMI_LOC_GET_EXTERNAL_POWER_CONFIG_REQ_V02 0x0052
#define QMI_LOC_GET_EXTERNAL_POWER_CONFIG_RESP_V02 0x0052
#define QMI_LOC_GET_EXTERNAL_POWER_CONFIG_IND_V02 0x0052
#define QMI_LOC_INFORM_LOCATION_SERVER_CONN_STATUS_REQ_V02 0x0053
#define QMI_LOC_INFORM_LOCATION_SERVER_CONN_STATUS_RESP_V02 0x0053
#define QMI_LOC_INFORM_LOCATION_SERVER_CONN_STATUS_IND_V02 0x0053
#define QMI_LOC_SET_PROTOCOL_CONFIG_PARAMETERS_REQ_V02 0x0054
#define QMI_LOC_SET_PROTOCOL_CONFIG_PARAMETERS_RESP_V02 0x0054
#define QMI_LOC_SET_PROTOCOL_CONFIG_PARAMETERS_IND_V02 0x0054
#define QMI_LOC_GET_PROTOCOL_CONFIG_PARAMETERS_REQ_V02 0x0055
#define QMI_LOC_GET_PROTOCOL_CONFIG_PARAMETERS_RESP_V02 0x0055
#define QMI_LOC_GET_PROTOCOL_CONFIG_PARAMETERS_IND_V02 0x0055
#define QMI_LOC_SET_SENSOR_CONTROL_CONFIG_REQ_V02 0x0056
#define QMI_LOC_SET_SENSOR_CONTROL_CONFIG_RESP_V02 0x0056
#define QMI_LOC_SET_SENSOR_CONTROL_CONFIG_IND_V02 0x0056
#define QMI_LOC_GET_SENSOR_CONTROL_CONFIG_REQ_V02 0x0057
#define QMI_LOC_GET_SENSOR_CONTROL_CONFIG_RESP_V02 0x0057
#define QMI_LOC_GET_SENSOR_CONTROL_CONFIG_IND_V02 0x0057
#define QMI_LOC_SET_SENSOR_PROPERTIES_REQ_V02 0x0058
#define QMI_LOC_SET_SENSOR_PROPERTIES_RESP_V02 0x0058
#define QMI_LOC_SET_SENSOR_PROPERTIES_IND_V02 0x0058
#define QMI_LOC_GET_SENSOR_PROPERTIES_REQ_V02 0x0059
#define QMI_LOC_GET_SENSOR_PROPERTIES_RESP_V02 0x0059
#define QMI_LOC_GET_SENSOR_PROPERTIES_IND_V02 0x0059
#define QMI_LOC_SET_SENSOR_PERFORMANCE_CONTROL_CONFIGURATION_REQ_V02 0x005A
#define QMI_LOC_SET_SENSOR_PERFORMANCE_CONTROL_CONFIGURATION_RESP_V02 0x005A
#define QMI_LOC_SET_SENSOR_PERFORMANCE_CONTROL_CONFIGURATION_IND_V02 0x005A
#define QMI_LOC_GET_SENSOR_PERFORMANCE_CONTROL_CONFIGURATION_REQ_V02 0x005B
#define QMI_LOC_GET_SENSOR_PERFORMANCE_CONTROL_CONFIGURATION_RESP_V02 0x005B
#define QMI_LOC_GET_SENSOR_PERFORMANCE_CONTROL_CONFIGURATION_IND_V02 0x005B
#define QMI_LOC_INJECT_SUPL_CERTIFICATE_REQ_V02 0x005C
#define QMI_LOC_INJECT_SUPL_CERTIFICATE_RESP_V02 0x005C
#define QMI_LOC_INJECT_SUPL_CERTIFICATE_IND_V02 0x005C
#define QMI_LOC_DELETE_SUPL_CERTIFICATE_REQ_V02 0x005D
#define QMI_LOC_DELETE_SUPL_CERTIFICATE_RESP_V02 0x005D
#define QMI_LOC_DELETE_SUPL_CERTIFICATE_IND_V02 0x005D
#define QMI_LOC_SET_POSITION_ENGINE_CONFIG_PARAMETERS_REQ_V02 0x005E
#define QMI_LOC_SET_POSITION_ENGINE_CONFIG_PARAMETERS_RESP_V02 0x005E
#define QMI_LOC_SET_POSITION_ENGINE_CONFIG_PARAMETERS_IND_V02 0x005E
#define QMI_LOC_GET_POSITION_ENGINE_CONFIG_PARAMETERS_REQ_V02 0x005F
#define QMI_LOC_GET_POSITION_ENGINE_CONFIG_PARAMETERS_RESP_V02 0x005F
#define QMI_LOC_GET_POSITION_ENGINE_CONFIG_PARAMETERS_IND_V02 0x005F
#define QMI_LOC_EVENT_NI_GEOFENCE_NOTIFICATION_IND_V02 0x0060
#define QMI_LOC_EVENT_GEOFENCE_GEN_ALERT_IND_V02 0x0061
#define QMI_LOC_EVENT_GEOFENCE_BREACH_NOTIFICATION_IND_V02 0x0062
#define QMI_LOC_ADD_CIRCULAR_GEOFENCE_REQ_V02 0x0063
#define QMI_LOC_ADD_CIRCULAR_GEOFENCE_RESP_V02 0x0063
#define QMI_LOC_ADD_CIRCULAR_GEOFENCE_IND_V02 0x0063
#define QMI_LOC_DELETE_GEOFENCE_REQ_V02 0x0064
#define QMI_LOC_DELETE_GEOFENCE_RESP_V02 0x0064
#define QMI_LOC_DELETE_GEOFENCE_IND_V02 0x0064
#define QMI_LOC_QUERY_GEOFENCE_REQ_V02 0x0065
#define QMI_LOC_QUERY_GEOFENCE_RESP_V02 0x0065
#define QMI_LOC_QUERY_GEOFENCE_IND_V02 0x0065
#define QMI_LOC_EDIT_GEOFENCE_REQ_V02 0x0066
#define QMI_LOC_EDIT_GEOFENCE_RESP_V02 0x0066
#define QMI_LOC_EDIT_GEOFENCE_IND_V02 0x0066
#define QMI_LOC_GET_BEST_AVAILABLE_POSITION_REQ_V02 0x0067
#define QMI_LOC_GET_BEST_AVAILABLE_POSITION_RESP_V02 0x0067
#define QMI_LOC_GET_BEST_AVAILABLE_POSITION_IND_V02 0x0067
#define QMI_LOC_INJECT_MOTION_DATA_REQ_V02 0x0068
#define QMI_LOC_INJECT_MOTION_DATA_RESP_V02 0x0068
#define QMI_LOC_INJECT_MOTION_DATA_IND_V02 0x0068
#define QMI_LOC_GET_NI_GEOFENCE_ID_LIST_REQ_V02 0x0069
#define QMI_LOC_GET_NI_GEOFENCE_ID_LIST_RESP_V02 0x0069
#define QMI_LOC_GET_NI_GEOFENCE_ID_LIST_IND_V02 0x0069
#define QMI_LOC_INJECT_GSM_CELL_INFO_REQ_V02 0x006A
#define QMI_LOC_INJECT_GSM_CELL_INFO_RESP_V02 0x006A
#define QMI_LOC_INJECT_GSM_CELL_INFO_IND_V02 0x006A
#define QMI_LOC_INJECT_NETWORK_INITIATED_MESSAGE_REQ_V02 0x006B
#define QMI_LOC_INJECT_NETWORK_INITIATED_MESSAGE_RESP_V02 0x006B
#define QMI_LOC_INJECT_NETWORK_INITIATED_MESSAGE_IND_V02 0x006B
#define QMI_LOC_WWAN_OUT_OF_SERVICE_NOTIFICATION_REQ_V02 0x006C
#define QMI_LOC_WWAN_OUT_OF_SERVICE_NOTIFICATION_RESP_V02 0x006C
#define QMI_LOC_WWAN_OUT_OF_SERVICE_NOTIFICATION_IND_V02 0x006C
#define QMI_LOC_EVENT_PEDOMETER_CONTROL_IND_V02 0x006D
#define QMI_LOC_EVENT_MOTION_DATA_CONTROL_IND_V02 0x006E
#define QMI_LOC_PEDOMETER_REPORT_REQ_V02 0x006F
#define QMI_LOC_PEDOMETER_REPORT_RESP_V02 0x006F
#define QMI_LOC_PEDOMETER_REPORT_IND_V02 0x006F
#define QMI_LOC_INJECT_WCDMA_CELL_INFO_REQ_V02 0x0070
#define QMI_LOC_INJECT_WCDMA_CELL_INFO_RESP_V02 0x0070
#define QMI_LOC_INJECT_WCDMA_CELL_INFO_IND_V02 0x0070
#define QMI_LOC_INJECT_TDSCDMA_CELL_INFO_REQ_V02 0x0071
#define QMI_LOC_INJECT_TDSCDMA_CELL_INFO_RESP_V02 0x0071
#define QMI_LOC_INJECT_TDSCDMA_CELL_INFO_IND_V02 0x0071
#define QMI_LOC_INJECT_SUBSCRIBER_ID_REQ_V02 0x0072
#define QMI_LOC_INJECT_SUBSCRIBER_ID_RESP_V02 0x0072
#define QMI_LOC_INJECT_SUBSCRIBER_ID_IND_V02 0x0072
#define QMI_LOC_SET_GEOFENCE_ENGINE_CONFIG_REQ_V02 0x0073
#define QMI_LOC_SET_GEOFENCE_ENGINE_CONFIG_RESP_V02 0x0073
#define QMI_LOC_SET_GEOFENCE_ENGINE_CONFIG_IND_V02 0x0073
#define QMI_LOC_GET_GEOFENCE_ENGINE_CONFIG_REQ_V02 0x0074
#define QMI_LOC_GET_GEOFENCE_ENGINE_CONFIG_RESP_V02 0x0074
#define QMI_LOC_GET_GEOFENCE_ENGINE_CONFIG_IND_V02 0x0074
#define QMI_LOC_GET_BATCH_SIZE_REQ_V02 0x0075
#define QMI_LOC_GET_BATCH_SIZE_RESP_V02 0x0075
#define QMI_LOC_GET_BATCH_SIZE_IND_V02 0x0075
#define QMI_LOC_START_BATCHING_REQ_V02 0x0076
#define QMI_LOC_START_BATCHING_RESP_V02 0x0076
#define QMI_LOC_START_BATCHING_IND_V02 0x0076
#define QMI_LOC_EVENT_BATCH_FULL_NOTIFICATION_IND_V02 0x0077
#define QMI_LOC_EVENT_LIVE_BATCHED_POSITION_REPORT_IND_V02 0x0078
#define QMI_LOC_READ_FROM_BATCH_REQ_V02 0x0079
#define QMI_LOC_READ_FROM_BATCH_RESP_V02 0x0079
#define QMI_LOC_READ_FROM_BATCH_IND_V02 0x0079
#define QMI_LOC_STOP_BATCHING_REQ_V02 0x007A
#define QMI_LOC_STOP_BATCHING_RESP_V02 0x007A
#define QMI_LOC_STOP_BATCHING_IND_V02 0x007A
#define QMI_LOC_RELEASE_BATCH_REQ_V02 0x007B
#define QMI_LOC_RELEASE_BATCH_RESP_V02 0x007B
#define QMI_LOC_RELEASE_BATCH_IND_V02 0x007B
#define QMI_LOC_EVENT_INJECT_WIFI_AP_DATA_REQ_IND_V02 0x007C
#define QMI_LOC_INJECT_WIFI_AP_DATA_REQ_V02 0x007D
#define QMI_LOC_INJECT_WIFI_AP_DATA_RESP_V02 0x007D
#define QMI_LOC_INJECT_WIFI_AP_DATA_IND_V02 0x007D
#define QMI_LOC_NOTIFY_WIFI_ATTACHMENT_STATUS_REQ_V02 0x007E
#define QMI_LOC_NOTIFY_WIFI_ATTACHMENT_STATUS_RESP_V02 0x007E
#define QMI_LOC_NOTIFY_WIFI_ATTACHMENT_STATUS_IND_V02 0x007E
#define QMI_LOC_NOTIFY_WIFI_ENABLED_STATUS_REQ_V02 0x007F
#define QMI_LOC_NOTIFY_WIFI_ENABLED_STATUS_RESP_V02 0x007F
#define QMI_LOC_NOTIFY_WIFI_ENABLED_STATUS_IND_V02 0x007F
#define QMI_LOC_EVENT_GEOFENCE_BATCHED_BREACH_NOTIFICATION_IND_V02 0x0080
#define QMI_LOC_EVENT_VEHICLE_DATA_READY_STATUS_IND_V02 0x0081
#define QMI_LOC_INJECT_VEHICLE_SENSOR_DATA_REQ_V02 0x0082
#define QMI_LOC_INJECT_VEHICLE_SENSOR_DATA_RESP_V02 0x0082
#define QMI_LOC_INJECT_VEHICLE_SENSOR_DATA_IND_V02 0x0082
#define QMI_LOC_GET_AVAILABLE_WWAN_POSITION_REQ_V02 0x0083
#define QMI_LOC_GET_AVAILABLE_WWAN_POSITION_RESP_V02 0x0083
#define QMI_LOC_GET_AVAILABLE_WWAN_POSITION_IND_V02 0x0083
#define QMI_LOC_SET_PREMIUM_SERVICES_CONFIG_REQ_V02 0x0084
#define QMI_LOC_SET_PREMIUM_SERVICES_CONFIG_RESP_V02 0x0084
#define QMI_LOC_SET_PREMIUM_SERVICES_CONFIG_IND_V02 0x0084
#define QMI_LOC_SET_XTRA_VERSION_CHECK_REQ_V02 0x0085
#define QMI_LOC_SET_XTRA_VERSION_CHECK_RESP_V02 0x0085
#define QMI_LOC_SET_XTRA_VERSION_CHECK_IND_V02 0x0085
#define QMI_LOC_EVENT_GNSS_MEASUREMENT_REPORT_IND_V02 0x0086
#define QMI_LOC_EVENT_SV_POLYNOMIAL_REPORT_IND_V02 0x0087
#define QMI_LOC_SET_GNSS_CONSTELL_REPORT_CONFIG_V02 0x0088
#define QMI_LOC_SET_GNSS_CONSTELL_REPORT_CONFIG_RESP_V02 0x0088
#define QMI_LOC_SET_GNSS_CONSTELL_REPORT_CONFIG_IND_V02 0x0088
#define QMI_LOC_ADD_GEOFENCE_CONTEXT_REQ_V02 0x0089
#define QMI_LOC_ADD_GEOFENCE_CONTEXT_RESP_V02 0x0089
#define QMI_LOC_ADD_GEOFENCE_CONTEXT_IND_V02 0x0089
#define QMI_LOC_SET_GEOFENCE_ENGINE_CONTEXT_REQ_V02 0x008A
#define QMI_LOC_SET_GEOFENCE_ENGINE_CONTEXT_RESP_V02 0x008A
#define QMI_LOC_SET_GEOFENCE_ENGINE_CONTEXT_IND_V02 0x008A
#define QMI_LOC_DELETE_GEOFENCE_CONTEXT_REQ_V02 0x008B
#define QMI_LOC_DELETE_GEOFENCE_CONTEXT_RESP_V02 0x008B
#define QMI_LOC_DELETE_GEOFENCE_CONTEXT_IND_V02 0x008B
#define QMI_LOC_EVENT_GEOFENCE_PROXIMITY_NOTIFICATION_IND_V02 0x008C
#define QMI_LOC_INJECT_GTP_CLIENT_DOWNLOADED_DATA_REQ_V02 0x008D
#define QMI_LOC_INJECT_GTP_CLIENT_DOWNLOADED_DATA_RESP_V02 0x008D
#define QMI_LOC_INJECT_GTP_CLIENT_DOWNLOADED_DATA_IND_V02 0x008D
#define QMI_LOC_GDT_UPLOAD_BEGIN_STATUS_REQ_V02 0x008E
#define QMI_LOC_GDT_UPLOAD_BEGIN_STATUS_RESP_V02 0x008E
#define QMI_LOC_GDT_UPLOAD_BEGIN_STATUS_IND_V02 0x008E
#define QMI_LOC_GDT_UPLOAD_END_REQ_V02 0x008F
#define QMI_LOC_GDT_UPLOAD_END_RESP_V02 0x008F
#define QMI_LOC_GDT_UPLOAD_END_IND_V02 0x008F
#define QMI_LOC_EVENT_GDT_UPLOAD_BEGIN_STATUS_REQ_IND_V02 0x0090
#define QMI_LOC_EVENT_GDT_UPLOAD_END_REQ_IND_V02 0x0091
/**
    @}
  */

/* Service Object Accessor */
/** @addtogroup wms_qmi_accessor
    @{
  */
/** This function is used internally by the autogenerated code.  Clients should use the
   macro loc_get_service_object_v02( ) that takes in no arguments. */
qmi_idl_service_object_type loc_get_service_object_internal_v02
 ( int32_t idl_maj_version, int32_t idl_min_version, int32_t library_version );

/** This macro should be used to get the service object */
#define loc_get_service_object_v02( ) \
          loc_get_service_object_internal_v02( \
            LOC_V02_IDL_MAJOR_VERS, LOC_V02_IDL_MINOR_VERS, \
            LOC_V02_IDL_TOOL_VERS )
/**
    @}
  */


#ifdef __cplusplus
}
#endif
#endif

