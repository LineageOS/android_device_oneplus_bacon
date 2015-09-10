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
#ifndef LOC_TARGET_H
#define LOC_TARGET_H
#define TARGET_SET(gnss,ssc) ( (gnss<<1)|ssc )
#define TARGET_DEFAULT       TARGET_SET(GNSS_MSM, HAS_SSC)
#define TARGET_MDM           TARGET_SET(GNSS_MDM, HAS_SSC)
#define TARGET_APQ_SA        TARGET_SET(GNSS_GSS, NO_SSC)
#define TARGET_MPQ           TARGET_SET(GNSS_NONE,NO_SSC)
#define TARGET_MSM_NO_SSC    TARGET_SET(GNSS_MSM, NO_SSC)
#define TARGET_QCA1530       TARGET_SET(GNSS_QCA1530, NO_SSC)
#define TARGET_PDS           TARGET_SET(GNSS_PDS, NO_SSC)
#define TARGET_AUTO          TARGET_SET(GNSS_AUTO, NO_SSC)
#define TARGET_UNKNOWN       TARGET_SET(GNSS_UNKNOWN, NO_SSC)
#define getTargetGnssType(target)  (target>>1)

#ifdef __cplusplus
extern "C"
{
#endif

unsigned int loc_get_target(void);

/*The character array passed to this function should have length
  of atleast PROPERTY_VALUE_MAX*/
void loc_get_target_baseband(char *baseband, int array_length);
/*The character array passed to this function should have length
  of atleast PROPERTY_VALUE_MAX*/
void loc_get_platform_name(char *platform_name, int array_length);

/* Please remember to update 'target_name' in loc_log.cpp,
   if do any changes to this enum. */
typedef enum {
    GNSS_NONE = 0,
    GNSS_MSM,
    GNSS_GSS,
    GNSS_MDM,
    GNSS_QCA1530,
    GNSS_PDS,
    GNSS_AUTO,
    GNSS_UNKNOWN
}GNSS_TARGET;

typedef enum {
    NO_SSC = 0,
    HAS_SSC
}SSC_TYPE;

#ifdef __cplusplus
}
#endif

#endif /*LOC_TARGET_H*/
