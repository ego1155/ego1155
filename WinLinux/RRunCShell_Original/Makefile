# Decide whether the commands will be shwon or not
VERBOSE = FALSE

# Compilation flags
CC := gcc
LD := gcc
WINDRES := windres -i

ifeq ($(shell lsb_release -si),Ubuntu)
CC := x86_64-w64-mingw32-gcc
LD := x86_64-w64-mingw32-gcc
WINDRES := x86_64-w64-mingw32-windres -i
endif

CFLAGS := -mwindows -W -Wall -Wextra -Os
RM := rm -rf
RMDIR := rm -rf
MKDIR := mkdir -p

ILIBSINC :=
LLIBDIR :=
CFLAGS := $(CFLAGS) $(ILIBSINC) $(LLIBDIR)

# File paths
PROJ_DIR := $(CURDIR)
TARGET := $(shell basename "$(PROJ_DIR)")
TARGET_DIR := ./Output
SRC_DIR := ./Sources
BUILD_DIR := ./Build
OBJ_DIR := $(BUILD_DIR)/Objs

# Files to be compiled
SRCS := $(wildcard $(SRC_DIR)/libs/*/*.c) $(wildcard $(SRC_DIR)/libs/*.c) $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
BUILD := $(OBJS:$(OBJ_DIR)/%.o=$(BUILD_DIR)/%)
INCLUDES = $(foreach src, $(SRCS), $(dir $(src)))

# Hide or not the calls depending of VERBOSE
ifeq ($(VERBOSE),TRUE)
    HIDE =
else
    HIDE = @
endif

RESOURCES_TARGET = resources_win
RESOURCES_OBJ = $(OBJ_DIR)/resources.o

all: preHeader exec postHeader

exec: $(TARGET) clean

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo + CC $<
	$(HIDE)$(MKDIR) -p $(dir $@)
	$(HIDE)$(CC) -static -m64 -no-pie -s -c $< $(CFLAGS) -o $@
	
$(BUILD_DIR)/%: $(OBJ_DIR)/%.o
	
$(TARGET): $(BUILD) $(RESOURCES_TARGET)
	$(HIDE)$(RMDIR) $(TARGET_DIR)
	@echo + LD $@
	$(HIDE)$(MKDIR) -p $(TARGET_DIR)
	$(HIDE)$(LD) -static -m64 -no-pie -s $(OBJS) $(RESOURCES_OBJ) $(CFLAGS) -o $(TARGET_DIR)/$(TARGET)
	
resources_win:
	$(HIDE)$(WINDRES) $(SRC_DIR)/resources.rc -o $(OBJ_DIR)/resources.o
	
.PHONY: all

clean:
	$(HIDE)$(RMDIR) $(BUILD_DIR)
	
preHeader:
	clear
	@echo ++++++++++++++++++ $(TARGET) ++++++++++++++++++

postHeader:
	@echo ++++++++++++++++++ $(TARGET) ++++++++++++++++++

touch:
	find $(SRC_DIR) -exec touch {} \;
