//
//  CAMGameController.h
//  coreautomationd
//
//  Created by Matthew Lucas on 4/30/13.
//  Copyright 2013 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CAMReturnValues.h"

#define kCAMGameControllerShortName  gameController

//  GCController Keys
#define kCAMGameControllerControllerID              @"controllerID"

//  ButtonInput Keys
#define kCAMGameControllerButtonInputAnalogKey      @"value"
#define kCAMGameControllerButtonInputDigitalKey     @"isPressed"

//  AxisInput Keys
#define kCAMGameControllerAxisInputAnalogKey        @"value"

//  DirectionInput Keys
#define kCAMGameControllerDirectionInputXAxisKey    @"xAxis"
#define kCAMGameControllerDirectionInputYAxisKey    @"yAxis"
#define kCAMGameControllerDirectionInputUpKey       @"up"
#define kCAMGameControllerDirectionInputDownKey     @"down"
#define kCAMGameControllerDirectionInputLeftKey     @"left"
#define kCAMGameControllerDirectionInputRightKey    @"right"

//  Gamepad Keys
#define kCAMGameControllerGamepadKey                @"gamepad"
#define kCAMGameControllerGamepadDpadKey            @"dpad"
#define kCAMGameControllerGamepadButtonAKey         @"buttonA"
#define kCAMGameControllerGamepadButtonBKey         @"buttonB"
#define kCAMGameControllerGamepadButtonXKey         @"buttonX"
#define kCAMGameControllerGamepadButtonYKey         @"buttonY"
#define kCAMGameControllerGamepadLeftShoulderKey    @"leftShoulder"
#define kCAMGameControllerGamepadRightShoulderKey   @"rightShoulder"

//  Extended Gamepad Keys
#define kCAMGameControllerExtendedGamepadKey        @"extendedGamepad"
#define kCAMGameControllerGamepadLeftThumbstickKey  @"leftThumbstick"
#define kCAMGameControllerGamepadRightThumbstickKey @"rightThumbstick"
#define kCAMGameControllerGamepadLeftTriggerKey     @"leftTrigger"
#define kCAMGameControllerGamepadRightTriggerKey    @"rightTrigger"

@protocol CAMGameController
@optional

/*!
 @method    start
 @abstract	Starts the monitoring of GameControllers
 */
- (CAMReturnVoid*)start;

/*!
 @method    stop
 @abstract	Stops the monitoring of GameControllers
 */
- (CAMReturnVoid*)stop;

/*!
 @method    allControllers
 @abstract	The controller objects corresponding to the list of currently connected controllers
 @return    Returns an array of NSDictionaries representing each connected controller.
 */
- (CAMReturnArray*)allControllers;

/*!
 @method    startWirelessControllerDiscovery
 @abstract	Starts the discovery of wireless controllers
 */
- (CAMReturnVoid*)startWirelessControllerDiscovery;

/*!
 @method    stopWirelessControllerDiscovery
 @abstract	Stops the discovery of wireless controllers
 */
- (CAMReturnVoid*)stopWirelessControllerDiscovery;

/*!
 @method    isPausedWithControllerID:
 @abstract	Returns whether we are in a paused state.
 @param controllerID    The controller ID (as returned by allControllers) of the game controller
 */
- (CAMReturnBool*)isPausedWithControllerID:(NSNumber *)controllerID;

/*!
 @method    vendorNameWithControllerID:
 @abstract	Whether the controller supports gamepad type
 @param controllerID    The controller ID (as returned by allControllers) of the game controller
 */
- (CAMReturnString*)vendorNameWithControllerID:(NSNumber *)controllerID;

/*!
 @method    attachedToDeviceWithControllerID:
 @abstract	Whether the controller is physically connected to the device.
 @param controllerID    The controller ID (as returned by allControllers) of the game controller
 */
- (CAMReturnBool*)attachedToDeviceWithControllerID:(NSNumber *)controllerID;

/*!
 @method    playerIndexWithControllerID:
 @abstract	The player index of the controller.
 @param controllerID    The controller ID (as returned by allControllers) of the game controller
 */
- (CAMReturnInteger*)playerIndexWithControllerID:(NSNumber *)controllerID;

/*!
 @method    playerIndexWithControllerID:
 @abstract	The player index of the controller.
 @param controllerID    The controller ID (as returned by allControllers) of the game controller
 */
- (CAMReturnVoid*)setPlayerIndex:(NSNumber *)index withControllerID:(NSNumber *)controllerID;

/*!
 @method    playerIndexUnset
 @abstract	The value used for unset player indexes
 */
- (CAMReturnInteger*)playerIndexUnset;

/*!
 @method    supportsGamepadWithControllerID:
 @abstract	Whether the controllers supports gamepad type
 @param controllerID    The controller ID (as returned by allControllers) of the game controller
 */
- (CAMReturnBool*)supportsGamepadWithControllerID:(NSNumber *)controllerID;

/*!
 @method    supportsExtendedGamepadWithControllerID:
 @abstract	Stops the discovery of wireless controllers
 @param controllerID    The controller ID (as returned by allControllers) of the game controller
 */
- (CAMReturnBool*)supportsExtendedGamepadWithControllerID:(NSNumber *)controllerID;


/*!
 @method    stateWithControllerID:
 @abstract	Returns the current state of the controller
 @param controllerID    The controller ID (as returned by allControllers) of the game controller
 @return    Returns a dictionary representing the controller and sub-dictionaries representing each controller type.
 */
- (CAMReturnDictionary*)stateWithControllerID:(NSNumber *)controllerID;

/*!
 @method    gamepadStateWithControllerID:
 @abstract	Returns the current state of the gamepad
 @param controllerID    The controller ID (as returned by allControllers) of the game controller
 @return    Returns a dictionary representing gamepad state
 */
- (CAMReturnDictionary*)gamepadStateWithControllerID:(NSNumber *)controllerID;

/*!
 @method    extendedGamepadStateWithControllerID:
 @abstract	Returns the current state of the extended gamepad
 @param controllerID    The controller ID (as returned by allControllers) of the game controller
 @return    Returns a dictionary representing the extended gamepad state
 */
- (CAMReturnDictionary*)extendedGamepadStateWithControllerID:(NSNumber *)controllerID;

/*!
 @method    getValueForKey:withControllerID:
 @abstract	Returns the object specified by key.
 @param controllerID    The controller ID (as returned by allControllers) of the game controller
 @return    Returns an object based on the key
 */
- (CAMReturn*)getValueForKey:(NSString *)key withControllerID:(NSNumber *)controllerID;

/*!
 @method    getValueForKeyPath:withControllerID:
 @abstract	Returns the object specified by keyPath.
 @param controllerID    The controller ID (as returned by allControllers) of the game controller
 @return    Returns an object based on the keyPath
 */
- (CAMReturn*)getValueForKeyPath:(NSString *)keyPath withControllerID:(NSNumber *)controllerID;

@end
