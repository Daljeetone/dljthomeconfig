//
//  CAMResourceManager.h
//  CoreAutomation
//
//  Created by Shannon Ma on 8/15/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

extern NSString * const kCAMDeviceResourceKey;
extern NSString * const kCAMBluetoothDeviceResourceKey;
extern NSString * const kCAMResourceTypeKey;
extern NSString * const kCAMResourceManagerResourcePropertiesUpdatedNotification;
extern NSString * const kCAMResourcePropertiesLastUpdatedKey;

typedef BOOL (^CheckoutPredicateBlock)(NSArray *devices, NSDictionary *bindings);

/*!
 @interface CAMResourceManager
 @discussion CAMResourceManager allows you to lock objects across processes. Objects should override NSObject.hash as this is used for object identity.
 */
@interface CAMResourceManager : NSObject
{
    NSMutableDictionary *objectLocks;
    NSMutableDictionary *objectClassLocks;
}

/*!
 @method sharedManager
 @discussion Uses a single shared manager to handle resources.
 */
+ (id)sharedManager;

/*!
 @method checkout
 @discussion Check out a particular resource.  This will create a file-system lock on the resource.
 @param predicates
	Use predicates to choose a resource to check out.
 @param objects
	Determine specifically which resources to check out.
 @result
	Returns an array of checked-out resources.
 */
- (NSArray *)checkout:(NSArray *)predicates resources:(NSArray *)objects;

/*!
 @method checkin
 @discussion Check the resources back in.
 @param objects
	The resource to check back in.
 */
- (void)checkin:(NSArray *)objects;

/*!
 @method checkout
 @discussion Check out a particular resource.  This will create a file-system lock on the resource.
 @param object
	Resource to check out.
 @result
	YES if you successfully checked out the resource.  NO if not.
 */
- (BOOL)checkoutResource:(NSObject *)object;

/*!
 @method checkout
 @discussion Check-in one particular resource.
 @param object
	Single resource to check in.
 */
- (void)checkinResource:(NSObject *)object;

/*!
 @method checkout:usingBlockPredicate:withDevices
 @param size The number of devices to checkout
 @param blockpredicate NSPredicate.
 @param devices The devices to checkout from.
 @discussion This will attempt to checkout "size" devices from "devices", by evaluating device combinations using "blockpredicate". The reason to use term "UsingBlockPredicate" is to differentiate the predicate functionalities with method checkout:resources:
    in method checkout:resources, predicates is a NSArray of predicate, each predicate evaluates each device. There is no way to specify the relationships between devices.
    in method checkout:usingBlockPredicate:withDevices, predicate is no longer an NSArray. It could be a NSPredicate from a "block" or from a NSPredicate string. The "block" can be used to specify the relationships between devices.
 */
- (NSArray *)checkout:(NSNumber *)size usingBlockPredicate:(NSPredicate *)blockpredicate withDevices:(NSArray *)devices;
@end
