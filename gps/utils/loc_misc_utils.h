/* Copyright (c) 2014, The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of The Linux Foundation, nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#ifndef _LOC_MISC_UTILS_H_
#define _LOC_MISC_UTILS_H_

#ifdef __cplusplus
extern "C" {
#endif

/*===========================================================================
FUNCTION loc_split_string

DESCRIPTION:
    This function is used to split a delimiter separated string into
    sub-strings. This function does not allocate new memory to store the split
    strings. Instead, it places '\0' in places of delimiters and assings the
    starting address of the substring within the raw string as the string address
    The input raw_string no longer remains to be a collection of sub-strings
    after this function is executed.
    Please make a copy of the input string before calling this function if
    necessary

PARAMETERS:
    char *raw_string: is the original string with delimiter separated substrings
    char **split_strings_ptr: is the arraw of pointers which will hold the addresses
                              of individual substrings
    int max_num_substrings: is the maximum number of substrings that are expected
                            by the caller. The array of pointers in the above parameter
                            is usually this long
    char delimiter: is the delimiter that separates the substrings. Examples: ' ', ';'

DEPENDENCIES
    N/A

RETURN VALUE
    int Number of split strings

SIDE EFFECTS
    The input raw_string no longer remains a delimiter separated single string.

EXAMPLE
    delimiter = ' ' //space
    raw_string = "hello new user" //delimiter is space ' '
    addresses  =  0123456789abcd
    split_strings_ptr[0] = &raw_string[0]; //split_strings_ptr[0] contains "hello"
    split_strings_ptr[1] = &raw_string[6]; //split_strings_ptr[1] contains "new"
    split_strings_ptr[2] = &raw_string[a]; //split_strings_ptr[2] contains "user"

===========================================================================*/
int loc_util_split_string(char *raw_string, char **split_strings_ptr, int max_num_substrings,
                     char delimiter);

/*===========================================================================
FUNCTION trim_space

DESCRIPTION
   Removes leading and trailing spaces of the string

DEPENDENCIES
   N/A

RETURN VALUE
   None

SIDE EFFECTS
   N/A
===========================================================================*/
void loc_util_trim_space(char *org_string);
#ifdef __cplusplus
}
#endif

#endif //_LOC_MISC_UTILS_H_
