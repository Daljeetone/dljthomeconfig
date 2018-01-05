#!/bin/bash

# Only works for master branch, folks!

TARGET_RELEASE=$1

next_tag () {
	TAG=$1
	PROJECT=`echo $TAG | cut -d'-' -f1`
	NUMERICAL=`echo $TAG | cut -d'-' -f2-`
	
	NEXT=$(($NUMERICAL + 1))
	
	echo $PROJECT-$NEXT
}

# Update things smartly
git checkout master
git pull 
git fetch --tags
git submodule init
git submodule update

LATEST_TAG=`git tag -l | sort -t - -k1,1n -k2,2n | tail -n 1`
PROJECT=`echo $LATEST_TAG | cut -d'-' -f1`

(git log $LATEST_TAG..HEAD | grep rdar ) && SUBMIT=1 || SUBMIT=0

#echo Submit: $SUBMIT

# TEST: 
if [ $SUBMIT -eq 1 ]; then
	# Radar list, no whitespace
	RADARS=`git log $LATEST_TAG..HEAD | grep rdar | sed 's/^ *//g'`
	echo "Radars since previous tag ($LATEST_TAG): $RADARS"
	
	NEW_TAG=$(next_tag $LATEST_TAG)
	
	echo "New Tag: $NEW_TAG"
	TAG_MSG=$(cat <<EOL
dub-submit: Tagging $PROJECT as $NEW_TAG for Submission
Radars:
$RADARS
EOL)
	echo "Tag message: $TAG_MSG"
	echo ""
	
	# Create the tag
	echo $TAG_MSG | git tag -a $NEW_TAG -F-
	# Sending tag to server
	git push --tags
	
	# Setup a clean source-root for submission in /tmp
	echo "# Archiving sources..."
	git archive --format=tar $NEW_TAG -o /tmp/$NEW_TAG.tar
	mkdir /tmp/$NEW_TAG
	echo "# Extracting sources..."
	gnutar xf /tmp/$NEW_TAG.tar -C /tmp/$NEW_TAG
	echo "# Submodule archive and extract..."
	git submodule foreach "git archive --format=tar \$sha1 -o /tmp/$NEW_TAG.\$sha1.tar"
	git submodule foreach "gnutar xf /tmp/$NEW_TAG.\$sha1.tar -C /tmp/$NEW_TAG/\$path"

	echo "# Root is at /tmp/$NEW_TAG"
	
	# Create submission notes
	/Network/Servers/xs1/release/bin/submitproject -createNotesTemplate tmp.plist $TARGET_RELEASE
	
	# Update radar list (key id is 7)
	/usr/libexec/PlistBuddy -c "Delete :7:response" tmp.plist
	/usr/libexec/PlistBuddy -c "Add :7:response array" tmp.plist
	for rdar in $RADARS; do
		/usr/libexec/PlistBuddy -c "Add :7:response: string $rdar" tmp.plist
	done
	
	/Network/Servers/xs1/release/bin/submitproject /tmp/$NEW_TAG $TARGET_RELEASE -notesfile tmp.plist
	
else
	echo "No submission necessary - no radars checked in since last tag"
fi
	
	
	