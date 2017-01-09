LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := native_audio_module
LOCAL_SRC_FILES := native_audio_jni.c

# add the dependencies of third-party libraries
# the library for native audio process
LOCAL_LDLIBS += -lOpenSLES
# the library for native log
LOCAL_LDLIBS += -llog
# the library for manage native asset manager
LOCAL_LDLIBS += -landroid


include $(BUILD_SHARED_LIBRARY)



