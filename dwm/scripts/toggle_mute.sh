#!/bin/sh

pamixer --toggle-mute

status=$(pamixer --get-volume-human)

if [[ $status == "muted" ]]; then
    dunstify -r 6667 -h int:value:0 "System Volume" "Muted" -u normal -i "/usr/share/icons/Arc/panel/16/audio-volume-muted-blocking.svg" -a Volume -t 5000
else
    dunstify -r 6667 -h int:value:"$(pamixer --get-volume)" "System Volume" "$(pamixer --get-volume)" -u normal -i "/usr/share/icons/Arc/panel/16/audio-volume-high.svg" -a Volume -t 5000
fi

canberra-gtk-play -i audio-volume-change
