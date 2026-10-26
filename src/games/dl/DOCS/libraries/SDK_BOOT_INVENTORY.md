# Identified boot SDK progress

**122/387 identified functions (31.52%) are decompiled and byte-matching** (2026-10-26).
This is a broader named-function inventory, not an exhaustive SDK census.
`code/sdk/` now also holds the pad, memory-card and kernel splits (`pad/libpad.c`,
`mc/libmc.c`, `kernel/libkernel.c`); every entry in those ranges has its own slot, and
functions not yet recovered (including handwritten kernel stubs) stay as retained assembly. Unknown routines are not silently counted
as complete. The denominator can grow as ownership is recovered.

| Component | Identified functions | Decompiled and matching |
|---|---:|---:|
| CD/DVD | 14 | 0 / 14 (0.00%) |
| DMA | 8 | 8 / 8 (100.00%) |
| IPU | 4 | 0 / 4 (0.00%) |
| MPEG | 11 | 0 / 11 (0.00%) |
| SIF | 50 | 19 / 50 (38.00%) |
| VU0 | 4 | 0 / 4 (0.00%) |
| configuration | 16 | 0 / 16 (0.00%) |
| file I/O | 18 | 7 / 18 (38.89%) |
| graphics | 15 | 0 / 15 (0.00%) |
| kernel/runtime | 180 | 26 / 180 (14.44%) |
| memory card | 17 | 17 / 17 (100.00%) |
| multitap | 8 | 8 / 8 (100.00%) |
| networking/localization | 20 | 20 / 20 (100.00%) |
| pad | 22 | 17 / 22 (77.27%) |

The machine-readable inventory is [SDK_BOOT.csv](../progress/SDK_BOOT.csv), with
addresses, current source ownership and selection evidence. It starts with the
named families in SDK_FINGERPRINTS.json, adds the verified C module helpers and
named INCLUDE_ASM entries in these identified ranges:

- Kernel, SIF and file I/O: `0x001267A0..0x0012EE30` (before compiler constructors).
- Memory card: `0x00139EC8..0x0013AE70`.
- Pad: `0x0013B1D0..0x0013C478`.
- Configuration: `0x00155510..0x00155AE0`.
- Additional SIF RPC: `0x00155AE0..0x00156390` (before SVO3 interface code).
- Named `sceMpeg*` APIs in the boot aggregate.

Unclassified `func_*` entries and unnamed MPEG/graphics helpers are excluded.
Kernel functions originally written in assembly remain counted as assembly;
this report measures recovered C/C++, not merely whether retained bytes match.
Newlib, compiler runtime, third-party libraries and overlays are excluded.

Matching claims come from the integrated check_sdk.py run, not from names or
retained assembly. This inventory does not change source ownership or split any
additional functions. See [multitap verification](SDK_MTAP.md).
