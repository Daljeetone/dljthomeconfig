//
//  CAMAuthenticationMethod.h
//  CoreAutomation
//
//  Created by David Rix Nelson on 10/15/10.
//  Copyright 2010 Apple Computer. All rights reserved.
//

#import <Cocoa/Cocoa.h>

/*!
 @interface CAMAuthenticationMethod
 @discussion This class represents the actual mechanism by which to authenticate.  
 */
@interface CAMAuthenticationMethod : NSObject {
    NSString *username;
    NSString *password;
}

/*!
 @property username
 @discussion Username to use in authentication.
 */
@property (copy) NSString *username;

/*!
 @property password
 @discussion Password to use in authentication.
 */
@property (copy) NSString *password;


/*!
 @method authenticationMethodFor
 @discussion Uses authentication for specified method.
 @param method
	Method to use to authenticate.
 @param authorizationHeader
	Header to use to authorize.
 */
+(id)authenticationMethodFor:(NSString *)method withHTTPAuthorizationHeader:(NSString *)authorizationHeader;
@end
