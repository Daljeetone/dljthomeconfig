#!/bin/bash

FUNCTIONS_ONLY=1
source lldiags-git-sync.sh

# TODO: Test within_directory with DIR="."
# TODO: Test within_directory with DIR="/b"
# TODO: Test within_directory with DIR="a/b"

function wd
{
	echo -n "$1"$'\t'"$2"$'\t'": "
	echo "$(within_directory "$1" "$2")"
}

#cd /Users/ctran/tmp
#mkdir a
#mkdir b
#touch a/b
wd "a" "a/b"
wd "a/" "a/b"
wd "a/." "a/b"
wd "." "a/b"
wd "." "a"
wd "/" "a/b"
wd "/." "a/b"
echo
wd "b" "a/b"
wd "b/" "a/b"
wd "./b" "a/b"
wd "/Users/ctran/tmp/b" "a/b"
echo
wd "a" "./a/b"
wd "a/" "./a/b"
wd "a/." "./a/b"
wd "." "./a/b"
wd "." "./a"
wd "/" "./a/b"
wd "/." "./a/b"
echo
wd "a" "/Users/ctran/tmp/b"
wd "a/" "/Users/ctran/tmp/b"
wd "a/." "/Users/ctran/tmp/b"
wd "." "/Users/ctran/tmp/b"
wd "/" "/Users/ctran/tmp/b"
wd "/." "/Users/ctran/tmp/b"
echo
wd "a" "/Users/ctran/tmp/a/b"
wd "a/" "/Users/ctran/tmp/a/b"
wd "a/." "/Users/ctran/tmp/a/b"
wd "." "/Users/ctran/tmp/a/b"
wd "/" "/Users/ctran/tmp/a/b"
wd "/." "/Users/ctran/tmp/a/b"
