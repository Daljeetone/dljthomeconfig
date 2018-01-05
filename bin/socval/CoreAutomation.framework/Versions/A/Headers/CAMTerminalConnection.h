//
//  CAMTerminalConnection.h
//  CoreAutomation
//
//  Created by Matt Massicotte on 4/2/10.
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "CAMCommunicating.h"

/*! 
 @interface CAMTerminalConnection
 @discussion This interface allows for connection to the terminal service in CAM.
 */
@interface CAMTerminalConnection : NSObject <CAMCommandLineInterfacing>
{
    @private
    NSString*       prompt;
    BOOL            stripPrompt;
    
    NSCharacterSet* newLineCharacterSet;
}

/*! 
 @property prompt
 @discussion Determines where the Terminal prompt is.
 */
@property (nonatomic, copy)   NSString* prompt;

/*! 
 @property stripPrompt
 @discussion This property determines if necessary to strip the prompt line of the output.
 */
@property (nonatomic, assign) BOOL      stripPrompt;

/*! 
 @method loginAs:withPassword:
 @discussion Supply the user credentials for the command.
 @param user
	The user to run the command as.
 @param password
	Password for the user specified.
 */
- (void)loginAs:(NSString*)user withPassword:(NSString*)password;

/*! 
 @method connect
 @discussion Connects to this Terminal service. Part of CAMCommandLineInterfacing.
 */
- (void)connect;

/*! 
 @method disconnect
 @discussion Disonnects to this Terminal service. Part of CAMCommandLineInterfacing.
 */
- (void)disconnect;


/*! 
 @method write
 @discussion This method writes what you specify to the command line in Terminal.
 @param string
	String to write.
 */
- (void)write:(NSString*)string;

/*! 
 @discussion Reads a byte at a time from the Terminal.
 @result
	The uint8_t byte read.
 */
@property (NS_NONATOMIC_IOSONLY, readonly) uint8_t readByte;

@end
