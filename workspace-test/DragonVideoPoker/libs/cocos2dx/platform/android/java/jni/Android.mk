LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libcocos2dx
LOCAL_SRC_FILES := libcocos2dx.cpp

include $(BUILD_SHARED_LIBRARY)
