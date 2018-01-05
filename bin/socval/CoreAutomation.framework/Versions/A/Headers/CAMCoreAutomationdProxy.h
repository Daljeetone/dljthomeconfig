//
//  CAMCoreAutomationdProxy.h
//  CoreAutomation
//
//  Created by Christopher Whitney on 10/28/11.
//  Copyright (c) 2011 Apple Inc. All rights reserved.
//
#import <Availability.h> // So we get TARGET_OS_IPHONE
#import <Foundation/Foundation.h>
#import "CAMCoreAutomationdProtocols.h"

@class CAMConnection;

// Abstract class
@interface CAMCoreAutomationdProxy : NSProxy {
	CAMConnection * _connection;
	NSString* _shortName;
	BOOL _isUserRoot;
}

/*!
 @brief Returns a proxy to a certain coreautomationd "technology".
 @param connection	A connection instance that provides a coreautomationd connection.
 */
+ (instancetype)proxyWithConnection:(CAMConnection *)connection;

/*!
 @brief Toggle function call statistic logging.
 @param generateStatisticsLog A boolean value indicating whether the log shoulde be generated.
 */
+ (void)logStatistics:(BOOL)generateStatisticsLog;

/*!
 @brief Returns a proxy to a certain coreautomationd "technology".
 @param aConnection	A CAMAMDConnection to a device instance that will accept the connection.
 */
- (instancetype)initWithConnection:(CAMConnection *)aConnection;

/*!
 @brief Returns a proxy to a certain coreautomationd "technology".
 @param connection	A connection instance that provides a coreautomationd connection.
 @param shortName	A short name indicating the specific technology.
 */
- (instancetype)initWithConnection:(CAMConnection *)connection shortName:(NSString *)shortName;

/*!
 @brief Set this proxy to use the device's root user instance of coreautomationd
 @return this object, so that this method may be used as part of a [[[device technology] asRoot] someMethod] chain.
 */
- (instancetype)asRoot;

/*!
 @brief Set this proxy to use the device's mobile user instance of coreautomationd
 @return this object, so that this method may be used as part of a [[[device technology] asMobile] someMethod] chain.
 @discussion The mobile connection is the default, so this method should only be needed when given proxy instance needs to flip between root and mobile.
 */
- (instancetype)asMobile;

/*!
 @brief The underlying connection object for direct message forward to the device.
 */
@property (nonatomic, retain, readonly) CAMConnection *coreautomationdConnection;

@end


#pragma mark -
#pragma mark Proxy Subclasses
@interface CAMAWDLProxy : CAMCoreAutomationdProxy <CAMAWDL>
@end

@interface CAMAccessibilityProxy : CAMCoreAutomationdProxy <CAMAccessibility>
@end

@interface CAMAddressBookProxy : CAMCoreAutomationdProxy <CAMAddressBook>
@end

@interface CAMArchiveProxy : CAMCoreAutomationdProxy <CAMArchive>
@end

@interface CAMC26Proxy : CAMCoreAutomationdProxy <CAMC26>
@end

@interface CAMCapabilitiesProxy : CAMCoreAutomationdProxy <CAMCapabilities>
@end

@interface CAMCarPlayProxy : CAMCoreAutomationdProxy <CAMCarPlay>
@end

@interface CAMCoreLocationProxy : CAMCoreAutomationdProxy <CAMCoreLocation>
@end

@interface CAMCoreMotionProxy : CAMCoreAutomationdProxy <CAMCoreMotion>
@end

@interface CAMCoreRoutineProxy : CAMCoreAutomationdProxy <CAMCoreRoutine>
@end

@interface CAMCoreTelephonyProxy : CAMCoreAutomationdProxy <CAMCoreTelephony>
@end

@interface CAMDeviceProxy : CAMCoreAutomationdProxy <CAMDevice>
@end

@interface CAMExternalAccessoryProxy : CAMCoreAutomationdProxy <CAMExternalAccessory>
@end

@interface CAMFaceTimeProxy : CAMCoreAutomationdProxy <CAMFaceTime>
@end

@interface CAMGameControllerProxy : CAMCoreAutomationdProxy <CAMGameController>
@end

@interface CAMGraphicsUtilitiesProxy : CAMCoreAutomationdProxy <CAMGraphicsUtilities>
@end

@interface CAMHIDProxy : CAMCoreAutomationdProxy <CAMHID>
@end

@interface CAMHomeKitProxy : CAMCoreAutomationdProxy <CAMHomeKit>
@end

@interface CAMiCloudProxy : CAMCoreAutomationdProxy <CAMiCloud>
@end

@interface CAMPassbookProxy : CAMCoreAutomationdProxy <CAMPassbook>
@end

@interface CAMIdentityServicesProxy : CAMCoreAutomationdProxy <CAMIdentityServices>
@end

@interface CAMImageTechProxy : CAMCoreAutomationdProxy <CAMImageTech>
@end

@interface CAMiMessageProxy : CAMCoreAutomationdProxy <CAMiMessage>
@end

@interface CAMContactsProxy : CAMCoreAutomationdProxy <CAMContacts>
@end

@interface CAMLocaleUtilitiesProxy : CAMCoreAutomationdProxy <CAMLocaleUtilities>
@end

@interface CAMMediaPlayerProxy : CAMCoreAutomationdProxy <CAMMediaPlayer>
@end

@interface CAMMediaLibraryProxy : CAMCoreAutomationdProxy <CAMMediaLibrary>
@end

@interface CAMMediaRemoteProxy : CAMCoreAutomationdProxy <CAMMediaRemote>
@end

@interface CAMMesaProxy : CAMCoreAutomationdProxy <CAMMesa>
@end

@interface CAMMobileSafariProxy : CAMCoreAutomationdProxy <CAMMobileSafari>
@end

@interface CAMMobileBluetoothProxy : CAMCoreAutomationdProxy <CAMMobileBluetooth>
@end

@interface CAMMultipeerConnectivityProxy : CAMCoreAutomationdProxy <CAMMultipeerConnectivity>
@end

@interface CAMSharingProxy : CAMCoreAutomationdProxy <CAMSharing>
@end

@interface CAMNearFieldProxy : CAMCoreAutomationdProxy <CAMNearField>
@end

@interface CAMNetworkingProxy : CAMCoreAutomationdProxy <CAMNetworking>
@end

@interface CAMSettingsProxy : CAMCoreAutomationdProxy <CAMSettings>
@end

@interface CAMShellProxy : CAMCoreAutomationdProxy <CAMShell>
@end

@interface CAMSpringBoardProxy : CAMCoreAutomationdProxy <CAMSpringBoard>
@end

@interface CAMStoreServicesProxy : CAMCoreAutomationdProxy <CAMStoreServices>
@end

@interface CAMAssistantServicesProxy : CAMCoreAutomationdProxy <CAMAssistantServices>
@end

@interface CAMSystemProxy : CAMCoreAutomationdProxy <CAMSystem>
@end

@interface CAMTelephonyUtilitiesProxy : CAMCoreAutomationdProxy <CAMTelephonyUtilities>
@end

@interface CAMVPNProxy : CAMCoreAutomationdProxy <CAMVPN>
@end

@interface CAMWiFiProxy : CAMCoreAutomationdProxy <CAMWiFi>
@end

@interface CAMObliterationProxy : CAMCoreAutomationdProxy <CAMObliteration>
@end

@interface CAMWirelessProximityProxy : CAMCoreAutomationdProxy <CAMWirelessProximity>
@end

@interface CAMAsyncProxy : CAMCoreAutomationdProxy <CAMAsync>
@end

@interface CAMSimpleAutomationProxy : CAMCoreAutomationdProxy <CAMSimpleAutomationProtocol>
@end


