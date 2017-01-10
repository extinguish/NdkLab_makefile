# the makefile of which need to depends on the static libraries that provided by submodules/
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_SRC_FILES := compute.cpp
LOCAL_MODULE := compute
LOCAL_STATIC_LIBRARIES := add mul divide
include $(BUILD_EXECUTABLE)