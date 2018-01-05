//
//  CAMMultiTarget.h
//  CoreAutomation
//
//  Created by Matt Massicotte on 3/13/10.
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class CAMTarget;

/*!
 @interface CAMMultiTarget
 @discussion CAM Multi-target.  This is used to control execution on multiple devices.
 */
@interface CAMMultiTarget : NSObject
{
    NSMutableArray*  targets;
    dispatch_group_t executionGroup;
}

/*!
 @property targets
 @discussion NSArray of targets.
 */
@property (nonatomic, strong) NSArray* targets;

/*!
 @method execute
 @discussion Execute method for multiple targets.
 @param block
	Block to perform the command for each target.
 */
- (void)execute:(void (^)(CAMTarget* target, NSUInteger idx))block;

/*!
 @method executeSerially
 @discussion Execute method that serially runs on each target.
 @param block
	Block to perform for each target.
 */
- (void)executeSerially:(void (^)(CAMTarget* target, NSUInteger idx))block;

@end
