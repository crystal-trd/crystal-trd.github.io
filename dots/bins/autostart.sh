#!/usr/bin/env bash

## Copyright (C) 2020-2022 Aditya Shakya <adi1090x@gmail.com>
## Everyone is permitted to copy and distribute copies of this file under GNU-GPL3
## Autostart Programs

# Polkit agent
#/usr/lib/xfce-polkit/xfce-polkit &
# Restore wallpaper
feh --bg-fill "$(tail -n 1 ~/.cache/wallpaper.txt)"
# Lauch dwmbar
~/Crystalwm/bins/dwmbar.sh &
xrdb -merge ~/.Xresources
# Lauch compositor
picom --experimental-backends &
#dunst &
setxkbmap -layout us -option compose:sclk
## Add your autostart programs here --------------
emacs --daemon & 

## -----------------------------------------------
# Launch DWM
~/Crystalwm/bins/dwm-flexi/dwm
#~/Crystalwm/bins/dwm/dwm
