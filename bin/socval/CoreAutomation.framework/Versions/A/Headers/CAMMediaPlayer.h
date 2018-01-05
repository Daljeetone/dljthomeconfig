//
//  CAMMediaPlayer.h
//  CoreAutomation
//
//  Created by Chris Whitney on 1/7/12.
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CAMReturnValues.h"

#define kCAMMediaPlayerShortName mediaPlayer

//Now Playing Info Keys
#define CAMMediaItemPropertyAlbumTitle                  @"CAMMediaItemPropertyAlbumTitle"                   // NSString
#define CAMMediaItemPropertyAlbumTrackCount             @"CAMMediaItemPropertyAlbumTrackCount"              // NSNumber (NSUInteger)
#define CAMMediaItemPropertyAlbumTrackNumber            @"CAMMediaItemPropertyAlbumTrackNumber"             // NSNumber (NSUInteger)
#define CAMMediaItemPropertyArtist                      @"CAMMediaItemPropertyArtist"                       // NSString
#define CAMMediaItemPropertyArtwork                     @"CAMMediaItemPropertyArtwork"                      // NSData
#define CAMMediaItemPropertyComposer                    @"CAMMediaItemPropertyComposer"                     // NSString
#define CAMMediaItemPropertyDiscCount                   @"CAMMediaItemPropertyDiscCount"                    // NSNumber (NSUInteger)
#define CAMMediaItemPropertyDiscNumber                  @"CAMMediaItemPropertyDiscNumber"                   // NSNumber (NSUInteger)
#define CAMMediaItemPropertyGenre                       @"CAMMediaItemPropertyGenre"                        // NSString
#define CAMMediaItemPropertyPersistentID                @"CAMMediaItemPropertyPersistentID"                 // NSNumber (uint64_t)
#define CAMMediaItemPropertyPlaybackDuration            @"CAMMediaItemPropertyPlaybackDuration"             // NSNumber (NSTimeInterval)
#define CAMMediaItemPropertyTitle                       @"CAMMediaItemPropertyTitle"                        // NSString
#define CAMNowPlayingInfoPropertyElapsedPlaybackTime    @"CAMNowPlayingInfoPropertyElapsedPlaybackTime"     // NSNumber (double)
#define CAMNowPlayingInfoPropertyPlaybackRate           @"CAMNowPlayingInfoPropertyPlaybackRate"            // NSNumber (double)
#define CAMNowPlayingInfoPropertyPlaybackQueueIndex     @"CAMNowPlayingInfoPropertyPlaybackQueueIndex"      // NSNumber (NSUInteger)
#define CAMNowPlayingInfoPropertyPlaybackQueueCount     @"CAMNowPlayingInfoPropertyPlaybackQueueCount"      // NSNumber (NSUInteger)
#define CAMNowPlayingInfoPropertyChapterNumber          @"CAMNowPlayingInfoPropertyChapterNumber"           // NSNumber (NSUInteger)
#define CAMNowPlayingInfoPropertyChapterCount           @"CAMNowPlayingInfoPropertyChapterCount"            // NSNumber (NSUInteger)
#define CAMNowPlayingInfoPropertyArtworkData            @"CAMNowPlayingInfoPropertyArtworkData"             // NSData
#define CAMNowPlayingInfoPropertyArtworkMIMEType        @"CAMNowPlayingInfoPropertyArtworkMIMEType"         // NSString
#define CAMNowPlayingInfoPropertyDefaultPlaybackRate    @"CAMNowPlayingInfoPropertyDefaultPlaybackRate"     // NSNumber (float)
#define CAMNowPlayingInfoPropertyIsAdvertisement        @"CAMNowPlayingInfoPropertyIsAdvertisement"         // NSNumber (BOOL)
#define CAMNowPlayingInfoPropertyIsAlwaysLive           @"CAMNowPlayingInfoPropertyIsAlwaysLive"            // NSNumber (BOOL)
#define CAMNowPlayingInfoPropertyIsBanned               @"CAMNowPlayingInfoPropertyIsBanned"                // NSNumber (BOOL)
#define CAMNowPlayingInfoPropertyIsInWishList           @"CAMNowPlayingInfoPropertyIsInWishList"            // NSNumber (BOOL)
#define CAMNowPlayingInfoPropertyIsLiked                @"CAMNowPlayingInfoPropertyIsLiked"                 // NSNumber (BOOL)
#define CAMNowPlayingInfoPropertyIsMusicApp             @"CAMNowPlayingInfoPropertyIsMusicApp"              // NSNumber (BOOL)
#define CAMNowPlayingInfoPropertyIsVideosApp            @"CAMNowPlayingInfoPropertyIsVideosApp"             // NSNumber (BOOL)
#define CAMNowPlayingInfoPropertyProhibitsSkip          @"CAMNowPlayingInfoPropertyProhibitsSkip"           // NSNumber (BOOL)
#define CAMNowPlayingInfoPropertyRadioStationIdentifier @"CAMNowPlayingInfoPropertyRadioStationIdentifier"  // NSNumber (int64_t)
#define CAMNowPlayingInfoPropertyRadioStationHash       @"CAMNowPlayingInfoPropertyRadioStationHash"        // NSString
#define CAMNowPlayingInfoPropertyRadioStationName       @"CAMNowPlayingInfoPropertyRadioStationName"        // NSString
#define CAMNowPlayingInfoPropertyRepeatMode             @"CAMNowPlayingInfoPropertyRepeatMode"              // NSNumber (CAMNowPlayingRepeatMode)
#define CAMNowPlayingInfoPropertyShuffleMode            @"CAMNowPlayingInfoPropertyShuffleMode"             // NSNumber (CAMNowPlayingShuffleMode)
#define CAMNowPlayingInfoPropertyPurchaseInfoData       @"CAMNowPlayingInfoPropertyPurchaseInfoData"        // NSData
#define CAMNowPlayingInfoPropertySupportsSkipForward    @"CAMNowPlayingInfoPropertySupportsSkipForward"     // NSNumber (BOOL)
#define CAMNowPlayingInfoPropertySupportsIsBanned       @"CAMNowPlayingInfoPropertySupportsIsBanned"        // NSNumber (BOOL)
#define CAMNowPlayingInfoPropertySupportsIsLiked        @"CAMNowPlayingInfoPropertySupportsIsLiked"         // NSNumber (BOOL)
#define CAMNowPlayingInfoPropertySupportsSkipBackward   @"CAMNowPlayingInfoPropertySupportsSkipBackward"    // NSNumber (BOOL)
#define CAMNowPlayingInfoPropertySupportsWishlisting    @"CAMNowPlayingInfoPropertySupportsWishlisting"     // NSNumber (BOOL)

typedef NS_ENUM(NSInteger, CAMNowPlayingRepeatMode) {
    CAMNowPlayingRepeatModeNone,
    CAMNowPlayingRepeatModeOne,
    CAMNowPlayingRepeatModeAll,
};

typedef NS_ENUM(NSInteger, CAMNowPlayingShuffleMode) {
    CAMNowPlayingShuffleModeOff,
    CAMNowPlayingShuffleModeAlbums,
    CAMNowPlayingShuffleModeSongs,
};

@protocol CAMMediaPlayer
@optional

/*!
 @method     hasMusic
 @abstract   Query if music is available in the media player library.
 */
- (CAMReturnBool*)hasMusic;

/*!
 @method     allSongIDs
 @abstract   Return persistent IDs for all songs.
 */
- (CAMReturnArray*)allSongIDs;

/*!
 @method     allArtistIDs
 @abstract   Return persistent IDs for all artists.
 */
- (CAMReturnArray*)allArtistIDs;

/*!
 @method     allAlbumIDs
 @abstract   Return persistent IDs for all albums.
 */
- (CAMReturnArray*)allAlbumIDs;

/*!
 @method     allPlaylistIDs
 @abstract   Return persistent IDs for all playlists.
 */
- (CAMReturnArray*)allPlaylistIDs;

/*!
 @method     allGenreIDs
 @abstract   Return persistent IDs for all genres.
 */
- (CAMReturnArray*)allGenreIDs;

/*!
 @method     metadataForID
 @abstract   Return all metadata for a persistent ID.
 */
- (CAMReturnDictionary*)metadataForID:(NSNumber*)pid;

/*!
 @method     hasVideo
 @abstract   Query if a video is available in the media player library.
 */
- (CAMReturnBool*)hasVideo;

/*!
 @method     playMusic
 @abstract   Start playing music from the media player library.
 */
- (CAMReturnVoid*)playMusic;

/*!
 @method     playMusicByTitle:
 @abstract   Start playing songs matching the given title.
 */
- (CAMReturnVoid*)playMusicByTitle:(NSString*)title;

/*!
 @method     playMusicByPlaylist:
 @abstract   Start playing the playlist with the given title.
 */
- (CAMReturnVoid*)playMusicByPlaylist:(NSString*)playlist;

/*!
 @method     pauseMusic
 @abstract   Pause the currently playing music.
 */
- (CAMReturnVoid*)pauseMusic;

/*!
 @method     stopMusic
 @abstract   Stop playing the current music.
 */
- (CAMReturnVoid*)stopMusic;

/*!
 @method     nowPlayingMediaItem
 @abstract   Gather information about the currently playing media item.
 @return     Returns a dictionary of information potentially including title, album, duration, current playback state and playback time.
 */
- (CAMReturnDictionary*)nowPlayingMediaItem;

/*!
 @method     scrubMedia
 @abstract   Scrubs the song progress slider to the specificed level. Assumes the song to be scrubbed is playing.
 @param      level A floating number between 0 and 1 representing the progress that is required.
 */
- (CAMReturnVoid*)scrubMedia:(NSNumber*)level;

/*!
 @method     isRadioEnabled
 @abstract   Checks if Radio is enabled.
 */
- (CAMReturnBool*)isRadioEnabled;

/*!
 @method     radioStations
 @abstract   Returns the list of Radio Stations contained in the default Radio Library.
 */
- (CAMReturnDictionary*)radioStations;

/*!
 @method     queueAsRadioStation
 @abstract   Returns the Radio Station that is currently in the playback queue.
 */
- (CAMReturnDictionary*)queueAsRadioStation;

/*!
 @method     playRadioStation
 @abstract   Start playing the Radio Station with the given station ID.
 */
- (CAMReturnBool*)playRadioStation:(NSNumber*)stationID;

/*!
 @method becomeNowPlayingApp
 @abstract Become the now playing app
 @discussion Allows custom now playing info to be set
 */
- (CAMReturnVoid *)becomeNowPlayingApp;

/*!
 @method resignNowPlayingApp
 @abstract Release control of the now playing app
 @discussion Returns control to previous now playing app
 */
- (CAMReturnVoid *)resignNowPlayingApp;

/*!
 @method setNowPlayingInfo
 @abstract Set the now playing information
 @param nowPlayingInfo The now playing information to set
 @discussion See MPNowPlayingInfoCenter for a list of supported properties. -becomeNowPlayingApp must be called for the now playing info to take effect
 */
- (CAMReturnVoid *)setNowPlayingInfo:(NSDictionary *)nowPlayingInfo;

/*!
 @method nowPlayingInfo
 @abstract Get the current now playing information. -becomeNowPlayingApp must be called for the now playing info to take effect
 */
- (CAMReturnDictionary *)nowPlayingInfo;

/*!
 @method quit
 @abstract Quit the running mediaPlayer application if possible
 @discussion Needed for platforms where mediaPlayer is iTunes
 */
- (CAMReturnVoid *)quit;


@end
