# First argument is OD user name
if [ -n "$1" ]; then
	user="$1"
else
	user=chanhduy
fi
exec kinit ${user}@APPLECONNECT.APPLE.COM
