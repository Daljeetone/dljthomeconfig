#!/bin/bash
# $1 KANZI ID


printHelp()
{
echo "Usage:./RunCheck.sh <kanzi_number> <producttype>"
echo "Example:bash RunCheck.sh 000F50 watch"
echo "Note:Comment marker in blacklist is #"
exit
}

if [ "$1" == "--help" ]; then
    printHelp;
    exit;
fi

KANZI_ID="KanziSWD-"$1
KANZI_ADDR="/dev/cu.kanzi-"$1
# ADDR=$1
# LOC=$2
PRODUCT=$2
# echo $ID
echo $KANZI_ID
echo $KANZI_ADDR
xcrun --sdk iphoneos SmokeySimulator --link $KANZI_ADDR --run TurnOn --clean

while read p; do
    p="${p%#*}"
    p=$(echo -e "${p}" | tr -d '[[:space:]]')
    if [ -n "$p" ]; then
        BLACKLIST="$BLACKLIST -e $p"
    fi
done <$PRODUCT

# echo $BLACKLIST
/SWE/Teams/CoreOS/PE/SOC/bin/socval/socval verifyTunables -p $KANZI_ID > ./tunables_$PRODUCT.txt
grep -v $BLACKLIST tunables_$PRODUCT.txt
