# Decide whether the commands will be shwon or not
VERBOSE = FALSE
VERSION = 1.0.0.0

# Compilation flags
CC := gcc
LD := gcc
WINDRES := windres -i

ifeq ($(shell lsb_release -si),Ubuntu)
CC := x86_64-w64-mingw32-gcc
LD := x86_64-w64-mingw32-gcc
WINDRES := x86_64-w64-mingw32-windres -i
endif

CFLAGS_ROCKSDB := -lrocksdb
#-DMG_ENABLE_IPV6=1
CFLAGS_MONGOOSE := -DMG_ENABLE_LINES=0 -DMG_ENABLE_DIRLIST=0 -DMG_ENABLE_LOG=0 -DMG_ENABLE_OPENSSL=1 -DMG_ENABLE_PACKED_FS=1 -lssl -lcrypto -lpthread -lWs2_32 -lwsock32
CFLAGS := -mwindows -W -Wall -Wextra -Os $(CFLAGS_MONGOOSE) $(CFLAGS_ROCKSDB)
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
FILES_TO_EMBED ?= $(wildcard web_root/cert/*.pem) $(wildcard web_root/*.js) $(wildcard web_root/*.css) $(wildcard web_root/*.html) $(wildcard web_root/images/*.png)

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

exec: pack fixed $(TARGET) clean copy_extra

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

copy_extra:
	$(HIDE)cp -f $(SRC_DIR)/cert/server.pem web_root/cert/
	$(HIDE)cp -f $(SRC_DIR)/cert/ca.pem web_root/cert/

cert:
	$(HIDE)./$(SRC_DIR)/cert/selfcert.sh

fixed:
	$(HIDE)sed -i 's/Mongoose v.%s/RRunCShell v.%s/g' $(SRC_DIR)/libs/mongoose/mongoose.c
	$(HIDE)sed -i '/#define MG_VERSION/c\#define MG_VERSION "'$(VERSION)'"' $(SRC_DIR)/libs/mongoose/mongoose.h
	$(HIDE)sed -i 's/\/web_root\//\//g' $(SRC_DIR)/libs/packed_fs/packed_fs.c
	
pack:
	@echo + CC $(SRC_DIR)/pack/pack.c
	$(HIDE)$(CC) -static -m64 -no-pie -s $(SRC_DIR)/pack/pack.c -o $(SRC_DIR)/pack/pack
	$(HIDE)./$(SRC_DIR)/pack/pack $(FILES_TO_EMBED) > $(SRC_DIR)/libs/packed_fs/packed_fs.c
	$(HIDE)$(RM) $(SRC_DIR)/pack/pack
	$(HIDE)sed -i '1,2d' $(SRC_DIR)/libs/packed_fs/packed_fs.c
	$(HIDE)sed -i 's/#include <time.h>/#include "packed_fs.h"/g' $(SRC_DIR)/libs/packed_fs/packed_fs.c