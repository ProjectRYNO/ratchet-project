# Deadlocked SDK compiler profiles

Current boot-only scope: **36/36 real functions (100.00%)** compiled and byte-matching in `code/sdk/`, covering networking/localization, DMA and multitap. Seven retained instruction fragments are excluded. Other SDK code remains in the game library aggregates.

The 2026-10-19 post-pull isolated build verifies 6,308 compiled bytes and all six complete module ranges (6,456 bytes). DMA contributes eight exact C functions; no real DMA routines remain assembly. See [DMA implementation and validation](SDK_DMA.md). DMA uses EE GCC 2.9 (991111-01); networking/localization retains SCE EE GCC 2.96. The historical 20/20 results below cover networking/localization only.

## Pad, memory card and kernel splits (2026-10-26)

**250/387 identified boot SDK functions (64.60%) are now byte-exact** (plus 52 untracked helpers) (see
[inventory](SDK_BOOT_INVENTORY.md)). New split objects, all built with EE GCC 2.9 (991111-01)
`-G0 -O2 -fno-builtin` like DMA/multitap:

- `sdk/mc/libmc.c` (0x00139EC8..0x0013AE70, was `game/lib_after_dma.cpp`): 17/17 exact.
- `sdk/pad/libpad.c` (0x0013B1D0..0x0013C478): 17 exact. Retained: `_pad_intr_hdr`
  (handwritten gp swap/`ei`), and near misses `scePadInit2` (one store), `scePadInfoPressMode`
  (branch vs `movz`), `scePadPortOpen`, `_send_to_iop`. Remainder is `game/lib_after_pad.cpp`.
- `sdk/kernel/libkernel.c` (0x001267A0..0x0012EE30, carved from `game/lib.cpp`; the rest is
  `game/lib_after_kernel.cpp`): 121 tracked functions exact (plus local helpers and `kCopy`
  duplicates) across SIF, IOP heap, load-file, file I/O, DECI2, TTY, printf, TLB/exec setup,
  timers and alarms. Syscall stubs and functions using `di`/`ei`/`sync`/`cache`/COP0 or setting
  `$gp` stay retained assembly (they were assembly or inline asm originally).

- `sdk/scf/libscf.c` (0x00155510..0x00155AE0, carved from `game/lib_after_pad.cpp`; the rest
  is `game/lib_after_scf.cpp`): 11 exact (ROMVER, OSD-config getters, BCD and date helpers).
  Near misses: `sceScfGetTimeZone`, `sceScfGetSummerTime`, `frombcd`, `AdjustTime`,
  `sceScfGetLocalTimefromRTC`. `clock->year % 4 == 0` (not `& 3`) was needed in adddate/subdate.
- `sdk/cdvd/libcdvd.c` and `sdk/graph/libgraph.c` (all of former `game/lib_after_libm.cpp`):
  CD/DVD 14 exact counting helpers, graphics 8 exact. Semaphore IDs are read through a
  `CD_VOLATILE()` access in the functions where retail reloads them, while the short S-command
  wrappers use plain reads; the retail library was probably split over files with different
  declarations. `graphGParam_t` needs 8-byte alignment so GCC folds the interlace/ffmode test in
  `sceGszbufaddr` into one 64-bit compare. `libgraph.o` is assembled with the 2.96 assembler,
  because the 991111 assembler expands the retained asm's 3-operand `mult`. Near misses:
  `cdvd_exit`, `_sceCd_cd_read_intr`, `sceCdPOffCallback`, `sceCdRead`, `sceGsResetGraph`
  (one register swap). `sceGsSetDefDrawEnv`/`sceGsSetDefLoadImage`/`sceGsSetDefStoreImage`
  contain `sync`; `_GetGsDxDyOffset` and `_sceCd_Poff_Intr` are syscall/gp code and stay asm.

- `sdk/mpeg/libmpeg.c` (0x0013C750..0x00146D10, carved from `game/lib_after_pad.cpp`; the rest
  is `game/lib_after_mpeg.cpp`): MPEG 6/11 and IPU 3/4 tracked, plus `setD3_CHCR`/`setD4_CHCR`
  and its duplicate. Like libgraph it is assembled with the 2.96 assembler. Near misses:
  `sceMpegInit` (retail puts a volatile store in the `jal` delay slot, as in `kputchar`),
  `sceMpegAddCallback` (gp-read barrier, see `sceSifCallRpc`).
- Kernel additions from parallel workers: `sceOpen`, `sceClose`, `sceDevctl` (the three requests
  overlay `fsRequest_t sdkFsRequest`), `_fs_version`, `_lf_version`, `sceSifInitIopHeap`,
  `sceSifResetIop`, `sceSifRebootIop`, `_sceSifLoadModuleBuffer`, `sceSifStopModule`,
  `InitSystemCallTableAddress`, `sceTtyHandler`, `SetArg`. `printfloat` is exact in
  `build/svo-library-work/b/C_t7.c` but needs its literal block at 0x00192E20 (0x30 bytes) mapped
  as a rodata slot before it can be integrated.

- **Assembler:** retail SDK code was assembled with the 2.96 assembler, not 991111's. It moves a
  store into a `jal`/`jr` delay slot (the 991111 one never does) and keeps EE 3-operand `mult`.
  Every SDK rule now uses `$(EEAS296)`. Reassembling all previously exact objects gave identical
  sections, and it made `ftoi`, `kputchar`, `sceMpegInit` and `cdvd_exit` exact.
- `sdk/mrpc/libmrpc.c` (0x00155AE0..0x00156390, former start of `lib_after_scf.cpp`, rest renamed
  `game/lib_after_mrpc.cpp`): 5 exact; `_request_end___dupe2` writes `$gp`.
- libmpeg: 25 more internals (allocator, bitstream helpers, error/DMA helpers, decode control)
  with worker D's `mpegInternal_t` layout; `sceIpuSync` takes the SDK's unused timeout argument.
- `printfloat` is integrated; libkernel's only `.rodata` (its literals) is renamed to
  `.kerneldata_printfloat` and fills the registered rodata slot 0x00192E20..0x00192E50.

- Later worker round: scf `sceScfGetSummerTime` (`GetOsdConfigParam2` returns `int`), `AdjustTime`,
  `sceScfGetLocalTimefromRTC`; mrpc `sceSifMInitRpc`; kernel `_request_rdata`/`_request_bind`
  (read `paddr`/`client` into locals first; packet type `sifRpcReqPkt_t` with untyped words);
  libmpeg header parsers and stream helpers (`_sceMpegNextHeader`, `_pictureHeader`,
  `_extensionAndUserData` copying `sdkMpegExtTable`, quant/sequence/picture extensions,
  `receiveDataFromIPU`, `_sceMpegErrorBdec`), with `pts`/`dts` (64-bit) and frame offset arrays
  added to `mpegInternal_t`. `frombcd` cannot be expressed: retail uses `mult $0` + `mflo`, which
  this compiler never emits for C.

- Newlib stubs `close`, `lseek`, `getpid`; `sceCdRead` (one plain busy-flag store through
  `CD_PLAIN()`); `sceIpuInit` (quadword VLC/CSC tables `sdkIpuVlcTable`/`sdkIpuCscTable`);
  `sceMpegCreate` with the `mpeg_t` timestamp fields, the allocator at `mpegInternal_t+0x118` and
  nine 0x68-byte reference image buffers; IPU wait helpers and `_dualPrimeVector`/`_motionVectors`.

Every entry in these ranges has its own `.lib_name` slot; padding words keep their own slots.
New globals are named in `symbols_core.text.txt` (`sdkPad*`, `sdkMc*`, `sdkSif*`, `sdkFs*`,
`sdkIopHeap*`, `sdkLoadFile*`, `sdkTimer`, ...). Verification: isolated split + build;
`check_main_elf` PASS with no change outside registered slots (726 changed bytes, all in
pre-existing non-SDK replacements). No gameplay test.

Lessons: snapshot structs (`padFrame_t`) rather than byte arrays fix sp-relative addressing;
a local pointer to an RPC buffer keeps it in one callee-saved register; callee return types
matter (`int DelayThread` freed `$2`; `void sceDeci2Poll`, `void TerminateLibrary`); `if (x) a = 1;
else a = 0;` gives `slti` where `a = x < 0` gives `srl`. This compiler emits sibling calls
(`j callee` tail calls), so small wrappers such as `_sceFsSigSema`, `SetT2_*`, `Exit` are plain C,
and a helper ending in a call cannot be inlined. A reload right after a store, or an unfilled
delay slot before a load, means a volatile field (`ttyData_t` socket/wlen/rlen/busy, timer
`seq`/`used`/`systemId`, counter `key`, alarm `counterId`). Load hoisting across a store means
the two fields have non-aliasing types (`void *` header packet pointer in `sceSifGetOtherData`).
`lui/ori 0xffff` for -1 means an `unsigned int` argument. Varargs use `va-mips.h` macros in
`libkernel.h` (this compiler has no `stdarg.h`).

Near misses (permuter or manual): `scePadInit2`, `scePadInfoPressMode`, `scePadPortOpen`,
`_send_to_iop`, `sceSifAddCmdHandler`, `sceSifCheckStatRpc` (final test folds into `mode & 1`),
`sceSifInitIopHeap`, `sceSifAddRebootNotifyHandler`, `kputchar` (return-copy placement),
`_fs_version`, `_lf_version`, `sceClose`, `sceLseek`/`sceRead`/`sceWrite` (where `nowait` is
assigned), `sceTtyHandler` (send-result register), `SetArg` (register allocation), `_request_call`/`_request_rdata`/`_request_bind`
(field alias sets; a 729-way type sweep found none), `iGetTimerSystemTime`/`GetTimerSystemTime`
(retail reads the count twice with `lwu`). `sceSifCallRpc` and `iSetTimerHandler` read `$gp`
through what behaves as a scheduling barrier (source-order stores, `move` from `$28`), which
points to inline asm in the original; they stay assembly unless inline asm is approved there.
Store orders that resist reasoning can be swept with `build/svo-library-work/b/permbf.py`
(it found `supplement_crt0`). Test sources are in `build/svo-library-work/b/` (`pad_*.c`, `mc_*.c`, `k_*.c`); compare with
`build/svo-library-work/sdkcmp.py SRC PREFIX` inside the container.

## Broader runtime inventory

The [SDK folder map](../../code/sdk/README.md) lists the additional boot runtime
components still in the game library aggregates. The [version/source survey](SDK_LAYOUT.md)
records retail `3000` / `3020` fingerprints and comparisons with pinned public
PS2SDK revisions. These additional libraries are not included in the 20/20 result.

## Final parser integration (2026-10-14)

**20/20 real SDK functions (100.00%) now compile to exact retail bytes.**
All 4,276 function bytes match, with resolved calls and data references. The
complete four-module region, 0x01E9A000..0x01E9B0F0 (4,336 bytes), also matches
retail including padding and the two retained unused instruction fragments.
Those fragments are not independent functions: the raw inventory is 20 compiled
entries out of 22 (90.91%). [SDK.json](../progress/SDK.json) and
[SDK.csv](../progress/SDK.csv) record the measured result.

The final `ezNetCtlRecreateIfstat` at 0x01E9AE48 is now in `code/sdk/i18n_inet.c`.
Its 668-byte body matches with the existing SDK compiler profile. Keeping the
phase store in the interface dispatch and publishing the detail field afterward
reproduces the retail register allocation. The dispatch is intentional even
though both branches currently perform the same store; simplifying it changes
compiler output. No fixed-register bindings, injected instructions, or masked
comparisons are used. The earlier unmatched research file has been removed.

`i18n_inet.h` owns the 12-byte `SdkPPPStatus` entry and parser declarations.
Its table/string addresses come from retail instructions. SCE 2.96 layout checks
now cover four SDK types. The split YAML assigns the verified twelve zero tail
bytes at ROM 0x44F0E4..0x44F0F0 to i18n_inet. Old generated copies of
`code/asm/build/junk/net.text/44f0e4_44f0f0.s` and
`assets/junk/net.text/44f0e4_44f0f0.textbin.bin` must be removed before resplitting
an older generated tree; they are obsolete untracked output.

The isolated snapshot was refreshed from revision `ed29792` to include the
current iksemel/SVO3 work, then overlaid with this SDK change. Serial split and
forced full compilation passed with ALLOW_NONMATCHING=0. Exact SDK comparison,
SDK layout checks, and the full placement/outside-slot audit all passed.
Whole-game strict comparison remains NONMATCH: 15,834 differing bytes in other
registered replacements (5,135 main; 10,699 network). Runtime headers match.
No ISO or gameplay test was performed. The reproduction commands below apply
to all 20 SDK functions now; the following sections retain the earlier history.

## Earlier 95% integration (2026-10-14)

**19/20 real SDK functions (95.00%) now compile to exact retail bytes.**
`libezcnf.c` contributes five functions, `libezctl.c` seven, and `i18n.c` seven.
All 3,608 compiled bytes match with resolved calls and data references. All three
complete module ranges match, including padding and two retained unused
instruction fragments. Including those fragments, the raw inventory is 19/22
entries (86.36%). Function-byte progress is 3,608/4,276 (84.38%).
See [SDK progress](../progress/SDK.json) and [function rows](../progress/SDK.csv).

The compiler profile below remains unchanged. Production functions use fixed
retail slots in `config/decompiled_functions.yaml`. `eznet_rpc.h` owns RPC
declarations; `i18n.h` owns the shared 0x38-byte `ezNetCtlStatus` (dltypes.txt
line 11229), 0x1fc-byte interface-info union, and 0x10-byte message-table entry.
Retail accesses establish the used layouts; union views and callback signatures
are recovered from retail. Globals reference existing storage. The character
table reuses the existing libc `_ctype_` symbol.

`ezNetCtlRecreateIfstat` at 0x01E9AE48 remains assembly. Its research source was
`TESTS/sdk_inet_unmatched.c` (removed after exact integration): 668 bytes, 648 equal bytes, with remaining register
allocation differences. It is excluded from completed C counts. `ezNetCnfExit`
preserves the retail uninitialized result when the module is not running.

Validation: isolated forced full build with ALLOW_NONMATCHING=0 passed;
`check_sdk.py` passed exact functions and complete module ranges;
`check_sdk_layouts.py` passed with SCE 2.96; the full placement/outside-slot audit
passed. Strict whole-game comparison reports 9,770 differing bytes (5,130 main,
4,640 network), all outside this SDK work and inside other registered replacements.
Runtime headers match. No ISO, emulator, or gameplay test was performed.

The snapshot is `/tmp/sdk-integration` in `projectryno-medius-probe`, using
rewritten absolute include paths and the snapshot-only `DnsCache.h` case alias.
It does not rebuild the concurrent SVO3 checkout. The YAML now assigns the four
zero padding bytes at ROM 0x44EA74..0x44EA78 to libezctl, where the compiler emits
the same padding. On an old generated tree, remove the obsolete untracked files
`code/asm/build/junk/net.text/44ea74_44ea78.s` and
`assets/junk/net.text/44ea74_44ea78.textbin.bin` before resplitting, to avoid
emitting the padding twice.

After `make split`, then a forced build:

```sh
python3 TESTS/check_sdk.py ../assets/dl/boot.elf build/boot_elf.elf build/code/sdk
python3 TESTS/check_sdk_layouts.py
python3 TESTS/check_main_elf.py ../assets/dl/boot.elf build/boot_elf.elf build/code/game/boot.o
python3 ../tools/compare_elf.py ../assets/dl/boot.elf build/boot_elf.elf
```

The research below describes the earlier compiler-only stage.

## Finding (2026-10-13)

For `src/games/dl/code/sdk`, the strongest tested compiler is Sony SCE
**ee-gcc 2.96-ee-001003-1**, paired with its **2.10-ee-001003-1 assembler**.
Seven fixed C probes match all **744 bytes** of their retail functions using
`-O2 -G0` with default split-address optimization and default alignment.

| Compiler | O1, default | O2, default | Os, default | O3, default |
| --- | ---: | ---: | ---: | ---: |
| SCE 2.96-ee-001003-1 | 0/7 | **7/7** | 4/7 | **7/7** |
| SCE 3.2-ee-040921 | 0/7 | 0/7 | 0/7 | 0/7 |
| ps2dev GCC 3.2.3 | 0/7 | 0/7 | 0/7 | 0/7 |

The full matrix tests three compilers, four optimization levels, default versus
`-mno-split-addresses`, and three alignment profiles (72 configurations / 504
function comparisons). Sony 3.2 and ps2dev 3.2.3 match none of these probes in
any tested configuration. This identifies the best tested working profile;
it does not prove the historical build version or distinguish O2 from O3.
Other Sony revisions and SN/ProDG were not tested.

## Why a separate profile

At O2, SCE 2.96 with default alignment matches 7/7. Medius's minimal alignment
settings reduce that to 4/7; disabling split-address optimization reduces it
to 2/7 even with default alignment. Explicit eight-byte function/loop/jump
alignment with one-byte label alignment also matches 7/7. Keep the simpler
defaults unless a later function supplies contrary evidence.

The Makefile now contains a dedicated `sdk/%.o` rule using:

```text
SDK_COMPILE_FLAGS = -G0 -O2 -fno-builtin -fno-common -ffunction-sections
SDK_AS_FLAGS = -EL -G0 -g -Icode/include
```

This reuses the existing `EEGCC296`, `EEAS296`, and `make ee-gcc296` installation
path. SVO3 and Medius settings are unchanged. SDK C declarations/probes need the
EE ABI; native host compiler output is not a matching reference.

## Probes and scope

| Source module | Function | Retail entry | Bytes |
| --- | --- | --- | ---: |
| i18n | ezNetCtlSwapMessageTables | 0x01E9AA78 | 76 |
| i18n | getMsgEntry | 0x01E9AAC8 | 132 |
| i18n | cbFormatAuthMessage | 0x01E9ACB0 | 72 |
| i18n | cbFormatPPPStatus | 0x01E9ACF8 | 124 |
| i18n | cbFormatPhoneNumber | 0x01E9AE30 | 24 |
| libezcnf | ezNetCnfGetCombination | 0x01E9A2B0 | 176 |
| libezctl | ezNetCtlDownInterface | 0x01E9A7C8 | 140 |

Evidence came from the retail R5900 Ghidra program, split retail instructions,
and prototype module grouping. Probe bindings use retail addresses from the
instructions/configuration, not prototype addresses. The original extracted ELF
SHA-256 is `ffbdb083ed3682c20dede63219a5d228c3b0fd9c9d236f0864b2faee334f05c7`.

The initial fixed-source comparison matched five functions with SCE 2.96.
Expressing the three table assignments as conditional expressions and giving
the RPC result-buffer address a local variable produced the other two exact
matches. The final seven-function source was then rerun unchanged across all
72 compiler/settings combinations. There are no inline instruction substitutions,
register bindings, relocation masks, or copied retail code bytes in the C probes.
Each probe is linked independently at its retail address so an oversized
candidate cannot overlap another probe. Exact comparison requires equal symbol
sizes as well as all function bytes, including resolved calls and data references.

`i18n_inet.c` is the fourth SDK module. Its assembly output was included in the
full rebuild comparison, but its 668-byte `ezNetCtlRecreateIfstat` has not yet
been reconstructed as a C probe. The seven probes establish three-module
coverage, not proof that every SDK function will match.

## Verification

- Saved probe matrix: **7/7 functions, 744/744 bytes** for SCE 2.96 O2 defaults.
- Forced isolated full build with the new SDK rule: **PASS**.
- Runtime headers and loaded bytes versus the pre-SDK-rule baseline: **identical**.
- Full placement/outside-slot audit: **PASS**.
- Whole-game retail matching remains **NONMATCH**: the isolated snapshot has
  34,164 existing differing bytes (5,130 main, 29,034 network). The SDK rule
  introduces none.
- No ISO or gameplay test was performed.

The build uses the existing `/tmp/medius-integration` snapshot in
`projectryno-medius-probe`, including its documented snapshot-only `DnsCache.h`
case alias and rewritten absolute INCLUDE_ASM paths. It does not rebuild or
clean the actively edited SVO3 checkout. Counts describe this saved snapshot.

At the initial compiler-only stage, all 22 SDK INCLUDE_ASM entries remained in production source (two are split
instruction remnants, not complete independent functions). These C bodies are
compiler probes only, so **SDK production C decompilation progress was 0%**.
Medius remains 3/1,462 (0.21%). Integrating the SDK probes into original module
headers/source and registering their slots is separate follow-up work.

## Reproduce

Source: `dl/TESTS/sdk_compiler_probes.c`.
Tool: `tools/sdk_compiler_probe.py`.
[SDK_COMPILER_RESULTS.json](SDK_COMPILER_RESULTS.json) records source/ELF hashes,
compiler/assembler fingerprints, symbol bindings, all flags and per-function
results. Exact counts use the original ELF directly, not assembly text comments.

```sh
python3 /ProjectRYNO/tools/sdk_compiler_probe.py \
  --output /ProjectRYNO/dl/build/sdk-compiler-results \
  --shim /opt/ee-gcc2.96/ee296_statshim.so \
  --compiler sony296 /opt/ee-gcc2.96/bin/ee-gcc /opt/ee-gcc2.96/ee/bin/as \
  --compiler ps2dev323 /opt/ps2dev/ee/bin/ee-gcc /opt/ps2dev/ee/bin/ee-as
```

Add `--compiler sony32 PATH/bin/ee-gcc PATH/ee/bin/as` to include the tested
Sony 3.2-ee-040921 archive. Compiler names starting with `sony` receive the
32-bit stat shim. The existing isolated experiment has this compiler at
`/probe/sony32`. Archives/binaries are local and not committed.

Ignored experiment outputs, initial probes, full matrix logs, and build evidence
are under `dl/build/medius_compiler_probe/sdk/`. Regenerate production assembly
with `make split` before a forced `make -B -j8 elf` when beginning integration.

Broader boot SDK tracking: **250/387 identified functions (64.60%)** are decompiled and byte-matching; this is an incomplete named-function inventory, not an all-SDK census. See [inventory](SDK_BOOT_INVENTORY.md) and [multitap verification](SDK_MTAP.md).

Publication recheck on `cff526a` plus SDK changes: all 36 SDK functions and the incoming 46 Medius functions match; placement/global/type checks pass. The whole ELF still differs by 2,172 bytes outside SDK. See [publication details](SDK_MTAP.md#publication-recheck-after-remote-update).
