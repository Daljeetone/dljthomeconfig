//
//  CAMHTTPServer.h
//  CoreAutomation
//
//  Created by Matt Massicotte on 6/13/10.
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CAMIPServer.h"

@protocol CAMHTTPServerDelegate;
@class CAMTCPServer;
@class CAMHTTPRequest, CAMHTTPResponse;
@class CAMAuthenticator;

/*!
 @class CAMHTTPServer
 */
@interface CAMHTTPServer : NSObject <CAMIPServer>
{
    @private
    BOOL isAuthenticationRequired;
    CAMAuthenticator *authenticator;
    
    CAMTCPServer* tcpServer;
    
    id <CAMHTTPServerDelegate> __unsafe_unretained delegate;
}

/*!
 @property isAuthenticationRequired
 */
@property () BOOL isAuthenticationRequired;

/*!
 @property useSSL
 */
@property () BOOL useSSL;

/*!
 @property sslKeyfile
 */
@property (copy) NSString *sslKeyfile;

/*!
 @property sslPassword
 */
@property (copy) NSString *sslPassword;

/*!
 @property sslDHFile
 */
@property (copy) NSString *sslDHFile;

/*!
 @property sslCAList
 */
@property (copy) NSString *sslCAList;

/*!
 @property authenticator
 */
@property (strong) CAMAuthenticator *authenticator;

/*!
 @property delegate
 */
@property (unsafe_unretained) id <CAMHTTPServerDelegate> delegate;

@end

/*!
 @protocol CAMHTTPServerDelegate
 */
@protocol CAMHTTPServerDelegate <NSObject>

- (CAMHTTPResponse *)httpServer:(CAMHTTPServer *)server responseForRequest:(CAMHTTPRequest *)request;

@end
