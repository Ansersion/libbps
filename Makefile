##################################################################
# Makefile for x86_64 Linux/OSX platform to debug the library.
# Use local gcc compiler with full debug info in object files
##################################################################

COMPILE_OPTS =		$(INCLUDES) -I. -c
COMPILE_OPTS += -g
COMPILE_OPTS += -fPIC
CC = cc

ALL = 
SRC =
OBJ =
INCLUDES =
MACRO 	= -DBPS_CPU64
LINK_OPTS =		
LIBRARY_SHARE_LINK = $(CC)
SHARE_LINK_OPTS = -shared
SHARE_LINK_OPTS += -fPIC

INCLUDES += -Iinc

SRC_DIR = src


CFLAGS +=		-Wall
CFLAGS +=		-Wundef
CFLAGS +=		-Wpointer-arith
CFLAGS +=		$(COMPILE_OPTS) 
CFLAGS +=		$(MACRO) 

LIBRARY_LINK =		ar ru

SRC 	+= ${wildcard $(SRC_DIR)/*.c}
OBJ 	+= ${patsubst %.c, %.o, $(SRC)}

TARGET_STATIC_LIB = libbps.a
TARGET_SHARE_LIB = libbps.so

ALL += $(TARGET_STATIC_LIB) 
ALL += $(TARGET_SHARE_LIB)

all: $(ALL)

$(TARGET_STATIC_LIB): $(OBJ) 
	$(LIBRARY_LINK) $(LINK_OPTS) $@ $(OBJ)
	# cscope: for vim editor searching
	# cscope -Rbq

$(TARGET_SHARE_LIB): $(OBJ) 
	$(LIBRARY_SHARE_LINK) $(SHARE_LINK_OPTS) -o $@ $(OBJ)
	# cscope: for vim editor searching
	# cscope -Rbq

$(OBJ):%.o:%.c
	$(CC) $(CFLAGS) $< -o $@ -MMD -MF $*.d -MP

clean:
	-rm -rf $(OBJ) $(ALL) core *.core *~ inc/*~ src/*.d cscope.*

install:
	@echo "install not supported\n"

##### Any additional, platform-specific rules come here:
