#ldd lawliet
#echo "/home/lawliet/Lawliet/trunk/src/app/libs" >> /etc/ld.so.conf
#ldconfig

LIBS_NAME:= libutility.so
OBJS_SRC:=

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

UTILITY_ROOT:=$(shell pwd)

UTILITY_SRC+=$(UTILITY_ROOT)/src/utility.c
UTILITY_SRC+=$(UTILITY_ROOT)/src/util_thread.c

OBJS_DIR:=$(UTILITY_ROOT)/objs
OBJS:=$(OBJS_DIR)/*

APP_DIR:=$(UTILITY_ROOT)/../src/app
LIBS_DIR:=$(APP_DIR)/libs

LDFLAGS:= -lpthread -lm

INCLUDE_DIR:=-I$(OBJS_ROOT)/include/
INCLUDE_DIR+=-I../../include/

CFLAGS:= -g -Wall -O2 -Werror -fPIC -Wunused-function -Wunused-label -Wunused-value -Wunused-variable
CFLAGS+= $(INCLUDE_DIR)

.PHONY:all clean

all: $(LIBS_NAME)

$(LIBS_NAME):
	$(CC) $(CFLAGS) -c $(UTILITY_SRC)
	mv *.o $(OBJS_DIR)
	#install -m 755 *.o $(OBJS_DIR)
	$(CC) $(CFLAGS) -shared $(OBJS) -o "$@" $(LDFLAGS)
	$(STRIP) $(LIBS_NAME)
	mv $(LIBS_NAME) $(LIBS_DIR)
	#install -m 755 $(LIBS_NAME) $(LIBS_DIR)

clean:
	rm -rf $(OBJS)
	rm -rf $(LIBS_DIR)/$(LIBS_NAME)
