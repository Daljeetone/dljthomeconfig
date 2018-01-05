//
//  CAMBluetoothAsyncNotifications.h
//  coreautomationd
//
//  Created by Chen Huang on 11/11/15.
//
//

#import <Foundation/Foundation.h>

FOUNDATION_EXPORT NSString *const AsyncNotification_Bluetooth_PairingCompleted;
FOUNDATION_EXPORT NSString *const AsyncNotification_Bluetooth_PairingPasskeyRequest;
/**
 *  User info will contain passkey with key set to "passkey"
 */
FOUNDATION_EXPORT NSString *const AsyncNotification_Bluetooth_PairingPasskeyDisplay;


// No compile-time initializer for NSSet or NSArray. Now let's use this bad hackish way to initialize for all notifications.
#define BluetoothNotifications \
	AsyncNotification_Bluetooth_PairingCompleted, \
	AsyncNotification_Bluetooth_PairingPasskeyRequest, \
	AsyncNotification_Bluetooth_PairingPasskeyDisplay