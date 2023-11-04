#!/usr/bin/env bash

## Author : Aditya Shakya (adi1090x)
## Github : @adi1090x
#
## Rofi   : Launcher (Modi Drun, Run, File Browser, Window)
#
## Available Styles
#
## style-1     style-2     style-3     style-4     style-5
## style-6     style-7     style-8     style-9     style-10

dir="$HOME/.config/rofi/"

## Run
if $(xrandr -q | grep -q "HDMI-A-2 connected")
then
	theme='cyberpunk'
	rofi -show drun -theme ${dir}/${theme}.rasi
else
	theme='cyberpunk_'
	rofi -show drun -theme ${dir}/${theme}.rasi
fi
