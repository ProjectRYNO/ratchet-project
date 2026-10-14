.PHONY: dump config split iso FORCE elf ps2dev ee-gcc296
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
else ifeq ($(GAME),$(FOLDER_GC))
	BASENAME = SCUS_972.68
else ifeq ($(GAME),$(FOLDER_UYA))
	BASENAME = SCUS_973.53
else ifeq ($(GAME),$(FOLDER_DL))
    BASENAME = SCUS_974.65
else
    $(error Unknown game directory: $(GAME). Expected d$(FOLDER_RAC), $(FOLDER_GC), $(FOLDER_UYA), or $(FOLDER_DL))
endif

CROSS = /usr/bin/mips-linux-gnu
RATCHET_CLI ?= /opt/ratchet-ps2/ratchet-ps2
CLI_CONFIG ?= $(ASSETS)/config.ini
PS2DEV_DIR ?= /opt/ps2dev
EEGCC = $(PS2DEV_DIR)/ee/bin/ee-gcc
EEGXX = $(PS2DEV_DIR)/ee/bin/ee-g++
# SVO3 and iksemel are Sony middleware built with SCE ee-gcc 2.96 (see DOCS/libraries/SVO3_TAIL_CALL_BLOCKERS.md).
# Its 32-bit binaries need the stat shim on Docker Desktop bind mounts.
EEGCC296_DIR ?= /opt/ee-gcc2.96
EEGCC296_URL = https://github.com/decompme/compilers/releases/download/compilers/ee-gcc2.96.tar.xz
EEGCC296 = LD_PRELOAD=$(EEGCC296_DIR)/ee296_statshim.so $(EEGCC296_DIR)/bin/ee-gcc
EEGXX296 = LD_PRELOAD=$(EEGCC296_DIR)/ee296_statshim.so $(EEGCC296_DIR)/bin/ee-g++
EEAS296 = LD_PRELOAD=$(EEGCC296_DIR)/ee296_statshim.so $(EEGCC296_DIR)/ee/bin/as

# Collect sources
SRC_C   = $(shell $(FIND) code -type f -name '*.c')
SRC_S = $(shell $(FIND) code -type f -name '*.s' | grep -v "asm/matchings\|asm/nonmatchings\|asm/build/core.bss.data.s\|asm/build/bss.data.s\|asm/build/cod/001A5180.bss.s\|asm/build/bss/00221080.bss.s")
SRC_CPP = $(shell $(FIND) code -type f -name '*.cpp')
SRC_BIN = $(shell [ -d assets ] && $(FIND) assets -type f -name '*.bin' || true)
INCLUDE = -Icode/include

BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/code
TARGET = $(BUILD_DIR)/boot_elf.elf
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
ifeq ($(ALLOW_NONMATCHING),1)
	COMMON_COMPILE_FLAGS += -DALLOW_NONMATCHING
endif

# Flags chosen by measured byte matches across SVO3 (see SVO3_TAIL_CALL_BLOCKERS.md).
# 2.96 has no compiler headers of its own; newlib and the generic builtin headers are shared.
SVO3_COMPILE_FLAGS = -G0 -Os -fno-exceptions -mno-split-addresses -falign-functions=4 -falign-loops=1 -falign-jumps=1 -falign-labels=1 \
	-isystem $(PS2DEV_DIR)/ee/ee/include -isystem $(PS2DEV_DIR)/ee/lib/gcc-lib/ee/3.2.3/include
ifeq ($(ALLOW_NONMATCHING),1)
	SVO3_COMPILE_FLAGS += -DALLOW_NONMATCHING
endif
# Sony's bundled assembler (2.10-ee) omits the MIPS III hazard nops that ps2dev ee-as inserts.
SVO3_AS_FLAGS = -EL -G0 -Icode/include
# iksemel ships with SVO3 and uses the same compiler. Retail schedules lui/lw pairs apart
# (iks_stack_new), which -mno-split-addresses prevents (see DOCS/libraries/IKSEMEL.md).
IKSEMEL_COMPILE_FLAGS = $(filter-out -mno-split-addresses,$(SVO3_COMPILE_FLAGS))

# Medius rt_memory: measured retail matches with default split-address and alignment passes;
# retail pads labels after unconditional branches to 8 bytes (rt_memory_allocate).
# Enable additional objects here as their C replacements are verified.
MEDIUS_OBJECTS = $(OBJ_DIR)/medius/rt_util/rt_memory.o $(OBJ_DIR)/medius/rt_util/rt_constraint.o \
	$(OBJ_DIR)/medius/rt_util/rt_string.o $(OBJ_DIR)/medius/rt_util/rt_mutex.o \
	$(OBJ_DIR)/medius/rt_util/rt_pack.o $(OBJ_DIR)/medius/rt_util/rt_msg_util.o $(OBJ_DIR)/medius/rt_util/rt_timebase.o
MEDIUS_COMPILE_FLAGS = -G0 -O2 -fno-builtin -fno-common -ffunction-sections
MEDIUS_AS_FLAGS = -EL -G0 -g -Icode/include
ifeq ($(ALLOW_NONMATCHING),1)
    MEDIUS_COMPILE_FLAGS += -DALLOW_NONMATCHING
endif

$(MEDIUS_OBJECTS): $(OBJ_DIR)/%.o: code/%.c
	@$(MKDIR) -p $(dir $@)
	$(EEGCC296) -S $(MEDIUS_COMPILE_FLAGS) $(INCLUDE) $< -o $(@:.o=.s)
	$(EEAS296) $(MEDIUS_AS_FLAGS) $(@:.o=.s) -o $@

# SDK networking/localization probes match SCE 2.96 with default alignment.
# Keep this independent of Medius's minimal alignment and SVO3's size flags.
SDK_COMPILE_FLAGS = -G0 -O2 -fno-builtin -fno-common -ffunction-sections
SDK_AS_FLAGS = -EL -G0 -g -Icode/include
ifeq ($(ALLOW_NONMATCHING),1)
    SDK_COMPILE_FLAGS += -DALLOW_NONMATCHING
endif

$(OBJ_DIR)/sdk/%.o: code/sdk/%.c
	@$(MKDIR) -p $(dir $@)
	$(EEGCC296) -S $(SDK_COMPILE_FLAGS) $(INCLUDE) $< -o $(@:.o=.s)
	$(EEAS296) $(SDK_AS_FLAGS) $(@:.o=.s) -o $@

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

ee-gcc296: ps2dev
	@if [ ! -f "$(EEGCC296_DIR)/ee296_statshim.so" ]; then \
		echo "[Project RYNO] Downloading SCE ee-gcc 2.96..."; \
		curl -L -o /tmp/ee-gcc2.96.tar.xz $(EEGCC296_URL) && \
		$(MKDIR) -p $(EEGCC296_DIR) && \
		tar -xJf /tmp/ee-gcc2.96.tar.xz -C $(EEGCC296_DIR) && \
		rm /tmp/ee-gcc2.96.tar.xz && \
		gcc -m32 -shared -fPIC -O2 -o $(EEGCC296_DIR)/ee296_statshim.so $(TOOLS)/ee296_statshim.c && \
		echo "[Project RYNO] ee-gcc 2.96 installed."; \
	fi

dump:
ifndef iso
	$(error ISO is not set. Usage: make dump iso='/isos/SCUS_974.65.Ratchet Deadlocked.iso')
endif
	$(RATCHET_CLI) map export-executables --game DL --input "$(iso)" --output "$(ASSETS)" --boot-elf "$(CURDIR)/$(TARGET)" --output-iso "$(CURDIR)/$(BUILD_DIR)/new_$(GAME).iso"

rom: ps2dev ee-gcc296
	@echo "[Project RYNO] Extracting ROM only..."
	$(PYTHON) $(TOOLS)/elf_to_rom.py $(ASSETS)/boot.elf $(CONFIG)/$(BASENAME).yaml $(CONFIG)/$(BASENAME).rom

split:
	$(PYTHON) $(TOOLS)/split_dl.py $(CONFIG)/$(BASENAME).yaml

iso: elf
	$(RATCHET_CLI) map build-boot --config "$(CLI_CONFIG)"

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

$(OBJ_DIR)/svo3/%.o: code/svo3/%.cpp
	@$(MKDIR) -p $(dir $@)
	$(EEGXX296) -S $(SVO3_COMPILE_FLAGS) $(INCLUDE) $< -o $(@:.o=.s)
	$(PYTHON) $(TOOLS)/svo3_rodata_sections.py $(@:.o=.s)
	$(EEAS296) $(SVO3_AS_FLAGS) $(@:.o=.s) -o $@

$(OBJ_DIR)/iksemel/%.o: code/iksemel/%.c
	@$(MKDIR) -p $(dir $@)
	$(EEGCC296) -S $(IKSEMEL_COMPILE_FLAGS) $(INCLUDE) $< -o $(@:.o=.s)
	$(PYTHON) $(TOOLS)/svo3_rodata_sections.py $(@:.o=.s)
	$(EEAS296) $(SVO3_AS_FLAGS) $(@:.o=.s) -o $@

$(OBJ_DIR)/%.o: code/%.cpp
	@$(MKDIR) -p $(dir $@)
	$(EEGXX) -c $(COMMON_COMPILE_FLAGS) $(INCLUDE) $< -o $@

$(BUILD_DIR)/assets/%.o: assets/%.bin
	@$(MKDIR) -p $(dir $@)
	$(CROSS)-objcopy -I binary -O elf32-tradlittlemips -B mips $< $@
