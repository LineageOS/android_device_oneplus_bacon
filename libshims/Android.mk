LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := wvm_shim.cpp
LOCAL_SHARED_LIBRARIES := libstagefright_foundation
LOCAL_MODULE := libshim_wvm
LOCAL_MODULE_TAGS := optional
include $(BUILD_SHARED_LIBRARY)
