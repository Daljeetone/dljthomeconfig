//
//  CAMBusManUSBControllerPrivate.h
//  CoreAutomation
//
//  Created by Tarek Khouzam on 1/13/12.
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

@interface CAMBusManUSBController (BusmanPrivate)

- (id)initWithAddress:(NSString *)address error:(NSError **)error; // Should only be called by CAMCambrionixManager

@end
