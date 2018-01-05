//
//  CAMAccessibility.h
//  CoreAutomation
//
//  Created by Darren Minifie on 7/23/12
//  Copyright (c) 2011 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CAMReturnValues.h"

#define kCAMAccessibilityShortName accessibility

@protocol CAMAccessibility
@optional

#pragma mark - VoiceOverTouch

/*!
 @method enableVoiceOver
 @abstract Enables VoiceOver.
 @return BOOL. YES if VoiceOver was successfully enabled
 */
- (CAMReturnBool *)enableVoiceOver;

/*!
 @method disableVoiceOver
 @abstract Disables VoiceOver.
 @return BOOL. YES if VoiceOver was successfully disabled
 */
- (CAMReturnBool *)disableVoiceOver;

/*!
 @method isVoiceOverEnabled
 @abstract Query VoiceOver running status.
 @return BOOL. YES if VoiceOver is running
 */
- (CAMReturnBool *)isVoiceOverEnabled;

/*!
 @method setVoiceOverSpeakingRate:
 @abstract Sets the VoiceOver speaking rate.
 @param speakingRate Speaking rate [0...1]
 */
- (CAMReturnVoid *)setVoiceOverSpeakingRate:(NSNumber *)speakingRate;

/*!
 @method voiceOverSpeakingRate
 @abstract Returns the VoiceOver speaking rate.
 @return A float [0..1] representing speaking rate.
 */
- (CAMReturnDouble *)voiceOverSpeakingRate;

/*!
 @method setVoiceOverSpeakingVolume:
 @abstract Sets the VoiceOver speaking volume.
 @param speakingVolume Speaking rate [0...1]
 @discussion The speaking volume is capped at the device volume, so setting
    this to 1 while system volume is 70% will capp speaking volume to 70%
 */
- (CAMReturnVoid *)setVoiceOverSpeakingVolume:(NSNumber *)speakingVolume;

/*!
 @method voiceOverSpeakingVolume
 @abstract Returns the VoiceOver speaking volume.
 @return A float [0..1] representing speaking volume.
 */
- (CAMReturnDouble *)voiceOverSpeakingVolume;

#pragma mark - Assistive Touch

/*!
 @method enableAssistiveTouch
 @abstract Enables AssistiveTouch.
 @return BOOL. YES if AssistiveTouch was successfully enabled
 */
- (CAMReturnBool *)enableAssistiveTouch;

/*!
 @method disableAssistiveTouch
 @abstract Disables AssistiveTouch.
 @return BOOL. YES if AssistiveTouch was successfully disabled
 */
- (CAMReturnBool *)disableAssistiveTouch;

/*!
 @method isAssistiveTouchEnabled
 @abstract Query AssistiveTouch running status.
 @return BOOL. YES if AssistiveTouch is running
 */
- (CAMReturnBool *)isAssistiveTouchEnabled;

/*!
 @method enableAssistiveTouchScanner
 @abstract Enables the scanner (switch software) in AssistiveTouch.
 @return BOOL. YES if AssistiveTouch scanner was successfully enabled
 */
- (CAMReturnBool *)enableAssistiveTouchScanner;

/*!
 @method disableAssistiveTouchScanner
 @abstract Disables the scanner (switch software) in AssistiveTouch.
 @return BOOL. YES if AssistiveTouch scanner was successfully disabled
 */
- (CAMReturnBool *)disableAssistiveTouchScanner;

/*!
 @method isAssistiveTouchScannerEnabled
 @abstract Query AssistiveTouch to see if the scanner (switch software) is running.
 @return BOOL. YES if AssistiveTouch scanner is running
 */
- (CAMReturnBool *)isAssistiveTouchScannerEnabled;

/*!
 @method enableAssistiveTouchHardware
 @abstract Enables the AssistiveTouch Hardware interface
 @return BOOL. YES if AssistiveTouch Hardware interface was successfully enabled
 */
- (CAMReturnBool *)enableAssistiveTouchHardware;

/*!
 @method disableAssistiveTouchHardware
 @abstract Disables the AssistiveTouch Hardware interface
 @return BOOL. YES if AssistiveTouch Hardware interface was successfully disabled
 */
- (CAMReturnBool *)disableAssistiveTouchHardware;

/*!
 @method isAssistiveTouchHardwareEnabled
 @abstract Query AssistiveTouch to see if the hardware interface is enabled
 @return BOOL. YES if AssistiveTouch hardware interface is running
 */
- (CAMReturnBool *)isAssistiveTouchHardwareEnabled;

#pragma mark - Zoom

/*!
 @method enableZoom
 @abstract Enables Zoom.
 @return BOOL. YES if Zoom was successfully enabled
 */
- (CAMReturnBool *)enableZoom;

/*!
 @method disableZoom
 @abstract Disables Zoom.
 @return BOOL. YES if Zoom was successfully disabled
 */
- (CAMReturnBool *)disableZoom;

/*!
 @method isZoomEnabled
 @abstract Query Zoom running status.
 @return BOOL. YES if Zoom is running
 */
- (CAMReturnBool *)isZoomEnabled;

#pragma mark - Accessibility Team Internal

/*!
 @method enableReportingValidationErrors
 @abstract Enable internal reporting of accessibility validation errors
 @return BOOL. YES if setting internal reporting was successful
 */
- (CAMReturnBool *)enableReportingValidationErrors;

/*!
 @method disableReportingValidationErrors
 @abstract Disable internal reporting of accessibility validation errors
 @return BOOL. YES if unsetting internal reporting was successful
 */
- (CAMReturnBool *)disableReportingValidationErrors;

/*!
 @method isReportingValidationErrors
 @abstract Determine if accessibility internal validation reporting is enabled
 @return BOOL. YES if internal reporting is enabled
 */
- (CAMReturnBool *)isReportingValidationErrors;

@end
