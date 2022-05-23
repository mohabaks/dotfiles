#!/bin/bash

xdg_autostart() {
    local config=$1
    shopt -s nullglob
    if [[ -d "$config/autostart" ]]; then
        local i
        for i in $config/autostart/*.desktop; do
            grep -q -E "^Hidden=true" "$i" && continue
            if grep -q -E "^OnlyShowIn=" "$i"; then
                # need to test twice, as lack of the line entirely means we still run it
                grep -E "^OnlyShowIn=" "$i" | grep -q 'I3;' || continue
            fi
            grep -E "^NotShowIn=" "$i" | grep -q 'I3;' && continue

            local trycmd=$(grep -E "^TryExec=" "$i" | cut -d'=' -f2)
            if [[ -n "$trycmd" ]]; then
                which "$trycmd" >/dev/null 2>&1 || continue
            fi

            local cmd=$(grep -E "^Exec=" "$i" | cut -d'=' -f2)
            if [[ -n "$cmd" ]]; then
                $cmd &
            fi
        done
    fi
}

xdg_autostart "${XDG_CONFIG_DIRS-/etc/xdg}"
xdg_autostart "${XDG_CONFIG_HOME-$HOME/.config}"
