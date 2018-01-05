//
//  CAMLocknetConnection_Private.h
//  CoreAutomation
//
//  Created by Matt Massicotte on 11/15/10.
//  Copyright 2010 Apple, Inc. All rights reserved.
//

/*! 
 @enum TelnetCommands
 @discussion iOS telnet command results.
 */
typedef enum _TelnetCommands
{
    TelnetCommandNone                = 0,   // I made this up as a placeholder
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
 @discussion iOS telnet options.
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
