//  Original:
//  CAMBusManUSBController.h
//  CoreAutomation
//
//  Created by Matt Massicotte on 9/8/10.
//  Copyright 2010 Apple, Inc. All rights reserved.
//

//  Updated: Most of the code went into
//  CAMCambrionixUSBController.h
//  CoreAutomation
//
//  Created by Tarek Khouzam on 1/13/12.
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import "CAMCambrionixUSBController.h"

// Busman specific methods

@interface CAMBusManUSBController : CAMCambrionixUSBController

- (NSString *)hubReset;
- (NSString *)ledTest;
- (NSString *)piezoTest;

@end
