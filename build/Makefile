include tool.inc

# LIBRARY NAME
TARGET_NAME = jerif
LIB_NAME = lib$(TARGET_NAME)
LIB_FULL_NAME = $(LIB_NAME).a
LIBS = -l$(TARGET_NAME)

# SOURCES
SRCS = 	jerif_check.c \
		jerif_stack.c

OBJS = $(SRCS:%.c=$(OBJ_PATH)/%.o)

# Target Library
INCS = -I$(INC_PATH)
LIBS_PATH = -L$(LIB_PATH)

# FLAGS
DBG_FLAGS = -g
CFLAGS = -W -O0 $(CCFLAGS) $(OPT_FLAGS) $(DBG_FLAGS )
LDFLAGS = $(EXT_INC_PATH) $(EXT_LIBS_PATH) $(EXT_LIBS)

# Target Sources
TARGET_SRSC = jerif.c

# Tester Target
TESTER = jerif_test
TESTER_PATH = $(HOME_PATH)/test
TESTER_SRCS = jerif_test.c
TESTER_BIN_PATH = $(BIN_PATH)

.SURFFIXES : .c .o

#.PHONY: all clean

all: comment $(LIB_NAME) $(TESTER) $(TARGET_NAME)

comment:
	@echo "======================"
	@echo "= Build $(TARGET_NAME)"
	@echo "======================"
	@echo

$(LIB_NAME): $(OBJS)
	@echo
	@echo "======================"
	@echo "= Linking $@ "
	@echo "======================"
	@`[ -d $(LIB_PATH) ] || $(MKDIR) $(LIB_PATH)`
	@$(AR) rcsv $(LIB_PATH)/$(LIB_FULL_NAME) $(OBJS)
	@echo

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@echo "* Compiling $@ "
	@`[ -d $(OBJ_PATH) ] || $(MKDIR) $(OBJ_PATH)`
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(TESTER):
	@echo "======================"
	@echo "= Build $@"
	@echo "======================"
	@`[ -d $(TESTER_BIN_PATH) ] || $(MKDIR) $(TESTER_BIN_PATH)`
	$(CC) -o $(TESTER_BIN_PATH)/$@ $(TESTER_PATH)/$(TESTER_SRCS) $(INCS) $(LIBS_PATH) $(LIBS) $(CFLAGS) $(LDFLAGS)
	@echo "======================"
	@echo

$(TARGET_NAME):
	@echo "======================"
	@echo "= Build $@"
	@echo "======================"
	@`[ -d $(BIN_PATH) ] || $(MKDIR) $(BIN_PATH)`
	$(CC) -o $(BIN_PATH)/$@ $(SRC_PATH)/$(TARGET_SRSC) $(INCS) $(LIBS_PATH) $(LIBS) $(CFLAGS) $(LDFLAGS)
	@echo "======================"
	@echo

clean:
	@echo "======================"
	@echo "= Clean $(LIB_NAME) "
	@echo "======================"
	$(RM) -rf $(OBJ_PATH) $(TESTER_PATH)/$(TESTER) $(LIB_PATH) $(TESTER_BIN_PATH)
