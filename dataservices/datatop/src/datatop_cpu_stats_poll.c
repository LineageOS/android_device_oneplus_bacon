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
 * @file datatop_cpu_stats_poll.c
 * @brief Calls dtop_value_only_init for necessary cpu datapoints.
 *
 * File contains methods for determing number of cpu's online and calling
 * correct initialization function to gather scaling_cur_freq data point
 * for each cpu along with each cpu's online status.
 */

#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>
#include "datatop_interface.h"
#include "datatop_fileops.h"
#include "datatop_str.h"
#include "datatop_polling.h"

#define DTOP_GEN_SIZE 8192
#define DTOP_GEN_LINE (DTOP_GEN_SIZE>>2)
#define NO_CPUS_ONLINE -1

/**
 * @brief Searches /sys/devices/system/cpu/ directory to get find number of CPUs.
 *
 * @return Number of CPUs found in directory.
 */
static int dtop_cpu_search(void)
{
	DIR *dp;
	struct dirent *entry;
	struct stat s;
	int cpu_amt;
	char cwd[1024];

	if (!getcwd(cwd, sizeof(cwd))) {
		fprintf(stderr, "Failed to get current working dir\n");
		return -1;
	}

	dp = opendir("/sys/devices/system/cpu/");
	if (dp == NULL) {
		fprintf(stderr, "err=%d: %s\n", errno, strerror(errno));
		fprintf(stderr, "Cannot open directory: %s\n",
					"/sys/devices/system/cpu/");
		return NO_CPUS_ONLINE;
	}

	chdir("/sys/devices/system/cpu/");
	cpu_amt = 0;
	while ((entry = readdir(dp))) {
		if (stat(entry->d_name, &s)) {
			printf("stat err=%d: %s\n", errno, strerror(errno));
			return NO_CPUS_ONLINE;
		}

		if (entry->d_name[0] == 'c' &&
			entry->d_name[1] == 'p' &&
			entry->d_name[2] == 'u' &&
			(isdigit(entry->d_name[3]))) {

			cpu_amt++;
		}
	}

	closedir(dp);
	chdir(cwd);
	return cpu_amt;
}

/**
 * @brief Creates a dpg designed for CPU online and CPU scaling_cur_freq stats.
 *
 * @param name Name of file dpg represents.
 */
static void construct_cpu_stat_dpg(char *name)
{
	char *file = malloc(strlen(name) + 1);
	struct dtop_data_point *dp =
			malloc(sizeof(struct dtop_data_point));
	struct dtop_data_point_gatherer *dpg = malloc
		(sizeof(struct dtop_data_point_gatherer));

	strlcpy(file, name, strlen(name) + 1);

	dp[0].type = DTOP_ULONG;
	dp[0].name = malloc(5);
	strlcpy(dp[0].name, "", 5);
	dp[0].prefix = NULL;
	dp[0].data.d_ulong = 0;
	dp[0].initial_data.d_ulong = 0;
	dp[0].skip = DO_NOT_SKIP;
	dp[0].initial_data_populated = NOT_POPULATED;

	dpg->prefix = file;
	dpg->file = file;
	dpg->poll = dtop_value_only_poll;
	dpg->data_points = dp;
	dpg->data_points_len = 1;
	dpg->deconstruct = dtop_value_only_dpg_deconstructor;

	dtop_register(dpg);
}

/**
 * @brief Calls dpg constructor for necessary CPU stat files.
 *
 * Creates file names based on number of CPUs found and calls the
 * dpg constructor for them.
 *
 * @param file Directory where the CPUs are found.
 * @param add String which is concatenated onto file and represents
 * the path after a CPU directory is entered.
 * @param cpu_amt Amount of CPUs found on device.
 */
static void cpu_poll_helper(char *file, char *add, int cpu_amt)
{
	int i;
	for (i = 0; i < cpu_amt; i++) {
		char *cpu_num = malloc(5);
		char *newfile;
		int nf_len;
		snprintf(cpu_num, 5, "%d", i);
		nf_len = strlen(file) + strlen(add) + strlen(cpu_num) + 2;
		newfile = malloc(nf_len);
		strlcpy(newfile, file, nf_len);
		strlcat(newfile, cpu_num, nf_len);
		strlcat(newfile, add, nf_len);
		free(cpu_num);
		construct_cpu_stat_dpg(newfile);
		free(newfile);
	}
}

/**
 * @brief Calls necessary functions for CPU stat dpgs.
 */
void dtop_cpu_stats_init(void)
{
	int cpu_amt;
	char *file = "/sys/devices/system/cpu/cpu";
	char *add = "/cpufreq/scaling_cur_freq";

	cpu_amt = dtop_cpu_search();
	cpu_poll_helper(file, add, cpu_amt);
	add = "/online";
	cpu_poll_helper(file, add, cpu_amt);
}
