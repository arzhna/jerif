# check os type
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CCFLAGS += -D_LINUX
endif
ifeq ($(UNAME_S),Darwin)
    CCFLAGS += -D_DARWIN
endif

# build path
HOME_PATH = $(shell pwd)/..
OBJ_PATH = $(HOME_PATH)/objs
LIB_PATH = $(HOME_PATH)/lib
OUT_PATH = $(HOME_PATH)/out

# build tools
MAKE = make
CC = gcc
AR = ar
RM = rm
CD = cd
CP = cp
LN = ln
MKDIR = mkdir
TARBALL = tar cvf