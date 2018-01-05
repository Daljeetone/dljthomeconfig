//
//  CAMObliteration.h
//  CoreAutomation
//
//  Created by Justin Ko on 4/3/12.
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//


#import <Foundation/Foundation.h>
#import "CAMReturnValues.h"

#define kCAMObliterationShortName obliteration

#define kCAMObliterationTypeDataOnly            @"DataOnlyWipeType"
#define kCAMObliterationTypeDataAndFirmware     @"DataAndFirmware"

@protocol CAMObliteration
@optional

/*!
 @method     obliterateType:message:options
 @abstract   Invokes the obliterator to wipe 
 @param type Must be one of kCAMObliterationTypeDataOnly or kCAMObliterationTypeDataAndFirmware
 @param message Optional message that will be left in NVRAM.
 @param options More options.
 @discussion
 The obliterator is the subsystem that is responsible for wiping when
 a Settings -> General -> Reset -> Erase All Content and Settings is invoked,
 or when a remote wipe from an Exchange Server or iCloud is sent. A data only
 wipe removes the contents of the device and reboots it back into a 'factory-fresh'
 state.
 
 A data and firmware wipe deletes user data, destroys the system partition, and
 removes the bootable firmware images, causing the device to be unbootable on reboot.
 Once in this state, the device will stick in DFU until a new bootable iOS is 
 restored to the device.
 
 No other options are supported yet.
 */
- (CAMReturnInteger*)obliterateType:(NSString *)type message:(NSString *)message
                            options:(NSDictionary *)options;

@end
