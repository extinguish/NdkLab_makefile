LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := ./divide.cpp
LOCAL_MODULE := divide

include $(BUILD_STATIC_LIBRARY)