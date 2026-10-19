# Boot multitap recovery

All **8/8 real functions (100%)**, including the disabled variadic debug helper,
are C implementations matching **840 retail bytes**. The complete boot range
`0x0013AE70..0x0013B1D0` (864 bytes) matches, including zero padding and the final
`0xCDCDCDCD` word. That word is retained explicitly and excluded from function counts.
No overlays, IOP driver implementation, or vendor sources were imported.

| Function | Retail address | Exact compiled bytes |
|---|---|---:|
| DPRINT | 0x0013AE70 | 40 |
| sceMtapSetWorkAddr | 0x0013AE98 | 92 |
| sceMtapInit | 0x0013AEF8 | 256 |
| sceMtapEnd | 0x0013AFF8 | 28 |
| sceMtapPortOpen | 0x0013B018 | 108 |
| sceMtapPortClose | 0x0013B088 | 108 |
| sceMtapGetConnection | 0x0013B0F8 | 108 |
| sceMtapGetModVersion | 0x0013B168 | 100 |

The Makefile selects EE GCC 2.9 (991111-01), `-G0 -O2 -fno-builtin`, and its
bundled assembler, as for DMA. Initialization binds RPC service `0x80000900`,
retries until the client server word at +0x24 is set, and requires the module
version shifted right four bits to equal `0x31`. The original signed decrement
delay is retained. Init clears 128 work bytes and ignores SetWorkAddr's result,
as retail does. RPC command IDs are 1/2/3/5/6, with 128-byte request/reply buffers.

The client at `0x001AEE80`, packet at `0x001AEEC0`, and work area at `0x001AEF40`
remain existing storage. Word-array declarations describe accessed offsets without
claiming recovery of the entire SIF client structure. Diagnostics are also named
at their original addresses. The following source aggregate is now
`game/lib_after_mtap.cpp`, starting at `scePadInit` (`0x0013B1D0`).

## Verification (2026-10-19)

- Isolated serial split then `make -j8 elf`: passed, fallback disabled.
- `check_sdk.py`: all 36 SDK functions / 6,308 compiled bytes exact, with all six
  whole module ranges / 6,456 bytes exact.
- `check_main_elf.py`: passed; no changes outside existing registered slots.
- `check_global_map.py`: passed, 807 recorded globals.
- `sdk_mtap_test.c`: 48 host cases passed with mocked RPC, including negative
  transport returns, reply selection, bind retry/error, version rejection,
  work-buffer clearing, and the deliberately ignored SetWorkAddr result.
- Whole ELF comparison remains nonmatching: 1,340 bytes outside SDK (726 core,
  614 SVO3), with matching runtime headers. No gameplay/hardware test.

The snapshot retains the earlier validation-only SVO3 include-case correction
(`DnsCache.h` to `DNSCache.h`). Other local SVO3 changes were not edited.

Rebuilt SHA-256: `f2c7767a91697c9b71388591f5ee2163d215bdaaf4f122f1e860ede03d3664d2`. Logs: `build/medius_compiler_probe/sdk_mtap/logs`.

The broader [identified boot SDK inventory](SDK_BOOT_INVENTORY.md) is now
**36/387 (9.30%)** decompiled and matching. This is a named-function inventory,
not a complete census of every SDK helper in the boot image.

## Publication recheck after remote update

Pulled `cff526a` (Medius batch 4), merged both type additions, and clean-built
that remote base plus only the staged SDK files. The separate local SVO3 work
was preserved but excluded from this commit/build. All 36 SDK functions and
46 Medius functions still pass exact-byte checks. The slot and global audits
pass; recovered-layout checks pass 2,010 sizes/offsets across 228 types.

This publication snapshot has **2,172 differing bytes outside SDK** (726 core,
1,446 SVO3), reflecting the exclusion of those local SVO3 improvements. It is
not a whole-ELF match. Archive CRLF source endings were normalized to LF inside
the snapshot for the historical compiler, alongside the include-case correction.

Publication ELF SHA-256: `3424ee97decf01f5c1caefec86e2b1abbe18cd149fe4034989cb9696c717303b`. Logs: `build/medius_compiler_probe/sdk_mtap/publish-logs`.
