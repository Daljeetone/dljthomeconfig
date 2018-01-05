//
//  CAMHTTPRoute.h
//  CoreAutomation
//
//  Created by Matt Massicotte on 10/20/10.
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CAMHTTPRequest.h"

/*!
 @class CAMHTTPRoute
 @discussion HTTP route.
 */
@interface CAMHTTPRoute : NSObject
{
    CAMHTTPRequestMethod method;
    NSArray*             urlComponents;
}

/*!
 @property method
 @discussion HTTP request method.
 */
@property (assign, readonly) CAMHTTPRequestMethod method;

/*!
 @property urlComponents
 @discussion URL components.
 */
@property (strong, readonly) NSArray*             urlComponents;

/*!
 @method aMethod
 @discussion Initialize method for HTTP request.
 @param aMethod
	The method to use.
 @param urlPattern
	URL pattern.
 */
- (id)initWithMethod:(CAMHTTPRequestMethod)aMethod andURLPattern:(NSString*)urlPattern;

/*!
 @method matchesURLComponents
 @discussion Mathes the URL components.
 @param components
	URL components.
 @result
	YES if it mathes and NO if it does not.
 */
- (BOOL)matchesURLComponents:(NSArray*)components;

@end
