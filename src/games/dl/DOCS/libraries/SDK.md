# Deadlocked SDK compiler profile

The **100% completion figure covers `code/sdk/`**: `libezcnf.c`, `libezctl.c`,
`i18n.c`, and `i18n_inet.c` (20 real functions). It does not cover every Sony SDK
library linked into the boot ELF. Additional SDK code, including CD/DVD and graphics
functions, remains assembly in `code/game/lib_after_libm.cpp`; the library aggregates
also contain C runtime and other code. See the [boot ELF table](../../README.md#boot-elf-decompilation-progress)
for these separate scopes. The two retained SDK instruction fragments are not
unfinished independent functions.

Rechecked on 2026-10-19 against the isolated libm-complete ELF
(`2e1283399004eacffe115cc09128eaa2757ff5f658b49a7171cd972d46d25189`):
`check_sdk.py` passes all 20 compiled functions (4,276 bytes) and all four complete
module ranges, including padding and retained fragments. This is an exact-byte
check, not a gameplay test.

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
