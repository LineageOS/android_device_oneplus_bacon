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
#define LOG_TAG "LocSvc_utils_cfg"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>
#include <loc_cfg.h>
#include <log_util.h>
#include <loc_misc_utils.h>
#ifdef USE_GLIB
#include <glib.h>
#endif
#include "platform_lib_includes.h"

/*=============================================================================
 *
 *                          GLOBAL DATA DECLARATION
 *
 *============================================================================*/

/* Parameter data */
static uint32_t DEBUG_LEVEL = 0xff;
static uint32_t TIMESTAMP = 0;

/* Parameter spec table */
static loc_param_s_type loc_param_table[] =
{
    {"DEBUG_LEVEL",    &DEBUG_LEVEL, NULL,    'n'},
    {"TIMESTAMP",      &TIMESTAMP,   NULL,    'n'},
};
int loc_param_num = sizeof(loc_param_table) / sizeof(loc_param_s_type);

typedef struct loc_param_v_type
{
    char* param_name;
    char* param_str_value;
    int param_int_value;
    double param_double_value;
}loc_param_v_type;

/*===========================================================================
FUNCTION loc_set_config_entry

DESCRIPTION
   Potentially sets a given configuration table entry based on the passed in
   configuration value. This is done by using a string comparison of the
   parameter names and those found in the configuration file.

PARAMETERS:
   config_entry: configuration entry in the table to possibly set
   config_value: value to store in the entry if the parameter names match

DEPENDENCIES
   N/A

RETURN VALUE
   None

SIDE EFFECTS
   N/A
===========================================================================*/
int loc_set_config_entry(loc_param_s_type* config_entry, loc_param_v_type* config_value)
{
    int ret=-1;
    if(NULL == config_entry || NULL == config_value)
    {
        LOC_LOGE("%s: INVALID config entry or parameter", __FUNCTION__);
        return ret;
    }

    if (strcmp(config_entry->param_name, config_value->param_name) == 0 &&
        config_entry->param_ptr)
    {
        switch (config_entry->param_type)
        {
        case 's':
            if (strcmp(config_value->param_str_value, "NULL") == 0)
            {
                *((char*)config_entry->param_ptr) = '\0';
            }
            else {
                strlcpy((char*) config_entry->param_ptr,
                        config_value->param_str_value,
                        LOC_MAX_PARAM_STRING + 1);
            }
            /* Log INI values */
            LOC_LOGD("%s: PARAM %s = %s", __FUNCTION__,
                     config_entry->param_name, (char*)config_entry->param_ptr);

            if(NULL != config_entry->param_set)
            {
                *(config_entry->param_set) = 1;
            }
            ret = 0;
            break;
        case 'n':
            *((int *)config_entry->param_ptr) = config_value->param_int_value;
            /* Log INI values */
            LOC_LOGD("%s: PARAM %s = %d", __FUNCTION__,
                     config_entry->param_name, config_value->param_int_value);

            if(NULL != config_entry->param_set)
            {
                *(config_entry->param_set) = 1;
            }
            ret = 0;
            break;
        case 'f':
            *((double *)config_entry->param_ptr) = config_value->param_double_value;
            /* Log INI values */
            LOC_LOGD("%s: PARAM %s = %f", __FUNCTION__,
                     config_entry->param_name, config_value->param_double_value);

            if(NULL != config_entry->param_set)
            {
                *(config_entry->param_set) = 1;
            }
            ret = 0;
            break;
        default:
            LOC_LOGE("%s: PARAM %s parameter type must be n, f, or s",
                     __FUNCTION__, config_entry->param_name);
        }
    }
    return ret;
}

/*===========================================================================
FUNCTION loc_fill_conf_item

DESCRIPTION
   Takes a line of configuration item and sets defined values based on
   the passed in configuration table. This table maps strings to values to
   set along with the type of each of these values.

PARAMETERS:
   input_buf : buffer contanis config item
   config_table: table definition of strings to places to store information
   table_length: length of the configuration table

DEPENDENCIES
   N/A

RETURN VALUE
   0: Number of records in the config_table filled with input_buf

SIDE EFFECTS
   N/A
===========================================================================*/
int loc_fill_conf_item(char* input_buf,
                       loc_param_s_type* config_table, uint32_t table_length)
{
    int ret = 0;

    if (input_buf && config_table) {
        char *lasts;
        loc_param_v_type config_value;
        memset(&config_value, 0, sizeof(config_value));

        /* Separate variable and value */
        config_value.param_name = strtok_r(input_buf, "=", &lasts);
        /* skip lines that do not contain "=" */
        if (config_value.param_name) {
            config_value.param_str_value = strtok_r(NULL, "=", &lasts);

            /* skip lines that do not contain two operands */
            if (config_value.param_str_value) {
                /* Trim leading and trailing spaces */
                loc_util_trim_space(config_value.param_name);
                loc_util_trim_space(config_value.param_str_value);

                /* Parse numerical value */
                if ((strlen(config_value.param_str_value) >=3) &&
                    (config_value.param_str_value[0] == '0') &&
                    (tolower(config_value.param_str_value[1]) == 'x'))
                {
                    /* hex */
                    config_value.param_int_value = (int) strtol(&config_value.param_str_value[2],
                                                                (char**) NULL, 16);
                }
                else {
                    config_value.param_double_value = (double) atof(config_value.param_str_value); /* float */
                    config_value.param_int_value = atoi(config_value.param_str_value); /* dec */
                }

                for(uint32_t i = 0; NULL != config_table && i < table_length; i++)
                {
                    if(!loc_set_config_entry(&config_table[i], &config_value)) {
                        ret += 1;
                    }
                }
            }
        }
    }

    return ret;
}

/*===========================================================================
FUNCTION loc_read_conf_r (repetitive)

DESCRIPTION
   Reads the specified configuration file and sets defined values based on
   the passed in configuration table. This table maps strings to values to
   set along with the type of each of these values.
   The difference between this and loc_read_conf is that this function returns
   the file pointer position at the end of filling a config table. Also, it
   reads a fixed number of parameters at a time which is equal to the length
   of the configuration table. This functionality enables the caller to
   repeatedly call the function to read data from the same file.

PARAMETERS:
   conf_fp : file pointer
   config_table: table definition of strings to places to store information
   table_length: length of the configuration table

DEPENDENCIES
   N/A

RETURN VALUE
   0: Table filled successfully
   1: No more parameters to read
  -1: Error filling table

SIDE EFFECTS
   N/A
===========================================================================*/
int loc_read_conf_r(FILE *conf_fp, loc_param_s_type* config_table, uint32_t table_length)
{
    int ret=0;

    unsigned int num_params=table_length;
    if(conf_fp == NULL) {
        LOC_LOGE("%s:%d]: ERROR: File pointer is NULL\n", __func__, __LINE__);
        ret = -1;
        goto err;
    }

    /* Clear all validity bits */
    for(uint32_t i = 0; NULL != config_table && i < table_length; i++)
    {
        if(NULL != config_table[i].param_set)
        {
            *(config_table[i].param_set) = 0;
        }
    }

    char input_buf[LOC_MAX_PARAM_LINE];  /* declare a char array */

    LOC_LOGD("%s:%d]: num_params: %d\n", __func__, __LINE__, num_params);
    while(num_params)
    {
        if(!fgets(input_buf, LOC_MAX_PARAM_LINE, conf_fp)) {
            LOC_LOGD("%s:%d]: fgets returned NULL\n", __func__, __LINE__);
            break;
        }

        num_params -= loc_fill_conf_item(input_buf, config_table, table_length);
    }

err:
    return ret;
}

/*===========================================================================
FUNCTION loc_udpate_conf

DESCRIPTION
   Parses the passed in buffer for configuration items, and update the table
   that is also passed in.

Reads the specified configuration file and sets defined values based on
   the passed in configuration table. This table maps strings to values to
   set along with the type of each of these values.

PARAMETERS:
   conf_data: configuration items in bufferas a string
   length: strlen(conf_data)
   config_table: table definition of strings to places to store information
   table_length: length of the configuration table

DEPENDENCIES
   N/A

RETURN VALUE
   number of the records in the table that is updated at time of return.

SIDE EFFECTS
   N/A
===========================================================================*/
int loc_update_conf(const char* conf_data, int32_t length,
                    loc_param_s_type* config_table, uint32_t table_length)
{
    int ret = -1;

    if (conf_data && length && config_table && table_length) {
        // make a copy, so we do not tokenize the original data
        char* conf_copy = (char*)malloc(length+1);

        if (conf_copy != NULL)
        {
            memcpy(conf_copy, conf_data, length);
            // we hard NULL the end of string to be safe
            conf_copy[length] = 0;

            // start with one record off
            uint32_t num_params = table_length - 1;
            char* saveptr = NULL;
            char* input_buf = strtok_r(conf_copy, "\n", &saveptr);
            ret = 0;

            LOC_LOGD("%s:%d]: num_params: %d\n", __func__, __LINE__, num_params);
            while(num_params && input_buf) {
                ret++;
                num_params -= loc_fill_conf_item(input_buf, config_table, table_length);
                input_buf = strtok_r(NULL, "\n", &saveptr);
            }
            free(conf_copy);
        }
    }

    return ret;
}

/*===========================================================================
FUNCTION loc_read_conf

DESCRIPTION
   Reads the specified configuration file and sets defined values based on
   the passed in configuration table. This table maps strings to values to
   set along with the type of each of these values.

PARAMETERS:
   conf_file_name: configuration file to read
   config_table: table definition of strings to places to store information
   table_length: length of the configuration table

DEPENDENCIES
   N/A

RETURN VALUE
   None

SIDE EFFECTS
   N/A
===========================================================================*/
void loc_read_conf(const char* conf_file_name, loc_param_s_type* config_table,
                   uint32_t table_length)
{
    FILE *conf_fp = NULL;
    char *lasts;
    loc_param_v_type config_value;
    uint32_t i;

    if((conf_fp = fopen(conf_file_name, "r")) != NULL)
    {
        LOC_LOGD("%s: using %s", __FUNCTION__, conf_file_name);
        if(table_length && config_table) {
            loc_read_conf_r(conf_fp, config_table, table_length);
            rewind(conf_fp);
        }
        loc_read_conf_r(conf_fp, loc_param_table, loc_param_num);
        fclose(conf_fp);
    }
    /* Initialize logging mechanism with parsed data */
    loc_logger_init(DEBUG_LEVEL, TIMESTAMP);
}
