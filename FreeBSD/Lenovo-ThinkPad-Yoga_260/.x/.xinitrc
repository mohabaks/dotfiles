# set keyboard
setxkbmap -layout us

# disable touch screen
xinput disable "Multitouch"

# enable X11 gui
xhost +archlinux.bhyve.local

# lockscreen
$HOME/.local/bin/locker

# Set cursor theme
xsetroot -cursor_name left_ptr

# set wallpaper
feh --bg-scale $HOME/Pictures/Walls/01.jpg

# start wm
exec dwmblocks &
exec dwm
