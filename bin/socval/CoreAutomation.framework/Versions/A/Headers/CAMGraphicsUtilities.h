//
//  CAMGraphicsUtilities.h
//  CoreAutomation
//
//  Exposes some APIs from SpringboardServices and other UI frameworks
//
//  Created by Chris Whitney on 1/3/12.
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CAMReturnValues.h"

#define kCAMGraphicsUtilitiesShortName graphicsUtilities

@protocol CAMGraphicsUtilities
@optional

/*!
 @method    isScreenLocked
 @abstract	Determines if the screen is currently locked.
 @return    Return True if the screen is locked, else False.
 */
- (CAMReturnBool*)isScreenLocked;

/*!
 @method    isPasscodeRequired
 @abstract	Determines if the screenlock requires a passcode. This code will return False if the screen is unlocked, regardless of whether a passcode is set.
 @return    Return True if the screenlock requires a passcode to unlock, else False.
 */
- (CAMReturnBool*)isPasscodeRequired;

/*!
 @method    currentScreenImage
 @abstract	Take a screenshot of the device and return the image data.
 @return    On success, returns an NSData object containing the image data in PNG format. Returns an error on failure.
 */
- (CAMReturnData*)currentScreenImage;

/*!
 @method    currentUnrotatedScreenImage
 @abstract	Take a screenshot of the device and return the image data. Does not perform a rotation on the device.
 @return    On success, returns an NSData object containing the image data in PNG format. Returns an error on failure.
 */
- (CAMReturnData*)currentUnrotatedScreenImage;

/*!
 @method    currentStarkScreenImage
 @abstract	Take a screenshot of the attached Stark device and return the image data.
 @return    On success, returns an NSData object containing the image data in PNG format. Returns an error on failure.
 */
- (CAMReturnData*)currentStarkScreenImage;

/*!
 @method    appIconsForIdentifiers:
 @abstract  Retrieve the application icon image data for a list of application specified by their identifiers.
 @return    On success, returns a dictionary of NSData objects containing the image data in PNG format keyed by application identifier. Returns nil on failure.
 */
- (CAMReturnDictionary*)appIconsForIdentifiers:(NSArray*)identifiers;

/*
 @method    pasteboardStrings
 @abstract  Calls [[UIPasteboard generalPasteboard] strings] and returns the resulting array of strings.
 @discussion The device must be unlocked in order to get the contents of the pasteboard.
 */
- (CAMReturnArray*)pasteboardStrings;

/*
 @method    setPasteboardString:
 @abstract  Calls [[UIPasteboard generalPasteboard] setValue:forPasteboardType:kUTTypeText] in order to paste the string onto the device pasteboard.
 @discussion The device must be unlocked in order to interact with the pasteboard.
 */
- (CAMReturnVoid*)setPasteboardString:(NSString*)aString;

/*!
 @method    sendAppPreferencesChangedWithDomain:key:
 @abstract  Post a notification (through Graphics Services) indicating a change in the value of a particular preference (specified by domain and key).
 */
- (CAMReturnVoid*)sendAppPreferencesChangedWithDomain:(NSString*)domain key:(NSString*)key;

/*!
 @method	userInterfaceIdiom
 @abstract	Returns the current UIUserInterfaceIdiom
 */
- (CAMReturnInteger*)userInterfaceIdiom;

/*!
 @method    screenScale
 @abstract  Returns the main UIScreen scale.
 */
- (CAMReturnDouble*)screenScale;

/*!
 @method    screenBounds
 @abstract  Returns the main UIScreen bounds.
 */
- (CAMReturnCGRect*)screenBounds;

/*!
 @method     screenOrientation
 @abstract   Get the orientation of the screen.
 @return     Returns a CAMReturnInteger corresponding to the UIInterfaceOrientation of the status bar.
 */
- (CAMReturnInteger *)screenOrientation;

/*!
 @method    isScreenOrientationLandscape
 @abstract  Determines if the screen orientation is landscape (left or right).
 @return    Returns True if the screen orientation is landscape (left or right), False if portrait.
 */
- (CAMReturnBool*)isScreenOrientationLandscape;

/*!
 @method    isScreenOrientationPortrait
 @abstract  Determines if the screen orientation is portrait (normal or upside-down).
 @return    Returns True if the screen orientation is portrait (normal or upside-down), False if landscape.
 */
- (CAMReturnBool*)isScreenOrientationPortrait;

@end
