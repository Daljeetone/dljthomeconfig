//
//  CAMXBSEventManagerClient.h
//  CoreAutomation
//
//  Created by Matt Massicotte on 6/13/10.
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>

extern NSString * const CAMBuildEventNotification;
extern NSString * const CAMBuildEventDetailsKey;
extern NSString * const CAMBuildEventBuildKey;

@class CAMSOAPRPCServer;
@class CAMXBSBuild;

/*!
 @interface CAMXBSEventManagerClient
 @discussion CAMXBSEventManagerClient handles waiting for notifications from XBS builds.
 */
@interface CAMXBSEventManagerClient : NSObject
{
    CAMSOAPRPCServer* soapServer;
    NSCondition*      nextEventCondition;
    NSDictionary*     lastEvent;
}

+ (instancetype)sharedClient;

/*!
 @method start
 @discussion Start listening for XBS build notifications.
 */
- (void)start;

/*!
 @method stop
 @discussion Stop listening for XBS build notifications.
 */
- (void)stop;

/*!
 @method waitForNextEventInTrains
 @discussion Waits for the next event given the train.
 @param trains
	Set of trains to listen for.
 @result
	NSDictionary with train information.
 */
- (NSDictionary *)waitForNextEventInTrains:(NSSet *)trains;

/*!
 @method waitForNextEventInTrains
 @discussion Waits for the next event given the train.
 @param trains
	Set of trains to listen for.
 @param images
	Set of images for the given trains.
 @result
	NSDictionary with train information.
 */
- (NSDictionary *)waitForNextEventInTrains:(NSSet *)trains containingImages:(NSSet *)images;

/*!
 @method waitForNextBuildInTrains
 @discussion Waits for the next build given the train.
 @param trains
	Set of trains to listen for.
 @param images
	Set of images for the given trains.
 @result
	CAMXBSBuild object containing build information.
 */
+ (CAMXBSBuild *)waitForNextBuildInTrains:(NSSet *)trains containingImages:(NSSet *)images;

/*!
 @method buildForEventDetails
 @discussion Gets a build for specific event information.
 @param details
	Specify the criteria for the build information.
 @result
	CAMXBSBuild object containing build information.
 */
+ (CAMXBSBuild *)buildForEventDetails:(NSDictionary *)details;

@end

