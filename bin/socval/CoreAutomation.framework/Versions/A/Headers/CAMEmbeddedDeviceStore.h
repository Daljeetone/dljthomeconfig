//
//  CAMEmbeddedDeviceStore.h
//  CoreAutomation
//
//  Created by Dan Stenmark on 3/10/12.
//  Copyright (c) 2012 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CAMEmbeddedDevice.h"

// These two notifications are guaranteed to be executed on the main thread.
extern NSString * const CAMEmbeddedDeviceAttachedNotification;
extern NSString * const CAMEmbeddedDeviceDetachedNotification;

// The userInfo key for CAMEmbeddedDeviceAttachedNotification and CAMEmbeddedDeviceDetachedNotification
// which fetches the CAMEmbeddedDevice that changed.
extern NSString * const CAMEmbeddedDeviceStateChangedKey;

/*!
 @interface CAMEmbeddedDeviceStore
 @discussion CAM Embedded Device Store.  This is used to maintain a persistent updating set of CAMEmbeddedDevices.
 */
@interface CAMEmbeddedDeviceStore : NSObject {
    /*!
     The set of currently attached devices.  This object is bindings-compatible.
     */
    NSSet *devices;
}

/*!
 @name Getting the Embedded Device Store
 @{
 */

/*! 
 @brief Returns the process's default embedded device store.
 @return The current process's default embedded device store.
 
 */
+ (CAMEmbeddedDeviceStore *)defaultStore;

/*!
 @}
 */

@property (readonly) NSSet<CAMEmbeddedDevice *> *devices;

@end
