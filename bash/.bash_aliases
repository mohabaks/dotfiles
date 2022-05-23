alias sudo="doas"

# SSH
. $HOME/.ss

# commands
alias ls='ls --color=auto'
alias dir='dir --color=auto'
alias grep='grep --color=auto'
alias fgrep='fgrep --color=auto'
alias egrep='egrep --color=auto'
alias diff='diff --color=auto'
alias ip='ip --color=auto'
alias ll='ls -l'
alias la='ls -A'
alias l='ls -CF'

# Misc
alias mypubip="curl https://ipinfo.io/ip"
alias gitcmhash="git log -n 1 | head -n 1 | sed -e 's/^commit //' | head -c 8"
