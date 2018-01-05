//
//  CAMPassbook.h
//  coreautomationd
//
//  Created by Aleksey Korenkov on 3/23/15.
//  Copyright 2015 Apple, Inc. All rights reserved.
//
//

#import <Foundation/Foundation.h>
#import "CAMReturnValues.h"

#define kCAMPassbookShortName passbook

@protocol CAMPassbook
@optional

/*!
 @method    addPKPassFromFile
 @abstract  Adds Passbook pass from pkpass binary file
 @param     path - path to pkpass binary file
 @return    Returns true if the pass with given path was added
 */
- (CAMReturnBool *)addPKPassFromFile:(NSString *)path;


/*!
 @method    removePassWithPassTypeIdentifier
 @abstract  Call removePassWithPassTypeIdentifier with useWatchConnection == @NO
 @return    None
 */
- (CAMReturnBool *)removePassWithPassTypeIdentifier:(NSString *)typeIdentifier serialNumber:(NSString *)serial;

/*!
 @method    removePassWithPassTypeIdentifier
 @abstract  Removes the given credit/debit card.
 @param     typeIdentifier - Obtained via [PKPass passTypeIdentifier]
 @param     serial - Obtained by [PKPass serialNumber]
 @return    Returns true if the pass existed and was removed successfully.
 */
- (CAMReturnBool *)removePassWithPassTypeIdentifier:(NSString *)typeIdentifier serialNumber:(NSString *)serial onWatch:(NSNumber *)useWatchConnection;

/*!
 @method    removeAllPKPasses
 @abstract  Call removeAllPKPassesOnWatch with useWatchConnection == @NO
 @return    None
 */
- (CAMReturnVoid *)removeAllPKPasses __attribute__((deprecated));

/*!
 @method    removeAllPKPassesOnWatch
 @abstract  Removes all Passbook's passes
 @param     useWatchConnection - True to do it on the paired watch, False to do it on this device.
 @return    None
 */
- (CAMReturnVoid *)removeAllPKPassesOnWatch:(NSNumber *)useWatchConnection;

/*!
 @method    getAllPKPasses
 @abstract  Call getAllPKPassesOnWatch with useWatchConnection == @NO
 @return    Array of dictionaries of @{passTypeIdentifier:NSString, serialNumber:NSString, description:NSString, primaryAccountNumberSuffix:NSString}
 */
- (CAMReturnArray *)getAllPKPasses __attribute__((deprecated));

/*!
 @method    getAllPKPassesOnWatch
 @abstract  Gets all the PKPass objects from the local or companion's pass library. PKPaymentPasses will include the PAN Suffix; other passes will have @"" for that key.
 @param     useWatchConnection - True to do it on the paired watch, False to do it on this device.
 @return    Array of dictionaries of @{passTypeIdentifier:NSString, serialNumber:NSString, description:NSString, primaryAccountNumberSuffix:NSString}
 */
- (CAMReturnArray *)getAllPKPassesOnWatch:(NSNumber *)useWatchConnection;

/*!
 @method    getCardsOnFile
 @abstract  Call getCardsOnFile with useWatchConnection == @NO
 @return    Array of dictionaries of @{description:NSString, sanitizedPrimaryAccountNumber:NSString, expiration:NSString}
 */
- (CAMReturnArray *)getCardsOnFile;

/*!
 @method    getCardsOnFileOnWatch
 @abstract  Gets all the cards on file (aka PKPaymentRemoteCredentials) on the local or companion PKPaymentWebService. Assumes you're logged into iCloud.
 @param     useWatchConnection - True to do it on the paired watch, False to do it on this device.
 @return    Array of dictionaries of @{description:NSString, sanitizedPrimaryAccountNumber:NSString, expiration:NSString}
 */
- (CAMReturnArray *)getCardsOnFileOnWatch:(NSNumber *)useWatchConnection;


/*!
 @method    provisionCardWithDictionary
 @abstract  Provisions the given credit/debit card.
 @param     provisioningOptions - Dictionary describing the provisioning operation to perform.
 
 @discussion Valid key/value pairs for provisioningOptions:
    NSString *cardholderName - name of the person that owns the card.
    NSString *primaryAccountNumber - the long number from the front of the card.
    NSString *expirationDate - expiration date, format is MM/YY.
    NSString *securityCode - Security/verification code from back of card.
    NSNumber *onWatch - True to provision it for the watch, False to do it on the phone. Default: False.
    NSNumber *withCardOnFile - True to provision card on file, False to create a new one. Default: False.
    NSNumber *waitForActivation - True to wait for the card to become active, False to return immediately (ie, Yellow Flow). Default: True.

    NSNumber *useInApp - True to perform InApp provisioning, False to perform Wallet-style.
        If True, you must provide either a kistaCardID or both cardPNO and cardFlow or encryptedData, ephemeralKey, and activationData.
        If True, you do not need to specify name, PAN, expiration, or security code. Default: False.
    NSNumber *kistaCardID - Specify the card that Passman should reserve from Kista for inApp provisioning.
    NSString *cardPNO - Specify the card that Passman should reserve from Kista for inApp provisioning, eg Argon.
    NSString *cardFlow - Specify the card that Passman should reserve from Kista for inApp provisioning, eg green.

    NSData *encryptedData - The encryptedData that you would have received from Kista
    NSData *ephemeralKey - The ephemeralKey that you would have received from Kista
    NSData *activationData - The activationData that you would have received from Kista
    NSString *nonceStr - The nonce used to generate the encryptedData/ephemeralKey/activationData. See generateSignedNonceOnWatch.
    NSData *publicKeyHash - The public key hash from the nonce. See generateSignedNonceOnWatch.
 
    NSNumber *forwardCardToWatch - True to forward a card that's ALREADY PROVISIONED ON the companion, over to the watch. Default: False.
    NSString *passTypeIdentifier - Identifier of the pass to forward to the watch.
    NSString *serialNumber - Serial number of the pass to forward to the watch.
 @return    Returns dictionary of @{passTypeIdentifier:NSString, serialNumber:NSString, termsURL:NSString} if the credit/debit card was successfully provisioned.
 */
- (CAMReturnDictionary *)provisionCardWithDictionary:(NSDictionary *)provisioningOptions;

/*!
 @method    provisionCardWithCardholderName
 @abstract  See documentation for provisionCardWithDictionary.
 */
- (CAMReturnDictionary *)provisionCardWithCardholderName:(NSString *)cardholderName primaryAccountNumber:(NSString *)accountNumber expirationDate:(NSString *)expiration securityCode:(NSString *)csc onWatch:(NSNumber *)useWatchConnection withCardOnFile:(NSNumber *)useCardOnFile waitForActivation:(NSNumber *)shouldWaitForActivation __attribute__((deprecated));

/*!
 @method    provisionCardWithCardholderName
 @abstract  See documentation for provisionCardWithDictionary.
 */
- (CAMReturnDictionary *)provisionCardWithCardholderName:(NSString *)cardholderName primaryAccountNumber:(NSString *)accountNumber expirationDate:(NSString *)expiration securityCode:(NSString *)csc onWatch:(NSNumber *)useWatchConnection withCardOnFile:(NSNumber *)useCardOnFile __attribute__((deprecated));

/*!
 @method    provisionCardWithCardholderName
 @abstract  See documentation for provisionCardWithDictionary.
 */
- (CAMReturnDictionary *)provisionCardWithCardholderName:(NSString *)cardholderName primaryAccountNumber:(NSString *)accountNumber expirationDate:(NSString *)expiration securityCode:(NSString *)csc onWatch:(NSNumber *)useWatchConnection __attribute__((deprecated));

/*!
 @method    provisionCardWithCardholderName
 @abstract  See documentation for provisionCardWithDictionary.
 */
- (CAMReturnDictionary *)provisionCardWithCardholderName:(NSString *)cardholderName primaryAccountNumber:(NSString *)accountNumber expirationDate:(NSString *)expiration securityCode:(NSString *)csc __attribute__((deprecated));

/*!
 @method    requestVerificationCodeForPassWithPassTypeIdentifier
 @abstract  Requests a verification code for the given credit/debit card, using the given channel. It's up to the user to actually obtain the code somehow (parse email, parse SMS, etc)
 @param     typeIdentifier - Obtained via [PKPass passTypeIdentifier]
 @param     serial - Obtained by [PKPass serialNumber]
 @param     channel - The verification channel to use. Valid values are "email" "sms" "inbound-call" "outbound-call" "bank-app" "bank-statement" "other".
 @param     useWatchConnection - True to do it on the paired watch, False to do it on this device.
 @return    Returns true if the request went through successfully.
 */
- (CAMReturnBool *)requestVerificationCodeForPassWithPassTypeIdentifier:(NSString *)typeIdentifier serialNumber:(NSString *)serial preferredChannel:(NSString *)channel onWatch:(NSNumber *)useWatchConnection;
- (CAMReturnBool *)requestVerificationCodeForPassWithPassTypeIdentifier:(NSString *)typeIdentifier serialNumber:(NSString *)serial preferredChannel:(NSString *)channel __attribute__((deprecated));

/*!
 @method    submitVerificationCode
 @abstract  Submits a verification code for the given credit/debit card.
 @param     verificationCode - The verification code that you want to submit.
 @param     typeIdentifier - Obtained via [PKPass passTypeIdentifier]
 @param     serial - Obtained by [PKPass serialNumber]
 @param     useWatchConnection - True to do it on the paired watch, False to do it on this device.
 @return    Returns true if the code was accepted.
 */
- (CAMReturnBool *)submitVerificationCode:(NSString *)verificationCode forPassWithPassTypeIdentifier:(NSString *)typeIdentifier serialNumber:(NSString *)serial onWatch:(NSNumber *)useWatchConnection;
- (CAMReturnBool *)submitVerificationCode:(NSString *)verificationCode forPassWithPassTypeIdentifier:(NSString *)typeIdentifier serialNumber:(NSString *)serial __attribute__((deprecated));

/*!
 @method    registerDevice
 @abstract  Call registerDeviceOnWatch with useWatchConnection == @NO
 @return    True if successful.
 */
- (CAMReturnBool *)registerDevice __attribute__((deprecated));

/*!
 @method    registerDeviceOnWatch
 @abstract  Registers the device with the Apple Pay servers, using the current iCloud account.
 @param     useWatchConnection - True to do it on the paired watch, False to do it on this device.
 @return    True if successful.
 */
- (CAMReturnBool *)registerDeviceOnWatch:(NSNumber *)useWatchConnection;


/*!
 @method    registerDevice
 @abstract  Queries the TSM for updates, as though a payment push was received. Used for debugging/troubleshooting.
 */
- (CAMReturnVoid *)simulatePaymentPush;

/*!
 @method    optionsForMerchantSession
 @abstract  Uses the merchantSession to retrieve Warsaw Instruction packets from the server.
 @param     merchantSessionDict - Dictionary describing a merchantSession.
             Sample: @{@"merchantIdentifier":@"f3e08a1b70...",
                 @"merchantSessionIdentifier":@"5e156c866f...",
                 @"domainName":@"syndrome.apple.com",
                 @"nonce":"e02c0633",
                 @"epochTimestamp":@1467069509979,
                 @"displayName":@"Syndrome",
                 @"signature":@"308006092a..."
             }
 @param     secureElementIdentifier - SEID to pass along to server
 @param     amount - Amount to charge, format is "12.34"
 @param     currencyCode - Type of currency for the payment, such as "USD"
 @return    Dictionary of @{@"instructions":NSData, @"signature":NSData}
 */
- (CAMReturnDictionary *)optionsForMerchantSession:(NSDictionary *)merchantSessionDict
                           secureElementIdentifier:(NSString *)secureElementIdentifier
                                            amount:(NSDecimalNumber *)amount
                                      currencyCode:(NSString *)currencyCode;

/*!
 @method    completeInAppPaymentWithPassTypeIdentifier
 @abstract  Creates an in app payment request and uses a merchantSession to complete it.
 @param     typeIdentifier - Obtained via [PKPass passTypeIdentifier]
 @param     serial - Obtained by [PKPass serialNumber]
 @param     theAuthorization - Valid NSData from Mesa's credentialhandle.
 @param     amount - Amount to charge, format is "12.34"
 @param     currencyCode - Type of currency for the payment, such as "USD"
 @param     countryCode - Country for the payment, such as "US"
 @param     merchantSessionDict - Dictionary describing a merchantSession.
                Sample: @{@"merchantIdentifier":@"f3e08a1b70...",
                          @"merchantSessionIdentifier":@"5e156c866f...",
                          @"domainName":@"syndrome.apple.com",
                          @"nonce":"e02c0633",
                          @"epochTimestamp":@1467069509979,
                          @"displayName":@"Syndrome",
                          @"signature":@"308006092a..."
                        }
 @return    [PKPaymentToken paymentData] after it's been through a call to completeSession
 */
- (CAMReturnData *)completeInAppPaymentWithPassTypeIdentifier:(NSString *)typeIdentifier
                                                serialNumber:(NSString *)serial
                                               authorization:(NSData *)theAuthorization
                                                      amount:(NSString *)amount
                                                    currency:(NSString *)currencyCode
                                                     country:(NSString *)countryCode
                                             merchantSession:(NSDictionary *)merchantSessionDict;

/*!
 @method    topUpPaymentPassWithPassTypeIdentifier
 @abstract  Tops up a transit pass, using a payment pass as the source of funds.
 @param     topUpTypeIdentifier - Pass to top up, obtained via [PKPass passTypeIdentifier]
 @param     topUpSerial - Pass to top up, obtained by [PKPass serialNumber]
 @param     paymentTypeIdentifier - Pass to pay with, obtained via [PKPass passTypeIdentifier]
 @param     paymentSerial - Pass to pay with, obtained by [PKPass serialNumber]
 @param     theAuthorization - Valid NSData from Mesa's credentialhandle.
 @param     amount - Amount to charge, format is "12.34". Be aware that if the currency is JPY, don't use cents.
 @return    YES if it worked, NO if it didn't.
 */
- (CAMReturnBool *)topUpPaymentPassWithPassTypeIdentifier:(NSString *)topUpTypeIdentifier
                                        topUpSerialNumber:(NSString *)topUpSerial
                           usingPaymentPassTypeIdentifier:(NSString *)paymentTypeIdentifier
                                        usingSerialNumber:(NSString *)paymentSerial
                                            authorization:(NSData *)theAuthorization
                                                   amount:(NSString *)amount;
/*!
 @method    rewrapInAppPayment
 @abstract  Creates an inapp payment request and rewraps it.
 @param     paymentDict - Dictionary of parameters describing the inapp payment.
 @discussion Valid key/value pairs for paymentDict:
     NSString *typeIdentifier - Obtained via [PKPass passTypeIdentifier]
     NSString *serial - Obtained by [PKPass serialNumber]
     NSData *theAuthorization - Valid NSData from Mesa's credentialhandle.
     NSString *amount - Amount to charge, format is "12.34"
     NSString *currencyCode - Type of currency for the payment, such as "USD"
     NSString *countryCode - Country for the payment, such as "US"
     NSString *capability - Merchant capabilities. "3DS", "EMV", or "both".
     NSString *merchantID - Merchant identifier, such as "up2048"
     NSNumber *returnToken - True to return the PKPaymentToken itself, not just its paymentData and TransactionIdentifier. THIS WON'T WORK when called across lockdown, because CAM can't serialize the PKPaymentToken properly. Only use this parameter internally.
 @return    Dictionary of the rewrapped token's information, @{@"paymentData":NSData*, @"transactionIdentifier":NSData*}. If you passed in paymentDict[@"returnToken"] == @YES, it will return @{@"paymentToken":PKPaymentToken*}.
 */
- (CAMReturnDictionary *)rewrapInAppPayment:(NSDictionary *)paymentDict;

/*!
 @method    rewrapInAppPaymentWithPassTypeIdentifier
 @abstract  Calls into rewrapInAppPayment: with a hardcoded merchantID of up2048.
 @return    [PKPaymentToken paymentData] after it's been through a rewrap
 */
- (CAMReturnData *)rewrapInAppPaymentWithPassTypeIdentifier:(NSString *)typeIdentifier serialNumber:(NSString *)serial authorization:(NSData *)theAuthorization amount:(NSString *)amount currency:(NSString *)currencyCode country:(NSString *)countryCode capability:(NSString *)capability;

// Convenience wrapper. Harcoded to amount=12.34, currencyCode=USD, countryCode=US
- (CAMReturnData *)rewrapInAppPaymentWithPassTypeIdentifier:(NSString *)typeIdentifier serialNumber:(NSString *)serial authorization:(NSData *)theAuthorization;

/*!
 @method    passForUniqueIdentifier
 @abstract  Utility method for translating a unique identifier back to the pass it represents.
 @param     uniqueIdentifier - Obtained via PKGeneratePassUniqueID()
 @return    Dictionary of @{passTypeIdentifier:NSString, serialNumber:NSString, description:NSString, primaryAccountNumberSuffix:NSString}
 */
- (CAMReturnDictionary *)passForUniqueIdentifier:(NSString *)uniqueIdentifier;

/*!
 @method    uniqueIdentifierForPassTypeIdentifier
 @abstract  Utility method for translating a pass type identifier and serial number into its unique identifier.
 @param     typeIdentifier - Obtained via [PKPass passTypeIdentifier]
 @param     serial - Obtained by [PKPass serialNumber]
 @return    NSString of pass's unique id, given by PKGeneratePassUniqueID().
 */
- (CAMReturnString *)uniqueIdentifierForPassTypeIdentifier:(NSString *)typeIdentifier serialNumber:(NSString *)serial;

/*!
 @method    getDefaultExpressFelicaTransitPass
 @abstract  Queries PKPaymentService for the default express transit pass
 @return    Dictionary of @{passTypeIdentifier:NSString, serialNumber:NSString, description:NSString, primaryAccountNumberSuffix:NSString}
 */
- (CAMReturnDictionary *)getDefaultExpressFelicaTransitPass;

/*!
 @method    setDefaultExpressFelicaTransitPassWithTypeIdentifier
 @abstract  Sets the default express transit pass to the uniqueID of the given pass.
 @param     typeIdentifier - Obtained via [PKPass passTypeIdentifier]
 @param     serial - Obtained by [PKPass serialNumber]
 @param     theAuthorization - Valid NSData from Mesa's credentialhandle.
 @return    YES if it worked, NO if it didn't.
 */
- (CAMReturnBool *)setDefaultExpressFelicaTransitPassWithTypeIdentifier:(NSString *)typeIdentifier serialNumber:(NSString *)serial authorization:(NSData *)theAuthorization;

/*!
 @method    expressPassesInformationForMode
 @abstract  Queries PKPaymentService for the default express passes. If the output has nil for the passUniqueIdentifier and the paymentApplicationIdentifier, express is off for that mode.
 @param     expressMode - String describing the express mode, such as @"access.hid.apple". Pass nil (pyobjc bridge: kCAMRemoteNilArgumentKey == @"argument-is-nil") for all modes.
 @return    Array of dictionaries of @{passUniqueIdentifier:NSString, paymentApplicationIdentifier:NSString, expressMode:NSString}
 */
- (CAMReturnArray *)expressPassesInformationForMode:(NSString *)expressMode;

/*!
 @method    setExpressWithPassInformation
 @abstract  Sets the default express pass according to the given PKExpressPassInformation.
 @param     expressPassInfo - Dictionary representing a PKExpressPassInformation object. Format is @{passUniqueIdentifier:NSString, paymentApplicationIdentifier:NSString, expressMode:NSString}.
 @param     theAuthorization - Valid NSData from Mesa's credentialhandle.
 @return    YES if it worked, NO if it didn't.
 */
- (CAMReturnBool *)setExpressWithPassInformation:(NSDictionary *)expressPassInfo authorization:(NSData *)theAuthorization;

/*!
 @method    getDefaultPaymentPass
 @abstract  Queries CFPreferences for the default payment pass
 @return    Dictionary of @{passTypeIdentifier:NSString, serialNumber:NSString, description:NSString, primaryAccountNumberSuffix:NSString}
 */
- (CAMReturnDictionary *)getDefaultPaymentPass;

/*!
 @method    setDefaultPaymentPassWithTypeIdentifier
 @abstract  Sets the default payment pass to the uniqueID of the given pass.
 @param     typeIdentifier - Obtained via [PKPass passTypeIdentifier]
 @param     serial - Obtained by [PKPass serialNumber]
 */
- (CAMReturnVoid *)setDefaultPaymentPassWithTypeIdentifier:(NSString *)typeIdentifier serialNumber:(NSString *)serial;

/*!
 @method    setPassSettings
 @abstract  Sets the back-of-pass settings as specified by the settingsDict argument.
 @param     settingsDict - A dictionary of settingName/settingValue pairs. Valid keys: @"setShowInLockScreenEnabled", @"setAutomaticUpdatesEnabled", @"setNotificationServiceUpdatesEnabled", @"setAutomaticPresentationEnabled". Valid values: @0 or @1.
 @param     typeIdentifier - Obtained via [PKPass passTypeIdentifier]
 @param     serial - Obtained by [PKPass serialNumber]
 @return    Dictionary of @{settingName, settingResult} pairs, where settingResult is @0 or @1.
 */
- (CAMReturnDictionary *)setPassSettings:(NSDictionary *)settingsDict withPassTypeIdentifier:(NSString *)typeIdentifier serialNumber:(NSString *)serial;

/*!
 @method    resetPassSettingsWithPassTypeIdentifier
 @abstract  Resets all pass settings to default.
 @param     typeIdentifier - Obtained via [PKPass passTypeIdentifier]
 @param     serial - Obtained by [PKPass serialNumber]
 @return    Dictionary of @{settingName, settingResult} pairs, where settingResult is @0 or @1.
 */
- (CAMReturnBool *)resetPassSettingsWithPassTypeIdentifier:(NSString *)typeIdentifier serialNumber:(NSString *)serial;

/*!
 @method    remoteDevices
 @abstract  Calls [PKContinutyPaymentService updateDevices], and returns an array of descriptions of the found PKRemoteDevices.
 @return    Array of NSStrings describing the remote devices.
 */
- (CAMReturnArray *)remoteDevices;

/*!
 @method    sendPaymentRequest
 @abstract  Creates and sends a PKRemotePaymentRequest to the specified remote device. Uses the remote device's default payment card as the payment method.
 @param     paymentDict - Dictionary of parameters describing the inapp payment.
 @param     remoteIDSUniqueID - The "device ID" string from a PKRemoteDevice.
 @discussion Valid key/value pairs for paymentDict:
     NSString *typeIdentifier - Obtained via [PKPass passTypeIdentifier]
     NSString *serial - Obtained by [PKPass serialNumber]
     NSString *amount - Amount to charge, format is "12.34"
     NSString *currencyCode - Type of currency for the payment, such as "USD"
     NSString *countryCode - Country for the payment, such as "US"
     NSString *capability - Merchant capabilities. "3DS", "EMV", or "both".
     NSString *merchantID - Merchant identifier, such as "up2048"
 @return    Dictionary of the rewrapped token's information, @{@"paymentData":NSData*, @"transactionIdentifier":NSData*}
 */
- (CAMReturnDictionary *)sendPaymentRequest:(NSDictionary *)paymentDict toRemoteDevice:(NSString *)remoteIDSUniqueID;


/*!
 @method    setCachedAuthData
 @abstract  Caches an authorization token for later use in authorizing a received PKPaymentRequest.
 @param     auth - Valid NSData from Mesa's credentialhandle.
 @return    N/A
 */
- (CAMReturnVoid *)setCachedAuthData:(NSData *)auth;

/*!
 @method    generateSignedNonceOnWatch
 @abstract  Uses the device's PKPaymentWebService to get a nonce and sign it.
 @param     useWatchConnection - True to do it on the paired watch, False to do it on this device.
 @return    A dictionary of nonce and certificate information, @{@"nonce":NSData*, @"nonceStr":NSString*, @"nonceSignature":NSData*, @"nonceSigStr":NSString*, @"certificates":NSArray* of NSData*, @"certArrayInStringFormat":NSString*, @"publicKeyHash":NSData*}
 */
- (CAMReturnDictionary *)generateSignedNonceOnWatch:(NSNumber *)useWatchConnection;

@end
