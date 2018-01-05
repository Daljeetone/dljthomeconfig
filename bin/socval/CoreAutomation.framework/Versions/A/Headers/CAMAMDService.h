//
//  CAMAMDService.h
//  CoreAutomation
//
//  Created by Matt Massicotte on 11/9/10.
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CAMAMDConnection;

/*! 
 @interface CAMAMDService
 @discussion Provides interaction with the AMD service with an iOS device.
 */
@interface CAMAMDService : NSObject
{
    NSString* name;
    
    // declare this CFTypeRef so we don't need to link/include MobileDevice
    CFTypeRef connectionRef;
    
    dispatch_queue_t     connectionIOQueue;
    dispatch_source_t    connectionReadSource;
    
    BOOL                 defaultPlistHandling;
    BOOL                 (^readHandler)(NSData*);
}

/*! 
 @method initWithName
 @discussion Initializes service and specifies the way commands are sent.
 @param aName
	Arbitrary name?
 @param useDefault
	Default is to send plists.
 */
- (id)initWithName:(NSString*)aName usingDefaultPlistHandling:(BOOL)useDefault;

/*! 
 @method initWithName
 @discussion Initializes service and specifies the way commands are sent.
 @param aName
	Arbitrary name?
 */
- (id)initWithName:(NSString*)aName;

/*! 
 @method startWithAMDConnection
 @discussion Starts a service to the device using the given connection.
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
 @method setReadDataHandler
 @discussion Specifies a block to handle a data read.
 @param block
	The block to do the read.
 */
- (void)setReadDataHandler:(BOOL (^)(NSData*))block;

/*! 
 @method read
 @discussion Read the specific data over AMD service.
 @param buffer
	Buffer to get the data.
 @param len
	Length of the buffer
 @result
    -1 on failure, 0 if the connection is closed, or the number of bytes sent.	
 */
- (NSInteger)read:(uint8_t*)buffer maxLength:(NSUInteger)len;

/*! 
 @method write
 @discussion Data to write to AMD service.
 @param buffer
	Buffer to write.
 @param len
	Length of the buffer to write.
 @result
	write return code.
 */
- (NSInteger)write:(const uint8_t*)buffer maxLength:(NSUInteger)len;

/*! 
 @method writeByte
 @discussion Writes just one byte.
 @param byte
	The byte to write.
 */
- (void)writeByte:(const uint8_t)byte;

/*! 
 @method sendMessage
 @discussion Sends a message via AMD service.
 @param message
	PList of the message to send.
 @param date
	Waits until this date, then returns.
 */
- (CFPropertyListRef)sendMessage:(CFPropertyListRef)message waitForResponseUntilDate:(NSDate*)date;

/*! 
 @property started
 @discussion Determines if the service is started.
 */
@property (assign, readonly) BOOL started;

/*!
 @property isValid
 @discussion Determines if the service is still valid.
 */
@property (assign, readonly) BOOL isValid;

/*! 
 @property name
 @discussion Name given.
 */
@property (copy, readonly) NSString* name;

/*!
 @method underlyingSocket
 @discussion The socket being used for communication with the service
 */
- (int)underlyingSocket;

@end
