#/bin/sh
echo "pppd dialing..."
rm -rf tmp
exit_status=`pppd call cmnet`
echo "pppd exit_status : $exit_status"

#pppd call cmnet &
sleep 20
echo "log:";cat tmp

cat tmp | grep DNS > tmp1
if [ -s tmp1 ]
then
	echo "tmp1";cat tmp1
	cat tmp1 | awk '{ print "nameserver " $4 }' >/etc/resolv.conf
	echo "dns";cat resolv.conf
	echo "pppd dial OK!"
	route del default
	route add default ppp0
	rm -rf tmp tmp1
else
	killall pppd

	echo "pppd dial error!"
	echo "please restart the modem, and run pppd again!"
	rm -rf tmp tmp1 resolv.conf
	exit
fi
