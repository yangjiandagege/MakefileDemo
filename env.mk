CC = @gcc
CFLAGS = -Wall
DEBUG = y

ifeq ($(DEBUG), y)
CFLAGS     += -g
else
CFLAGS     += -O2
endif

BASEPATH     = $(PWD)
OBJPATH      = $(BASEPATH)/obj
DYNAMIC_LIB_PATH = $(BASEPATH)/lib/dynamic
STATIC_LIB_PATH  = $(BASEPATH)/lib/static
INCDIR       += $(BASEPATH)/inc/linklist
INCDIR       += $(BASEPATH)/inc/login
INCLUDE = $(foreach dir, $(INCDIR), -I$(dir))

export INCLUDE BASEPATH CC CFLAGS OBJPATH DYNAMIC_LIB_PATH STATIC_LIB_PATH
