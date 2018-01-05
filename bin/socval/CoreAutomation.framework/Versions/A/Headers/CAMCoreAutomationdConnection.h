//
//  CAMCoreAutomationdConnection.h
//  CoreAutomation
//
//  Created by Chris Whitney on 10/26/11.
//  Copyright 2011 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CAMCoreAutomationdProxy.h"

@class CAMEmbeddedDevice;
@class CAMAMDConnection;
@class CAMAMDService;


/*! 
 @interface CAMCoreAutomationdConnection
 */
@interface CAMCoreAutomationdConnection : NSObject {
@private
    CAMAMDConnection* _connection;
    BOOL _isRoot;
}
	
#pragma mark -
#pragma mark Creating a Connection
/*!
 @name Creating a Connection
 @{
 */

/*!
 @brief Returns an initialized connection with coreautomationd via lockdown as the mobile user.
 @param aConnection	A CAMAMDConnection to a device instance that will accept the connection.
 */
- (instancetype)initWithAMDConnection:(CAMAMDConnection *)aConnection;

/*!
 @brief Returns an initialized connection with coreautomationd via lockdown.
 @param aConnection	A CAMAMDConnection to a device instance that will accept the connection.
 @param isRoot	Connect as either the "root" user or the "mobile" user.
 */
- (instancetype)initWithAMDConnection:(CAMAMDConnection *)aConnection asUserRoot:(BOOL)isRoot;

/*!
 @brief Returns a connection with coreautomationd via lockdown as the mobile user.
 @param aConnection	A CAMAMDConnection to a device instance that will accept the connection.
 */
+ (instancetype)connectionWithAMDConnection:(CAMAMDConnection *)aConnection;

/*!
 @brief Returns a connection with coreautomationd via lockdown.
 @param aConnection	A CAMAMDConnection to a device instance that will accept the connection.
 @param isRoot	Connect as either the "root" user or the "mobile" user.
 */
+ (instancetype)connectionWithAMDConnection:(CAMAMDConnection *)aConnection asUserRoot:(BOOL)isRoot;

#pragma mark -
#pragma mark Performing Commands
/*!
 @name Performing Commands
 @{
 */

/*!
 @brief	Perform a single coreautomationd command specified by a class keypath and method name
 @return A CAMReturn object, which stores both the return value and any error
 */
- (CAMReturn*)performCommandFromClass:(NSString*)classPath method:(NSString*)classMethod arguments:(NSArray*)args;

/*! @} Performing Commands */


#pragma mark -
#pragma mark Install coreautomationd
/*!
 @brief	Prepare coreautomationd on the device by syncing the coreautomationd root contained within CoreAutomation.framework to the device.
 @discussion This method is useful if the OS on the device is either missing coreautomationd or coreautomationd is out-of-date.
             However, there are some limitations to this method:
             1. CoreAutomation.framework must be installed using the .pkg installer. The Internal SDK version of CoreAutomation will not work.
             2. The device must have debug / codesign disabling boot-args set.
 @return Returns YES on success, NO on failure.
 */
+ (BOOL)installCoreAutomationd:(CAMEmbeddedDevice*)device;

/*!
 @brief	Sets a global timeout on connection commands. -1 is the default and means forever
 @discussion This is useful for multithreaded process where something blocking indefinitely is bad (and blocking other threads access the same object)
 */
+ (void)setGlobalTimeout:(NSInteger)timeout;


@end
