//
//  PurchaseHelper.cpp
//  MyTestProject
//
//  Created by Dung Ta Van on 1/20/15.
//
//

#include "PurchaseHelper.h"
#include "PluginManager.h"
#include "cocos2d.h"
#include "Configs.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::plugin;

PurchaseHelper::PurchaseHelper() :
mInapp(NULL),
mListener(NULL) {
    
}

PurchaseHelper* PurchaseHelper::getInstance() {
    static PurchaseHelper sInstance;
    
    return &sInstance;
}

void PurchaseHelper::init() {
    mInapp = new ProtocolIAP();
}

void PurchaseHelper::purgePurchase() {
    PluginManager::end();
}

void PurchaseHelper::loadInappPlugin() {
    if(!mListener) {
        mListener = new PurchaseListener;
    }
    
    mInapp = dynamic_cast<ProtocolIAP*>(PluginManager::getInstance()
                                        ->loadPlugin("IOSIAP"));
    mInapp->setResultListener(mListener);
    mInapp->setDebugMode(true);
}

void PurchaseHelper::unloadInappPlugin() {
    if(mInapp) {
        PluginManager::getInstance()->unloadPlugin("IOSIAP");
        mInapp = NULL;
    }
}

void PurchaseHelper::payByMode(plugin::TProductInfo info, PayMode mode) {
    ProtocolIAP* iap = NULL;
    switch(mode) {
        case eIOS:
            iap = mInapp;
            break;
        default:
            cocos2d::log("PurchaseHelper::Unsupported IAP");
            break;
    }
    if(iap) {
        iap->payForProduct(info);
    }
}

PurchaseHelper::~PurchaseHelper() {
    
    unloadInappPlugin();
    
    CC_SAFE_DELETE(mListener);
}

// Listener
void PurchaseListener::onPayResult(plugin::PayResultCode resultCode,
                                   const char *msg,
                                   plugin::TProductInfo info) {
    char inappInfo[1024] = { 0 };
    sprintf(inappInfo, "ProductID:%s\nPrice:%s\nDesc:%s",
            info.find("IAPId")->second.c_str(),
            info.find("IAPId")->second.c_str(),
            info.find("IAPId")->second.c_str());
    MessageBox(inappInfo , msg);
}

void PurchaseListener::onRequestProductsResult(plugin::IAPProductRequest ret,
                                               plugin::TProductList info) {
    int size = info.size();
    
    cocos2d::log("PurchaseListener::number of products: %d", size);
    for(int i = 0 ; i < size ; i++) {
        string productId = info.at(i)["IAPId"];
        cocos2d::log("PurchaseListener::product[%d]: %s", i, productId.c_str());
    }
}










