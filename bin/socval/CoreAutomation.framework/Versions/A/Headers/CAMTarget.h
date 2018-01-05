//
//  CAMTarget.h
//  CoreAutomation
//
//  Created by Matt Massicotte on 3/3/10.
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class CAMLogger;
@class CAMXBSBuild;

/*!
 @interface CAMTarget
 @discussion A CAM target is designed to be
 */
@interface CAMTarget : NSObject
{
    @private
    NSHost*    host;
    CAMLogger* logger;
}

/*!
 @property host
 @discussion This is the host associated with the target.
 */
@property (strong) NSHost    *host;

/*!
 @property logger
 @discussion This is the logger associated with the target.
 */
@property (strong, readonly) CAMLogger *logger;


@end
