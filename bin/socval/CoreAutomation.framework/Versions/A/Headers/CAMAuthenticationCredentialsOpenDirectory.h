//
//  CAMAuthenticationCredentialsOpenDirectory.h
//  CoreAutomation
//
//  Created by David Rix Nelson on 10/15/10.
//  Copyright 2010 Apple Computer. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "CAMAuthenticationCredentials.h"


/*!
 @interface CAMAuthenticationCredentialsOpenDirectory
 @discussion Interface for authentication credentials for Open Directory.
 */
@interface CAMAuthenticationCredentialsOpenDirectory : CAMAuthenticationCredentials {
    NSString *nodeName;
    NSArray *groups;

}

/*!
 @method initWithNodeName
 @discussion Initialize with the node name.
 */
-(id)initWithNodeName:(NSString *)name;

/*!
 @property nodeName
 @discussion Node name property.
 */
@property (copy) NSString *nodeName;

/*!
 @property groups
 @discussion Array of groups for Open Directory.
 */
@property (strong) NSArray *groups;
@end
