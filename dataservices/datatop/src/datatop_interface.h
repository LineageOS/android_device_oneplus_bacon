/************************************************************************
Copyright (c) 2015, The Linux Foundation. All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
************************************************************************/

/**
 * @file datatop_interface.h
 * @brief Declares functions held within datatop.c and datatop_helpers.c
 *
 * Declares functions which are held within datatop.c and datatop_helpers.c.
 * Also defines data structures used for storing data gathered during polling
 * such as datapoint names, values, and prefixes along with other valuable
 * information.
 */

#ifndef DATATOP_INTERFACE_H
#define DATATOP_INTERFACE_H

#include <inttypes.h>
#include "datatop_linked_list.h"

#define DTOP_ULONG 0
#define DTOP_LONG  1
#define DTOP_UINT  2
#define DTOP_INT   3
#define DTOP_UCHAR 4
#define DTOP_CHAR  5
#define DTOP_STR   6

#define FILE_ERROR       -1
#define FILE_SUCCESS      0
#define SKIP              1
#define DO_NOT_SKIP       0
#define POPULATED         1
#define NOT_POPULATED     0

#define DTOP_POLL_OK      0
#define DTOP_POLL_IO_ERR  1
#define NOT_CHECKED       0

#define QUIT              1

#define DTOP_DP_MAX_STR_LEN 32

#define DTOP_DP_HFILL   .initial_data_populated = NOT_POPULATED, \
			.skip = 0

/**
 * @struct dtop_data_union
 * @brief Provides the type for dp value.
 */
union dtop_data_union {
	uint64_t d_ulong;
	int64_t d_long;
	uint32_t d_uint;
	int32_t d_int;
	uint8_t d_uchar;
	int8_t d_char;
	char d_str[DTOP_DP_MAX_STR_LEN];
};

/**
 * @struct dtop_data_point
 * @brief Individual datapoint in a file.
 *
 * @var dtop_data_point::name
 * Stores the datapoints name.
 * @var dtop_data_point::prefix
 * Stores the individual prefix for the dp.
 * @var dtop_data_point::type
 * Type dp value is, see definitions.
 * @var dtop_data_point::initial_data
 * Holds the initial value of the dp the first time it was polled.
 * @var dtop_data_point::initial_data_populated
 * Variable that is changed when initial_data is populated.
 * @var dtop_data_point::data
 * Value of the dp at the most recent poll.
 */
struct dtop_data_point {
	char *name;
	char *prefix;

	/* Results of polling */
	char type;
	union dtop_data_union initial_data;
	char initial_data_populated;
	union dtop_data_union data;

	/* Skip on subsequent polls */
	char skip;
};

/**
 * @struct dtop_data_point_gatherer
 * @brief Struct used to hold data about a set of collected data.
 *
 * @var dtop_data_point_gatherer::prefix
 * Name of directory which data is collected from.
 * @var dtop_data_point_gatherer::file
 * File path that data is collected from.
 * @var dtop_data_point_gatherer::poll
 * Poll function takes a dtop_data_point_gatherer as parameter.
 * int equals, DTOP_POLL_IO_ERR - Poll of dpg unsuccessful, or
 * DTOP_POLL_OK - Poll of dpg successful.
 * @var dtop_data_point_gatherer::data_points
 * Pointer to a dtop_data_point struct (dp).
 * @var dtop_data_point_gatherer::data_points_len
 * Number of elements in the array of dp's the dpg accesses.
 */
struct dtop_data_point_gatherer {
	char *prefix;
	char *file;
	int (*poll)(struct dtop_data_point_gatherer *dpg);
	void (*deconstruct)(struct dtop_data_point_gatherer *dpg);

	struct dtop_data_point *data_points;
	int data_points_len;

	/* Private data */
	void *priv;
};

void dtop_register(struct dtop_data_point_gatherer *dpg);
void dtop_store_dp(struct dtop_data_point *dp, const char *str);
void dtop_print_dpg(struct dtop_data_point_gatherer *dpg);
void get_snapshot_diff(struct dtop_linked_list *dpg_list);
void dtop_print_snapshot_diff(struct dtop_linked_list *dpg_list);
void dtop_poll(struct dtop_linked_list *dpg_list);
int dtop_print_time_at_poll(FILE *fw);
int dtop_print_dpg_names_csv(struct dtop_data_point_gatherer *dpg, FILE *fw);
int dtop_write_pollingdata_csv(struct dtop_linked_list *dpg_list, FILE *fw);
void dtop_reset_dp_initial_values(struct dtop_linked_list *dpg_list);
void deconstruct_dpgs(struct dtop_linked_list *dpg_list);
int dtop_print_system_snapshot(char *file);


#ifndef HAVE_STRL_FUNCTIONS
#define strlcpy(X,Y,Z) strcpy(X,Y)
#define strlcat(X,Y,Z) strcat(X,Y)
#endif /* HAVE_STRL_FUNCTIONS */

#endif /*  DATATOP_INTERFACE_H */
