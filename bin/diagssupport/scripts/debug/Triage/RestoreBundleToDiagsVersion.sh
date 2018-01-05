#!/bin/bash

set -o errexit
set -o pipefail
set -u

SCRIPT="$(basename $0)"

if [ $# -lt 2 ]; then
	echo "Usage: $SCRIPT <bundle_version> <platform>"
	echo "  <bundle_version>  - Restore bundle version (e.g. 13A62460o)"
	echo "  <platform>        - Device platform (e.g. N66)"
	exit
fi

# FYI the corresponding DSTROOT for the SRCROOT below is "/SWE/release/Software/*/Updates/*${1}/Roots/FactoryLLDiags_${2}/"
FILES=($(ls $(eval echo "/SWE/iOS/Views/*Family/*/Updates/*${1}/Projects/FactoryLLDiags/bin/versions/diag-${2}.txt"))) || true

if [ ${#FILES[@]} -eq 1 ]; then
	if [ ! -e "${FILES[0]}" ]; then
		FILES=()
	fi
fi

if [ ${#FILES[@]} -eq 0 ]; then
	>&2 echo "$SCRIPT: No matches"
	>&2 echo "$SCRIPT: Hint: Are you signed into AppleConnect?"
	>&2 echo "$SCRIPT: Hint: Have you tried the combined binary name (e.g. Skye27C)?"
	exit 1
elif [ ${#FILES[@]} -gt 1 ]; then
	>&2 echo "$SCRIPT: Multiple matches"
fi

for i in "${FILES[@]}"; do
	echo -n "$(sed -e 's/diag-\(.*\)\.txt/\1/' <<< "$(basename "$i")"): "
	cat "$i"
done
