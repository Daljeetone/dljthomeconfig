//
//  CAMDarwinTarget.h
//  CoreAutomation
//
//  Created by Chen Huang on 6/23/14.
//
//

#import "CAMTarget.h"
#import "CAMCommunicating.h"
#import "CAMAsyncDelegateProtocol.h"


@class CAMConnectionContainer;

@protocol CAMDarwinInterface <NSObject>

/*!
 @property username
 @discussion This property is the username for the OS X target.
 */
@property (copy) NSString *username;

/*!
 @property password
 @discussion This property is the password for the OS X target.
 */
@property (copy) NSString *password;

/*!
 @property targetAddress
 @discussion The is the target's address.  IP address for OS X.
 */
@property (copy) NSString *targetAddress;

/*!
 @property connected
 @discussion Property tells whether this target is connected to automation.
 */
@property (assign) BOOL connected;

/*! @brief Operating system version information. */
@property (retain, readonly) CAMXBSBuild *build;

/*!
 @property buildVersion
 @discussion Build version for OS X target.
 */
@property (copy,   readonly) NSString    *buildVersion;

/*!
 @property productType
 @discussion Product type of the target.
 */
@property (copy,   readonly) NSString    *productType;

/*!
 @property hardwareModel
 @discussion Hardware model for the target.
 */
@property (copy,   readonly) NSString    *hardwareModel;

/*!
 @property hardwareModelPrefix
 @discussion .
 */
@property (copy,   readonly) NSString    *hardwareModelPrefix;

/*!
 @property bootArgs
 @discussion Boot args set for the target.
 */
@property (copy)             NSString    *bootArgs;

/*!
 @property hostname
 @discussion The host name for the target..
 */
@property (copy,   readonly) NSString    *hostname;

/*!
 @property versionInformation
 @discussion CoreAutomation Host Version
 */
@property (copy,   readonly) NSArray    *versionInformation;

@property (retain)   CAMConnectionContainer *connections;

- (BOOL)isBooted;
- (void)reboot:(BOOL)waitForBoot;

#pragma mark - Async
@property(assign, readwrite) id<CAMAsyncDelegateProtocol> asyncDelegate;

@end

@interface CAMDarwinTarget : CAMTarget <CAMDarwinInterface, CAMCommunicating>
{
    id <CAMFileTransferringDelegate> delegate;
    NSString *username;
    NSString *password;
    NSString *targetAddress;
    BOOL connected;
    CAMConnectionContainer *_connections;
}

@property (NS_NONATOMIC_IOSONLY, readonly) BOOL checkout;
- (void)checkin;

@end
