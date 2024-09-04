#!/bin/bash
# set disply
#$HOME/.config/bspwm/display.sh

# lockscreen
xss-lock --transfer-sleep-lock -- $HOME/.config/polybar/lockme &

# set cursor
xsetroot -cursor_name left_ptr

# start WM
exec bspwm
