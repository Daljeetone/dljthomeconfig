//
//  CAMAstris.h
//  CoreAutomation
//
//  Created by Keith Preston on 4/30/12.
//
//

struct AXconn_s;
struct AXcsversion_s;
@class CAMEmbeddedDevice;

/*!
 @interface CAMEmbeddedDevice
 @discussion Small wrapper around the astrisctl librarlibrary
 */
@interface CAMAstris : NSObject {
    struct AXconn_s *device;
    struct AXcsversion_s *version;
    NSString *__weak _path;
    NSString *_serialNumber;
}

/*!
 @brief Path of the astris device
 */
@property(weak, readonly) NSString *path;

/*!
 @brief Serial number of the astris device
 */
@property(readonly) NSString *serialNumber;

/*!
 @brief Get all connected Astris probes
 */
+ (NSArray *)allAstrisPaths;

/*!
 @brief Get all connected astris
 */
+ (NSArray *)allAstris;

/*! 
 @brief Create an Astris Device object
 @param path this should be the Astris Path for the device - typically "type"SWD-"Serialnumber" or the ethernet address
 */
- (id)initWithPath:(NSString *)path;

/*!
 @brief Opens the connected to the probe, kicking off another other connection to the probe
 */
- (BOOL)open;

/*!
 @brief Closes the connected to the probe
 */
- (BOOL)close;

/*!
 @brief Returns whether the probe is connected
 */
- (BOOL)isConnected;

/*!
 @brief Returns whether the probe is in use
 */
- (BOOL)isInUse;

/*!
 @brief Checkout Astris probe
 */
- (BOOL)checkout;

/*!
 @brief Checkin Astris probe
 */
- (void)checkin;

/*! 
 @brief Prints out a lot of debugging info to stdout for an astris
 */
- (void)printInfo;

/*!
 @brief Gets the connected device
 */
- (CAMEmbeddedDevice *)device;

/*!
 @brief Resets a device through the jtag, only works on Dev Fused units
 */
- (void)reset;

/*!
 @brief Detects whether a connected device is Panicked
 */
- (BOOL)isPanic;

/*!
 @brief Returns the panic string if the device is panicked
 */
- (NSString *)getPanicString;

/*! 
 @brief Change any of the relays of the Astris  See astris Ctrl.
 @param relay Name of Relay
 @param value Value of Relay to set to
 */
- (void)setRelay:(NSString *)relay withValue:(int)value;

/*! 
 @brief Get value of the relays of the Astris  See astris Ctrl.
 @param relay Name of Relay
 */
- (int)getRelay:(NSString *)relay;

/*! 
 @brief Disconnects a device on usb and power */
- (void)disconnect;

/*! 
 @brief Reconnects a device on usb and power
 */
- (void)reconnect;

/*!
 @brief Get all astris environment variables
 @return    Returns a dictionary of key-value pairs.
 */
- (NSDictionary *)allEnvironmentVariables;

/*!
 @brief Gets the specified environment variable
 @param variable    The environment variable name
 @return    Returns variable value or nil if variable does not exist
 */
- (NSString *)getEnvironmentVariable:(NSString *)variable;

/*!
 @brief Sets an environment variable
 @param variable    The environment variable name
 @param value   Variable to set
 @discussion    Passing a value of nil will delete the environment variable.
 */
- (void)setEnvironmentVariable:(NSString *)variable value:(NSString *)value;

@end
