#!/bin/bash

PW_REPO=~/Projects/git/prairiewolf
SHASTA_REPO=~/Projects/git/Shasta
PATCH_FOLDER=/tmp/patches

# Get into prairiewolf-src repository
pushd $PW_REPO

# Check for the latest changes
OLD_COMMIT=`git rev-parse HEAD`
git pull || exit 1
NEW_COMMIT=`git rev-parse HEAD`

if [ "$OLD_COMMIT" != "$NEW_COMMIT" ] ; then
	# Create a patch folder
	rm -rf $PATCH_FOLDER
	mkdir $PATCH_FOLDER
	
	# Make patches for each change
	git format-patch -o $PATCH_FOLDER $OLD_COMMIT..$NEW_COMMIT
	
	# Go into Shasta folder
	popd
	pushd $SHASTA_REPO
	
	# make sure we're working on master
	git checkout master
	
	# get up-to-date
	git pull || exit 1
	
	# Apply each patch
	git am --directory=diagnostics/ $PATCH_FOLDER/*.patch
	
	# And push changes upstream
	git push
	
	popd
	
else
	echo "Everything is up-to-date"
	exit 0
fi