//
//  CAMCoreTelephony.h
//  CoreAutomation
//
//  Created by Chris Whitney on 2/23/12.
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CAMReturnValues.h"
#import "CAMCoreTelephonyConstants.h"

#define kCAMCoreTelephonyShortName coreTelephony

@protocol CAMCoreTelephony
@optional

#pragma mark -
#pragma mark Network
/*!
 @method    phoneNumber
 @abstract  Returns the current phone number.
 @discussion This method is using CTSettingCopyMyPhoneNumber to fetch the number.
 */
- (CAMReturnString*)phoneNumber;
/*!
 @method    operatorName
 @abstract  Returns the operator name.
 @discussion This method is using CTRegistrationCopyOperatorName to fetch the operator name.
 */
- (CAMReturnString*)operatorName;
/*!
 @method    imsi
 @abstract  Returns the international mobile subscriber identity from CoreTelephony.
 */
- (CAMReturnString*)imsi;

/*!
 @method    isDataAttached
 @abstract  Returns whether or not data is attached.
 @discussion Returns True if data is attached. Otherwise, false is returned. This method is using CTRegistrationGetDataAttached to fetch the state.
 */
- (CAMReturnBool*)isDataAttached;

/*!
 @method    registrationStatus
 @abstract  Returns the current registration status as an integer. These are the following return types.
    0, RegistrationStatusUnknown
    1, RegistrationStatusNotRegistered
    2, RegistrationStatusSearching
    3, RegistrationStatusDenied
    4, RegistrationStatusRegisteredHome
    5, RegistrationStatusRegisteredRoaming
    6, RegistrationStatusEmergencyOnly
 @discussion This method is using CTRegistrationGetStatus to fetch the state.
 */
- (CAMReturnInteger*)registrationStatus;

/*!
 @method    isNetworkRegistered
 @abstract Returns True if the device is Registered Home or Registered Roaming.
 @discussion This method is using CTRegistrationGetStatus to fetch the state.
 */
- (CAMReturnBool*)isNetworkRegistered;

/*!
 @method    waitForRegistration:withTimeout:
 @abstract  Waits a specified number of seconds for the device registration to match the expected state.
 @param     expectedState This is a boolean value indicating the expected status to wait for. YES if waiting for registration. NO if waiting for no registration.
 @discussion This methods uses isNetworkRegistered to determine when the device is registered (or not).
 */
- (CAMReturnBool*)waitForRegistration:(NSNumber*)expectedState withTimeout:(NSNumber*)timeout;

/*!
 @method    waitForRegistrationStatus:withTimeout:
 @abstract  Waits a specified number of seconds for the device registration status to match kCTRegistrationStatusRegisteredHome or kCTRegistrationStatusRegisteredRoaming based upon incoming CT notification
 @param     expectedRegistrationStatus is string with expected values kCTRegistrationStatusRegisteredHome or kCTRegistrationStatusRegisteredRoaming
 @discussion Relying upon CT Notification instead of querying CT to get RegistrationStatus. TODO: Extending this functionality for other registration status states.
 */
- (CAMReturnBool*)waitForRegistrationStatus:(NSString*)expectedRegistrationStatus withTimeout:(NSNumber*)timeout;

/*!
 @method    waitForDataAttach:withTimeout:
 @abstract  Waits a specified number of seconds for the device data attach status to match the expected state.
 @param     expectedState This is a boolean value indicating the expected status to wait for. YES if waiting for data attach. NO if waiting for no data attach.
 @discussion This methods uses isDataAttached to determine when the device is data attached (or not).
 */
- (CAMReturnBool*)waitForDataAttach:(NSNumber*)expectedState withTimeout:(NSNumber*)timeout;

/*!
 @method    setAllowsLTE
 @abstract	Enable LTE on device.
 @discussion This will set device max allowed data rate to 4G/LTE. On success, return true. otherwise, return false.
 */
- (CAMReturnBool*)setAllowsLTE;
/*!
 @method    setDisallowsLTE
 @abstract	Disable LTE on device.
 @discussion This will set device max allowed data rate to 3G. On success, return true. otherwise, return false.
 */
- (CAMReturnBool*)setDisallowsLTE;
/*!
 @method    isLTEAllowed
 @abstract	Check whether LTE is allowed.
 @discussion If LTE is allowed, true is returned. Otherwise, false is returned.
 */
- (CAMReturnBool*)isLTEAllowed;

/*!
 @method     enables3G
 @deprecated This method is deprecated. Please use isWirelessTechnologyGenerationEnabled: instead.
 */
- (CAMReturnBool*)enables3G __attribute__((deprecated));
/*!
 @method     setEnables3G:
 @deprecated This method is deprecated. Please use setEnablesWirelessTechnologyGeneration: instead.
 */
- (CAMReturnVoid*)setEnables3G:(NSNumber*)state __attribute__((deprecated));

/*!
 @method    wirelessTechnologyGeneration
 @abstract	Trying to get the WirelessTechnologyGeneration from selected RATs.
 @discussion if RAT is automatic, it will not be able to deduce the WirelessTechnology generation. 0 will be returned.
 */
- (CAMReturnInteger*)wirelessTechnologyGeneration;
/*!
 @method    isWirelessTechnologyGenerationEnabled
 @abstract	Whether the specified wireless technology generation is enabled.
 */
- (CAMReturnBool*)isWirelessTechnologyGenerationEnabled:(NSNumber*)generation;
/*!
 @method    setEnablesWirelessTechnologyGeneration
 @abstract	Enable specified wireless technology generation.
 */
- (CAMReturnBool*)setEnablesWirelessTechnologyGeneration:(NSNumber*)generation;

- (CAMReturnBool*)allowsNetworkCellularData; //Controls Settings->General->Network->Cellular Data
- (CAMReturnVoid*)setAllowsNetworkCellularData:(NSNumber*)state verify:(NSNumber*)verifyChange;
- (CAMReturnBool*)disallowsCellularData; //Controls Settings -> Carrier Settings -> Disallow Cellular Data
- (CAMReturnVoid*)setDisallowsCellularData:(NSNumber*)state verify:(NSNumber*)verifyChange withinTimeout:(NSNumber*)seconds;
- (CAMReturnInteger*)activeCarrierTechnology;
- (CAMReturnInteger*)activeWirelessTechnology;
- (CAMReturnVoid*)setRATSelection:(NSNumber*)rat waitForRegistration:(NSNumber*)wait withinTimeout:(NSNumber*)seconds;
- (CAMReturnInteger*)RATSelection;
- (CAMReturnString*)radioAccessTechnology;
- (CAMReturnArray*)signalStrength;
- (CAMReturnArray*)signalStrengthAfterChangeNotificationWithinTimeout:(NSNumber*)seconds;
- (CAMReturnBool*)enablesDataRoaming;
- (CAMReturnVoid*)setEnablesDataRoaming:(NSNumber*)enable;
- (CAMReturnBool*)isCDMAInternationalRoamingAllowed;
- (CAMReturnBool*)CDMAInternationalRoamingStatus;
- (CAMReturnBool*)setCDMAInternationalRoamingStatus:(NSNumber*)status;
- (CAMReturnVoid*)setActivationStatus:(NSNumber*)active forPDPContext:(NSNumber*)contextID waitForNotification:(NSNumber*)flag withinTimeout:(NSNumber*)seconds;
- (CAMReturnBool*)activationStatusOfPDPContext:(NSNumber*)contextID;
- (CAMReturnDictionary*)mobileEquipmentInfo;
- (CAMReturnDictionary*)systemCapabilities;
- (CAMReturnBool*)hasSystemCapability:(NSNumber*)capability;
- (CAMReturnDictionary*)carrierInfo;

/*!
 @method    carrierEntitlements
 @abstract  Returns current carrier entitlements.
 @return    Returns a dictionary of string keys and values. The string contants are defined in CTCarrierEntitlements.h.
 */
- (CAMReturnDictionary*)carrierEntitlements;

/*!
 @method    supportsFaceTimeOverCellular
 @abstract  Returns whether or not the carrier has supports FaceTime over cellular data.
 @return    True if the carrier allows FaceTime over cellular data, otherwise False.
 */
- (CAMReturnBool*)supportsFaceTimeOverCellular;

/*!
 @method    supportsTetheringOverCellular
 @abstract  Returns whether or not the carrier supports tethering over cellular data.
 @return    True if the carrier allows tethering over cellular data, otherwise False.
 */
- (CAMReturnBool*)supportsTetheringOverCellular;

- (CAMReturnBool*)enablesVoiceRoaming;
- (CAMReturnVoid*)setEnablesVoiceRoaming:(NSNumber*)state;
- (CAMReturnBool*)enablesFastDormancy;
- (CAMReturnVoid*)setEnablesFastDormancy:(NSNumber*)state;
- (CAMReturnVoid*)setTimeCacheValidityPeriod:(NSNumber*)period;
- (CAMReturnInteger*) getTimeUpdateCounter;
- (CAMReturnInteger*) getTimeZoneUpdateCounter;
- (CAMReturnVoid*)resetTimeNotificationCounters: (NSNumber*)resetTimeUpdateCounter withTimeZoneCounter:(NSNumber*)resetTimeZoneUpdateCounter;
- (CAMReturnVoid*)waitForTimeNotification: (NSNumber*) waitForTimeUpdate
                             withTimeZone: (NSNumber*) waitForTimeZoneUpdate
                     withTimeAvailability: (NSNumber*) waitForTimeAvailabil
                 withTimeAvailabilityInfo: (NSNumber*) shouldTimeBeAvailable
                              withTimeout: (NSNumber*) timeout;
/*!
 @method    cellularUsage
 @abstract	Return cellular data usage per app.
 */
- (CAMReturnDictionary*)cellularUsage;

#pragma mark -
#pragma mark Sim Methods
- (CAMReturnInteger*)registrationCauseCode;
- (CAMReturnString*)simStatusDescription;
- (CAMReturnInteger*)remainingPinAttempts;
- (CAMReturnInteger*)remainingPukAttempts;
- (CAMReturnVoid*)pinUnlock:(NSString*)pin withinTimeout:(NSNumber*)seconds;
- (CAMReturnVoid*)pukUnlock:(NSString *)puk withNewPin:(NSString*)pin withinTimeout:(NSNumber*)seconds;
- (CAMReturnBool*)simLockEnabled;
- (CAMReturnVoid*)setsSimPinEnabled:(NSNumber*)enabled withPin:(NSString*)pin withinTimeout:(NSNumber*)seconds;
- (CAMReturnVoid*)changesSimPinPassword:(NSString*)oldPin toNewPin:(NSString*)newPin withinTimeout:(NSNumber*)seconds;
- (CAMReturnDictionary*)simToolkitMenuItems;
- (CAMReturnVoid*)selectSIMToolkitMenuItem:(NSNumber*)index;
- (CAMReturnString*)getSIMTrayStatus;

#pragma mark -
#pragma mark Network Selection
- (CAMReturnBool*)isNetworkSelectionAvailable;
- (CAMReturnInteger*)networkSelectionMode;
- (CAMReturnVoid*)enableAutomaticNetworkSelection:(NSNumber*)waitForNotification withinTimeout:(NSNumber*)seconds;
- (CAMReturnArray*)networkSelectionList:(NSNumber*)seconds;
- (CAMReturnVoid*)setNetworkSelection:(NSDictionary*)network withinTimeout:(NSNumber*)seconds;
- (CAMReturnDictionary*)networkSelection;
/*!
 @method    cellInfo
 @abstract	Get serving cell and neighbor cell information, including MCC, MNC, SID, NID, RSSI, EcIo, EcN0 and more.
 */
- (CAMReturnArray*)cellInfo;

#pragma mark -
#pragma mark Activation
- (CAMReturnVoid*)startOMADM:(NSNumber*)waitForRegistration withinTimeout:(NSNumber*)seconds;
/*!
 @method        startManualOTASP:waitForCompletion:withinTimeout
 @discussion    Device must be on CDMA carrier and registered at Home.
 */
- (CAMReturnBool*)startManualOTASP:(NSNumber*)waitForCompletion withinTimeout:(NSNumber*)seconds;

#pragma mark -
#pragma mark Calling
/*!
 @method    callRecentsNumber:waitForAnswer:withinTimeout:
 @abstract  This method will look for the phone number in the Recents list, then call the specified number if found.
 @param     digits - The phone number to search for and dial.
 @param     flag - If true, the function will wait until the call is answered. If false, the function will return after dialing the call.
 @param     seconds - Number of seconds to wait for the call to be answered.
 */
- (CAMReturnVoid*)callRecentsNumber:(NSString*)digits waitForAnswer:(NSNumber*)flag withinTimeout:(NSNumber*)seconds;
- (CAMReturnVoid*)callNumber:(NSString*)digits waitForAnswer:(NSNumber*)flag;
- (CAMReturnVoid*)callNumber:(NSString*)digits waitForAnswer:(NSNumber*)flag withinTimeout:(NSNumber*)seconds;
- (CAMReturnVoid*)callContact:(NSString*)name numberType:(NSNumber*)listingSpecifier waitForAnswer:(NSNumber*)flag withinTimeout:(NSNumber*)seconds;
- (CAMReturnVoid*)waitForCallFromNumber:(NSString*)digits withinTimeout:(NSNumber*)seconds;
- (CAMReturnVoid*)answerCallFromNumber:(NSString*)digits withinTimeout:(NSNumber*)seconds;
- (CAMReturnVoid*)holdCallAndWaitForNotification:(NSNumber*)wait withinTimeout:(NSNumber*)seconds; // Holds the first active call
- (CAMReturnVoid*)unholdCallAndWaitForNotification:(NSNumber*)wait withinTimeout:(NSNumber*)seconds; // Unholds / resumes the first held call
- (CAMReturnVoid*)mergeCallFromNumber:(NSString*)digits withNumber:(NSString*)otherDigits withinTimeout:(NSNumber*)seconds;
- (CAMReturnVoid*)swapTwoCalls; // Requires two active calls
- (CAMReturnVoid*)leaveConferenceCallWithNumber:(NSString*)digits withinTimeout:(NSNumber*)seconds;
- (CAMReturnVoid*)endCallWithNumber:(NSString*)digits onlyIncoming:(NSNumber*)flag withinTimeout:(NSNumber*)seconds;
- (CAMReturnVoid*)endAllCallsAndWaitForDisconnect:(NSNumber*)wait withTimeout:(NSNumber*)timeout;
- (CAMReturnVoid*)endAllCalls;
- (CAMReturnInteger*)activeCallCount;
- (CAMReturnArray*)activeCalls;
/*!
 @method    clearRecentCalls
 @abstract  This method clears all recent calls in the Recents list.
 */
- (CAMReturnBool*)clearRecentCalls;
/*!
 @method    isCallInRecents:
 @abstract  This method will check if a given phone number is present in the Recents list.
 @param     digits - Phone number digits to check for.
 */
- (CAMReturnBool*)isCallInRecents:(NSString*)digits;
- (CAMReturnInteger*)multiPartyCallCountMaximum;
- (CAMReturnVoid*)sendDMTFRingTone:(NSString*)digit;
- (CAMReturnBool*)waitForDisconnectedCallNotification:(NSString*)digits withinTimeout:(NSNumber*)seconds;

/*!
 @method    enableVoicePrivacy
 @abstract	Enable voice privacy in Carrier Settings.
 @discussion This function only applies to C2K devices. Behavior of this function for a UMTS device is undefined. This method may return before the change takes effect.
 */
- (CAMReturnVoid*)enableVoicePrivacy;

/*!
 @method    disableVoicePrivacy
 @abstract	Disable voice privacy in Carrier Settings.
 @discussion This function only applies to C2K devices. Behavior of this function for a UMTS device is undefined. This method may return before the change takes effect.
 */
- (CAMReturnVoid*)disableVoicePrivacy;

/*!
 @method    getVoicePrivacyStatus
 @abstract	Get the voice privacy status.
 @return    bool, if true, voicePrivacy is enabled, otherwise, voicePrivacy is disabled.
 @discussion This function only applies to C2K devices. Behavior of this function for a UMTS device is undefined.
 */
- (CAMReturnBool*)voicePrivacyStatus;
- (CAMReturnBool*)waitForCallBecomeAddableWithinTimeout: (NSNumber*) seconds;

#pragma mark -
#pragma mark SMS
- (CAMReturnVoid*)sendSMS:(NSString*)text fromSender:(NSString*)sender toRecipients:(NSArray*)recipients withFiles:(NSArray*)attachmentNamesAndData withinTimeout:(NSNumber*)seconds;
- (CAMReturnArray*)receiveSMSFromSender:(NSString*)digits numberOfMessages:(NSNumber*)count withinTimeout:(NSNumber*)seconds;
- (CAMReturnVoid*)clearSMSQueue;
- (CAMReturnInteger*)byteLimitForMMS;
/*
 @method        disallowAutomaticSMS
 @discussion    Settings->CarrierSettings->Disallow Telephony Features->Disallow Automatic SMS (switch on)
 */
- (CAMReturnVoid*)disallowAutomaticSMS;

/*
 @method        allowAutomaticSMS
 @discussion    Settings->CarrierSettings->Disallow Telephony Features->Disallow Automatic SMS (switch off)
 */
- (CAMReturnVoid*)allowAutomaticSMS;
- (CAMReturnBool*)isAutomaticSMSDisallowed;

#pragma mark -
#pragma mark CMAS Alert
/*!
 @method    waitForCMASAlert
 @abstract	Waits for Mobile Emergency Alerts - Presidential, Emergency, Amber and returns CMAS Alert received information.
 @return    CMAS Alert Information
 @discussion Waits for Mobile Emergency Alerts - Presidential, Emergency, Amber and returns CMAS Alert received information.
 */
- (CAMReturnDictionary*)waitForCMASAlert:(NSNumber*)timeout;
/*!
 @method     setCMASAlertState
 @abstract	 Set CMAS Alert State. AlertType string could be one of - "AMBER", "Emergency" or "Presidential".
 @discussion UI Equivalent to setting Government alert switches under Settings -> Notification Center -> Government Alerts
 @return     True if operation succeeded.
 */
-(CAMReturnBool *)setCMASAlertState:(NSNumber *)enabled withAlertType:(NSString *)alertType;
/*!
 @method     getCMASAlertState
 @abstract	 Get CMAS Alert State. AlertType string could be one of - "AMBER", "Emergency" or "Presidential"
 @discussion UI Equivalent to getting Government alert switches state under Settings -> Notification Center -> Government Alerts
 @return     True if operation succeeded.
 */
-(CAMReturnBool *)getCMASAlertState:(NSString *)alertType;

#pragma mark -

#pragma mark Caller ID
- (CAMReturnInteger*)callerIDMode;
- (CAMReturnVoid*)setCallerIDMode:(NSNumber*)type;

#pragma mark -
#pragma mark Call Waiting
- (CAMReturnBool*)callWaiting;
- (CAMReturnVoid*)setCallWaiting:(NSNumber*)type;

#pragma mark -
#pragma mark Call Forwarding
- (CAMReturnDictionary*)callForwardingForReason:(NSNumber*)type;
- (CAMReturnVoid*)setCallForwardingEnabled:(NSNumber*)flag withNumber:(NSString*)digits forReason:(NSNumber*)type;

#pragma mark -
#pragma mark Internal
- (CAMReturnBool*)resetModem;
- (CAMReturnVoid*)sendUSSD:(NSString*)digits;
- (CAMReturnBool*)hasEurekaBaseband;
- (CAMReturnBool*)hasInfineonBaseband;
- (CAMReturnBool*)supportsVoLTE;
/*!
 @method        vocoderInfo
 @discussion    Settings->CarrierSettings->Baseband->Baseband Audio-> Audio Vocoder Info
*/
- (CAMReturnDictionary*)vocoderInfo;

/*!
 @method        disallowCarrierEntitlement
 @discussion    Settings->CarrierSettings->Disallow Telephony Features->Carrier Entitlement (switch on)
 */
- (CAMReturnVoid*)disallowCarrierEntitlement;
/*!
 @method        allowCarrierEntitlement
 @discussion    Settings->CarrierSettings->Disallow Telephony Features->Carrier Entitlement (switch off)
 */
- (CAMReturnVoid*)allowCarrierEntitlement;
- (CAMReturnBool*)isCarrierEntitlementDisallowed;

/*!
 @method     basebandStatus
 @abstract   return current baseband status.
 @return     True if BB is in ON/Alive state, else it returns False.
 @discussion This checks the reset State of BB and determines if BB is ON(Alive) or DOWN(Reset) state.
 */
- (CAMReturnBool*)basebandStatus;

/*!
 @method    checkBasebandStatus:withTimeout
 @abstract	Check baseband hardware status.
 @param     expected - Baseband status. Up = True, Down = False
            timeout - time to wait before timeout
 @discussion This method must be run as root for Infineon Baseband! For Infineon baseband, SendATCommand is used and it needs root permission to access its channel. For Eureka Baseband, ETLTool is used and does not need to be run as root.
 */
- (CAMReturnBool*)checkBasebandStatus:(NSNumber*)expected withTimeout:(NSNumber*)timeout;

/*!
 @method     isAllBasebandLoggingEnabled
 @abstract   Checks if all required internal Baseband Logging switches are enabled.
 @discussion Checks if CSI, Global logging are enabled in CT. For Eureka Baseband, it checks if DIAG Logging is enabled. For Karoo(ICE) Baseband, it checks if ABM, STT Logging is enabled.
 */
- (CAMReturnBool*)isAllBasebandLoggingEnabled;

/*!
 @method     isAllBasebandLoggingDisabled
 @abstract   Check if all required internal Baseband Logging switches are disabled.
 @discussion Check if CSI, Global logging are disabled in CT. In addition to this, for Eureka Baseband it checks if DIAG Logging is disabled. For Karoo(ICE) Baseband, it checks if ABM, STT Logging is disabled.
 */
- (CAMReturnBool*)isAllBasebandLoggingDisabled;

/*!
 @method     setAllBasebandLoggingEnabled
 @abstract   Enables/Disables all required CT and BB logging settings.
 @discussion Enables/Disables CSI, Global logging and ABM Logging at CT. In addition to this, it enables/disables DIAG logging if Baseband is Eureka. Or enables/disables STT Logging for Karoo(ICE) Baseband.
 */
- (CAMReturnVoid*)setAllBasebandLoggingEnabled:(NSNumber*)flag;

/*!
 @method    isCSILoggingEnabled
 @abstract  Checks if CSI Logging is enabled
 */
- (CAMReturnBool*)isCSILoggingEnabled;

/*!
 @method     isMobileAnalyzerLoggingEnabled.
 @deprecated This method is deprecated.
 */
- (CAMReturnBool*)isMobileAnalyzerLoggingEnabled __attribute__((deprecated));

/*!
 @method isArtemisLoggingEnabled.
 @deprecated This method is deprecated.
 */
- (CAMReturnBool*)isArtemisLoggingEnabled __attribute__((deprecated));

/*!
 @method     isDIAGLoggingEnabled
 @abstract   Checks if DIAG Logging is enabled
 @discussion Eureka Baseband only.
 */
- (CAMReturnBool*)isDIAGLoggingEnabled;

/*!
 @method    isBasebandTraceEnabled
 @abstract  Checks if ABM Trace for both Eureka and Karoo(ICE) BB is enabled.
 */
- (CAMReturnBool*)isBasebandTraceEnabled;

/*!
 @method     setDIAGLoggingSize
 @abstract   Sets DIAG Logging History size. Valid sizes are 8, 16, 32, 40, 64, 128, 256, 512, 1024, 2048 and 8192MB respectively.
 @discussion Eureka Baseband only.
 */
- (CAMReturnBool*)setDIAGLoggingSize:(NSNumber *)size;

/*!
 @method     getDIAGLoggingSize
 @abstract   Get DIAG Logging History size.
 @discussion Eureka Baseband only.
 */
- (CAMReturnString*)getDIAGLoggingSize;

/*!
 @method    setCSILoggingEnabled
 @abstract  Enable/Disable CSI Logging.
 */
- (CAMReturnBool*)setCSILoggingEnabled:(NSNumber*)flag;

/*!
 @method     setMobileAnalyzerLoggingEnabled.
 @deprecated This method is deprecated.
 */
- (CAMReturnBool*)setMobileAnalyzerLoggingEnabled:(NSNumber*)flag __attribute__((deprecated));

/*!
 @method     setDIAGLoggingEnabled
 @abstract   Enable/Disable DIAG Logging.
 @discussion Eureka Baseband only.
 */
- (CAMReturnBool*)setDIAGLoggingEnabled:(NSNumber*)flag;

/*!
 @method     setDIAGLoggingSwitch.
 @abstract   DIAG Logging switch Enable/Disable ONLY.
 @discussion Applicable only to Eureka(MAV) Baseband. History Size and "Enabled During AP Sleep" switches are NOT changed.
 */
- (CAMReturnBool*)setDIAGLoggingSwitch:(NSNumber*)flag;

/*!
 @method     setDIAGLoggingEnabledDuringSleep
 @abstract   Enable/Disable DIAG Logging during sleep.
 @discussion Eureka Baseband only.
 */
- (CAMReturnBool*)setDIAGLoggingEnabledDuringSleep:(NSNumber*)flag;

/*!
 @method     DIAGLoggingEnabledDuringSleep
 @abstract   Checks if DIAG Logging during sleep is enabled or disabled.
 @discussion Eureka Baseband only.
 */
- (CAMReturnInteger*)DIAGLoggingEnabledDuringSleep;

/*!
 @method     setArtemisLoggingEnabled.
 @deprecated This method is deprecated.
 */
- (CAMReturnBool*)setArtemisLoggingEnabled:(NSNumber*)flag  __attribute__((deprecated));

/*!
 @method     isSTTLoggingEnabled.
 @abstract   Checks if STT Logging is Enabled/Disabled.
 @discussion Applicable only to Karoo(ICE) Baseband.
 */
- (CAMReturnBool*)isSTTLoggingEnabled;

/*!
 @method     setSTTLoggingEnabled.
 @abstract   STT Logging Enable/Disable.
 @discussion Applicable only to Karoo(ICE) Baseband. Sets history size to 2048 MB and enables switch "Enabled During AP Sleep".
 */
- (CAMReturnBool*)setSTTLoggingEnabled:(NSNumber*)flag;

/*!
 @method     setSTTLoggingSwitch.
 @abstract   STT Logging switch Enable/Disable ONLY.
 @discussion Applicable only to Karoo(ICE) Baseband. History Size and "Enabled During AP Sleep" switches are NOT changed.
 */
- (CAMReturnBool*)setSTTLoggingSwitch:(NSNumber*)flag;

/*!
 @method     setSTTLoggingSize.
 @abstract   Set STT Logging Size.
 @discussion Applicable only to Karoo(ICE) Baseband. Valid sizes are 8, 16, 32, 64, 128, 256, 512, 1024, 2048 and 8192MB respectively
 */
- (CAMReturnBool*)setSTTLoggingSize:(NSNumber *)size;

/*!
 @method     getSTTLoggingSize.
 @abstract   Get STT Logging Size.
 @discussion Karoo(ICE) Baseband only.
 */
- (CAMReturnString*)getSTTLoggingSize;

/*!
 @method     setSTTLoggingEnabledDuringSleep.
 @abstract   Enable/Disable STT Logging During Sleep.
 @discussion Karoo(ICE) Baseband only.
 */
- (CAMReturnBool*)setSTTLoggingEnabledDuringSleep:(NSNumber *)flag;

/*!
 @method     STTLoggingEnabledDuringSleep.
 @abstract   Returns whether STT Logging During Sleep is enabled/disabled.
 @discussion Karoo(ICE) Baseband only.
 */
- (CAMReturnString*)STTLoggingEnabledDuringSleep;

/*!
 @method     setABMLogging.
 @abstract   Enable/disable ABM Logging.
*/
- (CAMReturnBool*)setABMLogging:(NSNumber *)enabled;

/*!
 @method     setABMLoggingHistory.
 @abstract   Set ABM Logging History size. Valid sizes are 4, 8, 16, 32, 64, 128, 256, 512 MB respectively.
 */
- (CAMReturnBool*)setABMLoggingHistory:(NSNumber *)size;

/*!
 @method     getABMLoggingHistory.
 @abstract   Get ABM Logging History size.
 */
- (CAMReturnString*)getABMLoggingHistory;

/*!
 @method     ABMLoggingEnabled.
 @abstract   Returns if ABM Logging is enabled/disabled.
 */
- (CAMReturnBool*)ABMLoggingEnabled;

- (CAMReturnInteger*)isCoreDumpEnabled;
- (CAMReturnVoid*)setCoreDumpEnabled:(NSNumber*)flag;
- (CAMReturnVoid*)dumpBasebandStateWithReason:(NSString*)description;
- (CAMReturnVoid*)forceCoreDump;
- (CAMReturnInteger*)dumpCount;
- (CAMReturnBool*)waitForAllDumps:(NSNumber*)timeout;
- (CAMReturnBool*)removeBasebandLogs;
- (CAMReturnArray *)availableDMCFilters;
- (CAMReturnBool *)setSecondaryDMCFilter:(NSString*)filterName;
- (CAMReturnString *)secondaryDMCFilter;
- (CAMReturnVoid*)setFakePrimaryDNSKey:(NSString*)key;
- (CAMReturnVoid*)setFakeSecondaryDNSKey:(NSString*)key;
- (CAMReturnVoid*)setAudioLoggingEnabled:(NSNumber*)flag;
- (CAMReturnBool*)getAudioLoggingEnabled;
- (CAMReturnString*)dumpAudioLogs;

#pragma mark -
#pragma mark ETLTool
/*!
 @method    sendATCommand
 @abstract	Send the ATCommand to the baseband.
 @param     atcommand - the AT command to send to baseband
 @discussion Only available on Eureka baseband.
 */
- (CAMReturnString*)sendATCommand:(NSString*)atcommand;

/*!
 @method    clearMRU
 @abstract	This will clear most recent registration information from baseband.
 @discussion Only available on Eureka baseband.
 */
- (CAMReturnBool*)clearMRU;

#pragma mark -
#pragma mark QMI
/*!
 @method    enableQMI
 @param     state - Set to Yes to enable QMI, set to No to disble QMI
 @abstract  Tear down CommCenter and bring up QMI transport for coreautomationd, so that coreautomationd is able to send QMI message to baseband
 @discussion After CommCenter is down, coreautomationd is responsible for all the baseband communication. UI will not reflect any baseband status, and all other CoreTelephony API will not work until QMI has been disabled.
 */
- (CAMReturnBool*)enableQMI:(NSNumber*)state;
/*!
 @method    isQMIEnabled
 @abstract	Returns whether QMI is enabled by coreautomationd.
 */
- (CAMReturnBool*)isQMIEnabled;

#pragma mark -
#pragma mark Utility
- (CAMReturnBool*)phoneNumber:(NSString*)digits isEqualTo:(NSString*)otherDigits;
/*!
 @method    setPhoneNumber
 @abstract	Set PhoneNumber on the phone.
 @discussion Phone must be a GSM phone. Undefined behavior on CDMA phones. Also if it's a live device, the phone number might get changed back to original number from the network.
 */
- (CAMReturnBool*)setPhoneNumber:(NSString*)digits;

#pragma  mark -
#pragma mark Notification Recording
- (CAMReturnVoid*)startRecordingNotificationsWithName:(NSString*)name;
- (CAMReturnArray*)recordedNotifications;
- (CAMReturnVoid*)clearRecordedNotifications;

#pragma  mark -
#pragma mark APN
- (CAMReturnInteger*)pdpCount;
- (CAMReturnDictionary*)networkInfoForPdp:(NSNumber*)pdp;
- (CAMReturnString*)apnForPdp:(NSNumber*)pdp;
- (CAMReturnVoid*)setApn:(NSString*)apn forPdp:(NSNumber*)pdp;

#pragma  mark -
#pragma mark Visual Voicemail
/*!
 @method    setVoicemailProvisionalPassword
 @abstract	Provide voicemail password in case visual voicemail need it.
 @discussion If password is not provided or wrong and Visual voicemail is not subscribed yet. Visual voicemail will never get subscribed. If passowrd is wrong and Visual voicemail is subscribed, visual voicemail will become unsubscribed after password expires.
 */
- (CAMReturnVoid*)setVoicemailProvisionalPassword:(NSString*)password;
/*!
 @method    waitForIncomingVoicemail
 @abstract	wait from incoming voicemail from CoreTelephony framework. 
 @discussion This API works even if carrier doesn't support Visual voicemail. Also, because this is from CoreTelephony framework, a incoming voicemail doesn't mean there is a incoming visual voicemail. The incoming visual voicemail might come later due to processing by Visua Voicemail framework. If you want to check incoming visual voicemail, please use waitForIncomingVisualVoicemail: instead.
 */
- (CAMReturnBool*)waitForIncomingVoicemail:(NSNumber*)timeout;
/*!
 @method    waitForVoicemailSubscription
 @abstract	wait for voicemail to be subscribed.
 */
- (CAMReturnBool*)waitForVoicemailSubscription:(NSNumber*)timeout;
/*!
 @method    waitForIncomingVisualVoicemail
 @abstract	wait for incoming Visual voicemail.
 @discussion This waits for an incoming visual voicemail from Visual Voicemail framework.
 */
- (CAMReturnBool*)waitForIncomingVisualVoicemail:(NSNumber *)timeout;
/*!
 @method    voicemailProvisionalPassword
 @abstract	returns current voicemail Provisional password
 */
- (CAMReturnString*)voicemailProvisionalPassword;
/*!
 @method    mailboxRequiresSetup
 @abstract	returns whether the mailbox requires setup. If mailbox is not setup, others can not leave voicemail on this account.
 */
- (CAMReturnBool*)mailboxRequiresSetup;
/*!
 @method    setupMailboxWithPassword
 @abstract	Setup mailbox with a password. 
 */
- (CAMReturnVoid*)setupMailboxWithPassword:(NSString*)password;
/*!
 @method    getVoicemails
 @abstract	Return all the visual voicemails.
 */
- (CAMReturnArray*)getVoicemails;
/*!
 @method    trashedVoicemails
 @abstract	Return all trashed visual voicemails.
 */
- (CAMReturnArray*)trashedVoicemails;
/*!
 @method    clearAllTrashedVoicemails
 @abstract  Delete all trashed voicemails.
 */
- (CAMReturnVoid*)clearAllTrashedVoicemails;
/*!
 @method    deleteTrashedVoicemail
 @abstract  Delete a trashed voicemail.
 */
- (CAMReturnVoid*)deleteTrashedVoicemail:(NSDictionary*)voicemail;
/*!
 @method    voicemailWithIdentifier
 @abstract	Return the visual voicemail with id
 @return    a dictionary containing informations about the visual voicemail of id
 */
- (CAMReturnDictionary*)voicemailWithIdentifier:(NSNumber*)identifier;
/*!
 @method    moveVoicemailToTrash
 @abstract	Move the visual voicemail to trash.
 @discussion This method has been changed to synchronous. It will wait up to 60 seconds for the action to complete.
 <rdar://problem/15385315> getTelephony().MoveVoicemailToTrash(i) failed to clean mail in inbox
 */
- (CAMReturnVoid*)moveVoicemailToTrash:(NSDictionary*)voicemail;
/*!
 @method    moveVoicemailFromTrash
 @abstract  Move the visual voicemail from trash.
 @discussion This method has been changed to synchronous. It will wait up to 60 seconds for the action to complete.
 <rdar://problem/15385315> getTelephony().MoveVoicemailToTrash(i) failed to clean mail in inbox
 */
- (CAMReturnVoid*)moveVoicemailFromTrash:(NSDictionary*)voicemail;
/*!
 @method    isVoicemailRead
 @abstract  Return whether the voicemail is read
 */
- (CAMReturnBool*)isVoicemailRead:(NSDictionary*) voicemail;
/*!
 @method    isVoicemailTrashed
 @abstract  Return whether the voicemail is trashed
 */
- (CAMReturnBool*)isVoicemailTrashed:(NSDictionary*) voicemail;
/*!
 @method    isVoicemailOnline
 @abstract  If Visual voicemail is not online, it doesn't have data access.
 */
- (CAMReturnBool*)isVoicemailOnline;
/*!
 @method    isVoicemailOfflineDueToRoaming
 @abstract  Return whether voicemail is offline due to Roaming. (No data access)
 */
- (CAMReturnBool*)isVoicemailOfflineDueToRoaming;
/*!
 @method    isVoicemailSubscribed
 @abstract	Returns whether voicemail is subscribed.
 @discussion If voicemail is not subscribed, it will not able to check voicemail.
 */
- (CAMReturnBool*)isVoicemailSubscribed;

/*!
 @method    mailboxUsage
 @abstract	Returns the number of visual voicemail in the mailbox.
 */
- (CAMReturnInteger*)mailboxUsage;
/*!
 @method    changeMailboxPasswordTo:withOldPassword:
 @abstract	Change mailbox password. If oldPassword is not correct, the change will fail.
 @param newPassword - new voicemail password
 @param oldPassword - old voicemail password
 */
- (CAMReturnVoid*)changeMailboxPasswordTo:(NSString*)newPassword withOldPassword:(NSString*)oldPassword;

#pragma mark -
#pragma mark Data Usage per APP
- (CAMReturnArray*)dataUsagePerApp;
- (CAMReturnVoid*)resetDataUsage;

/*!
 @method    setCellularDataStatus:forApp
 @abstract	Enable Cellular Data switch for this specific app.
 @discussion appName is the name of the APP. Currently supporting: iTunes, FaceTime, Passbook Updates and Reading List.
 */
- (CAMReturnVoid*)setCellularDataStatus:(NSNumber*)enable forApp:(NSString*)appName;

/*!
 @method    cellularDataStatusForApp
 @abstract	Get Cellular Data switch status for this specific app.
 @discussion appName is the name of the APP. Currently supporting: iTunes, FaceTime, Passbook Updates and Reading List.
 */
- (CAMReturnBool*)cellularDataStatusForApp:(NSString*)appName;

/*!
 @method    totalUsage
 @abstract	Get total cellular usage 
 @discussion return a dictionary of
        DnlinkBytes, DnlinkPackets, UplinkBytes, UplinkPackets,
 */
- (CAMReturnDictionary*)totalUsage;


#pragma mark -
#pragma mark IMS Capability

/*!
 @method     IMSRegistrationStatus
 @abstract   Checks for IMS registration status
 @discussion returns IMS registration status type. Return values of status could be one of Unknown, OFF, SMS Only, Voice and SMS.
 */
- (CAMReturnInteger*)IMSRegistrationStatus;

/*!
 @method     enableVoLTE:
 @deprecated This method is deprecated. Please use setVoLTEEnabled: instead.
 */
- (CAMReturnVoid*)enableVoLTE:(NSNumber*)enable __attribute__((deprecated));

/*!
 @method     setVoLTEEnabled:
 @abstract   Enable/Disable VoLTE IMS feature
 @discussion Turn On/Off VoLTE on supported devices
 */
- (CAMReturnVoid*)setVoLTEEnabled:(NSNumber*)enabled;

/*!
 @method   VoLTEEnabled
 @abstract Returns True if VoLTE is enabled and False if VoLTE is disabled
 */
- (CAMReturnBool*)VoLTEEnabled;

/*!
 @method	supportWiFiCalling
 @abstract	Checks if device supports WiFi Calling
 */
- (CAMReturnBool*)supportsWiFiCalling;

/*!
 @method     setWiFiCallingEnabled:
 @abstract   Enable/Disable WiFiCalling feature
 @discussion Turn On/Off WiFi Calling on supported devices
 */
- (CAMReturnVoid*)setWiFiCallingEnabled:(NSNumber*)enabled;

/*!
 @method   WiFiCallingEnabled
 @abstract Returns True if WiFiCalling is enabled and False if WiFiCalling is disabled
 */
- (CAMReturnBool*)WiFiCallingEnabled;

/*!
 @method     setThumperEnabled:
 @abstract   Enable/Disable Thumper feature
 @discussion Turn On/Off Thumper on supported devices
 */
- (CAMReturnVoid*)setThumperEnabled:(NSNumber*)enabled;

/*!
 @method   ThumperEnabled
 @abstract Returns True if Thumper is enabled and False if Thumper is disabled
 */
- (CAMReturnBool*)ThumperEnabled;

/*!
 @method   ThumperiCloudReset
 @abstract Reset iCloud KVS for Thumper
 */
- (CAMReturnVoid*)ThumperiCloudReset;

/*!
 @method   isThumperAllowed
 @abstract Checks if Thumper is allowed
 */
- (CAMReturnBool*)isThumperAllowed;

/*!
 @method   getThumperCarrierName
 @abstract Returns Thumper Carrier name from Thumper secondary device.
 */
- (CAMReturnString*)getThumperCarrierName;

/*!
 @method   getThumperDeviceInfo
 @abstract Returns Thumper Device Information(Account-id/device-id/available slots/mdn) on Primary/Secondary Thumper device.
 */
- (CAMReturnDictionary*)getThumperDeviceInfo;

/*!
 @method    controlThumperDevice:withDeviceID
 @abstract	Controls the Thumper Device State.
 @discussion Supported operations are: ADD(0), REMOVE(1) Thumper service for a Secondary Device on Primary. ENABLE(3), DISABLE(4) Thumper service on Secondary device.
 */
- (CAMReturnVoid*)controlThumperDevice:(NSNumber*)oper withDeviceID:(NSString*)deviceID;

/*!
 @method carrierBundleVersion
 @abstract Returns Carrier Bundle version in a string, nil if it cannot be found
 */
- (CAMReturnString*)carrierBundleVersion;

/*!
 @method     setMMSEnabled:
 @abstract   Enables or disables MMS on devices that support MMS.
 */
-(CAMReturnVoid*)setMMSEnabled:(NSNumber*)enabled;

/*!
 @method     MMSEnabled:
 @abstract   Returns whether or not MMS is enabled.
 */
-(CAMReturnBool*)MMSEnabled;

/*!
 @method IMSRegistrationContextStatus
 @abstract Returns whether IMS registration is on WiFi (2), Cellular (1), or None (0)
 */
- (CAMReturnInteger*)IMSRegistrationContextStatus;

/*!
 @method IMSTransportType
 @abstract Returns IMS Phone Call Transport type is on WiFi or Cellular
*/
- (CAMReturnString*)IMSTransportType;

/*!
 @method waitForIMSConnectionEvent
 @abstract Wait for IMS Connection Notification event type
 */
-(CAMReturnDictionary*)waitForIMSConnectionEvent:(NSNumber*)timeout;

/*!
 @method waitForIMSTransportRegistrationStatus:transportStatus
 @abstract  Wait for IMS Registration Status notification
 @discussion Wait for IMS Connection type(connectionType): kCTIMSConnectionTypeWifi or kCTIMSConnectionTypeCellular, alongwith the IMS connection status(transportStatus): UP(1) or DOWN(0).
 */
- (CAMReturnBool*)waitForIMSTransportRegistrationStatus:(NSString*)connectionType transportStatus:(NSNumber*)transportStatus withTimeout:(NSNumber*)timeout;

/*!
 @method registrationInfo
 @abstract Returns the registration dictionary
 */
- (CAMReturnDictionary*)registrationInfo;

/*!
 @method pullThumperCall
 @abstract Detects and initiates Thumper Call Handoff
 */
- (CAMReturnBool*)pullThumperCall:(NSNumber*)timeout;

/*!
 @method pullRelayCall
 @abstract Pull Relay call to Host
 */
- (CAMReturnBool*)pullRelayCall:(NSNumber*)timeout;
@end
