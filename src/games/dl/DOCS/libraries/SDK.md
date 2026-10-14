# Deadlocked SDK compiler profile

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

All 22 SDK INCLUDE_ASM entries remain in production source (two are split
instruction remnants, not complete independent functions). These C bodies are
compiler probes only, so **SDK production C decompilation progress remains 0%**.
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
