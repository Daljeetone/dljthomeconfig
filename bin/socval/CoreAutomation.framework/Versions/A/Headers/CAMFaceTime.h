//
//  CAMFaceTime.h
//  CoreAutomation
//
//  Created by John Blackwell on 1/9/12.
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CAMReturnValues.h"

#define kCAMFaceTimeShortName faceTime

@protocol CAMFaceTime
@optional

/*!
 @method     faceTimeWithAddress:waitForActive:withTimeout:
 @abstract   Start a FaceTime call with another FaceTime address.
 @discussion The device's screen must be unlocked due to privacy restrictions.
 */
- (CAMReturnVoid*)faceTimeWithAddress:(NSString*)address waitForActive:(NSNumber*)wait withTimeout:(NSNumber*)timeout;

/*!
 @method     faceTimeAudioWithAddress:waitForActive:withTimeout:
 @abstract   Start a FaceTime Audio call with another FaceTime address. All of the below methods will work with a FaceTime Audio call.
 @discussion The device's screen must be unlocked due to privacy restrictions.
 */
- (CAMReturnVoid*)faceTimeAudioWithAddress:(NSString*)address waitForActive:(NSNumber*)wait withTimeout:(NSNumber*)timeout;

/*!
 @method     answerFaceTimeWithAddress:waitForActive:withTimeout:
 @abstract   Answer an incoming FaceTime call.
 */
- (CAMReturnVoid*)answerFaceTimeFromAddress:(NSString*)address waitForActive:(NSNumber*)wait withTimeout:(NSNumber*)timeout;

/*!
 @method     waitForFaceTimeWithAddress:withCallStatus:withTimeout:
 @abstract   Wait for an incoming FaceTime call.
 @discussion Call Status values: Idle=0, Active=1, Held=2, Sending=3, Ringing=4, Disconnected=5
 */
- (CAMReturnVoid*)waitForFaceTimeWithAddress:(NSString*)address withCallStatus:(NSNumber*)status withTimeout:(NSNumber*)timeout;

/*!
 @method     endFaceTimeWithAddress:waitForDisconnect:withTimeout:
 @abstract   End an active FaceTime call.
 */
- (CAMReturnVoid*)endFaceTimeWith:(NSString*)address waitForDisconnect:(NSNumber*)wait withTimeout:(NSNumber*)timeout;

/*!
 @method     endAllFaceTimeAndWaitForDisconnect:withTimeout:
 @abstract   End all active FaceTime calls and wait for every call to disconnect.
 */
- (CAMReturnVoid*)endAllFaceTimeAndWaitForDisconnect:(NSNumber*)wait withTimeout:(NSNumber*)timeout;

/*!
 @method     activeFaceTimeCount
 @abstract   Get the number of currently active FaceTime calls.
 @return     The number of active FaceTime calls.
 */
- (CAMReturnInteger*)activeFaceTimeCount;

/*!
 @method     totalFaceTimeCount
 @abstract   Get the total number of FaceTime calls seen by the device during the current coreautomationd session. This value is the sum of incoming and outgoing calls.
 @return     The number of total FaceTime calls seen.
 */
- (CAMReturnInteger*)totalFaceTimeCount;

/*!
 @method    allCalls
 @abstract  Get all facetime calls.
 @return    An array of calls.
 */
- (CAMReturnArray *)allCalls;

/*!
 @method    toggleFTPhoneNumberAccountService
 @abstract  Enable FT Phone Number based account.
 @return    Returns True if FT Service is completely enabled.
 */
- (CAMReturnBool*)toggleFTPhoneNumberAccountService:(NSNumber*)timeout;

/*!
 @method     enableFT
 @abstract   Using Apple ID sign-in or sign-out of FT.
 @discussion enable=0, Signs-out the AppleID account from FT. Sign-out does not require password.
 @return     Returns True if requested sign-in or sign-out operation is successful.
 */
- (CAMReturnBool*)enableFT:(NSNumber*)enable withAppleID:(NSString*)appleID withPassword:(NSString*)password withTimeout:(NSNumber*)timeout;

/*!
 @method     isAccountOperational
 @abstract   Checks if an Account is Operational.
 @discussion accountID should be empty for checking Phone number based FT registration.
 @return     Returns True if FT Service for the account is Operational.
 */
- (CAMReturnBool*)isAccountOperational:(NSString*)accountID;

/*!
 @method     getSignedInFTAccounts
 @abstract   Get Signed-in FT Accounts.
 @discussion Includes all account showing up in Settings->FaceTime (You Can be Reached list)
 @return     List of FT Accounts caller-ID.
 */
- (CAMReturnArray *)getSignedInFTAccounts;

/*!
 @method     callerID;
 @abstract   Get Caller ID of the FT Account in effect.
 @discussion UI equivalent of Settings->FaceTime (Caller ID Selected)
 @return     Caller ID string.
 */
- (CAMReturnString *)callerID;
@end
