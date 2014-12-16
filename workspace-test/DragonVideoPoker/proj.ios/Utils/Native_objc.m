//
//  Native_objc.m
//  Dragon Poker
//
//  Created by Nguyen Tien Thanh on 10/17/13.
//
//

#import "Native_objc.h"


@implementation Native_objc

@synthesize nativeObject;

static Native_objc * _sharedObject;

+ (Native_objc *)sharedObject
{
    
    if (_sharedObject != nil) {
        return _sharedObject;
    }
    
    _sharedObject = [[Native_objc alloc] init];
    return _sharedObject;
}

- (void)vibrate
{
	AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);
}

- (void)rateUsOnStore
{
	NSString *reviewURL = [NSString stringWithFormat:RATE_URL, PRODUCT_ID_2];
	
	[[UIApplication sharedApplication] openURL:[NSURL URLWithString:reviewURL]];
}

- (void)openUrl : (const char *)url
{
	NSString *urlString = [NSString stringWithFormat:@"%s", url];
	
	[[UIApplication sharedApplication] openURL:[NSURL URLWithString:urlString]];
}

- (void)sendFeedback : (const char *)emailSubject andUserId:(const char *)userId
{
    NSString *emailBody = [self createEmailBody:userId];
    
    NSString *content = [NSString stringWithFormat:@"mailto:%@?subject=%@&body=%@",
                         EMAIL_ADDRESS,
                         [NSString stringWithUTF8String:emailSubject],
                         emailBody];
    NSURL *emailURL = [NSURL URLWithString:
                       [content stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding]];
    
    [[UIApplication sharedApplication] openURL:emailURL];
}

- (NSString *)createEmailBody:(const char *)userId
{
    NSString *currSysVer = [[UIDevice currentDevice] systemVersion];
    NSLog(@"%@", currSysVer);
    
    NSString *currDeviceType = [self deviceName];
    NSLog(@"%@", currDeviceType);
    
    NSString *gameVersion = [NSString stringWithFormat:@"%@",
                             [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleVersion"]];
    
    NSString *body;
    body = [NSString stringWithFormat:@"\n--------------------------------\nHere's my info:\nUser Id: %@\nDevice Type: %@\niOS Version: %@\nGame Version: %@",
            [NSString stringWithUTF8String:userId],
            currDeviceType, currSysVer, gameVersion];
    
    body = [body stringByAppendingString:EMAIL_BODY];
    
    NSLog(@"%@", body);
    
    return body;
}

- (NSString *) deviceModel
{
    size_t size;
    sysctlbyname("hw.machine", NULL, &size, NULL, 0);
    char *model = malloc(size);
    sysctlbyname("hw.machine", model, &size, NULL, 0);
    NSString *deviceModel = [NSString stringWithCString:model encoding:NSUTF8StringEncoding];
    free(model);
    
    return deviceModel;
}

- (NSString *) deviceName
{
    NSString *deviceModel = [self deviceModel];
    
    if ([deviceModel isEqual:@"i386"])      return @"Simulator";  //iPhone Simulator
    if ([deviceModel isEqual:@"iPhone1,1"]) return @"iPhone 1G";   //iPhone 1G
    if ([deviceModel isEqual:@"iPhone1,2"]) return @"iPhone 3G";   //iPhone 3G
    if ([deviceModel isEqual:@"iPhone2,1"]) return @"iPhone 3GS";  //iPhone 3GS
    if ([deviceModel isEqual:@"iPhone3,1"]) return @"iPhone 4";    //iPhone 4 - AT&T
    if ([deviceModel isEqual:@"iPhone3,2"]) return @"iPhone 4";    //iPhone 4 - Other carrier
    if ([deviceModel isEqual:@"iPhone3,3"]) return @"iPhone 4";    //iPhone 4 - Other carrier
    if ([deviceModel isEqual:@"iPhone4,1"]) return @"iPhone 4S";   //iPhone 4S
    if ([deviceModel isEqual:@"iPod1,1"])   return @"iPod 1st"; //iPod Touch 1G
    if ([deviceModel isEqual:@"iPod2,1"])   return @"iPod 2nd"; //iPod Touch 2G
    if ([deviceModel isEqual:@"iPod3,1"])   return @"iPod 3rd"; //iPod Touch 3G
    if ([deviceModel isEqual:@"iPod4,1"])   return @"iPod 4th"; //iPod Touch 4G
    if ([deviceModel isEqual:@"iPad1,1"])   return @"iPad WiFi";   //iPad Wifi
    if ([deviceModel isEqual:@"iPad1,2"])   return @"iPad 3G";     //iPad 3G
    if ([deviceModel isEqual:@"iPad2,1"])   return @"iPad 2";      //iPad 2 (WiFi)
    if ([deviceModel isEqual:@"iPad2,2"])   return @"iPad 2";      //iPad 2 (GSM)
    if ([deviceModel isEqual:@"iPad2,3"])   return @"iPad 2";      //iPad 2 (CDMA)
    
    NSString *aux = [[deviceModel componentsSeparatedByString:@","] objectAtIndex:0];
    
    //If a newer version exists
    if ([aux rangeOfString:@"iPhone"].location != NSNotFound) {
        int version = [[aux stringByReplacingOccurrencesOfString:@"iPhone" withString:@""] intValue];
        if (version == 3) return @"iPhone4";
        if (version == 4) return @"iPhone4s";
        if (version == 5) return @"iPhone5";
        return @"New iPhone";
    }
    if ([aux rangeOfString:@"iPod"].location != NSNotFound) {
        int version = [[aux stringByReplacingOccurrencesOfString:@"iPod" withString:@""] intValue];
        if (version == 4) return @"iPod4thGen";
        if (version == 5) return @"iPod5thGen";
        return @"New iPod";
    }
    if ([aux rangeOfString:@"iPad"].location != NSNotFound) {
        int version = [[aux stringByReplacingOccurrencesOfString:@"iPad" withString:@""] intValue];
        if (version == 1) return @"iPad3G";
        if (version == 2) return @"iPad2";
        if (version == 3) return @"iPad3";
        if (version == 4) return @"iPad4";
        return @"New iPad";
    }
    
    //If none was found, send the original string
    return deviceModel;
}

@end
