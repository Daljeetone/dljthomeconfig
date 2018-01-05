//
//  CAMDeviceProxies
//  CoreAutomation
//
//  Created by Chen Huang on 5/16/14.
//
//
#import <Availability.h>
#ifndef CoreAutomation_CAMDeviceProxies_h
#define CoreAutomation_CAMDeviceProxies_h

#import <Foundation/Foundation.h>
#import "CAMCoreAutomationdProxy.h"

@class CAMSimpleAutomation;

@protocol CAMDeviceProxies

- (CAMAccessibilityProxy *)accessibility;
- (CAMAddressBookProxy*)addressBook;
- (CAMArchiveProxy *)archive;
- (CAMAssistantServicesProxy*)assistant;
- (CAMAWDLProxy*)AWDL;
- (CAMC26Proxy *)c26;
- (CAMCapabilitiesProxy*)capabilities;
- (CAMCarPlayProxy*)carPlay;
- (CAMCoreLocationProxy*)coreLocation;
- (CAMCoreMotionProxy*)coreMotion;
- (CAMCoreRoutineProxy*)coreRoutine;
- (CAMCoreTelephonyProxy*)coreTelephony;
- (CAMDeviceProxy*)device;
- (CAMExternalAccessoryProxy*)externalAccessory;
- (CAMFaceTimeProxy*)faceTime;
- (CAMGameControllerProxy*)gameController;
- (CAMGraphicsUtilitiesProxy*)graphicsUtilities;
- (CAMHIDProxy*)HID;
- (CAMiCloudProxy*)iCloud;
- (CAMLocaleUtilitiesProxy*)localeUtilities;
- (CAMMediaLibraryProxy*)mediaLibrary;
- (CAMMediaPlayerProxy*)mediaPlayer;
- (CAMMediaRemoteProxy*)mediaRemote;
- (CAMMesaProxy*)mesa;
- (CAMNearFieldProxy*)nfc;
- (CAMMobileBluetoothProxy*)bluetooth;
- (CAMMobileSafariProxy*)safari;
- (CAMMultipeerConnectivityProxy*)mc;
- (CAMSharingProxy*)sharing;
- (CAMNetworkingProxy*)networking;
- (CAMObliterationProxy*)obliteration;
- (CAMSettingsProxy*)settings;
- (CAMShellProxy*)os;
- (CAMSpringBoardProxy*)springboard;
- (CAMStoreServicesProxy*)store;
- (CAMSystemProxy*)system;
- (CAMTelephonyUtilitiesProxy*)tu;
- (CAMVPNProxy*)VPN;
- (CAMWiFiProxy*)WiFi;
- (CAMWirelessProximityProxy*)wp;
- (CAMAsyncProxy*)async;
- (CAMiMessageProxy*)iMessage;
- (CAMSimpleAutomation*)simply;
- (CAMSimpleAutomation*)simplyAsRoot;
- (CAMContactsProxy*)contacts;
- (CAMImageTechProxy*)imageTech;
@end
#endif
