//
//  CAMSerialFormatter.h
//  B188WirelessStress
//
//  Created by Jeffrey McGovern on 7/15/16.
//  Copyright © 2016 Apple, Inc. All rights reserved.
//

#ifndef CAMSerialFormatter_h
#define CAMSerialFormatter_h

#import <Foundation/Foundation.h>
#import <CoreAutomation/CAMReturnValues.h>

/*!
 @protocol CAMSerialFormatter
 @discussion Defines the messaging contract for a serial input and output formatter.
 */
@protocol CAMSerialFormatter <NSObject>

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

@optional
/*!
 @method cleanup
 @brief Cleans any limited resource (e.g. file descriptors, file handles, data structures)
 */
- (void)cleanup;

@end

#endif /* CAMSerialFormatter_h */
