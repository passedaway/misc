#/bin/sh

if [ -d "Public" ]
then
	echo "public is a dirctory"
else
	echo "public not a dirctory"
fi

flag=1

if [ 0 -eq $flag ]
then
	echo '$? is 0 '
else
	echo '$? is not 0'
fi
