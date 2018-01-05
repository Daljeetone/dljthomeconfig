//
//  CAMSpringBoard.h
//  CoreAutomation
//
//  Created by Matt Dreisbach on 1/27/12.
//  Copyright (c) 2012 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CAMReturnValues.h"

#define kCAMSpringBoardShortName springboard

@protocol CAMSpringBoard
@optional

/*!
 @method	isResponsive
 @abstract	Uses a SpringBoard watchdog port to determine if SpringBoard is responsive and accepting requests.
 @return	Immediately returns a CAMReturnBool indicating whether it's responsive or not.
 */
- (CAMReturnBool*)isResponsive;

/*!
 @method	waitUntilIsResponsiveWithTimeout:
 @abstract	Uses a SpringBoard watchdog port to wait until either SpringBoard is responsive or 'timeout' seconds have elapsed.
 @param		timeout
	An NSNumber object representing seconds to wait. Objects are required because this method is proxied to the device.
 @return	Returns a CAMReturnBool indicating whether it's responsive or not. 'YES' indicates it became responsive, 'NO' would indicate the timeout was reached.
 */
- (CAMReturnBool*)waitUntilResponsiveWithTimeout:(NSNumber *)timeout;


/*!
 @method	waitForActiveLayoutWithTimeout:
 @abstract	Uses a Frontboard observer to wait for layout to be displayed. Layout drawn on the UI is a good approximation of when the device interface is ready after restores, reboots, etc.
 @param		timeout
	An NSNumber object representing seconds to wait. Objects are required because this method is proxied to the device.
 @return	Returns a CAMReturnBool indicating whether a layout is displayed or not. 'YES' indicates there is a layout, 'NO' would indicate no UI layout drawn on device.
 */
- (CAMReturnBool*)waitForActiveLayoutWithTimeout:(NSNumber *)timeout;

/*!
 @method	launchApp:
 @abstract	Use SpringBoardServices to launch an application
 @param     suspended - bool indicate whether launch the application then immediately put the application in suspended mode.
            appName - string represent the Application's display name on the springboard. For example, "Safari", "Mail", "Maps"
 @return	Returns a CAMReturnBool indicating whether it's launched or not.
 */
- (CAMReturnBool*)launchApp:(NSString*)appName suspended:(NSNumber*)suspended;

/*!
 @method     launchAppWithBundleID:
 @abstract   Launch an application.
 @param      bundleID The reverse DNS format bundle ID of the app to launch such as "com.apple.springboard" or "com.apple.Maps".
 @return     Returns a CAMReturnBool indicating whether it launched or not.
 */
- (CAMReturnBool *)launchAppWithBundleID:(NSString *)bundleID;

/*!
 @method	terminateApp:
 @abstract	Use SpringBoardServices to terminate an application by App name.
 @return	Returns a CAMReturnBool indicating whether it terminated or not.
 */
- (CAMReturnBool*)terminateApp:(NSString*)appName;

/*!
 @method    terminateAppWithBundleID:
 @abstract  Use SpringBoardServices to terminat an application by BundleID.
 @param     bundleID The reverse DNS format bundle ID of the app to terminate such as "com.apple.Maps".
 @return    Returns a CAMReturnBool indicating whether it terminated or not.
 */
- (CAMReturnBool *)terminateAppWithBundleID:(NSString*)bundleID;

/*!
 @method	getAvailableApps:
 @abstract	Get information for all installed user, system, and internal apps on the device
 @return	Returns a CAMReturnDictionary, the keys are the bundle IDs for the apps, and the values are Dictionaries with all the app information that was available from the installation record.
 */
- (CAMReturnDictionary*)getAvailableApps;

/*!
 @method     getAppState:
 @abstract   Get the application state such as whether it is running in the foreground, background, or suspended.
 @param      bundleID The reverse DNS format bundle ID of the application to query.
 @discussion The possible return values are: "Unknown", "Terminated", "BackgroundTaskSuspended", "BackgroundRunning", "ForegroundRunning", "ProcessServer", and "ForegroundRunningObscured".
 @return     Returns a string representation of the application state.
 */
- (CAMReturnString *)getAppState:(NSString *)bundleID;

/*!
 @method     isAppRunningBackground:
 @abstract   Check if the application is running in the background.
 @param      bundleID The reverse DNS format bundle ID of the application to query.
 @return     Returns a CAMReturnBool indicating if the app is running in the background.
 */
- (CAMReturnBool *)isAppRunningBackground:(NSString *)bundleID;

/*!
 @method     isAppSuspended:
 @abstract   Check if the application is suspended.
 @param      bundleID The reverse DNS format bundle ID of the application to query.
 @return     Returns a CAMReturnBool indicating if the app is suspended.
 */
- (CAMReturnBool *)isAppSuspended:(NSString *)bundleID;

/*!
 @method     isAppRunningForeground:
 @abstract   Check if the application is running in the foreground.
 @param      bundleID The reverse DNS format bundle ID of the application to query.
 @return     Returns a CAMReturnBool indicating if the app is running in the foreground.
 */
- (CAMReturnBool *)isAppRunningForeground:(NSString *)bundleID;

/*!
 @method     getForegroundAppName
 @abstract   Get the name of the foreground app, if any.
 @discussion SpringBoard does not run as a foreground app, it runs as a process server.  If SpringBoard is the "foreground" app, then it will return an empty string.
 @return     Returns a CAMReturnString of the foreground app name.
 */
- (CAMReturnString *)getForegroundAppName;

@end
