#!/bin/bash
# build some functions
NUM_CPUS=`nproc`
echo "###############"
echo "### Using ${NUM_CPUS} cores"
SRC_DIR=$(pwd)
function fix_arch_ctl()
{
	ARCH=$(dpkg --print-architecture)
    echo "${ARCH}"
	sed '/Architecture/d' -i $1
	test ${ARCH}x == i386x && echo "Architecture: i386" >> $1
	test ${ARCH}x == armv7lx && echo "Architecture: armhf" >> $1
	test ${ARCH}x == amd64x && echo "Architecture: amd64" >> $1
	test ${ARCH}x == x86_64x && echo "Architecture: amd64" >> $1
	sed '$!N; /^\(.*\)\n\1$/!P; D' -i $1
}
function dpkg_build()
{
	# Calculate package size and update control file before packaging.
	if [ ! -e "$1" -o ! -e "$1/DEBIAN/control" ]; then exit 1; fi
	sed '/^Installed-Size/d' -i "$1/DEBIAN/control"
	size=$(du -s --apparent-size "$1" | awk '{print $1}')
	echo "Installed-Size: $size" >> "$1/DEBIAN/control"
	dpkg -b "$1" "$2"
}
# build 
cd UIDialogLib
#cmake .
make "-j${NUM_CPUS}"
# get back to root
cd ..
#sed '/Package/d' -i "${SRC_DIR}/files/DEBIAN/control"
#sed '/Depends/d' -i "${SRC_DIR}/files/DEBIAN/control"
#echo "Package: libuidialog" >> "${SRC_DIR}/files/DEBIAN/control"
#echo "Depends: icaclient" >> "${SRC_DIR}/files/DEBIAN/control"
#mkdir -p files/opt/Citrix/ICAClient/lib
#cp -ar UIDialogLib/UIDialogLib.so files/opt/Citrix/ICAClient/lib
#cp -ar Ressources files/opt/IT4S/startpage
#fix_arch_ctl "files/DEBIAN/control"
#dpkg_build files "${1}-libuidialog.deb"

# create directory to unpack the debian package 
mkdir icaclient_tmp

# check on which architecture we are running
if [ $(dpkg --print-architecture) == i386 ] ; then
    # download the package for this architecture
    wget http://it4s.backup.stockdashboard.de/debian/icaclient_13.3.0.344519_i386.deb
    dpkg-deb -x icaclient_13.3.0.344519_i386.deb icaclient_tmp
    dpkg-deb -e icaclient_13.3.0.344519_i386.deb icaclient_tmp
    
    # backup the old library
    mv icaclient_tmp/opt/Citrix/ICAClient/lib/UIDialogLib.so icaclient_tmp/opt/Citrix/ICAClient/lib/UIDialogLib.so.bak
    
    # copy newly compiled library
    cp UIDialogLib/UIDialogLib.so icaclient_tmp/opt/Citrix/ICAClient/lib/UIDialogLib.so
    dpkg-deb -b icaclient_tmp icaclient_13.3.0.344519_i386.deb
    
fi
