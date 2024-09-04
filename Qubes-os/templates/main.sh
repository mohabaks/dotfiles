#!/bin/bash
# Author: https://github.com/mohabaks
# Description: Main script for automating making changes on Qubes-OS Templates
msg(){
 echo -e "\033[32m[+] $@\033[0m"
}

template_status(){
	if $(qvm-ls --halted -O NAME|grep $1 &>/dev/null); then
		msg Starting qubes $1
		qvm-start -q $1
		sleep 15
	fi
}

sys-template(){
	local TARGET="fedora-40-sys"
	local TARGET_DIR="/home/user/QubesIncoming/dom0"
	local SCRIPT="fedora-sys"
	template_status $TARGET
	msg Copying require files to qube $TARGET
	qvm-copy-to-vm  $TARGET $(pwd)/$SCRIPT
	qvm-copy-to-vm  $TARGET $HOME/.themes &>/dev/null
	qvm-copy-to-vm  $TARGET $HOME/.icons/Flat-Remix-Blue-Dark &>/dev/null
	qvm-copy-to-vm  $TARGET $HOME/.icons/material_cursors &>/dev/null
	qvm-copy-to-vm  $TARGET $HOME/.fonts &>/dev/null
	qvm-copy-to-vm  $TARGET $(pwd)/bin &>/dev/null
	qvm-copy-to-vm  $TARGET $(pwd)/conf &>/dev/null
	msg Running $SCRIPT script
	qvm-run -u root --pass-io $TARGET "'$TARGET_DIR/$SCRIPT'"
}

app-template(){
	local TARGET="fedora-40-app"
	local TARGET_DIR="/home/user/QubesIncoming/dom0"
	local SCRIPT="fedora-app"
	template_status $TARGET
	msg Copying require files to qube $TARGET
	qvm-copy-to-vm  $TARGET $(pwd)/$SCRIPT
	qvm-copy-to-vm  $TARGET $HOME/.themes &>/dev/null
	qvm-copy-to-vm  $TARGET $HOME/.fonts &>/dev/null
	qvm-copy-to-vm  $TARGET $HOME/.icons/Flat-Remix-Blue-Dark &>/dev/null
	qvm-copy-to-vm  $TARGET $HOME/.icons/material_cursors &>/dev/null
	qvm-copy-to-vm  $TARGET $(pwd)/bin &>/dev/null
	qvm-copy-to-vm  $TARGET $(pwd)/conf &>/dev/null
	msg Running $SCRIPT script
	qvm-run -u root --pass-io $TARGET "'$TARGET_DIR/$SCRIPT'"
}

sys-template
app-template
