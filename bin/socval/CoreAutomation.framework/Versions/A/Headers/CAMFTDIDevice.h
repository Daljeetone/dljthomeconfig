//
//  CAMFTDIDevice.h
//  CoreAutomation
//
//  Created by Matt Massicotte on 3/8/11.
//  Copyright 2011 Apple, Inc. All rights reserved.
//

#import "CAMUSBDevice.h"
#import <IOKit/usb/IOUSBLib.h>

/*!
 @enum CAMFTDIDeviceMPSSEBitBangMode
 @discussion FTDI bit bang mode enum.
 */
enum _CAMFTDIDeviceMPSSEBitBangMode {
  CAMFTDIDeviceMPSSEBitBangModeCBUS = 0x20
};
typedef enum _CAMFTDIDeviceMPSSEBitBangMode CAMFTDIDeviceMPSSEBitBangMode;

/*!
 @enum CAMFTDIDevicePin
 @discussion FTDI device pin.
 */
enum _CAMFTDIDevicePin {
  CAMFTDIDevicePinCBUS2 = 0x4
};
typedef enum _CAMFTDIDevicePin CAMFTDIDevicePin;

/*!
 @interface CAMFTDIDevice
 @discussion FTDI device.
 */
@interface CAMFTDIDevice : CAMUSBDevice {
}

/*!
 @method setBitmask
 @discussion Sets the bit mask.
 @param mask
	Bit mask.
 @param mode
	Bit bang mode.
 */
- (void)setBitmask:(uint8_t)mask forMode:(CAMFTDIDeviceMPSSEBitBangMode)mode;

/*!
 @method jtagReset
 @discussion Resets the jtag.
 */
- (void)jtagReset;

@end
