/* Copyright (c) 2014, The Linux Foundation. All rights reserved.
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
#include <stdio.h>
#include <string.h>
#include <log_util.h>
#include <loc_misc_utils.h>
#include <ctype.h>

#define LOG_NDDEBUG 0
#define LOG_TAG "LocSvc_misc_utils"

int loc_util_split_string(char *raw_string, char **split_strings_ptr,
                          int max_num_substrings, char delimiter)
{
    int raw_string_index=0;
    int num_split_strings=0;
    unsigned char end_string=0;
    int raw_string_length=0;

    if(!raw_string || !split_strings_ptr) {
        LOC_LOGE("%s:%d]: NULL parameters", __func__, __LINE__);
        num_split_strings = -1;
        goto err;
    }
    LOC_LOGD("%s:%d]: raw string: %s\n", __func__, __LINE__, raw_string);
    raw_string_length = strlen(raw_string) + 1;
    split_strings_ptr[num_split_strings] = &raw_string[raw_string_index];
    for(raw_string_index=0; raw_string_index < raw_string_length; raw_string_index++) {
        if(raw_string[raw_string_index] == '\0')
            end_string=1;
        if((raw_string[raw_string_index] == delimiter) || end_string) {
            raw_string[raw_string_index] = '\0';
            LOC_LOGD("%s:%d]: split string: %s\n",
                     __func__, __LINE__, split_strings_ptr[num_split_strings]);
            num_split_strings++;
            if(((raw_string_index + 1) < raw_string_length) &&
               (num_split_strings < max_num_substrings)) {
                split_strings_ptr[num_split_strings] = &raw_string[raw_string_index+1];
            }
            else {
                break;
            }
        }
        if(end_string)
            break;
    }
err:
    LOC_LOGD("%s:%d]: num_split_strings: %d\n", __func__, __LINE__, num_split_strings);
    return num_split_strings;
}

void loc_util_trim_space(char *org_string)
{
    char *scan_ptr, *write_ptr;
    char *first_nonspace = NULL, *last_nonspace = NULL;

    if(org_string == NULL) {
        LOC_LOGE("%s:%d]: NULL parameter", __func__, __LINE__);
        goto err;
    }

    scan_ptr = write_ptr = org_string;

    while (*scan_ptr) {
        //Find the first non-space character
        if ( !isspace(*scan_ptr) && first_nonspace == NULL) {
            first_nonspace = scan_ptr;
        }
        //Once the first non-space character is found in the
        //above check, keep shifting the characters to the left
        //to replace the spaces
        if (first_nonspace != NULL) {
            *(write_ptr++) = *scan_ptr;
            //Keep track of which was the last non-space character
            //encountered
            //last_nonspace will not be updated in the case where
            //the string ends with spaces
            if ( !isspace(*scan_ptr)) {
                last_nonspace = write_ptr;
            }
        }
        scan_ptr++;
    }
    //Add NULL terminator after the last non-space character
    if (last_nonspace) { *last_nonspace = '\0'; }
err:
    return;
}
