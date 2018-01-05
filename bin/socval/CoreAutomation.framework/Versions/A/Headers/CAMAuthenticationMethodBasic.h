//
//  CAMAuthenticationMethodBasic.h
//  CoreAutomation
//
//  Created by David Rix Nelson on 10/15/10.
//  Copyright 2010 Apple Computer. All rights reserved.
//

#import "CAMAuthenticationMethod.h"


/*!
 @interface CAMAuthenticationMethodBasic
 @discussion CAM method for authentication.
 */
@interface CAMAuthenticationMethodBasic : CAMAuthenticationMethod {

}

/*!
 @method initWithHTTPAuthorizationHeader
 @discussion Initializer for HTTP authorization header.
 @param authorizationHeader
	Authorization header to initialize with.
 */
-(id)initWithHTTPAuthorizationHeader:(NSString *)authorizationHeader;

@end
