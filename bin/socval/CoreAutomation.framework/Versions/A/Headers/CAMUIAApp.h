//
//  CAMUIAApp.h
//  CoreAutomation
//
//  Created by Matt Massicotte on 6/5/10.
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class CAMEmbeddedDevice;

@interface CAMUIAApp : NSObject
{
    NSString*          name;
    NSArray*           libraryPaths;
    CAMEmbeddedDevice* device;
}

- (instancetype)initWithAppName:(NSString*)appName forDevice:(CAMEmbeddedDevice*)theDevice;

@property (copy,readonly) NSString *name;
@property (strong)        NSArray  *libraryPaths;

- (NSString*)runScripter:(NSString*)javaScriptText;
- (NSString*)function:(NSString*)functionName arguments:(NSArray*)args;
- (NSString*)function:(NSString*)functionName argument:(id)arg;
- (NSString*)function:(NSString*)functionName;

+ (NSDictionary*)appLibrariesForDevice:(CAMEmbeddedDevice*)theDevice;

+ (NSString*)javascriptFragmentForObject:(id)object;

@end
