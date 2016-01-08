ifneq ($(filter bacon,$(TARGET_DEVICE)),)

include $(call all-subdir-makefiles)

endif