LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := ../src/hello.c
LOCAL_MODULE := hello_second

include $(BUILD_EXECUTABLE)