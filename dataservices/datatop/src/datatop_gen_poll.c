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
 * @file datatop_gen_poll.c
 * @brief Contains functions which add ability to scan directories for data points.
 *
 * Contains functions that search through a directory and create dpg's for any
 * important data values found which can then be polled for data collection.
 */

#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "datatop_interface.h"
#include "datatop_fileops.h"
#include "datatop_str.h"
#include "datatop_gen_poll.h"

#define DTOP_GEN_SIZE 8192
#define DTOP_GEN_LINE (DTOP_GEN_SIZE>>2)

/**
 * @brief Searches a file to find the number of data values it contains.
 *
 * @param dpg The struct which contains the file to search.
 * @return Number of datapoints found in the file.
 */
static int get_number_of_values(struct dtop_data_point_gatherer *dpg)
{
	char *data;
	int read;
	char line[DTOP_GEN_LINE];
	int line_len;
	int i, num;

	read = dt_read_file(dpg->file, &data, DTOP_GEN_SIZE);
	line_len = dt_read_line(line, DTOP_GEN_LINE, data, DTOP_GEN_SIZE, 0);

	if (read == 0) {
		return 0;
	}

	if (line_len < 1) {
		dt_free(&data);
		return 0;
	}

	num = 1;
	for (i = 0; i < line_len; i++) {
		if ((line[i] == ' ' || line[i] == ','
		    || line[i] == '	') &&line[i+1] != 0)
			num++;
	}

	dt_free(&data);
	return num;
}

/**
 * @brief Stores the data collected from a dpg that was constructed during dtop_search.
 *
 * @param dpg Struct that polled data is added to.
 * @return DTOP_POLL_IO_ERR - Poll of dpg unsuccessful.
 * @return DTOP_POLL_OK - Poll of dpg successful.
 */
int dtop_gen_poll(struct dtop_data_point_gatherer *dpg)
{
	char *data;
	int read;
	char line[DTOP_GEN_LINE];
	int line_len;
	struct dt_procdict dict;
	int i;

	read = dt_read_file(dpg->file, &data, DTOP_GEN_SIZE);
	line_len = dt_read_line(line, DTOP_GEN_LINE, data, DTOP_GEN_SIZE, 0);

	if (read == 0 || data == 0)
		return DTOP_POLL_IO_ERR;

	dt_single_line_parse(line, line_len, &dict);

	for (i = 0; i < dpg->data_points_len; i++) {
		if (dict.val[i][0] == '-')
			dpg->data_points[i].type = DTOP_LONG;
		dtop_store_dp(&(dpg->data_points[i]), dict.val[i]);
	}

	dt_free(&data);
	return DTOP_POLL_OK;
}

/**
 * @brief Frees dynamically allocated dpg's.
 *
 * Frees the memory of dpg variables and the dpg for all dynamically allocated
 * dpgs.
 *
 * @param dpg Dpg to deconstruct and deallocate memory for.
 */
static void dtop_gen_dpg_deconstructor(struct dtop_data_point_gatherer *dpset)
{
	int i;
	for (i = 0; i < dpset->data_points_len; i++)
		free(dpset->data_points[i].name);
	free(dpset->data_points);
	free(dpset->file);
	free(dpset->prefix);
	free(dpset);
}

/**
 * @brief Creates a dpg and all necessary dp's corresponding to it.
 *
 * Dynamically allocates memory for dpg and dp structs which are then
 * created and added to a linked_list of dpgs through the dtop_register
 * function.
 *
 * @param dir Directory which file is located in, assigned to the dpg prefix.
 * @param name Name of file that dpg represents, assigned to a dp name.
 */
static void dpg_construction(char *dir, char *name)
{
	int num, i;
	int both_len = strlen(dir) + strlen(name) + 1;
	char *both = malloc(both_len);
	char *maindir;
	struct dtop_data_point_gatherer *dpg = malloc
	       (sizeof(struct dtop_data_point_gatherer));
	strlcpy(both, dir, both_len);
	strlcat(both, name, both_len);
	maindir = malloc(strlen(dir) + 1);
	strlcpy(maindir, dir, strlen(dir) + 1);

	dpg->prefix = maindir;
	dpg->file = both;
	dpg->poll = dtop_gen_poll;
	dpg->deconstruct = dtop_gen_dpg_deconstructor;
	num = get_number_of_values(dpg);

	if (num != 0) {
		struct dtop_data_point *dp = malloc
		       (num * sizeof(struct dtop_data_point));
		for (i = 0; i < num; i++) {
			if (num == 1) {
				dp[i].name = malloc(strlen(name) + 1);
				strlcpy(dp[i].name, name, strlen(name) + 1);
			} else {
				char *add = malloc(7 * sizeof(char));
				char *newname;
				int nn_len, dpn_len;
				snprintf(add, 7 * sizeof(char), "[%d]:", i);
				nn_len = strlen(name) + strlen(add) + 1;
				newname = malloc(nn_len);
				strlcpy(newname, name, nn_len);
				strlcat(newname, add, nn_len);
				dpn_len = strlen(newname) + 1;
				dp[i].name = malloc(dpn_len);
				strlcpy(dp[i].name, newname, dpn_len);
				free(add);
				free(newname);
			}
			dp[i].prefix = NULL;
			dp[i].type = DTOP_ULONG;
			dp[i].skip = DO_NOT_SKIP;
			dp[i].initial_data_populated = NOT_POPULATED;
		}

		dpg->data_points = dp;
		dpg->data_points_len = num;

		dtop_register(dpg);
	} else {
		free(dpg->prefix);
		free(dpg->file);
		free(dpg);
	}
}

/**
 * @brief Scans a directory for all important datapoints to be collected.
 *
 * Recursively scans a directory and locates all files which data will be
 * collected from.
 *
 * @param dir Directory to search.
 */
static int dtop_search(char *dir)
{
	DIR *dp;
	struct dirent *entry;
	struct stat s;
	char cwd[1024];

	if (!getcwd(cwd, sizeof(cwd))) {
		fprintf(stderr, "Failed to get current working dir\n");
		return -1;
	}

	dp = opendir(dir);
	if (dp == NULL) {
		fprintf(stderr, "err=%d: %s\n", errno, strerror(errno));
		fprintf(stderr, "Cannot open directory: %s\n", dir);
		return DIR_FAILURE;
	}

	chdir(dir);

	while ((entry = readdir(dp))) {
		if (stat(entry->d_name, &s)) {
			printf("stat err=%d: %s\n", errno, strerror(errno));
			return DIR_FAILURE;
		}

		if (strcmp(".", entry->d_name) != 0 &&
		   strcmp("..", entry->d_name) != 0 &&
		   S_ISREG(s.st_mode)) {

			dpg_construction(dir, entry->d_name);

		} else if (strcmp(".", entry->d_name) != 0 &&
			strcmp("..", entry->d_name) != 0 &&
			S_ISDIR(s.st_mode)) {
			int nd_len = strlen(dir) + strlen(entry->d_name) + 2;
			char *newdir = malloc(nd_len);
			strlcpy(newdir, dir, nd_len);
			strlcat(newdir, entry->d_name, nd_len);
			strlcat(newdir, "/", nd_len);
			dtop_search(newdir);
			free(newdir);
		}
	}

	closedir(dp);
	chdir(cwd);
	return DIR_SUCCESS;
}

/**
 * @brief Calls dtop_search for any specified directory.
 *
 * @param dir Directory to search.
 */
void dtop_gen_init(char *dir)
{
	dtop_search(dir);
}
