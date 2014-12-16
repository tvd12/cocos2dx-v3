//
//  GAHelper_objc.m
//  VideoPoker
//
//  Created by Nguyen Tien Thanh on 5/27/13.
//
//

#import "GAHelper_objc.h"
#import "GameParams.h"
#import "GameIAPHelper_objc.h"
#import "IAPHelper_objc.h"

#include "NativeHelper.h"


@implementation GAHelper_objc

+(GAHelper_objc *) sharedHelper
{
    static GAHelper_objc *sharedHelper;
    
    @synchronized(self)
    {
        if (!sharedHelper) {
            sharedHelper = [[GAHelper_objc alloc] init];
        }
    }
    
    return sharedHelper;
}

- (id) init
{
    self = [super init];
    
    if (self) {
        // Init params
        [GAI sharedInstance].trackUncaughtExceptions = YES;
        
        // Optional: set Google Analytics dispatch interval to e.g. 20 seconds.
        [GAI sharedInstance].dispatchInterval = 30;
        
        // Optional: set debug to YES for extra debugging information.
        [GAI sharedInstance].debug = YES;
        
        // Create tracker instance.
        tracker = [[GAI sharedInstance] trackerWithTrackingId:GOOGLE_ANALYTICS_ID];
        
        // Track user online
        [self onSignIn];
    }
    
    return self;
}

// Called after a user successfully signs in to your app.
- (void) onSignIn
{
    // The rest of your onSignIn code.
    [tracker setAppScreen:@"Login Scene"];
    tracker.sessionStart = YES;
    [tracker sendEventWithCategory:@"Main Category"
                        withAction:@"Start a new game"
                         withLabel:@"iOs Version"
                         withValue:nil]; // First activity of new session.
}

- (void) sendGameEvent : (const char*)eventName withValue : (long long)eventValue withCatagory:(const char*)catagoryName
{
    [tracker sendEventWithCategory:[NSString stringWithUTF8String:catagoryName]
                        withAction:@"Button Pressed"
                         withLabel:[NSString stringWithUTF8String:eventName]
                         withValue:[NSNumber numberWithLongLong:eventValue]];
}

- (void) sendScreenView : (const char*)screenName
{
    NSString *screenNameStr;
    screenNameStr = [NSString stringWithUTF8String:screenName];

    [tracker sendView:screenNameStr];
}

@end
