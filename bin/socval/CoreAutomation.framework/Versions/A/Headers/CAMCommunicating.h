//
//  CAMCommunicating.h
//  CoreAutomation
//
//  Created by Matt Massicotte on 3/6/10.
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>

/*! 
 @protocol CAMCommandLineInterfacing
 @discussion This protocol is used to provide an interface with calling command line execution.
 */
@protocol CAMCommandLineInterfacing <NSObject>

/*! 
 @method runCommand
 @discussion This method should be implemented on the platform intended to run the command.
 @param command 
	The command to execute.
 @param wait 
	A flag to determine whether if execution should wait for a result or return immediately.
 @result 
	This would most likely be the STDOUT from the command execution.
 */
- (NSString*)runCommand:(NSString*)command andWaitForResult:(BOOL)wait;

@optional
/*! 
 @method runCommand
 @discussion This method should be implemented on the platform intended to run the command.
 @param command 
	The command to execute.
 @result 
	This would most likely be the STDOUT from the command execution.
 */
- (NSString*)runCommand:(NSString*)command;

@end

/*! 
 @protocol CAMFileTransferringDelegate
 @discussion This protocol is used to implement methods to listen for file transfer notifications.
 */
@protocol CAMFileTransferringDelegate <NSObject>

@optional

// Callbacks for async send and receive.
/*! 
 @method sendDidSucceed
 @discussion The file was sent successfully.
 @param localPath The path to the file to send.
 @param remotePath The path on the remote location for the file to go.
 */
- (void)sendDidSucceed:(NSString *)localPath toLocation:(NSString *)remotePath;

/*! 
 @method sendDidFail
 @discussion The file was NOT sent successfully.
 @param localPath The path to the file to send.
 @param remotePath The path on the remote location for the file to go.
 */
- (void)sendDidFail:(NSString *)localPath toLocation:(NSString *)remotePath;

/*! 
 @method retrieveDidSucceed
 @discussion The file retrieval was successful.
 @param localPath The path to the file to send.
 @param remotePath The path on the remote location for the file to go.
 */
- (void)retrieveDidSucceed:(NSString *)remotePath toLocation:(NSString *)localPath;

/*! 
 @method retrieveDidFail
 @discussion The file retrieval was NOT successful.
 @param localPath The path to the file to send.
 @param remotePath The path on the remote location for the file to go.
 */
- (void)retrieveDidFail:(NSString *)remotePath toLocation:(NSString *)localPath;

@end

/*! 
 @protocol CAMFileTransferring
 @discussion The protocol is used to provide an interface for file transfer.
 */
@protocol CAMFileTransferring <NSObject>

/*! 
 @method fileExistsAtPath
 @discussion The file path specified exists.
 @param path
	Checks if the file exists at the given path.
 @result
	YES if the path exists and NO if the path does not exist.
 */
- (BOOL)fileExistsAtPath:(NSString *)path;

/*!
 @method fileExistsAtPath
 @discussion The file path specified exists, and checks for directory.
 @param path
 Checks if the file exists at the given path.
 @param isDirectory
 Sets isDirectory to YES if the given path is a directory
 @result
 YES if the path exists and NO if the path does not exist.
 */
- (BOOL)fileExistsAtPath:(NSString *)path isDirectory:(BOOL *)isDirectory;

/*! 
 @method send
 @discussion This method attempts to send the contents of the local path to the remote path.
 @param localPath The path to the file to send.
 @param remotePath The path on the remote location for the file to go.
 @result
	YES if the send was successful and NO if the send was not.
 */
- (BOOL)send:(NSString *)localPath toLocation:(NSString *)remotePath;

/*!
 @method send
 @discussion This method attempts to send the contents of the local path to the remote path.
 @param localPath The path to the file to send.
 @param remotePath The path on the remote location for the file to go.
 @param resolveSymlinks If set to NO, this copies symlinks instead of copying the destination of the symlinks.
 @result
 YES if the send was successful and NO if the send was not.
 */
- (BOOL)send:(NSString *)localPath toLocation:(NSString *)remotePath resolvingSymlinks:(BOOL)resolveSymlinks;

/*! 
 @method sendAsync
 @discussion This method attempts to send a file to the remotePath asynchronously. This method should be used with the CAMFileTransferringDelegate delegate protocol to receive the notifications.
 @param localPath The path to the file to send.
 @param remotePath The path on the remote location for the file to go.
 */
- (void)sendAsync:(NSString *)localPath toLocation:(NSString *)remotePath;

/*! 
 @method retrieve
 @discussion This method is the corollary to send.  It is aimed at retrieving the file instead of sending it.
 @param remotePath The path on the remote location for the file to go.
 @param localPath The path to the file to send.
 @result
	YES if the file was retrieved and NO if it was not.
 */
- (BOOL)retrieve:(NSString *)remotePath toLocation:(NSString *)localPath;

/*!
 @method retrieve
 @discussion This method is the corollary to send.  It is aimed at retrieving the file instead of sending it.
 @param remotePath The path on the remote location for the file to go.
 @param localPath The path to the file to send.
 @param resolveSymlinks If set to NO, this copies symlinks instead of copying the destination of the symlinks.
 @result
 YES if the file was retrieved and NO if it was not.
 */
- (BOOL)retrieve:(NSString *)remotePath toLocation:(NSString *)localPath resolvingSymlinks:(BOOL)resolveSymlinks;

/*! 
 @method retrieveAsync
 @discussion This method is used to retrieve a file asynchronously and should be used with the CAMFileTransferringDelegate protocol.
 @param remotePath 
	The path on the remote location for the file to go.
 @param localPath 
	The path to the file to send.
 */
- (void)retrieveAsync:(NSString *)remotePath toLocation:(NSString *)localPath;

/*! 
 @method removeItemAtPath
 @discussion This method is used to remove a file or directory a the path. This method should be used with the CAMFileTransferringDelegate protocol.
 @param path 
	The path of the item to remove.
 */
- (BOOL)removeItemAtPath:(NSString *)path;

/*!
 @method contentsOfDirectoryAtPath
 @discussion This method is used to enumerate contents of directory
 @param path
    The path of the directory
 */
- (NSArray *)contentsOfDirectoryAtPath:(NSString *)path;

/*!
 @method attributesOfFileAtPath
 @discussion This method is used to list attributes of a file at a given path
 @param path
    The path of the file
 */
- (NSDictionary *)attributesOfFileAtPath:(NSString *)path;

- (id <CAMFileTransferringDelegate>)delegate;

/*! 
 @method setDelegate
 @discussion Use this method to set the delegate for notifications.
 @param aDelegate
	The delegate that implements the CAMFileTransferringDelegate protocol.
 */
- (void)setDelegate:(id <CAMFileTransferringDelegate>)aDelegate;

@end

/*! 
 @protocol CAMCommunicating
 @discussion This protocol should implement both CAMCommandLineInterfacing and CAMFileTransferring.
 */
@protocol CAMCommunicating <CAMCommandLineInterfacing, CAMFileTransferring>

/*! 
 @method connect
 @discussion Implements the connect to the CAMCommunicating service.
 */
- (void)connect;

/*! 
 @method disconnect
 @discussion Implements the disconnect to the CAMCommunication service.
 */
- (void)disconnect;

@end
