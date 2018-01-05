#!/usr/bin/perl

use strict;
use Data::Dumper;
use POSIX;
use JSON;
use DateTime;
use DateTime::Format::Strptime;
use RadarWebServices;
use SysSWE;

binmode STDOUT, ":utf8";

my $Changed = 0;
my $WriteSchedule = 0;
my $WriteEffort = 0;
my $WritePriority = 0;
my $WriteDri = 0;
my $OriginalSchedule;
my $EffortFromFile = 0;
my $PriorityFromFile = 0;
my $DriFromFile = 0;
my $PuntRadars = 0;

my $ConfigFile;
my %EngineerData;
my $TlfProblemId;
my $TlfProblemKeyword;
my $TlfProblemComponent;
my $ProblemListString;
my @ProblemIdList;

my %DriList;

sub ParseProblemListString
{
	my ($ProblemId, $Field) = @_;
	my @Lines = grep { m!<rdar://problem/${ProblemId}>! } split("\n", $ProblemListString);
	die "Bad number of matches while looking for problem $ProblemId\n" if (scalar @Lines != 1);
	my $Pattern;
	if ($Field eq "effort") {
		$Pattern = "(\\d+)";
	} elsif ($Field eq "priority") {
		$Pattern = "P(\\d)"
	} elsif ($Field eq "disposition") {
		$Pattern = "(Single|Multi|Puntable)"
	} elsif ($Field eq "DRI") {
		$Pattern = "(" . join("|", keys %EngineerData) . ")";
	} else {
		die "Bad requested field $Field\n";
	}
	if (($Lines[0] =~ m!\|\s*${Pattern}\s*\|!) || ($Lines[0] =~ m!^\s*${Pattern}\s*\|!)) {
		return $1;
	}
	return;
}

foreach my $Arg (@ARGV) {
	if ($Arg eq "--write-schedule") {
		$WriteSchedule = 1;
	} elsif ($Arg eq "--write-effort") {
		$WriteEffort = 1;
	} elsif ($Arg eq "--write-priority") {
		$WritePriority = 1;
	} elsif ($Arg eq "--write-dri") {
		$WriteDri = 1;
	} elsif ($Arg eq "--write-all") {
		$WriteSchedule = 1;
		$WriteEffort = 1;
		$WritePriority = 1;
		$WriteDri = 1;
	} elsif ($Arg eq "--original") {
		$OriginalSchedule = 1;
	} elsif ($Arg eq "--current") {
		$OriginalSchedule = 0;
	} elsif ($Arg eq "--effort-from-file") {
		$EffortFromFile = 1;
	} elsif ($Arg eq "--priority-from-file") {
		$PriorityFromFile = 1;
	} elsif ($Arg eq "--dri-from-file") {
		$DriFromFile = 1;
	} elsif ($Arg eq "--from-file") {
		$EffortFromFile = 1;
		$PriorityFromFile = 1;
		$DriFromFile = 1;
	} elsif ($Arg eq "--punt") {
		$PuntRadars = 1;
	} elsif (!defined $ConfigFile) {
		$ConfigFile = $Arg;
	} else {
		die "Unknown argument " . $Arg . "\n";
	}
}

if ($WriteSchedule || $WriteEffort) {
	print("WRITE THROUGH MODE! RADARS WILL BE MODIFIED!\n\n");
}

die "Missing config file\n" unless (-f $ConfigFile);
eval `cat $ConfigFile`;

die "Require --original or --current\n" unless (defined $OriginalSchedule);
printf("Generating scedule for %s ETA dates\n", $OriginalSchedule ? "original" : "current");

if (defined $ProblemListString) {
	my @List = grep { m!<rdar://problem/(\d+)>! } split("\n", $ProblemListString);
	@ProblemIdList = map { m!<rdar://problem/(\d+)>!; $1 } @List;
}

printf("Fetching %d problems\n", scalar @ProblemIdList);
FetchRadarFields(\@ProblemIdList);

if ($PuntRadars) {
	my $Cutoff = 4;
	if (defined $ProblemListString) {
		@ProblemIdList = grep {
			ParseProblemListString($_, "disposition") ne "Puntable"
		} @ProblemIdList;
	}
	if ($PriorityFromFile && (defined $ProblemListString))  {
		@ProblemIdList = grep {
			my $Priority = GetRadarField($_, "priority");
			my $FilePriority = ParseProblemListString($_, "priority");
			(defined($FilePriority) && ($FilePriority <= $Cutoff)) || (!defined($FilePriority) && ($Priority <= $Cutoff))
		} @ProblemIdList;
	} else {
		@ProblemIdList = grep {
			GetRadarField($_, "priority") <= $Cutoff
		} @ProblemIdList;
	}
}

if ($TlfProblemId or $TlfProblemKeyword) {
	my $ExpectedProblems = join(" ", sort(@ProblemIdList));
	my $ActualProblems;
	my $Source;
	if ($TlfProblemId) {
		FetchRadarFields($TlfProblemId);
		$ActualProblems = join(" ", sort(GetRelatedProblems($TlfProblemId, "parent-of")));
		$Source = "TlfProblemId";
	} else {
		$ActualProblems = join(" ", sort(FindProblemsByKeyword($TlfProblemKeyword)));
		$Source = "TlfProblemKeyword";
	}
	unless ($ExpectedProblems eq $ActualProblems) {
		print "\n" .
			"INCONSISTENT \$" . $Source . " AND \@ProblemIdList\n" .
			"EXPECTED: " . $ExpectedProblems . "\n" .
			"ACTUAL: " . $ActualProblems . "\n\n";
	}
}
if ($TlfProblemId) {
	$TlfProblemComponent = GetRadarComponentField($TlfProblemId);
}

my $TargetCompletionField = $OriginalSchedule ? "targetCompletionOriginal" : "targetCompletionCurrent";
print("Generating taskOrder and $TargetCompletionField\n\n");

# Bump engineer start dates to account for completed work when calculating the running schedule
if (!$OriginalSchedule) {
	foreach my $ProblemId (@ProblemIdList) {
		next if (GetRadarField($ProblemId, "state") eq "Analyze");

		my $Responsible = (GetRadarPersonField($ProblemId, "dri") or GetRadarPersonField($ProblemId, "assignee"));
		my $Engineer = $EngineerData{$Responsible};
		next if (!defined $Engineer);

		my $ResolvedDate = GetRadarDateField($ProblemId, "resolvedAt");
		next if (!defined $ResolvedDate);
		$ResolvedDate = DateTime->new(month => $ResolvedDate->month(), day => $ResolvedDate->day(), year => $ResolvedDate->year());
		$Engineer->{Date} = $ResolvedDate if (DateTime->compare($Engineer->{Date}, $ResolvedDate) < 0);
	}
}

printf("%4s%1s  %-25s  %7s  %-10s%s  %3s  %s\n",
	"", "",
	"DRI",
	"Effort",
	"Date", " ",
	"Pri",
	"");
for (my $Index = 0; $Index < @ProblemIdList; $Index++) {
	my $ProblemId = $ProblemIdList[$Index];
	my %Settings = ( taskOrder => $Index + 1 );
	my $Responsible = 
		(($DriFromFile ?
			ParseProblemListString($ProblemId, "DRI") :
			GetRadarPersonField($ProblemId, "dri")) or
		GetRadarPersonField($ProblemId, "assignee"));
	my $Engineer = $EngineerData{$Responsible};
	my $ThisChanged = 0;
	my $EffortEstimateField = "effortOriginalTotalEstimate";
	my $EffortEstimate = GetRadarField($ProblemId, $EffortEstimateField);

	unless ($OriginalSchedule) {
		$EffortEstimateField = "effortCurrentTotalEstimate";
		my $CurrentEffortEstimate = GetRadarField($ProblemId, $EffortEstimateField);
		$EffortEstimate = $CurrentEffortEstimate if ($CurrentEffortEstimate > 0);
	}
	if ($EffortFromFile && (defined $ProblemListString)) {
		my $EffortDays = ParseProblemListString($ProblemId, "effort");
		$EffortEstimate = $EffortDays if ($EffortDays > 0);
	}
	$Settings{$EffortEstimateField} = $EffortEstimate;

	if (defined $Engineer) {
		if (defined $Engineer->{DSID}) {
			$Settings{dri} = $Engineer->{DSID};
		} else {
			die "Missing DSID for $Responsible in config file";
		}
		if ($OriginalSchedule || (GetRadarField($ProblemId, "state") eq "Analyze")) {
			AddWorkDays($Engineer->{Date}, $Settings{$EffortEstimateField} / $Engineer->{Loading});
			$Settings{$TargetCompletionField} = DateTime::Format::Strptime::strftime("%F", $Engineer->{Date});
		} else {
			my $CompletionDate = GetRadarDateField($ProblemId, "targetCompletionCurrent");
			if (!defined $CompletionDate) {
				$CompletionDate = GetRadarDateField($ProblemId, "resolvedAt");
			}
			$Settings{$TargetCompletionField} = DateTime::Format::Strptime::strftime("%F", $CompletionDate);
			# Task complete, so do nothing
		}
		$DriList{$Responsible} = 1;
	}

	$Settings{priority} = GetRadarField($ProblemId, "priority");
	if ($PriorityFromFile && (defined $ProblemListString)) {
		my $Priority = ParseProblemListString($ProblemId, "priority");
		if ((1 <= $Priority) && ($Priority <= 6)) {
			$Settings{priority} = $Priority;
		} else {
			die "Bad priority P$Priority for " . GetShortRadarUrl($ProblemId);
		}
	}

	foreach my $Field (keys %Settings) {
		my $RemoteValue = GetNormalizedRadarField($ProblemId, $Field);
		if ($RemoteValue ne $Settings{$Field}) {
			$ThisChanged = 1;
		}
	}
	$Changed = $Changed || $ThisChanged;

	printf("%4d%1s  %-25s  %7d  %-10s%s  %3s  %s\n",
		$Settings{taskOrder},
		$ThisChanged ? "*" : "",
		$Responsible,
		$Settings{$EffortEstimateField},
		($Settings{$TargetCompletionField} or "TBD"),
		($OriginalSchedule || (GetRadarField($ProblemId, "state") eq "Analyze")) ? " " : "#",
		"P" . $Settings{priority},
		GetRadarUrl($ProblemId));

	if ($ThisChanged && ($WriteSchedule || $WriteEffort || $WritePriority || $WriteDri)) {
		my @Fields;
		push(@Fields, "taskOrder", $TargetCompletionField) if ($WriteSchedule);
		push(@Fields, $EffortEstimateField) if ($WriteEffort);
		push(@Fields, "priority") if ($WritePriority);
		push(@Fields, "dri") if ($WriteDri);
		my %SettingsSubset = map { $_ => $Settings{$_} } @Fields;
		ModifyRadarFields($ProblemId, \%SettingsSubset);
	}
}

print("\nLegend: * Modified/Different");
print(" # Completed") unless $OriginalSchedule;
print("\n");

print("\nDRI completion dates (by ascending date)\n\n");

printf("%5s  %-25s  %7s  %-10s\n", "", "DRI", "Loading", "Date");
foreach my $Responsible (sort({ $EngineerData{$a}->{Date} <=> $EngineerData{$b}->{Date} } keys %DriList)) {
	printf("%5s  %-25s  %6g%%  %10s\n",
		"",
		$Responsible,
		$EngineerData{$Responsible}->{Loading} * 100,
		DateTime::Format::Strptime::strftime("%F", $EngineerData{$Responsible}->{Date}));
}

print("\nBlocking radars (by ascending task order)\n\n");

FetchRadarFields(\@ProblemIdList);
for (my $Index = 0; $Index < @ProblemIdList; $Index++) {
	my $ProblemId = $ProblemIdList[$Index];
	my @BlockingProblemIds = GetRelatedProblems($ProblemId, "blocked-by");
	next if (@BlockingProblemIds == 0);

	printf("%4d %s\n", $Index + 1, GetRadarUrl($ProblemId));
	foreach $ProblemId (sort @BlockingProblemIds) {
		my $Mark = "";
		if (GetRadarField($ProblemId, "state") eq "Analyze") {
			if ($TlfProblemComponent && (GetRadarComponentField($ProblemId) ne $TlfProblemComponent)) {
				$Mark = "\033[1mExtl\033[0m "
			} else {
				$Mark = "\033[1mOpen\033[0m "
			}
		} else {
				$Mark = "Done "
		}
		printf("\t%s%s\n", $Mark, GetRadarUrl($ProblemId));
	}
}

print("\nDone\n");
