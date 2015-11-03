include tool.inc

# PATH
INC_PATH = $(HOME_PATH)/src
SRC_PATH = $(HOME_PATH)/src

# LIBRARY NAME
LIB_NAME = jerif
LIB_FULL_NAME = lib$(LIB_NAME).a
LIBS = -l$(LIB_NAME)

# SOURCES
SRCS = 	jerif_stack.c

OBJS = $(SRCS:%.c=$(OBJ_PATH)/%.o)

# Target Library
INCS = -I$(INC_PATH)
LIBS_PATH = -L$(LIB_PATH)

# FLAGS
DBG_FLAGS = -g
CFLAGS = -W -O0 $(CCFLAGS) $(OPT_FLAGS) $(DBG_FLAGS )
LDFLAGS = $(EXT_INC_PATH) $(EXT_LIBS_PATH) $(EXT_LIBS)

# test target
EXAMPLE = jerif_test
EXAMPLE_PATH = $(HOME_PATH)/example
EXAMPLE_SRCS = jerif_test.c
EXAMPLE_BIN_PATH = $(HOME_PATH)/bin

.SURFFIXES : .c .o

#.PHONY: all clean

all: comment $(LIB_NAME) $(EXAMPLE)

comment:
	@echo "======================"
	@echo "= Build $(LIB_NAME)"
	@echo "======================"
	@echo

$(LIB_NAME): $(OBJS)
	@echo
	@echo "======================"
	@echo "= Linking $(LIB_FULL_NAME) "
	@echo "======================"
	@`[ -d $(LIB_PATH) ] || $(MKDIR) $(LIB_PATH)`
	@$(AR) rcsv $(LIB_PATH)/$(LIB_FULL_NAME) $(OBJS)
	@echo

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@echo "* Compiling $@ "
	@`[ -d $(OBJ_PATH) ] || $(MKDIR) $(OBJ_PATH)`
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

$(EXAMPLE):
	@echo "======================"
	@echo "= Build $@"
	@echo "======================"
	@`[ -d $(EXAMPLE_BIN_PATH) ] || $(MKDIR) $(EXAMPLE_BIN_PATH)`
	$(CC) -o $(EXAMPLE_BIN_PATH)/$@ $(EXAMPLE_PATH)/$(EXAMPLE_SRCS) $(INCS) $(LIBS_PATH) $(LIBS) $(CFLAGS) $(LDFLAGS)
	@echo "======================"
	@echo

clean:
	@echo "======================"
	@echo "= Clean $(LIB_NAME) "
	@echo "======================"
	$(RM) -rf $(OBJ_PATH) $(EXAMPLE_PATH)/$(EXAMPLE) $(LIB_PATH) $(EXAMPLE_BIN_PATH)
