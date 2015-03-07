EXEC_NAME:= lawliet
OBJS:= main.o

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
RELEASE_DIR:=$(PROJECT_ROOT)/bin/

INCLUDE_DIR:=-I$(PROJECT_ROOT)/include/

CFLAGS:= -g -Wall -O2 -Werror
CFLAGS+= $(INCLUDE_DIR)

all: $(EXEC_NAME)

$(EXEC_NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o "$@"
	$(STRIP) $(EXEC_NAME)
	mv $(EXEC_NAME) $(RELEASE_DIR)

clean:
	rm -rf $(EXEC_NAME) *.o
