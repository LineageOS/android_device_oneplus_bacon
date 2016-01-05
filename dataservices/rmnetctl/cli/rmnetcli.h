/******************************************************************************

			  R M N E T C L I . H

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

/******************************************************************************

  @file	   rmnetcli.h
  @brief   headers for the command line interface to expose rmnet control API's

  DESCRIPTION
  Header file containing definition for the command line interface to expose
  rmnet control API's

******************************************************************************/

#ifndef RMNETCLI_H
#define RMNETCLI_H

/* Print the help for the commands since the help flag was used. */
#define RMNETCTL_CFG_SUCCESS_HELP_COMMAND 100
/* No/invalid API call was specified. So return an error. */
#define RMNETCTL_CFG_FAILURE_NO_COMMAND 101
/* The buffer for egress device name was NULL */
#define RMNETCTL_CFG_FAILURE_EGRESS_DEV_NAME_NULL 102

/* This should always be the value of the starting element */
#define RMNETCFG_ERR_NUM_START 100

/* This should always be the total number of error message from CLI */
#define RMNETCFG_TOTAL_ERR_MSGS 3

#endif /* not defined RMNETCLI_H */
