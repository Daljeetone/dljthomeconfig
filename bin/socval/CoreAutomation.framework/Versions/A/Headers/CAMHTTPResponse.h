//
//  CAMHTTPResponse.h
//  CoreAutomation
//
//  Created by Matt Massicotte on 6/13/10.
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>

/*!
 @interface CAMHTTPResponse
 @discussion Interface for HTTP response.
 */
@interface CAMHTTPResponse : NSObject
{
    CFHTTPMessageRef messageRef;
}

/*!
 @property body
 @discussion HTTP response body.
 */
@property (copy) NSData* body;

/*!
 @property messageRef
 @discussion HTTP response message reference.
 */
@property (assign, readonly) CFHTTPMessageRef     messageRef;

/*!
 @method responseWithCode
 @discussion HTTP response code.
 */
+ (instancetype)responseWithCode:(NSUInteger)httpResponseCode;

/*!
 @method initWithCode
 @discussion Initialize a HTTP response with a code.
 */
- (instancetype)initWithCode:(NSUInteger)httpResponseCode;

/*!
 @method setValue
 @discussion Set value of an HTTP response.
 */
- (void)setValue:(NSString*)value forHeaderField:(NSString*)field;

/*!
 @property serializedData
 @discussion Get serialized data for HTTP response.
 */
@property (NS_NONATOMIC_IOSONLY, readonly, copy) NSData *serializedData;

@end
