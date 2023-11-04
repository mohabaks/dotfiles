#! /bin/sh
# Description: Simple script to build go tools from source
set -e
set -x

move(){
mv /go/bin/* /opt/bin/
}

ffuf(){
go install -v github.com/ffuf/ffuf/v2@latest
move
}

tomnomnom(){
git clone https://github.com/tomnomnom/gf.git \
    && cd gf && GO111MODULE=off go build -o /go/bin/gf && cd -
git clone https://github.com/tomnomnom/assetfinder.git \
    && cd assetfinder && GO111MODULE=off go build -o /go/bin/assetfinder && cd -
go install -v github.com/tomnomnom/meg@latest
go install -v github.com/tomnomnom/waybackurls@latest
go install -v github.com/tomnomnom/httprobe@latest
go install -v github.com/tomnomnom/anew@latest
go install -v github.com/tomnomnom/gron@latest
move
}

goaltdns(){
git clone https://github.com/subfinder/goaltdns.git \
    && cd goaltdns \
    && GO111MODULE=off go get -u github.com/subfinder/goaltdns
move
}

gobuster(){
go install -v github.com/OJ/gobuster/v3@latest
move
}

hebgp(){
go install -v github.com/mohabaks/hebgp@latest
move
}

gospider(){
go install -v github.com/jaeles-project/gospider@latest
move
}

hakrawler(){
go install -v github.com/hakluke/hakrawler@latest
move
}

httpx(){
go install -v github.com/projectdiscovery/httpx/cmd/httpx@latest
move 
}

metabigor(){
go install -v github.com/j3ssie/metabigor@latest
move
}

naabu(){
go install -v github.com/projectdiscovery/naabu/v2/cmd/naabu@latest
move
}

nuclei(){
go install -v github.com/projectdiscovery/nuclei/v2/cmd/nuclei@latest
move
}

shosubgo(){
go install -v github.com/incogbyte/shosubgo@latest
move
}

shuffledns(){
go install -v github.com/projectdiscovery/shuffledns/cmd/shuffledns@latest
move
}

subfinder(){
go install -v github.com/projectdiscovery/subfinder/v2/cmd/subfinder@latest
move
}

subjack(){
GO111MODULE=off go get -u github.com/haccer/subjack
move
}

awsenumerator(){
go install -v github.com/shabarkin/aws-enumerator@latest
move
}

main(){
       # Add function for tool to build
       awsenumerator
}

main
