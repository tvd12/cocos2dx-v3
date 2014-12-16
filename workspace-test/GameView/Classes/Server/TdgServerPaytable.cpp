//
//  TdgServerPaytable.cpp
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 5/8/14.
//
//

#include "TdgServerPaytable.h"
#include "TdgServer.h"
#include "ExtensionRequest.h"
#include "RoomInfo.h"
#include "PaytableCell.h"
#include "VideoPokerDefine.h"

#include <boost/algorithm/string.hpp>


TdgServerPaytable::TdgServerPaytable()
{
    
}

void TdgServerPaytable::sendPaytableRequest()
{
    boost::shared_ptr<SmartFox> smartFox = SERVER().getSmartFox();
    boost::shared_ptr<ISFSObject> parameters (new SFSObject());
	boost::shared_ptr<IRequest> request (new ExtensionRequest(EX_REQUEST_COMMAND_PAYTABLE,
                                                              parameters));
	smartFox->Send(request);
}

void TdgServerPaytable::processPaytableData(boost::shared_ptr<ISFSObject> userInfoData)
{
    ISFSArray* paytableArray = userInfoData->GetSFSArray(EX_REQUEST_PARAM_PAYTABLE_ARRAY).get();
    if (paytableArray) {
        for (int i = 0; i < paytableArray->Size(); i++) {
            ISFSObject* paytable = paytableArray->GetSFSObject(i).get();
            fetchingPaytableInfo(paytable);
        }
        for (int i = paytableArray->Size(); i < 11; i++) {
            PaytableCell* paytableCell = PaytableCell::create(PAYTABLE_EMPTY, "", -1);
            paytableCell->retain();
            PAYTABLE()->push_back(paytableCell);
        }
    }
    
    // finish joining game room
    SERVER().setJoiningStatus(kJoinedGameRoom);
}

void TdgServerPaytable::fetchingPaytableInfo(ISFSObject* paytable)
{
    long* paytableId = paytable->GetInt(EX_REQUEST_PARAM_PAYTABLE_HAND_ID).get();
    long* paytableMultiply = paytable->GetInt(EX_REQUEST_PARAM_PAYTABLE_HAND_MULTIPLY).get();
    string* paytableName = paytable->GetUtfString(EX_REQUEST_PARAM_PAYTABLE_HAND_NAME).get();
    
    if (paytableId != NULL && paytableMultiply != NULL && paytableName != NULL) {
//        CCLOG("Paytable id: %ld - Name: %s - Multiple: %ld",
//              *paytableId,
//              paytableName->c_str(),
//              *paytableMultiply);
        PaytableCell* paytableCell;
        paytableCell = PaytableCell::create(*paytableId,
                                            *paytableName,
                                            *paytableMultiply);
        paytableCell->retain();
        PAYTABLE()->push_back(paytableCell);
        
        // update jackpot to current room if could
        if (*paytableId == ROOMINFO()->getJackpotHand()) {
            string* jackpotName = new string(*paytableName);
            boost::algorithm::to_upper(*jackpotName);
            ROOMINFO()->setJackpotName(jackpotName);
        }
    }
}
