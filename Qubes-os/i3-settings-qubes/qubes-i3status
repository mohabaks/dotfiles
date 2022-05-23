#!/bin/bash

json() {
    if [[ -n "$3" ]]; then
        echo -n "{\"name\":\"$1\",\"color\":\"$3\",\"full_text\":\"$2\"},"
    else
        echo -n "{\"name\":\"$1\",\"full_text\":\"$2\"},"
    fi
}

status_net() {
    local netvms=$(qvm-ls --no-spinner --raw-data --fields NAME,FLAGS 2>/dev/null | grep '|...N....$' | cut -d '|' -f1)

    IFS_BAK=$IFS
    IFS=$'\n'
    for netvm in $netvms; do
        local ip_addr=$(qvm-run "$netvm" -p 'ip -o -f inet addr' 2>/dev/null)
        for ip_addr_line in $ip_addr; do
            local device_name=${ip_addr_line#* }
            device_name=${device_name%% *}

            if [[ $device_name == wl* ]]; then # this is a wifi device
                local net=$(qvm-run $netvm -p 'iwconfig' 2>/dev/null)
                local ssid=$(echo "$net" | perl -ne 'print "$1" if /ESSID:"(.*)"/')
                local ip=${ip_addr_line#* inet }
                ip=${ip%%/*}
                if [[ -n $ssid ]]; then
                    local quality=$(echo "$net" | perl -ne 'print "$1" if /Quality=([^ ]+)/')
                    json $device_name "$netvm: $ssid $ip $quality"
                fi
            elif [[ $device_name == en* ]]; then # this is an ethernet device
                local ip=${ip_addr_line#* inet }
                ip=${ip%%/*}
                json $device_name "$netvm: $ip"
            fi
        done
    done
    IFS=$IFS_BAK
    IFS_BAK=
}

status_time() {
    local time=$(date '+%F %T')
    echo -n "{\"name\":\"time\",\"full_text\":\"$time\"}" # last entry
}

status_bat() {
    local accum_now=0;
    local accum_full=0;

    for battery in /sys/class/power_supply/BAT*; do
        accum_now=$((accum_now + $(cat $battery/energy_now)))
        accum_full=$((accum_full + $(cat $battery/energy_full)))
    done
    local bat=$((100*accum_now/accum_full))

    local ac=''
    local color=''
    if [[ $(cat /sys/class/power_supply/AC/online) == '1' ]]; then
        ac=' AC'
    elif ((bat < 25)); then
        color='#ff0000'
    elif ((bat < 50)); then
        color='#ffff00'
    fi

    json bat "Bat: $bat%$ac" "$color"
}

status_load() {
    local load=$(uptime)
    load=${load/#*load average: }
    load=${load%,*,*}
    json load "Load: $load"
}

status_qubes() {
    local qubes=$(qvm-ls --no-spinner --raw-data --fields FLAGS 2>/dev/null | grep -v '^0' | grep '^.r......' | wc -l)
    json qubes "$qubes Qubes"
}

status_disk() {
    local disk=`df -h / | tail -n 1 | awk '{print $4}'`
    json disk "Disk free: $disk"
}

main() {
    echo '{"version":1}'
    echo '['
    echo '[]'
    local n
    for ((n=0; ; ++n)); do
        if (( n % 10 == 0 )); then
            local qubes=$(status_qubes)
            # network status disabled by default as it's dangerous to run a
            # command on a qube from dom0
            # local net=$(status_net)
            local disk=$(status_disk)
            local bat=$(status_bat)
            local load=$(status_load)
        fi
        local time=$(status_time)
        echo ",[$qubes$disk$bat$load$time]"
        sleep 1
    done
}

main
