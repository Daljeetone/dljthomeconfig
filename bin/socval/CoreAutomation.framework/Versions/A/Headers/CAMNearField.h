//
//  CAMNearField.h
//  CoreAutomation
//
//  Created by Anirban Maiti on 08/20/2013.
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//
#import <Availability.h> // So we get TARGET_OS_IPHONE
#import <Foundation/Foundation.h>
#import "CAMReturnValues.h"

#define kCAMNearFieldShortName nfc
#define kCAMNearFieldESEIndex @0
#define kCAMNearFieldICFIndex @1

@protocol CAMNearField <NSObject>
@optional

#pragma mark -
#pragma mark Callback Recording
- (CAMReturnArray *)callbackList;
- (CAMReturnVoid *)clearCallbackList;

#pragma mark -
#pragma mark Secure Element Info
- (CAMReturnString *)serialNumber:(NSNumber *)useIcf;
- (CAMReturnBool *)isInRestrictedMode:(NSNumber *)useIcf;

#pragma mark -
#pragma mark Hardware Event Listener
- (CAMReturnVoid *)registerHardwareEventListener;
- (CAMReturnVoid *)unregisterHardwareEventListener;

#pragma mark -
#pragma mark Applet Management
- (CAMReturnArray *)allApplets;
- (CAMReturnArray *)allAppletIdentifiers;
- (CAMReturnDictionary *)appletWithIdentifier:(NSString *)theIdentifier;
- (CAMReturnBool *)deleteAppletsWithIdentifiers:(NSArray *)theIdentifiers queueServerConnection:(NSNumber *)queueConnection;
- (CAMReturnBool *)deleteAllApplets; // Defaults to queueConnection YES.
- (CAMReturnBool *)deleteAllAppletsAndQueueServerConnection:(NSNumber *)queueConnection;
- (CAMReturnData *)signChallenge:(NSData *)challenge;

- (CAMReturnDictionary *)stateInformation:(NSNumber *)useIcf;

#pragma mark -
#pragma mark Secure Element Communication
- (CAMReturnData *)transceiveWithSecureElement:(NSData *)data useIcf:(NSNumber *)useIcf; // You must call stopSecureElementSession when finished sending data to the SE.
- (CAMReturnVoid *)stopSecureElementSession;
- (CAMReturnBool *)secureElementSessionRunning;

#pragma mark -
#pragma mark Deprecated SE Methods
// By adpoting NFSecureElementManagerSession <rdar://24761027>, I had to switch many of the functions that require useIcf from being deprecated to not deprecated.

// These don't care about which SE you're trying to talk to, they'll automatically deal with all applets on all SE's.
- (CAMReturnArray *)allApplets:(NSNumber *)useIcf __attribute__((deprecated));
- (CAMReturnArray *)allAppletIdentifiers:(NSNumber *)useIcf __attribute__((deprecated));
- (CAMReturnDictionary *)appletWithIdentifier:(NSString *)theIdentifier useIcf:(NSNumber *)useIcf __attribute__((deprecated));
- (CAMReturnBool *)deleteAppletsWithIdentifiers:(NSArray *)theIdentifiers queueServerConnection:(NSNumber *)queueConnection useIcf:(NSNumber *)useIcf __attribute__((deprecated));
- (CAMReturnBool *)deleteAllApplets:(NSNumber *)useIcf __attribute__((deprecated)); // Defaults to queueConnection YES.
- (CAMReturnBool *)deleteAllAppletsAndQueueServerConnection:(NSNumber *)queueConnection useIcf:(NSNumber *)useIcf __attribute__((deprecated));
- (CAMReturnData *)signChallenge:(NSData *)challenge useIcf:(NSNumber *)useIcf __attribute__((deprecated));

// These still care about which SE, so you should still specify useIcf.
- (CAMReturnString *)serialNumber __attribute__((deprecated));
- (CAMReturnBool *)isInRestrictedMode __attribute__((deprecated));
- (CAMReturnDictionary *)stateInformation __attribute__((deprecated));
- (CAMReturnData *)transceiveWithSecureElement:(NSData *)data __attribute__((deprecated)); // You must call stopSecureElementSession when finished sending data to the SE.

#pragma mark -
#pragma mark Remote Admin Management
- (CAMReturnBool *)queueServerConnection:(NSString *)theIdentifer;
- (CAMReturnBool *)queueServerConnectionForApplets:(NSArray *)theAppletIdentifiers;
- (CAMReturnVoid *)startRemoteAdminEventListener;
- (CAMReturnVoid *)stopRemoteAdminEventListener;
- (CAMReturnDictionary *)registrationInfo;
- (CAMReturnBool *)setRegistrationInfo:(NSDictionary *)theInfo;
- (CAMReturnBool *)connectToServer:(NSString *)theIdentifier;

/*!
 @method    getSELDInfoForBroker
 @abstract  Retrieve SELD info dictionary for transmitting to the Broker during device registration call.
 @result    Returns dictionary of information that would be passed to the broker.
 */
- (CAMReturnDictionary *)getSELDInfoForBroker;

/*!
 @method    getAPNPublicToken
 @abstract  Get public token use for APN push notification messaging.
 @result    Public token represented in a hex string.
 */
- (CAMReturnString *)getAPNPublicToken;

/*!
 @method    primaryRegionTopic
 @abstract  Returns the push topic name of the primary region.
 @result    NSString of the push topic name, which is a valid key value in the registration info dictionary. nil if error occurs, empty string if no primary region is set.
 */
- (CAMReturnString *)primaryRegionTopic;

#pragma mark -
#pragma mark Field Detect Session
- (CAMReturnVoid *)startFieldDetectSession;
- (CAMReturnVoid *)stopFieldDetectSession;
- (CAMReturnBool *)fieldDetectSessionRunning;
- (CAMReturnBool *)fieldPresent;
- (CAMReturnBool *)setFieldDetectEnabled:(NSNumber *)enabled;

- (CAMReturnVoid *)startFieldDetect:(NSNumber *)theSource idleExit:(NSNumber *)supportsIdleExit __attribute__((deprecated)); // Please use startFieldDetectSession instead.
- (CAMReturnVoid *)stopFieldDetect __attribute__((deprecated)); // Please use stopFieldDetectSession instead.
- (CAMReturnInteger *)fieldDetectSuspended __attribute__((deprecated)); // Please use fieldPresent instead.
- (CAMReturnInteger *)isFieldDetectRunning __attribute__((deprecated)); // Please use fieldDetectRunning instead.

#pragma mark -
#pragma mark ECommerce Payment Session
- (CAMReturnDictionary *)performECommercePayment:(NSDictionary *)theRequest authorization:(NSData *)theAuthorization;

- (CAMReturnDictionary *)authorizeEcommerceTransaction:(NSDictionary *)theRequest authorization:(NSData *)theSSEHandle __attribute__((deprecated)); // Please use performECommercePayment:authorization: instead.

#pragma mark -
#pragma mark Contactless Payment Session
- (CAMReturnVoid *)startContactlessPaymentSession;
- (CAMReturnVoid *)stopContactlessPaymentSession;
- (CAMReturnBool *)contactlessPaymentSessionRunning;
- (CAMReturnBool *)setActivePaymentApplet:(NSString *)theIdentifier makeDefault:(NSNumber *)makeDefault authorization:(NSData *)theAuthorization;
- (CAMReturnBool *)startCardEmulationWithAuthorization:(NSData *)theAuthorization;
- (CAMReturnDictionary *)defaultApplet;

- (CAMReturnVoid *)authorizeContactlessPaymentWithAuthToken:(NSData *)theSSEHandle __attribute__((deprecated));
- (CAMReturnVoid *)deauthorizeContactlessPayment __attribute__((deprecated));

#pragma mark -
#pragma mark Contactless Payment Event Reconstruction
- (CAMReturnData *)startEventData;
- (CAMReturnData *)endEventData;
- (CAMReturnVoid *)clearEventData;

#pragma mark -
#pragma mark Loyalty And Payment Session
- (CAMReturnVoid *)startLoyaltyAndPaymentSession;
- (CAMReturnVoid *)stopLoyaltyAndPaymentSession;
- (CAMReturnBool *)loyaltyAndPaymentSessionRunning;
- (CAMReturnBool *)setActivePaymentApplet:(NSString *)theIdentifier makeDefault:(NSNumber *)makeDefault __attribute__((deprecated));
- (CAMReturnBool *)setActivePaymentApplet:(NSString *)theIdentifier;
- (CAMReturnBool *)startCardEmulation:(NSNumber *)mode authorization:(NSData *)theAuthorization;
- (CAMReturnBool *)startDeferredCardEmulation:(NSNumber *)mode authorization:(NSData *)theAuthorization;
- (CAMReturnBool *)setHostCards:(NSArray *)theCards;
- (CAMReturnBool *)setLoyaltyNotReady;
- (CAMReturnString *)felicaAppletState:(NSString *)theIdentifier;

#pragma mark -
#pragma mark Reader Session
- (CAMReturnVoid *)startReaderSession;
- (CAMReturnVoid *)stopReaderSession;
- (CAMReturnVoid *)readerSessionRunning;

- (CAMReturnBool *)startPolling;
- (CAMReturnBool *)stopPolling;
- (CAMReturnBool *)connectTag:(NSDictionary *)tagDict;
- (CAMReturnBool *)disconnectTag;
- (CAMReturnDictionary *)checkNdefSupportsReadAndWrite;
- (CAMReturnBool *)checkPresence;
- (CAMReturnBool *)formatNdefWithKey:(NSData *)key;
- (CAMReturnBool *)ndefWriteRecords:(NSArray *)typeDataPairs;
- (CAMReturnString *)ndefRead;
- (CAMReturnData *)transceive:(NSData *)capdu;
- (CAMReturnDictionary *)readerSessionFelicaState;

#pragma mark -
#pragma mark Value Added Service Session
- (CAMReturnVoid *)startValueAddedServiceSession;
- (CAMReturnVoid *)stopValueAddedServiceSession;
- (CAMReturnBool *)valueAddedServiceSessionRunning;

#pragma mark -
#pragma mark Blessed User
/*!
 @method    checkUserBlessing:
 @abstract  Checks if the user with given UUID is blessed.
 @param     uuid - User's UUID to check against the stored blessed user UUID.
 @result    NFResultSuccess if the current user is blessed, NFResultNoBlessedUser if there is no blessed user set, NFResultSecurityViolation if the user is not the blessed user, NFResultSEIDChangedError if the hardware has changed under us.
 */
- (CAMReturnInteger *)checkUserBlessing:(NSString *)uuid;

/*!
 @method    setBlessedUser:
 @abstract  Sets up the blessed user. The blessed user is the only user which can use the SE.
 @param     userUUID - The UUID of the new user. Pass nil to reset the blessed user. This can only be reset by the current blessed user or the admin user.
 @param     externalAuthorization - A NSData representing the external authorization.
 @result    Returns nil or NFResultSuccess on success.
 */
- (CAMReturnInteger *)setBlessedUser:(NSString *)userUUID withAuthorization:(NSData *)externalAuthorization;

/*!
 @method    blessedUser
 @abstract  Reads the blessed user from storage. This does not mean the user can use the SE - the SEID or cards might have changed since the last boot.
 @result    The UUID of the blessed user.
 */
- (CAMReturnString *)blessedUser;

#pragma mark -
#pragma mark Express Transit/Access
- (CAMReturnBool *)setExpressTransitApplet:(NSString *)theIdentifier authorization:(NSData *)theAuthorization;
- (CAMReturnBool *)setExpressModesEnabled:(NSNumber *)enable;
- (CAMReturnBool *)requireAuthorizationForAllAppletsExcept:(NSString *)theIdentifier;
/*!
 @method    disableAuthorizationForIdentifier
 @abstract  Sets authTransient to False for an applet where authTransient is configurable
 @param     theIdentifier - string of the applet identifier (AID)
 @param     theAuthorization - Authorization handle data
 @result    Returns YES if authTransient is disabled on the specified applet identifier
 */
- (CAMReturnBool *)disableAuthorizationForIdentifier:(NSString *)theIdentifier authorization:(NSData *)theAuthorization;
- (CAMReturnBool *)expressModesEnabled;
- (CAMReturnBool *)isExpressAppletTypeSupported:(NSNumber *)type;
- (CAMReturnString *)expressTransitIdentifier;
- (CAMReturnBool *)addExpressApplet:(NSString *)theIdentifier type:(NSNumber *)appletType authorization:(NSData *)theAuthorization;
- (CAMReturnBool *)removeExpressApplet:(NSString *)theIdentifier type:(NSNumber *)appletType;
- (CAMReturnBool *)removeExpressApplet:(NSString *)theIdentifier type:(NSNumber *)appletType restoreAuthorization:(NSNumber *)restoreAuthorization;
- (CAMReturnArray *)expressAccessIdentifiers; // array of strings

#pragma mark -
#pragma mark Plastic Card Mode
/*!
 @method    enablePlasticCardMode:
 @abstract  Puts session into a mode where it does not send transaction events or take any automatic actions based on field on/off conditions
 @param     enable - integer of boolean, 1 to enable, 0 to disable.
 @result    Returns YES if the requested enable/disable was sucessful, otherwise NO
 */
- (CAMReturnBool *)enablePlasticCardMode:(NSNumber *)enable;

#pragma mark -
#pragma mark Seshat
/*!
 @method    startSeshatSession
 @abstract  Starts a session, if one isn't already running. If one is running, does nothing. You need to start a session before you can do anything with it.
 @result    Raises an error if it couldn't start the session.
 */
- (CAMReturnVoid *)startSeshatSession;
/*!
 @method    stopSeshatSession
 @abstract  Calls endSession assigns nil to the session held by coreautomationd. You need to stop a session when you're done with it; open sessions may prevent other sessions from starting.
 @result    None
 */
- (CAMReturnVoid *)stopSeshatSession;
/*!
 @method    seshatSessionRunning
 @abstract  Returns YES/NO if coreautomationd has a session.
 @result    None
 */
- (CAMReturnBool *)seshatSessionRunning;

/*!
 @method    allocateSlot:
 @abstract  Operation 0, aka Initialize User. Note that authorizingUser and authorizingUserToken are optional.
 @param     slotIndex - the index of the slot to allocate
 @param     authorizingUser - The index of the slot authorizing the addition of a new user. Pass in NF_SLOT_RESERVED to omit
 @param     authorizingUserToken - The token (16 bytes) associated with the autorizing user. Pass nil to omit.
 @result    Dictionary of @{"nfResult":NSNumber, "appletResult":NSNumber, "outToken":NSData, "outWriteCount":NSNumber}
 */
- (CAMReturnDictionary *)allocateSlot:(NSNumber *)slotIndex
                      authorizingUser:(NSNumber *)authorizingUser
                 authorizingUserToken:(NSData *)authorizingUserToken;

/*!
 @method    derive:
 @abstract  Operation 1, This command derives the SE secret from the given SHA256 of the passcode. This subject to the counter (aka failure count) being less than 10.
 @param     slotIndex - the index of the slot to use for derivation
 @param     userHash - The SHA256 of the passcode (input data of 32 bytes) on which to perform AES-CMAC.
 @result    Dictionary of @{"nfResult":NSNumber, "appletResult":NSNumber, "outData":NSData, "outWriteCount":NSNumber}
 */
- (CAMReturnDictionary *)derive:(NSNumber *)slotIndex
                       userHash:(NSData *)userHash;

/*!
 @method    resetCounter:
 @abstract  Operation 2. This command resets the counter for a given user. SEP will hold the token for each user as a Class A item, so this will ensure that the user’s keybag was successfully unlocked. The SE has no other method to verify the passcode.
 @param     slotIndex - the index of the slot to use for derivation
 @param     userToken - The token to authenticate the user
 @result    Dictionary of @{"nfResult":NSNumber, "appletResult":NSNumber, "outWriteCount":NSNumber}
 */
- (CAMReturnDictionary *)resetCounter:(NSNumber *)slotIndex
                            userToken:(NSData *)userToken;

/*!
 @method    authorizeUpdate:
 @abstract  Operation 3. This command authorizes a JCOP update to proceed without wiping the user data. The token is used as proof of user consent.
 @param     authorize - whether or not to authorize the update
 @param     slotIndex - the index of the slot to use for derivation. If authorize is FALSE, caller can pass NF_SLOT_RESERVED for slotIndex
 @param     userToken - The token to authenticate the user. If authorize is FALSE, caller can pass nil to userToken.
 @result    Dictionary of @{"nfResult":NSNumber, "appletResult":NSNumber, "outWriteCount":NSNumber}
 */
- (CAMReturnDictionary *)authorizeUpdate:(NSNumber *)authorize
                               slotIndex:(NSNumber *)slotIndex
                               userToken:(NSData *)userToken;

/*!
 @method    deleteSlot:
 @abstract  Operation 4. This command kills a user (or all users) without reallocating a new one
 @param     slotIndex - the index of the slot to use for derivation. Pass NF_SLOT_RESERVED to delete all slots.
 @result    Dictionary of @{"nfResult":NSNumber, "appletResult":NSNumber, "outWriteCount":NSNumber}
 */
- (CAMReturnDictionary *)deleteSlot:(NSNumber *)slotIndex;

/*!
 @method    getSeshatData:
 @abstract  Gets data from the Seshat Applet
 @result    Dictionary of @{"nfResult":NSNumber, "appletResult":NSNumber, "slotCounters":NSData, "updateKUD":NSNumber, "outWriteLimit":NSNumber, "outWriteCount":NSNumber}
 */
- (CAMReturnDictionary *)getSeshatData;

/*!
 @method    seshatResultIsTransientError:
 @abstract  Checks if the error is transient. If @YES, retry later.
 @param     nfResult - the nfResult part of a SeshatResult
 @param     appletResult - the appletResult part of a SeshatResult
 @result    YES if the error is transient (stack init failure). NO if the error means the operation will never succeed with the current parameters.
 */
- (CAMReturnBool *)seshatResultIsTransientError:(NSNumber *)nfResult appletResult:(NSNumber *)appletResult;

/*!
 @method    seshatObliterate:
 @abstract  Deletes all applets and seshat slots
 @result    Dictionary of @{"nfResult":NSNumber, "appletResult":NSNumber}
 */
- (CAMReturnDictionary *)seshatObliterate;

/*!
 @method    secureElementBootHistory
 @abstract  Retrieves an array containing the primary secure element's last 30 boot statuses. Values are NSNumber objects, 0 indicates a normal boot, 1 indicates a boot into restricted mode. Array size can be anywhere from 0-30 depending upon how many boots have occurred. Returns an error/nil array on failure.
 @result    Array of NSNumbers on success, error/nil array on failure.
 */
- (CAMReturnArray *)secureElementBootHistory;

/*!
 @method    preWarm
 @abstract  Starts the hardware initialization process so that the hardware is ready to handle sessions.
    This keeps the hardware powered on and loaded until first unlock of the device occurs.

 @result    A BOOL value indicating success or failure
 */
- (CAMReturnBool *)preWarm;

#pragma mark - NFNdefTagSession
/*!
 @method    startTagSession
 @abstract  Starts a session, if one isn't already running. If one is running, does nothing. You need to start a session before you can do anything with it.
 @result    Raises an error if it couldn't start the session.
 */
- (CAMReturnVoid *)startTagSession;

/*!
 @method    stopTagSession
 @abstract  Calls endSession assigns nil to the session held by coreautomationd. You need to stop a session when you're done with it; open sessions may prevent other sessions from starting.
 @result    None
 */
- (CAMReturnVoid *)stopTagSession;

/*!
 @method    tagSessionRunning
 @abstract  Returns YES/NO if coreautomationd has a session.
 @result    None
 */
- (CAMReturnBool *)tagSessionRunning;

/*!
 @method    startTagEmulation
 @abstract  Starts tag emulation using the provided ndef data
 @param     ndefData - The raw NDEF data to use during emulation
 @result    YES on success, NO on failure
 */
- (CAMReturnBool *)startTagEmulation:(NSData *)ndefData;

/*!
 @method    stopTagEmulation
 @abstract  Stops emulation
 @result    YES on success, NO on failure
 */
- (CAMReturnBool *)stopTagEmulation;

/*!
 @method    setEmulatedTagData
 @abstract  Sets the raw NDEF messages bytes to be used during emulation
 @param     ndefData - NSData containing the raw NDEF bytes
 @result    YES on success, NO on failure
 */
- (CAMReturnBool *)setEmulatedTagData:(NSData *)ndefData;

/*!
 @method    getEmulatedTagData
 @abstract  Returns the raw bytes currently held by the session
 @result    Valid on success, nil on failure
 */
- (CAMReturnData *)getEmulatedTagData;

/*!
 @method    setEmulatedTagWritable
 @abstract  Allows the session to present as a writeable NDEF tag (default NO)
 @param     enable - BOOL value indicating if the tag should be writeable (default NO)
 @result    YES on success, NO on failure
 */
- (CAMReturnBool *)setEmulatedTagWritable:(NSNumber *)enable;

/*!
 @method    startBluetoothLEPairingWithDeviceAddress:role:oobDataDictionary:
 @abstract  Starts Static Handover tag emulation for Bluetooth LE Pairing
 @param     deviceAddress - Bluetooth LE device address. 7 bytes in length.
     The data format is specified in Supplement to Bluetooth Core Specification (CSS) section 1.16.
     If value is nil device address will be excluded from the tag.
 @param     leRole - 1 byte LE role value (tag type 0x1C).  Refer to [BLUETOOTH_CORE] specification on definition.
 @param     dataDictionary - Array of NSData object storing list of optional Bluetooth AD entries.
     Each NSData object shall comply to the Advertising and Scan Response Data format ([BLUETOOTH_CORE],
     Volume 3, Part C, Section 11): AD Length field of 1 byte, AD Type field, and AD Data field.
 @result    YES on success, NO on failure
 */
- (CAMReturnBool *)startBluetoothLEPairingWithDeviceAddress:(NSData *)deviceAddress
                                                       role:(NSNumber *)leRole
                                            optionalOOBData:(NSArray *)dataDictionary;

/*!
 @method    startBluetoothLESecureConnectionWithDeviceAddress:role:oobDataDictionary:
 @abstract  Starts Static Handover tag emulation for Bluetooth Pairing using LE Secure Connections OOB model [Bluetooth Core 4.2, Volume 3, Part H, Section 2]
 @param     deviceAddress - Bluetooth device address. 6 bytes in length.
 @param     dataDictionary - Array of NSData object storing list of optional Bluetooth EIR entries.
     Each NSData object shall comply to the Extended Inquiry Response (EIR) format ([BLUETOOTH_CORE],
     Volume 3, Part C, Section 8): EIR Data Length field, EIR Data Type field, and EIR Data field.
 @result    YES on success, NO on failure
 */
- (CAMReturnBool *)startBluetoothLESecureConnectionWithDeviceAddress:(NSData *)deviceAddress
                                                     optionalOOBData:(NSArray *)dataDictionary;

#pragma mark - NFCISO15693ReaderSession (aka Abbott tag)
/*!
 @method    startISO15693ReaderSession
 @abstract  Starts a session, if one isn't already running. If one is running, does nothing. You need to start a session before you can do anything with it.
 @result    Raises an error if it couldn't start the session.
 */
- (CAMReturnVoid *)startISO15693ReaderSession;

/*!
 @method    stopISO15693ReaderSession
 @abstract  Calls endSession assigns nil to the session held by coreautomationd. You need to stop a session when you're done with it; open sessions may prevent other sessions from starting.
 @result    None
 */
- (CAMReturnVoid *)stopISO15693ReaderSession;

/*!
 @method    ISO15693ReaderSessionRunning
 @abstract  Returns YES/NO if coreautomationd has a session.
 @result    None
 */
- (CAMReturnBool *)ISO15693ReaderSessionRunning;

/*!
 @method ISO15693ReaderSessionIsReady
 @abstract The RF discovery polling begins immediately when a reader session is activated successfully.
     The readerSession:didDetectTags: will be called when a tag is detected.
 @result YES if the reader session is started and ready to use.
 */
- (CAMReturnBool *)ISO15693ReaderSessionIsReady;

/*!
 @method    sendCustomCommandWithConfiguration
 @param     commandConfiguration - Dictionary representing configuration for the Manufacturer Custom Command.
    Expected format: @{
        @"manufacturerCode":@(NSUInteger),
        @"customCommandCode":@(NSUInteger),
        @"requestParameters":NSData,
        @"maximumRetries":@(NSUInteger),
        @"retryInterval":@(NSTimeInterval)
    }
 @result NSData of the tag's response, or an error from the tag if it responded with one, or kCAMDErrorTimeout error if the tag did not respond
 */
- (CAMReturnData *)sendCustomCommandWithConfiguration:(NSDictionary *)commandConfiguration toNFCISO15693TagWithSerial:(NSData *)icSerialNumber;

/*!
 @method    readMultipleBlocksWithConfiguration
 @param     readConfiguration - Dictionary representing configuration for the Read Multiple Blocks command.
    Expected format: @{
        @"rangeLoc":@(NSUInteger),
        @"rangeLen":@(NSUInteger),
        @"chunkSize":@(NSUInteger),
        @"maximumRetries":@(NSUInteger),
        @"retryInterval":@(NSTimeInterval)
    }
 @result NSData of the tag's response, or an error from the tag if it responded with one, or kCAMDErrorTimeout error if the tag did not respond
 */
- (CAMReturnData *)readMultipleBlocksWithConfiguration:(NSDictionary *)readConfiguration fromNFCISO15693TagWithSerial:(NSData *)icSerialNumber;

#pragma mark NFPeerPaymentSession
/*!
 @method    startPeerPaymentSession
 @abstract  Starts a session, if one isn't already running. If one is running, does nothing. You need to start a session before you can do anything with it.
 @result    Raises an error if it couldn't start the session.
 */
- (CAMReturnVoid *)startPeerPaymentSession;
/*!
 @method    stopPeerPaymentSession
 @abstract  Calls endSession assigns nil to the session held by coreautomationd. You need to stop a session when you're done with it; open sessions may prevent other sessions from starting.
 @result    None
 */
- (CAMReturnVoid *)stopPeerPaymentSession;
/*!
 @method    peerPaymentSessionRunning
 @abstract  Returns YES/NO if coreautomationd has a session.
 @result    None
 */
- (CAMReturnBool *)peerPaymentSessionRunning;

/*!
 @method    performPeerPayment
 @abstract  Performs a SURF payment. User should startPeerPaymentSession before this, and stopPeerPaymentSession after.
 @param     paymentRequest - Dictionary representing an NFPeerPaymentRequest object.
     Structure of NFPeerPaymentRequest:
         {"topUpRequest":NFECommercePaymentRequest, "transferRequest":NFPeerPaymentTransferRequest}
     Structure of NFECommercePaymentRequest:
         {"appletIdentifier":NSString, "merchantData":NSData, "currencyCode":NSString, "countryCode":NSString, "transactionAmount":NSString, "transactionDate":NSString, "merchantCapabilities":NSNumber, "unpredictableNumber":NSNumber}
     Structure of NFPeerPaymentTransferRequest:
         {"transactionAmount":NSString, "appleTransactionHash":NSString, "publicTransactionHash":NSString, "transactionDate":NSString, "transactionCurrency":NSString, "transactionCountry":NSString, "nonce":NSData, "peerPaymentCertificate":NSData}
     
     topUpRequest is optional.
     transactionDate strings should be in RFC 3339 format: yyyy-MM-dd'T'HH:mm:ssZZZZZ. Example: 1996-12-19T16:39:57-08:00.
     transactionAmount strings will be passed through [NSDecimalNumber decimalNumberWithString:transactionAmount].
 @param     authorization - Valid NSData from Mesa's credentialhandle.
 @result    Dictionary representing an NFPeerPaymentResponse.
    Structure of NFPeerPaymentResponse:
        {"transactionData":NSData, "certificates":NSDictionary}
    Structure of certificates dictionary:
        {"RSA":NSString, "ECC":NSString, "ECDSA":NSString, "ECKA":NSString}
    certificates dictionary may not contain all elements.
 */
- (CAMReturnDictionary *)performPeerPayment:(NSDictionary *)paymentRequest authorization:(NSData *)authorization;

/*!
 @method    performPeerPaymentEnrollment
 @abstract  Enrolls the device in SURF. Will start and end an NFSecureElementManagerSession for you.
 @param     enrollmentRequest - Dictionary representing an NFPeerPaymentEnrollmentRequest object.
     Structure of NFPeerPaymentEnrollmentRequest:
         {"authenticationToken":NSString}
     authenticationToken comes from Accounts.framework.
 
 @result    Dictionary representing an NFPeerPaymentEnrollmentResponse.
     Structure of NFPeerPaymentEnrollmentResponse:
         {"prePeerPaymentCertificate":NSData, "certificates":NSDictionary}
     Structure of certificates dictionary:
         {"CASDCertificate":NSData}
     certificates dictionary may not contain all elements.
 */
- (CAMReturnDictionary *)performPeerPaymentEnrollment:(NSDictionary *)enrollmentRequest;

#pragma mark -
#pragma mark Button Press API
- (CAMReturnVoid *)enableQuickPayForButtonPress:(NSString *)theAID checkRestricted:(NSNumber *)check performActivate:(NSNumber *)enable performAuth:(NSNumber *)auth startEmulation:(NSNumber *)emu useIcf:(NSNumber *)useIcf;
- (CAMReturnInteger *) buttonDoublePressCount;

/*!
 @method    listenForDoubleButtonPressWithinTimeout:
 @abstract  Listens for the double button press on the Apple Watch via the HID usage kHIDUsage_Csmr_ALDigitalWallet. This API is operating at the HID layer so buttonDoublePressCount may not reflect changes seen here.
 @param     seconds - Number of seconds to wait for the double button press HID event.
 @return    Returns YES if the double button press occurred with the timeout. Otherwise NO is returned. If an error occurs, it will be returned.
 */
- (CAMReturnBool *)listenForDoubleButtonPressWithinTimeout:(NSNumber *)seconds;

#pragma mark -
#pragma mark Utility APIs
- (CAMReturnArray *)performanceData;
- (CAMReturnVoid *)stockholmLastError;
- (CAMReturnVoid *)insertLogText:(NSString *)text toFile:(NSString *)fileWithPath;
@end
