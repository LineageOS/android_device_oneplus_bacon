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
 * @file datatop_fileops.c
 * @brief Declares functions for reading and writing to files.
 *
 * Declares functions called when reading from files which data is collected.
 * Also contains methods to handle files which will be written to.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "datatop_interface.h"
#include "datatop_linked_list.h"
#include "datatop_opt.h"
#include "datatop_fileops.h"

/**
 * @brief Reads the lines from files which we are collecting data from.
 *
 * @param file File which is read from
 * @param buffer Pointer to buffer where data will be read. The buffer is allocated
 *               in dt_read_file() and passed back to the caller. Caller should
 *               free this when done.
 * @param len Maximum amount of data which should be read from the file.
 * @return Number of bytes of data placed in *buffer.
 */
int dt_read_file(const char *file, char **buffer, int len)
{
	int read;
	FILE *fp;

	*buffer = (char *)malloc(len);
	if (!(*buffer)) {
		fprintf(stderr, "%s(): malloc(%d) failed\n", __func__, len);
		return 0;
	}

	fp = fopen(file, "r");
	if (!fp) {
		fprintf(stderr, "%s(): Failed to open %s: ", __func__, file);
		fprintf(stderr, "Error: %s\n", strerror(errno));
		free(*buffer);
		*buffer = 0;
		return 0;
	}
	read = fread(*buffer, sizeof(char), len, fp);
	fclose(fp);

	return read;
}

/**
 * @brief Deallocates memory no longer being used.
 *
 * @param buffer Buffer to be deallocated.
 */
void dt_free(char **buffer)
{
	free(*buffer);
	*buffer = 0;
}

/**
 * @brief Checks for access to a file for writing.
 *
 * @param fw File to check access of.
 * @return INVALID - File already exists or write access denied.
 * @return VALID - File does not exist and can be written to.
 */
int dtop_check_writefile_access(char *fw)
{
	if (!access(fw, F_OK)) {
		printf("File specified already exists\n");
		return INVALID;
	}

	if (!access(fw, W_OK)) {
		printf("Permission to write to specified file denied\n");
		return INVALID;
	}

	return VALID;
}

/**
 * @brief Opens file and handles possible errors.
 *
 * @param fw File path to be opened.
 * @param to_file Pointer to the *file that is opened.
 * @return VALID - File opened successfully.
 * @return INVALID - File could not be opened.
 */
int dtop_open_writing_file(char *fw, FILE **to_file)
{
	*to_file = fopen(fw, "w");
	if (*to_file) {
		return VALID;
	} else {
		fprintf(stderr, "Value of errno: %d\n", errno);
		fprintf(stderr, "Error opening file: %s\n", strerror(errno));
		fprintf(stderr, "Please try writing to a non-existent file\n");
		printf("See datatop -h for help\n");
		return INVALID;
	}
}

/**
 * @brief Closes a file if not a standard stream.
 *
 * @param fw File to be closed.
 */
void dtop_close_file(FILE *fw)
{
	if (fw != stdout && fw != stderr && fw != stdin)
		fclose(fw);
}

/**
 * @brief Helper function to find number of lines in dual_line file.
 *
 * @return Number of lines in a dual_line file.
 */
int dtop_get_file_line_amount(char *name)
{
	signed char rc = 0;
	int line_count = 0;
	FILE *file = fopen(name, "r");
	while (rc != EOF) {
		if (rc == '\n')
			line_count++;
		rc = fgetc(file);
	}

	fclose(file);
	return line_count;
}
