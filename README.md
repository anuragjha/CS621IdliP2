# CS621Idli2 - Quality of Services

Project Setup Instructions

# ns-3 Setup
1. sudo apt-get install mercurial gcc g++ git cmake 
2. sudo apt-get python-dev python-setuptools qt5-default
3. cd && mkdir workspace && cd ~/workspace
4. hg clone http://code.nsnam.org/ns-3-allinone
5. cd ns-3-allinone/
6. ./download.py -n ns-3-dev
7. ./build.py
8. cd ns-3-dev
9. ./waf --enable-tests configure
10. ./test.py

# Repo setup to ns-3
0. cd ~/workspace/
1. git clone https://github.com/anuragjha/CS621IdliP2.git
2. sudo apt-get install rsync
3. rsync -a ~/workspace/CS621IdliP2/traffic-control/ ~/workspace/ns-3-allinone/ns-3-dev/src/traffic-control

# Repo setup for SPQ
4. cp ~/workspace/CS621IdliP2/cs621IdliP2.cc  ~/workspace/ns-3-allinone/ns-3-dev/scratch
5. cp ~/workspace/CS621IdliP2/config.xml ~/workspace/ns-3-allinone/ns-3-dev/

# Repo setup for DRR
6. cp ~/workspace/CS621IdliP2/cs621IdliP2DRR.cc  ~/workspace/ns-3-allinone/ns-3-dev/scratch
7. cp ~/workspace/CS621IdliP2/configDRR.xml ~/workspace/ns-3-allinone/ns-3-dev/ 

# Running project for SPQ
1. cd ~/workspace/ns-3-allinone/ns-3-dev/
2. ./waf configure
3. ./waf --run "cs621IdliP2 --filename=config.xml"

# Running project for DRR
1. cd ~/workspace/ns-3-allinone/ns-3-dev/
2. ./waf configure
3. ./waf --run "cs621IdliP2DRR --filename=configDRR.xml"