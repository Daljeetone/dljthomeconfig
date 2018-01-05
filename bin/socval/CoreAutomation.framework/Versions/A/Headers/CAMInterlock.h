//
//  CAMInterlock.h
//  CoreAutomation
//
//  Created by Shannon Ma on 5/19/11.
//  Copyright 2011 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 @brief Interprocess lock.
*/
@interface CAMInterlock : NSObject
{
@private
    int fileDescriptor;
    NSString *filePath;
    NSLock *intraprocessLock;
}

/*!
 @brief Initializes the lock.
 @param path    Path to the file that will represent the lock.
 Do not create more than more than one instance (inside of the same process) of this class for a given file path. This class is also not a recursive lock: calling lock while holding the lock will cause a deadlock.
 */
- (instancetype)initWithPath:(NSString *)path;

/*!
 @brief Acquires the lock. This is a blocking call.
 */
- (void)lock;

/*!
 @brief Tries to acquire the lock. This is a non-blocking call.
 */
@property (NS_NONATOMIC_IOSONLY, readonly) BOOL tryLock;

/*!
 @brief Releases the lock. The lock will always be released on process exit.
 */
- (void)unlock;

@end
