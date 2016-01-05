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
 * @file datatop_single_line_poll.c
 * @brief Adds ability for data collection from single line files
 *
 * File contains methods for searching and polling data from
 * single line files, meaning a file with multiple lines, but each
 * line contains the name of the dp, followed by the value.
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
* @struct dtop_single_line_vars
* @brief Struct used to hold necessary variables for dual_line_file dpgs.
*
* @var dtop_single_line_vars::line
* Array of strings where necessary dp names and values are held.
* @var dtop_single_line_vars::line_count
* Number of lines the file is that the dpg represents.
*/
struct dtop_single_line_vars {
	char **line;
	int line_count;
};

/**
 * @brief Stores the data collected from a single_line files.
 *
 * @param dpg Struct that polled data is added to.
 * @return DTOP_POLL_IO_ERR - Poll of dpg unsuccessful.
 * @return DTOP_POLL_OK - Poll of dpg successful.
 */
int dtop_single_line_poll(struct dtop_data_point_gatherer *dpg)
{
	char *data;
	int *line_len = malloc(sizeof(int) *
			((struct dtop_single_line_vars *)
			(dpg->priv))->line_count);
	int read;
	struct dt_procdict dict;
	int i, j, n, sum;

	read = dt_read_file(dpg->file, &data, DTOP_SINGLE_SIZE);
	if (read == 0 || data == 0)
		return DTOP_POLL_IO_ERR;

	sum = 0;
	/* Assigns each line read from the file, a length */
	for (n = 0; n < ((struct dtop_single_line_vars *)
				(dpg->priv))->line_count; n++) {
		line_len[n] = dt_read_line(((struct dtop_single_line_vars *)
					(dpg->priv))->line[n],
					   DTOP_SINGLE_LINE, data,
					   DTOP_SINGLE_SIZE, sum);
		if (n <= (((struct dtop_single_line_vars *)
			(dpg->priv))->line_count - 1)) {
			sum += (line_len[n] + 1);
		}

	}

	/* Stores dp names and values in dictionary */
	for (i = 0; i < dpg->data_points_len; i++)
		dt_parse_proc_same_line_key_and_val((
			(struct dtop_single_line_vars *)
			(dpg->priv))->line[i], line_len[i], i, &dict);

	/* Assigns the dp value to the dp struct */
	for (j = 0; j < dpg->data_points_len; j++) {
		i = dt_find_dict_idx(dpg->data_points[j].name, &dict);
		if (i >= 0 && i < dict.max)
			dtop_store_dp(&(dpg->data_points[j]),
				      dict.val[i]);
	}

	dt_free(&data);
	free(line_len);
	return DTOP_POLL_OK;
}

/**
 * @brief Frees dynamically allocated single_line_file dpgs.
 *
 * Frees the memory of the dpg along with it's data_points
 * and other malloc'd memory no longer needed.
 *
 * @param dpg Dpg to deconstruct and deallocate memory for.
 */
static void dtop_single_line_dpg_deconstructor
			(struct dtop_data_point_gatherer *dpset)
{
	int i;
	free(dpset->data_points);
	for (i = 0; i < ((struct dtop_single_line_vars *)
				(dpset->priv))->line_count; i++)
		free(((struct dtop_single_line_vars *)(dpset->priv))->line[i]);
	free(((struct dtop_single_line_vars *)(dpset->priv))->line);
	free(((struct dtop_single_line_vars *)(dpset->priv)));
	free(dpset);
}

/**
 * @brief Creates a dpg for a single_line file.
 *
 * Dynamically allocates memory for dpg which is then added to a linked list
 * via the dtop_register(dpg) function call.
 *
 * @param name Name of file dpg represents.
 * @param data_points dtop_data_point struct that dpg points to.
 * @param storage dtop_single_line_vars struct that holds relevant dpg variables.
 */
static void construct_single_line_file_dpg(char *name, struct dtop_data_point
		*data_points, struct dtop_single_line_vars *storage)
{
	struct dtop_data_point_gatherer *dpg = malloc
		(sizeof(struct dtop_data_point_gatherer));
	dpg->prefix = name;
	dpg->file = name;
	dpg->poll = dtop_single_line_poll;
	dpg->data_points = data_points;
	dpg->priv = (struct dtop_single_line_vars *)storage;
	dpg->data_points_len = storage->line_count;
	dpg->deconstruct = dtop_single_line_dpg_deconstructor;

	dtop_register(dpg);
}

/**
 * @brief Scans a single_line file for all datapoints and creats dps.
 *
 * Searches through a single_line file (Key followed by value on the
 * same line) for all available data points to create as dp structs.
 *
 * @param name Name of file.
 * @param storage dtop_single_line_vars struct where relevant variables are stored.
 */
int dtop_single_line_search(char *name, struct dtop_single_line_vars *storage)
{
	int i, k, n, sum;
	char *data;
	int *line_len = malloc(sizeof(int) * storage->line_count);
	int read;
	struct dt_procdict dict;
	struct dtop_data_point *data_points;

	storage->line = malloc(storage->line_count * sizeof(*storage->line));

	for (i = 0; i < storage->line_count; i++)
		storage->line[i] = malloc(sizeof(char) * DTOP_SINGLE_LINE);

	read = dt_read_file(name, &data, DTOP_SINGLE_SIZE);
	if (read == 0 || data == 0)
		return DTOP_POLL_IO_ERR;

	sum = 0;
	/* Assigns each line read from the file, a length */
	for (n = 0; n < storage->line_count; n++) {
		line_len[n] = dt_read_line(storage->line[n],
					   DTOP_SINGLE_LINE, data,
					   DTOP_SINGLE_SIZE, sum);
		if (n < (storage->line_count - 1))
			sum += (line_len[n] + 1);
	}

	/* Stores dp names and values in dictionary */
	for (i = 0; i < (storage->line_count); i++)
		dt_parse_proc_same_line_key_and_val(storage->line[i],
						line_len[i], i, &dict);

	data_points = malloc
		       (storage->line_count * sizeof(struct dtop_data_point));

	k = 0;
	/* Creates a dtop_data_point struct for each dp found in the file */
	for (i = 0; i < dict.max; i++) {
		if (dict.val[i][0] == '-')
			data_points[k].type = DTOP_LONG;
		else
			data_points[k].type = DTOP_ULONG;
		data_points[i].name = dict.key[i];
		data_points[i].prefix = NULL;
		k++;
	}

	/* Calls dpg constructor, dpg will point to the dp struct */
	construct_single_line_file_dpg(name, data_points, storage);

	free(line_len);
	dt_free(&data);

	return DTOP_POLL_OK;
}

/**
 * @brief Calls dtop_search for a files with single line format.
 *
 * Single line format refers to a file, where each line contains
 * the name of a dp, followed by the value of a dp.
 */
void dtop_single_line_init(char *name)
{
	struct dtop_single_line_vars *storage = malloc
			(sizeof(struct dtop_single_line_vars));
	storage->line_count = dtop_get_file_line_amount(name);
	dtop_single_line_search(name, storage);
}
