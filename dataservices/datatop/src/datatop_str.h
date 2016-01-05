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
 * @file datatop_str.h
 * @brief Declares methods held in datatop_str.c and defines dictionary struct.
 */

#ifndef DATATOP_STR_H
#define DATATOP_STR_H

#define DTOP_DICT_SIZE 2048

/**
 * @struct dt_procdict
 * @brief Struct used to create dictionary for parsing purposes.
 *
 * @var dt_procdict::max
 * Number of key/val pairs in dictionary.
 * @var dt_procdict::key
 * Holds the key that is used to access the value.
 * @var dt_procdict::val
 * Value that the key accesses.
 */
struct dt_procdict {
	int max;
	char *key[DTOP_DICT_SIZE];
	char *val[DTOP_DICT_SIZE];
};

int dt_read_line(char *buf1, int len1, const char *buf2, int len2, int start);

int dt_parse_proc_dictionary(char *line1, int len1, char *line2, int len2,
			     struct dt_procdict *dict);

int dt_find_dict_idx(const char *str, struct dt_procdict *dict);

int dt_parse_proc_same_line_key_and_val(char *line1, int len1, int l,
					struct dt_procdict *dict);

void dt_parse_for_prefix(char *line1, int len1, struct dt_procdict *dict);

int dt_single_line_parse(char *line1, int len1, struct dt_procdict *dict);
#endif /* DATATOP_STR_H */
