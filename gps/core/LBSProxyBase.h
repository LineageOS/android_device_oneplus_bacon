/* Copyright (c) 2013-2015, The Linux Foundation. All rights reserved.
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
#ifndef IZAT_PROXY_BASE_H
#define IZAT_PROXY_BASE_H
#include <gps_extended.h>
#include <MsgTask.h>

namespace loc_core {

class LocApiBase;
class LocAdapterBase;
class ContextBase;

class LBSProxyBase {
    friend class ContextBase;
    inline virtual LocApiBase*
        getLocApi(const MsgTask* msgTask,
                  LOC_API_ADAPTER_EVENT_MASK_T exMask,
                  ContextBase* context) const {

        (void)msgTask;
        (void)exMask;
        (void)context;
        return NULL;
    }
protected:
    inline LBSProxyBase() {}
public:
    inline virtual ~LBSProxyBase() {}
    inline virtual void requestUlp(LocAdapterBase* adapter,
                                   unsigned long capabilities) const {

        (void)adapter;
        (void)capabilities;
    }
    inline virtual bool hasAgpsExtendedCapabilities() const { return false; }
    inline virtual bool hasCPIExtendedCapabilities() const { return false; }
    inline virtual void modemPowerVote(bool power) const {

        (void)power;
    }
    virtual void injectFeatureConfig(ContextBase* context) const {

        (void)context;
    }
    inline virtual IzatDevId_t getIzatDevId() const { return 0; }
};

typedef LBSProxyBase* (getLBSProxy_t)();

} // namespace loc_core

#endif // IZAT_PROXY_BASE_H
