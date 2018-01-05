#!/bin/sh
export P4CLIENT=rdub-gcc-diags
export P4PORT=ipodmfgp4.apple.com:1722
export P4USER=rdub
export PATH="/opt/local/bin:/opt/local/sbin:/Users/rdub/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/usr/local/bin"

echo $PASSWORD | p4 login

cd $WORKSPACE
git checkout master || exit 1;
git pull || exit 1;
git checkout perforce || exit 1;
git p4 sync || exit 1;
echo "Return: $?"
git p4 rebase || exit 1;
echo "Return: $?"
git push || exit 1;
echo "Return: $?"
git checkout master || exit 1;
echo "Return: $?"
git merge --no-ff --no-edit perforce || exit 1;
echo "Return: $?"
git push || exit 1;
echo "Return: $?"
