//
//  GameIAPHelper_objc.h
//  XengHoaQua
//
//  Created by Nguyen Tien Thanh on 5/10/12.
//  Copyright 2012 Twin Dragons Games. All rights reserved.
//

#import "IAPHelper_objc.h"

// Credits IAP
#define PRODUCT_IDENTIFIER_CHIP1            @"com.tdgc.dragonvideopoker.chips1"
#define PRODUCT_IDENTIFIER_CHIP2            @"com.tdgc.dragonvideopoker.chips2"
#define PRODUCT_IDENTIFIER_CHIP3            @"com.tdgc.dragonvideopoker.chips3"
#define PRODUCT_IDENTIFIER_CHIP4            @"com.tdgc.dragonvideopoker.chips4"
#define PRODUCT_IDENTIFIER_CHIP5            @"com.tdgc.dragonvideopoker.chips5"
#define PRODUCT_IDENTIFIER_CHIP6            @"com.tdgc.dragonvideopoker.chips6"

#define DEFAULT_PRICE1                      1.99f
#define DEFAULT_PRICE2                      4.99f
#define DEFAULT_PRICE3                      9.99f
#define DEFAULT_PRICE4                      24.99f
#define DEFAULT_PRICE5                      49.99f
#define DEFAULT_PRICE6                      99.99f

#define DEFAULT_AMOUNT_CHIP1                0
#define DEFAULT_AMOUNT_CHIP2                0
#define DEFAULT_AMOUNT_CHIP3                0
#define DEFAULT_AMOUNT_CHIP4                0
#define DEFAULT_AMOUNT_CHIP5                0
#define DEFAULT_AMOUNT_CHIP6                0

// Purchased fail
#define MSG_PURCHASE_FAILED_TITLE           @"Error"
#define MSG_PURCHASE_FAILED_MESSAGE         @"Transaction failed!"


@interface GameIAPHelper_objc :  NSObject {
    NSNumberFormatter *priceFormatter;
    IAPHelper_objc *iapHelper;
}

@property (retain) NSNumberFormatter *priceFormatter;
@property (retain) IAPHelper_objc *iapHelper;

@property (nonatomic, assign) float chip6Price;
@property (nonatomic, assign) float chip5Price;
@property (nonatomic, assign) float chip4Price;
@property (nonatomic, assign) float chip3Price;
@property (nonatomic, assign) float chip2Price;
@property (nonatomic, assign) float chip1Price;

+ (GameIAPHelper_objc *)sharedHelper;

- (void)displayPurchaseFailedMessage;
- (void)resetFormatterCurrencyIfNeed;
- (void)requestProducts;
- (void)purchaseItem:(int)item;

@end
