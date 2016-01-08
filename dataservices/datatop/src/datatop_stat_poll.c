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
 * @file datatop_stat_poll.c
 * @brief Adds ability for data collection from /proc/stat
 *
 * File contains methods for searching and polling data from
 * "/proc/stat"
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "datatop_interface.h"
#include "datatop_fileops.h"
#include "datatop_str.h"

#define DTOP_STAT_SIZE 16384
#define DTOP_STAT_LINE (DTOP_STAT_SIZE>>2)

/**
* @struct dtop_stat_vars
* @brief Struct used to hold necessary variables for /proc/stat dpg
*
* @var dtop_stat_vars::line
* Array of strings where necessary dp names and values are held.
* @var dtop_stat_vars::line_count
* Number of lines the file is that the dpg represents.
*/
struct dtop_stat_vars {
	char **line;
	int line_count;
};

/**
 * @brief Parses lines with data in "/proc/stat"
 *
 * @param line1 Line to parse to find datapoint names and values.
 * @param len1 Length of line1.
 * @param n_index Index in the dictionary the key (name) is added to.
 * @param v_index Index in the dictionary the value is added to.
 * @param dict Dictionary the keys and values are added to.
 */
static int dt_stat_parse(char *line1, int len1,
			int n_index, int v_index, struct dt_procdict *dict)
{
	int i, k, j, start = 0;
	if (len1 < 1)
		return 0;

	if (line1 == 0 || dict == 0)
		return 0;

	dict->key[n_index] = &line1[0];
	for (i = 0; i < len1; i++) {
		if (line1[i] == ' ') {
			line1[i] = 0;
			start = (i+1);
			break;
		}
	}

	k = v_index;
	for (i = start; i < len1 && k < DTOP_DICT_SIZE; i++) {
		if (line1[i] != ' ') {
			dict->val[k] = &line1[i];
			for (j = i; j < len1; j++) {
				if (line1[j] == ' ') {
					line1[j] = 0;
					break;
				}
			}
			i = j;
			k++;
		}
	}

	dict->max = k;
	return k;
}

/**
 * @brief Stores the data collected from "/proc/stat"
 *
 * @param dpg Struct that polled data is added to.
 * @return DTOP_POLL_IO_ERR - Poll of dpg unsuccessful.
 * @return DTOP_POLL_OK - Poll of dpg successful.
 */
int dtop_stat_poll(struct dtop_data_point_gatherer *dpg)
{
	char *data;
	int *line_len = malloc(sizeof(int) *
			((struct dtop_stat_vars *)
			(dpg->priv))->line_count);
	int read;
	struct dt_procdict dict;
	int i, n, sum;
	int dp_count = 0;

	read = dt_read_file(dpg->file, &data, DTOP_STAT_SIZE);
	if (read == 0 || data == 0)
		return DTOP_POLL_IO_ERR;

	sum = 0;
	/* Assigns each line read from the file, a length */
	for (n = 0; n < ((struct dtop_stat_vars *)
				(dpg->priv))->line_count; n++) {
		line_len[n] = dt_read_line(((struct dtop_stat_vars *)
					(dpg->priv))->line[n],
					   DTOP_STAT_LINE, data,
					   DTOP_STAT_SIZE, sum);
		if (n <= (((struct dtop_stat_vars *)
			(dpg->priv))->line_count - 1)) {
			sum += (line_len[n] + 1);
		}

	}

	/* Stores dp names and values in dictionary */
	for (i = 0; i < ((struct dtop_stat_vars *)(dpg->priv))->line_count; i++)
		dp_count = dt_stat_parse(((struct dtop_stat_vars *)
			(dpg->priv))->line[i], line_len[i], i, dp_count, &dict);

	/* Assigns the dp value to the dp struct */
	for (n = 0; n < dp_count; n++) {
		dtop_store_dp(&(dpg->data_points[n]),
				dict.val[n]);
	}

	dt_free(&data);
	free(line_len);
	return DTOP_POLL_OK;
}

/**
 * @brief Frees dynamically allocated "/proc/stat" dpg.
 *
 * Frees the memory of the dpg along with it's data_points
 * and other malloc'd memory no longer needed.
 *
 * @param dpg Dpg to deconstruct and deallocate memory for.
 */
static void dtop_stat_dpg_deconstructor
			(struct dtop_data_point_gatherer *dpset)
{
	int i;
	for (i = 0; i < dpset->data_points_len; i++)
		free(dpset->data_points[i].name);
	free(dpset->data_points);
	for (i = 0; i < ((struct dtop_stat_vars *)
				(dpset->priv))->line_count; i++)
		free(((struct dtop_stat_vars *)(dpset->priv))->line[i]);
	free(((struct dtop_stat_vars *)(dpset->priv))->line);
	free(((struct dtop_stat_vars *)(dpset->priv)));

	free(dpset);
}

/**
 * @brief Creates a dpg for "/proc/stat" file
 *
 * Dynamically allocates memory for dpg which is then added to a linked list
 * via the dtop_register(dpg) function call.
 *
 * @param data_points dtop_data_point struct that dpg points to.
 * @param storage dtop_stat_vars struct that holds relevant dpg variables.
 * @param dp_count Number of data_points in data_points array
 */
static void construct_stat_file_dpg(struct dtop_data_point
		*data_points, struct dtop_stat_vars *storage, int dp_count)
{
	struct dtop_data_point_gatherer *dpg = malloc
		(sizeof(struct dtop_data_point_gatherer));
	dpg->prefix = "/proc/stat";
	dpg->file = "/proc/stat";
	dpg->poll = dtop_stat_poll;
	dpg->data_points = data_points;
	dpg->priv = (struct dtop_stat_vars *)storage;
	dpg->data_points_len = dp_count;
	dpg->deconstruct = dtop_stat_dpg_deconstructor;

	dtop_register(dpg);
}

/**
 * @brief Scans "/proc/stat" in order to autodetect dps.
 *
 * Searches through "/proc/stat" file for all available data
 * points to create as dp structs.
 *
 * @param storage dtop_stat_vars struct where relevant variables are stored.
 */
int dtop_stat_search(struct dtop_stat_vars *storage)
{
	int i, n, sum;
	char *data;
	int *line_len = malloc(sizeof(int) * storage->line_count);
	int read;
	struct dt_procdict dict;
	int dp_count = 0;
	int end;
	int *dp_per_line;
	struct dtop_data_point *data_points;
	int count = 0;

	storage->line = malloc(storage->line_count * sizeof(*storage->line));

	for (i = 0; i < storage->line_count; i++)
		storage->line[i] = malloc(sizeof(char) * DTOP_STAT_LINE);

	read = dt_read_file("/proc/stat", &data, DTOP_STAT_SIZE);
	if (read == 0 || data == 0)
		return DTOP_POLL_IO_ERR;

	sum = 0;
	/* Assigns each line read from the file, a length */
	for (n = 0; n < storage->line_count; n++) {
		line_len[n] = dt_read_line(storage->line[n],
					   DTOP_STAT_LINE, data,
					   DTOP_STAT_SIZE, sum);
		if (n < (storage->line_count - 1))
			sum += (line_len[n] + 1);
	}

	dp_per_line = malloc(sizeof(int) * (storage->line_count));
	/* Stores dp names in dictionary */

	for (i = 0; i < (storage->line_count); i++) {
		end = dp_count;
		dp_count = dt_stat_parse(storage->line[i],
				line_len[i], i, dp_count, &dict);
		dp_per_line[i] = (dp_count - end);
	}

	data_points = malloc(dp_count * sizeof(struct dtop_data_point));

	for (i = 0; i < (storage->line_count); i++) {
		for (n = 0; n < dp_per_line[i]; n++) {
			if (dp_per_line[i] == 1) {
				int dk_len = strlen(dict.key[i]) + 1;
				int dp_len;
				char *newname = malloc(dk_len);
				strlcpy(newname, dict.key[i], dk_len);
				dp_len = strlen(newname) + 1;
				data_points[count].name = malloc(dp_len);
				strlcpy(data_points[count].name, newname,
					dp_len);
				free(newname);
			} else {
				char *add = malloc(15 * sizeof(char));
				char *newname;
				int nn_len, dpn_len;
				snprintf(add, 15 * sizeof(char), "[%d]:", n);
				nn_len = strlen(dict.key[i]) + strlen(add) + 1;
				newname = malloc(nn_len);
				strlcpy(newname, dict.key[i], nn_len);
				strlcat(newname, add, nn_len);
				dpn_len = strlen(newname) + 1;
				data_points[count].name = malloc(dpn_len);
				strlcpy(data_points[count].name, newname,
					dpn_len);
				free(newname);
				free(add);
			}
			data_points[count].prefix = NULL;
			data_points[count].type = DTOP_ULONG;
			data_points[count].initial_data_populated
						= NOT_POPULATED;
			data_points[count].skip = DO_NOT_SKIP;
			count++;
		}
	}

	/* Calls dpg constructor, dpg will point to the dp struct */
	construct_stat_file_dpg(data_points, storage, dp_count);
	free(dp_per_line);
	free(line_len);
	dt_free(&data);

	return DTOP_POLL_OK;
}

/**
 * @brief Calls dtop_search for "/proc/stat" file.
 */
void dtop_stat_init(void)
{
	struct dtop_stat_vars *storage = malloc
			(sizeof(struct dtop_stat_vars));
	storage->line_count = dtop_get_file_line_amount("/proc/stat");
	dtop_stat_search(storage);
}
