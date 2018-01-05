#!/bin/bash -ex

PW_REPO=~/Home/jobs/Shasta-sync/prairiewolf-src
GILG_REPO=~/Home/jobs/Shasta-sync/gilgamesh
SHASTA_REPO=~/Home/jobs/Shasta-sync/workspace
PATCH_FOLDER=~/Home/jobs/Shasta-sync/patches

# First check if a previous patch session failed - if so, bail now
pushd $SHASTA_REPO

if [ -d .git/rebase-apply ] ; then 
	echo "Previous patch session b0rked.  Bailing out until this is fixed."
	echo "You can view the last successful build on jenkins - the hash from which to start updating should be recorded in the logs."
	exit 1
fi

popd

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
	echo "Prairiewolf: Everything is up-to-date"
fi

popd

pushd $GILG_REPO

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
	pushd $SHASTA_REPO
	
	# make sure we're working on master
	git checkout master
	
	# get up-to-date
	git pull || exit 1
	
	# Apply each patch
	git am --directory=bootloader/ $PATCH_FOLDER/*.patch
	
	# And push changes upstream
	git push

	popd
else
	echo "Gilgamesh: Everything is up-to-date"
fi

popd
