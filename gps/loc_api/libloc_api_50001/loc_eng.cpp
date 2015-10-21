/* Copyright (c) 2009-2015, The Linux Foundation. All rights reserved.
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
 *
 */

#define LOG_NDDEBUG 0
#define LOG_TAG "LocSvc_eng"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>
#include <ctype.h>
#include <math.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <netinet/in.h>         /* struct sockaddr_in */
#include <sys/socket.h>
#include <sys/time.h>
#include <netdb.h>
#include <time.h>
#include <new>
#include <LocEngAdapter.h>

#include <cutils/sched_policy.h>
#ifndef USE_GLIB
#include <utils/SystemClock.h>
#include <utils/Log.h>
#endif /* USE_GLIB */

#ifdef USE_GLIB
#include <glib.h>
#include <sys/syscall.h>
#endif /* USE_GLIB */

#include <string.h>

#include <loc_eng.h>
#include <loc_eng_ni.h>
#include <loc_eng_dmn_conn.h>
#include <loc_eng_dmn_conn_handler.h>
#include <loc_eng_msg.h>
#include <loc_eng_nmea.h>
#include <msg_q.h>
#include <loc.h>
#include "log_util.h"
#include "platform_lib_includes.h"
#include "loc_core_log.h"
#include "loc_eng_log.h"

#define SUCCESS TRUE
#define FAILURE FALSE

#ifndef GPS_CONF_FILE
#define GPS_CONF_FILE            "/etc/gps.conf"   //??? platform independent
#endif

#ifndef SAP_CONF_FILE
#define SAP_CONF_FILE            "/etc/sap.conf"
#endif

#define XTRA1_GPSONEXTRA         "xtra1.gpsonextra.net"

using namespace loc_core;

boolean configAlreadyRead = false;
unsigned int agpsStatus = 0;
loc_gps_cfg_s_type gps_conf;
loc_sap_cfg_s_type sap_conf;

/* Parameter spec table */
static const loc_param_s_type gps_conf_table[] =
{
  {"GPS_LOCK",                       &gps_conf.GPS_LOCK,                       NULL, 'n'},
  {"SUPL_VER",                       &gps_conf.SUPL_VER,                       NULL, 'n'},
  {"LPP_PROFILE",                    &gps_conf.LPP_PROFILE,                    NULL, 'n'},
  {"A_GLONASS_POS_PROTOCOL_SELECT",  &gps_conf.A_GLONASS_POS_PROTOCOL_SELECT,  NULL, 'n'},
  {"AGPS_CERT_WRITABLE_MASK",        &gps_conf.AGPS_CERT_WRITABLE_MASK,        NULL, 'n'},
  {"SUPL_MODE",                      &gps_conf.SUPL_MODE,                      NULL, 'n'},
  {"INTERMEDIATE_POS",               &gps_conf.INTERMEDIATE_POS,               NULL, 'n'},
  {"ACCURACY_THRES",                 &gps_conf.ACCURACY_THRES,                 NULL, 'n'},
  {"NMEA_PROVIDER",                  &gps_conf.NMEA_PROVIDER,                  NULL, 'n'},
  {"CAPABILITIES",                   &gps_conf.CAPABILITIES,                   NULL, 'n'},
  {"XTRA_VERSION_CHECK",             &gps_conf.XTRA_VERSION_CHECK,             NULL, 'n'},
  {"XTRA_SERVER_1",                  &gps_conf.XTRA_SERVER_1,                  NULL, 's'},
  {"XTRA_SERVER_2",                  &gps_conf.XTRA_SERVER_2,                  NULL, 's'},
  {"XTRA_SERVER_3",                  &gps_conf.XTRA_SERVER_3,                  NULL, 's'},
  {"USE_EMERGENCY_PDN_FOR_EMERGENCY_SUPL",  &gps_conf.USE_EMERGENCY_PDN_FOR_EMERGENCY_SUPL,          NULL, 'n'},
};

static const loc_param_s_type sap_conf_table[] =
{
  {"GYRO_BIAS_RANDOM_WALK",          &sap_conf.GYRO_BIAS_RANDOM_WALK,          &sap_conf.GYRO_BIAS_RANDOM_WALK_VALID, 'f'},
  {"ACCEL_RANDOM_WALK_SPECTRAL_DENSITY",     &sap_conf.ACCEL_RANDOM_WALK_SPECTRAL_DENSITY,    &sap_conf.ACCEL_RANDOM_WALK_SPECTRAL_DENSITY_VALID, 'f'},
  {"ANGLE_RANDOM_WALK_SPECTRAL_DENSITY",     &sap_conf.ANGLE_RANDOM_WALK_SPECTRAL_DENSITY,    &sap_conf.ANGLE_RANDOM_WALK_SPECTRAL_DENSITY_VALID, 'f'},
  {"RATE_RANDOM_WALK_SPECTRAL_DENSITY",      &sap_conf.RATE_RANDOM_WALK_SPECTRAL_DENSITY,     &sap_conf.RATE_RANDOM_WALK_SPECTRAL_DENSITY_VALID, 'f'},
  {"VELOCITY_RANDOM_WALK_SPECTRAL_DENSITY",  &sap_conf.VELOCITY_RANDOM_WALK_SPECTRAL_DENSITY, &sap_conf.VELOCITY_RANDOM_WALK_SPECTRAL_DENSITY_VALID, 'f'},
  {"SENSOR_ACCEL_BATCHES_PER_SEC",   &sap_conf.SENSOR_ACCEL_BATCHES_PER_SEC,   NULL, 'n'},
  {"SENSOR_ACCEL_SAMPLES_PER_BATCH", &sap_conf.SENSOR_ACCEL_SAMPLES_PER_BATCH, NULL, 'n'},
  {"SENSOR_GYRO_BATCHES_PER_SEC",    &sap_conf.SENSOR_GYRO_BATCHES_PER_SEC,    NULL, 'n'},
  {"SENSOR_GYRO_SAMPLES_PER_BATCH",  &sap_conf.SENSOR_GYRO_SAMPLES_PER_BATCH,  NULL, 'n'},
  {"SENSOR_ACCEL_BATCHES_PER_SEC_HIGH",   &sap_conf.SENSOR_ACCEL_BATCHES_PER_SEC_HIGH,   NULL, 'n'},
  {"SENSOR_ACCEL_SAMPLES_PER_BATCH_HIGH", &sap_conf.SENSOR_ACCEL_SAMPLES_PER_BATCH_HIGH, NULL, 'n'},
  {"SENSOR_GYRO_BATCHES_PER_SEC_HIGH",    &sap_conf.SENSOR_GYRO_BATCHES_PER_SEC_HIGH,    NULL, 'n'},
  {"SENSOR_GYRO_SAMPLES_PER_BATCH_HIGH",  &sap_conf.SENSOR_GYRO_SAMPLES_PER_BATCH_HIGH,  NULL, 'n'},
  {"SENSOR_CONTROL_MODE",            &sap_conf.SENSOR_CONTROL_MODE,            NULL, 'n'},
  {"SENSOR_USAGE",                   &sap_conf.SENSOR_USAGE,                   NULL, 'n'},
  {"SENSOR_ALGORITHM_CONFIG_MASK",   &sap_conf.SENSOR_ALGORITHM_CONFIG_MASK,   NULL, 'n'},
  {"SENSOR_PROVIDER",                &sap_conf.SENSOR_PROVIDER,                NULL, 'n'}
};

static void loc_default_parameters(void)
{
   /*Defaults for gps.conf*/
   gps_conf.INTERMEDIATE_POS = 0;
   gps_conf.ACCURACY_THRES = 0;
   gps_conf.NMEA_PROVIDER = 0;
   gps_conf.GPS_LOCK = 0;
   gps_conf.SUPL_VER = 0x10000;
   gps_conf.SUPL_MODE = 0x3;
   gps_conf.CAPABILITIES = 0x7;
   /* LTE Positioning Profile configuration is disable by default*/
   gps_conf.LPP_PROFILE = 0;
   /*By default no positioning protocol is selected on A-GLONASS system*/
   gps_conf.A_GLONASS_POS_PROTOCOL_SELECT = 0;
   /*XTRA version check is disabled by default*/
   gps_conf.XTRA_VERSION_CHECK=0;
   /*Use emergency PDN by default*/
   gps_conf.USE_EMERGENCY_PDN_FOR_EMERGENCY_SUPL = 1;

   /*Defaults for sap.conf*/
   sap_conf.GYRO_BIAS_RANDOM_WALK = 0;
   sap_conf.SENSOR_ACCEL_BATCHES_PER_SEC = 2;
   sap_conf.SENSOR_ACCEL_SAMPLES_PER_BATCH = 5;
   sap_conf.SENSOR_GYRO_BATCHES_PER_SEC = 2;
   sap_conf.SENSOR_GYRO_SAMPLES_PER_BATCH = 5;
   sap_conf.SENSOR_ACCEL_BATCHES_PER_SEC_HIGH = 4;
   sap_conf.SENSOR_ACCEL_SAMPLES_PER_BATCH_HIGH = 25;
   sap_conf.SENSOR_GYRO_BATCHES_PER_SEC_HIGH = 4;
   sap_conf.SENSOR_GYRO_SAMPLES_PER_BATCH_HIGH = 25;
   sap_conf.SENSOR_CONTROL_MODE = 0; /* AUTO */
   sap_conf.SENSOR_USAGE = 0; /* Enabled */
   sap_conf.SENSOR_ALGORITHM_CONFIG_MASK = 0; /* INS Disabled = FALSE*/
   /* Values MUST be set by OEMs in configuration for sensor-assisted
      navigation to work. There are NO default values */
   sap_conf.ACCEL_RANDOM_WALK_SPECTRAL_DENSITY = 0;
   sap_conf.ANGLE_RANDOM_WALK_SPECTRAL_DENSITY = 0;
   sap_conf.RATE_RANDOM_WALK_SPECTRAL_DENSITY = 0;
   sap_conf.VELOCITY_RANDOM_WALK_SPECTRAL_DENSITY = 0;
   sap_conf.GYRO_BIAS_RANDOM_WALK_VALID = 0;
   sap_conf.ACCEL_RANDOM_WALK_SPECTRAL_DENSITY_VALID = 0;
   sap_conf.ANGLE_RANDOM_WALK_SPECTRAL_DENSITY_VALID = 0;
   sap_conf.RATE_RANDOM_WALK_SPECTRAL_DENSITY_VALID = 0;
   sap_conf.VELOCITY_RANDOM_WALK_SPECTRAL_DENSITY_VALID = 0;
   /* default provider is SSC */
   sap_conf.SENSOR_PROVIDER = 1;

   /* None of the 10 slots for agps certificates are writable by default */
   gps_conf.AGPS_CERT_WRITABLE_MASK = 0;
}

// 2nd half of init(), singled out for
// modem restart to use.
static int loc_eng_reinit(loc_eng_data_s_type &loc_eng_data);
static void loc_eng_agps_reinit(loc_eng_data_s_type &loc_eng_data);

static int loc_eng_set_server(loc_eng_data_s_type &loc_eng_data,
                              LocServerType type, const char *hostname, int port);
// Internal functions
static void loc_inform_gps_status(loc_eng_data_s_type &loc_eng_data,
                                  GpsStatusValue status);
static void loc_eng_report_status(loc_eng_data_s_type &loc_eng_data,
                                  GpsStatusValue status);
static void loc_eng_process_conn_request(loc_eng_data_s_type &loc_eng_data,
                                         int connHandle, AGpsType agps_type);
static void loc_eng_agps_close_status(loc_eng_data_s_type &loc_eng_data, int is_succ);
static void loc_eng_handle_engine_down(loc_eng_data_s_type &loc_eng_data) ;
static void loc_eng_handle_engine_up(loc_eng_data_s_type &loc_eng_data) ;

static int loc_eng_start_handler(loc_eng_data_s_type &loc_eng_data);
static int loc_eng_stop_handler(loc_eng_data_s_type &loc_eng_data);
static int loc_eng_get_zpp_handler(loc_eng_data_s_type &loc_eng_data);
static void deleteAidingData(loc_eng_data_s_type &logEng);
static AgpsStateMachine*
getAgpsStateMachine(loc_eng_data_s_type& logEng, AGpsExtType agpsType);
static int dataCallCb(void *cb_data);
static void update_aiding_data_for_deletion(loc_eng_data_s_type& loc_eng_data) {
    if (loc_eng_data.engine_status != GPS_STATUS_ENGINE_ON &&
        loc_eng_data.aiding_data_for_deletion != 0)
    {
        loc_eng_data.adapter->deleteAidingData(loc_eng_data.aiding_data_for_deletion);
        loc_eng_data.aiding_data_for_deletion = 0;
    }
}

static void* noProc(void* data)
{
    return NULL;
}

/*********************************************************************
 * definitions of the static messages used in the file
 *********************************************************************/
//        case LOC_ENG_MSG_REQUEST_NI:
LocEngRequestNi::LocEngRequestNi(void* locEng,
                                 GpsNiNotification &notif,
                                 const void* data) :
    LocMsg(), mLocEng(locEng), mNotify(notif), mPayload(data) {
    locallog();
}
void LocEngRequestNi::proc() const {
    loc_eng_ni_request_handler(*((loc_eng_data_s_type*)mLocEng),
                               &mNotify, mPayload);
}
void LocEngRequestNi::locallog() const
{
    LOC_LOGV("id: %d\n  type: %s\n  flags: %d\n  time out: %d\n  "
             "default response: %s\n  requestor id encoding: %s\n"
             "  text encoding: %s\n  passThroughData: %p",
             mNotify.notification_id,
             loc_get_ni_type_name(mNotify.ni_type),
             mNotify.notify_flags,
             mNotify.timeout,
             loc_get_ni_response_name(mNotify.default_response),
             loc_get_ni_encoding_name(mNotify.requestor_id_encoding),
             loc_get_ni_encoding_name(mNotify.text_encoding),
             mPayload);
}
inline void LocEngRequestNi::log() const {
    locallog();
}

//        case LOC_ENG_MSG_INFORM_NI_RESPONSE:
// in loc_eng_ni.cpp

//        case LOC_ENG_MSG_START_FIX:
LocEngStartFix::LocEngStartFix(LocEngAdapter* adapter) :
    LocMsg(), mAdapter(adapter)
{
    locallog();
}
inline void LocEngStartFix::proc() const
{
    loc_eng_data_s_type* locEng = (loc_eng_data_s_type*)mAdapter->getOwner();
    loc_eng_start_handler(*locEng);
}
inline void LocEngStartFix::locallog() const
{
    LOC_LOGV("LocEngStartFix");
}
inline void LocEngStartFix::log() const
{
    locallog();
}
void LocEngStartFix::send() const {
    mAdapter->sendMsg(this);
}

//        case LOC_ENG_MSG_STOP_FIX:
LocEngStopFix::LocEngStopFix(LocEngAdapter* adapter) :
    LocMsg(), mAdapter(adapter)
{
    locallog();
}
inline void LocEngStopFix::proc() const
{
    loc_eng_data_s_type* locEng = (loc_eng_data_s_type*)mAdapter->getOwner();
    loc_eng_stop_handler(*locEng);
}
inline void LocEngStopFix::locallog() const
{
    LOC_LOGV("LocEngStopFix");
}
inline void LocEngStopFix::log() const
{
    locallog();
}
void LocEngStopFix::send() const {
    mAdapter->sendMsg(this);
}

//        case LOC_ENG_MSG_SET_POSITION_MODE:
LocEngPositionMode::LocEngPositionMode(LocEngAdapter* adapter,
                                       LocPosMode &mode) :
    LocMsg(), mAdapter(adapter), mPosMode(mode)
{
    mPosMode.logv();
}
inline void LocEngPositionMode::proc() const {
    mAdapter->setPositionMode(&mPosMode);
}
inline void LocEngPositionMode::log() const {
    mPosMode.logv();
}
void LocEngPositionMode::send() const {
    mAdapter->sendMsg(this);
}

LocEngGetZpp::LocEngGetZpp(LocEngAdapter* adapter) :
    LocMsg(), mAdapter(adapter)
{
    locallog();
}
inline void LocEngGetZpp::proc() const
{
    loc_eng_data_s_type* locEng = (loc_eng_data_s_type*)mAdapter->getOwner();
    loc_eng_get_zpp_handler(*locEng);
}
inline void LocEngGetZpp::locallog() const
{
    LOC_LOGV("LocEngGetZpp");
}
inline void LocEngGetZpp::log() const
{
    locallog();
}
void LocEngGetZpp::send() const {
    mAdapter->sendMsg(this);
}

struct LocEngSetTime : public LocMsg {
    LocEngAdapter* mAdapter;
    const GpsUtcTime mTime;
    const int64_t mTimeReference;
    const int mUncertainty;
    inline LocEngSetTime(LocEngAdapter* adapter,
                         GpsUtcTime t, int64_t tf, int unc) :
        LocMsg(), mAdapter(adapter),
        mTime(t), mTimeReference(tf), mUncertainty(unc)
    {
        locallog();
    }
    inline virtual void proc() const {
        mAdapter->setTime(mTime, mTimeReference, mUncertainty);
    }
    inline void locallog() const {
        LOC_LOGV("time: %lld\n  timeReference: %lld\n  uncertainty: %d",
                 mTime, mTimeReference, mUncertainty);
    }
    inline virtual void log() const {
        locallog();
    }
};

 //       case LOC_ENG_MSG_INJECT_LOCATION:
struct LocEngInjectLocation : public LocMsg {
    LocEngAdapter* mAdapter;
    const double mLatitude;
    const double mLongitude;
    const float mAccuracy;
    inline LocEngInjectLocation(LocEngAdapter* adapter,
                                double lat, double lon, float accur) :
        LocMsg(), mAdapter(adapter),
        mLatitude(lat), mLongitude(lon), mAccuracy(accur)
    {
        locallog();
    }
    inline virtual void proc() const {
        mAdapter->injectPosition(mLatitude, mLongitude, mAccuracy);
    }
    inline void locallog() const {
        LOC_LOGV("latitude: %f\n  longitude: %f\n  accuracy: %f",
                 mLatitude, mLongitude, mAccuracy);
    }
    inline virtual void log() const {
        locallog();
    }
};

//        case LOC_ENG_MSG_SET_SERVER_IPV4:
struct LocEngSetServerIpv4 : public LocMsg {
    LocEngAdapter* mAdapter;
    const unsigned int mNlAddr;
    const int mPort;
    const LocServerType mServerType;
    inline LocEngSetServerIpv4(LocEngAdapter* adapter,
                               unsigned int ip,
                               int port,
                               LocServerType type) :
        LocMsg(), mAdapter(adapter),
        mNlAddr(ip), mPort(port), mServerType(type)
    {
        locallog();
    }
    inline virtual void proc() const {
        mAdapter->setServer(mNlAddr, mPort, mServerType);
    }
    inline void locallog() const {
        LOC_LOGV("LocEngSetServerIpv4 - addr: %x, port: %d, type: %s",
                 mNlAddr, mPort, loc_get_server_type_name(mServerType));
    }
    inline virtual void log() const {
        locallog();
    }
};

//        case LOC_ENG_MSG_SET_SERVER_URL:
struct LocEngSetServerUrl : public LocMsg {
    LocEngAdapter* mAdapter;
    const int mLen;
    char* mUrl;
    inline LocEngSetServerUrl(LocEngAdapter* adapter,
                              char* urlString,
                              int url_len) :
        LocMsg(), mAdapter(adapter),
        mLen(url_len), mUrl(new char[mLen+1])
    {
        memcpy((void*)mUrl, (void*)urlString, url_len);
        mUrl[mLen] = 0;
        locallog();
    }
    inline ~LocEngSetServerUrl()
    {
        delete[] mUrl;
    }
    inline virtual void proc() const {
        mAdapter->setServer(mUrl, mLen);
    }
    inline void locallog() const {
        LOC_LOGV("LocEngSetServerUrl - url: %s", mUrl);
    }
    inline virtual void log() const {
        locallog();
    }
};

//        case LOC_ENG_MSG_A_GLONASS_PROTOCOL:
struct LocEngAGlonassProtocol : public LocMsg {
    LocEngAdapter* mAdapter;
    const unsigned long mAGlonassProtocl;
    inline LocEngAGlonassProtocol(LocEngAdapter* adapter,
                                  unsigned long protocol) :
        LocMsg(), mAdapter(adapter), mAGlonassProtocl(protocol)
    {
        locallog();
    }
    inline virtual void proc() const {
        mAdapter->setAGLONASSProtocol(mAGlonassProtocl);
    }
    inline  void locallog() const {
        LOC_LOGV("A-GLONASS protocol: 0x%lx", mAGlonassProtocl);
    }
    inline virtual void log() const {
        locallog();
    }
};

//        case LOC_ENG_MSG_SUPL_VERSION:
struct LocEngSuplVer : public LocMsg {
    LocEngAdapter* mAdapter;
    const int mSuplVer;
    inline LocEngSuplVer(LocEngAdapter* adapter,
                         int suplVer) :
        LocMsg(), mAdapter(adapter), mSuplVer(suplVer)
    {
        locallog();
    }
    inline virtual void proc() const {
        mAdapter->setSUPLVersion(mSuplVer);
    }
    inline  void locallog() const {
        LOC_LOGV("SUPL Version: %d", mSuplVer);
    }
    inline virtual void log() const {
        locallog();
    }
};

struct LocEngSuplMode : public LocMsg {
    UlpProxyBase* mUlp;

    inline LocEngSuplMode(UlpProxyBase* ulp) :
        LocMsg(), mUlp(ulp)
    {
        locallog();
    }
    inline virtual void proc() const {
        mUlp->setCapabilities(getCarrierCapabilities());
    }
    inline  void locallog() const {
    }
    inline virtual void log() const {
        locallog();
    }
};

//        case LOC_ENG_MSG_LPP_CONFIG:
struct LocEngLppConfig : public LocMsg {
    LocEngAdapter* mAdapter;
    const int mLppConfig;
    inline LocEngLppConfig(LocEngAdapter* adapter,
                           int lppConfig) :
        LocMsg(), mAdapter(adapter), mLppConfig(lppConfig)
    {
        locallog();
    }
    inline virtual void proc() const {
        mAdapter->setLPPConfig(mLppConfig);
    }
    inline void locallog() const {
        LOC_LOGV("LocEngLppConfig - profile: %d", mLppConfig);
    }
    inline virtual void log() const {
        locallog();
    }
};

//        case LOC_ENG_MSG_SET_SENSOR_CONTROL_CONFIG:
struct LocEngSensorControlConfig : public LocMsg {
    LocEngAdapter* mAdapter;
    const int mSensorsDisabled;
    const int mSensorProvider;
    inline LocEngSensorControlConfig(LocEngAdapter* adapter,
                                     int sensorsDisabled, int sensorProvider) :
        LocMsg(), mAdapter(adapter), mSensorsDisabled(sensorsDisabled),
        mSensorProvider(sensorProvider)
    {
        locallog();
    }
    inline virtual void proc() const {
        mAdapter->setSensorControlConfig(mSensorsDisabled, mSensorProvider);
    }
    inline  void locallog() const {
        LOC_LOGV("LocEngSensorControlConfig - Sensors Disabled: %d, Sensor Provider: %d",
                 mSensorsDisabled, mSensorProvider);
    }
    inline virtual void log() const {
        locallog();
    }
};

//        case LOC_ENG_MSG_SET_SENSOR_PROPERTIES:
struct LocEngSensorProperties : public LocMsg {
    LocEngAdapter* mAdapter;
    const bool mGyroBiasVarianceRandomWalkValid;
    const float mGyroBiasVarianceRandomWalk;
    const bool mAccelRandomWalkValid;
    const float mAccelRandomWalk;
    const bool mAngleRandomWalkValid;
    const float mAngleRandomWalk;
    const bool mRateRandomWalkValid;
    const float mRateRandomWalk;
    const bool mVelocityRandomWalkValid;
    const float mVelocityRandomWalk;
    inline LocEngSensorProperties(LocEngAdapter* adapter,
                                  bool gyroBiasRandomWalk_valid,
                                  float gyroBiasRandomWalk,
                                  bool accelRandomWalk_valid,
                                  float accelRandomWalk,
                                  bool angleRandomWalk_valid,
                                  float angleRandomWalk,
                                  bool rateRandomWalk_valid,
                                  float rateRandomWalk,
                                  bool velocityRandomWalk_valid,
                                  float velocityRandomWalk) :
        LocMsg(), mAdapter(adapter),
        mGyroBiasVarianceRandomWalkValid(gyroBiasRandomWalk_valid),
        mGyroBiasVarianceRandomWalk(gyroBiasRandomWalk),
        mAccelRandomWalkValid(accelRandomWalk_valid),
        mAccelRandomWalk(accelRandomWalk),
        mAngleRandomWalkValid(angleRandomWalk_valid),
        mAngleRandomWalk(angleRandomWalk),
        mRateRandomWalkValid(rateRandomWalk_valid),
        mRateRandomWalk(rateRandomWalk),
        mVelocityRandomWalkValid(velocityRandomWalk_valid),
        mVelocityRandomWalk(velocityRandomWalk)
    {
        locallog();
    }
    inline virtual void proc() const {
        mAdapter->setSensorProperties(mGyroBiasVarianceRandomWalkValid,
                                      mGyroBiasVarianceRandomWalk,
                                      mAccelRandomWalkValid,
                                      mAccelRandomWalk,
                                      mAngleRandomWalkValid,
                                      mAngleRandomWalk,
                                      mRateRandomWalkValid,
                                      mRateRandomWalk,
                                      mVelocityRandomWalkValid,
                                      mVelocityRandomWalk);
    }
    inline  void locallog() const {
        LOC_LOGV("Sensor properties validity, Gyro Random walk: %d "
                 "Accel Random Walk: %d "
                 "Angle Random Walk: %d Rate Random Walk: %d "
                 "Velocity Random Walk: %d\n"
                 "Sensor properties, Gyro Random walk: %f "
                 "Accel Random Walk: %f "
                 "Angle Random Walk: %f Rate Random Walk: %f "
                 "Velocity Random Walk: %f",
                 mGyroBiasVarianceRandomWalkValid,
                 mAccelRandomWalkValid,
                 mAngleRandomWalkValid,
                 mRateRandomWalkValid,
                 mVelocityRandomWalkValid,
                 mGyroBiasVarianceRandomWalk,
                 mAccelRandomWalk,
                 mAngleRandomWalk,
                 mRateRandomWalk,
                 mVelocityRandomWalk
            );
    }
    inline virtual void log() const {
        locallog();
    }
};

//        case LOC_ENG_MSG_SET_SENSOR_PERF_CONTROL_CONFIG:
struct LocEngSensorPerfControlConfig : public LocMsg {
    LocEngAdapter* mAdapter;
    const int mControlMode;
    const int mAccelSamplesPerBatch;
    const int mAccelBatchesPerSec;
    const int mGyroSamplesPerBatch;
    const int mGyroBatchesPerSec;
    const int mAccelSamplesPerBatchHigh;
    const int mAccelBatchesPerSecHigh;
    const int mGyroSamplesPerBatchHigh;
    const int mGyroBatchesPerSecHigh;
    const int mAlgorithmConfig;
    inline LocEngSensorPerfControlConfig(LocEngAdapter* adapter,
                                         int controlMode,
                                         int accelSamplesPerBatch,
                                         int accelBatchesPerSec,
                                         int gyroSamplesPerBatch,
                                         int gyroBatchesPerSec,
                                         int accelSamplesPerBatchHigh,
                                         int accelBatchesPerSecHigh,
                                         int gyroSamplesPerBatchHigh,
                                         int gyroBatchesPerSecHigh,
                                         int algorithmConfig) :
        LocMsg(), mAdapter(adapter),
        mControlMode(controlMode),
        mAccelSamplesPerBatch(accelSamplesPerBatch),
        mAccelBatchesPerSec(accelBatchesPerSec),
        mGyroSamplesPerBatch(gyroSamplesPerBatch),
        mGyroBatchesPerSec(gyroBatchesPerSec),
        mAccelSamplesPerBatchHigh(accelSamplesPerBatchHigh),
        mAccelBatchesPerSecHigh(accelBatchesPerSecHigh),
        mGyroSamplesPerBatchHigh(gyroSamplesPerBatchHigh),
        mGyroBatchesPerSecHigh(gyroBatchesPerSecHigh),
        mAlgorithmConfig(algorithmConfig)
    {
        locallog();
    }
    inline virtual void proc() const {
        mAdapter->setSensorPerfControlConfig(mControlMode,
                                             mAccelSamplesPerBatch,
                                             mAccelBatchesPerSec,
                                             mGyroSamplesPerBatch,
                                             mGyroBatchesPerSec,
                                             mAccelSamplesPerBatchHigh,
                                             mAccelBatchesPerSecHigh,
                                             mGyroSamplesPerBatchHigh,
                                             mGyroBatchesPerSecHigh,
                                             mAlgorithmConfig);
    }
    inline void locallog() const {
        LOC_LOGV("Sensor Perf Control Config (performanceControlMode)(%u) "
                 "accel(#smp,#batches) (%u,%u) "
                 "gyro(#smp,#batches) (%u,%u), "
                 "accel_high(#smp,#batches) (%u,%u) "
                 "gyro_high(#smp,#batches) (%u,%u), "
                 "algorithmConfig(%u)\n",
                 mControlMode,
                 mAccelSamplesPerBatch, mAccelBatchesPerSec,
                 mGyroSamplesPerBatch, mGyroBatchesPerSec,
                 mAccelSamplesPerBatchHigh, mAccelBatchesPerSecHigh,
                 mGyroSamplesPerBatchHigh, mGyroBatchesPerSecHigh,
                 mAlgorithmConfig);
    }
    inline virtual void log() const {
        locallog();
    }
};

//        case LOC_ENG_MSG_EXT_POWER_CONFIG:
struct LocEngExtPowerConfig : public LocMsg {
    LocEngAdapter* mAdapter;
    const int mIsBatteryCharging;
    inline LocEngExtPowerConfig(LocEngAdapter* adapter,
                                int isBatteryCharging) :
        LocMsg(), mAdapter(adapter),
        mIsBatteryCharging(isBatteryCharging)
    {
        locallog();
    }
    inline virtual void proc() const {
        mAdapter->setExtPowerConfig(mIsBatteryCharging);
    }
    inline void locallog() const {
        LOC_LOGV("LocEngExtPowerConfig - isBatteryCharging: %d",
                 mIsBatteryCharging);
    }
    inline virtual void log() const {
        locallog();
    }
};

//        case LOC_ENG_MSG_REPORT_POSITION:
LocEngReportPosition::LocEngReportPosition(LocAdapterBase* adapter,
                                           UlpLocation &loc,
                                           GpsLocationExtended &locExtended,
                                           void* locExt,
                                           enum loc_sess_status st,
                                           LocPosTechMask technology) :
    LocMsg(), mAdapter(adapter), mLocation(loc),
    mLocationExtended(locExtended),
    mLocationExt(((loc_eng_data_s_type*)
                  ((LocEngAdapter*)
                   (mAdapter))->getOwner())->location_ext_parser(locExt)),
    mStatus(st), mTechMask(technology)
{
    locallog();
}
void LocEngReportPosition::proc() const {
    LocEngAdapter* adapter = (LocEngAdapter*)mAdapter;
    loc_eng_data_s_type* locEng = (loc_eng_data_s_type*)adapter->getOwner();

    if (locEng->mute_session_state != LOC_MUTE_SESS_IN_SESSION) {
        bool reported = false;
        if (locEng->location_cb != NULL) {
            if (LOC_SESS_FAILURE == mStatus) {
                // in case we want to handle the failure case
                locEng->location_cb(NULL, NULL);
                reported = true;
            }
            // what's in the else if is... (line by line)
            // 1. this is a final fix; and
            //   1.1 it is a Satellite fix; or
            //   1.2 it is a sensor fix
            // 2. (must be intermediate fix... implicit)
            //   2.1 we accepte intermediate; and
            //   2.2 it is NOT the case that
            //   2.2.1 there is inaccuracy; and
            //   2.2.2 we care about inaccuracy; and
            //   2.2.3 the inaccuracy exceeds our tolerance
            else if ((LOC_SESS_SUCCESS == mStatus &&
                      ((LOC_POS_TECH_MASK_SATELLITE |
                        LOC_POS_TECH_MASK_SENSORS   |
                        LOC_POS_TECH_MASK_HYBRID) &
                       mTechMask)) ||
                     (LOC_SESS_INTERMEDIATE == locEng->intermediateFix &&
                      !((mLocation.gpsLocation.flags &
                         GPS_LOCATION_HAS_ACCURACY) &&
                        (gps_conf.ACCURACY_THRES != 0) &&
                        (mLocation.gpsLocation.accuracy >
                         gps_conf.ACCURACY_THRES)))) {
                locEng->location_cb((UlpLocation*)&(mLocation),
                                    (void*)mLocationExt);
                reported = true;
            }
        }

        // if we have reported this fix
        if (reported &&
            // and if this is a singleshot
            GPS_POSITION_RECURRENCE_SINGLE ==
            locEng->adapter->getPositionMode().recurrence) {
            if (LOC_SESS_INTERMEDIATE == mStatus) {
                // modem could be still working for a final fix,
                // although we no longer need it.  So stopFix().
                locEng->adapter->stopFix();
            }
            // turn off the session flag.
            locEng->adapter->setInSession(false);
        }

        LOC_LOGV("LocEngReportPosition::proc() - generateNmea: %d, position source: %d, "
                 "engine_status: %d, isInSession: %d",
                        locEng->generateNmea, mLocation.position_source,
                        locEng->engine_status, locEng->adapter->isInSession());

        if (locEng->generateNmea &&
            locEng->adapter->isInSession())
        {
            unsigned char generate_nmea = reported &&
                                          (mStatus != LOC_SESS_FAILURE);
            loc_eng_nmea_generate_pos(locEng, mLocation, mLocationExtended,
                                      generate_nmea);
        }

        // Free the allocated memory for rawData
        UlpLocation* gp = (UlpLocation*)&(mLocation);
        if (gp != NULL && gp->rawData != NULL)
        {
            delete (char*)gp->rawData;
            gp->rawData = NULL;
            gp->rawDataSize = 0;
        }
    }
}
void LocEngReportPosition::locallog() const {
    LOC_LOGV("LocEngReportPosition");
}
void LocEngReportPosition::log() const {
    locallog();
}
void LocEngReportPosition::send() const {
    mAdapter->sendMsg(this);
}


//        case LOC_ENG_MSG_REPORT_SV:
LocEngReportSv::LocEngReportSv(LocAdapterBase* adapter,
                               GnssSvStatus &sv,
                               GpsLocationExtended &locExtended,
                               void* svExt) :
    LocMsg(), mAdapter(adapter), mSvStatus(sv),
    mLocationExtended(locExtended),
    mSvExt(((loc_eng_data_s_type*)
            ((LocEngAdapter*)
             (mAdapter))->getOwner())->sv_ext_parser(svExt))
{
    locallog();
}
void LocEngReportSv::proc() const {
    LocEngAdapter* adapter = (LocEngAdapter*)mAdapter;
    loc_eng_data_s_type* locEng = (loc_eng_data_s_type*)adapter->getOwner();

    if (locEng->mute_session_state != LOC_MUTE_SESS_IN_SESSION)
    {
        if (locEng->sv_status_cb != NULL) {
            locEng->sv_status_cb((GpsSvStatus*)&(mSvStatus),
                                 (void*)mSvExt);
        }

        if (locEng->generateNmea)
        {
            loc_eng_nmea_generate_sv(locEng, mSvStatus, mLocationExtended);
        }
    }
}
void LocEngReportSv::locallog() const {
    LOC_LOGV("%s:%d] LocEngReportSv",__func__, __LINE__);
}
inline void LocEngReportSv::log() const {
    locallog();
}
void LocEngReportSv::send() const {
    mAdapter->sendMsg(this);
}

//        case LOC_ENG_MSG_REPORT_STATUS:
LocEngReportStatus::LocEngReportStatus(LocAdapterBase* adapter,
                                       GpsStatusValue engineStatus) :
    LocMsg(),  mAdapter(adapter), mStatus(engineStatus)
{
    locallog();
}
inline void LocEngReportStatus::proc() const
{
    LocEngAdapter* adapter = (LocEngAdapter*)mAdapter;
    loc_eng_data_s_type* locEng = (loc_eng_data_s_type*)adapter->getOwner();

    loc_eng_report_status(*locEng, mStatus);
    update_aiding_data_for_deletion(*locEng);
}
inline void LocEngReportStatus::locallog() const {
    LOC_LOGV("LocEngReportStatus");
}
inline void LocEngReportStatus::log() const {
    locallog();
}

//        case LOC_ENG_MSG_REPORT_NMEA:
LocEngReportNmea::LocEngReportNmea(void* locEng,
                                   const char* data, int len) :
    LocMsg(), mLocEng(locEng), mNmea(new char[len]), mLen(len)
{
    memcpy((void*)mNmea, (void*)data, len);
    locallog();
}
void LocEngReportNmea::proc() const {
    loc_eng_data_s_type* locEng = (loc_eng_data_s_type*) mLocEng;

    struct timeval tv;
    gettimeofday(&tv, (struct timezone *) NULL);
    int64_t now = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
    CALLBACK_LOG_CALLFLOW("nmea_cb", %d, mLen);

    if (locEng->nmea_cb != NULL)
        locEng->nmea_cb(now, mNmea, mLen);
}
inline void LocEngReportNmea::locallog() const {
    LOC_LOGV("LocEngReportNmea");
}
inline void LocEngReportNmea::log() const {
    locallog();
}

//        case LOC_ENG_MSG_REPORT_XTRA_SERVER:
LocEngReportXtraServer::LocEngReportXtraServer(void* locEng,
                                               const char *url1,
                                               const char *url2,
                                               const char *url3,
                                               const int maxlength) :
    LocMsg(), mLocEng(locEng), mMaxLen(maxlength),
    mServers(new char[3*(mMaxLen+1)])
{
    char * cptr = mServers;
    memset(mServers, 0, 3*(mMaxLen+1));

    // Override modem URLs with uncommented gps.conf urls
    if( gps_conf.XTRA_SERVER_1[0] != '\0' ) {
        url1 = &gps_conf.XTRA_SERVER_1[0];
    }
    if( gps_conf.XTRA_SERVER_2[0] != '\0' ) {
        url2 = &gps_conf.XTRA_SERVER_2[0];
    }
    if( gps_conf.XTRA_SERVER_3[0] != '\0' ) {
        url3 = &gps_conf.XTRA_SERVER_3[0];
    }
    // copy non xtra1.gpsonextra.net URLs into the forwarding buffer.
    if( NULL == strcasestr(url1, XTRA1_GPSONEXTRA) ) {
        strlcpy(cptr, url1, mMaxLen + 1);
        cptr += mMaxLen + 1;
    }
    if( NULL == strcasestr(url2, XTRA1_GPSONEXTRA) ) {
        strlcpy(cptr, url2, mMaxLen + 1);
        cptr += mMaxLen + 1;
    }
    if( NULL == strcasestr(url3, XTRA1_GPSONEXTRA) ) {
        strlcpy(cptr, url3, mMaxLen + 1);
    }
    locallog();
}

void LocEngReportXtraServer::proc() const {
    loc_eng_xtra_data_s_type* locEngXtra =
        &(((loc_eng_data_s_type*)mLocEng)->xtra_module_data);

    if (locEngXtra->report_xtra_server_cb != NULL) {
        CALLBACK_LOG_CALLFLOW("report_xtra_server_cb", %s, mServers);
        locEngXtra->report_xtra_server_cb(mServers,
                                          &(mServers[mMaxLen+1]),
                                          &(mServers[(mMaxLen+1)<<1]));
    } else {
        LOC_LOGE("Callback function for request xtra is NULL");
    }
}
inline void LocEngReportXtraServer::locallog() const {
    LOC_LOGV("LocEngReportXtraServers: server1: %s\n  server2: %s\n"
             "  server3: %s\n",
             mServers, &mServers[mMaxLen+1], &mServers[(mMaxLen+1)<<1]);
}
inline void LocEngReportXtraServer::log() const {
    locallog();
}

//        case LOC_ENG_MSG_REQUEST_BIT:
//        case LOC_ENG_MSG_RELEASE_BIT:
LocEngReqRelBIT::LocEngReqRelBIT(void* locEng, AGpsExtType type,
                                 int ipv4, char* ipv6, bool isReq) :
    LocMsg(), mLocEng(locEng), mType(type), mIPv4Addr(ipv4),
    mIPv6Addr(ipv6 ? new char[16] : NULL), mIsReq(isReq) {
    if (NULL != ipv6)
        memcpy(mIPv6Addr, ipv6, 16);
    locallog();
}
inline LocEngReqRelBIT::~LocEngReqRelBIT() {
    if (mIPv6Addr) {
        delete[] mIPv6Addr;
    }
}
void LocEngReqRelBIT::proc() const {
    loc_eng_data_s_type* locEng = (loc_eng_data_s_type*)mLocEng;
    BITSubscriber s(getAgpsStateMachine(*locEng, mType),
                    mIPv4Addr, mIPv6Addr);
    AgpsStateMachine* sm = (AgpsStateMachine*)s.mStateMachine;

    if (mIsReq) {
        sm->subscribeRsrc((Subscriber*)&s);
    } else {
        sm->unsubscribeRsrc((Subscriber*)&s);
    }
}
inline void LocEngReqRelBIT::locallog() const {
    LOC_LOGV("LocEngRequestBIT - ipv4: %d.%d.%d.%d, ipv6: %s",
             (unsigned char)mIPv4Addr,
             (unsigned char)(mIPv4Addr>>8),
             (unsigned char)(mIPv4Addr>>16),
             (unsigned char)(mIPv4Addr>>24),
             NULL != mIPv6Addr ? mIPv6Addr : "");
}
inline void LocEngReqRelBIT::log() const {
    locallog();
}
void LocEngReqRelBIT::send() const {
    loc_eng_data_s_type* locEng = (loc_eng_data_s_type*)mLocEng;
    locEng->adapter->sendMsg(this);
}

//        case LOC_ENG_MSG_RELEASE_BIT:
struct LocEngReleaseBIT : public LocMsg {
    const BITSubscriber mSubscriber;
    inline LocEngReleaseBIT(const AgpsStateMachine* stateMachine,
                            unsigned int ipv4, char* ipv6) :
        LocMsg(),
        mSubscriber(stateMachine, ipv4, ipv6)
    {
        locallog();
    }
    inline virtual void proc() const
    {
        AgpsStateMachine* sm = (AgpsStateMachine*)mSubscriber.mStateMachine;
        sm->unsubscribeRsrc((Subscriber*)&mSubscriber);
    }
    inline void locallog() const {
        LOC_LOGV("LocEngReleaseBIT - ipv4: %d.%d.%d.%d, ipv6: %s",
                 (unsigned char)(mSubscriber.ID>>24),
                 (unsigned char)(mSubscriber.ID>>16),
                 (unsigned char)(mSubscriber.ID>>8),
                 (unsigned char)mSubscriber.ID,
                 NULL != mSubscriber.mIPv6Addr ? mSubscriber.mIPv6Addr : "");
    }
    virtual void log() const {
        locallog();
    }
};

//        LocEngSuplEsOpened
LocEngSuplEsOpened::LocEngSuplEsOpened(void* locEng) :
    LocMsg(), mLocEng(locEng) {
    locallog();
}
void LocEngSuplEsOpened::proc() const {
    loc_eng_data_s_type* locEng = (loc_eng_data_s_type*)mLocEng;
    if (locEng->ds_nif) {
        AgpsStateMachine* sm = locEng->ds_nif;
        sm->onRsrcEvent(RSRC_GRANTED);
    }
}
void LocEngSuplEsOpened::locallog() const {
    LOC_LOGV("LocEngSuplEsOpened");
}
void LocEngSuplEsOpened::log() const {
    locallog();
}

//        LocEngSuplEsClosed
LocEngSuplEsClosed::LocEngSuplEsClosed(void* locEng) :
    LocMsg(), mLocEng(locEng) {
    locallog();
}
void LocEngSuplEsClosed::proc() const {
    loc_eng_data_s_type* locEng = (loc_eng_data_s_type*)mLocEng;
    if (locEng->ds_nif) {
        AgpsStateMachine* sm = locEng->ds_nif;
        sm->onRsrcEvent(RSRC_RELEASED);
    }
}
void LocEngSuplEsClosed::locallog() const {
    LOC_LOGV("LocEngSuplEsClosed");
}
void LocEngSuplEsClosed::log() const {
    locallog();
}


//        case LOC_ENG_MSG_REQUEST_SUPL_ES:
LocEngRequestSuplEs::LocEngRequestSuplEs(void* locEng, int id) :
    LocMsg(), mLocEng(locEng), mID(id) {
    locallog();
}
void LocEngRequestSuplEs::proc() const {
    loc_eng_data_s_type* locEng = (loc_eng_data_s_type*)mLocEng;
    if (locEng->ds_nif) {
        AgpsStateMachine* sm = locEng->ds_nif;
        DSSubscriber s(sm, mID);
        sm->subscribeRsrc((Subscriber*)&s);
    }
    else if (locEng->agnss_nif) {
        AgpsStateMachine *sm = locEng->agnss_nif;
        ATLSubscriber s(mID,
                        sm,
                        locEng->adapter,
                        false);
        sm->subscribeRsrc((Subscriber*)&s);
        LOC_LOGD("%s:%d]: Using regular ATL for SUPL ES", __func__, __LINE__);
    }
    else {
        locEng->adapter->atlOpenStatus(mID, 0, NULL, -1, -1);
    }
}
inline void LocEngRequestSuplEs::locallog() const {
    LOC_LOGV("LocEngRequestSuplEs");
}
inline void LocEngRequestSuplEs::log() const {
    locallog();
}

//        case LOC_ENG_MSG_REQUEST_ATL:
LocEngRequestATL::LocEngRequestATL(void* locEng, int id,
                                   AGpsExtType agps_type) :
    LocMsg(), mLocEng(locEng), mID(id), mType(agps_type) {
    locallog();
}
void LocEngRequestATL::proc() const {
    loc_eng_data_s_type* locEng = (loc_eng_data_s_type*)mLocEng;
    AgpsStateMachine* sm = (AgpsStateMachine*)
                           getAgpsStateMachine(*locEng, mType);
    if (sm) {
        ATLSubscriber s(mID,
                        sm,
                        locEng->adapter,
                        AGPS_TYPE_INVALID == mType);
        sm->subscribeRsrc((Subscriber*)&s);
    } else {
        locEng->adapter->atlOpenStatus(mID, 0, NULL, -1, mType);
    }
}
inline void LocEngRequestATL::locallog() const {
    LOC_LOGV("LocEngRequestATL");
}
inline void LocEngRequestATL::log() const {
    locallog();
}

//        case LOC_ENG_MSG_RELEASE_ATL:
LocEngReleaseATL::LocEngReleaseATL(void* locEng, int id) :
    LocMsg(), mLocEng(locEng), mID(id) {
    locallog();
}
void LocEngReleaseATL::proc() const {
    loc_eng_data_s_type* locEng = (loc_eng_data_s_type*)mLocEng;

   if (locEng->agnss_nif) {
        ATLSubscriber s1(mID, locEng->agnss_nif, locEng->adapter, false);
        if (locEng->agnss_nif->unsubscribeRsrc((Subscriber*)&s1)) {
            LOC_LOGD("%s:%d]: Unsubscribed from agnss_nif",
                     __func__, __LINE__);
            return;
        }
    }

    if (locEng->internet_nif) {
        ATLSubscriber s2(mID, locEng->internet_nif, locEng->adapter, false);
        if (locEng->internet_nif->unsubscribeRsrc((Subscriber*)&s2)) {
            LOC_LOGD("%s:%d]: Unsubscribed from internet_nif",
                     __func__, __LINE__);
            return;
        }
    }

    if (locEng->ds_nif) {
        DSSubscriber s3(locEng->ds_nif, mID);
        if (locEng->ds_nif->unsubscribeRsrc((Subscriber*)&s3)) {
            LOC_LOGD("%s:%d]: Unsubscribed from ds_nif",
                     __func__, __LINE__);
            return;
        }
    }

    LOC_LOGW("%s:%d]: Could not release ATL. "
             "No subscribers found\n",
             __func__, __LINE__);
    locEng->adapter->atlCloseStatus(mID, 0);
}
inline void LocEngReleaseATL::locallog() const {
    LOC_LOGV("LocEngReleaseATL");
}
inline void LocEngReleaseATL::log() const {
    locallog();
}

//        case LOC_ENG_MSG_REQUEST_WIFI:
//        case LOC_ENG_MSG_RELEASE_WIFI:
LocEngReqRelWifi::LocEngReqRelWifi(void* locEng, AGpsExtType type,
                                   loc_if_req_sender_id_e_type sender_id,
                                   char* s, char* p, bool isReq) :
    LocMsg(), mLocEng(locEng), mType(type), mSenderId(sender_id),
    mSSID(NULL == s ? NULL : new char[SSID_BUF_SIZE]),
    mPassword(NULL == p ? NULL : new char[SSID_BUF_SIZE]),
    mIsReq(isReq) {
    if (NULL != s)
        strlcpy(mSSID, s, SSID_BUF_SIZE);
    if (NULL != p)
        strlcpy(mPassword, p, SSID_BUF_SIZE);
    locallog();
}
LocEngReqRelWifi::~LocEngReqRelWifi() {
    if (NULL != mSSID) {
        delete[] mSSID;
    }
    if (NULL != mPassword) {
        delete[] mPassword;
    }
}
void LocEngReqRelWifi::proc() const {
    loc_eng_data_s_type* locEng = (loc_eng_data_s_type*)mLocEng;
    if (locEng->wifi_nif) {
        WIFISubscriber s(locEng->wifi_nif, mSSID, mPassword, mSenderId);
        if (mIsReq) {
            locEng->wifi_nif->subscribeRsrc((Subscriber*)&s);
        } else {
            locEng->wifi_nif->unsubscribeRsrc((Subscriber*)&s);
        }
    } else {
        locEng->adapter->atlOpenStatus(mSenderId, 0, NULL, -1, mType);
    }
}
inline void LocEngReqRelWifi::locallog() const {
    LOC_LOGV("%s - senderId: %d, ssid: %s, password: %s",
             mIsReq ? "LocEngRequestWifi" : "LocEngReleaseWifi",
             mSenderId,
             NULL != mSSID ? mSSID : "",
             NULL != mPassword ? mPassword : "");
}
inline void LocEngReqRelWifi::log() const {
    locallog();
}
void LocEngReqRelWifi::send() const {
    loc_eng_data_s_type* locEng = (loc_eng_data_s_type*)mLocEng;
    locEng->adapter->sendMsg(this);
}

//        case LOC_ENG_MSG_REQUEST_XTRA_DATA:
LocEngRequestXtra::LocEngRequestXtra(void* locEng) :
    mLocEng(locEng) {
    locallog();
}
void LocEngRequestXtra::proc() const
{
    loc_eng_xtra_data_s_type* locEngXtra =
        &(((loc_eng_data_s_type*)mLocEng)->xtra_module_data);

    if (locEngXtra->download_request_cb != NULL) {
        CALLBACK_LOG_CALLFLOW("download_request_cb", %p, mLocEng);
        locEngXtra->download_request_cb();
    } else {
        LOC_LOGE("Callback function for request xtra is NULL");
    }
}
inline void LocEngRequestXtra::locallog() const {
    LOC_LOGV("LocEngReqXtra");
}
inline void LocEngRequestXtra::log() const {
    locallog();
}

//        case LOC_ENG_MSG_REQUEST_TIME:
LocEngRequestTime::LocEngRequestTime(void* locEng) :
    LocMsg(), mLocEng(locEng)
{
    locallog();
}
void LocEngRequestTime::proc() const {
    loc_eng_data_s_type* locEng = (loc_eng_data_s_type*)mLocEng;
    if (gps_conf.CAPABILITIES & GPS_CAPABILITY_ON_DEMAND_TIME) {
        if (locEng->request_utc_time_cb != NULL) {
            locEng->request_utc_time_cb();
        } else {
            LOC_LOGE("Callback function for request time is NULL");
        }
    }
}
inline void LocEngRequestTime::locallog() const {
    LOC_LOGV("LocEngReqTime");
}
inline void LocEngRequestTime::log() const {
    locallog();
}

//        case LOC_ENG_MSG_DELETE_AIDING_DATA:
struct LocEngDelAidData : public LocMsg {
    loc_eng_data_s_type* mLocEng;
    const GpsAidingData mType;
    inline LocEngDelAidData(loc_eng_data_s_type* locEng,
                            GpsAidingData f) :
        LocMsg(), mLocEng(locEng), mType(f)
    {
        locallog();
    }
    inline virtual void proc() const {
        mLocEng->aiding_data_for_deletion = mType;
        update_aiding_data_for_deletion(*mLocEng);
    }
    inline void locallog() const {
        LOC_LOGV("aiding data msak %d", mType);
    }
    virtual void log() const {
        locallog();
    }
};

//        case LOC_ENG_MSG_ENABLE_DATA:
struct LocEngEnableData : public LocMsg {
    LocEngAdapter* mAdapter;
    const int mEnable;
    char* mAPN;
    const int mLen;
    inline LocEngEnableData(LocEngAdapter* adapter,
                            const char* name, int len, int enable) :
        LocMsg(), mAdapter(adapter),
        mEnable(enable), mAPN(NULL), mLen(len)
    {
        if (NULL != name) {
            mAPN = new char[len+1];
            memcpy((void*)mAPN, (void*)name, len);
            mAPN[len] = 0;
        }
        locallog();
    }
    inline ~LocEngEnableData() {
        if (NULL != mAPN) {
            delete[] mAPN;
        }
    }
    inline virtual void proc() const {
        mAdapter->enableData(mEnable);
        if (NULL != mAPN) {
            mAdapter->setAPN(mAPN, mLen);
        }
    }
    inline void locallog() const {
        LOC_LOGV("apn: %s\n  enable: %d",
                 (NULL == mAPN) ? "NULL" : mAPN, mEnable);
    }
    inline virtual void log() const {
        locallog();
    }
};

//        case LOC_ENG_MSG_INJECT_XTRA_DATA:
// loc_eng_xtra.cpp

//        case LOC_ENG_MSG_SET_CAPABILITIES:
struct LocEngSetCapabilities : public LocMsg {
    loc_eng_data_s_type* mLocEng;
    inline LocEngSetCapabilities(loc_eng_data_s_type* locEng) :
        LocMsg(), mLocEng(locEng)
    {
        locallog();
    }
    inline virtual void proc() const {
        if (NULL != mLocEng->set_capabilities_cb) {
            LOC_LOGV("calling set_capabilities_cb 0x%x",
                     gps_conf.CAPABILITIES);
            mLocEng->set_capabilities_cb(gps_conf.CAPABILITIES);
        } else {
            LOC_LOGV("set_capabilities_cb is NULL.\n");
        }
    }
    inline void locallog() const
    {
        LOC_LOGV("LocEngSetCapabilities");
    }
    inline virtual void log() const
    {
        locallog();
    }
};

//        case LOC_ENG_MSG_LOC_INIT:
struct LocEngInit : public LocMsg {
    loc_eng_data_s_type* mLocEng;
    inline LocEngInit(loc_eng_data_s_type* locEng) :
        LocMsg(), mLocEng(locEng)
    {
        locallog();
    }
    inline virtual void proc() const {
        loc_eng_reinit(*mLocEng);
        // set the capabilities
        mLocEng->adapter->sendMsg(new LocEngSetCapabilities(mLocEng));
    }
    inline void locallog() const
    {
        LOC_LOGV("LocEngInit");
    }
    inline virtual void log() const
    {
        locallog();
    }
};

//        case LOC_ENG_MSG_REQUEST_XTRA_SERVER:
// loc_eng_xtra.cpp

//        case LOC_ENG_MSG_ATL_OPEN_SUCCESS:
struct LocEngAtlOpenSuccess : public LocMsg {
    AgpsStateMachine* mStateMachine;
    const int mLen;
    char* mAPN;
    const AGpsBearerType mBearerType;
    inline LocEngAtlOpenSuccess(AgpsStateMachine* statemachine,
                                const char* name,
                                int len,
                                AGpsBearerType btype) :
        LocMsg(),
        mStateMachine(statemachine), mLen(len),
        mAPN(new char[len+1]), mBearerType(btype)
    {
        memcpy((void*)mAPN, (void*)name, len);
        mAPN[len] = 0;
        locallog();
    }
    inline ~LocEngAtlOpenSuccess()
    {
        delete[] mAPN;
    }
    inline virtual void proc() const {
        mStateMachine->setBearer(mBearerType);
        mStateMachine->setAPN(mAPN, mLen);
        mStateMachine->onRsrcEvent(RSRC_GRANTED);
    }
    inline void locallog() const {
        LOC_LOGV("LocEngAtlOpenSuccess agps type: %s\n  apn: %s\n"
                 "  bearer type: %s",
                 loc_get_agps_type_name(mStateMachine->getType()),
                 mAPN,
                 loc_get_agps_bear_name(mBearerType));
    }
    inline virtual void log() const {
        locallog();
    }
};

//        case LOC_ENG_MSG_ATL_CLOSED:
struct LocEngAtlClosed : public LocMsg {
    AgpsStateMachine* mStateMachine;
    inline LocEngAtlClosed(AgpsStateMachine* statemachine) :
        LocMsg(), mStateMachine(statemachine) {
        locallog();
    }
    inline virtual void proc() const {
        mStateMachine->onRsrcEvent(RSRC_RELEASED);
    }
    inline void locallog() const {
        LOC_LOGV("LocEngAtlClosed");
    }
    inline virtual void log() const {
        locallog();
    }
};

//        case LOC_ENG_MSG_ATL_OPEN_FAILED:
struct LocEngAtlOpenFailed : public LocMsg {
    AgpsStateMachine* mStateMachine;
    inline LocEngAtlOpenFailed(AgpsStateMachine* statemachine) :
        LocMsg(), mStateMachine(statemachine) {
        locallog();
    }
    inline virtual void proc() const {
        mStateMachine->onRsrcEvent(RSRC_DENIED);
    }
    inline void locallog() const {
        LOC_LOGV("LocEngAtlOpenFailed");
    }
    inline virtual void log() const {
        locallog();
    }
};

//        case LOC_ENG_MSG_ENGINE_DOWN:
LocEngDown::LocEngDown(void* locEng) :
    LocMsg(), mLocEng(locEng) {
    locallog();
}
inline void LocEngDown::proc() const {
    loc_eng_data_s_type* locEng = (loc_eng_data_s_type*)mLocEng;
    loc_eng_handle_engine_down(*locEng);
}
inline void LocEngDown::locallog() const {
    LOC_LOGV("LocEngDown");
}
inline void LocEngDown::log() const {
    locallog();
}

//        case LOC_ENG_MSG_ENGINE_UP:
LocEngUp::LocEngUp(void* locEng) :
    LocMsg(), mLocEng(locEng) {
    locallog();
}
inline void LocEngUp::proc() const {
    loc_eng_data_s_type* locEng = (loc_eng_data_s_type*)mLocEng;
    loc_eng_handle_engine_up(*locEng);
}
inline void LocEngUp::locallog() const {
    LOC_LOGV("LocEngUp");
}
inline void LocEngUp::log() const {
    locallog();
}

struct LocEngDataClientInit : public LocMsg {
    loc_eng_data_s_type* mLocEng;
    inline LocEngDataClientInit(loc_eng_data_s_type* locEng) :
        LocMsg(), mLocEng(locEng) {
        locallog();
    }
    virtual void proc() const {
        loc_eng_data_s_type *locEng = (loc_eng_data_s_type *)mLocEng;
        if(!locEng->adapter->initDataServiceClient()) {
            locEng->ds_nif = new DSStateMachine(servicerTypeExt,
                                               (void *)dataCallCb,
                                               locEng->adapter);
        }
    }
    void locallog() const {
        LOC_LOGV("LocEngDataClientInit\n");
    }
    virtual void log() const {
        locallog();
    }
};

struct LocEngInstallAGpsCert : public LocMsg {
    LocEngAdapter* mpAdapter;
    const size_t mNumberOfCerts;
    const uint32_t mSlotBitMask;
    DerEncodedCertificate* mpData;
    inline LocEngInstallAGpsCert(LocEngAdapter* adapter,
                              const DerEncodedCertificate* pData,
                              size_t numberOfCerts,
                              uint32_t slotBitMask) :
        LocMsg(), mpAdapter(adapter),
        mNumberOfCerts(numberOfCerts), mSlotBitMask(slotBitMask),
        mpData(new DerEncodedCertificate[mNumberOfCerts])
    {
        for (int i=0; i < mNumberOfCerts; i++) {
            mpData[i].data = new u_char[pData[i].length];
            if (mpData[i].data) {
                memcpy(mpData[i].data, (void*)pData[i].data, pData[i].length);
                mpData[i].length = pData[i].length;
            } else {
                LOC_LOGE("malloc failed for cert#%d", i);
                break;
            }
        }
        locallog();
    }
    inline ~LocEngInstallAGpsCert()
    {
        for (int i=0; i < mNumberOfCerts; i++) {
            if (mpData[i].data) {
                delete[] mpData[i].data;
            }
        }
        delete[] mpData;
    }
    inline virtual void proc() const {
        mpAdapter->installAGpsCert(mpData, mNumberOfCerts, mSlotBitMask);
    }
    inline void locallog() const {
        LOC_LOGV("LocEngInstallAGpsCert - certs=%u mask=%u",
                 mNumberOfCerts, mSlotBitMask);
    }
    inline virtual void log() const {
        locallog();
    }
};

struct LocEngUpdateRegistrationMask : public LocMsg {
    loc_eng_data_s_type* mLocEng;
    LOC_API_ADAPTER_EVENT_MASK_T mMask;
    loc_registration_mask_status mIsEnabled;
    inline LocEngUpdateRegistrationMask(loc_eng_data_s_type* locEng,
                                        LOC_API_ADAPTER_EVENT_MASK_T mask,
                                        loc_registration_mask_status isEnabled) :
        LocMsg(), mLocEng(locEng), mMask(mask), mIsEnabled(isEnabled) {
        locallog();
    }
    inline virtual void proc() const {
        loc_eng_data_s_type *locEng = (loc_eng_data_s_type *)mLocEng;
        locEng->adapter->updateRegistrationMask(mMask,
                                                mIsEnabled);
    }
    void locallog() const {
        LOC_LOGV("LocEngUpdateRegistrationMask\n");
    }
    virtual void log() const {
        locallog();
    }
};

struct LocEngGnssConstellationConfig : public LocMsg {
    LocEngAdapter* mAdapter;
    inline LocEngGnssConstellationConfig(LocEngAdapter* adapter) :
        LocMsg(), mAdapter(adapter) {
        locallog();
    }
    inline virtual void proc() const {
        if (mAdapter->gnssConstellationConfig()) {
            LOC_LOGV("Modem supports GNSS measurements\n");
            gps_conf.CAPABILITIES |= GPS_CAPABILITY_MEASUREMENTS;
        } else {
            LOC_LOGV("Modem does not support GNSS measurements\n");
        }
    }
    void locallog() const {
        LOC_LOGV("LocEngGnssConstellationConfig\n");
    }
    virtual void log() const {
        locallog();
    }
};

//        case LOC_ENG_MSG_REPORT_GNSS_MEASUREMENT:
LocEngReportGpsMeasurement::LocEngReportGpsMeasurement(void* locEng,
                                                       GpsData &gpsData) :
    LocMsg(), mLocEng(locEng), mGpsData(gpsData)
{
    locallog();
}
void LocEngReportGpsMeasurement::proc() const {
    loc_eng_data_s_type* locEng = (loc_eng_data_s_type*) mLocEng;
    if (locEng->mute_session_state != LOC_MUTE_SESS_IN_SESSION)
    {
        if (locEng->gps_measurement_cb != NULL) {
            locEng->gps_measurement_cb((GpsData*)&(mGpsData));
        }
    }
}
void LocEngReportGpsMeasurement::locallog() const {
    IF_LOC_LOGV {
        LOC_LOGV("%s:%d]: Received in GPS HAL."
                 "GNSS Measurements count: %d \n",
                 __func__, __LINE__, mGpsData.measurement_count);
        for (int i =0; i< mGpsData.measurement_count && i < GPS_MAX_SVS; i++) {
                LOC_LOGV(" GNSS measurement data in GPS HAL: \n"
                         " GPS_HAL => Measurement ID | prn | time_offset_ns | state |"
                         " received_gps_tow_ns| c_n0_dbhz | pseudorange_rate_mps |"
                         " pseudorange_rate_uncertainty_mps |"
                         " accumulated_delta_range_state | flags \n"
                         " GPS_HAL => %d | %d | %f | %d | %lld | %f | %f | %f | %d | %d \n",
                         i,
                         mGpsData.measurements[i].prn,
                         mGpsData.measurements[i].time_offset_ns,
                         mGpsData.measurements[i].state,
                         mGpsData.measurements[i].received_gps_tow_ns,
                         mGpsData.measurements[i].c_n0_dbhz,
                         mGpsData.measurements[i].pseudorange_rate_mps,
                         mGpsData.measurements[i].pseudorange_rate_uncertainty_mps,
                         mGpsData.measurements[i].accumulated_delta_range_state,
                         mGpsData.measurements[i].flags);
        }
        LOC_LOGV(" GPS_HAL => Clocks Info: type | time_ns \n"
                 " GPS_HAL => Clocks Info: %d | %lld", mGpsData.clock.type,
                 mGpsData.clock.time_ns);
    }
}
inline void LocEngReportGpsMeasurement::log() const {
    locallog();
}

/*********************************************************************
 * Initialization checking macros
 *********************************************************************/
#define STATE_CHECK(ctx, x, ret) \
    if (!(ctx))                  \
  {                              \
      /* Not intialized, abort */\
      LOC_LOGE("%s: log_eng state error: %s", __func__, x); \
      EXIT_LOG(%s, x);                                            \
      ret;                                                        \
  }
#define INIT_CHECK(ctx, ret) STATE_CHECK(ctx, "instance not initialized", ret)

uint32_t getCarrierCapabilities() {
    #define carrierMSA (uint32_t)0x2
    #define carrierMSB (uint32_t)0x1
    #define gpsConfMSA (uint32_t)0x4
    #define gpsConfMSB (uint32_t)0x2
    uint32_t capabilities = gps_conf.CAPABILITIES;
    if ((gps_conf.SUPL_MODE & carrierMSA) != carrierMSA) {
        capabilities &= ~gpsConfMSA;
    }
    if ((gps_conf.SUPL_MODE & carrierMSB) != carrierMSB) {
        capabilities &= ~gpsConfMSB;
    }

    LOC_LOGV("getCarrierCapabilities: CAPABILITIES %x, SUPL_MODE %x, carrier capabilities %x",
             gps_conf.CAPABILITIES, gps_conf.SUPL_MODE, capabilities);
    return capabilities;
}

/*===========================================================================
FUNCTION    loc_eng_init

DESCRIPTION
   Initialize the location engine, this include setting up global datas
   and registers location engien with loc api service.

DEPENDENCIES
   None

RETURN VALUE
   0: success

SIDE EFFECTS
   N/A

===========================================================================*/
int loc_eng_init(loc_eng_data_s_type &loc_eng_data, LocCallbacks* callbacks,
                 LOC_API_ADAPTER_EVENT_MASK_T event, ContextBase* context)

{
    int ret_val = 0;

    ENTRY_LOG_CALLFLOW();
    if (NULL == callbacks || 0 == event) {
        LOC_LOGE("loc_eng_init: bad parameters cb %p eMask %d", callbacks, event);
        ret_val = -1;
        EXIT_LOG(%d, ret_val);
        return ret_val;
    }

    STATE_CHECK((NULL == loc_eng_data.adapter),
                "instance already initialized", return 0);

    memset(&loc_eng_data, 0, sizeof (loc_eng_data));

    // Save callbacks
    loc_eng_data.location_cb  = callbacks->location_cb;
    loc_eng_data.sv_status_cb = callbacks->sv_status_cb;
    loc_eng_data.status_cb    = callbacks->status_cb;
    loc_eng_data.nmea_cb      = callbacks->nmea_cb;
    loc_eng_data.set_capabilities_cb = callbacks->set_capabilities_cb;
    loc_eng_data.acquire_wakelock_cb = callbacks->acquire_wakelock_cb;
    loc_eng_data.release_wakelock_cb = callbacks->release_wakelock_cb;
    loc_eng_data.request_utc_time_cb = callbacks->request_utc_time_cb;
    loc_eng_data.location_ext_parser = callbacks->location_ext_parser ?
        callbacks->location_ext_parser : noProc;
    loc_eng_data.sv_ext_parser = callbacks->sv_ext_parser ?
        callbacks->sv_ext_parser : noProc;
    loc_eng_data.intermediateFix = gps_conf.INTERMEDIATE_POS;
    // initial states taken care of by the memset above
    // loc_eng_data.engine_status -- GPS_STATUS_NONE;
    // loc_eng_data.fix_session_status -- GPS_STATUS_NONE;
    // loc_eng_data.mute_session_state -- LOC_MUTE_SESS_NONE;

    if ((event & LOC_API_ADAPTER_BIT_NMEA_1HZ_REPORT) && (gps_conf.NMEA_PROVIDER == NMEA_PROVIDER_AP))
    {
        event = event ^ LOC_API_ADAPTER_BIT_NMEA_1HZ_REPORT; // unregister for modem NMEA report
        loc_eng_data.generateNmea = true;
    }
    else
    {
        loc_eng_data.generateNmea = false;
    }

    loc_eng_data.adapter =
        new LocEngAdapter(event, &loc_eng_data, context,
                          (LocThread::tCreate)callbacks->create_thread_cb);

    LOC_LOGD("loc_eng_init created client, id = %p\n",
             loc_eng_data.adapter);
    loc_eng_data.adapter->sendMsg(new LocEngInit(&loc_eng_data));

    EXIT_LOG(%d, ret_val);
    return ret_val;
}

static int loc_eng_reinit(loc_eng_data_s_type &loc_eng_data)
{
    ENTRY_LOG();
    int ret_val = LOC_API_ADAPTER_ERR_SUCCESS;
    LocEngAdapter* adapter = loc_eng_data.adapter;

    adapter->sendMsg(new LocEngGnssConstellationConfig(adapter));
    adapter->sendMsg(new LocEngSuplVer(adapter, gps_conf.SUPL_VER));
    adapter->sendMsg(new LocEngLppConfig(adapter, gps_conf.LPP_PROFILE));
    adapter->sendMsg(new LocEngSensorControlConfig(adapter, sap_conf.SENSOR_USAGE,
                                                   sap_conf.SENSOR_PROVIDER));
    adapter->sendMsg(new LocEngAGlonassProtocol(adapter, gps_conf.A_GLONASS_POS_PROTOCOL_SELECT));

    /* Make sure at least one of the sensor property is specified by the user in the gps.conf file. */
    if( sap_conf.GYRO_BIAS_RANDOM_WALK_VALID ||
        sap_conf.ACCEL_RANDOM_WALK_SPECTRAL_DENSITY_VALID ||
        sap_conf.ANGLE_RANDOM_WALK_SPECTRAL_DENSITY_VALID ||
        sap_conf.RATE_RANDOM_WALK_SPECTRAL_DENSITY_VALID ||
        sap_conf.VELOCITY_RANDOM_WALK_SPECTRAL_DENSITY_VALID ) {
        adapter->sendMsg(new LocEngSensorProperties(adapter,
                                                    sap_conf.GYRO_BIAS_RANDOM_WALK_VALID,
                                                    sap_conf.GYRO_BIAS_RANDOM_WALK,
                                                    sap_conf.ACCEL_RANDOM_WALK_SPECTRAL_DENSITY_VALID,
                                                    sap_conf.ACCEL_RANDOM_WALK_SPECTRAL_DENSITY,
                                                    sap_conf.ANGLE_RANDOM_WALK_SPECTRAL_DENSITY_VALID,
                                                    sap_conf.ANGLE_RANDOM_WALK_SPECTRAL_DENSITY,
                                                    sap_conf.RATE_RANDOM_WALK_SPECTRAL_DENSITY_VALID,
                                                    sap_conf.RATE_RANDOM_WALK_SPECTRAL_DENSITY,
                                                    sap_conf.VELOCITY_RANDOM_WALK_SPECTRAL_DENSITY_VALID,
                                                    sap_conf.VELOCITY_RANDOM_WALK_SPECTRAL_DENSITY));
    }

    adapter->sendMsg(new LocEngSensorPerfControlConfig(adapter,
                                                       sap_conf.SENSOR_CONTROL_MODE,
                                                       sap_conf.SENSOR_ACCEL_SAMPLES_PER_BATCH,
                                                       sap_conf.SENSOR_ACCEL_BATCHES_PER_SEC,
                                                       sap_conf.SENSOR_GYRO_SAMPLES_PER_BATCH,
                                                       sap_conf.SENSOR_GYRO_BATCHES_PER_SEC,
                                                       sap_conf.SENSOR_ACCEL_SAMPLES_PER_BATCH_HIGH,
                                                       sap_conf.SENSOR_ACCEL_BATCHES_PER_SEC_HIGH,
                                                       sap_conf.SENSOR_GYRO_SAMPLES_PER_BATCH_HIGH,
                                                       sap_conf.SENSOR_GYRO_BATCHES_PER_SEC_HIGH,
                                                       sap_conf.SENSOR_ALGORITHM_CONFIG_MASK));

    adapter->sendMsg(new LocEngEnableData(adapter, NULL, 0, (agpsStatus ? 1:0)));

    loc_eng_xtra_version_check(loc_eng_data, gps_conf.XTRA_VERSION_CHECK);

    LOC_LOGD("loc_eng_reinit reinit() successful");
    EXIT_LOG(%d, ret_val);
    return ret_val;
}

/*===========================================================================
FUNCTION    loc_eng_cleanup

DESCRIPTION
   Cleans location engine. The location client handle will be released.

DEPENDENCIES
   None

RETURN VALUE
   None

SIDE EFFECTS
   N/A

===========================================================================*/
void loc_eng_cleanup(loc_eng_data_s_type &loc_eng_data)
{
    ENTRY_LOG_CALLFLOW();
    INIT_CHECK(loc_eng_data.adapter, return);

    // XTRA has no state, so we are fine with it.

    // we need to check and clear NI
#if 0
    // we need to check and clear ATL
    if (NULL != loc_eng_data.agnss_nif) {
        delete loc_eng_data.agnss_nif;
        loc_eng_data.agnss_nif = NULL;
    }
    if (NULL != loc_eng_data.internet_nif) {
        delete loc_eng_data.internet_nif;
        loc_eng_data.internet_nif = NULL;
    }
#endif
    if (loc_eng_data.adapter->isInSession())
    {
        LOC_LOGD("loc_eng_cleanup: fix not stopped. stop it now.");
        loc_eng_stop(loc_eng_data);
    }

#if 0 // can't afford to actually clean up, for many reason.

    LOC_LOGD("loc_eng_init: client opened. close it now.");
    delete loc_eng_data.adapter;
    loc_eng_data.adapter = NULL;

    loc_eng_dmn_conn_loc_api_server_unblock();
    loc_eng_dmn_conn_loc_api_server_join();

#endif

    EXIT_LOG(%s, VOID_RET);
}


/*===========================================================================
FUNCTION    loc_eng_start

DESCRIPTION
   Starts the tracking session

DEPENDENCIES
   None

RETURN VALUE
   0: success

SIDE EFFECTS
   N/A

===========================================================================*/
int loc_eng_start(loc_eng_data_s_type &loc_eng_data)
{
   ENTRY_LOG_CALLFLOW();
   INIT_CHECK(loc_eng_data.adapter, return -1);

   if(! loc_eng_data.adapter->getUlpProxy()->sendStartFix())
   {
       loc_eng_data.adapter->sendMsg(new LocEngStartFix(loc_eng_data.adapter));
   }

   EXIT_LOG(%d, 0);
   return 0;
}

static int loc_eng_start_handler(loc_eng_data_s_type &loc_eng_data)
{
   ENTRY_LOG();
   int ret_val = LOC_API_ADAPTER_ERR_SUCCESS;

   if (!loc_eng_data.adapter->isInSession()) {
       ret_val = loc_eng_data.adapter->startFix();

       if (ret_val == LOC_API_ADAPTER_ERR_SUCCESS ||
           ret_val == LOC_API_ADAPTER_ERR_ENGINE_DOWN ||
           ret_val == LOC_API_ADAPTER_ERR_PHONE_OFFLINE ||
           ret_val == LOC_API_ADAPTER_ERR_INTERNAL)
       {
           loc_eng_data.adapter->setInSession(TRUE);
       }
   }

   EXIT_LOG(%d, ret_val);
   return ret_val;
}

/*===========================================================================
FUNCTION    loc_eng_stop_wrapper

DESCRIPTION
   Stops the tracking session

DEPENDENCIES
   None

RETURN VALUE
   0: success

SIDE EFFECTS
   N/A

===========================================================================*/
int loc_eng_stop(loc_eng_data_s_type &loc_eng_data)
{
    ENTRY_LOG_CALLFLOW();
    INIT_CHECK(loc_eng_data.adapter, return -1);

    if(! loc_eng_data.adapter->getUlpProxy()->sendStopFix())
    {
        loc_eng_data.adapter->sendMsg(new LocEngStopFix(loc_eng_data.adapter));
    }

    EXIT_LOG(%d, 0);
    return 0;
}

static int loc_eng_stop_handler(loc_eng_data_s_type &loc_eng_data)
{
   ENTRY_LOG();
   int ret_val = LOC_API_ADAPTER_ERR_SUCCESS;

   if (loc_eng_data.adapter->isInSession()) {

       ret_val = loc_eng_data.adapter->stopFix();
       loc_eng_data.adapter->setInSession(FALSE);
   }

    EXIT_LOG(%d, ret_val);
    return ret_val;
}

/*===========================================================================
FUNCTION    loc_eng_mute_one_session

DESCRIPTION
   Mutes one session

DEPENDENCIES
   None

RETURN VALUE
   0: Success

SIDE EFFECTS
   N/A

===========================================================================*/
void loc_eng_mute_one_session(loc_eng_data_s_type &loc_eng_data)
{
    ENTRY_LOG();
    loc_eng_data.mute_session_state = LOC_MUTE_SESS_WAIT;
    EXIT_LOG(%s, VOID_RET);
}

/*===========================================================================
FUNCTION    loc_eng_set_position_mode

DESCRIPTION
   Sets the mode and fix frequency for the tracking session.

DEPENDENCIES
   None

RETURN VALUE
   0: success

SIDE EFFECTS
   N/A

===========================================================================*/
int loc_eng_set_position_mode(loc_eng_data_s_type &loc_eng_data,
                              LocPosMode &params)
{
    ENTRY_LOG_CALLFLOW();
    INIT_CHECK(loc_eng_data.adapter, return -1);

    // The position mode for AUTO/GSS/QCA1530 can only be standalone
    if (!(gps_conf.CAPABILITIES & GPS_CAPABILITY_MSB) &&
        !(gps_conf.CAPABILITIES & GPS_CAPABILITY_MSA) &&
        (params.mode != LOC_POSITION_MODE_STANDALONE)) {
        params.mode = LOC_POSITION_MODE_STANDALONE;
        LOC_LOGD("Position mode changed to standalone for target with AUTO/GSS/qca1530.");
    }

    if(! loc_eng_data.adapter->getUlpProxy()->sendFixMode(params))
    {
        LocEngAdapter* adapter = loc_eng_data.adapter;
        adapter->sendMsg(new LocEngPositionMode(adapter, params));
    }

    EXIT_LOG(%d, 0);
    return 0;
}

/*===========================================================================
FUNCTION    loc_eng_inject_time

DESCRIPTION
   This is used by Java native function to do time injection.

DEPENDENCIES
   None

RETURN VALUE
   0

SIDE EFFECTS
   N/A

===========================================================================*/
int loc_eng_inject_time(loc_eng_data_s_type &loc_eng_data, GpsUtcTime time,
                        int64_t timeReference, int uncertainty)
{
    ENTRY_LOG_CALLFLOW();
    INIT_CHECK(loc_eng_data.adapter, return -1);
    LocEngAdapter* adapter = loc_eng_data.adapter;

    adapter->sendMsg(new LocEngSetTime(adapter, time, timeReference,
                                       uncertainty));

    EXIT_LOG(%d, 0);
    return 0;
}


/*===========================================================================
FUNCTION    loc_eng_inject_location

DESCRIPTION
   This is used by Java native function to do location injection.

DEPENDENCIES
   None

RETURN VALUE
   0          : Successful
   error code : Failure

SIDE EFFECTS
   N/A
===========================================================================*/
int loc_eng_inject_location(loc_eng_data_s_type &loc_eng_data, double latitude,
                            double longitude, float accuracy)
{
    ENTRY_LOG_CALLFLOW();
    INIT_CHECK(loc_eng_data.adapter, return -1);
    LocEngAdapter* adapter = loc_eng_data.adapter;
    if(adapter->mSupportsPositionInjection)
    {
        adapter->sendMsg(new LocEngInjectLocation(adapter, latitude, longitude,
                                                  accuracy));
    }

    EXIT_LOG(%d, 0);
    return 0;
}


/*===========================================================================
FUNCTION    loc_eng_delete_aiding_data

DESCRIPTION
   This is used by Java native function to delete the aiding data. The function
   updates the global variable for the aiding data to be deleted. If the GPS
   engine is off, the aiding data will be deleted. Otherwise, the actual action
   will happen when gps engine is turned off.

DEPENDENCIES
   Assumes the aiding data type specified in GpsAidingData matches with
   LOC API specification.

RETURN VALUE
   None

SIDE EFFECTS
   N/A

===========================================================================*/
void loc_eng_delete_aiding_data(loc_eng_data_s_type &loc_eng_data, GpsAidingData f)
{
    ENTRY_LOG_CALLFLOW();
    INIT_CHECK(loc_eng_data.adapter, return);

    loc_eng_data.adapter->sendMsg(new LocEngDelAidData(&loc_eng_data, f));

    EXIT_LOG(%s, VOID_RET);
}

/*===========================================================================

FUNCTION    loc_inform_gps_state

DESCRIPTION
   Informs the GPS Provider about the GPS status

DEPENDENCIES
   None

RETURN VALUE
   None

SIDE EFFECTS
   N/A

===========================================================================*/
static void loc_inform_gps_status(loc_eng_data_s_type &loc_eng_data, GpsStatusValue status)
{
    ENTRY_LOG();

    if (loc_eng_data.status_cb)
    {
        GpsStatus gs = { sizeof(gs),status };
        CALLBACK_LOG_CALLFLOW("status_cb", %s,
                              loc_get_gps_status_name(gs.status));
        loc_eng_data.status_cb(&gs);
    }

    EXIT_LOG(%s, VOID_RET);
}

static int loc_eng_get_zpp_handler(loc_eng_data_s_type &loc_eng_data)
{
   ENTRY_LOG();
   int ret_val = LOC_API_ADAPTER_ERR_SUCCESS;
   UlpLocation location;
   LocPosTechMask tech_mask = LOC_POS_TECH_MASK_DEFAULT;
   GpsLocationExtended locationExtended;
   memset(&locationExtended, 0, sizeof (GpsLocationExtended));
   locationExtended.size = sizeof(locationExtended);

   ret_val = loc_eng_data.adapter->getZpp(location.gpsLocation, tech_mask);
  //Mark the location source as from ZPP
  location.gpsLocation.flags |= LOCATION_HAS_SOURCE_INFO;
  location.position_source = ULP_LOCATION_IS_FROM_ZPP;

  loc_eng_data.adapter->getUlpProxy()->reportPosition(location,
                                     locationExtended,
                                     NULL,
                                     LOC_SESS_SUCCESS,
                                     tech_mask);

  EXIT_LOG(%d, ret_val);
  return ret_val;
}

/*
  Callback function passed to Data Services State Machine
  This becomes part of the state machine's servicer and
  is used to send requests to the data services client
*/
static int dataCallCb(void *cb_data)
{
    LOC_LOGD("Enter dataCallCb\n");
    int ret=0;
    if(cb_data != NULL) {
        dsCbData *cbData = (dsCbData *)cb_data;
        LocEngAdapter *locAdapter = (LocEngAdapter *)cbData->mAdapter;
        if(cbData->action == GPS_REQUEST_AGPS_DATA_CONN) {
            LOC_LOGD("dataCallCb GPS_REQUEST_AGPS_DATA_CONN\n");
            ret =  locAdapter->openAndStartDataCall();
        }
        else if(cbData->action == GPS_RELEASE_AGPS_DATA_CONN) {
            LOC_LOGD("dataCallCb GPS_RELEASE_AGPS_DATA_CONN\n");
            locAdapter->stopDataCall();
        }
    }
    else {
        LOC_LOGE("NULL argument received. Failing.\n");
        ret = -1;
        goto err;
    }

err:
    LOC_LOGD("Exit dataCallCb ret = %d\n", ret);
    return ret;
}

/*===========================================================================
FUNCTION    loc_eng_agps_reinit

DESCRIPTION
   2nd half of loc_eng_agps_init(), singled out for modem restart to use.

DEPENDENCIES
   NONE

RETURN VALUE
   0

SIDE EFFECTS
   N/A

===========================================================================*/
static void loc_eng_agps_reinit(loc_eng_data_s_type &loc_eng_data)
{
    ENTRY_LOG();

    // Set server addresses which came before init
    if (loc_eng_data.supl_host_set)
    {
        loc_eng_set_server(loc_eng_data, LOC_AGPS_SUPL_SERVER,
                           loc_eng_data.supl_host_buf,
                           loc_eng_data.supl_port_buf);
    }

    if (loc_eng_data.c2k_host_set)
    {
        loc_eng_set_server(loc_eng_data, LOC_AGPS_CDMA_PDE_SERVER,
                           loc_eng_data.c2k_host_buf,
                           loc_eng_data.c2k_port_buf);
    }
    EXIT_LOG(%s, VOID_RET);
}
/*===========================================================================
FUNCTION    loc_eng_agps_init

DESCRIPTION
   Initialize the AGps interface.

DEPENDENCIES
   NONE

RETURN VALUE
   0

SIDE EFFECTS
   N/A

===========================================================================*/
void loc_eng_agps_init(loc_eng_data_s_type &loc_eng_data, AGpsExtCallbacks* callbacks)
{
    ENTRY_LOG_CALLFLOW();
    INIT_CHECK(loc_eng_data.adapter, return);
    STATE_CHECK((NULL == loc_eng_data.agps_status_cb),
                "agps instance already initialized",
                return);
    if (callbacks == NULL) {
        LOC_LOGE("loc_eng_agps_init: bad parameters cb %p", callbacks);
        EXIT_LOG(%s, VOID_RET);
        return;
    }
    LocEngAdapter* adapter = loc_eng_data.adapter;
    loc_eng_data.agps_status_cb = callbacks->status_cb;

    loc_eng_data.internet_nif = new AgpsStateMachine(servicerTypeAgps,
                                                     (void *)loc_eng_data.agps_status_cb,
                                                     AGPS_TYPE_WWAN_ANY,
                                                     false);
    loc_eng_data.wifi_nif = new AgpsStateMachine(servicerTypeAgps,
                                                 (void *)loc_eng_data.agps_status_cb,
                                                 AGPS_TYPE_WIFI,
                                                 true);

    if ((gps_conf.CAPABILITIES & GPS_CAPABILITY_MSA) ||
        (gps_conf.CAPABILITIES & GPS_CAPABILITY_MSB)) {
        loc_eng_data.agnss_nif = new AgpsStateMachine(servicerTypeAgps,
                                                      (void *)loc_eng_data.agps_status_cb,
                                                      AGPS_TYPE_SUPL,
                                                      false);

        if (adapter->mSupportsAgpsRequests) {
            if(gps_conf.USE_EMERGENCY_PDN_FOR_EMERGENCY_SUPL) {
                loc_eng_data.adapter->sendMsg(new LocEngDataClientInit(&loc_eng_data));
            }
            loc_eng_dmn_conn_loc_api_server_launch(callbacks->create_thread_cb,
                                                   NULL, NULL, &loc_eng_data);
        }
        loc_eng_agps_reinit(loc_eng_data);
    }

    EXIT_LOG(%s, VOID_RET);
}

static void deleteAidingData(loc_eng_data_s_type &logEng) {
    if (logEng.engine_status != GPS_STATUS_ENGINE_ON &&
        logEng.aiding_data_for_deletion != 0) {
        logEng.adapter->deleteAidingData(logEng.aiding_data_for_deletion);
        logEng.aiding_data_for_deletion = 0;
    }
}

static AgpsStateMachine*
getAgpsStateMachine(loc_eng_data_s_type &locEng, AGpsExtType agpsType) {
    AgpsStateMachine* stateMachine;
    switch (agpsType) {
    case AGPS_TYPE_WIFI: {
        stateMachine = locEng.wifi_nif;
        break;
    }
    case AGPS_TYPE_INVALID:
    case AGPS_TYPE_SUPL: {
        stateMachine = locEng.agnss_nif;
        break;
    }
    case AGPS_TYPE_SUPL_ES: {
        locEng.ds_nif ?
            stateMachine = locEng.ds_nif:
            stateMachine = locEng.agnss_nif;
        break;
    }
    default:
        stateMachine  = locEng.internet_nif;
    }
    return stateMachine;
}

/*===========================================================================
FUNCTION    loc_eng_agps_open

DESCRIPTION
   This function is called when on-demand data connection opening is successful.
It should inform engine about the data open result.

DEPENDENCIES
   NONE

RETURN VALUE
   0

SIDE EFFECTS
   N/A

===========================================================================*/
int loc_eng_agps_open(loc_eng_data_s_type &loc_eng_data, AGpsExtType agpsType,
                     const char* apn, AGpsBearerType bearerType)
{
    ENTRY_LOG_CALLFLOW();
    INIT_CHECK(loc_eng_data.adapter && loc_eng_data.agps_status_cb,
               return -1);

    if (apn == NULL)
    {
        LOC_LOGE("APN Name NULL\n");
        return 0;
    }

    LOC_LOGD("loc_eng_agps_open APN name = [%s]", apn);

    int apn_len = smaller_of(strlen (apn), MAX_APN_LEN);
    AgpsStateMachine* sm = getAgpsStateMachine(loc_eng_data, agpsType);

    loc_eng_data.adapter->sendMsg(
        new LocEngAtlOpenSuccess(sm, apn, apn_len, bearerType));

    EXIT_LOG(%d, 0);
    return 0;
}

/*===========================================================================
FUNCTION    loc_eng_agps_closed

DESCRIPTION
   This function is called when on-demand data connection closing is done.
It should inform engine about the data close result.

DEPENDENCIES
   NONE

RETURN VALUE
   0

SIDE EFFECTS
   N/A

===========================================================================*/
int loc_eng_agps_closed(loc_eng_data_s_type &loc_eng_data, AGpsExtType agpsType)
{
    ENTRY_LOG_CALLFLOW();
    INIT_CHECK(loc_eng_data.adapter && loc_eng_data.agps_status_cb,
               return -1);

    AgpsStateMachine* sm = getAgpsStateMachine(loc_eng_data, agpsType);
    loc_eng_data.adapter->sendMsg(new LocEngAtlClosed(sm));

    EXIT_LOG(%d, 0);
    return 0;
}

/*===========================================================================
FUNCTION    loc_eng_agps_open_failed

DESCRIPTION
   This function is called when on-demand data connection opening has failed.
It should inform engine about the data open result.

DEPENDENCIES
   NONE

RETURN VALUE
   0

SIDE EFFECTS
   N/A

===========================================================================*/
int loc_eng_agps_open_failed(loc_eng_data_s_type &loc_eng_data, AGpsExtType agpsType)
{
    ENTRY_LOG_CALLFLOW();
    INIT_CHECK(loc_eng_data.adapter && loc_eng_data.agps_status_cb,
               return -1);

    AgpsStateMachine* sm = getAgpsStateMachine(loc_eng_data, agpsType);
    loc_eng_data.adapter->sendMsg(new LocEngAtlOpenFailed(sm));

    EXIT_LOG(%d, 0);
    return 0;
}

/*===========================================================================

FUNCTION resolve_in_addr

DESCRIPTION
   Translates a hostname to in_addr struct

DEPENDENCIES
   n/a

RETURN VALUE
   TRUE if successful

SIDE EFFECTS
   n/a

===========================================================================*/
static boolean resolve_in_addr(const char *host_addr, struct in_addr *in_addr_ptr)
{
    ENTRY_LOG();
    boolean ret_val = TRUE;

    struct hostent             *hp;
    hp = gethostbyname(host_addr);
    if (hp != NULL) /* DNS OK */
    {
        memcpy(in_addr_ptr, hp->h_addr_list[0], hp->h_length);
    }
    else
    {
        /* Try IP representation */
        if (inet_aton(host_addr, in_addr_ptr) == 0)
        {
            /* IP not valid */
            LOC_LOGE("DNS query on '%s' failed\n", host_addr);
            ret_val = FALSE;
        }
    }

    EXIT_LOG(%s, loc_logger_boolStr[ret_val!=0]);
    return ret_val;
}

/*===========================================================================
FUNCTION    loc_eng_set_server

DESCRIPTION
   This is used to set the default AGPS server. Server address is obtained
   from gps.conf.

DEPENDENCIES
   NONE

RETURN VALUE
   0

SIDE EFFECTS
   N/A

===========================================================================*/
static int loc_eng_set_server(loc_eng_data_s_type &loc_eng_data,
                              LocServerType type, const char* hostname, int port)
{
    ENTRY_LOG();
    int ret = 0;
    LocEngAdapter* adapter = loc_eng_data.adapter;

    if (LOC_AGPS_SUPL_SERVER == type) {
        char url[MAX_URL_LEN];
        unsigned int len = 0;
        const char nohost[] = "NONE";
        if (hostname == NULL ||
            strncasecmp(nohost, hostname, sizeof(nohost)) == 0) {
            url[0] = NULL;
        } else {
            len = snprintf(url, sizeof(url), "%s:%u", hostname, (unsigned) port);
        }

        if (sizeof(url) > len) {
            adapter->sendMsg(new LocEngSetServerUrl(adapter, url, len));
        }
    } else if (LOC_AGPS_CDMA_PDE_SERVER == type ||
               LOC_AGPS_CUSTOM_PDE_SERVER == type ||
               LOC_AGPS_MPC_SERVER == type) {
        struct in_addr addr;
        if (!resolve_in_addr(hostname, &addr))
        {
            LOC_LOGE("loc_eng_set_server, hostname %s cannot be resolved.\n", hostname);
            ret = -2;
        } else {
            unsigned int ip = htonl(addr.s_addr);
            adapter->sendMsg(new LocEngSetServerIpv4(adapter, ip, port, type));
        }
    } else {
        LOC_LOGE("loc_eng_set_server, type %d cannot be resolved.\n", type);
    }

    EXIT_LOG(%d, ret);
    return ret;
}

/*===========================================================================
FUNCTION    loc_eng_set_server_proxy

DESCRIPTION
   If loc_eng_set_server is called before loc_eng_init, it doesn't work. This
   proxy buffers server settings and calls loc_eng_set_server when the client is
   open.

DEPENDENCIES
   NONE

RETURN VALUE
   0

SIDE EFFECTS
   N/A

===========================================================================*/
int loc_eng_set_server_proxy(loc_eng_data_s_type &loc_eng_data,
                             LocServerType type,
                             const char* hostname, int port)
{
    ENTRY_LOG_CALLFLOW();
    int ret_val = 0;

    LOC_LOGV("save the address, type: %d, hostname: %s, port: %d",
             (int) type, hostname, port);
    switch (type)
    {
    case LOC_AGPS_SUPL_SERVER:
        strlcpy(loc_eng_data.supl_host_buf, hostname,
                sizeof(loc_eng_data.supl_host_buf));
        loc_eng_data.supl_port_buf = port;
        loc_eng_data.supl_host_set = 1;
        break;
    case LOC_AGPS_CDMA_PDE_SERVER:
        strlcpy(loc_eng_data.c2k_host_buf, hostname,
                sizeof(loc_eng_data.c2k_host_buf));
        loc_eng_data.c2k_port_buf = port;
        loc_eng_data.c2k_host_set = 1;
        break;
    default:
        LOC_LOGE("loc_eng_set_server_proxy, unknown server type = %d", (int) type);
    }

    if (NULL != loc_eng_data.adapter)
    {
        ret_val = loc_eng_set_server(loc_eng_data, type, hostname, port);
    }

    EXIT_LOG(%d, ret_val);
    return ret_val;
}

/*===========================================================================
FUNCTION    loc_eng_agps_ril_update_network_availability

DESCRIPTION
   Sets data call allow vs disallow flag to modem
   This is the only member of sLocEngAGpsRilInterface implemented.

DEPENDENCIES
   None

RETURN VALUE
   0: success

SIDE EFFECTS
   N/A

===========================================================================*/
void loc_eng_agps_ril_update_network_availability(loc_eng_data_s_type &loc_eng_data,
                                                  int available, const char* apn)
{
    ENTRY_LOG_CALLFLOW();

    //This is to store the status of data availability over the network.
    //If GPS is not enabled, the INIT_CHECK will fail and the modem will
    //not be updated with the network's availability. Since the data status
    //can change before GPS is enabled the, storing the status will enable
    //us to inform the modem after GPS is enabled
    agpsStatus = available;

    INIT_CHECK(loc_eng_data.adapter, return);
    if (apn != NULL)
    {
        LOC_LOGD("loc_eng_agps_ril_update_network_availability: APN Name = [%s]\n", apn);
        int apn_len = smaller_of(strlen (apn), MAX_APN_LEN);
        LocEngAdapter* adapter = loc_eng_data.adapter;
        adapter->sendMsg(new LocEngEnableData(adapter, apn,  apn_len, available));
    }
    EXIT_LOG(%s, VOID_RET);
}

int loc_eng_agps_install_certificates(loc_eng_data_s_type &loc_eng_data,
                                      const DerEncodedCertificate* certificates,
                                      size_t numberOfCerts)
{
    ENTRY_LOG_CALLFLOW();
    int ret_val = AGPS_CERTIFICATE_OPERATION_SUCCESS;

    uint32_t slotBitMask = gps_conf.AGPS_CERT_WRITABLE_MASK;
    uint32_t slotCount = 0;
    for (uint32_t slotBitMaskCounter=slotBitMask; slotBitMaskCounter; slotCount++) {
        slotBitMaskCounter &= slotBitMaskCounter - 1;
    }
    LOC_LOGD("SlotBitMask=%u SlotCount=%u NumberOfCerts=%u",
             slotBitMask, slotCount, numberOfCerts);

    LocEngAdapter* adapter = loc_eng_data.adapter;

    if (numberOfCerts == 0) {
        LOC_LOGE("No certs to install, since numberOfCerts is zero");
        ret_val = AGPS_CERTIFICATE_OPERATION_SUCCESS;
    } else if (!adapter) {
        LOC_LOGE("adapter is null!");
        ret_val = AGPS_CERTIFICATE_ERROR_GENERIC;
    } else if (slotCount < numberOfCerts) {
        LOC_LOGE("Not enough cert slots (%u) to install %u certs!",
                 slotCount, numberOfCerts);
        ret_val = AGPS_CERTIFICATE_ERROR_TOO_MANY_CERTIFICATES;
    } else {
        for (int i=0; i < numberOfCerts; ++i)
        {
            if (certificates[i].length > AGPS_CERTIFICATE_MAX_LENGTH) {
                LOC_LOGE("cert#(%u) length of %u is too big! greater than %u",
                        certificates[i].length, AGPS_CERTIFICATE_MAX_LENGTH);
                ret_val = AGPS_CERTIFICATE_ERROR_GENERIC;
                break;
            }
        }

        if (ret_val == AGPS_CERTIFICATE_OPERATION_SUCCESS) {
            adapter->sendMsg(new LocEngInstallAGpsCert(adapter,
                                                       certificates,
                                                       numberOfCerts,
                                                       slotBitMask));
        }
    }

    EXIT_LOG(%d, ret_val);
    return ret_val;
}

void loc_eng_configuration_update (loc_eng_data_s_type &loc_eng_data,
                                   const char* config_data, int32_t length)
{
    ENTRY_LOG_CALLFLOW();

    if (config_data && length > 0) {
        loc_gps_cfg_s_type gps_conf_tmp = gps_conf;
        UTIL_UPDATE_CONF(config_data, length, gps_conf_table);
        LocEngAdapter* adapter = loc_eng_data.adapter;

        // it is possible that HAL is not init'ed at this time
        if (adapter) {
            if (gps_conf_tmp.SUPL_VER != gps_conf.SUPL_VER) {
                adapter->sendMsg(new LocEngSuplVer(adapter, gps_conf.SUPL_VER));
            }
            if (gps_conf_tmp.LPP_PROFILE != gps_conf.LPP_PROFILE) {
                adapter->sendMsg(new LocEngLppConfig(adapter, gps_conf.LPP_PROFILE));
            }
            if (gps_conf_tmp.A_GLONASS_POS_PROTOCOL_SELECT != gps_conf.A_GLONASS_POS_PROTOCOL_SELECT) {
                adapter->sendMsg(new LocEngAGlonassProtocol(adapter,
                                                            gps_conf.A_GLONASS_POS_PROTOCOL_SELECT));
            }
            if (gps_conf_tmp.SUPL_MODE != gps_conf.SUPL_MODE) {
                adapter->sendMsg(new LocEngSuplMode(adapter->getUlpProxy()));
            }
        }

        gps_conf_tmp.SUPL_VER = gps_conf.SUPL_VER;
        gps_conf_tmp.LPP_PROFILE = gps_conf.LPP_PROFILE;
        gps_conf_tmp.A_GLONASS_POS_PROTOCOL_SELECT = gps_conf.A_GLONASS_POS_PROTOCOL_SELECT;
        gps_conf_tmp.GPS_LOCK = gps_conf.GPS_LOCK;
        gps_conf = gps_conf_tmp;
    }

    EXIT_LOG(%s, VOID_RET);
}

/*===========================================================================
FUNCTION    loc_eng_report_status

DESCRIPTION
   Reports GPS engine state to Java layer.

DEPENDENCIES
   N/A

RETURN VALUE
   N/A

SIDE EFFECTS
   N/A

===========================================================================*/
static void loc_eng_report_status (loc_eng_data_s_type &loc_eng_data, GpsStatusValue status)
{
    ENTRY_LOG();
    // Switch from WAIT to MUTE, for "engine on" or "session begin" event
    if (status == GPS_STATUS_SESSION_BEGIN || status == GPS_STATUS_ENGINE_ON)
    {
        if (loc_eng_data.mute_session_state == LOC_MUTE_SESS_WAIT)
        {
            LOC_LOGD("loc_eng_report_status: mute_session_state changed from WAIT to IN SESSION");
            loc_eng_data.mute_session_state = LOC_MUTE_SESS_IN_SESSION;
        }
    }

    // Switch off MUTE session
    if (loc_eng_data.mute_session_state == LOC_MUTE_SESS_IN_SESSION &&
        (status == GPS_STATUS_SESSION_END || status == GPS_STATUS_ENGINE_OFF))
    {
        LOC_LOGD("loc_eng_report_status: mute_session_state changed from IN SESSION to NONE");
        loc_eng_data.mute_session_state = LOC_MUTE_SESS_NONE;
    }

    // Session End is not reported during Android navigating state
    boolean navigating = loc_eng_data.adapter->isInSession();
    if (status != GPS_STATUS_NONE &&
        !(status == GPS_STATUS_SESSION_END && navigating) &&
        !(status == GPS_STATUS_SESSION_BEGIN && !navigating))
    {
        if (loc_eng_data.mute_session_state != LOC_MUTE_SESS_IN_SESSION)
        {
            // Inform GpsLocationProvider about mNavigating status
            loc_inform_gps_status(loc_eng_data, status);
        }
        else {
            LOC_LOGD("loc_eng_report_status: muting the status report.");
        }
    }

    // Only keeps ENGINE ON/OFF in engine_status
    if (status == GPS_STATUS_ENGINE_ON || status == GPS_STATUS_ENGINE_OFF)
    {
        loc_eng_data.engine_status = status;
    }

    // Only keeps SESSION BEGIN/END in fix_session_status
    if (status == GPS_STATUS_SESSION_BEGIN || status == GPS_STATUS_SESSION_END)
    {
        loc_eng_data.fix_session_status = status;
    }
    EXIT_LOG(%s, VOID_RET);
}

/*===========================================================================
FUNCTION loc_eng_handle_engine_down
         loc_eng_handle_engine_up

DESCRIPTION
   Calls this function when it is detected that modem restart is happening.
   Either we detected the modem is down or received modem up event.
   This must be called from the deferred thread to avoid race condition.

DEPENDENCIES
   None

RETURN VALUE
   None

SIDE EFFECTS
   N/A

===========================================================================*/
void loc_eng_handle_engine_down(loc_eng_data_s_type &loc_eng_data)
{
    ENTRY_LOG();
    loc_eng_ni_reset_on_engine_restart(loc_eng_data);
    loc_eng_report_status(loc_eng_data, GPS_STATUS_ENGINE_OFF);
    EXIT_LOG(%s, VOID_RET);
}

void loc_eng_handle_engine_up(loc_eng_data_s_type &loc_eng_data)
{
    ENTRY_LOG();
    loc_eng_reinit(loc_eng_data);

    loc_eng_data.adapter->requestPowerVote();

    if (loc_eng_data.agps_status_cb != NULL) {
        if (loc_eng_data.agnss_nif)
            loc_eng_data.agnss_nif->dropAllSubscribers();
        if (loc_eng_data.internet_nif)
            loc_eng_data.internet_nif->dropAllSubscribers();

        loc_eng_agps_reinit(loc_eng_data);
    }

    // modem is back up.  If we crashed in the middle of navigating, we restart.
    if (loc_eng_data.adapter->isInSession()) {
        // This sets the copy in adapter to modem
        loc_eng_data.adapter->setInSession(false);
        loc_eng_data.adapter->sendMsg(new LocEngStartFix(loc_eng_data.adapter));
    }
    EXIT_LOG(%s, VOID_RET);
}

#ifdef USE_GLIB
/*===========================================================================
FUNCTION set_sched_policy

DESCRIPTION
   Local copy of this function which bypasses android set_sched_policy

DEPENDENCIES
   None

RETURN VALUE
   0

SIDE EFFECTS
   N/A

===========================================================================*/
static int set_sched_policy(int tid, SchedPolicy policy)
{
    return 0;
}
#endif /* USE_GLIB */

/*===========================================================================
FUNCTION    loc_eng_read_config

DESCRIPTION
   Initiates the reading of the gps config file stored in /etc dir

DEPENDENCIES
   None

RETURN VALUE
   0: success

SIDE EFFECTS
   N/A

===========================================================================*/
int loc_eng_read_config(void)
{
    ENTRY_LOG_CALLFLOW();
    if(configAlreadyRead == false)
    {
      // Initialize our defaults before reading of configuration file overwrites them.
      loc_default_parameters();
      // We only want to parse the conf file once. This is a good place to ensure that.
      // In fact one day the conf file should go into context.
      UTIL_READ_CONF(GPS_CONF_FILE, gps_conf_table);
      UTIL_READ_CONF(SAP_CONF_FILE, sap_conf_table);
      configAlreadyRead = true;
    } else {
      LOC_LOGV("GPS Config file has already been read\n");
    }

    EXIT_LOG(%d, 0);
    return 0;
}

/*===========================================================================
FUNCTION    loc_eng_gps_measurement_init

DESCRIPTION
   Initialize gps measurement module.

DEPENDENCIES
   N/A

RETURN VALUE
   0: success

SIDE EFFECTS
   N/A

===========================================================================*/
int loc_eng_gps_measurement_init(loc_eng_data_s_type &loc_eng_data,
                                 GpsMeasurementCallbacks* callbacks)
{
    ENTRY_LOG_CALLFLOW();

    STATE_CHECK((NULL == loc_eng_data.gps_measurement_cb),
                "gps measurement already initialized",
                return GPS_MEASUREMENT_ERROR_ALREADY_INIT);
    STATE_CHECK((callbacks != NULL),
                "callbacks can not be NULL",
                return GPS_MEASUREMENT_ERROR_GENERIC);
    STATE_CHECK(loc_eng_data.adapter,
                "GpsInterface must be initialized first",
                return GPS_MEASUREMENT_ERROR_GENERIC);

    // updated the mask
    LOC_API_ADAPTER_EVENT_MASK_T event = LOC_API_ADAPTER_BIT_GNSS_MEASUREMENT;
    loc_eng_data.adapter->sendMsg(new LocEngUpdateRegistrationMask(
                                                        &loc_eng_data,
                                                        event,
                                                        LOC_REGISTRATION_MASK_ENABLED));
    // set up the callback
    loc_eng_data.gps_measurement_cb = callbacks->measurement_callback;
    LOC_LOGD ("%s, event masks updated successfully", __func__);

    return GPS_MEASUREMENT_OPERATION_SUCCESS;
}

/*===========================================================================
FUNCTION    loc_eng_gps_measurement_close

DESCRIPTION
   Close gps measurement module.

DEPENDENCIES
   N/A

RETURN VALUE
   N/A

SIDE EFFECTS
   N/A

===========================================================================*/
void loc_eng_gps_measurement_close(loc_eng_data_s_type &loc_eng_data)
{
    ENTRY_LOG_CALLFLOW();

    INIT_CHECK(loc_eng_data.adapter, return);

    // updated the mask
    LOC_API_ADAPTER_EVENT_MASK_T event = LOC_API_ADAPTER_BIT_GNSS_MEASUREMENT;
    loc_eng_data.adapter->sendMsg(new LocEngUpdateRegistrationMask(
                                                          &loc_eng_data,
                                                          event,
                                                          LOC_REGISTRATION_MASK_DISABLED));
    // set up the callback
    loc_eng_data.gps_measurement_cb = NULL;
    EXIT_LOG(%d, 0);
}
