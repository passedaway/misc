
#!/bin/sh

#function define
usage() {
	echo "$0  <filename>  <filesize>"
	echo -e "args : \n\tfilename : input filename\n\tfilesize : dest file size(MB)\n"

	return 0
}

#start

#check args

if [ ! -f $1 ] ; then
	echo -e "Error : $1 file not found!"
	usage
	exit 0
fi

INPUT_FILENAME=$1

if [ $# != 2 ] ; then
	usage
	exit
fi

DEST_SIZE=$2

FILE_SIZE=`stat -c "%s" $1`

NEED_SIZE=$[ $DEST_SIZE * 1024 * 1024]
NEED_SIZE=$[ $NEED_SIZE - $FILE_SIZE ]

echo -e "file_size = $FILE_SIZE"
echo -e "dest_size = $DEST_SIZE"
echo -e "need_size = $NEED_SIZE"

cp $INPUT_FILENAME dest.out
i=1
for i in $( seq 1 $NEED_SIZE )
do
	echo -ne "\xff" >> dest.out
done

echo "exev over!\n"
