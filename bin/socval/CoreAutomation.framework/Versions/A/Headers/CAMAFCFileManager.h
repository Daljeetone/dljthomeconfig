//
//  CAMAFCFileManager.h
//  CoreAutomation
//
//  Created by Matt Massicotte on 4/13/10.
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <MobileDevice/AFCClient.h>

#define kCAMAFCConnectionTimeout 5
#define kCAMAFCDefaultIOSize     32768 // taken from afctool.m

// This class mirrors NSFileManager, so it can be use polymorphically to interact with a remote AFC file system

/*! 
 @interface CAMAFCFileManager
 @discussion Service to AFC for file transfers.
 */
@interface CAMAFCFileManager : NSObject
{
    AFCConnectionRef afcConnectionRef;
}

/*! 
 @method initWithAFCConnectionRef
 @discussion Initialize with AFC reference.
 @param ref
	AFC reference.
 */
- (id)initWithAFCConnectionRef:(AFCConnectionRef)ref;

/*! 
 @method contentsOfDirectoryAtPath
 @discussion Get the contents of a directory at path specified.
 @param path
	Path to directory.
 @param error
	Error code.
 @result
	Directory contents in an NSArray.
 */
- (NSArray *)contentsOfDirectoryAtPath:(NSString *)path error:(NSError **)error;

/*! 
 @method attributesOfItemAtPath
 @discussion Gets the file attributes of the item specified in the path.
 @param path
	Path of the item to get info on.
 @param error
	Error code.
 @result
	Attributes returned in an NSDictionary.
 */
- (NSDictionary *)attributesOfItemAtPath:(NSString *)path error:(NSError **)error;

/*! 
 @method destinationOfSymbolicLinkAtPath
 @discussion Gets the destination pointed to for a symbolic link.
 @param path
	Path to the symlink.
 @param error
	Returned error.
 @result
	Destination of the symbolic link.
 */
- (NSString *)destinationOfSymbolicLinkAtPath:(NSString *)path error:(NSError **)error;

/*! 
 @method createDirectoryAtPath
 @discussion Creates a directory.
 @param path
	Path to the directory to create.
 @param createIntermediates
	BOOL to specify if you should create the intermediates.
 @param attributes
	Attributes to apply to the newly created directory.
 @param error
	Error code.
 @result
	YES or NO depending on success.
 */
- (BOOL)createDirectoryAtPath:(NSString *)path withIntermediateDirectories:(BOOL)createIntermediates attributes:(NSDictionary *)attributes error:(NSError **)error;

/*! 
 @method createSymbolicLinkAtPath
 @discussion Creates a symbolic link at the path specified.
 @param path
	Path to symlink
 @param destPath
	Destination for symlink to point.
 @param error
	Error code.
 @result
	YES or NO depending on success.
 */
- (BOOL)createSymbolicLinkAtPath:(NSString *)path withDestinationPath:(NSString *)destPath error:(NSError **)error;

/*! 
 @method createFileAtPath
 @discussion Creates a file at the given path.
 @param path
	Path to create a file.
 @param data
	Contents of the new file.
 @param attr
	Attributes on the new file.
 @result
	YES or NO.
 */
- (BOOL)createFileAtPath:(NSString *)path contents:(NSData *)data attributes:(NSDictionary *)attr;

/*! 
 @method moveItemAtPath
 @discussion Moves an item to path specified.
 @param srcPath
	Path of the source item to move.
 @param dstPath
	Path of the destination.
 @param error
	Error code.
 @result
	YES or NO.
 */
- (BOOL)moveItemAtPath:(NSString *)srcPath toPath:(NSString *)dstPath error:(NSError **)error;

/*! 
 @method removeItemAtPath
 @discussion Removes the item at the path specified.
 @param path
	Item to remove.
 @param error
	Error code.
 @result
	YES or NO based on success.
 */
- (BOOL)removeItemAtPath:(NSString *)path error:(NSError **)error;

/*! 
 @method openRemoteFile
 @discussion Opens the remote file.
 @param path
	Path to file.
 @param mode
	Mode to open file with.
 @param error
	Error code.
 @param block
	Block to handle when the file is opened.
 @result
	YES or NO based on success.
 */
- (BOOL)openRemoteFile:(NSString*)path withMode:(CFIndex)mode error:(NSError **)error usingBlock:(void (^)(AFCFileDescriptorRef))block;

@end
