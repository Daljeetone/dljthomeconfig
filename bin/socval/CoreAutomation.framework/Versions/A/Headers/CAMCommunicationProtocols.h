//
//  CAMXPCProtocols.h
//  CoreAutomation
//
//  Created by Chen Huang on 5/16/14.
//
//

#import <Foundation/Foundation.h>
#import <Foundation/NSXPCConnection.h>
#import "CAMReturnValues.h"

@protocol CAMXPCProtocols <NSObject>
- (void)performCommandFromClass:(NSString*)classPath method:(NSString*)classMethod arguments:(NSArray*)args reply:(void (^)(CAMReturn * response))reply;

- (void)xpcEndpointsForLoggedInUsersWithReply:(void (^)(NSArray<NSXPCListenerEndpoint *> *endpoints))reply;
- (void)xpcEndpointForCurrentUserWithReply:(void (^)(NSXPCListenerEndpoint *endpoint))reply;

@end

@protocol CAMCommunicationProtocols <NSObject>
- (id)performCommandFromClass:(NSString*)classPath method:(NSString*)classMethod arguments:(NSArray*)args error:(NSError**)commandError;
- (NSDictionary*)performCommandDictionary:(NSDictionary*)request;
@end
