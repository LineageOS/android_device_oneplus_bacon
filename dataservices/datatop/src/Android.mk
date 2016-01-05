LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := datatop.c
LOCAL_SRC_FILES += datatop_cpu_stats_poll.c
LOCAL_SRC_FILES += datatop_dev_poll.c
LOCAL_SRC_FILES += datatop_dual_line_poll.c
LOCAL_SRC_FILES += datatop_fileops.c
LOCAL_SRC_FILES += datatop_gen_poll.c
LOCAL_SRC_FILES += datatop_helpers.c
LOCAL_SRC_FILES += datatop_linked_list.c
LOCAL_SRC_FILES += datatop_meminfo_file_poll.c
LOCAL_SRC_FILES += datatop_opt.c
LOCAL_SRC_FILES += datatop_single_line_poll.c
LOCAL_SRC_FILES += datatop_stat_poll.c
LOCAL_SRC_FILES += datatop_str.c
LOCAL_SRC_FILES += datatop_sys_snap.c
LOCAL_SRC_FILES += datatop_value_only_poll.c

LOCAL_CFLAGS := -Wall -Wextra -Werror -pedantic -std=c99
LOCAL_CFLAGS += -DVERSION="\"1.0.4"\"
LOCAL_CFLAGS += -DHAVE_STRL_FUNCTIONS
LOCAL_CFLAGS += -D _BSD_SOURCE

LOCAL_C_INCLUDES := $(LOCAL_PATH)

LOCAL_MODULE := datatop
LOCAL_MODULE_TAGS := optional

include $(BUILD_EXECUTABLE)
