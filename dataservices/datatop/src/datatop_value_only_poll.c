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
 * @file datatop_value_only_poll.c
 * @brief Adds ability for data collection from files with only values
 *
 * File contains methods for searching and polling data from
 * value_only files, meaning a file with a single line, containing
 * only values.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "datatop_interface.h"
#include "datatop_fileops.h"
#include "datatop_str.h"

#define DTOP_SINGLE_SIZE 8192
#define DTOP_SINGLE_LINE (DTOP_SINGLE_SIZE>>2)

/**
 * @brief Stores the data collected from a value_only files.
 *
 * @param dpg Struct that polled data is added to.
 * @return DTOP_POLL_IO_ERR - Poll of dpg unsuccessful.
 * @return DTOP_POLL_OK - Poll of dpg successful.
 */
int dtop_value_only_poll(struct dtop_data_point_gatherer *dpg)
{
	char *data;
	int line_len;
	char line[DTOP_SINGLE_LINE];
	int read;
	struct dt_procdict dict;
	int j;
	FILE *check = fopen(dpg->file, "r");
	if (check) {
		fclose(check);
		read = dt_read_file(dpg->file, &data, DTOP_SINGLE_SIZE);
	} else {
		return DTOP_POLL_IO_ERR;
	}

	if (read == 0 || data == 0)
		return DTOP_POLL_IO_ERR;

	line_len = dt_read_line(line, DTOP_SINGLE_LINE, data,
					   DTOP_SINGLE_SIZE, 0);

	/* Stores dp values in dictionary */
	dt_single_line_parse(line, line_len, &dict);

	/* Assigns the dp value to the dp struct */
	for (j = 0; j < dpg->data_points_len; j++)
		dtop_store_dp(&(dpg->data_points[j]), dict.val[j]);

	dt_free(&data);
	return DTOP_POLL_OK;
}

/**
 * @brief Frees dynamically allocated single line dpg.
 *
 * Frees the memory of the dpg along with it's data_points
 * and other malloc'd memory no longer needed.
 *
 * @param dpg Dpg to deconstruct and deallocate memory for.
 */
void dtop_value_only_dpg_deconstructor
			(struct dtop_data_point_gatherer *dpset)
{
	int i;
	for (i = 0; i < dpset->data_points_len; i++)
		free(dpset->data_points[i].name);
	free(dpset->data_points);
	free(dpset->file);
	free(dpset);
}

/**
 * @brief Creates a dpg for a single line file.
 *
 * Dynamically allocates memory for dpg which is then added to a linked list
 * via the dtop_register(dpg) function call.
 *
 * @param name Name of file dpg represents.
 * @param data_points dtop_data_point struct that dpg points to.
 * @param dp_count Number of data_points in data_points array
 */
static void construct_value_only_dpg(char *name, struct dtop_data_point
		*data_points, int dp_count)
{
	struct dtop_data_point_gatherer *dpg = malloc
		(sizeof(struct dtop_data_point_gatherer));
	dpg->prefix = name;
	dpg->file = name;
	dpg->poll = dtop_value_only_poll;
	dpg->data_points = data_points;
	dpg->data_points_len = dp_count;
	dpg->deconstruct = dtop_value_only_dpg_deconstructor;

	dtop_register(dpg);
}

/**
 * @brief Scans a single line file in order to autodetect dps.
 *
 * Searches through a file that contains a single line and only
 * values in order to detect and create dp's/
 *
 * @param name Name of file to scan.
 */
int dtop_value_only_search(char *name)
{
	int i;
	char *data;
	char line[DTOP_SINGLE_LINE];
	int line_len;
	int read;
	struct dt_procdict dict;
	struct dtop_data_point *data_points;


	read = dt_read_file(name, &data, DTOP_SINGLE_SIZE);
	if (read == 0 || data == 0) {
		free(name);
		return DTOP_POLL_IO_ERR;
	}

	line_len = dt_read_line(line,
				DTOP_SINGLE_LINE, data,
				DTOP_SINGLE_SIZE, 0);

	/* Stores dp values in dictionary */
	dt_single_line_parse(line, line_len, &dict);

	data_points = malloc(dict.max * sizeof(struct dtop_data_point));

	/* Creates a dtop_data_point struct for each dp found in the file */
	for (i = 0; i < dict.max; i++) {
		char *newname = malloc(sizeof(10));
		if (dict.val[i][0] == '-')
			data_points[i].type = DTOP_LONG;
		else
			data_points[i].type = DTOP_ULONG;
		data_points[i].name = malloc(sizeof(10));
		if (dict.max > 1)
			snprintf(newname, sizeof(10), "[%d]:", i);
		else
			strlcpy(newname, "", sizeof(10));
		strlcpy(data_points[i].name, newname, sizeof(10));
		free(newname);
		data_points[i].prefix = NULL;
		data_points[i].skip = DO_NOT_SKIP;
		data_points[i].initial_data_populated = NOT_POPULATED;
	}

	/* Calls dpg constructor, dpg will point to the dp struct */
	construct_value_only_dpg(name, data_points, dict.max);

	dt_free(&data);
	return DTOP_POLL_OK;
}

/**
 * @brief Calls dtop_search for files with a single line and only values.
 */
void dtop_value_only_init(char *name)
{
	char *file = malloc(strlen(name) + 1);
	strlcpy(file, name, strlen(name) + 1);
	dtop_value_only_search(file);
}
