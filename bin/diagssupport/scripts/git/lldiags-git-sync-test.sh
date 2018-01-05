#!/bin/bash

set -o pipefail
set -o errexit

# How to read repository diagrams:
# - Clones are arranged vertically and grow down
# - Orphan repos (i.e. no remote, or not cloned) are shown with dotted lines
# - Commits are arranged horizontally and grow to the right
# - First branch commits sprout diagonally down and to the right

# Tips for comparing output of these tests vs. a previous version of the sync script:
:<<'END'
./lldiags-git-sync-test.sh | tee output
perl -p -i output \
-e 's/\b[0-9a-f]{7}\b/xxxxxxx/;' \
-e 's/\b[0-9a-f]{40}\b/xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx/;' \
-e 's!^(Removing /tmp/sync-[-\w]*-)[a-zA-Z0-9]{6}$!\1xxxxxx!;' \
-e 's;'"$(pwd)"';xxx;g'
END

# Export must be a separate step if a subshell is in the expansion of a variable value
SYNC="$(cd $(dirname $0) && pwd)/lldiags-git-sync.sh $*"
export SYNC
ROOT="$(pwd)"
export ROOT
export FLLDU="git@gitlab.sd.apple.com:blackops/factorylldiagsutils.git"
CMKIT="$(ls -1d /tmp/CMKit_*diag_master-*/Staging | head -1)"
export CMKIT
export FLLSP="git@gitlab.sd.apple.com:blackops/factoryllscriptsplatforms.git"
export FLLSC="git@gitlab.sd.apple.com:blackops/factoryllscriptscommon.git"

function announce
{
	echo -n $'\e[1m'
	echo "**************************************************************************************************"
	echo "$@"
	echo "**************************************************************************************************"
	echo $'\e[0m'
}

function do_sync
{
	local DIR="$1"
	shift
	echo "========================================================================================"
	echo
	echo $'\e[1m'"$SYNC $*"$'\e[0m'
	echo
	(cd "$DIR" && $SYNC "$@")
	echo
	echo "========================================================================================"
	echo
}

function orphan_clone
{
	local SRC="$1"
	local DST="$2"
	shift 2
	git clone "$@" "$SRC" "$DST"
	git -C "$DST" remote remove origin
}

function create_reset
{
	local DIR="$1"
	local CMD="$2"
	if [ "$CMD" = "detach" ]; then
		if ! git -C "$DIR" rev-parse x 1>/dev/null 2>&1; then
			git -C "$DIR" tag x
		fi
		git -C "$DIR" tag -f -a -m detach x x
		git -C "$DIR" checkout -q --detach x
	else
		git -C "$DIR" tag x
	fi
}

function show_state
{
	local DIR="$1"
	local COMMAND="$2"
	echo "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -"
	echo
	echo $'\e[1m'"$DIR"$'\e[0m'
	echo
	echo "Remotes"
	if [ -n "$(git -C "$DIR" remote)" ]; then
		git -C "$DIR" remote -v | sed -e "s;$(pwd)/;;"
	else
		echo "(No remotes)"
	fi
	echo
	echo "Current branch"
	(git -C "$DIR" branch | grep "^\*") || echo "(No branch)"
	echo
	echo "Status:"
	git -C "$DIR" status
	echo
	for i in $(git -C "$DIR" for-each-ref --format='%(refname:short)' refs/heads/); do
		echo "History for branch $i:"
		git -C "$DIR" log $i --decorate --oneline
		echo
	done
	echo "Tags:"
	for i in $(git -C "$DIR" tag); do
		if [ "$i" != "x" ]; then
			echo -n "$(git -C "$DIR" rev-parse --short $i)"
			echo $'\t'"$i"
		fi
	done
	echo
	echo "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -"
	echo
	# NOTE: Ignore error messages from Git if tag "x" doesn't exist; branch name will just be blank
	local X_BRANCH="$(git -C "$DIR" branch --contains x 2>/dev/null | fgrep -v -e "(detached from" -e "(HEAD detached" | cut -c3-)"
	case "$COMMAND" in
		reset)
			echo "Resetting..."
			git -C "$DIR" reset --hard || true
			git -C "$DIR" clean -df || true
			git -C "$DIR" checkout "$X_BRANCH"
			git -C "$DIR" reset --hard x
			git -C "$DIR" clean -df
			for i in $(git -C "$DIR" for-each-ref --format='%(refname:short)' refs/heads/); do
				if [ "$i" != "$X_BRANCH" ]; then
					git -C "$DIR" branch -D "$i"
				fi
			done
			for i in $(git -C "$DIR" tag); do
				if [ "$i" = "x" ]; then
					git -C "$DIR" tag __x x
				else
					git -C "$DIR" tag -d "$i"
				fi
			done
			git -C "$DIR" fetch --tags
			git -C "$DIR" tag -f x __x
			git -C "$DIR" tag -d __x
			echo
			local X_HASH="$(git -C "$DIR" rev-parse x)"
			local X_COMMIT="$(git -C "$DIR" rev-list --max-count=1 x)"
			local X_DETACH="$(git -C "$DIR" tag --list -n1 x | fgrep detach)"
			if [ "$X_HASH" != "$X_COMMIT" -a -n "$X_DETACH" ]; then
				git -C "$DIR" checkout -q --detach x
				echo
			fi
			;;
		checkout)
			git -C "$DIR" checkout "$X_BRANCH"
			echo
			;;
		"")
			true
			;;
		*)
			false
			;;
	esac
}

##############################################################################
# FactoryLLDiagsUtils use case
##############################################################################
#
#                    A     B
# $FLLDU            O-----O    (master)
#                   :
#                   :A
# Mock-FLLDU-Clean  O          (master)
#                   |
#                   |A
# Mock-FLLDU-Remote O          (master)
#                   |
#                   |A
# Mock-FLLDU-Local  O          (master)
#
##############################################################################

function test_flldu
{
	announce "FLLDU: Setting up test repos"
	# Get copy of FLLDU
	orphan_clone "$FLLDU" Mock-FLLDU-Clean --depth 3
	# Prep our copy of FLLDU
	git -C Mock-FLLDU-Clean reset --hard HEAD~1
	create_reset Mock-FLLDU-Clean
	# Clone remote and local repo based on FLLDU
	git clone --branch master Mock-FLLDU-Clean Mock-FLLDU-Remote
	git clone --branch master Mock-FLLDU-Remote Mock-FLLDU-Local
	create_reset Mock-FLLDU-Remote detach
	echo
	show_state Mock-FLLDU-Clean
	show_state Mock-FLLDU-Remote
	show_state Mock-FLLDU-Local

	announce "FLLDU: Basic sync"
	do_sync Mock-FLLDU-Local --config FactoryLLDiagsUtils
	show_state Mock-FLLDU-Local reset

	announce "FLLDU: Basic sync + commit (normal, no-op, force)"
	do_sync Mock-FLLDU-Local --config FactoryLLDiagsUtils --commit
	show_state Mock-FLLDU-Local
	do_sync Mock-FLLDU-Local --config FactoryLLDiagsUtils
	show_state Mock-FLLDU-Local
	do_sync Mock-FLLDU-Local --config FactoryLLDiagsUtils --force
	show_state Mock-FLLDU-Local reset

	announce "FLLDU: Basic sync + commit + push"
	do_sync Mock-FLLDU-Local --config FactoryLLDiagsUtils-Automation --push
	show_state Mock-FLLDU-Remote reset
	show_state Mock-FLLDU-Local reset
}

##############################################################################
# CMKit use case
##############################################################################
#
# $CMKIT                    O                                 (master)
#                           :
#                           :TagOld
# Mock-CMKit-Old            O                                 (master)
#                          /:
#                         / :TagOld       TagNew
# Mock-CMKit-New         /: O------------O                    (master)
#                       | :
#                       |  \ TagOld       TagBranch
# Mock-CMKit-Branch     |   O------------O                    (TestBranch)
#                       |   :
#                       |   :TagOld       TagBranch    TagBranchNew
# Mock-CMKit-BranchNew   \  O------------O------------O       (TestBranch)
#                         \
#                          \ TagOld
# Mock-CMKit-Remote         O                                 (master)
#                           |
#                           |TagOld
# Mock-CMKit-Local          O                                 (master)
#
##############################################################################

function edit_cmkit
{
	local DIR="$1"
	local TXT="$2"
	local MSG="$3"
	local VER="$(sed -E 's/^.*-([0-9a-f]+)[^0-9a-f]+.*$/\1/g' <<< "$CMKIT")"
	perl -pi -e "s;(..)${VER:2};sprintf(\"%02x\",(hex(\$1)+1)%255).\"${VER:2}\";e" "$DIR/version.mk"
	perl -pi -e "s;Built \w+;$TXT;" "$DIR/diagnostics/Platform/Apple/Ipod/Tests/TestVersion/TestVersion.c"
	git -C "$DIR" commit -a -m "$MSG"
}

function test_cmkit
{
	announce "CMKit: Setting up test repos"
	# Set up "old" reference repo
	orphan_clone "$CMKIT" Mock-CMKit-Old
	create_reset Mock-CMKit-Old
	git -C Mock-CMKit-Old tag TagOld
	# Set up "new" reference repo
	orphan_clone Mock-CMKit-Old Mock-CMKit-New
	edit_cmkit Mock-CMKit-New "Built on" "Small change on master"
	git -C Mock-CMKit-New tag TagNew
	# Set up "branch" reference repo
	orphan_clone Mock-CMKit-Old Mock-CMKit-Branch
	git -C Mock-CMKit-Branch branch -m TestBranch
	edit_cmkit Mock-CMKit-Branch "Built by" "Branch"
	git -C Mock-CMKit-Branch tag TagBranch
	# Set up "branch-new" reference repo
	orphan_clone Mock-CMKit-Branch Mock-CMKit-BranchNew
	edit_cmkit Mock-CMKit-BranchNew "Built during" "Small change on branch"
	git -C Mock-CMKit-BranchNew tag TagBranchNew
	# Create remote and local repos based on reference repos
	git clone Mock-CMKit-Old Mock-CMKit-Remote
	git clone Mock-CMKit-Remote Mock-CMKit-Local
	create_reset Mock-CMKit-Remote detach
	# Set up "empty" target repo/root
	mkdir Mock-CMKit-Empty-Remote
	git -C Mock-CMKit-Empty-Remote init
	git -C Mock-CMKit-Empty-Remote checkout -b out-of-the-way
	git clone Mock-CMKit-Empty-Remote Mock-CMKit-Empty
	mkdir Mock-CMKit-Empty-Exact-Remote
	git -C Mock-CMKit-Empty-Exact-Remote init
	git -C Mock-CMKit-Empty-Exact-Remote checkout -b out-of-the-way
	git clone Mock-CMKit-Empty-Exact-Remote Mock-CMKit-Empty-Exact
	echo
	show_state Mock-CMKit-Old
	show_state Mock-CMKit-New
	show_state Mock-CMKit-Branch
	show_state Mock-CMKit-BranchNew
	show_state Mock-CMKit-Remote
	show_state Mock-CMKit-Local
	show_state Mock-CMKit-Empty
	show_state Mock-CMKit-Empty-Exact
	show_state Mock-CMKit-Empty-Remote
	show_state Mock-CMKit-Empty-Exact-Remote

	announce "CMKit: Basic sync (no-op, force)"
	do_sync Mock-CMKit-Local --config CMKit-Automation --repo "$CMKIT"
	show_state Mock-CMKit-Local
	do_sync Mock-CMKit-Local --config CMKit-Automation --repo "$CMKIT" --force
	show_state Mock-CMKit-Local reset

	announce "CMKit: Basic sync"
	do_sync Mock-CMKit-Local --config CMKit --repo "$ROOT/Mock-CMKit-New"
	show_state Mock-CMKit-Local reset

	announce "CMKit: Basic sync + commit"
	do_sync Mock-CMKit-Local --config CMKit --repo "$ROOT/Mock-CMKit-New" --tags --commit
	show_state Mock-CMKit-Local reset

	announce "CMKit: Basic sync + commit + push"
	do_sync Mock-CMKit-Local --config CMKit-Automation --repo "$ROOT/Mock-CMKit-New"
	show_state Mock-CMKit-Remote reset
	show_state Mock-CMKit-Local reset

	announce "CMKit: Basic sync + commit + push to new branch (normal, no-op, force) from master/branch"
	do_sync Mock-CMKit-Local --config CMKit-Automation --repo "$ROOT/Mock-CMKit-Branch"
	show_state Mock-CMKit-Remote
	show_state Mock-CMKit-Local
	do_sync Mock-CMKit-Local --config CMKit-Automation --repo "$ROOT/Mock-CMKit-Branch"
	show_state Mock-CMKit-Remote
	show_state Mock-CMKit-Local
	do_sync Mock-CMKit-Local --config CMKit-Automation --repo "$ROOT/Mock-CMKit-Branch" --force
	show_state Mock-CMKit-Remote
	show_state Mock-CMKit-Local checkout
	do_sync Mock-CMKit-Local --config CMKit-Automation --repo "$ROOT/Mock-CMKit-Branch"
	show_state Mock-CMKit-Remote
	show_state Mock-CMKit-Local checkout
	do_sync Mock-CMKit-Local --config CMKit-Automation --repo "$ROOT/Mock-CMKit-Branch" --force
	show_state Mock-CMKit-Remote reset
	show_state Mock-CMKit-Local reset

	announce "CMKit: Basic sync + commit + push to existing branch (normal, no-op, force) from branch"
	do_sync Mock-CMKit-Local --config CMKit-Automation --repo "$ROOT/Mock-CMKit-Branch"
	show_state Mock-CMKit-Remote
	show_state Mock-CMKit-Local
	do_sync Mock-CMKit-Local --config CMKit-Automation --repo "$ROOT/Mock-CMKit-BranchNew"
	show_state Mock-CMKit-Remote
	show_state Mock-CMKit-Local
	do_sync Mock-CMKit-Local --config CMKit-Automation --repo "$ROOT/Mock-CMKit-BranchNew"
	show_state Mock-CMKit-Remote
	show_state Mock-CMKit-Local
	do_sync Mock-CMKit-Local --config CMKit-Automation --repo "$ROOT/Mock-CMKit-BranchNew" --force
	show_state Mock-CMKit-Remote reset
	show_state Mock-CMKit-Local reset

	announce "CMKit: Basic sync + commit + push to existing branch (normal, no-op, force) from master"
	do_sync Mock-CMKit-Local --config CMKit-Automation --repo "$ROOT/Mock-CMKit-Branch"
	show_state Mock-CMKit-Remote
	show_state Mock-CMKit-Local checkout
	do_sync Mock-CMKit-Local --config CMKit-Automation --repo "$ROOT/Mock-CMKit-BranchNew"
	show_state Mock-CMKit-Remote
	show_state Mock-CMKit-Local checkout
	do_sync Mock-CMKit-Local --config CMKit-Automation --repo "$ROOT/Mock-CMKit-BranchNew"
	show_state Mock-CMKit-Remote
	show_state Mock-CMKit-Local checkout
	do_sync Mock-CMKit-Local --config CMKit-Automation --repo "$ROOT/Mock-CMKit-BranchNew" --force
	show_state Mock-CMKit-Remote reset
	show_state Mock-CMKit-Local reset

	announce "CMKit: Basic sync + commit + push to empty local and remote"
	do_sync Mock-CMKit-Empty --config CMKit-Automation --repo "$ROOT/Mock-CMKit-Old"
	show_state Mock-CMKit-Empty
	show_state Mock-CMKit-Empty-Remote

	announce "CMKit: Exact sync + commit + push to empty local and remote"
	do_sync Mock-CMKit-Empty-Exact --config CMKit-Automation --repo "$ROOT/Mock-CMKit-Old" --exact
	show_state Mock-CMKit-Empty-Exact
	show_state Mock-CMKit-Empty-Exact-Remote
}

##############################################################################
# FactoryLLScriptsPlatfom/FactoryLLScriptsCommon
##############################################################################
#
# $FLLS?                           O                    (master)
#                                  :
#                                  :TagOld
# Mock-FLLS?-Old                   O                    (master)
#                                 /:
#                                : :TagOld       TagNew
# Mock-FLLS?-New                 : O------------O       (master)
#                                :
#                                :\ TagOld
# Mock-FLLS?-Branch              : O                    (master)
#                                : :\
#                                : : \ TagBranch
#                                : :  O                 (FLLS?-Branch)
#                                : :
#                                : :TagOld
# Mock-FLLS?-BranchNew           : O                    (master branch not carried over)
#                                :  \
#                                :   \ TagBranch    TagBranchNew
#                                :    O------------O    (FLLS?-Branch)
#                                :
#                                 \ TagOld
# Mock-FLLS?-Clean (root-based)    O                    (master)
#                                  |
#                                  |TagOld
# Mock-FLLS?-Remote (root-based)   O                    (master)
#                                  |
#                                  |TagOld
# Mock-FLLS?-Local (root-based)    O                    (master)
#
##############################################################################

function edit_factory_scripts
{
	local DIR="$1"
	local FILE="$2"
	local TXT="$3"
	local MSG="${4:-Change sequence version to $TXT}"
	perl -pi -e "s;\d{8};$TXT;" "$DIR/$FILE"
	git -C "$DIR" commit -a -m "$MSG"
}

function build_factory_scripts
{
	local SRC="$(cd "$1" && pwd)"
	local DST="$(mkdir -p "$2" && cd "$2" && pwd)"
	shift 2
	(set -o errexit &&
		cd "$SRC" &&
		export SRCROOT="$SRC" &&
		export DSTROOT="$DST" &&
		export IPHONE_SDK_MARKETING_VERSION=9.0 &&
		export PLATROOT="$(xcodebuild -sdk iphoneos.internal -version PlatformPath 2>/dev/null)" &&
		export CHOWN=true &&
		make -s "$@")
}

function test_factory_scripts
{
	local WHICH="$1"

	local OLD="Mock-$WHICH-Old"
	local OLD_ROOT="Mock-$WHICH-Old-Root"
	local NEW="Mock-$WHICH-New"
	local NEW_ROOT="Mock-$WHICH-New-Root"
	local BRANCH="Mock-$WHICH-Branch"
	local BRANCH_ROOT="Mock-$WHICH-Branch-Root"
	local BRANCHNEW="Mock-$WHICH-BranchNew"
	local BRANCHNEW_ROOT="Mock-$WHICH-BranchNew-Root"
	local EMPTY="Mock-$WHICH-Empty"
	local EMPTY_EXACT="Mock-$WHICH-Empty-Exact"
	local EMPTY_REMOTE="Mock-$WHICH-Empty-Remote"
	local EMPTY_EXACT_REMOTE="Mock-$WHICH-Empty-Exact-Remote"
	local CLEAN="Mock-$WHICH-Clean"
	local REMOTE="Mock-$WHICH-Remote"
	local LOCAL="Mock-$WHICH-Local"

	local REF="${!WHICH}"
	local FILE=
	local TARGETS=()
	if [ "$WHICH" = "FLLSP" ]; then
		FILE="Smokey/Wildfire/N66N71/Main.plist"
		TARGETS=(install N66TARGETS)
	else
		FILE="Smokey/TestMemory/Main.plist"
		TARGETS=(install)
	fi

	announce "$WHICH: Setting up test repos"
	# Set up "old" reference repo/root
	orphan_clone "$REF" "$OLD" --depth 3 --branch master
	git -C "$OLD" tag TagOld
	build_factory_scripts "$OLD" "$OLD_ROOT" "${TARGETS[@]}"
	# Set up "new" reference repo/root
	orphan_clone "$OLD" "$NEW"
	edit_factory_scripts "$NEW" "$FILE" "88889901"
	git -C "$NEW" tag TagNew
	build_factory_scripts "$NEW" "$NEW_ROOT" "${TARGETS[@]}"
	# Set up "branch" reference repo/root
	orphan_clone "$OLD" "$BRANCH"
	git -C "$BRANCH" checkout -b "$WHICH-Branch"
	edit_factory_scripts "$BRANCH" "$FILE" "88889902"
	git -C "$BRANCH" tag TagBranch
	build_factory_scripts "$BRANCH" "$BRANCH_ROOT" "${TARGETS[@]}"
	# Set up "branch-new" reference repo/root
	orphan_clone "$BRANCH" "$BRANCHNEW"
	git -C "$BRANCHNEW" checkout "$WHICH-Branch"
	edit_factory_scripts "$BRANCHNEW" "$FILE" "88889903"
	git -C "$BRANCHNEW" tag TagBranchNew
	build_factory_scripts "$BRANCHNEW" "$BRANCHNEW_ROOT" "${TARGETS[@]}"
	# Set up "empty" target repo/root
	mkdir "$EMPTY_REMOTE"
	git -C "$EMPTY_REMOTE" init
	git -C "$EMPTY_REMOTE" checkout -b out-of-the-way
	git clone "$EMPTY_REMOTE" "$EMPTY"
	mkdir "$EMPTY_EXACT_REMOTE"
	git -C "$EMPTY_EXACT_REMOTE" init
	git -C "$EMPTY_EXACT_REMOTE" checkout -b out-of-the-way
	git clone "$EMPTY_EXACT_REMOTE" "$EMPTY_EXACT"
	# Set up remote and local repos based on reference roots
	rsync --archive "$OLD_ROOT/." "$CLEAN"
	(echo "export BUILD_BRANCH=master" &&
		echo "export GITHASH_LONG=$(git -C "$OLD" rev-parse HEAD)") > "$CLEAN/stamp.mk"
	git -C "$CLEAN" init
	git -C "$CLEAN" add .
	git -C "$CLEAN" commit -q -m "First commit"
	git -C "$CLEAN" tag TagOld
	git clone "$CLEAN" "$REMOTE"
	git clone "$REMOTE" "$LOCAL"
	create_reset "$REMOTE" detach
	create_reset "$LOCAL"
	echo
	show_state "$OLD"
	show_state "$NEW"
	show_state "$BRANCH"
	show_state "$BRANCHNEW"
	show_state "$EMPTY"
	show_state "$EMPTY_EXACT"
	show_state "$EMPTY_REMOTE"
	show_state "$EMPTY_EXACT_REMOTE"
	show_state "$CLEAN"
	show_state "$REMOTE"
	show_state "$LOCAL"

	announce "$WHICH: Basic sync (no-op, force)"
	do_sync "$LOCAL" --config FactoryLLScripts-Automation --tags --repo "$(pwd)/$OLD" --root "$(pwd)/$OLD_ROOT"
	show_state "$LOCAL"
	do_sync "$LOCAL" --config FactoryLLScripts-Automation --tags --repo "$(pwd)/$OLD" --root "$(pwd)/$OLD_ROOT" --force
	show_state "$LOCAL" reset

	announce "$WHICH: Basic sync + commit (normal, no-op, force)"
	do_sync "$LOCAL" --config FactoryLLScripts --tags --repo "$(pwd)/$NEW" --root "$(pwd)/$NEW_ROOT" --commit
	show_state "$LOCAL"
	do_sync "$LOCAL" --config FactoryLLScripts --tags --repo "$(pwd)/$NEW" --root "$(pwd)/$NEW_ROOT" --commit
	show_state "$LOCAL"
	do_sync "$LOCAL" --config FactoryLLScripts --tags --repo "$(pwd)/$NEW" --root "$(pwd)/$NEW_ROOT" --commit --force
	show_state "$LOCAL" reset

	announce "$WHICH: Basic sync + commit + push (normal, no-op, force) from master"
	do_sync "$LOCAL" --config FactoryLLScripts-Automation --tags --repo "$(pwd)/$NEW" --root "$(pwd)/$NEW_ROOT"
	show_state "$REMOTE"
	show_state "$LOCAL"
	do_sync "$LOCAL" --config FactoryLLScripts-Automation --tags --repo "$(pwd)/$NEW" --root "$(pwd)/$NEW_ROOT"
	show_state "$REMOTE"
	show_state "$LOCAL"
	do_sync "$LOCAL" --config FactoryLLScripts-Automation --tags --repo "$(pwd)/$NEW" --root "$(pwd)/$NEW_ROOT" --force
	show_state "$REMOTE" reset
	show_state "$LOCAL" reset

	announce "$WHICH: Basic sync + commit + push to new branch (normal, no-op, force) from master"
	do_sync "$LOCAL" --config FactoryLLScripts-Automation --tags --repo "$(pwd)/$BRANCH" --root "$(pwd)/$BRANCH_ROOT"
	show_state "$REMOTE"
	show_state "$LOCAL" checkout
	do_sync "$LOCAL" --config FactoryLLScripts-Automation --tags --repo "$(pwd)/$BRANCH" --root "$(pwd)/$BRANCH_ROOT"
	show_state "$REMOTE"
	show_state "$LOCAL" checkout
	do_sync "$LOCAL" --config FactoryLLScripts-Automation --tags --repo "$(pwd)/$BRANCH" --root "$(pwd)/$BRANCH_ROOT" --force
	show_state "$REMOTE" reset
	show_state "$LOCAL" reset

	announce "$WHICH: Basic sync + commit + push to existing branch (normal, no-op, force) from master"
	do_sync "$LOCAL" --config FactoryLLScripts-Automation --tags --repo "$(pwd)/$BRANCH" --root "$(pwd)/$BRANCH_ROOT"
	show_state "$REMOTE"
	show_state "$LOCAL" checkout
	do_sync "$LOCAL" --config FactoryLLScripts-Automation --tags --repo "$(pwd)/$BRANCHNEW" --root "$(pwd)/$BRANCHNEW_ROOT"
	show_state "$REMOTE"
	show_state "$LOCAL" checkout
	do_sync "$LOCAL" --config FactoryLLScripts-Automation --tags --repo "$(pwd)/$BRANCHNEW" --root "$(pwd)/$BRANCHNEW_ROOT"
	show_state "$REMOTE"
	show_state "$LOCAL" checkout
	do_sync "$LOCAL" --config FactoryLLScripts-Automation --tags --repo "$(pwd)/$BRANCHNEW" --root "$(pwd)/$BRANCHNEW_ROOT" --force
	show_state "$REMOTE" reset
	show_state "$LOCAL" reset

	announce "$WHICH: Basic sync + commit + push to empty local and remote"
	do_sync "$EMPTY" --config FactoryLLScripts-Automation --tags --repo "$(pwd)/$OLD" --root "$(pwd)/$OLD_ROOT"
	show_state "$EMPTY"
	show_state "$EMPTY_REMOTE"

	announce "$WHICH: Exact sync + commit + push to empty local and remote"
	do_sync "$EMPTY_EXACT" --config FactoryLLScripts-Automation --tags --repo "$(pwd)/$OLD" --root "$(pwd)/$OLD_ROOT" --exact
	show_state "$EMPTY_EXACT"
	show_state "$EMPTY_EXACT_REMOTE"
}

##############################################################################
# Do it!
##############################################################################

test_flldu
test_cmkit
test_factory_scripts FLLSP
test_factory_scripts FLLSC
announce "Complete!"
