#import "AppController.h"
#import "EAGLView.h"
#import "cocos2d.h"
#import "RootViewController.h"

#import "EziSocialManager.h"

#import "AppDelegate.h"
#include "TdgServer.h"
#include "HourlyBonusInfo.h"
#include "GameParams.h"

#import "GameIAPHelper.h"
#import "Appirater.h"
#import "GAHelper_objc.h"

#import <FacebookSDK/FacebookSDK.h>


@implementation AppController

#pragma mark -
#pragma mark Application lifecycle

// cocos2d application instance
static AppDelegate s_sharedApplication;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    // Init IAP
    GameIAPHelper::sharedHelper();

    // init google analytics
    [GAHelper_objc sharedHelper];

    // Appirater
    [Appirater setAppId:[NSString stringWithUTF8String:PRODUCT_ID]];
//    [Appirater setDebug:YES];

    // Override point for customization after application launch.

    // Add the view controller's view to the window and display.
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    
    // Init the EAGLView
    EAGLView *__glView = [EAGLView viewWithFrame: [window bounds]
                                     pixelFormat: kEAGLColorFormatRGB565
                                     depthFormat: GL_DEPTH24_STENCIL8_OES
                              preserveBackbuffer: NO
                                      sharegroup: nil
                                   multiSampling: NO
                                 numberOfSamples: 0];

    // Use RootViewController manage EAGLView 
    viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    viewController.wantsFullScreenLayout = YES;
    viewController.view = __glView;
    
    [__glView setMultipleTouchEnabled:YES]; // Multitouch

    // Set RootViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        [window addSubview: viewController.view];
    }
    else
    {
        // use this method on ios6
        [window setRootViewController:viewController];
    }
    
    [window makeKeyAndVisible];
    
    [[UIApplication sharedApplication] setStatusBarHidden:true];
    
    // Let the device know we want to receive push notifications
	[[UIApplication sharedApplication] registerForRemoteNotificationTypes:
     (UIRemoteNotificationTypeBadge |
      UIRemoteNotificationTypeSound |
      UIRemoteNotificationTypeAlert)];

    [self addChartBoost];

    cocos2d::CCApplication::sharedApplication()->run();

    // Launch apprirater
    [Appirater appLaunched:YES];

    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application {
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
    cocos2d::CCDirector::sharedDirector()->pause();
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */

    cocos2d::CCDirector::sharedDirector()->resume();
    
    // log facebook install ads
    NSDictionary* infoDict = [[NSBundle mainBundle] infoDictionary];
    NSString* facebookAppId = [infoDict objectForKey:@"FacebookAppID"];

    [FBSettings setDefaultAppID:facebookAppId];
    [FBAppEvents activateApp];
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
     */
    cocos2d::CCApplication::sharedApplication()->applicationDidEnterBackground();
    
    // Create collect bonus remider with local notification
    [self createHourlyBonusLocalNotification];
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    /*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
    [Appirater appEnteredForeground:YES];

    cocos2d::CCApplication::sharedApplication()->applicationWillEnterForeground();
}

- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
}


#pragma mark - Get game info

- (BOOL)application: (UIApplication*) application openURL:(NSURL *)url
  sourceApplication:(NSString *)sourceApplication annotation:(id)annotation
{
    // This is very important to add otherwise login to Facebook will not work and will result in failure everytime.
    if ([sourceApplication isEqualToString:@"com.apple.mobilesafari"] ||
        [sourceApplication isEqualToString:@"com.facebook.Facebook"]) {
        return [[EziSocialManager sharedManager] handleURL:url];
    }
    else {
        return NO;
    }
}

- (void)application:(UIApplication*)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData*)deviceToken
{
    NSString *token = [[deviceToken description] stringByTrimmingCharactersInSet:[NSCharacterSet characterSetWithCharactersInString:@"<>"]];
    token = [token stringByReplacingOccurrencesOfString:@" " withString:@""];
    
	NSLog(@"My token is: %@", token);
    SERVER().setDeviceToken(new string([token UTF8String]));
}

- (void)application:(UIApplication*)application didFailToRegisterForRemoteNotificationsWithError:(NSError*)error
{
    SERVER().setDeviceToken(new string("simulator_device"));
	NSLog(@"Failed to get token, error: %@", error);
}

#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
}


- (void)dealloc {
    [window release];
    [super dealloc];
}


#pragma mark - Create local notification

- (void)createHourlyBonusLocalNotification
{
    NSArray *arrayOfLocalNotifications = [[UIApplication sharedApplication] scheduledLocalNotifications] ;
    for (UILocalNotification *localNotification in arrayOfLocalNotifications) {
        if ([localNotification.alertBody isEqualToString:ALERT_HOURLY_BONUS_BODY]) {
            NSLog(@"the notification this is canceld is: %@", localNotification.alertBody);
            NSLog(@"the notification date is: %@", localNotification.fireDate);
            
            [[UIApplication sharedApplication] cancelLocalNotification:localNotification] ; // delete the notification from the system
        }
    }
    
    long long timeToBonus = (HOURLYBONUS()->getBonusMax() - HOURLYBONUS()->getCurrentBonus());
    timeToBonus = (long long)((float)timeToBonus / HOURLYBONUS()->getChipsPerSecond());
    
    NSDate *fireDate = [NSDate date];
    NSDate *fireDate2 = [NSDate dateWithTimeIntervalSinceNow:timeToBonus];
    [fireDate dateByAddingTimeInterval:timeToBonus];
    
    NSLog(@"%@", [fireDate description]);
    NSLog(@"%@", [fireDate2 description]);
    
    // Create local Notification
    UILocalNotification *bonusNotification = [[UILocalNotification alloc] init];
    bonusNotification.fireDate = fireDate2;
    bonusNotification.timeZone = [NSTimeZone localTimeZone];
    bonusNotification.repeatInterval= 0;        // don't repeat
    bonusNotification.alertBody = ALERT_HOURLY_BONUS_BODY;
    
    // Set the action button
    bonusNotification.alertAction = @"View";
    bonusNotification.soundName = UILocalNotificationDefaultSoundName;
    
    // Schedule the notification
    [[UIApplication sharedApplication] scheduleLocalNotification:bonusNotification];
}

#pragma mark - Add Chartboost

- (void)addChartBoost
{
    Chartboost *cb = [Chartboost sharedChartboost];

    // Notify the beginning of a user session
    [Chartboost startWithAppId:CHARTBOOST_APP_ID
                  appSignature:CHARTBOOST_APP_SIGNATURE
                      delegate:self];
    
    // Cache an interstitial at the default location
    [cb cacheInterstitial:CHARTBOOST_GOT_HOURLY_BONUS];
}

/*
 * Chartboost Delegate Methods
 *
 * Recommended for everyone: shouldDisplayInterstitial
 */


/*
 * shouldDisplayInterstitial
 *
 * This is used to control when an interstitial should or should not be displayed
 * The default is YES, and that will let an interstitial display as normal
 * If it's not okay to display an interstitial, return NO
 *
 * For example: during gameplay, return NO.
 *
 * Is fired on:
 * -Interstitial is loaded & ready to display
 */

- (BOOL)shouldDisplayInterstitial:(CBLocation)location {
    NSLog(@"about to display interstitial at location %@", location);
    
    // For example:
    // if the user has left the main menu and is currently playing your game, return NO;
    
    // Otherwise return YES to display the interstitial
    return YES;
}

- (void)didDisplayInterstitial:(CBLocation)location{
    NSLog(@"did Display Interstitial at location %@", location);
}


/*
 * didFailToLoadInterstitial
 *
 * This is called when an interstitial has failed to load for any reason
 *
 * Is fired on:
 * - No network connection
 * - No publishing campaign matches for that user (go make a new one in the dashboard)
 */

- (void)didFailToLoadInterstitial:(CBLocation)location
{
    NSLog(@"failure to load interstitial at location %@", location);
    
    // Show a house ad or do something else when a chartboost interstitial fails to load
}

/*
 * didCacheInterstitial
 *
 * Passes in the location name that has successfully been cached.
 *
 * Is fired on:
 * - All assets loaded
 * - Triggered by cacheInterstitial
 *
 * Notes:
 * - Similar to this is: cb.hasCachedInterstitial(String location)
 * Which will return true if a cached interstitial exists for that location
 */

- (void)didCacheInterstitial:(CBLocation)location
{
    NSLog(@"interstitial cached at location %@", location);
    
    //    if ([location isEqualToString:CHARTBOOST_AD_MAIN_1]) {
    //        [[Chartboost sharedChartboost] showInterstitial:location];
    //    }
    //    else if ([location isEqualToString:CHARTBOOST_AD_MAIN_2]) {
    //        [[Chartboost sharedChartboost] showInterstitial:location];
    //    }
}

/*
 * didFailToLoadMoreApps
 *
 * This is called when the more apps page has failed to load for any reason
 *
 * Is fired on:
 * - No network connection
 * - No more apps page has been created (add a more apps page in the dashboard)
 * - No publishing campaign matches for that user (add more campaigns to your more apps page)
 *  -Find this inside the App > Edit page in the Chartboost dashboard
 */

- (void)didFailToLoadMoreApps
{
    NSLog(@"failure to load more apps");
}

- (void)didDismissInterstitial:(CBLocation)location
{
    NSLog(@"dismissed interstitial at location %@", location);
    [[Chartboost sharedChartboost] cacheInterstitial:location];
}

- (void)didClickInterstitial:(CBLocation)location
{
    NSLog(@"did Click Interstitial at location %@", location);
    [[Chartboost sharedChartboost] cacheInterstitial:location];
}

@end
