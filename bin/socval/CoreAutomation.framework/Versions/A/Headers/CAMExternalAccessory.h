//
//  CAMExternalAccessory.h
//  coreautomationd
//
//  Created by Matthew Lucas on 4/2/13.
//  Copyright 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CAMReturnValues.h"

#define kCAMExternalAccessoryShortName  externalAccessory

// EAAccessory dictionary keys
#define kCAMExternalAccessoryEAAccessoryConnectionIDKey     @"connectionID"
#define kCAMExternalAccessoryEAAccessoryNameKey             @"name"
#define kCAMExternalAccessoryEAAccessoryManufacturerKey     @"manufacturer"
#define kCAMExternalAccessoryEAAccessoryModelNumberKey      @"modelNumber"
#define kCAMExternalAccessoryEAAccessorySerialNumberKey     @"serialNumber"
#define kCAMExternalAccessoryEAAccessoryFirmwareRevisionKey @"firmwareRevision"
#define kCAMExternalAccessoryEAAccessoryHardwareRevisionKey @"hardwareRevision"
#define kCAMExternalAccessoryEAAccessoryProtocolStringsKey  @"protocolStrings"

//  EASession dictionary keys
#define kCAMExternalAccessoryEASessionAccessoryKey          @"accessory"
#define kCAMExternalAccessoryEASessionSessionIDKey          @"sessionID"
#define kCAMExternalAccessoryEASessionProtocolStringKey     @"protocolString"

//  Location Type Keys
#define kCAMExternalAccessoryLocationSentenceTypeReserved   @"reserved"
#define kCAMExternalAccessoryLocationSentenceTypeGPGGA      @"GPGGA"
#define kCAMExternalAccessoryLocationSentenceTypeGPRMC      @"GPRMC"
#define kCAMExternalAccessoryLocationSentenceTypeGPGSV      @"GPGSV"
#define kCAMExternalAccessoryLocationSentenceTypePASCD      @"PASCD"
#define kCAMExternalAccessoryLocationSentenceTypePAGCD      @"PAGCD"
#define kCAMExternalAccessoryLocationSentenceTypePAACD      @"PAACD"
#define kCAMExternalAccessoryLocationSentenceTypeGPHDT      @"GPHDT"

@protocol CAMExternalAccessory
@optional

/*!
 @method    connectedAccessories
 @abstract	The accessory objects corresponding to the list of currently connected accessories
 @return    Returns an array of NSDictionaries representing each connected accessory.
 */
- (CAMReturnArray*)connectedAccessories;

/*!
 @method    showBluetoothAccessoryPicker
 @abstract  Shows the UI Bluetooth Accessory Picker
 */
- (CAMReturnVoid*)showBluetoothAccessoryPicker;

/*!
 @method    openSessions
 @abstract	The session objects corresponding to the list of currently open sessions
 @discussion    Returns an array of NSDictionaries representing each open session.
    Note: This only returns sessions opened by CAM, not by another App.
 @return    Returns an array of dictionaries representing open sessions.
 */
- (CAMReturnArray*)openSessions;

/*!
 @method    openSessionWithAccessoryID:withProtocolString:
 @abstract  Opens the EA Session.
 @param accessoryID Accessory Connection ID (as returned by connectedAccessories)
 @param protocolString  Protocol String to use for EA Session
 @return    Returns EA Session ID
 */
- (CAMReturnInteger*)openSessionWithAccessoryID:(NSNumber *)accessoryID withProtocolString:(NSString *)protocolString;

/*!
 @method    closeSessionWithSessionID:
 @abstract  Closes the EA Session.
 @param sessionID   The EA Session ID (as returned by openSessionWithAccessoryID:withProtocolString:)
 */
- (CAMReturnVoid*)closeSessionWithSessionID:(NSNumber *)sessionID;

/*!
 @method    writeData:withSessionID:
 @abstract  Writes data to the EA Session.
 @param sessionID   The EA Session ID (as returned by openSessionWithAccessoryID:withProtocolString:)
 */
- (CAMReturnBool*)writeData:(NSData *)data withSessionID:(NSNumber *)sessionID;

/*!
 @method    readBytesAvailableWithSessionID:
 @abstract  Gets the number of bytes available in the session's read buffer.
 @param sessionID   The EA Session ID (as returned by openSessionWithAccessoryID:withProtocolString:)
 @return    Number of bytes available to read.
 */
- (CAMReturnInteger*)readBytesAvailableWithSessionID:(NSNumber *)sessionID;

/*!
 @method    readDataWithLength:withSessionID:
 @abstract  Reads some part of the accessories buffer
 @param length  Number of bytes to read
 @param sessionID   The EA Session ID (as returned by openSessionWithAccessoryID:withProtocolString:)
 @return    Returns the data or error if unable to read the speicified number of bytes
 */
- (CAMReturnData*)readDataWithLength:(NSNumber*)length withSessionID:(NSNumber *)sessionID;

/*!
 @method    readDataWithSessionID:
 @abstract  Read all available EA Session data.
 @param sessionID   The EA Session ID (as returned by openSessionWithAccessoryID:withProtocolString:)
 @return    Returns the data or error if unable to read the speicified number of bytes
 */
- (CAMReturnData*)readDataWithSessionID:(NSNumber *)sessionID;

/*!
 @method    preferredAppWithAccessoryID:
 @abstract  Gets the perferred app Bundle ID
 @param accessoryID Accessory Connection ID (as returned by connectedAccessories)
 */
- (CAMReturnString*)preferredAppWithAccessoryID:(NSNumber *)accessoryID;

/*!
 @method    macAddressWithAccessoryID:
 @abstract  Gets the MAC address of the accessory.
 @param accessoryID Accessory Connection ID (as returned by connectedAccessories)
 */
- (CAMReturnString*)macAddressWithAccessoryID:(NSNumber *)accessoryID;

/*!
 @method    vehicleInfoDataWithAccessoryID:
 @abstract  Gets the current VehicleInfo data as sent by the device.
 @param accessoryID Accessory Connection ID (as returned by connectedAccessories)
 @return    Returns a dictionary representing current VehicleInfo Data
 */
- (CAMReturnDictionary*)vehicleInfoDataWithAccessoryID:(NSNumber *)accessoryID;

/*!
 @method    vehicleInfoSupportedTypesWithAccessoryID:
 @abstract  Gets the supported VehicleInfo types as identified by accessory.
 @param accessoryID Accessory Connection ID (as returned by connectedAccessories)
 @return    Returns a dictionary representing Supported VehicleInfo Types
 */
- (CAMReturnDictionary*)vehicleInfoSupportedTypesWithAccessoryID:(NSNumber *)accessoryID;

/*!
 @method    vehicleInfoInitialDataWithAccessoryID:
 @abstract  Gets the initial VehicleInfo data sent by the accessory (during Identification)
 @param accessoryID Accessory Connection ID (as returned by connectedAccessories)
 @return    Returns a dictionary representing initial VehicleInfo Data
 */
- (CAMReturnDictionary*)vehicleInfoInitialDataWithAccessoryID:(NSNumber *)accessoryID;

/*!
 @method    startLocation
 @abstract  Tells device to start requesting location information from connected accessories
 */
- (CAMReturnVoid*)startLocation;

/*!
 @method    stopLocation
 @abstract  Tells device to stop requesting location information from connected accessories
 */
- (CAMReturnVoid*)stopLocation;

/*!
 @method    setLocationSentenceTypes:withAccessoryID:
 @abstract  Sets the location types requested by the device.
 @param accessoryID Accessory Connection ID (as returned by connectedAccessories)
 */
- (CAMReturnVoid*)setLocationSentenceTypes:(NSArray *)sentenceTypes withAccessoryID:(NSNumber *)accessoryID;

/*!
 @method    locationSentenceTypesWithAccessoryID:
 @abstract  Supported NMEA types requested by the device.
 @param accessoryID Accessory Connection ID (as returned by connectedAccessories)
 @return    Returns an array of NMEA type strings
 */
- (CAMReturnArray*)locationSentenceTypesWithAccessoryID:(NSNumber *)accessoryID;

/*!
 @method    supportsLocationWithAccessoryID:
 @abstract  Whether the connected accessory has identified as supporting location
 @param accessoryID Accessory Connection ID (as returned by connectedAccessories)
 */
- (CAMReturnBool*)supportsLocationWithAccessoryID:(NSNumber *)accessoryID;

/*!
 @method    accessoryHasNMEASentencesAvailableWithAccessoryID:
 @abstract  Returns whether or not device has queued NMEA Sentences available for reading.
 @discussion    This will not work currently (Innsbruck and before) as locationd will read data first (emptying queue).
 @param accessoryID Accessory Connection ID (as returned by connectedAccessories)
 */
- (CAMReturnBool*)accessoryHasNMEASentencesAvailableWithAccessoryID:(NSNumber *)accessoryID;

/*!
 @method    nmeaSentenceWithAccessoryID:
 @abstract  Gets the oldest queued NMEA Sentence from device
 @param accessoryID Accessory Connection ID (as returned by connectedAccessories)
 */
- (CAMReturnString*)nmeaSentenceWithAccessoryID:(NSNumber *)accessoryID;

/*!
 @method    setIAPTimeSyncWithAccessoryID:params:
 @param accessoryID Accessory Connection ID (as returned by connectedAccessories)
 */
- (CAMReturnVoid*)setIAPTimeSyncWithAccessoryID:(NSNumber *)accessoryID params:(NSDictionary *)paramDictionary;

/*!
 @method    startIPAccessoryDiscovery
 @abstract  Starts device searching for IP Accessories
 */
- (CAMReturnVoid*)startIPAccessoryDiscovery;

/*!
 @method    stopWirelessAccessoryDiscovery
 @abstract  Stops device searching for IP Accessories
 */
- (CAMReturnVoid*)stopIPAccessoryDiscovery;

/*!
 @method    connectIPAccessory:
 @abstract  Connects to the named accessory
 @param accessory   Name of the accessory
 */
- (CAMReturnVoid*)connectIPAccessory:(NSString *)accessory;

/*!
 @method    disconnectIPAccessory:
 @abstract  Disconnects to the named accessory
 @param accessory   Name of the accessory
 */
- (CAMReturnVoid*)disconnectIPAccessory:(NSString *)accessory;

/*!
 @method    sendDestinationInformation:withUUID:
 @abstract  Sends test destinaiton information data using iAP with the data and a UUID provided
 @param destination   Dictionary containing destination data
 @param uuid   UUID used by the caller to keep track of the request
 */
- (CAMReturnVoid*)sendDestinationInformation:(NSDictionary*)destination withUUID:(NSNumber *)uuid;

/*!
 @method    beginOOBBTPpairing
 @abstract  Begins OOBBBPT pairing from the iOS device
 */
- (CAMReturnVoid*)beginOOBBTPpairing;

@end
