//
//  CAMCarPlay.h
//  coreautomationd
//
//  Created by Chris Whitney on 8/22/16.
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CAMReturnValues.h"

#define kCAMCarPlayShortName	carPlay

@protocol CAMCarPlay
@optional

/*!
 @brief A boolean value indicating if CarPlay might be available on this hardware.
 */
- (CAMReturnBool *)isCarPlayCapable;


/*!
 @brief A boolean value indicating if CarPlay is allowed by the restrictions and Siri configuration.
 */
- (CAMReturnBool *)isCarPlayAllowed;


/*!
 @brief An array representing the saved vehicles, such as might appear in Settings > General > CarPlay.

 @discussion The array contains dictionary representations of the vehicles. Each dictionary may contain values for:
    "identifier" : CarKit identifier
    "vehicleName" : display name
    "isPaired" : the setting for "allow while locked" (wired) or "use CarPlay" (wireless)
    "accessoryProtocols" : CarKit's cached values for the iAP2 ExternalAccessory protocols declared by the accessory
    "bluetoothAddress" : Bluetooth MAC formatted in colon-separated hexadecimal
    "carplayWiFiUUID" : CarKit's identifier for vehicle's corresponding Wi-Fi network
 */
- (CAMReturnArray *)allSavedVehicles;


/*!
 @brief Change the "allow while locked" (for wired) or "use CarPlay" (for wireless) configuration for a vehicle.
 
 @discussion The identifier should be the value for the "identifier" key in a dictionary returned by -allSavedVehicles.
*/
- (CAMReturnVoid *)setPaired:(NSNumber *)isPaired forVehicleWithIdentifier:(NSString *)vehicleID;


/*!
 @brief Creates a CarKit record for a new wireless CarPlay vehicle.

 @discussion A Bluetooth Classic pairing must already exist with the vehicle. You can create that pairing using CAMBluetooth's -pairWithDeviceAddress:pincode:forService:. The saved vehicle will be
 */
- (CAMReturnVoid *)saveVehicleWithName:(NSString *)name bluetoothAddress:(NSString *)bluetoothAddress;


/*!
 @brief Removes a CarKit record for a vehicle.

 @discussion The identifier should be the value for the "identifier" key in a dictionary returned by -allSavedVehicles.
 */
- (CAMReturnVoid *)removeSavedVehicleWithIdentifier:(NSString *)vehicleID;

@end
