//
//  TdgServerDelegate.h
//  DragonVideoPoker
//
//  Created by Nguyen Tien Thanh on 4/8/14.
//
//

#ifndef DragonVideoPoker_TdgServerDelegate_h
#define DragonVideoPoker_TdgServerDelegate_h

class TdgServerDelegate
{
public:
    TdgServerDelegate() {}
    virtual ~TdgServerDelegate() {}
    
    // server notify cards to game controller
    virtual void onDealCardsReceived() {}
    virtual void onDrawCardsReceived() {}
    
    virtual void onFirstDonCardReceived() {}
    virtual void onOtherDonCardsReceived() {}
    
    // server notify room variables update to game controller
    virtual void onJackpotUpdate() {}
    virtual void onNumberOnlinePlayersUpdate() {}
};


#endif
