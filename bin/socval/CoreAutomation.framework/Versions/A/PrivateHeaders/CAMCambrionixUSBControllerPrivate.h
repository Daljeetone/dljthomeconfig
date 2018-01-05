
//
//  CAMCambrionixUSBControllerPrivate.h
//  CoreAutomation
//
//  Created by Tarek Khouzam on 2/14/12.
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

// TODO: Look into using extern for these constants and initialize from a plist

#ifndef CoreAutomation_CAMCambrionixUSBControllerPrivate_h
#define CoreAutomation_CAMCambrionixUSBControllerPrivate_h

// Firmware Information //
#define BUSMANSUPPORTEDFIRMWARE [NSArray arrayWithObjects:@"CBRX1040V7", @"CBRX1040V8", nil]
#define BUSMANXLSUPPORTEDFIRMWARE [NSArray arrayWithObjects:@"1056V1", nil]
#define CAMBRIONIXSUPPORTEDFIRMWARE [[NSArray arrayWithArray:BUSMANSUPPORTEDFIRMWARE] arrayByAddingObjectsFromArray:BUSMANXLSUPPORTEDFIRMWARE]

// VendorID/ProductID Information //
#define SUPPORTEDHUBINFO [NSArray arrayWithObjects:@"1452", @"5641", @"1060", @"9479", nil]

// Prompt Information //
#define CAMBRIONIXPROMPTS [NSArray arrayWithObjects:@"[DONE]", @"[ERR]", @"[OK]", @">", nil] // Can't have '/r' breaks firmwareVersion. Add it when needed

// Commands that don't return a response //
#define CAMBRIONIXNONRESPONSIVEOUTPUT [NSDictionary dictionaryWithObjectsAndKeys:@"[OK]", @"hr", nil]
#define CAMBRIONIXNONRESPONSIVECLOSE [NSArray arrayWithObjects:@"hr", nil]

// Port States //
#define BUSMANSTATE_HOST 1
#define BUSMANSTATE_CHARGER 2
#define BUSMANSTATE_DISCONNECTED 3

// Device IDs //

/*
 M68    0x1290  iPhone 1,1
 N82    0x1292  iPhone 1,2
 N88    0x1294  iPhone 2,1
 N90    0x1297  iPhone 3,1
 N89    0x129B  iPhone 3,2
 N92    0x129C  iPhone 3,3
 N94    0x12A0  iPhone4,1
 N4x    0x12A8  iPhone5,x
 
 N45    0x1291  iPod 1,1
 N72    0x1293  iPod 2,1
 N72B   0x1296  iPod 2,2
 N18    0x1299  iPod 3,1
 N81    0x129E  iPod4,1
 N78    0x12AA  iPod5,1
 
 K48    0x129A  iPad 1,1
 K93    0x129F  iPad2,1
 K94    0x12A2  iPad2,2
 K95    0x12A3  iPad2,3
 J1     0x12A4  iPad3,1
 J2     0x12A5  iPad3,2
 J2A    0x12A6  iPad3,3
 P10x   0x12AB  iPad4,x
 
 K66    0x129D  AppleTV 2,1
 */

#define HIGHPOWER_1A [NSDictionary dictionaryWithObjectsAndKeys:                         \
                                       [NSNumber numberWithUnsignedInt:0x1290], @"M68",  \
                                       [NSNumber numberWithUnsignedInt:0x1291], @"N45",  \
                                       [NSNumber numberWithUnsignedInt:0x1292], @"N82",  \
                                       [NSNumber numberWithUnsignedInt:0x1293], @"N72",  \
                                       [NSNumber numberWithUnsignedInt:0x1294], @"N88",  \
                                       [NSNumber numberWithUnsignedInt:0x1296], @"N72B", \
                                       [NSNumber numberWithUnsignedInt:0x1297], @"N90",  \
                                       [NSNumber numberWithUnsignedInt:0x1299], @"N18",  \
                                       [NSNumber numberWithUnsignedInt:0x129B], @"N89",  \
                                       [NSNumber numberWithUnsignedInt:0x129C], @"N92",  \
                                       [NSNumber numberWithUnsignedInt:0x129E], @"N81",  \
                                       [NSNumber numberWithUnsignedInt:0x12A0], @"N94",  \
                                       [NSNumber numberWithUnsignedInt:0x12A8], @"N4x",  \
                                       [NSNumber numberWithUnsignedInt:0x12AA], @"N78",  \
                                       nil]

#define HIGHPOWER_2_1A [NSDictionary dictionaryWithObjectsAndKeys:                         \
                                         [NSNumber numberWithUnsignedInt:0x129A], @"K48",  \
                                         [NSNumber numberWithUnsignedInt:0x129F], @"K93",  \
                                         [NSNumber numberWithUnsignedInt:0x12A2], @"K94",  \
                                         [NSNumber numberWithUnsignedInt:0x12A3], @"K95",  \
                                         [NSNumber numberWithUnsignedInt:0x12A4], @"J1",   \
                                         [NSNumber numberWithUnsignedInt:0x12A5], @"J2",   \
                                         [NSNumber numberWithUnsignedInt:0x12A6], @"J2A",  \
                                         [NSNumber numberWithUnsignedInt:0x12AB], @"P10x", \
                                         nil]

#define BUSMANDEBUG NO
#define BM_HIGHPOWER NO

//USB info for controlling high power charge
#define BUSMAN_HIGHPOWER_APPLEVENDORID 1452
#define BUSMAN_HIGHPOWER_2100mA 1600
#define BUSMAN_HIGHPOWER_1000mA 500
#define BUSMAN_HIGHPOWER_500mA 0

#define NSLog(FORMAT, ...) printf("%s\n", [[NSString stringWithFormat:FORMAT, ##__VA_ARGS__] UTF8String]);
#define NSLog2(FORMAT, ...) printf("\t%s\n", [[NSString stringWithFormat:FORMAT, ##__VA_ARGS__] UTF8String]);

@interface CAMCambrionixUSBController (Private)

- (id)initWithAddress:(NSString *)address numberOfPorts:(NSInteger)num error:(NSError **)error;
- (NSString *)command:(NSString *)command flush:(BOOL)flush prompts:(NSArray *)prompts;
+ (IOReturn)highPowerChargeForProduct:(UInt32)usbProduct atPower:(unsigned short)power;
- (NSArray *)checkPorts:(NSArray *)ports;
- (NSString *)findFirmwareVersion:(NSString *)firmwareInfo pattern:(NSString *)frmPattern;
- (void)open;
- (void)close;

@end

#endif