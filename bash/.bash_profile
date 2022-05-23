#
# ~/.bash_profile
#

[[ -f ~/.bashrc ]] && . ~/.bashrc
[[ -f ~/.env ]] && . ~/.env

if [[ -z "$DISPLAY" ]] && [[ $(tty) = /dev/tty1 ]]; then
        exec startx -- -listen tcp
fi
