#/bin/sh
pppd_dialing()
{
	echo "pppd dialing..."
	rm -rf tmp
	pppd call cmnet  > tmp &
	#pppd call cmnet &
	sleep 20
	echo "log:";cat tmp

	cat tmp | grep DNS > tmp1
	if [ -s tmp1 ]
	then
	#	echo "tmp1";cat tmp1
		cat tmp1 | awk '{ print "nameserver " $4 }' >/etc/resolv.conf
		echo "dns:";cat /etc/resolv.conf
		echo "pppd dial OK!"
		route del default
		route add default ppp0
		rm -rf tmp tmp1
	else
		killall pppd

		echo "pppd dial error!"
		echo "please restart the modem, and run pppd again!"
		rm -rf tmp tmp1
	fi
}

echo "pppd dialing start."

true=1
while [ $true=1 ] 
do
	result=`ifconfig ppp0`
	case "$result" in
		"ppp0"*"Point-to-Point"*)
			echo "ppp0 working!"
			sleep 5
			;;
		*)
			echo "pppd not start, or has some execption!";echo "starting..."
#			killall pppd
#			sleep 2
			pppd_dialing
			;;
	esac

done
