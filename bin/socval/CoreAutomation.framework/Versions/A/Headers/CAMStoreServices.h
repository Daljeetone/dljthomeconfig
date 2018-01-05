//
//  CAMStoreServices.h
//  CoreAutomation
//
//  Created by Chen Huang on Mar 29, 2013.
//  Copyright (c) 2013 Apple. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CAMReturnValues.h"

#define kCAMStoreServicesShortName store

@protocol CAMStoreServices
@optional

#pragma mark - Accounts
- (CAMReturnInteger*)activeAccountID;
- (CAMReturnString*)activeAccountName;
- (CAMReturnBool*)setActiveAccountWithUniqueIdentifier:(NSString*)identifier;
- (CAMReturnBool*)signIn:(NSString*)appleID withPassword:(NSString*)password;
- (CAMReturnBool*)signOut:(NSString*)appleID;
- (CAMReturnBool*)signOutAllAccounts;
- (CAMReturnArray*)accounts;
- (CAMReturnBool*)authenticateAccount:(NSString*)appleID withPassword:(NSString*)password;
- (CAMReturnBool*)isAccountAuthenticated:(NSString*)appleID;

#pragma mark - Items
- (CAMReturnBool*)isApplicationInstalled:(NSString*)bundleID;
- (CAMReturnBool*)purchaseItemWithBundleIdentifier:(NSString*)bundleID;
- (CAMReturnBool*)lookupItemWithBundleIdentifier:(NSString*)bundleID;

#pragma mark - Downloads
- (CAMReturnBool*)waitForDownloadToComplete:(NSString*)bundleID withTimeout:(NSNumber *)seconds;
- (CAMReturnArray*)activeDownloads;
- (CAMReturnArray*)downloads;
- (CAMReturnVoid*)cancelDownload:(NSString*)bundleID;
- (CAMReturnVoid*)pauseDownload:(NSString*)bundleID;
- (CAMReturnVoid*)resumeDownload:(NSString*)bundleID;
- (CAMReturnBool*)isDownloadCancelable:(NSString*)bundleID;
- (CAMReturnInteger*)bytesDownloaded:(NSString*)bundleID;
- (CAMReturnInteger*)bytesTotal:(NSString*)bundleID;
- (CAMReturnDouble*)percentComplete:(NSString*)bundleID;

@end
