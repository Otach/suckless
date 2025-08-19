#!/bin/sh

password=$(find ~/.local/share/pass/company -maxdepth 1 -type f -name '*.gpg' |
                sed 's/.*\/\(.*\)\.gpg$/\1/' | dmenu -nb '#222222' -nf '#666666' -sb '#000000' -sf '#bbbbbb' -i -p " Pass:")
[ -n "$password" ] && pass show -c "company/${password}"

# Check to make sure that a password was selected
if [ "$password" = "" ]
then
		exit 1;
fi

dunstify -a "Pass" "$password" "Password copied to clipboard. Will clear in 45 seconds." -i "/usr/share/icons/breeze-dark/actions/24/edit-copy.png" -t 45000 -r 6666
