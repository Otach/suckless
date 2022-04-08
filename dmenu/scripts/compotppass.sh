#!/bin/sh

password=$(find ~/.local/share/pass/company -type f -name '*.gpg' |
                sed 's/.*\/\(.*\)\.gpg$/\1/' | sort | dmenu -nb '#222222' -nf '#666666' -sb '#000000' -sf '#bbbbbb' -i -p " Pass OTP:")
[ -n "$password" ] && pass otp "company/$password" -c
dunstify -a "Pass OTP" "$password" "OTP copied to clipboard. Will clear in 45 seconds."
