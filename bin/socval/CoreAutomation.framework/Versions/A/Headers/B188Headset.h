//
//  B188Headset.h
//  B188WirelessStress
//
//  Created by Jeffrey McGovern on 7/18/16.
//  Copyright © 2016 Apple, Inc. All rights reserved.
//

#ifndef B188Headset_h
#define B188Headset_h

#import <Foundation/Foundation.h>
#import <CoreAutomation/CAMLogger.h>

#import "BluetoothHeadset.h"
#import "B188Bud.h"

extern NSString *const kCAMB188LeftBudPath;
extern NSString *const kCAMB188RightBudPath;

extern NSString *const kCAMB188ButtonMedia;
extern NSString *const kCAMB188ButtonSiri;
extern NSString *const kCAMB188ButtonUnknown;
extern NSString *const kCAMB188ButtonUnknown;
extern NSString *const kCAMB188AudioStateA2DP;
extern NSString *const kCAMB188AudioStateHFP;
extern NSString *const kCAMB188AudioStateDisconnected;

extern NSString *const kCAMB188NotificationUnexpectedReset;
extern NSString *const kCAMB188NotificationAppResetPerformed;
extern NSString *const kCAMB188NotificationAppResetDetected;
extern NSString *const kCAMB188NotificationSideKey;
extern NSString *const kCAMB188NotificationRoleKey;
extern NSString *const kCAMB188NotificationAddrKey;

@interface B188Headset : NSObject <BluetoothHeadset>
#pragma mark -
#pragma mark Creating the Headset
/*!
 @name Creating the Headset
 @{
 */
/*!
 @method initWithGenericDevicePath:formatter:
 @discussion Initializer that will attempt to return a headset with the given generic paths, performing a couple if requested, opening the B188PythonFormatter in the default directory, and logging with CAMLoggerDebug level of filtering for both log files and NSLog.
 @param aPath String path of one of the buds without letter suffixes (e.g. /dev/cu.usbserial-14132 if ...14132D and ...14132C are present)
 @param bPath String path of the other bud without letter suffixes (e.g. /dev/cu.usbserial-14133 if ...14133D and ...14133C are present)
 @param performCouple Performs bud couple if true, does not couple otherwise
 */
- (instancetype)initWithPath:(NSString *)aPath andAnotherPath:(NSString *)bPath performCouple:(BOOL)performCouple;
/*!
 @method initWithGenericDevicePath:formatter:
 @discussion Initializer that will attempt to return a headset with the given generic paths, performing a couple if requested, opening the B188PythonFormatter using the scripts that reside in the specified directory, and setting the log file and NSLog filter levels of the the headset and buds to the respective log levels
 @param aPath String path of one of the buds without letter suffixes (e.g. /dev/cu.usbserial-14132 if ...14132D and ...14132C are present)
 @param bPath String path of the other bud without letter suffixes (e.g. /dev/cu.usbserial-14133 if ...14133D and ...14133C are present)
 @param performCouple Performs bud couple if true, does not couple otherwise
 @param dir String path to the directory containing the B188PythonFormatter scripts
 @param filterLevel CAMLoggerLevel level of message below which messages will NOT be logged to file
 @param NSLogFilterLevel CAMLoggerLevel level of message below which messages will NOT be logged to NSLog
 */
- (instancetype)initWithAllParameters:(NSString *)aPath
                       andAnotherPath:(NSString *)bPath
                        performCouple:(BOOL)performCouple
                            directory:(NSString *)dir
                          filterLevel:(CAMLoggerLevel)filterLevel
                     NSLogFilterLevel:(CAMLoggerLevel)NSLogFilterLevel;
/*! @} End Creating the Headset */

#pragma mark Closing the Headset
/*!
 @name Closing the Headset
 @{
 */
/*!
 @method close
 @brief Closes data structures and ports for headset and each bud. Absolutely must be called when finished with headset.
 */
- (void)close;
/*! @} End Closing the Headset */

#pragma mark -
#pragma mark Buds
/*!
 @name Buds
 @{
 */
/*! @brief Left Bud */
@property B188Bud *left;
/*! @brief Right Bud */
@property B188Bud *right;
/*! @brief Primary Bud (may change throughout use of headset) */
@property B188Bud *primary;
/*! @brief Secondary Bud (may change throughout use of headset) */
@property B188Bud *secondary;
/*! @} End Buds */

#pragma mark -
#pragma mark Logging
/*!
 @name Logging
 @{
 */
/*! @brief Logs the actions performed at the headset level */
@property CAMLogger *headsetLogger;
/*! @brief Log level for bud appTrace and baseband and headset log files --- any message below this will NOT log to file */
@property CAMLoggerLevel filterLevel;
/*! @brief Log level for NSLog output --- any message below this will NOT log to NSLog */
@property CAMLoggerLevel NSLogFilterLevel;

/*!
 @method logAll:message:
 @brief Logs to all log files and NSLog, appending a [Headset] to the message to indicate a logAll message
 @param level CAMLoggerLevel level below which messages will be ignored
 @param message String format of the message
 */
- (void)logAll:(CAMLoggerLevel)level message:(NSString *)message, ...;
/*!
 @method getAllLoggers
 @brief Creates and returns an array of the headset's and each bud's loggers
 @return Array of this headset's and its bud's CAMLogger objects
 */
- (NSArray *)getAllLoggers;
/*! @} End Logging */

#pragma mark -
#pragma mark Bud Role-Related Actions
/*!
 @name Bud Role-Related Actions
 @{
 */
/*!
 @method couple
 @brief Performs the coupling steps as outlined in <https://connectme.apple.com/docs/DOC-705564>
 */
- (void)couple;
/*!
 @method determinePrimaryAndSecondary
 @brief Determines which bud is primary and secondary, by comparing each bud's roles as obtained from serial command
 */
- (NSError *)determinePrimaryAndSecondary;
/*!
 @method updateAndGetPrimary
 @brief Determines which bud is primary and secondary and returns the determined primary bud
 @see determinePrimaryAndSecondary
 @return B188Bud the determined primary bud
 */
- (B188Bud *)updateAndGetPrimary;
/*! @} End Bud Role-Related Actions */

#pragma mark -
#pragma mark Bud Button-Related Actions
/*!
 @name Bud Button-Related Actions
 @{
 */
/*!
 @method getButton
 @brief Sends the serial command to get the primary bud's button mode, either kCAMB188ButtonMedia or kCAMB188ButtonSiri
 @return String of the primary bud's button mode, either kCAMB188ButtonMedia or kCAMB188ButtonSiri
 */
- (NSString *)getButton;
/*!
 @method setButtonTo:
 @brief Sets the bud's button mode to the provided mode on the primary bud
 @param mode String of the mode, either kCAMB188ButtonMedia or kCAMB188ButtonSiri
 @return String output of the set button serial command
 */
- (NSString *)setButtonTo:(NSString *)mode;
/*!
 @method doubleTap
 @brief Performs an double tap on the primary bud by sending the serial command through the commander
 @return String output of the serial command
 */
- (NSString *)doubleTap;
/*! @} End Bud Button-Related Actions */

#pragma mark -
#pragma mark BluetoothHeadset Functions
/*!
 @name BluetoothHeadset Functions
 @{
 */
/*!
 @method getBluetoothAddress
 @brief Returns the Bluetooth address of the headset
 @return String 
 */
- (NSString *)getBluetoothAddress;

/*!
 @method getBluetoothName
 @brief Returns the Bluetooth name of the headset, the name of the primary bud
 @return String the name of the determined primary bud
 */
- (NSString *)getBluetoothName;

/*!
 @method getAudioState
 @brief Returns the audio state of the headset, the audio state of the primary bud
 @return BTAudioState audio state of the device
 */
- (BTAudioState)getAudioState;

/*!
 @method nameForAudioState
 @brief Returns the string of the audio state
 */
+ (NSString *)nameForAudioState:(BTAudioState)state;

/*!
 @method enterPairingMode
 @brief Enters pairing mode on the determined primary
 @return BOOL true if the primary's local info command contains the string indicating that it is discoverable, false otherwise
 */
- (BOOL)enterPairingMode;
/*! @} End BluetoothHeadset Functions */

@end

#endif /* B188Headset_h */
