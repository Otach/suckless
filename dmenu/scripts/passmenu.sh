#!/bin/sh

password=$(find ~/.local/share/pass -maxdepth 1 -type f -name '*.gpg' |
				sed 's/.*\/\(.*\)\.gpg$/\1/' | sort | dmenu -nb '#222222' -nf '#666666' -sb '#000000' -sf '#bbbbbb' -i -hp 'google.com,digitalocean,discover.com' -p " Pass:")
[ -n "$password" ] && pass show -c "$password"

# Check to make sure that a password was selected
if [ "$password" = "" ] 
then
		exit 1;
fi

dunstify -a "Pass" "$password" "Password copied to clipboard. Will clear in 45 seconds."
