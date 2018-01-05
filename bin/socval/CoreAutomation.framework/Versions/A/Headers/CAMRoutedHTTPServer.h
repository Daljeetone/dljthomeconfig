//
//  CAMRoutedHTTPServer.h
//  CoreAutomation
//
//  Created by Matt Massicotte on 10/20/10.
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CAMIPServer.h"
#import "CAMHTTPRequest.h"
#import "CAMLogger.h"

@class CAMHTTPServer;
@class CAMHTTPResponse;


/*!
 @class CAMRoutedHTTPServer
 */
@interface CAMRoutedHTTPServer : NSObject <CAMIPServer>
{
    CAMHTTPServer*  httpServer;
    
    NSMutableArray* routesArray;
    NSMutableArray* routeHandlersArray;
}


/*!
 @method handleUrlPattern
 */
- (void)handleUrlPattern:(NSString*)urlPattern usingMethod:(CAMHTTPRequestMethod)method withBlock:(CAMHTTPResponse* (^)(CAMHTTPRequest*))block;

/*!
 @method handleGet
 */
- (void)handleGet:(NSString*)urlPattern withBlock:(CAMHTTPResponse* (^)(CAMHTTPRequest*))block;

/*!
 @method handlePut
 */
- (void)handlePut:(NSString*)urlPattern withBlock:(CAMHTTPResponse* (^)(CAMHTTPRequest*))block;

/*!
 @method handlePost
 */
- (void)handlePost:(NSString*)urlPattern withBlock:(CAMHTTPResponse* (^)(CAMHTTPRequest*))block;

/*!
 @method handleDelete
 */
- (void)handleDelete:(NSString*)urlPattern withBlock:(CAMHTTPResponse* (^)(CAMHTTPRequest*))block;

/*!
 @method responseWithCode
 */
- (CAMHTTPResponse*)responseWithCode:(NSUInteger)code;

/*!
 @method respondWithPlist
 */
- (CAMHTTPResponse*)respondWithPlist:(id)plistObject;

/*!
 @method respondWithPlist:code:
 */
- (CAMHTTPResponse*)respondWithPlist:(id)plistObject code:(NSUInteger) code;


/*!
 @method respondWithJSON
 */
- (CAMHTTPResponse*)respondWithJSON:(id)jsonObject;


/*!
 @method respondWithJSON:code:
 */
- (CAMHTTPResponse*)respondWithJSON:(id)jsonObject code:(NSUInteger) code;


/*!
 @method respondWithObject
 @discussion Looks at HTTP request's Content-Type to determine how to respond. Defaults to respondWithPlist.
 */
- (CAMHTTPResponse*)respondWithObject:(id)object forRequest:(CAMHTTPRequest *)request;

/*!
 @method respondWithObject:code:forRequest:
 @discussion Looks at HTTP request's Content-Type to determine how to respond. Defaults to respondWithPlist.
 */
- (CAMHTTPResponse*)respondWithObject:(id)object code:(NSUInteger) code forRequest:(CAMHTTPRequest *)request;


@end
