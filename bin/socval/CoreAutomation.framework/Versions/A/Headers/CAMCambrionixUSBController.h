//  Most code from original version of CAMBusManUSBController.m
//  Created by Matt Massicotte on 9/8/10.

//  CAMCambrionixUSBController.h
//  CoreAutomation
//
//  Created by Tarek Khouzam on 1/13/12.
//  Copyright (c) 2012 Apple Inc. All rights reserved.

#import <Foundation/Foundation.h>
#import "CAMUSBController.h"

@class CAMSerialPort;

@protocol CAMCambrionixProtocol <NSObject>

@optional

- (NSString *)command:(NSString *)command;

@end

@interface CAMCambrionixUSBController : CAMUSBController <CAMCambrionixProtocol> {
    NSString *__weak serialPath;
    CAMSerialPort *serialConnection;
    BOOL serialConnected;
    BOOL firmwareVerified;
    NSNumber *__weak numberOfPorts;
}

- (void)flush;
- (NSString *)serialReadBuffer;
- (NSString *)serialWriteBuffer;

- (NSInteger)getNumberOfPorts;

// Change specified ports to specified state
- (NSString *)port:(NSUInteger)port state:(NSUInteger)state;
- (NSArray *)ports:(NSArray *)ports state:(NSUInteger)state;
- (NSArray *)ports:(NSArray *)ports state:(NSUInteger)state withDelay:(NSUInteger)delay;

// Change state of all ports on hub
- (NSString *)connectAll;
- (NSString *)disconnectAll;
- (NSString *)charge;

// Change state of one port on hub
- (NSString *)connectPort:(NSUInteger)port;
- (NSString *)disconnectPort:(NSUInteger)port;
- (NSString *)chargePort:(NSUInteger)port;

// Change state of multiple ports on hub
- (NSArray *)connectPorts:(NSArray *)ports;
- (NSArray *)disconnectPorts:(NSArray *)ports;
- (NSArray *)chargePorts:(NSArray *)ports;

// Change state of one port on hub with delay
- (NSString *)connectPort:(NSUInteger)port withDelay:(NSUInteger)delay;
- (NSString *)disconnectPort:(NSUInteger)port withDelay:(NSUInteger)delay;
- (NSString *)chargePort:(NSUInteger)port withDelay:(NSUInteger)delay;

// Change state of multiple ports on hub with a delay
- (NSArray *)connectPorts:(NSArray *)ports withDelay:(NSUInteger)delay;
- (NSArray *)disconnectPorts:(NSArray *)ports withDelay:(NSUInteger)delay;
- (NSArray *)chargePorts:(NSArray *)ports withDelay:(NSUInteger)delay;

- (NSString *)whereAmI;
- (NSString *)restartFirmware;
- (NSString *)firmwareVersion;

- (NSString *)getAddress;
- (void)info;
- (NSString *)stringInfo;
- (NSString *)getAlias;
+ (NSString *)getAliasFile;
@property(weak, readonly) NSString *serialPath;
@property(readwrite) BOOL firmwareVerified;
@property(weak, readonly) NSNumber *numberOfPorts;
//@property (readonly) NSNumber* locationID;

@end
