#!/usr/bin/env bash
#
# Script name: dmconf
# Description: Choose from a list of configuration files to edit.
# Dependencies: dmenu, vim

DMEDITOR="vim"

declare -A options
options[bash]="$HOME/.bashrc"
options[bashprofile]="$HOME/.bash_profile"
options[task]="$HOME/.config/task/taskrc"
options[git]="$HOME/.config/git/config"
options[vim]="$HOME/.config/vim/vimrc"
options[xinit]="$HOME/.xinitrc"
options[dunst]="$HOME/.config/dunst/dunstrc"
options[barrier]="$HOME/.config/barrier"
options[neofetch]="$HOME/.config/neofetch/config.conf"
options[nitrogen]="$HOME/.config/nitrogen/nitrogen.cfg"
options[nitrogen-bg]="$HOME/.config/nitrogen/bg-saved.cfg"
options[picom]="$HOME/.config/picom/picom.conf"
options[dmenu]="$HOME/suckless/dmenu/config.def.h"
options[dwm]="$HOME/suckless/dwm/config.def.h"
options[slock]="$HOME/suckless/slock/config.def.h"
options[slstatus]="$HOME/suckless/slstatus/config.def.h"
options[st]="$HOME/suckless/st/config.def.h"
options[spotifyd]="$HOME/.config/spotifyd/spotifyd.conf"

# Clean options array making sure that the files exist
declare -A options_clean
  for i in "${!options[@]}"; do
    [[ -f ${options["${i}"]} ]] && options_clean["${i}"]=${options["${i}"]}
  done

# Piping the above array (cleaned) into dmenu.
# We use "printf '%s\n'" to format the array one item to a line.
choice=$(printf '%s\n' "${!options_clean[@]}" | sort | dmenu -nb '#222222' -nf '#666666' -sb '#000000' -sf '#bbbbbb' -i -p 'Edit config:' "$@")


# What to do when/if we choose a file to edit.
if [ "$choice" ]; then
  cfg=$(printf '%s\n' "${options_clean["${choice}"]}")
  st vim "$cfg"

# What to do if we just escape without choosing anything.
else
    echo "Program terminated." && exit 0
fi
