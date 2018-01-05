#!/bin/bash

# Command line arguments
BeforeFile=$1
AfterFile=$2
if [ -z "$BeforeFile" -o -z "$AfterFile" ]; then
	echo "Usage: $0 <before.pdf> <after.pdf>"
	exit 1
fi

MaxThreads=$(sysctl -n hw.physicalcpu)
TempDir=$(mktemp -d /tmp/delta-XXXXXX) || exit 1

function CountPages
{
	local Pages
	Pages=$(identify -density 10 -format "%n" "$2") || exit 1
	echo "$2: $Pages pages"
	eval "$1"="$Pages"
}

function RenderDiffs
{
	echo "Rendering differences for $1 pages"
	for ((j=0; j<$1; j+=$MaxThreads)); do 
		for ((i=j; i<j+$MaxThreads && i<$1; ++i)); do 
			echo -n "$(($i+1)) "
			compare -density 300 "$2"[$i] "$3"[$i] -compose src "$TempDir/delta-$i.gif" &
		done
		wait
	done
	echo
}

function CompareDiffs
{
	echo "Checking differences for $1 pages"
	local NumMismatches=0
	local Hash
	for ((i=0; i<$1; ++i)); do
		Hash=$(md5 "$TempDir/delta-$i.gif" | grep -o -i '[a-f0-9]\+$') || exit 1
		# This hash is appropriate for 8.5"x11" pape size
		if [ "$Hash" != "c885527c001060ae97811603da423253" ]; then
			echo $(($i+1))
			((++NumMismatches))
		fi
	done
	if [ $NumMismatches -eq 0 ]; then
		echo "All pages match"
	else
		echo "$NumMismatches pages differ"
	fi
	return $NumMismatches
}

CountPages BeforeFilePages "$BeforeFile"
CountPages AfterFilePages "$AfterFile"
if [ "$BeforeFilePages" -ne "$AfterFilePages" ]; then
	echo "Unequal number of pages"
	exit 1
fi


RenderDiffs $BeforeFilePages "$BeforeFile" "$AfterFile"
CompareDiffs $BeforeFilePages
if [ $? -eq 0 ]; then
	echo "Deleting $TempDir"
	rm -Rf "$TempDir"
	exit 0
else
	echo "Retaining $TempDir for analysis"
	exit 1
fi
