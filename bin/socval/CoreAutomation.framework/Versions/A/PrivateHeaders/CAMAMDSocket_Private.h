//
//  CAMAMDSocket_Private.h
//  CoreAutomation
//
//  Created by Chen Huang on 9/24/15.
//
//

#ifndef CAMAMDSocket_Private_h
#define CAMAMDSocket_Private_h

@interface CAMAMDSocket()

- (CAMAMDServiceConnection *)copyServiceConnection;

@property (retain, readwrite) CAMAMDServiceConnection *service_connection;
@property (retain, readwrite) CAMAMDLockdownService *lockdown_service;
@property (copy, readwrite) NSString *service_name;

@end


#endif /* CAMAMDSocket_Private_h */
