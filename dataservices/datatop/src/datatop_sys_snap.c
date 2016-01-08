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

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#include "datatop_interface.h"
#include "datatop_fileops.h"
#include "datatop_str.h"
#include "datatop_opt.h"

#define DTOP_SNAP_SIZE 8192
#define DTOP_SNAP_LINE (DTOP_SNAP_SIZE>>2)

static int dtop_system_snapshot_helper_print(char *file, const char *str)
{
	FILE *snap_file = fopen(file, "a");

	if (snap_file) {
		if (fprintf(snap_file, "%s", str) < 0) {
			fclose(snap_file);
			return FILE_ERROR;
		}
	} else {
			return FILE_ERROR;
	}
	fflush(snap_file);
	fclose(snap_file);
	return FILE_SUCCESS;
}

/**
 * @brief A helper function to dtop_print_system_snapshot.
 *
 * @param fw File that desired system data is printed to.
 * @return FILE_ERROR - Writing to file was unsuccessful.
 * @return FILE_SUCCESS - Writing to file was successful.
 */
static int dtop_run_and_log(char *file, const char *c1, const char **args)
{
	int i;
	pid_t child_pid;

	i = 0;
	dtop_system_snapshot_helper_print(file, "\n"
	"--------------------------------------------------------------\n"
	"Command: ");
	while(args[i] != 0) {
		dtop_system_snapshot_helper_print(file, args[i++]);
		dtop_system_snapshot_helper_print(file, " ");
	}
	dtop_system_snapshot_helper_print(file, "\n");


	child_pid = fork();
	if (child_pid == 0) {
		int fd = open(file, O_WRONLY | O_APPEND | O_CREAT,
						S_IRUSR | S_IWUSR);
		dup2(fd, STDOUT_FILENO);
		dup2(fd, STDERR_FILENO);
		close(fd);
		execvp(c1, (char * const *)args);
		printf("Failed to execute %s\n", c1);
		printf("errno=%d error=%s\n", errno, strerror(errno));
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		exit(0);
	} else if (child_pid < 0) {
		return FILE_ERROR;
	} else {
		int return_status;
		waitpid(child_pid, &return_status, 0);

		if (return_status != 0)
			return FILE_ERROR;
	}

	return FILE_SUCCESS;
}



/* IPv4 */
const char *ip_addr_cmd[] = {"ip", "addr", 0};
const char *ip_route_cmd[] = {"ip", "route", 0};
const char *ip_route_all_tables_cmd[] = {"ip", "route", "show", "table", "all", 0};
const char *ip_rule_cmd[] = {"ip", "rule", "show", 0};
const char *ip_tables_cmd[] = {"iptables", "-L", "-n", "-v", 0};
const char *ip_tables_nat_cmd[] = {"iptables", "-t", "nat", "-L", "-n", "-v", 0};
const char *ip_tables_mangle_cmd[] = {"iptables", "-t", "mangle", "-L", "-n", "-v", 0};
const char *ip_tables_raw_cmd[] = {"iptables", "-t", "raw", "-L", "-n", "-v", 0};

/* IPv6 */
const char *ip6_addr_cmd[] = {"ip", "-6", "addr", 0};
const char *ip6_route_cmd[] = {"ip", "-6", "route", 0};
const char *ip6_route_all_tables_cmd[] = {"ip", "-6", "route", "show", "table", "all", 0};
const char *ip6_rule_cmd[] = {"ip", "-6", "rule", "show", 0};
const char *ip6_tables_cmd[] = {"ip6tables", "-L", "-n", "-v", 0};
const char *ip6_tables_nat_cmd[] = {"ip6tables", "-t", "nat", "-L", "-n", "-v", 0};
const char *ip6_tables_mangle_cmd[] = {"ip6tables", "-t", "mangle", "-L", "-n", "-v", 0};
const char *ip6_tables_raw_cmd[] = {"ip6tables", "-t", "raw", "-L", "-n", "-v", 0};

/* Misc */
const char *rps_config[] = {"cat", "/sys/class/net/rmnet_mhi0/queues/rx-0/rps_cpus", 0};
const char *if_config[] = {"/data/busybox/busybox", "ifconfig", 0};
const char *netcfg[] = {"netcfg", 0};
const char *softnet_stat[] = {"cat", "/proc/net/softnet_stat", 0};

/* XFRM logging */
const char *xfrm_state[] = {"ip", "xfrm", "state", "show", 0};
const char *xfrm_policy[] = {"ip", "xfrm", "policy", "show", 0};
const char *xfrm_netstat[] = {"cat", "/proc/net/xfrm_stat", 0};

#define DO_DTOP_RUN_AND_LOG(X) \
	dtop_run_and_log(file, X[0], X);
/**
 * @brief Prints a System snapshot to a file specified by the user.
 *
 * @param fw File that system snapshot is printed to.
 * @return FILE_ERROR - Writing to file was unsuccessful.
 * @return FILE_SUCCESS - Writing to file was successful.
 */
int dtop_print_system_snapshot(char *file)
{
	dtop_system_snapshot_helper_print(file,
	"==============================================================\n"
	"    System Data Snapshot - Captured with Data Top             \n"
	"    Version ");
	dtop_system_snapshot_helper_print(file, VERSION);
	dtop_system_snapshot_helper_print(file, "\n"
	"==============================================================\n"
	"\n");

	/* IPv4 */
	DO_DTOP_RUN_AND_LOG(ip_addr_cmd);
	DO_DTOP_RUN_AND_LOG(ip_route_cmd);
	DO_DTOP_RUN_AND_LOG(ip_route_all_tables_cmd);
	DO_DTOP_RUN_AND_LOG(ip_rule_cmd);
	DO_DTOP_RUN_AND_LOG(ip_tables_cmd);
	DO_DTOP_RUN_AND_LOG(ip_tables_nat_cmd);
	DO_DTOP_RUN_AND_LOG(ip_tables_mangle_cmd);
	DO_DTOP_RUN_AND_LOG(ip_tables_raw_cmd);

	/* IPv6 */
	DO_DTOP_RUN_AND_LOG(ip6_addr_cmd);
	DO_DTOP_RUN_AND_LOG(ip6_route_cmd);
	DO_DTOP_RUN_AND_LOG(ip6_route_all_tables_cmd);
	DO_DTOP_RUN_AND_LOG(ip6_rule_cmd);
	DO_DTOP_RUN_AND_LOG(ip6_tables_cmd);
	DO_DTOP_RUN_AND_LOG(ip6_tables_nat_cmd);
	DO_DTOP_RUN_AND_LOG(ip6_tables_mangle_cmd);
	DO_DTOP_RUN_AND_LOG(ip6_tables_raw_cmd);

	/* Misc */
	DO_DTOP_RUN_AND_LOG(rps_config);
	DO_DTOP_RUN_AND_LOG(if_config);
	DO_DTOP_RUN_AND_LOG(netcfg);
	DO_DTOP_RUN_AND_LOG(softnet_stat);

	/* XFRM logging */
	DO_DTOP_RUN_AND_LOG(xfrm_state);
	DO_DTOP_RUN_AND_LOG(xfrm_policy);
	DO_DTOP_RUN_AND_LOG(xfrm_netstat);

	return FILE_SUCCESS;
}
