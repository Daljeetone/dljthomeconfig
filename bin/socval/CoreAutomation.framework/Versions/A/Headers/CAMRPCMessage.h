//
//  CAMRPCMessage.h
//  CoreAutomation
//
//  Created by Matt Massicotte on 6/19/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

/*!
 @interface CAMRPCMessage
 @discussion CAM RPC message.
 */
@interface CAMRPCMessage : NSObject
{
    NSString* target;
    NSString* method;
    NSArray*  arguments;
    BOOL      expectsReturn;
}

/*!
 @property target
 @discussion This is the target for RPC message.
 */
@property (copy)   NSString*  target;

/*!
 @property method
 @discussion RPC method.
 */
@property (copy)   NSString*  method;

/*!
 @property arguments
 @discussion RPC method arguments.
 */
@property (strong) NSArray*   arguments;

/*!
 @property expectsReturn
 @discussion The RPC method should expect to return.
 */
@property (assign) BOOL       expectsReturn;

/*!
 @property serializedData
 @discussion The serialized data of the RPC method.
 */
@property (strong, readonly) NSData* serializedData;

@end
