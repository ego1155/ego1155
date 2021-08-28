# Decide whether the commands will be shwon or not
VERBOSE = FALSE

# Compilation flags
CC := gcc
LD := gcc
WINDRES := windres -i
CFLAGS := -lssh -lplibsys -lssl -lcrypto
RM := rm -rf
RMDIR := rm -rf
MKDIR := mkdir -p

ifeq ($(shell uname -o),Msys)

OS_NAME :=
OS_VER :=
OS_DETAILS :=Window
OS_TARGET :=win
COPY_LIBS :=copy_libs_win
ILIBSINC := -I./Sources/plibsys/plibsys/src
LLIBDIR := -L./Sources/plibsys/window
CFLAGS := $(CFLAGS) $(ILIBSINC) $(LLIBDIR) -lws2_32 -L.
PLIBSYS := ./Sources/plibsys/plibsys_Window.sh

else ifeq ($(shell lsb_release -si),Ubuntu)

OS_NAME :=$(shell lsb_release -si)
OS_VER :=$(shell lsb_release -sr)
OS_DETAILS :=$(OS_NAME)_$(OS_VER)
OS_TARGET :=lnx
COPY_LIBS :=copy_libs_lnx
ILIBSINC := -I./Sources/plibsys/plibsys/src
LLIBDIR := -L./Sources/plibsys/ubuntu
CFLAGS := $(CFLAGS) $(ILIBSINC) $(LLIBDIR) -lpthread -lm -Wl,-R./libs/
PLIBSYS := ./Sources/plibsys/plibsys_Ubuntu.sh

else ifeq ($(shell uname),Darwin)

OS_NAME :=$(shell sw_vers -productName)
OS_VER :=$(shell sw_vers -productVersion)
OS_DETAILS :=$(OS_NAME)_$(OS_VER)
OS_TARGET :=osx
COPY_LIBS :=dylibbundler_osx
ILIBSINC := -I/usr/local/include -I./Sources/plibsys/plibsys/src
LLIBDIR := -L/usr/local/opt/libssh/lib -L./Sources/plibsys/macosx
CFLAGS := $(CFLAGS) -L./Sources/plibsys/macosx $(ILIBSINC) $(LLIBDIR)
PLIBSYS := ./Sources/plibsys/plibsys_MacOsX.sh

endif

# File paths
PROJ_DIR := $(CURDIR)
TARGET := $(shell basename "$(PROJ_DIR)")
TARGET_DIR := ./Output/$(OS_DETAILS)
SRC_DIR := ./Sources
BUILD_DIR := ./Build
OBJ_DIR := $(BUILD_DIR)/Objs

# Files to be compiled
SRCS := $(wildcard $(SRC_DIR)/libPfx/*/*.c) $(wildcard $(SRC_DIR)/libPfx/*.c) $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
BUILD := $(OBJS:$(OBJ_DIR)/%.o=$(BUILD_DIR)/%)
INCLUDES = $(foreach src, $(SRCS), $(dir $(src)))

# Hide or not the calls depending of VERBOSE
ifeq ($(VERBOSE),TRUE)
    HIDE =
else
    HIDE = @
endif

ifeq ($(OS_TARGET),win)
    FAVICON_TARGET = favicon_win
	FAVICON_OBJ = $(OBJ_DIR)/favicon.o
else
    FAVICON_TARGET =
	FAVICON_OBJ =
endif

all: preHeader exec postHeader

exec: $(TARGET) clean $(COPY_LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo + CC $<
	$(HIDE)$(MKDIR) -p $(dir $@)
	$(HIDE)$(CC) -m64 -no-pie -s -c $< $(CFLAGS) -o $@
	
$(BUILD_DIR)/%: $(OBJ_DIR)/%.o
	
$(TARGET): $(BUILD) $(FAVICON_TARGET)
	$(HIDE)$(RMDIR) $(TARGET_DIR)
	@echo + LD $@
	$(HIDE)$(MKDIR) -p $(TARGET_DIR)
	$(HIDE)$(LD) -m64 -no-pie -s $(OBJS) $(FAVICON_OBJ) $(CFLAGS) -o $(TARGET_DIR)/$(TARGET)
	
favicon_win:
	$(HIDE)$(WINDRES) $(SRC_DIR)/favicon.rc -o $(OBJ_DIR)/favicon.o
	
.PHONY: all

clean:
	$(HIDE)$(RMDIR) $(BUILD_DIR)
	
copy_libs_lnx:
	$(HIDE)$(MKDIR) -p $(TARGET_DIR)/libs
	$(HIDE)ldd $(TARGET_DIR)/$(TARGET) | grep "=> /" | awk '{print $$3}' | xargs -I '{}' cp -v '{}' $(TARGET_DIR)/libs/
	cp -v $(SRC_DIR)/plibsys/ubuntu/libplibsys.so.0 $(TARGET_DIR)/libs/
		
copy_libs_win:
	$(HIDE)ldd $(TARGET_DIR)/$(TARGET) | grep "=> /mingw64" | awk '{print $$3}' | xargs -I '{}' cp -v '{}' $(TARGET_DIR)/
	cp -v $(SRC_DIR)/plibsys/window/libplibsys.dll $(TARGET_DIR)/

dylibbundler_osx:
	$(HIDE)dylibbundler -od -b -s ./Sources/plibsys/macosx -x $(TARGET_DIR)/$(TARGET) -d $(TARGET_DIR)/libs/ -p @executable_path/libs/

preHeader:
	@echo ++++++++++++++++++ $(TARGET) ++++++++++++++++++

postHeader:
	@echo ++++++++++++++++++ $(TARGET) ++++++++++++++++++

plibsys:
	$(PLIBSYS)
	
touch:
	find $(SRC_DIR) -exec touch {} \;
