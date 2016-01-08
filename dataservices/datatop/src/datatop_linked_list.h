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
 * @file datatop_linked_list.h
 * @brief Defines linked list struct and declares linked list methods.
 *
 * Defines linked list struct which can be used for any data
 * storage. Declares methods held within datatop_linked_list.c.
 */

#ifndef DATATOP_LINKED_LIST_H
#define DATATOP_LINKED_LIST_H

/**
 * @struct dtop_linked_list
 * @brief Struct used to represent linked list node that stores a pointer with any type.
 *
 * @var dtop_linked_list::next_ptr
 * Pointer to next node in the list.
 * @var dtop_linked_list::data
 * Pointer to data the node stores.
 */
struct dtop_linked_list {
	struct dtop_linked_list *next_ptr;
	void *data;
};

struct dtop_linked_list *dtop_add_linked_list(void *data,
				struct dtop_linked_list *list);
void dtop_rem_linked_list(struct dtop_linked_list *head_ptr);
#endif /* DATATOP_LINKED_LIST_H */

