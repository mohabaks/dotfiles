# set keymap
setxkbmap -model pc105 -layout us

# detect external monitors
$HOME/.local/bin/externalMonitor

# set screenlock 
$HOME/.local/bin/locker

# set cursor
xsetroot -cursor_name left_ptr

# start bspwm
sxhkd &
exec bspwm
