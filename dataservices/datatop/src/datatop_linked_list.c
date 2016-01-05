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
 * @file datatop_linked_list.c
 * @brief Necessary linked_list functions created.
 *
 * Holds function which adds to or creates a linked list
 * used for storing dtop_data_point_gatherer's (dpg's).
 * Datapoints are stored in linked list for ability to
 * iteratively poll and print efficiently. Handles creation
 * and deletion of memory for linked list nodes.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "datatop_linked_list.h"

/**
 * @brief Adds a node to the beginning of a linked list.
 *
 * @param data A void pointer which can hold any data in the node.
 * @param list The list that is added to.
 * @return Updated linked list struct.
 */
struct dtop_linked_list *dtop_add_linked_list(void *data,
				struct dtop_linked_list *list)
{
	struct dtop_linked_list *list_node;
	list_node = malloc(sizeof(struct dtop_linked_list));

	if (!list_node) {
		fprintf(stderr, "failed to allocate memory.\n");
		exit(EXIT_FAILURE);
	}

	list_node->data = data;
	list_node->next_ptr = list;
	list = list_node;
	return list;
}

/**
 * @brief Deletes a linked list.
 *
 * @param head_ptr Pointer to the first node in the linked list that is to be deleted.
 */
void dtop_rem_linked_list(struct dtop_linked_list *head_ptr)
{
	struct dtop_linked_list *tmp_ptr = NULL;
	while (head_ptr) {
		tmp_ptr = head_ptr;
		head_ptr = head_ptr->next_ptr;
		free(tmp_ptr);
	}
}
