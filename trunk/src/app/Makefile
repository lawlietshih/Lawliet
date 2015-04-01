EXEC_NAME:= lawliet
LIBS_NAME:=
BOA_EXEC_NAME:= boa
PROJECT_SRC:=
LIBS_SRC:=
OBJS:=

CROSS_COMPILE	:= 
AS				:= $(CROSS_COMPILE)as
AR				:= $(CROSS_COMPILE)ar
CC				:= $(CROSS_COMPILE)gcc
CPP				:= $(CC) -E
LD				:= $(CROSS_COMPILE)ld
NM				:= $(CROSS_COMPILE)nm
OBJCOPY			:= $(CROSS_COMPILE)objcopy
OBJDUMP 		:= $(CROSS_COMPILE)objdump
RANLIB			:= $(CROSS_COMPILE)ranlib
READELF			:= $(CROSS_COMPILE)readelf
SIZE			:= $(CROSS_COMPILE)size
STRINGS 		:= $(CROSS_COMPILE)strings
STRIP			:= $(CROSS_COMPILE)strip

PROJECT_ROOT:=$(shell pwd)
RELEASE_DIR:=$(PROJECT_ROOT)/bin
MODULES_DIR:=$(PROJECT_ROOT)/modules
LIBS_DIR:=$(PROJECT_ROOT)/libs
OBJECTS_DIR:=$(MODULES_DIR)/objs
MODULES_OBJS:=$(OBJECTS_DIR)/*.o
THIRD_DIR:=$(PROJECT_ROOT)/third
BOA_DIR:=$(THIRD_DIR)/boa-0.94.13/src
BOA_EXE:=$(BOA_DIR)/$(BOA_EXEC_NAME)
BOA_CONFIG_DIR:=/etc/boa
BOA_WEB_DIR:=/var/www

PROJECT_SRC+=$(PROJECT_ROOT)/main.c
OBJS+=$(addprefix $(PROJECT_ROOT)/, $(addsuffix .o, $(basename $(notdir $(PROJECT_SRC)))))

LIBS_SRC+=$(LIBS_DIR)/libutility.so
LIBS_NAME+=$(basename $(notdir $(LIBS_SRC)))

LDFLAGS:= -lpthread -lm -l$(shell echo $(LIBS_NAME) | sed 's/lib//g')

INCLUDE_DIR:=-I$(PROJECT_ROOT)/include/

CFLAGS:= -g -Wall -O2 -Werror -Wunused-function -Wunused-label -Wunused-value -Wunused-variable
CFLAGS+= $(INCLUDE_DIR)

.PHONY:all modules modules_clean third third_clean clean kill_proc

all: $(EXEC_NAME)

third:
	make -j6 -C $(BOA_DIR)
	mv $(BOA_EXE) $(RELEASE_DIR)
	#install -m 755 $(BOA_EXE) $(RELEASE_DIR)
	sudo mkdir -p $(BOA_CONFIG_DIR)
	sudo mkdir -p $(BOA_WEB_DIR)
	sudo cp -rf $(BOA_DIR)/../boa.conf $(BOA_CONFIG_DIR)
	sudo cp -rf $(BOA_DIR)/web/* $(BOA_WEB_DIR)

$(EXEC_NAME): $(OBJS)
	make -j6 -C modules
	cd $(PROJECT_ROOT)
	$(CC) $(CFLAGS) $(OBJS) $(MODULES_OBJS) -L$(LIBS_DIR) $(LDFLAGS) -o "$@"
	$(STRIP) $(EXEC_NAME)
	mv $(EXEC_NAME) $(RELEASE_DIR)
	#install -m 755 $(EXEC_NAME) $(RELEASE_DIR)

modules:
	make -j6 -C $(MODULES_DIR) clean
	make -j6 -C $(MODULES_DIR) sys_server

modules_clean:
	make -j6 -C $(MODULES_DIR) clean

third_clean:
	rm -rf $(BOA_DIR)/*.o
	rm -rf $(BOA_DIR)/boa_indexer
	rm -rf $(RELEASE_DIR)/$(BOA_EXEC_NAME)

clean:
	rm -rf *.o
	rm -rf $(RELEASE_DIR)/$(EXEC_NAME)

kill_proc:
	#-killall -9 $(BOA_EXEC_NAME)
	-sudo killall -12 $(EXEC_NAME)
