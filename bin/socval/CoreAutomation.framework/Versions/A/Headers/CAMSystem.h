//
//  CAMSystem.h
//  coreautomationd
//
//  Created by john gale on 7/25/12.
//  Copyright 2011 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CAMReturnValues.h"

#define kCAMSystemShortName system

@protocol CAMSystem
@optional

/*!
 @method	averageTemp
 @abstract	Gets the average temperature of all sensors on the device, for those sensors returning positive floats.
 @return	Returns the average temperature of all sensors on the device.
*/
- (CAMReturnDouble *)averageTemp;

/*!
 @method	allSensors
 @abstract	Gets the ID, Description, and temperature of all sensors on the device.
 @return	Returns an array of dictionaries with keys @"ID", @"description", @"temperature"
*/
- (CAMReturnArray *)allSensors;

/*!
 @method	cpuTemp
 @abstract	Attempts to find the temperature of the cpu proximity sensor. Tries to be smart about matching known SoC names, like "M2" or "H4A".
 @return	Returns a dictionary with a key of the sensor Description, and a value of that sensor's temperature.
*/
- (CAMReturnDictionary *)cpuTemp;

/*!
 @method    batteryLevel
 @return    Returns the device's battery level
*/
- (CAMReturnDouble *)batteryLevel;

/*!
 @method    batteryLevelAccessory
 @param     matchIdentifierKey accessory identifier key. Use ALL for all accesories.
 @return    Returns array of attached accessories' battery levels
 */
- (CAMReturnArray *) batteryLevelAccessory:(NSString*) matchIdentifierKey;

/*!
 @method    batteryState
 @return    Returns the device's battery state
 @abstract  0 = UIDeviceBatteryStateUnknown,
            1 = UIDeviceBatteryStateUnplugged,   // on battery, discharging
            2 = UIDeviceBatteryStateCharging,    // plugged in, less than 100%
            3 = UIDeviceBatteryStateFull,        // plugged in, at 100%
 */
- (CAMReturnInteger *)batteryState;

/*!
 @method    hardwareRevision
 @return    Returns the device's hardware build revision (e.g. EVT, DVT, MP)
 @abstract  Attempts to find the device's hardware build revision with the SysCfg memory dump.  Returns things like EVT or DVT, or MP if non revision is found (suggesting a near-enough-to-production model).  Returns n/a if no data is returned from the SysCfg query.
 */
- (CAMReturnString *)hardwareRevision;

/*!
 @method    thermalPressureLevel
 @return    Returns the device's OSThermalPressureLevel
 @abstract  Values defined in enum OSThermalPressureLevel in header <libkern/OSThermalNotification.h>
 */
-(CAMReturnInteger *)thermalPressureLevel;

@end
