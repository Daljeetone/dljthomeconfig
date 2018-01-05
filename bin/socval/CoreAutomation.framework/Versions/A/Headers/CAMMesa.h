//
//  CAMMesa.h
//  coreautomationd
//
//  Created by Anirban Maiti on 4/4/14.
//
//

#import <Availability.h> // So we get TARGET_OS_IPHONE
#import <Foundation/Foundation.h>
#import "CAMReturnValues.h"

#define kCAMMesaShortName mesa

typedef NS_ENUM(NSInteger, CAMDLocalAuthState) {
	CAMDLocalAuthWaiting = 1,
	CAMDLocalAuthFingerOn,
	CAMDLocalAuthFingerOff,
	CAMDLocalAuthMatch,
	CAMDLocalAuthMatchMiss,
	CAMDLocalAuthError,
	CAMDLocalAuthNone
};


typedef NS_ENUM(NSInteger, kCAMAuthenticatorPolicy) {
    kCAMAuthenticatorPolicyContactless = 1,
    kCAMAuthenticatorPolicyEcommerce = 2,
};

@protocol CAMMesa <NSObject>
@optional
#pragma mark -
#pragma mark Mesa Driver.
- (CAMReturnVoid *)openDriver;
- (CAMReturnVoid *)closeDriver;

#pragma mark -
#pragma mark Mesa Recording.
- (CAMReturnBool *)startRecording;
- (CAMReturnData *)stopRecording;
- (CAMReturnArray *)processRecordedDataForEmulation:(NSData *)recordedData;

- (CAMReturnBool *)stopAndSaveRecording;
- (CAMReturnData *)getRecordedData;
- (CAMReturnInteger *)processAndGetCountOfCurrentRecordedData;
- (CAMReturnData *)getProcessedRecordedDataAt: (NSNumber *)index;

#pragma mark -
#pragma mark Mesa Emulation.
- (CAMReturnBool *) isReplaying;
- (CAMReturnBool *) startReplaying;
- (CAMReturnBool *) stopReplaying;
- (CAMReturnVoid *) putFingerprintImage:(NSData *)image;

#pragma mark -
#pragma mark Core Authenticator
- (CAMReturnVoid *)evaluatePolicy:(NSNumber *)policy timeout:(NSNumber *)timeout;
- (CAMReturnVoid *)cancelEvaluation;
- (CAMReturnVoid *)recreateContext;

- (CAMReturnInteger *)authenticationState;
- (CAMReturnVoid *)authenticationError;
- (CAMReturnData *)credentialHandle;
- (CAMReturnInteger *)activeState;

- (CAMReturnVoid *)enterPasscode:(NSString *)passcode;
// Options is dictionary of {"instructions":NSData,"signature":NSData}
- (CAMReturnVoid *)setOptionsForPayment:(NSDictionary *)options;
// Options is @0 to clear the scene or @1 to set the scene to "Done."
- (CAMReturnVoid *)setPostPaymentScene:(NSNumber *)options;

@end
