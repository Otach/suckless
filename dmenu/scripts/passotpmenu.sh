#!/bin/sh

password=$(find ~/.password-store/ -type f -name '*.gpg' |
                sed 's/.*\/\(.*\)\.gpg$/\1/' | dmenu -nb '#222222' -nf '#666666' -sb '#000000' -sf '#bbbbbb' -i -p "Pass:")

if [ "$password" == "" ];then
    exit 1
fi

pass otp "$password" -c
dunstify -a "Pass OTP" "$password" "OTP copied to clipboard. Will clear in 45 seconds."
