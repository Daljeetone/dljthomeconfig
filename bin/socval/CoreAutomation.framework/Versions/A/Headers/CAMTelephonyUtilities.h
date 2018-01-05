//
//  CAMTelephonyUtilities.h
//  coreautomationd
//
//  Created by Roberto Mitma Castro on 5/30/15.
//  Copyright 2015 Apple Inc. All rights reserved.
//
//
#import "CAMReturnValues.h"
#define kCAMTelephonyUtilitiesShortName tu

@protocol CAMTelephonyUtilities
@optional

/*!
 @method     initiateFaceTimeCallWith:(NSString *)callee waitForActive:(NSNumber*)wait withTimeout:(NSNumber*)timeout
 @abstract   Initiates a FaceTime call and waits for the call to be active if the waitForActive flag is set to True. Calls need to be initiated from an unlocked device.
 @discussion Before attempting the call, on an iOS device, screen will be unlocked in this method. If screen unlock fails, this method will return False and the call will not be attempted.
 */
-(CAMReturnBool*)initiateFaceTimeCallWith:(NSString *)callee waitForActive:(NSNumber*)wait withTimeout:(NSNumber*)timeout ;

/*!
 @method     answerFaceTimeTCall
 @abstract   Answer an incoming FaceTime call and waits for the call to be active if the waitForActive flag is set to True
 */
-(CAMReturnBool*)answerFaceTimeCallFrom:(NSString*)caller waitForActive:(NSNumber*)wait withTimeout:(NSNumber*)timeout;

/*!
 @method     upgradeToFaceTimeCall:(NSNumber*)wait withTimeout:(NSNumber*)timeout
 @abstract   Upgrades an existing call to a FaceTime video call
 */
-(CAMReturnBool*)upgradeToFaceTimeCall:(NSNumber*)wait withTimeout:(NSNumber*)timeout;

/*!
 @method     toggleCamera
 @abstract   Toggles the camera during a FaceTime call
 */
-(CAMReturnVoid*)toggleCamera;

/*!
 @method     getCamera
 @abstract   Gets the current camera being used during a FaceTime call
 */
-(CAMReturnString*)getCamera;

/*!
 @method     disconnectFaceTimeCallWaitForDisconnect:(NSNumber*)wait withTimeout:(NSNumber*)timeout
 @abstract   Disconnects the current call and waits for the call to be disconnected if the waitForDisconnect flag is set to True
 */
-(CAMReturnBool*)disconnectFaceTimeCallWaitForDisconnect:(NSNumber*)wait withTimeout:(NSNumber*)timeout;

/*!
 @method     initiateFaceTimeAudioCallWith:(NSString *)callee waitForActive:(NSNumber*)wait withTimeout:(NSNumber*)timeout
 @abstract   Initiate a FaceTimeAudio call and waits for the call to be active if the waitForActive flag is set to True. Calls need to be initiated from an unlocked device.
 @discussion Before attempting the call, on an iOS device, screen will be unlocked in this method. If screen unlock fails, this method will return False and the call will not be attempted.
 */
-(CAMReturnBool*)initiateFaceTimeAudioCallWith:(NSString *)callee waitForActive:(NSNumber*)wait withTimeout:(NSNumber*)timeout;

/*!
 @method     answerFaceTimeAudioCallFrom:(NSString*)caller waitForActive:(NSNumber*)wait withTimeout:(NSNumber*)timeout
 @abstract   Answer an incoming FaceTimeAudio call and waits for the call to be active if the waitForActive flag is set to True
 */
-(CAMReturnBool*)answerFaceTimeAudioCallFrom:(NSString*)caller waitForActive:(NSNumber*)wait withTimeout:(NSNumber*)timeout;

/*!
 @method     Hold and answer FaceTime Audio Call.
 @abstract   Holds the current call and answers an incoming FaceTimeAudio. Waits for the call to be active if the waitForActive flag is set to True.
 */
-(CAMReturnBool*)holdAndAnswerFaceTimeAudioCallFrom:(NSString*)caller waitForActive:(NSNumber*)wait withTimeout:(NSNumber*)timeout;

/*!
 @method     disconnectFaceTimeAudioCallWaitForDisconnect:(NSNumber*)wait withTimeout:(NSNumber*)timeout
 @abstract   Disconnects the current call and waits for the call to be disconnected if the waitForDisconnect flag is set to True
 */
-(CAMReturnBool*)disconnectFaceTimeAudioCallWaitForDisconnect:(NSNumber*)wait withTimeout:(NSNumber*)timeout;

/*!
 @method     initiatePhoneContinuityCallWith:(NSString *)callee waitForActive:(NSNumber*)wait withTimeout:(NSNumber*)timeout
 @abstract   Initiate a Phone Continuity call and waits for the call to be active if the waitForActive flag is set to True. Calls need to be initiated from an unlocked device.
 @discussion Before attempting the call, on an iOS device, screen will be unlocked in this method. If screen unlock fails, this method will return False and the call will not be attempted.
 */
-(CAMReturnBool*)initiatePhoneContinuityCallWith:(NSString *)callee waitForActive:(NSNumber*)wait withTimeout:(NSNumber*)timeout;

/*!
 @method     answerPhoneContinuityCallFrom:(NSString*)caller waitForActive:(NSNumber*)wait withTimeout:(NSNumber*)timeout
 @abstract   Answer an incoming Phone Continuity call and waits for the call to be active if the waitForActive flag is set to True
 */
-(CAMReturnBool*)answerPhoneContinuityCallFrom:(NSString*)caller waitForActive:(NSNumber*)wait withTimeout:(NSNumber*)timeout;

/*!
 @method     Hold and answer Phone Continuity Call.
 @abstract   Holds current call and answer an incoming Phone Continuity call. Waits for the call to be active if the waitForActive flag is set to True
 */
-(CAMReturnBool*)holdAndAnswerPhoneContinuityCallFrom:(NSString*)caller waitForActive:(NSNumber*)wait withTimeout:(NSNumber*)timeout;

/*!
 @method     disconnectPhoneContinuityCallWaitForDisconnect:(NSNumber*)wait withTimeout:(NSNumber*)timeout
 @abstract   Disconnects the current call and waits for the call to be disconnected if the waitForDisconnect flag is set to True
 */
-(CAMReturnBool*)disconnectPhoneContinuityCallWaitForDisconnect:(NSNumber*)wait withTimeout:(NSNumber*)timeout;

/*!
 @method     initiateWifiCallWith:(NSString *)callee waitForActive:(NSNumber*)wait withTimeout:(NSNumber*)timeout
 @abstract   Initiates a WiFi call and waits for the call to be active if the waitForActive flag is set to True. Calls need to be initiated from an unlocked device.
 @discussion Before attempting the call, on an iOS device, screen will be unlocked in this method. If screen unlock fails, this method will return False and the call will not be attempted.
 */
-(CAMReturnBool*)initiateWifiCallWith:(NSString *)callee waitForActive:(NSNumber*)wait withTimeout:(NSNumber*)timeout;

/*!
 @method     answerWifiCallFrom:(NSString*)caller waitForActive:(NSNumber*)wait withTimeout:(NSNumber*)timeout
 @abstract   Answer an incoming Wifi call and waits for the call to be active if the waitForActive flag is set to True
 */
-(CAMReturnBool*)answerWifiCallFrom:(NSString*)caller waitForActive:(NSNumber*)wait withTimeout:(NSNumber*)timeout;

/*!
 @method     Hold and answer Wifi Call.
 @abstract   Holds current call and answer an incoming Wifi call. Waits for the call to be active if the waitForActive flag is set to True
 */
-(CAMReturnBool*)holdAndAnswerWifiCallFrom:(NSString*)caller waitForActive:(NSNumber*)wait withTimeout:(NSNumber*)timeout;

/*!
 @method     disconnectWifiCallWaitForDisconnect:(NSNumber*)wait withTimeout:(NSNumber*)timeout
 @abstract   Disconnects the current call and waits for the call to be disconnected if the waitForDisconnect flag is set to True
 */
-(CAMReturnBool*)disconnectWifiCallWaitForDisconnect:(NSNumber*)wait withTimeout:(NSNumber*)timeout;

/*!
 @method     initiateTelephonyCallWith:(NSString *)callee waitForActive:(NSNumber*)wait withTimeout:(NSNumber*)timeout
 @abstract   Initiates a Telephony call and waits for the call to be active if the waitForActive flag is set to True. Calls need to be initiated from an unlocked device.
 @discussion Before attempting the call, on an iOS device, screen will be unlocked in this method. If screen unlock fails, this method will return False and the call will not be attempted.
 */
-(CAMReturnBool*)initiateTelephonyCallWith:(NSString *)callee waitForActive:(NSNumber*)wait withTimeout:(NSNumber*)timeout;

/*!
 @method     initiateTelephonyCallOfAnyTypeWith:(NSString *)callee waitForActive:(NSNumber*)wait withTimeout:(NSNumber*)timeout
 @abstract   Initiates a Telephony call on any technology(CS/IMS-VoLTE/IMS-WiFi) and waits for the call to be active if the waitForActive flag is set to True
 @discussion This API will not check Telephony Call Type. Outgoing call could be CS, VoLTE or WiFi. This API do check if Call service provider is Telephony Type for validation..
 */
-(CAMReturnBool*)initiateTelephonyCallOfAnyTypeWith:(NSString *)callee waitForActive:(NSNumber*)wait withTimeout:(NSNumber*)timeout;

/*!
 @method     answerTelephonyCallFrom:(NSString*)caller waitForActive:(NSNumber*)wait withTimeout:(NSNumber*)timeout
 @abstract   Answer an incoming Telephony call and waits for the call to be active if the waitForActive flag is set to True
 */
-(CAMReturnBool*)answerTelephonyCallFrom:(NSString*)caller waitForActive:(NSNumber*)wait withTimeout:(NSNumber*)timeout;

/*!
 @method     answerTelephonyCallOfAnyTypeFrom:(NSString*)caller waitForActive:(NSNumber*)wait withTimeout:(NSNumber*)timeout withVerification:(NSNumber*)verify
 @abstract   Answer an incoming Telephony call on any technology(CS/IMS-VoLTE/IMS-WiFi) and waits for the call to be active if the waitForActive flag is set to True
 @discussion This API will not check Telephony Call Type. Incoming call could be CS, VoLTE or WiFi. This API do check if Call service provider is Telephony Type for validation.
 */
-(CAMReturnBool*)answerTelephonyCallOfAnyTypeFrom:(NSString*)caller waitForActive:(NSNumber*)wait withTimeout:(NSNumber*)timeout;

/*!
 @method     Hold and answer Telephony(CS) Call.
 @abstract   Holds current call and answer an incoming Telephony(CS) call. Waits for the call to be active if the waitForActive flag is set to True
 */
-(CAMReturnBool*)holdAndAnswerTelephonyCallFrom:(NSString*)caller waitForActive:(NSNumber*)wait withTimeout:(NSNumber*)timeout;

/*!
 @method     disconnectTelephonyCallWaitForDisconnect:(NSNumber*)wait withTimeout:(NSNumber*)timeout
 @abstract   Disconnects the current call and waits for the call to be disconnected if the waitForDisconnect flag is set to True
 */
-(CAMReturnBool*)disconnectTelephonyCallWaitForDisconnect:(NSNumber*)wait withTimeout:(NSNumber*)timeout;

/*!
 @method     Swap Calls
 @abstract   Swap calls if two calls exist
 */
-(CAMReturnBool*)swapCalls;

/*!
 @method     Merge Calls
 @abstract   Merges calls if two calls exist
 */
-(CAMReturnBool*)mergeCalls;

/*!
 @method    Active Call Type
 @abstract  Get the current active Call Type
 */
-(CAMReturnInteger*)getActiveCallType;

/*!
 @method    Active Call
 @abstract  Get the call information for the front most Active Call
 */
-(CAMReturnDictionary*)getActiveCall;

/*!
 @method    End Active Call And Answer Incoming Call
 @abstract  End Active Call And Answer Incoming Call
 */
-(CAMReturnBool*) endActiveAndAnswerCall;

/*!
 @method    End Held Call And Answer Incoming Call
 @abstract  End Held Call And Answer Incoming Call
 */
-(CAMReturnBool*) endHoldAndAnswerCall;

/*!
 @method    Hold/UnHold Current Call
 @abstract  Hold/Unhold the currect active call. Does not validate the call type.
*/
-(CAMReturnBool*)toggleHold;

/*!
 @method suppressRingtone
 @abstract Suppress Ringtone
*/
-(CAMReturnVoid*)suppressRingtone;

/*!
 @method muteUnmuteCall
 @abstrct Set Mute/Unmute the active Call
*/
-(CAMReturnBool*) toggleMute;

/*!
 @method waitForIncomingCall
 @abstract Wait for incoming call from remote party.
 @discussion Wait for incoming call from remote party identified with MDN or URL, until timeout.
 */
-(CAMReturnBool*)waitForIncomingCall:(NSString*)remoteURI withTimeout:(NSNumber*)timeout;

typedef NS_ENUM(NSInteger, TUActiveCallType) {
    TUActiveCallTypeUnknown = -1,
    TUActiveCallTypeTelephony = 0,
    TUActiveCallTypeFTAudio = 1,
    TUActiveCallTypeFTVideo = 2,
    TUActiveCallTypeWiFiCalling = 3,
    TUActiveCallTypeRelay = 4,
    TUActiveCallType3rdParty = 5,
    TUActiveCallTypeVoLTE = 6
};

/*!
 @method     getCurrentCallState
 @abstract   Returns the current state of a call
    NoCurrentCall = -1
    CallStatusIdle = 0,
    CallStatusActive = 1,
    CallStatusHeld = 2,
    CallStatusSending = 3,
    CallStatusRinging = 4,
    CallStatusDisconnecting = 5,
    CallStatusDisconnected = 6,
 */
-(CAMReturnInteger*)getCurrentCallState;

-(CAMReturnDictionary*)callProviders;

/*!
 @method     frontmostCallProviderContext
 @abstract   Returns the Provider Context in dictionary for the front most user facing call.
 */
-(CAMReturnDictionary*)frontmostCallProviderContext;

/*!
 @method     answerFaceTimeAndHold:(NSNumber*)wait withTimeout:(NSNumber*)timeout
 @abstract   Answers FaceTime video call on the Watch and then call is Held.
 @discussion The call is held, so that it can be answered on the paired Phone using answerFaceTimeOnHold::
*/
-(CAMReturnBool*)answerFaceTimeAndHold:(NSNumber*)wait withTimeout:(NSNumber*)timeout;

/*!
 @method     answerFaceTimeOnHold:(NSNumber*)timeout
 @abstract   Answers FaceTime video call On hold on the Phone.
 @discussion The call is put on Hold on the Phone from watch using answerFaceTimeAndHold:withTimeout
 */
-(CAMReturnBool*)answerFaceTimeOnHold:(NSNumber*)timeout;

/*!
 @method     initiate3rdPartyCallWith:(NSString *)callee waitForActive:(NSNumber*)wait withTimeout:(NSNumber*)timeout withProvider:(NSString*)identifier
 @abstract   Initiates a 3rd Party call and waits for the call to be active if the waitForActive flag is set to True. Calls need to be initiated with the unlock screen
 */
-(CAMReturnBool*)initiate3rdPartyCallWith:(NSString *)callee waitForActive:(NSNumber*)wait withTimeout:(NSNumber*)timeout withProvider:(NSString*)identifier;

/*!
 @method     answer3rdPartyCallFrom:(NSString*)caller waitForActive:(NSNumber*)wait withTimeout:(NSNumber*)timeout withProvider:(NSString*)identifier
 @abstract   Answer an incoming 3rd Party call and waits for the call to be active if the waitForActive flag is set to True
 */
-(CAMReturnBool*)answer3rdPartyCallFrom:(NSString*)caller waitForActive:(NSNumber*)wait withTimeout:(NSNumber*)timeout withProvider:(NSString*)identifier;

/*!
 @method     holdAndAnswer3rdPartyCallFrom:(NSString*)caller waitForActive:(NSNumber*)wait withTimeout:(NSNumber*)timeout withProvider:(NSString*)identifier
 @abstract   Holds current call and answer an incoming 3rd Party call. Waits for the call to be active if the waitForActive flag is set to True
 */
-(CAMReturnBool*)holdAndAnswer3rdPartyCallFrom:(NSString*)caller waitForActive:(NSNumber*)wait withTimeout:(NSNumber*)timeout withProvider:(NSString*)identifier;

/*!
 @method     disconnect3rdPartyCallWaitForDisconnect:(NSNumber*)wait withTimeout:(NSNumber*)timeout withProvider:(NSString*)identifier
 @abstract   Disconnects the current 3rd Party call and waits for the call to be disconnected if the waitForDisconnect flag is set to True
 */
-(CAMReturnBool*)disconnect3rdPartyCallWaitForDisconnect:(NSNumber*)wait withTimeout:(NSNumber*)timeout;

/*!
 @method     -(CAMReturnBool*)declineAllIncomingCalls:(NSNumber*)wait withTimeout:(NSNumber*)timeout
 @abstract   Declines the current incoming audio and video calls and waits up until the timeout for the call to disconnect
 */
-(CAMReturnBool*)declineAllIncomingCalls:(NSNumber*)wait withTimeout:(NSNumber*)timeout;

/*!
 @method     -(CAMReturnBool*)declineIncomingAudioCall:(NSNumber*)wait withTimeout:(NSNumber*)timeout
 @abstract   Declines the current incoming audio call and waits up until the timeout for the call to disconnect
 */
-(CAMReturnBool*)declineIncomingAudioCall:(NSNumber*)wait withTimeout:(NSNumber*)timeout;

/*!
 @method     -(CAMReturnBool*)declineIncomingVideoCall:(NSNumber*)wait withTimeout:(NSNumber*)timeout
 @abstract   Declines the current incoming video call and waits up until the timeout for the call to disconnect
 */
-(CAMReturnBool*)declineIncomingVideoCall:(NSNumber*)wait withTimeout:(NSNumber*)timeout;

/*!
 @method     getAllCalls
 @abstract   Get all calls of any state and type currently available.
*/
-(CAMReturnArray*)getAllCalls;

/*!
 @method     callCount
 @abstract   Get number of calls available, of any type and state.
*/
-(CAMReturnInteger*)callCount;

/*!
 @method     endAllCalls
 @abstract   Ends all Calls in the device irrespective of it state and type.
 */
-(CAMReturnVoid*)endAllCalls;

/*!
 @method     removeAllCallInfo
 @abstract   Clears the call info dictionary
 */
-(CAMReturnVoid*)removeAllCallInfo;

/*!
 @method     -(CAMReturnDictionary*)getCallInfo;
 @abstract   Returns a dictionary that contains information about all calls
 */
-(CAMReturnDictionary*)getCallInfo;

/*!
 @method     -(CAMReturnBool *)sendDTMFKey
 @abstract   Sends DTMF keycodes for an active call only.
 @discussion Valid DTMF keys are '*', '#, 0 to 9, A,B,C,D.
             Caller is responsible for passing pause/delay and valid DTMF key.
 @return     @YES on success, @NO on failure.
*/
-(CAMReturnBool *)sendDTMFKey:(NSNumber *)key;

/*!
 @method     getCallerIDForActiveCall
 @abstract   Gets the Caller ID on display for the front most Active Call.
 @return     Caller ID String.
*/
-(CAMReturnString *)getCallerIDForActiveCall;

/*!
 @method     privateConversationWith
 @abstract   In a conference call start private conversation with callUUID.
 @param      callUUID - Call identifier, that can be fetched from tu().getAllCalls().value()[callindex]['dict']['callUUID']
 @discussion This API checks if the call is ungrouped and goes active.
 */
-(CAMReturnBool *)privateConversationWith:(NSString *)callUUID;
@end
