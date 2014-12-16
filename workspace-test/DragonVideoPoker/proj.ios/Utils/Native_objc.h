//
//  Native_objc.h
//  Dragon Poker
//
//  Created by Nguyen Tien Thanh on 10/17/13.
//
//

#import <Foundation/Foundation.h>
#import <AudioToolbox/AudioServices.h>

#define PRODUCT_ID_2    @"883096461"

#define EMAIL_ADDRESS   @"contact@twindragonsgames.com"
#define EMAIL_BODY      @"\n\nWebsite: http://twindragonsgames.com \nFacebook: http://www.facebook.com/twindragonsgames"

//#define RATE_URL        @"itms-apps://ax.itunes.apple.com/WebObjects/MZStore.woa/wa/viewContentsUserReviews?type=Purple+Software&id=%@"
#define RATE_URL        @"itms-apps://itunes.apple.com/app/id%@"

@interface Native_objc : NSObject

@property (retain) Native_objc *nativeObject;

+ (Native_objc *)sharedObject;

- (void)vibrate;
- (void)rateUsOnStore;
- (void)sendFeedback : (const char *)emailSubject andUserId:(const char *)userId;
- (void)openUrl : (const char *)url;

@end
