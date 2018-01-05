//
//  CAMSerialConnection.h
//  CoreAutomation
//
//  Created by Matt Massicotte on 4/2/10.
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "CAMTerminalConnection.h"

@class CAMSerialPort;

/*! 
 @interface CAMSerialConnection
 */
@interface CAMSerialConnection : CAMTerminalConnection
{
    @private
    CAMSerialPort* serialPort;
    
    BOOL           connected;
}


/*! 
 @method initWithBSDPath
 @discussion Initializes service with path.
 @param path
	Path on host to log.  *NOTE* I don't think this works at the moment.
 */
- (id)initWithBSDPath:(NSString *)path;

@end
