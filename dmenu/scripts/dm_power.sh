#!/usr/bin/env bash
#
# Script name: dm_power.sh
# Description: Choose from a list of power options
# Dependencies: dmenu

declare -A commands
commands["Reboot"]="systemctl reboot"
commands["Lock Screen"]="i3lock-multimonitor -i /home/mason/Pictures/background.png"
commands["Blackout Lock Screen"]="slock"
commands["Shutdown"]="systemctl poweroff"

choice=$(printf '%s\n' "${!commands[@]}" | dmenu -nb '#222222' -nf '#666666' -sb '#000000' -sf '#bbbbbb' -l 4 -i -p 'Shutdown menu:' "$@")

if [[ -z $choice ]]; then
    exit 1
fi

eval "${commands["${choice}"]}"

