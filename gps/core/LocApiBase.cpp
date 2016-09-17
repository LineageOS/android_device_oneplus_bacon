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
 *
 */
#define LOG_NDDEBUG 0
#define LOG_TAG "LocSvc_LocApiBase"

#include <dlfcn.h>
#include <LocApiBase.h>
#include <LocAdapterBase.h>
#include <log_util.h>
#include <LocDualContext.h>

namespace loc_core {

#define TO_ALL_LOCADAPTERS(call) TO_ALL_ADAPTERS(mLocAdapters, (call))
#define TO_1ST_HANDLING_LOCADAPTERS(call) TO_1ST_HANDLING_ADAPTER(mLocAdapters, (call))

int hexcode(char *hexstring, int string_size,
            const char *data, int data_size)
{
   int i;
   for (i = 0; i < data_size; i++)
   {
      char ch = data[i];
      if (i*2 + 3 <= string_size)
      {
         snprintf(&hexstring[i*2], 3, "%02X", ch);
      }
      else {
         break;
      }
   }
   return i;
}

int decodeAddress(char *addr_string, int string_size,
                   const char *data, int data_size)
{
    const char addr_prefix = 0x91;
    int i, idxOutput = 0;

    if (!data || !addr_string) { return 0; }

    if (data[0] != addr_prefix)
    {
        LOC_LOGW("decodeAddress: address prefix is not 0x%x but 0x%x", addr_prefix, data[0]);
        addr_string[0] = '\0';
        return 0; // prefix not correct
    }

    for (i = 1; i < data_size; i++)
    {
        unsigned char ch = data[i], low = ch & 0x0F, hi = ch >> 4;
        if (low <= 9 && idxOutput < string_size - 1) { addr_string[idxOutput++] = low + '0'; }
        if (hi <= 9 && idxOutput < string_size - 1) { addr_string[idxOutput++] = hi + '0'; }
    }

    addr_string[idxOutput] = '\0'; // Terminates the string

    return idxOutput;
}

struct LocSsrMsg : public LocMsg {
    LocApiBase* mLocApi;
    inline LocSsrMsg(LocApiBase* locApi) :
        LocMsg(), mLocApi(locApi)
    {
        locallog();
    }
    inline virtual void proc() const {
        mLocApi->close();
        mLocApi->open(mLocApi->getEvtMask());
    }
    inline void locallog() {
        LOC_LOGV("LocSsrMsg");
    }
    inline virtual void log() {
        locallog();
    }
};

struct LocOpenMsg : public LocMsg {
    LocApiBase* mLocApi;
    LOC_API_ADAPTER_EVENT_MASK_T mMask;
    inline LocOpenMsg(LocApiBase* locApi,
                      LOC_API_ADAPTER_EVENT_MASK_T mask) :
        LocMsg(), mLocApi(locApi), mMask(mask)
    {
        locallog();
    }
    inline virtual void proc() const {
        mLocApi->open(mMask);
    }
    inline void locallog() {
        LOC_LOGV("%s:%d]: LocOpen Mask: %x\n",
                 __func__, __LINE__, mMask);
    }
    inline virtual void log() {
        locallog();
    }
};

LocApiBase::LocApiBase(const MsgTask* msgTask,
                       LOC_API_ADAPTER_EVENT_MASK_T excludedMask,
                       ContextBase* context) :
    mExcludedMask(excludedMask), mMsgTask(msgTask),
    mMask(0), mSupportedMsg(0), mContext(context)
{
    memset(mLocAdapters, 0, sizeof(mLocAdapters));
}

LOC_API_ADAPTER_EVENT_MASK_T LocApiBase::getEvtMask()
{
    LOC_API_ADAPTER_EVENT_MASK_T mask = 0;

    TO_ALL_LOCADAPTERS(mask |= mLocAdapters[i]->getEvtMask());

    return mask & ~mExcludedMask;
}

bool LocApiBase::isInSession()
{
    bool inSession = false;

    for (int i = 0;
         !inSession && i < MAX_ADAPTERS && NULL != mLocAdapters[i];
         i++) {
        inSession = mLocAdapters[i]->isInSession();
    }

    return inSession;
}

void LocApiBase::addAdapter(LocAdapterBase* adapter)
{
    for (int i = 0; i < MAX_ADAPTERS && mLocAdapters[i] != adapter; i++) {
        if (mLocAdapters[i] == NULL) {
            mLocAdapters[i] = adapter;
            mMsgTask->sendMsg(new LocOpenMsg(this,
                                             (adapter->getEvtMask())));
            break;
        }
    }
}

void LocApiBase::removeAdapter(LocAdapterBase* adapter)
{
    for (int i = 0;
         i < MAX_ADAPTERS && NULL != mLocAdapters[i];
         i++) {
        if (mLocAdapters[i] == adapter) {
            mLocAdapters[i] = NULL;

            // shift the rest of the adapters up so that the pointers
            // in the array do not have holes.  This should be more
            // performant, because the array maintenance is much much
            // less frequent than event handlings, which need to linear
            // search all the adapters
            int j = i;
            while (++i < MAX_ADAPTERS && mLocAdapters[i] != NULL);

            // i would be MAX_ADAPTERS or point to a NULL
            i--;
            // i now should point to a none NULL adapter within valid
            // range although i could be equal to j, but it won't hurt.
            // No need to check it, as it gains nothing.
            mLocAdapters[j] = mLocAdapters[i];
            // this makes sure that we exit the for loop
            mLocAdapters[i] = NULL;

            // if we have an empty list of adapters
            if (0 == i) {
                close();
            } else {
                // else we need to remove the bit
                mMsgTask->sendMsg(new LocOpenMsg(this, getEvtMask()));
            }
        }
    }
}

void LocApiBase::updateEvtMask()
{
    mMsgTask->sendMsg(new LocOpenMsg(this, getEvtMask()));
}

void LocApiBase::handleEngineUpEvent()
{
    // This will take care of renegotiating the loc handle
    mMsgTask->sendMsg(new LocSsrMsg(this));

    LocDualContext::injectFeatureConfig(mContext);

    // loop through adapters, and deliver to all adapters.
    TO_ALL_LOCADAPTERS(mLocAdapters[i]->handleEngineUpEvent());
}

void LocApiBase::handleEngineDownEvent()
{
    // loop through adapters, and deliver to all adapters.
    TO_ALL_LOCADAPTERS(mLocAdapters[i]->handleEngineDownEvent());
}

void LocApiBase::reportPosition(UlpLocation &location,
                                GpsLocationExtended &locationExtended,
                                void* locationExt,
                                enum loc_sess_status status,
                                LocPosTechMask loc_technology_mask)
{
    // print the location info before delivering
    LOC_LOGV("flags: %d\n  source: %d\n  latitude: %f\n  longitude: %f\n  "
             "altitude: %f\n  speed: %f\n  bearing: %f\n  accuracy: %f\n  "
             "timestamp: %lld\n  rawDataSize: %d\n  rawData: %p\n  "
             "Session status: %d\n Technology mask: %u",
             location.gpsLocation.flags, location.position_source,
             location.gpsLocation.latitude, location.gpsLocation.longitude,
             location.gpsLocation.altitude, location.gpsLocation.speed,
             location.gpsLocation.bearing, location.gpsLocation.accuracy,
             location.gpsLocation.timestamp, location.rawDataSize,
             location.rawData, status, loc_technology_mask);
    // loop through adapters, and deliver to all adapters.
    TO_ALL_LOCADAPTERS(
        mLocAdapters[i]->reportPosition(location,
                                        locationExtended,
                                        locationExt,
                                        status,
                                        loc_technology_mask)
    );
}

void LocApiBase::reportSv(HaxxSvStatus &svStatus,
                  GpsLocationExtended &locationExtended,
                  void* svExt)
{
    // print the SV info before delivering
    LOC_LOGV("num sv: %d\n  ephemeris mask: %dxn  almanac mask: %x\n  gps/glo/bds in use"
             " mask: %x/%x/%x\n      sv: prn         snr       elevation      azimuth",
             svStatus.num_svs, svStatus.ephemeris_mask,
             svStatus.almanac_mask, svStatus.gps_used_in_fix_mask,
             svStatus.glo_used_in_fix_mask, svStatus.bds_used_in_fix_mask);
    for (int i = 0; i < svStatus.num_svs && i < GPS_MAX_SVS; i++) {
        LOC_LOGV("   %d:   %d    %f    %f    %f",
                 i,
                 svStatus.sv_list[i].prn,
                 svStatus.sv_list[i].snr,
                 svStatus.sv_list[i].elevation,
                 svStatus.sv_list[i].azimuth);
    }
    // loop through adapters, and deliver to all adapters.
    TO_ALL_LOCADAPTERS(
        mLocAdapters[i]->reportSv(svStatus,
                                     locationExtended,
                                     svExt)
    );
}

void LocApiBase::reportStatus(GpsStatusValue status)
{
    // loop through adapters, and deliver to all adapters.
    TO_ALL_LOCADAPTERS(mLocAdapters[i]->reportStatus(status));
}

void LocApiBase::reportNmea(const char* nmea, int length)
{
    // loop through adapters, and deliver to all adapters.
    TO_ALL_LOCADAPTERS(mLocAdapters[i]->reportNmea(nmea, length));
}

void LocApiBase::reportXtraServer(const char* url1, const char* url2,
                                  const char* url3, const int maxlength)
{
    // loop through adapters, and deliver to the first handling adapter.
    TO_1ST_HANDLING_LOCADAPTERS(mLocAdapters[i]->reportXtraServer(url1, url2, url3, maxlength));

}

void LocApiBase::requestXtraData()
{
    // loop through adapters, and deliver to the first handling adapter.
    TO_1ST_HANDLING_LOCADAPTERS(mLocAdapters[i]->requestXtraData());
}

void LocApiBase::requestTime()
{
    // loop through adapters, and deliver to the first handling adapter.
    TO_1ST_HANDLING_LOCADAPTERS(mLocAdapters[i]->requestTime());
}

void LocApiBase::requestLocation()
{
    // loop through adapters, and deliver to the first handling adapter.
    TO_1ST_HANDLING_LOCADAPTERS(mLocAdapters[i]->requestLocation());
}

void LocApiBase::requestATL(int connHandle, AGpsType agps_type)
{
    // loop through adapters, and deliver to the first handling adapter.
    TO_1ST_HANDLING_LOCADAPTERS(mLocAdapters[i]->requestATL(connHandle, agps_type));
}

void LocApiBase::releaseATL(int connHandle)
{
    // loop through adapters, and deliver to the first handling adapter.
    TO_1ST_HANDLING_LOCADAPTERS(mLocAdapters[i]->releaseATL(connHandle));
}

void LocApiBase::requestSuplES(int connHandle)
{
    // loop through adapters, and deliver to the first handling adapter.
    TO_1ST_HANDLING_LOCADAPTERS(mLocAdapters[i]->requestSuplES(connHandle));
}

void LocApiBase::reportDataCallOpened()
{
    // loop through adapters, and deliver to the first handling adapter.
    TO_1ST_HANDLING_LOCADAPTERS(mLocAdapters[i]->reportDataCallOpened());
}

void LocApiBase::reportDataCallClosed()
{
    // loop through adapters, and deliver to the first handling adapter.
    TO_1ST_HANDLING_LOCADAPTERS(mLocAdapters[i]->reportDataCallClosed());
}

void LocApiBase::requestNiNotify(GpsNiNotification &notify, const void* data)
{
    // loop through adapters, and deliver to the first handling adapter.
    TO_1ST_HANDLING_LOCADAPTERS(mLocAdapters[i]->requestNiNotify(notify, data));
}

void LocApiBase::saveSupportedMsgList(uint64_t supportedMsgList)
{
    mSupportedMsg = supportedMsgList;
}

void* LocApiBase :: getSibling()
    DEFAULT_IMPL(NULL)

LocApiProxyBase* LocApiBase :: getLocApiProxy()
    DEFAULT_IMPL(NULL)

void LocApiBase::reportGpsMeasurementData(GpsData &gpsMeasurementData)
{
    // loop through adapters, and deliver to all adapters.
    TO_ALL_LOCADAPTERS(mLocAdapters[i]->reportGpsMeasurementData(gpsMeasurementData));
}

enum loc_api_adapter_err LocApiBase::
   open(LOC_API_ADAPTER_EVENT_MASK_T mask)
DEFAULT_IMPL(LOC_API_ADAPTER_ERR_SUCCESS)

enum loc_api_adapter_err LocApiBase::
    close()
DEFAULT_IMPL(LOC_API_ADAPTER_ERR_SUCCESS)

enum loc_api_adapter_err LocApiBase::
    startFix(const LocPosMode& posMode)
DEFAULT_IMPL(LOC_API_ADAPTER_ERR_SUCCESS)

enum loc_api_adapter_err LocApiBase::
    stopFix()
DEFAULT_IMPL(LOC_API_ADAPTER_ERR_SUCCESS)

enum loc_api_adapter_err LocApiBase::
    deleteAidingData(GpsAidingData f)
DEFAULT_IMPL(LOC_API_ADAPTER_ERR_SUCCESS)

enum loc_api_adapter_err LocApiBase::
    enableData(int enable)
DEFAULT_IMPL(LOC_API_ADAPTER_ERR_SUCCESS)

enum loc_api_adapter_err LocApiBase::
    setAPN(char* apn, int len)
DEFAULT_IMPL(LOC_API_ADAPTER_ERR_SUCCESS)

enum loc_api_adapter_err LocApiBase::
    injectPosition(double latitude, double longitude, float accuracy)
DEFAULT_IMPL(LOC_API_ADAPTER_ERR_SUCCESS)

enum loc_api_adapter_err LocApiBase::
    setTime(GpsUtcTime time, int64_t timeReference, int uncertainty)
DEFAULT_IMPL(LOC_API_ADAPTER_ERR_SUCCESS)

enum loc_api_adapter_err LocApiBase::
    setXtraData(char* data, int length)
DEFAULT_IMPL(LOC_API_ADAPTER_ERR_SUCCESS)

enum loc_api_adapter_err LocApiBase::
    requestXtraServer()
DEFAULT_IMPL(LOC_API_ADAPTER_ERR_SUCCESS)

enum loc_api_adapter_err LocApiBase::
   atlOpenStatus(int handle, int is_succ, char* apn,
                 AGpsBearerType bear, AGpsType agpsType)
DEFAULT_IMPL(LOC_API_ADAPTER_ERR_SUCCESS)

enum loc_api_adapter_err LocApiBase::
    atlCloseStatus(int handle, int is_succ)
DEFAULT_IMPL(LOC_API_ADAPTER_ERR_SUCCESS)

enum loc_api_adapter_err LocApiBase::
    setPositionMode(const LocPosMode& posMode)
DEFAULT_IMPL(LOC_API_ADAPTER_ERR_SUCCESS)

enum loc_api_adapter_err LocApiBase::
    setServer(const char* url, int len)
DEFAULT_IMPL(LOC_API_ADAPTER_ERR_SUCCESS)

enum loc_api_adapter_err LocApiBase::
    setServer(unsigned int ip, int port,
              LocServerType type)
DEFAULT_IMPL(LOC_API_ADAPTER_ERR_SUCCESS)

enum loc_api_adapter_err LocApiBase::
    informNiResponse(GpsUserResponseType userResponse,
                     const void* passThroughData)
DEFAULT_IMPL(LOC_API_ADAPTER_ERR_SUCCESS)

enum loc_api_adapter_err LocApiBase::
    setSUPLVersion(uint32_t version)
DEFAULT_IMPL(LOC_API_ADAPTER_ERR_SUCCESS)

enum loc_api_adapter_err LocApiBase::
    setLPPConfig(uint32_t profile)
DEFAULT_IMPL(LOC_API_ADAPTER_ERR_SUCCESS)

enum loc_api_adapter_err LocApiBase::
    setSensorControlConfig(int sensorUsage,
                           int sensorProvider)
DEFAULT_IMPL(LOC_API_ADAPTER_ERR_SUCCESS)

enum loc_api_adapter_err LocApiBase::
    setSensorProperties(bool gyroBiasVarianceRandomWalk_valid,
                        float gyroBiasVarianceRandomWalk,
                        bool accelBiasVarianceRandomWalk_valid,
                        float accelBiasVarianceRandomWalk,
                        bool angleBiasVarianceRandomWalk_valid,
                        float angleBiasVarianceRandomWalk,
                        bool rateBiasVarianceRandomWalk_valid,
                        float rateBiasVarianceRandomWalk,
                        bool velocityBiasVarianceRandomWalk_valid,
                        float velocityBiasVarianceRandomWalk)
DEFAULT_IMPL(LOC_API_ADAPTER_ERR_SUCCESS)

enum loc_api_adapter_err LocApiBase::
    setSensorPerfControlConfig(int controlMode,
                               int accelSamplesPerBatch,
                               int accelBatchesPerSec,
                               int gyroSamplesPerBatch,
                               int gyroBatchesPerSec,
                               int accelSamplesPerBatchHigh,
                               int accelBatchesPerSecHigh,
                               int gyroSamplesPerBatchHigh,
                               int gyroBatchesPerSecHigh,
                               int algorithmConfig)
DEFAULT_IMPL(LOC_API_ADAPTER_ERR_SUCCESS)

enum loc_api_adapter_err LocApiBase::
    setExtPowerConfig(int isBatteryCharging)
DEFAULT_IMPL(LOC_API_ADAPTER_ERR_SUCCESS)

enum loc_api_adapter_err LocApiBase::
    setAGLONASSProtocol(unsigned long aGlonassProtocol)
DEFAULT_IMPL(LOC_API_ADAPTER_ERR_SUCCESS)

enum loc_api_adapter_err LocApiBase::
   getWwanZppFix(GpsLocation& zppLoc)
DEFAULT_IMPL(LOC_API_ADAPTER_ERR_SUCCESS)

enum loc_api_adapter_err LocApiBase::
   getBestAvailableZppFix(GpsLocation& zppLoc)
{
   memset(&zppLoc, 0, sizeof(zppLoc));
   DEFAULT_IMPL(LOC_API_ADAPTER_ERR_SUCCESS)
}

enum loc_api_adapter_err LocApiBase::
   getBestAvailableZppFix(GpsLocation & zppLoc, LocPosTechMask & tech_mask)
{
   memset(&zppLoc, 0, sizeof(zppLoc));
   memset(&tech_mask, 0, sizeof(tech_mask));
   DEFAULT_IMPL(LOC_API_ADAPTER_ERR_SUCCESS)
}

int LocApiBase::
    initDataServiceClient()
DEFAULT_IMPL(-1)

int LocApiBase::
    openAndStartDataCall()
DEFAULT_IMPL(-1)

void LocApiBase::
    stopDataCall()
DEFAULT_IMPL()

void LocApiBase::
    closeDataCall()
DEFAULT_IMPL()

int LocApiBase::
    setGpsLock(LOC_GPS_LOCK_MASK lock)
DEFAULT_IMPL(-1)

void LocApiBase::
    installAGpsCert(const DerEncodedCertificate* pData,
                    size_t length,
                    uint32_t slotBitMask)
DEFAULT_IMPL()

int LocApiBase::
    getGpsLock()
DEFAULT_IMPL(-1)

enum loc_api_adapter_err LocApiBase::
    setXtraVersionCheck(enum xtra_version_check check)
DEFAULT_IMPL(LOC_API_ADAPTER_ERR_SUCCESS)

int LocApiBase::
    updateRegistrationMask(LOC_API_ADAPTER_EVENT_MASK_T event,
                           loc_registration_mask_status isEnabled)
DEFAULT_IMPL(-1)

bool LocApiBase::
    gnssConstellationConfig()
DEFAULT_IMPL(false)

} // namespace loc_core
