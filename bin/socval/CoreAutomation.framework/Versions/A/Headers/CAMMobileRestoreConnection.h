//
//  CAMMobileRestoreConnection.h
//  CoreAutomation
//
//  Created by Shannon Ma on 7/21/11.
//  Copyright (c) 2011 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CAMMobileDeviceState.h"

extern NSCondition *deviceCatalogLock;

/*!
 @interface CAMMobileRestoreConnection
 @discussion This service provides installs for a PR2 doc.
 */
@interface CAMMobileRestoreConnection : NSObject
{
    
}

/*! 
 @method sharedConnection
 */
+ (id)sharedConnection;


/*! 
 @method lastError
 */
+ (NSError*)lastError;


/*! 
 @method dictionaryForIPSW
 @discussion Creates a dictionary for an IPSW.
 @param path
	Path to IPSW
 @param camOptions
	Options available for restore.
 @result
	Dictionary created.
 */
+ (NSDictionary *)dictionaryForIPSW:(NSString *)path camOptions:(NSDictionary *)camOptions;

/*! 
 @method dictionaryForPR2
 @discussion Creates a dictionary for a PR2 doc.
 @param options
	URL to the PR2 document created from PurpleRestore.
 @param camOptions
	Options available for restore.
 @result
	Dictionary created.
 */
+ (NSDictionary *)dictionaryForPR2:(NSDictionary*)options camOptions:(NSDictionary *)camOptions;

/*! 
 @method restoreDevice
 @discussion Restores device.
 @param deviceRef
	AMRestorableDeviceRef of the device.
 @param options
	Available options for the restore.
 @param progressBlock
	Block to handle progress updates.
 @result
	YES if successful restore, NO if unsuccessful.
 */
- (BOOL)restoreDevice:(AMRestorableDeviceRef)deviceRef options:(NSDictionary *)options usingProgressBlock:(void (^)(NSDictionary *progressInfo))progressBlock;


/*! 
 @method setLogURL
 @discussion sets the mobile restore file api to save a log type to a url
 @param deviceRef
	AMRestorableDeviceRef of the device.
 @param url
	File Location
 @param logType
	Type of Log
	#define kAMRestorableDeviceLogTypeSerial CFSTR("SerialLogType")
    #define kAMRestorableDeviceLogTypeHost CFSTR("HostLogType")
    #define kAMRestorableDeviceLogTypeDevice CFSTR("DeviceLogType")
 @result
	YES if successful restore, NO if unsuccessful.
 */
    - (BOOL)setLogURL:(AMRestorableDeviceRef)deviceRef withUrl:(NSURL*)url andType:(NSString*)logType;

@end