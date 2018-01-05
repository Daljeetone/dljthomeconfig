//
//  CAMLocknetConnection.h
//  CoreAutomation
//
//  Created by Matt Massicotte on 11/11/10.
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CAMAMDService;
@class CAMAMDConnection;
@class CAMShellCommand;

/*! 
 @interface CAMLocknetConnection
 @discussion Locknet is a lockdown implementation of telnet on the iOS device.  It is unclear how much longer this service will be around.
 */
@interface CAMLocknetConnection : NSObject
{
    CAMAMDService* locknetService;
    NSCondition*   readCondition;
    NSMutableData* readData;
    uint8_t        commandState;
    
    NSString*      user;
    NSString*      promptPattern;
    NSString*      firstPromptString;
}

/*! 
 @method startWithAMDConnection
 @discussion Starts service with the specified connection.
 @param aConnection
	CAMAMDConnection to the device.
 */
- (void)startWithAMDConnection:(CAMAMDConnection *)aConnection;

/*! 
 @method stop
 @discussion Stops the service.
 */
- (void)stop;

/*! 
 @method loginAs
 @discussion Logs in to telnet with these credentials.
 @param aUser
	Username.
 @param password
	Password.
 */
- (void)loginAs:(NSString*)aUser withPassword:(NSString*)password;

/*! 
 @method executeCommand
 @discussion Method to execute a command in locknet.
 @param shellCommand
	The CAMShellCommand object that represents your command.
 */
- (void)executeCommand:(CAMShellCommand*)shellCommand;

/*! 
 @property started
 @discussion Tells if the services is started.
 */
@property (assign, readonly) BOOL      started;

/*! 
 @property promptPattern
 @discussion Indicates the prompt pattern.
 */
@property (strong)           NSString* promptPattern;

@end
