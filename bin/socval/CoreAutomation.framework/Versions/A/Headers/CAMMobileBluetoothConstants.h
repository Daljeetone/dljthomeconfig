//
//  CAMMobileBluetoothConstants.h
//  coreautomationd
//
//  Created by Chen Huang on 1/27/15.
//
//

#ifndef coreautomationd_CAMMobileBluetoothConstants_h
#define coreautomationd_CAMMobileBluetoothConstants_h

#import <Foundation/Foundation.h>

// Bluetooth StateReport keys
FOUNDATION_EXPORT NSString *const kStateReportPairedDevicesKey;
FOUNDATION_EXPORT NSString *const kStateReportConnectedDevicesKey;
FOUNDATION_EXPORT NSString *const kStateReportConnectingDevicesKey;
FOUNDATION_EXPORT NSString *const kStateReportPinKey;
FOUNDATION_EXPORT NSString *const kStateReportPairedStatusKey;
FOUNDATION_EXPORT NSString *const kStateReportConnectedKey;
FOUNDATION_EXPORT NSString *const kStateReportDiscoverableKey;
FOUNDATION_EXPORT NSString *const kStateReportConnectableKey;
FOUNDATION_EXPORT NSString *const kStateReportPowerKey;

// BluetoothDevice Keys
FOUNDATION_EXPORT NSString *const kDeviceInfoAddressKey;
FOUNDATION_EXPORT NSString *const kDeviceInfoHashKey;
FOUNDATION_EXPORT NSString *const kDeviceInfoNameKey;
FOUNDATION_EXPORT NSString *const kDeviceInfoPairedKey;
FOUNDATION_EXPORT NSString *const kDeviceInfoConnectedKey;
FOUNDATION_EXPORT NSString *const kDeviceInfoConnectedServicesKey;
FOUNDATION_EXPORT NSString *const kDeviceInfoConnectedServicesCountKey;


// Bluetooth Security Keys (used for keychain)
FOUNDATION_EXPORT NSString *const kBluetoothSecurityClassicService;
FOUNDATION_EXPORT NSString *const kBluetoothSecurityClassicLTK;
FOUNDATION_EXPORT NSString *const kBluetoothSecurityClassicLTKType;
FOUNDATION_EXPORT NSString *const kBluetoothSecurityLEService;
FOUNDATION_EXPORT NSString *const kBluetoothSecurityLELocalKeys;
FOUNDATION_EXPORT NSString *const kBluetoothSecurityLERemoteKeys;
FOUNDATION_EXPORT NSString *const kBluetoothSecurityLELTK;
FOUNDATION_EXPORT NSString *const kBluetoothSecurityLELTKType;

#endif
