//
//  IAPHelper_objc.m
//  InAppRage
//
//  Created by Ray Wenderlich on 2/28/11.
//  Copyright 2011 Ray Wenderlich. All rights reserved.
//

#import "IAPHelper_objc.h"
//#include "PokerServer.h"
#include "TdgServer.h"


@implementation IAPHelper_objc
@synthesize productIdentifiers = _productIdentifiers;
@synthesize products = _products;
@synthesize request = _request;


- (id)initWithProductIdentifiers:(NSSet *)productIdentifiers {
    if ((self = [super init])) {
        
        // Store product identifiers
        _productIdentifiers = [productIdentifiers retain];
        
        [[SKPaymentQueue defaultQueue] addTransactionObserver: self];
    }
    return self;
}

- (void)requestProducts
{    
    self.request = [[[SKProductsRequest alloc] initWithProductIdentifiers:_productIdentifiers] autorelease];
    _request.delegate = self;
    [_request start];
}

#pragma mark - IAP Delegate

- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response 
{
    NSLog(@"Received products results...");   
    self.products = response.products;
//    self.request = nil;    
    
    [[NSNotificationCenter defaultCenter] postNotificationName:kProductsLoadedNotification
                                                        object:_products];    
}

- (void)recordTransaction:(SKPaymentTransaction *)transaction 
{    
    // TODO: Record the transaction on the server side...    
}

- (void)provideContent:(SKPaymentTransaction *)transaction 
{        
    NSDictionary *userInfo = [NSDictionary dictionaryWithObject:transaction forKey:@"pass"];

    [[NSNotificationCenter defaultCenter] postNotificationName:kProductPurchasedNotification 
                                                        object:self
                                                      userInfo:userInfo];
}

- (void)completeTransaction:(SKPaymentTransaction *)transaction
{    
    NSLog(@"completeTransaction: %@", transaction.payment.productIdentifier);
    
    // Verify transaction from Google App Engine Sever Side
    [self verifyReceiptedTransaction:transaction];
//    if ([self verifyReceiptedTransaction:transaction]) {
//        [self recordTransaction:transaction];
//        [self provideContent:transaction];
//    }
//    else {
//        [[NSNotificationCenter defaultCenter] postNotificationName:kProductPurchaseFailedNotification 
//                                                            object:transaction];
//    }
    
    [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
}

- (void)restorePreviousTransaction
{
    [[SKPaymentQueue defaultQueue] restoreCompletedTransactions];
}

- (void)restoreTransaction:(SKPaymentTransaction *)transaction {
    
    NSLog(@"restoreTransaction... %@", transaction.payment.productIdentifier);
    
    // Verify transaction from Google App Engine Sever Side    
    if ([self verifyReceiptedTransaction:transaction]) {
        [self recordTransaction: transaction];
        [self provideContent: transaction];
    }
    else {
        [[NSNotificationCenter defaultCenter] postNotificationName:kProductPurchaseFailedNotification
                                                            object:transaction];
    }
    
    [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
}

- (void)failedTransaction:(SKPaymentTransaction *)transaction {
    
    if (transaction.error.code != SKErrorPaymentCancelled)
    {
        NSLog(@"Transaction error: %@", transaction.error.localizedDescription);
    }
    
    [[NSNotificationCenter defaultCenter] postNotificationName:kProductPurchaseFailedNotification
                                                        object:transaction];
    
    [[SKPaymentQueue defaultQueue] finishTransaction: transaction];
    
}

- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions
{
    for (SKPaymentTransaction *transaction in transactions)
    {
        switch (transaction.transactionState)
        {
            case SKPaymentTransactionStatePurchased:
                [self completeTransaction:transaction];
                break;
                
            case SKPaymentTransactionStateFailed:
                [self failedTransaction:transaction];
                break;
                
            case SKPaymentTransactionStateRestored:
                [self restoreTransaction:transaction];
                break;
                
            case SKPaymentTransactionStatePurchasing:
                [self informPurchasingToUser:transaction];
                break;
                
            default:
                break;
        }
    }
}

- (void)informPurchasingToUser:(SKPaymentTransaction *)transaction
{
    [[NSNotificationCenter defaultCenter] postNotificationName:kProductPurchasingNotification
                                                        object:transaction];
}

#pragma mark - IAP features

- (void)buyProductIdentifier:(NSString *)productIdentifier
{
    if ([SKPaymentQueue canMakePayments]) {
        NSLog(@"Buying %@...", productIdentifier);
        
        SKProduct *product = [self productForIdentifier:productIdentifier];
        if (product != nil) {
            SKPayment *payment = [SKPayment paymentWithProduct:product];
            [[SKPaymentQueue defaultQueue] addPayment:payment];
        }
    }
}

- (BOOL)verifyReceiptedTransaction:(SKPaymentTransaction *)transaction
{
    // Display waiting screen
    NSString *jsonObjectString = [self encode:(uint8_t *)transaction.transactionReceipt.bytes
                                       length:transaction.transactionReceipt.length];      
    std::string *verifyData = new string([jsonObjectString UTF8String]);
    SERVER().sendVerifyIapData(verifyData);
    NSLog(@"jsonObjectString = %@", jsonObjectString);

    delete verifyData;
    
    // Who know?
    return YES;
}

- (NSString *)encode:(const uint8_t *)input length:(NSInteger)length
{
    static char table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
    
    NSMutableData *data = [NSMutableData dataWithLength:((length + 2) / 3) * 4];
    uint8_t *output = (uint8_t *)data.mutableBytes;
    
    for (NSInteger i = 0; i < length; i += 3) {
        NSInteger value = 0;
        for (NSInteger j = i; j < (i + 3); j++) {
            value <<= 8;
            
            if (j < length) {
                value |= (0xFF & input[j]);
            }
        }
        
        NSInteger index = (i / 3) * 4;
        output[index + 0] =                    table[(value >> 18) & 0x3F];
        output[index + 1] =                    table[(value >> 12) & 0x3F];
        output[index + 2] = (i + 1) < length ? table[(value >> 6)  & 0x3F] : '=';
        output[index + 3] = (i + 2) < length ? table[(value >> 0)  & 0x3F] : '=';
    }
    
    return [[[NSString alloc] initWithData:data encoding:NSASCIIStringEncoding] autorelease];
}

- (SKProduct *)productForIdentifier:(NSString *)productIdentifier
{
    SKProduct *myProduct = nil;
    
    for(int i = 0; i < [_products count]; i++) {
        SKProduct *product = [_products objectAtIndex:i];
        if ([[product productIdentifier] isEqualToString:productIdentifier]) {
            myProduct = product;
            break;
        }
    }
    
    return myProduct;
}

- (void)dealloc
{
    [_productIdentifiers release];
    _productIdentifiers = nil;
    [_products release];
    _products = nil;
    [_request release];
    _request = nil;
    [super dealloc];
}

@end
