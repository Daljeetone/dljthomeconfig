//
//  CAMNetworking.h
//  CoreAutomation
//
//  Created by Chris Whitney on 1/31/12.
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CAMReturnValues.h"

#define kCAMNetworkingShortName networking

@protocol CAMNetworking
@optional

- (CAMReturnBool*)hasWiFi;
- (CAMReturnBool*)hasWiFiDriver;

#pragma mark -
#pragma mark Airplane Mode
/*!
 @brief Checks the status of Airplane Mode.
 @return A BOOL of YES for airplane mode enabled, or NO for disabled.

 Relies on AppSupport's RadiosPreferences class.
 */
- (CAMReturnBool*)isAirplaneModeEnabled;

/*!
 @brief Set the status of Airplane Mode.
 @param flag	An NSNumber with a BOOL value.
 @return nil on success, or an NSError on failure.

 Relies on AppSupport's RadiosPreferences class.
 */
- (CAMReturnVoid*)setAirplaneModeEnabled:(NSNumber*)flag;


#pragma mark -
#pragma mark Network Settings
/*!
 @brief Query the device's current Domain Name Service settings
 @return A dictionary: possbile keys include 'DomainName', 'SearchDomains', and 'ServerAddresses'
 */
- (CAMReturnDictionary*)DNSSettings;

/*!
 @brief Query the device's current network settings
 @return a dictionary with keys 'IPv4' and / or 'IPv6', each with possible subkeys including 'PrimaryInterface', 'PrimaryService', 'Router'
 */
- (CAMReturnDictionary*)networkSettings;

/*!
 @brief Query the device's current network settings for a given interface
 @return a dictionary with keys 'IPv4' and / or 'IPv6', each with possible subkeys including 'PrimaryInterface', 'PrimaryService', 'Router'
 */
- (CAMReturnDictionary*)networkInterfaceSettings:(NSString*)ifname;


#pragma mark -
#pragma mark Bonjour Services
- (CAMReturnVoid*)registerService:(NSString*)serviceName withServiceType:(NSString*)serviceType withinTimeout:(NSNumber*)timeout;
- (CAMReturnVoid*)unregisterService;
- (CAMReturnArray*)discoverServices:(NSString*)serviceType withinTimeout:(NSNumber*)timeout;
- (CAMReturnVoid*)connectService:(NSString*)serviceName withServiceType:(NSString*)serviceType withinTimeout:(NSNumber*)timeout;


#pragma mark -
#pragma mark Tethering
/*!
 @brief Query the current tethering (personal hotspot) status
 @return Returns a dictionary with the keys ('state', 'reason')
 */
- (CAMReturnDictionary*)tetheringStatus;
/*!
 @brief Enable or disable tethering (personal hotspot)
 */
- (CAMReturnVoid*)setInternetTetheringEnabled:(NSNumber*)flag;
/*!
 @brief Query the curernt number of hosts that are tethering (connected to personal hotspot)
 @return Returns an integer counting the number of connected hosts
 */
- (CAMReturnInteger*)tetheredHostCount;

/*!
 @brief Authenticate for internet tethering.
 @return Returns bool represents authentication result.
 */
- (CAMReturnBool*)authenticateInternetTethering;

/*!
 @brief Whether internet tethering authenticated.
 @return Returns whether internet tethering is authenticated or not.
 */
- (CAMReturnBool*)internetTetheringAuthenticated;
@end
