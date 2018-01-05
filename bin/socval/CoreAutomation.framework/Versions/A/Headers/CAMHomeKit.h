//
//  CAMHomeKit
//  CoreAutomation
//
//  Created by Chen Xu on 2/19/14.
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CAMReturnValues.h"

#define kCAMHomeKitShortName homekit

@protocol CAMHomeKit
@optional

extern NSString* const kLocationNameKey;
extern NSString* const kLocationType;
extern NSString* const kLocationLatitudeKey;
extern NSString* const kLocationLongitudeKey;
extern NSString* const kLocationRadiusKey;
extern NSString* const kBeaconNameKey;
extern NSString* const kBeaconUUIDKey;
extern NSString* const kBeaconMajorKey;
extern NSString* const kBeaconMinorKey;
extern NSString* const kTriggerOnEntryKey;
extern NSString* const kTriggerOnExitKey;
extern NSString* const kLocationTypeBeacon;
extern NSString* const kLocationTypeCoordinates;

- (CAMReturnBool *)setupHomeManager;

// Homes

/*!
 @method    addHome
 @abstract  Add a home with specified name with timeout
 @param     homeName - Name of home to add
 */
- (CAMReturnVoid *)addHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    removeHome
 @abstract  Remove a home with specified name with timeout
 @param     homeName - Name of home to remove
 */
- (CAMReturnVoid *)removeHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    homes
 @abstract  Returns string form of array with home names
 @return	String of home names
 */
- (CAMReturnString *)homes;

/*!
 @method    homeExists
 @abstract  Checks whether a home exists
 @param     homeName - Name of home to check
 @return	Returns whether home with provided name exists
 */
- (CAMReturnBool *)homeExists:(NSString *)homeName;

/*!
 @method    roomForEntireHome
 @abstract  Returns name for the entire house
 @param     homeName - Name of home
 @return	Returns the room for the entire house
 */
- (CAMReturnString *)roomForEntireHome:(NSString *)homeName;

/*!
 @method    setPrimaryHome
 @abstract  Sets the home with name provided to be the primary home
 @param     homeName - Name of home
 */
- (CAMReturnVoid *)setPrimaryHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    renameHome
 @abstract  Renames home
 @param     homeName - Current home name
			newName - New home name
 */
- (CAMReturnVoid *)renameHome:(NSString *)homeName newName:(NSString *)newName withTimeout:(NSNumber *)timeout;

/*!
 @method    primaryHome
 @abstract  Returns the primary home name
 @return	Returns the primary home name
 */
- (CAMReturnString *)primaryHome;

// Rooms
/*!
 @method    addRoom
 @abstract  Adds room to home
 @param     roomName - Name of room to add
			homeName - Name of home to add room to
 */
- (CAMReturnVoid *)addRoom:(NSString *)roomName toHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    removeRoom
 @abstract  Removes room from home
 @param     roomName - Name of room to remove
			homeName - Name of home to remove room from
 */
- (CAMReturnVoid *)removeRoom:(NSString *)roomName fromHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    roomExists
 @abstract  Checks whether room exists in home
 @param     roomName - Name of room
			homeName - Name of home
 @return	Returns whether room exists in home
 */
- (CAMReturnBool *)roomExists:(NSString *)roomName inHome:(NSString *)homeName;


/*!
 @method    renameRoom
 @abstract  Renames room
 @param     roomName - Current room name
			newName - New room name
			homeName - Name of home
 */
- (CAMReturnVoid *)renameRoom:(NSString *)roomName newName:(NSString *)newName inHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

// Zones

/*!
 @method    addZone
 @abstract  Adds zone to home
 @param     zoneName - Name of zone to addd
			homeName - Name of home
 */
- (CAMReturnVoid *)addZone:(NSString *)zoneName toHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    removeZone
 @abstract  Removes zone from home
 @param     zoneName - Name of zone to remove
			homeName - Name of home
 */
- (CAMReturnVoid *)removeZone:(NSString *)zoneName fromHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    zoneExists
 @abstract  Checks whether zone exists in home
 @param     zoneName - Zone name
			homeName - Name of home
 @return	Returns whether zone exists in home
 */
- (CAMReturnBool *)zoneExists:(NSString *)zoneName inHome:(NSString *)homeName;

/*!
 @method    renameZone
 @abstract  Renames zone in home
 @param     zoneName - Current zone name
			newName - New zone name
			homeName - Name of home
 */
- (CAMReturnVoid *)renameZone:(NSString *)zoneName newName:(NSString *)newName inHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    addRoom
 @abstract  Adds room to zone in home
 @param     roomName - Name of room to add
			zoneName - Name of zone to add room to
			homeName - Name of home which contains zone
 */
- (CAMReturnVoid *)addRoom:(NSString *)roomName toZone:(NSString *)zoneName inHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    removeRoom
 @abstract  Removes room from zone in home
 @param     roomName - Name of room to remove
			zoneName - Name of zone to remove room from
			homeName - Name of home which contains zone
 */
- (CAMReturnVoid *)removeRoom:(NSString *)roomName fromZone:(NSString *)zoneName inHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    roomExists
 @abstract  Checks whether room exists in zone in home
 @param     roomName - Name of room to check
			zoneName - Name of zone which contains room
			homeName - Name of home which contains zone
 @return	Returns whether the room exists
 */
- (CAMReturnBool *)roomExists:(NSString *)roomName inZone:(NSString *)zoneName inHome:(NSString *)homeName;

// Action Sets

/*!
 @method    addActionSet
 @abstract  Adds action set to home
 @param     actionSetName - Name of action set to add
			homeName - Name of home
 */
- (CAMReturnVoid *)addActionSet:(NSString *)actionSetName toHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    removeActionSet
 @abstract  Removes action set from home
 @param     actionSetName - Name of action set to remove
			homeName - Name of home
 */
- (CAMReturnVoid *)removeActionSet:(NSString *)actionSetName fromHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    actionSetExists
 @abstract  Checks whether action set exists in home
 @param		actionSetName - Name of action set
			homeName - Name of home
 @return	Returns whether action set exists in home
 */
- (CAMReturnBool *)actionSetExists:(NSString *)actionSetName inHome:(NSString *)homeName;

/*!
 @method    renameActionSet
 @abstract  Renames action set in home
 @param		actionSetName - Current action set name
			newName - New action set name
			homeName - Name of home
 */
- (CAMReturnVoid *)renameActionSet:(NSString *)actionSetName newName:(NSString *)newName inHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    executeActionSet
 @abstract  Executes action set
 @param		actionSetName - Name of action set to execute
			homeName - Name of home
 */
- (CAMReturnVoid *)executeActionSet:(NSString *)actionSetName inHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

// Characteristic Write Actions

/*!
 @method    addCharacteristicWriteActions
 @abstract  Adds multiple characteristic write actions to action set
 @param		characteristicWriteActions - Dictionary of characteristic write actions to add in the format {characteristicType:value}
			actionSetName - Action set name to add write actions to
			serviceName - Name of service which contains action set
			accessoryName - Name of accessory which contains service
			homeName - Name of home
 */
- (CAMReturnVoid *)addCharacteristicWriteActions:(NSDictionary *)characteristicWriteActions actionSet:(NSString *)actionSetName service:(NSString *)serviceName accessory:(NSString *)accessoryName home:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    addCharacteristicWriteAction
 @abstract  Adds individual characteristic write action to action set
 @param		value - Value of write action
			characteristicType - Characteristic type of write action (i.e. - public.hap.characteristic.on)
			actionSetName - Action set name to add write actions to
			serviceName - Name of service which contains action set
			accessoryName - Name of accessory which contains service
			homeName - Name of home
 */
- (CAMReturnVoid *)addCharacteristicWriteAction:(id)value characteristic:(NSString *)characteristicType actionSet:(NSString *)actionSetName service:(NSString *)serviceName accessory:(NSString *)accessoryName home:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    removeCharacteristicWriteActionFromActionSet
 @abstract  Removes individual characteristic write action from action set
 @param		characteristicType - Characteristic type of write action (i.e. - public.hap.characteristic.on)
			actionSetName - Action set name to add write actions to
			serviceName - Name of service which contains action set
			accessoryName - Name of accessory which contains service
			homeName - Name of home
 */
- (CAMReturnVoid *)removeCharacteristicWriteActionFromActionSet:(NSString *)actionSetName characteristicType:(NSString *)characteristicType service:(NSString *)serviceName accessory:(NSString *)accessoryName home:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    replaceCharacteristicWriteAction
 @abstract  Replaces individual characteristic write action with new write action.  Only the value parameter should be updated.  All other parameters: characteristicType, actionSetName, serviceName, accessoryName, and homeName are used to find the write action.  If a write action with these specifications does not exist, we will fail.  We will not try to create a new write action if one does not already exist.
 @param		value - Value of write action to update
			characteristicType - Characteristic type of write action (i.e. - public.hap.characteristic.on)
			actionSetName - Action set name to add write actions to
			serviceName - Name of service which contains action set
			accessoryName - Name of accessory which contains service
			homeName - Name of home
 */
- (CAMReturnVoid *)replaceCharacteristicWriteAction:(id)value characteristicType:(NSString *)characteristicType actionSet:(NSString *)actionSetName service:(NSString *)serviceName accessory:(NSString *)accessoryName home:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    characteristicWriteActionExists
 @abstract  Checks whether characteristic action set exists
 @param		value - Value of write action
			characteristicType - Characteristic type of write action (i.e. - public.hap.characteristic.on)
			actionSetName - Action set name to add write actions to
			serviceName - Name of service which contains action set
			accessoryName - Name of accessory which contains service
			homeName - Name of home
 @return	Returns whether characteristic write action exists in home

 */
- (CAMReturnBool *)characteristicWriteActionExists:(id)value characteristicType:(NSString *)characteristicType actionSet:(NSString *)actionSetName service:(NSString *)serviceName accessory:(NSString *)accessoryName home:(NSString *)homeName;

// Users

/*!
 @method    addUser
 @abstract  Adds user to home
 @param		userName - Name of user to add
			homeName - Name of home
			confirmation - Whether to display confirmation for adding user
			isAdministrator - Whether user should be added as an administrator
 */
- (CAMReturnVoid *)addUser:(NSString *)userName toHome:(NSString *)homeName confirmation:(NSNumber *)confirmation isAdministrator:(NSNumber *)isAdministrator withTimeout:(NSNumber *)timeout;

/*!
 @method    removeUser
 @abstract  Removes user from home
 @param		userName - Name of user to remove
			homeName - Name of home
			confirmation - Whether to display confirmation for removing user
 */
- (CAMReturnVoid *)removeUser:(NSString *)userName fromHome:(NSString *)homeName confirmation:(NSNumber *)confirmation withTimeout:(NSNumber *)timeout;

/*!
 @method    userExists
 @abstract  Checks whether user exists in home
 @param		userName - Name of user to check
			homeName - Name of home
 @return	Returns whether the user exists in home
 */
- (CAMReturnBool *)userExists:(NSString *)userName inHome:(NSString *)homeName;

// Accessories

/*!
 @method    addAccessory
 @abstract  Searches for and adds accessory with no password specified.  Results in an error if the accessory cannot 
			be found or pairing fails.
 @param
			accessoryName - Name of accessory
			homeName - Name of home
 */
- (CAMReturnBool *)addAccessory:(NSString *)accessoryName toHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    addAccessory
 @abstract  Searches for and adds accessory with password specified.  Results in an error if the accessory cannot
 be found or pairing fails.
 @param
			accessoryName - Name of accessory
			homeName - Name of home
 */
- (CAMReturnBool *)addAccessory:(NSString *)accessoryName password:(NSString *)password toHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    timedAddAccessory
 @abstract  Searches for and adds accessory with password specified.  Results in an error if the accessory cannot
 be found or pairing fails. Returns a dictionary with the pairing time
 @param     accessoryName Name of accessory
            password Password of accessory
            homeName Name of home
            timeout Timeout before failing
 */
- (CAMReturnDictionary *)timedAddAccessory:(NSString *)accessoryName password:(NSString *)password toHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    isAccessoryDiscoverable
 @abstract  Searches for the accessory with the provided name. Returns true if found during browse
 @param
            accessoryName - Name of accessory

 */
- (CAMReturnBool *)isAccessoryDiscoverable:(NSString *)accessoryName withTimeout:(NSNumber *)timeout;

/*!
 @method    removeAccessory
 @abstract  Removes accessory from home
 @param
			accessoryName - Name of accessory
			homeName - Name of home
 */
- (CAMReturnVoid *)removeAccessory:(NSString *)accessoryName fromHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    isAccessoryReachable
 @abstract  Checks whether accessory is reachable or not
 @param
			accessoryName - Name of accessory
			homeName - Name of home
 */
- (CAMReturnBool *)isAccessoryReachable:(NSString *)accessoryName inHome:(NSString *)homeName;

/*!
 @method    isAccessoryBlocked
 @abstract  Checks whether accessory is blocked or not
 @param
            accessoryName - Name of accessory
            homeName - Name of home
 */
- (CAMReturnBool *)isAccessoryBlocked:(NSString *)accessoryName inHome:(NSString *)homeName;

/*!
 @method    unblockAccessory
 @abstract  Unblock previously blocked accessory
 @param
            accessoryName - Name of accessory
            homeName - Name of home
 */
- (CAMReturnVoid *)unblockAccessory:(NSString *)accessoryName inHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    accessoryExists
 @abstract  Checks whether an accessory exists within a home
 @param
			accessoryName - Name of accessory
			homeName - Name of home
 @return	Returns whether the accessory exists in room
 */
- (CAMReturnBool *)accessoryExists:(NSString *)accessoryName inHome:(NSString *)homeName;

/*!
 @method    setAccessoryRoom
 @abstract  Sets the room for a given accessory
 @param
			roomName - Name of room
			accessoryName - Name of accessory
 */
- (CAMReturnVoid *)setAccessoryRoom:(NSString *)roomName accessory:(NSString *)accessoryName inHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    accessoryRoom
 @abstract  Gets the room for a given accessory
 @param
			accessoryName - Name of accessory
 @return	Returns the room for a given accessory
 */
- (CAMReturnString *)accessoryRoom:(NSString *)accessoryName inHome:(NSString *)homeName;

/*!
 @method    renameAccessory
 @abstract  Renames the accessory
 @param
			accessoryName - Current name of accessory
			newName - New name of accessory
			homeName - Name of home
 */
- (CAMReturnVoid *)renameAccessory:(NSString *)accessoryName name:(NSString *)newName inHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

// Service Groups
/*!
 @method    addServiceGroup
 @abstract  Adds service group to home
 @param
			serviceGroupName - Name of service group
			homeName - Name of home
 */
- (CAMReturnVoid *)addServiceGroup:(NSString *)serviceGroupName toHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    removeServiceGroup
 @abstract  Remove a service group from a home
 @param
			serviceGroupName - Name of service group
			homeName - Name of home
 */
- (CAMReturnVoid *)removeServiceGroup:(NSString *)serviceGroupName fromHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    serviceGroupExists
 @abstract  Checks whether a service group exists
 @param
			serviceGroupName - Name of service group
			homeName - Name of home
 @return	Returns whether a service group exists
 */
- (CAMReturnBool *)serviceGroupExists:(NSString *)serviceGroupName inHome:(NSString *)homeName;

/*!
 @method    renameServiceGroup
 @abstract  Renames a service group
 @param
			serviceGroupName - Current name of service group
			newName - New name of service group
			homeName - Name of home
 */
- (CAMReturnVoid *)renameServiceGroup:(NSString *)serviceGroupName newName:(NSString *)newName inHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    addService
 @abstract  Adds a service to a service group
 @param
			serviceName - Name of service
			serviceGroupName - Name of service group
			accessoryName - Name of accessory
			homeName - Name of home
 */
- (CAMReturnVoid *)addService:(NSString *)serviceName toServiceGroup:(NSString *)serviceGroupName accessory:(NSString *)accessoryName inHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    removeService
 @abstract  Removes a service from a service group
 @param
			serviceName - Name of service
			serviceGroupName - Name of service group
			accessoryName - Name of accessory
			homeName - Name of home
 */
- (CAMReturnVoid *)removeService:(NSString *)serviceName fromServiceGroup:(NSString *)serviceGroupName accessory:(NSString *)accessoryName inHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    serviceExists
 @abstract  Checks whether a service exists
 @param
			serviceName - Name of service
			serviceGroupName - Name of service group
			homeName - Name of home
 @return	Returns whether a service exists in a service group
 */
- (CAMReturnBool *)serviceExists:(NSString *)serviceName inServiceGroup:(NSString *)serviceGroupName home:(NSString *)homeName;

// Service
/*!
 @method    setServiceName
 @abstract  Sets the service name at an index in the accessory
 @param
			serviceName - Name of service
			index - Index of service in accessory
			accessoryName - Name of accessory
			homeName - Name of home
 */
- (CAMReturnVoid *)setServiceName:(NSString *)serviceName index:(NSNumber *)index accessory:(NSString *)accessoryName inHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    setServiceName
 @abstract  Sets the service name by uuid in the accessory
 @param
            serviceName - Name to rename service to
            uuid - Unique identifer of service
            accessoryName - Name of accessory
            homeName - Name of home
 */
- (CAMReturnVoid *)setServiceName:(NSString *)serviceName withUUID:(NSString *)uuid accessory:(NSString *)accessoryName inHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    serviceName
 @abstract  Gets the service name at an index in the accessory
 @param
			index - Index of service in accessory
			accessoryName - Name of accessory
			homeName - Name of home
 */
- (CAMReturnString *)serviceName:(NSNumber *)index accessory:(NSString *)accessoryName inHome:(NSString *)homeName;


/*!
 @method    setServiceAssociatedServiceType
 @abstract  Sets the service associated service type
 @param
            associatedServiceType - Associated service type
            index - Index of service in accessory
            accessoryName - Name of accessory
            homeName - Name of home
 */
- (CAMReturnVoid *)setServiceAssociatedServiceType:(NSString *)associatedServiceType index:(NSNumber *)index accessory:(NSString *)accessoryName inHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    serviceAssociatedServiceType
 @abstract  Gets the service associated service type
 @param
            index - Index of service in accessory
            accessoryName - Name of accessory
            homeName - Name of home
 */
- (CAMReturnString *)serviceAssociatedServiceType:(NSNumber *)index accessory:(NSString *)accessoryName inHome:(NSString *)homeName;

// Characteristics

/*!
 @method    writeValue
 @abstract  Writes a value to a characteristic by service type
 @param
            value - Value to write
            characteristicType - Type of characteristic (i.e. - public.hap.characteristic.on)
            serviceType - Type of service
            accessoryName - Name of accessory
            homeName - Name of home
 */
- (CAMReturnVoid *)writeValue:(id)value characteristic:(NSString *)characteristicType serviceType:(NSString *)serviceType accessory:(NSString *)accessoryName home:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    writeValue
 @abstract  Writes a value to a characteristic
 @param
            value - Value to write
            characteristicType - Type of characteristic (i.e. - public.hap.characteristic.on)
            serviceName - Name of service
            accessoryName - Name of accessory
            homeName - Name of home
 */
- (CAMReturnVoid *)writeValue:(id)value characteristic:(NSString *)characteristicType service:(NSString *)serviceName accessory:(NSString *)accessoryName home:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    writeValue
 @abstract  Writes a value to a characteristic
 @param
            value - Value to write
            characteristicUUID = UUID of characteristic
            serviceUUID - UUID of service
            accessoryName - Name of accessory
            homeName - Name of home
 */
- (CAMReturnVoid *)writeValue:(id)value characteristic:(NSString *)characteristicUUID serviceUUID:(NSString *)serviceUUID accessory:(NSString *)accessoryName home:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    readCharacteristic
 @abstract  Reads a value of a characteristic by service type
 @param
            characteristicType - Type of characteristic (i.e. - public.hap.characteristic.on)
            serviceType - Type of service (UUID form)
            accessoryName - Name of accessory
            homeName - Name of home
 */
- (CAMReturn *)readCharacteristic:(NSString *)characteristicType serviceType:(NSString *)serviceType accessory:(NSString *)accessoryName home:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    readCharacteristic
 @abstract  Reads a value of a characteristic
 @param
			characteristicType - Type of characteristic (i.e. - public.hap.characteristic.on)
			serviceName - Name of service
			accessoryName - Name of accessory
			homeName - Name of home
 */
- (CAMReturn *)readCharacteristic:(NSString *)characteristicType service:(NSString *)serviceName accessory:(NSString *)accessoryName home:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    readCharacteristic
 @abstract  Reads a value of a characteristic
 @param
            characteristicUUID = UUID of characteristic
            serviceUUID - UUID of service
            accessoryName - Name of accessory
            homeName - Name of home
 */
- (CAMReturn *)readCharacteristic:(NSString *)characteristicUUID serviceUUID:(NSString *)serviceUUID accessory:(NSString *)accessoryName home:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    valueForCharacteristic
 @abstract  Returns the value of a HMCharacteristic object
 @param
            characteristicType - Type of characteristic (i.e. on - 00000025-0000-1000-8000-0026BB765291)
            serviceName - Name of service
            accessoryName - Name of accessory
            homeName - Name of home
 */
- (CAMReturn *)valueForCharacteristic:(NSString *)characteristicType service:(NSString *)serviceName accessory:(NSString *)accessoryName home:(NSString *)homeName;

/*!
 @method    enableNotification
 @abstract  Enable notification of a characteristic
 @param
            enable - NSNumber representing a BOOL for notification state
            characteristicType - Type of characteristic (i.e. - public.hap.characteristic.on)
            serviceType - Type of service
            accessoryName - Name of accessory
            homeName - Name of home
 */
- (CAMReturnVoid *)enableNotification:(NSNumber *)enable characteristic:(NSString *)characteristicType serviceType:(NSString *)serviceType accessory:(NSString *)accessoryName home:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    enableNotification
 @abstract  Enable notification of a characteristic
 @param
            enable - NSNumber representing a BOOL for notification state
            characteristicType - Type of characteristic (i.e. - public.hap.characteristic.on)
            serviceName - Name of service
            accessoryName - Name of accessory
            homeName - Name of home
 */
- (CAMReturnVoid *)enableNotification:(NSNumber *)enable characteristic:(NSString *)characteristicType service:(NSString *)serviceName accessory:(NSString *)accessoryName home:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    isNotificationEnabled
 @abstract  Check for notification of a characteristic
 @param
            characteristicType - Type of characteristic (i.e. - public.hap.characteristic.on)
            serviceName - Type of service
            accessoryName - Name of accessory
            homeName - Name of home
 */
- (CAMReturnBool *)isNotificationEnabled:(NSString *)characteristicType serviceType:(NSString *)serviceType accessory:(NSString *)accessoryName home:(NSString *)homeName;

/*!
 @method    isNotificationEnabled
 @abstract  Check for notification of a characteristic
 @param
            characteristicType - Type of characteristic (i.e. - public.hap.characteristic.on)
            serviceName - Name of service
            accessoryName - Name of accessory
            homeName - Name of home
 */
- (CAMReturnBool *)isNotificationEnabled:(NSString *)characteristicType service:(NSString *)serviceName accessory:(NSString *)accessoryName home:(NSString *)homeName;

// Triggers

/*!
 @method    addTimerTrigger
 @abstract  Adds a timer trigger
 @param
			triggerName - Name of trigger
			dateString - Date of trigger, in format MM/DD/YYYY hh:mm:ss (i.e. - 01/02/2013 01:02:03)
			interval - Interval of timer
			timeZoneString - String representation of TimeZone abbreviations (i.e. - CST, full list at [NSTimeZone abbreviationDictionary])
			homeName - Name of home
 */
- (CAMReturnVoid *)addTimerTrigger:(NSString *)triggerName date:(NSString *)dateString interval:(NSNumber *)interval timeZone:(NSString *)timeZoneString toHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;


/*!
 @method    addTimerTrigger
 @abstract  Adds a timer trigger
 @param
            triggerName - Name of trigger
            events - Array of dictionaries each representing an event to trigger:
                    {
                        kHMAccessoryNameKey :  Accessory name,
                        kHMServiceNameKey : Service name,
                        kHMCharacteristicTypeKey : Characteristic type;
                        kHMCharacteristicValueKey : Characteristic value to trigger;
                    }
            conditions - Predicate - Format: before sunset | after sunset | after sunrise | before sunrise | before HH:mm | after HH:mm. Supported operators: -a and -o. Example: "after sunrise -o before 17:30"
            locations - Array of dictionaries each representing a location event dictionary, valid formats are:
                1.) Location based events
                        {
                            kHMLocationType :  kLocationTypeCoordinates,
                            kHMLocationNameKey : NSString of name,
                            kHMLocationLatitudeKey : NSNumber float of latitude ;
                            kHMLocationLongitudeKey : NSNumber float of longitude;
                            kHMLocationRadiusKey : NSNumber float of radius;
                            kHMTriggerOnEntryKey : NSNumber bool of whether to trigger on entry;
                            kHMTriggerOnExitKey NSNumber bool of whether to trigger on exit;
                        }
                2.) Beacon based events
                        {
                            kHMLocationType :  kLocationTypeBeacon,
                            kHMBeaconNameKey : NSString of beacon name;
                            kHMBeaconUUIDKey : NSString of beacon UUID;
                            kHMBeaconMajorKey : NSNumber integer of major;
                            kHMBeaconMinorKey : NSNumber integer of minor;
                            kHMTriggerOnEntryKey : NSNumber bool of whether to trigger on entry;
                            kHMTriggerOnExitKey NSNumber bool of whether to trigger on exit;
                        }
            homeName - Name of home
            timeout - Timeout
 */
- (CAMReturnVoid *)addEventTrigger:(NSString *)triggerName events:(NSArray *)events conditions:(NSString *)conditions locations:(NSArray *)locations toHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;
/*!
 @method    removeTrigger
 @abstract  Removes a trigger
 @param
			triggerName - Name of trigger
			homeName - Name of home
 */
- (CAMReturnVoid *)removeTrigger:(NSString *)triggerName fromHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    triggerExists
 @abstract  Checks whether a trigger exists
 @param
			triggerName - Name of trigger
			homeName - Name of home
 */
- (CAMReturnBool *)triggerExists:(NSString *)triggerName inHome:(NSString *)homeName;

/*!
 @method    addActionSet
 @abstract  Adds an action set to a trigger
 @param
			actionSetName - Name of action set
			triggerName - Name of trigger
			homeName - Name of home
 */
- (CAMReturnVoid *)addActionSet:(NSString *)actionSetName toTrigger:(NSString *)triggerName inHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    removeActionSet
 @abstract  Removes an action set to a trigger
 @param
			actionSetName - Name of action set
			triggerName - Name of trigger
			homeName - Name of home
 */
- (CAMReturnVoid *)removeActionSet:(NSString *)actionSetName fromTrigger:(NSString *)triggerName inHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    setTriggerState
 @abstract  Set the state of the trigger
 @param
			state - NSNumber representing a BOOL for trigger state
			triggerName - Name of trigger
			homeName - Name of home
 */
- (CAMReturnVoid *)setTriggerState:(NSNumber *)state forTrigger:(NSString *)triggerName inHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    actionSetExists
 @abstract  Checks whether an action set exists
 @param
			actionSetName - Name of action set
			triggerName - Name of trigger
			homeName - Name of home
 */
- (CAMReturnBool *)actionSetExists:(NSString *)actionSetName inTrigger:(NSString *)triggerName inHome:(NSString *)homeName;

/*!
 @method    enableTrigger
 @abstract  Enables trigger
 @param
			triggerName - Name of trigger
			homeName - Name of home
 */
- (CAMReturnVoid *)enableTrigger:(NSString *)triggerName inHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    disableTrigger
 @abstract  Disables trigger
 @param
			triggerName - Name of trigger
			homeName - Name of home
 */
- (CAMReturnVoid *)disableTrigger:(NSString *)triggerName inHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    triggerFireDate
 @abstract  Gets the trigger fire date
 @param
			triggerName - Name of trigger
			homeName - Name of home
 @return	Returns the trigger fire date in format MM/DD/YYYY hh:mm:ss (i.e. - 01/02/2013 01:02:03)
 */
- (CAMReturnString *)triggerFireDate:(NSString *)triggerName inHome:(NSString *)homeName;

/*!
 @method    triggerInterval
 @abstract  Gets the trigger time interval
 @param
			triggerName - Name of trigger
			homeName - Name of home
 @return	Returns the trigger time interval
 */
- (CAMReturnInteger *)triggerInterval:(NSString *)triggerName inHome:(NSString *)homeName;

/*!
 @method    triggerState
 @abstract  Gets the trigger state
 @param
			triggerName - Name of trigger
			homeName - Name of home
 @return	Returns the state of the trigger
 */
- (CAMReturnBool *)triggerState:(NSString *)triggerName inHome:(NSString *)homeName;

/*!
 @method    updateTimerTrigger
 @abstract  Updates the time zone of the trigger
 @param
			triggerName - Name of trigger
			timeZoneName - String representation of TimeZone abbreviations (i.e. - CST, full list at [NSTimeZone abbreviationDictionary])
			homeName - Name of home
 */
- (CAMReturnVoid *)updateTimerTrigger:(NSString *)triggerName timeZone:(NSString *)timeZoneName inHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    updateTimerTrigger
 @abstract  Updates the interval of the trigger
 @param
			triggerName - Name of trigger
			interval - Interval of the trigger
			homeName - Name of home
 */
- (CAMReturnVoid *)updateTimerTrigger:(NSString *)triggerName interval:(NSNumber *)interval inHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    updateTimerTrigger
 @abstract  Updates the interval of the trigger
 @param
			triggerName - Name of trigger
			fireDate - Fire date of the trigger in format MM/DD/YYYY hh:mm:ss (i.e. - 01/02/2013 01:02:03)
			homeName - Name of home
 */
- (CAMReturnVoid *)updateTimerTrigger:(NSString *)triggerName fireDate:(NSString *)dateString inHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    renameTrigger
 @abstract  Renames the trigger
 @param
			triggerName - Current name of trigger
			newName - New name of the trigger
			homeName - Name of home
 */
- (CAMReturnVoid *)renameTrigger:(NSString *)triggerName newName:(NSString *)newName inHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    resetConfiguration
 @abstract  Resets the configuration on the device
 @param
			shouldResetCloud - Whether or not to reset cloud data
 */
- (CAMReturnVoid *)resetConfiguration:(NSNumber *)shouldResetCloud withTimeout:(NSNumber *)timeout;

/*!
 @method    dumpAll
 @abstract  Dumps the current HomeKit info
 @return	Returns a string of current HomeKit info
 */
- (CAMReturnString *)dumpAll;

/*!
 @method    accessoryLayoutForHome
 @abstract  Dumps the accessory/service/characteristic layout in a parsable manner
 @return	Returns an array of all accessories in a home and their corresponding services/characteristic UUID's
 @param
            home - The name of the home to retrieve the layout for
 */
- (CAMReturnArray *)accessoryLayoutForHome:(NSString *)home;

/*!
 @method    isAccessoryBridged
 @abstract  Returns a bool indiciating if the accessory is bridged in the provided home
 @param
            accessoryName - The name of accessory to validate
            home - The name of the home to retrieve the layout for
 */
- (CAMReturnBool *)isAccessoryBridged:(NSString *)accessoryName forHome:(NSString *)home;

- (CAMReturnString *)bridgeForAccessory:(NSString *)accessoryName forHome:(NSString *)home;

/*!
 @method    inviteUsers
 @abstract  Returns a bool indiciating if the invites were sent successfully
 @param
 userIDs - User Names or emails (User name requires that they be in address book)
 home - The name of the home the invite is for
 */
- (CAMReturnVoid *)inviteUsers:(NSArray *)userIDs toHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    acceptInvite
 @abstract  Returns a bool indiciating if the invite was accepted
 @param
 senderUserID - the sender's user id or name (for name they must be in address book)
 home - The name of the home the invite is for
 @return	YES if successful, otherwise NO
 */
- (CAMReturnBool *)acceptInvite:(NSString *)senderUserID toHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    declineInvite
 @abstract  Returns a bool indiciating if the invite was declined
 @param
 senderUserID - the sender's user id or name (for name they must be in address book)
 home - The name of the home that the invite was for
 */
- (CAMReturnVoid *)declineInvite:(NSString *)senderUserID toHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    cancelInvite
 @abstract  Returns a bool indiciating if the invite was canceled
 @param
 inviteeUserID - the invitee's user id or name (for name they must be in address book)
 home - The name of the home that the invite was for
 */
- (CAMReturnVoid *)cancelInvite:(NSString *)inviteeUserID toHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method    inviteExists
 @abstract  Returns a bool indiciating if the invite exists
 @param
 inviter - the sender's user id or name (for name they must be in address book)
 home - The name of the home that the invite is for
 */
- (CAMReturnBool *)inviteExists:(NSString *)inviter toHome:(NSString *)homeName;

/*!
 @method    enableRemoteAccess
 @abstract  Returns a bool indiciating if the invite exists
 @param
 homeName - Name of the home
 enable - Bool indicating enable (True) or disable (False)
 */
- (CAMReturnBool *)enableRemoteAccess:(NSString *)homeName enable:(BOOL)enable;

/*!
 @method    getInviteStatus
 @abstract  Returns a string indicating the status of the invite
 @param
 inviteeUserID - name of the user
 homeName - Name of the home
 */
- (CAMReturnString *)getInviteStatus:(NSString *)inviteeUserID toHome:(NSString *)homeName;

/*!
 @method    addAccessory
 @abstract  Browses for accessories for a fixed amount of time and adds accessory with no password specified.
 @param
 accessoryName - Name of accessory
 homeName - Name of home
 browseTime - Seconds to browse
 timeout - Seconds to wait for addAccessory completion before timing out.
 */
- (CAMReturnBool *)addAccessory:(NSString *)accessoryName toHome:(NSString *)homeName withBrowseTime:(NSNumber *)time andTimeout:(NSNumber *)timeout;

/*!
 @method    addAccessory
 @abstract  Browses for accessories for a fixed amount of time and adds accessory with no password specified.
 @param
 accessoryName - Name of accessory
 password - password for accessory
 homeName - Name of home
 browseTime - Seconds to browse
 timeout - Seconds to wait for addAccessory completion before timing out.
 */
- (CAMReturnBool *)addAccessory:(NSString *)accessoryName password:(NSString *)password toHome:(NSString *)homeName withBrowseTime:(NSNumber *)time andTimeout:(NSNumber *)timeout;

/*!
 @method    updateAdministratorAccess
 @abstract  Change whether a user has adminstrator access to a home or not.
 @param
 userName - Name of user.
 homeName - Name of the home.
 */
- (CAMReturnBool *)updateAdministratorAccess:(NSString *)userName inHome:(NSString *)homeName isAdministrator:(NSNumber *)adminAccess;

/*!
 @method    updateRemoteAccess
 @abstract  Change whether a user has remote access to a home or not.
 @param
 userName - Name of user
 homeName - Name of the home.
 */
- (CAMReturnBool *)updateRemoteAccess:(NSString *)userName inHome:(NSString *)homeName enableRemoteAccess:(NSNumber *)remoteAccess;

/*!
 @method    isAdministrtor
 @abstract  Check whether a user has administrator access to a home or not. Return true for access, false for no access.
 @param
 userName - Name of user
 homeName - Name of the home.
 */
- (CAMReturnBool *)isAdministrator:(NSString *)userName inHome:(NSString *)homeName;

/*!
 @method    hasRemoteAccess
 @abstract  Check whether a user has remote access to a home or not. Return true for access, false for no access.
 @param
 userName - Name of user.
 homeName - Name of the home.
 */
- (CAMReturnBool *)hasRemoteAccess:(NSString *)userName inHome:(NSString *)homeName;


/*!
 @method    getResidentNames
 @abstract  Returns an array with all the names of the resident devices for a given home.
 @param
 homeName - Name of home.
 */
- (CAMReturnArray *)getResidentNames:(NSString *)homeName;

/*!
 @method startCameraStream
 @abstract Starts the camera stream and waits for completion for a specified timeout interval.
 @param
 accessoryName - Name of the accessory.
 homeName - Name of the home.
 timeout - max time we wait for the semaphore to be signaled.
 */
- (CAMReturnBool *)startCameraStream:(NSString *)accessoryName inHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method startCameraStream
 @abstract Starts the camera stream and waits for completion for a specified timeout interval. This function is needed because of HomeKit's confusing design choice. startCameraStream does not expect error. Any start stream error is handled by didStopStreamWithError delegate.
 @param
 accessoryName - Name of the accessory.
 homeName - Name of the home.
 timeout - max time we wait for the semaphore to be signaled.
 */
- (CAMReturnBool *)startCameraStreamExpectError:(NSString *)accessoryName inHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method stopCameraStream
 @abstract Stops the camera stream and waits for completion for a specified timeout interval.
 @param
 accessoryName - Name of the accessory.
 homeName - Name of the home.
 timeout - max time we wait for the semaphore to be signaled.
 */
- (CAMReturnBool *)stopCameraStream:(NSString *)accessoryName inHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method takeSnapshot
 @abstract Takes a snapshot and waits for completion for a specified timeout interval.
 @param
 accessoryName - Name of the accessory.
 homeName - Name of the home.
 timeout - max time we wait for the semaphore to be signaled.
 */
- (CAMReturnBool *)takeSnapshot:(NSString *)accessoryName inHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

/*!
 @method startCameraStream
 @abstract Returns a string specifying the state of the stream. Streaming, NotStreaming, Starting, Stopping.
 @param
 accessoryName - Name of the accessory.
 homeName - Name of the home.
 */
- (CAMReturnString *)getStreamState:(NSString *)accessoryName inHome:(NSString *)homeName;

/*!
 @method didTriggerUpdate
 @abstract Returns True or False specifying whether the given trigger fired or was updated.
 @param
 triggerName - Name of the trigger.
 homeName - Name of the home.
 timeout - Max time that we allow for the trigger to fire or be updated.
 */
- (CAMReturnBool *)didTriggerUpdate:(NSString *)triggerName inHome:(NSString *)homeName withTimeout:(NSNumber *)timeout;

@end
