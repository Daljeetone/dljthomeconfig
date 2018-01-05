//
//  CAMPersistentConnection.h
//  CoreAutomation
//
//  This module will try to maintain a connection persistent between host framework and iOS device.
//  The hierarchy of this module is equivalent to CAMAMDConnection and CAMAMDService combined.
//
//  Created by Chen Huang on 8/21/15.
//
//

#import <Foundation/Foundation.h>
#import "CAMMobileDevice.h"
#import "CAMSocket.h"


@class CAMAMDPersistentConnection;

@protocol CAMAMDPersistentDelegate <NSObject>

/**
 *  This function will be invoked whenever there is a new plist arrived from the device
 *
 *  @param plist   The plist sent from device.
 *  @param connection the connection name
 */
- (void)AsyncReceivedResponse:(NSArray *)plist from:(id)connection;

@end


@interface CAMAMDPersistentConnection : NSObject

@property (readwrite, copy) NSString *name; // A custom name given by the delegate.
@property (readwrite, atomic, copy) ReadHandler read_handler;
@property (readonly, atomic, assign) AMDeviceRef device;
@property (readonly, atomic, copy) NSString *service_name;
@property (readwrite, assign) id<CAMAMDPersistentDelegate> delegate;

/*!
 @method initWithDeviceRef:withService:
 @discussion Initializes service and specifies the way commands are sent.
 @param device
    A device reference from MobileDevice.framework.
 @param service_name
    service to run on the device side. i.e. com.apple.coreautomation.coreautomationd
 */
- (id)initWithDeviceRef:(AMDeviceRef)device withService:(NSString *)service_name;

/*!
 @method startWithAMDConnection
 @discussion Starts a service (given by service name) to the device.
 */
- (void)startConnection;

/*!
 @method stopConnection
 @discussion Stops the service.
 */
- (void)stopConnection;

/**
 *  Whether the connection is valid or not
 *
 *  @return Bool
 */
- (BOOL)isValid;

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
 @method sendMessage
 @discussion Sends a message via AMD service.
 @param message
	PList of the message to send.
 @param date
	Waits until this date, then returns.
 */
- (CFPropertyListRef)sendMessage:(CFPropertyListRef)message waitForResponseUntilDate:(NSDate*)date;

@end