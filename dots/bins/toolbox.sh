#!/usr/bin/env bash

main_menu() {
    egg=$(dialog --menu "Welcome to Crystalwms toolbox, what do you want to do today" 0 0 0 1 "Take a system snapshot" 2 "Do a world update" 3 "Launch dwm" 4 "Apply picom filters" 5 "Change system theme" 6 "Install a package"  7 "Uninstall a package" 8 "Shutdown" 9 "Reboot" 10 "Remote control the system using Discord" 3>&1 1>&2 2>&3 3>&-)
case $egg in
    "1") snapshot ;;
    "2") world_update ;;
    "3") startdwm ;;
    "4") picom_filters ;;
    "5") themer ;; # no need for function
    "6") install_package ;;
    "7") uninstall_package ;;
    "8") loginctl poweroff ;; # no need for function
    "9") loginctl reboot ;; # no need for function
    "10") (cd ~/remoteDiscordShell && python3 pyDiscordShellBot.py &) ;;

esac

}
snapshot() {
    snapname=$(dialog --title "Dialog title" --inputbox "Choose a name for your snapshot" 0 0  3>&1 1>&2 2>&3 3>&-)
    echo "$password" | sudo -S snapper -c root create --description $snapname
    echo "$password" | sudo grub-mkconfig -o /boot/grub/grub.cfg
    main_menu
}
world_update () {
    echo "$password" | sudo -S emerge --sync
    echo "$password" | sudo -S emerge -uqDN @world
    main_menu
}
get_password() {
    password=$(dialog --insecure --passwordbox "Enter your password:" 0 0 3>&1 1>&2 2>&3 3>&-)
}
get_password
main_menu
