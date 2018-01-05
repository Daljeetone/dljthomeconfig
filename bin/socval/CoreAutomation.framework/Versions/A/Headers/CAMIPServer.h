//
//  CAMIPServer.h
//  CoreAutomation
//
//  Created by Matt Massicotte on 10/22/10.
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>


/*!
 @protocol CAMIPServer
 */
@protocol CAMIPServer <NSObject>

/*!
 @property v4Port
 */
@property (assign) uint16_t v4Port;

/*!
 @property v6Port
 */
@property (assign) uint16_t v6Port;

/*!
 @method start
 */
- (BOOL)start:(NSError**)error;

/*!
 @method stop
 */
- (BOOL)stop;

@end
