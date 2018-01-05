//
//  CAMEmbeddedDeviceRestore.h
//  CoreAutomation
//
//  Created by Matt Massicotte on 9/20/10.
//  Copyright 2010 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

extern NSString* const CAMEmbeddedDeviceRestorePiecesPathKey;

extern NSString* const CAMEmbeddedDeviceRestoreFirmwareImageKey;
extern NSString* const CAMEmbeddedDeviceRestoreBasebandUpdateKey;
extern NSString* const CAMEmbeddedDeviceRestoreAutoBootDelayKey;
extern NSString* const CAMEmbeddedDeviceRestoreKernelCacheTypeKey;
extern NSString* const CAMEmbeddedDeviceRestoreUpdate;
extern NSString* const CAMEmbeddedDeviceRestoreSigningServerHost;
extern NSString* const CAMEmbeddedDeviceRestoreSigningServerPort;
extern NSString* const CAMEmbeddedDeviceRestoreSigningServerURL;

extern NSString* const CAMEmbeddedDeviceRestoreDefaultErasePR2Path;
extern NSString* const CAMEmbeddedDeviceRestoreDefaultErasePRPath;

typedef NS_ENUM(NSInteger, CAMEmbeddedDeviceRestoreBundle) {
    CAMEmbeddedDeviceRestoreBundleCustomer,
    CAMEmbeddedDeviceRestoreBundleDeveloper,
    CAMEmbeddedDeviceRestoreBundleCarrier
} ;
