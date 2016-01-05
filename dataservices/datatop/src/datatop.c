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
* @file datatop.c
* @brief Executes commands for application.
*
* Contains the main() function where program executes. Calls appropriate
* methods based on user's CLI commands. Executes parsing function to
* determine necessary output and handles errors which may arise during the
* parse. Initiliazes files for data collection. Will call functions designed
* to poll and print the data in understandable format.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include "datatop_interface.h"
#include "datatop_linked_list.h"
#include "datatop_opt.h"
#include "datatop_fileops.h"
#include "datatop_polling.h"
#include "datatop_gen_poll.h"

struct dtop_linked_list *first_dpg_list;
struct cli_opts usr_cl_opts;

/**
 * @brief Prints the datapoint names and values to the terminal.
 *
 * @param dpg_list A pointer to the first node of a linked list which
 *                 contains all data_point_gatherer structs to print.
 */
void dtop_print_terminal(struct dtop_linked_list *dpg_list)
{
	struct dtop_linked_list *curr_ptr = dpg_list;
	struct dtop_data_point_gatherer *dpset;

	while (curr_ptr) {
		dpset = (struct dtop_data_point_gatherer *) curr_ptr->data;
		dtop_print_dpg(dpset);
		curr_ptr = curr_ptr->next_ptr;
	}
}

/**
 * @brief Polls the data periodically and prints to file specified by the user.
 *
 * Polls the data as often as specified by the user in their CLI arguments
 * and outputs the data to a file also specified in CLI arguments. Then prints
 * a snapshot of delta(dp_value) to the terminal.
 *
 * @param dpg_list A pointer to the first node of a linked list which contains
 *                 all data_point_gatherer structs to poll and print.
 * @param fw A pointer to the file which will be printed to.
 * @return FILE_ERROR - Writing to file was unsuccessful.
 * @return FILE_SUCCESS - Writing to file was successful.
 */
int dtop_poll_periodically(struct dtop_linked_list *dpg_list, FILE *fw)
{
	struct timeval tv, timeout;
	fd_set rfds;
	time_t curtime, endtime;
	int inp = 0, quit = 0;
	struct dtop_linked_list *curr_ptr = dpg_list;
	struct dtop_data_point_gatherer *dpset;
	struct timeval ftime, itime, polltime;

	gettimeofday(&tv, NULL);
	curtime = tv.tv_sec;
	endtime = tv.tv_sec + usr_cl_opts.poll_time;

	/* print all of our datapoint names as column headers in csv format */
	if (fprintf(fw, "\"Time\",") < 0)
		return FILE_ERROR;

	while (curr_ptr) {
		dpset = (struct dtop_data_point_gatherer *) curr_ptr->data;
		if (dtop_print_dpg_names_csv(dpset, fw) == FILE_ERROR)
			return FILE_ERROR;
		curr_ptr = curr_ptr->next_ptr;
	}
	if (fprintf(fw, "\n") < 0)
		return FILE_ERROR;

	dtop_print_interactive_opts();
	gettimeofday(&itime, NULL);
	/* periodically poll the datapoints and print in csv format */
	while (curtime < endtime
		|| usr_cl_opts.poll_time == POLL_NOT_SPECIFIED) {
		FD_ZERO(&rfds);
		FD_SET(0, &rfds);
		timeout.tv_sec = usr_cl_opts.poll_per;
		timeout.tv_usec = 0;
		//ftime is right before timeout calculations for most acurate calculations
		gettimeofday(&ftime, NULL);
		timersub(&ftime, &itime, &polltime);
		timersub(&timeout,&polltime, &timeout);
		inp = select(1, &rfds, NULL, NULL, &timeout);
		gettimeofday(&itime, NULL);
		if (inp) {
			char s[4];
			scanf("%s", s);
			if (strcmp(s, "quit") == 0
			    || strcmp(s, "q") == 0) {
				quit = QUIT;
				break;
			}
			if (strcmp(s, "i") == 0) {
				dtop_print_snapshot_diff(first_dpg_list);
				dtop_reset_dp_initial_values(first_dpg_list);
			}
			if (strcmp(s, "l") == 0)
				dtop_print_snapshot_diff(first_dpg_list);
		}
		gettimeofday(&tv, NULL);
		curtime = tv.tv_sec;
		dtop_poll(dpg_list);
		printf("Polled at %ld.%06ld\n", tv.tv_sec, tv.tv_usec);
		if (dtop_print_time_at_poll(fw) == FILE_ERROR)
			return FILE_ERROR;
		if (dtop_write_pollingdata_csv(dpg_list, fw) == FILE_ERROR)
			return FILE_ERROR;
	}

	if (quit != QUIT)
		dtop_print_snapshot_diff(dpg_list);
	return FILE_SUCCESS;
}

static void dtop_set_niceness(int niceness)
{
	int pid, rc;
	pid = getpid();
	printf("Requesting nice %d\n", niceness);
	rc = setpriority(PRIO_PROCESS, pid, niceness);
	if (rc != 0)
		fprintf(stderr, "Error setting priority [%d]\n", errno);

	rc = getpriority(PRIO_PROCESS, pid);
	printf("Running with nice %d.\n", rc);
}

int main(int argc, char **argv)
{
	int parse_status;
	printf("DataTop - Version %s\n", VERSION);
	printf("(c)2014-2015 Linux Foundation\n");

	dtop_load_default_options(&usr_cl_opts);

	parse_status = dtop_parse_cli_opts(&usr_cl_opts, argc, argv);
	switch (parse_status) {
	case PARSE_SUCCESS:
		dtop_set_niceness(usr_cl_opts.priority);
	break;

	case PARSE_FORCE_EXIT:
		exit(EXIT_SUCCESS);
	break;

	case PARSE_FAILURE:
	default:
		printf("Failed to parse command line arguments.\n");
		exit(EXIT_FAILURE);
	break;
	}

	dtop_dual_line_init("/proc/net/netstat");
	dtop_dual_line_init("/proc/net/snmp");
	dtop_single_line_init("/proc/net/snmp6");
	dtop_gen_init("/proc/sys/net/");
	dtop_gen_init("/sys/module/rmnet_data/parameters/");
	dtop_gen_init("/sys/class/net/rmnet_mhi0/statistics/");
	dtop_gen_init("/sys/class/net/usb_rmnet0/statistics/");
	dtop_gen_init("/sys/class/net/rmnet_ipa0/statistics/");
	dtop_meminfo_init();
	dtop_dev_init();
	dtop_stat_init();
	dtop_cpu_stats_init();
	dtop_gen_init("/sys/kernel/debug/clk/bimc_clk/");
	dtop_gen_init("/sys/kernel/debug/clk/snoc_clk/");
	dtop_gen_init("/sys/kernel/debug/clk/pnoc_clk/");

	if (usr_cl_opts.print_cl == OPT_CHOSE) {
		dtop_poll(first_dpg_list);
		dtop_print_terminal(first_dpg_list);
	}

	if (usr_cl_opts.print_csv == OPT_CHOSE) {
		FILE *to_file = NULL;
		if ((dtop_open_writing_file(usr_cl_opts.file_name,
						&to_file)) == VALID) {
			printf("\nData being polled for %ld seconds.\n",
						usr_cl_opts.poll_time);
			if (dtop_poll_periodically(first_dpg_list, to_file)
			    == FILE_ERROR) {
				fprintf(stderr, "err=%d: %s\n", errno,
							strerror(errno));
				dtop_close_file(to_file);
				deconstruct_dpgs(first_dpg_list);
				dtop_rem_linked_list(first_dpg_list);
				exit(EXIT_FAILURE);
			}
			dtop_close_file(to_file);
		} else {
			printf("File Can Not Be Opened\n");
			exit(EXIT_FAILURE);
		}
	}

	if (usr_cl_opts.snapshot_file) {
		if (dtop_print_system_snapshot(usr_cl_opts.snapshot_file)
			    == FILE_ERROR) {
			fprintf(stderr, "err=%d: %s\n", errno,
						strerror(errno));
			deconstruct_dpgs(first_dpg_list);
			dtop_rem_linked_list(first_dpg_list);
			exit(EXIT_FAILURE);
		}
	}

	if (usr_cl_opts.print_cl == OPT_NOT_CHOSE &&
	    usr_cl_opts.print_csv == OPT_NOT_CHOSE) {
		if ((!usr_cl_opts.snapshot_file)
		   || usr_cl_opts.poll_time_selected == POLL_TIME_SELECTED) {
			printf("\nData will now be polled for %ld seconds.\n",
							usr_cl_opts.poll_time);
			dtop_poll(first_dpg_list);
			sleep(usr_cl_opts.poll_time);
			dtop_poll(first_dpg_list);
			dtop_print_snapshot_diff(first_dpg_list);
		}
	}

	deconstruct_dpgs(first_dpg_list);
	dtop_rem_linked_list(first_dpg_list);
	return 0;
}

/**
 * @brief Adds each dpg as a node to a linked list.
 *
 * Called when a dpg is initialized.
 *
 * @param dpg A pointer to a data_point_gatherer struct which is to be added to the linked list.
 */
void dtop_register(struct dtop_data_point_gatherer *dpg)
{
	if (dpg)
		first_dpg_list = dtop_add_linked_list(dpg, first_dpg_list);
}
