//
//  CAMAssistant.h
//  coreautomationd
//
//  Created by Chen Huang on 6/17/13.
//
//

#import <Foundation/Foundation.h>

#import "CAMReturnValues.h"

#define kCAMAssistantServicesShortName assistant

@protocol CAMAssistantServices <NSObject>
@optional

- (CAMReturnArray *)startRequestWithText:(NSString *)text withTimeout:(NSNumber *)timeout;
- (CAMReturnBool *)isSiriEnabled;
- (CAMReturnBool*)disableSiri;
- (CAMReturnBool*)enableSiri;
@end
