# Ensure make subshells have a full PATH (fixes python, mkdir, etc. in containers)
SHELL := /bin/bash
export PATH := /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:$(PATH)
PYTHON := /usr/bin/python3
MKDIR := /usr/bin/mkdir

# Force use GNU tools
FIND := /usr/bin/find

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

	WINE := wine
endif

WINE32 := /usr/lib/wine/wine
WINE64 := /usr/lib/wine/wine64
EEGCC = $(WINE32) tools/cc/bin/ee-gcc.exe
CROSS = /usr/bin/mips-linux-gnu
WRENCHFOLDER = /opt/wrench
WRENCHBUILD = /usr/lib/wine/wine64 /opt/wrench
TOOLS = /../tools
ASSETS = /../assets/dl

# -include userconfig.mk

# Collect sources
SRC_C   = $(shell $(FIND) code -type f -name '*.c')
SRC_S   = $(shell $(FIND) code -type f -name '*.s' | grep -v "_generated/matchings\|_generated/nonmatchings")
SRC_CPP = $(shell $(FIND) code -type f -name '*.cpp')
INCLUDE = -Icode/include -Itools/cc/lib/gcc-lib/ee/2.95.2/include

BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/code
TARGET = $(BUILD_DIR)/boot_elf.elf

BASENAME = SCUS_974.65

OBJS = $(SRC_S:code/%.s=$(OBJ_DIR)/%.o) \
       $(SRC_CPP:code/%.cpp=$(OBJ_DIR)/%.o) \
       $(SRC_C:code/%.c=$(OBJ_DIR)/%.o)

PRODG_DIR = ../tools/cc

COMMON_COMPILE_FLAGS = -G8 -O2 -ffast-math -fno-exceptions -Wa,-EL -Wa,-Icode/include -DALLOW_NONMATCHING

# EXTRA WRENCH commands:
#     /bin/wrenchbuild unpack_wads ~/ps2/ratchet-dl.iso -o /mnt/ramdisk/ -s
#     /bin/wrenchbuild pack /mnt/ramdisk/dl_sces_532_85/ -a dl -o ~/wrench/builds/build.iso -h release

all: $(TARGET)

dump:
ifndef ISO
	$(error ISO is not set. Usage: make dump ISO=/path/to/your/game.iso or ISO=D:\path\to\your\game.iso)
endif
	$(WINE64) $(WRENCHFOLDER)/wrenchbuild.exe unpack "$(shell /usr/bin/python3 $(TOOLS)/normalize_path.py "$(ISO)")" -o $(ASSETS)/

split:
	$(PYTHON) -m splat split config/SCUS_974.65.yaml --disassemble-all

iso:
	$(WRENCHBUILD)/wrenchbuild.exe  pack $(ASSETS) $(WRENCHFOLDER)/overlay -a dl -o build/rac.iso -h release --flusher-thread-hack

clean:
	rm -rf build
	rm -rf code/_generated
	rm -rf $(BASENAME).ld
	
$(TARGET): $(OBJS)
	@$(MKDIR) -p $(dir $@)
	$(CROSS)-strip $(OBJS) -N dummy-symbol-name
	$(CROSS)-ld -EL -T $(BUILD_DIR)/undefined_funcs_auto.txt -T $(BUILD_DIR)/undefined_syms_auto.txt -T $(BASENAME).ld -Map build/$(BASENAME).ld $(OBJS) -o $@
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

