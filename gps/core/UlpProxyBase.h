/* Copyright (c) 2013-2014, The Linux Foundation. All rights reserved.
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
#ifndef ULP_PROXY_BASE_H
#define ULP_PROXY_BASE_H

#include <gps_extended.h>

namespace loc_core {

class LocAdapterBase;

class UlpProxyBase {
public:
    LocPosMode mPosMode;
    bool mFixSet;
    inline UlpProxyBase() {
        mPosMode.mode = LOC_POSITION_MODE_INVALID;
        mFixSet = false;
    }
    inline virtual ~UlpProxyBase() {}
    inline virtual bool sendStartFix() { mFixSet = true; return false; }
    inline virtual bool sendStopFix() { mFixSet = false; return false; }
    inline virtual bool sendFixMode(LocPosMode &params) {
        mPosMode = params;
        return false;
    }

    inline virtual bool reportPosition(UlpLocation &location,
                                       GpsLocationExtended &locationExtended,
                                       void* locationExt,
                                       enum loc_sess_status status,
                                       LocPosTechMask loc_technology_mask) {
        return false;
    }
    inline virtual bool reportSv(GpsSvStatus &svStatus,
                                 GpsLocationExtended &locationExtended,
                                 void* svExt) {
        return false;
    }
    inline virtual bool reportStatus(GpsStatusValue status) {
        return false;
    }
    inline virtual void setAdapter(LocAdapterBase* adapter) {}
    inline virtual void setCapabilities(unsigned long capabilities) {}
    inline virtual bool reportBatchingSession(GpsExtBatchOptions &options,
                                              bool active) {
        return false;
    }
    inline virtual bool reportPositions(GpsExtLocation * locations,
                                        int32_t number_of_locations,
                                        enum loc_sess_status status,
                                        LocPosTechMask techMask) {
        return false;
    }
};

} // namespace loc_core

#endif // ULP_PROXY_BASE_H
