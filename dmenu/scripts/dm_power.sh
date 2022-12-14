#!/usr/bin/env bash
#
# Script name: dm_power.sh
# Description: Choose from a list of power options
# Dependencies: dmenu

declare -A commands
commands[" Lock"]="slock"
commands["⏼ Reboot"]="systemctl reboot"
commands[" Shutdown"]="systemctl poweroff"

choice=$(printf '%s\n' "${!commands[@]}" | dmenu -nb '#222222' -nf '#666666' -sb '#000000' -sf '#bbbbbb' -l 4 -i -p '⏻ Power menu:' "$@")

if [[ -z $choice ]]; then
    exit 1
fi

# TODO:
#   Add a confirmation prompt when reboot or shutdown is selected

eval "${commands["${choice}"]}"
