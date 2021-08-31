#!/bin/sh

site=$(dmenu -nb '#222222' -nf '#666666' -sb '#000000' -sf '#bbbbbb' -r -p "Site:")

if [ "$site" == "" ]; then
    dunstify -a "Password Generator" "No password generated" "A password identifier was not specified"
    exit 1
fi

pass generate $site 30
pass -c $site

dunstify -a "Password Generator" "$site" "Password was generated for $site and copied to your clipboard. The clipboard will be cleared in 45 seconds."
