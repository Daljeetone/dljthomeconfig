//
//  CAMMobileDeviceState.h
//  CoreAutomation
//
//  Created by Matt Massicotte on 8/24/10.
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class CAMEmbeddedDevice;
@class CAMShellCommand;
@class CAMShellProxy;
@class CAMCoreAutomationdConnection;
@class CAMSyslogConnection;
@class CAMAMDRestorableConnection;
@class CAMConnectionContainer;

@class CAMUIAutomationConnection;

#include <MobileDevice/MobileRestore.h>

@interface CAMMobileDeviceState : NSObject {
    uint32_t locationID;
    NSNumber *ecid;
    CAMAMDRestorableConnection *restorableConnection;

    NSString *_hardwareModelString;
    NSString *_productTypeString;
}

+ (void)startMonitoring;

// Only pay attention to certain locations ID, should be the first thing called in a process
+ (void)filterActivity:(uint32_t)locationID;

+ (void)enumerateAttachedDevices:(void (^)(CAMMobileDeviceState *device, BOOL *shouldStop))block;

+ (instancetype)state;

@property(assign) uint32_t locationID;
@property(copy) NSNumber *ecid;
@property(copy, readonly) NSString *udid;
@property(copy, readonly) NSString *serialNumber;
@property(assign, readonly) BOOL isResponsive;
@property(assign, readonly) BOOL isPresent;
@property(assign, readonly) BOOL isAttachedViaUSB;
@property(strong) CAMAMDRestorableConnection *restorableConnection;
@property(unsafe_unretained) CAMConnectionContainer *connections; // TODO: CHANGE THIS BACK TO WEAK WHEN ARC CONVERSION IS DONE!!!
@property(copy) NSString *readableStatus;

// called when device states are detected
- (void)handleAttached;
- (void)handleDetached;

// called when device states are matched to real CAMEmbeddedDevice instances
- (BOOL)matchesDevice:(CAMEmbeddedDevice *)theDevice;

// called to establish connections
- (void)connect;
- (void)disconnect;
- (void)reattach;

- (instancetype)initWithAMDRestorableConnection:(CAMAMDRestorableConnection *)connection;

// these are abstract methods that can be implemented by the concrete states
// CAMEmbeddedDevice can defer to these, so behavior can be customized for
// the various device states easily without having switch statements everywhere

// communicating
- (void)executeCommand:(CAMShellCommand *)command;
- (NSString *)runCommand:(NSString *)command andWaitForResult:(BOOL)wait asUser:(NSString *)aUser withTimeout:(NSTimeInterval)timeout;
- (NSString *)runCommand:(NSString *)command andWaitForResult:(BOOL)wait;
- (NSString *)runCommand:(NSString *)command;

- (BOOL)send:(NSString *)localPath toLocation:(NSString *)remotePath;
- (BOOL)send:(NSString *)localPath toLocation:(NSString *)remotePath resolvingSymlinks:(BOOL)resolveSymlinks;
- (BOOL)retrieve:(NSString *)remotePath toLocation:(NSString *)localPath;
- (BOOL)retrieve:(NSString *)remotePath toLocation:(NSString *)localPath resolvingSymlinks:(BOOL)resolveSymlinks;
- (BOOL)fileExistsAtPath:(NSString *)path;
- (BOOL)fileExistsAtPath:(NSString *)path isDirectory:(BOOL *)isDirectory;
- (BOOL)removeItemAtPath:(NSString *)path;
- (NSArray *)contentsOfDirectoryAtPath:(NSString *)path;
- (NSDictionary *)attributesOfFileAtPath:(NSString *)path;

- (void)runiBootCommand:(NSString *)command waitForCompletion:(BOOL)wait;

// State transitioning Methods
// The return indicates if a transition will actually occur
@property(NS_NONATOMIC_IOSONLY, getter=getToOS, readonly) BOOL toOS;
@property(NS_NONATOMIC_IOSONLY, getter=getToiBoot, readonly) BOOL toiBoot;
@property(NS_NONATOMIC_IOSONLY, getter=getToDFU, readonly) BOOL toDFU;
- (void)reboot;

// lockdown functions
@property(assign, readonly) BOOL isPaired;

- (void)deactivate;
- (void)pair;
- (void)unpair;

- (BOOL)installCarrierBundle:(NSString *)ipccPath;

- (BOOL)retrieveSources:(NSArray *)sources toLocation:(NSString *)localPath;
- (BOOL)retrieveSource:(NSString *)source toLocation:(NSString *)localPath;
- (BOOL)retrieveWithCrashCopier:(NSString *)remotePath toLocation:(NSString *)localPath;

@property(strong, readonly) CAMCoreAutomationdConnection *coreautomationdConnection;
@property(strong, readonly) CAMCoreAutomationdConnection *rootCoreautomationdConnection;

@property(unsafe_unretained, readonly) CAMSyslogConnection *syslogConnection;

@property(unsafe_unretained, readonly) CAMUIAutomationConnection *uiautomation;

// application install uninstall helper
- (void)installAppFromPath:(NSString *)path installType:(NSString *)type;
- (void)uninstallAppWithId:(NSString *)bundleId;
@property(NS_NONATOMIC_IOSONLY, getter=getInstalledApplications, readonly, copy) NSDictionary<NSString *, id> *installedApplications;
- (NSDictionary *)installedApplicationsMatchingFilter:(NSDictionary *)options;
- (void)addProvisioningProfile:(NSString *)path;
- (void)removeProvisioningProfile:(NSString *)profileId;
@property(NS_NONATOMIC_IOSONLY, getter=getProvisioningProfiles, readonly, copy) NSDictionary *provisioningProfiles;

// Media Bundle
- (BOOL)syncMediaAndABBundle:(NSString *)localPath __deprecated_msg("Use -[CAMEmbeddedDevice syncMediaAndABBundle:] instead.");

// Backup and Restore
@property(NS_NONATOMIC_IOSONLY, readonly) BOOL backupFromNetwork;
- (BOOL)backupFromNetworkUsingProgressBlock:(void (^)(NSUInteger percent))block;

@property(NS_NONATOMIC_IOSONLY, readonly) BOOL backupFromLockdown;
- (BOOL)backupFromLockdownUsingProgressBlock:(void (^)(NSUInteger percent))block;

- (BOOL)restoreFromNetworkAndCopy:(BOOL)copyBackup password:(NSString *)password;
- (BOOL)restoreSourceFromNetwork:(NSString *)sourceIdentifier copy:(BOOL)copyBackup password:(NSString *)password usingProgressBlock:(void (^)(NSUInteger percent))block;

- (BOOL)restoreFromLockdownAndCopy:(BOOL)copyBackup password:(NSString *)password;
- (BOOL)restoreSourceFromLockdown:(NSString *)sourceIdentifier copy:(BOOL)copyBackup password:(NSString *)password usingProgressBlock:(void (^)(NSUInteger percent))block;

@property(NS_NONATOMIC_IOSONLY, readonly) BOOL cancelBackupRestore;

// System Properties
@property(copy, readonly) NSString *productVersion;

// Identity Properties
@property(copy, readonly) NSString *hardwareModel;
@property(copy, readonly) NSString *productType;

@end

extern NSString *const CAMMobileDeviceAttachedNotification;
extern NSString *const CAMMobileDeviceDetachedNotification;
extern NSString *const CAMUSBDeviceAttachedNotification;
extern NSString *const CAMUSBDeviceDetachedNotification;
