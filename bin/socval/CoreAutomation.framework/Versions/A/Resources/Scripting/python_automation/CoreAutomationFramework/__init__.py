#!/usr/bin/python
#
#  CoreAutomationFramework/__init__.py
#
#  Created on Chris Whitney on 5/7/2010.
#  Copyright (c) 2010 Apple Inc. All rights reserved.

'''
Python module for CoreAutomation.framework
'''

import objc, os, subprocess
from PyObjCTools import Debugging
Debugging.installVerboseExceptionHandler()

FRAMEWORK = 'CoreAutomation.framework'
XCODESELECT = "/usr/bin/xcode-select"
COREAUTOMATION_PATH = None

# Our favorite places are:
FAVORITEPLACES = ['/Library/Frameworks', '/AppleInternal/Library/Frameworks']

# If we have developer tools installed, look there as well.
if os.path.exists(XCODESELECT):
	PLATFORM_DIR = subprocess.Popen([XCODESELECT, '-print-path'], stdout=subprocess.PIPE).communicate()[0].strip()
	CAPATH = os.path.join(PLATFORM_DIR, 'Platforms/iPhoneOS.platform/System/Library/PrivateFrameworks')
	FAVORITEPLACES.append(CAPATH)

for path in FAVORITEPLACES:
	DIRECTORY = os.path.join(path, FRAMEWORK)
	if not os.path.exists(DIRECTORY):
		# print 'WARNING: Cannot find %s.' % DIRECTORY
		pass
	else:
		COREAUTOMATION_PATH = DIRECTORY
		break

if COREAUTOMATION_PATH is None or not os.path.exists(COREAUTOMATION_PATH):
	print "FATAL: Didn't find %s on the system." % FRAMEWORK
	print "(we looked in %s)." % (', '.join(FAVORITEPLACES))
	exit(1)

__bundle__ = objc.initFrameworkWrapper('CoreAutomationFramework', 
	frameworkIdentifier='com.apple.purple.coreautomation',
	frameworkPath=objc.pathForFramework(COREAUTOMATION_PATH),
	globals=globals())

del objc, os, subprocess
