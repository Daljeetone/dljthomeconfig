//
//  SAMDeferredMessage.h
//  coreautomationd
//
//  Created by Yuk Lai Suen on 2/18/13.
//
//

#import <Foundation/Foundation.h>

@interface SAMDeferredMessage : NSObject
{
@private
	NSArray *message;
	NSCondition *waitLock;
	id returnValue;
	BOOL sent;
}
@property (nonatomic, strong, readwrite) id returnValue;
@property (nonatomic, strong, readwrite) NSCondition *waitLock;
@property (nonatomic, strong, readwrite) NSArray *message;
@property (nonatomic, assign, readwrite) BOOL sent;
- (id) initWithMessage:(NSArray*)message waitLock:(NSCondition*)waitLock;
- (id) encodeDeferredMessage:(NSUUID*)uuid;
- (void) setAndNotifyReturnValue:(id) aReturnValue;
@end