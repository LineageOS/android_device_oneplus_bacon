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
#define LOG_TAG "LocSvc_afw"

#include <hardware/gps.h>
#include <gps_extended.h>
#include <loc_eng.h>
#include <loc_target.h>
#include <loc_log.h>
#include <fcntl.h>
#include <errno.h>
#include <dlfcn.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <LocDualContext.h>
#include <cutils/properties.h>

using namespace loc_core;

#define LOC_PM_CLIENT_NAME "GPS"

//Globals defns
static gps_location_callback gps_loc_cb = NULL;
static gps_sv_status_callback gps_sv_cb = NULL;

static void local_loc_cb(UlpLocation* location, void* locExt);
static void local_sv_cb(GpsSvStatus* sv_status, void* svExt);

static const GpsGeofencingInterface* get_geofence_interface(void);

// Function declarations for sLocEngInterface
static int  loc_init(GpsCallbacks* callbacks);
static int  loc_start();
static int  loc_stop();
static void loc_cleanup();
static int  loc_inject_time(GpsUtcTime time, int64_t timeReference, int uncertainty);
static int  loc_inject_location(double latitude, double longitude, float accuracy);
static void loc_delete_aiding_data(GpsAidingData f);
static int  loc_set_position_mode(GpsPositionMode mode, GpsPositionRecurrence recurrence,
                                  uint32_t min_interval, uint32_t preferred_accuracy,
                                  uint32_t preferred_time);
static const void* loc_get_extension(const char* name);
// Defines the GpsInterface in gps.h
static const GpsInterface sLocEngInterface =
{
   sizeof(GpsInterface),
   loc_init,
   loc_start,
   loc_stop,
   loc_cleanup,
   loc_inject_time,
   loc_inject_location,
   loc_delete_aiding_data,
   loc_set_position_mode,
   loc_get_extension
};

// Function declarations for sLocEngAGpsInterface
static void loc_agps_init(AGpsCallbacks* callbacks);
static int  loc_agps_open(const char* apn);
static int  loc_agps_closed();
static int  loc_agps_open_failed();
static int  loc_agps_set_server(AGpsType type, const char *hostname, int port);
static int  loc_agps_open_with_apniptype( const char* apn, ApnIpType apnIpType);

static const AGpsInterface sLocEngAGpsInterface =
{
   sizeof(AGpsInterface),
   loc_agps_init,
   loc_agps_open,
   loc_agps_closed,
   loc_agps_open_failed,
   loc_agps_set_server,
   loc_agps_open_with_apniptype
};

static int loc_xtra_init(GpsXtraCallbacks* callbacks);
static int loc_xtra_inject_data(char* data, int length);

static const GpsXtraInterface sLocEngXTRAInterface =
{
    sizeof(GpsXtraInterface),
    loc_xtra_init,
    loc_xtra_inject_data
};

static void loc_ni_init(GpsNiCallbacks *callbacks);
static void loc_ni_respond(int notif_id, GpsUserResponseType user_response);

static const GpsNiInterface sLocEngNiInterface =
{
   sizeof(GpsNiInterface),
   loc_ni_init,
   loc_ni_respond,
};

static int loc_gps_measurement_init(GpsMeasurementCallbacks* callbacks);
static void loc_gps_measurement_close();

static const GpsMeasurementInterface sLocEngGpsMeasurementInterface =
{
    sizeof(GpsMeasurementInterface),
    loc_gps_measurement_init,
    loc_gps_measurement_close
};

static void loc_agps_ril_init( AGpsRilCallbacks* callbacks );
static void loc_agps_ril_set_ref_location(const AGpsRefLocation *agps_reflocation, size_t sz_struct);
static void loc_agps_ril_set_set_id(AGpsSetIDType type, const char* setid);
static void loc_agps_ril_ni_message(uint8_t *msg, size_t len);
static void loc_agps_ril_update_network_state(int connected, int type, int roaming, const char* extra_info);
static void loc_agps_ril_update_network_availability(int avaiable, const char* apn);

static const AGpsRilInterface sLocEngAGpsRilInterface =
{
   sizeof(AGpsRilInterface),
   loc_agps_ril_init,
   loc_agps_ril_set_ref_location,
   loc_agps_ril_set_set_id,
   loc_agps_ril_ni_message,
   loc_agps_ril_update_network_state,
   loc_agps_ril_update_network_availability
};

static int loc_agps_install_certificates(const DerEncodedCertificate* certificates,
                                         size_t length);
static int loc_agps_revoke_certificates(const Sha1CertificateFingerprint* fingerprints,
                                        size_t length);

static const SuplCertificateInterface sLocEngAGpsCertInterface =
{
    sizeof(SuplCertificateInterface),
    loc_agps_install_certificates,
    loc_agps_revoke_certificates
};

static void loc_configuration_update(const char* config_data, int32_t length);

static const GnssConfigurationInterface sLocEngConfigInterface =
{
    sizeof(GnssConfigurationInterface),
    loc_configuration_update
};

static loc_eng_data_s_type loc_afw_data;
static int gss_fd = -1;
static int sGnssType = GNSS_UNKNOWN;
/*===========================================================================
FUNCTION    gps_get_hardware_interface

DESCRIPTION
   Returns the GPS hardware interaface based on LOC API
   if GPS is enabled.

DEPENDENCIES
   None

RETURN VALUE
   0: success

SIDE EFFECTS
   N/A

===========================================================================*/
const GpsInterface* gps_get_hardware_interface ()
{
    ENTRY_LOG_CALLFLOW();
    const GpsInterface* ret_val;

    char propBuf[PROPERTY_VALUE_MAX];

    loc_eng_read_config();

    // check to see if GPS should be disabled
    property_get("gps.disable", propBuf, "");
    if (propBuf[0] == '1')
    {
        LOC_LOGD("gps_get_interface returning NULL because gps.disable=1\n");
        ret_val = NULL;
    } else {
        ret_val = &sLocEngInterface;
    }

    loc_eng_read_config();

    EXIT_LOG(%p, ret_val);
    return ret_val;
}

// for gps.c
extern "C" const GpsInterface* get_gps_interface()
{
    unsigned int target = TARGET_DEFAULT;
    loc_eng_read_config();

    target = loc_get_target();
    LOC_LOGD("Target name check returned %s", loc_get_target_name(target));

    sGnssType = getTargetGnssType(target);
    switch (sGnssType)
    {
    case GNSS_GSS:
    case GNSS_AUTO:
        //APQ8064
        gps_conf.CAPABILITIES &= ~(GPS_CAPABILITY_MSA | GPS_CAPABILITY_MSB);
        gss_fd = open("/dev/gss", O_RDONLY);
        if (gss_fd < 0) {
            LOC_LOGE("GSS open failed: %s\n", strerror(errno));
        }
        else {
            LOC_LOGD("GSS open success! CAPABILITIES %0lx\n",
                     gps_conf.CAPABILITIES);
        }
        break;
    case GNSS_NONE:
        //MPQ8064
        LOC_LOGE("No GPS HW on this target. Not returning interface.");
        return NULL;
    case GNSS_QCA1530:
        // qca1530 chip is present
        gps_conf.CAPABILITIES &= ~(GPS_CAPABILITY_MSA | GPS_CAPABILITY_MSB);
        LOC_LOGD("qca1530 present: CAPABILITIES %0lx\n", gps_conf.CAPABILITIES);
        break;
    }
    return &sLocEngInterface;
}

/*===========================================================================
FUNCTION    loc_init

DESCRIPTION
   Initialize the location engine, this include setting up global datas
   and registers location engien with loc api service.

DEPENDENCIES
   None

RETURN VALUE
   0: success

SIDE EFFECTS
   N/Ax

===========================================================================*/
static int loc_init(GpsCallbacks* callbacks)
{
    int retVal = -1;
    ENTRY_LOG();
    LOC_API_ADAPTER_EVENT_MASK_T event;

    if (NULL == callbacks) {
        LOC_LOGE("loc_init failed. cb = NULL\n");
        EXIT_LOG(%d, retVal);
        return retVal;
    }

    event = LOC_API_ADAPTER_BIT_PARSED_POSITION_REPORT |
            LOC_API_ADAPTER_BIT_SATELLITE_REPORT |
            LOC_API_ADAPTER_BIT_LOCATION_SERVER_REQUEST |
            LOC_API_ADAPTER_BIT_ASSISTANCE_DATA_REQUEST |
            LOC_API_ADAPTER_BIT_IOCTL_REPORT |
            LOC_API_ADAPTER_BIT_STATUS_REPORT |
            LOC_API_ADAPTER_BIT_NMEA_1HZ_REPORT |
            LOC_API_ADAPTER_BIT_NI_NOTIFY_VERIFY_REQUEST;

    LocCallbacks clientCallbacks = {local_loc_cb, /* location_cb */
                                    callbacks->status_cb, /* status_cb */
                                    local_sv_cb, /* sv_status_cb */
                                    callbacks->nmea_cb, /* nmea_cb */
                                    callbacks->set_capabilities_cb, /* set_capabilities_cb */
                                    callbacks->acquire_wakelock_cb, /* acquire_wakelock_cb */
                                    callbacks->release_wakelock_cb, /* release_wakelock_cb */
                                    callbacks->create_thread_cb, /* create_thread_cb */
                                    NULL, /* location_ext_parser */
                                    NULL, /* sv_ext_parser */
                                    callbacks->request_utc_time_cb, /* request_utc_time_cb */
                                    };

    gps_loc_cb = callbacks->location_cb;
    gps_sv_cb = callbacks->sv_status_cb;

    retVal = loc_eng_init(loc_afw_data, &clientCallbacks, event, NULL);
    loc_afw_data.adapter->mSupportsAgpsRequests = !loc_afw_data.adapter->hasAgpsExtendedCapabilities();
    loc_afw_data.adapter->mSupportsPositionInjection = !loc_afw_data.adapter->hasCPIExtendedCapabilities();
    loc_afw_data.adapter->mSupportsTimeInjection = !loc_afw_data.adapter->hasCPIExtendedCapabilities();
    loc_afw_data.adapter->setGpsLockMsg(0);
    loc_afw_data.adapter->requestUlp(getCarrierCapabilities());
    loc_afw_data.adapter->setXtraUserAgent();

    if(retVal) {
        LOC_LOGE("loc_eng_init() fail!");
        goto err;
    }

    loc_afw_data.adapter->setPowerVoteRight(loc_get_target() == TARGET_QCA1530);
    loc_afw_data.adapter->setPowerVote(true);

    LOC_LOGD("loc_eng_init() success!");

err:
    EXIT_LOG(%d, retVal);
    return retVal;
}

/*===========================================================================
FUNCTION    loc_cleanup

DESCRIPTION
   Cleans location engine. The location client handle will be released.

DEPENDENCIES
   None

RETURN VALUE
   None

SIDE EFFECTS
   N/A

===========================================================================*/
static void loc_cleanup()
{
    ENTRY_LOG();

    loc_afw_data.adapter->setPowerVote(false);
    loc_afw_data.adapter->setGpsLockMsg(gps_conf.GPS_LOCK);

    loc_eng_cleanup(loc_afw_data);
    gps_loc_cb = NULL;
    gps_sv_cb = NULL;

    EXIT_LOG(%s, VOID_RET);
}

/*===========================================================================
FUNCTION    loc_start

DESCRIPTION
   Starts the tracking session

DEPENDENCIES
   None

RETURN VALUE
   0: success

SIDE EFFECTS
   N/A

===========================================================================*/
static int loc_start()
{
    ENTRY_LOG();
    int ret_val = loc_eng_start(loc_afw_data);

    EXIT_LOG(%d, ret_val);
    return ret_val;
}

/*===========================================================================
FUNCTION    loc_stop

DESCRIPTION
   Stops the tracking session

DEPENDENCIES
   None

RETURN VALUE
   0: success

SIDE EFFECTS
   N/A

===========================================================================*/
static int loc_stop()
{
    ENTRY_LOG();
    int ret_val = -1;
    ret_val = loc_eng_stop(loc_afw_data);

    EXIT_LOG(%d, ret_val);
    return ret_val;
}

/*===========================================================================
FUNCTION    loc_set_position_mode

DESCRIPTION
   Sets the mode and fix frequency for the tracking session.

DEPENDENCIES
   None

RETURN VALUE
   0: success

SIDE EFFECTS
   N/A

===========================================================================*/
static int  loc_set_position_mode(GpsPositionMode mode,
                                  GpsPositionRecurrence recurrence,
                                  uint32_t min_interval,
                                  uint32_t preferred_accuracy,
                                  uint32_t preferred_time)
{
    ENTRY_LOG();
    int ret_val = -1;
    LocPositionMode locMode;
    switch (mode) {
    case GPS_POSITION_MODE_MS_BASED:
        locMode = LOC_POSITION_MODE_MS_BASED;
        break;
    case GPS_POSITION_MODE_MS_ASSISTED:
        locMode = LOC_POSITION_MODE_MS_ASSISTED;
        break;
    default:
        locMode = LOC_POSITION_MODE_STANDALONE;
        break;
    }

    LocPosMode params(locMode, recurrence, min_interval,
                      preferred_accuracy, preferred_time, NULL, NULL);
    ret_val = loc_eng_set_position_mode(loc_afw_data, params);

    EXIT_LOG(%d, ret_val);
    return ret_val;
}

/*===========================================================================
FUNCTION    loc_inject_time

DESCRIPTION
   This is used by Java native function to do time injection.

DEPENDENCIES
   None

RETURN VALUE
   0

SIDE EFFECTS
   N/A

===========================================================================*/
static int loc_inject_time(GpsUtcTime time, int64_t timeReference, int uncertainty)
{
    ENTRY_LOG();
    int ret_val = 0;

    ret_val = loc_eng_inject_time(loc_afw_data, time,
                                  timeReference, uncertainty);

    EXIT_LOG(%d, ret_val);
    return ret_val;
}


/*===========================================================================
FUNCTION    loc_inject_location

DESCRIPTION
   This is used by Java native function to do location injection.

DEPENDENCIES
   None

RETURN VALUE
   0          : Successful
   error code : Failure

SIDE EFFECTS
   N/A
===========================================================================*/
static int loc_inject_location(double latitude, double longitude, float accuracy)
{
    ENTRY_LOG();

    int ret_val = 0;
    ret_val = loc_eng_inject_location(loc_afw_data, latitude, longitude, accuracy);

    EXIT_LOG(%d, ret_val);
    return ret_val;
}


/*===========================================================================
FUNCTION    loc_delete_aiding_data

DESCRIPTION
   This is used by Java native function to delete the aiding data. The function
   updates the global variable for the aiding data to be deleted. If the GPS
   engine is off, the aiding data will be deleted. Otherwise, the actual action
   will happen when gps engine is turned off.

DEPENDENCIES
   Assumes the aiding data type specified in GpsAidingData matches with
   LOC API specification.

RETURN VALUE
   None

SIDE EFFECTS
   N/A

===========================================================================*/
static void loc_delete_aiding_data(GpsAidingData f)
{
    ENTRY_LOG();
    loc_eng_delete_aiding_data(loc_afw_data, f);

    EXIT_LOG(%s, VOID_RET);
}

const GpsGeofencingInterface* get_geofence_interface(void)
{
    ENTRY_LOG();
    void *handle;
    const char *error;
    typedef const GpsGeofencingInterface* (*get_gps_geofence_interface_function) (void);
    get_gps_geofence_interface_function get_gps_geofence_interface;
    static const GpsGeofencingInterface* geofence_interface = NULL;

    dlerror();    /* Clear any existing error */

    handle = dlopen ("libgeofence.so", RTLD_NOW);

    if (!handle)
    {
        if ((error = dlerror()) != NULL)  {
            LOC_LOGE ("%s, dlopen for libgeofence.so failed, error = %s\n", __func__, error);
           }
        goto exit;
    }
    dlerror();    /* Clear any existing error */
    get_gps_geofence_interface = (get_gps_geofence_interface_function)dlsym(handle, "gps_geofence_get_interface");
    if ((error = dlerror()) != NULL || NULL == get_gps_geofence_interface)  {
        LOC_LOGE ("%s, dlsym for get_gps_geofence_interface failed, error = %s\n", __func__, error);
        goto exit;
     }

    geofence_interface = get_gps_geofence_interface();

exit:
    EXIT_LOG(%d, geofence_interface == NULL);
    return geofence_interface;
}
/*===========================================================================
FUNCTION    loc_get_extension

DESCRIPTION
   Get the gps extension to support XTRA.

DEPENDENCIES
   N/A

RETURN VALUE
   The GPS extension interface.

SIDE EFFECTS
   N/A

===========================================================================*/
const void* loc_get_extension(const char* name)
{
    ENTRY_LOG();
    const void* ret_val = NULL;

   LOC_LOGD("%s:%d] For Interface = %s\n",__func__, __LINE__, name);
   if (strcmp(name, GPS_XTRA_INTERFACE) == 0)
   {
       ret_val = &sLocEngXTRAInterface;
   }
   else if (strcmp(name, AGPS_INTERFACE) == 0)
   {
       ret_val = &sLocEngAGpsInterface;
   }
   else if (strcmp(name, GPS_NI_INTERFACE) == 0)
   {
       ret_val = &sLocEngNiInterface;
   }
   else if (strcmp(name, AGPS_RIL_INTERFACE) == 0)
   {
       char baseband[PROPERTY_VALUE_MAX];
       property_get("ro.baseband", baseband, "msm");
       if (strcmp(baseband, "csfb") == 0)
       {
           ret_val = &sLocEngAGpsRilInterface;
       }
   }
   else if (strcmp(name, GPS_GEOFENCING_INTERFACE) == 0)
   {
       if ((gps_conf.CAPABILITIES | GPS_CAPABILITY_GEOFENCING) == gps_conf.CAPABILITIES ){
           ret_val = get_geofence_interface();
       }
   }
   else if (strcmp(name, SUPL_CERTIFICATE_INTERFACE) == 0)
   {
       ret_val = &sLocEngAGpsCertInterface;
   }
   else if (strcmp(name, GNSS_CONFIGURATION_INTERFACE) == 0)
   {
       ret_val = &sLocEngConfigInterface;
   }
   else if (strcmp(name, GPS_MEASUREMENT_INTERFACE) == 0)
   {
       ret_val = &sLocEngGpsMeasurementInterface;
   }
   else
   {
      LOC_LOGE ("get_extension: Invalid interface passed in\n");
   }
    EXIT_LOG(%p, ret_val);
    return ret_val;
}

/*===========================================================================
FUNCTION    loc_agps_init

DESCRIPTION
   Initialize the AGps interface.

DEPENDENCIES
   NONE

RETURN VALUE
   0

SIDE EFFECTS
   N/A

===========================================================================*/
static void loc_agps_init(AGpsCallbacks* callbacks)
{
    ENTRY_LOG();
    loc_eng_agps_init(loc_afw_data, (AGpsExtCallbacks*)callbacks);
    EXIT_LOG(%s, VOID_RET);
}

/*===========================================================================
FUNCTION    loc_agps_open

DESCRIPTION
   This function is called when on-demand data connection opening is successful.
It should inform ARM 9 about the data open result.

DEPENDENCIES
   NONE

RETURN VALUE
   0

SIDE EFFECTS
   N/A

===========================================================================*/
static int loc_agps_open(const char* apn)
{
    ENTRY_LOG();
    AGpsType agpsType = AGPS_TYPE_SUPL;
    AGpsBearerType bearerType = AGPS_APN_BEARER_IPV4;
    int ret_val = loc_eng_agps_open(loc_afw_data, agpsType, apn, bearerType);

    EXIT_LOG(%d, ret_val);
    return ret_val;
}

/*===========================================================================
FUNCTION    loc_agps_open_with_apniptype

DESCRIPTION
   This function is called when on-demand data connection opening is successful.
It should inform ARM 9 about the data open result.

DEPENDENCIES
   NONE

RETURN VALUE
   0

SIDE EFFECTS
   N/A

===========================================================================*/
static int  loc_agps_open_with_apniptype(const char* apn, ApnIpType apnIpType)
{
    ENTRY_LOG();
    AGpsType agpsType = AGPS_TYPE_SUPL;
    AGpsBearerType bearerType;

    switch (apnIpType) {
        case APN_IP_IPV4:
            bearerType = AGPS_APN_BEARER_IPV4;
            break;
        case APN_IP_IPV6:
            bearerType = AGPS_APN_BEARER_IPV6;
            break;
        case APN_IP_IPV4V6:
            bearerType = AGPS_APN_BEARER_IPV4V6;
            break;
        default:
            bearerType = AGPS_APN_BEARER_INVALID;
            break;
    }

    int ret_val = loc_eng_agps_open(loc_afw_data, agpsType, apn, bearerType);

    EXIT_LOG(%d, ret_val);
    return ret_val;
}

/*===========================================================================
FUNCTION    loc_agps_closed

DESCRIPTION
   This function is called when on-demand data connection closing is done.
It should inform ARM 9 about the data close result.

DEPENDENCIES
   NONE

RETURN VALUE
   0

SIDE EFFECTS
   N/A

===========================================================================*/
static int loc_agps_closed()
{
    ENTRY_LOG();
    AGpsType agpsType = AGPS_TYPE_SUPL;
    int ret_val = loc_eng_agps_closed(loc_afw_data, agpsType);

    EXIT_LOG(%d, ret_val);
    return ret_val;
}

/*===========================================================================
FUNCTION    loc_agps_open_failed

DESCRIPTION
   This function is called when on-demand data connection opening has failed.
It should inform ARM 9 about the data open result.

DEPENDENCIES
   NONE

RETURN VALUE
   0

SIDE EFFECTS
   N/A

===========================================================================*/
int loc_agps_open_failed()
{
    ENTRY_LOG();
    AGpsType agpsType = AGPS_TYPE_SUPL;
    int ret_val = loc_eng_agps_open_failed(loc_afw_data, agpsType);

    EXIT_LOG(%d, ret_val);
    return ret_val;
}

/*===========================================================================
FUNCTION    loc_agps_set_server

DESCRIPTION
   If loc_eng_set_server is called before loc_eng_init, it doesn't work. This
   proxy buffers server settings and calls loc_eng_set_server when the client is
   open.

DEPENDENCIES
   NONE

RETURN VALUE
   0

SIDE EFFECTS
   N/A

===========================================================================*/
static int loc_agps_set_server(AGpsType type, const char* hostname, int port)
{
    ENTRY_LOG();
    LocServerType serverType;
    switch (type) {
    case AGPS_TYPE_SUPL:
        serverType = LOC_AGPS_SUPL_SERVER;
        break;
    case AGPS_TYPE_C2K:
        serverType = LOC_AGPS_CDMA_PDE_SERVER;
        break;
    default:
        serverType = LOC_AGPS_SUPL_SERVER;
    }
    int ret_val = loc_eng_set_server_proxy(loc_afw_data, serverType, hostname, port);

    EXIT_LOG(%d, ret_val);
    return ret_val;
}

/*===========================================================================
FUNCTIONf571
    loc_xtra_init

DESCRIPTION
   Initialize XTRA module.

DEPENDENCIES
   None

RETURN VALUE
   0: success

SIDE EFFECTS
   N/A

===========================================================================*/
static int loc_xtra_init(GpsXtraCallbacks* callbacks)
{
    ENTRY_LOG();
    GpsXtraExtCallbacks extCallbacks;
    memset(&extCallbacks, 0, sizeof(extCallbacks));
    extCallbacks.download_request_cb = callbacks->download_request_cb;
    int ret_val = loc_eng_xtra_init(loc_afw_data, &extCallbacks);

    EXIT_LOG(%d, ret_val);
    return ret_val;
}


/*===========================================================================
FUNCTION    loc_xtra_inject_data

DESCRIPTION
   Initialize XTRA module.

DEPENDENCIES
   None

RETURN VALUE
   0: success

SIDE EFFECTS
   N/A

===========================================================================*/
static int loc_xtra_inject_data(char* data, int length)
{
    ENTRY_LOG();
    int ret_val = -1;
    if( (data != NULL) && ((unsigned int)length <= XTRA_DATA_MAX_SIZE))
        ret_val = loc_eng_xtra_inject_data(loc_afw_data, data, length);
    else
        LOC_LOGE("%s, Could not inject XTRA data. Buffer address: %p, length: %d",
                 __func__, data, length);
    EXIT_LOG(%d, ret_val);
    return ret_val;
}

/*===========================================================================
FUNCTION    loc_gps_measurement_init

DESCRIPTION
   This function initializes the gps measurement interface

DEPENDENCIES
   NONE

RETURN VALUE
   None

SIDE EFFECTS
   N/A

===========================================================================*/
static int loc_gps_measurement_init(GpsMeasurementCallbacks* callbacks)
{
    ENTRY_LOG();
    int ret_val = loc_eng_gps_measurement_init(loc_afw_data,
                                               callbacks);

    EXIT_LOG(%d, ret_val);
    return ret_val;
}

/*===========================================================================
FUNCTION    loc_gps_measurement_close

DESCRIPTION
   This function closes the gps measurement interface

DEPENDENCIES
   NONE

RETURN VALUE
   None

SIDE EFFECTS
   N/A

===========================================================================*/
static void loc_gps_measurement_close()
{
    ENTRY_LOG();
    loc_eng_gps_measurement_close(loc_afw_data);

    EXIT_LOG(%s, VOID_RET);
}

/*===========================================================================
FUNCTION    loc_ni_init

DESCRIPTION
   This function initializes the NI interface

DEPENDENCIES
   NONE

RETURN VALUE
   None

SIDE EFFECTS
   N/A

===========================================================================*/
void loc_ni_init(GpsNiCallbacks *callbacks)
{
    ENTRY_LOG();
    loc_eng_ni_init(loc_afw_data,(GpsNiExtCallbacks*) callbacks);
    EXIT_LOG(%s, VOID_RET);
}

/*===========================================================================
FUNCTION    loc_ni_respond

DESCRIPTION
   This function sends an NI respond to the modem processor

DEPENDENCIES
   NONE

RETURN VALUE
   None

SIDE EFFECTS
   N/A

===========================================================================*/
void loc_ni_respond(int notif_id, GpsUserResponseType user_response)
{
    ENTRY_LOG();
    loc_eng_ni_respond(loc_afw_data, notif_id, user_response);
    EXIT_LOG(%s, VOID_RET);
}

// Below stub functions are members of sLocEngAGpsRilInterface
static void loc_agps_ril_init( AGpsRilCallbacks* callbacks ) {}
static void loc_agps_ril_set_ref_location(const AGpsRefLocation *agps_reflocation, size_t sz_struct) {}
static void loc_agps_ril_set_set_id(AGpsSetIDType type, const char* setid) {}
static void loc_agps_ril_ni_message(uint8_t *msg, size_t len) {}
static void loc_agps_ril_update_network_state(int connected, int type, int roaming, const char* extra_info) {}

/*===========================================================================
FUNCTION    loc_agps_ril_update_network_availability

DESCRIPTION
   Sets data call allow vs disallow flag to modem
   This is the only member of sLocEngAGpsRilInterface implemented.

DEPENDENCIES
   None

RETURN VALUE
   0: success

SIDE EFFECTS
   N/A

===========================================================================*/
static void loc_agps_ril_update_network_availability(int available, const char* apn)
{
    ENTRY_LOG();
    loc_eng_agps_ril_update_network_availability(loc_afw_data, available, apn);
    EXIT_LOG(%s, VOID_RET);
}

static int loc_agps_install_certificates(const DerEncodedCertificate* certificates,
                                         size_t length)
{
    ENTRY_LOG();
    int ret_val = loc_eng_agps_install_certificates(loc_afw_data, certificates, length);
    EXIT_LOG(%d, ret_val);
    return ret_val;
}
static int loc_agps_revoke_certificates(const Sha1CertificateFingerprint* fingerprints,
                                        size_t length)
{
    ENTRY_LOG();
    LOC_LOGE("%s:%d]: agps_revoke_certificates not supported");
    int ret_val = AGPS_CERTIFICATE_ERROR_GENERIC;
    EXIT_LOG(%d, ret_val);
    return ret_val;
}

static void loc_configuration_update(const char* config_data, int32_t length)
{
    ENTRY_LOG();
    loc_eng_configuration_update(loc_afw_data, config_data, length);
    switch (sGnssType)
    {
    case GNSS_GSS:
    case GNSS_AUTO:
    case GNSS_QCA1530:
        //APQ
        gps_conf.CAPABILITIES &= ~(GPS_CAPABILITY_MSA | GPS_CAPABILITY_MSB);
        break;
    }
    EXIT_LOG(%s, VOID_RET);
}

static void local_loc_cb(UlpLocation* location, void* locExt)
{
    ENTRY_LOG();
    if (NULL != location) {
        CALLBACK_LOG_CALLFLOW("location_cb - from", %d, location->position_source);

        if (NULL != gps_loc_cb) {
            gps_loc_cb(&location->gpsLocation);
        }
    }
    EXIT_LOG(%s, VOID_RET);
}

static void local_sv_cb(GpsSvStatus* sv_status, void* svExt)
{
    ENTRY_LOG();
    if (NULL != gps_sv_cb) {
        CALLBACK_LOG_CALLFLOW("sv_status_cb -", %d, sv_status->num_svs);
        gps_sv_cb(sv_status);
    }
    EXIT_LOG(%s, VOID_RET);
}

