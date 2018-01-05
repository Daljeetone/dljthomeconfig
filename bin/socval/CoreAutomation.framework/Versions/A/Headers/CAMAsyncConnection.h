//
//  CAMAsyncConnection.h
//  CoreAutomation
//
//  Created by Chen Huang on 10/14/15.
//
//

#import <Foundation/Foundation.h>
#import "CAMConnection.h"
#import "CAMAMDPersistentConnection.h"
#import "CAMDarwinTarget.h"

@interface CAMAsyncConnection : CAMConnection<CAMAMDPersistentDelegate>

- (instancetype)initWithDeviceRef:(AMDeviceRef)aDeviceRef;

@property (nonatomic, readonly, retain) CAMAMDPersistentConnection *rootConnection;
@property (nonatomic, readonly, retain) CAMAMDPersistentConnection *mobileConnection;
@property (weak, readwrite) CAMDarwinTarget *target;

/**
 *  Enable Async transmission protocol on remotedevice.
 */
- (void)enableAsyncMode;

- (void)disableAsyncMode;   // Currently No OP.

@end
