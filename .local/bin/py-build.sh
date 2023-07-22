#! /bin/sh
# Description: Simple script to build go tools from source
set -e
set -x

move(){
mv $(pwd)/dist/* /opt/bin/
}

asnlookup(){
git clone https://github.com/yassineaboukir/Asnlookup.git
cd Asnlookup
pip install -r requirements.txt
pyinstaller -F asnlookup.py
move
}

brutespray(){
git clone https://github.com/x90skysn3k/brutespray.git
cd brutespray
pip install -r requirements.txt
pyinstaller -F brutespray.py
move
}

domlink(){
git clone https://github.com/vysecurity/DomLink.git
cd DomLink
pip install -r requirements.txt
pyinstaller -F domLink.py
move
}

eyewitness(){
git clone https://github.com/RedSiege/EyeWitness.git
cd EyeWitness
pip install netaddr \
    selenium \
    fuzzywuzzy \
    pyvirtualdisplay \
    python-Levenshtein
pyinstaller --onefile Python/EyeWitness.py
move
}

impacket(){
git clone https://github.com/fortra/impacket.git
cd impacket
pip install impacket
pip install -r requirements.txt
for i in examples/*
do
    pyinstaller -F $i
done
move
}

knockpy(){
git clone https://github.com/guelfoweb/knock.git
cd knock
pip install -r requirements.txt
pyinstaller --onefile knockpy.py
move
}

linkfinder(){
git clone https://github.com/GerbenJavado/LinkFinder.git
cd LinkFinder
pip install -r requirements.txt
pyinstaller --onefile linkfinder.py
move
}

subdomainizer(){
git clone https://github.com/nsonaniya2010/SubDomainizer.git
cd SubDomainizer
pip install -r requirements.txt
pyinstaller -F SubDomainizer.py
move
}

unfurl(){
git clone https://github.com/JLospinoso/unfurl.git
cd unfurl
pyinstaller --onefile unfurl.py
move
}


main(){
       # Add function for tool to build
}

main
