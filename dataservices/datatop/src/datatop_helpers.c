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
 * @file datatop_helpers.c
 * @brief Contains functions which output data.
 *
 * Contains functions which are used for printing data to output streams.
 * Handles all formatting for data output. Also contains functions which
 * are responsible for data gathering and collection.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <errno.h>
#include "datatop_interface.h"
#include "datatop_linked_list.h"
#include "datatop_fileops.h"

/**
 * @brief Prints the name and prefix of a datapoint.
 *
 * @param dp Dp whose name and prefix is printed.
 * @param prefix Directory where dp is contained.
 * @param fw File to print the information to.
 * @return FILE_ERROR - Writing to file was unsuccessful.
 * @return FILE_SUCCESS - Writing to file was successful.
 */
static int dtop_format_dp_names(struct dtop_data_point *dp, const char
						*prefix, FILE *fw)
{
	if (dp->prefix) {
		if (fprintf(fw, "\"%s:%s:%s\",", prefix, dp->prefix,
							dp->name) < 0)
			return FILE_ERROR;
	} else {
		if (fprintf(fw, "\"%s::%s\",", prefix, dp->name) < 0)
			return FILE_ERROR;
	}
	return FILE_SUCCESS;
}

/**
 * @brief Prints the value of a datapoint.
 *
 * Checks the type of the value and will print it accordingly.
 *
 * @param dp Pointer to the data_point struct which holds the value that will
 *           be printed.
 * @param fw File to print the information to.
 * @return FILE_ERROR - Writing to file was unsuccessful.
 * @return FILE_SUCCESS - Writing to file was successful.
 */
static int dtop_format_dp_values(struct dtop_data_point *dp, FILE *fw)
{
	switch (dp->type) {
	case DTOP_ULONG:
		if (fprintf(fw, "%"PRIu64, dp->data.d_ulong) < 0)
			return FILE_ERROR;
	break;
	case DTOP_LONG:
		if (fprintf(fw, "%"PRId64, dp->data.d_long) < 0)
			return FILE_ERROR;
	break;
	case DTOP_UINT:
		if (fprintf(fw, "%d", dp->data.d_uint) < 0)
			return FILE_ERROR;
	break;
	case DTOP_INT:
		if (fprintf(fw, "%u", dp->data.d_uint) < 0)
			return FILE_ERROR;
	break;
	case DTOP_UCHAR:
		if (fprintf(fw, "%c,", dp->data.d_uchar) < 0)
			return FILE_ERROR;
		if (fprintf(fw, "(0x%02X)", dp->data.d_uchar) < 0)
			return FILE_ERROR;
	break;
	case DTOP_CHAR:
		if (fprintf(fw, "%c,", dp->data.d_char) < 0)
			return FILE_ERROR;
		if (fprintf(fw, "(%d)", dp->data.d_char) < 0)
			return FILE_ERROR;
	break;
	case DTOP_STR:
		if (fprintf(fw, "\"%s\"", dp->data.d_str) < 0)
			return FILE_ERROR;
	break;
	default:
		if (fprintf(fw, "UNKNOWN_TYPE") < 0)
			return FILE_ERROR;
	break;
	}
	return FILE_SUCCESS;
}

/**
 * @brief Prints the name and prefix of a dp, formatted appropriately.
 *
 * @param dpset data_point_gatherer used to access dp directory.
 * @param dp data_point used to get datapoint prefix if available.
 */
static void dtop_format_text_for_snapshot
	(struct dtop_data_point_gatherer *dpset, struct dtop_data_point dp)
{
	printf("%s:", dpset->prefix);
	if (dp.prefix)
		printf("%s:", dp.prefix);

	printf("%s::", dp.name);
}

/**
 * @brief Prints a datapoint value to a specified csv file.
 *
 * @param dp Datapoint that holds the value to be printed.
 * @param fw File to print to.
 * @return FILE_ERROR - Writing to file was unsuccessful.
 * @return FILE_SUCCESS - Writing to file was successful.
 */
static int dtop_print_dp_csv(struct dtop_data_point *dp, FILE *fw)
{
	if (dtop_format_dp_values(dp, fw) == FILE_ERROR)
		return FILE_ERROR;
	if (fprintf(fw, ",") < 0)
		return FILE_ERROR;
	return FILE_SUCCESS;
}

/**
 * @brief Prints a datapoint value to the terminal.
 *
 * @param dp Holds the value to be printed print.
 * @param prefix Used to print prefix of the data_point.
 */
static void dtop_print_dp(struct dtop_data_point *dp, const char *prefix)
{
	dtop_format_dp_names(dp, prefix, stdout);
	printf(" ");
	dtop_format_dp_values(dp, stdout);
	printf("\n");
}

/**
 * @brief Finds delta(value) of a datapoint.
 *
 * Function accounts for different types that values may be.
 *
 * @param dpset Pointer to a data_point used as another parameter for printing.
 * @param dp Datapoint which contains the value to find the difference of.
 */
static void dtop_handle_dp_type_for_snapshot(
	struct dtop_data_point_gatherer *dpset, struct dtop_data_point dp)
{
	int64_t int64;

	switch (dp.type) {
	case DTOP_ULONG:
	default:
		/* This is less than ideal. Replace with 128-bit ops later */
		int64 = (int64_t)dp.data.d_ulong
			- (int64_t)dp.initial_data.d_ulong;
		if (int64 != 0) {
			dtop_format_text_for_snapshot(dpset, dp);
			printf("%"PRId64"\n", int64);
		}
	break;

	case DTOP_LONG:
		/* This is less than ideal. Replace with 128-bit ops later */
		int64 = (int64_t)dp.data.d_long
			- (int64_t)dp.initial_data.d_long;
		if (int64 != 0) {
			dtop_format_text_for_snapshot(dpset, dp);
			printf("%"PRId64"\n", int64);
		}
	break;

	case DTOP_UINT:
		int64 = (int64_t)dp.data.d_uint
			- (int64_t)dp.initial_data.d_uint;
		if (int64 != 0) {
			dtop_format_text_for_snapshot(dpset, dp);
			printf("%"PRId64"\n", int64);
		}
	break;

	case DTOP_INT:
		int64 = (int64_t)dp.data.d_int
			- (int64_t)dp.initial_data.d_int;
		if (int64 != 0) {
			dtop_format_text_for_snapshot(dpset, dp);
			printf("%"PRId64"\n", int64);
		}
	break;
	}
}

/**
 * @brief Calls the dtop_print_dp_csv function for each data_point a dpg has access to.
 *
 * @param dpg A data_point_gatherer struct that is iterated through for each datapoint.
 * @param fw File to print datapoint values to.
 * @return FILE_ERROR - Writing to file was unsuccessful.
 * @return FILE_SUCCESS - Writing to file was successful.
 */
static int dtop_print_dpg_csv(struct dtop_data_point_gatherer *dpg, FILE *fw)
{
	int i;

	for (i = 0; i < dpg->data_points_len; i++)
		if (dtop_print_dp_csv(&(dpg->data_points[i]), fw) == FILE_ERROR)
			return FILE_ERROR;
	return FILE_SUCCESS;
}

/**
 * @brief Calls the dtop_format_dp_names function for each data_point a dpg has access to.
 *
 * @param dpg A data_point_gatherer struct that is iterated through for each datapoint.
 * @param fw File to printg datapoint names and prefixes to.
 * @return FILE_ERROR - Writing to file was unsuccessful.
 * @return FILE_SUCCESS - Writing to file was successful.
 */
int dtop_print_dpg_names_csv(struct dtop_data_point_gatherer *dpg, FILE *fw)
{
	int i;

	for (i = 0; i < dpg->data_points_len; i++)
		if (dtop_format_dp_names(&(dpg->data_points[i]),
		dpg->prefix, fw) == FILE_ERROR)
			return FILE_ERROR;

	return FILE_SUCCESS;
}

/**
 * @brief Prints all dp values to a specified file.
 *
 * This function is responsible for the printing of all data_point values
 * to a specified file. It will iterate through the linked list which contains
 * all of the dpgs and will print each dp value, being sure to flush the buffer.
 *
 * @param dpg_list Pointer to first node of linked list which contains all dpgs.
 * @param fw File that data prints to.
 * @return FILE_ERROR - Writing to file was unsuccessful.
 * @return FILE_SUCCESS - Writing to file was successful.
 */
int dtop_write_pollingdata_csv(struct dtop_linked_list *dpg_list, FILE *fw)
{
	struct dtop_linked_list *curr_ptr = dpg_list;
	struct dtop_data_point_gatherer *dpset;

	while (curr_ptr) {
		dpset = (struct dtop_data_point_gatherer *) curr_ptr->data;
		if (dtop_print_dpg_csv(dpset, fw) == FILE_ERROR)
			return FILE_ERROR;
		curr_ptr = curr_ptr->next_ptr;
		fflush(fw);
	}

	if (fprintf(fw, "\n") < 0)
		return FILE_ERROR;

	return FILE_SUCCESS;
}

/**
 * @brief Calls the dtop_print_dp function for each data_point a dpg has access to.
 *
 * @param dpg A data_point_gatherer struct that is iterated through for each datapoint.
 */
void dtop_print_dpg(struct dtop_data_point_gatherer *dpg)
{
	int i;
	for (i = 0; i < dpg->data_points_len; i++)
		dtop_print_dp(&(dpg->data_points[i]), dpg->prefix);
}

/**
 * @brief Stores the values for the datapoints and populates the initial value.
 *
 * @param dp A datapoint whose value will be stored.
 * @param str Str used for sscanf function call to find value of dp.
 */
void dtop_store_dp(struct dtop_data_point *dp, const char *str)
{
	switch (dp->type) {
	case DTOP_ULONG:
		sscanf(str, "%"PRIu64, &(dp->data.d_ulong));
		if (dp->initial_data_populated == NOT_POPULATED) {
			dp->initial_data.d_ulong = dp->data.d_ulong;
			dp->initial_data_populated = POPULATED;
		}
	break;
	case DTOP_LONG:
		sscanf(str, "%"PRId64, &(dp->data.d_long));
		if (dp->initial_data_populated == NOT_POPULATED) {
			dp->initial_data.d_long = dp->data.d_long;
			dp->initial_data_populated = POPULATED;
		}
	break;
	case DTOP_UINT:
		sscanf(str, "%u",  &(dp->data.d_uint));
		if (dp->initial_data_populated == NOT_POPULATED) {
			dp->initial_data.d_uint = dp->data.d_uint;
			dp->initial_data_populated = POPULATED;
		}
	break;
	case DTOP_INT:
		sscanf(str, "%d",  &(dp->data.d_int));
		if (dp->initial_data_populated == NOT_POPULATED) {
			dp->initial_data.d_int = dp->data.d_int;
			dp->initial_data_populated = POPULATED;
		}
	break;
	case DTOP_UCHAR:
		sscanf(str, "%c",  &(dp->data.d_uchar));
		if (dp->initial_data_populated == NOT_POPULATED) {
			dp->initial_data.d_uchar = dp->data.d_uchar;
			dp->initial_data_populated = POPULATED;
		}
	break;
	case DTOP_CHAR:
		sscanf(str, "%c",  &(dp->data.d_char));
		if (dp->initial_data_populated == NOT_POPULATED) {
			dp->initial_data.d_char = dp->data.d_char;
			dp->initial_data_populated = POPULATED;
		}
	break;
	case DTOP_STR:
		sscanf(str, "%s",  dp->data.d_str);
		if (dp->initial_data_populated == NOT_POPULATED) {
			memcpy(dp->initial_data.d_str, dp->data.d_str,
			       DTOP_DP_MAX_STR_LEN);
			dp->initial_data_populated = POPULATED;
		}
	break;
	default:
	break;
	}
}

/**
 * @brief Responsible for calculating and printing current time to file.
 *
 * Prints the time since 1970, in Seconds and Milliseconds.
 *
 * @param fw File that time is printed to.
 * @return FILE_ERROR - Writing to file was unsuccessful.
 * @return FILE_SUCCESS - Writing to file was successful.
 */
int dtop_print_time_at_poll(FILE *fw)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);

	if (fprintf(fw, "%10ld", tv.tv_sec) < 0)
		return FILE_ERROR;

	if (fprintf(fw, ".%06ld,", tv.tv_usec) < 0)
		return FILE_ERROR;

	return FILE_SUCCESS;
}

/**
 * @brief Polls all dp values and updates each value.
 *
 * @param dpg_list Pointer to first node of linked list which contains all dpgs.
 */
void dtop_poll(struct dtop_linked_list *dpg_list)
{
	struct dtop_linked_list *curr_ptr = dpg_list;
	struct dtop_data_point_gatherer *dpset;

	while (curr_ptr) {
		dpset = (struct dtop_data_point_gatherer *) curr_ptr->data;
		dpset->poll(dpset);
		curr_ptr = curr_ptr->next_ptr;
	}
}

/**
 * @brief Prints the delta(value) of all data_points to terminal.
 *
 * @param dpg_list Pointer to first node of linked list which contains all dpgs.
 */
void dtop_print_snapshot_diff(struct dtop_linked_list *dpg_list)
{
	int i;

	struct dtop_linked_list *curr_ptr = dpg_list;
	struct dtop_data_point_gatherer *dpset;
	printf("\n");
	printf("Change In Datapoint Values\n");
	printf("---------------------------\n");
	while (curr_ptr) {
		dpset = (struct dtop_data_point_gatherer *) curr_ptr->data;
		for (i = 0; i < dpset->data_points_len; i++)
			dtop_handle_dp_type_for_snapshot(dpset,
					  dpset->data_points[i]);
		curr_ptr = curr_ptr->next_ptr;
	}
	printf("\n");
}

/**
 * @brief Resets the initial values of all data_points.
 *
 * @param dpg_list Pointer to first node of linked list which contains all dpgs.
 */
void dtop_reset_dp_initial_values(struct dtop_linked_list *dpg_list)
{
	int i;

	struct dtop_linked_list *curr_ptr = dpg_list;
	struct dtop_data_point_gatherer *dpset;

	while (curr_ptr) {
		dpset = (struct dtop_data_point_gatherer *) curr_ptr->data;
		for (i = 0; i < dpset->data_points_len; i++)
			dpset->data_points[i].initial_data_populated
							= NOT_POPULATED;
		curr_ptr = curr_ptr->next_ptr;
	}
}

/**
 * @brief Calls deconstructor method for all dpgs dynamically created.
 *
 * Checks to see if each dpg created has a deconstructor method. If not null,
 * function calls the appropiate deconstructor method to deallocate memory.
 *
 * @param dpg_list Pointer to first node of linked list which contains all dpgs.
 */
void deconstruct_dpgs(struct dtop_linked_list *dpg_list)
{
	struct dtop_linked_list *curr_ptr = dpg_list;
	struct dtop_data_point_gatherer *dpset;

	while (curr_ptr) {
		dpset = (struct dtop_data_point_gatherer *) curr_ptr->data;
		if (dpset->deconstruct)
			dpset->deconstruct(dpset);
		curr_ptr = curr_ptr->next_ptr;
	}
}
