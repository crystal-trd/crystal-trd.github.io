
file=$(echo "/home/crystal/Pictures/Wallpapers/"$(exa ~/Pictures/Wallpapers | shuf -n 1))
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

