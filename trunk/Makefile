#Makefile for Project Lawliet

TOP_DIR=$(PWD)
SRC=$(TOP_DIR)/src
APP_DIR=$(SRC)/app
UTI_DIR=$(TOP_DIR)/utility
OUT_DIR=$(TOP_DIR)/out
RELEASE_DIR=$(OUT_DIR)/release

APP_RLS_DIR=$(APP_DIR)/bin
APP_BIN=Lawliet_app_$(AP_VERSION)

all:firmware

exe:
	cd $(APP_RLS_DIR) ; \
	sudo ./lawliet
	cd $(TOP_DIR)

del:
	find . -name '*~' -exec rm -v {} \;

permit:
	find -type d -exec chmod 755 {} \;
	find -type f -exec chmod 755 {} \;

third_party:
	make -j6 -C $(APP_DIR) third_clean
	make -j6 -C $(APP_DIR) third
	cd $(TOP_DIR)

utility_libs:
	echo "make utility libs..."
	make -j6 -C $(UTI_DIR) clean
	make -j6 -C $(UTI_DIR)
	cd $(TOP_DIR)

user_app:
	echo "make AP..."
	rm -rf $(RELEASE_DIR)/*_ap_*
	make -j6 -C $(APP_DIR) clean
	make -j6 -C $(APP_DIR)
	cd $(TOP_DIR)

firmware: utility_libs user_app
	echo "make firmware..."
	cd $(RELEASE_DIR) ; \
	rm -rf *.laf ; \
	cd $(TOP_DIR)

clean_utility_libs:
	echo "clean utility libs..."
	make -j6 -C $(UTI_DIR) clean
	cd $(TOP_DIR)

clean_user_app:
	echo "clean AP..."
	make -j6 -C $(APP_DIR) clean
	cd $(TOP_DIR)
	rm -rf $(RELEASE_DIR)/*_ap_*

clean: clean_utility_libs clean_user_app
	make -j6 -C $(APP_DIR) third_clean
	rm -rf $(RELEASE_DIR)/*.laf
	cd $(TOP_DIR)
	echo "clean all"

kill_process:
	make -j6 -C $(APP_DIR) kill_proc
	cd $(TOP_DIR) 
