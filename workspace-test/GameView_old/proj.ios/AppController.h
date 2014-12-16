#import <UIKit/UIKit.h>
#import "Chartboost.h"

#define ALERT_HOURLY_BONUS_BODY         @"Your free Chips are ready! Collect them now?"

@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate, ChartboostDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
}

@end

