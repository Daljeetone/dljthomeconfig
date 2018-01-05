//
//  CAMIONotification.h
//  CoreAutomation
//
//  Created by Matt Massicotte on 3/14/10.
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>

/*!
 @interface CAMIONotification
 @discussion IO Notification.
 */
@interface CAMIONotification : NSObject {
    IONotificationPortRef notifyPort;
    CFRunLoopSourceRef runLoopSource;
    io_iterator_t iterator;
    void (^observerBlock)(io_iterator_t);
}

/*!
 @method observeName
 @discussion Handler when receiving an IO notification.
 @param name
	IO name.
 @param matchingDict
	Dictionary matching the IO we're looking for.
 @param block
	Block to perform handler.
 */
- (void)observeName:(const io_name_t)name matchingDict:(NSDictionary *)matchingDict usingBlock:(void (^)(io_iterator_t))block;

@end
