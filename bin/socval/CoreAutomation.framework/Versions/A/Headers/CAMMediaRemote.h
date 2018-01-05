//
//  CAMMediaRemote.h
//  CoreAutomation
//
//  Created by John Blackwell on 1/12/15.
//  The below APIs have been tested on Apple Watch and iOS devices.
//

#ifndef coreautomationd_CAMMediaRemote_h
#define coreautomationd_CAMMediaRemote_h

#import <Foundation/Foundation.h>
#import "CAMReturnValues.h"


#define kCAMMediaRemoteShortName mediaRemote

@protocol CAMMediaRemote
@optional


/*!
 @method     nowPlayingInfo
 @abstract   Please see CAMMediaPlayer.h for keys defined to extract track info.
 @return     Returns a dictionary containing info about the currently playing track.
 */
-(CAMReturnDictionary*)nowPlayingInfo;
/*!
 @method     play
 @abstract   Starts media playback. This API uses the MediaRemote.framework to control music playback (the same mechanism Control Center and BT use).
 @return     Returns YES if successful. Otherwise NO is returned.
 */
-(CAMReturnBool*)play;

/*!
 @method     togglePlayPause
 @abstract   Toggles the play pause button. This API uses the MediaRemote.framework to control music playback (the same mechanism Control Center and BT use).
 @return     Returns YES if successful. Otherwise NO is returned.
 */
-(CAMReturnBool*)togglePlayPause;

/*!
 @method     pause
 @abstract   Pauses the media playback. This API uses the MediaRemote.framework to control music playback (the same mechanism Control Center and BT use).
 @return     Returns YES if successful. Otherwise NO is returned.
 */
-(CAMReturnBool*)pause;

/*!
 @method     stop
 @abstract   Stops media playback. This API uses the MediaRemote.framework to control music playback (the same mechanism Control Center and BT use).
 @return     Returns YES if successful. Otherwise NO is returned.
 */
-(CAMReturnBool*)stop;

/*!
 @method     nextTrack
 @abstract   Skips to the next track. This API uses the MediaRemote.framework to control music playback (the same mechanism Control Center and BT use).
 @return     Returns YES if successful. Otherwise NO is returned.
 */
-(CAMReturnBool*)nextTrack;
/*!
 @method     previousTrack
 @abstract   Skips to the previous track. This API uses the MediaRemote.framework to control music playback (the same mechanism Control Center and BT use).
 @return     Returns YES if successful. Otherwise NO is returned.
 */
-(CAMReturnBool*)previousTrack;

/*!
 @method     advanceShuffleMode
 @abstract   Moves the shuffle mode forward one position. This API uses the MediaRemote.framework to control music playback (the same mechanism Control Center and BT use).
 @return     Returns YES if successful. Otherwise NO is returned.
 */
-(CAMReturnBool*)advanceShuffleMode;

/*!
 @method     advanceRepeatMode
 @abstract   Moves the repeat mode forward one position. This API uses the MediaRemote.framework to control music playback (the same mechanism Control Center and BT use).
 @return     Returns YES if successful. Otherwise NO is returned.
 */
-(CAMReturnBool*)advanceRepeatMode;

/*!
 @method     beginFastForward
 @abstract   Starts fast forwarding. This API uses the MediaRemote.framework to control music playback (the same mechanism Control Center and BT use).
 @return     Returns YES if successful. Otherwise NO is returned.
 */
-(CAMReturnBool*)beginFastForward;

/*!
 @method     endFastForward
 @abstract   Ends fast forwarding. This API uses the MediaRemote.framework to control music playback (the same mechanism Control Center and BT use).
 @return     Returns YES if successful. Otherwise NO is returned.
 */
-(CAMReturnBool*)endFastForward;

/*!
 @method     beginRewind
 @abstract   Begins rewinding. This API uses the MediaRemote.framework to control music playback (the same mechanism Control Center and BT use).
 @return     Returns YES if successful. Otherwise NO is returned.
 */
-(CAMReturnBool*)beginRewind;

/*!
 @method     endRewind
 @abstract   Ends rewinding. This API uses the MediaRemote.framework to control music playback (the same mechanism Control Center and BT use).
 @return     Returns YES if successful. Otherwise NO is returned.
 */
-(CAMReturnBool*)endRewind;

/*!
 @method     isMediaPlaying
 @abstract   Returns whether or not media is currently playing. This API uses the MediaRemote.framework to control music playback (the same mechanism Control Center and BT use).
 @return     Returns YES if music is playing. Otherwise NO is returned.
 */
-(CAMReturnBool*)isMediaPlaying;

@end

#endif
