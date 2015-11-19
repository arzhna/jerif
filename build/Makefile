include tool.inc

TARGET_NAME = jerif
LIB_NAME = lib$(TARGET_NAME)

# SOURCES
SRCS = 	jerif_stack.c \
		jerif_check.c \
		jerif_detect.c \
		jerif_misc.c

OBJS = $(SRCS:%.c=$(OBJ_PATH)/%.o)

# Target Library
INCS = -I$(INC_PATH)
LIBS_PATH = -L$(LIB_PATH)

# FLAGS
DBG_FLAGS = -g
CFLAGS = -W -O0 $(CCFLAGS) $(OPT_FLAGS) $(DBG_FLAGS)

# STATIC LIBRARY
STATIC_LIB_NAME = $(LIB_NAME).a

# DYNAMIC LIBRARY
ifeq ($(UNAME_S),Linux)
	CFLAGS += -fPIC
	LDFLAGS += -shared
	DYNAMIC_LIB_NAME = lib$(TARGET_NAME).so
	INSTALL_LIB_NAME = $(TARGET_LIB).$(GIT_TAG)
	INSTALL_LIB_PATH = /usr/lib
	INSTALL_INC_PATH = /usr/include
else ifeq ($(UNAME_S),Darwin)
	LDFLAGS += -dynamiclib
	DYNAMIC_LIB_NAME = lib$(TARGET_NAME).dylib
	INSTALL_LIB_NAME = $(LIB_NAME).$(GIT_TAG).dylib
	INSTALL_LIB_PATH = /usr/local/lib
	INSTALL_INC_PATH = /usr/local/include
endif
LIBS = -l$(TARGET_NAME)

# Version
VERSION_FILE_NAME = jerif_ver
ifneq ("$(wildcard $(INC_PATH)/$(VERSION_FILE_NAME).h)","")
	VERSION_FILE_EXIST = y
else
	VERSION_FILE_EXIST = n
endif

# Target Sources
TARGET_SRSC = jerif.c

# Tester Target
TESTER = libjerif_test
TESTER_SRCS = jerif_test.c
TESTER_BIN_PATH = $(BIN_PATH)

.SURFFIXES : .c .o

#.PHONY: all clean

all: version $(STATIC_LIB_NAME) $(DYNAMIC_LIB_NAME) $(TESTER) $(TARGET_NAME)

version:
	@echo "==========================="
	@echo "= $(TARGET_NAME) $(GIT_TAG)"
	@echo "==========================="
ifeq ($(VERSION_FILE_EXIST),n)
	@echo "#define JERIF_VERSION \"$(GIT_TAG)\"" >> $(INC_PATH)/$(VERSION_FILE_NAME).tmp
	@$(CP) -f $(INC_PATH)/$(VERSION_FILE_NAME).tmp $(INC_PATH)/$(VERSION_FILE_NAME).h
	@$(RM) $(INC_PATH)/$(VERSION_FILE_NAME).tmp
endif

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@echo "* Compiling $@ "
	@`[ -d $(OBJ_PATH) ] || $(MKDIR) $(OBJ_PATH)`
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(STATIC_LIB_NAME): $(OBJS)
	@echo
	@echo "* Build $@ "
	@`[ -d $(LIB_PATH) ] || $(MKDIR) $(LIB_PATH)`
	@$(AR) rcsv $(LIB_PATH)/$@ $^
	@echo "  ==> Built $(LIB_PATH)/$@"
	@echo

$(DYNAMIC_LIB_NAME): $(OBJS)
	@echo "* Build $@"
	@`[ -d $(LIB_PATH) ] || $(MKDIR) $(LIB_PATH)`
	@$(CC) $(LDFLAGS) $^ -o $(LIB_PATH)/$@
	@echo "  ==> Built $(LIB_PATH)/$@"
	@echo

$(TESTER):
	@echo "* Build $@"
	@`[ -d $(TESTER_BIN_PATH) ] || $(MKDIR) $(TESTER_BIN_PATH)`
	@$(CC) -o $(TESTER_BIN_PATH)/$@ $(TESTER_PATH)/$(TESTER_SRCS) $(INCS) $(LIBS_PATH) $(LIBS)
	@echo "  ==> Built $(TESTER_BIN_PATH)/$@"
	@echo

$(TARGET_NAME):
	@echo "* Build $@"
	@`[ -d $(BIN_PATH) ] || $(MKDIR) $(BIN_PATH)`
	@$(CC) -o $(BIN_PATH)/$@ $(SRC_PATH)/$(TARGET_SRSC) $(INCS) $(LIBS_PATH) $(LIBS)
	@echo "  ==> Built $(BIN_PATH)/$@"
	@echo

clean:
	@echo "= Clean $(TARGET_NAME) "
	@$(RM) -rf $(OUT_PATH) $(OBJ_PATH) $(LIB_PATH) $(BIN_PATH) $(INC_PATH)/$(VERSION_FILE_NAME).h
	@echo

tarball: version
	@$(MAKE) -f makefile.tarball

tarball-clean:
	@$(MAKE) -f makefile.tarball clean

install:
	@echo "==========================="
	@echo "= $@ $(LIB_NAME)-$(GIT_TAG)"
	@echo "==========================="
	@-$(RM) -rf $(INSTALL_INC_PATH)/$(TARGET_NAME) $(INSTALL_LIB_PATH)/$(LIB_NAME)*
	@echo "* include ==> $(INSTALL_INC_PATH)/$(TARGET_NAME)"
	@$(CP) -r $(INC_PATH) $(INSTALL_INC_PATH)/$(TARGET_NAME)
	@echo "* $(STATIC_LIB_NAME) ==> $(INSTALL_LIB_PATH)"
	@$(CP) $(LIB_PATH)/$(STATIC_LIB_NAME) $(INSTALL_LIB_PATH)/
	@echo "* $(DYNAMIC_LIB_NAME) ==> $(INSTALL_LIB_PATH)"
	@$(CP) $(LIB_PATH)/$(DYNAMIC_LIB_NAME) $(INSTALL_LIB_PATH)/$(INSTALL_LIB_NAME)
	@$(LN) -s $(INSTALL_LIB_PATH)/$(INSTALL_LIB_NAME) $(INSTALL_LIB_PATH)/$(DYNAMIC_LIB_NAME)
	@echo "The installation of $(LIB_NAME) complete"
	@echo

uninstall:
	@echo "==========================="
	@echo "= $@ $(LIB_NAME)"
	@echo "==========================="
	@-$(RM) -rf $(INSTALL_INC_PATH)/$(TARGET_NAME) $(INSTALL_LIB_PATH)/$(LIB_NAME)*
	@echo "The uninstallation of $(LIB_NAME) complete"
	@echo
