//
//  CAMReturnValues.h
//  CoreAutomation
//
//  Created by Chris Whitney on 10/25/11.
//  Copyright 2011 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#if TARGET_OS_IPHONE
#import <CoreGraphics/CoreGraphics.h>
#else
#import <ApplicationServices/ApplicationServices.h>
#endif

extern NSString *CAMRETURN_OBJECT_KEY;
extern NSString *CAMRETURN_ERROR_KEY;

@interface CAMReturn : NSObject <NSSecureCoding>

@property(nonatomic, readonly) id value;
@property(nonatomic, readonly) NSError *error;

+ (instancetype)returnWithObject:(id)obj error:(NSError *)error;
- (instancetype)initWithObject:(id)obj error:(NSError *)error;

+ (BOOL)supportsSecureCoding;
- (instancetype)initWithCoder:(NSCoder *)decoder;
- (void)encodeWithCoder:(NSCoder *)encoder;
@end
#define RETURN_OBJECT(obj, err) return [CAMReturn returnWithObject:obj error:err]

// CAMReturnVoid is simply a different name for CAMReturn in order to document the return value intent.
@interface CAMReturnVoid : CAMReturn
+ (instancetype)returnWithError:(NSError *)error;
- (instancetype)initWithError:(NSError *)error;
@end
#define RETURN_VOID(err) return [CAMReturnVoid returnWithError:err]

@interface CAMReturnString : CAMReturn
@property(weak, nonatomic, readonly) NSString *stringValue;
+ (instancetype)returnWithString:(NSString *)str error:(NSError *)error;
- (instancetype)initWithString:(NSString *)obj error:(NSError *)error;
@end
#define RETURN_STRING(str, err) return [CAMReturnString returnWithString:str error:err]

@interface CAMReturnArray : CAMReturn
@property(nonatomic, readonly) NSArray *arrayValue; // TODO: removed weak from this. is that okay?
+ (instancetype)returnWithArray:(NSArray *)arr error:(NSError *)error;
- (instancetype)initWithArray:(NSArray *)arr error:(NSError *)error;
@end
#define RETURN_ARRAY(arr, err) return [CAMReturnArray returnWithArray:arr error:err]

@interface CAMReturnDictionary : CAMReturn
@property(nonatomic, readonly) NSDictionary *dictionaryValue; // TODO: removed weak from this. is that okay?
+ (instancetype)returnWithDictionary:(NSDictionary *)dict error:(NSError *)error;
- (instancetype)initWithDictionary:(NSDictionary *)dict error:(NSError *)error;
@end
#define RETURN_DICTIONARY(dict, err) return [CAMReturnDictionary returnWithDictionary:dict error:err]

@interface CAMReturnBool : CAMReturn
@property(nonatomic, readonly) BOOL boolValue;
+ (instancetype)returnWithBool:(BOOL)flag error:(NSError *)error;
- (instancetype)initWithBool:(BOOL)flag error:(NSError *)error;
@end
#define RETURN_BOOL(b, err) return [CAMReturnBool returnWithBool:b error:err]

@interface CAMReturnInteger : CAMReturn
@property(nonatomic, readonly) NSInteger integerValue;
+ (id)returnWithInteger:(NSInteger)num error:(NSError *)error;
- (instancetype)initWithInteger:(NSInteger)num error:(NSError *)error;
@end
#define RETURN_INTEGER(i, err) return [CAMReturnInteger returnWithInteger:i error:err]

@interface CAMReturnDouble : CAMReturn
@property(nonatomic, readonly) double doubleValue;
+ (id)returnWithDouble:(double)num error:(NSError *)error;
- (instancetype)initWithDouble:(double)num error:(NSError *)error;
@end
#define RETURN_DOUBLE(d, err) return [CAMReturnDouble returnWithDouble:d error:err]

@interface CAMReturnData : CAMReturn
@property(weak, nonatomic, readonly) NSData *dataValue;
+ (id)returnWithData:(NSData *)data error:(NSError *)error;
- (instancetype)initWithData:(NSData *)data error:(NSError *)error;
@end
#define RETURN_DATA(d, err) return [CAMReturnData returnWithData:d error:err]

@interface CAMReturnCGPoint : CAMReturn
@property(nonatomic, readonly) CGPoint pointValue;
+ (id)returnWithPoint:(CGPoint)point error:(NSError *)error;
- (instancetype)initWithPoint:(CGPoint)point error:(NSError *)error;
@end
#define RETURN_CGPOINT(p, err) return [CAMReturnCGPoint returnWithPoint:p error:err]

@interface CAMReturnCGRect : CAMReturn
@property(nonatomic, readonly) CGRect rectValue;
+ (id)returnWithRect:(CGRect)rect error:(NSError *)error;
- (instancetype)initWithRect:(CGRect)rect error:(NSError *)error;
@end
#define RETURN_CGRECT(r, err) return [CAMReturnCGRect returnWithRect:r error:err]

@interface CAMReturnShellTask : CAMReturnDictionary
@property(weak, nonatomic, readonly) NSString *standardOutput;
@property(weak, nonatomic, readonly) NSString *standardError;
@property(nonatomic, readonly) int returnCode;
+ (NSString *)stringAttemptFromData:(NSData *)data;
@end
#define kCAMReturnShellTaskStandardOutputKey @"standardOutput"
#define kCAMReturnShellTaskStandardErrorKey @"standardError"
#define kCAMReturnShellTaskReturnCodeKey @"returnCode"
#define RETURN_TASK_DICTIONARY(dict, err) return [CAMReturnShellTask returnWithDictionary:dict error:err]

@interface CAMReturnAsynchronousShellTask : CAMReturnShellTask
@property(weak, nonatomic, readonly) NSString *UUID;
@property(nonatomic, readonly) BOOL isRunning;
@property(nonatomic, readonly) int processIdentifier;
@end
#define kCAMReturnAsynchronousShellTaskUUIDKey @"UUID"
#define kCAMReturnAsynchronousShellTaskIsRunningKey @"isRunning"
#define kCAMReturnAsynchronousShellTaskIsNoHupKey @"isNoHup"
#define kCAMReturnAsynchronousShellTaskProcessIdentifierKey @"processIdentifier"
#define RETURN_ASYNC_TASK_DICTIONARY(dict, err) return [CAMReturnAsynchronousShellTask returnWithDictionary:dict error:err]
