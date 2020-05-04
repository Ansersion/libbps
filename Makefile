COMPILE_OPTS =		$(INCLUDES) -I. -c
COMPILE_OPTS += -g
CC = cc

ALL = 
SRC =
OBJ =
INCLUDES =
MACRO 	=
LINK_OPTS =		
LIBRARY_SHARE_LINK =
SHARE_LINK_OPTS =

INCLUDES += -Iinc

SRC_DIR = src


MACRO 	+= -DBPS_CPU64

CFLAGS +=		-Wall
CFLAGS +=		$(COMPILE_OPTS) 
CFLAGS +=		$(MACRO) 

LIBRARY_LINK =		ar ru

SRC 	+= ${wildcard $(SRC_DIR)/*.c}
OBJ 	+= ${patsubst %.c, %.o, $(SRC)}

TARGET_STATIC_LIB = libbps.a
TARGET_SHARE_LIB = libbps.so

ALL += $(TARGET_STATIC_LIB) 
#ALL += $(TARGET_SHARE_LIB)

all: $(ALL)

$(TARGET_STATIC_LIB): $(OBJ) 
	$(LIBRARY_LINK) $(LINK_OPTS) $@ $(OBJ)
	cscope -Rbq

$(TARGET_SHARE_LIB): $(OBJ) 
	$(LIBRARY_SHARE_LINK) $@ $(LIBRARY_SHARE_LINK_OPTS) $(OBJ)
	cscope -Rbq

$(OBJ):%.o:%.c
	$(CC) $(CFLAGS) $< -o $@ -MMD -MF $*.d -MP

clean:
	-rm -rf $(OBJ) $(ALL) core *.core *~ inc/*~ src/*.d cscope.*

install:
	@echo "install not supported\n"

##### Any additional, platform-specific rules come here:
