#
#  CoreAutomation.py
#
#  Created on Chris Whitney on 5/7/2010.
#  Copyright (c) 2010 Apple Inc. All rights reserved.

'''
    Python mapping for CoreAutomation.framework when installed by WirelessAutomation's .pkg installer
    '''

import objc, os, subprocess, sys
from PyObjCTools import Debugging
Debugging.installVerboseExceptionHandler()

# Default CoreAutomation is /AppleInternal/Library/WirelessAutomation/CoreAutomation.framework
FRAMEWORKNAME = 'CoreAutomation'
COREAUTOMATION_PATH = '/AppleInternal/Library/WirelessAutomation/CoreAutomation.framework'
FAVORITEPLACES = [COREAUTOMATION_PATH]

# Fallback to HomeDiagnostic
if not os.path.exists(COREAUTOMATION_PATH):
	COREAUTOMATION_PATH = '/AppleInternal/Library/Frameworks/CoreAutomation.framework'
	FAVORITEPLACES.append(COREAUTOMATION_PATH)

# Fallback to SDK
if not os.path.exists(COREAUTOMATION_PATH):
	XCODESELECT = "/usr/bin/xcode-select"
	PSW_VERS = subprocess.Popen(['xcrun', '--find', 'psw_vers'], stdout=subprocess.PIPE).communicate()[0].strip()
	if os.path.exists(XCODESELECT) and os.path.exists(PSW_VERS):
		PLATFORM_DIR = subprocess.Popen([XCODESELECT, '-print-path'], stdout=subprocess.PIPE).communicate()[0].strip()
		IOS_VERSION = subprocess.Popen([PSW_VERS, '-productVersion'], stdout=subprocess.PIPE).communicate()[0].strip()
		COREAUTOMATION_PATH = os.path.join(PLATFORM_DIR, 'Platforms/iPhoneOS.platform/Developer/SDKs',
			'iPhoneOS' + IOS_VERSION + '.Internal.sdk/AppleInternal/Library/Frameworks/CoreAutomation.framework')
		FAVORITEPLACES.append(COREAUTOMATION_PATH)

if not COREAUTOMATION_PATH or not os.path.exists(COREAUTOMATION_PATH):
	print "FATAL: Did not find %s on the system." % FRAMEWORKNAME
	print "(we looked in %s)." % (', '.join(FAVORITEPLACES))
	sys.exit(1)

__bundle__ = objc.initFrameworkWrapper(FRAMEWORKNAME, frameworkIdentifier='com.apple.coreautomation', frameworkPath=objc.pathForFramework(COREAUTOMATION_PATH), globals=globals())
bridgesupportfile = __bundle__.pathForResource_ofType_inDirectory_(FRAMEWORKNAME, 'bridgesupport', 'BridgeSupport')

try:
	if os.path.exists(bridgesupportfile):
		f = open(bridgesupportfile, 'r')
		xmldata = f.read()
		f.close()
		objc.parseBridgeSupport(xmldata, globals(), FRAMEWORKNAME)
except:
	sys.stderr.write("Warning: %s looks unparsable or doesn't exist - ignoring.\n" % (FRAMEWORKNAME + '.bridgesupport'))


del objc, os, subprocess, sys
