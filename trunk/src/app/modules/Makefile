OBJS_SRC:=

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

MODULES_ROOT:=$(shell pwd)

SYSSRV_SRC+=$(MODULES_ROOT)/sys_server/sys_server.c

OBJS_DIR:=$(MODULES_ROOT)/objs
OBJS:=$(OBJS_DIR)/*

LDFLAGS:= -lpthread -lm

INCLUDE_DIR+=-I../../include/

CFLAGS:= -g -Wall -O2 -Werror -Wunused-function -Wunused-label -Wunused-value -Wunused-variable
CFLAGS+= $(INCLUDE_DIR)

.PHONY:all sys_server clean

all: sys_server

sys_server:
	$(CC) $(CFLAGS) -c $(SYSSRV_SRC)
	mv *.o $(OBJS_DIR)
	#install -m 755 *.o $(OBJS_DIR)

clean:
	rm -rf $(OBJS)
