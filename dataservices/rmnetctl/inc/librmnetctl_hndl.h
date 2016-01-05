/******************************************************************************

			L I B R M N E T C T L _ H N D L. H

Copyright (c) 2013, 2015 The Linux Foundation. All rights reserved.

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

******************************************************************************/

/*!
*  @file    librmnetctl_hndl.h
*  @brief   rmnet control API's handle file
*/

#ifndef LIBRMNETCTL_HNDL_H
#define LIBRMNETCTL_HNDL_H

/*===========================================================================
			 DEFINITIONS AND DECLARATIONS
===========================================================================*/

/*!
* @brief Structure for RMNET control handles. A rmnet hndl contains the caller
* process id, the transaction id which is initialized to 0 for each new
* initialized handle and the netlink file descriptor for this handle.
* @var pid process id to be used for the netlink message
* @var transaction_id message number for debugging
* @var netlink_fd netlink file descriptor to be used
* @var src_addr source socket address properties for this message
* @var dest_addr destination socket address properties for this message
*/

struct rmnetctl_hndl_s {
	 uint32_t pid;
	 uint32_t transaction_id;
	 int netlink_fd;
	 struct sockaddr_nl src_addr, dest_addr;
};

#endif /* not defined LIBRMNETCTL_HNDL_H */

