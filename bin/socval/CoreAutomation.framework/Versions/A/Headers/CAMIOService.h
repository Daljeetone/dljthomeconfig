//
//  CAMIOService.h
//  CoreAutomation
//
//  Created by Matt Massicotte on 3/8/10.
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <IOKit/IOKitLib.h>

/*!
 @interface CAMIOService
 @discussion CAM IO service.  This service is the basis for IO methods.
 */
@interface CAMIOService : NSObject {
    io_service_t ioService;
}

/*!
 @method initWithService
 @discussion Initialize the IO service.
 */
- (instancetype)initWithService:(io_service_t)service;

/*!
 @property ioService
 @discussion IO service we used to initialize.
 */
@property(assign, readonly) io_service_t ioService;

/*!
 @method enumerateServicesInIterator
 @discussion Enumerates available IO services.
 @param iterator
	Used to enumerate services.
 @param block
	Block to handle IO services.
 */
+ (void)enumerateServicesInIterator:(io_iterator_t)iterator usingBlock:(void (^)(id service, NSUInteger idx))block;

/*!
 @method enumerateDevicesMatching
 @discussion Enumerate devices matching NSDictionary.
 @param matchingDict
	NSDictionary used to match.
 @param block
	Block to handle IO services.
 */
+ (void)enumerateDevicesMatching:(NSDictionary *)matchingDict usingBlock:(void (^)(id service, NSUInteger idx))block;

/*!
 @method enumerateAllDevicesUsingBlock
 @discussion Enumerates all IO devices.
 @param block
	Block to handle IO services.
 */
+ (void)enumerateAllDevicesUsingBlock:(void (^)(id service, NSUInteger idx))block;

/*!
 @method drainIterator
 @discussion Drains the iterator used.
 @param iterator
	Used to enumerate services.
 */
+ (void)drainIterator:(io_iterator_t)iterator;

/*!
 @method devicesMatching
 @discussion Devices matching NSDictionary.
 @param matchingDict
	NSDictionary used to match IO services.
 @result
	NSArray of devices.
 */
+ (NSArray *)devicesMatching:(NSDictionary *)matchingDict;

/*!
 @method allDevicesMatchingDictionary
 @discussion Gets all devices matching NSDictionary
 @result
	NSDictionary of devices.
 */
+ (NSDictionary *)allDevicesMatchingDictionary;

@end
