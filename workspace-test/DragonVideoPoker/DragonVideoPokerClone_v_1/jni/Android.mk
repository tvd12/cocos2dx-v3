LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

#APP_PLATFORM := android-19

LOCAL_CFLAGS := -g

LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../libs/smartfox

LOCAL_CFLAGS += -I$(LOCAL_PATH)/../libs/boost
LOCAL_LDLIBS += -L$(LOCAL_PATH)/../libs/boost/lib
LOCAL_LDLIBS += -lboost_system-gcc-mt-1_52 -lboost_thread-gcc-mt-1_52 -lboost_regex-gcc-mt-1_52

LOCAL_CPPFLAGS += -fexceptions
LOCAL_CPPFLAGS += -frtti

LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../libs/smartfox/Bitswarm
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../libs/smartfox/Controllers
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../libs/smartfox/Core/Sockets
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../libs/smartfox/Core
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../libs/smartfox/Entities/Data
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../libs/smartfox/Entities/Invitation
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../libs/smartfox/Entities/Managers
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../libs/smartfox/Entities/Match
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../libs/smartfox/Entities/Variables
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../libs/smartfox/Entities
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../libs/smartfox/Exceptions
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../libs/smartfox/FSM
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../libs/smartfox/Logging
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../libs/smartfox/Protocol/Serialization
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../libs/smartfox/Requests/Buddylist
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../libs/smartfox/Requests/Game
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../libs/smartfox/Requests
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../libs/smartfox/Util/md5
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../libs/smartfox/Util
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../libs/eziSocial
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../libs/eziSocial/Objects

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := \
		hellocpp/main.cpp \
		../../Classes/AppDelegate.cpp \
		../../Classes/CustomUI/Labels/ILabelSource.cpp \
		../../Classes/CustomUI/Labels/UpdateableLabelTTF.cpp \
		../../Classes/CustomUI/Buttons/AvatarMenuItem.cpp \
		../../Classes/CustomUI/Buttons/SelectGameMenuItem.cpp \
		../../Classes/CustomUI/Buttons/SelectGameMenuSprite.cpp \
		../../Classes/CustomUI/CCScrollLayer.cpp \
		../../Classes/CustomUI/Tables/TableView.cpp \
		../../Classes/GameController/CardManager.cpp \
		../../Classes/GameController/Payout.cpp \
		../../Classes/GameController/PokerHand.cpp \
		../../Classes/GameController/PokerHandData.cpp \
		../../Classes/Server/Data/Bonus/DailyBonusInfo.cpp \
		../../Classes/Server/Data/Bonus/HourlyBonusInfo.cpp \
		../../Classes/Server/Data/GamePlay/Card.cpp \
		../../Classes/Server/Data/GamePlay/Paytable.cpp \
		../../Classes/Server/Data/GamePlay/PaytableCell.cpp \
		../../Classes/Server/Data/GamePlay/TdgDealCardData.cpp \
		../../Classes/Server/Data/GamePlay/TdgDonCardData.cpp \
		../../Classes/Server/Data/GamePlay/TdgDrawCardData.cpp \
		../../Classes/Server/Data/IapProduct.cpp \
		../../Classes/Server/Data/Leaderboard.cpp \
		../../Classes/Server/Data/NotificationObject.cpp \
		../../Classes/Server/Data/RoomInfo.cpp \
		../../Classes/Server/Data/UserInfo/BaseUserInfo.cpp \
		../../Classes/Server/Data/UserInfo/UserInfo.cpp \
		../../Classes/Server/Data/UserInfo/UserStatistics.cpp \
		../../Classes/Server/Data/UserInfo/VipInfo.cpp \
		../../Classes/Server/TdgServer.cpp \
		../../Classes/Server/TdgServerBaseEvent.cpp \
		../../Classes/Server/TdgServerBonus.cpp \
		../../Classes/Server/TdgServerBuddy.cpp \
		../../Classes/Server/TdgServerConfig.cpp \
		../../Classes/Server/TdgServerExtensionListener.cpp \
		../../Classes/Server/TdgServerExtensionRequest.cpp \
		../../Classes/Server/TdgServerIap.cpp \
		../../Classes/Server/TdgServerPaytable.cpp \
		../../Classes/Server/TdgServerRoom.cpp \
		../../Classes/Server/TdgServerUser.cpp \
		../../Classes/Server/TdgServerVip.cpp \
		../../Classes/UI/Popup/_Common/PopUpLayer.cpp \
		../../Classes/UI/Popup/_Common/WaitingLayer.cpp \
		../../Classes/UI/Popup/Avatar/AvatarsPopupView.cpp \
		../../Classes/UI/Popup/DailyBonus/DailyBonusPopupView.cpp \
		../../Classes/UI/Popup/Jackpot/JackpotPopupView.cpp \
		../../Classes/UI/Popup/LevelUp/LevelupPopupView.cpp \
		../../Classes/UI/Popup/Notification/NotificationPopupView.cpp \
		../../Classes/UI/Popup/Paytable/PaytablePopupCellView.cpp \
		../../Classes/UI/Popup/Paytable/PaytablePopupView.cpp \
		../../Classes/UI/Popup/Profile/ProfilePopupView.cpp \
		../../Classes/UI/Popup/Setting/SettingPopupView.cpp \
		../../Classes/UI/Popup/Shop/ShoppingMenuItemView.cpp \
		../../Classes/UI/Popup/Shop/ShoppingMenuView.cpp \
		../../Classes/UI/Popup/Shop/ShoppingPopupView.cpp \
		../../Classes/UI/Popup/Shop/ShoppingTableView.cpp \
		../../Classes/UI/Popup/VipClub/VipClubPopupView.cpp \
		../../Classes/UI/Popup/VipUpgrade/VipUpgradePopupView.cpp \
		../../Classes/UI/Popup/Leaderboard/LeaderboardPopupView.cpp \
		../../Classes/UI/Scenes/Loading/LoadingScene.cpp \
		../../Classes/UI/Scenes/Lobby/LobbyScene.cpp \
		../../Classes/UI/Scenes/Login/LoginScene.cpp \
		../../Classes/UI/Scenes/MainGame/Controller/GameController.cpp \
		../../Classes/UI/Scenes/MainGame/GameScene.cpp \
		../../Classes/UI/Scenes/MainGame/Model/Chip.cpp \
		../../Classes/UI/Scenes/MainGame/Model/ChipBetted.cpp \
		../../Classes/UI/Scenes/MainGame/Model/Deck.cpp \
		../../Classes/UI/Scenes/MainGame/Model/GameModel.cpp \
		../../Classes/UI/Scenes/MainGame/ServerSimulate.cpp \
		../../Classes/UI/Scenes/MainGame/View/CardView.cpp \
		../../Classes/UI/Scenes/MainGame/View/ChipBettedView.cpp \
		../../Classes/UI/Scenes/MainGame/View/ChipMenuItemView.cpp \
		../../Classes/UI/Scenes/MainGame/View/ChipView.cpp \
		../../Classes/UI/Scenes/MainGame/View/DeckView.cpp \
		../../Classes/UI/Scenes/MainGame/View/GameView.cpp \
		../../Classes/UI/Scenes/MainGame/View/GameViewFooter.cpp \
		../../Classes/UI/Scenes/MainGame/View/GameViewHeader.cpp \
		../../Classes/UI/Scenes/MainGame/View/GameViewMiddle.cpp \
		../../Classes/UI/Scenes/MainGame/View/PaytableCellView.cpp \
		../../Classes/UI/Scenes/MainGame/View/PaytableView.cpp \
		../../Classes/UI/Scenes/SceneController.cpp \
		../../Classes/Utils/CCAndroidStringsParser.cpp \
		../../Classes/Utils/CCLocalization.cpp \
		../../Classes/Utils/ChartBoostHelper.cpp \
		../../Classes/Utils/Defines.cpp \
		../../Classes/Utils/EziHelper.cpp \
		../../Classes/Utils/FBAvatarDownloader.cpp \
		../../Classes/Utils/GameIAPHelper.cpp \
		../../Classes/Utils/GameParams.cpp \
		../../Classes/Utils/NativeHelper.cpp \
		../../Classes/Utils/SoundManager.cpp \
		../../Classes/Utils/TextUtils.cpp \
		../../Classes/Utils/VisibleRect.cpp \
		../../libs/smartfox/Bitswarm/BaseController.cpp \
		../../libs/smartfox/Bitswarm/BBox/BBClient.cpp \
		../../libs/smartfox/Bitswarm/BBox/BBEvent.cpp \
		../../libs/smartfox/Bitswarm/BitSwarmClient.cpp \
		../../libs/smartfox/Bitswarm/BitSwarmEvent.cpp \
		../../libs/smartfox/Bitswarm/ConnectionModes.cpp \
		../../libs/smartfox/Bitswarm/Message.cpp \
		../../libs/smartfox/Bitswarm/PendingPacket.cpp \
		../../libs/smartfox/Bitswarm/UDPManager.cpp \
		../../libs/smartfox/Controllers/ExtensionController.cpp \
		../../libs/smartfox/Controllers/SystemController.cpp \
		../../libs/smartfox/Core/BaseEvent.cpp \
		../../libs/smartfox/Core/PacketHeader.cpp \
		../../libs/smartfox/Core/SFSBuddyEvent.cpp \
		../../libs/smartfox/Core/SFSEvent.cpp \
		../../libs/smartfox/Core/SFSIOHandler.cpp \
		../../libs/smartfox/Core/SFSProtocolCodec.cpp \
		../../libs/smartfox/Core/Sockets/IPAddress.cpp \
		../../libs/smartfox/Core/Sockets/TCPClient.cpp \
		../../libs/smartfox/Core/Sockets/TCPSocketLayer.cpp \
		../../libs/smartfox/Core/Sockets/UDPClient.cpp \
		../../libs/smartfox/Core/Sockets/UDPSocketLayer.cpp \
		../../libs/smartfox/Core/ThreadManager.cpp \
		../../libs/smartfox/Entities/Data/SFSArray.cpp \
		../../libs/smartfox/Entities/Data/SFSDataWrapper.cpp \
		../../libs/smartfox/Entities/Data/SFSObject.cpp \
		../../libs/smartfox/Entities/Data/Vec3D.cpp \
		../../libs/smartfox/Entities/Invitation/SFSInvitation.cpp \
		../../libs/smartfox/Entities/Managers/SFSBuddyManager.cpp \
		../../libs/smartfox/Entities/Managers/SFSGlobalUserManager.cpp \
		../../libs/smartfox/Entities/Managers/SFSRoomManager.cpp \
		../../libs/smartfox/Entities/Managers/SFSUserManager.cpp \
		../../libs/smartfox/Entities/Match/BoolMatch.cpp \
		../../libs/smartfox/Entities/Match/LogicOperator.cpp \
		../../libs/smartfox/Entities/Match/MatchExpression.cpp \
		../../libs/smartfox/Entities/Match/NumberMatch.cpp \
		../../libs/smartfox/Entities/Match/RoomProperties.cpp \
		../../libs/smartfox/Entities/Match/StringMatch.cpp \
		../../libs/smartfox/Entities/Match/UserProperties.cpp \
		../../libs/smartfox/Entities/MMOItem.cpp \
		../../libs/smartfox/Entities/MMORoom.cpp \
		../../libs/smartfox/Entities/SFSBuddy.cpp \
		../../libs/smartfox/Entities/SFSConstants.cpp \
		../../libs/smartfox/Entities/SFSRoom.cpp \
		../../libs/smartfox/Entities/SFSUser.cpp \
		../../libs/smartfox/Entities/Variables/MMOItemVariable.cpp \
		../../libs/smartfox/Entities/Variables/ReservedBuddyVariables.cpp \
		../../libs/smartfox/Entities/Variables/ReservedRoomVariables.cpp \
		../../libs/smartfox/Entities/Variables/SFSBuddyVariable.cpp \
		../../libs/smartfox/Entities/Variables/SFSRoomVariable.cpp \
		../../libs/smartfox/Entities/Variables/SFSUserVariable.cpp \
		../../libs/smartfox/Exceptions/SFSCodecError.cpp \
		../../libs/smartfox/Exceptions/SFSError.cpp \
		../../libs/smartfox/Exceptions/SFSValidationError.cpp \
		../../libs/smartfox/FSM/FiniteStateMachine.cpp \
		../../libs/smartfox/FSM/FSMState.cpp \
		../../libs/smartfox/Http/SFSWebClient.cpp \
		../../libs/smartfox/Logging/Logger.cpp \
		../../libs/smartfox/Logging/LoggerEvent.cpp \
		../../libs/smartfox/Protocol/Serialization/DefaultObjectDumpFormatter.cpp \
		../../libs/smartfox/Protocol/Serialization/DefaultSFSDataSerializer.cpp \
		../../libs/smartfox/Requests/AdminMessageRequest.cpp \
		../../libs/smartfox/Requests/BanUserRequest.cpp \
		../../libs/smartfox/Requests/BaseRequest.cpp \
		../../libs/smartfox/Requests/Buddylist/AddBuddyRequest.cpp \
		../../libs/smartfox/Requests/Buddylist/BlockBuddyRequest.cpp \
		../../libs/smartfox/Requests/Buddylist/BuddyMessageRequest.cpp \
		../../libs/smartfox/Requests/Buddylist/GoOnlineRequest.cpp \
		../../libs/smartfox/Requests/Buddylist/InitBuddyListRequest.cpp \
		../../libs/smartfox/Requests/Buddylist/RemoveBuddyRequest.cpp \
		../../libs/smartfox/Requests/Buddylist/SetBuddyVariablesRequest.cpp \
		../../libs/smartfox/Requests/ChangeRoomCapacityRequest.cpp \
		../../libs/smartfox/Requests/ChangeRoomNameRequest.cpp \
		../../libs/smartfox/Requests/ChangeRoomPasswordStateRequest.cpp \
		../../libs/smartfox/Requests/CreateRoomRequest.cpp \
		../../libs/smartfox/Requests/ExtensionRequest.cpp \
		../../libs/smartfox/Requests/FindRoomsRequest.cpp \
		../../libs/smartfox/Requests/FindUsersRequest.cpp \
		../../libs/smartfox/Requests/Game/CreateSFSGameRequest.cpp \
		../../libs/smartfox/Requests/Game/InvitationReplyRequest.cpp \
		../../libs/smartfox/Requests/Game/InviteUsersRequest.cpp \
		../../libs/smartfox/Requests/Game/QuickJoinGameRequest.cpp \
		../../libs/smartfox/Requests/Game/SFSGameSettings.cpp \
		../../libs/smartfox/Requests/GenericMessageRequest.cpp \
		../../libs/smartfox/Requests/HandshakeRequest.cpp \
		../../libs/smartfox/Requests/JoinRoomRequest.cpp \
		../../libs/smartfox/Requests/KickUserRequest.cpp \
		../../libs/smartfox/Requests/LeaveRoomRequest.cpp \
		../../libs/smartfox/Requests/LoginRequest.cpp \
		../../libs/smartfox/Requests/LogoutRequest.cpp \
		../../libs/smartfox/Requests/ManualDisconnectionRequest.cpp \
		../../libs/smartfox/Requests/MessageRecipientMode.cpp \
		../../libs/smartfox/Requests/MMO/MapLimits.cpp \
		../../libs/smartfox/Requests/MMO/MMORoomSettings.cpp \
		../../libs/smartfox/Requests/MMO/SetMMOItemVariables.cpp \
		../../libs/smartfox/Requests/MMO/SetUserPositionRequest.cpp \
		../../libs/smartfox/Requests/ModeratorMessageRequest.cpp \
		../../libs/smartfox/Requests/ObjectMessageRequest.cpp \
		../../libs/smartfox/Requests/PingPongRequest.cpp \
		../../libs/smartfox/Requests/PlayerToSpectatorRequest.cpp \
		../../libs/smartfox/Requests/PrivateMessageRequest.cpp \
		../../libs/smartfox/Requests/PublicMessageRequest.cpp \
		../../libs/smartfox/Requests/RoomEvents.cpp \
		../../libs/smartfox/Requests/RoomExtension.cpp \
		../../libs/smartfox/Requests/RoomPermissions.cpp \
		../../libs/smartfox/Requests/RoomSettings.cpp \
		../../libs/smartfox/Requests/SetRoomVariablesRequest.cpp \
		../../libs/smartfox/Requests/SetUserVariablesRequest.cpp \
		../../libs/smartfox/Requests/SpectatorToPlayerRequest.cpp \
		../../libs/smartfox/Requests/SubscribeRoomGroupRequest.cpp \
		../../libs/smartfox/Requests/UnsubscribeRoomGroupRequest.cpp \
		../../libs/smartfox/SmartFox.cpp \
		../../libs/smartfox/Util/ByteArray.cpp \
		../../libs/smartfox/Util/ClientDisconnectionReason.cpp \
		../../libs/smartfox/Util/ConfigData.cpp \
		../../libs/smartfox/Util/ConfigLoader.cpp \
		../../libs/smartfox/Util/EventDispatcher.cpp \
		../../libs/smartfox/Util/LagMonitor.cpp \
		../../libs/smartfox/Util/md5/md5.c \
		../../libs/smartfox/Util/PasswordUtil.cpp \
		../../libs/smartfox/Util/SFSErrorCodes.cpp \
		../../libs/smartfox/Util/XMLParser/XMLNode.cpp \
		../../libs/smartfox/Util/XMLParser/XMLNodeList.cpp \
		../../libs/smartfox/Util/XMLParser/XMLNodeValue.cpp \
		../../libs/smartfox/Util/XMLParser/XMLObject.cpp \
		../../libs/smartfox/Util/XMLParser/XMLParser.cpp \
		../../libs/eziSocial/Objects/EziFacebookFriend.cpp \
		../../libs/eziSocial/Objects/EziFacebookUser.cpp \
		../../libs/eziSocial/Objects/EziFBIncomingRequest.cpp \
		../../libs/eziSocial/Objects/EziFBIncomingRequestManager.cpp \
		../../libs/eziSocial/Objects/EziSocialObject.cpp \
		../../libs/eziSocial/Objects/JNI_EziSocialManager.cpp \

LOCAL_C_INCLUDES := \
		$(LOCAL_PATH)/../../Classes \
		$(LOCAL_PATH)/../../Classes/CustomUI \
		$(LOCAL_PATH)/../../Classes/CustomUI/Labels \
		$(LOCAL_PATH)/../../Classes/CustomUI/Buttons \
		$(LOCAL_PATH)/../../Classes/CustomUI/Tables \
		$(LOCAL_PATH)/../../Classes/GameController \
		$(LOCAL_PATH)/../../Classes/Server \
		$(LOCAL_PATH)/../../Classes/Server/Data \
		$(LOCAL_PATH)/../../Classes/Server/Data/Bonus \
		$(LOCAL_PATH)/../../Classes/Server/Data/GamePlay \
		$(LOCAL_PATH)/../../Classes/Server/Data/UserInfo \
		$(LOCAL_PATH)/../../Classes/UI \
		$(LOCAL_PATH)/../../Classes/UI/Popup/_Common \
		$(LOCAL_PATH)/../../Classes/UI/Popup/Avatar \
		$(LOCAL_PATH)/../../Classes/UI/Popup/DailyBonus \
		$(LOCAL_PATH)/../../Classes/UI/Popup/Jackpot \
		$(LOCAL_PATH)/../../Classes/UI/Popup/LevelUp \
		$(LOCAL_PATH)/../../Classes/UI/Popup/Notification \
		$(LOCAL_PATH)/../../Classes/UI/Popup/Paytable \
		$(LOCAL_PATH)/../../Classes/UI/Popup/Profile \
		$(LOCAL_PATH)/../../Classes/UI/Popup/Setting \
		$(LOCAL_PATH)/../../Classes/UI/Popup/Shop \
		$(LOCAL_PATH)/../../Classes/UI/Popup/VipClub \
		$(LOCAL_PATH)/../../Classes/UI/Popup/VipUpgrade \
		$(LOCAL_PATH)/../../Classes/UI/Popup/Leaderboard \
		$(LOCAL_PATH)/../../Classes/UI/Scenes \
		$(LOCAL_PATH)/../../Classes/UI/Scenes/Loading \
		$(LOCAL_PATH)/../../Classes/UI/Scenes/Lobby \
		$(LOCAL_PATH)/../../Classes/UI/Scenes/Login \
		$(LOCAL_PATH)/../../Classes/UI/Scenes/MainGame \
		$(LOCAL_PATH)/../../Classes/UI/Scenes/MainGame/Controller \
		$(LOCAL_PATH)/../../Classes/UI/Scenes/MainGame/Model \
		$(LOCAL_PATH)/../../Classes/UI/Scenes/MainGame/View \
		$(LOCAL_PATH)/../../Classes/Utils \
		$(LOCAL_PATH)/../../libs/smartfox \
		$(LOCAL_PATH)/../../libs/smartfox/Bitswarm \
		$(LOCAL_PATH)/../../libs/smartfox/Bitswarm/BBox \
		$(LOCAL_PATH)/../../libs/smartfox/Controllers \
		$(LOCAL_PATH)/../../libs/smartfox/Core \
		$(LOCAL_PATH)/../../libs/smartfox/Core/Sockets \
		$(LOCAL_PATH)/../../libs/smartfox/Entities \
		$(LOCAL_PATH)/../../libs/smartfox/Entities/Data \
		$(LOCAL_PATH)/../../libs/smartfox/Entities/Invitation \
		$(LOCAL_PATH)/../../libs/smartfox/Entities/Managers \
		$(LOCAL_PATH)/../../libs/smartfox/Entities/Match \
		$(LOCAL_PATH)/../../libs/smartfox/Entities/Variables \
		$(LOCAL_PATH)/../../libs/smartfox/Exceptions \
		$(LOCAL_PATH)/../../libs/smartfox/FSM \
		$(LOCAL_PATH)/../../libs/smartfox/Http \
		$(LOCAL_PATH)/../../libs/smartfox/Logging \
		$(LOCAL_PATH)/../../libs/smartfox/Protocol \
		$(LOCAL_PATH)/../../libs/smartfox/Protocol/Serialization \
		$(LOCAL_PATH)/../../libs/smartfox/Requests \
		$(LOCAL_PATH)/../../libs/smartfox/Requests/Buddylist \
		$(LOCAL_PATH)/../../libs/smartfox/Requests/Game \
		$(LOCAL_PATH)/../../libs/smartfox/Requests/MMO \
		$(LOCAL_PATH)/../../libs/smartfox/Util \
		$(LOCAL_PATH)/../../libs/smartfox/Util/md5 \
		$(LOCAL_PATH)/../../libs/smartfox/Util/XMLParser \
		$(LOCAL_PATH)/../../libs/eziSocial/Objects \

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
#LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
#LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-add-path, /Volumes/Data/Android/ADT/cocos2d-x-2.2.3)

$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
#$(call import-module,external/Box2D)
#$(call import-module,external/chipmunk)
