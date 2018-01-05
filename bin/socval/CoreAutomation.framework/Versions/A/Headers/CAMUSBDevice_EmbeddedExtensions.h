//
//  CAMUSBDevice_EmbeddedExtensions.h
//  CoreAutomation
//
//  Created by Matt Massicotte on 3/7/10.
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "CAMUSBDevice.h"
#import "CAMMacOSXTarget.h"

@interface CAMUSBDevice (EmbeddedExtensions)

+ (void)enumerateAllMobileDevicesUsingBlock:(void (^)(id service, NSUInteger idx))block;

- (BOOL)potentialAppleMobileDevice;

- (NSDictionary *)firmwareInfoDictionary;

- (NSString *)deviceState;

+ (NSDictionary *)USBMap;
+ (NSDictionary *)rebuildUSBMap;
+ (id)valueFromUSBMapForKey:(NSString *)key atLocationID:(uint32_t)locationID;
+ (uint32_t)locationIDFromUSBMapForKey:(NSString *)key atLocationID:(uint32_t)locationID;

@end
