//
//  GAHelper_objc.h
//  VideoPoker
//
//  Created by Nguyen Tien Thanh on 5/27/13.
//
//

#import <Foundation/Foundation.h>
#import "GAI.h"
#import "StoreKit/StoreKit.h"

#define GOOGLE_ANALYTICS_ID                     @"UA-36352887-7"


@interface GAHelper_objc : NSObject {
    id<GAITracker> tracker;

}

+ (GAHelper_objc *) sharedHelper;

- (void) sendGameEvent : (const char*)eventName
             withValue : (long long)eventValue
           withCatagory: (const char*)catagoryName ;
- (void) sendScreenView : (const char*)screenName;

@end
