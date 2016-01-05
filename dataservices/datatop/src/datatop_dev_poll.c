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
 * @file datatop_dev_poll.c
 * @brief Adds ability for data collection from /proc/net/dev
 *
 * File contains methods for searching and polling data from
 * "/proc/net/dev"
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "datatop_interface.h"
#include "datatop_fileops.h"
#include "datatop_str.h"

#define DTOP_DEV_SIZE 8192
#define DTOP_DEV_LINE (DTOP_DEV_SIZE>>2)

/**
* @struct dtop_dev_vars
* @brief Struct used to hold necessary variables for /proc/net/dev dpg
*
* @var dtop_dev_vars::line
* Array of strings where necessary dp names and values are held.
* @var dtop_dev_vars::line_count
* Number of lines the file is that the dpg represents.
*/
struct dtop_dev_vars {
	char **line;
	int line_count;
};

/**
 * @brief Parses lines with data in "/proc/net/dev"
 *
 * @param line1 Line to parse to find datapoint names and values.
 * @param len1 Length of line1.
 * @param index Index in the dictionary the key (name) is added to.
 * @param dict Dictionary the keys and values are added to.
 */
static void dt_dev_parse(char *line1, int len1,
			 int index, struct dt_procdict *dict)
{
	int i, start = 0;
	int j, k, n;
	i = 0;
	while (line1[i] == '	' || line1[i] == ' ')
		i++;
	dict->key[index] = &line1[i];
	for (i = 0; i < len1; i++) {
		if (line1[i] == ':') {
			line1[i+1] = 0;
			start = i+2;
			break;
		}
	}

	k = 0;
	for (j = start; j < len1; j++) {
		if (line1[j] != '	' && line1[j] != ' ') {
			dict->val[k] = &line1[j];
			n = j;
			while (line1[n] != '	' && line1[n] != ' ')
				n++;
			if (n < len1)
				line1[n] = 0;
			j = n;
			k++;
		}
	}
}

/**
 * @brief Stores the data collected from "/proc/net/dev"
 *
 * @param dpg Struct that polled data is added to.
 * @return DTOP_POLL_IO_ERR - Poll of dpg unsuccessful.
 * @return DTOP_POLL_OK - Poll of dpg successful.
 */
int dtop_dev_poll(struct dtop_data_point_gatherer *dpg)
{
	char *data;
	int *line_len = malloc(sizeof(int) *
			((struct dtop_dev_vars *)
			(dpg->priv))->line_count);
	int read;
	struct dt_procdict *dict = malloc(sizeof(struct dt_procdict)
					*((struct dtop_dev_vars *)
					(dpg->priv))->line_count-2);
	int j, n, sum;
	int index = 0;
	int dp = 0;

	read = dt_read_file(dpg->file, &data, DTOP_DEV_SIZE);
	if (read == 0 || data == 0)
		return DTOP_POLL_IO_ERR;

	sum = 0;
	/* Assigns each line read from the file, a length */
	for (n = 0; n < ((struct dtop_dev_vars *)
				(dpg->priv))->line_count; n++) {
		line_len[n] = dt_read_line(((struct dtop_dev_vars *)
					(dpg->priv))->line[n],
					   DTOP_DEV_LINE, data,
					   DTOP_DEV_SIZE, sum);
		if (n <= (((struct dtop_dev_vars *)
			(dpg->priv))->line_count - 1)) {
			sum += (line_len[n] + 1);
		}

	}

	for (n = 2; n < ((struct dtop_dev_vars *)
			(dpg->priv))->line_count; n++) {
		dt_dev_parse(((struct dtop_dev_vars *)
				(dpg->priv))->line[n], line_len[n],
					index, &dict[index]);
		index++;
	}


	/* Assigns the dp value to the dp struct */
	for (n = 2; n < ((struct dtop_dev_vars *)
			(dpg->priv))->line_count; n++) {
		for (j = 0; j < 16; j++) {
			dtop_store_dp(&(dpg->data_points[dp]),
						dict[n-2].val[j]);
			dp++;
		}
	}

	dt_free(&data);
	free(line_len);
	free(dict);
	return DTOP_POLL_OK;
}

/**
 * @brief Frees dynamically allocated "/proc/net/dev" dpg.
 *
 * Frees the memory of the dpg along with it's data_points
 * and other malloc'd memory no longer needed.
 *
 * @param dpg Dpg to deconstruct and deallocate memory for.
 */
static void dtop_dev_dpg_deconstructor
			(struct dtop_data_point_gatherer *dpset)
{
	int i, j, dp;
	dp = 0;
	for (j = 0; j < ((((struct dtop_dev_vars *)
		(dpset->priv))->line_count)-2); j++) {
		for (i = 0; i < 16; i++) {
			free(dpset->data_points[dp].prefix);
			dp++;
		}
	}
	free(dpset->data_points);
	for (i = 0; i < ((struct dtop_dev_vars *)
				(dpset->priv))->line_count; i++)
		free(((struct dtop_dev_vars *)(dpset->priv))->line[i]);
	free(((struct dtop_dev_vars *)(dpset->priv))->line);
	free(((struct dtop_dev_vars *)(dpset->priv)));
	free(dpset);
}

/**
 * @brief Creates a dpg for "/proc/net/dev" file
 *
 * Dynamically allocates memory for dpg which is then added to a linked list
 * via the dtop_register(dpg) function call.
 *
 * @param data_points dtop_data_point struct that dpg points to.
 * @param storage dtop_dev_vars struct that holds relevant dpg variables.
 */
static void construct_dev_file_dpg(struct dtop_dev_vars *storage,
			int dp_count, struct dtop_data_point *data_points)
{
	struct dtop_data_point_gatherer *dpg = malloc
		(sizeof(struct dtop_data_point_gatherer));

	dpg->prefix = "/proc/net/dev";
	dpg->file = "/proc/net/dev";
	dpg->poll = dtop_dev_poll;
	dpg->data_points = data_points;
	dpg->priv = (struct dtop_dev_vars *)storage;
	dpg->data_points_len = dp_count;
	dpg->deconstruct = dtop_dev_dpg_deconstructor;

	dtop_register(dpg);
}

/**
 * @brief Scans "/proc/net/dev in order to autodetect dps.
 *
 * Searches through "/proc/net/dev" file for all available data
 * points to create as dp structs.
 *
 * @param name This is the file name "/proc/net/dev" passed in by dtop_dev_init
 * @param storage dtop_dev_vars struct where relevant variables are stored.
 */
int dtop_dev_search(char *name, struct dtop_dev_vars *storage)
{
	int i, n, sum;
	char *data;
	int *line_len = malloc(sizeof(int) * storage->line_count);
	int read;
	struct dt_procdict dict;
	struct dt_procdict dev_dict;
	struct dtop_data_point *data_points = malloc
		(sizeof(struct dtop_data_point) * 16 * (storage->line_count-2));
	int dp_count = (16 * (storage->line_count - 2));
	int index = 0;
	int dp = 0;

	storage->line = malloc(storage->line_count * sizeof(*storage->line));

	for (i = 0; i < storage->line_count; i++)
		storage->line[i] = malloc(sizeof(char) * DTOP_DEV_LINE);

	dev_dict.val[0] = "bytes";
	dev_dict.val[1] = "packets";
	dev_dict.val[2] = "errs";
	dev_dict.val[3] = "drop";
	dev_dict.val[4] = "fifo";
	dev_dict.val[5] = "frame";
	dev_dict.val[6] = "compressed";
	dev_dict.val[7] = "multicast";
	dev_dict.val[8] = "bytes";
	dev_dict.val[9] = "packets";
	dev_dict.val[10] = "errs";
	dev_dict.val[11] = "drop";
	dev_dict.val[12] = "fifo";
	dev_dict.val[13] = "colls";
	dev_dict.val[14] = "carrier";
	dev_dict.val[15] = "compressed";

	read = dt_read_file(name, &data, DTOP_DEV_SIZE);
	if (read == 0 || data == 0)
		return DTOP_POLL_IO_ERR;

	sum = 0;
	/* Assigns each line read from the file, a length */
	for (n = 0; n < storage->line_count; n++) {
		line_len[n] = dt_read_line(storage->line[n],
					   DTOP_DEV_LINE, data,
					   DTOP_DEV_SIZE, sum);
		if (n < (storage->line_count - 1))
			sum += (line_len[n] + 1);
	}

	construct_dev_file_dpg(storage, dp_count, data_points);

	for (n = 2; n < storage->line_count; n++) {
		dt_dev_parse(storage->line[n], line_len[n], index, &dict);
		index++;
	}

	for (n = 2; n < storage->line_count; n++) {
		for (i = 0; i < 16; i++) {
			char *pref = malloc(30 * sizeof(char));
			data_points[dp].skip = 0;
			data_points[dp].initial_data_populated = NOT_POPULATED;
			if (i < 8)
				strlcpy(pref, "Receive:", 30 * sizeof(char));
			else if (i >= 8)
				strlcpy(pref, "Transmit:", 30 * sizeof(char));
			strlcat(pref, dev_dict.val[i], 30 * sizeof(char));
			data_points[dp].prefix = pref;
			data_points[dp].name = dict.key[n-2];
			data_points[dp].type = DTOP_ULONG;
			dp++;
		}
		index++;
	}

	free(line_len);
	dt_free(&data);
	return DTOP_POLL_OK;
}

/**
 * @brief Calls dtop_search for "/proc/net/dev" file.
 */
void dtop_dev_init(void)
{
	struct dtop_dev_vars *storage = malloc
			(sizeof(struct dtop_dev_vars));
	storage->line_count = dtop_get_file_line_amount("/proc/net/dev");
	dtop_dev_search("/proc/net/dev", storage);
}
