## Makefile.am for main application

CFLAGS := -std=c99                        # Target c99 for portability
CFLAGS += -Wall -Wextra -Werror -pedantic # Strict code quality enforcement
CFLAGS += -g -D _BSD_SOURCE               # Enable debugging and BSD time functions

bin_PROGRAMS = datatop
datatop_SOURCES := datatop.c
datatop_SOURCES += datatop_fileops.c
datatop_SOURCES += datatop_dual_line_poll.c
datatop_SOURCES += datatop_single_line_poll.c
datatop_SOURCES += datatop_meminfo_file_poll.c
datatop_SOURCES += datatop_dev_poll.c
datatop_SOURCES += datatop_stat_poll.c
datatop_SOURCES += datatop_value_only_poll.c
datatop_SOURCES += datatop_str.c
datatop_SOURCES += datatop_cpu_stats_poll.c
datatop_SOURCES += datatop_helpers.c
datatop_SOURCES += datatop_linked_list.c
datatop_SOURCES += datatop_opt.c
datatop_SOURCES += datatop_gen_poll.c
datatop_SOURCES += datatop_sys_snap.c
