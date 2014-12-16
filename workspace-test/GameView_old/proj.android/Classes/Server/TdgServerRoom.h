//
//  TdgServerRoom.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/2/14.
//
//

#ifndef __DragonVideoPoker__TdgServerRoom__
#define __DragonVideoPoker__TdgServerRoom__

#include "SingLeton.h"
#include "cocos2d.h"

#include "SmartFox.h"
#include "BaseEvent.h"

#include "TdgServerDefine.h"
#include "TdgServerExtensionRequest.h"


USING_NS_CC;
using namespace std;
using namespace Sfs2X;

class TdgServerRoom : public SingLeton<TdgServerRoom>, public CCObject
{
public:
    TdgServerRoom();
    
    //smartfox callbacks
	static void OnSmartFoxRoomJoin(unsigned long long ptrContext, BASE_EVENT ptrEvent);
	static void OnSmartFoxRoomJoinError(unsigned long long ptrContext, BASE_EVENT ptrEvent);
	static void OnRoomVariablesUpdate(unsigned long long ptrContext, BASE_EVENT ptrEvent);

    void addRoomEventListeners();
    void addRoomVariablesUpdateListeners();
    void fetchingRoomStaticInfo(boost::shared_ptr<ISFSArray> roomStatics);
    void fetchingRoomDynamicInfo(Room* room);
    void fetchingLevelInfo(boost::shared_ptr<ISFSArray> levelList);

private:
    void addRoomVariablesUpdateListener(string extensionName, ExtensionDataCallback selector);
    
    void roomVariableUpdateGameInfoDynamic(boost::shared_ptr<Room> room, string *roomName);
    void roomVariableUpdateCurrentGameDynamic(boost::shared_ptr<Room> room, string *roomName);

    
    // extension request
    vector<TdgServerExtensionRequest *> mRoomVariableUpdateListeners;
};

#define SERVER_ROOM() TdgServerRoom::getSingleton()

#endif /* defined(__DragonVideoPoker__TdgServerRoom__) */
