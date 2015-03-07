#!/bin/sh

export PRJ_DIR=$PWD

VERSION_FILE=$PRJ_DIR/src/app/include/version.h

export AP_VERSION=`cat $VERSION_FILE | grep -w AP_VERSION | awk -F ' ' '{print $3}' | cut -c 2-12`

if [ -z $AP_VERSION ]; then
	echo "No AP_VERSION to be found, please check $VERSION_FILE?"
	exit 1
fi

echo APP version: $AP_VERSION
