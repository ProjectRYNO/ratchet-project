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
# Retail iksemel/SVO string helpers use four-byte function boundaries.
$(OBJ_DIR)/iksemel/src/iks.o: COMMON_COMPILE_FLAGS += -falign-functions=4
$(OBJ_DIR)/svo3/SVOString.o: COMMON_COMPILE_FLAGS += -Os -fno-schedule-insns -fno-reorder-blocks -falign-functions=4
# SVO3 core replacements retain fixed retail slots; matching remains tracked separately.
$(OBJ_DIR)/svo3/DownloadBinary.o $(OBJ_DIR)/svo3/ParseXML.o $(OBJ_DIR)/svo3/ParseSVMLAddObjects.o $(OBJ_DIR)/svo3/ParseSVMLForDownloads.o $(OBJ_DIR)/svo3/ParseXMLInfo.o $(OBJ_DIR)/svo3/PageRequestListener.o $(OBJ_DIR)/svo3/SVFileDownloadQueue.o $(OBJ_DIR)/svo3/TagUtils.o $(OBJ_DIR)/svo3/SVBrowser.o $(OBJ_DIR)/svo3/buttonTag.o $(OBJ_DIR)/svo3/CheckboxInputTag.o $(OBJ_DIR)/svo3/CHttp.o $(OBJ_DIR)/svo3/HttpSecure.o $(OBJ_DIR)/svo3/SetVariableTag.o $(OBJ_DIR)/svo3/TextTag.o $(OBJ_DIR)/svo3/TickerTag.o $(OBJ_DIR)/svo3/CDrawContextBase.o $(OBJ_DIR)/svo3/FormTag.o $(OBJ_DIR)/svo3/HiddenInputTag.o $(OBJ_DIR)/svo3/PopupTag.o $(OBJ_DIR)/svo3/QuickLinkTag.o $(OBJ_DIR)/svo3/SubmitInputTag.o $(OBJ_DIR)/svo3/DataTag.o $(OBJ_DIR)/svo3/ImageTag.o $(OBJ_DIR)/svo3/PageIDTag.o $(OBJ_DIR)/svo3/RadioInputTag.o $(OBJ_DIR)/svo3/SelectTag.o $(OBJ_DIR)/svo3/StaticImageTag.o $(OBJ_DIR)/svo3/TextInputTag.o $(OBJ_DIR)/svo3/CPage.o $(OBJ_DIR)/svo3/CreateGameTagModule.o $(OBJ_DIR)/svo3/GenericListBoxTag.o $(OBJ_DIR)/svo3/ListBoxTag.o $(OBJ_DIR)/svo3/LoginTagModule.o $(OBJ_DIR)/svo3/Navigation.o $(OBJ_DIR)/svo3/RTCommSock.o $(OBJ_DIR)/svo3/SVDownloadManager.o $(OBJ_DIR)/svo3/SVO_DBG.o $(OBJ_DIR)/svo3/SVTagModule.o $(OBJ_DIR)/svo3/TextAreaTag.o $(OBJ_DIR)/svo3/ImageTagModule.o $(OBJ_DIR)/svo3/DataTagModule.o $(OBJ_DIR)/svo3/PasswordInputTag.o $(OBJ_DIR)/svo3/GridTag.o $(OBJ_DIR)/svo3/md5.o $(OBJ_DIR)/svo3/LineTag.o $(OBJ_DIR)/svo3/RectangleTag.o $(OBJ_DIR)/svo3/SVTag.o $(OBJ_DIR)/svo3/LogoutTag.o $(OBJ_DIR)/svo3/RedirectTag.o $(OBJ_DIR)/svo3/BrowserInitTag.o $(OBJ_DIR)/svo3/SVURIStore.o $(OBJ_DIR)/svo3/URISchemeMgr.o $(OBJ_DIR)/svo3/RedirectTagModule.o $(OBJ_DIR)/svo3/CPluginManager.o $(OBJ_DIR)/svo3/CCookie.o $(OBJ_DIR)/svo3/SVTagModuleList.o $(OBJ_DIR)/svo3/HttpUtils.o $(OBJ_DIR)/svo3/DNSCache.o $(OBJ_DIR)/svo3/PageHistory.o $(OBJ_DIR)/svo3/SVChronograph.o $(OBJ_DIR)/svo3/SVSock.o $(OBJ_DIR)/svo3/UTF8_Util.o $(OBJ_DIR)/svo3/ButtonTagModule.o $(OBJ_DIR)/svo3/LineTagModule.o $(OBJ_DIR)/svo3/RectangleTagModule.o $(OBJ_DIR)/svo3/HiddenInputTagModule.o $(OBJ_DIR)/svo3/PasswordInputTagModule.o $(OBJ_DIR)/svo3/SubmitInputTagModule.o $(OBJ_DIR)/svo3/RadioInputTagModule.o $(OBJ_DIR)/svo3/TextInputTagModule.o $(OBJ_DIR)/svo3/TextTagModule.o $(OBJ_DIR)/svo3/TickerTagModule.o $(OBJ_DIR)/svo3/PageIDTagModule.o $(OBJ_DIR)/svo3/BrowserInitTagModule.o $(OBJ_DIR)/svo3/CheckboxInputTagModule.o $(OBJ_DIR)/svo3/FormTagModule.o $(OBJ_DIR)/svo3/GenericListBoxTagModule.o $(OBJ_DIR)/svo3/GridTagModule.o $(OBJ_DIR)/svo3/ListBoxTagModule.o $(OBJ_DIR)/svo3/LogoutTagModule.o $(OBJ_DIR)/svo3/PopupTagModule.o $(OBJ_DIR)/svo3/QuickLinkTagModule.o $(OBJ_DIR)/svo3/SelectTagModule.o $(OBJ_DIR)/svo3/SetVariableTagModule.o $(OBJ_DIR)/svo3/StaticImageTagModule.o $(OBJ_DIR)/svo3/TextAreaTagModule.o $(OBJ_DIR)/svo3/CPluginBase.o $(OBJ_DIR)/svo3/CQueryParams.o $(OBJ_DIR)/svo3/CConfig.o $(OBJ_DIR)/svo3/CMemoryContextBase.o $(OBJ_DIR)/svo3/CInputContextBase.o $(OBJ_DIR)/svo3/CError.o $(OBJ_DIR)/svo3/CSystemContextBase.o $(OBJ_DIR)/svo3/CAudioContextBase.o: COMMON_COMPILE_FLAGS += -G0 -Os -fno-schedule-insns -fno-reorder-blocks -falign-functions=4
# HTTP decoding fits its original slots with instruction scheduling enabled.
$(OBJ_DIR)/svo3/HttpUtils.o: COMMON_COMPILE_FLAGS += -fschedule-insns
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
	$(error ISO is not set. Usage: make dump iso='/isos/SCUS_974.65.Ratchet Deadlocked.iso')
endif
	$(RATCHET_CLI) map export-executables --game DL --input "$(iso)" --output "$(ASSETS)" --boot-elf "$(CURDIR)/$(TARGET)" --output-iso "$(CURDIR)/$(BUILD_DIR)/new_$(GAME).iso"

rom: ps2dev
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

$(OBJ_DIR)/%.o: code/%.cpp
	@$(MKDIR) -p $(dir $@)
	$(EEGXX) -c $(COMMON_COMPILE_FLAGS) $(INCLUDE) $< -o $@

$(BUILD_DIR)/assets/%.o: assets/%.bin
	@$(MKDIR) -p $(dir $@)
	$(CROSS)-objcopy -I binary -O elf32-tradlittlemips -B mips $< $@
