# Start of module
package RadarWebServices;

use strict;
use Exporter;

our $VERSION     = 1.00;
our @ISA         = qw(Exporter);
our @EXPORT      = qw(
	SetAdditonalRadarFields
	FetchRadarFields
	GetRelatedProblems
	GetAndPrefetchRelatedProblems
	GetShortRadarUrl
	GetRadarUrl
	GetRadarField
	GetNormalizedRadarField
	GetRadarDateField
	GetRadarPersonField
	GetRadarComponentField
	FindProblems
	FindProblemsByKeyword
	FindProblemsByComponent
	ModifyRadarFields
);
our @EXPORT_OK   = qw();
our %EXPORT_TAGS = ();

use Data::Dumper;
use JSON;
use DateTime;
use DateTime::Format::Strptime;
use Clone;

sub DEBUG { return; print "\033[1m" . join("", @_) . "\033[0m"; }
sub DEBUG_OUT { return; print "\033[0;31m" . join("", @_) . "\033[0m"; }
sub DEBUG_IN { return; print "\033[0;32m" . join("", @_) . "\033[0m"; }

sub ExecuteCommand
{
	my ($Command) = @_;
	DEBUG_OUT($Command . "\n");
	my $Response = qx/$Command/;
	DEBUG_IN($Response . "\n");
	die("Command failed!\n" . $Command . "\n" . $Response . "\n") if (($? >> 8) != 0);
	return $Response;
}

sub ExecuteRadarCommand
{
	my ($Command) = @_;
	my $Response = ExecuteCommand($Command);
	die "Failed to contact server\n" unless $Response;
	my $DecodedResponse = decode_json($Response);
	if (ref($DecodedResponse) eq "HASH") {
		die "Command: $Command\nRequest failed: $Response\n" if (defined $DecodedResponse->{status});
		$DecodedResponse = [ $DecodedResponse ];
	}
	return $DecodedResponse;
}

sub ConvertArrayToSet
{
	my %Set;
	foreach (@_) {
		++$Set{$_};
	}
	return %Set;
}

my $Curl = '/usr/bin/curl';

my $RadarHost = "radar-webservices.apple.com";

my @DefaultRadarProblemFields = qw(
	assignee assigneeLastModifiedAt
	counts classification component configurationSummary createdAt
	duplicateOfProblemID
	fingerprint fixOrder
	hasReleaseNotes hasSourceChanges hasWorkaround
	id isExternallyViewable isReadByAssignee
	lastModifiedAt
	milestone
	originator
	priority
	reproducible resolution
	state substate
	title
	);
my @DefaultRadarFindFields = qw(
	assignee assigneeLastModifiedAt
	counts classification component createdAt
	duplicateOfProblemID
	fingerprint fixOrder
	id isReadByAssignee
	lastModifiedAt
	milestone
	originator
	priority
	reproducible resolution
	state substate
	title
	);
my @CommonRadarProblemFields = qw(
	relatedProblems
	effortOriginalTotalEstimate effortCurrentTotalEstimate
	isAutoCalculated
	taskOrder
	targetCompletionOriginal targetCompletionCurrent targetStartDate
	dateNeededOriginal dateNeededCurrent
	dri
	resolvedAt closedAt
	);
# This is to be overridden by the user
my @AdditionalRadarFields = qw(
	);

my %RadarFieldCache;
my $CacheFileName = ".RadarWebServicesCache";

sub WriteCacheFile
{
	if (%RadarFieldCache) {
		printf("Writing %s\n", $CacheFileName);
		my $FileHandle;
		open($FileHandle, ">", $CacheFileName) or die("Failed to create cache file\n");
		print $FileHandle encode_json(\%RadarFieldCache);
		close $FileHandle;
	}
}

sub ReadCacheFile
{
	my $FileHandle;
	my $EncodedCache;

	if (keys(%RadarFieldCache) > 0) {
		return;
	}

	printf("Reading %s\n", $CacheFileName);
	open($FileHandle, "<", $CacheFileName) or return;

	local $/ = undef;
	$EncodedCache = <$FileHandle>;
	close $FileHandle;

	%RadarFieldCache = %{decode_json($EncodedCache)};
}

sub SetAdditonalRadarFields
{
	@AdditionalRadarFields = @_;
}

sub CacheRadarFields
{
	my ($ProblemId, $DecodedResponse) = @_;

	$ProblemId = int($ProblemId);
	if (!defined $RadarFieldCache{$ProblemId}) {
		$RadarFieldCache{$ProblemId} = {};
	}
	my $Key;
	foreach $Key (keys %$DecodedResponse) {
		$RadarFieldCache{$ProblemId}->{$Key} = $DecodedResponse->{$Key};
	}
	if (defined $DecodedResponse->{relatedProblems}) {
		my $Relative;
		foreach $Relative (@{$DecodedResponse->{relatedProblems}}) {
			my $RelatedProblem = $Relative->{problem};
			my $RelatedProblemId = $RelatedProblem->{id};
			foreach $Key (keys %$RelatedProblem) {
				$RadarFieldCache{$RelatedProblemId}->{$Key} = $RelatedProblem->{$Key};
			}
		}
	}
}

sub FetchRadarFields
{
	my ($Scope, @AllFields) = @_;
	my %ProblemIdSet;
	my @AllProblemIds;
	my $ProblemId;
	my $i;

	if (scalar @AllFields == 0)
	{
		# Default problem fields
		#
		# NOTE: Radar Web Services returns these fields if none are given, but
		#       omits them as soon as any specific fields are requested, so we
		#       have to manually include them here
		push @AllFields, @DefaultRadarProblemFields;
		# Additional problem fields that we will be using
		push @AllFields, @CommonRadarProblemFields;
		push @AllFields, @AdditionalRadarFields;
	}

	# Find the set of problem IDs that have uncached fields
	if (ref $Scope) {
		%ProblemIdSet = ConvertArrayToSet(@$Scope);
	} else {
		$ProblemIdSet{$Scope} = 1;
	}
	foreach $ProblemId (keys %ProblemIdSet) {
		if (defined $RadarFieldCache{$ProblemId}) {
			my $Field;
			my $Missing = undef;
			foreach $Field (@AllFields) {
				if (!exists $RadarFieldCache{$ProblemId}->{$Field}) {
					$Missing = 1;
					last;
				}
			}
			if (!$Missing) {
				delete $ProblemIdSet{$ProblemId};
			}
		}
	}
	if (scalar keys %ProblemIdSet == 0) {
		if (ref $Scope) {
			return;
		} else {
			return %{$RadarFieldCache{$Scope}};
		}
	}
	@AllProblemIds = sort(keys %ProblemIdSet);

	# Take this opportunity to fetch additional, common fields
	push @AllFields, @DefaultRadarProblemFields, @CommonRadarProblemFields, @AdditionalRadarFields;

	# Use SPNego (requires an active AppleConnect session) to contact the Radar servers
	#
	# curl -H "Accept: application/json" -H "Content-Type: application/json" -H "X-Fields-Requested: " --negotiate -s -u : https://radar-webservices.apple.com/problems/14577575
	my $Command = $Curl .
		' -H "Accept: application/json"' .
		' -H "Content-Type: application/json"' .
		' -H "X-Fields-Requested: ' .  join(",", @AllFields) . '"' .
		' --negotiate -s -u :' .
		' https://' . $RadarHost . '/problems/' . join(",", @AllProblemIds);
	my $DecodedResponse = ExecuteRadarCommand($Command);
	#print Dumper($DecodedResponse);

	# Cache all the fields returned
	# Also create entries for the related problems buried in the JSON tree
	for ($i = 0; $i < scalar @AllProblemIds; ++$i) {
		CacheRadarFields($AllProblemIds[$i], $DecodedResponse->[$i]);
	}

	# For now, we consider the request of multiple problem IDs to be a prefetch
	# operation and don't return anything in that situation
	if (ref $Scope) {
		return;
	} else {
		return %{$RadarFieldCache{$Scope}};
	}
}

sub GetRelatedProblems
{
	my ($ProblemId, $RelationType) = @_;
	my %Response = FetchRadarFields($ProblemId, "relatedProblems");
	my @Relevant = grep { $_->{relationType} eq $RelationType } @{$Response{relatedProblems}};
	return map { $_->{problem}->{id} } @Relevant;
}

sub GetShortRadarUrl
{
	my ($ProblemId) = @_;
	# e.g. <rdar://problem/14647599>
	return "<rdar://problem/$ProblemId>";
}

sub GetRadarUrl
{
	my ($ProblemId) = @_;
	my %Response = FetchRadarFields($ProblemId, "title");
	my $Title = $Response{title};
	# e.g. <rdar://problem/14647599> Method for passing top-level arguments to sequences (via command line, etc)
	return "<rdar://problem/$ProblemId> $Title";
}

sub GetRadarField
{
	my ($ProblemId, $Field) = @_;
	my %Response = FetchRadarFields($ProblemId, $Field);
	return $Response{$Field};
}

sub GetNormalizedRadarField
{
	my $FieldValue = GetRadarField(@_);
	if (ref($FieldValue) eq "HASH") {
		# This should take care of person fields like:
		# assignee, dri, originator
		if (defined $FieldValue->{dsid}) {
			$FieldValue = $FieldValue->{dsid};
		}
	} else {
		# Handle other vector types?
	}
	return $FieldValue;
}

sub GetRadarDateField 
{
	my ($ProblemId, $Field) = @_;
	my %Response = FetchRadarFields($ProblemId, $Field);
	my $DateString = $Response{$Field};
	if (length $DateString) {
		my $Complex = DateTime::Format::Strptime->new(
			pattern => "%Y-%m-%dT%H:%M:%S%z",
			on_error => "undef",
		);
		my $Simple = DateTime::Format::Strptime->new(
			pattern => "%Y-%m-%d",
			on_error => "undef",
		);
		return $Complex->parse_datetime($DateString) || return $Simple->parse_datetime($DateString);
	} else {
		return;
	}
}

sub GetRadarPersonField 
{
	my ($ProblemId, $Field) = @_;
	my %Response = FetchRadarFields($ProblemId, $Field);
	my $Person = $Response{$Field}->{firstName};
	if (length $Response{$Field}->{lastName}) {
		if (length $Person) {
			$Person .= " ";
		}
		$Person .= $Response{$Field}->{lastName};
	}
	return $Person;
}

sub GetRadarComponentField
{
	my ($ProblemId) = @_;
	my %Response = FetchRadarFields($ProblemId, "component");
	my $ComponentName = $Response{component}->{name};
	my $ComponentVersion = $Response{component}->{version};
	if (length $ComponentVersion) {
		return sprintf("%s | %s", $ComponentName, $ComponentVersion);
	} else {
		return $ComponentName;
	}
}

sub FindProblems
{
	my ($Criteria) = @_;
	my $EncodedCriteria = encode_json($Criteria);
	my $Command = $Curl .
		' -m 600' .
		' -X POST' .
		" -d '" . $EncodedCriteria . "'" .
		' -H "Accept: application/json"' .
		' -H "Content-Type: application/json"' .
		' -H "X-Fields-Requested: ' .  join(",", @DefaultRadarFindFields) . '"' .
		' --negotiate -s -u :' .
		' https://' . $RadarHost . '/problems/find';
	my $DecodedResponse = ExecuteRadarCommand($Command);
	map { CacheRadarFields($_->{id}, $_) } @$DecodedResponse;
	return map { $_->{id} } @$DecodedResponse;
}

sub FindProblemsByKeyword
{
	my $Key = join(" ", sort(@_));
	if (!defined $RadarFieldCache{Keywords}) {
		$RadarFieldCache{Keywords} = {};
	}
	if (!defined $RadarFieldCache{Keywords}->{$Key}) {
		my @Response = FindProblems({ keyword => \@_ });
		$RadarFieldCache{Keywords}->{$Key} = \@Response;
	}
	return @{$RadarFieldCache{Keywords}->{$Key}};
}

sub FindProblemsByComponent
{
	my ($Name, $Version, $Include, $State) = @_;
	my %Criteria = (
		component => {
			name => $Name,
			version => $Version,
		},
	);
	if ($Include) {
		$Criteria{component}->{includeSubcomponents} = JSON::true;
	}
	if ($State) {
		$Criteria{state} = $State;
	}
	return FindProblems(\%Criteria);
}

sub HashRenameKey
{
	my ($HashRef, $Old, $New) = @_;
	if (defined $HashRef->{$Old}) {
		$HashRef->{$New} = delete $HashRef->{$Old};
	}
}

sub ModifyRadarFields
{
	my ($Scope, $Settings) = @_;
	my (%ProblemIdSet, $PostSettings);
	my ($Field, $ProblemId);

	if (ref $Scope) {
		%ProblemIdSet = ConvertArrayToSet(@$Scope);
	} else {
		$ProblemIdSet{$Scope} = 1;
	}

	foreach $ProblemId (keys %ProblemIdSet) {
		if (exists $RadarFieldCache{$ProblemId}) {
			foreach $Field (keys %$Settings) {
				#printf("Deleting %s from %s\n", $Field, $ProblemId);
				delete $RadarFieldCache{$ProblemId}->{$Field};
			}
		}
	}

	$PostSettings = Clone::clone($Settings);
	$PostSettings->{problemIDs} = [ keys %ProblemIdSet ];
	HashRenameKey($PostSettings, "effortOriginalTotalEstimate", "effortOriginalTotal");
	HashRenameKey($PostSettings, "effortCurrentTotalEstimate", "effortCurrentTotal");

	my $Command = $Curl .
		' -X POST' .
		" -d '" . encode_json($PostSettings) . "'" .
		' -H "Accept: application/json"' .
		' -H "Content-Type: application/json"' .
		' --negotiate -s -u :' .
		' https://' . $RadarHost . '/problems/modify';
	ExecuteRadarCommand($Command);
}

INIT
{
	ReadCacheFile();
	print("\n");
}

END
{
	print("\n");
	WriteCacheFile();
}

# End of module
1;
