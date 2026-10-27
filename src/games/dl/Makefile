.PHONY: dump config split iso FORCE elf ps2dev ee-gcc296 ee-gcc29 ee-gcc-sn136
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
EEGCC29_DIR ?= /opt/ee-gcc2.9-990721
EEGCC29_URL = https://github.com/decompme/compilers/releases/download/compilers/ee-gcc2.9-990721.tar.xz
EEGCC29_SHA256 = ad2ea68afff2be25d21a1d51a75e8a0eea8f259018e6580622355cd01b95676b
EEGCC29 = LD_PRELOAD=$(EEGCC296_DIR)/ee296_statshim.so $(EEGCC29_DIR)/bin/ee-gcc
EEAS29 = LD_PRELOAD=$(EEGCC296_DIR)/ee296_statshim.so $(EEGCC29_DIR)/ee/bin/as
EEGCC29_01_DIR ?= /opt/ee-gcc2.9-991111-01
EEGCC29_01_URL = https://github.com/decompme/compilers/releases/download/compilers/ee-gcc2.9-991111-01.tar.xz
EEGCC29_01_SHA256 = ed684fd98f89d36b0121caab311052089103e3b36241fcef4338cc9ea41c75b8
EEGCC29_01 = LD_PRELOAD=$(EEGCC296_DIR)/ee296_statshim.so $(EEGCC29_01_DIR)/bin/ee-gcc
EEAS29_01 = LD_PRELOAD=$(EEGCC296_DIR)/ee296_statshim.so $(EEGCC29_01_DIR)/ee/bin/as
EESN136_DIR ?= /opt/ee-gcc2.95.3-136
EESN136_URL = https://github.com/decompme/compilers/releases/download/compilers/ee-gcc2.95.3-136.tar.gz
EESN136_SHA256 = 3b6ae6897229ad005aaf1b0afaa1f3cb46e74b4c21a42e01130c07c0c598067f
WIBO ?= /opt/wibo-1.2.0
WIBO_URL = https://github.com/decompals/wibo/releases/download/1.2.0/wibo-i686
WIBO_SHA256 = 2575d3b0a2f408b2c2b0850db56f1af5d005a138394a6774eba77b6708ecc304
EESN136 = $(WIBO) $(EESN136_DIR)/bin/ee-gcc.exe
EEAS_SN136 = $(WIBO) $(EESN136_DIR)/lib/gcc-lib/ee/2.95.3/as.exe

# Collect sources
SRC_C   = $(filter-out code/newlib/libm/upstream/%,$(shell $(FIND) code -type f -name '*.c'))
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
# Measured sound profile; see DOCS/sound/989SND_MATCHING.md.
# SN v1.36 packs scalar register saves with -fopt-stack. The assembler's -g
# preserves compiler NOPs and delay slots; this is required for exact matching.
# The assembly adapter reproduces legacy six-word loops from compiler output.
# The only division has a constant, nonzero divisor (741).
SOUND_COMPILE_FLAGS = -G16 -O2 -fopt-stack -mno-check-zero-division
SOUND_AS_FLAGS = -EL -G8 -g
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
# CHttp downloadBody: retail shows none of the -Os GCSE code hoisting of its identical Recv arms,
# while the rest of CHttp needs GCSE, so it is built alone without it (DECISIONS D14).
$(OBJ_DIR)/svo3/CHttp_downloadBody.o: SVO3_COMPILE_FLAGS += -fno-gcse
# Sony's bundled assembler (2.10-ee) omits the MIPS III hazard nops that ps2dev ee-as inserts.
# -g stops Sony as from filling delay slots itself; retail SVO3 was assembled that way (DECISIONS K07).
SVO3_AS_FLAGS = -EL -G0 -g -Icode/include
# iksemel matches without -g; keep its flags separate.
IKSEMEL_AS_FLAGS = -EL -G0 -Icode/include
# iksemel ships with SVO3 and uses the same compiler. Retail schedules lui/lw pairs apart
# (iks_stack_new), which -mno-split-addresses prevents (see DOCS/libraries/IKSEMEL.md).
IKSEMEL_COMPILE_FLAGS = $(filter-out -mno-split-addresses,$(SVO3_COMPILE_FLAGS))

# Medius rt_memory: measured retail matches with default split-address and alignment passes;
# retail pads labels after unconditional branches to 8 bytes (rt_memory_allocate).
# Enable additional objects here as their C replacements are verified.
MEDIUS_OBJECTS = $(OBJ_DIR)/medius/rt_util/rt_memory.o $(OBJ_DIR)/medius/rt_util/rt_constraint.o \
	$(OBJ_DIR)/medius/rt_util/rt_string.o $(OBJ_DIR)/medius/rt_util/rt_mutex.o \
	$(OBJ_DIR)/medius/rt_util/rt_pack.o $(OBJ_DIR)/medius/rt_util/rt_msg_util.o $(OBJ_DIR)/medius/rt_util/rt_timebase.o \
	$(OBJ_DIR)/medius/rt_util/rt_circ_buf.o $(OBJ_DIR)/medius/rt_util/rt_ip.o \
	$(OBJ_DIR)/medius/rt_util/rt_list_buf.o $(OBJ_DIR)/medius/rt_util/rt_time.o \
	$(OBJ_DIR)/medius/rt_util/rt_mtrandgen.o $(OBJ_DIR)/medius/rt_util/ps2/rt_mutex_platform.o \
	$(OBJ_DIR)/medius/rt_util/ps2/rt_time_platform.o $(OBJ_DIR)/medius/rt_util/rt_token.o \
	$(OBJ_DIR)/medius/rt_crypt/src/md5.o $(OBJ_DIR)/medius/rt_crypt/src/RC4.o \
	$(OBJ_DIR)/medius/rt_crypt/src/md2.o $(OBJ_DIR)/medius/rt_crypt/src/SHA1.o \
	$(OBJ_DIR)/medius/rt_crypt/src/md4.o $(OBJ_DIR)/medius/rt_crypt/src/rt_crypt_public.o \
	$(OBJ_DIR)/medius/rt_crypt/src/rt_crypt.o $(OBJ_DIR)/medius/rt_crypt/src/LargeInt.o \
	$(OBJ_DIR)/medius/rt_crypt/src/RSA.o $(OBJ_DIR)/medius/rt_cert/src/OID.o \
	$(OBJ_DIR)/medius/dme_client/src/DmeInterfaceManager.o $(OBJ_DIR)/medius/MediusClientLibrary/src/stringmanager.o \
	$(OBJ_DIR)/medius/dme_client/src/DmeRegister.o $(OBJ_DIR)/medius/MediusDList/src/MediusDMetaType.o \
	$(OBJ_DIR)/medius/rt_util/rt_parse.o $(OBJ_DIR)/medius/dme_client/src/DmeList.o \
	$(OBJ_DIR)/medius/MediusDList/src/MediusDList_shared.o \
	$(OBJ_DIR)/medius/StreamMedia/src/sequence.o $(OBJ_DIR)/medius/StreamMedia/src/vsequence.o \
	$(OBJ_DIR)/medius/MediusClientLibrary/src/MediusClans.o $(OBJ_DIR)/medius/MediusClientLibrary/src/MediusClient.o \
	$(OBJ_DIR)/medius/dme_client/src/DmeAddress.o \n	$(OBJ_DIR)/medius/MediusClientLibrary/src/MediusBilling.o $(OBJ_DIR)/medius/MediusClientLibrary/src/MediusFileServices.o
# Retail rt_parse and DmeRegister never tail-call: a wrapper returning another call's
# result keeps jal + jr. Every function in both matches with sibling calls disabled.
MEDIUS_NO_SIBCALL_OBJECTS = $(OBJ_DIR)/medius/rt_util/rt_parse.o $(OBJ_DIR)/medius/dme_client/src/DmeRegister.o
$(MEDIUS_NO_SIBCALL_OBJECTS): MEDIUS_COMPILE_FLAGS += -fno-optimize-sibling-calls
# Open-source PS2SDK headers (from the ps2dev toolchain) supply EE kernel and libcdvd
# declarations; Sony-only calls PS2SDK lacks are declared in code/sdk/sce_missing.h.
# The ee-gcc 2.96 package ships no compiler headers, so stddef.h/stdarg.h (pulled in by
# kernel.h) come from the ps2dev gcc's own include directory.
PS2SDK_FLAGS = -D_EE -isystem $(PS2DEV_DIR)/ps2sdk/ee/include -isystem $(PS2DEV_DIR)/ps2sdk/common/include \
	$(addprefix -isystem ,$(wildcard $(PS2DEV_DIR)/ee/lib/gcc-lib/ee/*/include))
MEDIUS_COMPILE_FLAGS = -G0 -O2 -fno-builtin -fno-common -ffunction-sections $(PS2SDK_FLAGS)
MEDIUS_AS_FLAGS = -EL -G0 -g -Icode/include
ifeq ($(ALLOW_NONMATCHING),1)
    MEDIUS_COMPILE_FLAGS += -DALLOW_NONMATCHING
endif

$(MEDIUS_OBJECTS): $(OBJ_DIR)/%.o: code/%.c
	@$(MKDIR) -p $(dir $@)
	$(EEGCC296) -S $(MEDIUS_COMPILE_FLAGS) $(INCLUDE) $< -o $(@:.o=.s)
	$(PYTHON) $(TOOLS)/svo3_rodata_sections.py $(@:.o=.s)
	$(EEAS296) $(MEDIUS_AS_FLAGS) $(@:.o=.s) -o $@

# Boot libdma matches the same historical 991111-01 toolchain used by libm.
SDK_DMA_COMPILE_FLAGS = -G0 -O2 -fno-builtin
$(OBJ_DIR)/sdk/dma/libdma.o: code/sdk/dma/libdma.c code/sdk/dma/libdma.h Makefile | ee-gcc29-01
	@$(MKDIR) -p $(dir $@)
	$(EEGCC29_01) -S $(SDK_DMA_COMPILE_FLAGS) $(INCLUDE) $< -o $(@:.o=.s)
	$(EEAS29_01) -EL -G0 -Icode/include $(@:.o=.s) -o $@

# Retail boot multitap uses the same 991111-01 profile as DMA.
$(OBJ_DIR)/sdk/mtap/libmtap.o: code/sdk/mtap/libmtap.c code/sdk/mtap/libmtap.h Makefile | ee-gcc29-01
	@$(MKDIR) -p $(dir $@)
	$(EEGCC29_01) -S $(SDK_DMA_COMPILE_FLAGS) $(INCLUDE) $< -o $(@:.o=.s)
	$(EEAS29_01) -EL -G0 -Icode/include $(@:.o=.s) -o $@

# libmpeg retained asm (3-operand mult) assembles to the retail size only with the 2.96 assembler.
$(OBJ_DIR)/sdk/mpeg/libmpeg.o: code/sdk/mpeg/libmpeg.c code/sdk/mpeg/libmpeg.h Makefile | ee-gcc29-01
	@$(MKDIR) -p $(dir $@)
	$(EEGCC29_01) -S $(SDK_DMA_COMPILE_FLAGS) $(INCLUDE) $< -o $(@:.o=.s)
	$(EEAS296) -EL -G0 -Icode/include $(@:.o=.s) -o $@

# libgraph retained asm (3-operand mult) assembles to the retail size only with the 2.96 assembler.
$(OBJ_DIR)/sdk/graph/libgraph.o: code/sdk/graph/libgraph.c code/sdk/graph/libgraph.h Makefile | ee-gcc29-01
	@$(MKDIR) -p $(dir $@)
	$(EEGCC29_01) -S $(SDK_DMA_COMPILE_FLAGS) $(INCLUDE) $< -o $(@:.o=.s)
	$(EEAS296) -EL -G0 -Icode/include $(@:.o=.s) -o $@

$(OBJ_DIR)/sdk/cdvd/libcdvd.o: code/sdk/cdvd/libcdvd.c code/sdk/cdvd/libcdvd.h Makefile | ee-gcc29-01
	@$(MKDIR) -p $(dir $@)
	$(EEGCC29_01) -S $(SDK_DMA_COMPILE_FLAGS) $(INCLUDE) $< -o $(@:.o=.s)
	$(EEAS29_01) -EL -G0 -Icode/include $(@:.o=.s) -o $@

$(OBJ_DIR)/sdk/scf/libscf.o: code/sdk/scf/libscf.c code/sdk/scf/libscf.h Makefile | ee-gcc29-01
	@$(MKDIR) -p $(dir $@)
	$(EEGCC29_01) -S $(SDK_DMA_COMPILE_FLAGS) $(INCLUDE) $< -o $(@:.o=.s)
	$(EEAS29_01) -EL -G0 -Icode/include $(@:.o=.s) -o $@

$(OBJ_DIR)/sdk/pad/libpad.o: code/sdk/pad/libpad.c code/sdk/pad/libpad.h Makefile | ee-gcc29-01
	@$(MKDIR) -p $(dir $@)
	$(EEGCC29_01) -S $(SDK_DMA_COMPILE_FLAGS) $(INCLUDE) $< -o $(@:.o=.s)
	$(EEAS29_01) -EL -G0 -Icode/include $(@:.o=.s) -o $@

$(OBJ_DIR)/sdk/mc/libmc.o: code/sdk/mc/libmc.c code/sdk/mc/libmc.h Makefile | ee-gcc29-01
	@$(MKDIR) -p $(dir $@)
	$(EEGCC29_01) -S $(SDK_DMA_COMPILE_FLAGS) $(INCLUDE) $< -o $(@:.o=.s)
	$(EEAS29_01) -EL -G0 -Icode/include $(@:.o=.s) -o $@

$(OBJ_DIR)/sdk/kernel/libkernel.o: code/sdk/kernel/libkernel.c code/sdk/kernel/libkernel.h Makefile | ee-gcc29-01
	@$(MKDIR) -p $(dir $@)
	$(EEGCC29_01) -S $(SDK_DMA_COMPILE_FLAGS) $(INCLUDE) $< -o $(@:.o=.s)
	$(EEAS29_01) -EL -G0 -Icode/include $(@:.o=.s) -o $@

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

ee-gcc29: ee-gcc296
	@if [ ! -f "$(EEGCC29_DIR)/bin/ee-gcc" ]; then \
		echo "[Project RYNO] Downloading SCE ee-gcc 2.9-990721..."; \
		curl -fL -o /tmp/ee-gcc2.9-990721.tar.xz $(EEGCC29_URL) && \
		echo "$(EEGCC29_SHA256)  /tmp/ee-gcc2.9-990721.tar.xz" | sha256sum -c - && \
		$(MKDIR) -p $(EEGCC29_DIR) && \
		$(PYTHON) -c 'import tarfile; tarfile.open("/tmp/ee-gcc2.9-990721.tar.xz").extractall("$(EEGCC29_DIR)", filter="data")'; \
	fi

ee-gcc29-01: ee-gcc296
	@if [ ! -f "$(EEGCC29_01_DIR)/bin/ee-gcc" ]; then \
		curl -fL -o /tmp/ee-gcc2.9-991111-01.tar.xz $(EEGCC29_01_URL) && \
		echo "$(EEGCC29_01_SHA256)  /tmp/ee-gcc2.9-991111-01.tar.xz" | sha256sum -c - && \
		$(MKDIR) -p $(EEGCC29_01_DIR) && \
		$(PYTHON) -c 'import tarfile; tarfile.open("/tmp/ee-gcc2.9-991111-01.tar.xz").extractall("$(EEGCC29_01_DIR)", filter="data")'; \
	fi

ee-gcc-sn136:
	@if [ ! -f "$(EESN136_DIR)/bin/ee-gcc.exe" ]; then \
		curl -fL -o /tmp/ee-gcc2.95.3-136.tar.gz $(EESN136_URL) && \
		echo "$(EESN136_SHA256)  /tmp/ee-gcc2.95.3-136.tar.gz" | sha256sum -c - && \
		$(MKDIR) -p $(EESN136_DIR) && \
		$(PYTHON) -c 'import tarfile; tarfile.open("/tmp/ee-gcc2.95.3-136.tar.gz").extractall("$(EESN136_DIR)", filter="data")'; \
	fi
	@if [ ! -f "$(WIBO)" ]; then \
		curl -fL -o /tmp/ryno-wibo-1.2.0 $(WIBO_URL) && \
		echo "$(WIBO_SHA256)  /tmp/ryno-wibo-1.2.0" | sha256sum -c - && \
		install -m 755 /tmp/ryno-wibo-1.2.0 $(WIBO); \
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

# Historical fdlibm profile. The -991111-01 archive emits the retail div.s workaround;
# -991111a reports the same version but produces different float instructions.
LIBM_COMPILE_FLAGS = -G0 -O2 -fno-builtin
LIBM_HEADERS = -include $(PS2DEV_DIR)/ee/ee/include/sys/types.h -Icode/newlib/libm/upstream/common -isystem $(PS2DEV_DIR)/ee/ee/include -isystem $(PS2DEV_DIR)/ee/lib/gcc-lib/ee/3.2.3/include
LIBM_MATCHED_OBJS = $(OBJ_DIR)/newlib/libm/math/e_fmod.o $(OBJ_DIR)/newlib/libm/math/e_pow.o $(OBJ_DIR)/newlib/libm/math/e_sqrt.o $(OBJ_DIR)/newlib/libm/math/ef_exp.o $(OBJ_DIR)/newlib/libm/math/ef_log.o $(OBJ_DIR)/newlib/libm/math/ef_log10.o $(OBJ_DIR)/newlib/libm/math/ef_pow.o $(OBJ_DIR)/newlib/libm/math/ef_rem_pio2.o $(OBJ_DIR)/newlib/libm/math/ef_sqrt.o $(OBJ_DIR)/newlib/libm/math/kf_cos.o $(OBJ_DIR)/newlib/libm/math/kf_rem_pio2.o $(OBJ_DIR)/newlib/libm/math/kf_sin.o $(OBJ_DIR)/newlib/libm/common/s_copysign.o $(OBJ_DIR)/newlib/libm/math/s_fabs.o $(OBJ_DIR)/newlib/libm/common/s_finite.o $(OBJ_DIR)/newlib/libm/math/s_isnan.o $(OBJ_DIR)/newlib/libm/common/s_matherr.o $(OBJ_DIR)/newlib/libm/common/s_scalbn.o $(OBJ_DIR)/newlib/libm/math/sf_ceil.o $(OBJ_DIR)/newlib/libm/common/sf_copysign.o $(OBJ_DIR)/newlib/libm/math/sf_cos.o $(OBJ_DIR)/newlib/libm/math/sf_fabs.o $(OBJ_DIR)/newlib/libm/common/sf_finite.o $(OBJ_DIR)/newlib/libm/math/sf_floor.o $(OBJ_DIR)/newlib/libm/math/sf_isnan.o $(OBJ_DIR)/newlib/libm/common/sf_scalbn.o $(OBJ_DIR)/newlib/libm/math/w_fmod.o $(OBJ_DIR)/newlib/libm/math/w_pow.o $(OBJ_DIR)/newlib/libm/math/w_sqrt.o $(OBJ_DIR)/newlib/libm/math/wf_asin.o $(OBJ_DIR)/newlib/libm/math/wf_exp.o $(OBJ_DIR)/newlib/libm/math/wf_log.o $(OBJ_DIR)/newlib/libm/math/wf_log10.o $(OBJ_DIR)/newlib/libm/math/wf_pow.o $(OBJ_DIR)/newlib/libm/math/wf_sqrt.o $(OBJ_DIR)/newlib/libm/common/s_rint.o $(OBJ_DIR)/newlib/libm/math/ef_asin.o
LIBM_DATA_OBJS = $(OBJ_DIR)/newlib/libm/math/e_fmod.o $(OBJ_DIR)/newlib/libm/math/e_pow.o $(OBJ_DIR)/newlib/libm/math/ef_exp.o $(OBJ_DIR)/newlib/libm/math/ef_log.o $(OBJ_DIR)/newlib/libm/math/ef_log10.o $(OBJ_DIR)/newlib/libm/math/ef_pow.o $(OBJ_DIR)/newlib/libm/math/ef_rem_pio2.o $(OBJ_DIR)/newlib/libm/math/kf_rem_pio2.o $(OBJ_DIR)/newlib/libm/common/s_scalbn.o $(OBJ_DIR)/newlib/libm/math/w_fmod.o $(OBJ_DIR)/newlib/libm/math/w_pow.o $(OBJ_DIR)/newlib/libm/math/w_sqrt.o $(OBJ_DIR)/newlib/libm/math/wf_asin.o $(OBJ_DIR)/newlib/libm/math/wf_exp.o $(OBJ_DIR)/newlib/libm/math/wf_log.o $(OBJ_DIR)/newlib/libm/math/wf_log10.o $(OBJ_DIR)/newlib/libm/math/wf_pow.o $(OBJ_DIR)/newlib/libm/math/wf_sqrt.o $(OBJ_DIR)/newlib/libm/common/s_rint.o
$(LIBM_MATCHED_OBJS): $(OBJ_DIR)/newlib/libm/%.o: code/newlib/libm/%.c code/newlib/libm/upstream/%.c code/newlib/libm/upstream/common/fdlibm.h $(TOOLS)/drop_unused_rodata.py Makefile | ee-gcc29-01
	@$(MKDIR) -p $(dir $@)
	$(EEGCC29_01) -S $(LIBM_COMPILE_FLAGS) $(LIBM_HEADERS) $(INCLUDE) $< -o $(@:.o=.s)
	$(EEAS29_01) -EL -G0 $(@:.o=.s) -o $@
	$(CROSS)-strip -x -N dummy-symbol-name $@
	$(if $(filter $@,$(LIBM_DATA_OBJS)),$(CROSS)-objcopy --rename-section .rodata=.libmdata_$(notdir $*) $@,$(PYTHON) $(TOOLS)/drop_unused_rodata.py $@ --objcopy $(CROSS)-objcopy)

$(OBJ_DIR)/989snd/ee/989snd.o: code/989snd/ee/989snd.c code/989snd/ee/989snd.h Makefile $(TOOLS)/sound_loop_compat.py | ee-gcc-sn136
	@$(MKDIR) -p $(dir $@)
	$(EESN136) -S $(SOUND_COMPILE_FLAGS) $(INCLUDE) $< -o $(@:.o=.s)
	$(PYTHON) $(TOOLS)/sound_loop_compat.py $(@:.o=.s) $(@:.o=.compat.s)
	$(EEAS_SN136) $(SOUND_AS_FLAGS) $(@:.o=.compat.s) -o $@

$(OBJ_DIR)/svo3/%.o: code/svo3/%.cpp
	@$(MKDIR) -p $(dir $@)
	$(EEGXX296) -S $(SVO3_COMPILE_FLAGS) $(INCLUDE) $< -o $(@:.o=.s)
	$(PYTHON) $(TOOLS)/svo3_rodata_sections.py $(@:.o=.s)
	$(EEAS296) $(SVO3_AS_FLAGS) $(@:.o=.s) -o $@

$(OBJ_DIR)/iksemel/%.o: code/iksemel/%.c
	@$(MKDIR) -p $(dir $@)
	$(EEGCC296) -S $(IKSEMEL_COMPILE_FLAGS) $(INCLUDE) $< -o $(@:.o=.s)
	$(PYTHON) $(TOOLS)/svo3_rodata_sections.py $(@:.o=.s)
	$(EEAS296) $(IKSEMEL_AS_FLAGS) $(@:.o=.s) -o $@

$(OBJ_DIR)/%.o: code/%.cpp
	@$(MKDIR) -p $(dir $@)
	$(EEGXX) -c $(COMMON_COMPILE_FLAGS) $(INCLUDE) $< -o $@

$(BUILD_DIR)/assets/%.o: assets/%.bin
	@$(MKDIR) -p $(dir $@)
	$(CROSS)-objcopy -I binary -O elf32-tradlittlemips -B mips $< $@
