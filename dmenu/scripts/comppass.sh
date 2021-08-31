#!/bin/sh

password=$(find ~/.password-store/company -maxdepth 1 -type f -name '*.gpg' |
                sed 's/.*\/\(.*\)\.gpg$/\1/' | dmenu -nb '#222222' -nf '#666666' -sb '#000000' -sf '#bbbbbb' -i -p "Pass:")

if [ "$password" == "" ];then
    exit 1
fi

pass -c "company/${password}"
dunstify -a "Pass" "$password" "Password copied to clipboard. Will clear in 45 seconds."
