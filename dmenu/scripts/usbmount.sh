#!/bin/sh

mount $(lsblk -lp | awk '/part/ {print $1, "(" $4 ")"}' | dmenu -nb '#222222' -nf '#666666' -sb '#000000' -sf '#bbbbbb' -p mount | awk '{print $1}') /mnt
