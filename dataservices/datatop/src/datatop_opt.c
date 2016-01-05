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
 * @file datatop_opt.c
 * @brief Adds getopt functionality for CLI commands.
 *
 * Contains method for getopt functionality used for parsing
 * the CLI arguments into executable commands. Handles
 * errors which arise when parsing.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>
#include "datatop_opt.h"
#include "datatop_interface.h"
#include "datatop_linked_list.h"
#include "datatop_fileops.h"

/**
 * @brief Populate the comand line options with sane defaults
 *
 * @param clopts Struct used to hold data regarding CLI arguments.
 */
void dtop_load_default_options(struct cli_opts *clopts)
{
	memset(clopts, 0, sizeof(struct cli_opts));

	clopts->priority = DEFAULT_NICE;
}

/**
 * @brief Parses all CLI commands for main() to execute.
 *
 * @param clopts Struct used to hold data regarding CLI arguments.
 * @param argc Parameter used to read CLI commands from.
 * @param argv Parameter used to read CLI arguments from.
 * @return PARSE_SUCCESS - CLI arguments read successfully,
 * @return PARSE_FAILURE - CLI arguments and/or input not valid.
 * @return PARSE_FORCE_EXIT - Exit immediately, print help options.
 */
int dtop_parse_cli_opts(struct cli_opts *clopts, int argc, char **argv)
{
	int option;

	if (!clopts || !*argv) {
		printf("Internal Error: Null Pointer\n");
		goto error;
	}

	while ((option = getopt(argc, argv, "phi:t:w:s:n:")) != -1) {
		switch (option) {
		case 'p':
			clopts->print_cl = OPT_CHOSE;
		break;

		case 'h':
			dtop_print_help_opts();
			return PARSE_FORCE_EXIT;
		break;

		case 'n':
			clopts->priority = strtol(optarg, 0, 10);
			if (clopts->priority > 19 || clopts->priority < -20) {
				printf("Argument for -n is not valid. ");
				printf("Must be between -20 and 19.\n");
				goto error;
			}
		break;

		case 'i':
			clopts->poll_per = strtol(optarg, 0, 10);
			if (clopts->poll_per <= 0) {
				printf("Argument for -i is not valid. ");
				printf("Must be positive integer.\n");
				goto error;
			}
		break;

		case 't':
			clopts->poll_time = strtol(optarg, 0, 10);
			clopts->poll_time_selected = POLL_TIME_SELECTED;
			if (clopts->poll_time <= 0) {
				printf("Argument for -t is not valid. ");
				printf("Must be positive integer.\n");
				goto error;
			}
		break;

		case 'w':
			if (dtop_check_writefile_access(optarg) == VALID) {
				clopts->file_name = optarg;
				clopts->print_csv = OPT_CHOSE;
			} else {
				goto error;
			}
		break;

		case 's':
			if (dtop_check_writefile_access(optarg) == VALID)
				clopts->snapshot_file = optarg;
			else
				goto error;
		break;

		case '?':
		default:
			goto error;
		}
	}

	if (clopts->poll_time == 0) {
		if (clopts->print_csv == 1)
			clopts->poll_time = POLL_NOT_SPECIFIED;
		else
			clopts->poll_time = POLL_TIME_DEFAULT;
	}
	if (clopts->poll_per == 0)
		clopts->poll_per = DEFAULT_POLL_INTERVAL;

	return PARSE_SUCCESS;

error:
	printf("See datatop -h for help\n");
	return PARSE_FAILURE;
}

/**
 * @brief Prints the options the user has for the program to terminal.
 */
void dtop_print_help_opts(void)
{
	printf("The following datatop commands are:\n");
	printf("\t-p\t\t\tPrint output to terminal\n");
	printf("\t-i , seconds\t\tSpecify polling period\n");
	printf("\t-t , seconds\t\tSpecify polling duration\n");
	printf("\t-w , file name (.csv)\tWrite output to a file\n");
	printf("\t-s , file name\t\tPrint system snapshot to a file\n");
	printf("\t-n , nice value\t\tSet niceness (default 19)\n");
	printf("\t-h\t\t\tGet help\n");
}


/**
* @brief Prints the interactive options the user can enter during runtime.
*/
void dtop_print_interactive_opts(void)
{
	printf("The following interactive commands are:\n");
	printf("\tq | quit\tTerminate program at any time\n");
	printf("\ti\t\tPrint dp differences, reset initial dp values\n");
	printf("\tl\t\tPrint dp differences since last reset\n");
	printf("\n");
}
