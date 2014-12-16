LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := \
		hellocpp/main.cpp \
		../../Classes/AppDelegate.cpp \
		../../Classes/HelloWorldScene.cpp \
		../../Classes/SqliteTest/sqlite3.c \
		../../Classes/SqliteTest/Test/SqlCell.cpp \
		../../Classes/SqliteTest/Test/SqlColumn.cpp \
		../../Classes/SqliteTest/Test/Sqlite3Helper.cpp \
		../../Classes/SqliteTest/Test/SqlObject.cpp \
		../../Classes/SqliteTest/Test/SqlRow.cpp \
		../../Classes/SqliteTest/Test/Try/MainGameLayer.cpp \
		../../Classes/SqliteTest/Test/Try/MapAreaLayer.cpp \
		../../Classes/SqliteTest/Test/Try/MapManager.cpp \
		../../Classes/SqliteTest/Test/Try/SqliteTestScene.cpp \
		../../Classes/TableTest/Lobby/LobbyLayerCellView.cpp \
		../../Classes/TableTest/Lobby/LobbyLayerView.cpp \
		../../Classes/TableTest/Word/WordLayer.cpp \
		../../Classes/TestFacebookShare/TestFacebookShare.cpp \
		../../Classes/TestFacebookUser/TestFacebookUserScene.cpp \
		../../Classes/View/Extends/Labels/ILabelSource.cpp \
		../../Classes/View/Extends/Labels/UpdateableLabelTTF.cpp \
		../../Classes/View/Extends/Layer/CommonLayer.cpp \
		../../Classes/View/Extends/Layer/PopupLayer.cpp \
		../../Classes/View/Extends/Layer/TableLayer.cpp \
		../../Classes/View/Extends/Tables/TableView.cpp \

LOCAL_C_INCLUDES := \
		$(LOCAL_PATH)/../../Classes \
		$(LOCAL_PATH)/../../Classes/SqliteTest \
		$(LOCAL_PATH)/../../Classes/SqliteTest/Test \
		$(LOCAL_PATH)/../../Classes/SqliteTest/Test/Try \
		$(LOCAL_PATH)/../../Classes/TableTest/Lobby \
		$(LOCAL_PATH)/../../Classes/TableTest/Word \
		$(LOCAL_PATH)/../../Classes/TestFacebookShare \
		$(LOCAL_PATH)/../../Classes/TestFacebookUser \
		$(LOCAL_PATH)/../../Classes/View/Extends/Labels \
		$(LOCAL_PATH)/../../Classes/View/Extends/Layer \
		$(LOCAL_PATH)/../../Classes/View/Extends/Tables \

LOCAL_STATIC_LIBRARIES := cocos2dx_static

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static \
PluginProtocolStatic

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,plugin/protocols/proj.android/jni)
