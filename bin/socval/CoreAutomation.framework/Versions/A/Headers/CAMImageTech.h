//
//  CAMImageTech.h
//  coreautomationd
//
//  Created by David O'Leary on 2/17/17.
//
//

#import "CAMReturnValues.h"
#define kCAMImageTechShortName imageTech

@protocol CAMImageTech
@optional

/*!
 @method    currentSourcePath
 @return    Returns the path to the currently-retained CGImageSourceRef, if set.
 */
- (CAMReturnString *)currentSourcePath;

/*!
 @method    currentDestinationPath
 @return    Returns the path to the currently-retained CGImageDestinationRef, if set.
 */
- (CAMReturnString *)currentDestinationPath;

/*!
 @method    imageSourceProperties
 @return    Returns the properties dictionary from the currently-retained CGImageSourceRef, if present.
 */
- (CAMReturnDictionary *)imageSourceProperties;

/*!
 @method    setImageSourceProperties
 @abstract  Takes the passed-in disctionary and retains it as the currentMetadataProperties property.
 */
- (CAMReturnString *)setImageSourceProperties:(CFDictionaryRef)properties;

/*!
 @method    imageDestinationSetProperties
 @abstract  Adds the currently-retained medata properties dictionary to the destination, if present.
 */
- (CAMReturnDictionary *)imageDestinationSetProperties;

/*!
 @method    currentImageWidth
 @return    Returns the width of the currently-retained CGImageSourceRef, if present.
 */
- (CAMReturnInteger *)currentImageWidth;

/*!
 @method    currentImageHeight
 @return    Returns the height of the currently-retained CGImageSourceRef, if present.
 */
- (CAMReturnInteger *)currentImageHeight;

/*!
 @method    currentImageBitsPerComponent
 @return    Returns the bits per component of the currently-retained CGImageSourceRef, if present.
 */
- (CAMReturnInteger *)currentImageBitsPerComponent;

/*!
 @method    currentImageBitsPerPixel
 @return    Returns the bits per pixel of the currently-retained CGImageSourceRef, if present.
 */
- (CAMReturnInteger *)currentImageBitsPerPixel;

/*!
 @method    currentImageBytesPerRow
 @return    Returns the bytes per row of the currently-retained CGImageSourceRef, if present.
 */
- (CAMReturnInteger *)currentImageBytesPerRow;

/*!
 @method    extensionNameForUTI
 @return    Returns the file extension appropriate for the passed-in UTI.
 */
- (CAMReturnString *)extensionNameForUTI:(NSString *)utiString;

/*!
 @method    currentImageSourceGetCount
 @return    Returns the number of images stored in the image source file container. Returns -1 if image source is nil.
 */
- (CAMReturnInteger *)imageSourceGetCount;

/*!
 @method    imageSourceGetStatusAtIndex
 @return    Returns the current status of the image at `index' in the current image source. The index is zero-based. The returned status is particularly informative for incremental image sources but may used by clients providing non-incremental data as well.
 */
- (CAMReturnString *)imageSourceGetStatusAtIndex:(NSNumber *) indexNum;

/*!
 @method    imageSourceGetStatus
 @return    Returns the overall status of the image source `isrc'.  The status is particularly informative for incremental image sources, but may be used by clients providing non-incremental data as well.
 */
- (CAMReturnString *)imageSourceGetStatus;

/*!
 @method    addCurrentImageToDestination
 @abstract  Takes the currently-retained CGImageRef and adds it to the current destination.
 @return    Returns a positive double value for success indicating duration for the operation, or -1 for failure.
 */
- (CAMReturnDouble *)addCurrentImageToDestinationWithOptions:(NSDictionary*)options;

/*!
 @method    addImageFromSourceAtIndexToDestination
 @abstract  Take an image from current source at the given index and add it to the current destination. Image properties are not added to the destination in this method.
 @return    Returns a positive double value for success indicating duration for the operation, or -1 for failure.
 
 */
- (CAMReturnDouble *)addImageFromSourceAtIndexToDestination:(NSNumber *) indexNum;

/*!
 @method    finalizeCurrentDestination
 @abstract    Calls CGImageDestinationFinalize on the currently-retained CGImageDestinationRef, if set
 @return    Returns a positive double value for success indicating duration for the operation, or -1 for failure.
 */
- (CAMReturnDouble *)finalizeCurrentDestination;

/*!
 @method    checkFileSizeAtPath
 @abstract    Ensures that there is a file at the path, that it is a file and not a directory, and then returns the size of the file or an error.
 @return    Returns a positive integer value for success indicating size in bytes, or -1 for failure.
 */
- (CAMReturnInteger *)checkFileSizeAtPath:(NSString *)path;

/*!
 @method    imageSourceCopyTypeIdentifiers
 @return    Returns an array of the uniform type identifiers (UTIs) that are supported for image source.
 */
- (CAMReturnArray *)imageSourceCopyTypeIdentifiers;

/*!
 @method    imageDestinationCopyTypeIdentifiers
 @return    Returns an array of the uniform type identifiers (UTIs) that are supported for image destinations.
 */
- (CAMReturnArray *)imageDestinationCopyTypeIdentifiers;

/*!
 @method    imageSourceCreateThumbnailAtIndex
 @return    Return the image at `index' in the image source `isrc'. The index is zero-based. The `options' dictionary may be used to request additional creation options.
 */
- (CAMReturnDouble *)imageSourceCreateImageAtIndex:(NSNumber *) indexNum
                                           options:(NSDictionary *) options;

/*!
 @method    imageSourceCreateThumbnailAtIndex
 @return    Returns a thumbnail of the image at `index' in the current image source. The index is zero-based. The `options' dictionary may be used to request additional thumbnail creation options.
 */
- (CAMReturnDouble *)imageSourceCreateThumbnailAtIndex:(NSNumber *) indexNum
                                               maxSize:(NSNumber *) maxSize;
/*!
 @method    imageDestinationCreateWithURL
 @abstract  Create an image destination writing to `url'. The parameter `type' specifies the type identifier of the resulting image file.  The parameter `count' specifies number of images (not including thumbnails) that the image file will contain. The `options' dictionary is reserved  for future use; currently, you should pass NULL for this parameter. Note that if `url' already exists, it will be overwritten.
 @return    Returns the path for the image destination set.
 */
- (CAMReturnString *)imageDestinationCreateWithURL:(NSString *) path
                                              type:(NSString *) type
                                             count:(NSNumber *) countNum;

/*!
 @method    imageSourceCreateWithURL
 @abstract  Create an image source reading from `url'. The `options' dictionary may be used to request additional creation options.
 @return    Returns the path for the image source set.
 */
- (CAMReturnString *)imageSourceCreateWithURL:(NSString *) path
                                      options:(CFDictionaryRef) options;

@end
