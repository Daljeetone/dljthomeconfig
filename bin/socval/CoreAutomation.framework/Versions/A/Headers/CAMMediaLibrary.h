//
//  CAMMediaLibrary.h
//  coreautomationd
//
//  Created by Jude Prakash on 10/4/13.
//
//

#import <Foundation/Foundation.h>

#import "CAMReturnValues.h"

#define kCAMMediaLibraryShortName mediaLibrary

typedef NS_ENUM(NSInteger, CAMMediaLibraryType) {
	kMediaLibraryTypeDeviceLibrary,
    kMediaLibraryTypeiTunesRadioLibrary,
    kMediaLibraryTypeDeviceUnknownLibrary
} ;

@protocol CAMMediaLibrary

@optional

/*!
 @method     mediaLibraryInformation
 @abstract   Returns information about the media libraries on the device. This includes local device library, home shared libraries and Radio library.
 */
- (CAMReturnArray*)mediaLibraryInformation;

@end
