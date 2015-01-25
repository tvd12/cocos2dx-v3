LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

#$(call import-add-path,$(LOCAL_PATH)/../../../cocos2dx-plugin-util)

LOCAL_MODULE := google_analytics_static

LOCAL_MODULE_FILENAME := libgoogle_analytics_static

LOCAL_SRC_FILES :=\
		Classes/GoogleAnalyticsHelper.cpp \

LOCAL_CFLAGS := -std=c++11 -Wno-psabi
LOCAL_EXPORT_CFLAGS := -Wno-psabi

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../include
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include 

LOCAL_LDLIBS := -landroid
LOCAL_LDLIBS += -llog
LOCAL_STATIC_LIBRARIES := cocos2dx_plugin_util

include $(BUILD_STATIC_LIBRARY)

#$(call import-module,android/jni)
