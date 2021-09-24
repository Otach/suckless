#!/usr/bin/env bash
#
# Script name: mount_remote_shares.sh
# Description: Choose from a list of remote shares to mount
# Dependencies: dmenu

declare -A commands
commands["Picture Server"]="sudo mount -t cifs //167.99.237.45/pictures /mnt/remote-picture-server/ -o username=mason"
commands["Remote Server"]="sudo mount -t cifs //mwtechservices.com/mwtechservices /mnt/company-server/ -o username=mason"

choice=$(printf '%s\n' "${!commands[@]}" | dmenu -nb '#222222' -nf '#666666' -sb '#000000' -sf '#bbbbbb' -l 4 -i -p 'Remote Share Mount:' "$@")

if [[ -z $choice ]]; then
    exit 1
fi

pass=$(dmenu -nb '#222222' -nf '#666666' -sb '#000000' -sf '#bbbbbb' -P -p "Password:")

command=${commands[$choice]}
full_command=$command",password="$pass

dunstify -a "Remote Share Mount" "Info" "Please press your security key to finish mounting"
$full_command

