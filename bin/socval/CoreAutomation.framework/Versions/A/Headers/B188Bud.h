//
//  B188Bud.h
//  B188WirelessStress
//
//  Created by Jeffrey McGovern on 7/18/16.
//  Copyright © 2016 Apple, Inc. All rights reserved.
//

#ifndef B188Bud_h
#define B188Bud_h

#import <CoreAutomation/CAMLogger.h>

#import "CAMSerialPortDispatchable.h"
#import "CAMSerialFormatter.h"

extern NSString *const kCAMB188RolePrimary;
extern NSString *const kCAMB188RoleSecondary;

extern NSString *const kCAMB188SideLeft;
extern NSString *const kCAMB188SideRight;

extern NSString *const kCAMB188ButtonMedia;
extern NSString *const kCAMB188ButtonSiri;
extern NSString *const kCAMB188ButtonUnknown;

extern NSString *const kCAMB188AudioStateDisconnected;
extern NSString *const kCAMB188AudioStateA2DP;
extern NSString *const kCAMB188AudioStateHFP;

extern NSString *const kCAMB188InearStateUnknown;
extern NSString *const kCAMB188InearStateOut;
extern NSString *const kCAMB188InearStateIn;

extern NSString *const kCAMB188NotificationAppResetPerformed;
extern NSString *const kCAMB188NotificationAppResetDetected;
extern NSString *const kCAMB188NotificationSideKey;
extern NSString *const kCAMB188NotificationRoleKey;
extern NSString *const kCAMB188NotificationAddrKey;

@interface B188Bud : NSObject

- (id)init __attribute__((unavailable("init not possible for B188Bud")));

/*!
 @method getBudFromGenericPath
 @brief Class method of currently allocated buds, for dispatched reads
 @param path String of the bud's generic path
 @return Requested bud object if still allocated, nil otherwise
 */
+ (B188Bud *)getBudFromGenericPath:(NSString *)path;

#pragma mark -
#pragma mark Creating the Bud
/*!
 @name Creating the Bud
 @{
 */

/*!
 @method initWithGenericDevicePath:formatter:
 @brief Initializer that will attempt to return a bud with the given generic path and serial input/output formatter, with filter level for all logging at CAMLevelDebug
 @param path String path of the bud without letter suffixes (e.g. /dev/cu.usbserial-14132 if ...14132D and ...14132C are present)
 */
- (instancetype)initWithGenericDevicePath:(NSString *)path formatter:(id<CAMSerialFormatter>)formatter;

/*!
 @method initWithAllParameters:formatter:filterLevel:NSLogFilterLevel:
 @brief Initializer that will attempt to return a bud with the given generic path, serial input/output formatter, log file filter level, and NSLog filter level
 @param path String path of the bud without letter suffixes (e.g. /dev/cu.usbserial-14132 if ...14132D and ...14132C are present)
 @param filterLevel CAMLoggerLevel level of message below which messages will NOT be logged to file
 @param NSLogFilterLevel CAMLoggerLevel level of message below which messages will NOT be logged to NSLog
 */
- (instancetype)initWithAllParameters:(NSString *)path
                            formatter:(id<CAMSerialFormatter>)formatter
                          filterLevel:(CAMLoggerLevel)filterLevel
                     NSLogFilterLevel:(CAMLoggerLevel)NSLogFilterLevel;
/*! @} End Creating the Bud */

#pragma mark Closing the Bud
/*!
 @name Closing the Bud
 @{
 */

/*!
 @method close
 @brief Closes data structures and ports. Absolutely must be called when finished with bud.
 */
- (void)close;
/*! @} End Closing the Bud */

#pragma mark Config Values
/*!
 @name Config Values
 @brief Values obtained from most recently sent serial command
 @{
 */

/*! @brief Bluetooth MAC Address */
@property NSString *addr;
/*! @brief Partner Bud's Bluetooth MAC Address */
@property NSString *caddr;
/*! @brief Bluetooth Name */
@property NSString *name;
/*! @brief Primary/Secondary Role in Headset For This Bud */
@property NSString *role;
/*! @brief Left/Right Side of Headset This Bud Represents */
@property NSString *side;
/*! @brief Mode of Doubletap Button */
@property NSString *button;
/*! @} End Config Values */

#pragma mark -
#pragma mark Communication
/*!
 @name Communication
 @discussion Communicates with the B188 device for reading and writing
 @{
 */

/*! @brief Path of Bud Without Letter Suffixes */
@property NSString *genericPath;
/*! @brief Path to AppTrace Command Device (Ending in 'D') */
@property NSString *commandPath;
/*! @brief Path to Baseband Output Device (Ending in 'C') */
@property NSString *basebandPath;
/*! @brief Queue for Event-Driven Reads and Dispatching of Commands */
@property dispatch_queue_t commandQueue;

/*! @brief AppTrace Command Serial Port Reader/Writer */
@property CAMSerialPortDispatchable *commander;
/*! @brief Baseband Reader Serial Port Reader */
@property CAMSerialPortDispatchable *basebandReader;
/*! @brief Serial Port Input and Output Formatter */
@property id<CAMSerialFormatter> formatter;

#pragma mark Sending Commands
/*!
 @method dispatchCommand
 @brief Dispatches the given command onto the commander dispatch queue and returns the formatted output of the command
 @param command String of the serial command to be added to the commander's dispatch queue
 @return String output of the serial command
 */
- (NSString *)dispatchCommand:(NSString *)command;

#pragma mark Reading Output
/*!
 @method readCommandOutput
 @brief Reads and logs the appTrace commander output, logging and returning the formatted output
 @return String of the formatted output from the appTrace commander
 */
- (CAMReturnString *)readCommandOutput;
/*!
 @method readBasebandOutput
 @brief Reads and logs the so-called baseband output, logging and returning the formatted output
 @return String of the formatted output from the baseband
 */
- (CAMReturnString *)readBasebandOutput;

/*! @} End Communication */

#pragma mark Logging
/*!
 @name Logging
 @{
 */

/*! @brief Log level for NSLog output --- any message below this will NOT log to NSLog */
@property CAMLoggerLevel NSLogFilterLevel;
/*! @brief Log level for appTrace and baseband log files --- any message below this will NOT log to file */
@property CAMLoggerLevel filterLevel;
/*! @brief Logs the command appTrace output */
@property CAMLogger *appTraceLogger;
/*! @brief Logs the baseband output */
@property CAMLogger *basebandLogger;

/*!
 @method logAll:message:
 @brief Logs to all log files and NSLog, appending a [Bud] to the message to indicate a logAll message
 @param level CAMLoggerLevel level below which messages will be ignored
 @param message String format of the message
 */
- (void)logAll:(CAMLoggerLevel)level message:(NSString *)message, ...;
/*!
 @method getAllLoggers
 @brief Creates and returns an array of the bud's loggers
 @return Array of this bud's CAMLogger objects
 */
- (NSArray *)getAllLoggers;
/*! @} End Logging */

#pragma mark -
#pragma mark Getting State From Serial
/*!
 @name Getting State From Serial
 @discussion Gets the requested state from the bud using a serial command sent through the commander.
 @{
 */

/*!
 @method getLocalInfoFromSerial
 @brief Sends the 'local info' serial command, returning the output, which should contain master/slave and connectability information
 @return String output of the local info command
 */
- (NSString *)getLocalInfoFromSerial;
/**
 @method getAllFromSerial
 @brief Sends the 'cfg get all' serial command, returning the output
 @return String output of the cfg get all command
 */
- (NSString *)getAllFromSerial;
/*!
 @method getAddrFromSerial
 @brief Sends the serial command to get the MAC address of the bud
 @return String of the bud's MAC address in the (regex) form ([0-9A-F]{2}[:-]){5}([0-9A-F]{2})
 */
- (NSString *)getAddrFromSerial;
/*!
 @method getCaddrFromSerial
 @brief Sends the serial command to get the bud's partner MAC address
 @return String of the bud partner's MAC address, in the (regex) form ([0-9A-F]{2}[:-]){5}([0-9A-F]{2})
 */
- (NSString *)getCaddrFromSerial;
/*!
 @method getNameFromSerial
 @brief Sends the serial command to get the bud's name
 @return String of the bud's name
 */
- (NSString *)getNameFromSerial;
/*!
 @method getRoleFromSerial
 @brief Sends the serial command to get the bud's role, either kCAMB188RolePrimary or kCAMB188RoleSecondary
 @return String of the bud's role, either kCAMB188RolePrimary or kCAMB188RoleSecondary
 */
- (NSString *)getRoleFromSerial;
/*!
 @method getSideFromSerial
 @brief Sends the serial command to get the bud's side, either kCAMB188SideLeft or kCAMB188SideRight
 @return String of the bud's side, either kCAMB188SideLeft or kCAMB188SideRight
 */
- (NSString *)getSideFromSerial;
/*!
 @method getButtonFromSerial
 @brief Sends the serial command to get the bud's button mode, either kCAMB188ButtonMedia or kCAMB188ButtonSiri
 @return String of the bud's button mode, either kCAMB188ButtonMedia or kCAMB188ButtonSiri
 */
- (NSString *)getButtonFromSerial;
/*!
 @method getInearFromSerial
 @brief Sends the serial command to get the bud's inear state, either kCAMB188InearStateUnknown, kCAMB188InearStateIn, kCAMB188InearStateOut
 @return String of the bud's inear state, either kCAMB188InearStateUnknown, kCAMB188InearStateIn, kCAMB188InearStateOut
 */
- (NSString *)getInearFromSerial;
/*!
 @method getAudioStateFromSerial
 @brief Sends the serial command to get the bud's audio state, either kCAMB188AudioStateDisconnected, kCAMB188AudioStateA2DP, kCAMB188AudioStateHFP
 @return String of the bud's inear state, either kCAMB188AudioStateDisconnected, kCAMB188AudioStateA2DP, kCAMB188AudioStateHFP
 */
- (NSString *)getAudioStateFromSerial;
/*! @} End Getting State From Serial */

#pragma mark Setting State From Serial
/*!
 @name Setting State Via Serial
 @discussion Sets the state of the bud by sending a serial command through the commander
 @{
 */
/*!
 @method setCaddrViaSerialTo:
 @brief Sets the bud's partner MAC address to the provided address
 @param caddr String of the new bud partner's MAC address in the (regex) form ([0-9A-F]{2}[:-]){5}([0-9A-F]{2})
 @return String output of the set caddr serial command
 */
- (NSString *)setCaddrViaSerialTo:(NSString *)caddr;
/*!
 @method setRoleViaSerialTo:
 @brief Sets the bud's role to the provided role
 @param role String of the role, either kCAMB188RolePrimary or kCAMB188RoleSecondary
 @return String output of the set role serial command
 */
- (NSString *)setRoleViaSerialTo:(NSString *)role;
/*!
 @method setButtonViaSerialTo:
 @brief Sets the bud's button mode to the provided mode
 @param button String of the mode, either kCAMB188ButtonMedia or kCAMB188ButtonSiri
 @return String output of the set button serial command
 */
- (NSString *)setButtonViaSerialTo:(NSString *)button;
/*! @} End Setting State Via Serial */

#pragma mark Performing Actions Via Serial
/*!
 @name Performing Actions Via Serial
 @discussion Performs the requested action on the bud by sending a serial command through the commander
 @{
 */
/*!
 @method appReset
 @brief Performs an app reset by sending the app reset serial command through the commander
 @return String output of the app reset serial command
 */
- (NSString *)appReset;
/*!
 @method setPairOn
 @brief Enters pairing mode by sending the pair on serial command through the commander
 @return String output of the pair on serial command
 */
- (NSString *)setPairOn;
/*!
 @method setPairOff
 @brief Enters pairing mode by sending the pair off serial command through the commander
 @return String output of the pair off serial command
 */
- (NSString *)setPairOff;
/*!
 @method setToInear
 @brief Sets the inear state of the bud to in by sending a serial command through the commander
 @return String output of the serial command
 */
- (NSString *)setToInear;
/*!
 @method setToOutear
 @brief Sets the inear state of the bud to out by sending a serial command through the commander
 @return String output of the serial command
 */
- (NSString *)setToOutear;
/*!
 @method doubleTap
 @brief Performs an double tap by sending the serial command through the commander
 @return String output of the serial command
 */
- (NSString *)doubleTap;
/*! @} End Performing Actions Via Serial */

@end

#endif /* B188Bud_h */
