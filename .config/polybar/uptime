#!/bin/bash
seconds="$(< /proc/uptime)"
seconds="${seconds/.*}"

days="$((seconds / 60 / 60 / 24))"
hours="$((seconds / 60 / 60 % 24))"
mins="$((seconds / 60 % 60)) min"


if [[ "$days" != "0" ]];then
        if [[ "$days" = "1" ]] && [[ "$hours" = "1" ]];then
                uptime="$days day, $hours hr, $mins"
                echo "$uptime"
        elif [[ "$days" = "1" ]] && [[ "$hours" != "1" ]];then
                uptime="$days day, $hours hrs, $mins"
                echo "$uptime"
        else
                uptime="$days days, $hours hrs, $mins"
                echo "$uptime"
        fi
elif [[ "$hours" = "0" ]];then
        uptime="$mins"
        echo "$uptime"
else
        uptime="$hours hrs, $mins"
        echo "$uptime"
fi
