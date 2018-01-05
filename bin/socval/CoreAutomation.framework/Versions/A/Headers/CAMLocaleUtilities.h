//
//  CAMLocaleUtilities.h
//  CoreAutomation
//
//  Created by Matt Dreisbach on 1/27/12.
//  Copyright (c) 2012 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CAMReturnValues.h"

#define kCAMLocaleUtilitiesShortName localeUtilities

@protocol CAMLocaleUtilities
@optional

/*!
 @method    preferredLanguages
 @abstract	The user's language preference order.
 @return    On success, returns an an array of NSString objects, each of which is a canonicalized IETF BCP 47 language identifier.  Returns an error on failure.
 */
- (CAMReturnArray*)preferredLanguages;

/*!
 @method    currentLocaleIdentifier
 @abstract	The identifier for the user's current locale.
 @return    On success, returns an an NSString, a canonicalized IETF BCP 47 locale identifier.  Returns an error on failure.
 */
- (CAMReturnString*)currentLocaleIdentifier;


/*!
 @method    setDeviceLanguage
 @abstract	Set Device display language.
 @return    On success, returns an void.  Returns an error on failure.
 @discuss   Device lanaguage is determined by the order of items in preferredLanguages. preferredLanguage returns an array of languages. To set device language, we need to move the language to the index 0, and move the rest array down by 1. locale also needs to be provided.
 */

- (CAMReturnVoid*)setDeviceLanguage:(NSString*)languageCode withLocale:(NSString*) locale;

/*!
 @method    availableLocaleIdentifiers
 @abstract	Return all available locale identifiers as an array of strings
 @return    On success, returns an array of strings
 */
- (CAMReturnArray*)availableLocaleIdentifiers;


/*!
 @method    currentLogicalLocale
 @abstract	The current logical locale for the current user.The locale is formed from the settings for the current user’s chosen system locale overlaid with any custom settings the user has specified in System Preferences.
 @return    The object always reflects the current state of the current user’s locale settings.
 */
- (CAMReturnString*) currentLogicalLocale;

@end
