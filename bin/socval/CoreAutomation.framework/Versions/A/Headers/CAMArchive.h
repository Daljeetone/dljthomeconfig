//
//  CAMArchive.h
//  CoreAutomation
//
//  Created by Sahel Jalal on 4/14/13.
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CAMReturnValues.h"

#define kCAMArchiveShortName archive

// Archive method return dictionary keys
#define kCAMArchiveSucceededKey         @"archive-succeeded"
#define kCAMArchiveIdentifierKey        @"archive-identifier"
#define kCAMArchivePathKey              @"archive-path"
#define kCAMArchiveNameKey              @"archive-name"
#define kCAMArchiveTypeKey              @"archive-type"
#define kCAMArchiveCompressedSizeKey    @"archive-compressed-size"
#define kCAMArchiveUncompressedSizeKey  @"archive-uncompressed-size"
#define kCAMArchiveCompressionRatioKey  @"archive-compression-ratio"
#define kCAMArchiveFilesKey             @"archive-files"
#define kCAMArchiveFoldersKey           @"archive-folders"
#define kCAMArchiveErrorsKey            @"archive-errors"
#define kCAMArchiveFileCreated          @"archive-file-created"

typedef NS_ENUM(NSInteger, ArchiveType) {
    kCAMArchiveTypeNone = 0,
    kCAMArchiveTypeGzip,   // default
    kCAMArchiveTypeBzip2
} ;

@protocol CAMArchive
@optional

/*
 @method archiveFilesAtPath:
 @abstract Create an archive of all files and folders at given path.
 @discussion Uses default compression type of gzip with max uncompressed size of 1GB. Archive name is a dynamically generated UUID with compression extension.
 @return Returns a dictionary with relevant archive information, including whether the archive was created successfully.
 */
- (CAMReturnDictionary *)archiveFilesAtPath:(NSString *)path;

/*
 @method archiveFilesAtPath:withArchiveType:
 @abstract Create an archive of all files and folders at given path.
 @discussion Uses supplied compression type with max uncompressed size of 1GB. Archive name is a dynamically generated UUID with compression extension.
 @return Returns a dictionary with relevant archive information, including whether the archive was created successfully.
 */
- (CAMReturnDictionary *)archiveFilesAtPath:(NSString *)path withArchiveType:(NSNumber *)type;

/*
 @method archiveFilesAtPath:withArchiveName:
 @abstract Create an archive of all files and folders at given path.
 @discussion Uses default compression type of gzip with max uncompressed size of 1GB. Creates archive with the name that is supplied.
 @return Returns a dictionary with relevant archive information, including whether the archive was created successfully.
 */
- (CAMReturnDictionary *)archiveFilesAtPath:(NSString *)path withArchiveName:(NSString *)name;

/*
 @method archiveFilesAtPath:withMaxUncompressedSize:
 @abstract Create an archive of all files and folders at given path.
 @discussion Uses default compression type of gzip with max uncompressed size as supplied. Archive name is a dynamically generated UUID with compression extension.
 @return Returns a dictionary with relevant archive information, including whether the archive was created successfully.
 */
- (CAMReturnDictionary *)archiveFilesAtPath:(NSString *)path withMaxUncompressedSize:(NSNumber *)size;

/*
 @method archiveFilesAtPath:withArchiveType:withArchiveName:
 @abstract Create an archive of all files and folders at given path.
 @discussion Uses supplied compression type with max uncompressed size of 1GB. Creates archive with the name that is supplied.
 @return Returns a dictionary with relevant archive information, including whether the archive was created successfully.
 */
- (CAMReturnDictionary *)archiveFilesAtPath:(NSString *)path withArchiveType:(NSNumber *)type withArchiveName:(NSString *)name;

/*
 @method archiveFilesAtPath:withArchiveType:withMaxUncompressedSize:
 @abstract Create an archive of all files and folders at given path.
 @discussion Uses supplied compression type with max uncompressed size as supplied. Archive name is a dynamically generated UUID with compression extension.
 @return Returns a dictionary with relevant archive information, including whether the archive was created successfully.
 */
- (CAMReturnDictionary *)archiveFilesAtPath:(NSString *)path withArchiveType:(NSNumber *)type withMaxUncompressedSize:(NSNumber *)size;

/*
 @method archiveFilesAtPath:withArchiveName:withMaxUncompressedSize:
 @abstract Create an archive of all files and folders at given path.
 @discussion Uses default compression type of gzip with max uncompressed size as supplied. Creates archive with the name that is supplied.
 @return Returns a dictionary with relevant archive information, including whether the archive was created successfully.
 */
- (CAMReturnDictionary *)archiveFilesAtPath:(NSString *)path withArchiveName:(NSString *)name withMaxUncompressedSize:(NSNumber *)size;

/*
 @method archiveFilesAtPath:withArchiveType:withArchiveName:withMaxUncompressedSize:
 @abstract Create an archive of all files and folders at given path.
 @discussion Uses supplied compression type with max uncompressed size as supplied. Creates archive with the name that is supplied.
 @return Returns a dictionary with relevant archive information, including whether the archive was created successfully.
 */
- (CAMReturnDictionary *)archiveFilesAtPath:(NSString *)path withArchiveType:(NSNumber *)type withArchiveName:(NSString *)name withMaxUncompressedSize:(NSNumber *)size;

/*
 @method archiveFiles:
 @abstract Create an archive of all files and folders in given array.
 @discussion Uses default compression type of gzip with max uncompressed size of 1GB. Archive name is a dynamically generated UUID with compression extension.
 @return Returns a dictionary with relevant archive information, including whether the archive was created successfully.
 */
- (CAMReturnDictionary *)archiveFiles:(NSArray *)files;

/*
 @method archiveFiles:withArchiveType:
 @abstract Create an archive of all files and folders in given array.
 @discussion Uses supplied compression type with max uncompressed size of 1GB. Archive name is a dynamically generated UUID with compression extension.
 @return Returns a dictionary with relevant archive information, including whether the archive was created successfully.
 */
- (CAMReturnDictionary *)archiveFiles:(NSArray *)files withArchiveType:(NSNumber *)type;

/*
 @method archiveFiles:withArchiveName:
 @abstract Create an archive of all files and folders in given array.
 @discussion Uses default compression type of gzip with max uncompressed size of 1GB. Creates archive with the name that is supplied.
 @return Returns a dictionary with relevant archive information, including whether the archive was created successfully.
 */
- (CAMReturnDictionary *)archiveFiles:(NSArray *)files withArchiveName:(NSString *)name;

/*
 @method archiveFiles:withMaxUncompressedSize:
 @abstract Create an archive of all files and folders in given array.
 @discussion Uses default compression type of gzip with max uncompressed size as supplied. Archive name is a dynamically generated UUID with compression extension.
 @return Returns a dictionary with relevant archive information, including whether the archive was created successfully.
 */
- (CAMReturnDictionary *)archiveFiles:(NSArray *)files withMaxUncompressedSize:(NSNumber *)size;

/*
 @method archiveFiles:withArchiveType:withArchiveName:
 @abstract Create an archive of all files and folders in given array.
 @discussion Uses supplied compression type with max uncompressed size of 1GB. Creates archive with the name that is supplied.
 @return Returns a dictionary with relevant archive information, including whether the archive was created successfully.
 */
- (CAMReturnDictionary *)archiveFiles:(NSArray *)files withArchiveType:(NSNumber *)type  withArchiveName:(NSString *)name;

/*
 @method archiveFiles:withArchiveType:withMaxUncompressedSize:
 @abstract Create an archive of all files and folders in given array.
 @discussion Uses supplied compression type with max uncompressed size as supplied. Archive name is a dynamically generated UUID with compression extension.
 @return Returns a dictionary with relevant archive information, including whether the archive was created successfully.
 */
- (CAMReturnDictionary *)archiveFiles:(NSArray *)files withArchiveType:(NSNumber *)type  withMaxUncompressedSize:(NSNumber *)size;

/*
 @method archiveFiles:withArchiveName:withMaxUncompressedSize:
 @abstract Create an archive of all files and folders in given array.
 @discussion Uses default compression type of gzip with max uncompressed size as supplied. Creates archive with the name that is supplied.
 @return Returns a dictionary with relevant archive information, including whether the archive was created successfully.
 */
- (CAMReturnDictionary *)archiveFiles:(NSArray *)files withArchiveName:(NSString *)name withMaxUncompressedSize:(NSNumber *)size;

/*
 @method archiveFiles:withArchiveType:withArchiveName:withMaxUncompressedSize:
 @abstract Create an archive of all files and folders in given array.
 @discussion Uses supplied compression type with max uncompressed size as supplied. Creates archive with the name that is supplied.
 @return Returns a dictionary with relevant archive information, including whether the archive was created successfully.
 */
- (CAMReturnDictionary *)archiveFiles:(NSArray *)files withArchiveType:(NSNumber *)type  withArchiveName:(NSString *)name withMaxUncompressedSize:(NSNumber *)size;

/*
 @method archiveFiles:withArchiveType:withArchiveName:withMaxUncompressedSize:
 @abstract Create an archive of all files and folders in given array.  Allows for flattening of folder structure within folders.
 @discussion Uses supplied compression type with max uncompressed size as supplied. Creates archive with the name that is supplied.
 @return Returns a dictionary with relevant archive information, including whether the archive was created successfully.
 */
- (CAMReturnDictionary *)archiveFiles:(NSArray *)files withArchiveType:(NSNumber *)type  withArchiveName:(NSString *)name withMaxUncompressedSize:(NSNumber *)size shouldFlatten:(NSNumber *)shouldFlatten;

/*
 @method archiveFileSets:
 @abstract Create an archive with directories for each given dictionary key containing files and folders in the associated arrays.
 @discussion Uses default compression type of gzip with max uncompressed size of 1GB. Archive name is a dynamically generated UUID with compression extension. The file sets are arrays of files/folders for different dictionary keys. This allows for creating an archive with multiple top level folders for those keys that include the associated data.
 @return Returns a dictionary with relevant archive information, including whether the archive was created successfully.
 */
- (CAMReturnDictionary *)archiveFileSets:(NSDictionary *)fileSets;

/*
 @method archiveFileSets:withArchiveType:
 @abstract Create an archive with directories for each given dictionary key containing files and folders in the associated arrays.
 @discussion Uses supplied compression type with max uncompressed size of 1GB. Archive name is a dynamically generated UUID with compression extension. The file sets are arrays of files/folders for different dictionary keys. This allows for creating an archive with multiple top level folders for those keys that include the associated data.
 @return Returns a dictionary with relevant archive information, including whether the archive was created successfully.
 */
- (CAMReturnDictionary *)archiveFileSets:(NSDictionary *)fileSets withArchiveType:(NSNumber *)type;

/*
 @method archiveFileSets:withArchiveName:
 @abstract Create an archive with directories for each given dictionary key containing files and folders in the associated arrays.
 @discussion Uses default compression type of gzip with max uncompressed size of 1GB. Creates archive with the name that is supplied. The file sets are arrays of files/folders for different dictionary keys. This allows for creating an archive with multiple top level folders for those keys that include the associated data.
 @return Returns a dictionary with relevant archive information, including whether the archive was created successfully.
 */
- (CAMReturnDictionary *)archiveFileSets:(NSDictionary *)fileSets withArchiveName:(NSString *)name;

/*
 @method archiveFileSets:withMaxUncompressedSize:
 @abstract Create an archive with directories for each given dictionary key containing files and folders in the associated arrays.
 @discussion Uses default compression type of gzip with max uncompressed size as supplied. Archive name is a dynamically generated UUID with compression extension. The file sets are arrays of files/folders for different dictionary keys. This allows for creating an archive with multiple top level folders for those keys that include the associated data.
 @return Returns a dictionary with relevant archive information, including whether the archive was created successfully.
 */
- (CAMReturnDictionary *)archiveFileSets:(NSDictionary *)fileSets withMaxUncompressedSize:(NSNumber *)size;

/*
 @method archiveFileSets:withArchiveType:withArchiveName:
 @abstract Create an archive with directories for each given dictionary key containing files and folders in the associated arrays.
 @discussion Uses supplied compression type with max uncompressed size of 1GB. Creates archive with the name that is supplied. The file sets are arrays of files/folders for different dictionary keys. This allows for creating an archive with multiple top level folders for those keys that include the associated data.
 @return Returns a dictionary with relevant archive information, including whether the archive was created successfully.
 */
- (CAMReturnDictionary *)archiveFileSets:(NSDictionary *)fileSets withArchiveType:(NSNumber *)type withArchiveName:(NSString *)name;

/*
 @method archiveFileSets:withArchiveType:withMaxUncompressedSize:
 @abstract Create an archive with directories for each given dictionary key containing files and folders in the associated arrays.
 @discussion Uses supplied compression type with max uncompressed size as supplied. Archive name is a dynamically generated UUID with compression extension. The file sets are arrays of files/folders for different dictionary keys. This allows for creating an archive with multiple top level folders for those keys that include the associated data.
 @return Returns a dictionary with relevant archive information, including whether the archive was created successfully.
 */
- (CAMReturnDictionary *)archiveFileSets:(NSDictionary *)fileSets withArchiveType:(NSNumber *)type withMaxUncompressedSize:(NSNumber *)size;

/*
 @method archiveFileSets:withArchiveName:withMaxUncompressedSize:
 @abstract Create an archive with directories for each given dictionary key containing files and folders in the associated arrays.
 @discussion Uses default compression type of gzip with max uncompressed size as supplied. Creates archive with the name that is supplied. The file sets are arrays of files/folders for different dictionary keys. This allows for creating an archive with multiple top level folders for those keys that include the associated data.
 @return Returns a dictionary with relevant archive information, including whether the archive was created successfully.
 */
- (CAMReturnDictionary *)archiveFileSets:(NSDictionary *)fileSets withArchiveName:(NSString *)name withMaxUncompressedSize:(NSNumber *)size;

/*
 @method archiveFileSets:withArchiveType:withArchiveName:withMaxUncompressedSize:
 @abstract Create an archive with directories for each given dictionary key containing files and folders in the associated arrays.
 @discussion Uses supplied compression type with max uncompressed size as supplied. Creates archive with the name that is supplied. The file sets are arrays of files/folders for different dictionary keys. This allows for creating an archive with multiple top level folders for those keys that include the associated data.
 @return Returns a dictionary with relevant archive information, including whether the archive was created successfully.
 */
- (CAMReturnDictionary *)archiveFileSets:(NSDictionary *)fileSets withArchiveType:(NSNumber *)type withArchiveName:(NSString *)name withMaxUncompressedSize:(NSNumber *)size;

/*
 @method archiveFileSets:withArchiveType:withArchiveName:withMaxUncompressedSize:
 @abstract Create an archive with directories for each given dictionary key containing files and folders in the associated arrays. Allows for flattening of folder structure within folders.
 @discussion Uses supplied compression type with max uncompressed size as supplied. Creates archive with the name that is supplied. The file sets are arrays of files/folders for different dictionary keys. This allows for creating an archive with multiple top level folders for those keys that include the associated data.
 @return Returns a dictionary with relevant archive information, including whether the archive was created successfully.
 */
- (CAMReturnDictionary *)archiveFileSets:(NSDictionary *)fileSets withArchiveType:(NSNumber *)type withArchiveName:(NSString *)name withMaxUncompressedSize:(NSNumber *)size shouldFlatten:(NSNumber *)shouldFlatten;

/*
 @method archiveFileSets:withArchiveType:withArchiveName:withMaxUncompressedSize:
 @abstract Create an archive with directories for each given dictionary key containing files and folders in the associated arrays. Allows for flattening of folder structure within folders and an array of paths to strip out of the final archived structure.  For example, if pathsToStrip contains "/a/b/c", any files that contain these paths will have them removed in the final archived product.
 @discussion Uses supplied compression type with max uncompressed size as supplied. Creates archive with the name that is supplied. The file sets are arrays of files/folders for different dictionary keys. This allows for creating an archive with multiple top level folders for those keys that include the associated data.
 @return Returns a dictionary with relevant archive information, including whether the archive was created successfully.
 */
- (CAMReturnDictionary *)archiveFileSets:(NSDictionary *)fileSets withArchiveType:(NSNumber *)type withArchiveName:(NSString *)name withMaxUncompressedSize:(NSNumber *)size shouldFlatten:(NSNumber *)shouldFlatten pathsToStrip:(NSArray *)pathsToStrip;
@end
