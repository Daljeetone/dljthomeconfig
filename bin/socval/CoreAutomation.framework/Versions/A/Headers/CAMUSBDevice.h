//
//  CAMUSBDevice.h
//  CoreAutomation
//
//  Created by Matt Massicotte on 3/6/10.
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import "CAMIOService.h"
#import <IOKit/usb/IOUSBLib.h>

/*!
 @interface CAMUSBDevice
 @discussion CAM USB device.
 */
@interface CAMUSBDevice : CAMIOService {
    uint32_t locationID;
    uint16_t productID;
    uint16_t vendorID;
    NSString *usbSerialNumber;
    NSDictionary *usbProperties;

    IOUSBDeviceInterface **interface;
    BOOL opened;
}

/*!
 @method initWithService
 @discussion Initialize USB device with service.
 @param io_service
	IO Service.
 */
- (instancetype)initWithService:(io_service_t)io_service;

/*!
 @method deviceWithSerialNumber
 @discussion Gets USB device with serial number.
 @param serial
	Serial number.
 */
+ (instancetype)deviceWithSerialNumber:(NSString *)serial;

/*!
 @method deviceWithLocationID
 @discussion Gets USB device with Location ID
 @param location_id Location ID
 Serial number.
 */
+ (instancetype)deviceWithLocationID:(uint32_t)location_id;

/*!
 @property locationID
 @discussion Location ID of the USB device.
 */
@property(assign, readonly) uint32_t locationID;

/*!
 @property vendorID
 @discussion Vendor ID of USB device.
 */
@property(assign, readonly) uint16_t vendorID;

/*!
 @property productID
 @discussion Produce ID of USB device.
 */
@property(assign, readonly) uint16_t productID;

/*!
 @property serialNumber
 @discussion Serial number of USB device.
 */
@property(copy, readonly) NSString *serialNumber;

/*!
 @property properties
 @discussion USB properties of the device.
 */
@property(strong, readonly) NSDictionary *properties;

/*!
 @property children
 @discussion Children USB devices.
 */
@property(strong, readonly) NSArray *children;

/*!
 @property parent
 @discussion Parent USB device.
 */
@property(strong, readonly) CAMUSBDevice *parent;

/*!
 @method allDevicesMatchingDictionary
 @discussion Gets devices matching the dictionary options.
 */
+ (NSDictionary *)allDevicesMatchingDictionary;

/*!
 @method allDevicesMatchingDictionaryWithVendorID
 @discussion Gets USB device matching dictionary and Vendor ID.
 @param vendorID
	Vendor ID of USB device.
 @param productID
	Product ID of USB device.
 @result
	NSDictionary of USB devices.
 */
+ (NSDictionary *)allDevicesMatchingDictionaryWithVendorID:(NSInteger)vendorID andWithProductID:(NSInteger)productID;

/*!
 @method openInterface
 @discussion Opens USB device interface.
 */
- (void)openInterface;

/*!
 @method closeInterface
 @discussion Closes USB device interface.
 */
- (void)closeInterface;

/*!
 @discussion Attempts to determine if the USB device is stale or not by getting the PlugInInterface for the service.
 */
@property(NS_NONATOMIC_IOSONLY, getter=isStale, readonly) BOOL stale;

/*!
 @discussion Attempts to determine if the USB device is responding to requests. In most cases you should be able to use this as an isPanicked() method; timeout of 5s.
 */
@property(NS_NONATOMIC_IOSONLY, getter=isResponsive, readonly) BOOL responsive;

/*!
 @method reset
 @discussion Resets the USB device interface.
 */
- (void)reset;

/*!
 @method issueDeviceRequest
 @discussion Issues a USB device request.
 @param request
	USB device request issued.
 */
- (void)issueDeviceRequest:(IOUSBDevRequest)request;

@end
