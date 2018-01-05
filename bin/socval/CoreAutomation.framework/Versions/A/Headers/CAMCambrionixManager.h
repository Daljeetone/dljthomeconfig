//
//  CAMCambrionixManager.h
//  CoreAutomation
//
//  Created by Tarek Khouzam on 4/30/12.
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#define BUSMANPORT @"BusmanPort"
#define BUSMANSERIAL @"BusmanSerial"
#define BUSMANXLTYPE @"BusmanPortType"

#import "CAMCambrionixUSBController.h"

@interface CAMCambrionixManager : NSObject

@property(readonly) NSMutableDictionary *physicallyAttachedHubs;
@property(readonly) NSMutableDictionary *hubsLocationID;
@property(readonly) NSMutableDictionary *availableHubObjects;

// Init
+ (CAMCambrionixManager *)getManager;
+ (CAMCambrionixManager *)getManager:(NSInteger)time error:(NSError **)error;

// Get Cambrionix Objects
- (CAMCambrionixUSBController *)getController:(NSString *)address grandParentVendor:(NSInteger)vendor grandParentProduct:(NSInteger)product error:(NSError **)error;
- (CAMCambrionixUSBController *)getController:(NSString *)address targetVendor:(NSInteger)vendor targetProduct:(NSInteger)product error:(NSError **)error;
- (CAMCambrionixUSBController *)getController:(NSString *)address classType:(Class)type error:(NSError **)error;

// Get addresses of attached hubs without the need to create hub objects
- (NSArray *)getBusmanAddresses;
- (NSArray *)getBusmanXLAddresses;
- (NSDictionary *)getAllAddressesWithTypes;

// Returns hub objects if already created. If not, create new hub object
- (NSArray *)getBusmanControllers;
- (NSArray *)getBusmanXLControllers;
- (NSArray *)getAllControllers;

// Set the state for all connected devices
- (void)connectAll;
- (void)disconnectAll;
- (void)chargeAll;

// Set all connected device to highpower
- (void)highPowerCharge;

// Set the state for existing controllers
- (void)connectExisting;
- (void)disconnectExisting;
- (void)chargeExisting;

// Returns copies of class variables
- (NSDictionary *)getPhysicallyAttachedHubs;
- (NSDictionary *)getAvailableHubObjects;
- (NSDictionary *)getHubsLocationID;

// Returns the port number for the device at the location ID
+ (NSDictionary *)findBusmanPort:(NSNumber *)locationID;

//-(void)printInfo;

@end
