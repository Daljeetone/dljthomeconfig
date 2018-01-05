FRAMEWORK = 'CoreAutomation.framework'
XCODESELECT = '/usr/bin/xcode-select'
PSW_VERS= '`xcrun --find psw_vers`'
ca_path = ''

# Our favorite places are:
favoritePlaces = ['/AppleInternal/Library/WirelessAutomation', '/AppleInternal/Library/Frameworks']

# If we have developer tools installed, look there as well.
if File.exists?(XCODESELECT) and File.exists?(PSW_VERS)
	PLATFORM_DIR  = `#{XCODESELECT} -print-path`.strip()
	IOS_VERSION = `#{PSW_VERS} -productVersion`.strip()
	CA_PATH = "#{PLATFORM_DIR}/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS#{IOS_VERSION}.Internal.sdk/AppleInternal/Library/Frameworks"
	favoritePlaces << CA_PATH
end

favoritePlaces.each() do |path|
	directory = File.join(path, FRAMEWORK)
	if not File.exists?(directory)
		# print "WARNING: Cannot find #{directory}.\n"
	else
		ca_path = directory
		break
	end
end

COREAUTOMATION_PATH = ca_path
if COREAUTOMATION_PATH.nil? or not File.exists?(COREAUTOMATION_PATH)
	print "FATAL: Didn't find #{FRAMEWORK} on the system.\n"
	print "(we looked in #{favoritePlaces.join(', ')}).\n"
	exit(1)
end

def using_macruby?
	# if we have framework, we are running in macruby
	Kernel.respond_to?(:framework)
end

if using_macruby?
	framework(COREAUTOMATION_PATH)
else
	require 'osx/foundation'
	# Ruby's bridgesupport parser doesn't like the customized .bridgesupport file that Python needs <rdar://12436344>, so give Ruby a dummy .bridgesupport file.
	rubyBridgePath = File.join(COREAUTOMATION_PATH, "Resources", "BridgeSupport", "Ruby")
	OSX.__load_bridge_support_file__(rubyBridgePath, "CoreAutomation")
	OSX.require_framework(COREAUTOMATION_PATH)
end

dirname = File.dirname(__FILE__)

require dirname + "/cam/embedded_device.rb"
require dirname + "/cam/wifi_interface.rb"
require dirname + "/cam/mac_os_x_machine.rb"
require dirname + "/cam/uia_app.rb"
require dirname + "/cam/multi_target.rb"
require dirname + "/cam/xbs_build.rb"
require dirname + "/cam/xbs_event_manager_client.rb"
require dirname + "/cam/bus_boy_usb_controller.rb"
