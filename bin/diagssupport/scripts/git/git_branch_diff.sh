#!/bin/sh

# Usage: ./git_branch_diff.sh <other-branch>
# This compares the tip of the current branch to the branch-point 
# relative to the other target branch (where in history)

BASE=`git merge-base $1 HEAD`
echo "Merge Base: $BASE"

echo "Files changed:"
git diff --stat $BASE HEAD

#echo "Diff:"
#git diff $BASE HEAD
