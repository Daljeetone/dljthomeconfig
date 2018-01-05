#!/bin/bash

set -o errexit -o pipefail
#set -xv

while getopts "hs:" OPT; do
	case $OPT in
		s)
			SHASTA="${OPTARG}"
			;;
		h)
			cat << HERE
Scan directories for 

Usage: $(basename $0) [-s <shasta>] <dir> ...

-s <shasta>    Path to Shasta repo
<dir> ...      Director(ies) tree to san
HERE
			exit 0
			;;
		*)
			exit 1
			;;
	esac
done
shift $((OPTIND-1))

if [ -z "$1" ]; then
	>&2 echo "Missing paths"
	exit 1
fi


if [ -z "${SHASTA}" ]; then
	>&2 echo "Missing path to Shasta"
	exit 1
fi
PROJECTS=( $(cd ${SHASTA}/bootloader/Platform/Apple && ls -d *diag | sed -e 's/diag$//' | sort -u) )

for d in "$@"; do
	# This product code name is the substring after the last dash
	THIS="$(cd "$d" && pwd)"
	THIS="${THIS##*-}"
	case $THIS in
		D10|D11) FRIENDS=( D10 D11 ) ;;
		N56|N61) FRIENDS=( N56 N61 ) ;;
		N66|N71) FRIENDS=( N66 N71 ) ;;
		*) FRIENDS=( "${THIS}" ) ;;
	esac
	BLACKLIST=( $(printf "%s\n" "${PROJECTS[@]}" | fgrep -w -v $(printf -- "-e %s " "${FRIENDS[@]}")) )
	REGEX="$(printf "|%s" "${BLACKLIST[@]}")"
	REGEX="${REGEX:1}"

	echo
	echo -e "===> \033[0;31m$d\033[0m"
	echo

	eval find "$d"/* $(printf -- "-name '*%s*' -o " "${BLACKLIST[@]}") -false | GREP_COLOR="30;43" grep --color -E -e "${REGEX}"
	echo

	# NOTE: To find all file extensions:
	#       find . -type f -not -path '*/.git/*' | grep -o -e '\.[^.]*$' | sort -u
	ag -G '\.lua$|\.sh$|\.plist$' "${REGEX}" "$d"
done
