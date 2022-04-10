#!/bin/sh

pamixer -i $1

volume=$(pamixer --get-volume)

dunstify -r 6667 -h int:value:$volume "System Volume" "$volume" -u normal -i /usr/share/icons/Arc/panel/16/audio-volume-high.svg -a Volume -t 5000

canberra-gtk-play -i audio-volume-change
