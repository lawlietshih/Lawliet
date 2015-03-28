#!/bin/sh

option=1

echo
echo    "********************************************************************************"
echo    "* 0. Remove all ~ files                                                         "
echo    "* 1. Change the permissions (755)                                               "
echo    "* 2. Build Lawliet                                                              "
echo    "* 3. Build Third Party (boa)                                                    "
echo    "* 4. Clean all                                                                  "
echo    "* 5. Execute Lawliet                                                            "
echo    "* 6. Killall -9 Process                                                         "
echo    "********************************************************************************"
echo -n "Please select the module to build: "
read option

case $option in
	0)
		make del
		;;
	1)
		make permit
		;;
	2)
		bash sync_version.sh
		make firmware
		;;
	3)
		make third_party
		;;
	4)
		make clean
		;;
	5)
		make exe
		;;
	6)
		make kill_process
		;;
	*)
		echo "Error: You have to select correct module !"
		exit
		;;
esac
