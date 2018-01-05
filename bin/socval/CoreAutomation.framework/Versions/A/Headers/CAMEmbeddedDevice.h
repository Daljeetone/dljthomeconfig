//
//  CAMEmbeddedDevice.h
//  CoreAutomation
//
//  Created by Matt Massicotte on 3/3/10.
//  Copyright 2010 Apple, Inc. All rights reserved.
//
/*!
 CAMEmbeddedDevice is a representation of the an iOS device.
 */

#import <Cocoa/Cocoa.h>
#import "CAMDarwinTarget.h"
#import "CAMEmbeddedDeviceRestore.h"
#import "CAMDeviceProxies.h"

@class CAMLockdownChannel;
@class CAMUIAApp;
@class CAMUSBController;
@class CAMMobileDeviceState;
@class CAMSerialConnection;
@class CAMFTDIDevice;
@class CAMSerialPort;
@class CAMAstris;
@class CAMShellCommand;
@class CAMCoreAutomationdConnection;
@class CAMSyslogConnection;
@class CAMUIAutomationConnection;

// Specifier keys
extern NSString * const CAMEmbeddedDeviceUDID;
extern NSString * const CAMEmbeddedDeviceUSBLocationID;
extern NSString * const CAMEmbeddedDeviceSerialNumber;
extern NSString * const CAMEmbeddedDeviceECID;
extern NSString * const CAMEmbeddedDeviceSerialDevicePath;

// notifications
// Warning: this notification may not be delivered on the main thread
extern NSString * const CAMEmbeddedDevicesPresentChangedNotification;

#define kCAMMaximumSecondsBeforeShutdown 2*60
#define kCAMMaximumSecondsBeforeBoot     5*60
#define kCAMMaximumSecondsForDiscovery   5*60
#define kCAMMaximumSecondsForUSBChange   5
#define kCAMDefaultCommandTimeout        60.0*60.0
#define kCAMDefaultBasebandTimeout		 1
#define kCAMSecondsForAllDeviceDiscovery 2

/**
 App installation types enum
 */
enum _CAMEmbeddedDeviceAppInstallType
{
    CAMEmbeddedDeviceAppInstallTypeCustomer = 0,
    CAMEmbeddedDeviceAppInstallTypeDeveloper,
    CAMEmbeddedDeviceAppInstallTypeCarrier
};
typedef enum _CAMEmbeddedDeviceAppInstallType CAMEmbeddedDeviceAppInstallType;

/**
 SleepCycler states request enum
 */
enum _CAMEmbeddedDeviceSleepCyclerRequest
{
    CAMEmbeddedDeviceSleepCyclerNotRequested = 0,
    CAMEmbeddedDeviceSleepCyclerRequested,
    CAMEmbeddedDeviceSleepCyclerRequestFullfilled
};
typedef enum _CAMEmbeddedDeviceSleepCyclerRequest CAMEmbeddedDeviceSleepCyclerRequest;

/**
 Device orientation request enum
 */
typedef NS_ENUM(NSInteger, UIDeviceOrientation) {
    UIDeviceOrientationUnknown,
    UIDeviceOrientationPortrait,            // Device oriented vertically, home button on the bottom
    UIDeviceOrientationPortraitUpsideDown,  // Device oriented vertically, home button on the top
    UIDeviceOrientationLandscapeLeft,       // Device oriented horizontally, home button on the right
    UIDeviceOrientationLandscapeRight,      // Device oriented horizontally, home button on the left
    UIDeviceOrientationFaceUp,              // Device oriented flat, face up
    UIDeviceOrientationFaceDown             // Device oriented flat, face down
};

/*!
 @interface CAMEmbeddedDevice
 @discussion Main interface for automating an iOS device.
 */
@interface CAMEmbeddedDevice : CAMDarwinTarget <CAMCommunicating, CAMDeviceProxies, CAMDarwinInterface>

#pragma mark -
#pragma mark Creating a Device
/*!
 @name Creating a Device
 @{
 */

/*!
 @brief The designated initializer for CAMEmbeddedDevice
 @param specifiers A dictionary of values that are used to match against devices visible to this host
 @param waitForPresence A flag that indicates if this method should block until a device is visible
 @param timeout Seconds to wait for the device to become visible if waitForPresence is YES

 This method can be used to "target" a particular device by a number of values, such as UDID, ECID,
 locationID, and/or serial number.  There is a convenience version of this method that assumes the
 waitForPresense should be YES.
 */
- (instancetype)initWithSpecifiers:(NSDictionary *)specifiers andWaitUntilPresent:(BOOL)waitForPresence withTimeout:(NSTimeInterval)timeout;
/*!
 @brief
 Convenience version of initWithSpecifiers:andWaitUntilPresent:withTimeout: that assumes the
 default discovery timeout of 5*60 seconds.
 */
- (instancetype)initWithSpecifiers:(NSDictionary *)specifiers andWaitUntilPresent:(BOOL)waitForPresence;
/*!
 @brief
 Convenience version of initWithSpecifiers:andWaitUntilPresent: that assumes the
 waitForPresense should be YES.
 */
- (instancetype)initWithSpecifiers:(NSDictionary *)specifiers;

/*!
 @brief An initializer that will attempt to return the first device visible via USB
 */
- (instancetype)init;
/*!
 @brief
 An initializer that will attempt to return the booted device with the given UDID.
 Waits until the device is present.
 */
- (instancetype)initWithUDID:(NSString *)aUdid;
/*!
 @brief
 An initializer that will attempt to return the booted device with the given UDID.
 @param aUdid The Unique Device Identifier of the desired device
 @param waitForPresence A flag that indicates if this method should block until a device is visible
 */
- (instancetype)initWithUDID:(NSString*)aUdid andWaitUntilPresent:(BOOL)waitForPresence;
/*!
 @brief
 An initializer that will attempt to return the booted device with the given UDID within the timeout.
 @param aUdid The Unique Device Identifier of the desired device
 @param waitForPresence A flag that indicates if this method should block until a device is visible
 @param timeout Seconds to wait for the device to become visible if waitForPresence is YES
 */
- (instancetype)initWithUDID:(NSString*)aUdid andWaitUntilPresent:(BOOL)waitForPresence withTimeout:(NSTimeInterval)timeout;

/*!
 @brief
 An initializer that will attempt to return the device that is attached at a given USB location identifier.
 Waits until the device is present.
 @param aLocationID The USB location identifier of the desired device
 */
- (instancetype)initWithLocationID:(uint32_t)aLocationID;
/*!
 @brief
 An initializer that will attempt to return the device that is attached at a given USB location identifier.
 @param aLocationID The USB location identifier of the desired device
 @param waitForPresence A flag that indicates if this method should block until a device is visible
 */
- (instancetype)initWithLocationID:(uint32_t)aLocationID andWaitUntilPresent:(BOOL)waitForPresence;
/*!
 @brief
 An initializer that will attempt to return the device that is attached at a given USB location identifier within the timeout.
 @param aLocationID The USB location identifier of the desired device
 @param waitForPresence A flag that indicates if this method should block until a device is visible
 @param timeout Seconds to wait for the device to become visible if waitForPresence is YES
 */
- (instancetype)initWithLocationID:(uint32_t)aLocationID andWaitUntilPresent:(BOOL)waitForPresence withTimeout:(NSTimeInterval)timeout;


/*!
 @brief
 An initializer that will attempt to return the device with the given ECID.
 Waits until the device is present.
 @param anEcid An NSNumber representing the ECID (UniqueChipID) of the desired device.
 */
- (instancetype)initWithEcid:(NSNumber*)anEcid;
/*!
 @brief
 An initializer that will attempt to return the device with the given ECID.
 @param anEcid An NSNumber representing the ECID (UniqueChipID) of the desired device.
 @param waitForPresence A flag that indicates if this method should block until a device is visible
 */
- (instancetype)initWithEcid:(NSNumber*)anEcid andWaitUntilPresent:(BOOL)waitForPresence;
/*!
 @brief
 An initializer that will attempt to return the device with the given ECID.
 @param anEcid An NSNumber representing the ECID (UniqueChipID) of the desired device.
 @param waitForPresence A flag that indicates if this method should block until a device is visible
 @param timeout Seconds to wait for the device to become visible if waitForPresence is YES
 */
- (instancetype)initWithEcid:(NSNumber*)anEcid andWaitUntilPresent:(BOOL)waitForPresence withTimeout:(NSTimeInterval)timeout;


/*! @} End Creating a Device */


#pragma mark -
#pragma mark Getting Available Devices
/*!
 @name Getting Available Devices
 @{
 */

/*!
 @brief Returns an array of the devices immediately visible to the host via USB.
 Calls allDevicesWithTimeout with a default timeout of 5 mins. See allDevicesWithTimeout
 for more details.
  */
+ (NSArray *)allDevices;

/*!
 @brief Returns an array of devices immediately visible on the host via USB

 Due to the nature of device discovery by other means, this method does not guarantee that you will
 get an array that contains all devices you can actually communicate with on this host.  Upon invocation,
 this method scans the USB bus for devices that appear to be an Apple Mobile Device.  This method is not
 safe to use when responding to a CAMEmbeddedDevicesPresentChangedNotification posting.
 @param timeout Seconds to wait for each device to become present.
 */
+ (NSArray *)allDevicesWithTimeout:(NSTimeInterval)timeout;

/*!
 @brief Returns an array of the devices currently tracked by the framework

 This method will return all the Apple Mobile Devices that are currently being tracked.  When a process
 is first started, this array may not represent all devices actually attached to the host.  Use this method
 when you have a run loop and want to enumerate devices after a CAMEmbeddedDevicesPresentChangedNotification
 is posted.
 */
+ (NSArray *)allAttachedDevices;

/*!
 @brief Returns an array of the network devices currently tracked by the framework

 This method will return all the Apple Mobile Devices that are currently being tracked.
 */
+ (NSArray *)allNetworkDevices;

/*! @} End Getting Available Devices */


#pragma mark -
#pragma mark application install uninstall helper
/*!
 @brief
 Installs app from given path or ipa file on to the device
 @param path The ipa file or the appname.app path
 @param type One of the CAMEmbeddedDeviceAppInstallType types. (Usually CAMEmbeddedDeviceAppInstallTypeCustomer or CAMEmbeddedDeviceAppInstallTypeDeveloper)
 */
- (void)installAppFromPath:(NSString*)path installType:(CAMEmbeddedDeviceAppInstallType)type;

/*!
 @brief
 same as calling -[CAMEmbeddedDevice installAppFromPath:path installType:CAMEmbeddedDeviceAppInstallTypeCustomer];
 */
- (void)installAppFromPath:(NSString*)path;

/*!
 @brief
 Uninstall the app having the specified bundleId from the device.
 @param bundleId The bundleId of the app to be uninstalled
 */
- (void)uninstallAppWithId:(NSString*)bundleId;

/*!
 @deprecated Use installedApplicationsMatchingFilter: instead.
 @brief Returns a dictionary containing one entry per installed app keyed by the bundleId of the app.

 Gets a dictionary containing all the apps installed on the device. Each entry itself is a dictionary containing several keys.

 Some of these keys are :
 "CFBundleName" - App's name,
 "Path" - String containing path of application on device,
 "CFBundleExecutable" - Name of the app's executable,
 "CFBundleSupportedPlatforms" - Supported platforms as an array ex: ["iPhoneOS"].
 */
- (NSDictionary*)getInstalledApplications __attribute__((deprecated));

/*!
 @brief Returns a dictionary containing the Info.plist dictionary of all installed applications.

 Gets a dictionary containing all the apps installed keyed by the bundle identifiers. Each value is the Info.plist of that app.

 Some of the keys (from the Info.plist dictionary) are:
 "CFBundleName" - App's name,
 "Path" - String containing path of application on device,
 "CFBundleExecutable" - Name of the app's executable,
 "CFBundleSupportedPlatforms" - Supported platforms as an array ex: ["iPhoneOS"].

 Optionally, specify options to filter the results:
 "ApplicationType"    -> "Any", "System", "User", "Internal"
 "Attribute"          -> Either "HasSettingsBundle" or "HasSettingsBundleIcon". Only applications with that attribute will be returned.
 "BundleIDs"          -> CFString or array of strings that indicate the bundle IDs to lookup
 "ReturnAttributes"   -> CFString or array of strings indicating which of the keys from the Info.plist should be returned. Must include "CFBundleIdentifier".
 */
- (NSDictionary<NSString *, NSDictionary *> *)installedApplicationsMatchingFilter:(NSDictionary*)options;

#pragma mark - Async


#pragma mark - Code Coverage

/*!
 @method     flushCoverageData:
 @abstract   Trigger a __gcov_flush()
 @discussion Code Coverage data is only flushed on process exit. This enables a forced flush.
 @return     Returns true if code coverage is enabled.
 */
+ (BOOL)flushCoverageData;

#pragma mark -
#pragma mark Profile Functions

/*!
 @brief Adds the provisioning profile at the specified path to device.
 @param path Path of the mobile provisioning profile file
 */
- (void)addProvisioningProfile:(NSString*)path;

/*!
 @brief Removes the provisioning profile having the specified UUID, from the device

 note - Throws an exception if profile with matching UUID is not found.
 @param profileId The uuid of the profile to be removed
 */
- (void)removeProvisioningProfile:(NSString*)profileId;

/*!
 @brief Returns a dictionary containing all the provisioning profiles keyed by the profile UUID.

 The returned dictionary contains a dictionary per item with the following keys,
 "uuid" - uuid of the profile(NSString)
 "name" - name of profile(NSString),
 "expirationDate" - expiration date of the profile(NSDate)

 @return Dictionary of profiles or nil if no profiles are found.
 */
@property (NS_NONATOMIC_IOSONLY, getter=getProvisioningProfiles, readonly, copy) NSDictionary *provisioningProfiles;

#pragma mark -
#pragma mark Media Bundle Functions

/*!
 @brief Syncs a bundle to the device with Media and an optional AddressBook, then reboots the device by default.

 See http://eightball.apple.com/luna/index.php/Media_App_Test_Content for known bundles.

 @param localPath Path to the media bundle on the local machine.

 @return YES if the sync succeeded, otherwise NO.
 */
- (BOOL)syncMediaAndABBundle:(NSString *)localPath;
/*! @brief Syncs the media bundle but allows for custom reboot control. */
- (BOOL)syncMediaAndABBundle:(NSString *)localPath reboot:(BOOL)reboot;

// base properties
@property (copy,   readonly) NSString *udid;
@property (copy,   readonly, nonatomic) NSString *serialNumber;
@property (nonatomic, assign, readonly) uint32_t locationID;
@property (copy,   readonly) NSNumber *ecid;
@property (copy,   readonly) NSString *primateType;
@property (copy,   readonly) NSString *primateSerialNumber;
@property (copy,   readonly) NSString *serialPath;
@property (copy,   readonly) NSString *busmanSerial;
@property (copy,   readonly) NSNumber *busmanPort;


#pragma mark -
#pragma mark Changing State
/*!
 @name Changing State
 @{
 */

/*! @brief Returns the internal state of the device. */
@property (readonly, strong) CAMMobileDeviceState *internalState;

/*! @brief Attempts to get the device into a booted state */
- (void)getToOS;

/*! @brief Attempts to get the device into iBoot */
- (void)getToiBoot;

/*! @brief Attempts to get the device into DFU */
- (void)getToDFU;

/*!
 @brief Sends an NMI command over a serial connection if such exists.
 @warning This may cause extensive communication timeouts with this device.
 */
- (void)getToNMI;

/*! @brief Sends an iBoot command to the device. */
- (void)runiBootCommand:(NSString*)command waitForCompletion:(BOOL)wait;

/*! @brief Attempts to perform a jtag reset on a device
 @param wait Determines if the method should block until the device re-appears

 For this to work, the device must be attached with an element cable, and that cable
 must be properly mapped in CoreAutomation's usb_map.plist file.
 */
- (void)jtagReset:(BOOL)wait;

/*!
 @brief Waits until a device has gone offline.
 */
@property (NS_NONATOMIC_IOSONLY, readonly) BOOL waitUntilNotPresent;
- (BOOL)waitUntilNotPresentWithTimeout:(NSTimeInterval)timeout;

/*!
 @brief Waits until a device comes online.
 */
@property (NS_NONATOMIC_IOSONLY, readonly) BOOL waitUntilPresent;
- (BOOL)waitUntilPresentWithTimeout:(NSTimeInterval)timeout;

/*! @brief Mounts the root "/" writable
 This re-mounts "/" so that the file system is writable.
 */
@property (NS_NONATOMIC_IOSONLY, readonly) BOOL makeRootMountWritable;

/*!
 @brief This returns the serialPort associated with a device.
 This method tries to use Kong/Gorilla or a mapping file to associate
 */
@property (nonatomic, readonly, strong) CAMSerialPort *serialPort;

/*!
 @brief This returns the Astris associated with a device.
 This method tries to use Kong/Gorilla or a mapping file to associate
 */
@property (nonatomic, readonly, strong) CAMAstris *astris;

/*!
 @brief This returns an array of Trains supported by the given
 hardwareModel. This works based on CoreAutomationModelMapping.plist file
 */
+ (NSArray<NSString *> *)trainSupportForHardwareModel:(NSString *)hardwareModel;

/*!
 @brief This returns and array of Trains supported by a devices
 This works based on a CoreAutomationModelMapping.plist file that can be overriden by placing a file in
 /usr/local/CoreAutomationModelMapping.plist
 */
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSArray<NSString *> *trainSupport;

/*!
 @brief Returns root filesystem time parsed from mount
 */
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *filesystemType;

/*!
 @brief Returns nand cell type parsed from NANDInfoTool
 */
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *nandType;

/*!
 @brief Returns nand vendor parsed from NANDInfoTool
 */
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *nandVendor;

/*!
 @brief Returns nand capacity parsed from NANDInfoTool
 */
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *nandCapacity;

/*!
 @brief Parses NANDInfoTool and will return end of line that starts with string id
 */
- (NSString*)nandInfo:(NSString*)id;

/*!
 @brief Returns nand cycle count
 */
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *nandCycles;

/*!
 @brief Returns nand cycle count
 */
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSNumber *nandEolPercent;

/*!
 @brief Performs a IPSW-based software restore on the device
 @param ipswPath Path to the IPSW file
 */
- (BOOL)restoreIPSW:(NSString *)ipswPath withOptions:(NSDictionary*)options;

/*!
 @brief Performs a IPSW-based software restore on the device
 @param ipswPath Path to the IPSW file
 @param options A dictionary that specifies the parameters that will affect the restore
 @param progressBlock Block that will be called when there is a progress update
 */
- (BOOL)restoreIPSW:(NSString *)ipswPath withOptions:(NSDictionary*)options usingProgressBlock:(void (^)(NSDictionary *progressInfo))progressBlock;

/*!
 @brief Performs a IPSW-based software restore on the device
 @param theBuild The CAMXBSBuild object for the desired restore
 @param restoreBundle The bundle to restore the device with
 @param options A dictionary that specifies the parameters that will affect the restore
 */
- (BOOL)restoreBuildWithIPSW:(CAMXBSBuild *)theBuild usingRestoreBundle:(CAMEmbeddedDeviceRestoreBundle)restoreBundle withOptions:(NSDictionary*)options;

/*!
 @brief Performs a IPSW-based software restore on the device
 @param theBuild The CAMXBSBuild object for the desired restore
 @param restoreBundle The bundle to restore the device with
 @param options A dictionary that specifies the parameters that will affect the restore
 @param progressBlock Block that will be called when there is a progress update
 */
- (BOOL)restoreBuildWithIPSW:(CAMXBSBuild *)theBuild usingRestoreBundle:(CAMEmbeddedDeviceRestoreBundle)restoreBundle withOptions:(NSDictionary*)options usingProgressBlock:(void (^)(NSDictionary *progressInfo))progressBlock;

/*!
 @brief Peforms a software restore on the device
 @param theBuild The CAMXBSBuild object for the desired restore
 @param documentPath A path to the PR2 restore document to use
 @param options A dictionary that specifies the parameters that will affect the restore

 See CAMEmbeddedDeviceRestore.h for details on the keys that can be used in the restoreOptions
 dictionary.  In particular, check out CAMEmbeddedDeviceRestorePiecesPathKey, which can override the
 default location of the restore pieces that will be used.
 */
- (BOOL)restoreBuild:(CAMXBSBuild*)theBuild usingRestoreDocument:(NSString*)documentPath withOptions:(NSDictionary*)options;

/*!
 @brief Peforms a software restore on the device
 @param theBuild The CAMXBSBuild object for the desired restore
 @param documentPath A path to the PR2 restore document to use
 @param options A dictionary that specifies the parameters that will affect the restore
 @param progressBlock Block that will be called when there is a progress update

 See CAMEmbeddedDeviceRestore.h for details on the keys that can be used in the restoreOptions
 dictionary.  In particular, check out CAMEmbeddedDeviceRestorePiecesPathKey, which can override the
 default location of the restore pieces that will be used.
 */
- (BOOL)restoreBuild:(CAMXBSBuild*)theBuild usingRestoreDocument:(NSString*)documentPath withOptions:(NSDictionary*)options usingProgressBlock:(void (^)(NSDictionary *progressInfo))progressBlock;

/*!
 @brief Convenience wrapper around -restoreBuild:usingRestoreDocument:withOptions:
 @param theBuild The CAMXBSBuild object for the desired restore

 This is a simple wrapper around -restoreBuild:usingRestoreDocument:withOptions: that uses the PR2 document
 defined by CAMEmbeddedDeviceRestoreDefaultErasePRPath;
 */
- (BOOL)restore:(CAMXBSBuild*)theBuild;

/*!
 @brief Peforms a software restore on the device
 @param theBuild The CAMXBSBuild object for the desired restore
 @param documentPath A path to the PR2 restore document to use
 @param options A dictionary that specifies the parameters that will affect the restore

 See CAMEmbeddedDeviceRestore.h for details on the keys that can be used in the restoreOptions
 dictionary.  In particular, check out CAMEmbeddedDeviceRestorePiecesPathKey, which can override the
 default location of the restore pieces that will be used.

 NOTE: this function only sets up the restore task in the CFRunLoop. You still need to provide CFRunLoop cycles in the main thread to do the actual work.
 MainThread is needed because AppleConnect Creds and Personalization Build needs to run on the main thread (through experiments). CFRunLoop on threads
 other than main will exit immediately

 */

- (void)restoreBuildAsync:(CAMXBSBuild*)theBuild usingRestoreDocument:(NSString*)documentPath withOptions:(NSDictionary*)options;
/*!
 @brief Convenience wrapper around -restoreBuildAsync:usingRestoreDocument:withOptions:
 @param theBuild The CAMXBSBuild object for the desired restore

 This is a simple wrapper around -restoreBuild:usingRestoreDocument:withOptions: that uses the PR2 document
 defined by CAMEmbeddedDeviceRestoreDefaultErasePRPath;

 NOTE: this function only sets up the restore task in the CFRunLoop. You still need to provide CFRunLoop cycles in the main thread to do the actual work.
 MainThread is needed because AppleConnect Creds and Personalization Build needs to run on the main thread (through experiments). CFRunLoop on threads
 other than main will exit immediately
 */

- (void)restoreAsync:(CAMXBSBuild*)theBuild;

/*!
 @brief Convenience wrapper around -restoreIPSW:withOptions:usingProgressBlock
 @param theBundle a filesystem path (string) to the location of the IPSW bundle.
 This is a simple wrapper around -restoreIPSW:withOptions:usingProgressBlock.

 NOTE: this function only sets up the restore task in the CFRunLoop. You still need to provide CFRunLoop cycles in the main thread to do the actual work.
 MainThread is needed because AppleConnect Creds and Personalization Build needs to run on the main thread (through experiments). CFRunLoop on threads
 other than main will exit immediately
 */
- (void)restoreIPSWAsync:(NSString *)theBundle;

/*!
 @brief Convenience function to restore an array of devices
 @param theArrayOfDevices The Array contains CAMEmbeddedDevices
 @param theBuild The CAMXBSBuild object for the desired restore
 @param documentPath A path to the PR2 restore document to use
 @param options A dictionary that specifies the parameters that will affect the restore
 @return an Array of Bools, stores the restore results of corresponding device

 NOTE: This function setup a CFRunLoop for you and wait until it finishes all the restore.
 */
+ (NSArray *)restore: (NSArray *)theArrayOfDevices withBuild:(CAMXBSBuild*)theBuild usingRestoreDocument:(NSString*)documentPath withOptions:(NSDictionary*)options;

/*!
 @brief Convenience function to restore an array of devices
 @param theArrayOfDevices The Array contains CAMEmbeddedDevices
 @param theBuilds The Array contains CAMXBSBuild objects for the desired restore for each device in theArrayOfDevices, matched by index
 @param documentPaths The Array contains an array of paths to the PR2 restore documents to use for each device in theArrayOfDevice, matched by index
 @param options The Array contains an array of dictionaries that specifies the parameters that will affect the restore for each device in theArrayOfDevice, matched by index
 @return an Array of Bools, stores the restore results of corresponding device

 if any entry in the documentPath is NSNull, default PR2 path will be used instead CAMEmbeddedDeviceRestoreDefaultErasePRPath for that device at corresponding index
 if any entry in the options is NSNull, none customized options will be provided for that device at corresponding index.

 NOTE: This function setup a CFRunLoop for you and wait until it finishes all the restore.
 */


+ (NSArray *)restore: (NSArray *)theArrayOfDevices withArrayOfBuilds:(NSArray*)theBuilds usingArrayOfRestoreDocuments:(NSArray*)documentPaths withArrayOfOptions:(NSArray*)options;

/*!
 @brief Convenience function to restore an array of devices
 @param theArrayOfDevices an array of devices to operate on
 @param theBundles an array of actual IPSW bundles to install on each device, matched by index
 @param options parameters that will affect the restore for each device, matched by index
 @return an Array of Bools, stores the restore results of corresponding device

 if any entry in the options is NSNull, none customized options will be provided for that device at corresponding index.
 NOTE: This function sets up a CFRunLoop for you and waits until it finishes restoring.
 */
+ (NSArray *)restoreIPSWs:(NSArray*)theArrayOfDevices usingArrayOfIPSWs:(NSArray*)theBundles withArrayOfOptions:(NSArray*)options;

/*!
 @brief Mount a Personalized Disk Image on device
 @param bundleURL File URL for the PDI
 @param variant Image variant (AutomationDiskImage, DebugDiskImage, ProdAutomationDiskImage)
 @param options Personalization options.
                kPersonalizationUseCredentials: whether to use Apple Connect credentials or not
                kPersonalizationSigningServerURL: override default signing server URL
                kPersonalizationMountedBundlePath: path to already mounted image bundle
 NOTE: This method is not thread safe unless the option kPersonalizationMountedBundlePath is passed in. See
 <MobileDevice/PersonalizedImages.h> for more details.
 */
- (CAMReturnBool *)mountPDI:(NSURL *)bundleURL forVariant:(NSString *)variant usingOptions:(NSDictionary *)options;

/*! @} End Changing State */

#pragma mark -
#pragma mark Baseband Status
/*!
 @name Baseband Status
 @{
 */

/*!
 @brief Checks to see if the baseband is ready. On devices without baseband this will always return NO.
 */
@property (NS_NONATOMIC_IOSONLY, getter=isBasebandReady, readonly) BOOL basebandReady;

/*!
 @brief Waits until the baseband is ready or until 'timeout' seconds have elapsed, and returns the baseband status.
 */
- (BOOL)waitForBasebandWithTimeout:(NSTimeInterval)timeout;

/*! @} End Baseband Status */

#pragma mark -
#pragma mark Reserving Devices
/*!
 @name Reserving Devices
 @{
 */

/*!
 @brief Reserve devices that match the specified criteria.
 @param devicePredicates	An array of NSPredicates that match CAMEmbeddedDevice predicates.

 Checking out a device signals to other CoreAutomation clients that the device is in use.
 */
+ (NSArray *)checkout:(NSArray *)devicePredicates;
+ (NSArray *)checkout:(NSArray *)devicePredicates withDevices:(NSArray*)currentDevices;
+ (NSArray *)checkout:(NSNumber *)size usingBlockPredicate:(NSPredicate *)blockpredicate withDevices:(NSArray *)devices;

/*!
 @brief Unreserve a list of devices.
 @param devices	An array of CAMEmbeddedDevices that were checked out by you.

 Checking in a device signals to other CoreAutomation clients that the device is no longer in use and is available to other clients.
 */
+ (void)checkin:(NSArray *)devices;
- (void)checkin;

/*! @} End Reserving Devices */

#pragma mark -
#pragma mark Executing Shell Commands
/*!
 @name Executing Shell Commands
 @{
 */

/*!
 @brief Begins execution of a CAMShellCommand object
 @param shellCommand	The object to execute.

 Warning: this method is deprecated.

 If you're looking to run a simple command and heard "executeCommand is the way to go", you're probably looking for [[<device> os] executeCommand:arguments:]

 Read the wiki for more.  https://eightball.apple.com/luna/index.php/CoreAutomation#Running_Commands
 */

- (void)executeCommand:(CAMShellCommand*)shellCommand;

- (NSString*)runCommand:(NSString*)command andWaitForResult:(BOOL)wait;

/*!
 @brief Mildly more convinient wrapper around executeCommand:
 @param command	The shell string to execute
 @param wait	YES returns only after the command finishes
 @param aUser	Allows to you specify the user this command will run as
 @param timeout	If the command does not complete before this time, an exception will be raised

 */
- (NSString*)runCommand:(NSString*)command andWaitForResult:(BOOL)wait asUser:(NSString*)aUser withTimeout:(NSTimeInterval)timeout;

/*! @} End Executing Shell Commands */


#pragma mark -
#pragma mark Establishing Pairing and Activation
/*!
 @name Establishing Pairing and Activation
 @{
 */

/*! @brief Determine the activation state of the device */
@property (nonatomic, assign, readonly) BOOL      isActivated;
@property (nonatomic, weak, readonly) NSString* activationState;
/*! @brief Determine if the device has been paired with this host */
@property (nonatomic, assign, readonly) BOOL      isPaired;

/*! @brief Activate the device using the host-side 'activate' command */
- (void)activate;
/*! @brief Activate the device, but returns BOOL with error dict key of @"kCAMActivationLogPath" with log of failure. */
- (BOOL)activateWithError:(NSError **)error;
/*! @brief Deactivate the device */
- (void)deactivate;
/*! @brief Pair the device with this host */
- (void)pair;
/*! @brief Unpair the device with this host */
- (void)unpair;

/*! @} End Establishing Pairing and Activation */

/*!
 @brief Installs a carrier bundle on the device.
 @param ipccPath	Carrier bundle package.
 */
- (BOOL)installCarrierBundle:(NSString *)ipccPath;

/*!
 @brief Transfers a set of file sources over MobileFileRelay.
 @param sources	An array of file sources to sync.
 @param localPath The destination to save the files to.
 */
- (BOOL)retrieveSources:(NSArray *)sources toLocation:(NSString *)localPath;

/*!
 @brief Transfers a file source over MobileFileRelay.
 @param source	An array of file sources to sync.
 @param localPath The destination to save the files to.
 */
- (BOOL)retrieveSource:(NSString *)source toLocation:(NSString *)localPath;

/*!
 @brief Transfers files over CAMCrashReportConnection.
 @param remotePath file or directory to sync.
 @param localPath The destination to save the files to.
 */
- (BOOL)retrieveWithCrashCopier:(NSString *)remotePath toLocation:(NSString *)localPath;

/*!
 @brief Transfers remote files over rsync
 @param remotePath The remote file path to receive
 @param localPath The local path to store the files
 @param options Rsync options as defined in the man pages. These are space delimited
 */
- (BOOL)rsyncFromRemote:(NSString *)remotePath toLocal:(NSString *)localPath options:(NSString *)options;

/*!
 @brief Transfers local files over rsync
 @param localPath The local file path to send
 @param remotePath The remote file path to store the files
 @param options Rsync options as defined in the man pages. These are space delimited
 */
- (BOOL)rsyncFromLocal:(NSString *)localPath toRemote:(NSString *)remotePath options:(NSString *)options;

/*!
 @name coreautomationd Connection
 @{
 */

@property (weak, readonly) CAMCoreAutomationdConnection* coreautomationdConnection;
@property (weak, readonly) CAMCoreAutomationdConnection* rootCoreautomationdConnection;

/*! @} End coreautomationd Connection */

/*!
 @name Syslog
 @{
 */
/*!
 @brief Returns a connection to the device's syslog.
 @discussion Most commonly used with -setHostPath: to stream the device's syslog to a file on the host.
 */
@property (weak, readonly) CAMSyslogConnection* syslogConnection;
/*! @} End Syslog */


/*!
 @name uiautomation
 @{
 */
/*!
 @brief Returns a connection to uiautomationd.
 */
@property (weak, readonly) CAMUIAutomationConnection *uiautomation;
/*! @} End uiautomation */


// presence detection and control
/*!
 @brief Identifies the device by flashing the screen.
 */
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSString *identify;
/*!
 @brief Identifies the device by flashing the screen and optionally vibrating and playing a noise.
 */
- (NSString *)identifyAndPlaySound:(BOOL)playSound;

/*!
 @brief Returns true if the device can open a lockdownd connection.
 */
@property (assign, readonly) BOOL					isResponsive;

/*!
 @brief Returns true if the device is present on the USB bus.
 */
@property (assign, readonly) BOOL					isPresent;

/*!
 @brief Returns true if the USB device has timed out after 5s; in most cases you can use this as an isPanicked() method.
 */
@property (assign, readonly) BOOL					isTimedOut;

@property (assign, readonly) BOOL					isAttachedViaUSB;
@property (nonatomic, strong)           CAMUSBController		*usbController;

- (void)attachUSBAndWaitForConnect:(BOOL)wait;
- (void)detachUSBAndWaitForDisconnect:(BOOL)wait;

/*!
 @brief Communicate with the device using the WiFi transport, if available.
 @return A boolean indicating if the transport switch succeeded.
 */
@property (NS_NONATOMIC_IOSONLY, readonly) BOOL useAMDNetworkConnection;

/*!
 @brief Communicate with the device using the USB transport, if available.
 @return A boolean indicating if the transport switch succeeded.
 */
@property (NS_NONATOMIC_IOSONLY, readonly) BOOL useAMDRestorableConnection;

/*!
 @brief Communicate with the device using the USB transport, if available.
 @return A boolean indicating if the transport switch succeeded.
 */
@property (NS_NONATOMIC_IOSONLY, readonly) BOOL useAsyncConnection;

#pragma mark -
#pragma mark UI Control

/*!
 @brief Returns a CAMUIAApp object
 @param appName The UIAutomation name of the application

 This function returns an object that can act as a proxy for a real UIAApp object in JavaScript on the device.
 It is more convenient when used with one of the scripting bridges, but can be helpful on its own.

 */
- (CAMUIAApp *)appForName:(NSString *)appName;

/*!
 @brief Executes a JavaScript fragment, returning the output
 @param javaScriptText The fragment to execute
 @param libraries An array of UIAutomation libaries to include.  Can be nil.

 Executes JavaScript using scripter on the device.  The result of the invocation is a string containing
 any output from scripter on stdout.  If the script invocation should fail, this function will raise an
 exception.  This allows a script failure to propagate from the JavaScript into your process.

 */
- (NSString*)runScripter:(NSString*)javaScriptText usingLibraryPaths:(NSArray*)libraries;

/*!
 @brief Gets an NSImage of the device screen
 */
@property (NS_NONATOMIC_IOSONLY, getter=getScreenShot, readonly, copy) NSImage *screenShot;

/*!
 @brief Gets an NSImage of the device's Stark screen
 */
@property (NS_NONATOMIC_IOSONLY, getter=getStarkScreenShot, readonly, copy) NSImage *starkScreenShot;

/*!
 @brief Takes a screen shot and saves it as a PNG to disk
 @param url The path to save the PNG file
 */
- (void)writeScreenShotToURL:(NSURL*)url;

/*!
 @brief Takes a screen shot and saves it as a PNG to disk. Performs any rotations on the host to conserve device memory.
 @param url The path to save the PNG file
 */
- (void)saveScreenShotToURL:(NSURL*)url;

/*!
 @brief Takes a screen shot of the Stark screen and saves it as a PNG to disk
 @param url The path to save the PNG file
 */
- (void)writeStarkScreenShotToURL:(NSURL*)url;

/*!
 @brief Fetches application icons for the given app bundle identifiers
 @param options An array of CFBundleIdentifiers
 @return A dictionary of NSImages keyed by the bundle identifer.
 If the bundle identifier has no icon (such as com.apple.webapp), it will not be present in the returned dictionary.
 */
- (NSDictionary*)appIconsForIdentifiers:(NSArray*)options;

#pragma mark -
#pragma mark Backup and Restore

/*!
 @brief Backup a device from the network.
 */
@property (NS_NONATOMIC_IOSONLY, readonly) BOOL backupFromNetwork;

/*!
 @brief Backup a device from the network.
 @param block   Block that will be run whenever backup progress has changed.
 */
- (BOOL)backupFromNetworkUsingProgressBlock:(void (^)(NSUInteger percent))block;

/*!
 @brief Backup a device from the local host.
 */
@property (NS_NONATOMIC_IOSONLY, readonly) BOOL backupFromLockdown;

/*!
 @brief Backup a device from the local host.
 @param block   Block that will be run whenever backup progress has changed.
 */
- (BOOL)backupFromLockdownUsingProgressBlock:(void (^)(NSUInteger percent))block;

/*!
 @brief Restores a device's latest backup from the network.
 @param copyBackup          Denotes if the backup should be copied when restoring.
 @param aPassword           Specify nil here unless the backup file is encrypted.
 If nil is specified and the backup file is encrypted, we'll try get the password from Keychain.
 @param waitForBoot         Denotes whether to wait for the device to reboot.
 */
- (BOOL)restoreFromNetworkAndCopy:(BOOL)copyBackup password:(NSString *)aPassword waitForBoot:(BOOL)waitForBoot;

/*!
 @brief Restores a device from the network.
 @param sourceIdentifier    Name of the backup that will be used.
 @param copyBackup          Denotes if the backup should be copied when restoring.
 @param aPassword           Specify nil here unless the backup file is encrypted.
 If nil is specified and the backup file is encrypted, we'll try get the password from Keychain.
 @param waitForBoot         Denotes whether to wait for the device to reboot.
 */
- (BOOL)restoreSourceFromNetwork:(NSString *)sourceIdentifier copy:(BOOL)copyBackup password:(NSString *)aPassword waitForBoot:(BOOL)waitForBoot;

/*!
 @brief Restores a device from the network.
 @param sourceIdentifier    Name of the backup that will be used.
 @param copyBackup          Denotes if the backup should be copied when restoring.
 @param aPassword           Specify nil here unless the backup file is encrypted.
 If nil is specified and the backup file is encrypted, we'll try get the password from Keychain.
 @param waitForBoot         Denotes whether to wait for the device to reboot.
 @param block               Block that will be run whenever restore progress has changed.
 */
- (BOOL)restoreSourceFromNetwork:(NSString *)sourceIdentifier copy:(BOOL)copyBackup password:(NSString *)aPassword waitForBoot:(BOOL)waitForBoot usingProgressBlock:(void (^)(NSUInteger percent))block;

/*!
 @brief Restores a device's latest backup from the local host.
 @param copyBackup          Denotes if the backup should be copied when restoring.
 @param aPassword           Specify nil here unless the backup file is encrypted.
 If nil is specified and the backup file is encrypted, we'll try get the password from Keychain.
 @param waitForBoot         Denotes whether to wait for the device to reboot.
 */
- (BOOL)restoreFromLockdownAndCopy:(BOOL)copyBackup password:(NSString *)aPassword waitForBoot:(BOOL)waitForBoot;

/*!
 @brief Restores a device on the local host.
 @param sourceIdentifier    Name of the backup that will be used.
 @param copyBackup          Denotes if the backup should be copied when restoring.
 @param aPassword           Specify nil here unless the backup file is encrypted.
 If nil is specified and the backup file is encrypted, we'll try get the password from Keychain.
 @param waitForBoot         Denotes whether to wait for the device to reboot.
 */
- (BOOL)restoreSourceFromLockdown:(NSString *)sourceIdentifier copy:(BOOL)copyBackup password:(NSString *)aPassword waitForBoot:(BOOL)waitForBoot;

/*!
 @brief Restores a device on the local host.
 @param sourceIdentifier    Name of the backup that will be used.
 @param copyBackup          Denotes if the backup should be copied when restoring.
 @param aPassword           Specify nil here unless the backup file is encrypted.
 If nil is specified and the backup file is encrypted, we'll try get the password from Keychain.
 @param waitForBoot         Denotes whether to wait for the device to reboot.
 @param block               Block that will be run whenever restore progress has changed.
 */
- (BOOL)restoreSourceFromLockdown:(NSString *)sourceIdentifier copy:(BOOL)copyBackup password:(NSString *)aPassword waitForBoot:(BOOL)waitForBoot usingProgressBlock:(void (^)(NSUInteger percent))block;

/*!
 @brief Cancels the current backup or restore operation.
 */
@property (NS_NONATOMIC_IOSONLY, readonly) BOOL cancelBackupRestore;

/*!
 @method setRestoreLogURL
 @discussion sets the mobile restore file api to save a log type to a url
 @param url
	File Location
 @param logType
	Type of Log
	#define kAMRestorableDeviceLogTypeSerial CFSTR("SerialLogType")
 #define kAMRestorableDeviceLogTypeHost CFSTR("HostLogType")
 #define kAMRestorableDeviceLogTypeDevice CFSTR("DeviceLogType")
 @result
	YES if successful restore, NO if unsuccessful.
 */
- (BOOL)setRestoreLogURL:(NSURL*)url withType:(NSString*)logType;

#pragma mark -
#pragma mark Properties

@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSDictionary *devicePropertyDictionary;

/*!
 @name Device Capabilites
 @{
 */
/*! @brief Determine if the device is DFU */
@property (assign, readonly) BOOL isInDFU;
/*! @brief Determine if the device is in iBoot */
@property (assign, readonly) BOOL isInIBoot;
/*! @brief Determine if the device has baseband hardware */
@property (assign, readonly) BOOL hasBaseband;
/*! @brief Determine if the device has a SIM card installed */
@property (assign, readonly) BOOL hasSIM;
/*! @brief Determine if the device has WiFi hardware */
@property (assign, readonly) BOOL hasWiFi;
/*! @brief Determine if the device has accelerometer hardware */
@property (assign, readonly) BOOL hasAccelerometer;
/*! @brief Determine if the device has gyroscope hardware */
@property (assign, readonly) BOOL hasGyro;
/*! @brief Determine if the device has magnetometer (compass) hardware */
@property (assign, readonly) BOOL hasCompass;
/*! @brief Determine if the device has GPS hardware */
@property (assign, readonly) BOOL hasGPS;
/*! @brief Determine if the device has Bluetooth hardware */
@property (assign, readonly) BOOL hasBluetooth;
/*! @brief Determine if the device has Bluetooth low energy hardware */
@property (assign, readonly) BOOL hasBluetoothLowEnergy;
/*! @brief Determines if the device has FaceTime. This property will only work on internal builds. */
@property (assign, readonly) BOOL hasFaceTime;
/*! @brief Determines if the device has AirDrop capabilities */
@property (assign, readonly) BOOL hasAirDrop;
/*! @brief Determines if the device has AWDL capabilities */
@property (assign, readonly) BOOL hasAWDL;
/*! @brief Determine if the device has LTE  */
@property (assign, readonly) BOOL hasLTE;
/*! @brief Determine if the device has CDMA  */
@property (assign, readonly) BOOL isCDMA;
/*! @brief Determine if the device has Thumper Capability  */
@property (assign, readonly) BOOL supportsThumper;
/*! @brief Determine if the device supports Apple Wireless Diagnostics.  */
@property (assign, readonly) BOOL hasAWD;
/*! @brief Determine if the device has LTE  */
@property (assign, readonly) BOOL hasTDSCDMA;
/*! @brief Determine if the device's carrier supports FaceTime over cellular.  */
@property (assign, readonly) BOOL supportsFaceTimeOverCellular;
/*! @brief Determine if the device's carrier supports Tethering over cellular.  */
@property (assign, readonly) BOOL supportsTetheringOverCellular;
/*! @brief Determine if the device has Oscar sideband.  */
@property (assign, readonly) BOOL hasOscarSideband;
/*! @brief Determine if the device has an SEP.  */
@property (assign, readonly) BOOL hasSEP;
/*! @brief Determine if the device has Mesa (Touch ID).  */
@property (assign, readonly) BOOL hasMesa;
/*! @brief Determine if the device has an NFC radio.  */
@property (assign, readonly) BOOL hasNFC;
/*! @brief Determine if the device has a secure element.  */
@property (assign, readonly) BOOL hasSecureElement;
/*! @brief Determine if the device connects with USB Lightning Connector.  */
@property (assign, readonly) BOOL hasLightningConnector;
/*! @brief Determine the type of secure element (DEV or PROD).  */
@property (weak, readonly) NSString* secureElementType;
/*! @brief Determine if the device has supports App store.  */
@property (assign, readonly) BOOL supportsAppStore;
/*! @brief Determine if the device has supports Assistant (Siri).  */
@property (assign, readonly) BOOL supportsAssistant;
/*! @brief Determine if the device is an Apple TV.  */
@property (assign, readonly) BOOL isAppleTV;
/*! @brief Determine if the device is an Apple Watch.  */
@property (assign, readonly) BOOL isAppleWatch;
/*! @brief Determine if the device can be a Watch Companion.  */
@property (assign, readonly) BOOL isWatchCompanion;
/*! @brief Determine Baseband Chipset identifier. */
@property (assign, readonly) NSString* basebandChipset;
/* @} End Device Capabilities */

/*!
 @name System Properties
 @{
 */
/*! @brief ram */
@property (copy, readonly) NSNumber* ram;
/*! @brief Disk Capacity */
@property (copy, readonly) NSNumber* diskCapacity;
/*! @brief Data Partition Size in gigabytes*/
@property (copy, readonly) NSNumber* dataPartitionSize;
/*! @brief Free Disk Space in gigabytes */
@property (copy, readonly) NSNumber* freeDiskSpace;
/*! @brief iBoot Version */
@property (copy, readonly) NSString* iBootVersion;
/*! @brief Kernel Type */
@property (copy, readonly) NSString* kernelType;
/*! @brief Battery Identifier */
@property (copy, readonly) NSNumber* batteryID;
/*!
 @return    Returns the device's battery state
 @abstract  0 = UIDeviceBatteryStateUnknown,
 1 = UIDeviceBatteryStateUnplugged,   // on battery, discharging
 2 = UIDeviceBatteryStateCharging,    // plugged in, less than 100%
 3 = UIDeviceBatteryStateFull,        // plugged in, at 100%
 */
@property (copy, readonly) NSString* batteryState;
/*!
 @return    Returns the device's battery level between 0 and 1, or -1 if no value could be read.
 */
@property (copy, readonly) NSNumber* batteryLevel;
/*! @brief Model Number */
@property (copy, readonly) NSString* modelNumber;
/*! @brief Product Version */
@property (copy, readonly) NSString* productVersion;
/*! @brief Time Interval Since 1970 */
@property (copy, readonly) NSNumber* timeIntervalSince1970;         // Returns an int or nil.
/*! @brief Time Zone Offset From UTC */
@property (copy, readonly) NSNumber* timeZoneOffsetFromUTC;         // Returns a float or nil.
/*! @brief Activation Public Key */
@property (copy, readonly) NSData*   activationPublicKey;
/*! @brief Software Bundle Version */
@property (copy, readonly) NSString* softwareBundleVersion;
/*! @brief Time Zone */
@property (copy, readonly) NSString* timeZone;
/*! @brief Determine if the device is password protected */
@property (copy, readonly) NSNumber* passwordProtected;             // Returns a BOOL or nil.
/*! @brief Determing if the device is set to use the 24 hour clock */
@property (copy, readonly) NSNumber* uses24HourClock;               // Returns a BOOL or nil.
/*! @brief Partition Type */
@property (copy, readonly) NSString* partitionType;
/*! @brief Region Info */
@property (copy, readonly) NSString* regionInfo;
/*! @brief Springboard Lockdown Ever Registered Key */
@property (copy, readonly) NSNumber* sbLockdownEverRegisteredKey;   // Returns a BOOL or nil.
/*! @brief Supported Device Families */
@property (copy, readonly) NSArray*  supportedDeviceFamilies;
/*! @brief Activation State Acknowledged */
@property (copy, readonly) NSNumber* activationStateAcknowledged;   // Returns a BOOL or nil.
/*! @brief Average Temperature */
@property (copy, readonly) NSNumber* averageTemp;
/*!
 @return    Returns the device's thermal pressure level
 @abstract  Values defined in enum OSThermalPressueLevel in header <libkern/OSThermalNotification.h>
 */
@property (copy, readonly) NSString* thermalPressureLevel;
/* @} End System Properties */

/*!
 @name System-on-a-chip Properties
 @{
 */
/*! @brief Production SoC */
@property (copy, readonly) NSNumber* productionSOC;
/*! @brief Chip Die Identifier */
@property (copy, readonly) NSNumber* dieID;
/*! @brief Unique Chip Identifier. This is also the device's ECID. */
@property (copy, readonly) NSNumber* uniqueChipID;
/*! @brief Core Voltages */
@property (copy, readonly) NSArray*  coreVoltages;
/*! @brief SoC Type */
@property (copy, readonly) NSString* socType;
/*! @brief SoC Revision */
@property (copy, readonly) NSString* socRevision;
/*! @brief SoC Name */
@property (copy, readonly) NSString* socName;
/*! @brief Architecture of the CPU (i.e. 'armv6' or 'armv7') */
@property (copy, readonly) NSString* cpuArchitecture;
/*! @} End System-on-a-chip Properties */

/*!
 @name Display Properties
 @{
 */
/* @brief LCM Build Type (e.g. 'EVT1', 'DVT3', 'MP1', ...) */
@property (copy, readonly) NSString* lcmBuild;
/* @brief LCM Vendor */
@property (copy, readonly) NSString* lcmVendor;
/* @brief LCM Device Type (e.g. 'N90', 'K48', ...) */
@property (copy, readonly) NSString* lcmDevice;
/* @brief LCM Autoboot Support */
@property (readonly)       BOOL      lcmAutoboot;
/* @brief LCM Native Color */
@property (copy, readonly) NSString* lcmNativeColor;
/* @brief LCM Backlight Calibration Byte */
@property (readonly) uint8_t lcmBacklightCalibration;
/* @brief LCM Raw Panel ID */
@property (copy, readonly) NSString* lcmRawPanelID;
/* @} End Display Properties */

/*!
 @name Identity Properties
 @{
 */
/*! @brief Customized, friendly name of the device */
@property (copy)           NSString* deviceName;
/*! @brief A hash of a shuffled form of UniqueDeviceID. Used in log files. */
@property (copy, readonly) NSString* inverseDeviceID;
/*! @brief Category string describing the device (i.e. 'iPad') */
@property (copy, readonly) NSString* deviceClass;
/*! @brief Whether the device is running an emulated build variant */
@property (readonly) BOOL isEmulatedDevice;
/*! @brief mlbSerialNumber */
@property (copy, readonly) NSString* mlbSerialNumber;
/*! @brief Case color of the device (white, black) */
@property (copy, readonly) NSString* deviceColor;
/*! @brief Release type of the device  */
@property (copy, readonly) NSString* releaseType;
/*! @brief Denotes if a device has a carrier build */
@property (copy, readonly) NSNumber* carrierBuild;
/*! @brief Denotes if a device has an internal build */
@property (copy, readonly) NSNumber* isInternal;
/*! @brief Denotes if a device has an UI build */
@property (copy, readonly) NSNumber* uiBuild;
/*! @brief Board ID value */
@property (copy, readonly) NSString* boardID;
/*! @} End Indentity Properties */


/*!
 @name Host Properties
 @{
 */
/*! @brief logPath */
@property (copy, readonly) NSString* logPath;
/*! @brief trustedHostAttached
	@return BOOL or nil
 */
@property (copy, readonly) NSNumber* trustedHostAttached;
/*! @brief Determine if a host is attached.
	@return BOOL or nil
 */
@property (copy, readonly) NSNumber* hostAttached;
/*! @} Host Properties */

/*!
 @name Baseband Properties
 @{
 */
/*! @brief International Mobile Subscriber Identity of the current SIM card */
@property (copy, readonly) NSString* imsi;
/*! @brief Integrated Circuit Card Identifier of the current SIM card */
@property (copy, readonly) NSString* iccid;
/*! @brief Mobile Subscriber Network Code */
@property (copy, readonly) NSString* mobileSubscriberNetworkCode;
/*! @brief Mobile Subscriber Country Code */
@property (copy, readonly) NSString* mobileSubscriberCountryCode;
/*! @brief Baseband's serial number */
@property (copy, readonly) NSData* basebandSerialNumber;
/*! @brief String representation of the baseband firmware version number */
@property (copy, readonly) NSString* basebandVersion;
/*! @brief Baseband status */
@property (copy, readonly) NSString* basebandStatus;
/*! @brief Name of the active carrier */
@property (copy, readonly) NSString* operatorName;
/*! @brief String representation of the device's International Mobile Equipment Identity */
@property (copy, readonly) NSString* imei;
/*! @brief Current self-reported phone number of the device */
@property (copy, readonly) NSString* phoneNumber;
/*! @brief SIM card status string */
@property (copy, readonly) NSString* simStatus;
/*! @brief SIM card status string */
@property (copy, readonly) NSString* simTrayStatus;
/*! @brief Number of calls currently active */
@property (copy, readonly) NSNumber* callsInProgress;               // Returns a BOOL or nil.
/*! @brief Baseband bootloader version string*/
@property (copy, readonly) NSString* basebandBootloaderVersion;
/*! @brief MEID string */
@property (copy, readonly) NSString* meid;
/*! @brief Denotes if a device has telephony capability */
@property (copy, readonly) NSNumber* telephonyCapability;
/*! @brief Returns the active carrier technology. -1 for Unknown, 0 for GSM, 1 for CDMA. */
@property (copy, readonly) NSNumber* carrierTechnology;
/*! @brief Returns the Carrier Name. */
@property (copy, readonly) NSString* carrierName;

/*! @} Baseband Properties */



/*!
 @name Security Properties
 @{
 */
/*! @brief Effective security mode for Ap */
@property (copy, readonly) NSNumber* effectiveSecurityModeAp;
/*! @brief Effective security mode for SEP */
@property (copy, readonly) NSNumber* effectiveSecurityModeSEP;
/*! @brief Certificate security mode */
@property (copy, readonly) NSNumber* certificateSecurityMode;

/*! @} Security Properties */


/*!
 @name Production Status Properties
 @{
 */
/*! @brief Effective production status for Ap */
@property (copy, readonly) NSNumber* effectiveProductionStatusAp;
/*! @brief Effective production status for SEP */
@property (copy, readonly) NSNumber* effectiveProductionStatusSEP;
/*! @brief Certificate production status */
@property (copy, readonly) NSNumber* certificateProductionStatus;

/*! @} Production Status Properties */

/*!
 @name Other Properties
 @{
 */
/*! @brief sdio Product Info */
@property (copy, readonly) NSString* sdioProductInfo;
/*! @brief Protocol Version */
@property (copy, readonly) NSString* protocolVersion;
/*! @brief iosdio Product ID */
@property (copy, readonly) NSNumber* iosdioProductID;               // Returns an int or nil.
/*! @brief iosdio Manufacturer ID */
@property (copy, readonly) NSNumber* iosdioManufacturerID;          // Returns an int or nil.
/*! @brief Denotes if the device supports WiFi */
@property (copy, readonly) NSNumber* supportsWiFi;
/*! @brief Denotes if the device is capable of syncing over WiFi */
@property (copy, readonly) NSNumber* supportsWiFiSyncing;
/*! @brief WiFi Media Access Control Address */
@property (copy, readonly) NSString* wiFiAddress;
/*! @brief Bluetooth Media Access Control Address */
@property (copy, readonly) NSString* bluetoothAddress;
/*! @} Other Properties */
/*! @brief Flag indicating the device is expected to experience a detach event */
@property (atomic, readwrite) CAMEmbeddedDeviceSleepCyclerRequest sleepCycleRequest;
/*! @} Other Properties */

@end
