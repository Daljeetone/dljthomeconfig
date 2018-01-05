//
//  CAMShell.h
//  CoreAutomation
//
//  Created by Chris Whitney on 10/25/11.
//  Copyright 2011 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CAMReturnValues.h"

#define kCAMShellShortName os

@protocol CAMShell
@optional

#pragma mark -
#pragma mark Command Execution
/*!
 @method     executeCommand:
 @abstract   Synchronously execute a command-line task.
*/
- (CAMReturnShellTask*)executeCommand:(NSString*)command;

/*!
 @method     executeCommand:
 @abstract   Synchronously execute a command-line task. Optionally provide blocks for periodic updates and completion.
 */
- (CAMReturnShellTask *)executeCommand:(NSString *)command updates:(void (^)(NSString *standardOutput, NSString *standardError))updates completion:(void (^)())completion;

/*!
 @method     executeCommand:arguments:
 @abstract   Synchronously execute a command-line task with an array of arguments.
*/
- (CAMReturnShellTask*)executeCommand:(NSString*)command arguments:(NSArray*)args;

/*!
 @method     executeCommand:arguments:environment:
 @abstract   Synchronously execute a command-line task with an array of arguments and an environment dictionary.
 */
- (CAMReturnShellTask*)executeCommand:(NSString*)command
                            arguments:(NSArray*)args
                          environment:(NSDictionary *)env;

/*!
 @method     executeCommand:arguments:withTimeout:
 @abstract   Synchronously execute a command-line task with an array of arguments within specified timeout period. If timeout reached but process is still running, process will be killed.
 @availability Available in Innsbruck11A279 devices or later.
*/
- (CAMReturnShellTask*)executeCommand:(NSString*)command
                            arguments:(NSArray*)args
                          withTimeout:(NSNumber*)seconds;

/*!
 @method     executeCommand:arguments:environment:withTimeout:
 @abstract   Synchronously execute a command-line task with an array of arguments and an environment dictionary within specified timeout period. If timeout reached but process is still running, process will be killed.
 */
- (CAMReturnShellTask*)executeCommand:(NSString*)command
                            arguments:(NSArray*)args
                          environment:(NSDictionary *)env
                          withTimeout:(NSNumber*)seconds;

/*!
 @method     executeCommand:arguments:withTimeout:updates:completion:
 @abstract   Synchronously execute a command-line task with an array of arguments within specified timeout period. If timeout reached but process is still running, process will be killed. Optionally provide blocks for periodic updates and completion.
 @availability Available in Innsbruck11A279 devices or later.
 */
- (CAMReturnShellTask*)executeCommand:(NSString*)command
                            arguments:(NSArray*)args
                          withTimeout:(NSNumber*)seconds
							  updates:(void (^)(NSString *standardOutput, NSString *standardError))updates
                           completion:(void (^)())completion;

/*!
 @method     executeCommand:arguments:environment:withTimeout:updates:completion:
 @abstract   Synchronously execute a command-line task with an array of arguments and an environment dictionary within specified timeout period. If timeout reached but process is still running, process will be killed. Optionally provide blocks for periodic updates and completion.
 */
- (CAMReturnShellTask*)executeCommand:(NSString*)command
                            arguments:(NSArray*)args
                          environment:(NSDictionary *)env
						  withTimeout:(NSNumber*)seconds
                              updates:(void (^)(NSString *, NSString *))updates
                           completion:(void (^)())completion;

/*!
 @method	executeShellCommand:
 @abstract	A handy "/bin/sh -c $@" wrapper around executeCommand to more easily allow pipes, fh redirects, etc
 @availability Available in Innsbruck11A156 devices or later.
 */
- (CAMReturnShellTask*)executeShellCommand:(NSString*)command NS_SWIFT_NAME(execute(shellCommand:));;

/*!
 @method	executeShellCommand:updates:completion:
 @abstract	A handy "/bin/sh -c $@" wrapper around executeCommand to more easily allow pipes, fh redirects, etc. Optionally provide blocks for periodic updates and completion.
 */
- (CAMReturnShellTask*)executeShellCommand:(NSString*)command
                                   updates:(void (^)(NSString *standardOutput, NSString *standardError))updates
                                completion:(void (^)())completion;

/*!
 @method launchedTaskWithCommand:
 @abstract Asynchronously execute a command.
 @discussion Use other methods to poll the standard output / standard error, and terminate when desired. Make sure to eventually terminate the task to avoid leaving stray processes.
 */
- (CAMReturnAsynchronousShellTask*)launchedTaskWithCommand:(NSString*)command;

/*!
 @method launchedTaskWithCommand:updates:completion:
 @abstract Asynchronously execute a command. Optionally provide blocks for periodic updates and completion.
 @discussion Use other methods to poll the standard output / standard error, and terminate when desired. Make sure to eventually terminate the task to avoid leaving stray processes.
 @availability Available in Innsbruck11A279 devices or later.
 */
- (CAMReturnAsynchronousShellTask *)launchedTaskWithCommand:(NSString*)command
                                                    updates:(void (^)(NSString *standardOutput, NSString *standardError))updates
                                                 completion:(void (^)())completion;

/*!
 @method launchedTaskWithCommand:arguments:
 @abstract Asynchronously execute a command.
 @discussion Use other methods to poll the standard output / standard error, and terminate when desired. Make sure to eventually terminate the task to avoid leaving stray processes.
*/
- (CAMReturnAsynchronousShellTask*)launchedTaskWithCommand:(NSString*)command
                                                 arguments:(NSArray*)args;

/*!
 @method launchedTaskWithCommand:arguments:environment:
 @abstract Asynchronously execute a command.
 @discussion Use other methods to poll the standard output / standard error, and terminate when desired. Make sure to eventually terminate the task to avoid leaving stray processes.
 */
- (CAMReturnAsynchronousShellTask*)launchedTaskWithCommand:(NSString*)command
                                                 arguments:(NSArray*)args
                                               environment:(NSDictionary *)env;

/*!
 @method launchedTaskWithCommand:arguments:updates:completion:
 @abstract Asynchronously execute a command. Optionally provide blocks for periodic updates and completion.
 @discussion Use other methods to poll the standard output / standard error, and terminate when desired. Make sure to eventually terminate the task to avoid leaving stray processes.
 */
- (CAMReturnAsynchronousShellTask *)launchedTaskWithCommand:(NSString *)command
                                                  arguments:(NSArray *)args
													updates:(void (^)(NSString *standardOutput, NSString *standardError))updates
												 completion:(void (^)())completion;

/*!
 @method launchedTaskWithCommand:arguments:environment:updates:completion:
 @abstract Asynchronously execute a command. Optionally provide blocks for periodic updates and completion.
 @discussion Use other methods to poll the standard output / standard error, and terminate when desired. Make sure to eventually terminate the task to avoid leaving stray processes.
 */
- (CAMReturnAsynchronousShellTask*)launchedTaskWithCommand:(NSString*)command
                                                 arguments:(NSArray*)args
                                               environment:(NSDictionary *)env
												   updates:(void (^)(NSString *standardOutput, NSString *standardError))updates
												completion:(void (^)())completion;

/*!
 @method launchedNoHUPTaskWithCommand:arguments:
 @abstract Asynchronously execute a command, and don't kill it when coreautomationd exits.
 @discussion Use other methods to poll the standard output / standard error, and terminate when desired. Make sure to eventually terminate the task to avoid leaving stray processes. Abusing this without manually managing your processes may lead to filling up the device's proc table, resulting in CAM service exceptions: "unable to start service coreautomationd."
 @availability Available in Innsbruck11A249 devices or later.
 */
- (CAMReturnAsynchronousShellTask*)launchedNoHUPTaskWithCommand:(NSString*)command
                                                      arguments:(NSArray*)args;

/*!
 @method launchedNoHUPTaskWithCommand:arguments:environment:
 @abstract Asynchronously execute a command, and don't kill it when coreautomationd exits.
 @discussion Use other methods to poll the standard output / standard error, and terminate when desired. Make sure to eventually terminate the task to avoid leaving stray processes. Abusing this without manually managing your processes may lead to filling up the device's proc table, resulting in CAM service exceptions: "unable to start service coreautomationd."
 @availability Available in Innsbruck11A249 devices or later.
 */
- (CAMReturnAsynchronousShellTask*)launchedNoHUPTaskWithCommand:(NSString*)command
                                                      arguments:(NSArray*)args
                                                    environment:(NSDictionary *)env;

/*!
 @method launchedNoHUPTaskWithCommand:arguments:updates:completion:
 @abstract Asynchronously execute a command, and don't kill it when coreautomationd exits. Optionally provide blocks for periodic updates and completion.
 @discussion Use other methods to poll the standard output / standard error, and terminate when desired. Make sure to eventually terminate the task to avoid leaving stray processes. Abusing this without manually managing your processes may lead to filling up the device's proc table, resulting in CAM service exceptions: "unable to start service coreautomationd."
 */
- (CAMReturnAsynchronousShellTask *)launchedNoHUPTaskWithCommand:(NSString *)command
                                                       arguments:(NSArray *)args
                                                         updates:(void (^)(NSString *standardOutput, NSString *standardError))updates
                                                      completion:(void (^)())completion;

/*!
 @method launchedNoHUPTaskWithCommand:arguments:environment:updates:completion:
 @abstract Asynchronously execute a command, and don't kill it when coreautomationd exits. Optionally provide blocks for periodic updates and completion.
 @discussion Use other methods to poll the standard output / standard error, and terminate when desired. Make sure to eventually terminate the task to avoid leaving stray processes. Abusing this without manually managing your processes may lead to filling up the device's proc table, resulting in CAM service exceptions: "unable to start service coreautomationd."
 */
- (CAMReturnAsynchronousShellTask *)launchedNoHUPTaskWithCommand:(NSString *)command
                                                       arguments:(NSArray *)args
                                                     environment:(NSDictionary *)env
                                                         updates:(void (^)(NSString *standardOutput, NSString *standardError))updates
                                                      completion:(void (^)())completion;

/*!
 @method statusOfTaskWithUUID:
 @abstract Update the status of a previously launched task.
 @param uuid The unique identifier of a previously launched task. Use -[CAMReturnAsynchronousShellTask UUID].
 @code
	CAMReturnAsynchronousShellTask* task = [[device os] launchCommand:@"/usr/bin/fs_usage"];
	// Handle [task error] if necessary. Wait a bit...

	// ...then ask for an updated version of the task. Usually this would done in a polling loop.
	task = [[device os] statusOfTaskWithUUID:[task UUID]];

	// The data is now fresh.
	NSLog(@"New standard output: %@", [task standardOutput]);
 @endcode
*/
- (CAMReturnAsynchronousShellTask*)statusOfTaskWithUUID:(NSString*)uuid;

/*!
 @method statusOfTaskWithUUID:resetOutput:
 @abstract Update the status of a previously launched task and optionally clear the saved output for that task.
 @param uuid The unique identifier of a previously launched task. Use -[CAMReturnAsynchronousShellTask UUID].
 @discussion Setting resetOutput to [NSNumber numberWithBool:YES] will empty the saved standardOutput and standardError after the data is gathered.
			 Thus, resetOutput can be used when polling for only the new data since the last poll.
             Or use as necessary to reduce device-side memory consumption for verbose, long-running tasks.
*/
- (CAMReturnAsynchronousShellTask*)statusOfTaskWithUUID:(NSString*)uuid resetOutput:(NSNumber*)flag;


/*!
 @method terminateTaskWithUUID:
 @abstract Terminate a previously launched task.
 @param uuid The unique identifier of a previously launched task. Use -[CAMReturnAsynchronousShellTask UUID].
 @discussion Sends SIGTERM. If the task is still running after 10 seconds, sends SIGKILL.
			 After terminating a task, the UUID is invalid.
 @return An updated version of the task's information.
*/
- (CAMReturnAsynchronousShellTask*)terminateTaskWithUUID:(NSString*)uuid;

/*!
 @method terminateAllCommands
 @abstract Terminate all previously launched tasks that are still running.
 @discussion Sends SIGTERM to all tasks. If any task is still running after 10 seconds, sends SIGKILL to that task.
 */
-(CAMReturnVoid*)terminateAllTasks;

/*!
 @method signalTaskWithUUID:withSignal:
 @abstract Signal a previously launched task with a signal number.
 */
- (CAMReturnAsynchronousShellTask *)signalTaskWithUUID:(NSString *)uuid withSignal:(NSNumber *)signal;

#pragma mark -
#pragma mark Sleep
/*!
 @method sleep
 @abstract Sleep the device for 30 seconds.
 @discussion This function runs sleepForCycles with a sleep time of 30 seconds.
*/
- (CAMReturnVoid*)sleep;

/*!
 @method sleepForCycles
 @abstract Sleep the device using the SleepCycler binary.
 @param cycles The number of sleep cycles to perform.
 @param sleepSeconds The number of seconds to sleep for.
 @param awakeSeconds The number of seconds to remain awake for.
 @discussion After this function returns, the SleepCycler binary is run on the device.
*/
- (CAMReturnVoid*)sleepForCycles:(NSNumber *)cycles secondsToSleep:(NSNumber *)sleepSeconds secondsToRemainAwake:(NSNumber *)awakeSeconds;

#pragma mark -
#pragma mark File System
/*!
 @method	contentsOfDirectoryAtPath:
 @abstract	Returns an NSArray containing a list of the path contents if no errors occured.
 */
- (CAMReturnArray*)contentsOfDirectoryAtPath:(NSString*)path;

/*!
 @method	contentsOfDirectoryAtPath:recursively:
 @abstract	Returns an NSArray containing a list of the path contents if no errors occured.
 @param recursive If not zero, it will return the deep listing of the directory.
 */
- (CAMReturnArray*)contentsOfDirectoryAtPath:(NSString*)path recursively:(NSNumber*)recursive;

/*!
 @method	contentsOfDirectoryAtPath:recursively:includingPropertiesForKeys:options
 @abstract	Returns a dictionary containing a list of the path contents if no errors occured including key properties that were requested.
 @discussion Since we can't pass NSURL object types back and forth, the returned items would be the url path strings.
 @param path The path for the directory whose contents you want to enumerate.
 @param recursive If not zero, it will return the deep listing of the directory.
 @param keys An array of keys that identify the file properties that you want pre-fetched for each item in the directory. For each returned item, the specified properties are fetched and returned in related dictionary. These are CFURL resource property keys.
 @param mask Options for the enumeration. These are NSFileManager directory enumeration options.
 @return Returns a dictionary of paths that match the criteria given. The key is the path, and the value is a dictionary with property key values requested for that path.
 */
- (CAMReturnDictionary *)contentsOfDirectoryAtPath:(NSString *)path recursively:(NSNumber *)recursive includingPropertiesForKeys:(NSArray *)keys options:(NSNumber *)mask;

/*!
 @method	fileExistsAtPath:
 @abstract	Returns true if and only if the path (or path it links to) is a file.
 */
- (CAMReturnBool*)fileExistsAtPath:(NSString*)path;

/*!
 @method	directoryExistsAtPath:
 @abstract	Returns true if and only if the path (or path it links to) is a directory.
 */
- (CAMReturnBool*)directoryExistsAtPath:(NSString*)path;

/*!
 @method	destinationOfSymbolicLinkAtPath:
 @abstract	Returns the path of a symlink.
 */
- (CAMReturnString*)destinationOfSymbolicLinkAtPath:(NSString*)path;

/*!
 @method	removeItemAtPath:
 @abstract	Deletes the item at the specified path.
 */
- (CAMReturnBool*)removeItemAtPath:(NSString *)path;

/*!
 @method	copyItemAtPath:toPath
 @abstract	Copies the item at the specified path.
 */
- (CAMReturnBool *)copyItemAtPath:(NSString *)srcPath toPath:(NSString *)dstPath NS_RETURNS_NOT_RETAINED;

/*!
 @method	moveItemAtPath:toPath
 @abstract	Moves the item at the specified path.
 */
- (CAMReturnBool *)moveItemAtPath:(NSString *)srcPath toPath:(NSString *)dstPath;

/*!
 @method	createDirectoryAtPath:withIntermediateDirectories:attributes
 @abstract	Creates directories at specified path with intermediate folders with given attributes.
 */
- (CAMReturnBool *)createDirectoryAtPath:(NSString *)path withIntermediateDirectories:(NSNumber *)createIntermediates attributes:(NSDictionary *)attributes;



- (CAMReturnVoid *)registerForDistributedNotificationsNamed:(NSString *)name sender:(NSString *)sender;
- (CAMReturnVoid *)unregisterForDistributedNotifications;
- (CAMReturnVoid *)postDistributedNotificationNamed:(NSString *)name payload:(NSDictionary *)payload;
- (CAMReturnArray *)retrieveAllDistributedNotifications;
- (CAMReturnArray *)waitForAndRetrieveDistributedNotificationsWithTimeout:(NSNumber *)timeout;


#pragma mark -
#pragma mark Internal
- (CAMReturnArray*)versionInformation;
- (CAMReturnVoid*)markLogWithString:(NSString*)label;
- (CAMReturnArray*)pathsToCrashLogsInDirectory:(NSString*)directoryPath;
- (CAMReturnArray*)pathsToAllCrashLogs;
- (CAMReturnDouble*)timeIntervalSinceReferenceDate;


@end
