//
//  CAMAddressBook.h
//  CoreAutomation
//
//  Created by Chris Whitney on 2/9/12.
//  Copyright (c) 2012 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CAMReturnValues.h"

#define kCAMAddressBookShortName addressBook

@protocol CAMAddressBook
@optional
#pragma mark -
#pragma mark AddressBook
/*!
 @method allPhoneNumbers:
 @abstract Grab all contacts with phone numbers from the Address Book.
 @discussion Excludes pager, fax, and custom-labeled numbers.
 @return Returns an array of dictionaries. Each dictionaries is a single (name + phone type), number pair.
 */
- (CAMReturnArray*)allPhoneNumbers;

/*!
 @method allContact:
 @abstract Grab all contacts.
 @discussion AllContacts available.
 @return Returns an dictionary. The key of the dictionary is the contact ID in address book.
    The element is an array containing contactID, contact Name, phone Number (NSArray), emails (NSArray)
 */
- (CAMReturnDictionary*)allContacts;

/*!
 @method addContact:
 @abstract add a contact.
 @discussion contactInfo should contain:
    "firstName" (key): NSString (value)
    "lastName" (key): NSString (value)
    "phoneNumbers" (key): NSDictionary (value) of labels (NSString) and numbers (NSString)
    "emails" (key): NSDictionary (value) of labels (NSString) and emails (NSString)
 @return The contact ID added.
 */
- (CAMReturnInteger *)addContact:(NSDictionary *)contactInfo;

/*!
 @method removeContact:
 @abstract remove a contact.
 @discussion Remove the contact that has "contactID"
 @return Whether the addition is successful.
 */
- (CAMReturnBool*)removeContact:(NSNumber *)contactID;

/*!
 @method blockContact:
 @abstract block contact.
 @discussion Block the contact that has "contactID". It will block all his emails and phone numbers.
    which means no SMS, iMessage, MMS, PhoneCall, Emails from this contact.
 @return Whether the addition is successful.
 */
- (CAMReturnBool*)blockContact:(NSNumber *)contactID;

/*!
 @method unblockContact:
 @abstract Unblock contact.
 @discussion unblock the contact that has "contactID". It will unblock all his emails and phone numbers.
 @return Whether the addition is successful.
 */
- (CAMReturnBool*)unblockContact:(NSNumber*)contactID;

// Convenience functions.

/*!
 @method blockEmail:
 @abstract block a specific email
 @discussion block a specific email.
 @return Whether the block is successful.
 */
- (CAMReturnBool*)blockEmail:(NSString *)email;

/*!
 @method blockPhoneNumber:
 @abstract block a specific phone number
 @discussion block a specific phone number.
 @return Whether the block is successful.
 */
- (CAMReturnBool*)blockPhoneNumber:(NSString *)phoneNumber;

/*!
 @method unblockEmail:
 @abstract unblock an email.
 @return Whether the unblock is successful.
 */
- (CAMReturnBool*)unblockEmail:(NSString *)email;

/*!
 @method unblockPhoneNumber:
 @abstract unblock an phone number.
 @return Whether the unblock is successful.
 */
- (CAMReturnBool*)unblockPhoneNumber:(NSString *)phoneNumber;

/*!
 @method isIncomingCommunicationBlockedForPhoneNumber:
 @abstract Whether the phone number is in the block list or not.
 @return BOOL Whether the phone number is in the block list or not.
 */
- (CAMReturnBool *)isIncomingCommunicationBlockedForPhoneNumber:(NSString *)phoneNumber;

/*!
 @method isIncomingCommunicationBlockedForEmailAddress:
 @abstract Whether the email is in the block list or not.
 @return BOOL Whether the email is in the block list or not.
 */
- (CAMReturnBool *)isIncomingCommunicationBlockedForEmailAddress:(NSString *)emailAddress;

#pragma mark -
#pragma mark AddressBookFavorite

/*!
 @method addContact:toFavorite:
 @abstract Add a contact to favorite list.
 @param contactID contactID of the contact
 @param type Type can be 
    kABFavoritesEntryTypePhone = 0, 
    kABFavoritesEntryTypeFaceTime
    kABFavoritesEntryTypeFaceTimeAudio
    kABFavoritesEntryTypeAny
 @return BOOL success or failure.
 */
- (CAMReturnBool *)addContact:(NSNumber *)contactID toFavorite:(NSNumber *)type;

/*!
 @method removeFavorite:fromContact:
 @abstract Remove a contact from favorite list.
 @param contactID contactID of the contact
 @param type Type can be
     kABFavoritesEntryTypePhone = 0,
     kABFavoritesEntryTypeFaceTime
     kABFavoritesEntryTypeFaceTimeAudio
     kABFavoritesEntryTypeAny
 @return BOOL success or failure.
 */
- (CAMReturnVoid *)removeFavorite:(NSNumber *)type fromContact:(NSNumber *)contactID;

- (CAMReturnVoid *)removeFavoriteEntryAtIndex:(NSNumber *)index;

- (CAMReturnBool *)isProperty:(NSString *)property
               withIdentifier:(NSNumber *)identifier
                  fromContact:(NSNumber *)contactID
         inFavoriteListOfType:(NSNumber *)type;

- (CAMReturnBool *)addProperty:(NSString *)property
                withIdentifier:(NSNumber *)identifier
                   fromContact:(NSNumber *)contactID
          toFavoriteListOfType:(NSNumber *)type;
/*!
 @method listAllContactsInFavorite:
 @abstract List all favorite in the favorite list.
 @return Array of favorites.
 */
- (CAMReturnArray *)listAllFavoriteEntries;
//- (CAMReturnVoid *)removeAllFavoriteEntries;
@end
