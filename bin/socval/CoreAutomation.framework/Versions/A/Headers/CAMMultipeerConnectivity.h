//
//  CAMMultipeerConnectivity.h
//  coreautomationd
//
//  Created by Roberto Mitma Castro on 10/30/14.
//
//

#import <Foundation/Foundation.h>
#import "CAMReturnValues.h"
#define kCAMMultipeerConnectivityShortName mc

@protocol CAMMultipeerConnectivity <NSObject>
@optional

/*!
 @method     resetTestData
 @abstract   Resets the messages, pictureLocations, connectionStates, and history test data
 */
-(CAMReturnVoid *)resetTestData;

/*!
 @method     createPeerID:(NSString*)name
 @abstract   Initiates an instance of MCPeerID
 */
-(CAMReturnBool *)createPeerID:(NSString *)name;

/*!
 @method     startSession
 @abstract   Initiates a MCSession with the MCPeerID initialized in createPeerID
 */
-(CAMReturnBool *)startSession;

/*!
 @method     startSessionWithSecurityIdentityFileName:password:encryptionPreference:
 @abstract   Initiates a MCSession with the MCPeerID initialized in createPeerID,
             security identity, and encryption preference.
 */
-(CAMReturnBool *)startSessionWithSecurityIdentityFileName:(NSString *)identityFileName
                                                 password:(NSString *)identityPassword
                                     encryptionPreference:(NSNumber *)encryptionPreference;

/*!
 @method     end
 @abstract   disconnects the MCSession
 */
- (CAMReturnBool *)end;

/*!
 @method     setSendInvitationDelay
 @abstract   Sets a delay that determines how much time the browser should wait before it sends an invite after peer discovery
 */
- (CAMReturnVoid *)setSendInvitationDelay:(NSNumber *)delay;

/*!
 @method     setAcceptInvitationDelay
 @abstract   Sets a delay that determines how much time the advertiser should wait before it accepts an incoming invitation
 */
- (CAMReturnVoid *)setAcceptInvitationDelay:(NSNumber *)delay;

/*!
 @method     setPeersToInvite:(NSArray<NSString *> *)peerIDs
 @abstract   Specify peers that should be invited to a session by the browser. Default value is nil, which means that
             all discovered peers will be invited. Empty array will result in no peers being invited.
 */
- (CAMReturnVoid *)setPeersToInvite:(NSArray<NSString *> *)peerIDs;

/*!
 @method     peersToInvite
 @abstract   Returns an array of peers that are set to be invited to a session.
 */
- (CAMReturnArray *)peersToInvite;

/*!
 @method     initAdvertiserWithServiceType:(NSString *)service;
 @abstract   Initializes a MCNearbyServiceAdvertiser for the existing MCPeerID and the service provided
 */
-(CAMReturnBool *)createAdvertiserWithServiceType:(NSString *)service;

/*!
 @method     startAdvertising
 @abstract   Starts advertising using the MCNearbyServiceAdvertiser previously initialized
 */
-(CAMReturnBool *)startAdvertising;

/*!
 @method     stopAdvertising
 @abstract   Stops advertising
 */
-(CAMReturnBool *)stopAdvertising;

/*!
 @method     initBrowserWithServiceType:(NSString *)service;
 @abstract   Initializes a MCNearbyServiceBrowser for the existing MCPeerID and the service provided
 */
-(CAMReturnBool *)createBrowserWithServiceType:(NSString *)service;

/*!
 @method     startBrowsing;
 @abstract   Starts browsing using the previously initialized MCNearbyServiceBrowser
 */
-(CAMReturnBool *)startBrowsing;

/*!
 @method     stopBrowsing;
 @abstract   Stops browsing
 */
-(CAMReturnBool *)stopBrowsing;

/*!
 @method     sendMessage:(NSString *)message
 @abstract   Sends the provided message to all connected peers
 */
-(CAMReturnBool *)sendMessage:(NSString *)message;

/*!
 @method     sendMessageWithLength:(NSNumber *)messageLength toPeers:(NSArray<NSString *> *)peerDisplayNames
 @abstract   Sends a message with specified length in bytes to specified recipients
 */
- (CAMReturnString *)sendMessageWithLength:(NSNumber *)messageLength toPeers:(NSArray<NSString *> *)peerDisplayNames;

/*!
 @method     sendResource:(NSString *)resource;
 @abstract   Sends the provided resource to all peers
 */
-(CAMReturnVoid *)sendResource:(NSString *)resource;

/*!
 @method     sendResource:(NSString *)resource withName:(NSString *)name toPeers:(NSArray<NSString *> *)peerDisplayNames
 @abstract   Sends the provided resource to specified peers
 */
-(CAMReturnVoid *)sendResource:(NSString *)resource withName:(NSString *)name toPeers:(NSArray<NSString *> *)peerDisplayNames;

/*!
 @method     getConnectedPeers;
 @abstract   Returns an array with all the connected peers to the mcsession
 */
-(CAMReturnArray *)getConnectedPeers;

/*!
 @method     getInterfaceTypesForPeer:(NSString*)peerIDDisplayName
 @abstract   Gets connected interfaces
 */
-(CAMReturnArray *)getInterfaceTypesForPeer:(NSString *)peerIDDisplayName;

/*!
 @method     closeDirectConnectionsWithPeer:(NSString *)peerIDDisplayName
 @abstract   Closes all direct connections to peer
 */
-(CAMReturnBool *)closeDirectConnectionsWithPeer:(NSString *)peerIDDisplayName;

/*!
 @method     getMessages;
 @abstract   Returns an array of all the received messages
 */
-(CAMReturnArray *)getMessages;

/*!
 @method     getConnectionStates;
 @abstract   Returns a dictionary with peer name as a key and the connection states it went through as the value
 */
-(CAMReturnDictionary *)getConnectionStates;

/*!
 @method     disconnectFromSession;
 @abstract   Disconnects peer from session
 */
-(CAMReturnVoid *)disconnectFromSession;

/*!
 @method     getResourcesLocation;
 @abstract   Returns an array with the received resources locations
 */
-(CAMReturnArray *)getResourcesLocation;

/*!
 @method     getHistory;
 @abstract   Returns an array with the history of events
 */
-(CAMReturnArray *)getHistory;

/*!
 @method     getPeerID;
 @abstract   Returns the MCPeerID display name
 */
-(CAMReturnString *)getPeerID;

@end
