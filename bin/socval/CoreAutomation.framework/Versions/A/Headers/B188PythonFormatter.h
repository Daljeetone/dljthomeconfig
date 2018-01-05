//
//  B188PythonFormatter.h
//  B188WirelessStress
//
//  Created by Jeffrey McGovern on 8/19/16.
//  Copyright © 2016 Apple, Inc. All rights reserved.
//

#ifndef B188PythonFormatter_h
#define B188PythonFormatter_h

#import <Foundation/Foundation.h>
#import <CoreAutomation/CAMLogger.h>
#import "CAMSerialFormatter.h"

/*!
 @interface B188PythonFormatter
 @discussion Forks log_parser.py, which bterm.py uses, with python to make B188 output human readable and machine parsable.
 */
@interface B188PythonFormatter : NSObject <CAMSerialFormatter>

/*!
 @method defaultScriptDirectory
 @brief Evaluates and returns the default script directory, with the tilde expanded
 @return String of the default script directory with tilde expanded
 */
+ (NSString *)defaultScriptDirectory;

#pragma mark -
#pragma mark Creating the Formatter
/*!
 @name Creating the Formatter
 @{
 */

/*!
 @method initWithScriptDirectory
 @brief Initializer that will attempt to return a serial input/output formatter that forks a WAF python script in the default directory for formatting
 */
- (instancetype)init;
/*!
 @method initWithScriptDirectory
 @brief Initializer that will attempt to return a serial input/output formatter that forks a WAF python script in the given directory for formatting
 @param dir String of the full path to the directory enclosing the log_parser.py, source_parser.py, and host.logdata files
 */
- (instancetype)initWithScriptDirectory:(NSString *)dir;
/*! @} End Creating the formatter */

#pragma mark -
#pragma mark CAMSerialFormatter Functions
/*!
 @method formatInput
 @brief Formats the input string into a string suitable for sending to the serial device
 
 @param input NSString * the input command
 @return NSString * input command formatted for serial communication
 */
- (CAMReturnString *)formatInput:(NSString *)input;

/*!
 @method formatOutput
 @brief Formats the output string of the serial terminal into an appropriate format
 
 @param output NSString * the serial terminal output
 @return formatted output, suitable for further processing, be it human or machine readable
 */
- (CAMReturnString *)formatOutput:(NSString *)output;

/*!
 @method cleanup
 @brief Closes the pipes to the child process and kills it
 */
- (void)cleanup;

#pragma mark -
/*! @brief PID of the python child process */
@property(readonly) int childPid;

@end

#endif /* B188PythonFormatter_h */
