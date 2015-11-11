/* Copyright (c) 2009-2013, The Linux Foundation. All rights reserved.
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

#include <loc_eng.h>
#include <MsgTask.h>
#include "log_util.h"
#include "platform_lib_includes.h"

using namespace loc_core;

struct LocEngRequestXtraServer : public LocMsg {
    LocEngAdapter* mAdapter;
    inline LocEngRequestXtraServer(LocEngAdapter* adapter) :
        LocMsg(), mAdapter(adapter)
    {
        locallog();
    }
    inline virtual void proc() const {
        mAdapter->requestXtraServer();
    }
    inline void locallog() const {
        LOC_LOGV("LocEngRequestXtraServer");
    }
    inline virtual void log() const {
        locallog();
    }
};

struct LocEngInjectXtraData : public LocMsg {
    LocEngAdapter* mAdapter;
    char* mData;
    const int mLen;
    inline LocEngInjectXtraData(LocEngAdapter* adapter,
                                char* data, int len):
        LocMsg(), mAdapter(adapter),
        mData(new char[len]), mLen(len)
    {
        memcpy((void*)mData, (void*)data, len);
        locallog();
    }
    inline ~LocEngInjectXtraData()
    {
        delete[] mData;
    }
    inline virtual void proc() const {
        mAdapter->setXtraData(mData, mLen);
    }
    inline  void locallog() const {
        LOC_LOGV("length: %d\n  data: %p", mLen, mData);
    }
    inline virtual void log() const {
        locallog();
    }
};

struct LocEngSetXtraVersionCheck : public LocMsg {
    LocEngAdapter *mAdapter;
    int mCheck;
    inline LocEngSetXtraVersionCheck(LocEngAdapter* adapter,
                                        int check):
        mAdapter(adapter), mCheck(check) {}
    inline virtual void proc() const {
        locallog();
        mAdapter->setXtraVersionCheck(mCheck);
    }
    inline void locallog() const {
        LOC_LOGD("%s:%d]: mCheck: %d",
                 __func__, __LINE__, mCheck);
    }
    inline virtual void log() const {
        locallog();
    }
};

/*===========================================================================
FUNCTION    loc_eng_xtra_init

DESCRIPTION
   Initialize XTRA module.

DEPENDENCIES
   N/A

RETURN VALUE
   0: success

SIDE EFFECTS
   N/A

===========================================================================*/
int loc_eng_xtra_init (loc_eng_data_s_type &loc_eng_data,
                       GpsXtraExtCallbacks* callbacks)
{
    int ret_val = -1;
    loc_eng_xtra_data_s_type *xtra_module_data_ptr;
    ENTRY_LOG();

    if(callbacks == NULL) {
        LOC_LOGE("loc_eng_xtra_init: failed, cb is NULL");
    } else {
        xtra_module_data_ptr = &loc_eng_data.xtra_module_data;
        xtra_module_data_ptr->download_request_cb = callbacks->download_request_cb;
        xtra_module_data_ptr->report_xtra_server_cb = callbacks->report_xtra_server_cb;

        ret_val = 0;
    }
    EXIT_LOG(%d, ret_val);
    return ret_val;
}

/*===========================================================================
FUNCTION    loc_eng_xtra_inject_data

DESCRIPTION
   Injects XTRA file into the engine but buffers the data if engine is busy.

DEPENDENCIES
   N/A

RETURN VALUE
   0

SIDE EFFECTS
   N/A

===========================================================================*/
int loc_eng_xtra_inject_data(loc_eng_data_s_type &loc_eng_data,
                             char* data, int length)
{
    ENTRY_LOG();
    LocEngAdapter* adapter = loc_eng_data.adapter;
    adapter->sendMsg(new LocEngInjectXtraData(adapter, data, length));
    EXIT_LOG(%d, 0);
    return 0;
}
/*===========================================================================
FUNCTION    loc_eng_xtra_request_server

DESCRIPTION
   Request the Xtra server url from the modem

DEPENDENCIES
   N/A

RETURN VALUE
   0

SIDE EFFECTS
   N/A

===========================================================================*/
int loc_eng_xtra_request_server(loc_eng_data_s_type &loc_eng_data)
{
    ENTRY_LOG();
    LocEngAdapter* adapter = loc_eng_data.adapter;
    adapter->sendMsg(new LocEngRequestXtraServer(adapter));
    EXIT_LOG(%d, 0);
    return 0;
}
/*===========================================================================
FUNCTION    loc_eng_xtra_version_check

DESCRIPTION
   Injects the enable/disable value for checking XTRA version
   that is specified in gps.conf

DEPENDENCIES
   N/A

RETURN VALUE
   none

SIDE EFFECTS
   N/A

===========================================================================*/
void loc_eng_xtra_version_check(loc_eng_data_s_type &loc_eng_data,
                                int check)
{
    ENTRY_LOG();
    LocEngAdapter *adapter = loc_eng_data.adapter;
    adapter->sendMsg(new LocEngSetXtraVersionCheck(adapter, check));
    EXIT_LOG(%d, 0);
}
