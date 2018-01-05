#!/bin/bash

##############################################################################
# Prerequisites/Assumptions:
#   - Current working directory ("local") is a clone of the Git repo where we
#     ultimately want the files to be synced ("remote").  This is the
#     destination for the copy operations.
#   - Reference repository ("reference") already has the desired files commited
#     and there are no uncommited changes in the workspace (where applicable).
#     This is the source for the copy operations.
#   - Local repo has its remote tracking branches up to date.  This script can
#     switch local branches and also checks whether local/remote/reference
#     repos are using the same branch names.
#   - Branches other than master already exist either locally/on the remote, or
#     the user is OK with those branches being created as orphans.
#   - The master and other branches in the local repo share the same remote
##############################################################################

function real_path
{
	if [ $# -lt 1 ]; then
		echo "$SCRIPT: real_path: Missing path"
		exit 1
	fi
	local DIRNAME="$(cd "$(dirname "$1")" 2>/dev/null && pwd)" || {
		echo "$SCRIPT: real_path: Bad directory"
		exit 1
	}
	if [ "${DIRNAME:0:1}" != "/" ]; then
		echo "$SCRIPT: real_path: Unexpected relative path"
		exit 1
	fi
	local BASENAME="$(basename "$1")" || {
		echo "$SCRIPT: real_path: Bad base name"
		exit 1
	}
	# Calling dirname/basename on "/" or "." is a special case, as is "trailing/dot/."
	if [ "$DIRNAME" = "/" ]; then
		if [ "$BASENAME" = "/" -o "$BASENAME" = "." ]; then
			echo "$DIRNAME"
		else
			echo "$DIRNAME$BASENAME"
		fi
	else
		if [ "$BASENAME" = "." ]; then
			echo "$DIRNAME"
		else
			echo "$DIRNAME/$BASENAME"
		fi
	fi
}

function within_directory
{
	if [ $# -lt 2 ]; then
		echo "$SCRIPT: within_directory: Missing directory or path"
		exit 1
	fi
	local DIR="$(real_path "$1")" || {
		echo "$SCRIPT: within_directory: Bad directory"
		exit 1
	}
	local PATH="$(real_path "$2")" || {
		echo "$SCRIPT: within_directory: Bad path"
		exit 1
	}
	if [ -z "$DIR" -o -z "$PATH" ]; then
		echo "$SCRIPT: within_directory: Bad directory or path"
		exit 1
	fi
	if [ "${DIR:0:1}" != "/" -o "${PATH:0:1}" != "/" ]; then
		echo "$SCRIPT: within_directory: Expected real_path to return absolute paths"
		exit 1
	fi
	local PREFIX=
	if [ "$DIR" = "/" ]; then
		PREFIX="/"
	else
		PREFIX="$DIR/"
	fi
	if [ "${PATH:0:${#PREFIX}}" = "$PREFIX" ]; then
		echo "${PATH:${#PREFIX}}"
	fi
}

function default_branch
{
	if [ $# -lt 1 ]; then
		echo "$SCRIPT: default_branch: Missing repo"
		exit 1
	fi
	local REPO="$1"
	local HEADS="$(git ls-remote -h "$REPO" | cut -c53-)" || exit 1
	if [ "$(wc -w <<< "$HEADS")" -eq 1 ]; then
		# The one and only branch
		echo "$HEADS"
	else
		if [ -d "$REPO" ]; then
			# The branch that is currently checked out (and HEAD isn't detached)
			git -C "$REPO" symbolic-ref --short HEAD || {
				echo "$SCRIPT: default_branch: HEAD is either bad or detached in repo $REPO"
				exit 1
			}
		else
			# Remote repo with many branches (and there isn't a concept of "current branch")
			echo "$SCRIPT: default_branch: Too many branches in $REPO"
			exit 1
		fi
	fi
}

function repo_file_exists
{
	if [ $# -lt 3 ]; then
		echo "$SCRIPT: repo_file_exists: Missing repo, branch, or file"
		exit 1
	fi
	local REPO="$1"
	local BRANCH="$2"
	local FILE="$3"
	git archive --format=tar --remote="$REPO" "$BRANCH" "$FILE" &> /dev/null
}

function extract_version
{
	if [ $# -lt 3 ]; then
		echo "$SCRIPT: extract_version: Missing repo, branch, or file"
		exit 1
	fi
	local REPO="$1"
	local BRANCH="$2"
	local FILE="$3"
	git archive --format=tar --remote="$REPO" "$BRANCH" "$FILE" | tar -xOf - | grep -m1 -e "${COMMIT_VAR}.*=" | sed -e 's/^.*=[ \t]*//'
}

function extract_commit
{
	if [ $# -lt 1 ]; then
		echo "$SCRIPT: extract_commit: Missing repo"
		exit 1
	fi
	local REPO="$1"
	local BRANCH="$2"
	if [ -d "$REPO" ]; then
		git -C "$REPO" rev-parse "$BRANCH"
	else
		git ls-remote "$REPO" "$BRANCH"
	fi
}

function shallow_clone
{
	if [ $# -lt 3 ]; then
		echo "$SCRIPT: shallow_clone: Missing repo, branch, or directory"
		exit 1
	fi
	local REPO="$1"
	local BRANCH="$2"
	local DIR="$3"
	# Workaround for Git complaints about using --depth for local clones
	local DEPTH=
	if [ ! -d "$REPO" ]; then
		DEPTH="--depth 1"
	fi
	git clone $DEPTH --branch "$BRANCH" "$REPO" "$DIR"
}

function pack_lines
{
	if [ $# -lt 2 ]; then
		echo "$SCRIPT: pack_lines: Missing file or commands"
		exit 1
	fi
	local FILE="$1"
	shift
	perl -pe "s/\n/\000/;" "$FILE" | xargs -0 "$@"
}

if [ -n "$FUNCTIONS_ONLY" ]; then
	return
fi

##############################################################################

# Abort on failed commands and undefined variable dereferences
set -o pipefail
set -o errexit
set -u

# Make "cd" behave literally
unset CDPATH

# Save $0 in case something manipulates the command line arguments
SCRIPT=$(basename $0)

GITQ=

##############################################################################

NORMALEXIT=
HITLIST=()
WARNINGS=()

function exit_ok
{
	NORMALEXIT=1
	exit 0
}

function warning
{
	echo -n $'\e[1m'
	echo "WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING"
	echo "$1"
	echo "WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING"
	echo -n $'\e[0m'
	WARNINGS+=( "$1" )
}

function clean_up
{
	if [ -z "$NORMALEXIT" ]; then
		echo
		echo "$SCRIPT: Abnormal exit"
	fi
	if [ "${#WARNINGS[@]}" -gt 0 ]; then
		echo
		echo "Accumulated warnings:"
		for i in "${WARNINGS[@]}"; do
			echo "$i"
		done
	fi
	if [ -z "$OPT_KEEPTEMP" -a "${#HITLIST[@]}" -gt 0 ]; then
		echo
		for i in "${HITLIST[@]}"; do
			echo "Removing $i"
			rm -Rf "$i"
		done
	fi
}

trap clean_up EXIT

##############################################################################

CFG_METHOD_EXACT=1
CFG_METHOD_MIRROR=2
CFG_METHOD_NAMES=( [1]="Exact" [2]="Mirror" )

CFG_VER_STAMP=1
CFG_VER_COMMIT=2
CFG_VER_NAMES=( [1]="Stamp" [2]="Commit" )

OPT_FORCE=
OPT_COMMIT=
OPT_PUSH=
OPT_CREATEBRANCH=
OPT_TAGS=
OPT_TAGS_WARNING=
OPT_QUIET=
OPT_METHOD=
OPT_VER=
OPT_REPO=
OPT_ROOT=
OPT_ROOT_WARNING=
OPT_BRANCH=
OPT_VAR=
OPT_STAMP=
OPT_BLACKLIST=
OPT_DEST=
OPT_CONFIG=
OPT_KEEPTEMP=
OPT_GUARDSTAMP=

while [ $# -gt 0 ]; do
	case "$1" in
		-f|--force)
			OPT_FORCE=1
			;;
		-c|--commit)
			OPT_COMMIT=1
			;;
		-p|--push)
			OPT_PUSH=1
			;;
		-B|--create-branch)
			OPT_CREATEBRANCH=1
			;;
		-t|--tags)
			OPT_TAGS=1
			;;
		-q|--quiet)
			OPT_QUIET=1
			;;
		-K|--keep-temp)
			OPT_KEEPTEMP=1
			;;
		-g|--guard-stamp-file)
			OPT_GUARDSTAMP=1
			;;
		-e|--exact)
			OPT_METHOD="$CFG_METHOD_EXACT"
			;;
		-m|--mirror)
			OPT_METHOD="$CFG_METHOD_MIRROR"
			;;
		-s|--stamp)
			OPT_VER="$CFG_VER_STAMP"
			;;
		-k|--change)
			OPT_VER="$CFG_VER_COMMIT"
			;;
		-r|--repo)
			[ $# -ge 2 ] || { echo "$SCRIPT: Missing reference repo specification"; exit 1; }
			OPT_REPO="$2"
			shift
			;;
		-R|--root)
			[ $# -ge 2 ] || { echo "$SCRIPT: Missing reference root specification"; exit 1; }
			OPT_ROOT="$2"
			shift
			;;
		-b|--branch)
			[ $# -ge 2 ] || { echo "$SCRIPT: Missing reference branch name"; exit 1; }
			OPT_BRANCH="$2"
			shift
			;;
		-v|--var)
			[ $# -ge 2 ] || { echo "$SCRIPT: Missing stamp variable name"; exit 1; }
			OPT_VAR="$2"
			shift
			;;
		-o|--stamp-file)
			[ $# -ge 2 ] || { echo "$SCRIPT: Missing stamp file name"; exit 1; }
			OPT_STAMP="$2"
			shift
			;;
		-x|--blacklist)
			[ $# -ge 2 ] || { echo "$SCRIPT: Missing blacklist file name"; exit 1; }
			OPT_BLACKLIST="$2"
			shift
			;;
		-d|--dest)
			[ $# -ge 2 ] || { echo "$SCRIPT: Missing destination path"; exit 1; }
			OPT_DEST="$2"
			shift
			;;
		-Q|--config)
			[ $# -ge 2 ] || { echo "$SCRIPT: Missing configuration set name"; exit 1; }
			OPT_CONFIG="$2"
			shift
			;;
		-h|--help)
			echo "Sync and stage files from a reference Git repo to the repo of the current working directory"
			echo
			echo "Usage:"
			echo "    $SCRIPT [-f] [-c [-p]] [-q <cfg>]  [-d <dir>] [-e | -m] [-s | -k] [-t]"
			echo "        [-r <repo>] [-b <branch>] [-R <root>] [-B] [-o <file>] [-v <var>]"
			echo "        [-g] [-x <file>]"
			echo "    $SCRIPT -h"
			echo
			echo "Commit options:"
			echo "  -f | --force             Force sync even if hashes match"
			echo "  -c | --commit            Commit changes"
			echo "  -p | --push              Pushes changes (requires -c)"
			echo
			echo "Sync methods:"
			echo "  -e | --exact             Exact sync (copy only files that already exist locally)"
			echo "  -m | --mirror            Mirror sync (make local match reference)"
			echo "  -d | --dest <dir>        Sync files to directory <dir>"
			echo "  -x | --blacklist <file>  Exclude files/directories listed in <file>"
			echo "  -B | --create-branch     Create/check out remote branch if local/reference branch names differ"
			echo "  -t | --tags              Copy tags from HEAD of reference branch"
			echo
			echo "Reference repo:"
			echo "  -r | --repo <repo>       Use <repo> as source for files and metadata"
			echo "  -b | --branch <branch>   Use branch <branch> from reference repo"
			echo "  -R | --root <root>       Use <root> for files instead of <repo>"
			echo
			echo "Reference version tracking:"
			echo "  -s | --stamp             Track reference repo by stamp file"
			echo "  -k | --change            Track reference repo by latest change (commit hash)"
			echo "  -o | --stamp-file <file> Use <file> as stamp file"
			echo "  -v | --var <var>         Use <var> for tracking version in stamp file"
			echo "  -g | --guard-stamp-file  Guard the stamp file from deletion"
			echo
			echo "Other options:"
			echo "  -Q | --config <cfg>      Use pre-defined configuration set <cfg>"
			echo "  -q | --quiet             Make some Git commands less verbose"
			echo "  -K | --keep-temp         Do not delete temporary files"
			echo "  -h | --help              This help text"
			echo
			exit_ok
			;;
		*)
			echo "$SCRIPT: Unexpected option $1"
			exit 1
			;;
	esac
	shift
done

[ $# -eq 0 ] || { echo "$SCRIPT: Extraneous arguments: $@"; exit 1; }

if [ -n "$OPT_CONFIG" ]; then
	case "$OPT_CONFIG" in
		FactoryLLDiagsUtils|FactoryLLDiagsUtils-Automation)
			OPT_REPO="${OPT_REPO:-git@gitlab.sd.apple.com:blackops/shasta.git}"
			OPT_BRANCH="${OPT_BRANCH:-master}"
			#OPT_ROOT=
			OPT_DEST="${OPT_DEST:-Shasta}"
			OPT_METHOD="${OPT_METHOD:-$CFG_METHOD_EXACT}"
			OPT_VER="${OPT_VER:-$CFG_VER_COMMIT}"
			OPT_STAMP="${OPT_STAMP:-stamp.mk}"
			OPT_VAR="${OPT_VAR:-GITHASH_LONG}"
			#OPT_GUARDSTAMP=
			if [ "$OPT_CONFIG" = "FactoryLLDiagsUtils-Automation" ]; then
				#OPT_CREATEBRANCH=
				#OPT_TAGS=
				OPT_COMMIT="${OPT_COMMIT:-1}"
				#OPT_PUSH="${OPT_PUSH:-1}"
			fi
			;;
		CMKit|CMKit-Automation)
			#OPT_REPO="${OPT_REPO:-/tmp/CMKit_N71diag_master-a848a91/Staging}"
			#OPT_BRANCH="${OPT_BRANCH:-master}"
			#OPT_ROOT=
			OPT_DEST="${OPT_DEST:-.}"
			OPT_METHOD="${OPT_METHOD:-$CFG_METHOD_MIRROR}"
			OPT_VER="${OPT_VER:-$CFG_VER_STAMP}"
			OPT_STAMP="${OPT_STAMP:-version.mk}"
			OPT_VAR="${OPT_VAR:-BUILD_ID_VERSION}"
			#OPT_GUARDSTAMP=
			if [ "$OPT_CONFIG" = "CMKit-Automation" ]; then
				OPT_CREATEBRANCH="${OPT_CREATEBRANCH:-1}"
				OPT_TAGS="${OPT_TAGS:-1}"
				OPT_COMMIT="${OPT_COMMIT:-1}"
				OPT_PUSH="${OPT_PUSH:-1}"
			else
				OPT_TAGS_WARNING="${OPT_TAGS_WARNING:-1}"
			fi
			;;
		FactoryLLScripts|FactoryLLScripts-Automation)
			#OPT_REPO="${OPT_REPO:-/Volumes/Case-sensitive/git/FactoryLLScriptsPlatforms}"
			#OPT_BRANCH="${OPT_BRANCH:-master}"
			#OPT_ROOT=
			OPT_ROOT_WARNING=1
			OPT_DEST="${OPT_DEST:-.}"
			OPT_METHOD="${OPT_METHOD:-$CFG_METHOD_MIRROR}"
			OPT_VER="${OPT_VER:-$CFG_VER_COMMIT}"
			OPT_STAMP="${OPT_STAMP:-stamp.mk}"
			OPT_VAR="${OPT_VAR:-GITHASH_LONG}"
			OPT_GUARDSTAMP="${OPT_GUARDSTAMP:-1}"
			if [ "$OPT_CONFIG" = "FactoryLLScripts-Automation" ]; then
				OPT_CREATEBRANCH="${OPT_CREATEBRANCH:-1}"
				#OPT_TAGS=
				OPT_COMMIT="${OPT_COMMIT:-1}"
				OPT_PUSH="${OPT_PUSH:-1}"
			fi
			;;
		*)
			echo "$SCRIPT: Bad configuration name $OPT_CONFIG"
			exit 1
			;;
	esac
fi

if [ -n "$OPT_QUIET" ]; then
	GITQ="-q"
fi

[ -n "$OPT_METHOD" ] || { echo "$SCRIPT: Missing --exact or --mirror"; exit 1; }
[ -n "$OPT_VER" ] || { echo "$SCRIPT: Missing --stamp or --change"; exit 1; }
[ -n "$OPT_REPO" ] || { echo "$SCRIPT: Missing --repo"; exit 1; }
#[ -n "$OPT_BRANCH" ] || { echo "$SCRIPT: Missing --branch"; exit 1; }
[ -n "$OPT_DEST" ] || { echo "$SCRIPT: Missing --dest"; exit 1; }
[ -n "$OPT_VAR" ] || { echo "$SCRIPT: Missing --var"; exit 1; }
[ -n "$OPT_STAMP" ] || { echo "$SCRIPT: Missing --stamp-file"; exit 1; }

if [ -n "$OPT_PUSH" -a -z "$OPT_COMMIT" ]; then
	echo "$SCRIPT: --push requires --commit"
	exit 1
fi
if [ -n "$OPT_TAGS" -a -z "$OPT_COMMIT" ]; then
	echo "$SCRIPT: --tags requires --commit"
	exit 1
fi
if [ -z "$OPT_ROOT" -a -n "$OPT_ROOT_WARNING" ]; then
	warning "$SCRIPT: --root highly recommended for this configuration, but not specfied"
	echo
fi
if [ -z "$OPT_TAGS" -a -n "$OPT_TAGS_WARNING" ]; then
	warning "$SCRIPT: --tags highly recommended for this configuration, but not specfied"
	echo
fi
if [ -z "$OPT_PUSH" -a -n "$OPT_CREATEBRANCH" ]; then
	warning "$SCRIPT: --push highly recommended with --create-branch, but not specfied"
	echo
fi

##############################################################################

# Configuration parameters
echo "Initializing repo information"

# Commit-tracking variable for $CFG_VER_STAMP
COMMIT_VAR="$OPT_VAR"

# Local repo info
LOCAL_TOP="$(git rev-parse --show-toplevel)"
LOCAL_BRANCH="$(git -C "$LOCAL_TOP" symbolic-ref --short HEAD)" || { echo "$SCRIPT: No local branch name"; exit 1; }
LOCAL_BRANCH_REMOTE="$(git -C "$LOCAL_TOP" config branch."$LOCAL_BRANCH".remote)" || { echo "$SCRIPT: No remote for ${LOCAL_BRANCH}"; exit 1; }

# Relative to the top of the local repo
BLACKLIST="$OPT_BLACKLIST"
LOCAL_DEST="$OPT_DEST"
LOCAL_STAMP="$OPT_STAMP"

# Relative to other directories in the local repo
LOCAL_RELATIVE_STAMP="$(within_directory "$LOCAL_TOP/$LOCAL_DEST" "$LOCAL_TOP/$LOCAL_STAMP")" || { echo "$SCRIPT: Can't get relative path of stamp file"; exit 1; }

# Reference repo info
REFERENCE_REPO="$OPT_REPO"
REFERENCE_BRANCH="${OPT_BRANCH:-$(default_branch "$REFERENCE_REPO")}" || { echo "$SCRIPT: Bad or missing remote branch name"; exit 1; }
REFERENCE_TOP=
REFERENCE_ROOT=

# Relative to the top of the reference repo
# NOTE: Currently, REFERENCE_STAMP and LOCAL_STAMP must be the same
REFERENCE_STAMP="$LOCAL_STAMP"

echo "Subtask done!"
echo

##############################################################################

# First and foremost, reject stowaway changes
if [ -n "$(git -C "$LOCAL_TOP" diff --name-only --cached)" ]; then
	echo "$SCRIPT: Cowardly refusing to comingle with uncomitted changes in index"
	exit 1
fi
if [ -n "$(git -C "$LOCAL_TOP" diff --name-only)" ]; then
	echo "$SCRIPT: Cowardly refusing to comingle with uncomitted changes in workspace"
	exit 1
fi

##############################################################################

# Configuration summary
echo "Sync method:     ${CFG_METHOD_NAMES[$OPT_METHOD]}"
echo "Tracking method: ${CFG_VER_NAMES[$OPT_VER]}"
echo

##############################################################################

# Local repository info
echo "Local repo:           $LOCAL_TOP"
echo "Local branch:         $LOCAL_BRANCH"
echo "Local branch remote:  $LOCAL_BRANCH_REMOTE"
LOCAL_VER=
if repo_file_exists "$LOCAL_TOP" "$LOCAL_BRANCH" "$LOCAL_STAMP"; then
	LOCAL_VER=$(extract_version "$LOCAL_TOP" "$LOCAL_BRANCH" "$LOCAL_STAMP") || { echo "$SCRIPT: Bad local stamp"; exit 1; }
	if [ -z "$LOCAL_VER" ]; then
		echo "$SCRIPT: Bad local version"
		exit 1
	fi
	echo "Local version:        $LOCAL_VER"
else
	echo "Local version:        n/a"
fi
echo

# Reference repository info
echo "Reference repo:       $REFERENCE_REPO"
echo "Reference branch:     $REFERENCE_BRANCH"
if [ "$OPT_VER" = "$CFG_VER_STAMP" ]; then
	REFERENCE_VER=$(extract_version "$REFERENCE_REPO" "$REFERENCE_BRANCH" "$REFERENCE_STAMP") || { echo "$SCRIPT: Bad reference stamp"; exit 1; }
else
	if [ -n "$LOCAL_VER" ]; then
		HASH_LENGTH=${#LOCAL_VER}
	else
		HASH_LENGTH=40
	fi
	REFERENCE_VER=$(extract_commit "$REFERENCE_REPO" "$REFERENCE_BRANCH" | cut -c 1-${HASH_LENGTH}) || { echo "$SCRIPT: No reference commit"; exit 1; }
fi
if [ -z "$REFERENCE_VER" ]; then
	echo "$SCRIPT: Bad reference version"
	exit 1
fi
echo "Reference version:    $REFERENCE_VER"
echo

if [ -n "$LOCAL_VER" -o "$OPT_METHOD" = "$CFG_METHOD_EXACT" ]; then
	# Compare version numbers
	if [ "$LOCAL_VER" = "$REFERENCE_VER" -a "$LOCAL_BRANCH" = "$REFERENCE_BRANCH" ]; then
		if [ -n "$OPT_FORCE" ]; then
			echo "Already up to date, but proceeding anyway"
			echo
		else
			echo "Already up to date"
			exit_ok
		fi
	fi
fi

##############################################################################

# Get local access to the reference repo + branch (i.e. on this file system)
REFERENCE_TOP=""
if [ -d "$REFERENCE_REPO" ]; then
	# NOTE: Can't combine this next check with the previous one because the
	#       shell will expand the Git invocation before checking whether
	#       REFERENCE_REPO is a directory
	if [ "$(git -C "$REFERENCE_REPO" rev-parse --abbrev-ref HEAD)" = "$REFERENCE_BRANCH" ]; then
		echo "Using reference repo as-is"
		REFERENCE_TOP="$REFERENCE_REPO"
	fi
fi
if [ -z "$REFERENCE_TOP" ]; then
	# Either clone the reference (which is actually local) or grab a shallow copy from the server
	echo "Cloning reference repo..."
	REFERENCE_TOP=$(mktemp -d /tmp/sync-reference-repo-XXXXXX) || {
		echo "$SCRIPT: Failed to create directory $REFERENCE_TOP for reference repo"
		exit 1
	}
	HITLIST+=( "$REFERENCE_TOP" )
	shallow_clone "$REFERENCE_REPO" "$REFERENCE_BRANCH" "$REFERENCE_TOP"
	echo "Subtask done!"
fi
echo

# Reference files may be a product of the reference repo
REFERENCE_ROOT="${OPT_ROOT:-$REFERENCE_TOP}"
if [ ! -d "$REFERENCE_ROOT" ]; then
	echo "$SCRIPT: Reference path $REFERENCE_TOP is not a directory"
	exit 1
fi

##############################################################################

# Check branch names after confirming that the reference branch name is OK
UPSTREAM_PENDING=
if [ "$LOCAL_BRANCH" != "$REFERENCE_BRANCH" ]; then
	if [ -z "$OPT_CREATEBRANCH" ]; then
		echo "$SCRIPT: Local and reference branch names are different"
		exit 1
	fi
	if [ -n "$(git -C "$LOCAL_TOP" branch --list "$REFERENCE_BRANCH")" ]; then
		echo "Checking out branch $REFERENCE_BRANCH locally..."
		git -C "$LOCAL_TOP" checkout "$REFERENCE_BRANCH"
	else
		git -C "$LOCAL_TOP" fetch "$LOCAL_BRANCH_REMOTE"
		if [ -n "$(git -C "$LOCAL_TOP" ls-remote "$LOCAL_BRANCH_REMOTE" "$REFERENCE_BRANCH")" ]; then
			echo "Checking out branch $REFERENCE_BRANCH from $LOCAL_BRANCH_REMOTE..."
			git -C "$LOCAL_TOP" checkout -b "$REFERENCE_BRANCH" "$LOCAL_BRANCH_REMOTE/$REFERENCE_BRANCH"
		else
			[ -d "$LOCAL_TOP" ] || { echo "$SCRIPT: Local repo is not in a directory"; exit 1; }
			[ -d "$LOCAL_TOP/$LOCAL_DEST" ] || { echo "$SCRIPT: Option --dest does not specify a directory"; exit 1; }
			if [ "$(real_path "$LOCAL_TOP")" != "$(real_path "$LOCAL_TOP/$LOCAL_DEST")" ]; then
				echo "$SCRIPT: Cowardly refusing to create new branch $REFERENCE_BRANCH without --dest set to the top-level directory"
				exit 1
			fi
			if [ "$OPT_METHOD" != "$CFG_METHOD_MIRROR" ]; then
				echo "$SCRIPT: Cowardly refusing to create new branch $REFERENCE_BRANCH without mirror method"
				exit 1
			fi
			echo "Creating orphan branch $REFERENCE_BRANCH (with upstream \"$LOCAL_BRANCH_REMOTE\" to be set later)..."
			git -C "$LOCAL_TOP" checkout --orphan "$REFERENCE_BRANCH"
			# Since we require LOCAL_DEST to be ".", we know that LOCAL_RELATIVE_STAMP is a non-empty string
			if [ -n "$OPT_GUARDSTAMP" ]; then
				git -C "$LOCAL_TOP" ls-files | fgrep -x -v -e "$LOCAL_RELATIVE_STAMP" | tr '\n' '\0' | xargs -0 git -C "$LOCAL_TOP" rm -q -f
			else
				git -C "$LOCAL_TOP" rm -q -rf .
			fi
			UPSTREAM_PENDING=1
		fi
	fi
	echo "Subtask done!"
	echo

	LOCAL_BRANCH="$REFERENCE_BRANCH"
	echo "Local branch is now $LOCAL_BRANCH"
	if [ -n "$UPSTREAM_PENDING" ]; then
		LOCAL_VER=
		echo "Local version is unset for now"
	else
		LOCAL_VER=$(extract_version "$LOCAL_TOP" "$LOCAL_BRANCH" "$LOCAL_STAMP") || { echo "$SCRIPT: Bad local stamp after branch"; exit 1; }
		if [ -z "$LOCAL_VER" ]; then
			echo "$SCRIPT: Bad local version"
			exit 1
		fi
		echo "Local version is now $LOCAL_VER"
		if [ "$LOCAL_VER" = "$REFERENCE_VER" ]; then
			if [ -n "$OPT_FORCE" ]; then
				echo "Already up to date, but proceeding anyway"
			else
				echo "Already up to date"
				exit_ok
			fi
		fi
	fi
	echo
fi

if [ -z "$OPT_PUSH" -a -n "$UPSTREAM_PENDING" ]; then
	warning "$SCRIPT: Orphan branch will not have upstream without --push"
	echo
fi

##############################################################################

function list_files
{
	if [ $# -lt 3 ]; then
		echo "$SCRIPT: list_files: Missing \"which\", variable, directory"
		exit 1
	fi
	local WHICH="$1"
	local VAR="$2"
	local DIR="$3"
	echo "Creating $WHICH file list..."
	eval $VAR='"$(mktemp /tmp/sync-$WHICH-files-XXXXXX)"' || { 
		echo "$SCRIPT: list_files: Failed to create file for $WHICH file list"
		exit 1
	}
	HITLIST+=( "${!VAR}" )
	# NOTE: Don't use "git rev-parse --is-inside-work-tree" for the
	#       conditional check because $DIR might be an untracked directory
	#       in a Git repo
	if git -C "$DIR" ls-files --error-unmatch 1>/dev/null 2>&1; then
		git -C "$DIR" ls-files > "${!VAR}"
	else
		(cd "$DIR" && find . -not -type d | cut -c3-) > "${!VAR}"
	fi
}

# Create and populate LOCAL_MANIFEST/REFERENCE_MANIFEST
list_files "local" LOCAL_MANIFEST "$LOCAL_TOP/$LOCAL_DEST"
list_files "reference" REFERENCE_MANIFEST "$REFERENCE_ROOT"
echo "Subtask done!"
echo

# Check if LOCAL_STAMP is inside LOCAL_DEST
if [ -n "$LOCAL_RELATIVE_STAMP" ]; then
	if ! fgrep -l -x -e "$LOCAL_RELATIVE_STAMP" "$REFERENCE_MANIFEST" 1>/dev/null 2>&1; then
		if [ -z "$OPT_GUARDSTAMP" ]; then
			echo "$SCRIPT: Stamp file $LOCAL_STAMP is inside $LOCAL_DEST and will be deleted"
			exit 1
		else
			echo "Amending file lists to guard $LOCAL_STAMP"
			perl -n -i -e 'print unless m/^\Q'"$LOCAL_RELATIVE_STAMP"'\E$/' "$LOCAL_MANIFEST"
			echo "Subtask done!"
			echo
		fi
	fi
fi

##############################################################################

if [ -n "$OPT_TAGS" ]; then
	echo "Reading all tags from reference branch $REFERENCE_BRANCH..."
	{ OLD_IFS="$IFS"; IFS=$'\n'; REFERENCE_TAGS=( $(git -C "$REFERENCE_TOP" tag --points-at HEAD) ); IFS="$OLD_IFS"; } || {
		echo "$SCRIPT: Failed to get reference tags"
		exit 1
	}
	echo "Subtask done!"
	echo
fi

##############################################################################

# Sync files from REFERENCE_ROOT to LOCAL_DEST using selected method
if [ "$OPT_METHOD" = "$CFG_METHOD_EXACT" ]; then
	echo "Using repo files to exactly update local files..."
	MANIFEST="$LOCAL_MANIFEST"
else
	echo "Replacing repo with reference files..."
	echo "Deleting local files..."
	pack_lines "$LOCAL_MANIFEST" git -C "$LOCAL_TOP/$LOCAL_DEST" rm -q --
	MANIFEST="$REFERENCE_MANIFEST"
fi
echo "Copying reference files..."
rsync \
	--links \
	--exclude-from "$BLACKLIST" \
	--include "*" \
	--files-from "$MANIFEST" \
	"$REFERENCE_ROOT" \
	"$LOCAL_TOP/$LOCAL_DEST"
echo "Subtask done!"
echo

# Tell Git about the new/updated files
echo "Staging files..."
pack_lines "$MANIFEST" git -C "$LOCAL_TOP/$LOCAL_DEST" add --
echo "Subtask done!"
echo

# Exit early when the only differences are due to changes outside of the local files
if [ -z "$(git -C "$LOCAL_TOP" diff --name-only --cached)" ]; then
	echo "No changes"
	exit_ok
fi

# Update the stamp only for commit-based versioning.
echo "Touching local version stamp..."
if [ ! -e "$LOCAL_TOP/$LOCAL_STAMP" -a -z "$LOCAL_VER" ]; then
    echo "${COMMIT_VAR}=${REFERENCE_VER}" > "$LOCAL_TOP/$LOCAL_STAMP"
else
    perl -p -i -e "s/\b(${COMMIT_VAR}\s*=\s*)\w+\b/\1\Q${REFERENCE_VER}\E/" "$LOCAL_TOP/$LOCAL_STAMP"
fi
git -C "$LOCAL_TOP" add -- "$LOCAL_STAMP"
echo "Subtask done!"
echo

# Commit changes to local repo
if [ -n "$OPT_COMMIT" ]; then
	# NOTE: If we make it here without any staged changes, Git will error
	#       when trying to commit, thereby ending this script, which is OK
	#       since that would be a terminal condition anyway
	echo "Committing changes..."
	git -C "$LOCAL_TOP" commit $GITQ -m "Autosync from $REFERENCE_VER"
	echo "Subtask done!"
	echo

	if [ -n "$OPT_TAGS" ]; then
		if [ "${#REFERENCE_TAGS[@]}" -eq 0 ]; then
			echo "No reference tags to apply"
		else
			echo "Applying tags from reference branch $REFERENCE_BRANCH..."
			for i in "${REFERENCE_TAGS[@]}"; do
				echo "Tag: $i"
				git -C "$LOCAL_TOP" tag "$i" HEAD
			done
			echo "Subtask done!"
		fi
		echo
	fi
fi

# Push changes to server
if [ -n "$OPT_PUSH" ]; then
	echo "Pushing changes to remote server..."
	# Avoid the vagaries of "simple"/"default"/etc due to a plain "git push" by explicitly specifying the push target
	if [ -n "$UPSTREAM_PENDING" ]; then
		LOCAL_TRACKING_REMOTE="$LOCAL_BRANCH_REMOTE"
		LOCAL_TRACKING_BRANCH="$LOCAL_BRANCH"
	else
		LOCAL_TRACKING_REMOTE="$(git -C "$LOCAL_TOP" config branch.$LOCAL_BRANCH.remote)" || {
			echo "$SCRIPT: No remote for local branch $LOCAL_BRANCH"
			exit 1
		}
		LOCAL_TRACKING_BRANCH="$(git -C "$LOCAL_TOP" config branch.$LOCAL_BRANCH.merge)" || {
			echo "$SCRIPT: No tracking branch for local branch $LOCAL_BRANCH"
			exit 1
		}
	fi
	git -C "$LOCAL_TOP" push ${UPSTREAM_PENDING:+-u} "$LOCAL_TRACKING_REMOTE" "$LOCAL_TRACKING_BRANCH"
	echo "Subtask done!"
	echo

	if [ -n "$OPT_TAGS" ]; then
		if [ "${#REFERENCE_TAGS[@]}" -eq 0 ]; then
			echo "No reference tags to push"
		else
			echo "Pushing tags to remote server..."
			git -C "$LOCAL_TOP" push "$LOCAL_TRACKING_REMOTE" "${REFERENCE_TAGS[@]}"
			echo "Subtask done!"
		fi
		echo
	fi
fi

##############################################################################

echo "All done!"
exit_ok
