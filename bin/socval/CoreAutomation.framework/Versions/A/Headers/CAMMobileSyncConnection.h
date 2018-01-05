//
//  CAMMobileSyncConnection.h
//  CoreAutomation
//
//  Created by Shannon Ma on 6/1/11.
//  Copyright 2011 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
@class CAMConnection;


/*! 
 @interface CAMMobileSyncConnection
 @discussion Service to handle iOS backups/restores.
 */
@interface CAMMobileSyncConnection : NSObject
{
    CAMConnection *_connection;
}

#pragma mark -
#pragma mark Creating a Connection

/*! 
 @method initWithConnection
 @discussion Initializes the service with connection to the device.
 @param connection
	Connection to device.
 */
- (id)initWithConnection:(CAMConnection *)connection;

/*! 
 @method connectionWithConnection
 @discussion Connects to device in specified state.
 @param connection
	Connection to device.
 */
+ (instancetype)connectionWithConnection:(CAMConnection *)connection;

#pragma mark -
#pragma mark Backup

/*!
 @brief Backup a device from the network.
 */
- (BOOL)backupFromNetwork;

/*!
 @brief Backup a device from the network.
 @param block   Block that will be run whenever backup progress has changed.
*/
- (BOOL)backupFromNetworkUsingProgressBlock:(void (^)(NSUInteger percent))block;

/*!
 @brief Backup a device from the local host.
 */
- (BOOL)backupFromLockdown;

/*!
 @brief Backup a device from the local host.
 @param block   Block that will be run whenever backup progress has changed.
 */
- (BOOL)backupFromLockdownUsingProgressBlock:(void (^)(NSUInteger percent))block;

#pragma mark -
#pragma mark Restore

/*!
 @brief Restores a device's latest backup from the network.
 @param copyBackup          Denotes if the backup should be copied when restoring.
 @param password            Specify nil here unless the backup file is encrypted.
                            If nil is specified and the backup file is encrypted, we'll try get the password from Keychain.
 */
- (BOOL)restoreFromNetworkAndCopy:(BOOL)copyBackup password:(NSString *)password;

/*!
 @brief Restores a device from the network.
 @param sourceIdentifier    Name of the backup that will be used.
 @param copyBackup          Denotes if the backup should be copied when restoring.
 @param password            Specify nil here unless the backup file is encrypted.
                            If nil is specified and the backup file is encrypted, we'll try get the password from Keychain.
 @param block               Block that will be run whenever restore progress has changed.
 */
- (BOOL)restoreSourceFromNetwork:(NSString *)sourceIdentifier copy:(BOOL)copyBackup password:(NSString *)password usingProgressBlock:(void (^)(NSUInteger percent))block;

/*!
 @brief Restores a device's latest backup from the local host.
 @param copyBackup          Denotes if the backup should be copied when restoring.
 @param password            Specify nil here unless the backup file is encrypted.
                            If nil is specified and the backup file is encrypted, we'll try get the password from Keychain.
 */
- (BOOL)restoreFromLockdownAndCopy:(BOOL)copyBackup password:(NSString *)password;

/*!
 @brief Restores a device on the local host.
 @param sourceIdentifier    Name of the backup that will be used.
 @param copyBackup          Denotes if the backup should be copied when restoring.
 @param password            Specify nil here unless the backup file is encrypted.
                            If nil is specified and the backup file is encrypted, we'll try get the password from Keychain.
 @param block               Block that will be run whenever restore progress has changed.
 */
- (BOOL)restoreSourceFromLockdown:(NSString *)sourceIdentifier copy:(BOOL)copyBackup password:(NSString *)password usingProgressBlock:(void (^)(NSUInteger percent))block;

/*!
 @brief Cancels the current backup or restore operation.
 */
- (BOOL)cancelBackupRestore;

@end
