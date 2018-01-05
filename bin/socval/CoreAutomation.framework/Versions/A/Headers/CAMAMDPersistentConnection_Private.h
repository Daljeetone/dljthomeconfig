//
//  CAMAMDPersistentConnection_Private.h
//  CoreAutomation
//
//  Created by Chen Huang on 10/15/15.
//
//

#ifndef CAMAMDPersistentConnection_Private_h
#define CAMAMDPersistentConnection_Private_h

#import "CAMAMDPersistentConnection.h"
#import "CAMSocket.h"
#import "CAMAMDSocket.h"

// The following two items is for saving corrupted plist.
extern NSString * const kCoreAutomationDefaultsDomain;
extern NSString * const kCoreAutomationSaveCorruptPlistsKey;



@interface CAMAMDPersistentConnection()
{
    @public
    dispatch_queue_t    delegateIOQueue;
    NSCondition         *responseCondition;
}
@property (readwrite, atomic, assign) AMDeviceRef device;
@property (readwrite, atomic, copy) NSString *service_name;
@property (readwrite, retain) CAMSocket * cam_socket;
@property (readwrite, atomic, retain) NSMutableData *dataFragements;
@property (readwrite, retain) NSArray *response;

- (NSArray *)composePlist:(NSData *)data;
- (void)processDataFragments;
- (BOOL)isDataCommandResponse:(NSData *)data;

@end


#endif /* CAMAMDPersistentConnection_Private_h */
