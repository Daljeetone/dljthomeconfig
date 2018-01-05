//
//  SAMBlock.h
//  CoreAutomationDevice
//
//  Created by Yuk Lai Suen on 2/18/13.
//

/********************************************************************
 Class to support remote block invocation (Incomplete) - Yuk Lai Suen (2/22/2013)
 ********************************************************************/

#import <Foundation/Foundation.h>
#import "CAMSimpleAutomationProtocol.h"
#import <Block_private.h>

#define SAMBlockReferenceId @"CEBB33E9-F43C-42DA-B256-45382873BEC6"
#define SAMBlockCalledId @"58AF1E1F-9114-48D8-BE8B-839C045047A4"
#define SAMBlockFlags @"0"
#define SAMBlockSignature @"1"
#define SAMBlockResult @"2"

@interface SAMRemoteBlockProxy : NSObject
+ (id)proxyWithObject:(NSDictionary *)dictionary simple:(id<CAMSimpleAutomationProtocol>)simple;
@end

/** \brief This is an object meant to hold a block on the *host* device.
 *
 * The host executes the block passed to the -executeBlockCall:block:
 */
@interface SAMBlockWrapper : NSObject
{
@private
    id block;
    NSNumber *blockId;
    NSString *signature;
    int flags;
    id<CAMSimpleAutomationProtocol> simple;
}
@property (nonatomic, retain, readonly) NSNumber *blockId;
@property (nonatomic, retain, readonly) id block;
@property (nonatomic, assign, readonly) void *blockFunctionPointer;
@property (nonatomic, copy,   readonly) NSString *signature;
- (id)initWithBlock:(id)block simple:(id<CAMSimpleAutomationProtocol>)simple;
- (NSDictionary *)encodeToDictionary;
@end
