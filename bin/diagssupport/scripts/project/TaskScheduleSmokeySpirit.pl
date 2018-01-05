%EngineerData = (
	"Chanh-Duy Tran" => {
		Date => DateTime->new(month => 9, day => (25 - 13), year => 2013),
		Loading => 0.75
	},
	"Mike Ralph" => {
		Date => DateTime->new(month => 9, day => 26, year => 2013),
		Loading => 0.5
	},
	"Joon-Sup Han" => {
		Date => DateTime->new(month => 11, day => 11, year => 2013),
		Loading => 0.5
	},
);

# <rdar://problem/14659901> ☂ Smokey "Spirit" TLF
$TlfProblemId = 14659901;

$ProblemListString = <<HERE;
<rdar://problem/14774104> Shared libraries need a versioning scheme
<rdar://problem/13210875> Shared libraries need a way to have platform-specific definitions
<!rdar://problem/12441712> Support for nested PLISTs in Smokey/Cinnamon
<rdar://problem/12560005> Define BehaviorOnFail per test item rather than only at the root of sequence
<rdar://problem/12203816> Method for passing arguments to scripts (via command line, etc)
<rdar://problem/14647599> Method for passing top-level arguments to sequences (via command line, etc)
<!rdar://problem/12802538> Fix Data Reporting for Wildfire (Secondary results output)
<rdar://problem/15047649> Smokey failures should return error at test layer
<!rdar://problem/11070068> PDCAWriterLib support for appending to a plist file
<!rdar://problem/14524539> [PDCAWriterLib] Supporting binary plist output for output speed
<rdar://problem/14307143> Release Smokey Simulator as part of iOSNonUI SDK
<rdar://problem/13431253> Smokey should publish a EFI_SIMPLE_TEXT_OUT_PROTOCOL to gather console ouput rather than reading the ConsoleMux buffer
<rdar://problem/12557492> Factor out DiagShell line editing functionality (aka readline library)
<rdar://problem/14664689> Support executing commands in smokeyshell from DiagShell command line
<!rdar://problem/11771605> Smokey should use SetFontFile() to set a consistent font file
<!rdar://problem/12954021> Support logging verbosity in Smokey
<!rdar://problem/14255445> Support API for printing custom text on screen during Smokey
<rdar://problem/12625748> Need a way for Smokey to run when Smokey.log has contents
<rdar://problem/14464603> ☂ Improve factory collection and reporting of failures in Smokey sequences
<rdar://problem/14504412> Earthbound's Smokey plug-in should identify specific classes of failures
<rdar://problem/15385142> x Smokey ART plugin
<rdar://problem/14719547> Smokey Error Reporting: Report something other than "Iteration 1" for command failures
<!rdar://problem/13060012> Fatal events do not stop Smokey
<rdar://problem/14730904> Smokey gets angry when boot-args is not set
<!rdar://problem/13021510> control diags output muxing
<!rdar://problem/12054949> smokey --summary doesn't hide nodes whose children all have 0 iterations
<!rdar://problem/14469540> ☂ Enable CurrentTest library to use Smokey as the command sequencer (dynamic sequences)
<!rdar://problem/14647716> Make --summary and --sequence work for dynamic sequences
<!rdar://problem/11103542> [Smokey] Feature to disable background tasks during "critical" tests
<!rdar://problem/11613179> Feature to call user functions periodically in between sequence actions
<!rdar://problem/11423711> Need mechanism to resurrect user data when continuing sequence
<!rdar://problem/12213316> When authenticating a sequence, make sure to include command line overrides
<!rdar://problem/12322009> Authenticate sequence before running it
<!rdar://problem/14562623> Authenticate files opened by sequences
<rdar://problem/14535242> Lift remaining smokeyshell restrictions on PROD-fused SoC
<rdar://problem/14647870> [☂ Smokey "Spirit"] Outstanding undocumented features
HERE
