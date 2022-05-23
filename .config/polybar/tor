#!/bin/bash

status=$( systemctl status tor|grep Active|cut -d":" -f2|cut -d" " -f2)

if [[ -n "$status" ]] && [[ "$status" = "active" ]];then
        echo "torOn"
else
        echo "torOff"
fi
