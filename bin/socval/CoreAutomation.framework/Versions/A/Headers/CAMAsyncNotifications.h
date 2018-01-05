//
//  CAMDAsyncNotifications.h
//  coreautomationd
//
//  Created by Chen Huang on 11/11/15.
//
//


#import "CAMBluetoothAsyncNotifications.h"
#import "CAMWirelessProximityAsyncNotifications.h"

@interface CAMAsyncNotification : NSObject

+ (NSSet *)allNotifications;

@end