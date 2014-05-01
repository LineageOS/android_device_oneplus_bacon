LOCAL_PATH := $(call my-dir)

#----------------------------------------------------------------------
# extra images
#----------------------------------------------------------------------
include build/core/generate_extra_images.mk

# Radio images
$(call add-radio-file,radio/filesmap)
$(call add-radio-file,radio/NON-HLOS.bin)
$(call add-radio-file,radio/sbl1.mbn)
$(call add-radio-file,radio/sdi.mbn)
$(call add-radio-file,radio/emmc_appsboot.mbn)
$(call add-radio-file,radio/rpm.mbn)
$(call add-radio-file,radio/tz.mbn)
$(call add-radio-file,radio/logo.bin)
