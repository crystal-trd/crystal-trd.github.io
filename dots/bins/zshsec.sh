#!/bin/bash
lockey=$(cat /home/crystal/.config/lockey.txt)
trap '' 2

cfp() {
   mount /dev/disk/by-uuid/56F623881D34FD10 /mnt
   usbkey=$(cat /mnt/poem.txt | base64)
  if [[ "$lockey" == "$usbkey" ]]; then
	  clear
	  echo "Welcome back queen!!"
		umount /mnt
	else
		loginctl poweroff
  fi

}


read -p "Insert the USB Stick and Hit [Enter] to continue"
cfp
