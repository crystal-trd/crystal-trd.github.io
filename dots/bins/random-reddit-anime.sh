

WALLPAPER_DIR="/home/crystal/Pictures/Wallpapers/Reddit"
URI="https://www.reddit.com/r/animewallpaper/search.json?q=flair%3Adesktop&restrict_sr=on&nsfw=on&sort=new"
DESKTOP_PATH="~/"

USERAGENT="Mozilla/5.0 (X11; Linux x86_64; rv:100.0) Gecko/20100101 Firefox/100.0"

IMGURL=$(curl -H "User-Agent: $USERAGENT" $URI   | jq '.data.children' | jq '.[].data.url' | egrep "(jpe?g|png)\"$" | sed s/\"//g | sort -R | head -1)
echo $IMGURL
IMGFILE=$WALLPAPER_DIR/$(printf "%s\n" "${IMGURL##*/}")
echo $IMGFILE
curl $IMGURL -o $IMGFILE
file=$(echo "$IMGFILE")
killall xwinwrap
                if [[ "$file" =~ ".thumb.png" ]]; then
                        vid=$(echo "$file" | sed 's/.thumb.png//g')
                        wpg -s "$file"
                        case "$(loginctl show-session self -p Type)" in
                                "Type=wayland") mpvpaper -o "-wid WID --no-osc --no-osd-bar --loop-file --player-operation-mode=cplayer --no-audio --panscan=1.0 --no-input-default-bindings" eDP-1 $vid.mp4 & ;;
                                *) xwinwrap -ov -g 1366x768+0+0 -- mpv -wid WID $vid.mp4 --no-osc --no-osd-bar --loop-file --player-operation-mode=cplayer --no-audio --panscan=1.0 --no-input-default-bindings & ;;
                        esac
                        pywal-discord -p /home/crystal/.config/discocss
                        pywalfox update && xsetroot -name "fsignal:1"
                        echo "$file" >> /home/crystal/.cache/wallpaper.txt
                        killall nsxiv

else
                        wpg -s "$file"
                        case "$(loginctl show-session self -p Type)" in

                                "Type=wayland") setwallpaper $file & ;;
                        esac
                        pywal-discord -p /home/crystal/.config/discocss
                        pywalfox update && xsetroot -name "fsignal:1"
                        echo "$file" >> /home/crystal/.cache/wallpaper.txt
                        killall nsxiv
fi

