//
//  SAMCoding.h
//  CoreAutomationDevice
//
//  Created by Yuk Lai Suen on 2/22/13.
//
//

#import <Foundation/Foundation.h>
#import "CAMSimpleAutomationProtocol.h"

#define SAMSystemUUID @"bb4e3b60-70c9-11e2-bcfd-0800200c9a66" // unique ID key for system UUID.
#define SAMClassName @"5a9c7460-c7ee-41e0-a39f-a89f74110d42" // unique ID key for class name.
#define SAMInstanceId @"8e720354-57a4-46ab-83e8-2aba100ef84d" // unique ID for instanceId.
#define SAMProtocolName @"1"
#define SAMMethods @"2"
#define SAMClassMethods @"3"
#define SAMPointerToObject @"687FD801-06EC-41F0-A0EE-C33874E02CA3" // unique ID to indicate a pointer to an object
#define SAMNullPointer @"87134474-5734-4253-8625-0420F183EAA7" // unique ID to indicate a NULL pointer
#define SAMNil @"d4161201-daf5-4bbd-ae4f-9bf319fabbe0" // unique ID to indicate a nil object
#define SAMNSNull @"e62c6522-4eda-453e-ade8-7b86433b7634" // unique ID to indicate a NSNull object
#define SAMNSUUID @"56916047-6e48-4a62-ac43-7b8cc5d235b8" // unique ID to indicate a NSUUID object
#define SAMNSKeyedArchivedObjectData @"adfd9487-f26c-4b4c-8bd3-1f66642f4eb1" // unique ID to indicate a NSSecureCoding object
#define SAMNonPlistDictionaryObjectData @"2a841eaa-818d-11e6-b294-9762864cb5a7" // unique ID to indicate a Dictionary object (non plist dictionary)
#define SAMReturnValueKey @"return"

@interface SAMCoding : NSObject
{
@private
    NSUUID *systemUUID;
    NSNumber *instanceId;
    NSDictionary *methods;
	NSString *protocolName;
	NSDictionary *protocolRequiredMethods;
	NSDictionary *protocolOptionalMethods;
	NSString *className;
	id<CAMSimpleAutomationProtocol> simple;
	id object;
}

@property (nonatomic, strong, readonly) NSUUID *systemUUID;
@property (atomic, strong, readonly) id<CAMSimpleAutomationProtocol> simple;
@property (nonatomic, strong, readonly) NSNumber *instanceId;
@property (nonatomic, strong, readonly) NSString *protocolName;
@property (nonatomic, strong, readonly) NSDictionary *protocolRequiredMethods;
@property (nonatomic, strong, readonly) NSDictionary *protocolOptionalMethods;
@property (nonatomic, strong, readonly) NSString *className;
@property (nonatomic, strong, readonly) NSDictionary *methods;
@property (nonatomic, strong, readonly) id object;
+ (NSDictionary*) getMethodDictionaryFromClass:(Class)klass;
+ (NSDictionary*) getMethodDictionaryFromProtocolName:(NSString*)protocolName required:(BOOL)required;
+ (NSNumber*) instanceIdForObject:(id)object;
+ (id) encodeObject:(id)object simple:(id<CAMSimpleAutomationProtocol>)simple;
+ (id) decodeObject:(id)object simple:(id<CAMSimpleAutomationProtocol>)simple;
+ (id) nilObject;
+ (id) pointerToObject;
+ (id) nullPointer;
- (id) initWithObject:(id)object simple:(id<CAMSimpleAutomationProtocol>)simple;
- (id) initWithDictionary:(NSDictionary*)dictionary simple:(id<CAMSimpleAutomationProtocol>)aSimple;
- (id) initWithProtocolName:(NSString*)protocolName;
- (id) initWithClassName:(NSString*)className simple:(id<CAMSimpleAutomationProtocol>)aSimple;
- (NSDictionary*) encodeToDictionary;
@end
