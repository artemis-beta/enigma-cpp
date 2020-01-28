#!/bin/bash

export BOOSTINCLUDE=/usr/local/opt/boost/include/
export DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

if [ "$DIR" != "$PWD" ]; then
	echo "ERROR This script should be run from the repository!"
	exit 1
fi

if [ ! -d "$BOOSTINCLUDE" ]; then
	echo "ERROR: Could not find boost libraries at '${BOOSTINCLUDE}'. Please amend this script to point to your boost C++ library include directory"
	exit 1
fi

rm -rf EnigmaUI.app
mkdir build
cd build
cmake ..
make
mv EnigmaUI.app ..
cd -
macdeployqt EnigmaUI.app
rm -rf build
