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

docker run -d --rm -p 8080:8080 -it forscht/ddrive --port 8080 --token OTgzMTA5Nzg1NDc2MDA1ODk4.G43xHO.nEQ25Px8jLGiLwFPx7crccmEXeF3FNgulgoKQ8 --channelId 999040576764793044
docker run -d --rm -p 8888:8080 -v "/home/crystal/my-instance/searxng:/etc/searxng" -e "BASE_URL=http://localhost:8888/" searxng/searxng
## -----------------------------------------------
# Launch DWM
~/Crystalwm/bins/dwm-flexi/dwm
#~/Crystalwm/bins/dwm/dwm
