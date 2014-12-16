//
//  GameIAPHelper.h
//  VideoPoker
//
//  Created by Nguyen Tien Thanh on 1/18/13.
//
//

#ifndef __VideoPoker__GameIAPHelper__
#define __VideoPoker__GameIAPHelper__

#ifndef CC_TARGET_OS_IPHONE
#include <jni.h>
#include "jni/JniHelper.h"
#endif

class  GameIAPHelper {
    
public:
    static GameIAPHelper* sharedHelper(void);
    void purchasedChips(int type);
    void purchasedGold(int type);
    
    const char* getItemPriceString(int itemType);
    void purchaseItem(int itemType);
    
    bool isGotPriceFromServer;
    
    void finishPurchasing();
    
};

#ifndef CC_TARGET_OS_IPHONE
#ifdef __cplusplus
extern "C" {
#endif
    
    JNIEXPORT void JNICALL Java_com_tdgc_videopokerjackpot_utils_TDGInAppHelper_nativeCancelPurchase
    (JNIEnv * env, jobject obj);
    
    JNIEXPORT void JNICALL Java_com_tdgc_videopokerjackpot_utils_TDGInAppHelper_nativeVerifyInApp
    (JNIEnv * env, jobject obj, jstring packageGame, jstring productId, jstring purchaseToken);

#ifdef __cplusplus
}
#endif
#endif

#endif /* defined(__VideoPoker__GameIAPHelper__) */
