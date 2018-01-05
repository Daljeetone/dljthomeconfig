//
//  CAMUIAutomationConnection.h
//  CoreAutomation
//
//  Created by Jonathan B Morgan on 8/29/16.
//
//

#import <Foundation/Foundation.h>
#import "CAMCoreAutomationdProtocols.h"

@class CAMEmbeddedDevice;
@class CAMAMDConnection;
@class CAMAMDService;

@interface CAMUIAutomationConnection : NSObject

/*!
 @brief Returns an initialized connection with uiautomationd via lockdown as the mobile user.
 @param aConnection	A CAMAMDConnection to a device instance that will accept the connection.
 */
- (instancetype)initWithAMDConnection:(CAMAMDConnection *)aConnection;

/*!
 @brief Returns an initialized connection with uiautomationd via lockdown.
 @param aConnection	A CAMAMDConnection to a uiautomationd instance that will accept the connection.
 @param isRoot	Connect as either the "root" user or the "mobile" user.
 */
- (instancetype)initWithAMDConnection:(CAMAMDConnection *)aConnection asUserRoot:(BOOL)isRoot;

/*!
 @brief Returns a connection with uiautomationd via lockdown as the mobile user.
 @param aConnection	A CAMAMDConnection to a device instance that will accept the connection.
 */
+ (instancetype)connectionWithAMDConnection:(CAMAMDConnection *)aConnection;

/*!
 @brief Returns a connection with uiautomationd via lockdown.
 @param aConnection	A CAMAMDConnection to a device instance that will accept the connection.
 @param isRoot	Connect as either the "root" user or the "mobile" user.
 */
+ (instancetype)connectionWithAMDConnection:(CAMAMDConnection *)aConnection asUserRoot:(BOOL)isRoot;

-(void) stop;

#pragma mark -
#pragma mark Performing Commands

/*!
 @brief	Begins async execution of the passed in string of JavaScript on the device
 @param script A string containing a UIAutomation2 script.
 @return A dictionary confirming receipt of the script.
 */
- (NSDictionary *)runScript:(NSString *)script;

/*!
 @brief	Begins async execution of the passed in JavaScript file on the device
 @param filePath A path to a JavaScript file containing a UIAutomation2 script.
 @return A dictionary confirming receipt of the script.
 */
- (NSDictionary *)runFile:(NSString *)filePath;

/*!
 @brief	Gathers logs, errors, and return values for the currently running script on the device
 @return A dictionary containing script logs and, if the script has completed, any JS errors or return values emitted
 */
- (NSDictionary *)collectLogs;

/*!
 @brief Gets the version number of the device's uiautomationd Lockdown service.
 @return The version number from the device.
 */
- (NSNumber *)versionNumber;

@end
