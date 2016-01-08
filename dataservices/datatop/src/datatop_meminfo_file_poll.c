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
 * @file datatop_meminfo_file_poll.c
 * @brief Adds ability for data collection from /proc/meminfo
 *
 * File contains methods for searching and polling data from
 * "/proc/meminfo"
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include "datatop_interface.h"
#include "datatop_fileops.h"
#include "datatop_str.h"

#define DTOP_MEM_SIZE 8192
#define DTOP_MEM_LINE (DTOP_MEM_SIZE>>2)

/**
* @struct dtop_meminfo_vars
* @brief Struct used to hold necessary variables for /proc/meminfo dpg
*
* @var dtop_meminfo_vars::line
* Array of strings where necessary dp names and values are held.
* @var dtop_meminfo_vars::line_count
* Number of lines the file is that the dpg represents.
*/
struct dtop_meminfo_vars {
	char **line;
	int line_count;
};

/**
 * @brief Parses lines with data in "/proc/meminfo"
 *
 * @param line1 Line to parse to find datapoint names and values.
 * @param len1 Length of line1.
 * @param l Index in the dictionary the key/value pair is added to.
 * @param dict Dictionary the keys and values are added to.
 */
int dt_meminfo_parse(char *line1, int len1,
			int l, struct dt_procdict *dict)
{
	int i, k, n;
	if (len1 < 1)
		return 0;

	if (line1 == 0 || dict == 0)
		return 0;

	k = l;
	dict->key[k] = &line1[0];
	for (i = 0; i < len1 && k < DTOP_DICT_SIZE; i++) {
		if (line1[i] == ' ' || line1[i] == '	') {
			line1[i] = 0;
			n = i+1;
			while (line1[n] == '	' || line1[n] == ' ')
				n++;
			dict->val[k] = &line1[n];
			while (line1[n] != ' ')
				n++;
			line1[n] = 0;
			break;
		}
	}
	k++;
	dict->max = k;
	return k;
}

/**
 * @brief Stores the data collected from a "/proc/meminfo"
 *
 * @param dpg Struct that polled data is added to.
 * @return DTOP_POLL_IO_ERR - Poll of dpg unsuccessful.
 * @return DTOP_POLL_OK - Poll of dpg successful.
 */
int dtop_meminfo_poll(struct dtop_data_point_gatherer *dpg)
{
	char *data;
	int *line_len = malloc(sizeof(int) *
			((struct dtop_meminfo_vars *)
			(dpg->priv))->line_count);
	int read;
	struct dt_procdict dict;
	int i, j, n, sum;

	read = dt_read_file(dpg->file, &data, DTOP_MEM_SIZE);
	if (read == 0 || data == 0)
		return DTOP_POLL_IO_ERR;

	sum = 0;
	/* Assigns each line read from the file, a length */
	for (n = 0; n < ((struct dtop_meminfo_vars *)
				(dpg->priv))->line_count; n++) {
		line_len[n] = dt_read_line(((struct dtop_meminfo_vars *)
					(dpg->priv))->line[n],
					   DTOP_MEM_LINE, data,
					   DTOP_MEM_SIZE, sum);
		if (n <= (((struct dtop_meminfo_vars *)
			(dpg->priv))->line_count - 1)) {
			sum += (line_len[n] + 1);
		}

	}

	/* Stores dp names and values in dictionary */
	for (i = 0; i < dpg->data_points_len; i++)
		dt_meminfo_parse(((struct dtop_meminfo_vars *)
			(dpg->priv))->line[i], line_len[i], i, &dict);

	/* Assigns the dp value to the dp struct */
	for (j = 0; j < dpg->data_points_len; j++) {
		i = dt_find_dict_idx(dpg->data_points[j].name, &dict);
		if (i >= 0 && i < dict.max) {
			sscanf(dict.val[i], "%" PRIu64,
			       &(dpg->data_points[i].data.d_ulong));
			dpg->data_points[i].data.d_ulong *= 1024;
			if (dpg->data_points[i].
				initial_data_populated == NOT_POPULATED) {
				dpg->data_points[i].initial_data.d_ulong
					= dpg->data_points[i].data.d_ulong;
				dpg->data_points[i].initial_data_populated
					= POPULATED;
			}
		}
	}

	dt_free(&data);
	free(line_len);
	return DTOP_POLL_OK;
}

/**
 * @brief Frees dynamically allocated "/proc/meminfo" dpg.
 *
 * Frees the memory of the dpg along with it's data_points
 * and other malloc'd memory no longer needed.
 *
 * @param dpg Dpg to deconstruct and deallocate memory for.
 */
static void dtop_meminfo_dpg_deconstructor
			(struct dtop_data_point_gatherer *dpset)
{
	int i;
	free(dpset->data_points);
	for (i = 0; i < ((struct dtop_meminfo_vars *)
				(dpset->priv))->line_count; i++)
		free(((struct dtop_meminfo_vars *)(dpset->priv))->line[i]);
	free(((struct dtop_meminfo_vars *)(dpset->priv))->line);
	free(((struct dtop_meminfo_vars *)(dpset->priv)));
	free(dpset);
}

/**
 * @brief Creates a dpg for "/proc/meminfo" file
 *
 * Dynamically allocates memory for dpg which is then added to a linked list
 * via the dtop_register(dpg) function call.
 *
 * @param data_points dtop_data_point struct that dpg points to.
 * @param storage dtop_meminfo_vars struct that holds relevant dpg variables.
 */
static void construct_meminfo_file_dpg(struct dtop_data_point
		*data_points, struct dtop_meminfo_vars *storage)
{
	struct dtop_data_point_gatherer *dpg = malloc
		(sizeof(struct dtop_data_point_gatherer));
	dpg->prefix = "/proc/meminfo";
	dpg->file = "/proc/meminfo";
	dpg->poll = dtop_meminfo_poll;
	dpg->data_points = data_points;
	dpg->priv = (struct dtop_meminfo_vars *)storage;
	dpg->data_points_len = storage->line_count;
	dpg->deconstruct = dtop_meminfo_dpg_deconstructor;

	dtop_register(dpg);
}

/**
 * @brief Scans "/proc/meminfo in order to autodetect dps.
 *
 * Searches through "/proc/meminfo" file for all available data
 * points to create as dp structs.
 *
 * @param storage dtop_meminfo_vars struct where relevant variables are stored.
 */
int dtop_meminfo_search(struct dtop_meminfo_vars *storage)
{
	int i, k, n, sum;
	char *data;
	int *line_len = malloc(sizeof(int) * storage->line_count);
	int read;
	struct dt_procdict dict;
	struct dtop_data_point *data_points;

	storage->line = malloc(storage->line_count * sizeof(*storage->line));

	for (i = 0; i < storage->line_count; i++)
		storage->line[i] = malloc(sizeof(char) * DTOP_MEM_LINE);

	read = dt_read_file("/proc/meminfo", &data, DTOP_MEM_SIZE);
	if (read == 0 || data == 0)
		return DTOP_POLL_IO_ERR;

	sum = 0;
	/* Assigns each line read from the file, a length */
	for (n = 0; n < storage->line_count; n++) {
		line_len[n] = dt_read_line(storage->line[n],
					   DTOP_MEM_LINE, data,
					   DTOP_MEM_SIZE, sum);
		if (n < (storage->line_count - 1))
			sum += (line_len[n] + 1);
	}

	/* Stores dp names in dictionary */
	for (i = 0; i < (storage->line_count); i++)
		dt_parse_proc_same_line_key_and_val(storage->line[i],
						line_len[i], i, &dict);

	data_points = malloc
		       (storage->line_count * sizeof(struct dtop_data_point));

	k = 0;
	/* Creates a dtop_data_point struct for each dp found in the file */
	for (i = 0; i < dict.max; i++) {
		data_points[i].name = dict.key[i];
		data_points[i].prefix = NULL;
		data_points[i].type = DTOP_ULONG;
		k++;
	}

	/* Calls dpg constructor, dpg will point to the dp struct */
	construct_meminfo_file_dpg(data_points, storage);

	free(line_len);
	dt_free(&data);

	return DTOP_POLL_OK;
}

/**
 * @brief Calls dtop_search for "/proc/meminfo" file.
 */
void dtop_meminfo_init(void)
{
	struct dtop_meminfo_vars *storage = malloc
			(sizeof(struct dtop_meminfo_vars));
	storage->line_count = dtop_get_file_line_amount("/proc/meminfo");
	dtop_meminfo_search(storage);
}
