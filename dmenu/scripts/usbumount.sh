#!/bin/sh

declare -A commands
commands["Picture Server"]="/mnt/remote-picture-server"
commands["Remote Server"]="/mnt/company-server"

choice=$(printf '%s\n' "${!commands[@]}" | dmenu -nb '#222222' -nf '#666666' -sb '#000000' -sf '#bbbbbb' -l 4 -i -p ' Unmount:' "$@")

if [[ -z $choice ]]; then
    exit 1
fi

dunstify -a "Storage Unmount" "Info" "Please press your security key to finish unmounting"
sudo umount ${commands[$choice]}

