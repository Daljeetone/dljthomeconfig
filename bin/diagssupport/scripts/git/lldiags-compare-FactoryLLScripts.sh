#!/bin/bash

# Compare the HEAD of all branches of FactoryLLScriptsCommon-* and
# FactoryLLScriptsPlatforms-* in hwtegit.apple.com against the respective
# commits in FactoryLLScriptsCommon and FactoryLLScriptsPlatforms in
# gitlab.sd.apple.com.  This can be used for these purposes
#
# - Verify that the initial commits to hwtegit.apple.com (which is done
#   manually) are correct
#
# - Double check that the continuous sync process is copying the correct files

set -o errexit -o pipefail -u
#set -vx

# NOTE: When using these, do not wrap them with double quotes to avoid
#       generating a zero-length command line option
DIFFQ=-q
GITQ=-q

# TODO: Define these variables from the command line or modify this file before
#       running this script!
# NOTE: We will be actively checking out specific commits from these repos, so
#       make sure there are no uncommited changes!
#FLLSC=/Volumes/Case-sensitive/git/Diags/FactoryLLScriptsCommon-Master
#FLLSP=/Volumes/Case-sensitive/git/Diags/FactoryLLScriptsPlatforms-Master
test -n "${FLLSC}" || { >&2 echo "FLLSC is undefined"; exit 1; }
test -n "${FLLSP}" || { >&2 echo "FLLSP is undefined"; exit 1; }

ROOT=$(mktemp -d /tmp/compare-XXXXXX)

git -C "${FLLSC}" fetch ${GITQ} origin
git -C "${FLLSP}" fetch ${GITQ} origin

# Iterate over the given local clones of hwtegit.apple.com
for i in "$@"; do
	# Strip any trailing slashes from the repo path
	CMKIT="$(cd "$i" && pwd)"
	# Infer the reference repo so we can build the roots by ourself
	case "${CMKIT}" in
		*/FactoryLLScriptsCommon*)
			REF="$FLLSC"
			PLATFORMTARGETS=
			;;
		*/FactoryLLScriptsPlatforms*)
			REF="$FLLSP"
			PLATFORMTARGETS="$(basename "${CMKIT}" | cut -c27-)"TARGETS
			;;
		*)
			>&2 echo "Don't know how to handle ${CMKIT}"
			exit 1
			;;
	esac
	# Get the latest branch updates
	git -C "${CMKIT}" fetch ${GITQ} origin
	git -C "${CMKIT}" remote prune origin
	# Iterate over each branch for this repo in hwtegit.apple.com
	for j in $(git -C "${CMKIT}" branch -a | grep "remotes/origin" | grep -v "remotes/origin/HEAD"); do
		# Get the branch name
		BRANCH=${j#remotes/origin/}
		# Get the hash of the commit in the reference repo
		git -C "${CMKIT}" checkout ${GITQ} "${BRANCH}"
		git -C "${CMKIT}" merge ${GITQ} "origin/${BRANCH}"
		HASH=$(grep -o -m1 -e "=.*" "${CMKIT}/stamp.mk" | cut -c2-)
		# Status update
		echo "$(basename ${CMKIT}) -- ${BRANCH} @ ${HASH:0:7}"
		echo
		git -C "${REF}" branch -r --contains "${HASH}" | grep -q -w -e "origin/${BRANCH}" || {
			>&2 echo "${HASH} did not come from ${BRANCH}"
			exit 1
		}
		# Build a root from the reference repo
		git -C "${REF}" checkout ${GITQ} "${HASH}"
		git -C "${REF}" submodule ${GITQ} update --init
		rm -Rf "${ROOT}"/*
		(cd "${REF}" && SRCROOT="${REF}" DSTROOT="${ROOT}" PATH="~/bin/override:$PATH" make install ${PLATFORMTARGETS}) &> /dev/null || {
			>&2 echo "Failed to build root"
			exit 1
		}
		# Confirm that this branch in hwtegit.apple.com matches the output from gitlab.sd.apple.com
		# TODO: Need diff 3.3 or later to get --no-dereference option for comparing symlinks
		#       http://unix.stackexchange.com/a/179114
		diff ${DIFFQ} -r -x .git -x stamp.mk "${ROOT}" "${CMKIT}" || echo
	done
done

# Delete only on success.  On failure, user is able to inspect manually, but must delete by themselves.
rm -Rf "${ROOT}"
