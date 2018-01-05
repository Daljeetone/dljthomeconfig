//
//  CAMHID.h
//  CoreAutomation
//
//  Created by Corby Ziesman on 05/10/2013.
//  Copyright (c) 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CAMReturnValues.h"

#define kCAMHIDShortName HID

@protocol CAMHID
@optional


/*!
 @method     startMonitoringForEvents:
 @abstract   This method listens for a list of provided HID events and serializes them. The method will wait indefinitely for matching events. If an
             empty array or nil is passed, it listens for every HID event.
 @param      events - An array of integer values for each hidEvent type enum. For example [35, 3] will listen for GameController and Keyboard events
             respectively.
 @discussion This method clears the buffer before starting to monitor for HID events. To get current state of buffer anytime else, see method
             monitoredEventsBuffer
 @return     Void
 */
- (CAMReturnVoid *)startMonitoringForEvents:(NSArray *)events;

/*!
 @method     stopMonitoring
 @abstract   Stops HID Monitor
 @discussion This method stops monitoring HID events. Related methods are startMonitoringForEvents: and monitoredEventsBuffer.
 @return     Void
 */
- (CAMReturnVoid *)stopMonitoring;

/*!
 @method     monitoredEventsBuffer
 @abstract   Returns the current state of HID Events buffer.
 @discussion Related methods are startMonitoringForEvents: and stopMonitoring.
 @return     CAMReturnDictionary. The keys of the dictionary correspond to the integer value of HID Event type enum. The value is an array of received 
             events for that type. Example, for GameController HID events, @{ @"35" : @[ @{ //event1_dictionary },
                                                                                         @{ //event2_dictionary }]}
 */
- (CAMReturnDictionary *)monitoredEventsBuffer;

/*!
 @method     startHIDReceiverWithTimeout:seconds
 @abstract   Starts HID Monitor with given timeout
 @discussion This is run to start HID monitoring. After the HID events are received, use getReceivedHIDUsages or getReceivedHIDKeystrokes to see the result.
 @return     Void
 */
- (CAMReturnVoid *)startHIDReceiverWithTimeout:(NSNumber *)seconds;

/*!
 @method     getReceivedHIDUsages
 @abstract   Returns an array of received HID events, displaying the usage, usage page, and time received.
 @discussion This is useful to view HID events for keyboards as well as accessories using consumer page such as media remote controls which may have play and pause buttons.
 @return     Array of HID events received.
 */
- (CAMReturnArray *)getReceivedHIDUsages;

/*!
 @method     getReceivedHIDKeystrokes
 @abstract   Returns an array of received keystroke HID events, displaying the key and time received.
 @discussion This is useful to view HID events for keyboards.  The HID usage is translated to the keyboard character.
 @return     Array of HID events received.
 */
- (CAMReturnArray *)getReceivedHIDKeystrokes;

/*!
 @method     listenForHIDEvent:withinTimeout:
 @abstract   This method listens for a provided HID event. The method will wait up to the timeout in seconds for a matching event.
 @param      hidEvent - The hidEvent should be either a keystroke or a usage value. For example kHIDUsage_Csmr_ALDigitalWallet (0x1BA) would be 442.
 @param      seconds - The number of seconds to wait for the HID event.
 @return     Returns YES if the HID event is encountered before the timeout. Otherwise NO is returned.
 */
- (CAMReturnBool *)listenForHIDEvent:(NSNumber*)hidEvent withinTimeout:(NSNumber*)seconds;

@end
