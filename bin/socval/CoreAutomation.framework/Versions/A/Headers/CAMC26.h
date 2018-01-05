//
//  CAMC26.h
//  coreautomationd
//
//  Created by Brandon Kieft on 7/9/14.
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CAMReturnValues.h"

#define kCAMC26ShortName c26

#define kCAMC26StreamTypeDockControl       0x00
#define kCAMC26StreamTypeiAUP              0x01
#define kCAMC26StreamTypePing              0x02
#define kCAMC26StreamTypePong              0x03
#define kCAMC26StreamTypeAuthentication    0x04

@protocol CAMC26
@optional

/*!
 @method    openStreamWithType:
 @abstract  Opens a C26 stream of the specified type
 @return    Returns a UUID string used to identify the stream.
*/
- (CAMReturnString *)openStreamWithType:(NSNumber *)streamType;

/*!
 @method        sendData:toStream:
 @abstract      Sends the given bytes to the specified stream
 @description   The stream UUID must match a UUID returned by the openStreamWithType: method
 @return        YES if the bytes were sent successfully, otherwise NO
 */
- (CAMReturnBool *)sendData:(NSData *)data toStream:(NSString *)streamUUID;


/*!
 @method        receiveData
 @abstract      Receives data from the specified stream
 @description   The stream UUID must match a UUID returned by the openStreamWithType: method.
 @return        An NSArray of NSDictionary objects if the read was successful, otherwise nil. The NSDictionary objects have two keys: "data" and "timestamp".
 */
- (CAMReturnArray *)receiveDataFromStream:(NSString *)streamUUID;

- (CAMReturnBool *)waitForAuthenticationCompletion:(NSNumber *)timeout;

@end
