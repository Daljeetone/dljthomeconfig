# Back-up variables (shouldn't be used normally)
XCODE_PLATFORM_PATH := $(shell xcodebuild -sdk iphoneos.internal -version PlatformPath)
XCODE_DEVELOPER_PATH := $(shell xcode-select --print-path)

# XBS-defined variables
DSTROOT ?=
OBJROOT ?=
SYMROOT ?=
SRCROOT ?=
DEVELOPER_INSTALL_DIR ?=
ARM_PLATFORM_DIR ?= $(XCODE_PLATFORM_PATH)
DEVELOPER_DIR ?= $(XCODE_DEVELOPER_PATH)

# Intra-SDK paths
# e.g. ARM_PLATFORM_DIR = /BuildRoot/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform
# e.g. DEVELOPER_DIR = /BuildRoot/Applications/Xcode.app/Contents/Developer
# e.g. DEVELOPER_INSTALL_DIR = /Applications/Xcode.app/Contents/Developer
# e.g. INSTALL_PLATFORM_PATH = /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform
INSTALL_PLATFORM_PATH = $(subst $(DEVELOPER_DIR),$(DEVELOPER_INSTALL_DIR),$(ARM_PLATFORM_DIR))
INSTALL_DIAGS_SUPPORT_PATH = $(INSTALL_PLATFORM_PATH)/usr/local/lib/EFIDiagsSupport

.PHONY: installsrc installhdrs install clean
.PHONY: LLDBScripts

installsrc:
	@ditto -v Makefile "$(SRCROOT)/"
	@ditto -v scripts/debug/LLDB/Python "$(SRCROOT)/scripts/debug/LLDB/Python"

installhdrs:
	@echo "This projects has no headers"

LLDBScripts:
	@ditto --norsrc -v scripts/debug/LLDB/Python/ $(DSTROOT)/$(INSTALL_DIAGS_SUPPORT_PATH)/scripts/debug/LLDB/Python

install: LLDBScripts

clean:
ifeq ($(OBJROOT),)
	@echo Cowardly refusing to delete
else
	rm -Rf "$(OBJROOT)/*"
endif
