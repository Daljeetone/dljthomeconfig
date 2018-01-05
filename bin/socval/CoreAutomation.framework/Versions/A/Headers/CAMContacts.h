//
//  CAMContacts.h
//  coreautomationd
//
//  Created by Shakul Hameed on 11/2/16.
//
//

#import <Foundation/Foundation.h>
#import "CAMReturnValues.h"

#define kCAMContactsShortName contacts

@protocol CAMContacts
@optional

/*!
 @method addContact:
 @abstract add a contact.
 @discussion contactInfo should contain:
 "givenName" (key): NSString (value)
 "familyName" (key): NSString (value)
 "nickname" (key): NSString (value)
 "phoneNumbers" (key): NSDictionary (value) of labels("iPhone"/"mobile"/"main"/"home fax"/"work fax"/"other fax"/"pager") (NSString) and numbers (NSString)
 "emailAddresses" (key): NSDictionary (value) of labels ("home"/"work"/"other") (NSString) and emails (NSString)
 @return Unique contact identifier.
 */
- (CAMReturnString *)addContact:(NSDictionary *)contactInfo;

/*!
 @method deleteContact:
 @abstract delete a contact.
 @param identifier is the unique contact identifier.
 @discussion Contact identifier is returned during add contact.
 @return @YES on success or @NO on failure.
 */
- (CAMReturnBool *)deleteContact:(NSString *)identifier;

/*!
 @method allContacts
 @abstract Return all contacts in dictionary.
 */
- (CAMReturnDictionary *)allContacts;
@end
