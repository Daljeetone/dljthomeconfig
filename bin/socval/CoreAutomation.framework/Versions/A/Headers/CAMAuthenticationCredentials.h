//
//  CAMAuthenticationCredentials.h
//  CoreAutomation
//
//  Created by David Rix Nelson on 10/15/10.
//  Copyright 2010 Apple Computer. All rights reserved.
//

#import <Cocoa/Cocoa.h>

/*!
 @interface CAMAuthenticationCredentials
 @discussion This class is the base interface from which other authentication classes will be based.
 */
@interface CAMAuthenticationCredentials : NSObject {

}

/*!
 @method authenticateUsername
 @discussion Implement a basic user/password method to do authentication.
 */

-(BOOL)authenticateUsername:(NSString *)username withPassword:(NSString *)password;

@end
