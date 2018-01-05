//
//  CoreAutomationErrors.h
//  CoreAutomation
//
//  Created by Chris Whitney on 4/23/10.
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

extern NSString* const CAMMobileDeviceErrorDomain;

extern NSString* const CAMErrorDomain;

/*!
 @enum 
 @discussion File IO errors
 */
enum {
	// File I/O errors
	CAMHostFileCreateError = 1,

	CAMCoreAutomationdNoConnectionError = 10
};

extern NSString* const CAMResourceManagerErrorDomain;

/*!
 @enum 
 @discussion Checkout errors.
 */
enum {
    // Checkout errors.
    CAMResourceManagerInsufficientError = 1,
    CAMResourceManagerResourceNoMatchError = 2,
    CAMResourceManagerResourceInUseError = 3,
    CAMResourceManagerClassLockError = 4
};
