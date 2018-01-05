//
//  CAMRsyncConnection.h
//  CoreAutomation
//
//  Created by Brandon Kieft on 1/23/14.
//
//

#import <Foundation/Foundation.h>
@class CAMAMDConnection;

/*!
 @interface CAMRsyncConnection
 @description Rsync files over a lockdown connection
 */
@interface CAMRsyncConnection : NSObject
{
    NSString *_username;
    NSString *_password;
    NSString *_module;
    CAMAMDConnection *_amdConnection;
    dispatch_semaphore_t _listeningSemaphore;
    uint16_t _listeningPort;
    NSTask *_rsyncTask;
}

/*!
 @brief Account name on the device
 @description The name of the account you want to log in as when running rsync. Defaults to 'root'
 */
@property (nonatomic, strong) NSString *username;

/*!
 @brief Password of the account
 @description The password for the account associated with the username
 */
@property (nonatomic, strong) NSString *password;

/*!
 @brief Module to use
 @description Modules are defined in /etc/rsyncd.conf on the device
 */
@property (nonatomic, strong) NSString *module;

/*!
 @brief Initialize a CAMRsyncConnection for communication over lockdown
 @param aConnection CAMAMDConnection used to connect to the device over lockdown
 */
- (instancetype)initWithAMDConnection:(CAMAMDConnection *)aConnection;

/*!
 @brief Transfers remote files over rsync
 @param remotePath The remote file path to receive
 @param localPath The local path to store the files
 @param options Rsync options as defined in the man pages. These are space delimited
 */
- (BOOL)receiveFromRemote:(NSString *)remotePath toLocal:(NSString *)localPath options:(NSString *)options;

/*!
 @brief Transfers local files over rsync
 @param remotePath The remote file path to store the files
 @param localPath The local file path to send
 @param options Rsync options as defined in the man pages. These are space delimited
 */
- (BOOL)sendToRemote:(NSString *)remotePath fromLocal:(NSString *)localPath options:(NSString *)options;

@end
