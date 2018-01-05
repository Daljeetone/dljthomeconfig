//
//  CAMXBSBuild.h
//  CoreAutomation
//
//  Created by Matt Massicotte on 3/6/10.
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>

extern NSString *const CAMXBSBuildMountRestoreImages;
extern NSString *const CAMXBSBuildMountSungoalRestoreImages;
extern NSString *const CAMXBSBuildMountMustang;
extern NSString *const CAMXBSBuildMountSungoalMustang;
extern NSString *const CAMXBSBuildUnmapped;

/*!
 @interface CAMXBSBuild
 @discussion Defines a CAM XBS build object.
 */
@interface CAMXBSBuild : NSObject

/*!
 @method initWithString
 @discussion Initializes a build with a string.
 @param string
	Full build string. (ex. Hoodoo9B179)
 */
- (instancetype)initWithString:(NSString *)string;

/*!
 @method initWithString
 @discussion Initializes a build with a string.
 @param string
	Full build string. (ex. Hoodoo9B179)
 @param mountKey
	Key used to mount to the AFP share.
 */
- (instancetype)initWithString:(NSString *)string atMount:(NSString *)mountKey;

/*!
 @method buildWithString
 @discussion Creates a CAM XBS build object.
 @param string
	Full build string. (ex. Hoodoo9B179)
 */
+ (instancetype)buildWithString:(NSString *)string;

/*!
 @method buildWithString
 @discussion Creates a CAM XBS build object.
 @param string
	Full build string. (ex. Hoodoo9B179)
 @param mountKey
	Mount key for the AFP share.
 */
+ (instancetype)buildWithString:(NSString *)string atMount:(NSString *)mountKey;

/*!
 @property mount
 @discussion AFP share mount.
 */
@property (nonatomic, copy, readonly)   NSString *mount;

/*!
 @property server
 @discussion The AFP server for this build.
 */
@property (nonatomic, copy, readonly)   NSString *server;

/*!
 @property mountURL
 @discussion The full AFP mount URL (e.g. afp://server/mount) for this build.
 */
@property (nonatomic, copy, readonly)   NSURL *mountURL;

/*!
 @property train
 @discussion XBS build train. (ex. Hoodoo in Hoodoo9B179)
 */
@property (nonatomic, copy, readonly)   NSString *train;

/*!
 @property buildName
 @discussion XBS build name. (ex. 9B179 in Hoodoo9B179)
 */
@property (nonatomic, copy, readonly)   NSString *buildName;

/*!
 @property buildPrefix
 @discussion XBS build prefix.  (ex. 9B in Hoodoo9B179)
 */
@property (nonatomic, copy, readonly)   NSString *buildPrefix;

/*!
 @property majorNumber
 @discussion XBS major number. (ex. 9 in Hoodoo9B179)
 */
@property (nonatomic, copy, readonly)   NSNumber *majorNumber;

/*!
 @property majorLetter
 @discussion XBS major letter. (ex. B in Hoodoo9B179)
 */
@property (nonatomic, copy, readonly)   NSString *majorLetter;

/*!
 @property minorNumber
 @discussion XPS minor number. (ex. 179 in Hoodoo9B179)
 */
@property (nonatomic, copy, readonly)   NSNumber *minorNumber;

/*!
 @property suffix
 @discussion XBS suffix. (ex. 'a' in Hoodoo9B179a)
 */
@property (nonatomic, copy, readonly)   NSString *suffix;

/*!
 @property qualifier
 @discussion XBS build qualifier. (ex. 'DOA' in Hoodoo9B179a.DOA)
 */
@property (nonatomic, copy, readonly)   NSString *qualifier;

/*!
 @property fullBuildName
 @discussion XBS full build name. (ex. Hoodoo9B179)
 */
@property (nonatomic, copy, readonly)   NSString *fullBuildName;

/*!
 @property hasSuffix
 @discussion Boolean for whether has XBS suffix or not. (ex. 'a' in Hoodoo9B179a)
 */
@property (nonatomic, assign, readonly) BOOL hasSuffix;

/*!
 @property hasQualifier
 @discussion If there is a period, then everything after the period is the qualifier.  Ex. DOA in Hoodoo9B179a.DOA.
 */
@property (nonatomic, assign, readonly) BOOL hasQualifier;

/*!
 @property restorePiecesPath
 @discussion Path to the restore pieces.
 */
@property (copy, readonly)   NSString *restorePiecesPath;

/*!
 @method restorePiecesPathForHardwareModel:withVariant
 @param model
 	the hardware model codename the device is identified by, e.g. N88AP
 @param variant
    the type of install requested, e.g. "Internal Development", "Internal Install", etc.
 @result
    a string representation of the full path to the bundle (.dmg) containing the restore image, nil if unavailable or unsupported.
 */
- (NSString*)restorePiecesPathForHardwareModel:(NSString*)model withVariant:(NSString*)variant;

/*!
 @method compare
 @discussion Compare two builds.
 @param otherBuild
	Compares which is older/newer.
 @result
	NSComparisonResult to check.
 */
- (NSComparisonResult)compare:(CAMXBSBuild *)otherBuild;

/*!
 @method isEqualToBuild
 @discussion Determine if this build is equal to another one.
 @param build
	Build to compare against.
 @result
	YES if builds are equal.
 */
- (BOOL)isEqualToBuild:(CAMXBSBuild *)build;

/*!
 @method mostRecentBuildForTrain
 @discussion Takes a train and grabs the most recent build. Assumes non-AppleTV.
 @param trainName
	Train to grab build.
 @result
	Build object of most recent.
 */
+ (CAMXBSBuild *)mostRecentBuildForTrain:(NSString*)trainName;

/*!
 @method mostRecentBuildForTrain
 @discussion Takes a train and grabs the most recent build.
 @param trainName
 Train to grab build.
 @param isMustang
 Whether the mount point should be at Mustang (AppleTV) or not.
 @result
 Build object of most recent.
 */
+ (CAMXBSBuild *)mostRecentBuildForTrain:(NSString*)trainName isMustang:(BOOL)isMustang;

/*!
 @method mostRecentBuildForTrain
 @discussion Takes a train and grabs the most recent build.
 @param trainName
	Train to grab build.
 @param mountKey
	Mount key for the AFP share.
 @result
	Build object of most recent.
 */
+ (CAMXBSBuild *)mostRecentBuildForTrain:(NSString *)trainName atMount:(NSString *)mountKey;

/*!
 @method mostRecentBuildAtURL
 @discussion Gets the most recent build given a URL.
 @param url
	URL of the train.
 @result
	CAMXBSBuild object of the most recent build.
 */
+ (CAMXBSBuild *)mostRecentBuildAtURL:(NSURL*)url;

/*!
 @method mostRecentBuildAtURL
 @discussion Gets the most recent build given a URL.
 @param url
	URL of the train.
 @param mountKey
	Mount key for the AFP share.
 @result
	CAMXBSBuild object of the most recent build.
 */
+ (CAMXBSBuild *)mostRecentBuildAtURL:(NSURL *)url atMount:(NSString *)mountKey;

@end
