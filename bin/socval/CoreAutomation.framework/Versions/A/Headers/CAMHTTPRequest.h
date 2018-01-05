//
//  CAMHTTPRequest.h
//  CoreAutomation
//
//  Created by Matt Massicotte on 6/13/10.
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>

/*!
 @enum _CAMHTTPRequestMethod
 @discussion HTTP request method.
 */
enum _CAMHTTPRequestMethod
{
    CAMHTTPRequestMethodUnknown = 0,
    CAMHTTPRequestMethodGet,
    CAMHTTPRequestMethodPut,
    CAMHTTPRequestMethodPost,
    CAMHTTPRequestMethodDelete
};
typedef enum _CAMHTTPRequestMethod CAMHTTPRequestMethod;

/*! 
 @interface CAMHTTPRequest
 @discussion HTTP request interface for CAM.
 */
@interface CAMHTTPRequest : NSObject
{
    CFHTTPMessageRef messageRef;
	NSHost *source;
    NSString *_ipAddress;
}

/*!
 @property messageRef
 @discussion Holds the message reference.
 */
@property (assign, readonly) CFHTTPMessageRef     messageRef;

/*!
 @property body
 @discussion NSData holds the body of your HTTP request.
 */
@property (copy,   readonly) NSData*              body;

/*!
 @property contentLength
 @discussion Content length of HTTP request.
 */
@property (weak, readonly) NSNumber*            contentLength;

/*!
 @property acceptType
 @discussion Returns value of HTTP request header field 'Accept' - http://www.w3.org/Protocols/rfc2616/rfc2616-sec14.html
 */
@property (weak, readonly) NSString*            acceptType;

/*!
 @property url
 @discussion URL of the HTTP request.
 */
@property (copy,   readonly) NSURL*               url;

/*!
 @property urlComponents
 @discussion URL components of HTTP request.
 */
@property (strong, readonly) NSArray*             urlComponents;

/*!
 @property requestMethod
 @discussion HTTP request method.
 */
@property (assign, readonly) CAMHTTPRequestMethod requestMethod;

/*!
 @property source
 @discussion Source of the HTTP request.
 */
@property (strong) NSHost *source;

/**
 @property ipAddress
 @discussion IP address of the source of the HTTP request
 */
@property (strong) NSString *ipAddress;

/**
 @discussion Converts CAMHTTPRequestMethod to HTTP verb string (GET, PUT, POST, DELETE, etc...)
 */
+ (NSString *)httpVerbFromEnum:(CAMHTTPRequestMethod)requestMethod;

@end
