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
 * @file datatop_opt.h
 * @brief Declares methods and defines struct used within datatop_opt.c
 *
 * Struct defined is used when parsing the CLI arguments.
 */

#ifndef DATATOP_OPT_H
#define DATATOP_OPT_H

#define OPT_CHOSE             1
#define OPT_NOT_CHOSE         0
#define DEFAULT_POLL_INTERVAL 1
#define POLL_NOT_SPECIFIED   -1
#define POLL_TIME_DEFAULT     30
#define POLL_TIME_SELECTED     1
#define PARSE_SUCCESS     0
#define PARSE_FAILURE    -1
#define PARSE_FORCE_EXIT -2
#define VALID 0
#define INVALID -1
#define DEFAULT_NICE 19               /* Lowest priority */

/**
 * @struct cli_opts
 * @brief Struct used to store arguments from CLI input.
 *
 * @var cli_opts::print_cl
 * Represents -p argument.
 * @var cli_opts::poll_per
 * Polling frequency argument.
 * @var cli_opts::poll_time
 * Polling duration argument.
 * @var cli_opts::cli_help
 * Represents -h argument.
 * @var cli_opts::file_name
 * File name argument.
 * @var cli_opts::print_csv
 * Represents -w argument.
 */
struct cli_opts {
	int print_cl;                   /* -p option */
	long int poll_per;              /* -i option */
	long int poll_time;             /* -t option */
	int cli_help;                   /* -h option */
	char *file_name;                /* -w option */
	char *snapshot_file;            /* -s option */
	int print_csv;
	int poll_time_selected;
	int priority;                   /* -n option (niceness) */
};

int dtop_parse_cli_opts(struct cli_opts *clopts, int argc, char **argv);
void dtop_print_help_opts(void);
void dtop_print_interactive_opts(void);
void dtop_load_default_options(struct cli_opts *clopts);

#endif /* DATATOP_OPT_H */

