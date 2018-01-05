#!/usr/bin/perl

use File::Temp qw(tempdir);
use File::Glob qw(:bsd_glob);
use File::Fetch;
use File::Find;
use File::Basename;
use Archive::Extract;

use autodie;
use strict;
use warnings;

my $YELLOW = "\033[1;33m";
my $BOLD = "\033[1m";
my $RESET = "\033[0m";

my $Version = $ARGV[0];
die "${\basename $0}: Missing diags version (e.g. 15C0547bm)\n" unless $Version;

my @GoodFrames;
my $Arch = "arm64";

print("Paste panic spew here and terminate with <Ctrl-D>, or cancel with <Ctrl-C>\n");
{
	my $FrameNumber;
	while (<STDIN>) {
		if (m/^#(\d+).*?(\(arm\)|\(thumb\))?$/) {
			$FrameNumber = int($1);
			if (defined $2) {
				$Arch = "arm";
			}
		} elsif (m/(\w+\.macho).*offset.*(0x[0-9a-f]+)/i) {
			push @GoodFrames, {
				Number => $FrameNumber,
				Name => $1,
				Offset => hex($2)
			};
			$FrameNumber = undef;
		}
	}
}
print("\n\n");

print("Identified ${\scalar @GoodFrames} addresses\n");
exit if (@GoodFrames == 0);
print("\n");

my $TempDir = tempdir("/tmp/symbolicate-XXXXXXX", CLEANUP => 1) or die;
print("Temporary directory is $TempDir\n");
my $OutDir = "${TempDir}/Uncompressed";
my $DownloadDir = "${TempDir}/Download";
my $ShastaDir = "${TempDir}/Shasta";
mkdir($OutDir) or die;
mkdir($DownloadDir) or die;
mkdir($ShastaDir) or die;
print("\n");

print("Downloading extras for ${Version} from build server...\n");
{
	my $URL = 'http://wendigo.apple.com/panic_query.php?user=PanicUser22&passwd=998pu822&version=' . $Version;
	my $Fetcher = File::Fetch->new(uri => $URL) or die;
	my $Extras = $Fetcher->fetch(to => $DownloadDir) or die "Failed to fetch ${Version}\n";
	my $Archiver = Archive::Extract->new(archive => $Extras, type => "zip") or die;
	$Archiver->extract(to => $OutDir) or die "Bad archive\n";
}
print("\n");

print("Downloading source for ${Version} from source control...\n");
{
	my $Remote = 'git@gitlab.sd.apple.com:blackops/shasta.git';
	(qx(git ls-remote '${Remote}' | grep -e 'refs/tags/.*_${Version}\$') or die) =~ m#[0-9a-f]+\s+(refs/tags/(.*))#i;
	print("Tag is ${2}\n");
	system("git archive --format=tar --remote='${Remote}' ${1} | tar -C '${ShastaDir}' -xf -") and die;
}
print("\n");

foreach my $Frame (@GoodFrames) {
	my $OffsetString = sprintf("0x%X", $Frame->{Offset});

	my $Lead = sprintf("[%03d] %-30s %-10s ", $Frame->{Number}, $Frame->{Name}, $OffsetString);

	my @AllPaths = bsd_glob("$OutDir/*_extra/*_release/{bootloader,diag}/$Frame->{Name}");
	if (@AllPaths) {
		foreach my $Path (@AllPaths) {
			print("${YELLOW}${Lead}");
			(qx(atos -o '${Path}' -arch ${Arch} '${OffsetString}') or die) =~ m#(\S+)\s+\(in .*\)\s+\((.*):(\d+)\)$#;
			my ($Func, $File, $Line) = ($1, $2, int($3));
			print "$Func ($File:$Line)${RESET}\n";
			find(
				sub
				{
					return unless ($_ eq $File);
					open(my $Handle, "<", $File::Find::name) or die;
					my @FileLines = <$Handle>;
					print("===> ${File::Find::name} <===\n");
					print(join("", grep { defined; } @FileLines[$Line-4, $Line-2]));
					print("${BOLD}" . $FileLines[$Line-1] . "${RESET}") if ($FileLines[$Line-1]);
					print(join("", grep { defined; } @FileLines[$Line+0, $Line+2]));
				},
				$ShastaDir);
		}
	} else {
		print("${YELLOW}${Lead}${RESET}\n");
	}
	print("\n");
}
