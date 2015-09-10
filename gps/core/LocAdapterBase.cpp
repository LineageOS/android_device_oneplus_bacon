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
#define LOG_TAG "LocSvc_LocAdapterBase"

#include <dlfcn.h>
#include <LocAdapterBase.h>
#include <loc_target.h>
#include <log_util.h>
#include <LocAdapterProxyBase.h>

namespace loc_core {

// This is the top level class, so the constructor will
// always gets called. Here we prepare for the default.
// But if getLocApi(targetEnumType target) is overriden,
// the right locApi should get created.
LocAdapterBase::LocAdapterBase(const LOC_API_ADAPTER_EVENT_MASK_T mask,
                               ContextBase* context, LocAdapterProxyBase *adapterProxyBase) :
    mEvtMask(mask), mContext(context),
    mLocApi(context->getLocApi()), mLocAdapterProxyBase(adapterProxyBase),
    mMsgTask(context->getMsgTask())
{
    mLocApi->addAdapter(this);
}

void LocAdapterBase::handleEngineUpEvent()
{
    if (mLocAdapterProxyBase) {
        mLocAdapterProxyBase->handleEngineUpEvent();
    }
}

void LocAdapterBase::handleEngineDownEvent()
{
    if (mLocAdapterProxyBase) {
        mLocAdapterProxyBase->handleEngineDownEvent();
    }
}

void LocAdapterBase::
    reportPosition(UlpLocation &location,
                   GpsLocationExtended &locationExtended,
                   void* locationExt,
                   enum loc_sess_status status,
                   LocPosTechMask loc_technology_mask)
DEFAULT_IMPL()

void LocAdapterBase::
    reportSv(GpsSvStatus &svStatus,
             GpsLocationExtended &locationExtended,
             void* svExt)
DEFAULT_IMPL()


void LocAdapterBase::
    reportStatus(GpsStatusValue status)
DEFAULT_IMPL()


void LocAdapterBase::
    reportNmea(const char* nmea, int length)
DEFAULT_IMPL()

bool LocAdapterBase::
    reportXtraServer(const char* url1, const char* url2,
                     const char* url3, const int maxlength)
DEFAULT_IMPL(false)

bool LocAdapterBase::
    requestXtraData()
DEFAULT_IMPL(false)

bool LocAdapterBase::
    requestTime()
DEFAULT_IMPL(false)

bool LocAdapterBase::
    requestLocation()
DEFAULT_IMPL(false)

bool LocAdapterBase::
    requestATL(int connHandle, AGpsType agps_type)
DEFAULT_IMPL(false)

bool LocAdapterBase::
    releaseATL(int connHandle)
DEFAULT_IMPL(false)

bool LocAdapterBase::
    requestSuplES(int connHandle)
DEFAULT_IMPL(false)

bool LocAdapterBase::
    reportDataCallOpened()
DEFAULT_IMPL(false)

bool LocAdapterBase::
    reportDataCallClosed()
DEFAULT_IMPL(false)

bool LocAdapterBase::
    requestNiNotify(GpsNiNotification &notify, const void* data)
DEFAULT_IMPL(false)

void LocAdapterBase::
    shutdown()
DEFAULT_IMPL()
} // namespace loc_core
