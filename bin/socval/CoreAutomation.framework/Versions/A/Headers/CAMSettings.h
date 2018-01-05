//
//  CAMSettings.h
//  CoreAutomation
//
//  Created by Chris Whitney on 2/6/12.
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CAMReturnValues.h"

#define kCAMSettingsShortName settings

// Profile Keys
#define kCAMSettingsProfileDisplayNameKey @"displayName"
#define kCAMSettingsProfileIdentifierKey @"identifier"
#define kCAMSettingsProfileUUIDKey @"uuid"

typedef enum AudioRoute
{
    kAudioRouteUnknown = -1,
    
    // Output only.
    kAudioRouteSpeaker = 0,
    kAudioRouteHeadphone,
    kAudioRouteHeadset,
    kAudioRouteReceiver,
    kAudioRouteBestSpeaker,
    kAudioRouteLineOut,
    kAudioRoutePersistentLineOut,
    kAudioRouteUSB,
    kAudioRouteDisplayPort,
    kAudioRouteAirTunes,
    kAudioRouteHDMI,
    kAudioRouteBluetoothLEOutput,
    kAudioRouteSPDIF,
    
    // Input only.
    kAudioRouteLineIn,
    kAudioRouteMicrophoneBuiltIn,
    kAudioRouteMicrophoneWired,
    kAudioRouteMicrophoneBluetooth,
    kAudioRouteUSBInput,
    
    // Input + output.
    kAudioRouteTTY,
    kAudioRouteHeadsetBT,
    kAudioRouteHeadphonesBT,
    kAudioRouteLineInOut,
    kAudioRouteHeadsetInOut,
    kAudioRouteSpeakerAndMicrophone,
    kAudioRouteHeadphonesAndMicrophone,
    kAudioRouteBestSpeakerAndMicrophone,
    kAudioRouteReceiverAndMicrophone
} AudioRoute;


typedef enum AudioCategory
{
    kAudioCategory_Active = 0, // Internal: this referes to the active category, theres isnt any corresponding entity in AV Controller
    kAudioCategory_AudioVideo,
    kAudioCategory_Ringtone,
    kAudioCategory_PhoneCall,
    kAudioCategory_TTYCall,
    kAudioCategory_VoiceMail,
    kAudioCategory_VoicemailGreeting,
    kAudioCategory_RingtonePreview,
    kAudioCategory_Alarm,
    kAudioCategory_Record,
    kAudioCategory_PlayAndRecord,
    kAudioCategory_Alert,
    kAudioCategory_FindMyPhone,
    kAudioCategory_EmergencyAlert,
    kAudioCategory_EmergencyAlert_Muteable
} AudioCategory;

@protocol CAMSettings
@optional

extern NSString *EveryoneOption;
extern NSString *NoOneOption;
extern NSString *FavoritesOption;
extern NSString *ContactsOption;
extern NSString *AddressBookGroupOption;

#pragma mark -
#pragma mark Preferences
- (CAMReturnVoid*)setValue:(id)value forPreferencesKey:(NSString*)key inDomain:(NSString*)domain;
- (CAMReturnVoid*)deletePreferencesKey:(NSString*)key inDomain:(NSString*)domain;
- (CAMReturnVoid*)postDarwinNotification:(NSString*)key;

#pragma mark -
#pragma mark Profiles
// Returns a dictionary with keys ('displayName', 'identifier', 'uuid')
- (CAMReturnDictionary*)installProfileFromURL:(NSString*)url promptAnswers:(NSDictionary*)responses;

// Returns a dictionary with keys ('displayName', 'identifier', 'uuid')
- (CAMReturnDictionary*)installProfileWithData:(NSData*)payload promptAnswers:(NSDictionary*)responses;

- (CAMReturnVoid*)uninstallProfileWithIdentifier:(NSString*)identifier;

// Returns an array of dictionaries with keys ('displayName', 'identifier', 'uuid')
- (CAMReturnArray*)installedProfiles;

#pragma mark -
#pragma mark Settings

/*!
 @method    isPasscodeSet:
 @abstract  Ask if a passcode is set.
 @return    YES if a passcode is set, NO otherwise.
 */
- (CAMReturnBool*)isPasscodeSet;

/*!
 @method    setPasscode:
 @abstract  Set a new passcode. A passcode must not be set already on the device. Passcodes can be either numeric or alphanumeric strings.
 @return    YES if the set succeeded, NO otherwise.
 */
- (CAMReturnBool*)setPasscode:(NSString*)passcode;

/*!
 @method    changePasscodeFrom:toPasscode:
 @abstract  Change an existing passcode to a different passcode.
 @return    YES if the change succeeded, NO otherwise.
 */
- (CAMReturnBool*)changePasscodeFrom:(NSString*)oldPasscode toPasscode:(NSString*)newPasscode;
/*!
 @method    removePasscode:
 @abstract  Remove the current passcode. You must know the passcode to remove it.
 @return    YES if the remove succeeded, NO otherwise.
 */
- (CAMReturnBool*)removePasscode:(NSString*)passcode;

/*!
 @method    verifyPasscode:
 @abstract  Test that the passcode matches the stored passcode.
 @return    YES if the passcode matches, NO otherwise.
 */
- (CAMReturnBool*)verifyPasscode:(NSString*)passcode;

/*!
 @method    isScreenLocked:
 @abstract  Ask is screen is locked.
 @return    YES if the screen is locked, NO otherwise.
 */
- (CAMReturnBool*)isScreenLocked;
    
/*!
 @method    lockScreen:
 @abstract  Lock the screen of the device.
 @return    YES if the lock succeeds, NO otherwise. 
 */
- (CAMReturnBool*)lockScreen;

/*!
 @method    bypassSetupAssistant:
 @abstract  Sets up the device with sensible defaults (location services: on, diagnostic logs: on), bypassing the setup assistant. The device needs to be activated beforehand. This function must be called asRoot().
 @return    a compound object with a success state in .boolValue (YES if successful, NO otherwise) and an .error object with the POSIX description of the error in case of failure.
*/
- (CAMReturnBool*)bypassSetupAssistant;

/*!
 @brief Auto-lock time in seconds. A negative number indicates never.
 */
- (CAMReturnInteger*)getAutoLockInterval;

/*!
 @brief Auto-lock time in seconds. Specify a negative number to never auto-lock.
 */
- (CAMReturnVoid*)setAutoLockInterval:(NSNumber*)value;

/*!
 @method    resetNetworkSettings
 @abstract    Resets all network settings – equivalent to Settings -> General -> Reset -> Reset Network Settings
 @return    Returns an error on failure.
 */
- (CAMReturnVoid*)resetNetworkSettings;

/*!
 @method    eraseAllContentsAndSettings
 @abstract    Erases all contents and settings – equivalent to Settings -> General -> Reset -> Erase All Contents and Settings
 @return    Returns an error on failure.
 */
- (CAMReturnVoid*)eraseAllContentsAndSettings;

/*!
 @method    appleWirelessDiagnosticsEnabled
 @abstract  Returns current state of Diagnostics & Usage - equivalent to Settings->General->About->Diagnostics & Usage.
 @return    This returns either the current state of appleWirelessDiagnostics. If the current state is MCRestrictedBoolNoData(0), this method returns false.
 */
- (CAMReturnBool*)appleWirelessDiagnosticsEnabled;

/*!
 @method    setAppleWirelessDiagnosticsEnabled
 @abstract  Enable or Disable Diagnostics & Usage - equivalent to Settings->General->About->Diagnostics & Usage.
 @param        enable An NSNumber initialized with the BOOL values YES or NO.
 @return    This returns nothing.
 */
- (CAMReturnVoid*)setAppleWirelessDiagnosticsEnabled:(NSNumber*)enable;

/*!
 @method    setPowerlogEnabled
 @abstract  Enable or Disable Powerlog - equivalent to Internal Settings -> Power -> Battery Life Logging
 @param        enable An NSNumber initialized with the BOOL values YES or NO.
 @return    This returns nothing.
 */
- (CAMReturnVoid*)setPowerlogEnabled:(NSNumber*)enable;

#pragma mark Audio Video Routing
- (CAMReturnInteger *)getAudioSourceType;
- (CAMReturnVoid *)setAudioSourceType:(NSNumber*)routeId;
- (CAMReturnInteger *)getVoiceMute;
- (CAMReturnVoid *)setVoiceMute:(NSNumber*)enabled;

#pragma mark AV Volume control
/*!
 @method    activeAVCategory
 @abstract  get the active AV category.
 @return    Returns AudioCategory or an error on failure
 */
- (CAMReturnInteger *)activeAVCategory;

/*!
 @method    getVolume
 @abstract  get the volume value for the given AV category.
 @param     category ref AudioCategory. To use the active category, pass kAudioCategory_Active
 @return    Returns volume value or an error on failure
 */
- (CAMReturnDouble *)getVolume:(NSNumber*)category;

/*!
 @method    setVolume
 @abstract  set the volume value for the given AV category.
 @param         volume float value could be 0.0 to 1.0. This could be related to 16 UI level volume by multiplying with 0.0625
                category: ref AudioCategory enum. To use the active category, pass kAudioCategory_Active
 @return    Returns an error on failure
 */
- (CAMReturnVoid *)setVolume:(NSNumber*)volume forCategory:(NSNumber*)category;

/*!
 @method    changeVolumeBy
 @abstract  increment/decrement the volume level for the given AV category.
 @param         delta float value could be 0.0 to 1.0. This could be related to 16 level volume by multiplying with 0.0625
                category: ref AudioCategory enum. To use the active category, pass kAudioCategory_Active
 @return    Returns an error on failure
 */
- (CAMReturnVoid *)changeVolumeBy:(NSNumber*)delta forCategory:(NSNumber*)category;

/*!
 @method    setVoicecallAudioInjection
 @abstract  Enable or Disable Audio Injection during a voicecall. This will only enables the audio injection settings. To make audio injection work, there should be a wavefile named "iiii.000.ulout.wav" in the device's /tmp folder.
 @param        enable An NSNumber initialized with the BOOL values YES or NO.
            WaveFile is a NSDictionay contains a key @"file" with a value NSData* of the wave file
 @return    This returns nothing.
 */
- (CAMReturnVoid*)setVoicecallAudioInjection:(NSNumber*)enable withWaveFile:(NSDictionary*)WaveFile;

/*!
 @method    setStreamCaptureForTelephonyAndFaceTime
 @abstract  Enable or Disable Stream Capture during a voicecall or FaceTime. This will enable/disable recording
	of the audio to /tmp folder.
 @param        enable An NSNumber initialized with the BOOL values YES or NO.
 @return    This returns nothing.
 */
- (CAMReturnVoid*)setStreamCaptureForTelephonyAndFaceTime:(NSNumber*)enable;

/*!
 @method    setSiriLoggingEnabled
 @param     enable - YES - enables Siri logging, NO - disables Siri Logging
 @return    None
 @abstract  This command is equivalent to Settings -> Internal -> Siri -> Log to file
 */
- (CAMReturnVoid*)setSiriLoggingEnabled:(NSNumber*)enable;

/*!
 @method    siriLoggingEnabled
 @return    Returns whether siri logging is enabled.
 */
- (CAMReturnBool*)siriLoggingEnabled;

/*!
 @method    getRouteNames
 @return    Returns array of pickable route names for AirPlay
 */
- (CAMReturnArray*)getRouteNames;

/*!
 @method    pickRouteName
 @param     routeName a pickable route name for AirPlay. Use getRouteNames to query available route names to pick from.
 @return    Returns pass or fail
 */
- (CAMReturnBool *)pickRouteName:(NSString *)routeName;

/*!
 @method    unlockWatchScreen:
 @abstract  unlock and wake up watch screen
 @return    YES if successful, NO otherwise
 */
- (CAMReturnBool *)unlockWatchScreen;

/*!
 @method    dumpAWDLogs
 @abstract  Dumps AWD Logs
 */
- (CAMReturnVoid *)dumpAWDLogs;

/*!
 @method    setDNDManualEnabled:
 @param     enabled @YES enable , @NO disable.
 @abstract  Set Manual DND to enable/disable
 */
- (CAMReturnVoid *)setDNDManualEnabled:(NSNumber *)enabled;

/*!
 @method    setDNDScheduledEnabled:
 @param     enabled @YES enable , @NO disable.
 @abstract  Set Scheduled DND to enable/disable
 */
- (CAMReturnVoid *)setDNDScheduledEnabled:(NSNumber *)enabled;

/*!
 @method    setDNDScheduledRangeFrom:toDate:
 @abstract  Set DND scheduled date range.
 */
- (CAMReturnVoid *)setDNDScheduledRangeFrom:(NSDate *)fromDate to:(NSDate *)toDate;

/*!
 @method    isDNDRepeatedCalls
 @abstract  Returns DND Repeated Calls switch state
 @return    YES if enabled, NO otherwise
 */
- (CAMReturnBool *)isDNDRepeatedCalls;

/*!
 @method    setDNDRepeatedCalls:
 @param     repeatedCalls @YES enable, @NO disable.
 @abstract  Set DND Repeated Calls switch state
 */
- (CAMReturnVoid *)setDNDRepeatedCalls:(NSNumber *)repeatedCalls;

/*!
 @method     setDNDSilenceWhileLocked:
 @param      mode @YES enable, @NO disable.
 @abstract   Silence always or when device is locked.
*/
- (CAMReturnVoid *)setDNDSilenceWhileLocked:(NSNumber *)mode;

/*!
 @method     getDNDSilenceWhileLocked:
 @abstract   Silence always (0) or when device is locked(1).
 */
- (CAMReturnBool *)getDNDSilenceWhileLocked;

/*!
 @method     getDNDAllowCallsFromType
 @abstract   Returns "Allows Calls From" value currently from DND.
 @discussion Key "type" can have values 0("NO_ONE"), 1("FAVORITES"), 2("AddressBookGroup"), 4("CONTACTS"), 16("EVERYONE").
             2("AddressBookGroup") will have additional key/value pairs for RecordID (Address Book Record ID), and GroupName.
 */
- (CAMReturnDictionary *)getDNDAllowCallsFromType;

/*!
 @method     setDNDAllowCallsFromType
 @abstract   Set "Allows Calls From" value in DND.
 @param      type could be "EVERYONE" (EveryoneOption), "NO_ONE"(NoOneOption), "FAVORITES"(FavoritesOption), "CONTACTS"(ContactsOption), "AddressBookGroup"(AddressBookGroupOption).
             If type is "AddressBookGroup", recordID and groupName are required. Same can be retrieved through
             getDNDAllowCallsFromType.
 */
- (CAMReturnVoid *)setDNDAllowCallsFromType:(NSString *)type recordID:(NSNumber *)recordID groupName:(NSString *)groupName;
@end
