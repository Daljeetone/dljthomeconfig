#!/usr/bin/perl

use strict;
use JSON;
use RadarWebServices;
use Getopt::Long qw(GetOptions);

binmode STDOUT, ":utf8";

my $MyComponentName = "Purple FW Diags";
my $MyComponentVersion = "2.0";
my $MyRelation = "parent-of";
my $IncludeSubcomponents = 0;
my $IncludeExternals = 1;
my @ProblemIdList;
my %ProblemTree;
my %ProblemNodeCache;
my %ExternalProblems;

GetOptions(
	"parent" => sub { $MyRelation = "parent-of" },
	"blocked" => sub { $MyRelation = "blocked-by" },
	"component=s" => \$MyComponentName,
	"version=s" => \$MyComponentVersion,
	"subs!" => \$IncludeSubcomponents,
	"externals!" => \$IncludeExternals,
) || die;

printf("Fetching radars from $MyComponentName | $MyComponentVersion (%s subcomponents)\n", $IncludeSubcomponents ? "including" : "excluding");
@ProblemIdList = FindProblemsByComponent($MyComponentName, $MyComponentVersion, $IncludeSubcomponents, "Analyze");
FetchRadarFields(\@ProblemIdList);
print("\n");

print("Showing ${MyRelation} relations\n\n");

foreach my $ThisProblemId (@ProblemIdList) {
	$ProblemTree{$ThisProblemId} = {};
	$ProblemNodeCache{$ThisProblemId} = $ProblemTree{$ThisProblemId};
}

foreach my $ThisProblemId (@ProblemIdList) {
	my @SubtaskIdList = GetRelatedProblems($ThisProblemId, $MyRelation);
	foreach my $ThisSubtaskId (@SubtaskIdList) {
		if (! defined $ProblemNodeCache{$ThisSubtaskId}) {
			if ($IncludeExternals) {
				if (GetRadarField($ThisSubtaskId, "state") eq "Analyze") {
					$ProblemNodeCache{$ThisSubtaskId} = {};
					$ExternalProblems{$ThisSubtaskId} = 1;
				}
			} else {
				next;
			}
		}
		$ProblemNodeCache{$ThisProblemId}->{$ThisSubtaskId} = $ProblemNodeCache{$ThisSubtaskId};
		delete $ProblemTree{$ThisSubtaskId};
	}
}

sub PrintSubtasks
{
	my ($Preamble, $SubtaskIdList) = @_;
	foreach my $ThisSubtaskId (@$SubtaskIdList) {
		print($Preamble);
		print("\x1B[1mEXT\x1B[0m ") if ($ExternalProblems{$ThisSubtaskId});
		print(GetRadarUrl($ThisSubtaskId), "\n");
		if (%{$ProblemNodeCache{$ThisSubtaskId}}) {
			PrintSubtasks(
				"$Preamble\t",
				[ sort(grep { GetRadarField($_, "state") eq "Analyze" } keys(%{$ProblemNodeCache{$ThisSubtaskId}})) ]
			);
		}
	}
}

PrintSubtasks("", [ sort(keys(%ProblemTree)) ]);

