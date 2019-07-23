COMPILE_OPTS =		$(INCLUDES) -I. -c -g -Wall
# COMPILE_OPTS += -O2
CC = cc

ALL = 
SRC =
OBJ =
INCLUDES =
MACRO 	=
LINK_OPTS =		
LIBRARY_SHARE_LINK = ar
LIBRARY_SHARE_LINK_OPTS = cr

INCLUDES += -Iinc

SRC_DIR = src


# BP_CPU64/BP_CPU32/BP_CPU16/BP_CPU8
MACRO 	+= -DBP_CPU64
MACRO 	+= -DBP_USE_STD
MACRO 	+= -DDEBUG
MACRO 	+= -DBP_MEM_DYN

CFLAGS +=		$(COMPILE_OPTS) 
CFLAGS +=		$(MACRO) 

LIBRARY_LINK =		ar cr 

SRC 	+= ${wildcard $(SRC_DIR)/*.c}
OBJ 	+= ${patsubst %.c, %.o, $(SRC)}

TARGET_STATIC_LIB = libbps.a
TARGET_SHARE_LIB = libbps.so

ALL += $(TARGET_STATIC_LIB) 
ALL += $(TARGET_SHARE_LIB)

all: $(ALL)

$(TARGET_STATIC_LIB): $(OBJ) 
	$(LIBRARY_LINK) $(LINK_OPTS) $@ $(OBJ)
	ctags -R --exclude=.git --exclude=log *
	cscope -Rbq

$(TARGET_SHARE_LIB): $(OBJ) 
	$(LIBRARY_SHARE_LINK) $(LIBRARY_SHARE_LINK_OPTS) $@ $(OBJ)
#   ctags -R --exclude=.git --exclude=log *
#	cscope -Rbq

$(OBJ):%.o:%.c
	$(CC) $(CFLAGS) $< -o $@ -MMD -MF $*.d -MP

clean:
	-rm -rf $(OBJ) $(ALL) core *.core *~ inc/*~ src/*.d cscope.*

install:
	@echo "install not supported\n"

##### Any additional, platform-specific rules come here:
