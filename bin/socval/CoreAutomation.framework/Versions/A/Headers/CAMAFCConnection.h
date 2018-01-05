//
//  CAMAFCConnection.h
//  CoreAutomation
//
//  Created by Matt Massicotte on 4/6/10.
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "CAMCommunicating.h"

@class CAMMobileDeviceBootedState;
@class CAMAFCFileManager;
@class CAMAMDConnection;

/*!
 @interface CAMAFCConnection
 @discussion Notes on Internal vs. Customer builds

 On Internal builds we're allowed to use the unrestricted AFC service, meaning
 that we can send and receive files anywhere on the device's filesystem

 On Customer builds, we have the public AFC service. All file transfers to and
 from the device are rooted at /private/var/mobile/Media/ rather than /

 This is generally transparent to the user. If you are on a Customer build and
 send a.txt to /files/, it will actually go to /private/var/mobile/Media/files/

 If you then attempt to retrieve /files/a.txt, it will retrieve it from the
 restricted path at /private/var/mobile/Media/files/a.txt
 */
@interface CAMAFCConnection : NSObject <CAMFileTransferring>

/*!
 @property delegate
 @discussion Apply delegate to get notifications.
 */
@property(unsafe_unretained, nonatomic) id<CAMFileTransferringDelegate> delegate;

/*!
 @property rootFilePath
 @discussion The path at which all transfers are rooted on the device's file system.
 As mentioned above, this will generally be / for internal build variants and
 /private/var/mobile/Media for non-internal.
 */
@property (readonly, strong) NSString *rootFilePath;

/*!
 @method initWithAMDConnection
 @discussion Initialize with an CAMAMDConnection.
 @param aConnection CAMAMDConnection to the device.
 */
- (id)initWithAMDConnection:(CAMAMDConnection *)aConnection;

/*!
 @method isValid
 @discussion Returns whether the AFC connection is still valid.
 @return YES if the connection is still valid. NO otherwise
 */
- (BOOL)isValid;

/*!
 @method disconnect
 @discussion Disconnects AFC service.
 */
- (void)disconnect;

@end
