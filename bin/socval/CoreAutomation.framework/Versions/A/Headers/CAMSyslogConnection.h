//
//  CAMSyslogConnection.h
//  CoreAutomation
//
//  Created by Chris Whitney on 5/24/11.
//  Copyright 2011 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CAMEmbeddedDevice;
@class CAMAMDConnection;
@class CAMAMDService;


/*! 
 @class CAMSyslogConnection
 */
@interface CAMSyslogConnection : NSObject

#pragma mark -
#pragma mark Creating a Connection
/*!
 @name Creating a Connection
 @{
 */

/*!
 @brief Start a connection with syslog_relay to a device via lockdown.
 @discussion	Call startWithAMDConnection: again after any state
 @param aConnection	CAMAMDConnection to a device
 */
- (BOOL)startWithAMDConnection:(CAMAMDConnection *)aConnection;


/*!
 @brief Stop the connection with syslog_relay.
 */
- (void)stop;

/*! @} End Creating a Connection */

#pragma mark -
#pragma mark Handling Syslog Data
/*!
 @name Handling Syslog Data
 @{
 */

/*!
 @brief Execute a block when syslog text is available.
		The block will be called with the new syslog text since the last invocation of that block.
 @param block	Block that will process the data
 */
- (void)setSyslogDataHandler:(void (^)(CAMSyslogConnection *connection, NSString *syslogText))block;


/*!
 @brief Set a path on the host to accept the syslog stream from the device.
 @param path	A path on the host's filesystem. The parent directory must already exist, and the data will be appended if a file already exists.
 @return An error representing the reason why the log file could not be created. (Returned instead of passed-by-reference to make it easier to use from scripting bridges.)
 */
- (NSError*)setHostPath:(NSString *)path;

/*! @} End Handling Syslog Data  */

@end
