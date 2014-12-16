//
//  IAPHelper_objc.h
//  InAppRage
//
//  Created by Ray Wenderlich on 2/28/11.
//  Copyright 2011 Ray Wenderlich. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "StoreKit/StoreKit.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Define IAP
//
////////////////////////////////////////////////////////////////////////////////////////////////////
// Verify secret
#define VERIFY_URL          @"http://twindragonsgames.com/inapp/slots-metro-3749HDMMOidk/validateaction.php"
#define VERIFY_CODE         6686

#define kProductsLoadedNotification         @"ProductsLoaded"
#define kProductPurchasedNotification       @"ProductPurchased"
#define kProductPurchaseFailedNotification  @"ProductPurchaseFailed"
#define kProductPurchasingNotification      @"ProductPurchasing"

@interface IAPHelper_objc : NSObject <SKProductsRequestDelegate, SKPaymentTransactionObserver, SKRequestDelegate> {
    NSSet * _productIdentifiers;    
    NSArray * _products;
    SKProductsRequest * _request;
}

@property (retain) NSSet *productIdentifiers;
@property (retain) NSArray * products;
@property (retain) SKProductsRequest *request;

- (void)requestProducts;

- (id)initWithProductIdentifiers:(NSSet *)productIdentifiers;

- (void)buyProductIdentifier:(NSString *)productIdentifier;

- (NSString *)encode:(const uint8_t *)input length:(NSInteger)length;

- (BOOL)verifyReceiptedTransaction:(SKPaymentTransaction *)transaction;

- (void)informPurchasingToUser:(SKPaymentTransaction *)transaction;

- (void)restorePreviousTransaction;

- (SKProduct *)productForIdentifier:(NSString *)productIdentifier;

@end
