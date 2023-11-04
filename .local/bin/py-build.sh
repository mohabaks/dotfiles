#! /bin/sh
# Description: Simple script to build python tools from source with the help
#              of docker
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
pip install netaddr selenium fuzzywuzzy pyvirtualdisplay python-Levenshtein
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

certipy(){
git clone https://github.com/ly4k/Certipy.git
cd Certipy
sed -i 's/\\\\/\//' Certipy.spec
pip install impacket requests requests_ntlm asn1crypto
pyinstaller Certipy.spec
move
}

passthecert(){
git clone https://github.com/AlmondOffSec/PassTheCert.git
cd PassTheCert
pip install impacket requests requests_ntlm
pyinstaller -F Python/passthecert.py
move
}

gitdumper(){
git clone https://github.com/arthaud/git-dumper.git
cd git-dumper
pip install -r requirements.txt
pyinstaller -F git_dumper.py
move
}

s3accountsearch(){
git clone https://github.com/WeAreCloudar/s3-account-search.git
cd s3-account-search
pip install boto3 aws-assume-role-lib
pyinstaller -F s3_account_search/cli.py
cp $(pwd)/dist/cli /opt/bin/s3-account-search
}

jwt_tool(){
git clone https://github.com/ticarpi/jwt_tool.git
cd jwt_tool
pip install -r requirements.txt
pyinstaller -F jwt_tool.py
move
}

jwt_tool(){
git clone https://github.com/ticarpi/jwt_tool.git
cd jwt_tool
pip install -r requirements.txt
pyinstaller -F jwt_tool.py
move
}

pacu(){
git clone https://github.com/RhinoSecurityLabs/pacu.git
cd pacu
pip install -r requirements.txt
pyinstaller --hidden-import pacu -F cli.py
cp $(pwd)/dist/cli /opt/bin/pacu
}

# list of binary to build
pacu
