//
//  CAMAsync.h
//  coreautomationd
//
//	This module is use to test CoreAutomation Async feature in live and stress environment.
//	This proxy has no other purpose.
//
//  Created by Chen Huang on 10/2/15.
//
//

#ifndef CAMAsync_h
#define CAMAsync_h

#import <Foundation/Foundation.h>

#import "CAMReturnValues.h"

#define kCAMAsyncShortName async

@protocol CAMAsync <NSObject>
@optional

#pragma mark - Async Utility
/**
 *  Enable Async protocol when transfer information between host and device
 *
 *  @return CAMReturnVoid
 */
- (CAMReturnVoid *)enableAsyncMode;

/**
 *  Disable Async protocol when transfer information between host and device.
 *
 *  @discussion both host side and device should disable Async protocol in order to communicate successfully. This is usually taken care of by the host side.
 *
 *  @return CAMReturnVoid
 */
- (CAMReturnVoid *)disableAsyncMode;

/**
 *  Whether async protocol is used.
 *
 *  @return CAMReturnBool
 */
- (CAMReturnBool *)isAsyncModeEnabled;

#pragma mark - Notification
/**
 *  Register for notification.
 *
 *  @discussion Only registered notification will be delivered.
 *
 *  @param name name of the notification.
 *
 *  @return CAMReturnBool If notification is registered successfully, YES will be returned otherwise NO.
 */
- (CAMReturnBool *)registerForNotification:(NSString *)name;

/**
 *  Deregister a notification
 *
 *  @param name name of the notification
 *
 *  @return If notification is deregistered successfully, YES will be returned otherwise NO.
 */
- (CAMReturnBool *)deregisterForNotification:(NSString *)name;

/**
 *  Register all notification
 *
 *  @return If registered successfully, YES will be returned otherwise No.
 */
- (CAMReturnBool *)registerForAllNotifications;

/**
 *  Deregistered all notifications
 *
 *  @return If deregistered successfully, YES will be returned, otherwise NO.
 */
- (CAMReturnBool *)deregisterForAllNotifications;

/**
 *  Get currently registered notifications
 *
 *  @return An array of notifications currently registered.
 */
- (CAMReturnArray *)currentlyRegisteredNotifications;


#pragma mark - Test & Debug
/**
 *  Testing Only
 *  Repeatly send data with interval. Data is sent directly through lockdown channel.
 *
 *  @param data    data to send
 *  @param seconds interval between repeats in seconds
 *  @param times   the number of repeats. Each repeat send one data throuhg lockdown channel.
 *
 *  @return CAMReturnVoid
 */
- (CAMReturnVoid *)send:(NSData *)data withInterval:(NSNumber *)seconds andRepeat:(NSNumber *)times;

/**
 *  Testing Only
 *  Send data. Data is sent directly through lockdown channel.
 *
 *  @param data data to send
 *
 *  @return CAMReturnVoid
 */
- (CAMReturnVoid *)send:(NSData *)data;

/**
 *  Testing Only
 *	Post async notification without using CAMDAsyncUtility. Async notification is directly serialized into binary plist format.
 *  It's then sent directly through lockdown channel.
 *
 *  @param notification NSNotification to send
 *
 *  @return CAMReturnVoid
 */
- (CAMReturnVoid *)postNotification:(NSNotification*)notification;

/**
 *  Testing Only
 *	Post async notification without using CAMDAsyncUtility. Async notification is directly serialized into binary plist format.
 *  It's then sent directly through lockdown channel.
 *
 *  @param name notification name
 *	@param userinfo extra information with this notification.
 *
 *  @return CAMReturnVoid
 */
- (CAMReturnVoid *)postNotificationWithName:(NSString *)name andUserInfo:(NSDictionary *)userinfo;

/**
 *  Testing Only
 *  Repeatly post asyn notification without using CAMDAsyncUtility.
 *
 *  @param times    number of times to repeat
 *  @param name     notification name
 *  @param userinfo extra information with this notification
 *
 *  @return CAMReturnVoid
 */
- (CAMReturnVoid *)repeat:(NSNumber *)times notificationWithName:(NSString *)name andUserInfo:(NSDictionary *)userinfo;

/**
 *  Testing Only
 *  Post a notification with large footprint for testing purpose.
 *
 *  @return CAMReturnVoid
 */
- (CAMReturnVoid *)postLargeNotification;

/**
 *  Testing Only
 *  Post Async notification using CAMDAsyncUtility.
 *
 *  @param name     name of the notification
 *  @param userinfo extra info for the notification
 *
 *  @return CAMReturnVoid
 */
- (CAMReturnVoid *)postAsyncNotification:(NSString *)name andUserInfo:(NSDictionary *)userinfo;

/**
 *  Testing Only
 *  Repeatly sending async notification using CAMDAsyncUtility
 *
 *  @param times    The number of times to repeat
 *  @param name     notification name
 *  @param userinfo extra information with this notification
 *
 *  @return CAMReturnVoid
 */
- (CAMReturnVoid *)repeat:(NSNumber *)times asyncNotificationWithName:(NSString *)name andUserInfo:(NSDictionary *)userinfo;

/**
 *  Testing Only
 *  Post a notification with name "AsyncNotification_Bluetooth_PairingPasskeyRequest" with userinfo set to @{"passkey": "123456"}
 *
 *  @return CAMReturnVoid
 */
- (CAMReturnVoid *)postNotificationSample;

@end


#endif /* CAMAsync_h */
