//
//  CAMBusBoyUSBController.h
//  CoreAutomation
//
//  Created by Matt Massicotte on 8/9/10.
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import "CAMUSBController.h"
#import "CAMBusBoyDevice.h"

@interface CAMBusBoyUSBController : CAMUSBController {
    CAMBusBoyDevice *busBoy;
}

- (id)initWithLocationID:(uint32_t)locationID;

@property(assign, readonly) uint32_t locationID;

@end
