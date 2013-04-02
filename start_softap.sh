#!/bin/sh
echo "insmod wlan driver"
insmod wlan.ko

echo "config wlan0"
ifconfig wlan0 up
ifconfig wlan0 192.168.1.1
ifconfig wlan0 up
killall -9 udhcpc

echo "config iptables for nat"
echo 1 > /proc/sys/net/ipv4/ip_forward
iptables -F
iptables -t nat -F
iptables -t filter -F
iptables -t nat -A POSTROUTING -o eth0 -j MASQUERADE

echo "start udhcpd"
udhcpd &

echo "start
hostapd -d hostapd.conf 0>/dev/null 1>/dev/null 2>/dev/null &
