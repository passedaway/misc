#/bin/sh

usage()
{
	echo "usage:"
	echo "$0 src-directory result-directory"
	echo " "
}

for_directory()
{
	echo "enter directory : $1 $2"
	local result=`ls $1`
	local tmp=0
	src_cur_dir=$1
	dest_cur_dir=$2
	for tmp in $result
	do
		if [ -d "$src_cur_dir/$tmp" ]
		then
			#directory
			for_directory $src_cur_dir/$tmp $dest_cur_dir/$tmp
			#echo $1 $2 "src_cur_dir $src_cur_dir"
			#echo "=========== $result"
			src_cur_dir=$1
			dest_cur_dir=$2
		else
			#not directory
			case "$tmp" in
				*".h")
					echo "copy: $src_cur_dir/$tmp ---> $dest_cur_dir/$tmp"
					if [ ! -d $dest_cur_dir ]
					then
						echo "mkdir: $dest_cur_dir not exists. create it"
						mkdir $dest_cur_dir -p
					fi
					cp "$src_cur_dir/$tmp" $dest_cur_dir/$tmp -rf
				#	echo "copy: over"
					;;
				*);;
			esac
		fi
	done

	echo "leave for directory: $1 $2"
}

# start process
echo "start process..."
if [ $# != 2 ]
then
	echo "args not invalid ? see usage."
	usage $0
	exit -1
fi

src_cur_dir=$1
dest_cur_dir=$2

#check $1 valid
if [ ! -d $1 ]
then
	echo "$1 is not directory ?"
	usage
	exit -2
fi

#check $2 valid
if [ -f $2 ]
then
	rm -rf $2
fi

if [ ! -d $2 ] 
then
	mkdir $2
else
	got=0
	echo -n "alread exist. remove ? [Y/n]"
	while [ $got == 0 ] 
	do
		read line
		case $line in
			[yY])
				got=1
				;;
			[nN])
				got=2
				;;
		esac
		if [ $got == 0 ] 
		then
			echo -n "alread exist. remove ? [Y/n]"
		fi
	done

	if [ $got == 1 ]
	then
		echo "remove $2"
		rm $2/* -rf
	fi

	if [ $got == 2 ]
	then
		echo "process terminate."
		exit 0
	fi
fi

echo ""
echo "processing ..."
for_directory $1 $2

echo ""
echo "process over!"

