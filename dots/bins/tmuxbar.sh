#!/bin/bash

interval=0



## Wi-fi
wlan() {
	case "$(cat /sys/class/net/w*/operstate 2>/dev/null)" in
		up) printf "  Connected " ;;
		down) printf " 睊 Disconnected " ;;
	esac
}

## Time
clock() {
	printf "  "
	printf "$(date +%H:%M)"
}

volume () {
  printf "  "
  printf "$(amixer get Master | tail -n1 | awk -F ' ' '{print $5}' | tr -d '[]%')"
  printf "%%"
}
timed () {
    printf "  "
    printf "$(LC_TIME=en_GB.UTF-8 date "+%A %d %B %Y" )"
}
## Battery Info
battery() {
	BAT=$(upower -i `upower -e | grep 'BAT'` | grep 'percentage' | cut -d':' -f2 | tr -d '%,[:blank:]')
	AC=$(upower -i `upower -e | grep 'BAT'` | grep 'state' | cut -d':' -f2 | tr -d '[:blank:]')

	if [[ "$AC" == "charging" ]]; then
		printf "  $BAT%%"
	elif [[ "$AC" == "fully-charged" ]]; then
		printf " Full"
	else
		if [[ ("$BAT" -ge "0") && ("$BAT" -le "20") ]]; then
			printf "  $BAT%%"
		elif [[ ("$BAT" -ge "20") && ("$BAT" -le "40") ]]; then
			printf "  $BAT%%"
		elif [[ ("$BAT" -ge "40") && ("$BAT" -le "60") ]]; then
			printf "  $BAT%%"
		elif [[ ("$BAT" -ge "60") && ("$BAT" -le "80") ]]; then
			printf "  $BAT%%"
		elif [[ ("$BAT" -ge "80") && ("$BAT" -le "100") ]]; then
			printf "  $BAT%%"
		fi
	fi
}

## Brightness
brightness() {
	printf " %.0f" `xbacklight -get`
	echo "%"
}
## Main
while true; do
  [ "$interval" == 0 ] || [ $(("$interval" % 3600)) == 0 ]
  interval=$((interval + 1))
  sleep 1 && echo "$(battery) |$(volume) | $(brightness) |$(wlan)|$(clock) |$(timed)"
done
