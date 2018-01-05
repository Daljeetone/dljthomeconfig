//
//  CAMWiFi.h
//  CoreAutomation
//
//  Created by Chris Whitney on 2/15/12.
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CAMReturnValues.h"

#define kCAMWiFiShortName WiFi

// WiFi Keys
#define kCAMWiFiUUIDKey             @"uuid"               // String
#define kCAMWiFiBSSIDKey            @"bssid"              // String
#define kCAMWiFiSSIDKey             @"ssid"               // String
#define kCAMWiFiUserNameKey         @"userName"           // String
#define kCAMWiFiPasswordKey         @"password"           // String
#define kCAMWiFiRequiresPasswordKey @"requiresPassword"   // Bool
#define kCAMWiFiIsHiddenKey         @"isHidden"           // Bool
#define kCAMWiFiIsWEPKey            @"isWep"              // Bool
#define kCAMWiFiIsWPAKey            @"isWpa"              // Bool
#define kCAMWiFiIsWPA2Key           @"isWpa2"             // Bool
#define kCAMWiFiIsEAPKey            @"isEap"              // Bool
#define kCAMWiFiIsWAPIKey           @"isWapi"             // Bool
#define kCAMWiFiIsHS20              @"isHS20"             // Bool
#define kCAMWiFiAgeKey              @"age"                // Float
#define kCAMWiFiChannelKey          @"channel"            // Integer
#define kCAMWiFiModeKey             @"mode"               // Integer
#define kCAMWiFiAuthLower           @"authLower"          // Integer
#define kCAMWiFiAuthUpper           @"authUpper"          // Integer
#define kCAMWiFiCipherType          @"cipherType"         // Integer
#define kCAMWiFiRSSIKey             @"rssi"               // Integer
#define kCAMWiFiEntryKey            @"entry"              // String
#define kCAMWiFiSecurityKey         @"security"           // Integer
#define kCAMWiFiCountryCodeKey      @"countryCode"        // String

#define kWakeInfoTimestampKey       @"IO80211InterfaceWoWWakeUpTimeStamp"
#define kWakeInfoReasonKey          @"IO80211InterfaceWoWWakeUpReason"
#define kWakeInfoCommandKey         @"IO80211InterfaceWoWWakeUpCommand"
#define kWakeInfoDataKey            @"IO80211InterfaceWoWWakeUpData"



@protocol CAMWiFi
@optional

#pragma mark -
#pragma mark Power
- (CAMReturnVoid*)on;
- (CAMReturnVoid*)off;
- (CAMReturnBool*)isOn;
- (CAMReturnBool*)isActive;

#pragma mark -
#pragma mark Connections
// Note: associate requires a dictionary that is one of the results from scanForNetworkName:withinTimeout:
- (CAMReturnVoid*)associateWithNetwork:(NSDictionary*)networkInfo;
- (CAMReturnVoid*)disassociate;
- (CAMReturnDictionary*)currentNetwork;
- (CAMReturnArray*)scanForNetworkName:(NSString*)ssid withinTimeout:(NSNumber*)timeout;
- (CAMReturnArray*)scanForNetworkName:(NSString*)ssid withinTimeout:(NSNumber*)timeout withinCacheAge:(NSNumber*)maxage;
- (CAMReturnArray*)scanForChannel:(NSString*)channel withinTimeout:(NSNumber*)timeout withinCacheAge:(NSNumber*)maxage withDwellTime:(NSNumber*)dwellTime;
- (CAMReturnDouble*)secondsTakenInScanning;  // Returns time took (seconds) for the last wifi scan.
- (CAMReturnArray*)lastDisconnectedReason;
- (CAMReturnBool*)isDeviceMultiBand;

#pragma mark -
#pragma mark Preferred List
//For OSX the "uuid" is actually the ssid. They are different in iOS, but for OSX uuid is set to ssid.
- (CAMReturnArray*)listPreferredNetworks;
/*!
 @method    isPreferredNetwork
 @abstract  Verifies whether a network is a preferred network.
 @param     ssid - network SSID
 security - Currently not used. rdar://problem/21246792
 */
- (CAMReturnBool*)isPreferredNetwork:(NSString*)ssid withSecurity:(NSString*)security;

/*!
 @method    addPreferredNetworkID
 @abstract  Adds a network to a list of preferred networks.
 This method is called by WAF. It is only called after associating to a network to add the latter to a list of preferred networks.
 This functionality is needed in iOS. On a MAC it is not needed because the networks are added to the list automatically.
 The method behaves differently in iOS and OSX. In iOS it adds the network to AutoJoin list.
 In OSX it checks that the network is already added and sets an error if it's not.
 Error is set in case of failure.
 @param     uuid - network uuid in iOS, network ssid in OSX
 */
- (CAMReturnVoid*)addPreferredNetworkID:(NSString*)uuid;
- (CAMReturnVoid*)removePreferredNetworkID:(NSString*)uuid;
- (CAMReturnVoid*)removeAllPreferredNetworks;

#pragma mark -
#pragma mark TCP / IP
- (CAMReturnVoid*)useDHCPForNetworkName:(NSString*)ssid;
// Note: IP settings uses a dictionary with certain keys (ipAddress, router, etc) that are not yet exposed.
- (CAMReturnVoid*)useManualIPSettings:(NSDictionary*)ipInfo forNetworkName:(NSString*)ssid;
- (CAMReturnString*)interfaceName;

#pragma mark -
#pragma mark Logging
- (CAMReturnBool*)isLoggingEnabled;
- (CAMReturnVoid*)setLoggingEnabled:(NSNumber*)flag;
- (CAMReturnBool*)isFileLoggingEnabled;
- (CAMReturnVoid*)setFileLoggingEnabled:(NSNumber*)flag;
- (CAMReturnBool*)isDriverLoggingEnabled;
- (CAMReturnVoid*)setDriverLoggingEnabled:(NSNumber*)flag;
- (CAMReturnString*)dumpWiFiLogs;

#pragma mark -
#pragma mark Internal
- (CAMReturnArray*)vendorIdentifiers;
- (CAMReturnVoid*)reattach;

#pragma mark -
#pragma mark WoW
- (CAMReturnBool*)isWoWSupported;
- (CAMReturnBool*)isWoWEnabled;
- (CAMReturnInteger*)registerRemoteNotification:(NSString*)deviceToken forDeviceName:(NSString*)deviceName withServer:(NSString*)server;
- (CAMReturnInteger*)unregisterRemoteNotification:(NSString*)deviceToken forDeviceName:(NSString*)deviceName withServer:(NSString*)server;
- (CAMReturnDictionary*)lastWakeInfo;
- (CAMReturnBool*)isLPASEnabled;

#pragma mark -
#pragma mark ePNO
- (CAMReturnVoid*)setBackgroundScanNetworks:(NSArray*)networks;
- (CAMReturnArray*)backgroundScanNotifications;
- (CAMReturnVoid*)clearBackgroundScanNotifications;
- (CAMReturnBool*)isBackgroundScanSuspend;

#pragma mark -
#pragma mark WiFi Tethering
- (CAMReturnBool*)isWiFiTetheringSupported;
- (CAMReturnBool*)isWiFiTetheringEnabled;
- (CAMReturnVoid*)setWiFiTetheringPassword:(NSString*)password;
- (CAMReturnString*)WiFiTetheringPassword;
- (CAMReturnBool*)isWiFiTetheringDiscoverable;
- (CAMReturnVoid*)setWiFiTetheringDiscoverable:(NSNumber*)flag;

#pragma mark -
#pragma mark GAS
// Generic Advertisement Service APIs
- (CAMReturnArray*)getGasNetworkInformation:(NSArray*)bssids fromChannels:(NSArray*)channels forQueries:(NSArray*)queries withProtocol:(NSNumber*)protocol withTimeout:(NSNumber*)timeout;
- (CAMReturnArray*)getMCCMNC:(NSString*)bssid onChannel:(NSNumber*)channel withTimeout:(NSNumber*)timeout;
- (CAMReturnArray*)getNAIRealm:(NSString*)bssid onChannel:(NSNumber*)channel withTimeout:(NSNumber*)timeout;
- (CAMReturnArray*)getRoamingConsortium:(NSString*)bssid onChannel:(NSNumber*)channel withTimeout:(NSNumber*)timeout;

#pragma mark - CoreWLAN (Yellow Only)
- (CAMReturnInteger *)transmitRate;
- (CAMReturnInteger *)transmitPower;
- (CAMReturnInteger *)rssiValue;
- (CAMReturnInteger *)noiseMeasurement;
- (CAMReturnInteger *)channelNumber;
- (CAMReturnInteger *)channelWidth;
- (CAMReturnInteger *)channelBand;
- (CAMReturnInteger *)security;
- (CAMReturnInteger *)interfaceMode;
- (CAMReturnInteger *)activePHYMode;
- (CAMReturnBool *)deviceAttached;
- (CAMReturnBool *)serviceActive;
- (CAMReturnString *)ssid;
- (CAMReturnString *)bssid;
- (CAMReturnString *)hardwareAddress;
- (CAMReturnString *)countryCode;
- (CAMReturnArray *)supportedWLANChannels;
- (CAMReturnArray *)cachedScanResults;
- (CAMReturnArray *)scan:(NSString*)ssid;
- (CAMReturnBool *)associate:(NSString*)ssid password:(NSString *)password;
- (CAMReturnBool *)associateEnterprise:(NSString*)ssid username:(NSString *)username password:(NSString *)password;
- (CAMReturnBool *)createIBSSWithSSID:(NSDictionary*)networkInfo;
- (CAMReturnString *)chipsetName;

#pragma mark - CoreWLAN (Private)
- (CAMReturnInteger *)mcsIndex;
- (CAMReturnInteger *)maximumLinkSpeed;
- (CAMReturnInteger *)physicalLayerMode;
- (CAMReturnInteger *)interfaceControlState;
- (CAMReturnBool *)monitorMode;
- (CAMReturnBool *)networkInterfaceAvailable;
- (CAMReturnBool *)busy;
- (CAMReturnVoid *)destroyIBSS;
- (CAMReturnVoid *)clearScanCache;
- (CAMReturnDictionary *)lastNetworkJoined;
- (CAMReturnInteger *)startAutoJoin;
- (CAMReturnBool *)causedLastWake;

#pragma mark - Ranging
- (CAMReturnBool *)AWDLBringUp:(NSDictionary *)startRequest withTimeout:(NSNumber *)timeout;
- (CAMReturnBool *)isWiFiRangingSupported;
- (CAMReturnDictionary *)GetAWDLInfo;
- (CAMReturnArray *)GetPeerList;
- (CAMReturnBool *)SetRangable;
- (CAMReturnVoid *)AWDLTeardown;
- (CAMReturnDouble *)GetAWDLPeerTime;
- (CAMReturnDouble *)GetAWDLUpTime;
- (CAMReturnBool *)StartRanging;
- (CAMReturnString *)GetRangingResultTime:(NSNumber*)startTimeoutSec;
- (CAMReturnDictionary *)GetRangingResults:(NSNumber*)startTimeoutSec;

@end
