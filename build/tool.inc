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
BIN_PATH = $(HOME_PATH)/bin
OUT_PATH = $(HOME_PATH)/out
INC_PATH = $(HOME_PATH)/include
SRC_PATH = $(HOME_PATH)/src

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

# version
GIT_TAG = $(shell git describe master --abbrev=0)
VER_MAJOR = $(firstword $(subst ., ,$(GIT_TAG)))
