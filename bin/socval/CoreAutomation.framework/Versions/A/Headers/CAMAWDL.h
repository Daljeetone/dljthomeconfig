//
//  CAMAWDL.h
//  CoreAutomation
//
//  Created by Inna Noten 7/30/14.
//	Copyright 2013-2014 Apple Inc. All rights reserved.

//

#import <Foundation/Foundation.h>

#import "CAMReturnValues.h"

#define kCAMAWDLShortName AWDL


@protocol CAMAWDL
@optional

#pragma mark - AirDrop

/*!
 @method    supportsAWDL
 @abstract  Yellow only. Checks whether AWDL is supported on a device.
 @return    Returns YES if AWDL is suported, NO otherwise. Set error if there was
            an exception getting the information
 */
- (CAMReturnBool *)supportsAWDL;

/*!
 @method    sendFilesWithICloud
 @abstract  Sends specified files to host using iCloud to enable automatic AirDrop acception.
 This is a blocking call. It assumes that source and target devices use the same iCloud account and both have a contact with the same
 first name and iCloud email. In this case the transmissions are accepted automatically so the blocking call works (no need to call a
 receive method to allow the transmission).
 @param		file_names - array of files to send
 host_name - target hostname
 trials - send for the specified number of times. Default is 1. Use a higher number to get more accurate statistics.
 timeout - timeout before stoping a send cycle. Default is 120 sec.
 @return    Statistics dictionary with keys "average" and "stddev" for the time it took to send the file(s). The stats are per trial.
 Sending several files is considered as one trial. Set <trials> to greater than one to get meaningful statistics.
 For one trial "average" is just the time it took to send the file(s) and "stddev" is 0.
 */
- (CAMReturnDictionary *)sendFilesWithICloud:(NSArray *)file_names toHost:(NSString *)host_name withTrials:(NSNumber *)trials withTimeout:(NSNumber *)timeout;

/*!
 @method    receiveFiles
 @abstract  Initiates file receiving
 @param		outputPath - save files received to a different folder than default (default is ~/Downloads)
 timeout - timeout before quitting, 0 for indefinite (default)
 numOperations - sender terminates when number of operations are completed (NUM < 0 == unlimited, default)
 */
- (CAMReturnVoid *)receiveFiles:(NSString *)outputPath withTimeout:(NSNumber *)timeout;

/*!
 @method    browse
 @abstract  Browses for available AirDrop peers
 @param     timeout - timeout before quitting, 0 for indefinite (default)
 @return	Returns array of hostnames of the found peers
 */
- (CAMReturnArray *)browse:(NSNumber *)timeout;

/*!
 @method    browseForPeer
 @abstract  Browses for a specified peer until it is found within the timeout period
 @param     host_name - peer to browse for
 timeout - timeout before quitting, 0 for indefinite (default)
 @return	Duration in seconds it took to find the peer. 0 if peer is not found
 */
- (CAMReturnDouble *)browseForPeer:(NSString *)host_name withTimeout:(NSNumber *)timeout;

/*!
 @method    setAirDropMode
 @abstract  Sets Airdrop mode.
 @param     mode - desired mode, case sencitive. One of kAirDropOff, kAirDropContactsOnly or kAirDropEveryone ("Off", "Everyone" or "Contacts Only")
 @return	Returns nothing. Sets error if the mode was not set.
 */
- (CAMReturnVoid *)setAirDropMode:(NSString *)mode;

/*!
 @method    getAirDropMode
 @abstract  Browses for available AirDrop peers
 @return	Returns current mode as a string
 */
- (CAMReturnString *)getAirDropMode;

/*!
 @method    setVerbosity
 @abstract  Sets debug level to control output verbosity
 @param     level - desired level, one of:
 kAirDropVerbosityLevelNone = 0,
 kAirDropVerbosityLevelDefault = 1,
 kAirDropVerbosityLevelHigh = 2,
 kAirDropVerbosityLevelDebug = 3

 */
- (CAMReturnVoid *)setVerbosity:(NSNumber *)level;

#pragma mark - Internal

@end

