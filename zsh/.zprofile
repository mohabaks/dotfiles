#!/bin/zsh

[[ -f ~/.zshrc ]] && . ~/.zshrc

if [[ -z "$DISPLAY" ]] && [[ $(tty) = /dev/tty1 ]]; then
	exec dbus-run-session -- Hyprland -c $HOME/.config/hypr/monitor/hyprland.conf
	#exec dbus-run-session -- Hyprland -c $HOME/.config/hypr/laptop/hyprland.conf
fi
