//
//  CAMTelnetConnection.h
//  CoreAutomation
//
//  Created by Matt Massicotte on 3/3/10.
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "CAMTerminalConnection.h"

/*! 
 @enum TelnetCommands
 @discussion These are the enums that represent telnet interaction.
 */
typedef enum _TelnetCommands
{
    TelnetCommandEndOfSubnegotiation = 240,
    TelnetCommandNOP                 = 241,
    TelnetCommandDataMark            = 242,
    TelnetCommandBreak               = 243,
    TelnetCommandSuspend             = 244,
    TelnetCommandAbortOutput         = 245,
    TelnetCommandAreYouThere         = 246,
    TelnetCommandEraseCharacter      = 247,
    TelnetCommandEraseLine           = 248,
    TelnetCommandGoAhead             = 249,
    TelnetCommandSubnegotiation      = 250,
    TelnetCommandWill                = 251,
    TelnetCommandWont                = 252,
    TelnetCommandDo                  = 253,
    TelnetCommandDont                = 254,
    TelnetCommandStart               = 255
} TelnetCommands;

/*! 
 @enum TelnetOptions
 @discussion These are the enums that represent telnet options.
 */
typedef enum _TelnetOptions
{
    TelnetOptionEcho              = 1,
    TelnetOptionSuppressGoAhead   = 3,
    TelnetOptionStatus            = 5,
    TelnetOptionTimingMark        = 6,
    TelnetOptionTerminalType      = 24,
    TelnetOptionWindowSize        = 31,
    TelnetOptionTerminalSpeed     = 32,
    TelnetOptionRemoteFlowControl = 33,
    TelnetOptionLinemode          = 34,
    TelnetOptionXDisplayLocation  = 35,
    TelnetOptionEnvironment       = 36,
    TelnetOptionNewEnvironment    = 39
} TelnetOptions;

/*! 
 @interface CAMTelnetConnection
 @discussion This interface is used to create a telnet connection to a device/machine.
 */
@interface CAMTelnetConnection : CAMTerminalConnection
{
    @private
    NSInputStream*  inStream;
    NSOutputStream* outStream;
    
    BOOL            connected;
}

/*! 
 @method initWithInputStream
 @discussion This is the designated initializer.
 @param inputStream
	Specifies the input stream.
 @param outputStream
	Specifies the output stream.
 */
- (instancetype)initWithInputStream:(NSInputStream *)inputStream andOutputStream:(NSOutputStream *)outputStream;

/*! 
 @method initWithURL
 @discussion This initializer can be used to initialize with a URL.
 @param url
	The url of the remote device.
 */
- (instancetype)initWithURL:(NSURL *)url;

@end
