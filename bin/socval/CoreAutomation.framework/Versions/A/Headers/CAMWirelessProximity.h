//
//  CAMWirelessProximity
//  CoreAutomation
//
//  Created by Chen Huang on 12/4/13.
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CAMReturnValues.h"

#define kCAMWirelessProximityShortName wp

#define kCAMWirelessProximityUUID               @"uuid"
#define kCAMWirelessProximityMajor              @"major"
#define kCAMWirelessProximityMinor              @"minor"
#define kCAMWirelessProximityZoneEnter          @"zoneEnter"
#define kCAMWirelessProximityZoneExit           @"zoneExit"
#define kCAMWirelessProximityZones              @"zones"
#define kCAMWirelessProximityError              @"error"
#define kCAMWirelessProximityData               @"data"
#define kCAMWirelessProximityTimeout            @"timeout"
#define kCAMWirelessProximityType               @"type"
#define kCAMWiProxContinuityTypeError           @"Invalid Continuity Type"
#define kCAMWirelessProximityState              @"state"
#define kCAMWirelessProximityBTBandwidthState   @"btbandwidthstate"
#define kCAMWirelessProximityAdvertisingType    @"advertisingtype"
#define kCAMWirelessProximityScanningType       @"scanningtype"
#define kCAMWirelessProximityDiscoverType       @"discovertype"
#define kCAMWirelessProximityPeerInfo           @"peerinfo"
#define kCAMWirelessProximityDeviceIdentifier   @"deviceIdentifier"
#define kCAMWirelessProximityRSSI               @"rssi"


@protocol CAMWirelessProximity

@optional

#pragma mark -
#pragma mark WPStateTracker
- (CAMReturnInteger*) WirelessProximityState;

#pragma mark -
#pragma mark WPAdvertising
- (CAMReturnInteger *)advertiserState;

- (CAMReturnBool *)advertiserRegisterService:(NSDictionary *) theValues;
- (CAMReturnBool *)advertiserDeregisterService:(NSDictionary *) theValues;

- (CAMReturnInteger *)deviceScannerState;
- (CAMReturnBool *) deviceScannerScanForDeviceType:(NSString *)type forPeriodOf:(NSNumber *)scanPeriod blocking:(NSNumber *)isBlocking;
- (CAMReturnDouble *) deviceScannerDeregisterForDevices:(NSDictionary*)theValues;
- (CAMReturnDouble *) deviceScannerDeregisterAllDeviceChanges;

- (CAMReturnArray *) devicesFound;

#pragma mark -
#pragma mark WPZoneTracker
/*!
 @method		zoneTrackerRegisterForZoneChangesMatching:
 @abstract		register for zone changes.
 @param         zoneChangeInformation is a dictionary and contains the following information:
 "zones":        Array of dictionaries, each dictionary should be like:
 "uuid":     NSString of UUID Value (mandantory)
 "major":    NSNumber (16 bits value)   (optional)
 "minor":    NSNumber 16 bits value   (optional)
 "zoneEnter":    Bool
 "zoneExit":     Bool
 
 @discussion    This will register zone changes.
 */
- (CAMReturnBool *) zoneTrackerRegisterForZoneChangesMatching:(NSDictionary *)zoneChangeInformation;

/*!
 @method		zoneTrackerDeregisterForZoneChanges:
 @abstract		Deregister for zone changes.
 @param         zoneChangeInformation is a dictionary and contains the following information:
 "zones":        Array of dictionaries, each dictionary should be like:
 "uuid":     NSString of UUID Value (mandantory)
 
 @discussion    This will deregister zone changes described in the zoneChangeInformation.
 */
- (CAMReturnBool *) zoneTrackerDeregisterForZoneChanges:(NSDictionary *)zoneChangeInformation;

/*!
 @method		zoneTrackerDeregisterAllZoneChanges:
 @abstract		Deregister all zone changes.
 @discussion    This will deregister all zone changes.
 */
- (CAMReturnVoid *) zoneTrackerDeregisterAllZoneChanges;

/*!
 @method		isWirelessProximityReady:
 @abstract		Whether the WirelessProximity framework is ready. BT has to be on before wireless proximity to become ready.
 */
- (CAMReturnBool *) isWirelessProximityReady;

/*!
 @method		waitForWirelessProximityToBecomeReadyWithTimeout:
 @abstract		Wait for wireless proximity to become ready. BT has to be on before wireless proximity to become ready.
 */
- (CAMReturnBool *) waitForWirelessProximityToBecomeReadyWithTimeout:(NSNumber *)timeout;

- (CAMReturnArray *) enteredZones;
- (CAMReturnArray *) exitedZones;
- (CAMReturnBool *) resetEnteredZones;
- (CAMReturnBool *) resetExitedZones;

#pragma mark -
#pragma mark WPAWDL
/*!
 @method		awdlStartConnectionlessAWDLServiceAdvertisingWithData:
 @return		Timestamp of the call in milliseconds since 1970.
 @abstract		Start AWDL advertising.
 */
- (CAMReturnDouble *) awdlStartConnectionlessAWDLServiceAdvertisingWithData:(NSData*)data;

/*!
 @method		awdlStopConnectionlessAWDLServiceAdvertising:
 @return		Timestamp of the call in milliseconds since 1970.
 @abstract		Stop AWDL advertising.
 */
- (CAMReturnDouble *) awdlStopConnectionlessAWDLServiceAdvertising;

/*!
 @method		awdlStartConnectionlessAWDLServiceScanning:
 @return		Timestamp of the call in milliseconds since 1970.
 @abstract		Start AWDL service scanning.
 */
- (CAMReturnDouble *) awdlStartConnectionlessAWDLServiceScanning;

/*!
 @method		awdlStopConnectionlessAWDLServiceScanning:
 @return		Timestamp of the call in milliseconds since 1970.
 @abstract		Stop AWDL service scanning.
 */
- (CAMReturnDouble *) awdlStopConnectionlessAWDLServiceScanning;

/*!
 @method		awdlHashEmail:
 @abstract      Hash emails down.
 */
- (CAMReturnData *) awdlHashEmail:(NSString *)email;

/*!
 @method		awdlGenerateDataFromEmails:
 @abstract      Generates the payload to adverise with.
 @param         emails	An array containing up to three email address strings.
 */
- (CAMReturnData *) awdlGenerateDataFromEmails:(NSArray *)emails;

#pragma mark -
#pragma mark WPAirPlaySolo
/*!
 *  @method         airPlaySoloStartConnectionlessAdvertisingWithData:
 *  @param          theValues    @{ WPPuckType : NSString,  WPPuckTypeAirPlaySoloAdvertisingData : NSData }
 *  @discussion     This tells the framework to start advertising for given puck type and payload
 */
- (CAMReturnDouble *) airPlaySoloStartConnectionlessAdvertisingWithData:(NSDictionary*)theValues;

/*!
 *  @method         airPlaySoloStopConnectionlessAdvertising
 *  @discussion     This tells the framework to stop advertising
 */
- (CAMReturnDouble *) airPlaySoloStopConnectionlessAdvertising;

/*!
 *  @method         airPlaySoloStopConnectionlessAdvertising
 *  @param          type    The WPPuckType type (WPPuckTypeAirPlaySoloSourcePresence or WPPuckTypeAirPlaySoloTargetPresence
 that we want to stop advertising for
 *  @discussion     This tells the framework to stop advertising
 */
- (CAMReturnDouble *) airPlaySoloStopConnectionlessAdvertising:(NSString *)type;

/*!
 *  @method         airPlaySoloStartConnectionlessScanningWithData
 *  @param          theValues      @{ WPPuckType : NSString }
 *  @discussion     This tells the framework to start scanning for given puck type
 */
- (CAMReturnDouble *) airPlaySoloStartConnectionlessScanningWithData:(NSDictionary*)theValues;

/*!
 *  @method         airPlaySoloStopConnectionlessScanningWithData
 *  @param          theValues      @{ WPPuckType : NSString }
 *  @discussion     This tells the framework to stop scanning for given puck type
 */
- (CAMReturnDouble *) airPlaySoloStopConnectionlessScanningWithData:(NSDictionary*)theValues;

/*!
 *  @method       airPlaySoloStartTrackingPeer:withData:
 *  @param        peer - Peer UUID
 *  @param        theValues      @{ WPPuckType : NSString }
 *  @discussion   Start tracking peer. Max number of AppleTV can be tracked is 15.
 */
- (CAMReturnDouble *) airPlaySoloStartTrackingPeer:(NSString *)peer withData:(NSDictionary*)theValues;

/*!
 *  @method       airPlaySoloStopTrackingPeer:withData:
 *  @param        peer  peer UUID to track
 *  @param        theValues      @{ WPPuckType : NSString }
 *  @discussion   Stop tracking peer
 */
- (CAMReturnDouble *) airPlaySoloStopTrackingPeer:(NSString *)peer withData:(NSDictionary*)theValues;

#pragma mark -
#pragma mark WPContinuity
/*!
 *  @method       startAdvertisingOfType:withData:
 *  @param        type One of WPContinuityTypeActivity, WPContinuityTypeTetheringTargetPresence, WPContinuityTypeTetheringSourcePresence
 *  @param        data - max data length is 22 bytes
 *  @discussion   Start advertising of a type and data blob
 */
- (CAMReturnDouble *)continuityStartAdvertisingOfType:(NSNumber *)type withData:(NSData *)data;

/*!
 *  @method       stopAdvertisingOfType:
 *  @param        type One of WPContinuityTypeActivity, WPContinuityTypeTetheringTargetPresence, WPContinuityTypeTetheringSourcePresence
 *  @discussion   Stop advertising of a type
 */
- (CAMReturnDouble *)continuityStopAdvertisingOfType:(NSNumber *)type;

/*!
 *  @method       startScanningForType:withData:peers:
 *  @param        type One of WPContinuityTypeActivity, WPContinuityTypeTetheringTargetPresence, WPContinuityTypeTetheringSourcePresence
 *  @param        data - activity would pass in nil for data - max data length is 22 bytes
 *  @param        peers - NSArray of UUID strings identifying peers to return.  If nil, return all peers found
 *  @discussion   Scan for a type and data blob.
 */
- (CAMReturnDouble *)continuityStartScanningForType:(NSNumber *)type withData:(NSData *)data peers:(NSArray *)peers;

/*!
 *  @method       stopScanningForType:
 *  @param        type One of WPContinuityTypeActivity, WPContinuityTypeTetheringTargetPresence, WPContinuityTypeTetheringSourcePresence
 *  @discussion   Stop scanning for a type.
 */
- (CAMReturnDouble *)continuityStopScanningForType:(NSNumber *)type;

/*!
 *  @method       connectToPeer:
 *  @param        peer  peer UUID
 *  @discussion   Connect to given Peer.
 */
- (CAMReturnDouble *)continuityConnectToPeer:(NSString *)peer;

/*!
 *  @method       disconnectFromPeer:
 *  @param        peer  peer UUID
 *  @discussion   Disconnect from peer as soon as no more data to send. If no data transfer going on for 5s, it will automatically be disconnected
 */
- (CAMReturnDouble *)continuityDisconnectFromPeer:(NSString *)peer;

/*!
 *  @method       sendData:toPeer
 *  @param        data - Max data length is 65535 bytes
 *  @param        peer  peer UUID
 *  @discussion   Send data to peer
 */
- (CAMReturnDouble *)continuitySendData:(NSData *)data toPeer:(NSString *)peer;

/*!
 *  @method       startTrackingPeer:peer
 *  @param        peer  peer UUID - Max number of peers can be tracked is 15
 *  @param        type - One of WPContinuityTypeActivity, WPContinuityTypeTetheringTargetPresence, WPContinuityTypeTetheringSourcePresence
 *  @discussion   Start tracking peer
 */
- (CAMReturnDouble *)continuityStartTrackingPeer:(NSString *)peer forType:(NSNumber *)type;

/*!
 *  @method       stopTrackingPeer:peer
 *  @param        peer  peer UUID
 *  @param        type - one of WPContinuityTypeActivity, WPContinuityTypeTetheringTargetPresence, WPContinuityTypeTetheringSourcePresence
 *  @discussion   Stop tracking peer
 */
- (CAMReturnDouble *)continuityStopTrackingPeer:(NSString *)peer forType:(NSNumber *)type;

#pragma mark -
#pragma mark WPTransfer
- (CAMReturnDouble *)atvStartScan;
- (CAMReturnDouble *)atvStopScan;
- (CAMReturnDouble *)atvStartAdvertising;
- (CAMReturnDouble *)atvStopAdvertising;
- (CAMReturnDouble *)atvIgnoreDevice;

#pragma mark -
#pragma mark WPNearby
-(CAMReturnDouble*)startAdvertisingOfType:(NSNumber *)advertisingType data:(NSData *)data priority:(NSNumber *)priority mode:(NSNumber *)mode;
-(CAMReturnDouble*)startAdvertisingOfType:(NSNumber *)advertisingType withData:(NSData *)data priority:(NSNumber *)priority;
-(CAMReturnDouble*)startAdvertisingOfType:(NSNumber *)advertisingType withData:(NSData *)data;
-(CAMReturnDouble*)stopAdvertisingOfType:(NSNumber *)advertisingType;
-(CAMReturnDouble*)startScanningForType:(NSNumber *)scanningType data:(NSData *)data mask:(NSData *)mask peers:(NSArray *)peers scanMode:(NSNumber *)scanMode;
-(CAMReturnDouble*)startScanningForType:(NSNumber *)scanningType data:(NSData *)data mask:(NSData *)mask peers:(NSArray *)peers scanMode:(NSNumber *)scanMode rssi:(NSNumber *)rssi duplicates:(BOOL)duplicates;
-(CAMReturnDouble*)startScanningForType:(NSNumber *)scanningType data:(NSData *)data mask:(NSData *)mask peers:(NSArray *)peers scanMode:(NSNumber *)scanMode rssi:(NSNumber *)rssi duplicates:(BOOL)duplicates scanCache:(BOOL)scanCache;
-(CAMReturnDouble*)stopScanningForType:(NSNumber *)scanningType;
-(CAMReturnDouble*)connectToPeer:(NSString *)peer;
-(CAMReturnDouble*)disconnectFromPeer:(NSString *)peer;
-(CAMReturnDouble*)sendData:(NSData *)data toPeer:(NSString *)peer;
-(CAMReturnDouble*)startTrackingPeer:(NSString *)peer forType:(NSNumber *)type;
-(CAMReturnDouble*)stopTrackingPeer:(NSString *)peer forType:(NSNumber *)type;

#pragma mark -
#pragma mark WPPairing
-(CAMReturnDouble *)startProximityPairingServiceScanningWithRSSI:(NSNumber *)rssi duplicates:(BOOL)duplicate;
-(CAMReturnDouble *)startProximityPairingServiceScanning;
-(CAMReturnDouble *)stopProximityPairingServiceScanning;
-(CAMReturnDouble *)ignoreDeviceUntilNextUnlock:(NSString *)deviceUUID ignoreDevice:(BOOL)ignore;
#pragma mark -
#pragma mark WPHomeKit
/*!
 *  @method       startScanningWithData:(NSDictionary*)data
 *  @deprecated Use startScanningWithData:forType:.
 *  @param        data @{ WPHomeKitScanBlobData : NSData,  WPHomeKitScanMaskData : NSData, WPHomeKitScanDutyCycle : NSNumber}
 *                      blob/mask max data length is 22 bytes
 *  @discussion   This tells the framework to start scanning for given puck type
 */
-(CAMReturnDouble *)startScanningWithData:(NSDictionary*)data __attribute__ ((deprecated));
/*!
 *  @method       startScanningWithData:forType:
 *  @param        data @{ WPHomeKitScanBlobData : NSData,  WPHomeKitScanMaskData : NSData, WPHomeKitScanDutyCycle : NSNumber}
 *                      blob/mask max data length is 22 bytes
 *  @param        type NSInteger WPHomeKitType: WPHomeKitTypeOld=0 or WPHomeKitTypeNew=1
 *  @discussion   This tells the framework to start scanning for given puck type
 */
-(CAMReturnDouble *)startScanningWithData:(NSDictionary*)data forType:(NSNumber *)type;
/*!
 *  @method       stopScanning
 *  @deprecated Use stopScanning:.
 *  @discussion   This tells the framework to stop scanning for given puck type
 */
-(CAMReturnDouble *)stopScanning __attribute__ ((deprecated));
/*!
 *  @method       stopScanning:(WPHomeKitType)type
 *  @param        type WPHomeKitType: WPHomeKitTypeOld=0 or WPHomeKitTypeNew=1
 *  @discussion   This tells the framework to stop scanning for given puck type
 */
-(CAMReturnDouble *)stopScanning:(NSNumber *)type;
/*!
 *  @method       checkAllowDuplicate
 *  @discussion   This tells the framework to check if duplicate advertising reports enabled or not
 */
-(CAMReturnDouble *)checkAllowDuplicate;
#pragma mark -
#pragma mark WPHeySiri
/*!
 *  @method       heySiriStartAdvertisingWithData:data
 *  @param        data      @{ WPHeySiriAdvertisingData : NSData }
 *  @discussion   This tells the framework to start advertising it's Hey Siri data
 */
-(CAMReturnDouble*)heySiriStartAdvertisingWithData:(NSDictionary *)data;
/*!
 *  @method       heySiriScanningAndAdvertisingWithData:data
 *  @param        data    @{ WPHeySiriAdvertisingData : NSData }
 *  @discussion   This tells the framework to start advertising and start scanning it's Hey Siri data
 */
-(CAMReturnDouble*)heySiriScanningAndAdvertisingWithData:(NSDictionary *)data;
/*!
 *  @method       heySiriStopScanningAndAdvertising
 *  @discussion   This tells the framework to stop scanning and advertising it's Hey Siri
 */
-(CAMReturnDouble*)heySiriStopScanningAndAdvertising;
/*!
 *  @method       heySiriStopScanning
 *  @discussion   This tells the framework to stop scanning it's Hey Siri
 */
-(CAMReturnDouble*)heySiriStopScanning;
/*!
 *  @method       heySiriStartScanning
 *  @discussion   This tells the framework to start scanning it's Hey Siri
 */
-(CAMReturnDouble*)heySiriStartScanning;
/*!
 *  @method       heySiriStopAdvertising
 *  @discussion   This tells the framework to stop advertising it's Hey Siri
 */
-(CAMReturnDouble*)heySiriStopAdvertising;

#pragma mark -
#pragma mark WPMagicSwitch
/*!
 *  @method       magicSwitchStartScanningWithData:data
 *  @param        data  @{ WPMagicSwitchScanBlobData : NSData,  WPMagicSwitchScanMaskData : NSData,
 *                       WPMagicSwitchScanDutyCycle : NSNumber, WPMagicSwitchScanPeers : NSArray}
 *                      blob/mask max data length is 22 bytes
 *                      peers - NSArray of NSUUIDs identifying peers to return.  If nil, return all peers found
 *
 *  @discussion   This tells the framework to start scanning with given blob/mask and scan duty cycle values
 */
- (CAMReturnDouble*)magicSwitchStartScanningWithData:(NSDictionary*)data;
/*!
 *  @method        magicSwitchStopScanning
 *  @discussion    This tells the framework to stop scanning
 */
- (CAMReturnDouble*)magicSwitchStopScanning;
/*!
 *  @method        smagicSwitchStartAdvertisingWithData:(NSDictionary*)data
 *  @param         data @{ WPMagicSwitchAdvertisingData : NSData,  WPMagicSwitchAdvertiseTypeInterval : NSNumber}
 *  @abstract      This tells the framework to start advertising with given advertising interval
 *  @discussion    You must issue stop advertising and restart advertising whenever advertising interval needs to be changed
 */
- (CAMReturnDouble*)magicSwitchStartAdvertisingWithData:(NSDictionary*)data;
/*!
 *  @method        magicSwitchStopAdvertising
 *  @discussion    This tells the framework to stop advertising
 */
- (CAMReturnDouble*)magicSwitchStopAdvertising;

#if !RC_SEED_BUILD
#pragma mark - Enable Test mode
/*!
 *  @method       enable test mode
 *  @discussion   Once test mode is enabled, this process will be named as "WiProx" test client.
        all other non-test client will be removed from WiProx.
        Once all WiProx test clients disconnected from WiProx, test mode will be disabled on WiProx.
        Only then, regular WiProx client will work again.
 */
-(CAMReturnVoid *)enableTestMode;
#endif // !RC_SEED_BUILD

@end
