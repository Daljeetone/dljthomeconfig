//
//  CAMCapabilities.h
//  CoreAutomation
//
//  Created by Chris Whitney on 12/21/11.
//  Copyright (c) 2011 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CAMReturnValues.h"

#define kCAMCapabilitiesShortName capabilities

@protocol CAMCapabilities
@optional
/*!
 @method valueForGraphicsServicesCapability:
 @abstract Ask Graphics Services for the value of a capabiltity key.
 @return Returns an entry in the SpringBoard capability plist. Returns nil if the current device doesn't have the capability.
 */
- (CAMReturn*)valueForGraphicsServicesCapability:(NSString*)capability;

/*!
 @method hasGraphicsServicesCapability:
 @abstract Ask Graphics Services if a capability key is both present and enabled.
 @return Returns YES if a capability or restrction is present and enabled.
 */
- (CAMReturnBool*)hasGraphicsServicesCapability:(NSString*)capability;

/*!
 @method valueForMobileGestaltCapability:
 @abstract Ask Mobile Gestalt for the value of a capability key.
 @return Returns an object representing the value or nil (along with an error) if the capability key was not found.
 */
- (CAMReturn*)valueForMobileGestaltCapability:(NSString*)capability;


/*!
 @method hasWiFi
 @abstract Ask Mobile WiFi if the device has WiFi.
 @return Returns YES if the device has WiFi.
 */
- (CAMReturnBool*)hasWiFi;

/*!
 @method supportsWiFiRanging
 @abstract Asks WiFiManager is device supports WiFiRanging
 @return Returns YES is the device supports WiFiRanging
 */
- (CAMReturnBool*)supportsWiFiRanging;

/*!
 @method supportsVenice
 @abstract Ask Mobile Gestalt for the value of venice capabiltity key.
 @return Returns YES if the device supports venice.
 */
- (CAMReturnBool*)supportsVenice;

/*!
 @method supportsMMS
 @abstract Ask Mobile Gestalt if the device supports MMS.
 @return Returns YES if the device supports MMS.
 */
- (CAMReturnBool*)supportsMMS;

/*!
 @method isEmulatedDevice
 @abstract Ask Mobile Gestalt if this device is an emulated device.
 @return Returns YES if the device is an emulated device.
 */
- (CAMReturnBool*)isEmulatedDevice;

/*!
 @method isAppleTV
 @abstract Ask Mobile Gestalt if this device is an Apple TV.
 @return Returns YES if the device is an Apple TV.
 */
- (CAMReturnBool*)isAppleTV;

/*!
 @method isiPad
 @abstract Ask Mobile Gestalt if this device is an iPad.
 @return Returns YES if the device is an iPad.
 */
- (CAMReturnBool*)isiPad;

/*!
 @method isiPhone
 @abstract Ask Mobile Gestalt if this device is an iPhone.
 @return Returns YES if the device is an iPhone.
 */
- (CAMReturnBool*)isiPhone;

/*!
 @method isiPod
 @abstract Ask Mobile Gestalt if this device is an iPod.
 @return Returns YES if the device is an iPod.
 */
- (CAMReturnBool*)isiPod;

/*!
 @method isAppleWatch
 @abstract Ask Mobile Gestalt if this device is an AppleWatch.
 @return Returns YES if the device is an AppleWatch.
 */
- (CAMReturnBool*)isAppleWatch;

/*!
 @method isWatchCompanion
 @abstract Ask Mobile Gestalt if this device can act as a companion device to an AppleWatch.
 @return Returns YES if the device can be a watch companion.
 */
- (CAMReturnBool*)isWatchCompanion;

/*!
 @method hasBaseband
 @abstract Ask Mobile Gestalt if this device has a baseband.
 @return Returns YES if the device has baseband.
 */
- (CAMReturnBool*)hasBaseband;

/*!
 @method hasSEP
 @abstract Ask Mobile Gestalt if this device is SEP enabled.
 @return Returns YES if the device supports SEP.
 */
- (CAMReturnBool*)hasSEP;

/*!
 @method hasMesa
 @abstract Ask Mobile Gestalt if this device has Mesa.
 @return Returns YES if the device has Mesa.
 */
- (CAMReturnBool*)hasMesa;

/*!
 @method hasNFC
 @abstract Ask Mobile Gestalt if this device has an NFC radio.
 @return Returns YES if the device has NFC.
 */
- (CAMReturnBool*)hasNFC;

/*!
 @method hasSecureElement
 @abstract Ask Mobile Gestalt if this device has a secure element.
 @return Returns YES if the device has a secure element.
 */
- (CAMReturnBool*)hasSecureElement;

/*!
 @method getSecureElementType
 @abstract Ask NFHardwareManager for the secure element type.
 @return Returns PROD, DEV or if no secure element, UNKNOWN.
 */
- (CAMReturnString*)secureElementType;

/*!
 @method hasLightningConnector
 @abstract Ask Mobile Gestalt if this device supports a 9 pin (E75) connector
 @return Returns YES if the device supports a 9 pin (E75) connector
 */
- (CAMReturnBool*)hasLightningConnector;

/*!
 @method supportsAppStore
 @abstract Ask Mobile Gestalt if this device supports App Store.
 @return Returns YES if the device supports App Store.
 */
- (CAMReturnBool*)supportsAppStore;

/*!
 @method supportsAssistant
 @abstract Ask Mobile Gestalt if this device supports Siri.
 @return Returns YES if the device supports App Store.
 */
- (CAMReturnBool*)supportsAssistant;

/*!
 @method basebandChipset
 @abstract Ask Mobile Gestalt about Baseband Chipset identifier.
 @discussion Returned identifier can be used to identify Baseband vendors.
 @return Returns Baseband Chipset identifier string
 */
- (CAMReturnString*)basebandChipset;

@end
