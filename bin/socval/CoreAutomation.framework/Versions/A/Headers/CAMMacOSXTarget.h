//
//  CAMMacOSXTarget.h
//  CoreAutomation
//
//  Created by Matt Massicotte on 3/3/10.
//  Copyright 2010 Apple, Inc. All rights reserved.
//
/*!
 CAMMacOSXTarget is a generic representation of remote computers (whether iOS or Mac OS) that are capable of responding 
 to some fundamental operations such as running shell commands, copying files, and rebooting.
*/

#import <Cocoa/Cocoa.h>
#import "CAMDarwinTarget.h"
#import "CAMCommunicating.h"
#import "CAMDeviceProxies.h"

@class CAMXBSBuild;

/*!
 @interface CAMMacOSXTarget
 @discussion OS X target device.
 */
@interface CAMMacOSXTarget : CAMDarwinTarget <CAMCommunicating, CAMDeviceProxies, CAMDarwinInterface>
{
    NSMutableDictionary* urlMountPoints;

    void (^stdoutHandler)(NSString *);
    void (^stderrHandler)(NSString *);
    
    @private
    dispatch_queue_t runCommandQueue;
    NSMutableDictionary *proxyDictionary;
    int shutdownSignal;
}

+ (NSArray *)localTargets;

+ (id)localMachine;

/*!
 @method: remoteMachine:
 @param ip      The ip address of the remote machine. The target marchine to connect to must be pingable.
                Local SSL certificate should be able to sign & encrypt/descrypt. It must also has an identitiy.
 @return        CAMMacOSXTarget to represent remote machine.
 @discussion    Created CAMMacOSXTarget doesn't initiate connection to remote machine. Connection will be initiated when first API call is made.
 */
+ (id)remoteMachine:(NSString *)ip;

/*!
 @method setStdoutHandler
 @discussion Set a STDOUT handler.
 */
- (void)setStdoutHandler:(void (^)(NSString *))block;

/*!
 @method setStderrHandler
 @discussion Set a STDERR handler.
 */
- (void)setStderrHandler:(void (^)(NSString *))block;


/*! @brief Connect to the target */
- (void)connect;
/*! @brief Disconnect from the target */
- (void)disconnect;

// basic functions
/*!
 @method reboot
 @discussion Reboots the target.
 @param waitForBoot
	Tell whether to wait until reboot is complete.
 */
- (void)reboot:(BOOL)waitForBoot;
@property (nonatomic, copy) NSDate *systemDate;


/*!
 @method mountPath
 @discussion Mounts device to the specified path.
 @param path
	Path to the mount point.
 @param error
	Error code.
 */
- (void)mountPath:(NSString *)path error:(NSError *)error;

/*!
 @method mountURL
 @discussion Mounts device to the specified path.
 @param url
	URL to where the device is mounted.
 @param error
	Error in mount URL.
 */
- (void)mountURL:(NSURL *)url error:(NSError *)error;

/*!
 @method unmountPath
 @discussion Unmounts from path.
 @param path
	Path to unmount.
 @param error
	Error code
 */
- (void)unmountPath:(NSString *)path error:(NSError *)error;

/*!
 @method unmountURL
 @discussion Unmounts from path.
 @param url
	URL to unmount.
 @param error
	Error code
 */
- (void)unmountURL:(NSURL *)url error:(NSError *)error;

- (BOOL)useAsyncConnection;

@end
