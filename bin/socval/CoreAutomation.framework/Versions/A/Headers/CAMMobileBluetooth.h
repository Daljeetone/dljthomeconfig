//
//  CAMMobileBluetooth.h
//  coreautomationd
//
//  Created by Anirban Maiti on 2/10/12.
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CAMMobileBluetoothConstants.h"

#import "CAMReturnValues.h"

#define kCAMMobileBluetoothShortName    bluetooth

typedef NS_ENUM(NSInteger, CAMDCoreBluetoothPeripheralDescriptorType) {
	kCAMCBUUIDCharacteristicExtendedPropertiesString, // Not supported
    kCAMCBUUIDCharacteristicUserDescriptionString, 
    kCAMCBUUIDServerCharacteristicConfigurationString,// Not supported
    kCAMCBUUIDCharacteristicFormatString,
	kCAMCBUUIDCharacteristicAggregateFormatString, // Not supported
	kCAMCBUUIDClientCharacteristicConfigurationString
} ;

@protocol CAMMobileBluetooth <NSObject>

@optional
#pragma mark -
#pragma mark Power
- (CAMReturnVoid *)on;
- (CAMReturnVoid *)off;
- (CAMReturnBool *)isOn;

#pragma mark -
#pragma mark Properties
- (CAMReturnString *)name;
- (CAMReturnString *)address;
- (CAMReturnString *)pin;
- (CAMReturnVoid *)setPin:(NSString*)code;
- (CAMReturnBool*)isServiceSupported:(NSNumber*)service;
- (CAMReturnInteger*)supportedServices;
- (CAMReturnString *)bluetoothDaemonName;
- (CAMReturnString *)chipsetName;   // Yellow Only
- (CAMReturnBool *)supportsLowEnergy; // Yellow Only

#pragma mark -
#pragma mark Pairing
- (CAMReturnVoid *)setPairingEnabled:(NSNumber*)enabled;
- (CAMReturnDictionary *)pairWithDeviceAddress:(NSString*)macAddress pincode:(NSString*)pin forService:(NSNumber*)serviceMask;
- (CAMReturnVoid *)unpairWithDeviceAddress:(NSString*)macAddress;
- (CAMReturnBool *)isPairedWithDeviceAddress:(NSString*)macAddress;
- (CAMReturnString *)passKeyWithDeviceAddress:(NSString*)macAddress;
- (CAMReturnArray *)pairedDevices;

/*!
 @method        ltkForDevice:
 @abstract      Retrieve the Long term key from paried device.
 @discussion    If device is not paired, it will return nil string with error. (iOS only)
 */
- (CAMReturnString *)ltkForDevice:(NSString *)deviceAddress;

#pragma mark -
#pragma mark Connections

/*!
 @method        connectWithDeviceAddress:forService:
 @abstract      Try to connect to the bluetooth device with specified address.
 @discussion    serviceMask doesn't apply to Yellow and will be ignored.
 */
- (CAMReturnBool *)connectWithDeviceAddress:(NSString*)macAddress forService:(NSNumber*)serviceMask;
- (CAMReturnBool *)disconnectWithDeviceAddress:(NSString*)macAddress;
- (CAMReturnVoid *)setConnectable:(NSNumber*)state;
- (CAMReturnBool *)isConnectable;
- (CAMReturnBool *)isConnected;
- (CAMReturnInteger *)connectedServicesMaskForDeviceAddress:(NSString*)macAddress;
- (CAMReturnArray *)connectedDevices;
- (CAMReturnArray *)connectionHistory;
- (CAMReturnVoid *)clearHistory;

#pragma mark -
#pragma mark Discovery
- (CAMReturnBool *)canDiscoverDeviceAddress:(NSString*)macAddress;
- (CAMReturnBool *)canDiscoverDeviceName:(NSString*)friendlyName;
- (CAMReturnVoid *)setDiscoverable:(NSNumber*)state;
- (CAMReturnBool *)isDiscoverable;

- (CAMReturnVoid *)startDiscovery:(NSNumber *)timeout;
- (CAMReturnVoid *)stopDiscovery;
- (CAMReturnArray *)discoveredDevices;

- (CAMReturnBool *)setAFHMap:(NSData *)afhMap;
- (CAMReturnData *)readAFHMap:(NSString *)remoteAddress;

- (CAMReturnVoid *)startProximityDiscovery;

#pragma mark Proximity Discovery
- (CAMReturnVoid *)startProximityDiscovery:(NSNumber *)timeout;
- (CAMReturnVoid *)stopProximityDiscovery;
- (CAMReturnArray *)discoveredProximityDevices;
- (CAMReturnBool *) pairingProximityDevice:(NSString *)addressString;

#pragma mark -
#pragma mark Profile Specific
- (CAMReturnBool *)isSCOAudioConnected;
- (CAMReturnBool *)isA2DPAudioConnected;
- (CAMReturnBool *)isVoiceRecognitionAudioConnected;

#pragma mark -
#pragma mark HID
- (CAMReturnVoid *)startHIDReceiverWithTimeout:(NSNumber *)seconds;
- (CAMReturnArray *)resultsFromStoppingHIDReceiver;
- (CAMReturnBool *)setHIDReportStreamStart:start reportID:(NSNumber *)reportID;
- (CAMReturnBool *)setHIDReportid:(NSNumber *)reportid forPid:(NSNumber *)pid forUsage:(NSNumber *)usage forData:(NSData *)data;

#if !RC_SEED_BUILD
#pragma mark -
#pragma mark Accessory
/*!
 @method		accessoryMicModeBTAddress:macAddress
 @abstract		gets the accessory Mic Mode for macAddress
 @discussion	returns 1 if active mic is selected based upon in ear detection, 2 on the right bud, 3 on the left bud
 */
- (CAMReturnInteger *)accessoryMicModeBTAddress:(NSString *)macAddress;
- (CAMReturnInteger *)setAccessoryMicModeBTAddress:(NSString *)macAddress forMicMode:(NSNumber *)micMode;

/*!
 @method		inEarDetectionEnabledBTAddress
 @abstract		gets if in ear detection is enabled for macAddress
 @discussion	returns 1 if enabled, 0 if disabled
 */
- (CAMReturnBool *)inEarDetectionEnabledBTAddress:(NSString *)macAddress;
- (CAMReturnBool *)setInEarDetectionEnabledBTAddress:(NSString *)macAddress enabled:(NSNumber *)enabled;
- (CAMReturnBool *)setAccessory:(NSString *)macAddress buttonType:(NSNumber *)buttonType;
- (CAMReturnInteger *)accessoryButtonType:(NSString *)macAddress;
- (CAMReturnBool *)setAccessory:(NSString *)macAddress name:(NSString *)name;
- (CAMReturnString *)accessoryName:(NSString *)macAddress;
- (CAMReturnBool *)setAccessory:(NSString *)macAddress userName:(NSString *)name;

#endif // RC_SEED_BUILD

#pragma mark - PAN (Yellow Only API)
- (CAMReturnVoid *)enablePANConnectionOnAddress:(NSString *)bdaddr;
- (CAMReturnVoid *)disablePANConnectionOnAddress:(NSString *)bdaddr;
- (CAMReturnBool *)getPANConnectionStateFromAddress:(NSString *)bdaddr;

#pragma mark -
#pragma mark Internal
- (CAMReturnBool *)hasBTServerCrashed;
- (CAMReturnVoid *)resetAfterBTServerCrash;
- (CAMReturnBool *)restartBTServer;
- (CAMReturnDictionary *)stateReport;

- (CAMReturnVoid *)insertLogText:(NSString *)text;
- (CAMReturnBool *)isLoggingEnabled;
- (CAMReturnVoid *)setLoggingEnabled:(NSNumber *)state;
- (CAMReturnVoid *)setLoggingEnabled:(NSNumber *)state forStack:(NSString *)stackName;
- (CAMReturnVoid *)setLoggingLevel:(NSString *)level forProfile:(NSString *)profileName;
/*! @brief Attempts dump Bluetooth Packet Log. */
- (CAMReturnVoid *)dumpBluetoothPacketLog;

#pragma mark -
#pragma mark LE Central Support
- (CAMReturnVoid *)scanForPeripheralsWithServices:(NSArray*)serviceUUIDs options:(NSDictionary *)options;
- (CAMReturnVoid *)stopScan;
- (CAMReturnVoid *)resetPeripheralScan;
- (CAMReturnArray *)discoveredPeripherals;
- (CAMReturnArray *)retrieveConnectedPeripherals:(NSNumber*)timeout;
- (CAMReturnArray *)retrievePeripherals:(NSArray*) peripheralUUIDs withTimeout:(NSNumber*)timeout;

- (CAMReturnBool *)connectPeripheral:(NSNumber*)peripheralHandle options:(NSDictionary *)options;
- (CAMReturnBool *)isPeripheralConnected:(NSNumber*)peripheralHandle;
- (CAMReturnVoid *)cancelConnectionForPeripheral:(NSNumber*)peripheralHandle force:(NSNumber*)force;
- (CAMReturnVoid *)setConnectionUpdate:(NSNumber*)connectionHandle interval:(NSNumber*)connectionInterval;
- (CAMReturnVoid *)setConnectionLatency:(NSNumber*) latency forPeripheral:(NSNumber*)peripheralHandle;

- (CAMReturnArray *)getServices:(NSArray*)knownServiceUUIDs forPeripheral:(NSNumber*)peripheralHandle discoverTree:(NSNumber*)option withTimeout:(NSNumber*)timeout;
- (CAMReturnArray *)discoverIncludedServices:(NSArray*)knownIncludedServiceUUIDs forService:(NSData*)serviceUUID forPeripheral:(NSNumber*)peripheralHandle withTimeout:(NSNumber*)timeout;
- (CAMReturnArray *)discoverCharacteristics:(NSArray*)knownCharacteristicUUIDs forService:(NSData*)serviceUUID forPeripheral:(NSNumber*)peripheralHandle withTimeout:(NSNumber*)timeout;
- (CAMReturnArray *)discoverDescriptorsForCharacteristic:(NSData*)characteristicUUID forService:(NSData*)serviceUUID forPeripheral:(NSNumber*)peripheralHandle withTimeout:(NSNumber*)timeout;


- (CAMReturnVoid *)readValueForCharacteristic:(NSData*)characteristicUUID forService:(NSData*)serviceUUID forPeripheral:(NSNumber*)peripheralHandle  withTimeout:(NSNumber*)timeout;
- (CAMReturnData *)getValueForCharacteristic:(NSData*)characteristicUUID forService:(NSData*)serviceUUID forPeripheral:(NSNumber*)peripheralHandle;
- (CAMReturnVoid *)writeValue:(NSData*)data byType:(NSNumber*)type forCharacteristic:(NSData*)characteristicUUID forService:(NSData*)serviceUUID forPeripheral:(NSNumber*)peripheralHandle withTimeout:(NSNumber*)timeout;
- (CAMReturnVoid *)setNotifyValue:(NSNumber*)notifyValue forCharacteristic:(NSData*)characteristicUUID forService:(NSData*)serviceUUID forPeripheral:(NSNumber*)peripheralHandle;
- (CAMReturnDictionary *)characteristicPerfData:(NSData*)characteristicUUID forService:(NSData*)serviceUUID forPeripheral:(NSNumber*)peripheralHandle;

- (CAMReturnVoid *)readValueForDescriptor:(NSData*)descriptorUUID forCharacteristic:(NSData*)characteristicUUID forService:(NSData*)serviceUUID forPeripheral:(NSNumber*)peripheralHandle  withTimeout:(NSNumber*)timeout;
- (CAMReturnData *)getValueForDescriptor:(NSData*)descriptorUUID forCharacteristic:(NSData*)characteristicUUID forService:(NSData*)serviceUUID forPeripheral:(NSNumber*)peripheralHandle;
- (CAMReturnVoid *)writeValue:(NSData*)data forDescriptor:(NSData*)descriptorUUID forCharacteristic:(NSData*)characteristicUUID forService:(NSData*)serviceUUID forPeripheral:(NSNumber*)peripheralHandle withTimeout:(NSNumber*)timeout;
- (CAMReturnDictionary *)descriptorPerfData:(NSData*)descriptorUUID forCharacteristic:(NSData*)characteristicUUID forService:(NSData*)serviceUUID forPeripheral:(NSNumber*)peripheralHandle;

- (CAMReturnArray *)recordedNotificationsForPeripheral:(NSNumber*)peripheralHandle;

- (CAMReturnVoid *)readRSSIForPeripheral:(NSNumber*)peripheralHandle;
- (CAMReturnInteger *)rssiValueForPeripheral:(NSNumber*)peripheralHandle;
- (CAMReturnDictionary *)rssiReadPerfDataForPeripheral:(NSNumber*)peripheralHandle;
- (CAMReturnInteger *)connectionIntervalForPeripheral:(NSNumber*)peripheralHandle;


/*!
 @method		setAutoPairForPeripheral:enabled:
 @abstract		set the LE pairing request to accept automatically.
 @discussion	if autoPairing is disabled, the passKey request wont be accepted and the passKey have to provided by the remote device.
				e.g, in case of LE HID, turn this OFF. We would need to type in the passKey from the HID device.
 */
- (CAMReturnVoid *)setAutoPairForPeripheral:(NSNumber*)peripheralHandle enabled:(NSNumber*)enabled;

/*!
 @method		setPasskeyForPeripheral:key:
 @abstract		set the passkey to resond to pairing request.
 e.g, in case of pencil. We would need to enter a specific passkey "1234".
 */
- (CAMReturnVoid *)setPasskeyForPeripheral:(NSNumber*)peripheralHandle key:(NSNumber*)passkey;

/*!
 @method        setUseOutOfBandPairingOnCentral:
 @deprecated Use setUseOutOfBandPairingOnCentral:withOOBData:.
 @abstract      enables or disables the use of out-of-band pairing for subsequent pairing attempts on all peers.
 */
- (CAMReturnVoid *)setUseOutOfBandPairingOnCentral:(NSNumber*)enabled __attribute__ ((deprecated));

/*!
 @method        setUseOutOfBandPairingOnCentral:withOOBData:
 @abstract      enables or disables the use of out-of-band pairing for subsequent pairing attempts on all peers. oobData is returned by getOutOfBandPairingData:
 @discussion    Pairing will use out-of-band authentication.
 */
- (CAMReturnVoid *)setUseOutOfBandPairingOnCentral:(NSNumber*)enabled withOOBData:(NSData*)data;

/*!
 @method		pairPeripheral:
 @abstract		Pair with the peripheral. Returns error if it fails to complete the pairing process.
 @discussion	if autoPairing is disabled, pairing wont be successful, but this function wont return any error. Use isPeripheralPaired to get the pairing status.
 */
- (CAMReturnVoid *)pairPeripheral:(NSNumber*)peripheralHandle;
- (CAMReturnInteger *)isPeripheralPaired:(NSNumber*)peripheralHandle;
- (CAMReturnArray *)retrievePairedPeripherals;
- (CAMReturnInteger *)passKeyForPeripheral:(NSNumber*)peripheralHandle;
- (CAMReturnVoid *)unpairPeripheral:(NSNumber*)peripheralHandle;
- (CAMReturnBool *)waitForOutOfBandPairingToComplete:(NSNumber*)peripheralHandle withTimeout:(NSNumber*)timeout;

/*!
 @method        ltkForPeripheral:
 @abstract      Retrieve the long term key from peripheral.
 @discussion    If peripheral is not paired, it will return nil string with error.
 */
- (CAMReturnString *)ltkForPeripheral:(NSNumber *)peripheralHandle;

/*!
 @method        startThroughput:withInterval:forIterations:byType:forCharacteristic:forService:forPeripheral
 @abstract      This method will start to send rawInput repeatly over specified iterations. rawInput will also be prefixed with a 2 bytes identification number.
 @discussion    4 bytes identification number is used to identify each LE transaction. The receiving end will use this transaction number to identify missed packets.
 */
- (CAMReturnVoid *)startThroughput:(NSDictionary *)rawInput
                      withInterval:(NSNumber *)milliseconds
                     forIterations:(NSNumber *)times
                            byType:(NSNumber*)type
                 forCharacteristic:(NSData*)characteristicUUID
                        forService:(NSData*)serviceUUID
                     forPeripheral:(NSNumber*)peripheralHandle;

/*!
 @method        isiCloudPaired:
 @abstract      This method will report if current device is LE paired with a public bluetooth address.
 @discussion    This method is useful to check if device is iCloud paired.
 */
- (CAMReturnBool *)isiCloudPaired:(NSString *)publicAddress;

/*!
 @method        pairingRecords:
 @abstract      This method will return a dictionary of pairing records per public address.
 @discussion    Returned dictionary will be similar to this:
 
 Value: (
 {
 "Public 90:3C:92:34:12:2E" =         {
     "Local Encryption" =             {
         "Encrypted Diversifier" = <efbb>;
         "Long-term Key Length" = <10>;
         "Long-term Key Type" = <01>;
         "Random Number" = <c059b629 cb6c3f4c>;};
 
     "Remote Encryption" =             {
         "Encrypted Diversifier" = <9e04>;
         "Long-term Key" = <b7d93fb1 87266f5d d0cc2411 41827388>;
         "Long-term Key Length" = <10>;
         "Long-term Key Type" = <01>;
         "Random Number" = <14c6dadd c3d328f7>;};
 
     "Remote IRK" = <ebe0ff9b 833ad4d2 a61762a7 76585bcb>;};
 },
 {
 "Public 90:3C:92:34:91:9F" =         {
     "Local Encryption" =             {
         "Encrypted Diversifier" = <618b>;
         "Long-term Key Length" = <10>;
         "Long-term Key Type" = <01>;
         "Random Number" = <40f56a3d 74c2a0f5>;
         };
     "Remote Encryption" =             {
         "Encrypted Diversifier" = <40ac>;
         "Long-term Key" = <c4ec0175 1b52aca2 30f446be 26cc5638>;
         "Long-term Key Length" = <10>;
         "Long-term Key Type" = <01>;
         "Random Number" = <7d49741a 8a83ed3e>;
         };
     "Remote IRK" = <3518796c 5c6a2dc8 cfaecb84 64a592ee>;};
 }
 )
 */
- (CAMReturnDictionary *)pairingRecords;

#pragma mark -
#pragma mark LE Peripheral Support

- (CAMReturnInteger *)createServiceWithUUID:(NSData *)uuid primaryService:(NSNumber *)primaryService includeWithAdvertise:(NSNumber *)advertisePacket;
- (CAMReturnVoid *)addService:(NSNumber*)serviceHandle;
- (CAMReturnVoid *)removeService:(NSNumber *)serviceHandle;
- (CAMReturnVoid *)removeAllServices;
- (CAMReturnVoid *)setUseOutOfBandPairingOnPeripheral:(NSNumber *)enabled;
- (CAMReturnData *)getOutOfBandPairingData;

- (CAMReturnVoid *)addIncludedService:(NSNumber *)serviceHandle parentService:(NSNumber *)parentHandle;

- (CAMReturnInteger *)createCharacteristicWithUUID:(NSData *)uuid properties:(NSNumber*)properties value:(NSData *)value permissions:(NSNumber*)permissions;
- (CAMReturnData *)valueForCharacteristic:(NSNumber *)handle;
- (CAMReturnVoid *)setValueForCharacteristic:(NSNumber *)handle value:(NSData *)value;
- (CAMReturnVoid *)addCharacteristic:(NSNumber*)handle parentService:(NSNumber *)parentServiceHandle;

- (CAMReturnInteger *)createDescriptorWithType:(NSNumber *)type value:(NSData *)value;
- (CAMReturnData *)valueForDescriptor:(NSNumber *)handle;
- (CAMReturnVoid *)addDescriptor:(NSNumber*)handle parentCharacteristic:(NSNumber *)parentCharacteristicHandle;

- (CAMReturnVoid *)startAdvertisingWithData:(NSDictionary *)advData;
- (CAMReturnVoid *)startAdvertisingWithName:(NSString *)peripheralName powerLevel:(NSNumber *)level manufacturerData:(NSData *)data;
- (CAMReturnVoid *)stopAdvertising;
- (CAMReturnVoid *)setAdvertisingInterval:(NSNumber *)interval;

- (CAMReturnBool *)isPeripheralAdvertising;
- (CAMReturnInteger *)connectionLatency;
- (CAMReturnVoid *)setConnectionLatency:(NSNumber *)latency;
- (CAMReturnArray *)connectedCentrals;
- (CAMReturnArray *)characteristicValueChangeListnerCentrals;

#pragma mark -
#pragma mark Scalable Pipe Support
- (CAMReturnBool *)registerEndpoint:(NSString *)identifer type:(NSNumber *)type priority:(NSNumber *)priority withTimeout:(NSNumber *)timeout;
- (CAMReturnBool *)unregisterEndpoint:(NSString *)identifer withTimeout:(NSNumber *)timeout;
- (CAMReturnDictionary *)endpoints;
- (CAMReturnBool *)isEndpointRegistered:(NSString *)identifer;
- (CAMReturnBool *)isEndpointConnected:(NSString *)identifer;

- (CAMReturnDictionary *)writeToPipeAtEndpoint:(NSString *)identifer withData:(NSData *)data withThroughput:(NSNumber *)throughput atFrequency:(NSNumber *)frequency;
- (CAMReturnInteger *)writeToPipeAtEndpoint:(NSString *)identifer withData:(NSData *)data withTimeout:(NSNumber *)timeout;
- (CAMReturnData *)readFromPipeAtEndpoint:(NSString *)identifier withTimeout:(NSNumber *)timeout;
- (CAMReturnDictionary *)readFromPipeAtEndpoint:(NSString *)identifier calculateHash:(NSNumber *)calculateHash withTimeout:(NSNumber *)timeout;
- (CAMReturnDictionary *)lastReceivedStartEndTime:(NSString *)identifier;

#pragma mark - Debug
/*!
 @method        enableMFiAuthentication
 @abstract      Enable Apple MFi Authentication for Bluetooth LEA peripherals.
 @discussion    MFi authentication is enabled by default in Blacktail and above. MFi authentication checks if a LEA peripheral is MFi authenticated by Apple.
                If MFi authentication fails, MobileBluetooth will disconnect LEA peripheral in 90 seconds.
 
                This only applies to iOS as of 2014/12/12.
 */
- (CAMReturnVoid*)enableMFiAuthentication;

/*!
 @method        disableMFiAuthentication
 @abstract      Disable Apple MFi Authentication for Bluetooth LEA peripherals.
 @discussion    MFi authentication is enabled by default in Blacktail and above. MFi authentication checks if a LEA peripheral is MFi authenticated by Apple.
                If MFi authentication fails, MobileBluetooth will disconnect LEA peripheral in 90 seconds.
                
                This only applies to iOS as of 2014/12/12.
 */
- (CAMReturnVoid*)disableMFiAuthentication;
@end
