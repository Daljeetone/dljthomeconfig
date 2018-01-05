//
//  CAMLogger.h
//  CoreAutomation
//
//  Created by Matt Massicotte on 5/5/10.
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>

/*! Default logging directory */
extern NSString * const kCAMLogDir;

#define LOG_LEVEL_TYPE_COUNT 5

/*! Mapping of CAMLoggerLevel enum to level name that prints in the log */
extern NSString * const kCAMLoggerLevelTypeNamesArray[LOG_LEVEL_TYPE_COUNT];

/*!
 @enum CAMLoggerLevel
 @discussion Logger levels.
 */
typedef NS_ENUM(NSInteger, CAMLoggerLevel)
{
    CAMLogDebug = 0,
    CAMLogInfo = 1,
    CAMLogWarning = 2,
    CAMLogError = 3,
    CAMLogFatal = 4,
    CAMLogNSLogDefaultLevel = NSIntegerMax
};

/*!
 @interface CAMLogger
 @discussion This is the default logger for CAM.  Use this to log debug information.
 */
@interface CAMLogger : NSObject
{
    NSString*        _logPath;
    CAMLoggerLevel   _filterLevel;
    CAMLoggerLevel   _NSLogFilterLevel;
    NSDateFormatter* _dateFormatter;
    NSMutableSet*    _chainedLoggers;
    @private
    NSFileHandle*    _persistentCAMFileHandle;
    @private
    unsigned long    _rolloverId;
}

/*!
 @brief Returns the global, shared logger for CAM. Will init the logger on first invocation. Defaults logging filter level to CAMLogDebug.
*/
+ (CAMLogger *)defaultLogger;

/*!
 @brief Create a logger with specific file path, filter level, and flag which if true rolls the log over at midnight.
 @param filePath	Path to create the log file. Intermediate directories will also be created.
 @param filterLevel	The default logging level to filter from.
 @param rolloverLogAtMidnight	If set to YES, will start a NSTimer which rolls over the log at midnight (if process was started before 11pm local time, otherwise will rollover at second midnight).

 Available CAMLoggerLevel logging levels:
 CAMLogDebug = 0,
 CAMLogInfo = 1,
 CAMLogWarning = 2,
 CAMLogError = 3,
 CAMLogFatal = 4
 */
- (CAMLogger *)initWithLog:(NSString *)filePath filterLevel:(CAMLoggerLevel)filterLevel rolloverLogAtMidnight:(BOOL)rolloverLogAtMidnight;

/*!
 @brief Log a message at the specified logging level.
 @param level	A CAMLoggerLevel constant describing the priority of the message.
 @param format	A format string and follow-on arguments as per [NSString stringWithFormat:]
 */
- (void)log:(CAMLoggerLevel)level message:(NSString *)format, ...;

/*!
 @brief Log a message at the specified logging level. If 'andNSLog' is YES, also write the message to NSLog.
 @param level		A CAMLoggerLevel constant describing the priority of the message.
 @param logToNSLog	If YES, also log the message to NSLog.
 @param format		A format string and follow-on arguments as per [NSString stringWithFormat:]
 */
- (void)log:(CAMLoggerLevel)level andNSLog:(BOOL)logToNSLog message:(NSString *)format, ...;

/*!
 @brief Log a message at the specified logging level, throttling logging when necessary.
 @details Wrapper around log:message: that temporarily disables logging if too many messages
          are submitted from the same source in a short period of time. Stops logging
          for 5 seconds if 5 messages are logged from the same source within 1 second.
 @param level	A CAMLoggerLevel constant describing the priority of the message.
 @param source	A unique String identifier for the logging source.
 @param format	A format string and follow-on arguments as per [NSString stringWithFormat:]
 */
- (BOOL)log:(CAMLoggerLevel)level throttlingMessagesFromSource:(NSString *)source message:(NSString *)format, ...;

/*!
 @brief Chain another CAMLogger instance to this CAMLogger. This results in log messages written to this CAMLogger instance to also be written to the chained CAMLogger. The relationship is uni-directional.
 @param logger	CAMLogger to chain our logger to.
 */
- (void)chainLogger:(CAMLogger *)logger;

/*!
 @brief Destroys the CAM log to help prevent log clutter.
 */
- (void)selfDestruct;

/*!
 @brief Create log file at path and return file handle. If file already exists, just return file handle to it.
 @param logPath	Path of log file to create.
 @return NSFileHandle for log path.
 @throws CAMLoggerException if we could not acquire a valid file handle.
 */
+ (NSFileHandle *)createOrUpdateLogFileWithPath:(NSString *)logPath;

/*!
 @brief Returns the root logging directory where all CAMLogger logs will live. Defaults to ~/Library/Logs/Automation but can be configured via 'defaults'.
 @details
 defaults write com.apple.ApplicationName RootLoggingDirectory "~/Library/Logs/Automation"
 */
+ (NSString *)rootLoggingDirectory;

/*!
 @brief Filter logs out that are below this CAMLoggerLevel.
 */
@property CAMLoggerLevel filterLevel;

/*!
 @brief Log messages written to this level and higher will also go to NSLog.
 */
@property CAMLoggerLevel NSLogFilterLevel;

/*!
 @brief File system Location for this logger instance.
 */
@property (readonly, copy) NSString *logPath;

/*!
 @brief Log to these additional CAMLogger's when logging to this logger instance.
 */
@property (readonly, strong) NSMutableSet *chainedLoggers;

@end
