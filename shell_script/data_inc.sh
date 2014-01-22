#!/bin/sh
ifconfig | read v1 v2 v3 v4 v5 v6

echo "v1 = $v1"
echo "v2 = $v2"
echo "v5 = $v5"

v7=00:12:34:56:7b:90

echo "v7 = $v7"
echo $v7 > a.txt
echo "cat a.txt"
cat a.txt
read v1 v2 v3 v4 v5 v6 < a.txt
echo "v6 = $v6"

va=`echo $v7 | awk -F: '{print $5}'`


echo "va = $va"

vb=$(((16#$va + 1)))
echo "$vb ` printf "%x" $vb` "
