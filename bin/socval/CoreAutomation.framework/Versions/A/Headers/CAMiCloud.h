//
//  CAMiCloud.h
//  coreautomationd
//
//  Created by Wayne Finlay on 3/31/14.
//
//

#import <Foundation/Foundation.h>
#import "CAMReturnValues.h"

#define kCAMiCloudShortName iCloud

@protocol CAMiCloud
@optional

/*!
 @method    addiCloudAccount:password:withTimeout:
 @abstract  Adds an existing iCloud account to the device. It will not create an iCloud account on the server.
 @param		username - User name of the account ie: johnappleseed@icloud.com
            password - Password for the user name
            timeout - timeout for iCloud operations to complete
 @return	Returns account identifier if the account was added
 */
- (CAMReturnString *)addiCloudAccount:(NSString *)username password:(NSString *)password withTimeout:(NSNumber *)timeout;

/*!
 @method    removeiCloudAccount
 @abstract  Removes an iCloud account from the device. Don't worry, it will not delete the account from the server!
 @param		identifier - account identifier
            timeout - timeout for iCloud operations to complete
 @return	Returns true if the account was removed
 */
- (CAMReturnBool *)removeiCloudAccount:(NSString *)identifier withTimeout:(NSNumber *)timeout;
/*!
 @method    removeAlliCloudAccounts
 @abstract  Removes all iCloud accounts from the device. Don't worry, it will not delete the accounts from the server!
            This method is deprecated from 2/27/2017. Some accounts need further authentication before removal. And the API 
            was not being supplied with password. Hence,accounts like FMiP would not get deleted as a part of this API call.
            Hence, it was decided to deprecate this API call.
 @param		timeout for iCloud operations to complete
 @return	Returns true if the accounts were removed
 */
- (CAMReturnBool *)removeAlliCloudAccounts:(NSNumber *)timeout __attribute__((deprecated));

/*!
 @method    makeAccountPrimaryForIdentifier:
 @abstract  makes account primary
 @param		identifier - account identifier
 @return	Returns true if account was made primary
 */
- (CAMReturnBool *)makeAccountPrimaryForIdentifier:(NSString *)identifier;

/*!
 @method    setEnabled:forDataclass:accountIdentifier:
 @abstract  enables/disables dataclass for account
 @param		enabled - enable/disable flag
            dataclass - the dataclass
            identifier - account identifier
            timeout for service to signal the change
 @return	Returns true if dataclass was enabled/disabled for account
 */
- (CAMReturnBool *)setEnabled:(NSNumber *)enabled forDataclass:(NSString *)dataclass accountIdentifier:(NSString *)identifier withTimeout:(NSNumber *)timeout;

/*!
 @method    iCloudAccounts
 @abstract  Returns an array of all iCloud accounts on the device
 @return	Returns array of iCloud account identifiers
 */
- (CAMReturnArray *)iCloudAccounts;

/*!
 @method    usernameForAccountIdentifier:
 @abstract  Returns the iCloud account's identifier
 @param		identifier - account identifier
 @return	Returns a username string
 */
- (CAMReturnString *)usernameForAccountIdentifier:(NSString *)identifier;

/*!
 @method    identifierForUsername:
 @abstract  Returns the iCloud account's identifier
 @param     username - account username
 @return	Returns an identifier string
 */
- (CAMReturnString *)identifierForUsername:(NSString *)username;

/*!
 @method    setAccountProperty:forKey:accountIdentifier:
 @abstract  sets a account property
 @param     property - account property value
            key - account property key
            identifier - account identifier
 @return	Returns true if setting the account property was successful
 */
- (CAMReturnBool *)setAccountProperty:(NSObject *)property forKey:(NSString *)key accountIdentifier:(NSString *)identifier;

/*!
 @method    setAccountPropertyDictionary:forKey:accountIdentifier:
 @abstract  sets a account property using a dictionary
 @param     property - account property value to a dictionary
            key - account property key
            identifier - account identifier
 @return	Returns true if setting the account property was successful
 */
- (CAMReturnBool *)setAccountPropertyDictionary:(NSDictionary *)property forKey:(NSString *)key accountIdentifier:(NSString *)identifier;

/*!
 @method    setAccountPropertyArray:forKey:accountIdentifier:
 @abstract  sets a account property using a array
 @param     property - account property value to a dictionary
            key - account property key
            identifier - account identifier
 @return	Returns true if setting the account property was successful
 */
- (CAMReturnBool *)setAccountPropertyArray:(NSArray *)property forKey:(NSString *)key accountIdentifier:(NSString *)identifier;

/*!
 @method    setAccountPropertyString:forKey:accountIdentifier:
 @abstract  sets a account property to a string value
 @param     property - account property value as a string
            key - account property key
            identifier - account identifier
 @return	Returns true if setting the account property was successful
 */
- (CAMReturnBool *)setAccountPropertyString:(NSString *)property forKey:(NSString *)key accountIdentifier:(NSString *)identifier;

/*!
 @method    setAccountPropertyValue:forKey:accountIdentifier:
 @abstract  sets a account property to a number value
 @param     property - account property value as a number
            key - account property key
            identifier - account identifier
 @return	Returns true if setting the account property was successful
 */
- (CAMReturnBool *)setAccountPropertyValue:(NSNumber *)property forKey:(NSString *)key accountIdentifier:(NSString *)identifier;

/*!
 @method    setFindMyDevice:accountIdentifier:password:withTimeout:
 @abstract  enables/disables Find My Device. To be used on existing accounts.
 @param		enabled - enable/disable flag
            identifier - account identifier
            password - account password
            timeout for service to signal the change
 @return	Returns true if FMD was enabled/disabled for account
 */
- (CAMReturnBool *)setFindMyDevice:(NSNumber *)enabled accountIdentifier:(NSString *)identifier password:(NSString *)password withTimeout:(NSNumber *)timeout;

/*!
 @method    getAccountProperty:accountIdentifier:
 @abstract  Gets the property for an account
 @param     key - account property key
            identifier - account identifier
 @return    Returns array containing the property value
 */
- (CAMReturnArray *)getAccountProperty:(NSString *)key accountIdentifier:(NSString *)identifier;

/*!
 @method    getAccountDescription:
 @abstract  Gets full description for an account. Useful for troubleshooting.
 @param     identifier - account identifier
 @return    Returns string containing current settings for the account
 */
- (CAMReturnString *)getAccountDescription:(NSString *)identifier;

/*!
 @method    getLoggedInAccount
 @abstract  Gets the username for the currently signed in iCloud account
 @return    Returns username of active account
 */
- (CAMReturnString *)getLoggedInAccount;

/*!
 @method    lastAuthenticationResults
 @abstract  Returns the last fetched authentication results dictionary for the last logged-in iCloud account
 @return    Returns the last authentication results dictionary
 */
- (CAMReturnDictionary *)lastAuthenticationResults;

/*!
 @method    generateCode
 @abstract  Generates an HSA2 code on an authenticated HSA2 device.
 @return	Returns six digit code
 */
- (CAMReturnString *)generateCode;

#pragma mark - iCloud Backup
/*!
 @method     enableBackup:
 @abstract   Enable/Disable iCloud Backup on Primary iCloud account
 @discussion Device should be already signed-in into Primary iCloud account
 */
- (CAMReturnVoid *)enableBackup:(NSNumber *)enable;

/*!
 @method     backupNow
 @abstract   Triggers iCloud backup for all enabled classes.
 @discussion This is similar to operation Settings->iCloud->Backup->Backup Now. Verify backup progress using backupState.
*/
- (CAMReturnVoid *)backupNow;

/*!
 @method     backupEnabled
 @abstract   Checks if iCloud backup is enabled
 @discussion Returns the state of UI switch Settings->iCloud->Backup->iCloud Backup
 */
- (CAMReturnBool *)backupEnabled;

/*!
 @method     backupState
 @abstract   Returns the iCloud Backup State
 @return     Dictionary containing active/last backup operation information.
*/
- (CAMReturnDictionary *)backupState;

/*!
 @method     dateOfLastBackup
 @abstract   Returns date of last Backup.
 @return     Date of last backup.
*/
- (CAMReturnString *)dateOfLastBackup;

/*!
 @method     restoreFromBackup:withSnapshot:
 @abstract   Restore from iCloud backup with backup ID and Snapshot ID.
 @discussion Use listBackups to select backup ID and snapshot ID.
 */
- (CAMReturnVoid *)restoreFromBackup:(NSString *)backupID withSnapshot:(NSNumber *)snapshotID;

/*!
 @method     listBackups
 @abstract   List iCloud backups available.
 @return     Array of iCloud Backups.
 */
- (CAMReturnArray *)listBackups;

/*!
 @method     restoreState
 @abstract   Returns iCloud Restore state
 @return     Dictionary containing active/last restore operation information.
 */
- (CAMReturnDictionary *)restoreState;

typedef NS_ENUM(NSUInteger, BackupRestoreState) {
    MBStateIdle = 0,
    MBStateStarting = 1,
    MBStateRunning = 2,
    MBStateEnding = 3,
    MBStateEnded = 4,
    MBStateCancelled = 5,
    MBStateFailed = 6,
};

typedef NS_ENUM(NSUInteger, SnapshotState) {
    MBSnapshotStateUnknown,
    MBSnapshotStateEmpty,
    MBSnapshotStateUncommitted,
    MBSnapshotStateCommitted,
};

#pragma mark - accounts_tool

/*!
 @method     setTimeout
 @abstract   Sets the timeout for operations conducted by the ACTool APIs
 @param      timeout - Timeout for calls to ACTool in seconds
 */
- (CAMReturnVoid *)setTimeout:(NSNumber *)timeout;

/*!
 @method     NotificationsEnabled
 @abstract   Enable/disable notifications in the account store
 @param      enabled - True to enable posting of notifications
 */
- (CAMReturnVoid *)NotificationsEnabled:(NSNumber *)enabled;

/*!
 @method     listAccounts
 @abstract   List accounts on the device. Set verbose to True to have method log verbosely.
 @param      verbose - True for verbose output
 @return     Array of accounts where the account is a dictionary of account properties
 */
- (CAMReturnArray *)listAccounts:(NSNumber *)verbose;

/*!
 @method     listAccount
 @abstract   Returns details on specified account identifier
 @param      accountIdentifier - Identifier for an account on the device
 @return     Account dictionary
 */
- (CAMReturnDictionary *)listAccount:(NSString *)accountIdentifier;

/*!
 @method     listSyncAccounts
 @abstract   Lists accounts that sync
 @discussion The returned dictionary may contain the keys keychainAccounts and keychainHostnameAccounts whose value
             holds an array of accounts. Each account element in the array is actually a dictionary holding the
             properties for the account.
 @return     Dictionary containing {@"keychainAccounts" : @[ @{account_properties} ], @"keychainHostnameAccounts" : @[ @{account_properties} ]}
 */
- (CAMReturnDictionary *)listSyncAccounts;

/*!
 @method     listDeletedSyncAccounts
 @abstract   Lists sync accounts that are deleted
 @return     Dictionary with keys 'keychainDeletedAccounts' and 'keychainDeletedHostnameAccounts' that contain an array of deleted accounts
 */
- (CAMReturnDictionary *)listDeletedSyncAccounts;

/*!
 @method     listAccountTypes
 @abstract   Lists supported account types
 @param      verbose - True for verbose output
 @return     Array of account types
 */
- (CAMReturnArray *)listAccountTypes:(NSNumber *)verbose;

/*!
 @method     listDataclasses
 @abstract   General list of supported dataclasses
 @return     Array of Dataclasses
 */
- (CAMReturnArray *)listDataclasses;

/*!
 @method     listAccountsForType
 @abstract   List of accounts that match the specified account type
 @param      typeIdentifier - the account type (eg: com.apple.account.AppleAccount)
 @return     Array of account dictionaries
 */
- (CAMReturnArray *)listAccountsForType:(NSString *)typeIdentifier;

/*!
 @method     listAccountsEnabledForDataclass
 @abstract   Lists the accounts that have the specified Dataclass enabled
 @param      dataclassIdentifier - Identifier for the dataclass (eg: com.apple.Dataclass.Bookmarks)
 @return     Array of account dictionaries
 */
- (CAMReturnArray *)listAccountsEnabledForDataclass:(NSString *)dataclassIdentifier;

/*!
 @method listKerberosAccounts
 @abstract   List of account for the specified kerberos url
 @param      url - account domain
 @return     Array of account dictionaries
 */
- (CAMReturnArray *)listKerberosAccounts:(NSString *)url;

/*!
 @method     createAccountType:withDisplayName:withCredentialType
 @abstract   Creates an of the specified type, display name and credential type.
 @param      typeIdentifer - Account type eg: com.apple.account.AppleAccount
 @param      displayName - Display name for the account
 @param      credentialType - Type of credential (need to find a list of types...)
 @return     String containing the new identifier for the created account
 */
- (CAMReturnString *)createAccountType:(NSString *)typeIdentifer withDisplayName:(NSString *)displayName withCredentialType:(NSString *)credentialType;

/*!
 @method     deleteAccountType
 @abstract   Removes account of the specified type
 @param      typeIdentifier - the account type (eg: com.apple.account.AppleAccount)
 */
- (CAMReturnVoid *)deleteAccountType:(NSString *)typeIdentifier;

/*!
 @method     createAccount:withDisplayName:withUserName:withPassword:state
 @abstract   Creates an account
 @param      typeIdentifier - the account type (eg: com.apple.account.AppleAccount)
 @param      displayName - Display name for the account
 @param      username - username for the account
 @param      password - password for the account
 @param      state - True to set account as visible
 @return     String containing the account identifier for the newly created account
 */
- (CAMReturnString *)createAccount:(NSString *)typeIdentifier withDisplayName:(NSString *)displayName withUserName:(NSString *)username withPassword:(NSString *)password state:(NSString *)state;

/*!
 @method     deleteAccount
 @abstract   Deletes the account specified by the account identifier
 @param      accountIdentifier - Identifier for an account on the device
 */
- (CAMReturnVoid *)deleteAccount:(NSString *)accountIdentifier;

/*!
 @method     deleteAccounts
 @abstract   Deletes the account for the specified account idenitifers
 @param      accountIdentifiers - Array of Identifiers of accounts on the device
 */
- (CAMReturnVoid *)deleteAccounts:(NSArray *)accountIdentifiers;

/*!
 @method     deleteAccountsForUsername
 @abstract   Deletes the account for the specified username
 @param      username - username for the account to delete
 */
- (CAMReturnVoid *)deleteAccountsForUsername:(NSString *)username;

/*!
 @method setProperty:withKey:withValue
 @abstract   Sets the property for the key/value pair on the specified account identifier
 @param      accountIdentifier - Identifier for an account on the device
 @param      key - Key name for property
 @param      value - String containing property value
 */
- (CAMReturnVoid *)setProperty:(NSString *)accountIdentifier withKey:(NSString *)key withValue:(NSString *)value;

/*!
 @method     setPropertyAsArray:withKey:withArray
 @abstract   Sets the property for the key/value pair on the specified account identifier where the value is an array
 @param      accountIdentifier - Identifier for an account on the device
 @param      key - Key name for property
 @param      value - Array containing property values
 */
- (CAMReturnVoid *)setPropertyAsArray:(NSString *)accountIdentifier withKey:(NSString *)key withArray:(NSArray *)value;

/*!
 @method     setParent:withParentAccountIdentifier
 @abstract   Sets the parent account for the specified account identifier
 @param      accountIdentifier - Identifier for an account on the device
 @param      parentAccountIdentifier - Identifier that is to the be parent of the specified accountIdentifier
 */
- (CAMReturnVoid *)setParent:(NSString *)accountIdentifier withParentAccountIdentifier:(NSString *)parentAccountIdentifier;

/*!
 @method     setAuthenticationType:withAuthenticationType
 @abstract   Sets the authentication type for the specified account identifier
 @param      accountIdentifier - Identifier for an account on the device
 @param      authenticationType - Authentication type for the account eg: 'Kerberos', 'OAuth', 'pararent' or 'none'
 */
- (CAMReturnVoid *)setAuthenticationType:(NSString *)accountIdentifier withAuthenticationType:(NSString *)authenticationType;

/*!
 @method     setAuthenticated:isAuthenticated
 @abstract   ets the specified account authentication state
 @param      accountIdentifier - Identifier for an account on the device
 @param      authenticated - True to set the account as authentication
 */
- (CAMReturnVoid *)setAuthenticated:(NSString *)accountIdentifier isAuthenticated:(NSNumber *)authenticated;

/*!
 @method     setActive:isActive
 @abstract   Sets the specified account's active state
 @param      accountIdentifier - Identifier for an account on the device
 @param      active - True to set account as active
 */
- (CAMReturnVoid *)setActive:(NSString *)accountIdentifier isActive:(NSNumber *)active;

/*!
 @method     enableDataclass:withDataclassName:enabled
 @abstract   Sets the specified Dataclass as enabled for the specified account identifier
 @param      accountIdentifier - Identifier for an account on the device
 @param      dataclassName - Identifier for the dataclass (eg: com.apple.Dataclass.Bookmarks)
 @param      enabled - True to enable, False to disable
 */
- (CAMReturnVoid *)enableDataclass:(NSString *)accountIdentifier withDataclassName:(NSString *)dataclassName enabled:(NSNumber *)enabled;

/*!
 @method     verifyCredentials
 @abstract   Tries to verify the credentials for the specified account identifier
 @param      accountIdentifier - Identifier for an account on the device
 */
- (CAMReturnVoid *)verifyCredentials:(NSString *)accountIdentifier;

/*!
 @method     resetAuthFailures
 @abstract   Resets the authentication failures on the specified account identifier
 @param      accountIdentifier - Identifier for an account on the device
 */
- (CAMReturnVoid *)resetAuthFailures:(NSString *)accountIdentifier;

/*!
 @method     renewCredentials:force:avoidUI:withReason
 @abstract   Renews credentials for the specified account identifier
 @param      accountIdentifier - Identifier for an account on the device
 @param      force - True to force renewal
 @param      avoidUI - True to avoid UI from appearing
 @param      reason - String containing reason for credential renewal
 */
- (CAMReturnVoid *)renewCredentials:(NSString *)accountIdentifier force:(NSNumber *)force avoidUI:(NSNumber *)avoidUI withReason:(NSString *)reason;

/*!
 @method     removeCredentialItem:forCredentialKey
 @abstract   Removes the credential specified in the credential key from the specified account identifier
 @param      accountIdentifier - Identifier for an account on the device
 @param      credentialKey - String containing the key name for the credential to remove
 */
- (CAMReturnVoid *)removeCredentialItem:(NSString *)accountIdentifier forCredentialKey:(NSString *)credentialKey;

/*!
 @method     setCredentialOAuthToken:forToken:withTokenSecret
 @abstract   Sets the token and token secret for the specified account identifier
 @param      accountIdentifier - Identifier for an account on the device
 @param      token - String containing token
 @param      tokenSecret - True to set service as touchID protected
 */
- (CAMReturnVoid *)setCredentialOAuthToken:(NSString *)accountIdentifier forToken:(NSString *)token withTokenSecret:(NSString *)tokenSecret;

/*!
 @method     getCredentialOAuthToken
 @abstract   Returns the token from the keychain store the specified service id for the specified account identifier
 @param      accountIdentifier - Identifier for an account on the device
 @return     String containing the token
 */
- (CAMReturnString *)getCredentialOAuthToken:(NSString *)accountIdentifier;

/*!
 @method setCredentialToken:withServiceID:withToken:requiresTouchID
 @abstract   For the specified account identifer sets credential token for the specified
             keychain component id. Set requiresTouchID to True if credential requires
             touchID protection.
 @param      accountIdentifier - Identifier for an account on the device
 @param      serviceID - Keychain service component id
 @param      token - String containing token
 @param      requiresTouchID - True to set service as touchID protected
 */
- (CAMReturnVoid *)setCredentialToken:(NSString *)accountIdentifier withServiceID:(NSString *)serviceID withToken:(NSString *)token requiresTouchID:(NSNumber *)requiresTouchID;

/*!
 @method     getCredentialToken:withServiceID
 @abstract   Returns the token from the keychain store the specified service id for the specified account identifier
 @param      accountIdentifier - Identifier for an account on the device
 @param      serviceID - Keychain service component id
 @return     String containing the token
 */
- (CAMReturnString *)getCredentialToken:(NSString *)accountIdentifier withServiceID:(NSString *)serviceID;

/*!
 @method     removeCredentialToken:withServiceID
 @abstract   Removes the token from the keychain store the specified service id for the specified account identifier
 @param      accountIdentifier - Identifier for an account on the device
 @param      serviceID - Keychain service component id
 */
- (CAMReturnVoid *)removeCredentialToken:(NSString *)accountIdentifier withServiceID:(NSString *)serviceID;

/*!
 @method     listCredentials
 @abstract   Returns the credentials for the specified account identifier
 @param      accountIdentifier - Identifier for an account on the device
 @return     Dictionary containing credentials. Keys include 'credentialType', 'requiresTouchID' and various other credential items.
 */
- (CAMReturnDictionary *)listCredentials:(NSString *)accountIdentifier;

/*!
 @method     flushCredentialCache
 @abstract   Post notification that the keychain has changed
 */
- (CAMReturnVoid *)flushCredentialCache;

/*!
 @method     flushPluginCache
 @abstract   Flushes the plugin cache. Currently flushes AuthenticationPluginCache, AccessPluginCache, NotificationPluginCache, LastSystemVersion
 */
- (CAMReturnVoid *)flushPluginCache;

/*!
 @method     missingCredentials
 @abstract   Returns an array of account identifiers of accounts that have missing credentials
 @return     Array of account identifiers with missing credentials
 */
- (CAMReturnArray *)missingCredentials;

/*!
 @method     getClientToken
 @abstract   Returns the client token for the specified account identifier
 @param      accountIdentifier - Identifier for an account on the device
 @return     String containing the client token
 */
- (CAMReturnString *)getClientToken:(NSString *)accountIdentifier;

/*!
 @method     addClientToken:withIdentifier
 @abstract   Adds token to specified account identifier
 @param      token - Token to add to account identifer
 @param      accountIdentifier - Identifier for an account on the device
 */
- (CAMReturnVoid *)addClientToken:(NSString *)token withIdentifier:(NSString *)accountIdentifier;

/*!
 @method     setVisiblity
 @abstract   Sets the specified account identifier's visibility
 @param      accountIdentifier - Identifier for an account on the device
 @param      state - True to set account as visible
 */
- (CAMReturnVoid *)setVisiblity:(NSString *)accountIdentifier state:(NSNumber *)state;

/*!
 @method     sendAccount
 @abstract   Saves account to account store
 @param      accountIdentifier - Identifier for an account on the device
 */
- (CAMReturnVoid *)sendAccount:(NSString *)accountIdentifier;

/*!
 @method     listAccountsOnPairedDeviceForType
 @abstract   Lists the accounts on the paired device matchine account type identifier.
 @param      typeIdentifier - the account type (eg: com.apple.account.AppleAccount)
 @return     Array of account dictionaries
 */
- (CAMReturnArray *)listAccountsOnPairedDeviceForType:(NSString *)typeIdentifier;

/*!
 @method     enableFileLogging
 @abstract   Set ACFileLoggingLevel to debug level
 */
- (CAMReturnVoid *)enableFileLogging;

/*!
 @method     reportTelemetry
 @abstract   Reports telemetry for landmark event
 */
- (CAMReturnVoid *)reportTelemetry;
@end
