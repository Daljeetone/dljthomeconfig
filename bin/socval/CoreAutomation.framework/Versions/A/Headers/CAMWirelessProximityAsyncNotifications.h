//
//  CAMWirelessProximityAsyncNotifications.h
//  coreautomationd
//
//  Created by Inna Noten on 03/10/16.
//
//

#import <Foundation/Foundation.h>

// ZoneTracker
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_Zones_DidUpdateState;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_Zones_EnteredZone;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_Zones_ExitedZone;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_Zones_DidFailToRegisterZones;

// AWDL
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_AWDL_DidUpdateState;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_AWDL_StartedAdvertising;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_AWDL_StoppedAdvertising;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_AWDL_AdvertisingPending;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_AWDL_FailedToStartAdvertising;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_AWDL_StartedScanning;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_AWDL_StoppedScanning;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_AWDL_FailedToStartScanning;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_AWDL_FoundDevice;

// AirPlaySolo
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_AirPlaySolo_DidUpdateState;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_AirPlaySolo_StartedAdvertising;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_AirPlaySolo_StoppedAdvertising;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_AirPlaySolo_AdvertisingPending;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_AirPlaySolo_FailedToStartAdvertising;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_AirPlaySolo_StartedScanning;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_AirPlaySolo_StoppedScanning;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_AirPlaySolo_FailedToStartScanning;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_AirPlaySolo_FoundDevice;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_AirPlaySolo_DidStartTrackingPeer;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_AirPlaySolo_DidStopTrackingPeer;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_AirPlaySolo_DidLosePeer;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_AirPlaySolo_PeerTrackingSlotsAvailable;

// Continuity
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_Continuity_DidUpdateState;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_Continuity_DidChangeBluetoothBandwidthState;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_Continuity_StartedAdvertising;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_Continuity_StoppedAdvertising;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_Continuity_AdvertisingPending;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_Continuity_FailedToStartAdvertising;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_Continuity_StartedScanning;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_Continuity_StoppedScanning;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_Continuity_FailedToStartScanning;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_Continuity_DiscoveredTypeWithData;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_Continuity_DiscoveredPeerWithData;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_Continuity_ConnectedToPeer;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_Continuity_DisconnectedFromPeer;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_Continuity_SentData;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_Continuity_ReceivedData;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_Continuity_DidStartTrackingPeer;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_Continuity_DidStopTrackingPeer;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_Continuity_DidLosePeer;

//ATV
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_ATV_DidUpdateAdvertiserState;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_ATV_DidUpdateScannerState;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_ATV_DidReceiveData;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_ATV_DidFailWithError;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_ATV_FailedToStartAdvertising;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_ATV_FailedToStartScanning;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_ATV_TransferComplete;


//Nearby
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_NearBy_DidUpdateState;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_NearBy_DidChangeBluetoothBandwidthState;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_NearBy_DidStartAdvertisingType;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_NearBy_DidDeferAdvertisingType;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_NearBy_DidStopAdvertisingType;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_NearBy_DidFailToStartAdvertisingOfType;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_NearBy_DidStartScanningForType;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_NearBy_DidStopScanningForType;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_NearBy_DidFailToStartScanningForType;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_NearBy_DidDiscoverType;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_NearBy_DidLosePeer;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_NearBy_DidConnectToPeer;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_NearBy_DidDisconnectFromPeer;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_NearBy_DidSendData;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_NearBy_DidReceiveData;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_NearBy_DidStartTrackingPeer;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_NearBy_DidStopTrackingPeer;


//Device Scanner
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_DeviceScanner_DidUpdateState;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_DeviceScanner_FoundDevice;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_DeviceScanner_FoundRequestedDevice;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_DeviceScanner_DidFailToRegisterDevices;

// WirelessProximity Pairing
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_WPPairing_DidUpdateState;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_WPPairing_FoundDevice;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_WPPairing_FoundDevicePeeringInfo;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_WPPairing_StartedScanning;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_WPPairing_StoppedScanning;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_WPPairing_FailedToStartScanning;

//WirelessProximity HomeKit
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_WPHomeKit_DidUpdateState;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_WPHomeKit_FoundDevice;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_WPHomeKit_FoundDeviceRSSI;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_WPHomeKit_StartedScanning;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_WPHomeKit_StoppedScanning;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_WPHomeKit_FailedToStartScanning;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_WPHomeKit_AllowDuplicate;

//WirelessProximity HeySiri
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_WPHeySiri_FoundDeviceWithData;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_WPHeySiri_StartedAdvertising;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_WPHeySiri_AdvertisingPending;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_WPHeySiri_StoppedAdvertising;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_WPHeySiri_FailedToStartAdvertisingWithError;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_WPHeySiri_StartedScanning;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_WPHeySiri_StoppedScanning;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_WPHeySiri_FailedToStartScanningWithError;

//WirelessProximity MagicSwitch
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_WPMagicSwitch_DidUpdateState;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_WPMagicSwitch_StartedScanning;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_WPMagicSwitch_StoppedScanning;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_WPMagicSwitch_FailedToStartScanningWithError;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_WPMagicSwitch_FoundDeviceWithData;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_WPMagicSwitch_StartedAdvertising;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_WPMagicSwitch_StoppedAdvertising;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_WPMagicSwitch_PendingAdvertising;
FOUNDATION_EXPORT NSString *const AsyncNotification_WirelessProximity_WPMagicSwitch_FailedToStartAdvertisingWithError;

// No compile-time initializer for NSSet or NSArray. Now let's use this bad hackish way to initialize for all notifications.
#define WirelessProximityNotifications \
	AsyncNotification_WirelessProximity_Zones_DidUpdateState, \
	AsyncNotification_WirelessProximity_Zones_EnteredZone, \
	AsyncNotification_WirelessProximity_Zones_ExitedZone, \
    AsyncNotification_WirelessProximity_Zones_DidFailToRegisterZones, \
    AsyncNotification_WirelessProximity_AWDL_DidUpdateState, \
    AsyncNotification_WirelessProximity_AWDL_StartedAdvertising, \
    AsyncNotification_WirelessProximity_AWDL_StoppedAdvertising, \
    AsyncNotification_WirelessProximity_AWDL_AdvertisingPending, \
    AsyncNotification_WirelessProximity_AWDL_FailedToStartAdvertising, \
    AsyncNotification_WirelessProximity_AWDL_StartedScanning, \
    AsyncNotification_WirelessProximity_AWDL_StoppedScanning, \
    AsyncNotification_WirelessProximity_AWDL_FailedToStartScanning, \
    AsyncNotification_WirelessProximity_AWDL_FoundDevice, \
    AsyncNotification_WirelessProximity_AirPlaySolo_DidUpdateState, \
    AsyncNotification_WirelessProximity_AirPlaySolo_StartedAdvertising, \
    AsyncNotification_WirelessProximity_AirPlaySolo_StoppedAdvertising, \
    AsyncNotification_WirelessProximity_AirPlaySolo_AdvertisingPending, \
    AsyncNotification_WirelessProximity_AirPlaySolo_FailedToStartAdvertising, \
    AsyncNotification_WirelessProximity_AirPlaySolo_StartedScanning, \
    AsyncNotification_WirelessProximity_AirPlaySolo_StoppedScanning, \
    AsyncNotification_WirelessProximity_AirPlaySolo_FailedToStartScanning, \
    AsyncNotification_WirelessProximity_AirPlaySolo_FoundDevice, \
    AsyncNotification_WirelessProximity_AirPlaySolo_DidStartTrackingPeer, \
    AsyncNotification_WirelessProximity_AirPlaySolo_DidStopTrackingPeer, \
    AsyncNotification_WirelessProximity_AirPlaySolo_DidLosePeer, \
    AsyncNotification_WirelessProximity_AirPlaySolo_PeerTrackingSlotsAvailable, \
    AsyncNotification_WirelessProximity_Continuity_DidUpdateState, \
    AsyncNotification_WirelessProximity_Continuity_DidChangeBluetoothBandwidthState, \
    AsyncNotification_WirelessProximity_Continuity_StartedAdvertising, \
    AsyncNotification_WirelessProximity_Continuity_StoppedAdvertising, \
    AsyncNotification_WirelessProximity_Continuity_AdvertisingPending, \
    AsyncNotification_WirelessProximity_Continuity_FailedToStartAdvertising, \
    AsyncNotification_WirelessProximity_Continuity_StartedScanning, \
    AsyncNotification_WirelessProximity_Continuity_StoppedScanning, \
    AsyncNotification_WirelessProximity_Continuity_FailedToStartScanning, \
    AsyncNotification_WirelessProximity_Continuity_DiscoveredTypeWithData, \
    AsyncNotification_WirelessProximity_Continuity_DiscoveredPeerWithData, \
    AsyncNotification_WirelessProximity_Continuity_ConnectedToPeer, \
    AsyncNotification_WirelessProximity_Continuity_DisconnectedFromPeer, \
    AsyncNotification_WirelessProximity_Continuity_SentData, \
    AsyncNotification_WirelessProximity_Continuity_ReceivedData, \
    AsyncNotification_WirelessProximity_Continuity_DidStartTrackingPeer, \
    AsyncNotification_WirelessProximity_Continuity_DidStopTrackingPeer, \
    AsyncNotification_WirelessProximity_Continuity_DidLosePeer, \
    AsyncNotification_WirelessProximity_ATV_DidUpdateAdvertiserState, \
    AsyncNotification_WirelessProximity_ATV_DidUpdateScannerState, \
    AsyncNotification_WirelessProximity_ATV_DidReceiveData, \
    AsyncNotification_WirelessProximity_ATV_DidFailWithError, \
    AsyncNotification_WirelessProximity_ATV_FailedToStartAdvertising, \
    AsyncNotification_WirelessProximity_ATV_FailedToStartScanning, \
    AsyncNotification_WirelessProximity_ATV_TransferComplete, \
    AsyncNotification_WirelessProximity_NearBy_DidUpdateState, \
    AsyncNotification_WirelessProximity_NearBy_DidChangeBluetoothBandwidthState, \
    AsyncNotification_WirelessProximity_NearBy_DidStartAdvertisingType, \
    AsyncNotification_WirelessProximity_NearBy_DidDeferAdvertisingType, \
    AsyncNotification_WirelessProximity_NearBy_DidStopAdvertisingType, \
    AsyncNotification_WirelessProximity_NearBy_DidFailToStartAdvertisingOfType, \
    AsyncNotification_WirelessProximity_NearBy_DidStartScanningForType, \
    AsyncNotification_WirelessProximity_NearBy_DidStopScanningForType, \
    AsyncNotification_WirelessProximity_NearBy_DidFailToStartScanningForType, \
    AsyncNotification_WirelessProximity_NearBy_DidDiscoverType, \
    AsyncNotification_WirelessProximity_NearBy_DidLosePeer, \
    AsyncNotification_WirelessProximity_NearBy_DidConnectToPeer, \
    AsyncNotification_WirelessProximity_NearBy_DidDisconnectFromPeer, \
    AsyncNotification_WirelessProximity_NearBy_DidSendData, \
    AsyncNotification_WirelessProximity_NearBy_DidReceiveData, \
    AsyncNotification_WirelessProximity_NearBy_DidStartTrackingPeer, \
    AsyncNotification_WirelessProximity_NearBy_DidStopTrackingPeer, \
    AsyncNotification_WirelessProximity_DeviceScanner_DidUpdateState, \
    AsyncNotification_WirelessProximity_DeviceScanner_FoundDevice, \
    AsyncNotification_WirelessProximity_DeviceScanner_FoundRequestedDevice, \
    AsyncNotification_WirelessProximity_DeviceScanner_DidFailToRegisterDevices, \
    AsyncNotification_WirelessProximity_WPPairing_DidUpdateState, \
    AsyncNotification_WirelessProximity_WPPairing_FoundDevice, \
    AsyncNotification_WirelessProximity_WPPairing_FoundDevicePeeringInfo, \
    AsyncNotification_WirelessProximity_WPPairing_StartedScanning, \
    AsyncNotification_WirelessProximity_WPPairing_StoppedScanning, \
    AsyncNotification_WirelessProximity_WPPairing_FailedToStartScanning, \
    AsyncNotification_WirelessProximity_WPHomeKit_DidUpdateState, \
    AsyncNotification_WirelessProximity_WPHomeKit_FoundDevice, \
    AsyncNotification_WirelessProximity_WPHomeKit_FoundDeviceRSSI, \
    AsyncNotification_WirelessProximity_WPHomeKit_StartedScanning, \
    AsyncNotification_WirelessProximity_WPHomeKit_StoppedScanning, \
    AsyncNotification_WirelessProximity_WPHomeKit_FailedToStartScanning, \
    AsyncNotification_WirelessProximity_WPHomeKit_AllowDuplicate, \
    AsyncNotification_WirelessProximity_WPHeySiri_FoundDeviceWithData, \
    AsyncNotification_WirelessProximity_WPHeySiri_StartedAdvertising, \
    AsyncNotification_WirelessProximity_WPHeySiri_AdvertisingPending, \
    AsyncNotification_WirelessProximity_WPHeySiri_StoppedAdvertising, \
    AsyncNotification_WirelessProximity_WPHeySiri_FailedToStartAdvertisingWithError, \
    AsyncNotification_WirelessProximity_WPHeySiri_StartedScanning, \
    AsyncNotification_WirelessProximity_WPHeySiri_StoppedScanning, \
    AsyncNotification_WirelessProximity_WPHeySiri_FailedToStartScanningWithError, \
    AsyncNotification_WirelessProximity_WPMagicSwitch_DidUpdateState, \
    AsyncNotification_WirelessProximity_WPMagicSwitch_StartedScanning, \
    AsyncNotification_WirelessProximity_WPMagicSwitch_StoppedScanning, \
    AsyncNotification_WirelessProximity_WPMagicSwitch_FailedToStartScanningWithError, \
    AsyncNotification_WirelessProximity_WPMagicSwitch_FoundDeviceWithData, \
    AsyncNotification_WirelessProximity_WPMagicSwitch_StartedAdvertising, \
    AsyncNotification_WirelessProximity_WPMagicSwitch_StoppedAdvertising, \
    AsyncNotification_WirelessProximity_WPMagicSwitch_PendingAdvertising, \
    AsyncNotification_WirelessProximity_WPMagicSwitch_FailedToStartAdvertisingWithError