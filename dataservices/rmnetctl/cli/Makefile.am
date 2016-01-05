AM_CFLAGS = -Wall -Werror -Wundef -Wstrict-prototypes -Wno-trigraphs
AM_CFLAGS += -I./../inc
rmnetcli_SOURCES = rmnetcli.c
bin_PROGRAMS = rmnetcli
requiredlibs = ../src/librmnetctl.la
rmnetcli_LDADD = $(requiredlibs)
LOCAL_MODULE := librmnetctl
LOCAL_PRELINK_MODULE := false
include $(BUILD_SHARED_LIBRARY)
