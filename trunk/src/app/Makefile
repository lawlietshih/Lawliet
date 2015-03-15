EXEC_NAME:= lawliet
BOA_EXEC_NAME:= boa
PROJECT_SRC:=
OBJS:=

CROSS_COMPILE	:= 
AS		:= $(CROSS_COMPILE)as
AR		:= $(CROSS_COMPILE)ar
CC		:= $(CROSS_COMPILE)gcc
CPP		:= $(CC) -E
LD		:= $(CROSS_COMPILE)ld
NM		:= $(CROSS_COMPILE)nm
OBJCOPY		:= $(CROSS_COMPILE)objcopy
OBJDUMP 	:= $(CROSS_COMPILE)objdump
RANLIB		:= $(CROSS_COMPILE)ranlib
READELF		:= $(CROSS_COMPILE)readelf
SIZE		:= $(CROSS_COMPILE)size
STRINGS 	:= $(CROSS_COMPILE)strings
STRIP		:= $(CROSS_COMPILE)strip

PROJECT_ROOT:=$(shell pwd)
RELEASE_DIR:=$(PROJECT_ROOT)/bin
MODULES_DIR:=$(PROJECT_ROOT)/modules
OBJECTS_DIR:=$(MODULES_DIR)/objs
THIRD_DIR:=$(PROJECT_ROOT)/third
BOA_DIR:=$(THIRD_DIR)/boa-0.94.13/src
BOA_EXE:=$(BOA_DIR)/$(BOA_EXEC_NAME)
BOA_CONFIG_DIR:=/etc/boa
BOA_WEB_DIR:=/var/www

PROJECT_SRC+=$(PROJECT_ROOT)/main.c
OBJS+=$(addprefix $(PROJECT_ROOT)/, $(addsuffix .o, $(basename $(notdir $(PROJECT_SRC)))))

LDFLAGS:= -lpthread -lm

INCLUDE_DIR:=-I$(PROJECT_ROOT)/include/

CFLAGS:= -g -Wall -O2 -Werror
CFLAGS+= $(INCLUDE_DIR)

.PHONY:all third clean kill_proc

all: $(EXEC_NAME)

third:
	make -j6 -C $(BOA_DIR)
	mv $(BOA_EXE) $(RELEASE_DIR)
	mkdir -p $(BOA_CONFIG_DIR)
	mkdir -p $(BOA_WEB_DIR)
	cp -rf $(BOA_DIR)/../boa.conf $(BOA_CONFIG_DIR)
	cp -rf $(BOA_DIR)/web/* $(BOA_WEB_DIR)

$(EXEC_NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o "$@" $(LDFLAGS)
	$(STRIP) $(EXEC_NAME)
	mv $(EXEC_NAME) $(RELEASE_DIR)

third_clean:
	rm -rf $(BOA_DIR)/*.o
	rm -rf $(BOA_DIR)/boa_indexer
	rm -rf $(RELEASE_DIR)/$(BOA_EXEC_NAME)

clean:
	rm -rf *.o
	rm -rf $(RELEASE_DIR)/$(EXEC_NAME)

kill_proc:
	-killall -9 $(BOA_EXEC_NAME)
	-killall -9 $(EXEC_NAME)
