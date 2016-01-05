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
 * @file datatop_dual_line_poll.c
 * @brief Adds ability for data collection from dual line files.
 *
 * File contains methods for searching and polling data from
 * dual line files, meaning the first line contains the dp names
 * while the second line contains the corresponding values.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "datatop_interface.h"
#include "datatop_fileops.h"
#include "datatop_str.h"

#define DTOP_DUAL_SIZE 8192
#define DTOP_DUAL_LINE (DTOP_DUAL_SIZE>>2)

/**
* @struct dtop_dual_line_vars
* @brief Struct used to hold necessary variables for dual_line_file dpgs.
*
* @var dtop_dual_line_vars::line
* Array of strings where necessary dp names and values are held.
* @var dtop_dual_line_vars::line2
* Array of strings where necessary dp names and values are held.
* @var dtop_dual_line_vars::line_count
* Number of lines the file is that the dpg represents.
*/
struct dtop_dual_line_vars {
	char **line;
	char **line2;
	int line_count;
};

/**
 * @brief Stores the data collected from a dual_line file.
 *
 * @param dpg Struct that polled data is added to.
 * @return DTOP_POLL_IO_ERR - Poll of dpg unsuccessful.
 * @return DTOP_POLL_OK - Poll of dpg successful.
 */
int dtop_dual_line_poll(struct dtop_data_point_gatherer *dpg)
{
	char *data;
	int *line_len = malloc(sizeof(int) *
			((struct dtop_dual_line_vars *)
			(dpg->priv))->line_count);
	int *line_len2 = malloc(sizeof(int) *
			((struct dtop_dual_line_vars *)
			(dpg->priv))->line_count);
	int read;

	struct dt_procdict *dict = malloc(sizeof(struct dt_procdict)
					* (((struct dtop_dual_line_vars *)
					(dpg->priv))->line_count/2));
	struct dt_procdict *prefix_dict = malloc(sizeof(struct dt_procdict)
					* (((struct dtop_dual_line_vars *)
					(dpg->priv))->line_count/2));
	int i, j, k, n, sum, sum2;

	read = dt_read_file(dpg->file, &data, DTOP_DUAL_SIZE);
	if (read == 0 || data == 0)
		return DTOP_POLL_IO_ERR;

	sum = 0;
	sum2 = 0;
	/* Assigns each line read from the file, a length */
	for (n = 0; n < ((struct dtop_dual_line_vars *)
				(dpg->priv))->line_count; n++) {
		line_len[n] = dt_read_line(((struct dtop_dual_line_vars *)
					(dpg->priv))->line[n],
					   DTOP_DUAL_LINE, data,
					   DTOP_DUAL_SIZE, sum);
		line_len2[n] = dt_read_line(((struct dtop_dual_line_vars *)
					(dpg->priv))->line2[n],
					    DTOP_DUAL_LINE, data,
					    DTOP_DUAL_SIZE, sum2);
		if (n <= (((struct dtop_dual_line_vars *)
				(dpg->priv))->line_count-2)) {
			sum += (line_len[n] + 1);
			sum2 += (line_len2[n] + 1);
		}

	}

	/* Stores dp names and values in dictionary */
	for (i = 0; i < (((struct dtop_dual_line_vars *)
				(dpg->priv))->line_count/2); i++)
		dt_parse_proc_dictionary(((struct dtop_dual_line_vars *)
					(dpg->priv))->line[2*i],
					  line_len[2*i],
					  ((struct dtop_dual_line_vars *)
					  (dpg->priv))->line[(2*i)+1],
					  line_len[(2*i)+1],
					  &dict[i]);

	/* Stores dp prefices in dictionary */
	for (i = 0; i < (((struct dtop_dual_line_vars *)
				(dpg->priv))->line_count/2); i++)
		dt_parse_for_prefix(((struct dtop_dual_line_vars *)
				(dpg->priv))->line2[2*i], line_len2[2*i],
				    &prefix_dict[i]);

	/* Assigns a dp value to each dp struct */
	for (k = 0; k < (((struct dtop_dual_line_vars *)
				(dpg->priv))->line_count/2); k++) {
		for (j = 0; j < dpg->data_points_len; j++) {
			i =  dt_find_dict_idx(dpg->data_points[j].name,
					      &dict[k]);
			if (i >= 0 && i < dict[k].max &&
				(strcmp(dpg->data_points[j].prefix,
				prefix_dict[k].val[i]) == 0))

				dtop_store_dp(&(dpg->data_points[j]),
					      dict[k].val[i]);
		}
	}

	dt_free(&data);
	free(line_len);
	free(line_len2);
	free(dict);
	free(prefix_dict);
	return DTOP_POLL_OK;
}

/**
 * @brief Frees dynamically allocated dual_line_file dpgs.
 *
 * Frees the memory of the dpg along with it's data_points
 * and other malloc'd memory no longer needed.
 *
 * @param dpg Dpg to deconstruct and deallocate memory for.
 */
static void dtop_dual_line_dpg_deconstructor
			(struct dtop_data_point_gatherer *dpset)
{
	int i;
	free(dpset->data_points);
	for (i = 0; i < ((struct dtop_dual_line_vars *)
				(dpset->priv))->line_count; i++) {
		free(((struct dtop_dual_line_vars *)(dpset->priv))->line[i]);
		free(((struct dtop_dual_line_vars *)(dpset->priv))->line2[i]);
	}
	free(((struct dtop_dual_line_vars *)(dpset->priv))->line);
	free(((struct dtop_dual_line_vars *)(dpset->priv))->line2);
	free(((struct dtop_dual_line_vars *)(dpset->priv)));
	free(dpset);
}

/**
 * @brief Creates a dpg for a dual_line file.
 *
 * Dynamically allocates memory for dpg which is then added to a linked list
 * via the dtop_register(dpg) function call.
 *
 * @param name Name of file dpg represents.
 * @param data_points dtop_data_point struct that dpg points to.
 * @param storage dtop_dual_line_vars struct that hold relevant dpg variables.
 * @param dp_count Number of datapoints in dtop_data_point struct array.
 */
static void construct_dual_line_file_dpg(char *name, struct dtop_data_point
		*data_points, struct dtop_dual_line_vars *storage, int dp_count)
{
	struct dtop_data_point_gatherer *dpg = malloc
		(sizeof(struct dtop_data_point_gatherer));
	dpg->prefix = name;
	dpg->file = name;
	dpg->poll = dtop_dual_line_poll;
	dpg->data_points = data_points;
	dpg->priv = (struct dtop_dual_line_vars *)storage;
	dpg->data_points_len = dp_count;
	dpg->deconstruct = dtop_dual_line_dpg_deconstructor;

	dtop_register(dpg);
}

/**
 * @brief Scans a dual_line file for all datapoints and creats dps.
 *
 * Searches through a dual_line file (Key on one line with value on next line)
 * for all available data points to create as dp structs.
 *
 * @param name Name of file.
 * @param storage dtop_dual_line_vars struct where relevant variables are stored.
 */
int dtop_dual_line_search(char *name, struct dtop_dual_line_vars *storage)
{
	int i, j, k, n, sum, sum2;
	char *data;
	int *line_len = malloc(sizeof(int) * storage->line_count);
	int *line_len2 = malloc(sizeof(int) * storage->line_count);
	int read;
	struct dt_procdict *dict, *prefix_dict;
	struct dtop_data_point *data_points;
	int dp_count = 0;

	storage->line = malloc(storage->line_count * sizeof(*storage->line));
	storage->line2 = malloc(storage->line_count * sizeof(*storage->line2));
	for (i = 0; i < storage->line_count; i++) {
		storage->line[i] = malloc(sizeof(char) * DTOP_DUAL_LINE);
		storage->line2[i] = malloc(sizeof(char) * DTOP_DUAL_LINE);
	}
	dict = malloc(sizeof(struct dt_procdict) * (storage->line_count/2));
	prefix_dict = malloc(sizeof(struct dt_procdict)
				* (storage->line_count/2));

	read = dt_read_file(name, &data, DTOP_DUAL_SIZE);
	if (read == 0 || data == 0)
		return DTOP_POLL_IO_ERR;

	sum = 0;
	sum2 = 0;
	/* Assigns each line read from the file, a length */
	for (n = 0; n < storage->line_count; n++) {
		line_len[n] = dt_read_line(storage->line[n],
					   DTOP_DUAL_LINE, data,
					   DTOP_DUAL_SIZE, sum);
		line_len2[n] = dt_read_line(storage->line2[n],
					    DTOP_DUAL_LINE, data,
					    DTOP_DUAL_SIZE, sum2);
		if (n <= (storage->line_count-2)) {
			sum += (line_len[n] + 1);
			sum2 += (line_len2[n] + 1);
		}

	}

	/* Stores dp names and prefixes in dictionaries */
	for (i = 0; i < (storage->line_count/2); i++)
		dt_parse_proc_dictionary(storage->line[2*i], line_len[2*i],
			 storage->line[(2*i)+1], line_len[(2*i)+1], &dict[i]);

	for (i = 0; i < (storage->line_count/2); i++)
		dt_parse_for_prefix(storage->line2[2*i], line_len2[2*i],
				    &prefix_dict[i]);

	/* Finds how many data points were gathered from the file */
	for (j = 0; j < (storage->line_count/2); j++) {
		for (i = 0; i < dict[j].max; i++)
			dp_count++;
	}

	data_points = malloc(dp_count * sizeof(struct dtop_data_point));

	k = 0;
	/* Creates a dtop_data_point struct for each dp found in the file */
	for (j = 0; j < (storage->line_count/2); j++)
		for (i = 0; i < dict[j].max; i++) {
			if (dict[j].val[i][0] == '-')
				data_points[k].type = DTOP_LONG;
			else
				data_points[k].type = DTOP_ULONG;
			data_points[k].name = dict[j].key[i];
			data_points[k].prefix = prefix_dict[j].val[i];
			data_points[k].skip = DO_NOT_SKIP;
			data_points[k].initial_data_populated = NOT_POPULATED;
			k++;
		}

	/* Calls dpg constructor, dpg will point to the dp struct */
	construct_dual_line_file_dpg(name, data_points, storage, dp_count);

	free(line_len);
	free(line_len2);
	free(dict);
	free(prefix_dict);
	dt_free(&data);

	return DTOP_POLL_OK;
}

/**
 * @brief Calls dtop_search for a file with dual line pairs.
 */
void dtop_dual_line_init(char *name)
{
	struct dtop_dual_line_vars *storage = malloc
			(sizeof(struct dtop_dual_line_vars));
	storage->line_count = dtop_get_file_line_amount(name);

	if (storage->line_count%2 != 0) {
		printf("Dual line file, %s, contains error.\n", name);
		printf("Data will not be collected from %s\n", name);
		return;
	}
	dtop_dual_line_search(name, storage);
}
