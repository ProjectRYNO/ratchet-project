# Boot ELF DMA recovery

Verified 2026-10-19. Scope is the retail boot executable only. Source was recovered
from its instructions and Ghidra output; no official Sony SDK sources were used.

`code/sdk/dma/libdma.c` owns `0x001399E0..0x00139EC8` (1,256 bytes).
The split preserves original entry points, padding and data ownership. The next
aggregate, `game/lib_after_dma.cpp`, starts at `sceMcInit` (`0x00139EC8`).

| Function | Address | Exact compiled bytes | State |
|---|---|---:|---|
| WaitDma | 0x001399E0 | 112 | C, exact |
| CheckAddress | 0x00139A58 | 40 | C, exact |
| memclr | 0x00139A80 | 52 | C, exact |
| sceDmaGetChan | 0x00139AB8 | 40 | C, exact |
| sceDmaReset | 0x00139AE0 | — | Retained assembly |
| sceDmaPutEnv | 0x00139BC0 | — | Retained assembly |
| sceDmaSend | 0x00139DA0 | 104 | C, exact |
| sceDmaPause | 0x00139E28 | — | Retained assembly |

DMA is **8/8 real functions (100%)**, or 1,192/1,192 function bytes (100%).
The four retained instruction fragments at `0x00139A50`, `0x00139D98`,
`0x00139E08`, and `0x00139EC0` are excluded from the function count.
All real DMA functions are recovered in C. The entire module also matches retail, including the retained instruction fragments and padding.

## Compiler and layout

The Makefile selects **EE GCC 2.9, 991111-01**, with `-G0 -O2 -fno-builtin`
and its bundled assembler (`-EL -G0 -Icode/include`). This is the existing libm
toolchain, distinct from the SCE EE GCC 2.96 networking/localization profile.
Compiler trials also included the July 1999 compiler, other November variants,
SCE 2.96 and PS2DEV 3.2.3; the selected compiler reproduces all eight implementations.
Source forms matter: signed `memclr` length, signed DMA control masking, separate
address-mask operations, and the original timeout loop were retained.

`sdkDmaChannels` names existing data at `0x00167BC0` (ten pointers), and
`sdkDmaTimeout` names the existing string at `0x00194E30`. Neither allocates
replacement storage. Registers use volatile word pointers without speculative
SDK structure definitions. Function slots are registered in
`config/decompiled_functions.yaml`; compiled functions do not use assembly fallback.

## Validation

Built in the isolated `/tmp/sdk-boot-dma` snapshot in `projectryno-medius-probe`:
serial `make rom`, `make split`, then `make -j8 elf`, with nonmatching fallback
disabled. The snapshot alone needed the existing SVO3 include spelling
`DnsCache.h` corrected to `DNSCache.h` for Linux; the working SVO3 source was
not changed by this task.

- `TESTS/check_sdk.py`: all 28 compiled SDK functions / 5,468 bytes exact;
  all five complete module ranges / 5,592 bytes exact.
- `TESTS/check_main_elf.py`: placement audit passed; all differences confined
  to existing registered replacement slots.
- `TESTS/check_global_map.py`: 807 recovered global names at retail addresses.
- `TESTS/sdk_dma_test.c`: 395 host cases passed, covering channel bounds,
  address conversion, guarded memory clearing, timeout handling and mocked DMA
  register updates. Hardware was mocked; this is not a console/gameplay test.
- `tools/compare_elf.py`: **whole ELF still nonmatching**, with 1,340 differing
  bytes outside SDK (726 core/startup, 614 SVO3). Runtime headers match.

Original SHA-256: `ffbdb083ed3682c20dede63219a5d228c3b0fd9c9d236f0864b2faee334f05c7`.
Rebuilt SHA-256: `64078bbf47afbe00257afd64342b76547f19cb33c1a5b679fa78d7a6480da246`.
Local probe/build logs are under `build/medius_compiler_probe/sdk_boot/logs-complete`.
No ISO or gameplay validation was performed.

The expanded `code/sdk/` scope is **28/28 real functions (100%)**. Other boot
SDK components remain in game aggregates and are not included in that percentage.
No real DMA functions remain in assembly.

## Final three-function recovery

`sceDmaPause` preserves the otherwise-unused volatile read of DMAC control and
restores interrupts only when `DIntr` reported they were enabled. `sceDmaReset`
walks the ten retail reset flags, preserves unselected channels, acknowledges DMA
status and installs a cleared environment. Its final status store intentionally
uses an ordinary pointer to reproduce the original call delay slot; the resolved
instruction stream is checked in full.

`DmaEnv` is an instruction-confirmed 20-byte layout. The ring-base member at +12
is a pointer; its aliasing behavior is necessary for the original load schedule.
The four selector bounds return -1 through -4 without writing the environment.
Existing reset flags (0x00194E48), selector tables (0x00194E70/80/90), and saved
environment (0x001AD858) are named with externs, without new allocations.

Host tests map ordinary memory at the MMIO addresses and mock interrupt calls.
They cover selectors, error returns, register packing, saved environment, reset
selection and interrupt restoration, but do not simulate DMA or write-one-to-clear
hardware semantics. EE layout checks verify offsets independently of host pointers.
