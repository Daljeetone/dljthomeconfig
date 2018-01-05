//
//  CAMIdentityServices.h
//  coreautomationd
//
//  Created by John Blackwell on 10/13/14.
//
//

#import "CAMReturnValues.h"

#define kCAMIdentityServicesShortName ids

@protocol CAMIdentityServices
@optional
-(CAMReturnBool*)startService;
-(CAMReturnDictionary*)sendMessage:(NSDictionary*)message withPriority:(NSNumber*)priority timeout:(NSNumber*)timeout;
-(CAMReturnArray*)receivedMessages;
-(CAMReturnArray*)clearReceivedMessages;
-(CAMReturnDictionary*)idsDevices;

/*!
 @method   enableTextMessageForwarding:(NSNumber*)enable withiCloudDeviceUUID:(NSString*)deviceUUID
 @abstract Enable/Disable Text Message Forwarding on a iCloud Device. Provide device Unique ID.
 @discussion  Toggles device switch under Settings->iMessage->Text Message Forwarding. This will only work, if you are signed-in using 2-Factor Authentication(HSA2) enabled Apple ID. An Apple ID with Credit Card verified, supports 2-Factor Authentication(HSA2). HSA2 on an AppleID can be first-time configured by going to Settings->iCloud->Apple ID->Password & Security, and enabling 2-Factor Authentication. (Follow the questions on screen to get it configured).
 */
-(CAMReturnBool*)enableTextMessageForwarding:(NSNumber*)enable withiCloudDeviceUUID:(NSString*)deviceUUID;

/*!
 @method     enableCallsOnOtherDevice:(NSNumber *)enable withTimeout:(NSNumber *)timeout
 @abstract   Enable/Disable Call on Other Device functionality(Relay).
 @discussion Toggles master switch under Settings->Phone->Calls On Other Device. FT and iCloud sign-in is required.
 */
-(CAMReturnBool*)enableCallsOnOtherDevice:(NSNumber *)enable withTimeout:(NSNumber *)timeout;

/*!
 @method     enableCallsOnOtherDevice:(NSNumber *)enable withiCloudDeviceUUID:(NSString *)deviceUUID withTimeout:(NSNumber*)timeout
 @abstract   Enable/Disable Call on Other Device functionality(Relay). Controls Call Relay per device.
 @discussion Toggles master switch under Settings->Phone->Calls On Other Device.This will only work, if you are signed-in using 2-Factor Authentication(HSA2) enabled Apple ID. An Apple ID with Credit Card verified, supports 2-Factor Authentication(HSA2). HSA2 on an AppleID can be first-time configured by going to Settings->iCloud->Apple ID->Password & Security, and enabling 2-Factor Authentication. (Follow the questions on screen to get it configured). FT and iCloud sign-in is required.
 */
-(CAMReturnBool*)enableCallsOnOtherDevice:(NSNumber *)enable withiCloudDeviceUUID:(NSString *)deviceUUID withTimeout:(NSNumber*)timeout;

/*!
 @method   smsRelayIDSDevices
 @abstract Get All IDS Devices registered under SMS Relay IDS Service.
 */
-(CAMReturnDictionary*)smsRelayIDSDevices;

/*!
 @method   callRelayIDSDevices
 @abstract Get All IDS Devices registered under Call Relay(Phone Continuity) IDS Service.
 */
-(CAMReturnDictionary*)callRelayIDSDevices;
@end
