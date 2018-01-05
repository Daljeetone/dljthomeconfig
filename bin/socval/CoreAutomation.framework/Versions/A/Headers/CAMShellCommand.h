//
//  CAMShellCommand.h
//  CoreAutomation
//
//  Created by Matt Massicotte on 11/9/10.
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/*! 
 @interface CAMShellCommand
 @discussion A CAMShellCommand provides an interface for creating a shell command.  This object should contain all info related to the shell command intended to execute.
 */
@interface CAMShellCommand : NSObject
{
    BOOL wait;
    NSString*      user;
    NSString*      command;
    NSTimeInterval timeout;
    
    NSString*      standardOut;
}

/*! 
 @property wait
 @discussion The wait property should tell the call to wait until the command is complete or to proceed before completion.
 */
@property (assign) BOOL           wait;

/*! 
 @property user
 @discussion This property should specify the user that will run the command.
 */
@property (copy)   NSString*      user;

/*! 
 @property command
 @discussion This property should have the full contents of the shell command to be executed.
 */
@property (copy)   NSString*      command;

/*! 
 @property timeout
 @discussion This property provides a timeout in order to catch a command that is taking longer than expected.  The current default is 5.0 (used to determin 5 seconds).
 */
@property (assign) NSTimeInterval timeout;

/*! 
 @property standardOut
 @discussion This property should be used to get the STDOUT created from executing the command.
 */
@property (copy)   NSString*      standardOut;

@end
