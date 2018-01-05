//
//  CAMCoreLocation.h
//  CoreAutomation
//
//  Created by Chris Whitney on 1/17/12.
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CAMReturnValues.h"

#define kCAMCoreLocationShortName coreLocation

@protocol CAMCoreLocation
@optional

#pragma mark -
#pragma mark Availability
- (CAMReturnBool*)locationServicesEnabled;
- (CAMReturnBool*)headingAvailable;
/*!
 @deprecated	Use isMonitoringAvailableForClass instead.
 @method		regionMonitoringAvailable:
 @abstract      Query whether region monitoring is avaliable
 @return		A BOOL set to YES if the region monitoring is available otherwise NO.
 */
- (CAMReturnBool*)regionMonitoringAvailable  __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_4_0,__IPHONE_7_0);

/*!
 @deprecated	Use isMonitoringAvailableForClass: and authorizationStatus: instead.
 @method		regionMonitoringEnabled:
 @abstract      Query whether region monitoring is enabled
 @return		A BOOL set to YES if the region monitoring is enabled otherwise NO.
 */
- (CAMReturnBool*)regionMonitoringEnabled __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_4_0,__IPHONE_7_0);


/*!
 @method		isMonitoringAvailableForClass:
 @abstract      Query whether monitoring is avaliable for a CLRegion class.
 @param         classNameString class name in string.
 @return		A BOOL set to YES if the region monitoring is enabled otherwise NO.
 */
- (CAMReturnBool*)isMonitoringAvailableForClass:(NSString*)classNameString;
/*!
 @method		significantLocationChangeMonitoringAvailable
 @abstract      Query whether significan Location Change monitoring is available
 @return		A BOOL set to YES if the significan Location change monitoring is available otherwise NO.
 */
- (CAMReturnBool*)significantLocationChangeMonitoringAvailable;
/*!
 @method		deferredLocationUpdatesAvailable
 @abstract      Query whether defferred location update is available
 @return		A BOOL set to YES if the defferred location update is available otherwise NO.
 */
- (CAMReturnBool*) deferredLocationUpdatesAvailable;

#pragma mark -
#pragma mark One-shot location
- (CAMReturnDictionary*)locationWithDesiredAccuracy:(NSNumber*)accuracy requireAccuracy:(NSNumber*)filterAccuracy requireTechnology:(NSNumber*)filterType withinTimeout:(NSNumber*)timeout ignoreLocationUnknown:(NSNumber*)maskUnknown;

#pragma mark -
#pragma mark Location

/*! Method  setDesiredAccuracy:.
 *          will pass a value to CLLocationManager's desiredAccuracy property
 * \param   accuracy NSNumber double  
 * \return  Void 
 */
- (CAMReturnVoid*)setDesiredAccuracy:(NSNumber*)accuracy;

/*! Method  desiredAccuracy.
 *          Returns the value of CLLocationManager's desiredAccuracy property.
 * \return  A CLLocationAccuracy (double ) in meters. 
 */
- (CAMReturnDouble*)desiredAccuracy;

/*! Method  setDistanceFilter:. 
 *          Will pass a value to CLLocationManager's distanceFilter property, The value should be a double (expressing meters).
 * \param   distance NSNumber double
 * \return  Void
 */
- (CAMReturnVoid*)setDistanceFilter:(NSNumber*)distance;

/*! Method  distanceFilter. 
 *          Returns the value of CLLocationManager's distanceFilter property.
 * \return  CLLocationDistance (double) in meters.
 */
- (CAMReturnDouble*)distanceFilter;

/*! Method  startUpdatingLocation. 
 *          Calls CLLocationManager's startUpdatingLocation, and start recording locations.
 * \return	Void
 */
- (CAMReturnVoid*)startUpdatingLocation;

/*! Method  stopUpdatingLocation. 
 *          Calls CLLocationManager's stopUpdatingLocation, and stop recording locations.
 * \return  Void
 */
- (CAMReturnVoid*)stopUpdatingLocation;

/*! Method  location. 
 *          Retrieves the last location received.
 * \return	An dictionary representing the CLLocation object (or nil).
 */
- (CAMReturnDictionary*)location;

/*! Method  recordedLocations. 
 *          Retrieve the locations recorded until now.
 * \return	An array of dictionary objects representing CLLocations objects received (chronological order).
 */
- (CAMReturnArray*)recordedLocations;

/*! Method  recordedLocationErrors. 
 *          Retrieves any location errors recorded until now.
 * \return  An array of dictionary objects representing NSError objects received (chronological order).
 */
- (CAMReturnArray*)recordedLocationErrors;

/*! Method  resultsFromClearingLocationsAndErrors. 
 *          Returns the current values of the recordedLocations and recordedLocationErrors arrays, then clear them both.
 *          Use resultsFromClearingLocationsAndErrors when periodically polling for new locations.
 *          This ensures that the stored locations do not grow without bound, and makes distinguishing new locations easier.
 * \return	An array containing two objects: the value of recordedLocations, then the value of recordedLocationErrors.
 */
- (CAMReturnArray*)resultsFromClearingLocationsAndErrors;

/*! Method  fetchPredictedConditionsForActionType.
 *          Returns the predicted conditions for the action type.
 * \return	An array containing the predicted condition objects.
 */
- (CAMReturnArray *)fetchPredictedConditionsForActionType:(NSNumber*)actionType;

#pragma mark -
#pragma mark Significant Location Change

/*! Method  startMonitoringSignificantLocationChanges. 
 *          Calls CLLocationManager's startMonitoringSignificantLocationChanges.
 * \return  Void
 */
- (CAMReturnVoid*)startMonitoringSignificantLocationChanges;

/*! Method  stopMonitoringSignificantLocationChanges. 
 *          Calls CLLocationManager's stopMonitoringSignificantLocationChanges.
 * \return  Void
 */
- (CAMReturnVoid*)stopMonitoringSignificantLocationChanges;

/*! Method  recordedSignificantChangeLocations. 
 *          Retrieves the significant location change notifications recorded until now.
 * \return  An array of dictionary objects representing CLLocations objects received (chronological order).
 */
- (CAMReturnArray*)recordedSignificantChangeLocations;

/*! Method  recordedSignificantChangeLocationErrors.
 *          Retrieves any significant location change errors recorded until now.
 * \return	An array of dictionary objects representing NSError objects received (chronological order).
 */
- (CAMReturnArray*)recordedSignificantChangeLocationErrors;

/*! Method  resultsFromClearingSignificantChangeLocationsAndErrors.
 *          Returns the current values of the recordedSignificantChangeLocations and recordedSignificantChangeLocationErrors arrays, then clear them both.
 *          Use when periodically polling for new locations. This ensures that the stored locations do not grow without bound, and makes distinguishing new locations easier.
 * \return	An array containing two objects: the value of recordedSignificantChangeLocations, then the value of recordedSignificantChangeLocationErrors.
 */
- (CAMReturnArray*)resultsFromClearingSignificantChangeLocationsAndErrors;


#pragma mark -
#pragma mark Deferred Location Update
/*!
 @method    allowDeferredLocationUpdatesUntilTraveled:timeout:
 @param     distance Exit condition
 @param     timeout Exit condition
 */
- (CAMReturnVoid*)allowDeferredLocationUpdatesUntilTraveled:(NSNumber*)distance timeout:(NSNumber*)timeout;
/*!
 @method    disallowDeferredLocationUpdates
 */
- (CAMReturnVoid*)disallowDeferredLocationUpdates;
/*!
 @method    deferredUpdatesWithErrorAndClear
            This call will also clean the internal cache for update.
 @return    An array contains errors for deferred update
 */
- (CAMReturnArray*)deferredUpdatesWithErrorAndClear;
/*!
 @method    setPausesLocationUpdatesAutomatically:
 @param     flag true or flase in NSNumber format
 */
- (CAMReturnVoid*)setPausesLocationUpdatesAutomatically:(NSNumber*)flag;


#pragma mark -
#pragma mark Region Monitoring
/*!
 @method    maximumRegionMonitoringDistance
 @abstract	The value of CLLocationManager's maximumRegionMonitoringDistance property.
 @return	a number containing a CLLocationDistance (double) in meters
 */
- (CAMReturnDouble*)maximumRegionMonitoringDistance;

/*!
 @method    monitoredRegions
 @abstract	Retrieve any regions that are currently being monitored.
 @return	An NSArray of dictionary objects representing CLRegion objects.
 */
- (CAMReturnArray*)monitoredRegions;

/*!
 @method    startMonitoringForRegion:
 @abstract	Start monitoring a region (specified by the keys "center", "radius", and "identifier").
 */
- (CAMReturnVoid*)startMonitoringForRegion:(NSDictionary *)regionDict;

/*!
 @method    stopMonitoringForRegion:
 @abstract	Stop monitoring a region (specified by the keys "center", "radius", and "identifier").
 */
- (CAMReturnVoid*)stopMonitoringForRegion:(NSDictionary*)regionDict;

/*!
 @method    recordedStartedMonitoringRegions
 @abstract	Retrieve any regions that have succesfully started monitoring.
 @return	An array of dictionary objects representing CLRegion objects received (chronological order).
 */
- (CAMReturnArray*)recordedStartedMonitoringRegions;

/*!
 @method    recordedEnteredRegions
 @abstract	Retrieve any regions entered until now.
 @return	An array of dictionary objects representing CLRegion objects received (chronological order).
 */
- (CAMReturnArray*)recordedEnteredRegions;

/*!
 @method    recordedExitedRegions
 @abstract	Retrieve any regions exited until now.
 @return	An array of dictionary objects representing CLRegion objects received (chronological order).
 */
- (CAMReturnArray*)recordedExitedRegions;

/*!
 @method    recordedRegionErrors
 @abstract	Retrieve any region errors recorded until now.
 @return	An array of [dictionary, dictionary] pairs representing CLRegion, NSError pairs received (chronological order).
 */
- (CAMReturnArray*)recordedRegionErrors;

/*!
 @method     resultsFromClearingRegionNotificationsAndErrors
 @abstract	 Return the current values of recordedStartedMonitoringRegions, recordedEnteredRegions, recordedExitedRegions and recordedRegionErrors arrays, then clear them all.
 @discussion Use when periodically polling for new region information. This ensures that the stored region notifications do not grow without bound, and makes distinguishing new notifications easier.
 @return	 An array containing four objects: the values of recordedStartedMonitoringRegions, recordedEnteredRegions, recordedExitedRegions, and recordedHeadingErrors.
 */
- (CAMReturnArray*)resultsFromClearingRegionNotificationsAndErrors;

/*!
 @method     region:containsCoordinate:
 @abstract	 Test if a region (dictionary representation of a CLRegion object) contains a given coordinate (array representation of a latitude / longitude pair). Calls -[CLRegion containsCoordinate:].
 @return	 A BOOL set to YES if the region contains the given coordinate, otherwise NO.
 */
- (CAMReturnBool*)region:(NSDictionary*)regionDict containsCoordinate:(NSArray*)coordinatePair;


#pragma mark -
#pragma mark Heading
/*!
 @method    setHeadingOrientation:
 @abstract	Sets the value for CLLocationManager's setHeadingOrientation.
 @param		orientation		An int enum value from CLDeviceOrientation
 */
- (CAMReturnVoid*)setHeadingOrientation:(NSNumber*)orientation;

/*!
 @method    headingOrientation
 @abstract	The value of CLLocationManager's headingOrientation property.
 @return	An int enum value from CLDeviceOrientation
 */
- (CAMReturnInteger*)headingOrientation;

/*!
 @method    setHeadingFilter:
 @abstract	Sets the value for CLLocationManager's setHeadingFilter.
 @param		filter		A double representing degrees (CLLocationDegrees)
 */
- (CAMReturnVoid*)setHeadingFilter:(NSNumber*)filter;

/*!
 @method    headingFilter
 @abstract	The value of CLLocationManager's headingFilter property.
 @return	A double representing degrees (CLLocationDegrees)
 */
- (CAMReturnDouble*)headingFilter;

/*!
 @method    startUpdatingHeading
 @abstract	Call CLLocationManager's startUpdatingHeading, and start recording headings.
 */
- (CAMReturnVoid*)startUpdatingHeading;

/*!
 @method    stopUpdatingHeading
 @abstract	Call CLLocationManager's stopUpdatingHeading, and stop recording headings.
 */
- (CAMReturnVoid*)stopUpdatingHeading;

/*!
 @method    heading
 @abstract	Retrieve the last heading received.
 @return	A dictionary representing the CLHeading object (or nil).
 */
- (CAMReturnDictionary*)heading;

/*!
 @method    recordedHeadings
 @abstract	Retrieve any headings recorded until now.
 @return	An array of dictionary objects representing CLHeading objects received (chronological order).
 */
- (CAMReturnArray*)recordedHeadings;

/*!
 @method    recordedHeadingErrors
 @abstract	Retrieve any heading errors recorded until now.
 @return	An array of dictionary objects representing NSError objects received (chronological order).
 */
- (CAMReturnArray*)recordedHeadingErrors;

/*!
 @method     resultsFromClearingHeadingsAndErrors
 @abstract	 Return the current values of the recordedHeadings and recordedErrors arrays, then clear them both.
 @discussion Use resultsFromClearingHeadingsAndErrors when periodically polling for new headings.
 This ensures that the stored headings do not grow without bound, and makes distinguishing new headings easier.
 @return	 An array containing two objects: the value of recordedHeadings, then the value of recordedHeadingErrors.
 */
- (CAMReturnArray*)resultsFromClearingHeadingsAndErrors;

/*!
 @method    displaysHeadingCalibration
 @abstract	The value that will be returned for the CLLocationManagerDelegate method locationManagerShouldDisplayHeadingCalibration.
 */
- (CAMReturnBool*)displaysHeadingCalibration;

/*!
 @method    setDisplaysHeadingCalibration:
 @abstract	Sets the value returned for the CLLocationManagerDelegate method locationManagerShouldDisplayHeadingCalibration.
 */
- (CAMReturnVoid*)setDisplaysHeadingCalibration:(NSNumber*)flag;

/*!
 @method    dismissHeadingCalibrationDisplay
 @abstract	Call CLLocationManager's dismissHeadingCalibrationDisplay, which will dismiss the calibration alert.
 */
- (CAMReturnVoid*)dismissHeadingCalibrationDisplay;


#pragma mark -
#pragma mark Geocoding
/*!
 @method    reverseGeocodeLocation:withinTimeout:
 @abstract	Call CLGeocoder's reverseGeocodeLocation and return the resulting placemarks
 */
- (CAMReturnArray*)reverseGeocodeLocation:(NSDictionary*)location withinTimeout:(NSNumber*)timeout;

/*!
 @method    geocodeAddressDictionary:withinTimeout:
 @abstract	Call CLGeocoder's geocodeAddressDictionary: and return the resulting placemarks
 @discussion Build up the address dictionary using the keys defined in AddressBook
 */
- (CAMReturnArray*)geocodeAddressDictionary:(NSDictionary*)address withinTimeout:(NSNumber*)timeout;

/*!
 @method    geocodeAddressString:withinTimeout:
 @abstract	Call CLGeocoder's geocodeAddressString: and return the resulting placemarks
 */
- (CAMReturnArray*)geocodeAddressString:(NSString*)address withinTimeout:(NSNumber*)timeout;

/*!
 @method    geocodeAddressString:inRegion:withinTimeout:
 @abstract	Call CLGeocoder's geocodeAddressString:inRegion: and return the resulting placemarks
 @discussion The region provides a hint to the geocoder. The region is defined by {"center": {"latitude":<value>, "longitude":<value>}, "radius":<value>, "identifier":<string>}
 */
- (CAMReturnArray*)geocodeAddressString:(NSString*)address inRegion:(NSDictionary*)region withinTimeout:(NSNumber*)timeout;

#pragma mark -
#pragma mark Location Simulation

/*!
 *  @discussion Returns an array of NSString objects representing available simulation scenarios.  Pass one of these objects as the argument to selectScenario: to prepare that scenario.
 */
- (CAMReturnArray*)availableScenarios;

/*!
 * @discussion Returns the localized display name of a scenario returned from availableScenarios.
 */
- (CAMReturnString*)localizedNameForScenario:(NSString*)scenario;

/*!
 * @discussion  Loads an available scenario (returned by availableScenarios).  You must still call startLocationSimulation to begin the execution of the selected scenario.
 */
- (CAMReturnVoid*)selectScenario:(NSString*)scenario;

/*!
 * @discussion Loads a scenario from a particular URL.  Only file-based URLs are accepted.
 *      This method is not normally used.  Instead, select an available scenario using the selectScenario: method.
 */
- (CAMReturnVoid*)loadScenarioFromURL:(NSURL*)url;

#define CAMLocationSimulationDeliveryBehaviorPassThrough [NSNumber numberWithInt:0]
#define CAMLocationSimulationDeliveryBehaviorConsiderType [NSNumber numberWithInt:1]

/*!
 *	@brief	Set the simulation to either act as new location provider, or override existing providers (based on the location's type).
 */
- (CAMReturnVoid*)setLocationDeliveryBehavior:(NSNumber*)deliveryType;

/*!
 *	@brief	Determine if the simulation is acting as new location provider, or overriding existing providers (based on the location's type).
 */
- (CAMReturnInteger*)locationDeliveryBehavior;

/*!
 *	@brief	Clears any pending simulated locations.
 */
- (CAMReturnVoid*)clearSimulatedLocations;

/*!
 *	@brief	Add a simulated location.
 *
 *	If neither of the locationDistance or locationInterval properties are set,
 *  the location will be delivered immediately.  Otherwise, interpolation will take place between
 *  the previous simulated location and the newly appended location.
 *
 *  Locations will not be delivered until startLocationSimulation is called.
 */
- (CAMReturnVoid*)appendSimulatedLocation:(NSDictionary*)locationDict;

/*!
 *	@brief Set the distance that should be traveled between location notifications delivered by the location manager.
 *
 *	Specify at most one of locationDistance or locationInterval.  If neither property is set,
 *	then no interpolation will take place between passed in locations.  If both properties
 *	are set, the most recently set value will be used.
 */
- (CAMReturnVoid*)setLocationDistance:(NSNumber*)value;

/*!
 *	@brief	Specifies the distance that will be traveled between location notifications delivered by the location manager.
 */
- (CAMReturnDouble*)locationDistance;

/*!
 *	@brief Set the frequency of location notifications delivered by the location manager.
 *
 *	Specify at most one of locationDistance or locationInterval.  If neither property is set,
 *	then no interpolation will take place between passed in locations.  If both properties
 *	are set, the most recently set value will be used.
 */
- (CAMReturnVoid*)setLocationInterval:(NSNumber*)value;

/*!
 *	@brief Specifies the frequency of location notifications delivered by the location manager.
 */
- (CAMReturnDouble*)locationInterval;

/*!
 * @brief  Set the speed at which interpolation between locations should take place.
 *
 *	This property will only be effective if one of locationDistance or locationInterval is specified.
 *	Note that setting this property does not affect the speed property on the CLLocation objects passed
 *	through the location manager.  If this property isn't set, a default value will be used.
 */
- (CAMReturnVoid*)setLocationSpeed:(NSNumber*)value;

/*!
 * @brief  Specifies the speed at which interpolation between locations should take place.
 */
- (CAMReturnDouble*)locationSpeed;

// send kCLErrorLocationUnavailable after lifespan expires
#define CAMLocationSimulationRepeatBehaviorSendUnavailable [NSNumber numberWithInt:0]
// repeat the last entry if of limited lifespan
#define CAMLocationSimulationRepeatBehaviorRepeatLastEntry [NSNumber numberWithInt:1]

/*!
 *	@brief Set if and how simulated locations should be delivered after the last location is reached.
 *
 *	The default value is CLSimulationRepeatBehaviorUnavailable.
 */
- (CAMReturnVoid*)setLocationRepeatBehavior:(NSNumber*)value;

/*!
 *	@brief Specifies the speed at which interpolation between locations should take place.
 */
- (CAMReturnInteger*)locationRepeatBehavior;

/*!
 *	@brief Start location simulation.
 */
- (CAMReturnVoid*)startLocationSimulation;

/*!
 *	@brief Stop location simulation.
 */
- (CAMReturnVoid*)stopLocationSimulation;


#pragma mark -
#pragma mark WiFi simulation

/*!
 *	@brief Set the results that should be returned from the next WiFi scan.
 *
 *	The parameter is an array of NSString objects representing the WiFi MAC addresses to be returned by the scan.
 *	Note that while these results take effect immediately once startWifiSimulation is called, they will not be
 *	retrieved for the purposes of location until the daemon requests a scan.
 */
- (CAMReturnVoid*)setWifiScanResults:(NSArray *)results;

/*!
 *	@brief	Set the simulated WiFi power state.
 *
 *	The default is for WiFi power to be on.
 *	This value will not take effect until startWifiSimulation is called.
 */
- (CAMReturnVoid*)setSimulatedWifiPower:(NSNumber*)power;

/*!
 *	@brief	Start WiFi simulation.
 */
- (CAMReturnVoid*)startWifiSimulation;

/*!
 *	@brief	Stop WiFi simulation.
 */
- (CAMReturnVoid*)stopWifiSimulation;


#pragma mark -
#pragma mark Cell simulation

/*!
 *	@brief	Set the serving cell to be used for the purposes of location.
 *	The argument is a cell in the format returned by _CTServerConnectionCellMonitorGetCellInfo.
 *	See <CoreTelephony/CTCellMonitorTypes.h> for details.
 *	The daemon will be notified of the change in serving cell.
 *	The serving cell will not take effect until startCellSimulation is called.
 */
- (CAMReturnVoid*)setSimulatedCell:(NSDictionary *)cell;

/*!
 *	@brief	Set the simulated cell registration status.
 *	The default is for the device to be registered.
 *	This value will not take effect until startCellSimulation is called.
 */
- (CAMReturnVoid*)setSimulatedCellRegistrationStatus:(NSNumber*)registered;

/*!
 *	@brief	Start cell simulation.
 */
- (CAMReturnVoid*)startCellSimulation;

/*!
 *	@brief	Stop cell simulation.
 */
- (CAMReturnVoid*)stopCellSimulation;


#pragma mark -
#pragma mark CL Internal
/*!
 @method    technologiesInUse
 @abstract  Determine which technologies (Cellular, WiFi, GPS, etc) Core Location is currently using.
 @return	Returns an array of values from the
 CLLocationType enum, representing the location technologies currently in use.
 */
- (CAMReturnArray*)technologiesInUse;

/*!
 @method    setLocationServicesEnabled:
 @abstract  Globally enable or disable location services.
 */
- (CAMReturnVoid*)setLocationServicesEnabled:(NSNumber*)flag;

/*!
 @method    resetApps
 @abstract  Reset the location warnings for all apps.
 */
- (CAMReturnVoid*)resetApps;

/*!
 @method        authorizationStatusForBundleIdentifier:
 @discussion    Wrapper for [CLLocationManager authorizationStatusForBundleIdentifier:].
                The return value is translated from enum into string.
 */
- (CAMReturnString *)authorizationStatusForBundleWithIdentifier:(NSString *)bundleID;

/*!
 @method        authorizationStatusForBundleIdentifier:
 @discussion    Wrapper for [CLLocationManager authorizationStatusForBundleIdentifier:].
                Use the effective bundle.
 */
- (CAMReturnString*)authorizationStatus;

/*!
 @method        setAuthorizationStatusByType:forBundleIdentifier:
 @discussion    Wrapper for [CLLocationManager setAuthorizationStatusByType:forBundleIdentifier:]
                Takes an int value mapping to CLAuthorizationStatus and the name for the bundle e.g. "com.apple.Maps"
                Allows more fine-grained control than setAuthorizationStatus:forBundleIdentifier: which is exclusively YES/NO.
 */
- (CAMReturnVoid *)setAuthorizationStatusByType:(NSNumber*)type forBundleIdentifier:(NSString *)bundleID;

/*!
 @method        setAuthorizationStatus:forBundleIdentifier:
 @discussion    Wrapper for [CLLocationManager setAuthorizationStatusByType:forBundleIdentifier:]
                Takes a boolean value YES/NO as "authorized" (mapping YES to kCLAuthorizationStatusAuthorizedAlways and NO to kCLAuthorizationStatusDenied), and the name for the bundle e.g. "com.apple.Maps"
 */
- (CAMReturnVoid *)setAuthorizationStatus:(NSNumber*)authorized forBundleIdentifier:(NSString *)bundleID;

/*!
 @method        setAuthorizationStatus: 
 @discussion    This is default case
                Internally calls [self setAuthorizationStatusByType:forBundleIdentifier:] (mapping YES to kCLAuthorizationStatusAuthorizedAlways and NO to kCLAuthorizationStatusDenied)
                Use the effective bundle.
 */
- (CAMReturnVoid *)setAuthorizationStatus:(NSNumber*)authorized;

/*!
 @method        setAuthorizationStatusByType:
 @discussion    Internally calls [self setAuthorizationStatusByType:forBundle:]
                Use the effective bundle.
 */
- (CAMReturnVoid *)setAuthorizationStatusByType:(NSNumber*)type;

/*!
 @method        setEffectiveBundleWithIdentifier:
 @discussion    All CLLocationManager will be init with the effective bundle
 */
- (CAMReturnBool *)setEffectiveBundleWithIdentifier:(NSString *)bundleID;

/*!
 @method        resetEffectiveBundle
 @discussion    Will reset the effective bundle to whatever CAMDCorelocation class belongs to
                aka. [NSBundle bundleForClass:NSClassFromString(@"CAMDCoreLocation")]
 */
- (CAMReturnVoid *)resetEffectiveBundle;


#pragma mark -
#pragma mark CL Beacon
/*!
 @method        createBeaconRegion:
 @abstract      Wrapper for CLLocationManager.startRangingBeaconsInRegion:.
 @discussion    Takes a NSDictionary at input, looks for following keys.
                "proximityUUID" : NSString.
                "identifier"    : NSString.
                "major"         : NSNumber - will be casted to 16 bit short int.
                "minor"         : NSNumber - will be casted to 16 bit short int.
                Any key thats not list above will not be be processed. If the object type for a key does not match the list above, the behavior is undefined.
                A CLBeaconRegion object will be created with the given dictionary, and CLLocationManager.startRangingBeaconsInRegion: will process that CLBeaconRegion object.
 @return        A token string to the CLBeaconRegion created from the input dictionary.
 */
- (CAMReturnString *)createBeaconRegion:(NSDictionary*)beaconRegionDict ;

/*!
 @method        setActiveBeaconRegion:
 @abstract      Set active beaconRegion, all beacon relating calls will use the active beaconRegion.
 @arguement     A token to the beaconRegion to be set active 
 */
- (CAMReturnVoid *)setActiveBeaconRegion:(NSString *)tokenToBeaconRegion ;

/*!
 @method        deleteBeaconRegion:
 @abstract      Delete a beaconRegion using the token. If active is deleted, active will be set to nil
 @arguement     A token to the beaconRegion to be delete
 */
- (CAMReturnVoid *)deleteBeaconRegion:(NSString *)tokenToBeaconRegion ;

/*!
 @method        createBeaconDelegate:
 @abstract      Create CLBeaconDelegate with default bundle
 @return        A token string to the CLBeaconDelegate created.
 */
- (CAMReturnString *)createBeaconDelegate;
/*!
 @method        createBeaconDelegateWithEffectiveBundleIdentifier:
 @abstract      Create CLBeaconDelegate with a bundle indentifier
 @return        A token string to the CLBeaconDelegate created.
 */
- (CAMReturnString *)createBeaconDelegateWithEffectiveBundleIdentifier:(NSString *)bundleID ;
/*!
 @method        setActiveBeaconDelegate:
 @abstract      Set active beaconDelegate, all beacon relating calls will use the active beaconDelegate.
 @arguement     A token to the beaconDelegate to be set active
 */
- (CAMReturnVoid *)setActiveBeaconDelegate:(NSString *)tokenToDelegate ;

/*!
 @method        deleteBeaconDelegate:
 @abstract      Delete a beaconDelegate using the token. If active is deleted, active will be set to nil
 @arguement     A token to the beaconDelegate to be delete
 */
- (CAMReturnVoid *)deleteBeaconDelegate:(NSString *)tokenToDelegate ;

/*!
 @method        startMonitoring
 @abstract      Wrapper for CLLocationManager.startMonitoringForRegion:.
 @param         regionToken A token string referring to the CLRegion.
 */
- (CAMReturnBool *)startMonitoring:(NSString *)regionToken;

/*!
 @method        stopMonitoring
 @abstract      Wrapper for CLLocationManager.stopMonitoringForRegion:.
 @param         regionToken A token string referring to the CLRegion.
 */
- (CAMReturnVoid *)stopMonitoring:(NSString *)regionToken;

/*!
 @method        startRangingBeacons
 @abstract      Wrapper for CLLocationManager.startRangingBeaconsInRegion:.
 @return        A token string to the CLBeaconRegion created from the input dictionary.
 */
- (CAMReturnVoid *)startRangingBeacons ;

/*!
 @method        stopRangingBeacons
 @abstract      Wrapper for CLLocationManager.stopRangingBeaconsInRegion:.
 @return        A bool indicating whether the function call success.
 */
- (CAMReturnVoid *) stopRangingBeacons ;

/*!
 @method        rangingBeaconsInRegion
 @discussion    Get information from corelocation's "callback" that provides infomation didRangeBeacons:inRegion:
                It only works after startRangingBeacons is called and before stopRangingBeacons is called.
                Each call to this function will clean the internal cache. The caller is responsible to keep infomation.
 @return        A NSArray of NSDictionary.
                Each dictionary item contents following structure 
                @"beacons" : NSArray of NSDictionary
                             Each dictionary item contents following structure 
                             @"UUID"    : NSString
                             @"major"   : NSNumber
                             @"minor"   : NSNumber
                             @"range"   : NSNumber
                @"region"  : NSDictonry
                             @"proximityUUID : NSString
                             @"major"        : NSNumber
                             @"minor"        : NSNumber
                             note: there are some legacy key from CLRegion that does not matter for this function.
 */
- (CAMReturnArray *)rangingBeaconsInRegion ;

/*!
 @method        rangingBeaconsFailedInRegionWithErrors
 @discussion    Get information from corelocation's "callback" that provides infomation rangingBeaconsDidFailForRegion:withError:
                It only works after startRangingBeacons is called and before stopRangingBeacons is called.
                Each call to this function will clean the internal cache. The caller is responsible to keep infomation.
 @return        A NSArray of NSDictionary.
                Each dictionary item contents following structure 
                @"region"  : NSDictonary
                             @"proximityUUID : NSString
                             @"major"        : NSNumber
                             @"minor"        : NSNumber
                             note: there are some legacy key from CLRegion that does not matter for this function.
                @"error"   : NSDictionary (Content infomation from NSError) 
 */
- (CAMReturnArray *)rangingBeaconsFailedInRegionWithErrors ;

/*!
 @method        generateAdvertisementDataForBeaconRegion:
 @abstract      Wrapper for CLBeaconRegion.peripheralDataWithMeasuredPower:.
 @discussion    Takes a NSDictionary at input, looks for following keys.
 "proximityUUID" : NSString.
 "identifier"    : NSString.
 "power"         : NSNumber - will be casted to 16 bit short int.
 "major"         : NSNumber - will be casted to 16 bit short int.
 "minor"         : NSNumber - will be casted to 16 bit short int.
 Any key thats not list above will not be be processed. If the object type for a key does not match the list above, the behavior is undefined.
 A dictionary of data will be genearted, this data can be used by CoreBluetooth.startAdvertising to broadcast.
 @return        A dictionary created fro CoreBluetooth.startAdvertising.
 */
- (CAMReturnDictionary *)generateAdvertisementDataForBeaconRegion:(NSString *)beaconRegionToken;

@end








