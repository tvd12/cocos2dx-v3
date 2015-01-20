//
//  PurchaseHelper.h
//  MyTestProject
//
//  Created by Dung Ta Van on 1/20/15.
//
//

#ifndef __MyTestProject__PurchaseHelper__
#define __MyTestProject__PurchaseHelper__

#include "ProtocolIAP.h"

using namespace cocos2d;

class PurchaseListener : public plugin::PayResultListener {
public:
    virtual void onPayResult(plugin::PayResultCode resultCode,
                             const char* msg,
                             plugin::TProductInfo info);
    virtual void onRequestProductsResult(plugin::IAPProductRequest ret,
                                         plugin::TProductList info);
};

class PurchaseHelper {
public:
    static PurchaseHelper* getInstance();
    static void purgePurchase();
    
    typedef enum {
        eNoneMode = 0,
        eIOS
    } PayMode;
    
    void init();
    void unloadInappPlugin();
    void loadInappPlugin();
    void payByMode(plugin::TProductInfo info, PayMode mode = eIOS);
    
    /**
     * @function: inappCallback
     * @param: resultCode:
     *  typedef enum {
     *      RequestSuccees = 0,
     *      RequestFail,
     *      RequestTimeout,
     *  }  IAPProductRequest;
     *
     * @param: msg: success or fail message (i.e. "parse productInfo fail")
     */
    void inappCallback(int resultCode, const std::string &msg);
    
    CC_SYNTHESIZE(PurchaseListener*, mListener, Listener);
    
    ~PurchaseHelper();
    
protected:
    PurchaseHelper();
    PurchaseHelper(const PurchaseHelper &) = delete;
    void operator = (const PurchaseHelper &) = delete;
    
    plugin::ProtocolIAP* mInapp;
};

#endif /* defined(__MyTestProject__PurchaseHelper__) */
