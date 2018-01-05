package CoreAutomation;
use base Exporter, DynaLoader;
$VERSION = '1.0';
    
use PerlObjCBridge;
use Foundation;

my $framework_loaded = 0;

BEGIN {
	my $framework = 'CoreAutomation.framework';
	my $xcodeselect = "/usr/bin/xcode-select";
	chomp(my $psw_vers = `xcrun --find psw_vers`);
	my $coreautomation_path = "";

	# Our favorite places are:
	@favorite_places = ("/AppleInternal/Library/WirelessAutomation/", "/AppleInternal/Library/Frameworks/");

	# If we have developer tools installed, look there as well.
	if ((-e $xcodeselect) && (-e $psw_vers)) {
		my $developer_path = `$xcodeselect -print-path`;
		chomp($developer_path);
		my $ios_version = `$psw_vers -productVersion`;
		chomp($ios_version);
		my $ca_path = $developer_path . '/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS' . $ios_version . '.Internal.sdk/AppleInternal/Library/Frameworks';
		push (@favorite_places, $ca_path);
	}

	foreach (@favorite_places) {
		my $directory = join('/', $_, $framework);
		if ( -d $directory) {
			$coreautomation_path = $directory;
			last;
		} else {
			# print STDERR "WARNING: Cannot find $directory.\n";
		}
	}

	if ($coreautomation_path eq '' || ! -d $coreautomation_path) {
		print STDERR "FATAL: Didn't find $framework in @favorite_places";
		print STDERR "(we looked in " + join(", ", @favorite_places) + ")";
		exit 1;
	}

	$framework = NSBundle->alloc()->initWithPath_($coreautomation_path);

	$framework->load();
	if ($framework->isLoaded()) {
		$framework_loaded = 1;
	} else {
		print STDERR "Failed to load CoreAutomation framework at $path\n";
	}
}

package CAMEmbeddedDevice;
use base PerlObjCBridge;

package CAMXBSBuild;
use base PerlObjCBridge;

package CAMMultiDevice;
use base PerlObjCBridge;

package CAMMacOSXTarget;
use base PerlObjCBridge;

package CAMUIAApp;
use base PerlObjCBridge;

package CAMXBSEventManagerClient;
use base PerlObjCBridge;

1;
