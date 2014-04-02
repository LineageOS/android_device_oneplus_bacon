LOCAL_PATH := $(call my-dir)

#----------------------------------------------------------------------
# extra images
#----------------------------------------------------------------------
include build/core/generate_extra_images.mk

# Radio images
$(call add-radio-file,radio/filesmap)
$(call add-radio-file,radio/logo.bin)
