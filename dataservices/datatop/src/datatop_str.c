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
 * @file datatop_str.c
 * @brief Algorithms used for storing and polling data created.
 *
 * Methods created which store collected data from files in
 * dictionaries for many different file formats.
 */

#include <stdio.h>
#include <string.h>
#include "datatop_str.h"

/** @brief Reads an individual line from a file.
 *
 * Will read from buf2 until either a '\n' is reached, or the end of buf1
 * or buf2 is reached. The result is guaranteed to be null terminated.
 *
 * @param buf1 Destination buffer to store the read line.
 * @param len1 Size of destination buffer.
 * @param buf2 Source buffer to read lines from. Const, will not be
 *             modified by this function.
 * @param len2 Size of the source buffer.
 * @param start Offset (in bytes) to start reading from source buffer.
 * @return Length of line (of chars).
 */
int dt_read_line(char *buf1, int len1, const char *buf2, int len2, int start)
{
	int i, j;

	if (len1 < 1 || len2 < 1 || start < 0 || start > len2)
		return 0;

	if (buf1 == 0 || buf2 == 0)
		return 0;

	i = 0;
	j = start;

	while ((i < (len1-1)) && (j < len2)) {
		buf1[i] = buf2[j];
		if (buf1[i] == '\n')
			break;
		i++;
		j++;
	}
	buf1[i] = 0;
	return i;
}

/**
 * @brief Parses files that have Names and Values on separate lines.
 *
 * Use this method to parse files that have names on one line, followed by
 * the corresponding values on the next line. Such as "/proc/net/netstat"
 *
 * @param line1 First line that is parsed to store the datapoint names as keys.
 * @param len1 Length of line1.
 * @param line2 Second line that is parsed to store the datapoint values as dictionary values.
 * @param len2 Length of line2.
 * @param dict Dictionary that keys and values are added to.
 * @return Number of key/val pairs in the dictionary.
 */
int dt_parse_proc_dictionary(char *line1, int len1, char *line2,
			     int len2, struct dt_procdict *dict)
{
	int i, j, k;

	if (len1 < 1 || len2 < 1)
		return 0;

	if (line1 == 0 || line2 == 0 || dict == 0)
		return 0;

	k = 0;
	for (i = 0; i < len1 && k < DTOP_DICT_SIZE; i++) {
		if (line1[i] == ' ') {
			dict->key[k] = &line1[i+1];
			line1[i] = 0;
			k++;
		}
	}
	j = k;

	k = 0;
	for (i = 0; i < len2 && k < DTOP_DICT_SIZE; i++) {
		if (line2[i] == ' ') {
			dict->val[k] = &line2[i+1];
			line2[i] = 0;
			k++;
		}
	}
	if (j != k) {
		if (k < j)
			j = k;
		fprintf(stderr, "Warning, list index length mismatch\n");
	}
	dict->max = j;
	return j;
}

/**
 * @brief Parses line for prefixes for files that have individual data_point prefixes.
 *
 * Use this method for lines that have a prefix before data begins. Such as
 * "/proc/net/snmp"
 *
 * @param line1 Line to parse to find datapoint prefix.
 * @param len1 Length of line1.
 * @param dict Dictionary prefix is being added to.
 */
void dt_parse_for_prefix(char *line1, int len1, struct dt_procdict *dict)
{
	int i, j, k;

	if (len1 < 1)
		return;

	if (line1 == 0 || dict == 0)
		return;

	k = 0;
	for (i = 0; i < len1 && k < DTOP_DICT_SIZE; i++) {
		if (line1[i] == ' ') {
			dict->key[k] = &line1[i+1];
			line1[i] = 0;
			k++;
		}
	}

	for (j = 0; j < k; j++)
		dict->val[j] = &line1[0];

	for (j = 0; j < len1; j++) {
		if (line1[j] == ':')
			line1[j] = 0;
	}
}

/**
 * @brief Finds the dictionary index of a data_point name.
 *
 * @param str Name of data_point that is to be located in dict.
 * @param dict Dictionary to look through for dp name.
 * @return Dictionary index of name if found.
 * @return -1 if name not found in dictionary keys.
 */
int dt_find_dict_idx(const char *str, struct dt_procdict *dict)
{
	int i;
	if (str == 0 || dict == 0)
		return -1;

	for (i = 0; i < dict->max; i++) {
		if (dict->key[i] && !strcmp(str, dict->key[i]))
			return i;
	}
	return -1;
}

/**
 * @brief Parses files that have Names and Values on same line.
 *
 * Use this method to parse lines that have a dp name followed
 * by a dp value. Such as "/proc/net/snmp6"
 *
 * @param line1 Line to parse to find datapoint names and values.
 * @param len1 Length of line1.
 * @param l Index in the dictionary the key/val pair is added to.
 * @param dict Dictionary the keys and values are added to.
 * @return Number of key/val pairs in the dictionary.
 */
int dt_parse_proc_same_line_key_and_val(char *line1, int len1,
					int l, struct dt_procdict *dict)
{
	int i, k, n;
	if (len1 < 1)
		return 0;

	if (line1 == 0 || dict == 0)
		return 0;

	k = l;
	for (i = 0; i < len1 && k < DTOP_DICT_SIZE; i++) {
		if (line1[i] == ' ') {
			dict->key[k] = &line1[0];
			line1[i] = 0;
			for (n = i+1; n < len1; n++) {
				if (line1[n] != ' ') {
					dict->val[k] = &line1[n+1];
					break;
				}
			}
			break;
		}
	}
	k++;
	dict->max = k;
	return k;
}

/**
 * @brief Parses files that have a single line.
 *
 * Parses a single line file for csv, tab-separated, space-separated, and single
 * value formats and adds values to a dictionary. Such as
 * "/proc/sys/net/ipv4/ping_group_range"
 *
 * Use this method to parse lines that contain only values.
 *
 * @param line1 Line to parse.
 * @param len1 Length of line1.
 * @param dict Dictionary datapoints are added to.
 * @return Number of values dictionary holds.
 */
int dt_single_line_parse(char *line1, int len1, struct dt_procdict *dict)
{
	int i, k;
	k = 0;
	dict->val[k] = &line1[0];
	k++;

	for (i = 0; i < len1; i++) {
		if (line1[i] == ' ' || line1[i] == ',' || line1[i] == '	') {
			line1[i] = 0;
			dict->val[k] = &line1[i+1];
			k++;
		}
	}
	dict->max = k;
	return k;
}
