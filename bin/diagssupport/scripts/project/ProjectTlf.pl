#!/usr/bin/perl

use strict;
use feature "state";
use Data::Dumper;
use POSIX;
use JSON;
use DateTime;
use DateTime::Format::Strptime;
use RadarWebServices;

binmode STDOUT, ":utf8";

my $ConfigFile = "ProjectTlfConfig.pl";
my $MilestoneProblemId;
my $TlfProblemId;
my $TlfProblemKeyword;

foreach my $Arg (@ARGV) {
	$ConfigFile = $Arg;
}

die "Missing config file\n" unless (-f $ConfigFile);
eval `cat $ConfigFile`;

sub FormatTaskDate
{
	my ($ProblemId, $Indentation) = @_;
	$Indentation = "" unless (defined $Indentation);
	my $Width = 130 - length $Indentation;
	return sprintf("%s%*.*s %s",
		$Indentation, -$Width, $Width,
		GetRadarUrl($ProblemId),
		DateTime::Format::Strptime::strftime("%F", GetRadarDateField($ProblemId, "lastModifiedAt")));
}

sub FormatTaskEffort
{
	my ($ProblemId, $Indentation) = @_;
	$Indentation = "" unless (defined $Indentation);
	my $Width = 130 - length $Indentation;
	return sprintf("%s%*.*s %d",
		$Indentation, -$Width, $Width,
		GetRadarUrl($ProblemId),
		GetRadarField($ProblemId, "effortOriginalTotalEstimate"));
}

sub FormatGroupEffort
{
	my ($ProblemId, $Indentation) = @_;
	return FormatTaskEffort($ProblemId, $Indentation) .
		sprintf(" (%ssummed)", , GetRadarField($ProblemId, "isAutoCalculated") ? "" : "not ");
}

sub FormatKeynoteBringup
{
	my ($GroupId, $ProblemId) = @_;
	my $GroupTitle = "";
	my $Assignee = "";
	state $LastKeynoteGroupId = 0;

	$GroupId = $ProblemId if (!defined $GroupId);

	if ($LastKeynoteGroupId != $GroupId) {
		$GroupTitle = GetRadarField($GroupId, "title");
		$GroupTitle =~ s/^.*\[.*\]\s*//;
		$LastKeynoteGroupId = $GroupId;
	}

	$Assignee = GetRadarPersonField($ProblemId, "dri");
	$Assignee = GetRadarPersonField($ProblemId, "assignee") if (length $Assignee == 0);

	my $Eta = GetRadarDateField($ProblemId, "targetCompletionCurrent") or GetRadarDateField($ProblemId, "targetCompletionOriginal");

	return sprintf("%s\t%d\t%s\t%s\t%d\t%s\t%s",
		$GroupTitle,
		$ProblemId,
		($GroupId == $ProblemId) ? "" : GetRadarField($ProblemId, "title"),
		$Assignee,
		(GetRadarField($ProblemId, "effortCurrentTotalEstimate") or GetRadarField($ProblemId, "effortOriginalTotalEstimate")),
		($Eta ? DateTime::Format::Strptime::strftime("%F", $Eta) : "TBD"),
		(GetRadarField($ProblemId, "state") eq "Analyze") ? "" : DateTime::Format::Strptime::strftime("%F", GetRadarDateField($ProblemId, "resolvedAt")),
	);
}

sub FormatRisk
{
	my ($ProblemId, $Numeric) = @_;
	if (GetRadarField($ProblemId, "state") ne "Analyze") {
		return $Numeric ? 4 : "Done";
	}
	my $Priority = GetRadarField($ProblemId, "priority");
	if ($Priority == 1) {
		return $Numeric ? 1 : "High";
	} elsif ($Priority == 2) {
		return $Numeric ? 2 : "Medium";
	} else {
		return $Numeric ? 3 : "Low";
	}
}

my $LastKeynoteLine = 0;
sub FormatKeynoteDashboard
{
	my ($ProblemId) = @_;
	my $ETA = GetRadarField($ProblemId, "targetCompletionOriginal");

	if (GetRadarField($ProblemId, "state") ne "Analyze") {
		$ETA = "Done";
	}

	return sprintf("%d\t%s\t%d\t%s\t%s\t%s",
		++$LastKeynoteLine,
		GetRadarField($ProblemId, "title"),
		$ProblemId,
		FormatRisk($ProblemId),
		GetRadarPersonField($ProblemId, "assignee"),
		$ETA,
		);
}

#map { print($_ . "\n") } FindProblemsByComponent("Purple FW Diags", "Smokey");
#exit(0);

my $LastWeek = DateTime->now()->truncate(to => "week")->subtract(weeks => 1);

print "Getting open task groups\n";
my @AllMilestoneGroupProblemIds = sort(GetRelatedProblems($MilestoneProblemId, "parent-of"));
FetchRadarFields(\@AllMilestoneGroupProblemIds);

print "Getting TLF radars\n";
my @AllTlfSubtaskProblemIds =
	sort($TlfProblemId ?
		GetRelatedProblems($TlfProblemId, "parent-of") :
		FindProblemsByKeyword($TlfProblemKeyword));
FetchRadarFields(\@AllTlfSubtaskProblemIds);

my ($GroupProblemId, @RelevantProblemIds, $SubtaskProblemId);

print "Getting all tasks\n";
undef @RelevantProblemIds;
foreach $GroupProblemId (@AllMilestoneGroupProblemIds) {
	push @RelevantProblemIds, sort(GetRelatedProblems($GroupProblemId, "parent-of"));
}
FetchRadarFields(\@RelevantProblemIds);

print "\n";
print "------------------------------------------------------------------------------\n";
print "TLF tree\n";
print "------------------------------------------------------------------------------\n";
print "\n";

if ($TlfProblemId) {
	print FormatGroupEffort($TlfProblemId) . "\n";
} else {
	print "Keyword: " . $TlfProblemKeyword. "\n";
}

print "\n";

foreach $GroupProblemId (@AllMilestoneGroupProblemIds) {
	next if (GetRadarField($GroupProblemId, "effortOriginalTotalEstimate") == 0);

	print FormatGroupEffort($GroupProblemId) . "\n";

	@RelevantProblemIds = sort(GetRelatedProblems($GroupProblemId, "parent-of"));
	if (GetRadarField($GroupProblemId, "isAutoCalculated")) {
		@RelevantProblemIds = grep {$_ ~~ @AllTlfSubtaskProblemIds} @RelevantProblemIds;
	}
	FetchRadarFields(\@RelevantProblemIds);

	foreach $SubtaskProblemId (@RelevantProblemIds) {
		print FormatTaskEffort($SubtaskProblemId, "    ") . "\n";
	}
}

print "\n";
print "------------------------------------------------------------------------------\n";
print "Keynote bring-up slide\n";
print "------------------------------------------------------------------------------\n";
print "\n";

my %ProblemParent;

FetchRadarFields(\@AllMilestoneGroupProblemIds);
foreach $GroupProblemId (@AllMilestoneGroupProblemIds) {
	@RelevantProblemIds = sort(GetRelatedProblems($GroupProblemId, "parent-of"));
	if (GetRadarField($GroupProblemId, "isAutoCalculated")) {
		@RelevantProblemIds = grep {$_ ~~ @AllTlfSubtaskProblemIds} @RelevantProblemIds;
	}

	FetchRadarFields(\@RelevantProblemIds);
	foreach $SubtaskProblemId (@RelevantProblemIds) {
		$ProblemParent{$SubtaskProblemId} = $GroupProblemId;
	}
}

my $LineNumber = 0;
FetchRadarFields(\@AllTlfSubtaskProblemIds);
foreach $SubtaskProblemId (sort { GetRadarField($a, "taskOrder") <=> GetRadarField($b, "taskOrder") } @AllTlfSubtaskProblemIds) {
	#print sprintf("%d\t", ++$LineNumber);
	print FormatKeynoteBringup($ProblemParent{$SubtaskProblemId}, $SubtaskProblemId) . "\n";
}

print "\n";
print "------------------------------------------------------------------------------\n";
print "Modified in the previous week\n";
print "------------------------------------------------------------------------------\n";
print "\n";

my @RecentProblemIds;

foreach $GroupProblemId (@AllMilestoneGroupProblemIds) {
	print FormatGroupEffort($GroupProblemId) . "\n";

	@RelevantProblemIds = sort(GetRelatedProblems($GroupProblemId, "parent-of"));
	@RelevantProblemIds = grep { DateTime->compare($LastWeek, GetRadarDateField($_, "lastModifiedAt")) <= 0 } @RelevantProblemIds;

	push @RecentProblemIds, @RelevantProblemIds;

	FetchRadarFields(\@RelevantProblemIds);
	foreach $SubtaskProblemId (@RelevantProblemIds) {
		print FormatTaskDate($SubtaskProblemId, "    ") . "\n";
	}
}

print "\n";
print "------------------------------------------------------------------------------\n";
print "Keynote dashboard slide\n";
print "------------------------------------------------------------------------------\n";
print "\n";

foreach $SubtaskProblemId (sort { FormatRisk($a, 1) <=> FormatRisk($b, 1) } @RecentProblemIds) {
	print FormatKeynoteDashboard($SubtaskProblemId) . "\n";
}
