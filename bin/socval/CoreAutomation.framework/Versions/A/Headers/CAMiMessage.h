//
//  CAMiMessage.h
//  coreautomationd
//
//  Created by Wayne Finlay on 3/23/16.
//
//

#import <Foundation/Foundation.h>
#import "CAMReturnValues.h"

#define kCAMiMessageShortName iMessage

@protocol CAMiMessage
@optional

/*!
 @method     info
 @abstract   Get device information.
 @return     Returns dictionary of device properties.
 */
- (CAMReturnDictionary *)info;

/*!
 @method    toggleiMessagePhoneNumberAccountService
 @abstract  Switch iMessage Phone Number based account.
 @return    Returns True if iMessage Service is completely switched.
 */
- (CAMReturnBool*) toggleiMessagePhoneNumberAccountService:(NSNumber*)timeout;

/*!
 @method     enableiMessage
 @abstract   Using Apple ID sign-in or sign-out of FT.
 @param      enable 1 to sign-in, 0 to sign-out the AppleID account from iMessage. Sign-out does not require password.
 @return     Returns True if requested sign-in or sign-out operation is successful.
 */
- (CAMReturnBool*) enableiMessage:(NSNumber *)enable withAppleID:(NSString *)appleID withPassword:(NSString *)password withTimeout:(NSNumber *)timeout;

/*!
 @method     list
 @abstract   Get iMessage accounts on the device.
 @return     Returns list of account dictionary.
 */
- (CAMReturnArray *)list;

/*!
 @method     sendMessage
 @abstract   Send iMessage to recipients.
 @param      accountLogin Account login string, can be phone number or email
             recipients Recipients string array
             subjectString Message subject string
             messageString Message content string
 @return     Returns sent message dictionary.
 */
- (CAMReturnDictionary *)sendMessage:(NSString *)accountLogin withRecipients:(NSArray *)recipients withMessage:(NSString *)messageString withFiles:(NSArray *)filePaths;

/*!
 @method     deleteMessage
 @abstract   Delete iMessage with account login, recipients, unique ID
 @param      accountLogin Account login string, can be phone number or email
             recipients Recipients string array
             messageGUID Message unique ID string
 @return     Returns True if successful.
 */
- (CAMReturnBool *)deleteMessage:(NSString *)accountLogin withRecipients:(NSArray *)recipients withMessageGUID:(NSString *)messageGUID;

/*!
 @method     deleteMessageWithGUID
 @abstract   Delete iMessage with unique ID.
 @param      messageGUID Message unique ID string, find this ID from sendMessage/chats
 @return     Returns True if successful.
 */
- (CAMReturnBool *)deleteMessageWithGUID:(NSString *)messageGUID;

/*!
 @method     chats
 @abstract   Get all chats.
 @return     Returns list of chat dictionary.
 */
- (CAMReturnArray *)chats;

/*!
 @method     getMessageWithGUID
 @abstract   Get message with unique ID.
 @param      messageGUID Message unique ID string, find this ID from sendMessage/chats
 @return     Returns message dictionary.
 */
- (CAMReturnDictionary *)getMessageWithGUID:(NSString *)messageGUID;

/*!
 @method     getMessageDictionaryWithGUID
 @abstract   Get message with unique ID (uses IMDPersistence method)
 @param      messageGUID Message unique ID string, find this ID from sendMessage/chats
 @return     Returns message dictionary.
 */
- (CAMReturnDictionary *)getMessageDictionaryWithGUID:(NSString *)messageGUID;

/*!
 @method     sendMessageSync
 @abstract   send message in a synchronous way blocking on imagent
 @param      messageText message text
             destinationID destination handle
             filePaths file paths, if any
             groupID groupID of group to send to
             service SMS vs iMessage
             timeOut time to wait before failing message send
 @return     Returns message dictionary.
 */
- (CAMReturnDictionary *)sendMessageSync:(NSString *)messageText destinationID:(NSString *)destinationID filePaths:(NSArray *)filePaths groupID:(NSString *)groupID service:(NSString *)service timeOut:(NSNumber *)timeOut;

/*!
 @method     addParticipantsToGroupWithGroupID
 @abstract   add participants to group in a synchronous way blocking on imagent
 @param      groupID group identifier
             participants array of participant handles
             timeOut time to wait before failing message send
             extraParameters optional additional parameters
 @return     Returns message dictionary.
 */
- (CAMReturnDictionary *)addParticipantsToGroupWithGroupID:(NSString *)groupID participants:(NSArray<NSString *> *)participants timeOut:(NSNumber *)timeOut extraParameters:(NSDictionary *)extraParameters;

/*!
 @method     removeParticipantsFromGroupWithGroupID
 @abstract   remove participants to group in a synchronous way blocking on imagent
 @param      groupID group identifier
             participants array of participant handles
             timeOut time to wait before failing message send
             extraParameters optional additional parameters
 @return     Returns message dictionary.
 */
- (CAMReturnDictionary *)removeParticipantsFromGroupWithGroupID:(NSString *)groupID participants:(NSArray<NSString *> *)participants timeOut:(NSNumber *)timeOut extraParameters:(NSDictionary *)extraParameters;

/*!
 @method     changeGroupNameWithGroupID
 @abstract   change group name on a group in a synchronous way blocking on imagent
 @param      groupID group identifier
             newName new name for group
             timeOut time to wait before failing message send
             extraParameters optional additional parameters
 @return     Returns message dictionary.
 */
- (CAMReturnDictionary *)changeGroupNameWithGroupID:(NSString *)groupID newName:(NSString *) newName timeOut:(NSNumber *)timeOut extraParameters:(NSDictionary *)extraParameters;

/*!
 @method     groupParticipantsWithGroupID
 @abstract   get list of participants in group
 @param      groupID group identifier
             timeOut time to wait before failing message send
             extraParameters optional additional parameters
 @return     Returns message dictionary.
 */
- (CAMReturnDictionary *)groupParticipantsWithGroupID:(NSString *)groupID timeOut:(NSNumber *)timeOut extraParameters:(NSDictionary *)extraParameters;

/*!
 @method     groupNameWithGroupID
 @abstract   get name of a group with the groupID
 @param      groupID group identifier
             timeOut time to wait before failing message send
             extraParameters optional additional parameters
 @return     Returns message dictionary.
 */
- (CAMReturnDictionary *)groupNameWithGroupID:(NSString *)groupID timeOut:(NSNumber *)timeOut extraParameters:(NSDictionary *)extraParameters;

/*!
 @method     createGroupChatWithDestinationIDs
 @abstract   create a group chat with the passed destination IDs
 @param      destinationIDs array of destinationIDs
             extraParameters optional additional parameters
 @return     Returns message dictionary with key @"groupID", the new groupID that was created.
 */
- (CAMReturnDictionary *)createGroupChatWithDestinationIDs:(NSArray *)destinationIDs extraParameters:(NSDictionary *)extraParameters;

/*!
 @method        IMCoreAutomationPerformOperationWithDictionary
 @abstract      Call IMCore method from coreautomation.
 @dict keys     Need to pass in method name and method arguments:
 @"methodName" - IMCore method name
 @"arg1", @"arg2", @"arg3".... - method arguments in order
 @return        Returns dictionary with results
 */
- (CAMReturnDictionary *)IMCoreAutomationPerformOperationWithDictionary:(NSDictionary *)argsDict;
@end
