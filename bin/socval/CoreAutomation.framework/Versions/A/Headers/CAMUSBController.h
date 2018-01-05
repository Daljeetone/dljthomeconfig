//
//  CAMUSBController.h
//  CoreAutomation
//
//  Created by Matt Massicotte on 8/9/10.
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>

/*!
 @interface CAMUSBController
 @discussion CAM USB controller.  Used to control a generic USB port.
 */
@interface CAMUSBController : NSObject {
}

/*!
 @method allControllers
 @discussion Get all controlers.
 */
+ (id)allControllers;

/*!
 @method connectAll
 @discussion Connect to all USB ports.
 */
+ (void)connectAll;

/*!
 @method disconnectAll
 @discussion Disconnect from all USB ports.
 */
+ (void)disconnectAll;

/*!
 @method connect
 @discussion Connect to this USB controller instance.
 */
- (void)connect;

/*!
 @method disconnect
 @discussion Disconnect from this USB controller instance.
 */
- (void)disconnect;

@end
