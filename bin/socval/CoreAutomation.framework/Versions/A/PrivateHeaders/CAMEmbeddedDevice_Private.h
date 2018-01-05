/*
 *  CAMEmbeddedDevice_Private.h
 *  CoreAutomation
 *
 *  Created by Matt Massicotte on 3/13/10.
 *  Copyright 2010 Apple, Inc. All rights reserved.
 *
 */

@class CAMMobileDeviceState;

@interface CAMEmbeddedDevice (PrivateMethods)

+ (int)runPlatformCommand:(NSString*)string;

- (void)findRegisteredStates;

@property (retain) CAMMobileDeviceState*          internalState;
@property (retain, readonly) NSMutableDictionary* propertyCache;

@end
