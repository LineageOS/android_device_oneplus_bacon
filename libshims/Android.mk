LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := camera_shim.cpp
LOCAL_SHARED_LIBRARIES := libui
LOCAL_MODULE := libshim_camera
LOCAL_MODULE_TAGS := optional
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := cameraclient_shim.cpp

LOCAL_MODULE := libshim_cameraclient
LOCAL_MODULE_TAGS := optional
include $(BUILD_SHARED_LIBRARY)
