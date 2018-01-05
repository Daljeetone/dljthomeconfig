//
//  CAMSimpleAutomationProtocol.h
//  coreautomationd
//
//  Created by Yuk Lai Suen on 1/29/13.
//
//

#import <Foundation/Foundation.h>
#import "CAMReturnValues.h"

#define kCAMSimpleAutomationShortName simply

//!  Protocol for simple autotmation
/*!
 This protocol is mostly internal and should not be used by client objects. This interface can change. See SimpleAutomation.h for
 client usage.
 */

@protocol CAMSimpleAutomationProtocol <NSObject>
@property (nonatomic, retain, readonly) NSUUID *systemUUID; /**< system UUID for uniquely identify where simple automation is running. */
@property (nonatomic, retain, readonly) NSMutableDictionary *localObjectProxies; /**< A dictionary of all local object proxies for remote clients. */
@property (nonatomic, retain, readonly) NSMutableDictionary *remoteObjectProxies; /**< A dictionary of all remote proxies for local clients. */

/*!
 @method    sendMessage:
 @abstract  This send an invocation as an array. Client code should not need to call this directly.
 For example, in an class method invocation, the first message element would be the class name.
 The second message element would be the selector name.
 The third message onwards would be serialized objects or proxy objects from the remote side.
 @return    CAMReturn object with the value being the return of the call, serialized.
 */
- (CAMReturn*) sendMessage:(NSArray*)message;
@optional

/*!
 @method    executeMessage:
 @abstract  This executes the message locally. The message is same as those passed to "sendMessage:" function.
 @return    A dictionary with the class method names as keys and the type encodings of arguments and returns as values.
 */
- (CAMReturn*) executeMessage:(NSArray*)message;

/*!
 @method    _loadBundle:
 @abstract  Load remote bundle of specified path at run time.
 @return    CAMReturnVoid.
 */
- (CAMReturnBool*) _loadBundle:(NSString*)bundlePath;

/*!
 @method    _allClassesForBundlePath:
 @abstract  Load remote bundle of specified path at runtime if needed and return all its classes
 @return    CAMReturnDictionary with dictionary object that represents the bundle's class and protocol definitions.
 */
- (CAMReturnDictionary*) _allClassesForBundlePath:(NSString*)bundlePath;

/*!
 @method    _classForName:
 @abstract  return the class definition for the given name
 @return    CAMReturnDictionary with dictionary object that represents the bundle's class and protocol definitions.
 */
- (CAMReturnDictionary*) _classForName:(NSString*)className;


/*!
 @method    remoteDefinitionForClassName:
 @abstract  Returns the definition for a given class name.
 @return    CAMReturnDictionary of all remote class definitions.
 */
- (CAMReturnDictionary*)remoteDefinitionForClassName:(NSString *)className;

/*!
 @method    ping
 @abstract  This is a special function - a temporary solution to work around the lockdown message passing
 between the device and host. Since currently the host-to-device connection objects does not
 easily allow device to initiate a message to the host, the host is constantly pinging the device
 for callbacks.
 @return    CAMReturnArray with each element being a callback in the form of "deferred" message.
 The first element of the message is a random unique ID of message for tracking callback return
 values, and the second element being the actual message itself (an array similar to that
 passed to "sendMessage:" function).
 */
- (CAMReturnArray*) ping;


/*!
 @method    pingReturn:
 @abstract  This works together with ping. Ping fetches all the callbacks from the remote device.
 After the calls are made, pingReturn sends the return values back to the remote device.
 Each element of the finishedInvokes is an array, with the first element being the unique ID
 of the message returned from the ping call, and the second element being the return value.
 @return    CAMReturnVoid.
 */
- (CAMReturnVoid*) pingReturn:(NSArray*)finishedInvokes;

/*!
 @method    addDeferredMessage:waitLock:
 @abstract  Adds a "deferred" message (see method ping) with a waitlock to wait for the return value.
 @return    NSUUID randomly generated to uniquely identify this message when returned from the remote side.
 */
- (NSUUID*) addDeferredMessage:(NSArray*)message waitLock:(NSCondition*)lock;

/*!
 @method    removeDeferredmMessage:
 @abstract  Remove the "deferred" message (see method ping) with the specified UUID to avoid duplicated calls.
 */
- (void) removeDeferredMessage:(NSUUID*)uuid;

/*!
 @method    getDeferredMessageReturnValue:
 @abstract  Get the return value of a "deferred" message of the specified UUID.
 @return    The return value as object or primitive type.
 */
- (id) getDeferredMessageReturnValue:(NSUUID*)uuid;
@end
