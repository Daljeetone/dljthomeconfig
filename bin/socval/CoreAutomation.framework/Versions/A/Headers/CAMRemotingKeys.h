//
//  CAMRemotingKeys.h
//  CoreAutomation
//
//  Created by Christopher Whitney on 10/27/11.
//  Copyright (c) 2011 Apple Inc. All rights reserved.
//

// Requests should set the following keys
#define kCAMRemoteClassPathKey		@"classpath"
#define kCAMRemoteMethodKey			@"method"
#define kCAMRemoteArgumentsKey		@"arguments"

// Failure responses will set at minimum error-code
#define kCAMRemoteErrorKey						@"error"
#define kCAMRemoteErrorDictionaryDomainKey		@"error-domain"
#define kCAMRemoteErrorDictionaryCodeKey		@"error-code"
#define kCAMRemoteErrorDictionaryUserInfoKey	@"error-info"

// Successful responses are either an empty dict or dict with a return-value
#define kCAMRemoteReturnClassKey	@"return-class"
#define kCAMRemoteReturnValueKey	@"return-value"

// Place holders needing some kind of conversion
#define kCAMRemoteNilArgumentKey    @"argument-is-nil"
#define kCAMRemoteBlockArgumentKey  @"argument-is-block"

// Convert a kCAM*ShortName macro into a string
#define _NSStringFromMacro(arg) @#arg
#define NSStringFromMacro(arg) _NSStringFromMacro(arg)
