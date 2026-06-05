.PHONY: all dump config split iso clean

SHELL := /bin/bash
export PATH := /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:$(PATH)

# Setup needed paths
PYTHON := /usr/bin/python3
MKDIR := /usr/bin/mkdir
FIND := /usr/bin/find

# Set game folder names
FOLDER_RAC = rac
FOLDER_GC = gc
FOLDER_UYA = uya
FOLDER_DL = dl

# Get game path and setup relative paths
CONTAINER_ROOT = /ProjectRYNO
GAME := $(notdir $(CURDIR))
ASSETS = $(CONTAINER_ROOT)/assets/$(GAME)
CURRENT_GAME = $(CONTAINER_ROOT)/$(GAME)
CONFIG = $(CONTAINER_ROOT)/$(GAME)/config
TOOLS = $(CONTAINER_ROOT)/tools
REQUIREMENTS = $(CONTAINER_ROOT)/requirements.txt


ifeq ($(GAME),$(FOLDER_RAC))
	BASENAME = SCUS_971.99
	WRENCH_ID = rac
else ifeq ($(GAME),$(FOLDER_GC))
	BASENAME = SCUS_972.68
	WRENCH_ID = gc
else ifeq ($(GAME),$(FOLDER_UYA))
	BASENAME = SCUS_973.53
	WRENCH_ID = uya
else ifeq ($(GAME),$(FOLDER_DL))
    BASENAME = SCUS_974.65
	WRENCH_ID = dl
else
    $(error Unknown game directory: $(GAME). Expected d$(FOLDER_RAC), $(FOLDER_GC), $(FOLDER_UYA), or $(FOLDER_DL))
endif

ifeq ($(OS),Windows_NT)
	OS_ID := Windows
	PATH_SEP := \\
	COPY := copy
	DELETE := del
	DELETEFLAGS := /s /q
else
	OS_ID := $(shell uname 2>/dev/null || echo Unknown)
	PATH_SEP := /
	COPY := cp
	DELETE := rm
	DELETEFLAGS := -rf
endif

WINE32 := /usr/lib/wine/wine
WINE64 := /usr/lib/wine/wine64
EEGCC = $(WINE32) tools/cc/bin/ee-gcc.exe
CROSS = /usr/bin/mips-linux-gnu
WRENCH_DIR = /opt/wrench
WRENCHBUILD = /usr/lib/wine/wine64 /opt/wrench
PS2DEV_DIR = /opt/ps2dev
PS2DEV_OBJCOPY = $(PS2DEV_DIR)/ee/bin/ee-objcopy
PS2DEV_READELF = $(PS2DEV_DIR)/ee/bin/ee-readelf

# -include userconfig.mk

# Collect sources
SRC_C   = $(shell $(FIND) code -type f -name '*.c')
SRC_S   = $(shell $(FIND) code -type f -name '*.s' | grep -v "asm/matchings\|asm/nonmatchings")
SRC_CPP = $(shell $(FIND) code -type f -name '*.cpp')
INCLUDE = -Icode/include -Itools/cc/lib/gcc-lib/ee/2.95.2/include

BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/code
TARGET = $(BUILD_DIR)/boot_elf.elf

OBJS = $(SRC_S:code/%.s=$(OBJ_DIR)/%.o) \
       $(SRC_CPP:code/%.cpp=$(OBJ_DIR)/%.o) \
       $(SRC_C:code/%.c=$(OBJ_DIR)/%.o)

PRODG_DIR = $(TOOLS)/cc

COMMON_COMPILE_FLAGS = -G8 -O2 -ffast-math -fno-exceptions -Wa,-EL -Wa,-Icode/include -DALLOW_NONMATCHING

# EXTRA WRENCH commands:
#     /bin/wrenchbuild unpack_wads ~/ps2/ratchet-dl.iso -o /mnt/ramdisk/ -s
#     /bin/wrenchbuild pack /mnt/ramdisk/dl_sces_532_85/ -a dl -o ~/wrench/builds/build.iso -h release

all: $(TARGET)

ps2dev:
	@if [ ! -f "$(PS2DEV_DIR)/ee/bin/ee-gcc" ]; then \
		echo "[Project RYNO] Downloading ps2dev v1.2.0..."; \
		curl -L -o /tmp/ps2dev.tar.gz https://github.com/ps2dev/ps2dev/releases/download/v1.2.0/ps2dev-ubuntu-latest.tar.gz && \
		$(MKDIR) -p $(PS2DEV_DIR) && \
		tar -xzf /tmp/ps2dev.tar.gz -C $(PS2DEV_DIR) --strip-components=1 && \
		rm /tmp/ps2dev.tar.gz && \
		echo "[Project RYNO] ps2dev installed."; \
	fi

dump:
ifndef iso
	$(error ISO is not set. Usage: make dump iso=/path/to/your/game.iso or ISO=D:\path\to\your\game.iso)
endif
	$(WRENCH_DIR)/wrenchbuild unpack "$(shell /usr/bin/python3 $(TOOLS)/normalize_path.py "$(iso)")" -o $(ASSETS)
	@if [ -f "$(ASSETS)/build.asset" ]; then \
		echo "[Project RYNO] Fixing build.asset ELF path..."; \
		sed -i 's|src: "boot_elf.elf"|src: "$(CONTAINER_ROOT)/$(GAME)/build/boot_elf.elf"|' $(ASSETS)/build.asset; \
	fi

rom: ps2dev
	@echo "[Project RYNO] Extracting ROM only..."
	$(PS2DEV_OBJCOPY) -O binary $(ASSETS)/boot_elf.elf $(CONFIG)/$(BASENAME).rom

split:
	$(PYTHON) -m splat split $(CONFIG)/$(BASENAME).yaml --disassemble-all

iso:
	$(WRENCH_DIR)/wrenchbuild pack $(ASSETS) $(WRENCH_DIR)/overlay -a $(WRENCH_ID) -o build/new_$(GAME).iso -h release --flusher-thread-hack

# Clean all but .rom for quick rebuild
clean:
	rm -rf build
	rm -rf code/asm
	rm -rf assets
	rm -rf include
	rm -rf cache
	rm -rf config/$(BASENAME).d
	rm -rf config/$(BASENAME).ld

# start from scratch
full-clean: clean
	rm -rf config/$(BASENAME).rom
	
$(TARGET): $(OBJS)
	@$(MKDIR) -p $(dir $@)
	$(CROSS)-strip $(OBJS) -N dummy-symbol-name
	$(CROSS)-ld -EL -T $(BUILD_DIR)/undefined_funcs_auto.txt -T $(BUILD_DIR)/undefined_syms_auto.txt -T $(CONFIG)/$(BASENAME).ld -Map build/$(BASENAME).ld $(OBJS) -o $@
	$(CROSS)-objcopy $(TARGET) build/boot_elf.elf -O binary

$(OBJ_DIR)/%.o: code/%.s
	@$(MKDIR) -p $(dir $@)
	$(CROSS)-as $(INCLUDE) -EL -no-pad-sections -march=5900 -mabi=eabi $< -o $@

$(OBJ_DIR)/%.o: code/%.c
	@$(MKDIR) -p $(dir $@)
	$(EEGCC) -c $(COMMON_COMPILE_FLAGS) $(INCLUDE) -B$(PRODG_DIR)/lib/gcc-lib/ee/2.95.2/ $< -o $@

$(OBJ_DIR)/%.o: code/%.cpp
	@$(MKDIR) -p $(dir $@)
	$(EEGCC) -v -c -x c++ $(COMMON_COMPILE_FLAGS) $(INCLUDE) -B$(PRODG_DIR)/lib/gcc-lib/ee/2.95.2/ $< -o $@
