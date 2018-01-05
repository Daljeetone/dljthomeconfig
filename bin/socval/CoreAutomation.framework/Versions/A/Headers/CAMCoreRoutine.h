//
//  CAMCoreRoutine.h
//  coreautomationd
//
//  Created by Aleksey Korenkov on 1/27/16.
//
//
#import <TargetConditionals.h>

#import <Foundation/Foundation.h>
#import "CAMReturnValues.h"

#define kCAMCoreRoutineShortName coreRoutine

@protocol CAMCoreRoutine
@optional

/*!
 *  @method        portraitAddEntityWithName:category:date:sourceBundleID:
 *  @discussion    add entity with name and category to source with bundleID at date
 *
 *  @param         name           NSString source bundle identifier
 *  @param         category       NSString category, must be on of the following otherwise Unkown
 *                                  Person, Organization, Location, Restaurant, ActivityLocation,
 *                                  Media, Artist, StreetAddress, City, State, Country
 *  @param         date           NSDate date
 *  @param         bundleID       NSString source bundle identifier
 *
 *  @return        a bool represent the success
 */
- (CAMReturnBool *)portraitAddEntityWithName:(NSString *)name category:(NSString *)category date:(NSDate *)date sourceBundleID:(NSString *)bundleID;

/*!
 *  @method        portraitFetchEntitiesForCategory:
 *  @discussion    fetch all entities for given category
 *
 *  @param         category       NSString category, must be on of the following otherwise Unkown
 *                                  Person, Organization, Location, Restaurant, ActivityLocation,
 *                                  Media, Artist, StreetAddress, City, State, Country
 *
 *  @return        a bool represent the success
 */
- (CAMReturnArray *)portraitFetchEntitiesForCategory:(NSString *)category;

/*!
 *  @method        portraitDeleteAllEntitiesFromSourcesWithBundleId:
 *  @discussion    delete all entities from all spotlight sources with given bundle identifier
 *
 *  @param         bundleID       NSString bundle identifier
 *
 *  @return        a bool represent the success
 */
- (CAMReturnBool *)portraitDeleteAllEntitiesFromSourcesWithBundleID:(NSString *)bundleID;

/*!
 *  @method        proactiveExpertsDonateLocation:bundleID:startDate:endDate:
 *  @discussion    add an entry into duet apps location database for bundle
 *
 *  @param         metaData       NSDictionary meta data for the event, dictionary of the keys
 *                                locationName - string
 *                                subThoroughfare - string
 *                                thoroughfare - string
 *                                fullyFormattedAddress - string
 *                                postalCode - string
 *                                city - string
 *                                stateOrProvince - string
 *                                country - string
 *                                latitude - string
 *                                longitude - string
 *                                phoneNumbers - list of the strings
 *                                URL = string
 *                                displayName = string
 *
 *  @param         bundleID       NSString bundle identifier
 *  @param         startDate      NSDate event start date
 *  @param         endDate        NSDate event end date
 *
 *  @return        a bool represent the success
 */
- (CAMReturnBool *)proactiveExpertsDonateLocation:(NSDictionary *)metaData
                                         bundleID:(NSString *)bundleID
                                        startDate:(NSDate *)startDate
                                          endDate:(NSDate *)endDate;

/*!
 *  @method        proactiveExpertsCleanupDonatedLocationsForBundleID:
 *  @discussion    remove all enties from duet apps location database for bundle
 *
 *  @param         bundleID       NSString bundle identifier
 *
 *  @return        a bool represent the success
 */
- (CAMReturnBool *)proactiveExpertsCleanupDonatedLocationsForBundleID:(NSString *)bundleID;

/*!
 *  @method        mapsClearAllFavorites
 *  @discussion    remove all enties form maps favorites storage
 */
- (CAMReturnVoid *)mapsClearAllFavorites;

/*!
 *  @method        mapsClearAllHistoryEntries
 *  @discussion    remove all enties form maps history storage
 */
- (CAMReturnVoid *)mapsClearAllHistoryEntries;

/*!
 *  @method        mapsAddFavoriteWithTitle:city:latitude:longitude:
 *  @discussion    add maps favority with Title, City, Latitude and Longitude
 *
 *  @param         title       NSString title for favority
 *  @param         city        NSString city for favority
 *  @param         latitude    NSNumber latitude for placemark
 *  @param         longitude   NSNumber longitude for placemark
 */
- (CAMReturnVoid *)mapsAddFavoriteWithTitle:(NSString *)title
                                       city:(NSString *)city
                                   latitude:(NSNumber *)latitude
                                  longitude:(NSNumber *)longitude;

/*!
 *  @method        mapsRemoveFavoriteWithTitle:
 *  @discussion    remove maps favority for given Title
 *
 *  @param         title       NSString title for favority
 */
- (CAMReturnVoid *)mapsRemoveFavoriteWithTitle:(NSString *)title;

/*!
 *  @method        mapsAddHistoryPlaceDisplayForCity:latitude:longitude:
 *  @discussion    add maps history event for City, Latitude and Longitude
 *
 *  @param         city        NSString city for history event
 *  @param         latitude    NSNumber latitude for placemark
 *  @param         longitude   NSNumber longitude for placemark
 *  @param         usageDate   NSDate usage timestamp
 */
- (CAMReturnVoid *)mapsAddHistoryPlaceDisplayForCity:(NSString *)city
                                            latitude:(NSNumber *)latitude
                                           longitude:(NSNumber *)longitude
                                           usageDate:(NSDate *)usageDate;

/*!
 *  @method        mapsAddHistoryRouteFromCity:fromLatitude:fromLongitude:toCity:toLatitude:toLongitude:usageDate
 *  @discussion    add maps history route from point to point
 *
 *  @param         fromCity        NSString city for start point (use "Current Location" for
                                            start point being current location)
 *  @param         fromLatitude    NSNumber from latitude for placemark
 *  @param         fromLongitude   NSNumber from longitude for placemark
 *  @param         toCity          NSString city to end point
 *  @param         toLatitude      NSNumber to latitude for placemark
 *  @param         toLongitude     NSNumber to longitude for placemark
 *  @param         usageDate       NSDate usage timestamp
 */
- (CAMReturnVoid *)mapsAddHistoryRouteFromCity:(NSString *)fromCity
                                  fromLatitude:(NSNumber *)fromLatitude
                                 fromLongitude:(NSNumber *)fromLongitude
                                        toCity:(NSString *)toCity
                                    toLatitude:(NSNumber *)toLatitude
                                   toLongitude:(NSNumber *)toLongitude
                                     usageDate:(NSDate *)usageDate;

/*!
 *  @method        mapsRemoveHistoryEntry:locality:
 *  @discussion    remove maps history event (Route or PlaceDisplay)
 *
 *  @param         entry        NSString history event envry, must be "Route" or "PlaceDisplay"
 *  @param         locality     NSString city name representation for placemark (for Route case
 *                                       it must be for one of the way points)
 */
- (CAMReturnVoid *)mapsRemoveHistoryEntry:(NSString *)entry
                                 locality:(NSString *)locality;

/*!
 *  @method        fetchLOIs
 *  @discussion    fetch LOIs
 */
- (CAMReturnArray *)fetchLOIs;

/*!
 *  @method        forceSCI
 *  @discussion    Force CoreRoutine Sequential Cluster Identification (relearn)
 */
- (CAMReturnVoid *)forceSCI;

/*!
 *  @method        clearRoutineStateModel
 *  @discussion    clear CoreRoutine state model
 */
- (CAMReturnVoid *)clearRoutineStateModel;

/*!
 *  @method        forceEventModelRefresh
 *  @discussion    Force CoreRoutine event model to refresh
 */
- (CAMReturnVoid *) forceEventModelRefresh;

/*!
 *  @method        injectLocationWithLatitude:longitude:uncertainty:timestamp:
 *  @discussion    Inject location with given data
 *
 *  @param         latitude     NSNumber latitude
 *  @param         longitude    NSNumber latitude
 *  @param         uncertainty  NSNumber uncertainty
 *  @param         timestamp    NSDate timestamp
 */
- (CAMReturnVoid *)injectLocationWithLatitude:(NSNumber *)latitude
                                    longitude:(NSNumber *)longitude
                                  uncertainty:(NSNumber *)uncertainty
                                    timestamp:(NSDate *)timestamp;

/*!
 *  @method        setParkedLocationWithNotes:notes:latitude:longitude:
 *  @discussion    Set parked location for vehicle with notes, latitude and longitude
 */
- (CAMReturnVoid *) setParkedLocationWithNotes:(NSString *)notes latitude:(NSNumber *)latitude longitude:(NSNumber *)longitude;

/*!
 *  @method        fetchParkedLocations:
 *  @discussion    Fetch parked locations
 */
- (CAMReturnArray *) fetchParkedLocations;

/*!
    @method     getTitlesForLocalCalendars:

    @discussion Get list os the local calandars titles

    @return     An Array of the strings representing the local calandars title.
*/
- (CAMReturnArray *) getTitlesForLocalCalendars;

/*!
    @method     getTitleForDefaultCalendar:

    @discussion Get title for default calandar

    @return     A string for title of the default calendar.
*/
- (CAMReturnString *) getTitleForDefaultCalendar;

/*!
    @method     addLocalCalendarWithTitle:

    @discussion Create new calandar with given title

    @param      calendarTitle       NSString title for calendar.

    @return     A bool representing success.
*/
- (CAMReturnBool *) addLocalCalendarWithTitle:(NSString *)calendarTitle;

/*!
    @method     removeLocalCalendarWithTitle:

    @discussion Remove calandar with given title
                This will remove all events for given calendar

    @param      calendarTitle       NSString title for calendar

    @return     A bool representing success
*/
- (CAMReturnBool *) removeLocalCalendarWithTitle:(NSString *)calendarTitle;

/*!
    @method     isLocalCalendarWithTitleExists:

    @discussion Check if local calendar with given title exists

    @param      calendarTitle   NSString title for calendar
 
    @return     A bool representing existence
*/
- (CAMReturnBool *) isLocalCalendarWithTitleExists:(NSString *)calendarTitle;

/*!
    @method     addEventWithTitle:locationDescription:startDate:andEndDate:toCalendarWithTitle:
 
    @discussion Create new event
 
    @param      eventTitle          NSString title for event
    @param      locationDescription NSString location description
    @param      startDate           NSDate event start date
    @param      endDate             NSDate event end date
    @param      calendarTitle       NSString title for calendar
 
    @return     A bool representing success
*/
- (CAMReturnBool *) addEventWithTitle:(NSString *)eventTitle
                  locationDescription:(NSString *)locationDescription
                            startDate:(NSDate *)startDate
                           andEndDate:(NSDate *)endDate
                  toCalendarWithTitle:(NSString *)calendarTitle;

/*!
    @method     addEventWithTitle:locationDescription:latitude:andLongitude:startDate:andEndDate:toCalendarWithTitle:

    @discussion Create new event with geo location

    @param      eventTitle          NSString title for event
    @param      locationDescription NSString location description
    @param      latitude            NSNumber latitude of the location of the event
    @param      longitude           NSNumber longitude of the location of the event
    @param      startDate           NSDate event start date
    @param      endDate             NSDate event end date
    @param      calendarTitle       NSString title for calendar

    @return     A bool representing success
*/
- (CAMReturnBool *) addEventWithTitle:(NSString *)eventTitle
                  locationDescription:(NSString *)locationDescription
                             latitude:(NSNumber *)latitude
                         andLongitude:(NSNumber *)longitude
                            startDate:(NSDate *)startDate
                           andEndDate:(NSDate *)endDate
                  toCalendarWithTitle:(NSString *)calendarTitle;

/*!
    @method     addEventWithTitle:locationDescription:latitude:andLongitude:startDate:andEndDate:recurrenceFrequency:recurrenceInterval:recurrenceEndDate:toCalendarWithTitle:

    @discussion Create new event recurring event with geo location
                In case any of the recurrence params fail its validation, a regular event will be created

    @param      eventTitle          NSString title for event
    @param      locationDescription NSString location description
    @param      latitude            NSNumber latitude of the location of the event
    @param      longitude           NSNumber longitude of the location of the event
    @param      startDate           NSDate event start date
    @param      endDate             NSDate event end date
    @param      recurrenceFrequency NSString recurrence frequency of the event, can be only one of Daily, Weekly, Monthly or Yearly
    @param      recurrenceInterval  NSNumber recurrence interval os the event
    @param      recurrenceEndDate   NSDate recurrence end date
    @param      calendarTitle       NSString title for calendar
 
    @return     A bool representing success
*/
- (CAMReturnBool *) addEventWithTitle:(NSString *)eventTitle
                  locationDescription:(NSString *)locationDescription
                             latitude:(NSNumber *)latitude
                         andLongitude:(NSNumber *)longitude
                            startDate:(NSDate *)startDate
                           andEndDate:(NSDate *)endDate
                  recurrenceFrequency:(NSString *)recurrenceFrequency
                   recurrenceInterval:(NSNumber *)recurrenceInterval
                    recurrenceEndDate:(NSDate *)recurrenceEndDate
                  toCalendarWithTitle:(NSString *)calendarTitle;

/*!
    @method     removeEventsFromLocalCalendar:startDate:andEndDate:

    @discussion Remove all events from calendar for given date range
 
                For performance reasons, this method will only return events within a four year timespan.
                If the date range between the startDate and endDate is greater than four years, then it will be shortened
                to the first four years.

    @param      calendarTitle   NSString title for calendar
    @param      startDate       NSDate start date, can be as far as 4 year back
    @param      endDate         NSDate end date

    @return     A bool representing success
*/
- (CAMReturnBool *) removeEventsFromLocalCalendarWithTitle:(NSString *)calendarTitle
                                                 startDate:(NSDate *)startDate
                                                andEndDate:(NSDate *)endDate;

/*!
    @method     removeEventsFromLocalCalendar:startDate:andEndDate:

    @discussion Get array of the dictionaries of the events from calendar for given date range
                Keys title, calendarTitle, locationDescription, endDate and startDate
 
                For performance reasons, this method will only return events within a four year timespan.
                If the date range between the startDate and endDate is greater than four years, then it will be shortened
                to the first four years.

    @param      calendarTitle   NSString title for calendar
    @param      startDate       NSDate start date, can be as far as 4 year back
    @param      endDate         NSDate end date

    @return     An array of dictionaries
*/
- (CAMReturnArray *) getEventsFromLocalCalendarWithTitle:(NSString *)calendarTitle
                                               startDate:(NSDate *)startDate
                                              andEndDate:(NSDate *)endDate;

/*!
    @method     fetchPredictedLOIsAssociatedToEventWithTitle:location:calendar:

    @discussion Get array of the dictionaries of the predicted LOIs from CoreRoutine
                Keys uuid, confidence, latitude and longitude

    @param      eventTitle          NSString title of the event
    @param      locationDescription NSString location of the event (represent locationDescription of an event)
    @param      calendarTitle       NSString title for calendar, could be an empty string

    @return     An array of dictionaries
 */
- (CAMReturnArray *) fetchPredictedLOIsAssociatedToEventWithTitle:(NSString *)eventTitle
                                                         location:(NSString *)locationDescription
                                                         calendar:(NSString *)calendarTitle;
@end

