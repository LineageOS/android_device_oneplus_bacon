/* Copyright (c) 2011-2012, 2015 The Linux Foundation. All rights reserved.
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

#ifndef LOC_LOG_H
#define LOC_LOG_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <ctype.h>
#include <stdlib.h>
#include "loc_target.h"

typedef struct
{
   const char *name;
   long        val;
} loc_name_val_s_type;

#define NAME_VAL(x) {"" #x "", x }

#define UNKNOWN_STR "UNKNOWN"

#define CHECK_MASK(type, value, mask_var, mask) \
   (((mask_var) & (mask)) ? (type) (value) : (type) (-1))

#define LOC_TABLE_SIZE(table) (sizeof(table)/sizeof((table)[0]))

/* Get names from value */
const char* loc_get_name_from_mask(const loc_name_val_s_type table[], size_t table_size, long mask);
const char* loc_get_name_from_val(const loc_name_val_s_type table[], size_t table_size, long value);
const char* loc_get_msg_q_status(int status);
const char* loc_get_target_name(unsigned int target);

extern const char* log_succ_fail_string(int is_succ);

extern char *loc_get_time(char *time_string, size_t buf_size);

#ifdef __cplusplus
}
#endif

#endif /* LOC_LOG_H */
