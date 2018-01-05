//
//  CAMAuthenticator.h
//  CoreAutomation
//
//  Created by David Rix Nelson on 10/15/10.
//  Copyright 2010 Apple Computer. All rights reserved.
//

#import <Cocoa/Cocoa.h>

/*!
 @interface CAMAuthenticator
 @discussion The authenticator class is used to verify credentials.
 */
@interface CAMAuthenticator : NSObject {
    // Array of strings that corrispond to methods to encode authentication info
    NSArray *allowedAuthenticationMethods;
    
    // Array of CAMAuthenticationCredentials that are available to verify credentials
    NSArray *authenticationCredentials;
    
}

/*!
 @property allowedAuthenticationMethods
 @discussion Gets the authentication methods possible.
 */
@property (strong) NSArray *allowedAuthenticationMethods;

/*!
 @property authenticationCredentials
 @discussion NSArray of authentication credentials.
 */
@property (strong) NSArray *authenticationCredentials;

/*!
 @method defaultAuthenticator
 @discussion The default authenticator used.
 */
+(id)defaultAuthenticator;

/*!
 @method defaultLocalAuthenticator
 @discussion The local default authenticator used.
 */
+(id)defaultLocalAuthenticator;

/*!
 @method defaultAppleODAuthenticator
 @discussion The default Apple Open Directory authenticator.
 */
+(id)defaultAppleODAuthenticator;

/*!
 @method authenticateWithHTTPAuthorizationHeader
 @discussion Authenticates using HTTP authorization header.
 @param authorizationHeader
	Authorization header.
 @result
	YES if the credentials authenticate
	NO if the credentials do not authenticate
 */

-(BOOL)authenticateWithHTTPAuthorizationHeader:(NSString *)authorizationHeader;

/*!
 @method isAllowedAuthenticationMethod
 @discussion This method returns if the authentication method is allowed or not.
 @param method
	Method to check.
 @result
	YES if allowed and NO if not allowed.
 */
-(BOOL)isAllowedAuthenticationMethod:(NSString *)method;


@end
