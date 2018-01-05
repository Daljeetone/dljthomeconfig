//
//  SAMObjectProxy.h
//  CoreAutomationDevice
//
//  Created by Yuk Lai Suen on 2/6/13.
//
//

#import <Foundation/Foundation.h>
#import "CAMSimpleAutomationProtocol.h"
#import "SAMCoding.h"

@interface SAMObjectProxy : NSProxy
{
	SAMCoding *simpleCoding;
	BOOL isClassObject;
}
@property (nonatomic, retain, readonly) SAMCoding *simpleCoding;
+ (id) objectProxyWithDictionary:(NSDictionary*)dictionary simple:(id<CAMSimpleAutomationProtocol>)simple;
- (id) initWithDictionary:(NSDictionary*)dictionary simple:(id<CAMSimpleAutomationProtocol>)simple;
- (id) initWithClassName:(NSString *)className simple:(id<CAMSimpleAutomationProtocol>)simple;
- (id) initWithObject:(id)object simple:(id<CAMSimpleAutomationProtocol>)simple;
@end
