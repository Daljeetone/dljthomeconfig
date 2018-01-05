//
//  CAMSimpleAutomationHost.h
//  CoreAutomation
//
//  Created by Yuk Lai Suen on 2/5/13.
//
//

#import <Foundation/Foundation.h>
#import <Foundation/NSObject.h>
#import "CAMSimpleAutomationProtocol.h"
#import "CAMCoreAutomationdProxy.h"
// #import "CAMMobileDeviceState.h"

//!  CAMSimpleAutomation
/*!
 "Simplicity is the ultimate sophistication" - Leonardo da Vinci
 
 SimpleAutomation is an automation tool designed to simplify test automation between OSX and iOS. It also shortens the time 
 to test new APIs. Plug in a device with the new API, then test development for the new API can start right there on OSX.

 It enables all these by loading any frameworks (public or private) remotely on the phone, while allowing the test logic
 running on OSX. All protocol and class definitions are loaded at runtime and hence there is no requirement for static
 header/lib linking to the test code. If any custom objects need to be referenced remotely, a proxy object is created
 for the client underneath the hood. The proxy object would serialize and forward the actual call to the remote side that
 the real object resides. Return values are then returned from the remote side. If the return object is a custom object,
 then a proxy object is created again for your test to call methods on it.  All the heavy lifting is done automatically
 without you noticing it most of the time.
 
 SimpleAutomation also support delegation. Delegates are enabled by inheriting from supporting classes. (See SAMProtocol.)
 
 Example below:
 
 =======================================Test Code If I were to Program on iOS=============================================
 
 #import <CoreBluetooth/CoreBluetooth.h>
 @interface TestDelegate : NSObject<CBCentralManagerDelegate>
 - (void)centralManagerDidUpdateState:(CBCentralManager*)central;
 @end
 
 @implementation TestDelegate
 - (void)centralManagerDidUpdateState:(CBCentralManager*)central
 {
    NSLog(@"======Callback on Device ======");
    NSLog(@"Current state: %u", central.state()); // Note that we are making a call to a custom object passed into callback here.
 }
 @end
 
 #import <CoreBluetooth/CoreBluetooth.h>
 int main(int argc, const char * argv[])
 {
     ...
     TestDelegate *delegate = [[TestDelegate alloc] init];
     
     CBCentralManager *central = [[CBCentralManager alloc] initWithDelegate:delegate queue:nil];
     ...
 }
 
 =================================Test Code If I were to Program on OSX with SimpleAutomation=============================
 
 @interface TestDelegate : SAMProtocol // Inherit from a helper class from SimpleAutomation
 - (void)centralManagerDidUpdateState:(id)central;
 @end
 
 @implementation TestDelegate
 - (NSString*) protocolName
 {
     //Note that we have to implement this function to tell SimpleAutomation the remote protocol this delegate implements.
     return @"CBCentralManagerDelegate";
 }
 
 // Note that we have the same selector, but we use id instead of concrete type (CBCentralManager*) for any custom class inputs.
 // NSString, NSNumber, NSData are ok to be defined as is in the delegate interface.
 - (void)centralManagerDidUpdateState:(id)central
 {
     NSLog(@"======Callback on Host ======");
     NSLog(@"Current state: %u", central.state()); // Note that we are making a call to a custom object passed into callback here REMOTELY.
 }
 
 @end
 
 int main(int argc, const char * argv[])
 {
     ...
     // Dynamically load any framework, private or public, to test
     BOOL result = [device.simply loadBundle:@"/System/Library/Frameworks/CoreBluetooth.framework"];
 
     if (!result)
     {
         // failed to load bundle
         return 1;
     }

     TestDelegate *delegate = [[TestDelegate alloc] init];
     
     // We have to allocate the object on the device, but the rest of the calls, including init is the same.
     id central = [[[device.simply remoteClasses] CBCentralManager] initWithDelegate:delegate queue:nil];
     ...
 }
 
 =================================Test Code If I were to Program on OSX with SimpleAutomation in Python =============================
 from CoreAutomation import *
 
 class TestDelegate(SAMProtocol):
 def protocolName(self):
    return "CBCentralManagerDelegate"
 
 def centralManagerDidUpdateState_(self, central):
    print "======Callback on Host ======"
    print "Current state:", central.state()
 
 # device below is a CAMEmbeddedDevice object
 ret = device.simply().loadBundle_("/System/Library/Frameworks/CoreBluetooth.framework")
 if result:
    d = TestDelegate.alloc().init()
 
    central = device.simply().remoteClasses().CBCentralManager().initWithDelegate_queue_(d, None)
 
 */

@interface CAMSimpleAutomation : NSObject <CAMSimpleAutomationProtocol>
{
@private
    NSCondition *stopPingInvokeLock;
    BOOL pingInvokeStopped;
	NSUUID *systemUUID;
    dispatch_queue_t invokeQueue;
    NSMutableDictionary *localObjectProxies;
    NSMutableDictionary *remoteObjectProxies;
    NSMutableDictionary *remoteClassDefinitions;
    NSMutableDictionary *bundles;
    NSMutableArray *loadedBundlesPaths;
	CAMConnection *mobileConnection;
    BOOL asRoot;
}
@property (nonatomic, retain, readwrite) NSUUID *systemUUID; /**< system UUID for uniquely identify where simple automation is running. */

/*!
 @method    initWithUDID:connection:
 @abstract  An instance of CAMSimpleAutomation object for a particular connection object.
 @return    CAMSimpleAutomation object.
 */
- (id) initWithUDID:(NSString*)udid connection:(CAMConnection*)aConnection;

/*!
 @method    initWithUDID:connection:asRoot:
 @abstract  An instance of CAMSimpleAutomation object for a particular connection object.
 @param     asRoot whether or not simply should be running as root on the target device
 @return    CAMSimpleAutomation object.
 */
- (id) initWithUDID:(NSString*)udid connection:(CAMConnection*)aConnection asRoot:(BOOL)asRoot;

/*!
 @method    allocClass:
 @abstract  Allocate class remotely with specified class. Similar to calling "alloc" locally.
 @return    The proxy for the instance of remote object.
 */
- (id) allocClass:(NSString*)className;

/*!
 @method    remoteClass:
 @abstract  Remote class object of the specified class name.
 @return    The proxy for the remote class object for calling class methods.
 */
- (id) remoteClass:(NSString*)className;

/*!
 @method    loadBundle:
 @abstract  Load remote bundle of specified path at run time.
 @return    YES indicating success, and NO value indicating failure.
 */
- (BOOL) loadBundle:(NSString*)bundlePath;

/*!
 @method    startPingInvoke:
 @abstract  Start polling device for callbacks. Used by CAMEmbeddedDevice object. Client don't need it.
 */
- (void) startPingInvoke;

/*!
 @method    stopPingInvoke:
 @abstract  Stop polling device for callbacks. Used by CAMEmbeddedDevice object. Client don't need it.
 */
- (void) stopPingInvoke;

/*!
 @method    remoteClasses
 @abstract  Returns an object that has the class definitions of all remotely loaded bundles.
 */
- (id) remoteClasses;
@end