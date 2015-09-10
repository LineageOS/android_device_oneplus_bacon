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
#ifndef LOC_API_ENG_ADAPTER_H
#define LOC_API_ENG_ADAPTER_H

#include <ctype.h>
#include <hardware/gps.h>
#include <loc.h>
#include <loc_eng_log.h>
#include <log_util.h>
#include <LocAdapterBase.h>
#include <LocDualContext.h>
#include <UlpProxyBase.h>
#include <platform_lib_includes.h>

#define MAX_URL_LEN 256

using namespace loc_core;

class LocEngAdapter;

class LocInternalAdapter : public LocAdapterBase {
    LocEngAdapter* mLocEngAdapter;
public:
    LocInternalAdapter(LocEngAdapter* adapter);

    virtual void reportPosition(UlpLocation &location,
                                GpsLocationExtended &locationExtended,
                                void* locationExt,
                                enum loc_sess_status status,
                                LocPosTechMask loc_technology_mask);
    virtual void reportSv(GpsSvStatus &svStatus,
                          GpsLocationExtended &locationExtended,
                          void* svExt);
    virtual void reportStatus(GpsStatusValue status);
    virtual void setPositionModeInt(LocPosMode& posMode);
    virtual void startFixInt();
    virtual void stopFixInt();
    virtual void getZppInt();
    virtual void setUlpProxy(UlpProxyBase* ulp);
    virtual void shutdown();
};

typedef void (*loc_msg_sender)(void* loc_eng_data_p, void* msgp);

class LocEngAdapter : public LocAdapterBase {
    void* mOwner;
    LocInternalAdapter* mInternalAdapter;
    UlpProxyBase* mUlp;
    LocPosMode mFixCriteria;
    bool mNavigating;
    // mPowerVote is encoded as
    // mPowerVote & 0x20 -- powerVoteRight
    // mPowerVote & 0x10 -- power On / Off
    unsigned int mPowerVote;
    static const unsigned int POWER_VOTE_RIGHT = 0x20;
    static const unsigned int POWER_VOTE_VALUE = 0x10;

public:
    bool mSupportsAgpsRequests;
    bool mSupportsPositionInjection;
    bool mSupportsTimeInjection;

    LocEngAdapter(LOC_API_ADAPTER_EVENT_MASK_T mask,
                  void* owner, ContextBase* context,
                  MsgTask::tCreate tCreator);
    virtual ~LocEngAdapter();

    virtual void setUlpProxy(UlpProxyBase* ulp);
    inline void requestUlp(unsigned long capabilities) {
        mContext->requestUlp(mInternalAdapter, capabilities);
    }
    inline LocInternalAdapter* getInternalAdapter() { return mInternalAdapter; }
    inline UlpProxyBase* getUlpProxy() { return mUlp; }
    inline void* getOwner() { return mOwner; }
    inline bool hasAgpsExtendedCapabilities() {
        return mContext->hasAgpsExtendedCapabilities();
    }
    inline bool hasCPIExtendedCapabilities() {
        return mContext->hasCPIExtendedCapabilities();
    }
    inline const MsgTask* getMsgTask() { return mMsgTask; }

    inline enum loc_api_adapter_err
        startFix()
    {
        return mLocApi->startFix(mFixCriteria);
    }
    inline enum loc_api_adapter_err
        stopFix()
    {
        return mLocApi->stopFix();
    }
    inline enum loc_api_adapter_err
        deleteAidingData(GpsAidingData f)
    {
        return mLocApi->deleteAidingData(f);
    }
    inline enum loc_api_adapter_err
        enableData(int enable)
    {
        return mLocApi->enableData(enable);
    }
    inline enum loc_api_adapter_err
        setAPN(char* apn, int len)
    {
        return mLocApi->setAPN(apn, len);
    }
    inline enum loc_api_adapter_err
        injectPosition(double latitude, double longitude, float accuracy)
    {
        return mLocApi->injectPosition(latitude, longitude, accuracy);
    }
    inline enum loc_api_adapter_err
        setXtraData(char* data, int length)
    {
        return mLocApi->setXtraData(data, length);
    }
    inline enum loc_api_adapter_err
        requestXtraServer()
    {
        return mLocApi->requestXtraServer();
    }
    inline enum loc_api_adapter_err
        atlOpenStatus(int handle, int is_succ, char* apn, AGpsBearerType bearer, AGpsType agpsType)
    {
        return mLocApi->atlOpenStatus(handle, is_succ, apn, bearer, agpsType);
    }
    inline enum loc_api_adapter_err
        atlCloseStatus(int handle, int is_succ)
    {
        return mLocApi->atlCloseStatus(handle, is_succ);
    }
    inline enum loc_api_adapter_err
        setPositionMode(const LocPosMode *posMode)
    {
        if (NULL != posMode) {
            mFixCriteria = *posMode;
        }
        return mLocApi->setPositionMode(mFixCriteria);
    }
    inline enum loc_api_adapter_err
        setServer(const char* url, int len)
    {
        return mLocApi->setServer(url, len);
    }
    inline enum loc_api_adapter_err
        setServer(unsigned int ip, int port,
                  LocServerType type)
    {
        return mLocApi->setServer(ip, port, type);
    }
    inline enum loc_api_adapter_err
        informNiResponse(GpsUserResponseType userResponse, const void* passThroughData)
    {
        return mLocApi->informNiResponse(userResponse, passThroughData);
    }
    inline enum loc_api_adapter_err
        setSUPLVersion(uint32_t version)
    {
        return mLocApi->setSUPLVersion(version);
    }
    inline enum loc_api_adapter_err
        setLPPConfig(uint32_t profile)
    {
        return mLocApi->setLPPConfig(profile);
    }
    inline enum loc_api_adapter_err
        setSensorControlConfig(int sensorUsage, int sensorProvider)
    {
        return mLocApi->setSensorControlConfig(sensorUsage, sensorProvider);
    }
    inline enum loc_api_adapter_err
        setSensorProperties(bool gyroBiasVarianceRandomWalk_valid, float gyroBiasVarianceRandomWalk,
                            bool accelBiasVarianceRandomWalk_valid, float accelBiasVarianceRandomWalk,
                            bool angleBiasVarianceRandomWalk_valid, float angleBiasVarianceRandomWalk,
                            bool rateBiasVarianceRandomWalk_valid, float rateBiasVarianceRandomWalk,
                            bool velocityBiasVarianceRandomWalk_valid, float velocityBiasVarianceRandomWalk)
    {
        return mLocApi->setSensorProperties(gyroBiasVarianceRandomWalk_valid, gyroBiasVarianceRandomWalk,
                                           accelBiasVarianceRandomWalk_valid, accelBiasVarianceRandomWalk,
                                           angleBiasVarianceRandomWalk_valid, angleBiasVarianceRandomWalk,
                                           rateBiasVarianceRandomWalk_valid, rateBiasVarianceRandomWalk,
                                           velocityBiasVarianceRandomWalk_valid, velocityBiasVarianceRandomWalk);
    }
    inline virtual enum loc_api_adapter_err
        setSensorPerfControlConfig(int controlMode, int accelSamplesPerBatch, int accelBatchesPerSec,
                            int gyroSamplesPerBatch, int gyroBatchesPerSec,
                            int accelSamplesPerBatchHigh, int accelBatchesPerSecHigh,
                            int gyroSamplesPerBatchHigh, int gyroBatchesPerSecHigh, int algorithmConfig)
    {
        return mLocApi->setSensorPerfControlConfig(controlMode, accelSamplesPerBatch, accelBatchesPerSec,
                                                  gyroSamplesPerBatch, gyroBatchesPerSec,
                                                  accelSamplesPerBatchHigh, accelBatchesPerSecHigh,
                                                  gyroSamplesPerBatchHigh, gyroBatchesPerSecHigh,
                                                  algorithmConfig);
    }
    inline virtual enum loc_api_adapter_err
        setExtPowerConfig(int isBatteryCharging)
    {
        return mLocApi->setExtPowerConfig(isBatteryCharging);
    }
    inline virtual enum loc_api_adapter_err
        setAGLONASSProtocol(unsigned long aGlonassProtocol)
    {
        return mLocApi->setAGLONASSProtocol(aGlonassProtocol);
    }
    inline virtual int initDataServiceClient()
    {
        return mLocApi->initDataServiceClient();
    }
    inline virtual int openAndStartDataCall()
    {
        return mLocApi->openAndStartDataCall();
    }
    inline virtual void stopDataCall()
    {
        mLocApi->stopDataCall();
    }
    inline virtual void closeDataCall()
    {
        mLocApi->closeDataCall();
    }
    inline enum loc_api_adapter_err
        getZpp(GpsLocation &zppLoc, LocPosTechMask &tech_mask)
    {
        return mLocApi->getBestAvailableZppFix(zppLoc, tech_mask);
    }
    enum loc_api_adapter_err setTime(GpsUtcTime time,
                                     int64_t timeReference,
                                     int uncertainty);
    enum loc_api_adapter_err setXtraVersionCheck(int check);
    inline virtual void installAGpsCert(const DerEncodedCertificate* pData,
                                        size_t length,
                                        uint32_t slotBitMask)
    {
        mLocApi->installAGpsCert(pData, length, slotBitMask);
    }
    virtual void handleEngineDownEvent();
    virtual void handleEngineUpEvent();
    virtual void reportPosition(UlpLocation &location,
                                GpsLocationExtended &locationExtended,
                                void* locationExt,
                                enum loc_sess_status status,
                                LocPosTechMask loc_technology_mask);
    virtual void reportSv(GpsSvStatus &svStatus,
                          GpsLocationExtended &locationExtended,
                          void* svExt);
    virtual void reportStatus(GpsStatusValue status);
    virtual void reportNmea(const char* nmea, int length);
    virtual bool reportXtraServer(const char* url1, const char* url2,
                                  const char* url3, const int maxlength);
    virtual bool requestXtraData();
    virtual bool requestTime();
    virtual bool requestATL(int connHandle, AGpsType agps_type);
    virtual bool releaseATL(int connHandle);
    virtual bool requestNiNotify(GpsNiNotification &notify, const void* data);
    virtual bool requestSuplES(int connHandle);
    virtual bool reportDataCallOpened();
    virtual bool reportDataCallClosed();

    inline const LocPosMode& getPositionMode() const
    {return mFixCriteria;}
    inline virtual bool isInSession()
    { return mNavigating; }
    void setInSession(bool inSession);

    // Permit/prohibit power voting
    inline void setPowerVoteRight(bool powerVoteRight) {
        mPowerVote = powerVoteRight ? (mPowerVote | POWER_VOTE_RIGHT) :
                                      (mPowerVote & ~POWER_VOTE_RIGHT);
    }
    inline bool getPowerVoteRight() const {
        return (mPowerVote & POWER_VOTE_RIGHT) != 0 ;
    }
    // Set the power voting up/down and do actual operation if permitted
    inline void setPowerVote(bool powerOn) {
        mPowerVote = powerOn ? (mPowerVote | POWER_VOTE_VALUE) :
                               (mPowerVote & ~POWER_VOTE_VALUE);
        requestPowerVote();
    }
    inline bool getPowerVote() const {
        return (mPowerVote & POWER_VOTE_VALUE) != 0 ;
    }
    // Do power voting according to last settings if permitted
    void requestPowerVote();

    /*Values for lock
      1 = Do not lock any position sessions
      2 = Lock MI position sessions
      3 = Lock MT position sessions
      4 = Lock all position sessions
    */
    inline int setGpsLock(LOC_GPS_LOCK_MASK lock)
    {
        return mLocApi->setGpsLock(lock);
    }

    int setGpsLockMsg(LOC_GPS_LOCK_MASK lock);

    /*
      Returns
      Current value of GPS lock on success
      -1 on failure
     */
    inline int getGpsLock()
    {
        return mLocApi->getGpsLock();
    }

};

#endif //LOC_API_ENG_ADAPTER_H
