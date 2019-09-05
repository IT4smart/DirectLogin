#!/bin/bash
# build some functions
NUM_CPUS=`nproc`
echo "###############"
echo "### Using ${NUM_CPUS} cores"
SRC_DIR=$(pwd)

# build
cd UIDialogLib
#cmake .
make "-j${NUM_CPUS}"
# get back to root
cd ..

# Find version of debian
export DEBIAN_VERSION=$(awk -F= '$1=="VERSION_ID" { print $2 ;}' /etc/os-release | tr -d \")

# check on which architecture we are running
if [ $(dpkg --print-architecture) == i386 ] ; then
    # download the package for this architecture
    wget https://mirror.it4smart.eu/src/icaclient_13.3.0.344519_i386.deb
    dpkg-deb -x icaclient_13.3.0.344519_i386.deb icaclient_tmp
    dpkg-deb -e icaclient_13.3.0.344519_i386.deb icaclient_tmp/DEBIAN

    # backup the old library
    mv icaclient_tmp/opt/Citrix/ICAClient/lib/UIDialogLib.so icaclient_tmp/opt/Citrix/ICAClient/lib/UIDialogLib.so.bak

    # copy newly compiled library
    cp UIDialogLib/UIDialogLib.so icaclient_tmp/opt/Citrix/ICAClient/lib/UIDialogLib.so

    dpkg-deb -b icaclient_tmp icaclient_13.3.0.344519_i386.deb

elif [ $(dpkg --print-architecture) == armhf ] ; then
    # create directory to unpack the debian package
    mkdir -p icaclient_13.3_tmp/DEBIAN
    mkdir -p icaclient_13.10_tmp/DEBIAN
    
    # download the package for this architecture
    wget https://mirror.it4smart.eu/src/icaclient_13.3.0.344519_armhf.deb
    wget https://mirror.it4smart.eu/src/icaclient_13.10.0.20_armhf.deb
    dpkg-deb -x icaclient_13.3.0.344519_armhf.deb icaclient_13.3_tmp
    dpkg-deb -x icaclient_13.10.0.20_armhf.deb icaclient_13.10_tmp
    dpkg-deb -e icaclient_13.3.0.344519_armhf.deb icaclient_13.3_tmp/DEBIAN
    dpkg-deb -e icaclient_13.10.0.20_armhf.deb icaclient_13.10_tmp/DEBIAN

    # backup the old library
    mv icaclient_13.3_tmp/opt/Citrix/ICAClient/lib/UIDialogLib.so icaclient_13.3_tmp/opt/Citrix/ICAClient/lib/UIDialogLib.so.bak
    mv icaclient_13.10_tmp/opt/Citrix/ICAClient/lib/UIDialogLib.so icaclient_13.10_tmp/opt/Citrix/ICAClient/lib/UIDialogLib.so.bak

    # copy newly compiled library
    cp UIDialogLib/UIDialogLib.so icaclient_13.3_tmp/opt/Citrix/ICAClient/lib/UIDialogLib.so
    cp UIDialogLib/UIDialogLib.so icaclient_13.10_tmp/opt/Citrix/ICAClient/lib/UIDialogLib.so

    dpkg-deb -b icaclient_13.3_tmp icaclient_13.3.0.344519~deb${DEBIAN_VERSION}_armhf.deb
    dpkg-deb -b icaclient_13.10_tmp icaclient_13.10.0.20~deb${DEBIAN_VERSION}_armhf.deb
elif [ $(dpkg --print-architecture) == amd64 ] ; then
    # download the package for this architecture
    wget https://mirror.it4smart.eu/src/icaclient_13.3.0.344519_amd64.deb
    dpkg-deb -x icaclient_13.3.0.344519_amd64.deb icaclient_tmp
    dpkg-deb -e icaclient_13.3.0.344519_amd64.deb icaclient_tmp/DEBIAN

    # backup the old library
    mv icaclient_tmp/opt/Citrix/ICAClient/lib/UIDialogLib.so icaclient_tmp/opt/Citrix/ICAClient/lib/UIDialogLib.so.bak

    # copy newly compiled library
    cp UIDialogLib/UIDialogLib.so icaclient_tmp/opt/Citrix/ICAClient/lib/UIDialogLib.so

    dpkg-deb -b icaclient_tmp icaclient_13.3.0.344519_amd64.deb
else
    echo -e "The architecture $(dpkg --print-architecture) is not supported"

fi
