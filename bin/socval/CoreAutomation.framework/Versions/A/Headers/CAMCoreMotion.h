//
//  CAMCoreMotion.h
//  CoreAutomation
//
//  Created by Chris Whitney on 1/24/12.
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CAMReturnValues.h"

#define kCAMCoreMotionShortName	coreMotion

@protocol CAMCoreMotion
@optional

#pragma mark -
#pragma mark Accelerometer
- (CAMReturnBool*)isAccelerometerActive;
- (CAMReturnBool*)isAccelerometerAvailable;
- (CAMReturnDouble*)accelerometerUpdateInterval;
- (CAMReturnVoid*)setAccelerometerUpdateInterval:(NSNumber*)interval;
- (CAMReturnVoid*)startAccelerometerUpdates;
- (CAMReturnVoid*)startAccelerometerUpdatesToQueue;
- (CAMReturnVoid*)stopAccelerometerUpdates;
- (CAMReturnDictionary*)accelerometerData;
- (CAMReturnArray*)queuedAccelerometerData;
- (CAMReturnArray*)queuedAccelerometerErrors;
- (CAMReturnArray*)resultsFromClearingAccelerometerDataAndErrors;

#pragma mark -
#pragma mark Gyro
- (CAMReturnBool*)isGyroActive;
- (CAMReturnBool*)isGyroAvailable;
- (CAMReturnDouble*)gyroUpdateInterval;
- (CAMReturnVoid*)setGyroUpdateInterval:(NSNumber*)interval;
- (CAMReturnVoid*)startGyroUpdates;
- (CAMReturnVoid*)startGyroUpdatesToQueue;
- (CAMReturnVoid*)stopGyroUpdates;
- (CAMReturnDictionary*)gyroData;
- (CAMReturnArray*)queuedGyroData;
- (CAMReturnArray*)queuedGyroErrors;
- (CAMReturnArray*)resultsFromClearingGyroDataAndErrors;

#pragma mark -
#pragma mark Magnetometer
- (CAMReturnBool*)isMagnetometerActive;
- (CAMReturnBool*)isMagnetometerAvailable;
- (CAMReturnDouble*)magnetometerUpdateInterval;
- (CAMReturnVoid*)setMagnetometerUpdateInterval:(NSNumber*)interval;
- (CAMReturnVoid*)startMagnetometerUpdates;
- (CAMReturnVoid*)startMagnetometerUpdatesToQueue;
- (CAMReturnVoid*)stopMagnetometerUpdates;
- (CAMReturnDictionary*)magnetometerData;
- (CAMReturnArray*)queuedMagnetometerData;
- (CAMReturnArray*)queuedMagnetometerErrors;
- (CAMReturnArray*)resultsFromClearingMagnetometerDataAndErrors;

#pragma mark -
#pragma mark Motion
- (CAMReturnBool*)isDeviceMotionActive;
- (CAMReturnBool*)isDeviceMotionAvailable;
- (CAMReturnDouble*)deviceMotionUpdateInterval;
- (CAMReturnVoid*)setDeviceMotionUpdateInterval:(NSNumber*)interval;
- (CAMReturnInteger*)availableAttitudeReferenceFrames;
- (CAMReturnInteger*)attitudeReferenceFrame;
- (CAMReturnVoid*)startDeviceMotionUpdates;
- (CAMReturnVoid*)startDeviceMotionUpdatesToQueue;
- (CAMReturnVoid*)startDeviceMotionUpdatesUsingReferenceFrame:(NSNumber*)frame;
- (CAMReturnVoid*)startDeviceMotionUpdatesToQueueUsingReferenceFrame:(NSNumber*)frame;
- (CAMReturnVoid*)stopDeviceMotionUpdates;
- (CAMReturnDictionary*)deviceMotion;
- (CAMReturnArray*)queuedDeviceMotions;
- (CAMReturnArray*)queuedDeviceMotionErrors;
- (CAMReturnArray*)resultsFromClearingDeviceMotionsAndErrors;

#pragma mark -
#pragma mark Six Axis SPI
- (CAMReturnVoid*)startUsing6AxisSensorFusionOnInterval:(NSNumber*)interval fsync:(NSNumber*)fsync bandwidth:(NSNumber*)bandwidth useAccelerometer:(NSNumber*)useAccelerometer;
- (CAMReturnArray*)queued6AxisData;
- (CAMReturnArray*)resultsFromClearing6AxisData;
- (CAMReturnVoid*)stopUsing6AxisSensorFusion;

#pragma mark -
#pragma mark Oscar SideBand Controller
- (CAMReturnVoid*)startSimulatedDeviceMotion:(NSNumber*)deviceMotion;
- (CAMReturnVoid*)stopSimulatedDeviceMotion;

/*!
 @method    supportSimulatedDeviceMotion
 @abstract	It detects if device has oscar sideband support.
 @discussion Internally, this is trying to set the oscar sideband to default mode kCMActivityManagerOscarSidebandStateStationary. And then detect the response. So this will alter the oscar side state.
 */
- (CAMReturnBool*)supportSimulatedDeviceMotion;

#pragma mark -
#pragma mark Pedometer
/*
 @method        isStepCountingAvailable:
 @return        A bool indicating whether step counting is available 
 */
- (CAMReturnBool *)isStepCountingAvailable;
/*
 @method        isDistanceAvailable:
 @return        A bool indicating whether distance is available
 */
- (CAMReturnBool *)isDistanceAvailable;
/*
 @method        isFloorCountingAvailable:
 @return        A bool indicating whether floor counting is available
 */
- (CAMReturnBool *)isFloorCountingAvailable;
/*
 @method        isPaceAvailable:
 @return        A bool indicating whether pace is available
 */
- (CAMReturnBool *)isPaceAvailable;
/*
 @method        createNewPedometer:
 @return        A token (in NSString) to access the new pedometer
 */
- (CAMReturnString *)createNewPedometer;
/*
 @method        deletePedometer:
 */
- (CAMReturnVoid *)deletePedometer:(NSString *)token;
/*
 @method        queryPedometer:startingfrom:to:
 @discussion    Used in pair with getLatestQueryResultOnPedometer:
                Query will NOT be queued. In another word, if you run queryPedometer:startingfrom:to: twice in a row,
                getLatestQueryResultOnPedometer: will return the result from the last one.
 */
- (CAMReturnVoid *)queryPedometer:(NSString *)token startingfrom:(NSDate *)start to:(NSDate *)end;
/*
 @method        getLatestQueryResultOnPedometer:
 @discussion    Query will NOT be queued. In another word, if you run queryStepPedometer:startingfrom:to: twice in a row,
                getLatestQueryResultOnPedometer: will return the result from the last one.
 */
- (CAMReturnDictionary*)getLatestQueryResultOnPedometer:(NSString *)token;
/*
 @method        startPedometerUpdates:
 @discussion    Relating methods getPedometerItems: and stopPedometerUpdates:
                The notification from CoreMotion will be queue up and can be retreive with getPedometerItems:
                Must run stopPedometerUpdates: to stop the notification.
 */
- (CAMReturnVoid *)startPedometerUpdates:(NSString *)token;
/*
 @method        getPedometerItems:
 @discussion    Get an array of pedometer notifications.
                Every time this function is run, the internal cache will be cleaned. The caller is responsible for retaining the data.
                Each item in the array will be a dictionary with following structure however unsupported capabilitied are ommited.
                @"numberOfSteps"   NSNumber*
                @"distance"        NSNumber*
                @"floorsAscended"  NSNumber*
                @"floorsDescended" NSNumber*
                @"currentPace"     NSNumber*
                @"timestamp"       NSDate*
                @"error"           NSError*
 
 */
- (CAMReturnArray *)getPedometerItemsOnPedometer:(NSString *)token;
/*
 @method        stopPedometerUpdates:
 @discussion    stopPedometerUpdates: should be called as soon as pedometer updates is not required to conserve memory
 */
- (CAMReturnVoid *)stopPedometerUpdates:(NSString *)token;

#pragma mark -
#pragma mark Vehicle
/*
 @method        postVehicleDisconnectedNotification:
 @discussion    Post vehice disconnected darwin notification
 */
- (CAMReturnVoid *) postVehicleDisconnectedNotification;

/*
 @method        postVehicleConnectedNotification:
 @discussion    Post vehice connecteded darwin notification
 */
- (CAMReturnVoid *) postVehicleConnectedNotification;

/*
 @method        postVehicleDisconnectedNotificationInternal:
 @discussion    Post vehice disconnected darwin notification internal
 */
- (CAMReturnVoid *) postVehicleDisconnectedNotificationInternal;

/*
 @method        postVehicleConnectedNotificationInternal:
 @discussion    Post vehice connecteded darwin notification internal
 */
- (CAMReturnVoid *) postVehicleConnectedNotificationInternal;

/*
 @method        postVehicleExitNotification:
 @discussion    Post vehice exit darwin notification
 */
- (CAMReturnVoid *) postVehicleExitNotification;
@end

