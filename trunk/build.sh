#!/bin/sh

module=1

echo
echo    "********************************************************************************"
echo    "* 1. Build sys_server                                                           "
echo    "* 2. Build sys_client                                                           "
echo    "*                                                                               "
echo    "********************************************************************************"
echo -n "Please select the module to build: "
read module

case $module in 
	1)
		source ./sync_version.sh
		make clean
		make firmware
		;;
	2)
		source ./sync_version.sh
		make clean
		make firmware
		;;
	*)
		echo "Error: You have to select correct module !"
		exit
		;;
esac
