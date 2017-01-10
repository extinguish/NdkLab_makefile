# the main entrance of the Android.mk, and this makefile contains all of the basic
# sub-modules of this whole project
TOP_LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

# now, include the make file under the main/ and submodules/ directory
include $(TOP_LOCAL_PATH)/../src/submodules/Android.mk
include $(TOP_LOCAL_PATH)/../src/main/Android.mk
