/* Copyright (c) 2012-2014, The Linux Foundation. All rights reserved.
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
 *     * Neither the name of The Linux Foundation nor the names of its
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

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <hardware/gps.h>
#include <cutils/properties.h>
#include "loc_target.h"
#include "loc_log.h"
#include "log_util.h"

#define APQ8064_ID_1 "109"
#define APQ8064_ID_2 "153"
#define MPQ8064_ID_1 "130"
#define MSM8930_ID_1 "142"
#define MSM8930_ID_2 "116"
#define APQ8030_ID_1 "157"
#define APQ8074_ID_1 "184"
#define PDS_ID_1     "178"

#define LINE_LEN 100
#define STR_LIQUID    "Liquid"
#define STR_SURF      "Surf"
#define STR_MTP       "MTP"
#define STR_APQ       "apq"
#define STR_AUTO      "auto"
#define IS_STR_END(c) ((c) == '\0' || (c) == '\n' || (c) == '\r')
#define LENGTH(s) (sizeof(s) - 1)
#define GPS_CHECK_NO_ERROR 0
#define GPS_CHECK_NO_GPS_HW 1
/* When system server is started, it uses 20 seconds as ActivityManager
 * timeout. After that it sends SIGSTOP signal to process.
 */
#define QCA1530_DETECT_TIMEOUT 15
#define QCA1530_DETECT_PRESENT "yes"
#define QCA1530_DETECT_PROGRESS "detect"

static unsigned int gTarget = (unsigned int)-1;

static int read_a_line(const char * file_path, char * line, int line_size)
{
    FILE *fp;
    int result = 0;

    * line = '\0';
    fp = fopen(file_path, "r" );
    if( fp == NULL ) {
        LOC_LOGE("open failed: %s: %s\n", file_path, strerror(errno));
        result = -1;
    } else {
        int len;
        fgets(line, line_size, fp);
        len = strlen(line);
        len = len < line_size - 1? len : line_size - 1;
        line[len] = '\0';
        LOC_LOGD("cat %s: %s", file_path, line);
        fclose(fp);
    }
    return result;
}

/*!
 * \brief Checks if QCA1530 is avalable.
 *
 * Function verifies if qca1530 SoC is configured on the device. The test is
 * based on property value. For 1530 scenario, the value shall be one of the
 * following: "yes", "no", "detect". All other values are treated equally to
 * "no". When the value is "detect" the system waits for SoC detection to
 * finish before returning result.
 *
 * \retval true - QCA1530 is available.
 * \retval false - QCA1530 is not available.
 */
static bool is_qca1530(void)
{
    static const char qca1530_property_name[] = "sys.qca1530";
    bool res = false;
    int ret, i;
    char buf[PROPERTY_VALUE_MAX];

    memset(buf, 0, sizeof(buf));

    for (i = 0; i < QCA1530_DETECT_TIMEOUT; ++i)
    {
        ret = property_get(qca1530_property_name, buf, NULL);
        if (ret < 0)
        {
            LOC_LOGV( "qca1530: property %s is not accessible, ret=%d",
                  qca1530_property_name,
                  ret);

            break;
        }

        LOC_LOGV( "qca1530: property %s is set to %s",
                  qca1530_property_name,
                  buf);

        if (!memcmp(buf, QCA1530_DETECT_PRESENT,
                    sizeof(QCA1530_DETECT_PRESENT)))
        {
            res = true;
            break;
        }
        if (!memcmp(buf, QCA1530_DETECT_PROGRESS,
                    sizeof(QCA1530_DETECT_PROGRESS)))
        {
            LOC_LOGV("qca1530: SoC detection is in progress.");
            sleep(1);
            continue;
        }
        break;
    }

    LOC_LOGD("qca1530: detected=%s", res ? "true" : "false");
    return res;
}

/*The character array passed to this function should have length
  of atleast PROPERTY_VALUE_MAX*/
void loc_get_target_baseband(char *baseband, int array_length)
{
    if(baseband && (array_length >= PROPERTY_VALUE_MAX)) {
        property_get("ro.baseband", baseband, "");
        LOC_LOGD("%s:%d]: Baseband: %s\n", __func__, __LINE__, baseband);
    }
    else {
        LOC_LOGE("%s:%d]: NULL parameter or array length less than PROPERTY_VALUE_MAX\n",
                 __func__, __LINE__);
    }
}

/*The character array passed to this function should have length
  of atleast PROPERTY_VALUE_MAX*/
void loc_get_platform_name(char *platform_name, int array_length)
{
    if(platform_name && (array_length >= PROPERTY_VALUE_MAX)) {
        property_get("ro.board.platform", platform_name, "");
        LOC_LOGD("%s:%d]: Target name: %s\n", __func__, __LINE__, platform_name);
    }
    else {
        LOC_LOGE("%s:%d]: Null parameter or array length less than PROPERTY_VALUE_MAX\n",
                 __func__, __LINE__);
    }
}

unsigned int loc_get_target(void)
{
    if (gTarget != (unsigned int)-1)
        return gTarget;

    static const char hw_platform[]      = "/sys/devices/soc0/hw_platform";
    static const char id[]               = "/sys/devices/soc0/soc_id";
    static const char hw_platform_dep[]  =
        "/sys/devices/system/soc/soc0/hw_platform";
    static const char id_dep[]           = "/sys/devices/system/soc/soc0/id";
    static const char mdm[]              = "/dev/mdm"; // No such file or directory

    char rd_hw_platform[LINE_LEN];
    char rd_id[LINE_LEN];
    char rd_mdm[LINE_LEN];
    char baseband[LINE_LEN];

    if (is_qca1530()) {
        gTarget = TARGET_QCA1530;
        goto detected;
    }

    loc_get_target_baseband(baseband, sizeof(baseband));

    if (!access(hw_platform, F_OK)) {
        read_a_line(hw_platform, rd_hw_platform, LINE_LEN);
    } else {
        read_a_line(hw_platform_dep, rd_hw_platform, LINE_LEN);
    }
    if (!access(id, F_OK)) {
        read_a_line(id, rd_id, LINE_LEN);
    } else {
        read_a_line(id_dep, rd_id, LINE_LEN);
    }
    if( !memcmp(baseband, STR_AUTO, LENGTH(STR_AUTO)) )
    {
          gTarget = TARGET_AUTO;
          goto detected;
    }
    if( !memcmp(rd_hw_platform, STR_MTP, LENGTH(STR_MTP)) ){
        if( !memcmp(rd_id, PDS_ID_1, LENGTH(PDS_ID_1))
            && IS_STR_END(rd_id[LENGTH(PDS_ID_1)]) )
            gTarget = TARGET_PDS;
    }
    else if( !memcmp(baseband, STR_APQ, LENGTH(STR_APQ)) ){
        if( !memcmp(rd_id, MPQ8064_ID_1, LENGTH(MPQ8064_ID_1))
            && IS_STR_END(rd_id[LENGTH(MPQ8064_ID_1)]) )
            gTarget = TARGET_MPQ;
        else
            gTarget = TARGET_APQ_SA;
    }
    else {
        if( (!memcmp(rd_hw_platform, STR_LIQUID, LENGTH(STR_LIQUID))
             && IS_STR_END(rd_hw_platform[LENGTH(STR_LIQUID)])) ||
            (!memcmp(rd_hw_platform, STR_SURF,   LENGTH(STR_SURF))
             && IS_STR_END(rd_hw_platform[LENGTH(STR_SURF)])) ||
            (!memcmp(rd_hw_platform, STR_MTP,   LENGTH(STR_MTP))
             && IS_STR_END(rd_hw_platform[LENGTH(STR_MTP)]))) {

            if (!read_a_line( mdm, rd_mdm, LINE_LEN))
                gTarget = TARGET_MDM;
        }
        else if( (!memcmp(rd_id, MSM8930_ID_1, LENGTH(MSM8930_ID_1))
                   && IS_STR_END(rd_id[LENGTH(MSM8930_ID_1)])) ||
                  (!memcmp(rd_id, MSM8930_ID_2, LENGTH(MSM8930_ID_2))
                   && IS_STR_END(rd_id[LENGTH(MSM8930_ID_2)])) )
             gTarget = TARGET_MSM_NO_SSC;
        else
             gTarget = TARGET_UNKNOWN;
    }

detected:
    LOC_LOGD("HAL: %s returned %d", __FUNCTION__, gTarget);
    return gTarget;
}
