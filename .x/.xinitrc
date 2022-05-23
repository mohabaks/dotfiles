#!/bin/sh
#
#             _       _ _            
#       __  _(_)_ __ (_) |_ _ __ ___ 
#       \ \/ / | '_ \| | __| '__/ __|
#        >  <| | | | | | |_| | | (__ 
#       /_/\_\_|_| |_|_|\__|_|  \___|
#
#
#

# lockscreen
xss-lock -v -- i3lock -i $HOME/Pictures/Walls/lock.png \
          --ring-color=198388 --keyhl-color=47d4b9 --bshl-color=277fff \
          --clock --date-color=c5d1eb --time-color=c5d1eb --inside-color=11121d &

# mute speaker
amixer sset Speaker mute

# set cursor theme
xsetroot -cursor_name left_ptr

# start urxvt server
urxvtd -q &

# start dunst
dunst -config $HOME/.config/dunst/dunstrc &

# disable touch screen
xinput disable "Wacom Pen and multitouch sensor Finger"

# allow LXD/Docker GUI Apps
xhost +local:

# set wallpaper
feh --bg-scale $HOME/Pictures/Walls/wall.jpg

# load .Xresources
xrdb $HOME/.Xresources

# start WM
exec dwmblocks 2>/dev/null &
exec dwm
