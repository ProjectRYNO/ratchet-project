# Boot SDK layout and public-source comparison

Survey: 2026-10-19. This records the retail library fingerprints and compares public PS2SDK revisions. It does not import Sony sources, change splits, or claim new byte-matching functions.

## Findings

The boot ELF contains Sony runtime components with `3000` stamps and memory-card/pad components with `3020` stamps. The working interpretation is a 3.0.x runtime, including 3.0.2-era MC/pad libraries. Treat this as a component-version fingerprint, not proof of a unique installed SDK release: unchanged libraries can retain older stamps in later distributions. No official SDK archive was downloaded or inspected.

Public PS2SDK is a separate homebrew source tree. Its 2004/2005 extended-pad and extended-memory-card paths are useful interface references, but inspected initialization and read paths differ materially from retail. There is no demonstrated public SDK version that can be copied in to complete this backlog. Compiler tuning cannot remove these behavioral/structural differences.

## Retail evidence

Input: `src/games/assets/dl/boot.elf`, SHA-256 `ffbdb083ed3682c20dede63219a5d228c3b0fd9c9d236f0864b2faee334f05c7`. Addresses below were mapped through ELF PT_LOAD segments, not inferred from raw file offsets.

| Loaded address | Exact embedded stamp |
|---|---|
| `0x164678` | `PsIIlibkernl3000` |
| `0x165fc0` | `PsIIlibcdvd 3000` |
| `0x167b80` | `PsIIlibgraph3000` |
| `0x167bb0` | `PsIIlibdma  3000` |
| `0x167be8` | `PsIIlibmc   3020` |
| `0x167c08` | `PsIIlibpad  3020` |
| `0x167c60` | `PsIIlibvu0  3000` |
| `0x167e60` | `PsIIlibipu  3000` |
| `0x16fc08` | `PsIIlibscf  3000` |
| `0x16fc30` | `PsIIlibmrpc 3000` |

The existing 20/20 exact SDK functions cover four network/localization files only. MC, pad and most runtime code remain explicit assembly in `game/lib.cpp` and `game/lib_after_libm.cpp`. See [SDK scope](SDK.md) and [the folder map](../../code/sdk/README.md). No larger SDK percentage is established by this survey.

## Public revisions compared

These are date-selected Git snapshots, not claimed numbered PS2SDK releases. The 2005 year-end revision postdates the game; it is a nearby comparison, not evidence that the game used it.

| Snapshot | Pinned revision | Assessment |
|---|---|
| 2004 | [d27397d3d88a](https://github.com/ps2dev/ps2sdk/tree/d27397d3d88a9a0c960b091cdda28e3a573cf7eb) | Useful older protocol baseline; ee/rpc/padx selects NEW_PADMAN. No ee/dma or ee/graph directory in this snapshot. |
| 2005 | [2886bea52303](https://github.com/ps2dev/ps2sdk/tree/2886bea52303c1ccfdf56767fd61c0fe0af8d038) | Same pad/padx/multitap C file bytes as 2004; memory-card source changed. Adds ee/dma, ee/graph and math3d directories. Best nearby layout reference, not a byte-match claim. |
| 2006 | [fbdea39a7d70](https://github.com/ps2dev/ps2sdk/tree/fbdea39a7d700e743ea950427beefaa0af43edc3) | pad/padx files are two bytes longer than earlier snapshots; memory-card file matches 2005. No evidence this is a better matching source. |
| current | [329e2bb43287](https://github.com/ps2dev/ps2sdk/tree/329e2bb43287e16af16c4dde1c614e2662c24468) | Modern combined old/new pad handling and expanded tree; useful documentation, least appropriate assumption for original code generation. |

The inspected reference files declare AFL-2.0; see the pinned [LICENSE](https://github.com/ps2dev/ps2sdk/blob/d27397d3d88a9a0c960b091cdda28e3a573cf7eb/LICENSE) and [README](https://github.com/ps2dev/ps2sdk/blob/d27397d3d88a9a0c960b091cdda28e3a573cf7eb/README). Public availability alone is not the provenance criterion. Preserve applicable notices/license and record adaptations if code is later reused; no third-party source has been added to production code in this survey.

## Concrete differences that rule out a straight import

### Memory card

`sceMcInit` at `0x00139EC8` has a `0x228`-byte body. Retail creates two semaphores, synchronizes/waits, binds RPC `0x80000400`, sends initialization command `0xFE`, then requires server version >= `0x20A` and manager version >= `0x20E`. These thresholds describe IOP module compatibility, not the SDK release number.

The public [mcInit(type)](https://github.com/ps2dev/ps2sdk/blob/d27397d3d88a9a0c960b091cdda28e3a573cf7eb/ee/rpc/memorycard/src/libmc.c) selects MC/XMC at runtime. Its XMC path uses the same RPC family, but the old source checks `0x205` / `0x206` and lacks retail's semaphore setup. Current inspected source retains those older thresholds. Merely renaming functions or choosing a compiler cannot produce retail bytes from this unchanged implementation.

### Pad

`scePadInit` at `0x0013B1D0` binds `0x80000100` and `0x80000101`, requires `(moduleVersion >> 8) == 4`, and calls a separate `scePadInit2`. The public old ROM-pad variant binds `0x8000010F` / `0x8000011F`, so it is the wrong protocol family.

The public [padx source](https://github.com/ps2dev/ps2sdk/blob/d27397d3d88a9a0c960b091cdda28e3a573cf7eb/ee/rpc/padx/src/libpadx.c) selects NEW_PADMAN and the matching RPC IDs. However, its version result is not enforced, state initialization is organized differently, and it returns a different initialization convention. This makes padx the relevant reference, not a matching implementation.

`scePadRead` at `0x0013BA20` tests whether the port is open and asks `scePadGetDmaStr` to fill a stack snapshot; its length comes from snapshot offset `0x60`. The old public implementation reads directly from a selected DMA buffer. The new-pad public data layout also places length at `0x60`, which is useful ABI evidence but does not establish matching control flow or memory-synchronization behavior.

### Multitap

Retail `sceMtapInit` at `0x0013AEF8` binds `0x80000900`. The inspected public [multitap source](https://github.com/ps2dev/ps2sdk/blob/d27397d3d88a9a0c960b091cdda28e3a573cf7eb/ee/rpc/multitap/src/libmtap.c) instead binds three services `0x80000901` / `02` / `03`. Do not treat it as a direct replacement.

## Recommended implementation order

1. Recover the small DMA block and SCF helpers directly from retail, while testing compiler/assembler settings per block. The existing SDK networking compiler profile is not proof for every runtime library.
2. Recover pad with the public historical padx layout as a reference and retail as authority. Keep retail snapshot/cache behavior, globals and module checks.
3. Recover MC with the extended RPC family as a reference; preserve retail semaphore and callback behavior. Do not substitute older public minimum versions.
4. Split larger kernel/SIF/CDVD/graphics/MPEG blocks only after checking helper ownership, adjacent data, padding and original entry addresses. Keep newlib and compiler runtime separate.

This order is an engineering estimate based on visible scope, not a measured completion-time promise. Moving INCLUDE_ASM wrappers into sdk/ would improve organization but would not decompile them.

## Validation and limits

Compared public 2004, 2005, 2006 and pinned-current files and public tree layouts (2004, 2005, current). Verified the inspected retail assembly against ELF-loaded addresses: MC init 552 bytes, pad init 336 bytes including padding, pad read 120 bytes including padding. Used Ghidra for cross-checking; its MC decompilation incorrectly terminates at WaitSema, so assembly governs the full routine.

No SDK source was compiled in this survey, no full build/gameplay test was run, and no source/split/Makefile/manifest was changed. No new exact functions or progress percentage are claimed. The named-function counts in the folder map omit unnamed helpers and are not completion denominators.

Reproducible reference SHAs, file hashes, ELF identity, stamps and named-function inventory are in [SDK_FINGERPRINTS.json](SDK_FINGERPRINTS.json). Downloaded public references and scratch scripts are under `build/sdk-survey/` (ignored build data).

## Boot DMA implementation follow-up

The retail DMA block has now been split and five functions recovered directly from boot instructions, with EE GCC 2.9 (991111-01) producing exact bytes. No vendor sources were imported. See [the implementation record](SDK_DMA.md); the earlier survey remains reference research, not a matching claim for other components.
