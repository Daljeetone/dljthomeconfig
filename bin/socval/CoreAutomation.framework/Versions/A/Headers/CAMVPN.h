//
//  CAMVPN.h
//  CoreAutomation
//
//  Created by Chris Whitney on 2/14/12.
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CAMReturnValues.h"

#define kCAMVPNShortName VPN

// VPN Keys
#define kCAMVPNNameKey @"name"
#define kCAMVPNTypeKey @"type"

@protocol CAMVPN
@optional

- (CAMReturnArray*)networks;
- (CAMReturnInteger*)stateOfNetworkNamed:(NSString*)name;
- (CAMReturnVoid*)startNetworkNamed:(NSString*)name;
- (CAMReturnVoid*)stopNetworkNamed:(NSString*)name;

@end
