LOCAL_PATH := $(call my-dir)

# build the first lib
include $(CLEAR_VARS)

LOCAL_MODULE := twolibs_first
LOCAL_SRC_FILES := first.c

include $(BUILD_STATIC_LIBRARY)

# build the second lib
include $(CLEAR_VARS)

LOCAL_MODULE := twolibs_second
LOCAL_SRC_FILES := second.c

LOCAL_STATIC_LIBRARIES := twolibs_first


include $(BUILD_SHARED_LIBRARY)



