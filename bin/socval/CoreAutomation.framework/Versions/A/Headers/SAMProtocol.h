//
//  SAMProtocol.h
//  coreautomationd
//
//  Created by Yuk Lai Suen on 2/22/13.
//
//

#import <Foundation/Foundation.h>
#import "SAMCoding.h"

//! Parent class for implementing remote protocol locally
/*!
 When you need to implement a protocol from the remote device, inherit from this class and implement the "protocolName:" function.
 A proxy object would be created for you when this object is passed to a call on a remote device. For example, when you need to implement
 a delegate objects to receive callbacks from another object on the remote device, implement your object to inherit from this class.
 */

@interface SAMProtocol : SAMCoding
/*!
 @method    protocolName:
 @abstract  This is an abstract function that returns nil. Inherited class must implement this 
			function to provide the name of the remote protocol that it implements.
 @return    Name of the remote protocol that the inherited class implements.
 */
- (NSString *) protocolName;

/*!
 @method    useMethodDefinitionsInClient:
 @abstract  Specify that SAM should use the method defintion from the client.
 @details	Protocol defintions might not be available to Objective-C runtime if they were not implemented
			in the framework nor used in \@protocol() call. To solve this problem, we can ask SAM to trust
			the method defintions defined by the child class of SAMProtocol. 
 @return    YES if use method definitions in client. NO by default.
 */
- (BOOL) useMethodDefinitionsInClient;
@end

