//
//  CAMMobileDevice.h
//  CoreAutomation
//
//  This module provide a wrapper to MobileDevice.framework APIs.
//  Please refer to MobileDevice.h for more documentation.
//
//  Created by Chen Huang on 8/20/15.
//
//

#import <Foundation/Foundation.h>
#import <MobileDevice/AMDServiceConnection.h>
#import <MobileDevice/MobileDevice.h>

@interface CAMMobileDevice : NSObject

#pragma mark - Service
+ (AMDError)secureStart:(AMDeviceRef)device
                service:(CFStringRef)service
            withOptions:(CFDictionaryRef)options
  intoServiceConnection:(AMDServiceConnectionRef*)service_out;

#pragma mark - Session
+ (AMDError)startSession:(AMDeviceRef)device;
+ (AMDError)stopSession:(AMDeviceRef)device;
+ (AMDError)connect:(AMDeviceRef)device;
+ (AMDError)disconnect:(AMDeviceRef)device;
+ (AMDError)isValidDevice:(AMDeviceRef)device;

#pragma mark - Property
+ (CFPropertyListRef)copyValue:(AMDeviceRef)device
                    fromDomain:(CFStringRef)domain
                        forKey:(CFStringRef)key
                         error:(AMDError *)error;
+ (AMDError)setValue:(AMDeviceRef)device
          fromDomain:(CFStringRef)domain
              forKey:(CFStringRef)key
           withValue:(CFTypeRef)value;

#pragma mark - Pairing
+ (AMDError)pair:(AMDeviceRef)device;
+ (AMDError)unpair:(AMDeviceRef)device;
+ (AMDError)validatePairing:(AMDeviceRef)device;


@end
