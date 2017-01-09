LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := Hello.cpp
LOCAL_MODULE := hello_first

include $(BUILD_EXECUTABLE)
