//
//  GameIAPHelper_objc.m
//  XengHoaQua
//
//  Created by Nguyen Tien Thanh on 5/10/12.
//  Copyright 2012 Twin Dragons Games. All rights reserved.
//

#import "GameIAPHelper_objc.h"
#import "GameIAPHelper.h"

#include "TdgServer.h"
#include "IapProduct.h"
#include "TdgServerDefine.h"
#include "cocos2d.h"


#import "StoreKit/StoreKit.h"

@implementation GameIAPHelper_objc

@synthesize chip6Price;
@synthesize chip5Price;
@synthesize chip4Price;
@synthesize chip3Price;
@synthesize chip2Price;
@synthesize chip1Price;

@synthesize priceFormatter, iapHelper;


static GameIAPHelper_objc * _sharedHelper;

+ (GameIAPHelper_objc *) sharedHelper {
    
    if (_sharedHelper != nil) {
        return _sharedHelper;
    }
    
    _sharedHelper = [[GameIAPHelper_objc alloc] init];
    return _sharedHelper;
}

- (id)init
{
    if ((self = [super init])) {
        // Add IAP Observer
        [self addIAPObserver];

        NSSet *productIdentifiers = [NSSet setWithObjects:
                                     PRODUCT_IDENTIFIER_CHIP6,
                                     PRODUCT_IDENTIFIER_CHIP5,
                                     PRODUCT_IDENTIFIER_CHIP4,
                                     PRODUCT_IDENTIFIER_CHIP3,
                                     PRODUCT_IDENTIFIER_CHIP2,
                                     PRODUCT_IDENTIFIER_CHIP1,
                                     nil];
        
        // Init IAP Helper
        iapHelper = [[IAPHelper_objc alloc] initWithProductIdentifiers:productIdentifiers];
    }

    return self;
}

- (void)requestProducts
{
    [iapHelper requestProducts];
}

- (void)displayPurchaseFailedMessage
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:MSG_PURCHASE_FAILED_TITLE
                                                    message:MSG_PURCHASE_FAILED_MESSAGE
                                                   delegate:nil
                                          cancelButtonTitle:@"OK"
                                          otherButtonTitles:nil, nil];
    
    [alert show];
    [alert release];
}

- (void)resetFormatterCurrencyIfNeed
{
    if (priceFormatter == nil) {
        priceFormatter = [[NSNumberFormatter alloc] init];
        [priceFormatter setNumberStyle:NSNumberFormatterCurrencyStyle];
        [priceFormatter setLocale:[[NSLocale alloc] initWithLocaleIdentifier:@"en_US"]];
    }
}

#pragma mark - IAP Observer

- (void)addIAPObserver
{
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(productsLoaded:)
                                                 name:kProductsLoadedNotification
                                               object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(productPurchased:)
                                                 name:kProductPurchasedNotification
                                               object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(productPurchaseFailed:)
                                                 name:kProductPurchaseFailedNotification
                                               object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(productPurchasing:)
                                                 name:kProductPurchasingNotification
                                               object:nil];
}

- (void)removeIAPObserver
{
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:kProductPurchasedNotification
                                                  object:nil];
    
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:kProductPurchaseFailedNotification
                                                  object:nil];
    
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:kProductPurchasingNotification
                                                  object:nil];
    
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:kProductsLoadedNotification
                                                  object:nil];
}

- (void)productsLoaded:(NSNotification *)notification
{
    NSArray *myProduct = iapHelper.products;
    for(int i = 0; i < [myProduct count]; i++) {
        SKProduct *product = [myProduct objectAtIndex:i];
        NSLog(@"Name: %@ - Price: %f",[product localizedTitle],[[product price] doubleValue]);
        NSLog(@"Product identifier: %@", [product productIdentifier]);
        
        // Update currency format
        if (priceFormatter == nil) {
            priceFormatter = [[NSNumberFormatter alloc] init];
            [priceFormatter setNumberStyle:NSNumberFormatterCurrencyStyle];
            [priceFormatter setLocale:product.priceLocale];
        }
        
        NSString *formattedPrice = [priceFormatter stringFromNumber:product.price];
        NSLog(@"Money symbol: %@", formattedPrice);

        // update price of product
        float price = [[product price] floatValue];
        int type;
        
        // update chip price
        if ([[product productIdentifier] isEqualToString:PRODUCT_IDENTIFIER_CHIP1]) {
            type = kIAPChip1;
            chip1Price = price;
        }
        else if ([[product productIdentifier] isEqualToString:PRODUCT_IDENTIFIER_CHIP2]) {
            type = kIAPChip2;
            chip2Price = price;
        }
        else if ([[product productIdentifier] isEqualToString:PRODUCT_IDENTIFIER_CHIP3]) {
            type = kIAPChip3;
            chip3Price = price;
        }
        else if ([[product productIdentifier] isEqualToString:PRODUCT_IDENTIFIER_CHIP4]) {
            type = kIAPChip4;
            chip4Price = price;
        }
        else if ([[product productIdentifier] isEqualToString:PRODUCT_IDENTIFIER_CHIP5]) {
            type = kIAPChip5;
            chip5Price = price;
        }
        else if ([[product productIdentifier] isEqualToString:PRODUCT_IDENTIFIER_CHIP6]) {
            type = kIAPChip6;
            chip6Price = price;
        }
        
        // update text price
        IapProduct* iapProduct;
        iapProduct = IAPLIST()->at(type);
        
        iapProduct->setPrice(new std::string([formattedPrice UTF8String]));
    }

    // we got price from server
    GameIAPHelper::sharedHelper()->isGotPriceFromServer = true;
}

- (void)productPurchased:(NSNotification *)notification
{
    SKPaymentTransaction *transaction = (SKPaymentTransaction *)[[notification userInfo] valueForKey:@"pass"];
    
    NSString *productIdentifier = transaction.payment.productIdentifier;
    NSLog(@"productPurchased: %@", productIdentifier);
    
    // Purchase Chips
    if ([productIdentifier isEqualToString:PRODUCT_IDENTIFIER_CHIP1] ||
        [productIdentifier isEqualToString:PRODUCT_IDENTIFIER_CHIP2] ||
        [productIdentifier isEqualToString:PRODUCT_IDENTIFIER_CHIP3] ||
        [productIdentifier isEqualToString:PRODUCT_IDENTIFIER_CHIP4] ||
        [productIdentifier isEqualToString:PRODUCT_IDENTIFIER_CHIP5] ||
        [productIdentifier isEqualToString:PRODUCT_IDENTIFIER_CHIP6]) {
        [self purchasedChips:[transaction retain]];
    }
}

- (void)productPurchasing:(NSNotification *)notification
{
    // Do nothing
}

- (void)productPurchaseFailed:(NSNotification *)notification
{
    // Inform message to user
    [self displayPurchaseFailedMessage];
    
//    INAPP().setJustFinishPurchasing(true);
    GameIAPHelper::sharedHelper()->finishPurchasing();
}

- (void)purchasedChips:(SKPaymentTransaction *)transaction
{
    NSString *productIdentifier = transaction.payment.productIdentifier;

    if ([productIdentifier isEqualToString:PRODUCT_IDENTIFIER_CHIP1]) {
        GameIAPHelper::sharedHelper()->purchasedChips(kIAPChip1);
    }
    else if ([productIdentifier isEqualToString:PRODUCT_IDENTIFIER_CHIP2]) {
        GameIAPHelper::sharedHelper()->purchasedChips(kIAPChip2);
    }
    else if ([productIdentifier isEqualToString:PRODUCT_IDENTIFIER_CHIP3]) {
        GameIAPHelper::sharedHelper()->purchasedChips(kIAPChip3);
    }
    else if ([productIdentifier isEqualToString:PRODUCT_IDENTIFIER_CHIP4]) {
        GameIAPHelper::sharedHelper()->purchasedChips(kIAPChip4);
    }
    else if ([productIdentifier isEqualToString:PRODUCT_IDENTIFIER_CHIP5]) {
        GameIAPHelper::sharedHelper()->purchasedChips(kIAPChip5);
    }
    else if ([productIdentifier isEqualToString:PRODUCT_IDENTIFIER_CHIP6]) {
        GameIAPHelper::sharedHelper()->purchasedChips(kIAPChip6);
    }
}

- (void)purchaseItem:(int)item
{
    switch (item) {
        case kIAPChip1:
            [iapHelper buyProductIdentifier:PRODUCT_IDENTIFIER_CHIP1];
            break;
            
        case kIAPChip2:
            [iapHelper buyProductIdentifier:PRODUCT_IDENTIFIER_CHIP2];
            break;
            
        case kIAPChip3:
            [iapHelper buyProductIdentifier:PRODUCT_IDENTIFIER_CHIP3];
            break;
            
        case kIAPChip4:
            [iapHelper buyProductIdentifier:PRODUCT_IDENTIFIER_CHIP4];
            break;
            
        case kIAPChip5:
            [iapHelper buyProductIdentifier:PRODUCT_IDENTIFIER_CHIP5];
            break;
            
        case kIAPChip6:
            [iapHelper buyProductIdentifier:PRODUCT_IDENTIFIER_CHIP6];
            break;
            
        default:
            break;
    }
}

@end
