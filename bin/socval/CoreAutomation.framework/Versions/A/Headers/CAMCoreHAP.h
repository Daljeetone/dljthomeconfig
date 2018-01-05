//
//  CAMCoreHAP.h
//  coreautomationd
//
//  Created by Matthew Lucas on 4/22/14.
//  Copyright 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CAMReturnValues.h"

#define kCAMCoreHAPShortName  coreHAP

// HAPAccessorySever Keys
#define kCAMCoreHAPAccessoryServerID            @"accessoryServerID"
#define kCAMCoreHAPAccessoryServerIdentifier    @"identifier"
#define kCAMCoreHAPAccessoryServerPaired        @"paired"
#define kCAMCoreHAPAccessoryServerReachable     @"reachable"

//  HAPAccessory Keys
#define kCAMCoreHAPAccessoryInstanceID          @"instanceID"
#define kCAMCoreHAPAccessoryName                @"name"
#define kCAMCoreHAPAccessoryServices            @"services"

//  HAPService Keys
#define kCAMCoreHAPServiceType                  @"type"
#define kCAMCoreHAPServiceInstanceID            @"instanceID"
#define kCAMCoreHAPServiceCharacteristcs        @"characteristics"

//  HAPCharacteristic Keys
#define kCAMCoreHAPCharacteristicEventNotificationsEnabled  @"eventNotificationsEnabled"
#define kCAMCoreHAPCharacteristicInstanceID     @"instanceID"
#define kCAMCoreHAPCharacteristicMetadata       @"metadata"
#define kCAMCoreHAPCharacteristicProperties     @"properties"
#define kCAMCoreHAPCharacteristicType           @"type"
#define kCAMCoreHAPCharacteristicValue          @"value"

#define kCAMCoreHAPCharacteristicReadable       @"readable"
#define kCAMCoreHAPCharacteristicWritable       @"writable"
#define kCAMCoreHAPCharacteristicNotify         @"notify"

//  HAPDescriptor Keys
#define kCAMCoreHAPDescriptorIdentifier         @"identifier"
#define kCAMCoreHAPDescriptorValue              @"value"

//  HAPMetadata Keys
#define kCAMCoreHAPMetadataManufacturerDescription  @"manufacturerDescription";
#define kCAMCoreHAPMetadataFormat                   @"format";
#define kCAMCoreHAPMetadataUnits                    @"units";

//  HAPKeychain Keys
#define kCAMCoreHAPKeychainStorePublicKey       @"publicKey"
#define kCAMCoreHAPKeychainStoreSecretKey       @"secretKey"
#define kCAMCoreHAPKeychainStoreUsername        @"username"

@protocol CAMCoreHAP
@optional

#pragma mark -
#pragma mark Manager

/*!
 *  @brief  Starts the CoreHAPManager.
 *
 *  @discussion This must be called before anything else.
 */
- (CAMReturnVoid *)start;

/*!
 *  @brief  Stops the CoreHAPManager.
 *
 *  @discussion After calling this only start should be called.
 */
- (CAMReturnVoid *)stop;

/*!
 *  @brief  Returns all the discovered accessory servers.
 *
 *  @return An NSArray of dictionaries representing HAPAccessoryServer objects.
 */
- (CAMReturnArray *)allAccessoryServers;

/*!
 *  @brief  Returns the accessory server.
 *
 *  @param  accessoryServerID   The accessory server ID as returned by allAccessoryServers.
 *  @return A dictionary representing the HAPAccessoryServer object.
 */
- (CAMReturnDictionary *)accessoryServerForAccessoryServerID:(NSNumber *)accessoryServerID;

/*!
 *  @brief  Attempts to pair the accessory.
 *
 *  @discussion Attempts to pair the accessory with the provided password. This is not thread safe.
 *  @param  password    The pairing password to use
 *  @param  accessoryServerID   The accessory server ID as returned by allAccessoryServers.
 *  @param  timeout How long to wait for pairing to complete. Default is 30s.
 *  @returns YES if pairing is successful, NO otherwise. An NSError may be returned indicating the failure reason.
 */
- (CAMReturnBool *)pairWithPassword:(NSString *)password accessoryServerID:(NSNumber *)accessoryServerID timeout:(NSNumber *)timeout;

/*!
 *  @brief  Starts discovery of server accessories.
 *
 *  @discussion Starts the discovery of server accessories.
 *  @param  accessoryServerID   The accessory server ID as returned by allAccessoryServers.
 *  @return Returns an NSError if discovery failed.
 */
- (CAMReturnVoid *)discoverAccessoriesForAccessoryServerID:(NSNumber *)accessoryServerID;

- (CAMReturnArray *)allAccessoriesForAccessoryServerID:(NSNumber *)accessoryServerID;

- (CAMReturnDictionary *)accessoryForAccessoryInstanceID:(NSNumber *)accessoryInstanceID accessoryServerID:(NSNumber *)accessoryServerID;

/*!
 *  @brief  Returns all services for the accessory.
 *
 *  @param  accessoryInstanceID The HAKAccessory instance ID.
 *  @param  accessoryServerID   The accessory server ID as returned by allAccessoryServers.
 *  @return An array representing the HAPServices of the accessory.
 */
- (CAMReturnArray *)allServicesForAccessoryInstanceID:(NSNumber *)accessoryInstanceID accessoryServerID:(NSNumber *)accessoryServerID;

/*!
 *  @brief  Returns a particular services for the accessory.
 *
 *  @param  serviceInstanceID   The HAPService instanceID.
 *  @param  accessoryInstanceID The HAKAccessory instance ID.
 *  @param  accessoryServerID   The accessory server ID as returned by allAccessoryServers.
 *  @return A dictionary representing the HAPService object.
 */
- (CAMReturnDictionary *)serviceForServiceInstanceID:(NSNumber *)serviceInstanceID accessoryInstanceID:(NSNumber *)accessoryInstanceID accessoryServerID:(NSNumber *)accessoryServerID;

/*!
 *  @brief  Returns all characteristics for the service.
 *
 *  @param  serviceInstanceID   The HAPService instanceID.
 *  @param  accessoryInstanceID The HAKAccessory instance ID.
 *  @param  accessoryServerID   The accessory server ID as returned by allAccessoryServers.
 *  @return An array representing the HAPCharacteristic of the service.
 */
- (CAMReturnArray *)allCharacteristicsForServiceInstanceID:(NSNumber *)serviceInstanceID accessoryInstanceID:(NSNumber *)accessoryInstanceID accessoryServerID:(NSNumber *)accessoryServerID;

/*!
 *  @brief  Returns a particular characteristic for the service.
 *
 *  @param  characteristicInstanceID    The HAPCharacteristic instanceID.
 *  @param  serviceInstanceID   The HAPService instanceID.
 *  @param  accessoryInstanceID The HAKAccessory instance ID.
 *  @param  accessoryServerID   The accessory server ID as returned by allAccessoryServers.
 *  @return A dictionary representing the HAPCharacteristic object.
 */
- (CAMReturnDictionary *)characteristicForCharacteristicInstanceID:(NSNumber *)characteristicInstanceID serviceInstanceID:(NSNumber *)serviceInstanceID accessoryInstanceID:(NSNumber *)accessoryInstanceID accessoryServerID:(NSNumber *)accessoryServerID;

/*!
 *  @brief  Returns the characteristic value.
 *
 *  @discussion The value of a characteristic is id therefore this object may return any valid plist type.
 *  @discussion This does not perform an accessory read. You must call
 *              readValueForCharacteristicInstanceID:serviceInstanceID:accessoryInstanceID:timeout to retrieve the 
 *              value of the accessory.
 *
 *  @param  characteristicInstanceID    The HAPCharacteristic instanceID.
 *  @param  serviceInstanceID   The HAPService instanceID.
 *  @param  accessoryInstanceID The HAKAccessory instance ID.
 *  @param  accessoryServerID   The accessory server ID as returned by allAccessoryServers.
 *  @return The value object.
 */
- (CAMReturn *)valueForCharacteristicInstanceID:(NSNumber *)characteristicInstanceID serviceInstanceID:(NSNumber *)serviceInstanceID accessoryInstanceID:(NSNumber *)accessoryInstanceID accessoryServerID:(NSNumber *)accessoryServerID;

/*!
 *  @brief  Sets the characteristic value.
 *
 *  @discussion This performs a synchronous write to the accessory
 *
 *  @param  value   Must be a valid plist type of nil.
 *  @param  characteristicInstanceID    The HAPCharacteristic instanceID.
 *  @param  serviceInstanceID   The HAPService instanceID.
 *  @param  accessoryInstanceID The HAKAccessory instance ID.
 *  @param  accessoryServerID   The accessory server ID as returned by allAccessoryServers.
 *  @param  timeout The timeout for the remote read
 *  @return The value object.
 */
- (CAMReturnVoid *)setValue:(id)value characteristicInstanceID:(NSNumber *)characteristicInstanceID serviceInstanceID:(NSNumber *)serviceInstanceID accessoryInstanceID:(NSNumber *)accessoryInstanceID accessoryServerID:(NSNumber *)accessoryServerID timeout:(NSNumber *)timeout;
/*!
 *  @brief  Reads the value from the accessory.
 *
 *  @param  characteristicInstanceID    The HAPCharacteristic instanceID.
 *  @param  serviceInstanceID   The HAPService instanceID.
 *  @param  accessoryInstanceID The HAKAccessory instance ID.
 *  @param  accessoryServerID   The accessory server ID as returned by allAccessoryServers.
 *  @param  timeout The timeout for the remote read
 */
- (CAMReturnVoid *)readValueForCharacteristicInstanceID:(NSNumber *)characteristicInstanceID serviceInstanceID:(NSNumber *)serviceInstanceID accessoryInstanceID:(NSNumber *)accessoryInstanceID accessoryServerID:(NSNumber *)accessoryServerID timeout:(NSNumber *)timeout;

/*!
 *  @brief  Returns the controller's keys and username.
 *
 *  return  A NSDictionary representing the HAPSytemKeychainStore or nil.
 */
- (CAMReturnDictionary *)getControllerKeyPair;

/*!
 *  @brief  Removes the controllers key store.
 *
 *  @discussion This action will also remove all accessory key stores. This cannot be undone, use with 
 *              caution.
 */
- (CAMReturnVoid *)removeControllerKeyPair;

/*!
 *  @brief  Returns the accessory's public key.
 *
 *  @param  username    The username of the accessory.
 *  @return The accessory's public key or nil.
 */
- (CAMReturnData *)accessoryPublicKeyForUsername:(NSString *)username;

/*!
 *  @brief  Sets the accessory's public key.
 *
 *  @discussion This pairs the accessory.
 *  @param publicKey    The accessory's publicKey.
 *  @param  username    The username of the accessory.
 */
- (CAMReturnVoid *)setAccessoryPublicKey:(NSData *)publicKey forUsername:(NSString *)username;

/*!
 *  @brief  Removes all accessory key stores.
 *
 *  @discussion  This removes all accessory pairings, use with caution.
 */
- (CAMReturnVoid *)removeAllAccessoryKeys;

@end
