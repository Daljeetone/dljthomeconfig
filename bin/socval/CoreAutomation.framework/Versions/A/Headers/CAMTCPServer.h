//
//  CAMTCPServer.h
//  CoreAutomation
//
//  Created by Matt Massicotte on 6/13/10.
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "CAMIPServer.h"

#import <openssl/ssl.h>
#import <openssl/ossl_typ.h>

@protocol CAMTCPServerDelegate;
@class CAMTCPConnection;

/*!
 @class CAMTCPServer
 */
@interface CAMTCPServer : NSObject <CAMIPServer>
{
    @private
    BOOL useSSL;
    SSL_CTX *ctx;
    SSL *ssl;
    
    BIO *bio_err;
    
    NSString *sslKeyfile;
    NSString *sslPassword;
    NSString *sslDHFile;
    NSString *sslCAList;
    
    uint16_t v4Port;
    uint16_t v6Port;
    
    dispatch_queue_t  requestQueue;
    dispatch_source_t v4SocketSource;
    
    id <CAMTCPServerDelegate> __unsafe_unretained delegate;
}

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
 @property delegate
 */
@property (unsafe_unretained) id <CAMTCPServerDelegate> delegate;

- (ssize_t)readFromSocket:(int)socket intoBuffer:(void *)buffer ofMaxLength:(size_t)length;
- (ssize_t)writeToSocket:(int)socket fromBuffer:(const void *)buffer ofLength:(size_t)length;

@end

/*!
 @protocol CAMTCPServerDelegate
 */
@protocol CAMTCPServerDelegate <NSObject>

/*!
 @method tcpServer
 */
- (void)tcpServer:(CAMTCPServer *)server acceptedConnectionOnSocket:(int)socket;

@end