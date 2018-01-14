/* Copyright (c) 2014 The Linux Foundation. All rights reserved.
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

#ifndef LOC_ADAPTER_PROXY_BASE_H
#define LOC_ADAPTER_PROXY_BASE_H

#include <ContextBase.h>
#include <gps_extended.h>

namespace loc_core {

class LocAdapterProxyBase {
private:
    LocAdapterBase *mLocAdapterBase;
protected:
    inline LocAdapterProxyBase(const LOC_API_ADAPTER_EVENT_MASK_T mask,
                   ContextBase* context):
                   mLocAdapterBase(new LocAdapterBase(mask, context, this)) {
    }
    inline virtual ~LocAdapterProxyBase() {
        delete mLocAdapterBase;
    }
    ContextBase* getContext() const {
        return mLocAdapterBase->getContext();
    }
    inline void updateEvtMask(LOC_API_ADAPTER_EVENT_MASK_T event,
                              loc_registration_mask_status isEnabled) {
        mLocAdapterBase->updateEvtMask(event,isEnabled);
    }

public:
    inline virtual void handleEngineUpEvent() {};
    inline virtual void handleEngineDownEvent() {};
    inline virtual bool reportPosition(UlpLocation &location,
                                       GpsLocationExtended &locationExtended,
                                       enum loc_sess_status status,
                                       LocPosTechMask loc_technology_mask) {

        (void)location;
        (void)locationExtended;
        (void)status;
        (void)loc_technology_mask;
        return false;
    }
};

} // namespace loc_core

#endif //LOC_ADAPTER_PROXY_BASE_H
