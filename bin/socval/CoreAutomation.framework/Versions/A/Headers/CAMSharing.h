//
//  CAMSharing.h
//  coreautomationd
//
//  Leanne Huang
//
//  Copyright © 2016 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CAMReturnValues.h"

#define kCAMSharingShortName sharing

@protocol CAMSharing <NSObject>
@optional

/*!
 @method     attemptAutoUnlock
 @abstract   Attempt an Auto Unlock with any set up nearby devices.
 */
- (CAMReturnBool *)attemptAutoUnlock;

/*!
 @method     attemptAutoUnlock
 @abstract   Interate through all eligible devices and try enable them for Auto Unlock
 */
- (CAMReturnArray *)listEligibleDevices;
- (CAMReturnBool *)enableDevice:(NSNumber *)deviceIndex WithPasscode:(NSString *)passcode;
- (CAMReturnBool *)disableDevice:(NSNumber *)deviceIndex;
- (CAMReturnVoid *)autoUnlockOccurredReset;
- (CAMReturnBool *)autoUnlockOccurred;
- (CAMReturnBool *)enableAllDevicesWithPasscode:(NSString *)passcode;
- (CAMReturnDictionary *)attemptAutoUnlockWithResults;
- (CAMReturnBool *)writeClipboard:(NSString *)myString;
- (CAMReturnString *)readClipboard;

/*!
 @method     proximityDiscoveredDevices:timeout
 @abstract   discover proximity devices (B188s)
 @param      timeout timeout duration in seconds
 @return     dictionary of devices
 */
- (CAMReturnDictionary *)proximityDiscoveredDevices:(NSNumber *)timeout;

/*!
 @method     nearbyactionDiscoveredDevices:timeout
 @abstract   discover nearby action devices (B238s)
 @param      timeout timeout duration in seconds
 @return     dictionary of devices
 */
- (CAMReturnDictionary *)nearbyactionDiscoveredDevices:(NSNumber *)timeout;

/*!
 @method     startAppleTVSetupSessionWithPeerUUID:uuid
 @abstract   Start tap to setup pairing session with an AppleTV
 @param      uuid discovered by proximityDiscoveredDevices
 @return     True if succeeded, False otherwise.
 */
- (CAMReturnBool *)startAppleTVSetupSessionWithPeerUUID:(NSString*)uuid;

/*!
 @method     startB238SetupSessionWithPeerUUID:uuid withPin:pin
 @abstract   Start tap to setup pairing session with B238
 @param      uuid discovered by nearbyactionDiscoveredDevices
 @param      pin last four digit of the B238's serial number
 @return     a dictionary with timing results
 */
- (CAMReturnBool *)startB238SetupSessionWithPeerUUID:(NSString*)uuid withPin:(NSString*)pin;

/*!
 @method     startB238SetupService
 @abstract   Start tap to setup service on B238
 @return     True if succeeded, False otherwise.
 */
- (CAMReturnBool *)startB238SetupService;

/*!
 @method     startB238SetupService
 @abstract   Start tap to setup service on B238
 @return     True if succeeded, False otherwise.
 */
- (CAMReturnBool *)stopB238SetupService;

/*!
 @method     waitForNotificationAlert:withTimeout:
 @abstract   Wait for a BulletinBoard Alert.
 @param      matchAlertInfo . BulletinBoard sectionID string to lookout for. Usually its in the form of com.apple.mobilephone, com.apple.MobileSMS etc.
 @discussion sectionID string(if unknown) can be retrieved by sending alert notifications and fetching the alert notification detail by CAM API sharing().fetchNotificationAlerts(). The output will have list of Alerts. Match the alert message and its sectionID. Use this sectionID for your subsequent calls to this API.
 @return     Bulletin Board alert dictionary containing the following keys: @"message", @"date", @"sectionID", @"title", @"publicationDate", @"expirationDate", @"inertWhenLocked", @"loading", @"turnsOnDisplay", @"clearable", @"allowsAddingToLockScreenWhenUnlocked",@"allowsAutomaticRemovalFromLockScreen", @"threadID", @"visuallyIndicatesWhenDateIsInFuture"
 */
- (CAMReturnDictionary *)waitForNotificationAlert:(NSString *)matchAlertInfo withTimeout:(NSNumber *)timeout;

/*!
 @method     fetchNotificationAlerts:
 @abstract   Fetches the list of BulletinBoard alerts, which are also consumed by Notification Center and Springboard. This API is equivalent to that of reading Notification Center.
 @return     List of Bulletin Board alerts. Each alert has the following keys:: @"message", @"date", @"sectionID", @"title", @"publicationDate", @"expirationDate", @"inertWhenLocked", @"loading", @"turnsOnDisplay", @"clearable", @"allowsAddingToLockScreenWhenUnlocked",@"allowsAutomaticRemovalFromLockScreen", @"threadID", @"visuallyIndicatesWhenDateIsInFuture"
 */
- (CAMReturnDictionary *)fetchNotificationAlerts:(NSNumber*)timeout;

@end

