# Start of module
package SysSWE;

use strict;
use Exporter;

our $VERSION     = 1.00;
our @ISA         = qw(Exporter);
our @EXPORT      = qw(
	IsWorkDay
	AddWorkDays
);
our @EXPORT_OK   = qw();
our %EXPORT_TAGS = ();

use POSIX;

my @Holidays = (
	# Apple corporate 2013
	# https://hrweb.cdn-apple.com/US/en/subtopic/431
	DateTime->new(month =>  1, day =>  1, year => 2013), # New Year’s Day            Jan 1 
	DateTime->new(month =>  5, day => 27, year => 2013), # Memorial Day              May 27
	DateTime->new(month =>  7, day =>  4, year => 2013), # Independence Day          Jul 4 
	DateTime->new(month =>  9, day =>  2, year => 2013), # Labor Day                 Sep 2 
	DateTime->new(month => 11, day => 25, year => 2013), # Thanksgiving Bonus        Nov 25
	DateTime->new(month => 11, day => 26, year => 2013), # Thanksgiving Bonus        Nov 26
	DateTime->new(month => 11, day => 27, year => 2013), # Thanksgiving Bonus        Nov 27
	DateTime->new(month => 11, day => 28, year => 2013), # Thanksgiving              Nov 28
	DateTime->new(month => 11, day => 29, year => 2013), # Day after Thanksgiving    Nov 29
	DateTime->new(month => 12, day => 24, year => 2013), # Christmas Eve             Dec 24
	DateTime->new(month => 12, day => 25, year => 2013), # Christmas Day             Dec 25
	DateTime->new(month => 12, day => 26, year => 2013), # Winter Holiday Shutdown   Dec 26
	DateTime->new(month => 12, day => 27, year => 2013), # Winter Holiday Shutdown   Dec 27
	DateTime->new(month => 12, day => 30, year => 2013), # Winter Holiday Shutdown   Dec 30
	DateTime->new(month => 12, day => 31, year => 2013), # New Year’s Eve            Dec 31

	# Apple corporate 2014
	# https://hrweb.cdn-apple.com/US/en/subtopic/431
	DateTime->new(month =>  1, day =>  1, year => 2014), # New Year’s Day           Jan 1 
	DateTime->new(month =>  5, day => 26, year => 2014), # Memorial Day             May 26
	DateTime->new(month =>  7, day =>  4, year => 2014), # Independence Day         Jul 4 
	DateTime->new(month =>  9, day =>  1, year => 2014), # Labor Day                Sep 1 
	DateTime->new(month => 11, day => 27, year => 2014), # Thanksgiving             Nov 27
	DateTime->new(month => 11, day => 28, year => 2014), # Day after Thanksgiving   Nov 28
	DateTime->new(month => 12, day => 24, year => 2014), # Christmas Eve            Dec 24
	DateTime->new(month => 12, day => 25, year => 2014), # Christmas Day            Dec 25
	DateTime->new(month => 12, day => 26, year => 2014), # Winter Holiday Shutdown  Dec 26
	DateTime->new(month => 12, day => 29, year => 2014), # Winter Holiday Shutdown  Dec 29
	DateTime->new(month => 12, day => 30, year => 2014), # Winter Holiday Shutdown  Dec 30
	DateTime->new(month => 12, day => 31, year => 2014), # New Year’s Eve           Dec 31
);

sub IsWorkDay
{
	my ($Date) = @_;
	my $Day;
	if ($Date->day_of_week() <= 5) {
		foreach $Day (@Holidays) {
			# Calling DateTime->compare($Date, $Day) will compare times as
			# well, but we want to compare only the date portion
			if ($Date->year() == $Day->year()) {
				if ($Date->month() == $Day->month()) {
					if ($Date->day() == $Day->day()) {
						return 0;
					}
				}
			}
		}
		return 1;
	}
	return 0;
}

sub AddWorkDays
{
	my ($Date, $Days) = @_;

	while (!IsWorkDay($Date)) {
		$Date->add(days => 1);
	}
	# This should really be using ceil()...
	for ($Days = floor($Days); $Days > 0; --$Days) {
		$Date->add(days => 1);
		while (!IsWorkDay($Date)) {
			$Date->add(days => 1);
		}
	}
}

# End of module
1;
