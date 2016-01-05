/******************************************************************************
			S O C K E V _ C L I . C
Copyright (c) 2013, The Linux Foundation. All rights reserved.
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

/******************************************************************************
  @file    sockev_cli.c
  @brief   command line test utility to receive sockev netlink messages.
******************************************************************************/

#include <sys/socket.h>
#include <linux/netlink.h>
#include <linux/sockev.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define SOCKEVCLI_ERROR -1

int main(void)
{
	int skfd, rc;
	socklen_t addrlen;
	struct sockaddr_nl my_addr, src_addr;
	struct nlmsghdr *nlh = NULL;
	struct sknlsockevmsg *msg;

	nlh = (struct nlmsghdr *)
		malloc(NLMSG_SPACE(sizeof(struct sknlsockevmsg) + 16));
	if (!nlh) {
		fprintf(stderr, "malloc() failed\n");
		return SOCKEVCLI_ERROR;
	}

	skfd = socket(AF_NETLINK, SOCK_RAW, NETLINK_SOCKEV);
	if (skfd < 0) {
		fprintf(stderr, "nl_open_sock: socket failed\n");
		return SOCKEVCLI_ERROR;
	}

	memset(&my_addr, 0, sizeof(struct sockaddr_nl));

	my_addr.nl_family = AF_NETLINK;
	my_addr.nl_pid = getpid();
	my_addr.nl_groups = SKNLGRP_SOCKEV;

	rc = bind(skfd, (struct sockaddr *)&my_addr,
		  sizeof(struct sockaddr_nl));
	if (rc < 0) {
		fprintf(stderr, "nl_open_sock: bind failed\n");
		close(skfd);
		return SOCKEVCLI_ERROR;
	}

	while (1) {
		recvfrom(skfd, nlh, sizeof(struct sknlsockevmsg) + 16, 0,
			 (const struct sockaddr *)&src_addr, &addrlen);
		msg = NLMSG_DATA(nlh);
		printf("----------------------------\n");
		printf("pid:\t%d\n", msg->pid);
		printf("event:\t%s\n", msg->event);
		printf("skfamily:\t0x%04X\n", msg->skfamily);
		printf("skstate:\t%03d\n", msg->skstate);
		printf("skprotocol:\t%03d\n", msg->skprotocol);
		printf("sktype:\t0x%04X\n", msg->sktype);
		printf("skflags:\t0x%016llX\n", msg->skflags);
	}

	return 0;
}

