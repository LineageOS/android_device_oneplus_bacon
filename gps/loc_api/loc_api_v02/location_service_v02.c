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
/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*
 *THIS IS AN AUTO GENERATED FILE. DO NOT ALTER IN ANY WAY
 *====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/* This file was generated with Tool version 6.14.5
   It was generated on: Thu Jul  2 2015 (Spin 0)
   From IDL File: location_service_v02.idl */

#include "stdint.h"
#include "qmi_idl_lib_internal.h"
#include "location_service_v02.h"
#include "common_v01.h"


/*Type Definitions*/
static const uint8_t qmiLocApplicationIdStructT_data_v02[] = {
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |QMI_IDL_STRING,
  QMI_IDL_OFFSET8(qmiLocApplicationIdStructT_v02, applicationProvider),
  QMI_LOC_MAX_APP_ID_PROVIDER_LENGTH_V02,

  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |QMI_IDL_STRING,
  QMI_IDL_OFFSET8(qmiLocApplicationIdStructT_v02, applicationName),
  QMI_LOC_MAX_APP_ID_NAME_LENGTH_V02,

  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocApplicationIdStructT_v02, applicationVersion_valid),

  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |QMI_IDL_STRING,
  QMI_IDL_OFFSET8(qmiLocApplicationIdStructT_v02, applicationVersion),
  QMI_LOC_MAX_APP_ID_VERSION_LENGTH_V02,

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocGPSTimeStructT_data_v02[] = {
  QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET8(qmiLocGPSTimeStructT_v02, gpsWeek),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGPSTimeStructT_v02, gpsTimeOfWeekMs),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocDOPStructT_data_v02[] = {
  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocDOPStructT_v02, PDOP),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocDOPStructT_v02, HDOP),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocDOPStructT_v02, VDOP),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocSensorUsageIndicatorStructT_data_v02[] = {
  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSensorUsageIndicatorStructT_v02, usageMask),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSensorUsageIndicatorStructT_v02, aidingIndicatorMask),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocSvInfoStructT_data_v02[] = {
  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSvInfoStructT_v02, validMask),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSvInfoStructT_v02, system),

  QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET8(qmiLocSvInfoStructT_v02, gnssSvId),

  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocSvInfoStructT_v02, healthStatus),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSvInfoStructT_v02, svStatus),

  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocSvInfoStructT_v02, svInfoMask),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSvInfoStructT_v02, elevation),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSvInfoStructT_v02, azimuth),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSvInfoStructT_v02, snr),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocNiVxNotifyVerifyStructT_data_v02[] = {
  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocNiVxNotifyVerifyStructT_v02, posQosIncl),

  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocNiVxNotifyVerifyStructT_v02, posQos),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocNiVxNotifyVerifyStructT_v02, numFixes),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocNiVxNotifyVerifyStructT_v02, timeBetweenFixes),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocNiVxNotifyVerifyStructT_v02, posMode),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocNiVxNotifyVerifyStructT_v02, encodingScheme),

  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocNiVxNotifyVerifyStructT_v02, requestorId),
  QMI_LOC_NI_MAX_REQUESTOR_ID_LENGTH_V02,
  QMI_IDL_OFFSET8(qmiLocNiVxNotifyVerifyStructT_v02, requestorId) - QMI_IDL_OFFSET8(qmiLocNiVxNotifyVerifyStructT_v02, requestorId_len),

  QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocNiVxNotifyVerifyStructT_v02, userRespTimerInSeconds),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocNiSuplFormattedStringStructT_data_v02[] = {
  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocNiSuplFormattedStringStructT_v02, formatType),

  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocNiSuplFormattedStringStructT_v02, formattedString),
  QMI_LOC_NI_MAX_CLIENT_NAME_LENGTH_V02,
  QMI_IDL_OFFSET8(qmiLocNiSuplFormattedStringStructT_v02, formattedString) - QMI_IDL_OFFSET8(qmiLocNiSuplFormattedStringStructT_v02, formattedString_len),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocNiSuplQopStructT_data_v02[] = {
  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocNiSuplQopStructT_v02, validMask),

  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocNiSuplQopStructT_v02, horizontalAccuracy),

  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocNiSuplQopStructT_v02, verticalAccuracy),

  QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET8(qmiLocNiSuplQopStructT_v02, maxLocAge),

  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocNiSuplQopStructT_v02, delay),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocIpV4AddrStructType_data_v02[] = {
  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocIpV4AddrStructType_v02, addr),

  QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET8(qmiLocIpV4AddrStructType_v02, port),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocIpV6AddrStructType_data_v02[] = {
  QMI_IDL_FLAGS_IS_ARRAY |QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET8(qmiLocIpV6AddrStructType_v02, addr),
  QMI_LOC_IPV6_ADDR_LENGTH_V02,

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocIpV6AddrStructType_v02, port),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocNiSuplServerInfoStructT_data_v02[] = {
  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocNiSuplServerInfoStructT_v02, suplServerAddrTypeMask),

  QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocNiSuplServerInfoStructT_v02, ipv4Addr),
  QMI_IDL_TYPE88(0, 8),
  QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocNiSuplServerInfoStructT_v02, ipv6Addr),
  QMI_IDL_TYPE88(0, 9),
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |QMI_IDL_STRING,
  QMI_IDL_OFFSET8(qmiLocNiSuplServerInfoStructT_v02, urlAddr),
  QMI_LOC_MAX_SERVER_ADDR_LENGTH_V02,

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocNiSuplNotifyVerifyStructT_data_v02[] = {
  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocNiSuplNotifyVerifyStructT_v02, valid_flags),

  QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocNiSuplNotifyVerifyStructT_v02, suplServerInfo),
  QMI_IDL_TYPE88(0, 10),
  QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_FLAGS_IS_ARRAY |QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocNiSuplNotifyVerifyStructT_v02, suplSessionId),
  QMI_LOC_NI_SUPL_SLP_SESSION_ID_BYTE_LENGTH_V02,

  QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_FLAGS_IS_ARRAY |QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocNiSuplNotifyVerifyStructT_v02, suplHash),
  QMI_LOC_NI_SUPL_HASH_LENGTH_V02,

  QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocNiSuplNotifyVerifyStructT_v02, posMethod),

  QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocNiSuplNotifyVerifyStructT_v02, dataCodingScheme),

  QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET16ARRAY(qmiLocNiSuplNotifyVerifyStructT_v02, requestorId),
  QMI_IDL_TYPE88(0, 6),
  QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET16ARRAY(qmiLocNiSuplNotifyVerifyStructT_v02, clientName),
  QMI_IDL_TYPE88(0, 6),
  QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET16ARRAY(qmiLocNiSuplNotifyVerifyStructT_v02, suplQop),
  QMI_IDL_TYPE88(0, 7),
  QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocNiSuplNotifyVerifyStructT_v02, userResponseTimer),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocNiUmtsCpCodedStringStructT_data_v02[] = {
  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocNiUmtsCpCodedStringStructT_v02, dataCodingScheme),

  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocNiUmtsCpCodedStringStructT_v02, codedString),
  QMI_LOC_NI_CODEWORD_MAX_LENGTH_V02,
  QMI_IDL_OFFSET8(qmiLocNiUmtsCpCodedStringStructT_v02, codedString) - QMI_IDL_OFFSET8(qmiLocNiUmtsCpCodedStringStructT_v02, codedString_len),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocNiUmtsCpNotifyVerifyStructT_data_v02[] = {
  QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET8(qmiLocNiUmtsCpNotifyVerifyStructT_v02, valid_flags),

  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocNiUmtsCpNotifyVerifyStructT_v02, invokeId),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocNiUmtsCpNotifyVerifyStructT_v02, dataCodingScheme),

  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocNiUmtsCpNotifyVerifyStructT_v02, notificationText),
  QMI_LOC_NI_MAX_CLIENT_NAME_LENGTH_V02,
  QMI_IDL_OFFSET8(qmiLocNiUmtsCpNotifyVerifyStructT_v02, notificationText) - QMI_IDL_OFFSET8(qmiLocNiUmtsCpNotifyVerifyStructT_v02, notificationText_len),

  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocNiUmtsCpNotifyVerifyStructT_v02, clientAddress),
  QMI_LOC_NI_MAX_EXT_CLIENT_ADDRESS_V02,
  QMI_IDL_OFFSET8(qmiLocNiUmtsCpNotifyVerifyStructT_v02, clientAddress) - QMI_IDL_OFFSET8(qmiLocNiUmtsCpNotifyVerifyStructT_v02, clientAddress_len),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocNiUmtsCpNotifyVerifyStructT_v02, locationType),

  QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocNiUmtsCpNotifyVerifyStructT_v02, requestorId),
  QMI_IDL_TYPE88(0, 12),
  QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocNiUmtsCpNotifyVerifyStructT_v02, codewordString),
  QMI_IDL_TYPE88(0, 12),
  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocNiUmtsCpNotifyVerifyStructT_v02, lcsServiceTypeId),

  QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET8(qmiLocNiUmtsCpNotifyVerifyStructT_v02, userResponseTimer),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocNiVxServiceInteractionStructT_data_v02[] = {
  QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocNiVxServiceInteractionStructT_v02, niVxReq),
  QMI_IDL_TYPE88(0, 5),
  QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocNiVxServiceInteractionStructT_v02, serviceInteractionType),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocNiSuplVer2ExtStructT_data_v02[] = {
  QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET8(qmiLocNiSuplVer2ExtStructT_v02, supportedNetworksMask),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocNiSuplVer2ExtStructT_v02, triggerType),

  QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET8(qmiLocNiSuplVer2ExtStructT_v02, gnssType),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocEmergencyNotificationStructT_data_v02[] = {
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |QMI_IDL_STRING,
  QMI_IDL_OFFSET8(qmiLocEmergencyNotificationStructT_v02, eslpUrl),
  QMI_LOC_MAX_SERVER_ADDR_LENGTH_V02,

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocAssistanceServerUrlStructT_data_v02[] = {
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |QMI_IDL_STRING,
  QMI_IDL_OFFSET8(qmiLocAssistanceServerUrlStructT_v02, serverUrl),
  QMI_LOC_MAX_SERVER_ADDR_LENGTH_V02,

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocTimeServerListStructT_data_v02[] = {
  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocTimeServerListStructT_v02, delayThreshold),

  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocTimeServerListStructT_v02, timeServerList),
  QMI_LOC_MAX_NTP_SERVERS_V02,
  QMI_IDL_OFFSET8(qmiLocTimeServerListStructT_v02, timeServerList) - QMI_IDL_OFFSET8(qmiLocTimeServerListStructT_v02, timeServerList_len),
  QMI_IDL_TYPE88(0, 17),
  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocPredictedOrbitsAllowedSizesStructT_data_v02[] = {
  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocPredictedOrbitsAllowedSizesStructT_v02, maxFileSizeInBytes),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocPredictedOrbitsAllowedSizesStructT_v02, maxPartSize),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocPredictedOrbitsServerListStructT_data_v02[] = {
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocPredictedOrbitsServerListStructT_v02, serverList),
  QMI_LOC_MAX_PREDICTED_ORBITS_SERVERS_V02,
  QMI_IDL_OFFSET8(qmiLocPredictedOrbitsServerListStructT_v02, serverList) - QMI_IDL_OFFSET8(qmiLocPredictedOrbitsServerListStructT_v02, serverList_len),
  QMI_IDL_TYPE88(0, 17),
  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocSensorControlConfigSamplingSpecStructT_data_v02[] = {
  QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET8(qmiLocSensorControlConfigSamplingSpecStructT_v02, samplesPerBatch),

  QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET8(qmiLocSensorControlConfigSamplingSpecStructT_v02, batchesPerSecond),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocSensorReadyStatusStructT_data_v02[] = {
  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocSensorReadyStatusStructT_v02, injectEnable),

  QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocSensorReadyStatusStructT_v02, dataFrequency),
  QMI_IDL_TYPE88(0, 21),
  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocGeofencePositionStructT_data_v02[] = {
  QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocGeofencePositionStructT_v02, timestampUtc),

  QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocGeofencePositionStructT_v02, latitude),

  QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocGeofencePositionStructT_v02, longitude),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGeofencePositionStructT_v02, horUncEllipseSemiMinor),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGeofencePositionStructT_v02, horUncEllipseSemiMajor),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGeofencePositionStructT_v02, horUncEllipseOrientAzimuth),

  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocGeofencePositionStructT_v02, speedHorizontal_valid),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGeofencePositionStructT_v02, speedHorizontal),

  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocGeofencePositionStructT_v02, altitudeWrtEllipsoid_valid),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGeofencePositionStructT_v02, altitudeWrtEllipsoid),

  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocGeofencePositionStructT_v02, vertUnc_valid),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGeofencePositionStructT_v02, vertUnc),

  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocGeofencePositionStructT_v02, speedVertical_valid),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGeofencePositionStructT_v02, speedVertical),

  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocGeofencePositionStructT_v02, heading_valid),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGeofencePositionStructT_v02, heading),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocGeofenceIdContinuousStructT_data_v02[] = {
  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGeofenceIdContinuousStructT_v02, idLow),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGeofenceIdContinuousStructT_v02, idHigh),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocPredictedOrbitsDataValidityStructT_data_v02[] = {
  QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocPredictedOrbitsDataValidityStructT_v02, startTimeInUTC),

  QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET8(qmiLocPredictedOrbitsDataValidityStructT_v02, durationHours),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocAltitudeSrcInfoStructT_data_v02[] = {
  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocAltitudeSrcInfoStructT_v02, source),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocAltitudeSrcInfoStructT_v02, linkage),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocAltitudeSrcInfoStructT_v02, coverage),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocDeleteSvInfoStructT_data_v02[] = {
  QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET8(qmiLocDeleteSvInfoStructT_v02, gnssSvId),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocDeleteSvInfoStructT_v02, system),

  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocDeleteSvInfoStructT_v02, deleteSvInfoMask),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocDeleteBDSSvInfoStructT_data_v02[] = {
  QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET8(qmiLocDeleteBDSSvInfoStructT_v02, gnssSvId),

  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocDeleteBDSSvInfoStructT_v02, deleteSvInfoMask),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocWifiFixTimeStructT_data_v02[] = {
  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocWifiFixTimeStructT_v02, wifiPositionTime),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocWifiFixPosStructT_data_v02[] = {
  QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocWifiFixPosStructT_v02, lat),

  QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocWifiFixPosStructT_v02, lon),

  QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET8(qmiLocWifiFixPosStructT_v02, hepe),

  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocWifiFixPosStructT_v02, numApsUsed),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocWifiFixPosStructT_v02, fixErrorCode),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocWifiApInfoStructT_data_v02[] = {
  QMI_IDL_FLAGS_IS_ARRAY |QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocWifiApInfoStructT_v02, macAddr),
  QMI_LOC_WIFI_MAC_ADDR_LENGTH_V02,

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocWifiApInfoStructT_v02, rssi),

  QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET8(qmiLocWifiApInfoStructT_v02, channel),

  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocWifiApInfoStructT_v02, apQualifier),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocWifiApSsidStructT_data_v02[] = {
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |QMI_IDL_STRING,
  QMI_IDL_OFFSET8(qmiLocWifiApSsidStructT_v02, ssid),
  QMI_LOC_MAX_WIFI_AP_SSID_STR_LENGTH_V02,

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLoc3AxisSensorSampleStructT_data_v02[] = {
  QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET8(qmiLoc3AxisSensorSampleStructT_v02, timeOffset),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLoc3AxisSensorSampleStructT_v02, xAxis),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLoc3AxisSensorSampleStructT_v02, yAxis),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLoc3AxisSensorSampleStructT_v02, zAxis),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLoc3AxisSensorSampleListStructT_data_v02[] = {
  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLoc3AxisSensorSampleListStructT_v02, timeOfFirstSample),

  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLoc3AxisSensorSampleListStructT_v02, flags),

  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLoc3AxisSensorSampleListStructT_v02, sensorData),
  QMI_LOC_SENSOR_DATA_MAX_SAMPLES_V02,
  QMI_IDL_OFFSET8(qmiLoc3AxisSensorSampleListStructT_v02, sensorData) - QMI_IDL_OFFSET8(qmiLoc3AxisSensorSampleListStructT_v02, sensorData_len),
  QMI_IDL_TYPE88(0, 33),
  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocSensorTemperatureSampleStructT_data_v02[] = {
  QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET8(qmiLocSensorTemperatureSampleStructT_v02, timeOffset),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSensorTemperatureSampleStructT_v02, temperature),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocSensorTemperatureSampleListStructT_data_v02[] = {
  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSensorTemperatureSampleListStructT_v02, timeSource),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSensorTemperatureSampleListStructT_v02, timeOfFirstSample),

  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocSensorTemperatureSampleListStructT_v02, temperatureData),
  QMI_LOC_SENSOR_DATA_MAX_SAMPLES_V02,
  QMI_IDL_OFFSET8(qmiLocSensorTemperatureSampleListStructT_v02, temperatureData) - QMI_IDL_OFFSET8(qmiLocSensorTemperatureSampleListStructT_v02, temperatureData_len),
  QMI_IDL_TYPE88(0, 35),
  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocApnProfilesStructT_data_v02[] = {
  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocApnProfilesStructT_v02, pdnType),

  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |QMI_IDL_STRING,
  QMI_IDL_OFFSET8(qmiLocApnProfilesStructT_v02, apnName),
  QMI_LOC_MAX_APN_NAME_LENGTH_V02,

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocCircularGeofenceArgsStructT_data_v02[] = {
  QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocCircularGeofenceArgsStructT_v02, latitude),

  QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocCircularGeofenceArgsStructT_v02, longitude),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocCircularGeofenceArgsStructT_v02, radius),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocGeofenceMotionStateConfigStructT_data_v02[] = {
  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGeofenceMotionStateConfigStructT_v02, motionState),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGeofenceMotionStateConfigStructT_v02, motionStateSpeed),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocMotionDataStructT_data_v02[] = {
  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocMotionDataStructT_v02, motion_state),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocMotionDataStructT_v02, motion_mode),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocMotionDataStructT_v02, probability_of_state),

  QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET8(qmiLocMotionDataStructT_v02, age),

  QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET8(qmiLocMotionDataStructT_v02, timeout),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocGSMCellIdStructT_data_v02[] = {
  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGSMCellIdStructT_v02, MCC),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGSMCellIdStructT_v02, MNC),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGSMCellIdStructT_v02, LAC),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGSMCellIdStructT_v02, CID),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocWCDMACellIdStructT_data_v02[] = {
  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocWCDMACellIdStructT_v02, mcc),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocWCDMACellIdStructT_v02, mnc),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocWCDMACellIdStructT_v02, cid),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocTDSCDMACellIdStructT_data_v02[] = {
  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocTDSCDMACellIdStructT_v02, mcc),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocTDSCDMACellIdStructT_v02, mnc),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocTDSCDMACellIdStructT_v02, cid),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocTDSCDMACellIdStructT_v02, lac),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocBatchedReportStructT_data_v02[] = {
  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocBatchedReportStructT_v02, fixId),

  QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocBatchedReportStructT_v02, validFields),

  QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocBatchedReportStructT_v02, latitude),

  QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocBatchedReportStructT_v02, longitude),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocBatchedReportStructT_v02, horUncCircular),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocBatchedReportStructT_v02, speedHorizontal),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocBatchedReportStructT_v02, speedUnc),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocBatchedReportStructT_v02, altitudeWrtEllipsoid),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocBatchedReportStructT_v02, speedVertical),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocBatchedReportStructT_v02, heading),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocBatchedReportStructT_v02, headingUnc),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocBatchedReportStructT_v02, technologyMask),

  QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocBatchedReportStructT_v02, timestampUtc),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocBatchedReportStructT_v02, timeUnc),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocBatchedReportStructT_v02, magneticDeviation),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocBatchedReportStructT_v02, vertUnc),

  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocBatchedReportStructT_v02, horConfidence),

  QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocBatchedReportStructT_v02, gpsTime),
  QMI_IDL_TYPE88(0, 1),
  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocWifiApDataStructT_data_v02[] = {
  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocWifiApDataStructT_v02, wifiApDataMask),

  QMI_IDL_FLAGS_IS_ARRAY |QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocWifiApDataStructT_v02, macAddress),
  QMI_LOC_WIFI_MAC_ADDR_LENGTH_V02,

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocWifiApDataStructT_v02, apTransmitPower),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocWifiApDataStructT_v02, apAntennaGain),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocWifiApDataStructT_v02, apSignalToNoise),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocWifiApDataStructT_v02, apDeviceType),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocWifiApDataStructT_v02, apRssi),

  QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET8(qmiLocWifiApDataStructT_v02, apChannel),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocWifiApDataStructT_v02, apRoundTripDelay),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocWifiApDataStructT_v02, apRoundTripDelayUnit),

  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocWifiApDataStructT_v02, apRoundTripDelayAccuracy),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocWifiApDataStructT_v02, mobileSignalToNoise),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocWifiApDataStructT_v02, mobileRssi),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocVehicleSensorSampleStructT_data_v02[] = {
  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocVehicleSensorSampleStructT_v02, timeOffset),

  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocVehicleSensorSampleStructT_v02, axisSample),
  QMI_LOC_VEHICLE_SENSOR_DATA_MAX_AXES_V02,
  QMI_IDL_OFFSET8(qmiLocVehicleSensorSampleStructT_v02, axisSample) - QMI_IDL_OFFSET8(qmiLocVehicleSensorSampleStructT_v02, axisSample_len),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocVehicleSensorSampleListStructType_data_v02[] = {
  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocVehicleSensorSampleListStructType_v02, sampleTimeBase),

  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocVehicleSensorSampleListStructType_v02, axesValidity),

  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocVehicleSensorSampleListStructType_v02, sensorData),
  QMI_LOC_VEHICLE_SENSOR_DATA_MAX_SAMPLES_V02,
  QMI_IDL_OFFSET8(qmiLocVehicleSensorSampleListStructType_v02, sensorData) - QMI_IDL_OFFSET8(qmiLocVehicleSensorSampleListStructType_v02, sensorData_len),
  QMI_IDL_TYPE88(0, 46),
  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocVehicleOdometrySampleStructT_data_v02[] = {
  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocVehicleOdometrySampleStructT_v02, timeOffset),

  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocVehicleOdometrySampleStructT_v02, distanceTravelled),
  QMI_LOC_VEHICLE_ODOMETRY_MAX_MEASUREMENTS_V02,
  QMI_IDL_OFFSET8(qmiLocVehicleOdometrySampleStructT_v02, distanceTravelled) - QMI_IDL_OFFSET8(qmiLocVehicleOdometrySampleStructT_v02, distanceTravelled_len),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocVehicleOdometrySampleListStructT_data_v02[] = {
  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocVehicleOdometrySampleListStructT_v02, sampleTimeBase),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocVehicleOdometrySampleListStructT_v02, flags),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocVehicleOdometrySampleListStructT_v02, wheelFlags),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocVehicleOdometrySampleListStructT_v02, distanceTravelledBase),

  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocVehicleOdometrySampleListStructT_v02, odometryData),
  QMI_LOC_VEHICLE_SENSOR_DATA_MAX_SAMPLES_V02,
  QMI_IDL_OFFSET8(qmiLocVehicleOdometrySampleListStructT_v02, odometryData) - QMI_IDL_OFFSET8(qmiLocVehicleOdometrySampleListStructT_v02, odometryData_len),
  QMI_IDL_TYPE88(0, 48),
  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocRcvrClockFrequencyInfoStructT_data_v02[] = {
  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocRcvrClockFrequencyInfoStructT_v02, clockDrift),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocRcvrClockFrequencyInfoStructT_v02, clockDriftUnc),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocRcvrClockFrequencyInfoStructT_v02, sourceOfFreq),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocLeapSecondInfoStructT_data_v02[] = {
  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocLeapSecondInfoStructT_v02, leapSec),

  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocLeapSecondInfoStructT_v02, leapSecUnc),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocInterSystemBiasStructT_data_v02[] = {
  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocInterSystemBiasStructT_v02, validMask),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInterSystemBiasStructT_v02, timeBias),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInterSystemBiasStructT_v02, timeBiasUnc),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocGnssTimeStructT_data_v02[] = {
  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGnssTimeStructT_v02, system),

  QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET8(qmiLocGnssTimeStructT_v02, systemWeek),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGnssTimeStructT_v02, systemMsec),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGnssTimeStructT_v02, systemClkTimeBias),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGnssTimeStructT_v02, systemClkTimeUncMs),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocGloTimeStructT_data_v02[] = {
  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocGloTimeStructT_v02, gloFourYear),

  QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET8(qmiLocGloTimeStructT_v02, gloDays),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGloTimeStructT_v02, gloMsec),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGloTimeStructT_v02, gloClkTimeBias),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGloTimeStructT_v02, gloClkTimeUncMs),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocGnssTimeExtStructT_data_v02[] = {
  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGnssTimeExtStructT_v02, refFCount),

  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocGnssTimeExtStructT_v02, systemRtc_valid),

  QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocGnssTimeExtStructT_v02, systemRtcMs),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGnssTimeExtStructT_v02, sourceOfTime),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocSVTimeSpeedStructT_data_v02[] = {
  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSVTimeSpeedStructT_v02, svTimeMs),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSVTimeSpeedStructT_v02, svTimeSubMs),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSVTimeSpeedStructT_v02, svTimeUncMs),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSVTimeSpeedStructT_v02, dopplerShift),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSVTimeSpeedStructT_v02, dopplerShiftUnc),

  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocSVTimeSpeedStructT_v02, dopplerAccel_valid),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSVTimeSpeedStructT_v02, dopplerAccel),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocSVMeasurementStructT_data_v02[] = {
  QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET8(qmiLocSVMeasurementStructT_v02, gnssSvId),

  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocSVMeasurementStructT_v02, gloFrequency),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSVMeasurementStructT_v02, svStatus),

  QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET8(qmiLocSVMeasurementStructT_v02, validMask),

  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocSVMeasurementStructT_v02, healthStatus),

  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocSVMeasurementStructT_v02, svInfoMask),

  QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocSVMeasurementStructT_v02, validMeasStatusMask),

  QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocSVMeasurementStructT_v02, measurementStatus),

  QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET8(qmiLocSVMeasurementStructT_v02, CNo),

  QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET8(qmiLocSVMeasurementStructT_v02, gloRfLoss),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSVMeasurementStructT_v02, measLatency),

  QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocSVMeasurementStructT_v02, svTimeSpeed),
  QMI_IDL_TYPE88(0, 56),
  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocSVMeasurementStructT_v02, lossOfLock),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSVMeasurementStructT_v02, multipathEstimate),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSVMeasurementStructT_v02, fineSpeed),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSVMeasurementStructT_v02, fineSpeedUnc),

  QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocSVMeasurementStructT_v02, carrierPhase),

  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocSVMeasurementStructT_v02, cycleSlipCount),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSVMeasurementStructT_v02, svAzimuth),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSVMeasurementStructT_v02, svElevation),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocWifiApMacAddressStructT_data_v02[] = {
  QMI_IDL_FLAGS_IS_ARRAY |QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocWifiApMacAddressStructT_v02, wifiApMacAddress),
  QMI_LOC_WIFI_MAC_ADDR_LENGTH_V02,

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocIBeaconIdStructT_data_v02[] = {
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |QMI_IDL_STRING,
  QMI_IDL_OFFSET8(qmiLocIBeaconIdStructT_v02, uuid),
  QMI_LOC_MAX_IBEACON_UUID_STR_LENGTH_V02,

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocIBeaconIdStructT_v02, majorNumber),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocIBeaconIdStructT_v02, minorNumber),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocDbtPositionStructT_data_v02[] = {
  QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocDbtPositionStructT_v02, timestampUtc),

  QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocDbtPositionStructT_v02, latitude),

  QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocDbtPositionStructT_v02, longitude),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocDbtPositionStructT_v02, horUncEllipseSemiMinor),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocDbtPositionStructT_v02, horUncEllipseSemiMajor),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocDbtPositionStructT_v02, horUncEllipseOrientAzimuth),

  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocDbtPositionStructT_v02, speedHorizontal_valid),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocDbtPositionStructT_v02, speedHorizontal),

  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocDbtPositionStructT_v02, altitudeWrtEllipsoid_valid),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocDbtPositionStructT_v02, altitudeWrtEllipsoid),

  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocDbtPositionStructT_v02, vertUnc_valid),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocDbtPositionStructT_v02, vertUnc),

  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocDbtPositionStructT_v02, speedVertical_valid),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocDbtPositionStructT_v02, speedVertical),

  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocDbtPositionStructT_v02, heading_valid),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocDbtPositionStructT_v02, heading),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocDeleteGALSvInfoStructT_data_v02[] = {
  QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET8(qmiLocDeleteGALSvInfoStructT_v02, gnssSvId),

  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocDeleteGALSvInfoStructT_v02, deleteSvInfoMask),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocTimeZoneStructT_data_v02[] = {
  QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocTimeZoneStructT_v02, dstOffset),

  QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocTimeZoneStructT_v02, rawOffset),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocApCacheStructT_data_v02[] = {
  QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocApCacheStructT_v02, macAddress),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocApCacheStructT_v02, xLat),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocApCacheStructT_v02, yLon),

  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocApCacheStructT_v02, mar),

  QMI_IDL_FLAG_END_VALUE
};

static const uint8_t qmiLocApDoNotCacheStructT_data_v02[] = {
  QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocApDoNotCacheStructT_v02, macAddress),

  QMI_IDL_FLAG_END_VALUE
};

/*Message Definitions*/
static const uint8_t qmiLocGenRespMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x02,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocGenRespMsgT_v02, resp),
  QMI_IDL_TYPE88(1, 0)
};

static const uint8_t qmiLocInformClientRevisionReqMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInformClientRevisionReqMsgT_v02, revision)
};

static const uint8_t qmiLocRegEventsReqMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocRegEventsReqMsgT_v02, eventRegMask)
};

static const uint8_t qmiLocStartReqMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocStartReqMsgT_v02, sessionId),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocStartReqMsgT_v02, fixRecurrence) - QMI_IDL_OFFSET8(qmiLocStartReqMsgT_v02, fixRecurrence_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocStartReqMsgT_v02, fixRecurrence),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocStartReqMsgT_v02, horizontalAccuracyLevel) - QMI_IDL_OFFSET8(qmiLocStartReqMsgT_v02, horizontalAccuracyLevel_valid)),
  0x11,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocStartReqMsgT_v02, horizontalAccuracyLevel),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocStartReqMsgT_v02, intermediateReportState) - QMI_IDL_OFFSET8(qmiLocStartReqMsgT_v02, intermediateReportState_valid)),
  0x12,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocStartReqMsgT_v02, intermediateReportState),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocStartReqMsgT_v02, minInterval) - QMI_IDL_OFFSET8(qmiLocStartReqMsgT_v02, minInterval_valid)),
  0x13,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocStartReqMsgT_v02, minInterval),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocStartReqMsgT_v02, applicationId) - QMI_IDL_OFFSET8(qmiLocStartReqMsgT_v02, applicationId_valid)),
  0x14,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocStartReqMsgT_v02, applicationId),
  QMI_IDL_TYPE88(0, 0),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocStartReqMsgT_v02, configAltitudeAssumed) - QMI_IDL_OFFSET8(qmiLocStartReqMsgT_v02, configAltitudeAssumed_valid)),
  0x15,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocStartReqMsgT_v02, configAltitudeAssumed),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocStartReqMsgT_v02, minIntermediatePositionReportInterval) - QMI_IDL_OFFSET8(qmiLocStartReqMsgT_v02, minIntermediatePositionReportInterval_valid)),
  0x16,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocStartReqMsgT_v02, minIntermediatePositionReportInterval)
};

static const uint8_t qmiLocStopReqMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocStopReqMsgT_v02, sessionId)
};

static const uint8_t qmiLocEventPositionReportIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, sessionStatus),

  0x02,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, sessionId),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, latitude) - QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, latitude_valid)),
  0x10,
   QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, latitude),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, longitude) - QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, longitude_valid)),
  0x11,
   QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, longitude),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, horUncCircular) - QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, horUncCircular_valid)),
  0x12,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, horUncCircular),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, horUncEllipseSemiMinor) - QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, horUncEllipseSemiMinor_valid)),
  0x13,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, horUncEllipseSemiMinor),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, horUncEllipseSemiMajor) - QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, horUncEllipseSemiMajor_valid)),
  0x14,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, horUncEllipseSemiMajor),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, horUncEllipseOrientAzimuth) - QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, horUncEllipseOrientAzimuth_valid)),
  0x15,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, horUncEllipseOrientAzimuth),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, horConfidence) - QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, horConfidence_valid)),
  0x16,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, horConfidence),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, horReliability) - QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, horReliability_valid)),
  0x17,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, horReliability),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, speedHorizontal) - QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, speedHorizontal_valid)),
  0x18,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, speedHorizontal),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, speedUnc) - QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, speedUnc_valid)),
  0x19,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, speedUnc),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, altitudeWrtEllipsoid) - QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, altitudeWrtEllipsoid_valid)),
  0x1A,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, altitudeWrtEllipsoid),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, altitudeWrtMeanSeaLevel) - QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, altitudeWrtMeanSeaLevel_valid)),
  0x1B,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, altitudeWrtMeanSeaLevel),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, vertUnc) - QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, vertUnc_valid)),
  0x1C,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, vertUnc),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, vertConfidence) - QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, vertConfidence_valid)),
  0x1D,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, vertConfidence),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, vertReliability) - QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, vertReliability_valid)),
  0x1E,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, vertReliability),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, speedVertical) - QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, speedVertical_valid)),
  0x1F,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, speedVertical),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, heading) - QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, heading_valid)),
  0x20,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, heading),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, headingUnc) - QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, headingUnc_valid)),
  0x21,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, headingUnc),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, magneticDeviation) - QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, magneticDeviation_valid)),
  0x22,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, magneticDeviation),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, technologyMask) - QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, technologyMask_valid)),
  0x23,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, technologyMask),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, DOP) - QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, DOP_valid)),
  0x24,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, DOP),
  QMI_IDL_TYPE88(0, 2),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, timestampUtc) - QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, timestampUtc_valid)),
  0x25,
   QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, timestampUtc),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, leapSeconds) - QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, leapSeconds_valid)),
  0x26,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, leapSeconds),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, gpsTime) - QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, gpsTime_valid)),
  0x27,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, gpsTime),
  QMI_IDL_TYPE88(0, 1),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, timeUnc) - QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, timeUnc_valid)),
  0x28,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventPositionReportIndMsgT_v02, timeUnc),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocEventPositionReportIndMsgT_v02, timeSrc) - QMI_IDL_OFFSET16RELATIVE(qmiLocEventPositionReportIndMsgT_v02, timeSrc_valid)),
  0x29,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocEventPositionReportIndMsgT_v02, timeSrc),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocEventPositionReportIndMsgT_v02, sensorDataUsage) - QMI_IDL_OFFSET16RELATIVE(qmiLocEventPositionReportIndMsgT_v02, sensorDataUsage_valid)),
  0x2A,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET16ARRAY(qmiLocEventPositionReportIndMsgT_v02, sensorDataUsage),
  QMI_IDL_TYPE88(0, 3),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocEventPositionReportIndMsgT_v02, fixId) - QMI_IDL_OFFSET16RELATIVE(qmiLocEventPositionReportIndMsgT_v02, fixId_valid)),
  0x2B,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocEventPositionReportIndMsgT_v02, fixId),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocEventPositionReportIndMsgT_v02, gnssSvUsedList) - QMI_IDL_OFFSET16RELATIVE(qmiLocEventPositionReportIndMsgT_v02, gnssSvUsedList_valid)),
  0x2C,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocEventPositionReportIndMsgT_v02, gnssSvUsedList),
  QMI_LOC_MAX_SV_USED_LIST_LENGTH_V02,
  QMI_IDL_OFFSET16RELATIVE(qmiLocEventPositionReportIndMsgT_v02, gnssSvUsedList) - QMI_IDL_OFFSET16RELATIVE(qmiLocEventPositionReportIndMsgT_v02, gnssSvUsedList_len),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocEventPositionReportIndMsgT_v02, altitudeAssumed) - QMI_IDL_OFFSET16RELATIVE(qmiLocEventPositionReportIndMsgT_v02, altitudeAssumed_valid)),
  0x2D,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocEventPositionReportIndMsgT_v02, altitudeAssumed)
};

static const uint8_t qmiLocEventGnssSvInfoIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventGnssSvInfoIndMsgT_v02, altitudeAssumed),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventGnssSvInfoIndMsgT_v02, svList) - QMI_IDL_OFFSET8(qmiLocEventGnssSvInfoIndMsgT_v02, svList_valid)),
  0x10,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocEventGnssSvInfoIndMsgT_v02, svList),
  QMI_LOC_SV_INFO_LIST_MAX_SIZE_V02,
  QMI_IDL_OFFSET8(qmiLocEventGnssSvInfoIndMsgT_v02, svList) - QMI_IDL_OFFSET8(qmiLocEventGnssSvInfoIndMsgT_v02, svList_len),
  QMI_IDL_TYPE88(0, 4)
};

static const uint8_t qmiLocEventNmeaIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_STRING,
  QMI_IDL_OFFSET8(qmiLocEventNmeaIndMsgT_v02, nmea),
  QMI_LOC_NMEA_STRING_MAX_LENGTH_V02
};

static const uint8_t qmiLocEventNiNotifyVerifyReqIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventNiNotifyVerifyReqIndMsgT_v02, notificationType),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventNiNotifyVerifyReqIndMsgT_v02, NiVxInd) - QMI_IDL_OFFSET8(qmiLocEventNiNotifyVerifyReqIndMsgT_v02, NiVxInd_valid)),
  0x10,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocEventNiNotifyVerifyReqIndMsgT_v02, NiVxInd),
  QMI_IDL_TYPE88(0, 5),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocEventNiNotifyVerifyReqIndMsgT_v02, NiSuplInd) - QMI_IDL_OFFSET16RELATIVE(qmiLocEventNiNotifyVerifyReqIndMsgT_v02, NiSuplInd_valid)),
  0x11,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET16ARRAY(qmiLocEventNiNotifyVerifyReqIndMsgT_v02, NiSuplInd),
  QMI_IDL_TYPE88(0, 11),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocEventNiNotifyVerifyReqIndMsgT_v02, NiUmtsCpInd) - QMI_IDL_OFFSET16RELATIVE(qmiLocEventNiNotifyVerifyReqIndMsgT_v02, NiUmtsCpInd_valid)),
  0x12,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET16ARRAY(qmiLocEventNiNotifyVerifyReqIndMsgT_v02, NiUmtsCpInd),
  QMI_IDL_TYPE88(0, 13),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocEventNiNotifyVerifyReqIndMsgT_v02, NiVxServiceInteractionInd) - QMI_IDL_OFFSET16RELATIVE(qmiLocEventNiNotifyVerifyReqIndMsgT_v02, NiVxServiceInteractionInd_valid)),
  0x13,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET16ARRAY(qmiLocEventNiNotifyVerifyReqIndMsgT_v02, NiVxServiceInteractionInd),
  QMI_IDL_TYPE88(0, 14),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocEventNiNotifyVerifyReqIndMsgT_v02, NiSuplVer2ExtInd) - QMI_IDL_OFFSET16RELATIVE(qmiLocEventNiNotifyVerifyReqIndMsgT_v02, NiSuplVer2ExtInd_valid)),
  0x14,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET16ARRAY(qmiLocEventNiNotifyVerifyReqIndMsgT_v02, NiSuplVer2ExtInd),
  QMI_IDL_TYPE88(0, 15),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocEventNiNotifyVerifyReqIndMsgT_v02, suplEmergencyNotification) - QMI_IDL_OFFSET16RELATIVE(qmiLocEventNiNotifyVerifyReqIndMsgT_v02, suplEmergencyNotification_valid)),
  0x15,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET16ARRAY(qmiLocEventNiNotifyVerifyReqIndMsgT_v02, suplEmergencyNotification),
  QMI_IDL_TYPE88(0, 16)
};

static const uint8_t qmiLocEventInjectTimeReqIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventInjectTimeReqIndMsgT_v02, timeServerInfo) - QMI_IDL_OFFSET8(qmiLocEventInjectTimeReqIndMsgT_v02, timeServerInfo_valid)),
  0x10,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocEventInjectTimeReqIndMsgT_v02, timeServerInfo),
  QMI_IDL_TYPE88(0, 18)
};

static const uint8_t qmiLocEventInjectPredictedOrbitsReqIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocEventInjectPredictedOrbitsReqIndMsgT_v02, allowedSizes),
  QMI_IDL_TYPE88(0, 19),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventInjectPredictedOrbitsReqIndMsgT_v02, serverList) - QMI_IDL_OFFSET8(qmiLocEventInjectPredictedOrbitsReqIndMsgT_v02, serverList_valid)),
  0x10,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocEventInjectPredictedOrbitsReqIndMsgT_v02, serverList),
  QMI_IDL_TYPE88(0, 20)
};

static const uint8_t qmiLocEventInjectPositionReqIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventInjectPositionReqIndMsgT_v02, latitude),

  0x02,
   QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventInjectPositionReqIndMsgT_v02, longitude),

  0x03,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventInjectPositionReqIndMsgT_v02, horUncCircular),

  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x04,
   QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventInjectPositionReqIndMsgT_v02, timestampUtc)
};

static const uint8_t qmiLocEventEngineStateIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventEngineStateIndMsgT_v02, engineState)
};

static const uint8_t qmiLocEventFixSessionStateIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventFixSessionStateIndMsgT_v02, sessionState),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventFixSessionStateIndMsgT_v02, sessionId) - QMI_IDL_OFFSET8(qmiLocEventFixSessionStateIndMsgT_v02, sessionId_valid)),
  0x10,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventFixSessionStateIndMsgT_v02, sessionId)
};

static const uint8_t qmiLocEventWifiReqIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventWifiReqIndMsgT_v02, requestType),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventWifiReqIndMsgT_v02, tbfInMs) - QMI_IDL_OFFSET8(qmiLocEventWifiReqIndMsgT_v02, tbfInMs_valid)),
  0x10,
   QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventWifiReqIndMsgT_v02, tbfInMs)
};

static const uint8_t qmiLocEventSensorStreamingReadyStatusIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventSensorStreamingReadyStatusIndMsgT_v02, accelReady) - QMI_IDL_OFFSET8(qmiLocEventSensorStreamingReadyStatusIndMsgT_v02, accelReady_valid)),
  0x10,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocEventSensorStreamingReadyStatusIndMsgT_v02, accelReady),
  QMI_IDL_TYPE88(0, 22),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventSensorStreamingReadyStatusIndMsgT_v02, gyroReady) - QMI_IDL_OFFSET8(qmiLocEventSensorStreamingReadyStatusIndMsgT_v02, gyroReady_valid)),
  0x11,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocEventSensorStreamingReadyStatusIndMsgT_v02, gyroReady),
  QMI_IDL_TYPE88(0, 22),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventSensorStreamingReadyStatusIndMsgT_v02, accelTemperatureReady) - QMI_IDL_OFFSET8(qmiLocEventSensorStreamingReadyStatusIndMsgT_v02, accelTemperatureReady_valid)),
  0x12,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocEventSensorStreamingReadyStatusIndMsgT_v02, accelTemperatureReady),
  QMI_IDL_TYPE88(0, 22),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventSensorStreamingReadyStatusIndMsgT_v02, gyroTemperatureReady) - QMI_IDL_OFFSET8(qmiLocEventSensorStreamingReadyStatusIndMsgT_v02, gyroTemperatureReady_valid)),
  0x13,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocEventSensorStreamingReadyStatusIndMsgT_v02, gyroTemperatureReady),
  QMI_IDL_TYPE88(0, 22),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventSensorStreamingReadyStatusIndMsgT_v02, calibratedMagReady) - QMI_IDL_OFFSET8(qmiLocEventSensorStreamingReadyStatusIndMsgT_v02, calibratedMagReady_valid)),
  0x14,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocEventSensorStreamingReadyStatusIndMsgT_v02, calibratedMagReady),
  QMI_IDL_TYPE88(0, 22),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventSensorStreamingReadyStatusIndMsgT_v02, uncalibratedMagReady) - QMI_IDL_OFFSET8(qmiLocEventSensorStreamingReadyStatusIndMsgT_v02, uncalibratedMagReady_valid)),
  0x15,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocEventSensorStreamingReadyStatusIndMsgT_v02, uncalibratedMagReady),
  QMI_IDL_TYPE88(0, 22)
};

static const uint8_t qmiLocEventTimeSyncReqIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventTimeSyncReqIndMsgT_v02, refCounter)
};

static const uint8_t qmiLocEventSetSpiStreamingReportIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventSetSpiStreamingReportIndMsgT_v02, enable)
};

static const uint8_t qmiLocEventLocationServerConnectionReqIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventLocationServerConnectionReqIndMsgT_v02, connHandle),

  0x02,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventLocationServerConnectionReqIndMsgT_v02, requestType),

  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x03,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventLocationServerConnectionReqIndMsgT_v02, wwanType)
};

static const uint8_t qmiLocEventNiGeofenceNotificationIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventNiGeofenceNotificationIndMsgT_v02, geofenceId),

  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x02,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventNiGeofenceNotificationIndMsgT_v02, operationType)
};

static const uint8_t qmiLocEventGeofenceGenAlertIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventGeofenceGenAlertIndMsgT_v02, geofenceAlert)
};

static const uint8_t qmiLocEventGeofenceBreachIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventGeofenceBreachIndMsgT_v02, geofenceId),

  0x02,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventGeofenceBreachIndMsgT_v02, breachType),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventGeofenceBreachIndMsgT_v02, geofencePosition) - QMI_IDL_OFFSET8(qmiLocEventGeofenceBreachIndMsgT_v02, geofencePosition_valid)),
  0x10,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocEventGeofenceBreachIndMsgT_v02, geofencePosition),
  QMI_IDL_TYPE88(0, 23),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventGeofenceBreachIndMsgT_v02, breachConfidence) - QMI_IDL_OFFSET8(qmiLocEventGeofenceBreachIndMsgT_v02, breachConfidence_valid)),
  0x11,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventGeofenceBreachIndMsgT_v02, breachConfidence)
};

static const uint8_t qmiLocEventPedometerControlIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventPedometerControlIndMsgT_v02, requestPedometerData),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventPedometerControlIndMsgT_v02, resetStepCount) - QMI_IDL_OFFSET8(qmiLocEventPedometerControlIndMsgT_v02, resetStepCount_valid)),
  0x10,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventPedometerControlIndMsgT_v02, resetStepCount),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventPedometerControlIndMsgT_v02, stepCountThreshold) - QMI_IDL_OFFSET8(qmiLocEventPedometerControlIndMsgT_v02, stepCountThreshold_valid)),
  0x11,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventPedometerControlIndMsgT_v02, stepCountThreshold)
};

static const uint8_t qmiLocEventMotionDataControlIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventMotionDataControlIndMsgT_v02, requestMotionData)
};

static const uint8_t qmiLocEventGeofenceBatchedBreachIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventGeofenceBatchedBreachIndMsgT_v02, breachType),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventGeofenceBatchedBreachIndMsgT_v02, geofenceIdContinuousList) - QMI_IDL_OFFSET8(qmiLocEventGeofenceBatchedBreachIndMsgT_v02, geofenceIdContinuousList_valid)),
  0x10,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocEventGeofenceBatchedBreachIndMsgT_v02, geofenceIdContinuousList),
  QMI_LOC_MAX_GEOFENCE_ID_CONTINUOUS_LIST_LENGTH_V02,
  QMI_IDL_OFFSET8(qmiLocEventGeofenceBatchedBreachIndMsgT_v02, geofenceIdContinuousList) - QMI_IDL_OFFSET8(qmiLocEventGeofenceBatchedBreachIndMsgT_v02, geofenceIdContinuousList_len),
  QMI_IDL_TYPE88(0, 24),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedBreachIndMsgT_v02, geofenceIdDiscreteList) - QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedBreachIndMsgT_v02, geofenceIdDiscreteList_valid)),
  0x11,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocEventGeofenceBatchedBreachIndMsgT_v02, geofenceIdDiscreteList),
  QMI_LOC_MAX_GEOFENCE_ID_DISCRETE_LIST_LENGTH_V02,
  QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedBreachIndMsgT_v02, geofenceIdDiscreteList) - QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedBreachIndMsgT_v02, geofenceIdDiscreteList_len),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedBreachIndMsgT_v02, geofencePosition) - QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedBreachIndMsgT_v02, geofencePosition_valid)),
  0x12,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET16ARRAY(qmiLocEventGeofenceBatchedBreachIndMsgT_v02, geofencePosition),
  QMI_IDL_TYPE88(0, 23),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedBreachIndMsgT_v02, breachConfidence) - QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedBreachIndMsgT_v02, breachConfidence_valid)),
  0x13,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocEventGeofenceBatchedBreachIndMsgT_v02, breachConfidence),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedBreachIndMsgT_v02, headingUnc) - QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedBreachIndMsgT_v02, headingUnc_valid)),
  0x14,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocEventGeofenceBatchedBreachIndMsgT_v02, headingUnc),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedBreachIndMsgT_v02, vertUnc) - QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedBreachIndMsgT_v02, vertUnc_valid)),
  0x15,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocEventGeofenceBatchedBreachIndMsgT_v02, vertUnc),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedBreachIndMsgT_v02, speedUnc) - QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedBreachIndMsgT_v02, speedUnc_valid)),
  0x16,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocEventGeofenceBatchedBreachIndMsgT_v02, speedUnc),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedBreachIndMsgT_v02, horConfidence) - QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedBreachIndMsgT_v02, horConfidence_valid)),
  0x17,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocEventGeofenceBatchedBreachIndMsgT_v02, horConfidence),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedBreachIndMsgT_v02, vertConfidence) - QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedBreachIndMsgT_v02, vertConfidence_valid)),
  0x18,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocEventGeofenceBatchedBreachIndMsgT_v02, vertConfidence),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedBreachIndMsgT_v02, DOP) - QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedBreachIndMsgT_v02, DOP_valid)),
  0x19,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET16ARRAY(qmiLocEventGeofenceBatchedBreachIndMsgT_v02, DOP),
  QMI_IDL_TYPE88(0, 2),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedBreachIndMsgT_v02, gnssSvUsedList) - QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedBreachIndMsgT_v02, gnssSvUsedList_valid)),
  0x1A,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocEventGeofenceBatchedBreachIndMsgT_v02, gnssSvUsedList),
  QMI_LOC_MAX_SV_USED_LIST_LENGTH_V02,
  QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedBreachIndMsgT_v02, gnssSvUsedList) - QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedBreachIndMsgT_v02, gnssSvUsedList_len)
};

static const uint8_t qmiLocEventGeofenceProximityIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventGeofenceProximityIndMsgT_v02, proximityType),

  0x02,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventGeofenceProximityIndMsgT_v02, geofenceId),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventGeofenceProximityIndMsgT_v02, contextId) - QMI_IDL_OFFSET8(qmiLocEventGeofenceProximityIndMsgT_v02, contextId_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventGeofenceProximityIndMsgT_v02, contextId)
};

static const uint8_t qmiLocEventGdtUploadBeginStatusReqIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventGdtUploadBeginStatusReqIndMsgT_v02, serviceId),

  0x02,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventGdtUploadBeginStatusReqIndMsgT_v02, sessionId),

  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x03,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventGdtUploadBeginStatusReqIndMsgT_v02, filePath),
  QMI_LOC_MAX_GDT_PATH_LEN_V02,
  QMI_IDL_OFFSET8(qmiLocEventGdtUploadBeginStatusReqIndMsgT_v02, filePath) - QMI_IDL_OFFSET8(qmiLocEventGdtUploadBeginStatusReqIndMsgT_v02, filePath_len)
};

static const uint8_t qmiLocEventGdtUploadEndReqIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventGdtUploadEndReqIndMsgT_v02, serviceId),

  0x02,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventGdtUploadEndReqIndMsgT_v02, sessionId),

  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x03,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventGdtUploadEndReqIndMsgT_v02, endStatus)
};

/*
 * qmiLocGetServiceRevisionReqMsgT is empty
 * static const uint8_t qmiLocGetServiceRevisionReqMsgT_data_v02[] = {
 * };
 */

static const uint8_t qmiLocGetServiceRevisionIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetServiceRevisionIndMsgT_v02, status),

  0x02,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetServiceRevisionIndMsgT_v02, revision),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetServiceRevisionIndMsgT_v02, gnssMeFWVerString) - QMI_IDL_OFFSET8(qmiLocGetServiceRevisionIndMsgT_v02, gnssMeFWVerString_valid)),
  0x10,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_STRING,
  QMI_IDL_OFFSET8(qmiLocGetServiceRevisionIndMsgT_v02, gnssMeFWVerString),
  QMI_LOC_GNSS_ME_VERSION_STRING_MAX_LENGTH_V02,

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetServiceRevisionIndMsgT_v02, gnssHostSWVerString) - QMI_IDL_OFFSET8(qmiLocGetServiceRevisionIndMsgT_v02, gnssHostSWVerString_valid)),
  0x11,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_STRING,
  QMI_IDL_OFFSET8(qmiLocGetServiceRevisionIndMsgT_v02, gnssHostSWVerString),
  QMI_LOC_GNSS_HOSTED_SW_VERSION_STRING_MAX_LENGTH_V02,

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocGetServiceRevisionIndMsgT_v02, gnssSWVerString) - QMI_IDL_OFFSET16RELATIVE(qmiLocGetServiceRevisionIndMsgT_v02, gnssSWVerString_valid)),
  0x12,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_STRING,
  QMI_IDL_OFFSET16ARRAY(qmiLocGetServiceRevisionIndMsgT_v02, gnssSWVerString),
  QMI_LOC_GNSS_SW_VERSION_STRING_MAX_LENGTH_V02
};

/*
 * qmiLocGetFixCriteriaReqMsgT is empty
 * static const uint8_t qmiLocGetFixCriteriaReqMsgT_data_v02[] = {
 * };
 */

static const uint8_t qmiLocGetFixCriteriaIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetFixCriteriaIndMsgT_v02, status),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetFixCriteriaIndMsgT_v02, horizontalAccuracyLevel) - QMI_IDL_OFFSET8(qmiLocGetFixCriteriaIndMsgT_v02, horizontalAccuracyLevel_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetFixCriteriaIndMsgT_v02, horizontalAccuracyLevel),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetFixCriteriaIndMsgT_v02, intermediateReportState) - QMI_IDL_OFFSET8(qmiLocGetFixCriteriaIndMsgT_v02, intermediateReportState_valid)),
  0x11,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetFixCriteriaIndMsgT_v02, intermediateReportState),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetFixCriteriaIndMsgT_v02, minInterval) - QMI_IDL_OFFSET8(qmiLocGetFixCriteriaIndMsgT_v02, minInterval_valid)),
  0x12,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetFixCriteriaIndMsgT_v02, minInterval),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetFixCriteriaIndMsgT_v02, applicationId) - QMI_IDL_OFFSET8(qmiLocGetFixCriteriaIndMsgT_v02, applicationId_valid)),
  0x13,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocGetFixCriteriaIndMsgT_v02, applicationId),
  QMI_IDL_TYPE88(0, 0)
};

static const uint8_t qmiLocNiUserRespReqMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocNiUserRespReqMsgT_v02, userResp),

  0x02,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocNiUserRespReqMsgT_v02, notificationType),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocNiUserRespReqMsgT_v02, NiVxPayload) - QMI_IDL_OFFSET8(qmiLocNiUserRespReqMsgT_v02, NiVxPayload_valid)),
  0x10,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocNiUserRespReqMsgT_v02, NiVxPayload),
  QMI_IDL_TYPE88(0, 5),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocNiUserRespReqMsgT_v02, NiSuplPayload) - QMI_IDL_OFFSET16RELATIVE(qmiLocNiUserRespReqMsgT_v02, NiSuplPayload_valid)),
  0x11,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET16ARRAY(qmiLocNiUserRespReqMsgT_v02, NiSuplPayload),
  QMI_IDL_TYPE88(0, 11),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocNiUserRespReqMsgT_v02, NiUmtsCpPayload) - QMI_IDL_OFFSET16RELATIVE(qmiLocNiUserRespReqMsgT_v02, NiUmtsCpPayload_valid)),
  0x12,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET16ARRAY(qmiLocNiUserRespReqMsgT_v02, NiUmtsCpPayload),
  QMI_IDL_TYPE88(0, 13),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocNiUserRespReqMsgT_v02, NiVxServiceInteractionPayload) - QMI_IDL_OFFSET16RELATIVE(qmiLocNiUserRespReqMsgT_v02, NiVxServiceInteractionPayload_valid)),
  0x13,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET16ARRAY(qmiLocNiUserRespReqMsgT_v02, NiVxServiceInteractionPayload),
  QMI_IDL_TYPE88(0, 14),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocNiUserRespReqMsgT_v02, NiSuplVer2ExtPayload) - QMI_IDL_OFFSET16RELATIVE(qmiLocNiUserRespReqMsgT_v02, NiSuplVer2ExtPayload_valid)),
  0x14,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET16ARRAY(qmiLocNiUserRespReqMsgT_v02, NiSuplVer2ExtPayload),
  QMI_IDL_TYPE88(0, 15),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocNiUserRespReqMsgT_v02, suplEmergencyNotification) - QMI_IDL_OFFSET16RELATIVE(qmiLocNiUserRespReqMsgT_v02, suplEmergencyNotification_valid)),
  0x15,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET16ARRAY(qmiLocNiUserRespReqMsgT_v02, suplEmergencyNotification),
  QMI_IDL_TYPE88(0, 16)
};

static const uint8_t qmiLocNiUserRespIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocNiUserRespIndMsgT_v02, status)
};

static const uint8_t qmiLocInjectPredictedOrbitsDataReqMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectPredictedOrbitsDataReqMsgT_v02, totalSize),

  0x02,
   QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectPredictedOrbitsDataReqMsgT_v02, totalParts),

  0x03,
   QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectPredictedOrbitsDataReqMsgT_v02, partNum),

  0x04,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN | QMI_IDL_FLAGS_SZ_IS_16 |   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectPredictedOrbitsDataReqMsgT_v02, partData),
  ((QMI_LOC_MAX_PREDICTED_ORBITS_PART_LEN_V02) & 0xFF), ((QMI_LOC_MAX_PREDICTED_ORBITS_PART_LEN_V02) >> 8),
  QMI_IDL_OFFSET8(qmiLocInjectPredictedOrbitsDataReqMsgT_v02, partData) - QMI_IDL_OFFSET8(qmiLocInjectPredictedOrbitsDataReqMsgT_v02, partData_len),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocInjectPredictedOrbitsDataReqMsgT_v02, formatType) - QMI_IDL_OFFSET16RELATIVE(qmiLocInjectPredictedOrbitsDataReqMsgT_v02, formatType_valid)),
  0x10,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocInjectPredictedOrbitsDataReqMsgT_v02, formatType)
};

static const uint8_t qmiLocInjectPredictedOrbitsDataIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectPredictedOrbitsDataIndMsgT_v02, status),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocInjectPredictedOrbitsDataIndMsgT_v02, partNum) - QMI_IDL_OFFSET8(qmiLocInjectPredictedOrbitsDataIndMsgT_v02, partNum_valid)),
  0x10,
   QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectPredictedOrbitsDataIndMsgT_v02, partNum)
};

/*
 * qmiLocGetPredictedOrbitsDataSourceReqMsgT is empty
 * static const uint8_t qmiLocGetPredictedOrbitsDataSourceReqMsgT_data_v02[] = {
 * };
 */

static const uint8_t qmiLocGetPredictedOrbitsDataSourceIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetPredictedOrbitsDataSourceIndMsgT_v02, status),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetPredictedOrbitsDataSourceIndMsgT_v02, allowedSizes) - QMI_IDL_OFFSET8(qmiLocGetPredictedOrbitsDataSourceIndMsgT_v02, allowedSizes_valid)),
  0x10,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocGetPredictedOrbitsDataSourceIndMsgT_v02, allowedSizes),
  QMI_IDL_TYPE88(0, 19),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetPredictedOrbitsDataSourceIndMsgT_v02, serverList) - QMI_IDL_OFFSET8(qmiLocGetPredictedOrbitsDataSourceIndMsgT_v02, serverList_valid)),
  0x11,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocGetPredictedOrbitsDataSourceIndMsgT_v02, serverList),
  QMI_IDL_TYPE88(0, 20)
};

/*
 * qmiLocGetPredictedOrbitsDataValidityReqMsgT is empty
 * static const uint8_t qmiLocGetPredictedOrbitsDataValidityReqMsgT_data_v02[] = {
 * };
 */

static const uint8_t qmiLocGetPredictedOrbitsDataValidityIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetPredictedOrbitsDataValidityIndMsgT_v02, status),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetPredictedOrbitsDataValidityIndMsgT_v02, validityInfo) - QMI_IDL_OFFSET8(qmiLocGetPredictedOrbitsDataValidityIndMsgT_v02, validityInfo_valid)),
  0x10,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocGetPredictedOrbitsDataValidityIndMsgT_v02, validityInfo),
  QMI_IDL_TYPE88(0, 25)
};

static const uint8_t qmiLocInjectUtcTimeReqMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectUtcTimeReqMsgT_v02, timeUtc),

  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x02,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectUtcTimeReqMsgT_v02, timeUnc)
};

static const uint8_t qmiLocInjectUtcTimeIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectUtcTimeIndMsgT_v02, status)
};

static const uint8_t qmiLocInjectPositionReqMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, latitude) - QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, latitude_valid)),
  0x10,
   QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, latitude),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, longitude) - QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, longitude_valid)),
  0x11,
   QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, longitude),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, horUncCircular) - QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, horUncCircular_valid)),
  0x12,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, horUncCircular),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, horConfidence) - QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, horConfidence_valid)),
  0x13,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, horConfidence),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, horReliability) - QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, horReliability_valid)),
  0x14,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, horReliability),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, altitudeWrtEllipsoid) - QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, altitudeWrtEllipsoid_valid)),
  0x15,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, altitudeWrtEllipsoid),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, altitudeWrtMeanSeaLevel) - QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, altitudeWrtMeanSeaLevel_valid)),
  0x16,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, altitudeWrtMeanSeaLevel),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, vertUnc) - QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, vertUnc_valid)),
  0x17,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, vertUnc),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, vertConfidence) - QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, vertConfidence_valid)),
  0x18,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, vertConfidence),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, vertReliability) - QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, vertReliability_valid)),
  0x19,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, vertReliability),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, altSourceInfo) - QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, altSourceInfo_valid)),
  0x1A,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, altSourceInfo),
  QMI_IDL_TYPE88(0, 26),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, timestampUtc) - QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, timestampUtc_valid)),
  0x1B,
   QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, timestampUtc),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, timestampAge) - QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, timestampAge_valid)),
  0x1C,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, timestampAge),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, positionSrc) - QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, positionSrc_valid)),
  0x1D,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, positionSrc),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, rawHorUncCircular) - QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, rawHorUncCircular_valid)),
  0x1E,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, rawHorUncCircular),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, rawHorConfidence) - QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, rawHorConfidence_valid)),
  0x1F,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectPositionReqMsgT_v02, rawHorConfidence)
};

static const uint8_t qmiLocInjectPositionIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectPositionIndMsgT_v02, status)
};

static const uint8_t qmiLocSetEngineLockReqMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetEngineLockReqMsgT_v02, lockType)
};

static const uint8_t qmiLocSetEngineLockIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetEngineLockIndMsgT_v02, status)
};

/*
 * qmiLocGetEngineLockReqMsgT is empty
 * static const uint8_t qmiLocGetEngineLockReqMsgT_data_v02[] = {
 * };
 */

static const uint8_t qmiLocGetEngineLockIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetEngineLockIndMsgT_v02, status),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetEngineLockIndMsgT_v02, lockType) - QMI_IDL_OFFSET8(qmiLocGetEngineLockIndMsgT_v02, lockType_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetEngineLockIndMsgT_v02, lockType)
};

static const uint8_t qmiLocSetSbasConfigReqMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetSbasConfigReqMsgT_v02, sbasConfig)
};

static const uint8_t qmiLocSetSbasConfigIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetSbasConfigIndMsgT_v02, status)
};

/*
 * qmiLocGetSbasConfigReqMsgT is empty
 * static const uint8_t qmiLocGetSbasConfigReqMsgT_data_v02[] = {
 * };
 */

static const uint8_t qmiLocGetSbasConfigIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetSbasConfigIndMsgT_v02, status),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetSbasConfigIndMsgT_v02, sbasConfig) - QMI_IDL_OFFSET8(qmiLocGetSbasConfigIndMsgT_v02, sbasConfig_valid)),
  0x10,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetSbasConfigIndMsgT_v02, sbasConfig)
};

static const uint8_t qmiLocSetNmeaTypesReqMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetNmeaTypesReqMsgT_v02, nmeaSentenceType)
};

static const uint8_t qmiLocSetNmeaTypesIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetNmeaTypesIndMsgT_v02, status)
};

/*
 * qmiLocGetNmeaTypesReqMsgT is empty
 * static const uint8_t qmiLocGetNmeaTypesReqMsgT_data_v02[] = {
 * };
 */

static const uint8_t qmiLocGetNmeaTypesIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetNmeaTypesIndMsgT_v02, status),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetNmeaTypesIndMsgT_v02, nmeaSentenceType) - QMI_IDL_OFFSET8(qmiLocGetNmeaTypesIndMsgT_v02, nmeaSentenceType_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetNmeaTypesIndMsgT_v02, nmeaSentenceType)
};

static const uint8_t qmiLocSetLowPowerModeReqMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetLowPowerModeReqMsgT_v02, lowPowerMode)
};

static const uint8_t qmiLocSetLowPowerModeIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetLowPowerModeIndMsgT_v02, status)
};

/*
 * qmiLocGetLowPowerModeReqMsgT is empty
 * static const uint8_t qmiLocGetLowPowerModeReqMsgT_data_v02[] = {
 * };
 */

static const uint8_t qmiLocGetLowPowerModeIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetLowPowerModeIndMsgT_v02, status),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetLowPowerModeIndMsgT_v02, lowPowerMode) - QMI_IDL_OFFSET8(qmiLocGetLowPowerModeIndMsgT_v02, lowPowerMode_valid)),
  0x10,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetLowPowerModeIndMsgT_v02, lowPowerMode)
};

static const uint8_t qmiLocSetServerReqMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetServerReqMsgT_v02, serverType),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetServerReqMsgT_v02, ipv4Addr) - QMI_IDL_OFFSET8(qmiLocSetServerReqMsgT_v02, ipv4Addr_valid)),
  0x10,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocSetServerReqMsgT_v02, ipv4Addr),
  QMI_IDL_TYPE88(0, 8),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetServerReqMsgT_v02, ipv6Addr) - QMI_IDL_OFFSET8(qmiLocSetServerReqMsgT_v02, ipv6Addr_valid)),
  0x11,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocSetServerReqMsgT_v02, ipv6Addr),
  QMI_IDL_TYPE88(0, 9),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetServerReqMsgT_v02, urlAddr) - QMI_IDL_OFFSET8(qmiLocSetServerReqMsgT_v02, urlAddr_valid)),
  0x12,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_STRING,
  QMI_IDL_OFFSET8(qmiLocSetServerReqMsgT_v02, urlAddr),
  QMI_LOC_MAX_SERVER_ADDR_LENGTH_V02
};

static const uint8_t qmiLocSetServerIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetServerIndMsgT_v02, status)
};

static const uint8_t qmiLocGetServerReqMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetServerReqMsgT_v02, serverType),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetServerReqMsgT_v02, serverAddrTypeMask) - QMI_IDL_OFFSET8(qmiLocGetServerReqMsgT_v02, serverAddrTypeMask_valid)),
  0x10,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetServerReqMsgT_v02, serverAddrTypeMask)
};

static const uint8_t qmiLocGetServerIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetServerIndMsgT_v02, status),

  0x02,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetServerIndMsgT_v02, serverType),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetServerIndMsgT_v02, ipv4Addr) - QMI_IDL_OFFSET8(qmiLocGetServerIndMsgT_v02, ipv4Addr_valid)),
  0x10,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocGetServerIndMsgT_v02, ipv4Addr),
  QMI_IDL_TYPE88(0, 8),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetServerIndMsgT_v02, ipv6Addr) - QMI_IDL_OFFSET8(qmiLocGetServerIndMsgT_v02, ipv6Addr_valid)),
  0x11,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocGetServerIndMsgT_v02, ipv6Addr),
  QMI_IDL_TYPE88(0, 9),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetServerIndMsgT_v02, urlAddr) - QMI_IDL_OFFSET8(qmiLocGetServerIndMsgT_v02, urlAddr_valid)),
  0x12,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_STRING,
  QMI_IDL_OFFSET8(qmiLocGetServerIndMsgT_v02, urlAddr),
  QMI_LOC_MAX_SERVER_ADDR_LENGTH_V02
};

static const uint8_t qmiLocDeleteAssistDataReqMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocDeleteAssistDataReqMsgT_v02, deleteAllFlag),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocDeleteAssistDataReqMsgT_v02, deleteSvInfoList) - QMI_IDL_OFFSET8(qmiLocDeleteAssistDataReqMsgT_v02, deleteSvInfoList_valid)),
  0x10,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocDeleteAssistDataReqMsgT_v02, deleteSvInfoList),
  QMI_LOC_DELETE_MAX_SV_INFO_LENGTH_V02,
  QMI_IDL_OFFSET8(qmiLocDeleteAssistDataReqMsgT_v02, deleteSvInfoList) - QMI_IDL_OFFSET8(qmiLocDeleteAssistDataReqMsgT_v02, deleteSvInfoList_len),
  QMI_IDL_TYPE88(0, 27),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocDeleteAssistDataReqMsgT_v02, deleteGnssDataMask) - QMI_IDL_OFFSET16RELATIVE(qmiLocDeleteAssistDataReqMsgT_v02, deleteGnssDataMask_valid)),
  0x11,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocDeleteAssistDataReqMsgT_v02, deleteGnssDataMask),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocDeleteAssistDataReqMsgT_v02, deleteCellDbDataMask) - QMI_IDL_OFFSET16RELATIVE(qmiLocDeleteAssistDataReqMsgT_v02, deleteCellDbDataMask_valid)),
  0x12,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocDeleteAssistDataReqMsgT_v02, deleteCellDbDataMask),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocDeleteAssistDataReqMsgT_v02, deleteClockInfoMask) - QMI_IDL_OFFSET16RELATIVE(qmiLocDeleteAssistDataReqMsgT_v02, deleteClockInfoMask_valid)),
  0x13,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocDeleteAssistDataReqMsgT_v02, deleteClockInfoMask),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocDeleteAssistDataReqMsgT_v02, deleteBdsSvInfoList) - QMI_IDL_OFFSET16RELATIVE(qmiLocDeleteAssistDataReqMsgT_v02, deleteBdsSvInfoList_valid)),
  0x14,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET16ARRAY(qmiLocDeleteAssistDataReqMsgT_v02, deleteBdsSvInfoList),
  QMI_LOC_DELETE_MAX_BDS_SV_INFO_LENGTH_V02,
  QMI_IDL_OFFSET16RELATIVE(qmiLocDeleteAssistDataReqMsgT_v02, deleteBdsSvInfoList) - QMI_IDL_OFFSET16RELATIVE(qmiLocDeleteAssistDataReqMsgT_v02, deleteBdsSvInfoList_len),
  QMI_IDL_TYPE88(0, 28),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocDeleteAssistDataReqMsgT_v02, deleteGalSvInfoList) - QMI_IDL_OFFSET16RELATIVE(qmiLocDeleteAssistDataReqMsgT_v02, deleteGalSvInfoList_valid)),
  0x15,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET16ARRAY(qmiLocDeleteAssistDataReqMsgT_v02, deleteGalSvInfoList),
  QMI_LOC_DELETE_MAX_GAL_SV_INFO_LENGTH_V02,
  QMI_IDL_OFFSET16RELATIVE(qmiLocDeleteAssistDataReqMsgT_v02, deleteGalSvInfoList) - QMI_IDL_OFFSET16RELATIVE(qmiLocDeleteAssistDataReqMsgT_v02, deleteGalSvInfoList_len),
  QMI_IDL_TYPE88(0, 61)
};

static const uint8_t qmiLocDeleteAssistDataIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocDeleteAssistDataIndMsgT_v02, status)
};

static const uint8_t qmiLocSetXtraTSessionControlReqMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetXtraTSessionControlReqMsgT_v02, xtraTSessionControl)
};

static const uint8_t qmiLocSetXtraTSessionControlIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetXtraTSessionControlIndMsgT_v02, status)
};

/*
 * qmiLocGetXtraTSessionControlReqMsgT is empty
 * static const uint8_t qmiLocGetXtraTSessionControlReqMsgT_data_v02[] = {
 * };
 */

static const uint8_t qmiLocGetXtraTSessionControlIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetXtraTSessionControlIndMsgT_v02, status),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetXtraTSessionControlIndMsgT_v02, xtraTSessionControl) - QMI_IDL_OFFSET8(qmiLocGetXtraTSessionControlIndMsgT_v02, xtraTSessionControl_valid)),
  0x10,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetXtraTSessionControlIndMsgT_v02, xtraTSessionControl)
};

static const uint8_t qmiLocInjectWifiPositionReqMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocInjectWifiPositionReqMsgT_v02, wifiFixTime) - QMI_IDL_OFFSET8(qmiLocInjectWifiPositionReqMsgT_v02, wifiFixTime_valid)),
  0x10,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocInjectWifiPositionReqMsgT_v02, wifiFixTime),
  QMI_IDL_TYPE88(0, 29),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocInjectWifiPositionReqMsgT_v02, wifiFixPosition) - QMI_IDL_OFFSET8(qmiLocInjectWifiPositionReqMsgT_v02, wifiFixPosition_valid)),
  0x11,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocInjectWifiPositionReqMsgT_v02, wifiFixPosition),
  QMI_IDL_TYPE88(0, 30),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocInjectWifiPositionReqMsgT_v02, apInfo) - QMI_IDL_OFFSET8(qmiLocInjectWifiPositionReqMsgT_v02, apInfo_valid)),
  0x12,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocInjectWifiPositionReqMsgT_v02, apInfo),
  QMI_LOC_WIFI_MAX_REPORTED_APS_PER_MSG_V02,
  QMI_IDL_OFFSET8(qmiLocInjectWifiPositionReqMsgT_v02, apInfo) - QMI_IDL_OFFSET8(qmiLocInjectWifiPositionReqMsgT_v02, apInfo_len),
  QMI_IDL_TYPE88(0, 31),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocInjectWifiPositionReqMsgT_v02, horizontalReliability) - QMI_IDL_OFFSET16RELATIVE(qmiLocInjectWifiPositionReqMsgT_v02, horizontalReliability_valid)),
  0x13,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocInjectWifiPositionReqMsgT_v02, horizontalReliability),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocInjectWifiPositionReqMsgT_v02, rawHepe) - QMI_IDL_OFFSET16RELATIVE(qmiLocInjectWifiPositionReqMsgT_v02, rawHepe_valid)),
  0x14,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocInjectWifiPositionReqMsgT_v02, rawHepe),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocInjectWifiPositionReqMsgT_v02, wifiApSsidInfo) - QMI_IDL_OFFSET16RELATIVE(qmiLocInjectWifiPositionReqMsgT_v02, wifiApSsidInfo_valid)),
  0x15,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET16ARRAY(qmiLocInjectWifiPositionReqMsgT_v02, wifiApSsidInfo),
  QMI_LOC_WIFI_MAX_REPORTED_APS_PER_MSG_V02,
  QMI_IDL_OFFSET16RELATIVE(qmiLocInjectWifiPositionReqMsgT_v02, wifiApSsidInfo) - QMI_IDL_OFFSET16RELATIVE(qmiLocInjectWifiPositionReqMsgT_v02, wifiApSsidInfo_len),
  QMI_IDL_TYPE88(0, 32)
};

static const uint8_t qmiLocInjectWifiPositionIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectWifiPositionIndMsgT_v02, status)
};

static const uint8_t qmiLocNotifyWifiStatusReqMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocNotifyWifiStatusReqMsgT_v02, wifiStatus)
};

static const uint8_t qmiLocNotifyWifiStatusIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocNotifyWifiStatusIndMsgT_v02, status)
};

/*
 * qmiLocGetRegisteredEventsReqMsgT is empty
 * static const uint8_t qmiLocGetRegisteredEventsReqMsgT_data_v02[] = {
 * };
 */

static const uint8_t qmiLocGetRegisteredEventsIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetRegisteredEventsIndMsgT_v02, status),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetRegisteredEventsIndMsgT_v02, eventRegMask) - QMI_IDL_OFFSET8(qmiLocGetRegisteredEventsIndMsgT_v02, eventRegMask_valid)),
  0x10,
   QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetRegisteredEventsIndMsgT_v02, eventRegMask)
};

static const uint8_t qmiLocSetOperationModeReqMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetOperationModeReqMsgT_v02, operationMode)
};

static const uint8_t qmiLocSetOperationModeIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetOperationModeIndMsgT_v02, status)
};

/*
 * qmiLocGetOperationModeReqMsgT is empty
 * static const uint8_t qmiLocGetOperationModeReqMsgT_data_v02[] = {
 * };
 */

static const uint8_t qmiLocGetOperationModeIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetOperationModeIndMsgT_v02, status),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetOperationModeIndMsgT_v02, operationMode) - QMI_IDL_OFFSET8(qmiLocGetOperationModeIndMsgT_v02, operationMode_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetOperationModeIndMsgT_v02, operationMode)
};

static const uint8_t qmiLocSetSpiStatusReqMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetSpiStatusReqMsgT_v02, stationary),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetSpiStatusReqMsgT_v02, confidenceStationary) - QMI_IDL_OFFSET8(qmiLocSetSpiStatusReqMsgT_v02, confidenceStationary_valid)),
  0x10,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetSpiStatusReqMsgT_v02, confidenceStationary)
};

static const uint8_t qmiLocSetSpiStatusIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetSpiStatusIndMsgT_v02, status)
};

static const uint8_t qmiLocInjectSensorDataReqMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocInjectSensorDataReqMsgT_v02, opaqueIdentifier) - QMI_IDL_OFFSET8(qmiLocInjectSensorDataReqMsgT_v02, opaqueIdentifier_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectSensorDataReqMsgT_v02, opaqueIdentifier),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocInjectSensorDataReqMsgT_v02, threeAxisAccelData) - QMI_IDL_OFFSET8(qmiLocInjectSensorDataReqMsgT_v02, threeAxisAccelData_valid)),
  0x11,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocInjectSensorDataReqMsgT_v02, threeAxisAccelData),
  QMI_IDL_TYPE88(0, 34),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocInjectSensorDataReqMsgT_v02, threeAxisGyroData) - QMI_IDL_OFFSET16RELATIVE(qmiLocInjectSensorDataReqMsgT_v02, threeAxisGyroData_valid)),
  0x12,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET16ARRAY(qmiLocInjectSensorDataReqMsgT_v02, threeAxisGyroData),
  QMI_IDL_TYPE88(0, 34),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocInjectSensorDataReqMsgT_v02, threeAxisAccelDataTimeSource) - QMI_IDL_OFFSET16RELATIVE(qmiLocInjectSensorDataReqMsgT_v02, threeAxisAccelDataTimeSource_valid)),
  0x13,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocInjectSensorDataReqMsgT_v02, threeAxisAccelDataTimeSource),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocInjectSensorDataReqMsgT_v02, threeAxisGyroDataTimeSource) - QMI_IDL_OFFSET16RELATIVE(qmiLocInjectSensorDataReqMsgT_v02, threeAxisGyroDataTimeSource_valid)),
  0x14,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocInjectSensorDataReqMsgT_v02, threeAxisGyroDataTimeSource),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocInjectSensorDataReqMsgT_v02, accelTemperatureData) - QMI_IDL_OFFSET16RELATIVE(qmiLocInjectSensorDataReqMsgT_v02, accelTemperatureData_valid)),
  0x15,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET16ARRAY(qmiLocInjectSensorDataReqMsgT_v02, accelTemperatureData),
  QMI_IDL_TYPE88(0, 36),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocInjectSensorDataReqMsgT_v02, gyroTemperatureData) - QMI_IDL_OFFSET16RELATIVE(qmiLocInjectSensorDataReqMsgT_v02, gyroTemperatureData_valid)),
  0x16,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET16ARRAY(qmiLocInjectSensorDataReqMsgT_v02, gyroTemperatureData),
  QMI_IDL_TYPE88(0, 36),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocInjectSensorDataReqMsgT_v02, threeAxisMagData) - QMI_IDL_OFFSET16RELATIVE(qmiLocInjectSensorDataReqMsgT_v02, threeAxisMagData_valid)),
  0x17,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET16ARRAY(qmiLocInjectSensorDataReqMsgT_v02, threeAxisMagData),
  QMI_IDL_TYPE88(0, 34),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocInjectSensorDataReqMsgT_v02, threeAxisMagDataTimeSource) - QMI_IDL_OFFSET16RELATIVE(qmiLocInjectSensorDataReqMsgT_v02, threeAxisMagDataTimeSource_valid)),
  0x18,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocInjectSensorDataReqMsgT_v02, threeAxisMagDataTimeSource)
};

static const uint8_t qmiLocInjectSensorDataIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectSensorDataIndMsgT_v02, status),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocInjectSensorDataIndMsgT_v02, opaqueIdentifier) - QMI_IDL_OFFSET8(qmiLocInjectSensorDataIndMsgT_v02, opaqueIdentifier_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectSensorDataIndMsgT_v02, opaqueIdentifier),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocInjectSensorDataIndMsgT_v02, threeAxisAccelSamplesAccepted) - QMI_IDL_OFFSET8(qmiLocInjectSensorDataIndMsgT_v02, threeAxisAccelSamplesAccepted_valid)),
  0x11,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectSensorDataIndMsgT_v02, threeAxisAccelSamplesAccepted),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocInjectSensorDataIndMsgT_v02, threeAxisGyroSamplesAccepted) - QMI_IDL_OFFSET8(qmiLocInjectSensorDataIndMsgT_v02, threeAxisGyroSamplesAccepted_valid)),
  0x12,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectSensorDataIndMsgT_v02, threeAxisGyroSamplesAccepted),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocInjectSensorDataIndMsgT_v02, accelTemperatureSamplesAccepted) - QMI_IDL_OFFSET8(qmiLocInjectSensorDataIndMsgT_v02, accelTemperatureSamplesAccepted_valid)),
  0x13,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectSensorDataIndMsgT_v02, accelTemperatureSamplesAccepted),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocInjectSensorDataIndMsgT_v02, gyroTemperatureSamplesAccepted) - QMI_IDL_OFFSET8(qmiLocInjectSensorDataIndMsgT_v02, gyroTemperatureSamplesAccepted_valid)),
  0x14,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectSensorDataIndMsgT_v02, gyroTemperatureSamplesAccepted),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocInjectSensorDataIndMsgT_v02, threeAxisMagSamplesAccepted) - QMI_IDL_OFFSET8(qmiLocInjectSensorDataIndMsgT_v02, threeAxisMagSamplesAccepted_valid)),
  0x15,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectSensorDataIndMsgT_v02, threeAxisMagSamplesAccepted)
};

static const uint8_t qmiLocInjectTimeSyncDataReqMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectTimeSyncDataReqMsgT_v02, refCounter),

  0x02,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectTimeSyncDataReqMsgT_v02, sensorProcRxTime),

  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x03,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectTimeSyncDataReqMsgT_v02, sensorProcTxTime)
};

static const uint8_t qmiLocInjectTimeSyncDataIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectTimeSyncDataIndMsgT_v02, status)
};

/*
 * qmiLocGetCradleMountConfigReqMsgT is empty
 * static const uint8_t qmiLocGetCradleMountConfigReqMsgT_data_v02[] = {
 * };
 */

static const uint8_t qmiLocGetCradleMountConfigIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetCradleMountConfigIndMsgT_v02, status),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetCradleMountConfigIndMsgT_v02, cradleMountState) - QMI_IDL_OFFSET8(qmiLocGetCradleMountConfigIndMsgT_v02, cradleMountState_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetCradleMountConfigIndMsgT_v02, cradleMountState),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetCradleMountConfigIndMsgT_v02, confidenceCradleMountState) - QMI_IDL_OFFSET8(qmiLocGetCradleMountConfigIndMsgT_v02, confidenceCradleMountState_valid)),
  0x11,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetCradleMountConfigIndMsgT_v02, confidenceCradleMountState)
};

static const uint8_t qmiLocSetCradleMountConfigReqMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetCradleMountConfigReqMsgT_v02, cradleMountState),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetCradleMountConfigReqMsgT_v02, confidenceCradleMountState) - QMI_IDL_OFFSET8(qmiLocSetCradleMountConfigReqMsgT_v02, confidenceCradleMountState_valid)),
  0x10,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetCradleMountConfigReqMsgT_v02, confidenceCradleMountState)
};

static const uint8_t qmiLocSetCradleMountConfigIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetCradleMountConfigIndMsgT_v02, status)
};

/*
 * qmiLocGetExternalPowerConfigReqMsgT is empty
 * static const uint8_t qmiLocGetExternalPowerConfigReqMsgT_data_v02[] = {
 * };
 */

static const uint8_t qmiLocGetExternalPowerConfigIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetExternalPowerConfigIndMsgT_v02, status),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetExternalPowerConfigIndMsgT_v02, externalPowerState) - QMI_IDL_OFFSET8(qmiLocGetExternalPowerConfigIndMsgT_v02, externalPowerState_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetExternalPowerConfigIndMsgT_v02, externalPowerState)
};

static const uint8_t qmiLocSetExternalPowerConfigReqMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetExternalPowerConfigReqMsgT_v02, externalPowerState)
};

static const uint8_t qmiLocSetExternalPowerConfigIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetExternalPowerConfigIndMsgT_v02, status)
};

static const uint8_t qmiLocInformLocationServerConnStatusReqMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInformLocationServerConnStatusReqMsgT_v02, connHandle),

  0x02,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInformLocationServerConnStatusReqMsgT_v02, requestType),

  0x03,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInformLocationServerConnStatusReqMsgT_v02, statusType),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocInformLocationServerConnStatusReqMsgT_v02, apnProfile) - QMI_IDL_OFFSET8(qmiLocInformLocationServerConnStatusReqMsgT_v02, apnProfile_valid)),
  0x10,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocInformLocationServerConnStatusReqMsgT_v02, apnProfile),
  QMI_IDL_TYPE88(0, 37)
};

static const uint8_t qmiLocInformLocationServerConnStatusIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInformLocationServerConnStatusIndMsgT_v02, status)
};

static const uint8_t qmiLocSetProtocolConfigParametersReqMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetProtocolConfigParametersReqMsgT_v02, suplSecurity) - QMI_IDL_OFFSET8(qmiLocSetProtocolConfigParametersReqMsgT_v02, suplSecurity_valid)),
  0x10,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetProtocolConfigParametersReqMsgT_v02, suplSecurity),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetProtocolConfigParametersReqMsgT_v02, vxVersion) - QMI_IDL_OFFSET8(qmiLocSetProtocolConfigParametersReqMsgT_v02, vxVersion_valid)),
  0x11,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetProtocolConfigParametersReqMsgT_v02, vxVersion),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetProtocolConfigParametersReqMsgT_v02, suplVersion) - QMI_IDL_OFFSET8(qmiLocSetProtocolConfigParametersReqMsgT_v02, suplVersion_valid)),
  0x12,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetProtocolConfigParametersReqMsgT_v02, suplVersion),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetProtocolConfigParametersReqMsgT_v02, lppConfig) - QMI_IDL_OFFSET8(qmiLocSetProtocolConfigParametersReqMsgT_v02, lppConfig_valid)),
  0x13,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetProtocolConfigParametersReqMsgT_v02, lppConfig),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetProtocolConfigParametersReqMsgT_v02, assistedGlonassProtocolMask) - QMI_IDL_OFFSET8(qmiLocSetProtocolConfigParametersReqMsgT_v02, assistedGlonassProtocolMask_valid)),
  0x14,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetProtocolConfigParametersReqMsgT_v02, assistedGlonassProtocolMask),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetProtocolConfigParametersReqMsgT_v02, suplHashAlgo) - QMI_IDL_OFFSET8(qmiLocSetProtocolConfigParametersReqMsgT_v02, suplHashAlgo_valid)),
  0x15,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetProtocolConfigParametersReqMsgT_v02, suplHashAlgo),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetProtocolConfigParametersReqMsgT_v02, suplTlsVersion) - QMI_IDL_OFFSET8(qmiLocSetProtocolConfigParametersReqMsgT_v02, suplTlsVersion_valid)),
  0x16,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetProtocolConfigParametersReqMsgT_v02, suplTlsVersion),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetProtocolConfigParametersReqMsgT_v02, emergencyProtocol) - QMI_IDL_OFFSET8(qmiLocSetProtocolConfigParametersReqMsgT_v02, emergencyProtocol_valid)),
  0x17,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetProtocolConfigParametersReqMsgT_v02, emergencyProtocol),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetProtocolConfigParametersReqMsgT_v02, wifiScanInjectTimeout) - QMI_IDL_OFFSET8(qmiLocSetProtocolConfigParametersReqMsgT_v02, wifiScanInjectTimeout_valid)),
  0x18,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetProtocolConfigParametersReqMsgT_v02, wifiScanInjectTimeout)
};

static const uint8_t qmiLocSetProtocolConfigParametersIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetProtocolConfigParametersIndMsgT_v02, status),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetProtocolConfigParametersIndMsgT_v02, failedProtocolConfigParamMask) - QMI_IDL_OFFSET8(qmiLocSetProtocolConfigParametersIndMsgT_v02, failedProtocolConfigParamMask_valid)),
  0x10,
   QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetProtocolConfigParametersIndMsgT_v02, failedProtocolConfigParamMask)
};

static const uint8_t qmiLocGetProtocolConfigParametersReqMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetProtocolConfigParametersReqMsgT_v02, getProtocolConfigParamMask)
};

static const uint8_t qmiLocGetProtocolConfigParametersIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetProtocolConfigParametersIndMsgT_v02, status),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetProtocolConfigParametersIndMsgT_v02, suplSecurity) - QMI_IDL_OFFSET8(qmiLocGetProtocolConfigParametersIndMsgT_v02, suplSecurity_valid)),
  0x10,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetProtocolConfigParametersIndMsgT_v02, suplSecurity),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetProtocolConfigParametersIndMsgT_v02, vxVersion) - QMI_IDL_OFFSET8(qmiLocGetProtocolConfigParametersIndMsgT_v02, vxVersion_valid)),
  0x11,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetProtocolConfigParametersIndMsgT_v02, vxVersion),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetProtocolConfigParametersIndMsgT_v02, suplVersion) - QMI_IDL_OFFSET8(qmiLocGetProtocolConfigParametersIndMsgT_v02, suplVersion_valid)),
  0x12,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetProtocolConfigParametersIndMsgT_v02, suplVersion),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetProtocolConfigParametersIndMsgT_v02, lppConfig) - QMI_IDL_OFFSET8(qmiLocGetProtocolConfigParametersIndMsgT_v02, lppConfig_valid)),
  0x13,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetProtocolConfigParametersIndMsgT_v02, lppConfig),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetProtocolConfigParametersIndMsgT_v02, assistedGlonassProtocolMask) - QMI_IDL_OFFSET8(qmiLocGetProtocolConfigParametersIndMsgT_v02, assistedGlonassProtocolMask_valid)),
  0x14,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetProtocolConfigParametersIndMsgT_v02, assistedGlonassProtocolMask),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetProtocolConfigParametersIndMsgT_v02, suplHashAlgo) - QMI_IDL_OFFSET8(qmiLocGetProtocolConfigParametersIndMsgT_v02, suplHashAlgo_valid)),
  0x15,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetProtocolConfigParametersIndMsgT_v02, suplHashAlgo),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetProtocolConfigParametersIndMsgT_v02, suplTlsVersion) - QMI_IDL_OFFSET8(qmiLocGetProtocolConfigParametersIndMsgT_v02, suplTlsVersion_valid)),
  0x16,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetProtocolConfigParametersIndMsgT_v02, suplTlsVersion),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetProtocolConfigParametersIndMsgT_v02, emergencyProtocol) - QMI_IDL_OFFSET8(qmiLocGetProtocolConfigParametersIndMsgT_v02, emergencyProtocol_valid)),
  0x17,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetProtocolConfigParametersIndMsgT_v02, emergencyProtocol),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetProtocolConfigParametersIndMsgT_v02, wifiScanInjectTimeout) - QMI_IDL_OFFSET8(qmiLocGetProtocolConfigParametersIndMsgT_v02, wifiScanInjectTimeout_valid)),
  0x18,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetProtocolConfigParametersIndMsgT_v02, wifiScanInjectTimeout)
};

static const uint8_t qmiLocSetSensorControlConfigReqMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetSensorControlConfigReqMsgT_v02, sensorsUsage) - QMI_IDL_OFFSET8(qmiLocSetSensorControlConfigReqMsgT_v02, sensorsUsage_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetSensorControlConfigReqMsgT_v02, sensorsUsage),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetSensorControlConfigReqMsgT_v02, sensorProvider) - QMI_IDL_OFFSET8(qmiLocSetSensorControlConfigReqMsgT_v02, sensorProvider_valid)),
  0x11,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetSensorControlConfigReqMsgT_v02, sensorProvider)
};

static const uint8_t qmiLocSetSensorControlConfigIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetSensorControlConfigIndMsgT_v02, status)
};

/*
 * qmiLocGetSensorControlConfigReqMsgT is empty
 * static const uint8_t qmiLocGetSensorControlConfigReqMsgT_data_v02[] = {
 * };
 */

static const uint8_t qmiLocGetSensorControlConfigIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetSensorControlConfigIndMsgT_v02, status),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetSensorControlConfigIndMsgT_v02, sensorsUsage) - QMI_IDL_OFFSET8(qmiLocGetSensorControlConfigIndMsgT_v02, sensorsUsage_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetSensorControlConfigIndMsgT_v02, sensorsUsage),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetSensorControlConfigIndMsgT_v02, sensorProvider) - QMI_IDL_OFFSET8(qmiLocGetSensorControlConfigIndMsgT_v02, sensorProvider_valid)),
  0x11,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetSensorControlConfigIndMsgT_v02, sensorProvider)
};

static const uint8_t qmiLocSetSensorPropertiesReqMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetSensorPropertiesReqMsgT_v02, gyroBiasVarianceRandomWalk) - QMI_IDL_OFFSET8(qmiLocSetSensorPropertiesReqMsgT_v02, gyroBiasVarianceRandomWalk_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetSensorPropertiesReqMsgT_v02, gyroBiasVarianceRandomWalk),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetSensorPropertiesReqMsgT_v02, velocityRandomWalkSpectralDensity) - QMI_IDL_OFFSET8(qmiLocSetSensorPropertiesReqMsgT_v02, velocityRandomWalkSpectralDensity_valid)),
  0x11,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetSensorPropertiesReqMsgT_v02, velocityRandomWalkSpectralDensity),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetSensorPropertiesReqMsgT_v02, accelerationRandomWalkSpectralDensity) - QMI_IDL_OFFSET8(qmiLocSetSensorPropertiesReqMsgT_v02, accelerationRandomWalkSpectralDensity_valid)),
  0x12,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetSensorPropertiesReqMsgT_v02, accelerationRandomWalkSpectralDensity),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetSensorPropertiesReqMsgT_v02, angleRandomWalkSpectralDensity) - QMI_IDL_OFFSET8(qmiLocSetSensorPropertiesReqMsgT_v02, angleRandomWalkSpectralDensity_valid)),
  0x13,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetSensorPropertiesReqMsgT_v02, angleRandomWalkSpectralDensity),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetSensorPropertiesReqMsgT_v02, rateRandomWalkSpectralDensity) - QMI_IDL_OFFSET8(qmiLocSetSensorPropertiesReqMsgT_v02, rateRandomWalkSpectralDensity_valid)),
  0x14,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetSensorPropertiesReqMsgT_v02, rateRandomWalkSpectralDensity),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetSensorPropertiesReqMsgT_v02, vehicleDataUse) - QMI_IDL_OFFSET8(qmiLocSetSensorPropertiesReqMsgT_v02, vehicleDataUse_valid)),
  0x15,
   QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetSensorPropertiesReqMsgT_v02, vehicleDataUse),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetSensorPropertiesReqMsgT_v02, vehicleVelocityRandomWalkSpectralDensity) - QMI_IDL_OFFSET8(qmiLocSetSensorPropertiesReqMsgT_v02, vehicleVelocityRandomWalkSpectralDensity_valid)),
  0x16,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetSensorPropertiesReqMsgT_v02, vehicleVelocityRandomWalkSpectralDensity),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetSensorPropertiesReqMsgT_v02, vehicleAccelRandomWalkSpectralDensity) - QMI_IDL_OFFSET8(qmiLocSetSensorPropertiesReqMsgT_v02, vehicleAccelRandomWalkSpectralDensity_valid)),
  0x17,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetSensorPropertiesReqMsgT_v02, vehicleAccelRandomWalkSpectralDensity),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetSensorPropertiesReqMsgT_v02, vehicleAngleRandomWalkSpectralDensity) - QMI_IDL_OFFSET8(qmiLocSetSensorPropertiesReqMsgT_v02, vehicleAngleRandomWalkSpectralDensity_valid)),
  0x18,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetSensorPropertiesReqMsgT_v02, vehicleAngleRandomWalkSpectralDensity),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetSensorPropertiesReqMsgT_v02, vehicleAngularRateRandomWalkSpectralDensity) - QMI_IDL_OFFSET8(qmiLocSetSensorPropertiesReqMsgT_v02, vehicleAngularRateRandomWalkSpectralDensity_valid)),
  0x19,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetSensorPropertiesReqMsgT_v02, vehicleAngularRateRandomWalkSpectralDensity),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetSensorPropertiesReqMsgT_v02, vehicleOdometryScaleFactorRandomWalkSpectralDensity) - QMI_IDL_OFFSET8(qmiLocSetSensorPropertiesReqMsgT_v02, vehicleOdometryScaleFactorRandomWalkSpectralDensity_valid)),
  0x1A,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetSensorPropertiesReqMsgT_v02, vehicleOdometryScaleFactorRandomWalkSpectralDensity),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetSensorPropertiesReqMsgT_v02, vehicleOdometryVariance) - QMI_IDL_OFFSET8(qmiLocSetSensorPropertiesReqMsgT_v02, vehicleOdometryVariance_valid)),
  0x1B,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetSensorPropertiesReqMsgT_v02, vehicleOdometryVariance)
};

static const uint8_t qmiLocSetSensorPropertiesIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetSensorPropertiesIndMsgT_v02, status),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetSensorPropertiesIndMsgT_v02, failedSensorPropertiesMask) - QMI_IDL_OFFSET8(qmiLocSetSensorPropertiesIndMsgT_v02, failedSensorPropertiesMask_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetSensorPropertiesIndMsgT_v02, failedSensorPropertiesMask)
};

static const uint8_t qmiLocGetSensorPropertiesReqMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetSensorPropertiesReqMsgT_v02, getSensorPropertiesMask)
};

static const uint8_t qmiLocGetSensorPropertiesIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetSensorPropertiesIndMsgT_v02, status),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetSensorPropertiesIndMsgT_v02, gyroBiasVarianceRandomWalk) - QMI_IDL_OFFSET8(qmiLocGetSensorPropertiesIndMsgT_v02, gyroBiasVarianceRandomWalk_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetSensorPropertiesIndMsgT_v02, gyroBiasVarianceRandomWalk),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetSensorPropertiesIndMsgT_v02, velocityRandomWalkSpectralDensity) - QMI_IDL_OFFSET8(qmiLocGetSensorPropertiesIndMsgT_v02, velocityRandomWalkSpectralDensity_valid)),
  0x11,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetSensorPropertiesIndMsgT_v02, velocityRandomWalkSpectralDensity),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetSensorPropertiesIndMsgT_v02, accelerationRandomWalkSpectralDensity) - QMI_IDL_OFFSET8(qmiLocGetSensorPropertiesIndMsgT_v02, accelerationRandomWalkSpectralDensity_valid)),
  0x12,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetSensorPropertiesIndMsgT_v02, accelerationRandomWalkSpectralDensity),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetSensorPropertiesIndMsgT_v02, angleRandomWalkSpectralDensity) - QMI_IDL_OFFSET8(qmiLocGetSensorPropertiesIndMsgT_v02, angleRandomWalkSpectralDensity_valid)),
  0x13,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetSensorPropertiesIndMsgT_v02, angleRandomWalkSpectralDensity),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetSensorPropertiesIndMsgT_v02, rateRandomWalkSpectralDensity) - QMI_IDL_OFFSET8(qmiLocGetSensorPropertiesIndMsgT_v02, rateRandomWalkSpectralDensity_valid)),
  0x14,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetSensorPropertiesIndMsgT_v02, rateRandomWalkSpectralDensity),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetSensorPropertiesIndMsgT_v02, vehicleDataUse) - QMI_IDL_OFFSET8(qmiLocGetSensorPropertiesIndMsgT_v02, vehicleDataUse_valid)),
  0x15,
   QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetSensorPropertiesIndMsgT_v02, vehicleDataUse),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetSensorPropertiesIndMsgT_v02, vehicleVelocityRandomWalkSpectralDensity) - QMI_IDL_OFFSET8(qmiLocGetSensorPropertiesIndMsgT_v02, vehicleVelocityRandomWalkSpectralDensity_valid)),
  0x16,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetSensorPropertiesIndMsgT_v02, vehicleVelocityRandomWalkSpectralDensity),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetSensorPropertiesIndMsgT_v02, vehicleAccelRandomWalkSpectralDensity) - QMI_IDL_OFFSET8(qmiLocGetSensorPropertiesIndMsgT_v02, vehicleAccelRandomWalkSpectralDensity_valid)),
  0x17,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetSensorPropertiesIndMsgT_v02, vehicleAccelRandomWalkSpectralDensity),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetSensorPropertiesIndMsgT_v02, vehicleAngleRandomWalkSpectralDensity) - QMI_IDL_OFFSET8(qmiLocGetSensorPropertiesIndMsgT_v02, vehicleAngleRandomWalkSpectralDensity_valid)),
  0x18,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetSensorPropertiesIndMsgT_v02, vehicleAngleRandomWalkSpectralDensity),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetSensorPropertiesIndMsgT_v02, vehicleAngularRateRandomWalkSpectralDensity) - QMI_IDL_OFFSET8(qmiLocGetSensorPropertiesIndMsgT_v02, vehicleAngularRateRandomWalkSpectralDensity_valid)),
  0x19,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetSensorPropertiesIndMsgT_v02, vehicleAngularRateRandomWalkSpectralDensity),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetSensorPropertiesIndMsgT_v02, vehicleOdometryScaleFactorRandomWalkSpectralDensity) - QMI_IDL_OFFSET8(qmiLocGetSensorPropertiesIndMsgT_v02, vehicleOdometryScaleFactorRandomWalkSpectralDensity_valid)),
  0x1A,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetSensorPropertiesIndMsgT_v02, vehicleOdometryScaleFactorRandomWalkSpectralDensity),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetSensorPropertiesIndMsgT_v02, vehicleOdometryVariance) - QMI_IDL_OFFSET8(qmiLocGetSensorPropertiesIndMsgT_v02, vehicleOdometryVariance_valid)),
  0x1B,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetSensorPropertiesIndMsgT_v02, vehicleOdometryVariance)
};

static const uint8_t qmiLocSetSensorPerformanceControlConfigReqMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetSensorPerformanceControlConfigReqMsgT_v02, performanceControlMode) - QMI_IDL_OFFSET8(qmiLocSetSensorPerformanceControlConfigReqMsgT_v02, performanceControlMode_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetSensorPerformanceControlConfigReqMsgT_v02, performanceControlMode),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetSensorPerformanceControlConfigReqMsgT_v02, accelSamplingSpec) - QMI_IDL_OFFSET8(qmiLocSetSensorPerformanceControlConfigReqMsgT_v02, accelSamplingSpec_valid)),
  0x11,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocSetSensorPerformanceControlConfigReqMsgT_v02, accelSamplingSpec),
  QMI_IDL_TYPE88(0, 21),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetSensorPerformanceControlConfigReqMsgT_v02, gyroSamplingSpec) - QMI_IDL_OFFSET8(qmiLocSetSensorPerformanceControlConfigReqMsgT_v02, gyroSamplingSpec_valid)),
  0x12,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocSetSensorPerformanceControlConfigReqMsgT_v02, gyroSamplingSpec),
  QMI_IDL_TYPE88(0, 21),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetSensorPerformanceControlConfigReqMsgT_v02, algorithmConfig) - QMI_IDL_OFFSET8(qmiLocSetSensorPerformanceControlConfigReqMsgT_v02, algorithmConfig_valid)),
  0x13,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetSensorPerformanceControlConfigReqMsgT_v02, algorithmConfig),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetSensorPerformanceControlConfigReqMsgT_v02, accelSamplingSpecHigh) - QMI_IDL_OFFSET8(qmiLocSetSensorPerformanceControlConfigReqMsgT_v02, accelSamplingSpecHigh_valid)),
  0x14,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocSetSensorPerformanceControlConfigReqMsgT_v02, accelSamplingSpecHigh),
  QMI_IDL_TYPE88(0, 21),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetSensorPerformanceControlConfigReqMsgT_v02, gyroSamplingSpecHigh) - QMI_IDL_OFFSET8(qmiLocSetSensorPerformanceControlConfigReqMsgT_v02, gyroSamplingSpecHigh_valid)),
  0x15,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocSetSensorPerformanceControlConfigReqMsgT_v02, gyroSamplingSpecHigh),
  QMI_IDL_TYPE88(0, 21)
};

static const uint8_t qmiLocSetSensorPerformanceControlConfigIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetSensorPerformanceControlConfigIndMsgT_v02, status),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetSensorPerformanceControlConfigIndMsgT_v02, failedConfiguration) - QMI_IDL_OFFSET8(qmiLocSetSensorPerformanceControlConfigIndMsgT_v02, failedConfiguration_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetSensorPerformanceControlConfigIndMsgT_v02, failedConfiguration)
};

/*
 * qmiLocGetSensorPerformanceControlConfigReqMsgT is empty
 * static const uint8_t qmiLocGetSensorPerformanceControlConfigReqMsgT_data_v02[] = {
 * };
 */

static const uint8_t qmiLocGetSensorPerformanceControlConfigIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetSensorPerformanceControlConfigIndMsgT_v02, status),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetSensorPerformanceControlConfigIndMsgT_v02, performanceControlMode) - QMI_IDL_OFFSET8(qmiLocGetSensorPerformanceControlConfigIndMsgT_v02, performanceControlMode_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetSensorPerformanceControlConfigIndMsgT_v02, performanceControlMode),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetSensorPerformanceControlConfigIndMsgT_v02, accelSamplingSpec) - QMI_IDL_OFFSET8(qmiLocGetSensorPerformanceControlConfigIndMsgT_v02, accelSamplingSpec_valid)),
  0x11,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocGetSensorPerformanceControlConfigIndMsgT_v02, accelSamplingSpec),
  QMI_IDL_TYPE88(0, 21),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetSensorPerformanceControlConfigIndMsgT_v02, gyroSamplingSpec) - QMI_IDL_OFFSET8(qmiLocGetSensorPerformanceControlConfigIndMsgT_v02, gyroSamplingSpec_valid)),
  0x12,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocGetSensorPerformanceControlConfigIndMsgT_v02, gyroSamplingSpec),
  QMI_IDL_TYPE88(0, 21),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetSensorPerformanceControlConfigIndMsgT_v02, algorithmConfig) - QMI_IDL_OFFSET8(qmiLocGetSensorPerformanceControlConfigIndMsgT_v02, algorithmConfig_valid)),
  0x13,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetSensorPerformanceControlConfigIndMsgT_v02, algorithmConfig),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetSensorPerformanceControlConfigIndMsgT_v02, accelSamplingSpecHigh) - QMI_IDL_OFFSET8(qmiLocGetSensorPerformanceControlConfigIndMsgT_v02, accelSamplingSpecHigh_valid)),
  0x14,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocGetSensorPerformanceControlConfigIndMsgT_v02, accelSamplingSpecHigh),
  QMI_IDL_TYPE88(0, 21),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetSensorPerformanceControlConfigIndMsgT_v02, gyroSamplingSpecHigh) - QMI_IDL_OFFSET8(qmiLocGetSensorPerformanceControlConfigIndMsgT_v02, gyroSamplingSpecHigh_valid)),
  0x15,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocGetSensorPerformanceControlConfigIndMsgT_v02, gyroSamplingSpecHigh),
  QMI_IDL_TYPE88(0, 21)
};

static const uint8_t qmiLocInjectSuplCertificateReqMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectSuplCertificateReqMsgT_v02, suplCertId),

  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x02,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN | QMI_IDL_FLAGS_SZ_IS_16 |   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectSuplCertificateReqMsgT_v02, suplCertData),
  ((QMI_LOC_MAX_SUPL_CERT_LENGTH_V02) & 0xFF), ((QMI_LOC_MAX_SUPL_CERT_LENGTH_V02) >> 8),
  QMI_IDL_OFFSET8(qmiLocInjectSuplCertificateReqMsgT_v02, suplCertData) - QMI_IDL_OFFSET8(qmiLocInjectSuplCertificateReqMsgT_v02, suplCertData_len)
};

static const uint8_t qmiLocInjectSuplCertificateIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectSuplCertificateIndMsgT_v02, status)
};

static const uint8_t qmiLocDeleteSuplCertificateReqMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocDeleteSuplCertificateReqMsgT_v02, suplCertId) - QMI_IDL_OFFSET8(qmiLocDeleteSuplCertificateReqMsgT_v02, suplCertId_valid)),
  0x10,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocDeleteSuplCertificateReqMsgT_v02, suplCertId)
};

static const uint8_t qmiLocDeleteSuplCertificateIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocDeleteSuplCertificateIndMsgT_v02, status)
};

static const uint8_t qmiLocSetPositionEngineConfigParametersReqMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetPositionEngineConfigParametersReqMsgT_v02, injectedPositionControl) - QMI_IDL_OFFSET8(qmiLocSetPositionEngineConfigParametersReqMsgT_v02, injectedPositionControl_valid)),
  0x10,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetPositionEngineConfigParametersReqMsgT_v02, injectedPositionControl),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetPositionEngineConfigParametersReqMsgT_v02, filterSvUsage) - QMI_IDL_OFFSET8(qmiLocSetPositionEngineConfigParametersReqMsgT_v02, filterSvUsage_valid)),
  0x11,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetPositionEngineConfigParametersReqMsgT_v02, filterSvUsage),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetPositionEngineConfigParametersReqMsgT_v02, storeAssistData) - QMI_IDL_OFFSET8(qmiLocSetPositionEngineConfigParametersReqMsgT_v02, storeAssistData_valid)),
  0x12,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetPositionEngineConfigParametersReqMsgT_v02, storeAssistData),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetPositionEngineConfigParametersReqMsgT_v02, enableFasterTTFF) - QMI_IDL_OFFSET8(qmiLocSetPositionEngineConfigParametersReqMsgT_v02, enableFasterTTFF_valid)),
  0x13,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetPositionEngineConfigParametersReqMsgT_v02, enableFasterTTFF)
};

static const uint8_t qmiLocSetPositionEngineConfigParametersIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetPositionEngineConfigParametersIndMsgT_v02, status),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetPositionEngineConfigParametersIndMsgT_v02, failedPositionEngineConfigParamMask) - QMI_IDL_OFFSET8(qmiLocSetPositionEngineConfigParametersIndMsgT_v02, failedPositionEngineConfigParamMask_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetPositionEngineConfigParametersIndMsgT_v02, failedPositionEngineConfigParamMask)
};

static const uint8_t qmiLocGetPositionEngineConfigParametersReqMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetPositionEngineConfigParametersReqMsgT_v02, getPositionEngineConfigParamMask)
};

static const uint8_t qmiLocGetPositionEngineConfigParametersIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetPositionEngineConfigParametersIndMsgT_v02, status),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetPositionEngineConfigParametersIndMsgT_v02, injectedPositionControl) - QMI_IDL_OFFSET8(qmiLocGetPositionEngineConfigParametersIndMsgT_v02, injectedPositionControl_valid)),
  0x10,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetPositionEngineConfigParametersIndMsgT_v02, injectedPositionControl),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetPositionEngineConfigParametersIndMsgT_v02, filterSvUsage) - QMI_IDL_OFFSET8(qmiLocGetPositionEngineConfigParametersIndMsgT_v02, filterSvUsage_valid)),
  0x11,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetPositionEngineConfigParametersIndMsgT_v02, filterSvUsage),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetPositionEngineConfigParametersIndMsgT_v02, storeAssistData) - QMI_IDL_OFFSET8(qmiLocGetPositionEngineConfigParametersIndMsgT_v02, storeAssistData_valid)),
  0x12,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetPositionEngineConfigParametersIndMsgT_v02, storeAssistData),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetPositionEngineConfigParametersIndMsgT_v02, enableFasterTTFF) - QMI_IDL_OFFSET8(qmiLocGetPositionEngineConfigParametersIndMsgT_v02, enableFasterTTFF_valid)),
  0x13,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetPositionEngineConfigParametersIndMsgT_v02, enableFasterTTFF)
};

static const uint8_t qmiLocAddCircularGeofenceReqMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocAddCircularGeofenceReqMsgT_v02, transactionId),

  0x02,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocAddCircularGeofenceReqMsgT_v02, circularGeofenceArgs),
  QMI_IDL_TYPE88(0, 38),

  0x03,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocAddCircularGeofenceReqMsgT_v02, breachMask),

  0x04,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocAddCircularGeofenceReqMsgT_v02, includePosition),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocAddCircularGeofenceReqMsgT_v02, responsiveness) - QMI_IDL_OFFSET8(qmiLocAddCircularGeofenceReqMsgT_v02, responsiveness_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocAddCircularGeofenceReqMsgT_v02, responsiveness),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocAddCircularGeofenceReqMsgT_v02, confidence) - QMI_IDL_OFFSET8(qmiLocAddCircularGeofenceReqMsgT_v02, confidence_valid)),
  0x11,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocAddCircularGeofenceReqMsgT_v02, confidence),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocAddCircularGeofenceReqMsgT_v02, customResponsivenessValue) - QMI_IDL_OFFSET8(qmiLocAddCircularGeofenceReqMsgT_v02, customResponsivenessValue_valid)),
  0x12,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocAddCircularGeofenceReqMsgT_v02, customResponsivenessValue),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocAddCircularGeofenceReqMsgT_v02, dwellTime) - QMI_IDL_OFFSET8(qmiLocAddCircularGeofenceReqMsgT_v02, dwellTime_valid)),
  0x13,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocAddCircularGeofenceReqMsgT_v02, dwellTime),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocAddCircularGeofenceReqMsgT_v02, dwellTypeMask) - QMI_IDL_OFFSET8(qmiLocAddCircularGeofenceReqMsgT_v02, dwellTypeMask_valid)),
  0x14,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocAddCircularGeofenceReqMsgT_v02, dwellTypeMask)
};

static const uint8_t qmiLocAddCircularGeofenceIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocAddCircularGeofenceIndMsgT_v02, status),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocAddCircularGeofenceIndMsgT_v02, transactionId) - QMI_IDL_OFFSET8(qmiLocAddCircularGeofenceIndMsgT_v02, transactionId_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocAddCircularGeofenceIndMsgT_v02, transactionId),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocAddCircularGeofenceIndMsgT_v02, geofenceId) - QMI_IDL_OFFSET8(qmiLocAddCircularGeofenceIndMsgT_v02, geofenceId_valid)),
  0x11,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocAddCircularGeofenceIndMsgT_v02, geofenceId)
};

static const uint8_t qmiLocDeleteGeofenceReqMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocDeleteGeofenceReqMsgT_v02, geofenceId),

  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x02,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocDeleteGeofenceReqMsgT_v02, transactionId)
};

static const uint8_t qmiLocDeleteGeofenceIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocDeleteGeofenceIndMsgT_v02, status),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocDeleteGeofenceIndMsgT_v02, geofenceId) - QMI_IDL_OFFSET8(qmiLocDeleteGeofenceIndMsgT_v02, geofenceId_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocDeleteGeofenceIndMsgT_v02, geofenceId),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocDeleteGeofenceIndMsgT_v02, transactionId) - QMI_IDL_OFFSET8(qmiLocDeleteGeofenceIndMsgT_v02, transactionId_valid)),
  0x11,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocDeleteGeofenceIndMsgT_v02, transactionId)
};

static const uint8_t qmiLocQueryGeofenceReqMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocQueryGeofenceReqMsgT_v02, geofenceId),

  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x02,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocQueryGeofenceReqMsgT_v02, transactionId)
};

static const uint8_t qmiLocQueryGeofenceIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocQueryGeofenceIndMsgT_v02, status),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocQueryGeofenceIndMsgT_v02, geofenceId) - QMI_IDL_OFFSET8(qmiLocQueryGeofenceIndMsgT_v02, geofenceId_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocQueryGeofenceIndMsgT_v02, geofenceId),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocQueryGeofenceIndMsgT_v02, transactionId) - QMI_IDL_OFFSET8(qmiLocQueryGeofenceIndMsgT_v02, transactionId_valid)),
  0x11,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocQueryGeofenceIndMsgT_v02, transactionId),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocQueryGeofenceIndMsgT_v02, geofenceOrigin) - QMI_IDL_OFFSET8(qmiLocQueryGeofenceIndMsgT_v02, geofenceOrigin_valid)),
  0x12,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocQueryGeofenceIndMsgT_v02, geofenceOrigin),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocQueryGeofenceIndMsgT_v02, posWrtGeofence) - QMI_IDL_OFFSET8(qmiLocQueryGeofenceIndMsgT_v02, posWrtGeofence_valid)),
  0x13,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocQueryGeofenceIndMsgT_v02, posWrtGeofence),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocQueryGeofenceIndMsgT_v02, circularGeofenceArgs) - QMI_IDL_OFFSET8(qmiLocQueryGeofenceIndMsgT_v02, circularGeofenceArgs_valid)),
  0x14,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocQueryGeofenceIndMsgT_v02, circularGeofenceArgs),
  QMI_IDL_TYPE88(0, 38),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocQueryGeofenceIndMsgT_v02, geofenceState) - QMI_IDL_OFFSET8(qmiLocQueryGeofenceIndMsgT_v02, geofenceState_valid)),
  0x15,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocQueryGeofenceIndMsgT_v02, geofenceState)
};

static const uint8_t qmiLocSetGeofenceEngineConfigReqMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineConfigReqMsgT_v02, transactionId),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineConfigReqMsgT_v02, gnssUnavailableIndicationTimeout) - QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineConfigReqMsgT_v02, gnssUnavailableIndicationTimeout_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineConfigReqMsgT_v02, gnssUnavailableIndicationTimeout),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineConfigReqMsgT_v02, maxGeofences) - QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineConfigReqMsgT_v02, maxGeofences_valid)),
  0x11,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineConfigReqMsgT_v02, maxGeofences),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineConfigReqMsgT_v02, enableMotionDetectionSources) - QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineConfigReqMsgT_v02, enableMotionDetectionSources_valid)),
  0x12,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineConfigReqMsgT_v02, enableMotionDetectionSources),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineConfigReqMsgT_v02, enableCpiUsage) - QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineConfigReqMsgT_v02, enableCpiUsage_valid)),
  0x13,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineConfigReqMsgT_v02, enableCpiUsage),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineConfigReqMsgT_v02, gnssPositionSessionTimeout) - QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineConfigReqMsgT_v02, gnssPositionSessionTimeout_valid)),
  0x14,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineConfigReqMsgT_v02, gnssPositionSessionTimeout),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineConfigReqMsgT_v02, gnssPositionMaxPuncAcceptable) - QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineConfigReqMsgT_v02, gnssPositionMaxPuncAcceptable_valid)),
  0x15,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineConfigReqMsgT_v02, gnssPositionMaxPuncAcceptable),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineConfigReqMsgT_v02, mediumResponsivenessValue) - QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineConfigReqMsgT_v02, mediumResponsivenessValue_valid)),
  0x16,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineConfigReqMsgT_v02, mediumResponsivenessValue),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineConfigReqMsgT_v02, chalGnssEnvMinCpiWaitInterval) - QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineConfigReqMsgT_v02, chalGnssEnvMinCpiWaitInterval_valid)),
  0x17,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineConfigReqMsgT_v02, chalGnssEnvMinCpiWaitInterval),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineConfigReqMsgT_v02, motionStateInfo) - QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineConfigReqMsgT_v02, motionStateInfo_valid)),
  0x18,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineConfigReqMsgT_v02, motionStateInfo),
  QMI_LOC_GEOFENCE_MAX_MOTION_STATES_V02,
  QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineConfigReqMsgT_v02, motionStateInfo) - QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineConfigReqMsgT_v02, motionStateInfo_len),
  QMI_IDL_TYPE88(0, 39)
};

static const uint8_t qmiLocSetGeofenceEngineConfigIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineConfigIndMsgT_v02, status),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineConfigIndMsgT_v02, transactionId) - QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineConfigIndMsgT_v02, transactionId_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineConfigIndMsgT_v02, transactionId)
};

static const uint8_t qmiLocGetGeofenceEngineConfigReqMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetGeofenceEngineConfigReqMsgT_v02, transactionId)
};

static const uint8_t qmiLocGetGeofenceEngineConfigIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetGeofenceEngineConfigIndMsgT_v02, status),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetGeofenceEngineConfigIndMsgT_v02, transactionId) - QMI_IDL_OFFSET8(qmiLocGetGeofenceEngineConfigIndMsgT_v02, transactionId_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetGeofenceEngineConfigIndMsgT_v02, transactionId),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetGeofenceEngineConfigIndMsgT_v02, gnssUnavailableIndicationTimeout) - QMI_IDL_OFFSET8(qmiLocGetGeofenceEngineConfigIndMsgT_v02, gnssUnavailableIndicationTimeout_valid)),
  0x11,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetGeofenceEngineConfigIndMsgT_v02, gnssUnavailableIndicationTimeout),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetGeofenceEngineConfigIndMsgT_v02, maxGeofences) - QMI_IDL_OFFSET8(qmiLocGetGeofenceEngineConfigIndMsgT_v02, maxGeofences_valid)),
  0x12,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetGeofenceEngineConfigIndMsgT_v02, maxGeofences),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetGeofenceEngineConfigIndMsgT_v02, enabledMotionDetectionSources) - QMI_IDL_OFFSET8(qmiLocGetGeofenceEngineConfigIndMsgT_v02, enabledMotionDetectionSources_valid)),
  0x13,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetGeofenceEngineConfigIndMsgT_v02, enabledMotionDetectionSources),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetGeofenceEngineConfigIndMsgT_v02, enabledCpiUsage) - QMI_IDL_OFFSET8(qmiLocGetGeofenceEngineConfigIndMsgT_v02, enabledCpiUsage_valid)),
  0x14,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetGeofenceEngineConfigIndMsgT_v02, enabledCpiUsage)
};

static const uint8_t qmiLocEditGeofenceReqMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEditGeofenceReqMsgT_v02, geofenceId),

  0x02,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEditGeofenceReqMsgT_v02, transactionId),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEditGeofenceReqMsgT_v02, geofenceState) - QMI_IDL_OFFSET8(qmiLocEditGeofenceReqMsgT_v02, geofenceState_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEditGeofenceReqMsgT_v02, geofenceState),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEditGeofenceReqMsgT_v02, breachMask) - QMI_IDL_OFFSET8(qmiLocEditGeofenceReqMsgT_v02, breachMask_valid)),
  0x11,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocEditGeofenceReqMsgT_v02, breachMask),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEditGeofenceReqMsgT_v02, responsiveness) - QMI_IDL_OFFSET8(qmiLocEditGeofenceReqMsgT_v02, responsiveness_valid)),
  0x12,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEditGeofenceReqMsgT_v02, responsiveness)
};

static const uint8_t qmiLocEditGeofenceIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEditGeofenceIndMsgT_v02, status),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEditGeofenceIndMsgT_v02, geofenceId) - QMI_IDL_OFFSET8(qmiLocEditGeofenceIndMsgT_v02, geofenceId_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEditGeofenceIndMsgT_v02, geofenceId),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEditGeofenceIndMsgT_v02, transactionId) - QMI_IDL_OFFSET8(qmiLocEditGeofenceIndMsgT_v02, transactionId_valid)),
  0x11,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEditGeofenceIndMsgT_v02, transactionId),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEditGeofenceIndMsgT_v02, failedParams) - QMI_IDL_OFFSET8(qmiLocEditGeofenceIndMsgT_v02, failedParams_valid)),
  0x12,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEditGeofenceIndMsgT_v02, failedParams)
};

static const uint8_t qmiLocGetBestAvailablePositionReqMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionReqMsgT_v02, transactionId)
};

static const uint8_t qmiLocGetBestAvailablePositionIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, status),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, transactionId) - QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, transactionId_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, transactionId),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, latitude) - QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, latitude_valid)),
  0x11,
   QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, latitude),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, longitude) - QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, longitude_valid)),
  0x12,
   QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, longitude),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, horUncCircular) - QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, horUncCircular_valid)),
  0x13,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, horUncCircular),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, altitudeWrtEllipsoid) - QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, altitudeWrtEllipsoid_valid)),
  0x14,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, altitudeWrtEllipsoid),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, vertUnc) - QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, vertUnc_valid)),
  0x15,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, vertUnc),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, timestampUtc) - QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, timestampUtc_valid)),
  0x16,
   QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, timestampUtc),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, timeUnc) - QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, timeUnc_valid)),
  0x17,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, timeUnc),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, horUncEllipseSemiMinor) - QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, horUncEllipseSemiMinor_valid)),
  0x18,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, horUncEllipseSemiMinor),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, horUncEllipseSemiMajor) - QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, horUncEllipseSemiMajor_valid)),
  0x19,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, horUncEllipseSemiMajor),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, horUncEllipseOrientAzimuth) - QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, horUncEllipseOrientAzimuth_valid)),
  0x1A,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, horUncEllipseOrientAzimuth),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, horCircularConfidence) - QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, horCircularConfidence_valid)),
  0x1B,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, horCircularConfidence),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, horEllipticalConfidence) - QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, horEllipticalConfidence_valid)),
  0x1C,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, horEllipticalConfidence),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, horReliability) - QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, horReliability_valid)),
  0x1D,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, horReliability),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, horSpeed) - QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, horSpeed_valid)),
  0x1E,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, horSpeed),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, horSpeedUnc) - QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, horSpeedUnc_valid)),
  0x1F,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, horSpeedUnc),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, altitudeWrtMeanSeaLevel) - QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, altitudeWrtMeanSeaLevel_valid)),
  0x20,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, altitudeWrtMeanSeaLevel),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, vertConfidence) - QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, vertConfidence_valid)),
  0x21,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, vertConfidence),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, vertReliability) - QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, vertReliability_valid)),
  0x22,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, vertReliability),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, vertSpeed) - QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, vertSpeed_valid)),
  0x23,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, vertSpeed),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, vertSpeedUnc) - QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, vertSpeedUnc_valid)),
  0x24,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, vertSpeedUnc),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, heading) - QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, heading_valid)),
  0x25,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, heading),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, headingUnc) - QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, headingUnc_valid)),
  0x26,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, headingUnc),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, magneticDeviation) - QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, magneticDeviation_valid)),
  0x27,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, magneticDeviation),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, technologyMask) - QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, technologyMask_valid)),
  0x28,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, technologyMask),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, DOP) - QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, DOP_valid)),
  0x29,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocGetBestAvailablePositionIndMsgT_v02, DOP),
  QMI_IDL_TYPE88(0, 2),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocGetBestAvailablePositionIndMsgT_v02, gpsTime) - QMI_IDL_OFFSET16RELATIVE(qmiLocGetBestAvailablePositionIndMsgT_v02, gpsTime_valid)),
  0x2A,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET16ARRAY(qmiLocGetBestAvailablePositionIndMsgT_v02, gpsTime),
  QMI_IDL_TYPE88(0, 1),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocGetBestAvailablePositionIndMsgT_v02, timeSrc) - QMI_IDL_OFFSET16RELATIVE(qmiLocGetBestAvailablePositionIndMsgT_v02, timeSrc_valid)),
  0x2B,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocGetBestAvailablePositionIndMsgT_v02, timeSrc),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocGetBestAvailablePositionIndMsgT_v02, sensorDataUsage) - QMI_IDL_OFFSET16RELATIVE(qmiLocGetBestAvailablePositionIndMsgT_v02, sensorDataUsage_valid)),
  0x2C,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET16ARRAY(qmiLocGetBestAvailablePositionIndMsgT_v02, sensorDataUsage),
  QMI_IDL_TYPE88(0, 3),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocGetBestAvailablePositionIndMsgT_v02, gnssSvUsedList) - QMI_IDL_OFFSET16RELATIVE(qmiLocGetBestAvailablePositionIndMsgT_v02, gnssSvUsedList_valid)),
  0x2D,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocGetBestAvailablePositionIndMsgT_v02, gnssSvUsedList),
  QMI_LOC_MAX_SV_USED_LIST_LENGTH_V02,
  QMI_IDL_OFFSET16RELATIVE(qmiLocGetBestAvailablePositionIndMsgT_v02, gnssSvUsedList) - QMI_IDL_OFFSET16RELATIVE(qmiLocGetBestAvailablePositionIndMsgT_v02, gnssSvUsedList_len)
};

static const uint8_t qmiLocInjectMotionDataReqMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocInjectMotionDataReqMsgT_v02, motion_data),
  QMI_IDL_TYPE88(0, 40)
};

static const uint8_t qmiLocInjectMotionDataIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectMotionDataIndMsgT_v02, status)
};

static const uint8_t qmiLocGetNiGeofenceIdListReqMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetNiGeofenceIdListReqMsgT_v02, transactionId)
};

static const uint8_t qmiLocGetNiGeofenceIdListIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetNiGeofenceIdListIndMsgT_v02, status),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetNiGeofenceIdListIndMsgT_v02, transactionId) - QMI_IDL_OFFSET8(qmiLocGetNiGeofenceIdListIndMsgT_v02, transactionId_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetNiGeofenceIdListIndMsgT_v02, transactionId),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetNiGeofenceIdListIndMsgT_v02, niGeofenceIdList) - QMI_IDL_OFFSET8(qmiLocGetNiGeofenceIdListIndMsgT_v02, niGeofenceIdList_valid)),
  0x11,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetNiGeofenceIdListIndMsgT_v02, niGeofenceIdList),
  QMI_LOC_MAX_NI_GEOFENCE_ID_LIST_LENGTH_V02,
  QMI_IDL_OFFSET8(qmiLocGetNiGeofenceIdListIndMsgT_v02, niGeofenceIdList) - QMI_IDL_OFFSET8(qmiLocGetNiGeofenceIdListIndMsgT_v02, niGeofenceIdList_len)
};

static const uint8_t qmiLocInjectGSMCellInfoReqMsgT_data_v02[] = {
  0x01,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocInjectGSMCellInfoReqMsgT_v02, gsmCellId),
  QMI_IDL_TYPE88(0, 41),

  0x02,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectGSMCellInfoReqMsgT_v02, roamingStatus),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocInjectGSMCellInfoReqMsgT_v02, timingAdvance) - QMI_IDL_OFFSET8(qmiLocInjectGSMCellInfoReqMsgT_v02, timingAdvance_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectGSMCellInfoReqMsgT_v02, timingAdvance)
};

static const uint8_t qmiLocInjectGSMCellInfoIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectGSMCellInfoIndMsgT_v02, status)
};

static const uint8_t qmiLocInjectWCDMACellInfoReqMsgT_data_v02[] = {
  0x01,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocInjectWCDMACellInfoReqMsgT_v02, wcdmaCellId),
  QMI_IDL_TYPE88(0, 42),

  0x02,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectWCDMACellInfoReqMsgT_v02, roamingStatus),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocInjectWCDMACellInfoReqMsgT_v02, freq) - QMI_IDL_OFFSET8(qmiLocInjectWCDMACellInfoReqMsgT_v02, freq_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectWCDMACellInfoReqMsgT_v02, freq),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocInjectWCDMACellInfoReqMsgT_v02, psc) - QMI_IDL_OFFSET8(qmiLocInjectWCDMACellInfoReqMsgT_v02, psc_valid)),
  0x11,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectWCDMACellInfoReqMsgT_v02, psc)
};

static const uint8_t qmiLocInjectWCDMACellInfoIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectWCDMACellInfoIndMsgT_v02, status)
};

static const uint8_t qmiLocInjectTDSCDMACellInfoReqMsgT_data_v02[] = {
  0x01,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocInjectTDSCDMACellInfoReqMsgT_v02, tdscdmaCellId),
  QMI_IDL_TYPE88(0, 43),

  0x02,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectTDSCDMACellInfoReqMsgT_v02, roamingStatus),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocInjectTDSCDMACellInfoReqMsgT_v02, freq) - QMI_IDL_OFFSET8(qmiLocInjectTDSCDMACellInfoReqMsgT_v02, freq_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectTDSCDMACellInfoReqMsgT_v02, freq)
};

static const uint8_t qmiLocInjectTDSCDMACellInfoIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectTDSCDMACellInfoIndMsgT_v02, status)
};

static const uint8_t qmiLocInjectSubscriberIDReqMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocInjectSubscriberIDReqMsgT_v02, preferredIMSI) - QMI_IDL_OFFSET8(qmiLocInjectSubscriberIDReqMsgT_v02, preferredIMSI_valid)),
  0x10,
   QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectSubscriberIDReqMsgT_v02, preferredIMSI),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocInjectSubscriberIDReqMsgT_v02, preferredMSISDN) - QMI_IDL_OFFSET8(qmiLocInjectSubscriberIDReqMsgT_v02, preferredMSISDN_valid)),
  0x11,
   QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectSubscriberIDReqMsgT_v02, preferredMSISDN)
};

static const uint8_t qmiLocInjectSubscriberIDIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectSubscriberIDIndMsgT_v02, status)
};

static const uint8_t qmiLocInjectNetworkInitiatedMessageReqMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectNetworkInitiatedMessageReqMsgT_v02, injectedNIMessageType),

  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x02,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN | QMI_IDL_FLAGS_SZ_IS_16 |   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectNetworkInitiatedMessageReqMsgT_v02, injectedNIMessage),
  ((QMI_LOC_MAX_INJECTED_NETWORK_INITIATED_MESSAGE_LENGTH_V02) & 0xFF), ((QMI_LOC_MAX_INJECTED_NETWORK_INITIATED_MESSAGE_LENGTH_V02) >> 8),
  QMI_IDL_OFFSET8(qmiLocInjectNetworkInitiatedMessageReqMsgT_v02, injectedNIMessage) - QMI_IDL_OFFSET8(qmiLocInjectNetworkInitiatedMessageReqMsgT_v02, injectedNIMessage_len)
};

static const uint8_t qmiLocInjectNetworkInitiatedMessageIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectNetworkInitiatedMessageIndMsgT_v02, status)
};

/*
 * qmiLocWWANOutOfServiceNotificationReqMsgT is empty
 * static const uint8_t qmiLocWWANOutOfServiceNotificationReqMsgT_data_v02[] = {
 * };
 */

static const uint8_t qmiLocWWANOutOfServiceNotificationIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocWWANOutOfServiceNotificationIndMsgT_v02, status)
};

static const uint8_t qmiLocPedometerReportReqMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocPedometerReportReqMsgT_v02, timeSource),

  0x02,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocPedometerReportReqMsgT_v02, timestamp),

  0x03,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocPedometerReportReqMsgT_v02, timeInterval),

  0x04,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocPedometerReportReqMsgT_v02, stepCount),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocPedometerReportReqMsgT_v02, stepConfidence) - QMI_IDL_OFFSET8(qmiLocPedometerReportReqMsgT_v02, stepConfidence_valid)),
  0x10,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocPedometerReportReqMsgT_v02, stepConfidence),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocPedometerReportReqMsgT_v02, stepCountUncertainty) - QMI_IDL_OFFSET8(qmiLocPedometerReportReqMsgT_v02, stepCountUncertainty_valid)),
  0x11,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocPedometerReportReqMsgT_v02, stepCountUncertainty),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocPedometerReportReqMsgT_v02, stepRate) - QMI_IDL_OFFSET8(qmiLocPedometerReportReqMsgT_v02, stepRate_valid)),
  0x12,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocPedometerReportReqMsgT_v02, stepRate)
};

static const uint8_t qmiLocPedometerReportIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocPedometerReportIndMsgT_v02, status)
};

static const uint8_t qmiLocGetBatchSizeReqMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetBatchSizeReqMsgT_v02, transactionId),

  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x02,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetBatchSizeReqMsgT_v02, batchSize)
};

static const uint8_t qmiLocGetBatchSizeIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetBatchSizeIndMsgT_v02, status),

  0x02,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetBatchSizeIndMsgT_v02, transactionId),

  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x03,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetBatchSizeIndMsgT_v02, batchSize)
};

static const uint8_t qmiLocStartBatchingReqMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocStartBatchingReqMsgT_v02, minInterval) - QMI_IDL_OFFSET8(qmiLocStartBatchingReqMsgT_v02, minInterval_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocStartBatchingReqMsgT_v02, minInterval),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocStartBatchingReqMsgT_v02, horizontalAccuracyLevel) - QMI_IDL_OFFSET8(qmiLocStartBatchingReqMsgT_v02, horizontalAccuracyLevel_valid)),
  0x11,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocStartBatchingReqMsgT_v02, horizontalAccuracyLevel),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocStartBatchingReqMsgT_v02, fixSessionTimeout) - QMI_IDL_OFFSET8(qmiLocStartBatchingReqMsgT_v02, fixSessionTimeout_valid)),
  0x12,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocStartBatchingReqMsgT_v02, fixSessionTimeout),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocStartBatchingReqMsgT_v02, minDistance) - QMI_IDL_OFFSET8(qmiLocStartBatchingReqMsgT_v02, minDistance_valid)),
  0x13,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocStartBatchingReqMsgT_v02, minDistance),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocStartBatchingReqMsgT_v02, batchAllPos) - QMI_IDL_OFFSET8(qmiLocStartBatchingReqMsgT_v02, batchAllPos_valid)),
  0x14,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocStartBatchingReqMsgT_v02, batchAllPos),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocStartBatchingReqMsgT_v02, requestId) - QMI_IDL_OFFSET8(qmiLocStartBatchingReqMsgT_v02, requestId_valid)),
  0x15,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocStartBatchingReqMsgT_v02, requestId)
};

static const uint8_t qmiLocStartBatchingIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocStartBatchingIndMsgT_v02, status),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocStartBatchingIndMsgT_v02, requestId) - QMI_IDL_OFFSET8(qmiLocStartBatchingIndMsgT_v02, requestId_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocStartBatchingIndMsgT_v02, requestId)
};

static const uint8_t qmiLocEventBatchFullIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventBatchFullIndMsgT_v02, batchCount)
};

static const uint8_t qmiLocEventLiveBatchedPositionReportIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocEventLiveBatchedPositionReportIndMsgT_v02, liveBatchedReport),
  QMI_IDL_TYPE88(0, 44)
};

static const uint8_t qmiLocReadFromBatchReqMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocReadFromBatchReqMsgT_v02, numberOfEntries),

  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x02,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocReadFromBatchReqMsgT_v02, transactionId)
};

static const uint8_t qmiLocReadFromBatchIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocReadFromBatchIndMsgT_v02, status),

  0x02,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocReadFromBatchIndMsgT_v02, transactionId),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocReadFromBatchIndMsgT_v02, numberOfEntries) - QMI_IDL_OFFSET8(qmiLocReadFromBatchIndMsgT_v02, numberOfEntries_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocReadFromBatchIndMsgT_v02, numberOfEntries),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocReadFromBatchIndMsgT_v02, batchedReportList) - QMI_IDL_OFFSET8(qmiLocReadFromBatchIndMsgT_v02, batchedReportList_valid)),
  0x11,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocReadFromBatchIndMsgT_v02, batchedReportList),
  QMI_LOC_READ_FROM_BATCH_MAX_SIZE_V02,
  QMI_IDL_OFFSET8(qmiLocReadFromBatchIndMsgT_v02, batchedReportList) - QMI_IDL_OFFSET8(qmiLocReadFromBatchIndMsgT_v02, batchedReportList_len),
  QMI_IDL_TYPE88(0, 44)
};

static const uint8_t qmiLocStopBatchingReqMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocStopBatchingReqMsgT_v02, transactionId),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocStopBatchingReqMsgT_v02, requestId) - QMI_IDL_OFFSET8(qmiLocStopBatchingReqMsgT_v02, requestId_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocStopBatchingReqMsgT_v02, requestId)
};

static const uint8_t qmiLocStopBatchingIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocStopBatchingIndMsgT_v02, status),

  0x02,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocStopBatchingIndMsgT_v02, transactionId),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocStopBatchingIndMsgT_v02, requestId) - QMI_IDL_OFFSET8(qmiLocStopBatchingIndMsgT_v02, requestId_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocStopBatchingIndMsgT_v02, requestId)
};

static const uint8_t qmiLocReleaseBatchReqMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocReleaseBatchReqMsgT_v02, transactionId)
};

static const uint8_t qmiLocReleaseBatchIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocReleaseBatchIndMsgT_v02, status),

  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x02,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocReleaseBatchIndMsgT_v02, transactionId)
};

/*
 * qmiLocEventInjectWifiApDataReqIndMsgT is empty
 * static const uint8_t qmiLocEventInjectWifiApDataReqIndMsgT_data_v02[] = {
 * };
 */

static const uint8_t qmiLocInjectWifiApDataReqMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocInjectWifiApDataReqMsgT_v02, wifiApInfo),
  QMI_LOC_WIFI_MAX_REPORTED_APS_PER_MSG_V02,
  QMI_IDL_OFFSET8(qmiLocInjectWifiApDataReqMsgT_v02, wifiApInfo) - QMI_IDL_OFFSET8(qmiLocInjectWifiApDataReqMsgT_v02, wifiApInfo_len),
  QMI_IDL_TYPE88(0, 45)
};

static const uint8_t qmiLocInjectWifiApDataIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectWifiApDataIndMsgT_v02, status)
};

static const uint8_t qmiLocNotifyWifiAttachmentStatusReqMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocNotifyWifiAttachmentStatusReqMsgT_v02, attachState),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocNotifyWifiAttachmentStatusReqMsgT_v02, accessPointMacAddress) - QMI_IDL_OFFSET8(qmiLocNotifyWifiAttachmentStatusReqMsgT_v02, accessPointMacAddress_valid)),
  0x10,
  QMI_IDL_FLAGS_IS_ARRAY |  QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocNotifyWifiAttachmentStatusReqMsgT_v02, accessPointMacAddress),
  QMI_LOC_WIFI_MAC_ADDR_LENGTH_V02,

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocNotifyWifiAttachmentStatusReqMsgT_v02, wifiApSsid) - QMI_IDL_OFFSET8(qmiLocNotifyWifiAttachmentStatusReqMsgT_v02, wifiApSsid_valid)),
  0x11,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_STRING,
  QMI_IDL_OFFSET8(qmiLocNotifyWifiAttachmentStatusReqMsgT_v02, wifiApSsid),
  QMI_LOC_MAX_WIFI_AP_SSID_STR_LENGTH_V02
};

static const uint8_t qmiLocNotifyWifiAttachmentStatusIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocNotifyWifiAttachmentStatusIndMsgT_v02, status)
};

static const uint8_t qmiLocNotifyWifiEnabledStatusReqMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocNotifyWifiEnabledStatusReqMsgT_v02, enabledStatus)
};

static const uint8_t qmiLocNotifyWifiEnabledStatusIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocNotifyWifiEnabledStatusIndMsgT_v02, status)
};

static const uint8_t qmiLocEventVehicleDataReadyIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventVehicleDataReadyIndMsgT_v02, vehicleAccelReadyStatus) - QMI_IDL_OFFSET8(qmiLocEventVehicleDataReadyIndMsgT_v02, vehicleAccelReadyStatus_valid)),
  0x10,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventVehicleDataReadyIndMsgT_v02, vehicleAccelReadyStatus),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventVehicleDataReadyIndMsgT_v02, vehicleAngularRateReadyStatus) - QMI_IDL_OFFSET8(qmiLocEventVehicleDataReadyIndMsgT_v02, vehicleAngularRateReadyStatus_valid)),
  0x11,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventVehicleDataReadyIndMsgT_v02, vehicleAngularRateReadyStatus),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventVehicleDataReadyIndMsgT_v02, vehicleOdometryReadyStatus) - QMI_IDL_OFFSET8(qmiLocEventVehicleDataReadyIndMsgT_v02, vehicleOdometryReadyStatus_valid)),
  0x12,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventVehicleDataReadyIndMsgT_v02, vehicleOdometryReadyStatus)
};

static const uint8_t qmiLocInjectVehicleSensorDataReqMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocInjectVehicleSensorDataReqMsgT_v02, accelData) - QMI_IDL_OFFSET8(qmiLocInjectVehicleSensorDataReqMsgT_v02, accelData_valid)),
  0x10,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocInjectVehicleSensorDataReqMsgT_v02, accelData),
  QMI_IDL_TYPE88(0, 47),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocInjectVehicleSensorDataReqMsgT_v02, angRotationData) - QMI_IDL_OFFSET16RELATIVE(qmiLocInjectVehicleSensorDataReqMsgT_v02, angRotationData_valid)),
  0x11,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET16ARRAY(qmiLocInjectVehicleSensorDataReqMsgT_v02, angRotationData),
  QMI_IDL_TYPE88(0, 47),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocInjectVehicleSensorDataReqMsgT_v02, odometryData) - QMI_IDL_OFFSET16RELATIVE(qmiLocInjectVehicleSensorDataReqMsgT_v02, odometryData_valid)),
  0x12,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET16ARRAY(qmiLocInjectVehicleSensorDataReqMsgT_v02, odometryData),
  QMI_IDL_TYPE88(0, 49),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocInjectVehicleSensorDataReqMsgT_v02, changeInTimeScales) - QMI_IDL_OFFSET16RELATIVE(qmiLocInjectVehicleSensorDataReqMsgT_v02, changeInTimeScales_valid)),
  0x13,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocInjectVehicleSensorDataReqMsgT_v02, changeInTimeScales)
};

static const uint8_t qmiLocInjectVehicleSensorDataIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectVehicleSensorDataIndMsgT_v02, status)
};

static const uint8_t qmiLocGetAvailWwanPositionReqMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionReqMsgT_v02, transactionId)
};

static const uint8_t qmiLocGetAvailWwanPositionIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, status),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, transactionId) - QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, transactionId_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, transactionId),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, latitude) - QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, latitude_valid)),
  0x11,
   QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, latitude),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, longitude) - QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, longitude_valid)),
  0x12,
   QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, longitude),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, horUncCircular) - QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, horUncCircular_valid)),
  0x13,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, horUncCircular),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, altitudeWrtEllipsoid) - QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, altitudeWrtEllipsoid_valid)),
  0x14,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, altitudeWrtEllipsoid),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, vertUnc) - QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, vertUnc_valid)),
  0x15,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, vertUnc),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, timestampUtc) - QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, timestampUtc_valid)),
  0x16,
   QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, timestampUtc),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, timeUnc) - QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, timeUnc_valid)),
  0x17,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, timeUnc),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, horUncEllipseSemiMinor) - QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, horUncEllipseSemiMinor_valid)),
  0x18,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, horUncEllipseSemiMinor),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, horUncEllipseSemiMajor) - QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, horUncEllipseSemiMajor_valid)),
  0x19,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, horUncEllipseSemiMajor),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, horUncEllipseOrientAzimuth) - QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, horUncEllipseOrientAzimuth_valid)),
  0x1A,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, horUncEllipseOrientAzimuth),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, horCircularConfidence) - QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, horCircularConfidence_valid)),
  0x1B,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, horCircularConfidence),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, horEllipticalConfidence) - QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, horEllipticalConfidence_valid)),
  0x1C,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, horEllipticalConfidence),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, horReliability) - QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, horReliability_valid)),
  0x1D,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, horReliability),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, altitudeWrtMeanSeaLevel) - QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, altitudeWrtMeanSeaLevel_valid)),
  0x1E,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, altitudeWrtMeanSeaLevel),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, vertConfidence) - QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, vertConfidence_valid)),
  0x1F,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, vertConfidence),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, vertReliability) - QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, vertReliability_valid)),
  0x20,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, vertReliability),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, gpsTime) - QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, gpsTime_valid)),
  0x21,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, gpsTime),
  QMI_IDL_TYPE88(0, 1),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, timeSrc) - QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, timeSrc_valid)),
  0x22,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGetAvailWwanPositionIndMsgT_v02, timeSrc)
};

static const uint8_t qmiLocSetPremiumServicesCfgReqMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetPremiumServicesCfgReqMsgT_v02, premiumServiceType),

  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x02,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetPremiumServicesCfgReqMsgT_v02, premiumServiceCfg)
};

static const uint8_t qmiLocSetPremiumServicesCfgIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetPremiumServicesCfgIndMsgT_v02, status)
};

static const uint8_t qmiLocSetXtraVersionCheckReqMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetXtraVersionCheckReqMsgT_v02, xtraVersionCheckMode)
};

static const uint8_t qmiLocSetXtraVersionCheckIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetXtraVersionCheckIndMsgT_v02, status)
};

static const uint8_t qmiLocSetGNSSConstRepConfigReqMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetGNSSConstRepConfigReqMsgT_v02, measReportConfig) - QMI_IDL_OFFSET8(qmiLocSetGNSSConstRepConfigReqMsgT_v02, measReportConfig_valid)),
  0x10,
   QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetGNSSConstRepConfigReqMsgT_v02, measReportConfig),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetGNSSConstRepConfigReqMsgT_v02, svPolyReportConfig) - QMI_IDL_OFFSET8(qmiLocSetGNSSConstRepConfigReqMsgT_v02, svPolyReportConfig_valid)),
  0x11,
   QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetGNSSConstRepConfigReqMsgT_v02, svPolyReportConfig)
};

static const uint8_t qmiLocSetGNSSConstRepConfigIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetGNSSConstRepConfigIndMsgT_v02, status)
};

static const uint8_t qmiLocEventGnssSvMeasInfoIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, seqNum),

  0x02,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, maxMessageNum),

  0x03,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, system),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, rcvrClockFrequencyInfo) - QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, rcvrClockFrequencyInfo_valid)),
  0x10,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, rcvrClockFrequencyInfo),
  QMI_IDL_TYPE88(0, 50),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, leapSecondInfo) - QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, leapSecondInfo_valid)),
  0x11,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, leapSecondInfo),
  QMI_IDL_TYPE88(0, 51),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, gpsGloInterSystemBias) - QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, gpsGloInterSystemBias_valid)),
  0x12,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, gpsGloInterSystemBias),
  QMI_IDL_TYPE88(0, 52),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, gpsBdsInterSystemBias) - QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, gpsBdsInterSystemBias_valid)),
  0x13,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, gpsBdsInterSystemBias),
  QMI_IDL_TYPE88(0, 52),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, gpsGalInterSystemBias) - QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, gpsGalInterSystemBias_valid)),
  0x14,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, gpsGalInterSystemBias),
  QMI_IDL_TYPE88(0, 52),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, bdsGloInterSystemBias) - QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, bdsGloInterSystemBias_valid)),
  0x15,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, bdsGloInterSystemBias),
  QMI_IDL_TYPE88(0, 52),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, galGloInterSystemBias) - QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, galGloInterSystemBias_valid)),
  0x16,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, galGloInterSystemBias),
  QMI_IDL_TYPE88(0, 52),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, galBdsInterSystemBias) - QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, galBdsInterSystemBias_valid)),
  0x17,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, galBdsInterSystemBias),
  QMI_IDL_TYPE88(0, 52),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, systemTime) - QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, systemTime_valid)),
  0x18,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, systemTime),
  QMI_IDL_TYPE88(0, 53),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, gloTime) - QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, gloTime_valid)),
  0x19,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, gloTime),
  QMI_IDL_TYPE88(0, 54),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, systemTimeExt) - QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, systemTimeExt_valid)),
  0x1A,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, systemTimeExt),
  QMI_IDL_TYPE88(0, 55),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, svMeasurement) - QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, svMeasurement_valid)),
  0x1B,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, svMeasurement),
  QMI_LOC_SV_MEAS_LIST_MAX_SIZE_V02,
  QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, svMeasurement) - QMI_IDL_OFFSET8(qmiLocEventGnssSvMeasInfoIndMsgT_v02, svMeasurement_len),
  QMI_IDL_TYPE88(0, 57)
};

static const uint8_t qmiLocEventGnssSvPolyIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventGnssSvPolyIndMsgT_v02, gnssSvId),

  0x02,
   QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventGnssSvPolyIndMsgT_v02, T0),

  0x03,
   QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventGnssSvPolyIndMsgT_v02, svPolyFlagValid),

  0x04,
   QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventGnssSvPolyIndMsgT_v02, svPolyFlags),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventGnssSvPolyIndMsgT_v02, polyCoeffXYZ0) - QMI_IDL_OFFSET8(qmiLocEventGnssSvPolyIndMsgT_v02, polyCoeffXYZ0_valid)),
  0x10,
  QMI_IDL_FLAGS_IS_ARRAY |  QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventGnssSvPolyIndMsgT_v02, polyCoeffXYZ0),
  QMI_LOC_SV_POLY_XYZ_0_TH_ORDER_COEFF_SIZE_V02,

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventGnssSvPolyIndMsgT_v02, polyCoefXYZN) - QMI_IDL_OFFSET8(qmiLocEventGnssSvPolyIndMsgT_v02, polyCoefXYZN_valid)),
  0x11,
  QMI_IDL_FLAGS_IS_ARRAY |  QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventGnssSvPolyIndMsgT_v02, polyCoefXYZN),
  QMI_LOC_SV_POLY_XYZ_N_TH_ORDER_COEFF_SIZE_V02,

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventGnssSvPolyIndMsgT_v02, polyCoefClockBias) - QMI_IDL_OFFSET8(qmiLocEventGnssSvPolyIndMsgT_v02, polyCoefClockBias_valid)),
  0x12,
  QMI_IDL_FLAGS_IS_ARRAY |  QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventGnssSvPolyIndMsgT_v02, polyCoefClockBias),
  QMI_LOC_SV_POLY_SV_CLKBIAS_COEFF_SIZE_V02,

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventGnssSvPolyIndMsgT_v02, gloFrequency) - QMI_IDL_OFFSET8(qmiLocEventGnssSvPolyIndMsgT_v02, gloFrequency_valid)),
  0x13,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventGnssSvPolyIndMsgT_v02, gloFrequency),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventGnssSvPolyIndMsgT_v02, IODE) - QMI_IDL_OFFSET8(qmiLocEventGnssSvPolyIndMsgT_v02, IODE_valid)),
  0x14,
   QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventGnssSvPolyIndMsgT_v02, IODE),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventGnssSvPolyIndMsgT_v02, enhancedIOD) - QMI_IDL_OFFSET8(qmiLocEventGnssSvPolyIndMsgT_v02, enhancedIOD_valid)),
  0x15,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventGnssSvPolyIndMsgT_v02, enhancedIOD),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventGnssSvPolyIndMsgT_v02, svPosUnc) - QMI_IDL_OFFSET8(qmiLocEventGnssSvPolyIndMsgT_v02, svPosUnc_valid)),
  0x16,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventGnssSvPolyIndMsgT_v02, svPosUnc),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventGnssSvPolyIndMsgT_v02, ionoDelay) - QMI_IDL_OFFSET8(qmiLocEventGnssSvPolyIndMsgT_v02, ionoDelay_valid)),
  0x17,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventGnssSvPolyIndMsgT_v02, ionoDelay),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventGnssSvPolyIndMsgT_v02, ionoDot) - QMI_IDL_OFFSET8(qmiLocEventGnssSvPolyIndMsgT_v02, ionoDot_valid)),
  0x18,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventGnssSvPolyIndMsgT_v02, ionoDot),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventGnssSvPolyIndMsgT_v02, sbasIonoDelay) - QMI_IDL_OFFSET8(qmiLocEventGnssSvPolyIndMsgT_v02, sbasIonoDelay_valid)),
  0x19,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventGnssSvPolyIndMsgT_v02, sbasIonoDelay),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventGnssSvPolyIndMsgT_v02, sbasIonoDot) - QMI_IDL_OFFSET8(qmiLocEventGnssSvPolyIndMsgT_v02, sbasIonoDot_valid)),
  0x1A,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventGnssSvPolyIndMsgT_v02, sbasIonoDot),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventGnssSvPolyIndMsgT_v02, tropoDelay) - QMI_IDL_OFFSET8(qmiLocEventGnssSvPolyIndMsgT_v02, tropoDelay_valid)),
  0x1B,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventGnssSvPolyIndMsgT_v02, tropoDelay),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocEventGnssSvPolyIndMsgT_v02, elevation) - QMI_IDL_OFFSET16RELATIVE(qmiLocEventGnssSvPolyIndMsgT_v02, elevation_valid)),
  0x1C,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocEventGnssSvPolyIndMsgT_v02, elevation),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocEventGnssSvPolyIndMsgT_v02, elevationDot) - QMI_IDL_OFFSET16RELATIVE(qmiLocEventGnssSvPolyIndMsgT_v02, elevationDot_valid)),
  0x1D,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocEventGnssSvPolyIndMsgT_v02, elevationDot),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocEventGnssSvPolyIndMsgT_v02, elenationUnc) - QMI_IDL_OFFSET16RELATIVE(qmiLocEventGnssSvPolyIndMsgT_v02, elenationUnc_valid)),
  0x1E,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocEventGnssSvPolyIndMsgT_v02, elenationUnc),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocEventGnssSvPolyIndMsgT_v02, velCoef) - QMI_IDL_OFFSET16RELATIVE(qmiLocEventGnssSvPolyIndMsgT_v02, velCoef_valid)),
  0x1F,
  QMI_IDL_FLAGS_IS_ARRAY |  QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocEventGnssSvPolyIndMsgT_v02, velCoef),
  QMI_LOC_SV_POLY_VELOCITY_COEF_SIZE_V02
};

static const uint8_t qmiLocAddGeofenceContextReqMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocAddGeofenceContextReqMsgT_v02, transactionId),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocAddGeofenceContextReqMsgT_v02, geofenceId) - QMI_IDL_OFFSET8(qmiLocAddGeofenceContextReqMsgT_v02, geofenceId_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocAddGeofenceContextReqMsgT_v02, geofenceId),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocAddGeofenceContextReqMsgT_v02, wifiApSsidInfo) - QMI_IDL_OFFSET8(qmiLocAddGeofenceContextReqMsgT_v02, wifiApSsidInfo_valid)),
  0x11,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocAddGeofenceContextReqMsgT_v02, wifiApSsidInfo),
  QMI_LOC_WIFI_AREA_ID_LIST_LENGTH_V02,
  QMI_IDL_OFFSET8(qmiLocAddGeofenceContextReqMsgT_v02, wifiApSsidInfo) - QMI_IDL_OFFSET8(qmiLocAddGeofenceContextReqMsgT_v02, wifiApSsidInfo_len),
  QMI_IDL_TYPE88(0, 32),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocAddGeofenceContextReqMsgT_v02, wifiApMacAddressList) - QMI_IDL_OFFSET16RELATIVE(qmiLocAddGeofenceContextReqMsgT_v02, wifiApMacAddressList_valid)),
  0x12,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET16ARRAY(qmiLocAddGeofenceContextReqMsgT_v02, wifiApMacAddressList),
  QMI_LOC_WIFI_AREA_ID_LIST_LENGTH_V02,
  QMI_IDL_OFFSET16RELATIVE(qmiLocAddGeofenceContextReqMsgT_v02, wifiApMacAddressList) - QMI_IDL_OFFSET16RELATIVE(qmiLocAddGeofenceContextReqMsgT_v02, wifiApMacAddressList_len),
  QMI_IDL_TYPE88(0, 58),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocAddGeofenceContextReqMsgT_v02, tdsCdmaCellIDList) - QMI_IDL_OFFSET16RELATIVE(qmiLocAddGeofenceContextReqMsgT_v02, tdsCdmaCellIDList_valid)),
  0x13,
  QMI_IDL_FLAGS_IS_ARRAY |  QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET16ARRAY(qmiLocAddGeofenceContextReqMsgT_v02, tdsCdmaCellIDList),
  QMI_LOC_CELL_ID_LIST_LENGTH_V02,
  QMI_IDL_TYPE88(0, 43),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocAddGeofenceContextReqMsgT_v02, wcdmaCellIDList) - QMI_IDL_OFFSET16RELATIVE(qmiLocAddGeofenceContextReqMsgT_v02, wcdmaCellIDList_valid)),
  0x14,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET16ARRAY(qmiLocAddGeofenceContextReqMsgT_v02, wcdmaCellIDList),
  QMI_LOC_CELL_ID_LIST_LENGTH_V02,
  QMI_IDL_OFFSET16RELATIVE(qmiLocAddGeofenceContextReqMsgT_v02, wcdmaCellIDList) - QMI_IDL_OFFSET16RELATIVE(qmiLocAddGeofenceContextReqMsgT_v02, wcdmaCellIDList_len),
  QMI_IDL_TYPE88(0, 42),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocAddGeofenceContextReqMsgT_v02, gsmCellIDList) - QMI_IDL_OFFSET16RELATIVE(qmiLocAddGeofenceContextReqMsgT_v02, gsmCellIDList_valid)),
  0x15,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET16ARRAY(qmiLocAddGeofenceContextReqMsgT_v02, gsmCellIDList),
  QMI_LOC_CELL_ID_LIST_LENGTH_V02,
  QMI_IDL_OFFSET16RELATIVE(qmiLocAddGeofenceContextReqMsgT_v02, gsmCellIDList) - QMI_IDL_OFFSET16RELATIVE(qmiLocAddGeofenceContextReqMsgT_v02, gsmCellIDList_len),
  QMI_IDL_TYPE88(0, 41),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocAddGeofenceContextReqMsgT_v02, iBeaconList) - QMI_IDL_OFFSET16RELATIVE(qmiLocAddGeofenceContextReqMsgT_v02, iBeaconList_valid)),
  0x16,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET16ARRAY(qmiLocAddGeofenceContextReqMsgT_v02, iBeaconList),
  QMI_LOC_IBEACON_LIST_LENGTH_V02,
  QMI_IDL_OFFSET16RELATIVE(qmiLocAddGeofenceContextReqMsgT_v02, iBeaconList) - QMI_IDL_OFFSET16RELATIVE(qmiLocAddGeofenceContextReqMsgT_v02, iBeaconList_len),
  QMI_IDL_TYPE88(0, 59)
};

static const uint8_t qmiLocAddGeofenceContextIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocAddGeofenceContextIndMsgT_v02, status),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocAddGeofenceContextIndMsgT_v02, transactionId) - QMI_IDL_OFFSET8(qmiLocAddGeofenceContextIndMsgT_v02, transactionId_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocAddGeofenceContextIndMsgT_v02, transactionId),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocAddGeofenceContextIndMsgT_v02, geofenceId) - QMI_IDL_OFFSET8(qmiLocAddGeofenceContextIndMsgT_v02, geofenceId_valid)),
  0x11,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocAddGeofenceContextIndMsgT_v02, geofenceId),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocAddGeofenceContextIndMsgT_v02, contextId) - QMI_IDL_OFFSET8(qmiLocAddGeofenceContextIndMsgT_v02, contextId_valid)),
  0x12,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocAddGeofenceContextIndMsgT_v02, contextId)
};

static const uint8_t qmiLocSetGeofenceEngineContextReqMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineContextReqMsgT_v02, transactionId),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineContextReqMsgT_v02, utcTimeOfDay) - QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineContextReqMsgT_v02, utcTimeOfDay_valid)),
  0x10,
   QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineContextReqMsgT_v02, utcTimeOfDay),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineContextReqMsgT_v02, temperature) - QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineContextReqMsgT_v02, temperature_valid)),
  0x11,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineContextReqMsgT_v02, temperature)
};

static const uint8_t qmiLocSetGeofenceEngineContextIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineContextIndMsgT_v02, status),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineContextIndMsgT_v02, transactionId) - QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineContextIndMsgT_v02, transactionId_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSetGeofenceEngineContextIndMsgT_v02, transactionId)
};

static const uint8_t qmiLocDeleteGeofenceContextReqMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocDeleteGeofenceContextReqMsgT_v02, transactionId),

  0x02,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocDeleteGeofenceContextReqMsgT_v02, geofenceId),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocDeleteGeofenceContextReqMsgT_v02, contextId) - QMI_IDL_OFFSET8(qmiLocDeleteGeofenceContextReqMsgT_v02, contextId_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocDeleteGeofenceContextReqMsgT_v02, contextId)
};

static const uint8_t qmiLocDeleteGeofenceContextIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocDeleteGeofenceContextIndMsgT_v02, status),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocDeleteGeofenceContextIndMsgT_v02, transactionId) - QMI_IDL_OFFSET8(qmiLocDeleteGeofenceContextIndMsgT_v02, transactionId_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocDeleteGeofenceContextIndMsgT_v02, transactionId),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocDeleteGeofenceContextIndMsgT_v02, geofenceId) - QMI_IDL_OFFSET8(qmiLocDeleteGeofenceContextIndMsgT_v02, geofenceId_valid)),
  0x11,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocDeleteGeofenceContextIndMsgT_v02, geofenceId),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocDeleteGeofenceContextIndMsgT_v02, contextId) - QMI_IDL_OFFSET8(qmiLocDeleteGeofenceContextIndMsgT_v02, contextId_valid)),
  0x12,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocDeleteGeofenceContextIndMsgT_v02, contextId)
};

static const uint8_t qmiLocInjectGtpClientDownloadedDataReqMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN | QMI_IDL_FLAGS_SZ_IS_16 |   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectGtpClientDownloadedDataReqMsgT_v02, ClientDownloadedData),
  ((QMI_LOC_MAX_GTP_WWAN_CLIENT_DOWNLOADED_DATA_LEN_V02) & 0xFF), ((QMI_LOC_MAX_GTP_WWAN_CLIENT_DOWNLOADED_DATA_LEN_V02) >> 8),
  QMI_IDL_OFFSET8(qmiLocInjectGtpClientDownloadedDataReqMsgT_v02, ClientDownloadedData) - QMI_IDL_OFFSET8(qmiLocInjectGtpClientDownloadedDataReqMsgT_v02, ClientDownloadedData_len)
};

static const uint8_t qmiLocInjectGtpClientDownloadedDataIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectGtpClientDownloadedDataIndMsgT_v02, status)
};

static const uint8_t qmiLocGdtUploadBeginStatusReqMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGdtUploadBeginStatusReqMsgT_v02, serviceId),

  0x02,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGdtUploadBeginStatusReqMsgT_v02, sessionId),

  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x03,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGdtUploadBeginStatusReqMsgT_v02, gdtAccessStatus)
};

static const uint8_t qmiLocGdtUploadBeginStatusIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGdtUploadBeginStatusIndMsgT_v02, status)
};

static const uint8_t qmiLocGdtUploadEndReqMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGdtUploadEndReqMsgT_v02, serviceId),

  0x02,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGdtUploadEndReqMsgT_v02, sessionId),

  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x03,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGdtUploadEndReqMsgT_v02, gdtEndStatus)
};

static const uint8_t qmiLocGdtUploadEndIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocGdtUploadEndIndMsgT_v02, status)
};

static const uint8_t qmiLocStartDbtReqMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocStartDbtReqMsgT_v02, reqId),

  0x02,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocStartDbtReqMsgT_v02, minDistance),

  0x03,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocStartDbtReqMsgT_v02, distanceType),

  0x04,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocStartDbtReqMsgT_v02, needOriginLocation),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocStartDbtReqMsgT_v02, maxLatency) - QMI_IDL_OFFSET8(qmiLocStartDbtReqMsgT_v02, maxLatency_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocStartDbtReqMsgT_v02, maxLatency),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocStartDbtReqMsgT_v02, usageType) - QMI_IDL_OFFSET8(qmiLocStartDbtReqMsgT_v02, usageType_valid)),
  0x11,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocStartDbtReqMsgT_v02, usageType)
};

static const uint8_t qmiLocStartDbtIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocStartDbtIndMsgT_v02, status),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocStartDbtIndMsgT_v02, reqId) - QMI_IDL_OFFSET8(qmiLocStartDbtIndMsgT_v02, reqId_valid)),
  0x10,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocStartDbtIndMsgT_v02, reqId)
};

static const uint8_t qmiLocStopDbtReqMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocStopDbtReqMsgT_v02, reqId)
};

static const uint8_t qmiLocStopDbtIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocStopDbtIndMsgT_v02, status),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocStopDbtIndMsgT_v02, reqId) - QMI_IDL_OFFSET8(qmiLocStopDbtIndMsgT_v02, reqId_valid)),
  0x10,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocStopDbtIndMsgT_v02, reqId)
};

static const uint8_t qmiLocEventDbtPositionReportIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventDbtPositionReportIndMsgT_v02, reqId),

  0x02,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocEventDbtPositionReportIndMsgT_v02, dbtPosition),
  QMI_IDL_TYPE88(0, 60),

  0x03,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventDbtPositionReportIndMsgT_v02, positionType),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventDbtPositionReportIndMsgT_v02, headingUnc) - QMI_IDL_OFFSET8(qmiLocEventDbtPositionReportIndMsgT_v02, headingUnc_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventDbtPositionReportIndMsgT_v02, headingUnc),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventDbtPositionReportIndMsgT_v02, speedUnc) - QMI_IDL_OFFSET8(qmiLocEventDbtPositionReportIndMsgT_v02, speedUnc_valid)),
  0x11,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventDbtPositionReportIndMsgT_v02, speedUnc),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventDbtPositionReportIndMsgT_v02, horConfidence) - QMI_IDL_OFFSET8(qmiLocEventDbtPositionReportIndMsgT_v02, horConfidence_valid)),
  0x12,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventDbtPositionReportIndMsgT_v02, horConfidence),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventDbtPositionReportIndMsgT_v02, vertConfidence) - QMI_IDL_OFFSET8(qmiLocEventDbtPositionReportIndMsgT_v02, vertConfidence_valid)),
  0x13,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventDbtPositionReportIndMsgT_v02, vertConfidence),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventDbtPositionReportIndMsgT_v02, DOP) - QMI_IDL_OFFSET8(qmiLocEventDbtPositionReportIndMsgT_v02, DOP_valid)),
  0x14,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocEventDbtPositionReportIndMsgT_v02, DOP),
  QMI_IDL_TYPE88(0, 2),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventDbtPositionReportIndMsgT_v02, gnssSvUsedList) - QMI_IDL_OFFSET8(qmiLocEventDbtPositionReportIndMsgT_v02, gnssSvUsedList_valid)),
  0x15,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventDbtPositionReportIndMsgT_v02, gnssSvUsedList),
  QMI_LOC_MAX_SV_USED_LIST_LENGTH_V02,
  QMI_IDL_OFFSET8(qmiLocEventDbtPositionReportIndMsgT_v02, gnssSvUsedList) - QMI_IDL_OFFSET8(qmiLocEventDbtPositionReportIndMsgT_v02, gnssSvUsedList_len),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocEventDbtPositionReportIndMsgT_v02, positionSrc) - QMI_IDL_OFFSET16RELATIVE(qmiLocEventDbtPositionReportIndMsgT_v02, positionSrc_valid)),
  0x16,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocEventDbtPositionReportIndMsgT_v02, positionSrc)
};

static const uint8_t qmiLocEventDbtSessionStatusIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventDbtSessionStatusIndMsgT_v02, dbtSessionStatus),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventDbtSessionStatusIndMsgT_v02, reqId) - QMI_IDL_OFFSET8(qmiLocEventDbtSessionStatusIndMsgT_v02, reqId_valid)),
  0x10,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventDbtSessionStatusIndMsgT_v02, reqId)
};

static const uint8_t qmiLocSecureGetAvailablePositionReqMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSecureGetAvailablePositionReqMsgT_v02, secureLocDataMode),

  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x02,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN | QMI_IDL_FLAGS_SZ_IS_16 |   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocSecureGetAvailablePositionReqMsgT_v02, qmilocSecureGetAvailablePositionRequestData),
  ((QMI_LOC_SECURE_GET_AVAILABLE_POS_REQUEST_ENCRYPTED_MAX_V02) & 0xFF), ((QMI_LOC_SECURE_GET_AVAILABLE_POS_REQUEST_ENCRYPTED_MAX_V02) >> 8),
  QMI_IDL_OFFSET8(qmiLocSecureGetAvailablePositionReqMsgT_v02, qmilocSecureGetAvailablePositionRequestData) - QMI_IDL_OFFSET8(qmiLocSecureGetAvailablePositionReqMsgT_v02, qmilocSecureGetAvailablePositionRequestData_len)
};

static const uint8_t qmiLocSecureGetAvailablePositionIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSecureGetAvailablePositionIndMsgT_v02, sessionStatus),

  0x02,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocSecureGetAvailablePositionIndMsgT_v02, secureLocDataMode),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocSecureGetAvailablePositionIndMsgT_v02, qmilocSecureGetAvailablePositionInd) - QMI_IDL_OFFSET8(qmiLocSecureGetAvailablePositionIndMsgT_v02, qmilocSecureGetAvailablePositionInd_valid)),
  0x10,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN | QMI_IDL_FLAGS_SZ_IS_16 |   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocSecureGetAvailablePositionIndMsgT_v02, qmilocSecureGetAvailablePositionInd),
  ((QMI_LOC_SECURE_GET_AVAILABLE_POSITION_IND_ENCRYPTED_MAX_V02) & 0xFF), ((QMI_LOC_SECURE_GET_AVAILABLE_POSITION_IND_ENCRYPTED_MAX_V02) >> 8),
  QMI_IDL_OFFSET8(qmiLocSecureGetAvailablePositionIndMsgT_v02, qmilocSecureGetAvailablePositionInd) - QMI_IDL_OFFSET8(qmiLocSecureGetAvailablePositionIndMsgT_v02, qmilocSecureGetAvailablePositionInd_len)
};

static const uint8_t qmiLocEventGeofenceBatchedDwellIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventGeofenceBatchedDwellIndMsgT_v02, dwellType),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocEventGeofenceBatchedDwellIndMsgT_v02, geofenceIdContinuousList) - QMI_IDL_OFFSET8(qmiLocEventGeofenceBatchedDwellIndMsgT_v02, geofenceIdContinuousList_valid)),
  0x10,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocEventGeofenceBatchedDwellIndMsgT_v02, geofenceIdContinuousList),
  QMI_LOC_MAX_GEOFENCE_ID_CONTINUOUS_LIST_LENGTH_V02,
  QMI_IDL_OFFSET8(qmiLocEventGeofenceBatchedDwellIndMsgT_v02, geofenceIdContinuousList) - QMI_IDL_OFFSET8(qmiLocEventGeofenceBatchedDwellIndMsgT_v02, geofenceIdContinuousList_len),
  QMI_IDL_TYPE88(0, 24),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedDwellIndMsgT_v02, geofenceIdDiscreteList) - QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedDwellIndMsgT_v02, geofenceIdDiscreteList_valid)),
  0x11,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocEventGeofenceBatchedDwellIndMsgT_v02, geofenceIdDiscreteList),
  QMI_LOC_MAX_GEOFENCE_ID_DISCRETE_LIST_LENGTH_V02,
  QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedDwellIndMsgT_v02, geofenceIdDiscreteList) - QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedDwellIndMsgT_v02, geofenceIdDiscreteList_len),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedDwellIndMsgT_v02, geofencePosition) - QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedDwellIndMsgT_v02, geofencePosition_valid)),
  0x12,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET16ARRAY(qmiLocEventGeofenceBatchedDwellIndMsgT_v02, geofencePosition),
  QMI_IDL_TYPE88(0, 23),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedDwellIndMsgT_v02, headingUnc) - QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedDwellIndMsgT_v02, headingUnc_valid)),
  0x13,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocEventGeofenceBatchedDwellIndMsgT_v02, headingUnc),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedDwellIndMsgT_v02, vertUnc) - QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedDwellIndMsgT_v02, vertUnc_valid)),
  0x14,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocEventGeofenceBatchedDwellIndMsgT_v02, vertUnc),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedDwellIndMsgT_v02, speedUnc) - QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedDwellIndMsgT_v02, speedUnc_valid)),
  0x15,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocEventGeofenceBatchedDwellIndMsgT_v02, speedUnc),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedDwellIndMsgT_v02, horConfidence) - QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedDwellIndMsgT_v02, horConfidence_valid)),
  0x16,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocEventGeofenceBatchedDwellIndMsgT_v02, horConfidence),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedDwellIndMsgT_v02, vertConfidence) - QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedDwellIndMsgT_v02, vertConfidence_valid)),
  0x17,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocEventGeofenceBatchedDwellIndMsgT_v02, vertConfidence),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedDwellIndMsgT_v02, DOP) - QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedDwellIndMsgT_v02, DOP_valid)),
  0x18,
   QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET16ARRAY(qmiLocEventGeofenceBatchedDwellIndMsgT_v02, DOP),
  QMI_IDL_TYPE88(0, 2),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedDwellIndMsgT_v02, gnssSvUsedList) - QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedDwellIndMsgT_v02, gnssSvUsedList_valid)),
  0x19,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_FLAGS_OFFSET_IS_16 | QMI_IDL_GENERIC_2_BYTE,
  QMI_IDL_OFFSET16ARRAY(qmiLocEventGeofenceBatchedDwellIndMsgT_v02, gnssSvUsedList),
  QMI_LOC_MAX_SV_USED_LIST_LENGTH_V02,
  QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedDwellIndMsgT_v02, gnssSvUsedList) - QMI_IDL_OFFSET16RELATIVE(qmiLocEventGeofenceBatchedDwellIndMsgT_v02, gnssSvUsedList_len)
};

static const uint8_t qmiLocEventGetTimeZoneReqIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventGetTimeZoneReqIndMsgT_v02, status)
};

static const uint8_t qmiLocInjectTimeZoneInfoReqMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_8_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectTimeZoneInfoReqMsgT_v02, timeUtc),

  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x02,
   QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocInjectTimeZoneInfoReqMsgT_v02, timeZone),
  QMI_IDL_TYPE88(0, 62)
};

static const uint8_t qmiLocInjectTimeZoneInfoIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectTimeZoneInfoIndMsgT_v02, status)
};

static const uint8_t qmiLocInjectApCacheDataReqMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectApCacheDataReqMsgT_v02, versionNumber),

  0x02,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectApCacheDataReqMsgT_v02, partNumber),

  0x03,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectApCacheDataReqMsgT_v02, totalParts),

  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x04,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocInjectApCacheDataReqMsgT_v02, apCacheData),
  QMI_LOC_APCACHE_DATA_MAX_SAMPLES_V02,
  QMI_IDL_OFFSET8(qmiLocInjectApCacheDataReqMsgT_v02, apCacheData) - QMI_IDL_OFFSET8(qmiLocInjectApCacheDataReqMsgT_v02, apCacheData_len),
  QMI_IDL_TYPE88(0, 63)
};

static const uint8_t qmiLocInjectApCacheDataIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectApCacheDataIndMsgT_v02, status)
};

static const uint8_t qmiLocInjectApDoNotCacheDataReqMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectApDoNotCacheDataReqMsgT_v02, versionNumber),

  0x02,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectApDoNotCacheDataReqMsgT_v02, partNumber),

  0x03,
   QMI_IDL_GENERIC_1_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectApDoNotCacheDataReqMsgT_v02, totalParts),

  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x04,
  QMI_IDL_FLAGS_IS_ARRAY | QMI_IDL_FLAGS_IS_VARIABLE_LEN |  QMI_IDL_AGGREGATE,
  QMI_IDL_OFFSET8(qmiLocInjectApDoNotCacheDataReqMsgT_v02, apDoNotCacheData),
  QMI_LOC_APCACHE_DATA_MAX_SAMPLES_V02,
  QMI_IDL_OFFSET8(qmiLocInjectApDoNotCacheDataReqMsgT_v02, apDoNotCacheData) - QMI_IDL_OFFSET8(qmiLocInjectApDoNotCacheDataReqMsgT_v02, apDoNotCacheData_len),
  QMI_IDL_TYPE88(0, 64)
};

static const uint8_t qmiLocInjectApDoNotCacheDataIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocInjectApDoNotCacheDataIndMsgT_v02, status)
};

static const uint8_t qmiLocEventBatchingStatusIndMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocEventBatchingStatusIndMsgT_v02, batchingStatus)
};

static const uint8_t qmiLocQueryAonConfigReqMsgT_data_v02[] = {
  QMI_IDL_TLV_FLAGS_LAST_TLV | 0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocQueryAonConfigReqMsgT_v02, transactionId)
};

static const uint8_t qmiLocQueryAonConfigIndMsgT_data_v02[] = {
  0x01,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocQueryAonConfigIndMsgT_v02, status),

  QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocQueryAonConfigIndMsgT_v02, transactionId) - QMI_IDL_OFFSET8(qmiLocQueryAonConfigIndMsgT_v02, transactionId_valid)),
  0x10,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocQueryAonConfigIndMsgT_v02, transactionId),

  QMI_IDL_TLV_FLAGS_LAST_TLV | QMI_IDL_TLV_FLAGS_OPTIONAL | (QMI_IDL_OFFSET8(qmiLocQueryAonConfigIndMsgT_v02, aonCapability) - QMI_IDL_OFFSET8(qmiLocQueryAonConfigIndMsgT_v02, aonCapability_valid)),
  0x11,
   QMI_IDL_GENERIC_4_BYTE,
  QMI_IDL_OFFSET8(qmiLocQueryAonConfigIndMsgT_v02, aonCapability)
};

/* Type Table */
static const qmi_idl_type_table_entry  loc_type_table_v02[] = {
  {sizeof(qmiLocApplicationIdStructT_v02), qmiLocApplicationIdStructT_data_v02},
  {sizeof(qmiLocGPSTimeStructT_v02), qmiLocGPSTimeStructT_data_v02},
  {sizeof(qmiLocDOPStructT_v02), qmiLocDOPStructT_data_v02},
  {sizeof(qmiLocSensorUsageIndicatorStructT_v02), qmiLocSensorUsageIndicatorStructT_data_v02},
  {sizeof(qmiLocSvInfoStructT_v02), qmiLocSvInfoStructT_data_v02},
  {sizeof(qmiLocNiVxNotifyVerifyStructT_v02), qmiLocNiVxNotifyVerifyStructT_data_v02},
  {sizeof(qmiLocNiSuplFormattedStringStructT_v02), qmiLocNiSuplFormattedStringStructT_data_v02},
  {sizeof(qmiLocNiSuplQopStructT_v02), qmiLocNiSuplQopStructT_data_v02},
  {sizeof(qmiLocIpV4AddrStructType_v02), qmiLocIpV4AddrStructType_data_v02},
  {sizeof(qmiLocIpV6AddrStructType_v02), qmiLocIpV6AddrStructType_data_v02},
  {sizeof(qmiLocNiSuplServerInfoStructT_v02), qmiLocNiSuplServerInfoStructT_data_v02},
  {sizeof(qmiLocNiSuplNotifyVerifyStructT_v02), qmiLocNiSuplNotifyVerifyStructT_data_v02},
  {sizeof(qmiLocNiUmtsCpCodedStringStructT_v02), qmiLocNiUmtsCpCodedStringStructT_data_v02},
  {sizeof(qmiLocNiUmtsCpNotifyVerifyStructT_v02), qmiLocNiUmtsCpNotifyVerifyStructT_data_v02},
  {sizeof(qmiLocNiVxServiceInteractionStructT_v02), qmiLocNiVxServiceInteractionStructT_data_v02},
  {sizeof(qmiLocNiSuplVer2ExtStructT_v02), qmiLocNiSuplVer2ExtStructT_data_v02},
  {sizeof(qmiLocEmergencyNotificationStructT_v02), qmiLocEmergencyNotificationStructT_data_v02},
  {sizeof(qmiLocAssistanceServerUrlStructT_v02), qmiLocAssistanceServerUrlStructT_data_v02},
  {sizeof(qmiLocTimeServerListStructT_v02), qmiLocTimeServerListStructT_data_v02},
  {sizeof(qmiLocPredictedOrbitsAllowedSizesStructT_v02), qmiLocPredictedOrbitsAllowedSizesStructT_data_v02},
  {sizeof(qmiLocPredictedOrbitsServerListStructT_v02), qmiLocPredictedOrbitsServerListStructT_data_v02},
  {sizeof(qmiLocSensorControlConfigSamplingSpecStructT_v02), qmiLocSensorControlConfigSamplingSpecStructT_data_v02},
  {sizeof(qmiLocSensorReadyStatusStructT_v02), qmiLocSensorReadyStatusStructT_data_v02},
  {sizeof(qmiLocGeofencePositionStructT_v02), qmiLocGeofencePositionStructT_data_v02},
  {sizeof(qmiLocGeofenceIdContinuousStructT_v02), qmiLocGeofenceIdContinuousStructT_data_v02},
  {sizeof(qmiLocPredictedOrbitsDataValidityStructT_v02), qmiLocPredictedOrbitsDataValidityStructT_data_v02},
  {sizeof(qmiLocAltitudeSrcInfoStructT_v02), qmiLocAltitudeSrcInfoStructT_data_v02},
  {sizeof(qmiLocDeleteSvInfoStructT_v02), qmiLocDeleteSvInfoStructT_data_v02},
  {sizeof(qmiLocDeleteBDSSvInfoStructT_v02), qmiLocDeleteBDSSvInfoStructT_data_v02},
  {sizeof(qmiLocWifiFixTimeStructT_v02), qmiLocWifiFixTimeStructT_data_v02},
  {sizeof(qmiLocWifiFixPosStructT_v02), qmiLocWifiFixPosStructT_data_v02},
  {sizeof(qmiLocWifiApInfoStructT_v02), qmiLocWifiApInfoStructT_data_v02},
  {sizeof(qmiLocWifiApSsidStructT_v02), qmiLocWifiApSsidStructT_data_v02},
  {sizeof(qmiLoc3AxisSensorSampleStructT_v02), qmiLoc3AxisSensorSampleStructT_data_v02},
  {sizeof(qmiLoc3AxisSensorSampleListStructT_v02), qmiLoc3AxisSensorSampleListStructT_data_v02},
  {sizeof(qmiLocSensorTemperatureSampleStructT_v02), qmiLocSensorTemperatureSampleStructT_data_v02},
  {sizeof(qmiLocSensorTemperatureSampleListStructT_v02), qmiLocSensorTemperatureSampleListStructT_data_v02},
  {sizeof(qmiLocApnProfilesStructT_v02), qmiLocApnProfilesStructT_data_v02},
  {sizeof(qmiLocCircularGeofenceArgsStructT_v02), qmiLocCircularGeofenceArgsStructT_data_v02},
  {sizeof(qmiLocGeofenceMotionStateConfigStructT_v02), qmiLocGeofenceMotionStateConfigStructT_data_v02},
  {sizeof(qmiLocMotionDataStructT_v02), qmiLocMotionDataStructT_data_v02},
  {sizeof(qmiLocGSMCellIdStructT_v02), qmiLocGSMCellIdStructT_data_v02},
  {sizeof(qmiLocWCDMACellIdStructT_v02), qmiLocWCDMACellIdStructT_data_v02},
  {sizeof(qmiLocTDSCDMACellIdStructT_v02), qmiLocTDSCDMACellIdStructT_data_v02},
  {sizeof(qmiLocBatchedReportStructT_v02), qmiLocBatchedReportStructT_data_v02},
  {sizeof(qmiLocWifiApDataStructT_v02), qmiLocWifiApDataStructT_data_v02},
  {sizeof(qmiLocVehicleSensorSampleStructT_v02), qmiLocVehicleSensorSampleStructT_data_v02},
  {sizeof(qmiLocVehicleSensorSampleListStructType_v02), qmiLocVehicleSensorSampleListStructType_data_v02},
  {sizeof(qmiLocVehicleOdometrySampleStructT_v02), qmiLocVehicleOdometrySampleStructT_data_v02},
  {sizeof(qmiLocVehicleOdometrySampleListStructT_v02), qmiLocVehicleOdometrySampleListStructT_data_v02},
  {sizeof(qmiLocRcvrClockFrequencyInfoStructT_v02), qmiLocRcvrClockFrequencyInfoStructT_data_v02},
  {sizeof(qmiLocLeapSecondInfoStructT_v02), qmiLocLeapSecondInfoStructT_data_v02},
  {sizeof(qmiLocInterSystemBiasStructT_v02), qmiLocInterSystemBiasStructT_data_v02},
  {sizeof(qmiLocGnssTimeStructT_v02), qmiLocGnssTimeStructT_data_v02},
  {sizeof(qmiLocGloTimeStructT_v02), qmiLocGloTimeStructT_data_v02},
  {sizeof(qmiLocGnssTimeExtStructT_v02), qmiLocGnssTimeExtStructT_data_v02},
  {sizeof(qmiLocSVTimeSpeedStructT_v02), qmiLocSVTimeSpeedStructT_data_v02},
  {sizeof(qmiLocSVMeasurementStructT_v02), qmiLocSVMeasurementStructT_data_v02},
  {sizeof(qmiLocWifiApMacAddressStructT_v02), qmiLocWifiApMacAddressStructT_data_v02},
  {sizeof(qmiLocIBeaconIdStructT_v02), qmiLocIBeaconIdStructT_data_v02},
  {sizeof(qmiLocDbtPositionStructT_v02), qmiLocDbtPositionStructT_data_v02},
  {sizeof(qmiLocDeleteGALSvInfoStructT_v02), qmiLocDeleteGALSvInfoStructT_data_v02},
  {sizeof(qmiLocTimeZoneStructT_v02), qmiLocTimeZoneStructT_data_v02},
  {sizeof(qmiLocApCacheStructT_v02), qmiLocApCacheStructT_data_v02},
  {sizeof(qmiLocApDoNotCacheStructT_v02), qmiLocApDoNotCacheStructT_data_v02}
};

/* Message Table */
static const qmi_idl_message_table_entry loc_message_table_v02[] = {
  {sizeof(qmiLocGenRespMsgT_v02), qmiLocGenRespMsgT_data_v02},
  {sizeof(qmiLocInformClientRevisionReqMsgT_v02), qmiLocInformClientRevisionReqMsgT_data_v02},
  {sizeof(qmiLocRegEventsReqMsgT_v02), qmiLocRegEventsReqMsgT_data_v02},
  {sizeof(qmiLocStartReqMsgT_v02), qmiLocStartReqMsgT_data_v02},
  {sizeof(qmiLocStopReqMsgT_v02), qmiLocStopReqMsgT_data_v02},
  {sizeof(qmiLocEventPositionReportIndMsgT_v02), qmiLocEventPositionReportIndMsgT_data_v02},
  {sizeof(qmiLocEventGnssSvInfoIndMsgT_v02), qmiLocEventGnssSvInfoIndMsgT_data_v02},
  {sizeof(qmiLocEventNmeaIndMsgT_v02), qmiLocEventNmeaIndMsgT_data_v02},
  {sizeof(qmiLocEventNiNotifyVerifyReqIndMsgT_v02), qmiLocEventNiNotifyVerifyReqIndMsgT_data_v02},
  {sizeof(qmiLocEventInjectTimeReqIndMsgT_v02), qmiLocEventInjectTimeReqIndMsgT_data_v02},
  {sizeof(qmiLocEventInjectPredictedOrbitsReqIndMsgT_v02), qmiLocEventInjectPredictedOrbitsReqIndMsgT_data_v02},
  {sizeof(qmiLocEventInjectPositionReqIndMsgT_v02), qmiLocEventInjectPositionReqIndMsgT_data_v02},
  {sizeof(qmiLocEventEngineStateIndMsgT_v02), qmiLocEventEngineStateIndMsgT_data_v02},
  {sizeof(qmiLocEventFixSessionStateIndMsgT_v02), qmiLocEventFixSessionStateIndMsgT_data_v02},
  {sizeof(qmiLocEventWifiReqIndMsgT_v02), qmiLocEventWifiReqIndMsgT_data_v02},
  {sizeof(qmiLocEventSensorStreamingReadyStatusIndMsgT_v02), qmiLocEventSensorStreamingReadyStatusIndMsgT_data_v02},
  {sizeof(qmiLocEventTimeSyncReqIndMsgT_v02), qmiLocEventTimeSyncReqIndMsgT_data_v02},
  {sizeof(qmiLocEventSetSpiStreamingReportIndMsgT_v02), qmiLocEventSetSpiStreamingReportIndMsgT_data_v02},
  {sizeof(qmiLocEventLocationServerConnectionReqIndMsgT_v02), qmiLocEventLocationServerConnectionReqIndMsgT_data_v02},
  {sizeof(qmiLocEventNiGeofenceNotificationIndMsgT_v02), qmiLocEventNiGeofenceNotificationIndMsgT_data_v02},
  {sizeof(qmiLocEventGeofenceGenAlertIndMsgT_v02), qmiLocEventGeofenceGenAlertIndMsgT_data_v02},
  {sizeof(qmiLocEventGeofenceBreachIndMsgT_v02), qmiLocEventGeofenceBreachIndMsgT_data_v02},
  {sizeof(qmiLocEventPedometerControlIndMsgT_v02), qmiLocEventPedometerControlIndMsgT_data_v02},
  {sizeof(qmiLocEventMotionDataControlIndMsgT_v02), qmiLocEventMotionDataControlIndMsgT_data_v02},
  {sizeof(qmiLocEventGeofenceBatchedBreachIndMsgT_v02), qmiLocEventGeofenceBatchedBreachIndMsgT_data_v02},
  {sizeof(qmiLocEventGeofenceProximityIndMsgT_v02), qmiLocEventGeofenceProximityIndMsgT_data_v02},
  {sizeof(qmiLocEventGdtUploadBeginStatusReqIndMsgT_v02), qmiLocEventGdtUploadBeginStatusReqIndMsgT_data_v02},
  {sizeof(qmiLocEventGdtUploadEndReqIndMsgT_v02), qmiLocEventGdtUploadEndReqIndMsgT_data_v02},
  {sizeof(qmiLocGetServiceRevisionReqMsgT_v02), 0},
  {sizeof(qmiLocGetServiceRevisionIndMsgT_v02), qmiLocGetServiceRevisionIndMsgT_data_v02},
  {sizeof(qmiLocGetFixCriteriaReqMsgT_v02), 0},
  {sizeof(qmiLocGetFixCriteriaIndMsgT_v02), qmiLocGetFixCriteriaIndMsgT_data_v02},
  {sizeof(qmiLocNiUserRespReqMsgT_v02), qmiLocNiUserRespReqMsgT_data_v02},
  {sizeof(qmiLocNiUserRespIndMsgT_v02), qmiLocNiUserRespIndMsgT_data_v02},
  {sizeof(qmiLocInjectPredictedOrbitsDataReqMsgT_v02), qmiLocInjectPredictedOrbitsDataReqMsgT_data_v02},
  {sizeof(qmiLocInjectPredictedOrbitsDataIndMsgT_v02), qmiLocInjectPredictedOrbitsDataIndMsgT_data_v02},
  {sizeof(qmiLocGetPredictedOrbitsDataSourceReqMsgT_v02), 0},
  {sizeof(qmiLocGetPredictedOrbitsDataSourceIndMsgT_v02), qmiLocGetPredictedOrbitsDataSourceIndMsgT_data_v02},
  {sizeof(qmiLocGetPredictedOrbitsDataValidityReqMsgT_v02), 0},
  {sizeof(qmiLocGetPredictedOrbitsDataValidityIndMsgT_v02), qmiLocGetPredictedOrbitsDataValidityIndMsgT_data_v02},
  {sizeof(qmiLocInjectUtcTimeReqMsgT_v02), qmiLocInjectUtcTimeReqMsgT_data_v02},
  {sizeof(qmiLocInjectUtcTimeIndMsgT_v02), qmiLocInjectUtcTimeIndMsgT_data_v02},
  {sizeof(qmiLocInjectPositionReqMsgT_v02), qmiLocInjectPositionReqMsgT_data_v02},
  {sizeof(qmiLocInjectPositionIndMsgT_v02), qmiLocInjectPositionIndMsgT_data_v02},
  {sizeof(qmiLocSetEngineLockReqMsgT_v02), qmiLocSetEngineLockReqMsgT_data_v02},
  {sizeof(qmiLocSetEngineLockIndMsgT_v02), qmiLocSetEngineLockIndMsgT_data_v02},
  {sizeof(qmiLocGetEngineLockReqMsgT_v02), 0},
  {sizeof(qmiLocGetEngineLockIndMsgT_v02), qmiLocGetEngineLockIndMsgT_data_v02},
  {sizeof(qmiLocSetSbasConfigReqMsgT_v02), qmiLocSetSbasConfigReqMsgT_data_v02},
  {sizeof(qmiLocSetSbasConfigIndMsgT_v02), qmiLocSetSbasConfigIndMsgT_data_v02},
  {sizeof(qmiLocGetSbasConfigReqMsgT_v02), 0},
  {sizeof(qmiLocGetSbasConfigIndMsgT_v02), qmiLocGetSbasConfigIndMsgT_data_v02},
  {sizeof(qmiLocSetNmeaTypesReqMsgT_v02), qmiLocSetNmeaTypesReqMsgT_data_v02},
  {sizeof(qmiLocSetNmeaTypesIndMsgT_v02), qmiLocSetNmeaTypesIndMsgT_data_v02},
  {sizeof(qmiLocGetNmeaTypesReqMsgT_v02), 0},
  {sizeof(qmiLocGetNmeaTypesIndMsgT_v02), qmiLocGetNmeaTypesIndMsgT_data_v02},
  {sizeof(qmiLocSetLowPowerModeReqMsgT_v02), qmiLocSetLowPowerModeReqMsgT_data_v02},
  {sizeof(qmiLocSetLowPowerModeIndMsgT_v02), qmiLocSetLowPowerModeIndMsgT_data_v02},
  {sizeof(qmiLocGetLowPowerModeReqMsgT_v02), 0},
  {sizeof(qmiLocGetLowPowerModeIndMsgT_v02), qmiLocGetLowPowerModeIndMsgT_data_v02},
  {sizeof(qmiLocSetServerReqMsgT_v02), qmiLocSetServerReqMsgT_data_v02},
  {sizeof(qmiLocSetServerIndMsgT_v02), qmiLocSetServerIndMsgT_data_v02},
  {sizeof(qmiLocGetServerReqMsgT_v02), qmiLocGetServerReqMsgT_data_v02},
  {sizeof(qmiLocGetServerIndMsgT_v02), qmiLocGetServerIndMsgT_data_v02},
  {sizeof(qmiLocDeleteAssistDataReqMsgT_v02), qmiLocDeleteAssistDataReqMsgT_data_v02},
  {sizeof(qmiLocDeleteAssistDataIndMsgT_v02), qmiLocDeleteAssistDataIndMsgT_data_v02},
  {sizeof(qmiLocSetXtraTSessionControlReqMsgT_v02), qmiLocSetXtraTSessionControlReqMsgT_data_v02},
  {sizeof(qmiLocSetXtraTSessionControlIndMsgT_v02), qmiLocSetXtraTSessionControlIndMsgT_data_v02},
  {sizeof(qmiLocGetXtraTSessionControlReqMsgT_v02), 0},
  {sizeof(qmiLocGetXtraTSessionControlIndMsgT_v02), qmiLocGetXtraTSessionControlIndMsgT_data_v02},
  {sizeof(qmiLocInjectWifiPositionReqMsgT_v02), qmiLocInjectWifiPositionReqMsgT_data_v02},
  {sizeof(qmiLocInjectWifiPositionIndMsgT_v02), qmiLocInjectWifiPositionIndMsgT_data_v02},
  {sizeof(qmiLocNotifyWifiStatusReqMsgT_v02), qmiLocNotifyWifiStatusReqMsgT_data_v02},
  {sizeof(qmiLocNotifyWifiStatusIndMsgT_v02), qmiLocNotifyWifiStatusIndMsgT_data_v02},
  {sizeof(qmiLocGetRegisteredEventsReqMsgT_v02), 0},
  {sizeof(qmiLocGetRegisteredEventsIndMsgT_v02), qmiLocGetRegisteredEventsIndMsgT_data_v02},
  {sizeof(qmiLocSetOperationModeReqMsgT_v02), qmiLocSetOperationModeReqMsgT_data_v02},
  {sizeof(qmiLocSetOperationModeIndMsgT_v02), qmiLocSetOperationModeIndMsgT_data_v02},
  {sizeof(qmiLocGetOperationModeReqMsgT_v02), 0},
  {sizeof(qmiLocGetOperationModeIndMsgT_v02), qmiLocGetOperationModeIndMsgT_data_v02},
  {sizeof(qmiLocSetSpiStatusReqMsgT_v02), qmiLocSetSpiStatusReqMsgT_data_v02},
  {sizeof(qmiLocSetSpiStatusIndMsgT_v02), qmiLocSetSpiStatusIndMsgT_data_v02},
  {sizeof(qmiLocInjectSensorDataReqMsgT_v02), qmiLocInjectSensorDataReqMsgT_data_v02},
  {sizeof(qmiLocInjectSensorDataIndMsgT_v02), qmiLocInjectSensorDataIndMsgT_data_v02},
  {sizeof(qmiLocInjectTimeSyncDataReqMsgT_v02), qmiLocInjectTimeSyncDataReqMsgT_data_v02},
  {sizeof(qmiLocInjectTimeSyncDataIndMsgT_v02), qmiLocInjectTimeSyncDataIndMsgT_data_v02},
  {sizeof(qmiLocGetCradleMountConfigReqMsgT_v02), 0},
  {sizeof(qmiLocGetCradleMountConfigIndMsgT_v02), qmiLocGetCradleMountConfigIndMsgT_data_v02},
  {sizeof(qmiLocSetCradleMountConfigReqMsgT_v02), qmiLocSetCradleMountConfigReqMsgT_data_v02},
  {sizeof(qmiLocSetCradleMountConfigIndMsgT_v02), qmiLocSetCradleMountConfigIndMsgT_data_v02},
  {sizeof(qmiLocGetExternalPowerConfigReqMsgT_v02), 0},
  {sizeof(qmiLocGetExternalPowerConfigIndMsgT_v02), qmiLocGetExternalPowerConfigIndMsgT_data_v02},
  {sizeof(qmiLocSetExternalPowerConfigReqMsgT_v02), qmiLocSetExternalPowerConfigReqMsgT_data_v02},
  {sizeof(qmiLocSetExternalPowerConfigIndMsgT_v02), qmiLocSetExternalPowerConfigIndMsgT_data_v02},
  {sizeof(qmiLocInformLocationServerConnStatusReqMsgT_v02), qmiLocInformLocationServerConnStatusReqMsgT_data_v02},
  {sizeof(qmiLocInformLocationServerConnStatusIndMsgT_v02), qmiLocInformLocationServerConnStatusIndMsgT_data_v02},
  {sizeof(qmiLocSetProtocolConfigParametersReqMsgT_v02), qmiLocSetProtocolConfigParametersReqMsgT_data_v02},
  {sizeof(qmiLocSetProtocolConfigParametersIndMsgT_v02), qmiLocSetProtocolConfigParametersIndMsgT_data_v02},
  {sizeof(qmiLocGetProtocolConfigParametersReqMsgT_v02), qmiLocGetProtocolConfigParametersReqMsgT_data_v02},
  {sizeof(qmiLocGetProtocolConfigParametersIndMsgT_v02), qmiLocGetProtocolConfigParametersIndMsgT_data_v02},
  {sizeof(qmiLocSetSensorControlConfigReqMsgT_v02), qmiLocSetSensorControlConfigReqMsgT_data_v02},
  {sizeof(qmiLocSetSensorControlConfigIndMsgT_v02), qmiLocSetSensorControlConfigIndMsgT_data_v02},
  {sizeof(qmiLocGetSensorControlConfigReqMsgT_v02), 0},
  {sizeof(qmiLocGetSensorControlConfigIndMsgT_v02), qmiLocGetSensorControlConfigIndMsgT_data_v02},
  {sizeof(qmiLocSetSensorPropertiesReqMsgT_v02), qmiLocSetSensorPropertiesReqMsgT_data_v02},
  {sizeof(qmiLocSetSensorPropertiesIndMsgT_v02), qmiLocSetSensorPropertiesIndMsgT_data_v02},
  {sizeof(qmiLocGetSensorPropertiesReqMsgT_v02), qmiLocGetSensorPropertiesReqMsgT_data_v02},
  {sizeof(qmiLocGetSensorPropertiesIndMsgT_v02), qmiLocGetSensorPropertiesIndMsgT_data_v02},
  {sizeof(qmiLocSetSensorPerformanceControlConfigReqMsgT_v02), qmiLocSetSensorPerformanceControlConfigReqMsgT_data_v02},
  {sizeof(qmiLocSetSensorPerformanceControlConfigIndMsgT_v02), qmiLocSetSensorPerformanceControlConfigIndMsgT_data_v02},
  {sizeof(qmiLocGetSensorPerformanceControlConfigReqMsgT_v02), 0},
  {sizeof(qmiLocGetSensorPerformanceControlConfigIndMsgT_v02), qmiLocGetSensorPerformanceControlConfigIndMsgT_data_v02},
  {sizeof(qmiLocInjectSuplCertificateReqMsgT_v02), qmiLocInjectSuplCertificateReqMsgT_data_v02},
  {sizeof(qmiLocInjectSuplCertificateIndMsgT_v02), qmiLocInjectSuplCertificateIndMsgT_data_v02},
  {sizeof(qmiLocDeleteSuplCertificateReqMsgT_v02), qmiLocDeleteSuplCertificateReqMsgT_data_v02},
  {sizeof(qmiLocDeleteSuplCertificateIndMsgT_v02), qmiLocDeleteSuplCertificateIndMsgT_data_v02},
  {sizeof(qmiLocSetPositionEngineConfigParametersReqMsgT_v02), qmiLocSetPositionEngineConfigParametersReqMsgT_data_v02},
  {sizeof(qmiLocSetPositionEngineConfigParametersIndMsgT_v02), qmiLocSetPositionEngineConfigParametersIndMsgT_data_v02},
  {sizeof(qmiLocGetPositionEngineConfigParametersReqMsgT_v02), qmiLocGetPositionEngineConfigParametersReqMsgT_data_v02},
  {sizeof(qmiLocGetPositionEngineConfigParametersIndMsgT_v02), qmiLocGetPositionEngineConfigParametersIndMsgT_data_v02},
  {sizeof(qmiLocAddCircularGeofenceReqMsgT_v02), qmiLocAddCircularGeofenceReqMsgT_data_v02},
  {sizeof(qmiLocAddCircularGeofenceIndMsgT_v02), qmiLocAddCircularGeofenceIndMsgT_data_v02},
  {sizeof(qmiLocDeleteGeofenceReqMsgT_v02), qmiLocDeleteGeofenceReqMsgT_data_v02},
  {sizeof(qmiLocDeleteGeofenceIndMsgT_v02), qmiLocDeleteGeofenceIndMsgT_data_v02},
  {sizeof(qmiLocQueryGeofenceReqMsgT_v02), qmiLocQueryGeofenceReqMsgT_data_v02},
  {sizeof(qmiLocQueryGeofenceIndMsgT_v02), qmiLocQueryGeofenceIndMsgT_data_v02},
  {sizeof(qmiLocSetGeofenceEngineConfigReqMsgT_v02), qmiLocSetGeofenceEngineConfigReqMsgT_data_v02},
  {sizeof(qmiLocSetGeofenceEngineConfigIndMsgT_v02), qmiLocSetGeofenceEngineConfigIndMsgT_data_v02},
  {sizeof(qmiLocGetGeofenceEngineConfigReqMsgT_v02), qmiLocGetGeofenceEngineConfigReqMsgT_data_v02},
  {sizeof(qmiLocGetGeofenceEngineConfigIndMsgT_v02), qmiLocGetGeofenceEngineConfigIndMsgT_data_v02},
  {sizeof(qmiLocEditGeofenceReqMsgT_v02), qmiLocEditGeofenceReqMsgT_data_v02},
  {sizeof(qmiLocEditGeofenceIndMsgT_v02), qmiLocEditGeofenceIndMsgT_data_v02},
  {sizeof(qmiLocGetBestAvailablePositionReqMsgT_v02), qmiLocGetBestAvailablePositionReqMsgT_data_v02},
  {sizeof(qmiLocGetBestAvailablePositionIndMsgT_v02), qmiLocGetBestAvailablePositionIndMsgT_data_v02},
  {sizeof(qmiLocInjectMotionDataReqMsgT_v02), qmiLocInjectMotionDataReqMsgT_data_v02},
  {sizeof(qmiLocInjectMotionDataIndMsgT_v02), qmiLocInjectMotionDataIndMsgT_data_v02},
  {sizeof(qmiLocGetNiGeofenceIdListReqMsgT_v02), qmiLocGetNiGeofenceIdListReqMsgT_data_v02},
  {sizeof(qmiLocGetNiGeofenceIdListIndMsgT_v02), qmiLocGetNiGeofenceIdListIndMsgT_data_v02},
  {sizeof(qmiLocInjectGSMCellInfoReqMsgT_v02), qmiLocInjectGSMCellInfoReqMsgT_data_v02},
  {sizeof(qmiLocInjectGSMCellInfoIndMsgT_v02), qmiLocInjectGSMCellInfoIndMsgT_data_v02},
  {sizeof(qmiLocInjectWCDMACellInfoReqMsgT_v02), qmiLocInjectWCDMACellInfoReqMsgT_data_v02},
  {sizeof(qmiLocInjectWCDMACellInfoIndMsgT_v02), qmiLocInjectWCDMACellInfoIndMsgT_data_v02},
  {sizeof(qmiLocInjectTDSCDMACellInfoReqMsgT_v02), qmiLocInjectTDSCDMACellInfoReqMsgT_data_v02},
  {sizeof(qmiLocInjectTDSCDMACellInfoIndMsgT_v02), qmiLocInjectTDSCDMACellInfoIndMsgT_data_v02},
  {sizeof(qmiLocInjectSubscriberIDReqMsgT_v02), qmiLocInjectSubscriberIDReqMsgT_data_v02},
  {sizeof(qmiLocInjectSubscriberIDIndMsgT_v02), qmiLocInjectSubscriberIDIndMsgT_data_v02},
  {sizeof(qmiLocInjectNetworkInitiatedMessageReqMsgT_v02), qmiLocInjectNetworkInitiatedMessageReqMsgT_data_v02},
  {sizeof(qmiLocInjectNetworkInitiatedMessageIndMsgT_v02), qmiLocInjectNetworkInitiatedMessageIndMsgT_data_v02},
  {sizeof(qmiLocWWANOutOfServiceNotificationReqMsgT_v02), 0},
  {sizeof(qmiLocWWANOutOfServiceNotificationIndMsgT_v02), qmiLocWWANOutOfServiceNotificationIndMsgT_data_v02},
  {sizeof(qmiLocPedometerReportReqMsgT_v02), qmiLocPedometerReportReqMsgT_data_v02},
  {sizeof(qmiLocPedometerReportIndMsgT_v02), qmiLocPedometerReportIndMsgT_data_v02},
  {sizeof(qmiLocGetBatchSizeReqMsgT_v02), qmiLocGetBatchSizeReqMsgT_data_v02},
  {sizeof(qmiLocGetBatchSizeIndMsgT_v02), qmiLocGetBatchSizeIndMsgT_data_v02},
  {sizeof(qmiLocStartBatchingReqMsgT_v02), qmiLocStartBatchingReqMsgT_data_v02},
  {sizeof(qmiLocStartBatchingIndMsgT_v02), qmiLocStartBatchingIndMsgT_data_v02},
  {sizeof(qmiLocEventBatchFullIndMsgT_v02), qmiLocEventBatchFullIndMsgT_data_v02},
  {sizeof(qmiLocEventLiveBatchedPositionReportIndMsgT_v02), qmiLocEventLiveBatchedPositionReportIndMsgT_data_v02},
  {sizeof(qmiLocReadFromBatchReqMsgT_v02), qmiLocReadFromBatchReqMsgT_data_v02},
  {sizeof(qmiLocReadFromBatchIndMsgT_v02), qmiLocReadFromBatchIndMsgT_data_v02},
  {sizeof(qmiLocStopBatchingReqMsgT_v02), qmiLocStopBatchingReqMsgT_data_v02},
  {sizeof(qmiLocStopBatchingIndMsgT_v02), qmiLocStopBatchingIndMsgT_data_v02},
  {sizeof(qmiLocReleaseBatchReqMsgT_v02), qmiLocReleaseBatchReqMsgT_data_v02},
  {sizeof(qmiLocReleaseBatchIndMsgT_v02), qmiLocReleaseBatchIndMsgT_data_v02},
  {sizeof(qmiLocEventInjectWifiApDataReqIndMsgT_v02), 0},
  {sizeof(qmiLocInjectWifiApDataReqMsgT_v02), qmiLocInjectWifiApDataReqMsgT_data_v02},
  {sizeof(qmiLocInjectWifiApDataIndMsgT_v02), qmiLocInjectWifiApDataIndMsgT_data_v02},
  {sizeof(qmiLocNotifyWifiAttachmentStatusReqMsgT_v02), qmiLocNotifyWifiAttachmentStatusReqMsgT_data_v02},
  {sizeof(qmiLocNotifyWifiAttachmentStatusIndMsgT_v02), qmiLocNotifyWifiAttachmentStatusIndMsgT_data_v02},
  {sizeof(qmiLocNotifyWifiEnabledStatusReqMsgT_v02), qmiLocNotifyWifiEnabledStatusReqMsgT_data_v02},
  {sizeof(qmiLocNotifyWifiEnabledStatusIndMsgT_v02), qmiLocNotifyWifiEnabledStatusIndMsgT_data_v02},
  {sizeof(qmiLocEventVehicleDataReadyIndMsgT_v02), qmiLocEventVehicleDataReadyIndMsgT_data_v02},
  {sizeof(qmiLocInjectVehicleSensorDataReqMsgT_v02), qmiLocInjectVehicleSensorDataReqMsgT_data_v02},
  {sizeof(qmiLocInjectVehicleSensorDataIndMsgT_v02), qmiLocInjectVehicleSensorDataIndMsgT_data_v02},
  {sizeof(qmiLocGetAvailWwanPositionReqMsgT_v02), qmiLocGetAvailWwanPositionReqMsgT_data_v02},
  {sizeof(qmiLocGetAvailWwanPositionIndMsgT_v02), qmiLocGetAvailWwanPositionIndMsgT_data_v02},
  {sizeof(qmiLocSetPremiumServicesCfgReqMsgT_v02), qmiLocSetPremiumServicesCfgReqMsgT_data_v02},
  {sizeof(qmiLocSetPremiumServicesCfgIndMsgT_v02), qmiLocSetPremiumServicesCfgIndMsgT_data_v02},
  {sizeof(qmiLocSetXtraVersionCheckReqMsgT_v02), qmiLocSetXtraVersionCheckReqMsgT_data_v02},
  {sizeof(qmiLocSetXtraVersionCheckIndMsgT_v02), qmiLocSetXtraVersionCheckIndMsgT_data_v02},
  {sizeof(qmiLocSetGNSSConstRepConfigReqMsgT_v02), qmiLocSetGNSSConstRepConfigReqMsgT_data_v02},
  {sizeof(qmiLocSetGNSSConstRepConfigIndMsgT_v02), qmiLocSetGNSSConstRepConfigIndMsgT_data_v02},
  {sizeof(qmiLocEventGnssSvMeasInfoIndMsgT_v02), qmiLocEventGnssSvMeasInfoIndMsgT_data_v02},
  {sizeof(qmiLocEventGnssSvPolyIndMsgT_v02), qmiLocEventGnssSvPolyIndMsgT_data_v02},
  {sizeof(qmiLocAddGeofenceContextReqMsgT_v02), qmiLocAddGeofenceContextReqMsgT_data_v02},
  {sizeof(qmiLocAddGeofenceContextIndMsgT_v02), qmiLocAddGeofenceContextIndMsgT_data_v02},
  {sizeof(qmiLocSetGeofenceEngineContextReqMsgT_v02), qmiLocSetGeofenceEngineContextReqMsgT_data_v02},
  {sizeof(qmiLocSetGeofenceEngineContextIndMsgT_v02), qmiLocSetGeofenceEngineContextIndMsgT_data_v02},
  {sizeof(qmiLocDeleteGeofenceContextReqMsgT_v02), qmiLocDeleteGeofenceContextReqMsgT_data_v02},
  {sizeof(qmiLocDeleteGeofenceContextIndMsgT_v02), qmiLocDeleteGeofenceContextIndMsgT_data_v02},
  {sizeof(qmiLocInjectGtpClientDownloadedDataReqMsgT_v02), qmiLocInjectGtpClientDownloadedDataReqMsgT_data_v02},
  {sizeof(qmiLocInjectGtpClientDownloadedDataIndMsgT_v02), qmiLocInjectGtpClientDownloadedDataIndMsgT_data_v02},
  {sizeof(qmiLocGdtUploadBeginStatusReqMsgT_v02), qmiLocGdtUploadBeginStatusReqMsgT_data_v02},
  {sizeof(qmiLocGdtUploadBeginStatusIndMsgT_v02), qmiLocGdtUploadBeginStatusIndMsgT_data_v02},
  {sizeof(qmiLocGdtUploadEndReqMsgT_v02), qmiLocGdtUploadEndReqMsgT_data_v02},
  {sizeof(qmiLocGdtUploadEndIndMsgT_v02), qmiLocGdtUploadEndIndMsgT_data_v02},
  {sizeof(qmiLocStartDbtReqMsgT_v02), qmiLocStartDbtReqMsgT_data_v02},
  {sizeof(qmiLocStartDbtIndMsgT_v02), qmiLocStartDbtIndMsgT_data_v02},
  {sizeof(qmiLocStopDbtReqMsgT_v02), qmiLocStopDbtReqMsgT_data_v02},
  {sizeof(qmiLocStopDbtIndMsgT_v02), qmiLocStopDbtIndMsgT_data_v02},
  {sizeof(qmiLocEventDbtPositionReportIndMsgT_v02), qmiLocEventDbtPositionReportIndMsgT_data_v02},
  {sizeof(qmiLocEventDbtSessionStatusIndMsgT_v02), qmiLocEventDbtSessionStatusIndMsgT_data_v02},
  {sizeof(qmiLocSecureGetAvailablePositionReqMsgT_v02), qmiLocSecureGetAvailablePositionReqMsgT_data_v02},
  {sizeof(qmiLocSecureGetAvailablePositionIndMsgT_v02), qmiLocSecureGetAvailablePositionIndMsgT_data_v02},
  {sizeof(qmiLocEventGeofenceBatchedDwellIndMsgT_v02), qmiLocEventGeofenceBatchedDwellIndMsgT_data_v02},
  {sizeof(qmiLocEventGetTimeZoneReqIndMsgT_v02), qmiLocEventGetTimeZoneReqIndMsgT_data_v02},
  {sizeof(qmiLocInjectTimeZoneInfoReqMsgT_v02), qmiLocInjectTimeZoneInfoReqMsgT_data_v02},
  {sizeof(qmiLocInjectTimeZoneInfoIndMsgT_v02), qmiLocInjectTimeZoneInfoIndMsgT_data_v02},
  {sizeof(qmiLocInjectApCacheDataReqMsgT_v02), qmiLocInjectApCacheDataReqMsgT_data_v02},
  {sizeof(qmiLocInjectApCacheDataIndMsgT_v02), qmiLocInjectApCacheDataIndMsgT_data_v02},
  {sizeof(qmiLocInjectApDoNotCacheDataReqMsgT_v02), qmiLocInjectApDoNotCacheDataReqMsgT_data_v02},
  {sizeof(qmiLocInjectApDoNotCacheDataIndMsgT_v02), qmiLocInjectApDoNotCacheDataIndMsgT_data_v02},
  {sizeof(qmiLocEventBatchingStatusIndMsgT_v02), qmiLocEventBatchingStatusIndMsgT_data_v02},
  {sizeof(qmiLocQueryAonConfigReqMsgT_v02), qmiLocQueryAonConfigReqMsgT_data_v02},
  {sizeof(qmiLocQueryAonConfigIndMsgT_v02), qmiLocQueryAonConfigIndMsgT_data_v02}
};

/* Range Table */
/* No Ranges Defined in IDL */

/* Predefine the Type Table Object */
static const qmi_idl_type_table_object loc_qmi_idl_type_table_object_v02;

/*Referenced Tables Array*/
static const qmi_idl_type_table_object *loc_qmi_idl_type_table_object_referenced_tables_v02[] =
{&loc_qmi_idl_type_table_object_v02, &common_qmi_idl_type_table_object_v01};

/*Type Table Object*/
static const qmi_idl_type_table_object loc_qmi_idl_type_table_object_v02 = {
  sizeof(loc_type_table_v02)/sizeof(qmi_idl_type_table_entry ),
  sizeof(loc_message_table_v02)/sizeof(qmi_idl_message_table_entry),
  1,
  loc_type_table_v02,
  loc_message_table_v02,
  loc_qmi_idl_type_table_object_referenced_tables_v02,
  NULL
};

/*Arrays of service_message_table_entries for commands, responses and indications*/
static const qmi_idl_service_message_table_entry loc_service_command_messages_v02[] = {
  {QMI_LOC_GET_SUPPORTED_MSGS_REQ_V02, QMI_IDL_TYPE16(1, 0), 0},
  {QMI_LOC_GET_SUPPORTED_FIELDS_REQ_V02, QMI_IDL_TYPE16(1, 2), 5},
  {QMI_LOC_INFORM_CLIENT_REVISION_REQ_V02, QMI_IDL_TYPE16(0, 1), 7},
  {QMI_LOC_REG_EVENTS_REQ_V02, QMI_IDL_TYPE16(0, 2), 11},
  {QMI_LOC_START_REQ_V02, QMI_IDL_TYPE16(0, 3), 117},
  {QMI_LOC_STOP_REQ_V02, QMI_IDL_TYPE16(0, 4), 4},
  {QMI_LOC_GET_SERVICE_REVISION_REQ_V02, QMI_IDL_TYPE16(0, 28), 0},
  {QMI_LOC_GET_FIX_CRITERIA_REQ_V02, QMI_IDL_TYPE16(0, 30), 0},
  {QMI_LOC_NI_USER_RESPONSE_REQ_V02, QMI_IDL_TYPE16(0, 32), 1345},
  {QMI_LOC_INJECT_PREDICTED_ORBITS_DATA_REQ_V02, QMI_IDL_TYPE16(0, 34), 1053},
  {QMI_LOC_GET_PREDICTED_ORBITS_DATA_SOURCE_REQ_V02, QMI_IDL_TYPE16(0, 36), 0},
  {QMI_LOC_GET_PREDICTED_ORBITS_DATA_VALIDITY_REQ_V02, QMI_IDL_TYPE16(0, 38), 0},
  {QMI_LOC_INJECT_UTC_TIME_REQ_V02, QMI_IDL_TYPE16(0, 40), 18},
  {QMI_LOC_INJECT_POSITION_REQ_V02, QMI_IDL_TYPE16(0, 42), 123},
  {QMI_LOC_SET_ENGINE_LOCK_REQ_V02, QMI_IDL_TYPE16(0, 44), 7},
  {QMI_LOC_GET_ENGINE_LOCK_REQ_V02, QMI_IDL_TYPE16(0, 46), 0},
  {QMI_LOC_SET_SBAS_CONFIG_REQ_V02, QMI_IDL_TYPE16(0, 48), 4},
  {QMI_LOC_GET_SBAS_CONFIG_REQ_V02, QMI_IDL_TYPE16(0, 50), 0},
  {QMI_LOC_SET_NMEA_TYPES_REQ_V02, QMI_IDL_TYPE16(0, 52), 7},
  {QMI_LOC_GET_NMEA_TYPES_REQ_V02, QMI_IDL_TYPE16(0, 54), 0},
  {QMI_LOC_SET_LOW_POWER_MODE_REQ_V02, QMI_IDL_TYPE16(0, 56), 4},
  {QMI_LOC_GET_LOW_POWER_MODE_REQ_V02, QMI_IDL_TYPE16(0, 58), 0},
  {QMI_LOC_SET_SERVER_REQ_V02, QMI_IDL_TYPE16(0, 60), 297},
  {QMI_LOC_GET_SERVER_REQ_V02, QMI_IDL_TYPE16(0, 62), 11},
  {QMI_LOC_DELETE_ASSIST_DATA_REQ_V02, QMI_IDL_TYPE16(0, 64), 1156},
  {QMI_LOC_SET_XTRA_T_SESSION_CONTROL_REQ_V02, QMI_IDL_TYPE16(0, 66), 4},
  {QMI_LOC_GET_XTRA_T_SESSION_CONTROL_REQ_V02, QMI_IDL_TYPE16(0, 68), 0},
  {QMI_LOC_INJECT_WIFI_POSITION_REQ_V02, QMI_IDL_TYPE16(0, 70), 2353},
  {QMI_LOC_NOTIFY_WIFI_STATUS_REQ_V02, QMI_IDL_TYPE16(0, 72), 7},
  {QMI_LOC_GET_REGISTERED_EVENTS_REQ_V02, QMI_IDL_TYPE16(0, 74), 0},
  {QMI_LOC_SET_OPERATION_MODE_REQ_V02, QMI_IDL_TYPE16(0, 76), 7},
  {QMI_LOC_GET_OPERATION_MODE_REQ_V02, QMI_IDL_TYPE16(0, 78), 0},
  {QMI_LOC_SET_SPI_STATUS_REQ_V02, QMI_IDL_TYPE16(0, 80), 8},
  {QMI_LOC_INJECT_SENSOR_DATA_REQ_V02, QMI_IDL_TYPE16(0, 82), 2779},
  {QMI_LOC_INJECT_TIME_SYNC_DATA_REQ_V02, QMI_IDL_TYPE16(0, 84), 21},
  {QMI_LOC_SET_CRADLE_MOUNT_CONFIG_REQ_V02, QMI_IDL_TYPE16(0, 88), 11},
  {QMI_LOC_GET_CRADLE_MOUNT_CONFIG_REQ_V02, QMI_IDL_TYPE16(0, 86), 0},
  {QMI_LOC_SET_EXTERNAL_POWER_CONFIG_REQ_V02, QMI_IDL_TYPE16(0, 92), 7},
  {QMI_LOC_GET_EXTERNAL_POWER_CONFIG_REQ_V02, QMI_IDL_TYPE16(0, 90), 0},
  {QMI_LOC_INFORM_LOCATION_SERVER_CONN_STATUS_REQ_V02, QMI_IDL_TYPE16(0, 94), 129},
  {QMI_LOC_SET_PROTOCOL_CONFIG_PARAMETERS_REQ_V02, QMI_IDL_TYPE16(0, 96), 57},
  {QMI_LOC_GET_PROTOCOL_CONFIG_PARAMETERS_REQ_V02, QMI_IDL_TYPE16(0, 98), 11},
  {QMI_LOC_SET_SENSOR_CONTROL_CONFIG_REQ_V02, QMI_IDL_TYPE16(0, 100), 14},
  {QMI_LOC_GET_SENSOR_CONTROL_CONFIG_REQ_V02, QMI_IDL_TYPE16(0, 102), 0},
  {QMI_LOC_SET_SENSOR_PROPERTIES_REQ_V02, QMI_IDL_TYPE16(0, 104), 88},
  {QMI_LOC_GET_SENSOR_PROPERTIES_REQ_V02, QMI_IDL_TYPE16(0, 106), 7},
  {QMI_LOC_SET_SENSOR_PERFORMANCE_CONTROL_CONFIGURATION_REQ_V02, QMI_IDL_TYPE16(0, 108), 42},
  {QMI_LOC_GET_SENSOR_PERFORMANCE_CONTROL_CONFIGURATION_REQ_V02, QMI_IDL_TYPE16(0, 110), 0},
  {QMI_LOC_INJECT_SUPL_CERTIFICATE_REQ_V02, QMI_IDL_TYPE16(0, 112), 2009},
  {QMI_LOC_DELETE_SUPL_CERTIFICATE_REQ_V02, QMI_IDL_TYPE16(0, 114), 4},
  {QMI_LOC_SET_POSITION_ENGINE_CONFIG_PARAMETERS_REQ_V02, QMI_IDL_TYPE16(0, 116), 16},
  {QMI_LOC_GET_POSITION_ENGINE_CONFIG_PARAMETERS_REQ_V02, QMI_IDL_TYPE16(0, 118), 7},
  {QMI_LOC_ADD_CIRCULAR_GEOFENCE_REQ_V02, QMI_IDL_TYPE16(0, 120), 70},
  {QMI_LOC_DELETE_GEOFENCE_REQ_V02, QMI_IDL_TYPE16(0, 122), 14},
  {QMI_LOC_QUERY_GEOFENCE_REQ_V02, QMI_IDL_TYPE16(0, 124), 14},
  {QMI_LOC_EDIT_GEOFENCE_REQ_V02, QMI_IDL_TYPE16(0, 130), 32},
  {QMI_LOC_GET_BEST_AVAILABLE_POSITION_REQ_V02, QMI_IDL_TYPE16(0, 132), 7},
  {QMI_LOC_INJECT_MOTION_DATA_REQ_V02, QMI_IDL_TYPE16(0, 134), 19},
  {QMI_LOC_GET_NI_GEOFENCE_ID_LIST_REQ_V02, QMI_IDL_TYPE16(0, 136), 7},
  {QMI_LOC_INJECT_GSM_CELL_INFO_REQ_V02, QMI_IDL_TYPE16(0, 138), 30},
  {QMI_LOC_INJECT_NETWORK_INITIATED_MESSAGE_REQ_V02, QMI_IDL_TYPE16(0, 146), 1036},
  {QMI_LOC_WWAN_OUT_OF_SERVICE_NOTIFICATION_REQ_V02, QMI_IDL_TYPE16(0, 148), 0},
  {QMI_LOC_PEDOMETER_REPORT_REQ_V02, QMI_IDL_TYPE16(0, 150), 46},
  {QMI_LOC_INJECT_WCDMA_CELL_INFO_REQ_V02, QMI_IDL_TYPE16(0, 140), 36},
  {QMI_LOC_INJECT_TDSCDMA_CELL_INFO_REQ_V02, QMI_IDL_TYPE16(0, 142), 33},
  {QMI_LOC_INJECT_SUBSCRIBER_ID_REQ_V02, QMI_IDL_TYPE16(0, 144), 22},
  {QMI_LOC_SET_GEOFENCE_ENGINE_CONFIG_REQ_V02, QMI_IDL_TYPE16(0, 126), 224},
  {QMI_LOC_GET_GEOFENCE_ENGINE_CONFIG_REQ_V02, QMI_IDL_TYPE16(0, 128), 7},
  {QMI_LOC_GET_BATCH_SIZE_REQ_V02, QMI_IDL_TYPE16(0, 152), 14},
  {QMI_LOC_START_BATCHING_REQ_V02, QMI_IDL_TYPE16(0, 154), 39},
  {QMI_LOC_READ_FROM_BATCH_REQ_V02, QMI_IDL_TYPE16(0, 158), 14},
  {QMI_LOC_STOP_BATCHING_REQ_V02, QMI_IDL_TYPE16(0, 160), 14},
  {QMI_LOC_RELEASE_BATCH_REQ_V02, QMI_IDL_TYPE16(0, 162), 7},
  {QMI_LOC_INJECT_WIFI_AP_DATA_REQ_V02, QMI_IDL_TYPE16(0, 165), 2454},
  {QMI_LOC_NOTIFY_WIFI_ATTACHMENT_STATUS_REQ_V02, QMI_IDL_TYPE16(0, 167), 51},
  {QMI_LOC_NOTIFY_WIFI_ENABLED_STATUS_REQ_V02, QMI_IDL_TYPE16(0, 169), 7},
  {QMI_LOC_INJECT_VEHICLE_SENSOR_DATA_REQ_V02, QMI_IDL_TYPE16(0, 172), 3360},
  {QMI_LOC_GET_AVAILABLE_WWAN_POSITION_REQ_V02, QMI_IDL_TYPE16(0, 174), 7},
  {QMI_LOC_SET_PREMIUM_SERVICES_CONFIG_REQ_V02, QMI_IDL_TYPE16(0, 176), 14},
  {QMI_LOC_SET_XTRA_VERSION_CHECK_REQ_V02, QMI_IDL_TYPE16(0, 178), 7},
  {QMI_LOC_SET_GNSS_CONSTELL_REPORT_CONFIG_V02, QMI_IDL_TYPE16(0, 180), 22},
  {QMI_LOC_ADD_GEOFENCE_CONTEXT_REQ_V02, QMI_IDL_TYPE16(0, 184), 2517},
  {QMI_LOC_SET_GEOFENCE_ENGINE_CONTEXT_REQ_V02, QMI_IDL_TYPE16(0, 186), 25},
  {QMI_LOC_DELETE_GEOFENCE_CONTEXT_REQ_V02, QMI_IDL_TYPE16(0, 188), 21},
  {QMI_LOC_INJECT_GTP_CLIENT_DOWNLOADED_DATA_REQ_V02, QMI_IDL_TYPE16(0, 190), 517},
  {QMI_LOC_GDT_UPLOAD_BEGIN_STATUS_REQ_V02, QMI_IDL_TYPE16(0, 192), 21},
  {QMI_LOC_GDT_UPLOAD_END_REQ_V02, QMI_IDL_TYPE16(0, 194), 21},
  {QMI_LOC_START_DBT_REQ_V02, QMI_IDL_TYPE16(0, 196), 36},
  {QMI_LOC_STOP_DBT_REQ_V02, QMI_IDL_TYPE16(0, 198), 4},
  {QMI_LOC_SECURE_GET_AVAILABLE_POSITION_REQ_V02, QMI_IDL_TYPE16(0, 202), 268},
  {QMI_LOC_INJECT_TIME_ZONE_INFO_REQ_V02, QMI_IDL_TYPE16(0, 206), 30},
  {QMI_LOC_INJECT_APCACHE_DATA_REQ_V02, QMI_IDL_TYPE16(0, 208), 1616},
  {QMI_LOC_INJECT_APDONOTCACHE_DATA_REQ_V02, QMI_IDL_TYPE16(0, 210), 656},
  {QMI_LOC_QUERY_AON_CONFIG_REQ_V02, QMI_IDL_TYPE16(0, 213), 7}
};

static const qmi_idl_service_message_table_entry loc_service_response_messages_v02[] = {
  {QMI_LOC_GET_SUPPORTED_MSGS_RESP_V02, QMI_IDL_TYPE16(1, 1), 8204},
  {QMI_LOC_GET_SUPPORTED_FIELDS_RESP_V02, QMI_IDL_TYPE16(1, 3), 115},
  {QMI_LOC_INFORM_CLIENT_REVISION_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_REG_EVENTS_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_START_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_STOP_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_GET_SERVICE_REVISION_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_GET_FIX_CRITERIA_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_NI_USER_RESPONSE_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_INJECT_PREDICTED_ORBITS_DATA_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_GET_PREDICTED_ORBITS_DATA_SOURCE_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_GET_PREDICTED_ORBITS_DATA_VALIDITY_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_INJECT_UTC_TIME_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_INJECT_POSITION_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_SET_ENGINE_LOCK_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_GET_ENGINE_LOCK_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_SET_SBAS_CONFIG_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_GET_SBAS_CONFIG_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_SET_NMEA_TYPES_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_GET_NMEA_TYPES_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_SET_LOW_POWER_MODE_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_GET_LOW_POWER_MODE_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_SET_SERVER_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_GET_SERVER_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_DELETE_ASSIST_DATA_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_SET_XTRA_T_SESSION_CONTROL_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_GET_XTRA_T_SESSION_CONTROL_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_INJECT_WIFI_POSITION_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_NOTIFY_WIFI_STATUS_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_GET_REGISTERED_EVENTS_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_SET_OPERATION_MODE_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_GET_OPERATION_MODE_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_SET_SPI_STATUS_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_INJECT_SENSOR_DATA_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_INJECT_TIME_SYNC_DATA_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_SET_CRADLE_MOUNT_CONFIG_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_GET_CRADLE_MOUNT_CONFIG_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_SET_EXTERNAL_POWER_CONFIG_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_GET_EXTERNAL_POWER_CONFIG_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_INFORM_LOCATION_SERVER_CONN_STATUS_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_SET_PROTOCOL_CONFIG_PARAMETERS_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_GET_PROTOCOL_CONFIG_PARAMETERS_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_SET_SENSOR_CONTROL_CONFIG_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_GET_SENSOR_CONTROL_CONFIG_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_SET_SENSOR_PROPERTIES_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_GET_SENSOR_PROPERTIES_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_SET_SENSOR_PERFORMANCE_CONTROL_CONFIGURATION_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_GET_SENSOR_PERFORMANCE_CONTROL_CONFIGURATION_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_INJECT_SUPL_CERTIFICATE_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_DELETE_SUPL_CERTIFICATE_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_SET_POSITION_ENGINE_CONFIG_PARAMETERS_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_GET_POSITION_ENGINE_CONFIG_PARAMETERS_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_ADD_CIRCULAR_GEOFENCE_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_DELETE_GEOFENCE_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_QUERY_GEOFENCE_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_EDIT_GEOFENCE_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_GET_BEST_AVAILABLE_POSITION_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_INJECT_MOTION_DATA_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_GET_NI_GEOFENCE_ID_LIST_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_INJECT_GSM_CELL_INFO_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_INJECT_NETWORK_INITIATED_MESSAGE_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_WWAN_OUT_OF_SERVICE_NOTIFICATION_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_PEDOMETER_REPORT_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_INJECT_WCDMA_CELL_INFO_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_INJECT_TDSCDMA_CELL_INFO_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_INJECT_SUBSCRIBER_ID_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_SET_GEOFENCE_ENGINE_CONFIG_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_GET_GEOFENCE_ENGINE_CONFIG_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_GET_BATCH_SIZE_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_START_BATCHING_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_READ_FROM_BATCH_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_STOP_BATCHING_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_RELEASE_BATCH_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_INJECT_WIFI_AP_DATA_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_NOTIFY_WIFI_ATTACHMENT_STATUS_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_NOTIFY_WIFI_ENABLED_STATUS_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_INJECT_VEHICLE_SENSOR_DATA_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_GET_AVAILABLE_WWAN_POSITION_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_SET_PREMIUM_SERVICES_CONFIG_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_SET_XTRA_VERSION_CHECK_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_SET_GNSS_CONSTELL_REPORT_CONFIG_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_ADD_GEOFENCE_CONTEXT_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_SET_GEOFENCE_ENGINE_CONTEXT_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_DELETE_GEOFENCE_CONTEXT_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_INJECT_GTP_CLIENT_DOWNLOADED_DATA_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_GDT_UPLOAD_BEGIN_STATUS_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_GDT_UPLOAD_END_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_START_DBT_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_STOP_DBT_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_SECURE_GET_AVAILABLE_POSITION_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_INJECT_TIME_ZONE_INFO_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_INJECT_APCACHE_DATA_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_INJECT_APDONOTCACHE_DATA_RESP_V02, QMI_IDL_TYPE16(0, 0), 7},
  {QMI_LOC_QUERY_AON_CONFIG_RESP_V02, QMI_IDL_TYPE16(0, 0), 7}
};

static const qmi_idl_service_message_table_entry loc_service_indication_messages_v02[] = {
  {QMI_LOC_EVENT_POSITION_REPORT_IND_V02, QMI_IDL_TYPE16(0, 5), 392},
  {QMI_LOC_EVENT_GNSS_SV_INFO_IND_V02, QMI_IDL_TYPE16(0, 6), 2248},
  {QMI_LOC_EVENT_NMEA_IND_V02, QMI_IDL_TYPE16(0, 7), 203},
  {QMI_LOC_EVENT_NI_NOTIFY_VERIFY_REQ_IND_V02, QMI_IDL_TYPE16(0, 8), 1338},
  {QMI_LOC_EVENT_INJECT_TIME_REQ_IND_V02, QMI_IDL_TYPE16(0, 9), 776},
  {QMI_LOC_EVENT_INJECT_PREDICTED_ORBITS_REQ_IND_V02, QMI_IDL_TYPE16(0, 10), 783},
  {QMI_LOC_EVENT_INJECT_POSITION_REQ_IND_V02, QMI_IDL_TYPE16(0, 11), 40},
  {QMI_LOC_EVENT_ENGINE_STATE_IND_V02, QMI_IDL_TYPE16(0, 12), 7},
  {QMI_LOC_EVENT_FIX_SESSION_STATE_IND_V02, QMI_IDL_TYPE16(0, 13), 11},
  {QMI_LOC_EVENT_WIFI_REQ_IND_V02, QMI_IDL_TYPE16(0, 14), 12},
  {QMI_LOC_EVENT_SENSOR_STREAMING_READY_STATUS_IND_V02, QMI_IDL_TYPE16(0, 15), 48},
  {QMI_LOC_EVENT_TIME_SYNC_REQ_IND_V02, QMI_IDL_TYPE16(0, 16), 7},
  {QMI_LOC_EVENT_SET_SPI_STREAMING_REPORT_IND_V02, QMI_IDL_TYPE16(0, 17), 4},
  {QMI_LOC_EVENT_LOCATION_SERVER_CONNECTION_REQ_IND_V02, QMI_IDL_TYPE16(0, 18), 21},
  {QMI_LOC_GET_SERVICE_REVISION_IND_V02, QMI_IDL_TYPE16(0, 29), 532},
  {QMI_LOC_GET_FIX_CRITERIA_IND_V02, QMI_IDL_TYPE16(0, 31), 99},
  {QMI_LOC_NI_USER_RESPONSE_IND_V02, QMI_IDL_TYPE16(0, 33), 7},
  {QMI_LOC_INJECT_PREDICTED_ORBITS_DATA_IND_V02, QMI_IDL_TYPE16(0, 35), 12},
  {QMI_LOC_GET_PREDICTED_ORBITS_DATA_SOURCE_IND_V02, QMI_IDL_TYPE16(0, 37), 790},
  {QMI_LOC_GET_PREDICTED_ORBITS_DATA_VALIDITY_IND_V02, QMI_IDL_TYPE16(0, 39), 20},
  {QMI_LOC_INJECT_UTC_TIME_IND_V02, QMI_IDL_TYPE16(0, 41), 7},
  {QMI_LOC_INJECT_POSITION_IND_V02, QMI_IDL_TYPE16(0, 43), 7},
  {QMI_LOC_SET_ENGINE_LOCK_IND_V02, QMI_IDL_TYPE16(0, 45), 7},
  {QMI_LOC_GET_ENGINE_LOCK_IND_V02, QMI_IDL_TYPE16(0, 47), 14},
  {QMI_LOC_SET_SBAS_CONFIG_IND_V02, QMI_IDL_TYPE16(0, 49), 7},
  {QMI_LOC_GET_SBAS_CONFIG_IND_V02, QMI_IDL_TYPE16(0, 51), 11},
  {QMI_LOC_SET_NMEA_TYPES_IND_V02, QMI_IDL_TYPE16(0, 53), 7},
  {QMI_LOC_GET_NMEA_TYPES_IND_V02, QMI_IDL_TYPE16(0, 55), 14},
  {QMI_LOC_SET_LOW_POWER_MODE_IND_V02, QMI_IDL_TYPE16(0, 57), 7},
  {QMI_LOC_GET_LOW_POWER_MODE_IND_V02, QMI_IDL_TYPE16(0, 59), 11},
  {QMI_LOC_SET_SERVER_IND_V02, QMI_IDL_TYPE16(0, 61), 7},
  {QMI_LOC_GET_SERVER_IND_V02, QMI_IDL_TYPE16(0, 63), 304},
  {QMI_LOC_DELETE_ASSIST_DATA_IND_V02, QMI_IDL_TYPE16(0, 65), 7},
  {QMI_LOC_SET_XTRA_T_SESSION_CONTROL_IND_V02, QMI_IDL_TYPE16(0, 67), 7},
  {QMI_LOC_GET_XTRA_T_SESSION_CONTROL_IND_V02, QMI_IDL_TYPE16(0, 69), 11},
  {QMI_LOC_INJECT_WIFI_POSITION_IND_V02, QMI_IDL_TYPE16(0, 71), 7},
  {QMI_LOC_NOTIFY_WIFI_STATUS_IND_V02, QMI_IDL_TYPE16(0, 73), 7},
  {QMI_LOC_GET_REGISTERED_EVENTS_IND_V02, QMI_IDL_TYPE16(0, 75), 18},
  {QMI_LOC_SET_OPERATION_MODE_IND_V02, QMI_IDL_TYPE16(0, 77), 7},
  {QMI_LOC_GET_OPERATION_MODE_IND_V02, QMI_IDL_TYPE16(0, 79), 14},
  {QMI_LOC_SET_SPI_STATUS_IND_V02, QMI_IDL_TYPE16(0, 81), 7},
  {QMI_LOC_INJECT_SENSOR_DATA_IND_V02, QMI_IDL_TYPE16(0, 83), 34},
  {QMI_LOC_INJECT_TIME_SYNC_DATA_IND_V02, QMI_IDL_TYPE16(0, 85), 7},
  {QMI_LOC_SET_CRADLE_MOUNT_CONFIG_IND_V02, QMI_IDL_TYPE16(0, 89), 7},
  {QMI_LOC_GET_CRADLE_MOUNT_CONFIG_IND_V02, QMI_IDL_TYPE16(0, 87), 18},
  {QMI_LOC_SET_EXTERNAL_POWER_CONFIG_IND_V02, QMI_IDL_TYPE16(0, 93), 7},
  {QMI_LOC_GET_EXTERNAL_POWER_CONFIG_IND_V02, QMI_IDL_TYPE16(0, 91), 14},
  {QMI_LOC_INFORM_LOCATION_SERVER_CONN_STATUS_IND_V02, QMI_IDL_TYPE16(0, 95), 7},
  {QMI_LOC_SET_PROTOCOL_CONFIG_PARAMETERS_IND_V02, QMI_IDL_TYPE16(0, 97), 18},
  {QMI_LOC_GET_PROTOCOL_CONFIG_PARAMETERS_IND_V02, QMI_IDL_TYPE16(0, 99), 64},
  {QMI_LOC_SET_SENSOR_CONTROL_CONFIG_IND_V02, QMI_IDL_TYPE16(0, 101), 7},
  {QMI_LOC_GET_SENSOR_CONTROL_CONFIG_IND_V02, QMI_IDL_TYPE16(0, 103), 21},
  {QMI_LOC_SET_SENSOR_PROPERTIES_IND_V02, QMI_IDL_TYPE16(0, 105), 14},
  {QMI_LOC_GET_SENSOR_PROPERTIES_IND_V02, QMI_IDL_TYPE16(0, 107), 95},
  {QMI_LOC_SET_SENSOR_PERFORMANCE_CONTROL_CONFIGURATION_IND_V02, QMI_IDL_TYPE16(0, 109), 14},
  {QMI_LOC_GET_SENSOR_PERFORMANCE_CONTROL_CONFIGURATION_IND_V02, QMI_IDL_TYPE16(0, 111), 49},
  {QMI_LOC_INJECT_SUPL_CERTIFICATE_IND_V02, QMI_IDL_TYPE16(0, 113), 7},
  {QMI_LOC_DELETE_SUPL_CERTIFICATE_IND_V02, QMI_IDL_TYPE16(0, 115), 7},
  {QMI_LOC_SET_POSITION_ENGINE_CONFIG_PARAMETERS_IND_V02, QMI_IDL_TYPE16(0, 117), 14},
  {QMI_LOC_GET_POSITION_ENGINE_CONFIG_PARAMETERS_IND_V02, QMI_IDL_TYPE16(0, 119), 23},
  {QMI_LOC_EVENT_NI_GEOFENCE_NOTIFICATION_IND_V02, QMI_IDL_TYPE16(0, 19), 14},
  {QMI_LOC_EVENT_GEOFENCE_GEN_ALERT_IND_V02, QMI_IDL_TYPE16(0, 20), 7},
  {QMI_LOC_EVENT_GEOFENCE_BREACH_NOTIFICATION_IND_V02, QMI_IDL_TYPE16(0, 21), 85},
  {QMI_LOC_ADD_CIRCULAR_GEOFENCE_IND_V02, QMI_IDL_TYPE16(0, 121), 21},
  {QMI_LOC_DELETE_GEOFENCE_IND_V02, QMI_IDL_TYPE16(0, 123), 21},
  {QMI_LOC_QUERY_GEOFENCE_IND_V02, QMI_IDL_TYPE16(0, 125), 65},
  {QMI_LOC_EDIT_GEOFENCE_IND_V02, QMI_IDL_TYPE16(0, 131), 28},
  {QMI_LOC_GET_BEST_AVAILABLE_POSITION_IND_V02, QMI_IDL_TYPE16(0, 133), 391},
  {QMI_LOC_INJECT_MOTION_DATA_IND_V02, QMI_IDL_TYPE16(0, 135), 7},
  {QMI_LOC_GET_NI_GEOFENCE_ID_LIST_IND_V02, QMI_IDL_TYPE16(0, 137), 82},
  {QMI_LOC_INJECT_GSM_CELL_INFO_IND_V02, QMI_IDL_TYPE16(0, 139), 7},
  {QMI_LOC_INJECT_NETWORK_INITIATED_MESSAGE_IND_V02, QMI_IDL_TYPE16(0, 147), 7},
  {QMI_LOC_WWAN_OUT_OF_SERVICE_NOTIFICATION_IND_V02, QMI_IDL_TYPE16(0, 149), 7},
  {QMI_LOC_EVENT_PEDOMETER_CONTROL_IND_V02, QMI_IDL_TYPE16(0, 22), 15},
  {QMI_LOC_EVENT_MOTION_DATA_CONTROL_IND_V02, QMI_IDL_TYPE16(0, 23), 4},
  {QMI_LOC_PEDOMETER_REPORT_IND_V02, QMI_IDL_TYPE16(0, 151), 7},
  {QMI_LOC_INJECT_WCDMA_CELL_INFO_IND_V02, QMI_IDL_TYPE16(0, 141), 7},
  {QMI_LOC_INJECT_TDSCDMA_CELL_INFO_IND_V02, QMI_IDL_TYPE16(0, 143), 7},
  {QMI_LOC_INJECT_SUBSCRIBER_ID_IND_V02, QMI_IDL_TYPE16(0, 145), 7},
  {QMI_LOC_SET_GEOFENCE_ENGINE_CONFIG_IND_V02, QMI_IDL_TYPE16(0, 127), 14},
  {QMI_LOC_GET_GEOFENCE_ENGINE_CONFIG_IND_V02, QMI_IDL_TYPE16(0, 129), 39},
  {QMI_LOC_GET_BATCH_SIZE_IND_V02, QMI_IDL_TYPE16(0, 153), 21},
  {QMI_LOC_START_BATCHING_IND_V02, QMI_IDL_TYPE16(0, 155), 14},
  {QMI_LOC_EVENT_BATCH_FULL_NOTIFICATION_IND_V02, QMI_IDL_TYPE16(0, 156), 7},
  {QMI_LOC_EVENT_LIVE_BATCHED_POSITION_REPORT_IND_V02, QMI_IDL_TYPE16(0, 157), 90},
  {QMI_LOC_READ_FROM_BATCH_IND_V02, QMI_IDL_TYPE16(0, 159), 460},
  {QMI_LOC_STOP_BATCHING_IND_V02, QMI_IDL_TYPE16(0, 161), 21},
  {QMI_LOC_RELEASE_BATCH_IND_V02, QMI_IDL_TYPE16(0, 163), 14},
  {QMI_LOC_EVENT_INJECT_WIFI_AP_DATA_REQ_IND_V02, QMI_IDL_TYPE16(0, 164), 0},
  {QMI_LOC_INJECT_WIFI_AP_DATA_IND_V02, QMI_IDL_TYPE16(0, 166), 7},
  {QMI_LOC_NOTIFY_WIFI_ATTACHMENT_STATUS_IND_V02, QMI_IDL_TYPE16(0, 168), 7},
  {QMI_LOC_NOTIFY_WIFI_ENABLED_STATUS_IND_V02, QMI_IDL_TYPE16(0, 170), 7},
  {QMI_LOC_EVENT_GEOFENCE_BATCHED_BREACH_NOTIFICATION_IND_V02, QMI_IDL_TYPE16(0, 24), 1254},
  {QMI_LOC_EVENT_VEHICLE_DATA_READY_STATUS_IND_V02, QMI_IDL_TYPE16(0, 171), 12},
  {QMI_LOC_INJECT_VEHICLE_SENSOR_DATA_IND_V02, QMI_IDL_TYPE16(0, 173), 7},
  {QMI_LOC_GET_AVAILABLE_WWAN_POSITION_IND_V02, QMI_IDL_TYPE16(0, 175), 145},
  {QMI_LOC_SET_PREMIUM_SERVICES_CONFIG_IND_V02, QMI_IDL_TYPE16(0, 177), 7},
  {QMI_LOC_SET_XTRA_VERSION_CHECK_IND_V02, QMI_IDL_TYPE16(0, 179), 7},
  {QMI_LOC_EVENT_GNSS_MEASUREMENT_REPORT_IND_V02, QMI_IDL_TYPE16(0, 182), 1610},
  {QMI_LOC_EVENT_SV_POLYNOMIAL_REPORT_IND_V02, QMI_IDL_TYPE16(0, 183), 325},
  {QMI_LOC_SET_GNSS_CONSTELL_REPORT_CONFIG_IND_V02, QMI_IDL_TYPE16(0, 181), 7},
  {QMI_LOC_ADD_GEOFENCE_CONTEXT_IND_V02, QMI_IDL_TYPE16(0, 185), 28},
  {QMI_LOC_SET_GEOFENCE_ENGINE_CONTEXT_IND_V02, QMI_IDL_TYPE16(0, 187), 14},
  {QMI_LOC_DELETE_GEOFENCE_CONTEXT_IND_V02, QMI_IDL_TYPE16(0, 189), 28},
  {QMI_LOC_EVENT_GEOFENCE_PROXIMITY_NOTIFICATION_IND_V02, QMI_IDL_TYPE16(0, 25), 21},
  {QMI_LOC_INJECT_GTP_CLIENT_DOWNLOADED_DATA_IND_V02, QMI_IDL_TYPE16(0, 191), 7},
  {QMI_LOC_GDT_UPLOAD_BEGIN_STATUS_IND_V02, QMI_IDL_TYPE16(0, 193), 7},
  {QMI_LOC_GDT_UPLOAD_END_IND_V02, QMI_IDL_TYPE16(0, 195), 7},
  {QMI_LOC_EVENT_GDT_UPLOAD_BEGIN_STATUS_REQ_IND_V02, QMI_IDL_TYPE16(0, 26), 273},
  {QMI_LOC_EVENT_GDT_UPLOAD_END_REQ_IND_V02, QMI_IDL_TYPE16(0, 27), 21},
  {QMI_LOC_START_DBT_IND_V02, QMI_IDL_TYPE16(0, 197), 11},
  {QMI_LOC_EVENT_DBT_POSITION_REPORT_IND_V02, QMI_IDL_TYPE16(0, 200), 283},
  {QMI_LOC_EVENT_DBT_SESSION_STATUS_IND_V02, QMI_IDL_TYPE16(0, 201), 11},
  {QMI_LOC_STOP_DBT_IND_V02, QMI_IDL_TYPE16(0, 199), 11},
  {QMI_LOC_SECURE_GET_AVAILABLE_POSITION_IND_V02, QMI_IDL_TYPE16(0, 203), 1043},
  {QMI_LOC_EVENT_GEOFENCE_BATCHED_DWELL_NOTIFICATION_IND_V02, QMI_IDL_TYPE16(0, 204), 1247},
  {QMI_LOC_EVENT_GET_TIME_ZONE_INFO_IND_V02, QMI_IDL_TYPE16(0, 205), 7},
  {QMI_LOC_INJECT_TIME_ZONE_INFO_IND_V02, QMI_IDL_TYPE16(0, 207), 7},
  {QMI_LOC_INJECT_APCACHE_DATA_IND_V02, QMI_IDL_TYPE16(0, 209), 7},
  {QMI_LOC_INJECT_APDONOTCACHE_DATA_IND_V02, QMI_IDL_TYPE16(0, 211), 7},
  {QMI_LOC_EVENT_BATCHING_STATUS_IND_V02, QMI_IDL_TYPE16(0, 212), 7},
  {QMI_LOC_QUERY_AON_CONFIG_IND_V02, QMI_IDL_TYPE16(0, 214), 21}
};

/*Service Object*/
struct qmi_idl_service_object loc_qmi_idl_service_object_v02 = {
  0x06,
  0x02,
  0x10,
  8204,
  { sizeof(loc_service_command_messages_v02)/sizeof(qmi_idl_service_message_table_entry),
    sizeof(loc_service_response_messages_v02)/sizeof(qmi_idl_service_message_table_entry),
    sizeof(loc_service_indication_messages_v02)/sizeof(qmi_idl_service_message_table_entry) },
  { loc_service_command_messages_v02, loc_service_response_messages_v02, loc_service_indication_messages_v02},
  &loc_qmi_idl_type_table_object_v02,
  0x2C,
  NULL
};

/* Service Object Accessor */
qmi_idl_service_object_type loc_get_service_object_internal_v02
 ( int32_t idl_maj_version, int32_t idl_min_version, int32_t library_version ){
  if ( LOC_V02_IDL_MAJOR_VERS != idl_maj_version || LOC_V02_IDL_MINOR_VERS != idl_min_version
       || LOC_V02_IDL_TOOL_VERS != library_version)
  {
    return NULL;
  }
  return (qmi_idl_service_object_type)&loc_qmi_idl_service_object_v02;
}

