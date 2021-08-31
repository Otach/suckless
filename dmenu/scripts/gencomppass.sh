#!/bin/sh

site=$(dmenu -nb '#222222' -nf '#666666' -sb '#000000' -sf '#bbbbbb' -r -p "Site:")

if [ "$site" == "" ]; then
    dunstify -a "Company Password Generator" "No password generated" "A password identifier was not specified"
    exit 1
fi

pass generate "company/$site" 30
pass -c "company/$site"

dunstify -a "Company Password Generator" "company/$site" "Password was generated for company/$site and copied to your clipboard. The clipboard will be cleared in 45 seconds."
