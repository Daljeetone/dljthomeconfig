//
//  CAMDevice.h
//  CoreAutomation
//
//  Created by Wayne Finlay on 10/24/2014.
//  Copyright (c) 2014 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CAMReturnValues.h"

#define kCAMDeviceShortName Device

@protocol CAMDevice
@optional

/*!
 @method     filterNSDataLogging:
 @abstract   Enable/disable NSData filtering in the coreautomationd log
 @discussion This enables/disables the filtering of NSData from the log on the device. This method is a dummy method since the call is captured in CAMDEmbeddedDevice 
 @return     Void
 */
- (CAMReturnVoid*)filterNSDataLogging:(NSNumber *)enable;

/*!
 @method     flushCoverageData:
 @abstract   Trigger a __gcov_flush()
 @discussion Code Coverage data is only flushed on process exit. This enables a forced flush.
 @return     Returns true if code coverage is enabled.
 */
- (CAMReturnBool*)flushCoverageData;

/*!
 @method     notifyFlushCoverageData:
 @abstract   Trigger a __gcov_flush() in subscribed processes
 @discussion Code Coverage data is only flushed on process exit. This enables a forced flush.
 @return     Returns true for no reason.
*/
- (CAMReturnBool*)notifyFlushCoverageData;
@end

