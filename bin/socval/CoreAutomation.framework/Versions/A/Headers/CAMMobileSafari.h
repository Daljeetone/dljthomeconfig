//
//  CAMMobileSafari.h
//  CoreAutomation
//
//  Created by Chris Whitney on 12/14/11.
//  Copyright (c) 2011 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CAMReturnValues.h"

#define kCAMMobileSafariShortName safari

@protocol CAMMobileSafari
@optional

/*!
 @method     deleteAllData
 @abstract   Delete all stored website data such as cookies, caches, and HTML5 databases.
 @discussion This is equivalent to Settings -> Safari -> Clear Cookies and Data.
 */
- (CAMReturnVoid*)deleteAllData;

@end
