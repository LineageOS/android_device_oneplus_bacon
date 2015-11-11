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
 *
 */
#define LOG_NDDEBUG 0
#define LOG_TAG "LocSvc_EngAdapter"

#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>
#include <cutils/properties.h>
#include <LocEngAdapter.h>
#include "loc_eng_msg.h"
#include "loc_log.h"

#define CHIPSET_SERIAL_NUMBER_MAX_LEN 16
#define USER_AGENT_MAX_LEN 512

using namespace loc_core;

LocInternalAdapter::LocInternalAdapter(LocEngAdapter* adapter) :
    LocAdapterBase(adapter->getMsgTask()),
    mLocEngAdapter(adapter)
{
}
void LocInternalAdapter::setPositionModeInt(LocPosMode& posMode) {
    sendMsg(new LocEngPositionMode(mLocEngAdapter, posMode));
}
void LocInternalAdapter::startFixInt() {
    sendMsg(new LocEngStartFix(mLocEngAdapter));
}
void LocInternalAdapter::stopFixInt() {
    sendMsg(new LocEngStopFix(mLocEngAdapter));
}
void LocInternalAdapter::getZppInt() {
    sendMsg(new LocEngGetZpp(mLocEngAdapter));
}

LocEngAdapter::LocEngAdapter(LOC_API_ADAPTER_EVENT_MASK_T mask,
                             void* owner, ContextBase* context,
                             LocThread::tCreate tCreator) :
    LocAdapterBase(mask,
                   //Get the AFW context if VzW context has not already been intialized in
                   //loc_ext
                   context == NULL?
                   LocDualContext::getLocFgContext(tCreator,
                                                   NULL,
                                                   LocDualContext::mLocationHalName,
                                                   false)
                   :context),
    mOwner(owner), mInternalAdapter(new LocInternalAdapter(this)),
    mUlp(new UlpProxyBase()), mNavigating(false),
    mSupportsAgpsRequests(false),
    mSupportsPositionInjection(false),
    mSupportsTimeInjection(false),
    mPowerVote(0)
{
    memset(&mFixCriteria, 0, sizeof(mFixCriteria));
    mFixCriteria.mode = LOC_POSITION_MODE_INVALID;
    LOC_LOGD("LocEngAdapter created");
}

inline
LocEngAdapter::~LocEngAdapter()
{
    delete mInternalAdapter;
    LOC_LOGV("LocEngAdapter deleted");
}

void LocEngAdapter::setXtraUserAgent() {
    struct LocSetXtraUserAgent : public LocMsg {
        const ContextBase* const mContext;
        inline LocSetXtraUserAgent(ContextBase* context) :
            LocMsg(), mContext(context) {
        }
        virtual void proc() const {
            char release[PROPERTY_VALUE_MAX];
            char manufacture[PROPERTY_VALUE_MAX];
            char model[PROPERTY_VALUE_MAX];
            char carrier[PROPERTY_VALUE_MAX];
            char board[PROPERTY_VALUE_MAX];
            char brand[PROPERTY_VALUE_MAX];
            char chipsetsn[CHIPSET_SERIAL_NUMBER_MAX_LEN];
            char userAgent[USER_AGENT_MAX_LEN];
            const char defVal[] = "-";

            property_get("ro.build.version.release", release,     defVal);
            property_get("ro.product.manufacturer",  manufacture, defVal);
            property_get("ro.product.model", model,   defVal);
            property_get("ro.carrier",       carrier, defVal);
            property_get("ro.product.board", board,   defVal);
            property_get("ro.product.brand", brand,   defVal);
            getChipsetSerialNo(chipsetsn, sizeof(chipsetsn), defVal);

            snprintf(userAgent, sizeof(userAgent), "A/%s/%s/%s/%s/%s/QCX3/s%u/-/%s/-/%s/-/-/-",
                     release, manufacture, model, board, carrier,
                     mContext->getIzatDevId(), chipsetsn, brand);

            for (int i = 0; i < sizeof(userAgent) && userAgent[i]; i++) {
                if (' ' == userAgent[i]) userAgent[i] = '#';
            }

            saveUserAgentString(userAgent, strlen(userAgent));
            LOC_LOGV("%s] UserAgent %s", __func__, userAgent);
        }

        void saveUserAgentString(const char* data, const int len) const {
            const char XTRA_FOLDER[] = "/data/misc/location/xtra";
            const char USER_AGENT_FILE[] = "/data/misc/location/xtra/useragent.txt";

            if (data == NULL || len < 1) {
                LOC_LOGE("%s:%d]: invalid input data = %p len = %d", __func__, __LINE__, data, len);
                return;
            }

            struct stat s;
            int err = stat(XTRA_FOLDER, &s);
            if (err < 0) {
                if (ENOENT == errno) {
                    if (mkdir(XTRA_FOLDER, 0700) < 0) {
                        LOC_LOGE("%s:%d]: make XTRA_FOLDER failed", __func__, __LINE__);
                        return;
                    }
                } else {
                    LOC_LOGE("%s:%d]: XTRA_FOLDER invalid", __func__, __LINE__);
                    return;
                }
            }

            FILE* file = fopen(USER_AGENT_FILE, "wt");
            if (file == NULL) {
                LOC_LOGE("%s:%d]: open USER_AGENT_FILE failed", __func__, __LINE__);
                return;
            }

            size_t written = fwrite(data, 1, len, file);
            fclose(file);
            file = NULL;

            // set file permission
            chmod(USER_AGENT_FILE, 0600);

            if (written != len) {
                LOC_LOGE("%s:%d]: write USER_AGENT_FILE failed", __func__, __LINE__);
            }
        }

        void getChipsetSerialNo(char buf[], int buflen, const char def[]) const {
            const char SOC_SERIAL_NUMBER[] = "/sys/devices/soc0/serial_number";

            FILE* file = fopen(SOC_SERIAL_NUMBER, "rt");
            if (file == NULL) {
                // use default upon unreadable file
                strlcpy(buf, def, buflen);

            } else {
                size_t size = fread(buf, 1, buflen - 1, file);
                if (size == 0) {
                   // use default upon empty file
                   strlcpy(buf, def, buflen);

                } else {
                   buf[size] = '\0';
                }

                fclose(file);

                // remove trailing spaces
                size_t len = strlen(buf);
                while (--len >= 0 && isspace(buf[len])) {
                    buf[len] = '\0';
                }
            }

            return;
        }

    };

    sendMsg(new LocSetXtraUserAgent(mContext));
}

void LocInternalAdapter::setUlpProxy(UlpProxyBase* ulp) {
    struct LocSetUlpProxy : public LocMsg {
        LocAdapterBase* mAdapter;
        UlpProxyBase* mUlp;
        inline LocSetUlpProxy(LocAdapterBase* adapter, UlpProxyBase* ulp) :
            LocMsg(), mAdapter(adapter), mUlp(ulp) {
        }
        virtual void proc() const {
            LOC_LOGV("%s] ulp %p adapter %p", __func__,
                     mUlp, mAdapter);
            mAdapter->setUlpProxy(mUlp);
        }
    };

    sendMsg(new LocSetUlpProxy(mLocEngAdapter, ulp));
}

void LocEngAdapter::setUlpProxy(UlpProxyBase* ulp)
{
    if (ulp == mUlp) {
        //This takes care of the case when double initalization happens
        //and we get the same object back for UlpProxyBase . Do nothing
        return;
    }

    LOC_LOGV("%s] %p", __func__, ulp);
    if (NULL == ulp) {
        LOC_LOGE("%s:%d]: ulp pointer is NULL", __func__, __LINE__);
        ulp = new UlpProxyBase();
    }

    if (LOC_POSITION_MODE_INVALID != mUlp->mPosMode.mode) {
        // need to send this mode and start msg to ULP
        ulp->sendFixMode(mUlp->mPosMode);
    }

    if(mUlp->mFixSet) {
        ulp->sendStartFix();
    }

    delete mUlp;
    mUlp = ulp;
}

int LocEngAdapter::setGpsLockMsg(LOC_GPS_LOCK_MASK lockMask)
{
    struct LocEngAdapterGpsLock : public LocMsg {
        LocEngAdapter* mAdapter;
        LOC_GPS_LOCK_MASK mLockMask;
        inline LocEngAdapterGpsLock(LocEngAdapter* adapter, LOC_GPS_LOCK_MASK lockMask) :
            LocMsg(), mAdapter(adapter), mLockMask(lockMask)
        {
            locallog();
        }
        inline virtual void proc() const {
            mAdapter->setGpsLock(mLockMask);
        }
        inline  void locallog() const {
            LOC_LOGV("LocEngAdapterGpsLock - mLockMask: %x", mLockMask);
        }
        inline virtual void log() const {
            locallog();
        }
    };
    sendMsg(new LocEngAdapterGpsLock(this, lockMask));
    return 0;
}

void LocEngAdapter::requestPowerVote()
{
    if (getPowerVoteRight()) {
        /* Power voting without engine lock:
         * 101: vote down, 102-104 - vote up
         * These codes are used not to confuse with actual engine lock
         * functionality, that can't be used in SSR scenario, as it
         * conflicts with initialization sequence.
         */
        bool powerUp = getPowerVote();
        LOC_LOGV("LocEngAdapterVotePower - Vote Power: %d", (int)powerUp);
        setGpsLock(powerUp ? 103 : 101);
    }
}

void LocInternalAdapter::reportPosition(UlpLocation &location,
                                        GpsLocationExtended &locationExtended,
                                        void* locationExt,
                                        enum loc_sess_status status,
                                        LocPosTechMask loc_technology_mask)
{
    sendMsg(new LocEngReportPosition(mLocEngAdapter,
                                     location,
                                     locationExtended,
                                     locationExt,
                                     status,
                                     loc_technology_mask));
}


void LocEngAdapter::reportPosition(UlpLocation &location,
                                   GpsLocationExtended &locationExtended,
                                   void* locationExt,
                                   enum loc_sess_status status,
                                   LocPosTechMask loc_technology_mask)
{
    if (! mUlp->reportPosition(location,
                               locationExtended,
                               locationExt,
                               status,
                               loc_technology_mask )) {
        mInternalAdapter->reportPosition(location,
                                         locationExtended,
                                         locationExt,
                                         status,
                                         loc_technology_mask);
    }
}

void LocInternalAdapter::reportSv(GnssSvStatus &svStatus,
                                  GpsLocationExtended &locationExtended,
                                  void* svExt){
    sendMsg(new LocEngReportSv(mLocEngAdapter, svStatus,
                               locationExtended, svExt));
}

void LocEngAdapter::reportSv(GnssSvStatus &svStatus,
                             GpsLocationExtended &locationExtended,
                             void* svExt)
{

    // We want to send SV info to ULP to help it in determining GNSS
    // signal strength ULP will forward the SV reports to HAL without
    // any modifications
    if (! mUlp->reportSv(svStatus, locationExtended, svExt)) {
        mInternalAdapter->reportSv(svStatus, locationExtended, svExt);
    }
}

void LocEngAdapter::setInSession(bool inSession)
{
    mNavigating = inSession;
    mLocApi->setInSession(inSession);
    if (!mNavigating) {
        mFixCriteria.mode = LOC_POSITION_MODE_INVALID;
    }
}

void LocInternalAdapter::reportStatus(GpsStatusValue status)
{
    sendMsg(new LocEngReportStatus(mLocEngAdapter, status));
}

void LocEngAdapter::reportStatus(GpsStatusValue status)
{
    if (!mUlp->reportStatus(status)) {
        mInternalAdapter->reportStatus(status);
    }
}

inline
void LocEngAdapter::reportNmea(const char* nmea, int length)
{
    sendMsg(new LocEngReportNmea(mOwner, nmea, length));
}

inline
bool LocEngAdapter::reportXtraServer(const char* url1,
                                        const char* url2,
                                        const char* url3,
                                        const int maxlength)
{
    if (mSupportsAgpsRequests) {
        sendMsg(new LocEngReportXtraServer(mOwner, url1,
                                           url2, url3, maxlength));
    }
    return mSupportsAgpsRequests;
}

inline
bool LocEngAdapter::requestATL(int connHandle, AGpsType agps_type)
{
    if (mSupportsAgpsRequests) {
        sendMsg(new LocEngRequestATL(mOwner,
                                     connHandle, agps_type));
    }
    return mSupportsAgpsRequests;
}

inline
bool LocEngAdapter::releaseATL(int connHandle)
{
    if (mSupportsAgpsRequests) {
        sendMsg(new LocEngReleaseATL(mOwner, connHandle));
    }
    return mSupportsAgpsRequests;
}

inline
bool LocEngAdapter::requestXtraData()
{
    if (mSupportsAgpsRequests) {
        sendMsg(new LocEngRequestXtra(mOwner));
    }
    return mSupportsAgpsRequests;
}

inline
bool LocEngAdapter::requestTime()
{
    if (mSupportsAgpsRequests) {
        sendMsg(new LocEngRequestTime(mOwner));
    }
    return mSupportsAgpsRequests;
}

inline
bool LocEngAdapter::requestNiNotify(GpsNiNotification &notif, const void* data)
{
    if (mSupportsAgpsRequests) {
        notif.size = sizeof(notif);
        notif.timeout = LOC_NI_NO_RESPONSE_TIME;

        sendMsg(new LocEngRequestNi(mOwner, notif, data));
    }
    return mSupportsAgpsRequests;
}

inline
bool LocEngAdapter::requestSuplES(int connHandle)
{
    if (mSupportsAgpsRequests)
        sendMsg(new LocEngRequestSuplEs(mOwner, connHandle));
    return mSupportsAgpsRequests;
}

inline
bool LocEngAdapter::reportDataCallOpened()
{
    if(mSupportsAgpsRequests)
        sendMsg(new LocEngSuplEsOpened(mOwner));
    return mSupportsAgpsRequests;
}

inline
bool LocEngAdapter::reportDataCallClosed()
{
    if(mSupportsAgpsRequests)
        sendMsg(new LocEngSuplEsClosed(mOwner));
    return mSupportsAgpsRequests;
}

inline
void LocEngAdapter::handleEngineDownEvent()
{
    sendMsg(new LocEngDown(mOwner));
}

inline
void LocEngAdapter::handleEngineUpEvent()
{
    sendMsg(new LocEngUp(mOwner));
}

enum loc_api_adapter_err LocEngAdapter::setTime(GpsUtcTime time,
                                                int64_t timeReference,
                                                int uncertainty)
{
    loc_api_adapter_err result = LOC_API_ADAPTER_ERR_SUCCESS;

    LOC_LOGD("%s:%d]: mSupportsTimeInjection is %d",
             __func__, __LINE__, mSupportsTimeInjection);

    if (mSupportsTimeInjection) {
        LOC_LOGD("%s:%d]: Injecting time", __func__, __LINE__);
        result = mLocApi->setTime(time, timeReference, uncertainty);
    } else {
        mSupportsTimeInjection = true;
    }
    return result;
}

enum loc_api_adapter_err LocEngAdapter::setXtraVersionCheck(int check)
{
    enum loc_api_adapter_err ret;
    ENTRY_LOG();
    enum xtra_version_check eCheck;
    switch (check) {
    case 0:
        eCheck = DISABLED;
        break;
    case 1:
        eCheck = AUTO;
        break;
    case 2:
        eCheck = XTRA2;
        break;
    case 3:
        eCheck = XTRA3;
        break;
    default:
        eCheck = DISABLED;
    }
    ret = mLocApi->setXtraVersionCheck(eCheck);
    EXIT_LOG(%d, ret);
    return ret;
}

void LocEngAdapter::reportGpsMeasurementData(GpsData &gpsMeasurementData)
{
    sendMsg(new LocEngReportGpsMeasurement(mOwner,
                                           gpsMeasurementData));
}

/*
  Update Registration Mask
 */
void LocEngAdapter::updateRegistrationMask(LOC_API_ADAPTER_EVENT_MASK_T event,
                                           loc_registration_mask_status isEnabled)
{
    LOC_LOGD("entering %s", __func__);
    int result = LOC_API_ADAPTER_ERR_FAILURE;
    result = mLocApi->updateRegistrationMask(event, isEnabled);
    if (result == LOC_API_ADAPTER_ERR_SUCCESS) {
        LOC_LOGD("%s] update registration mask succeed.", __func__);
    } else {
        LOC_LOGE("%s] update registration mask failed.", __func__);
    }
}

/*
  Set Gnss Constellation Config
 */
bool LocEngAdapter::gnssConstellationConfig()
{
    LOC_LOGD("entering %s", __func__);
    bool result = false;
    result = mLocApi->gnssConstellationConfig();
    return result;
}
