# !/bin/bash
#
#     █                    █                   
#     █                    █                   
#     █                    █                   
#     █▓██   ░███░  ▒███▒  █▒██▒   █▒██▒  ▓██▒ 
#     █▓ ▓█  █▒ ▒█  █▒ ░█  █▓ ▒█   ██  █ ▓█  ▓ 
#     █   █      █  █▒░    █   █   █     █░    
#     █   █  ▒████  ░███▒  █   █   █     █     
#     █   █  █▒  █     ▒█  █   █   █     █░    
#     █▓ ▓█  █░ ▓█  █░ ▒█  █   █   █     ▓█  ▓ 
#     █▓██   ▒██▒█  ▒███▒  █   █   █      ▓██▒ 
#                                                  

export VISUAL=vim
export EDITOR=vim
export BROWSER=qutebrowser
export XDG_CONFIG_HOME="$HOME/.config"
export TERM=xterm

# If not running interactively, don't do anything
[[ $- != *i* ]] && return


#-----------------------------------------------------------------------
#
#                           PROMPT
#-----------------------------------------------------------------------

#PS1="\[\033[1;31m\]\342\224\214\342\224\200\$([[ \$? != 0 ]] && echo \"[\[\033[1;31m\]\342\234\227\[\033[0;37m\]]\342\224\200\")[$(if [[ ${EUID} != 0 ]]; then echo '\[\033[0;39m\]\u\[\033[01;31m\]@\[\033[01;39m\]\h'; fi)\[\033[1;31m\]]\342\224\200[\[\033[0;39m\]\w\[\033[1;31m\]]\n\[\033[1;31m\]\342\224\224\342\224\200\342\224\200\342\225\274 \[\033[0m\]\[\e[01;31m\]\\$\[\e[0m\] "

git_branch(){
        git branch --show-current 2>/dev/null
}

PS1="\[\e[32;1m\](\[\e[34;1m\]\u\[\e[32;1m\])-(\[\e[31;1m\]\h\[\e[32;1m\])-(\[\e[32;1m\]\w\[\e[32;1m\])-(\[\[\e[37;0m\]\e[33;1m\]\e[5m\]\$(git_branch)\e[0m\]\[\e[32;1m\])\e[32;1m\]\n$ \[\e[0m\]"
#PS1="\[\e[31;1m\](\[\e[37;1m\]\u\[\e[33;1m\]@\[\e[34;1m\]\h\[\e[31;1m\])-(\[\e[30;1m\]\w\[\e[31;1m\])-(\[\[\e[37;1m\]\e[32;1m\]\e[5m\]\$(git_branch)\e[0m\]\[\e[31;1m\])\e[31;1m\]\n$ \[\e[0m\]"

#-----------------------------------------------------------------------
#                                           
#                           ALIASES
#-----------------------------------------------------------------------

if [[ -f ~/.bash_aliases ]];then
        . ~/.bash_aliases
fi

#-----------------------------------------------------------------------
#                                           
#                           FUNCTIONS
#-----------------------------------------------------------------------

if [[ -f ~/.func ]];then
        . ~/.func
fi

#-----------------------------------------------------------------------
#  
#                      COLORS FOR MAN PAGES 
#-----------------------------------------------------------------------

export LESS_TERMCAP_mb=$'\e[0;33m'
export LESS_TERMCAP_md=$'\e[0;31m'
export LESS_TERMCAP_me=$'\e[0m'
export LESS_TERMCAP_se=$'\e[0m'
export LESS_TERMCAP_so=$'\e[0;34m'
export LESS_TERMCAP_ue=$'\e[0m'
export LESS_TERMCAP_us=$'\e[0;36m'

GPG_TTY=$(tty)
export GPG_TTY

if [[ -f /usr/local/share/bash-completion/bash_completion.sh ]]; then
     source /usr/local/share/bash-completion/bash_completion.sh
fi
