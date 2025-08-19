#!/bin/sh

if [ $# -ne 1 ]; then
    echo "This script requires only 1 argument";
    exit
fi

echo $1 | nc -U /tmp/awfulmc.sock
