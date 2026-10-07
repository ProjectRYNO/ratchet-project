.PHONY: dump config split iso FORCE elf
.DEFAULT_GOAL := elf

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
CONFIG = $(CONTAINER_ROOT)/$(GAME)/config
TOOLS = $(CONTAINER_ROOT)/tools


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

CROSS = /usr/bin/mips-linux-gnu
WRENCH_DIR = /opt/wrench
PS2DEV_DIR ?= /opt/ps2dev
EEGCC = $(PS2DEV_DIR)/ee/bin/ee-gcc
EEGXX = $(PS2DEV_DIR)/ee/bin/ee-g++

# Collect sources
SRC_C   = $(shell $(FIND) code -type f -name '*.c')
SRC_S = $(shell $(FIND) code -type f -name '*.s' | grep -v "asm/matchings\|asm/nonmatchings\|asm/build/core.bss.data.s\|asm/build/bss.data.s\|asm/build/cod/001A5180.bss.s\|asm/build/bss/00221080.bss.s")
SRC_CPP = $(shell $(FIND) code -type f -name '*.cpp')
SRC_BIN = $(shell [ -d assets ] && $(FIND) assets -type f -name '*.bin' || true)
INCLUDE = -Icode/include

BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/code
TARGET = $(BUILD_DIR)/boot_elf.elf
ELF_ASSET_SRC = ../../$(GAME)/$(TARGET)
ELF_ENTRYPOINT = ENTRYPOINT

OBJS = $(SRC_S:code/%.s=$(OBJ_DIR)/%.o) \
    	$(SRC_CPP:code/%.cpp=$(OBJ_DIR)/%.o) \
    	$(SRC_C:code/%.c=$(OBJ_DIR)/%.o) \
		$(SRC_BIN:assets/%.bin=$(BUILD_DIR)/assets/%.o)

ALLOW_NONMATCHING ?= 0
COMMON_COMPILE_FLAGS = -G8 -O2 -ffast-math -fno-exceptions -Wa,-EL -Wa,-Icode/include -Wa,-no-pad-sections
# Keep the recovered EE sound functions inside their original address slots.
# The only division has a constant, nonzero divisor (741).
$(OBJ_DIR)/989snd/ee/989snd.o: COMMON_COMPILE_FLAGS += -Os -fno-schedule-insns -fno-reorder-blocks -mno-check-zero-division
# Retail iksemel accessors occupy 20-byte slots at four-byte boundaries.
$(OBJ_DIR)/iksemel/src/iks.o: COMMON_COMPILE_FLAGS += -falign-functions=4
ifeq ($(ALLOW_NONMATCHING),1)
	COMMON_COMPILE_FLAGS += -DALLOW_NONMATCHING
endif

elf: $(TARGET)

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

rom: ps2dev
	@echo "[Project RYNO] Extracting ROM only..."
	$(PYTHON) $(TOOLS)/elf_to_rom.py $(ASSETS)/boot_elf.elf $(CONFIG)/$(BASENAME).yaml $(CONFIG)/$(BASENAME).rom

split:
	$(PYTHON) $(TOOLS)/split_dl.py $(CONFIG)/$(BASENAME).yaml

iso:
	@$(MKDIR) -p $(BUILD_DIR)
	@rm -f $(BUILD_DIR)/new_$(GAME).iso
	@sed -i 's|src: ".*boot_elf\.elf"|src: "$(ELF_ASSET_SRC)"|' $(ASSETS)/build.asset
	$(WRENCH_DIR)/wrenchbuild pack $(ASSETS) $(WRENCH_DIR)/overlay -a $(WRENCH_ID) -o $(BUILD_DIR)/new_$(GAME).iso -h release --flusher-thread-hack

# Clean all but .rom for quick rebuild
clean:
	rm -rf build
	rm -rf code/asm
	rm -rf include
	rm -rf cache
	rm -rf config/$(BASENAME).d
	rm -rf config/$(BASENAME).ld

# start from scratch
full-clean: clean
	rm -rf config/$(BASENAME).rom
	
$(TARGET): $(OBJS) $(CONFIG)/$(BASENAME).ld $(CONFIG)/decompiled_functions.yaml $(TOOLS)/gen_matching_symbols.py
	@$(MKDIR) -p $(dir $@)
	@$(PYTHON) $(TOOLS)/gen_matching_symbols.py --decompiled $(CONFIG)/decompiled_functions.yaml $(CONFIG)/symbols_core.text.txt code/asm/matchings code/asm/nonmatchings > $(BUILD_DIR)/matching_symbols_auto.txt
	$(CROSS)-strip -x -N dummy-symbol-name $(OBJS)
	$(CROSS)-ld -EL -G0 -z muldefs -z max-page-size=0x1000 --no-warn-mismatch --no-check-sections --defsym=_gp=0x22597F -e $(ELF_ENTRYPOINT) -T $(BUILD_DIR)/undefined_funcs_auto.txt -T $(BUILD_DIR)/undefined_syms_auto.txt -T $(BUILD_DIR)/matching_symbols_auto.txt -T $(CONFIG)/$(BASENAME).ld -Map build/$(BASENAME).map $(OBJS) -o $@
	$(PYTHON) $(TOOLS)/patch_elf_runtime_headers.py $@

$(OBJ_DIR)/%.o: code/%.s
	@$(MKDIR) -p $(dir $@)
	$(PYTHON) $(TOOLS)/asm_preprocess.py $< | $(CROSS)-as $(INCLUDE) -EL -no-pad-sections -march=5900 -mabi=eabi - -o $@

$(OBJ_DIR)/%.o: code/%.c
	@$(MKDIR) -p $(dir $@)
	$(EEGCC) -c $(COMMON_COMPILE_FLAGS) $(INCLUDE) $< -o $@

$(OBJ_DIR)/%.o: code/%.cpp
	@$(MKDIR) -p $(dir $@)
	$(EEGXX) -c $(COMMON_COMPILE_FLAGS) $(INCLUDE) $< -o $@

$(BUILD_DIR)/assets/%.o: assets/%.bin
	@$(MKDIR) -p $(dir $@)
	$(CROSS)-objcopy -I binary -O elf32-tradlittlemips -B mips $< $@
