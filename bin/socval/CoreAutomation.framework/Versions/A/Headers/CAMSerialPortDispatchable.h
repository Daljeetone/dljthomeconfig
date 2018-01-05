//
//  CSAMSerialPortDispatched.h
//  B188WirelessStress
//
//  Created by Jeffrey McGovern on 8/17/16.
//  Copyright © 2016 Apple, Inc. All rights reserved.
//

#ifndef CSAMSerialPortDispatchable_h
#define CSAMSerialPortDispatchable_h

#import <Foundation/Foundation.h>
#import <CoreAutomation/CoreAutomation.h>
#import <CoreAutomation/CAMSerialPort.h>

/*!
 @interface CAMSerialPortDispatchable
 @discussion Writes and reads from a serial device, with the optional ability to reopen the device with O_EVTONLY to add a callback to a queue that uses adds the callback to the queue whenever data is ready to be read from the serial device.
 */
@interface CAMSerialPortDispatchable : CAMSerialPort

#pragma mark -
/*!
 @method dispatchReadEventHandler:callback:
 @brief Uses ioctl to allow the serial port to be reopened, reopens it with O_EVTONLY, builds a dispatch source on the given queue that calls the given callback when data is ready to be read, and returns the dispatch source created so that it can be closed later when the use is over
 @param queue dispatch queue to place the callback onto
 @param callback dispatch block to be placed onto the dispatch queue whenever data is ready to be read
 @return Dispatch source created in this process
 */
- (dispatch_source_t)dispatchReadEventHandler:(dispatch_queue_t)queue callback:(dispatch_block_t)callback;

#pragma mark -
/*!
 @method readOutput
 @brief Consumes any output from the serial port, returning it as an NSString object
 @return String output read from the serial port
 */
- (NSString *)readOutput;

@end

#endif /* CSAMSerialPortDispatchable_h */
