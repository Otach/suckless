#!/usr/bin/env bash
#
# Script name: mount_remote_shares.sh
# Description: Choose from a list of remote shares to mount
# Dependencies: dmenu

if [ "$1" == "m" ]; then

    declare -A commands
    commands["Picture"]="sudo -A mount -t cifs //167.99.237.45/pictures /mnt/remote-picture-server/ -o username=mason,uid=1000,gid=1000,sec=ntlmssp"
    commands["Company"]="sudo -A mount -t cifs //mwtechservices.com/mwtechservices /mnt/company-server/ -o username=mason,uid=1000,gid=1000,sec=ntlmssp"
    commands["Home"]="sudo -A mount -t cifs //192.168.40.153/mason /mnt/home-server/ -o username=mason,uid=mason,gid=mason"
    commands["FuzzerMounted"]="sudo -A mount -t cifs //192.168.40.154/mounted_disk /mnt/fuzzer-mounted/ -o username=mason,uid=mason,gid=mason"
    commands["Movies"]="sudo -A mount -t cifs //192.168.40.153/storage_dir /mnt/movies/ -o username=mason,uid=mason,gid=mason"
    commands["SevenSeas"]="sudo -A mount -t cifs //192.168.40.153/seven_seas /mnt/sevenseas/ -o username=mason,uid=mason,gid=mason"
    commands["Crafty"]="sudo -A mount -t cifs //167.99.237.45/crafty_backups /mnt/crafty_backups/ -o username=mason,uid=1000,gid=1000,sec=ntlmssp"
    choice=$(printf '%s\n' "${!commands[@]}" | dmenu -nb '#222222' -nf '#666666' -sb '#000000' -sf '#bbbbbb' -l 7 -i -p " Mount Remote Share:")

    if [[ -z $choice ]]; then
        exit 2
    fi

    pass=$(dmenu -nb '#222222' -nf '#666666' -sb '#000000' -sf '#bbbbbb' -P -p "Password:")

    command=${commands[$choice]}
    full_command=$command",password="$pass

    dunstify -a "Remote Share Mount" "Info" "Please press your security key to finish mounting" -r 6667
    $full_command

    # Check that the command completed successfully. If not, give a notification saying that it failed.
    if [[ $? -ne 0 ]]; then
        dunstify -a "Remote Share Mount" "Warning" "Could not mount the filesystem. Please try again." -r 6667 -t 5000 -i "/usr/share/icons/AdwaitaLegacy/32x32/status/dialog-error-symbolic.symbolic.png"
        exit 4
    fi
    dunstify -a "Remote Share Mount" "Success" "Filesystem Mounted" -i "/usr/share/icons/AdwaitaLegacy/32x32/places/network-server-symbolic.symbolic.png" -r 6667 -t 5000

elif [ "$1" == "u" ]; then

    declare -A umount_commands
    mounted_filesystems=$(cat /etc/mtab | grep /mnt | awk '{split($0, a, " "); print a[2];}' | grep -v usb$)
    for n in $mounted_filesystems; do
        umount_commands["$n"]="sudo umount $n"
    done
    choice=$(printf '%s\n' "${!umount_commands[@]}" | dmenu -nb '#222222' -nf '#666666' -sb '#000000' -sf '#bbbbbb' -l 6 -i -p " Unmount Remote Share:")

    if [[ -z $choice ]]; then
        exit 3
    fi

    command=${umount_commands[$choice]}
    $command

else
    echo "No Command supplied"
    exit 1
fi


