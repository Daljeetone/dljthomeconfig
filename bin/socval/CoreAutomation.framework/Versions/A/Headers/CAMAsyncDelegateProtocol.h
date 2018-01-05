//
//  CAMTargetAsyncDelegateProtocol.h
//  CoreAutomation
//
//  Created by Chen Huang on 11/16/15.
//
//

@class CAMDarwinTarget;

@protocol CAMAsyncDelegateProtocol <NSObject>

/**
 *  This function will be invoked whenever there is a new plist arrived from the device
 *
 *  @param plist                The plist sent from device.
 *  @param target               The device that receives this notification
 *  @param isRoot               Whether this is from Root connection or Mobile/User connection.
 */
- (void)AsyncReceivedResponse:(NSArray *)plist from:(CAMDarwinTarget *)target isRoot:(BOOL)isRoot;

@end
