//
//  CAMSerialPort.h
//  CoreAutomation
//
//  Created by Matt Massicotte on 3/8/10.
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "CAMIOService.h"
#import <termios.h>

extern NSString *const CAMSerialPortSpeedKey;

/*!
 @interface CAMSerialPort
 @discussion CAM serial port class.
 */
@interface CAMSerialPort : CAMIOService {
    NSFileHandle *hostFile;
    dispatch_queue_t connectionIOQueue;
    dispatch_source_t connectionReadSource;

    int fileDescriptor;
    struct termios originalTermiosOptions;

    int maximumReadAttempts;
    int delayBetweenReads;
    int delayBetweenWrites;

    NSMutableString *serialReadBuffer;
    NSMutableString *serialWriteBuffer;

    NSDateFormatter *dateFormatter;
    BOOL lastLogLineEndedWithNewline;
}

/*!
 @method serialPortWithBSDPath
 @discussion Create serial port with BSD path.
 @param path
	BSD path.
 */
+ (id)serialPortWithBSDPath:(NSString *)path;

/*!
 @method initWithoutSearchWithBSDPath
 @discussion Create serial port with BSD path, doesn't try to match device to USB BSD serial through search
 @param path
 BSD path.
 */
- (id)initWithoutSearchWithBSDPath:(NSString *)path;

/*!
 @method allDevicesMatchingDictionary
 @discussion Gets an NSDictionary for all devices over serial.
 @result
	NSDictionary of devices.
 */
+ (NSDictionary *)allDevicesMatchingDictionary;

/*!
 @property bsdPath
 @discussion Gets the BSD path.
 */
@property(nonatomic, copy, readonly) NSString *bsdPath;

#pragma mark Configurable options
/*!
 @property maximumReadAttempts
 @discussion Option for maximun read attempts.
 */
@property(assign) int maximumReadAttempts;

/*!
 @property delayBetweenReads
 @discussion Option for the delay between reads.
 */
@property(assign) int delayBetweenReads;

/*!
 @property delayBetweenWrites
 @discussion Option for delay between writes.
 */
@property(assign) int delayBetweenWrites;

#pragma mark Read and Write buffers
/*!
 @property serialReadBuffer
 @discussion Option for serial read buffer.
 */
@property(readonly) NSString *serialReadBuffer;

/*!
 @property serialWriteBuffer
 @discussion Option for serial write buffer.
 */
@property(readonly) NSString *serialWriteBuffer;

#pragma mark Open and Close
/*!
 @method open
 @discussion Opens the serial port.
 */
- (bool)open;

/*!
 @method openWithOptions
 @discussion Open serial port with options.
 @param optionsDictionary
	Options to pass in for opening serial port.
 */
- (bool)openWithOptions:(NSDictionary *)optionsDictionary;

/*!
 @method close
 @discussion Close the serial port.
 */
- (void)close;

#pragma mark Reading
/*!
 @method read
 @discussion Read from serial port. If you use one of these you will need to do your own checking and repeated attempt handling.
 @param buffer
	Buffer to read into.
 @param len
	Length to read in buffer.
 */
- (NSInteger)read:(uint8_t *)buffer maxLength:(NSUInteger)len;

/*!
 @method readByte
 @discussion Read byte from serial port. If you use one of these you will need to do your own checking and repeated attempt handling.
 @result
	Byte to read.
 */
- (uint8_t)readByte;

/*!
 @method readString
 @discussion Read string from serial.
 @result
	String with read data.
 */
- (NSString *)readString;

// all reads for these are inside for loops, if maximumReadAttempts is hit an NSException will
// be thrown
/*!
 @method readByteUntil
 @discussion Read string from serial until specified byte.
 @result
	Byte read.
 */
- (uint8_t)readByteUntil:(uint8_t)byte;

/*!
 @method readStringUntil
 @discussion Read string from serial until set of matching string.
 @param matchingString String to match that ends reading
 @result
	String with read data.
 */
- (NSString *)readStringUntil:(NSString *)matchingString;

/*!
 @method readStringUntilOneOf
 @discussion Read string from serial.
 @param matchingStrings
	Reads until the matching strings specified.
 @result
	String with read data.
 */
- (NSString *)readStringUntilOneOf:(NSArray *)matchingStrings;

#pragma mark Writing
//
/*!
 @method write
 @discussion Writes buffer to serial port. If you use one of these you will need to do your own checking and repeated attempt handling.
 @param buffer
	Buffer to write.
 @param len
	length of buffer to write.
 @result
	Integer result from writing a byte to serial.
 */
- (NSInteger)write:(const uint8_t *)buffer maxLength:(NSUInteger)len;
/*!
 @method writeByte
 @discussion Writes a byte to serial.
 @param byte
	Byte to write to serial.
 @result
	Integer result from writing a byte to serial.
 */
- (NSInteger)writeByte:(uint8_t)byte;

// these will throw exceptions if something does not go right
/*!
 @method writeString
 @discussion Write to serial. This will throw exceptions if something does not go right.
 @param string
	String to write.
 */
- (void)writeString:(NSString *)string;

/*!
 @method writeStringExpectingEcho
 @discussion Write to serial, expecting echo. This will throw exceptions if something does not go right.
 @param string
	String to write.
 */
- (void)writeStringExpectingEcho:(NSString *)string;

/*!
 @brief Set a path on the host to accept the serial stream from the device.
 @param path	A path on the host's filesystem. The parent directory must already exist, and the data will be appended if a file already exists.
 @return An error representing the reason why the log file could not be created. (Returned instead of passed-by-reference to make it easier to use from scripting bridges.)
 */
- (NSError *)setHostPath:(NSString *)path;

@end

@interface NSString (SerialPortAdditions)
- (NSString *)ASCIIValues;
@end
