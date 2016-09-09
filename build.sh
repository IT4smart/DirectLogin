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

# create directory to unpack the debian package 
mkdir -p icaclient_tmp/DEBIAN

# check on which architecture we are running
if [ $(dpkg --print-architecture) == i386 ] ; then
    # download the package for this architecture
    wget http://it4s.backup.stockdashboard.de/src/icaclient_13.3.0.344519_i386.deb
    dpkg-deb -x icaclient_13.3.0.344519_i386.deb icaclient_tmp
    dpkg-deb -e icaclient_13.3.0.344519_i386.deb icaclient_tmp/DEBIAN
    
    # backup the old library
    mv icaclient_tmp/opt/Citrix/ICAClient/lib/UIDialogLib.so icaclient_tmp/opt/Citrix/ICAClient/lib/UIDialogLib.so.bak
    
    # copy newly compiled library
    cp UIDialogLib/UIDialogLib.so icaclient_tmp/opt/Citrix/ICAClient/lib/UIDialogLib.so

    dpkg-deb -b icaclient_tmp icaclient_13.3.0.344519_i386.deb
    
elif [ $(dpkg --print-architecture) == armv7 ] ; then
    # download the package for this architecture
    wget http://it4s.backup.stockdashboard.de/src/icaclient_13.3.0.344519_armhf.deb
    dpkg-deb -x icaclient_13.3.0.344519_armhf.deb icaclient_tmp
    dpkg-deb -e icaclient_13.3.0.344519_armhf.deb icaclient_tmp/DEBIAN
    
    # backup the old library
    mv icaclient_tmp/opt/Citrix/ICAClient/lib/UIDialogLib.so icaclient_tmp/opt/Citrix/ICAClient/lib/UIDialogLib.so.bak
    
    # copy newly compiled library
    cp UIDialogLib/UIDialogLib.so icaclient_tmp/opt/Citrix/ICAClient/lib/UIDialogLib.so

    dpkg-deb -b icaclient_tmp icaclient_13.3.0.344519_armhf.deb
else
    echo -e "The architecture $(dpkg --print-architecture) is not supported"
    
fi
