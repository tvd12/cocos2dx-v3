LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
                   ../../Classes/TestFacebookUser/TestFacebookUserScene.cpp \
                   ../../Classes/TestFacebookShare/TestFacebookShare.cpp \
                   ../../Classes/SqliteTest/sqlite3.c \
                   ../../Classes/SqliteTest/Test/SqliteTestScene.cpp \
                   ../../Classes/SqliteTest/Test/Sqlite3Helper.cpp \
                   ../../Classes/SqliteTest/Test/SqlCell.cpp \
                   ../../Classes/SqliteTest/Test/SqlColumn.cpp \
                   ../../Classes/SqliteTest/Test/SqlObject.cpp \
                   ../../Classes/SqliteTest/Test/SqlRow.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
					$(LOCAL_PATH)/../../Classes/TestFacebookUser \
					$(LOCAL_PATH)/../../Classes/TestFacebookShare \
					$(LOCAL_PATH)/../../Classes/SqliteTest/Test \
					$(LOCAL_PATH)/../../Classes/SqliteTest \

LOCAL_STATIC_LIBRARIES := cocos2dx_static

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static \
PluginProtocolStatic

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,plugin/protocols/proj.android/jni)
