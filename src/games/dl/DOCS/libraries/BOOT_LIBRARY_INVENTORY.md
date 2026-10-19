# Boot ELF library inventory

Survey: 2026-10-19. The game's split configuration is
[`SCUS_974.65.yaml`](../../config/SCUS_974.65.yaml), not `config.yml`.
This is a source/configuration survey, not a new build or compiler identification.
No split entries, function ownership or source files were moved.

## Already separated in the YAML

| Source group | Active C/C++ split entries | Current scope/status |
| --- | ---: | --- |
| `989snd/ee` | 1 | 59/59 functions compiled and exact |
| `sdk` | 6 | 36/36 real functions compiled and exact; networking/localization, DMA and multitap |
| `newlib/libm` | 37 | 37/37 functions compiled and exact |
| `iksemel/src` | 5 | 40/40 functions compiled and exact |
| `svo3` | 97 | 934/934 functions compiled; 899 exact in the latest module report |
| `medius` | 84 | 37/1,462 tracked entries compiled and exact; substantial work remains |

Medius already contains separate subtrees for `rt_libnet`, `dme_client`,
`dme_object`, `rt_util`, `rt_comm`, `rt_udp`, `rt_upnp`, `rt_msg`, `rt_crypt`,
`rt_ssl`, `rt_cert`, `StreamMedia`, `MediusClientLibrary`, `MediusDList` and
`MediusMessage`. Those are unfinished areas inside an existing library tree,
not missing top-level folders. The commented `mbill_cache`, `mbill_register`,
`rt_hash`, and `mbill_callback` entries have no offsets; they are research
placeholders, not confirmed active translation-unit splits.

## Candidate library folders still hidden in aggregate sources

Although physically under `game/`, the two library aggregates contain substantial
third-party/runtime code. The paths below are **proposed organization**, not
confirmed original archive/member names or approved split boundaries. Representative
symbols and addresses come from `config/symbols_core.text.txt`; the current
implementations are explicit `INCLUDE_ASM` entries.

| Candidate folder | Identified code | Representative retail evidence |
| --- | --- | --- |
| `newlib/libc/` | C library: memory/string, stdio, allocation, conversions | `memcpy` at `0x0011A370`, `malloc` at `0x0011EF60`; `printf`, `strtod`, `_malloc_r` |
| `libgcc/` | Compiler runtime, integer arithmetic and software floating point | `__divdi3` at `0x0012EF00`; `__do_global_ctors`, `dpadd`, `dpdiv`, `fptodp` |
| `sdk/kernel/` | Kernel syscall wrappers, threads, semaphores, cache and timers | `SetGsCrt` at `0x001267A0`; `CreateThread`, `CreateSema`, `FlushCache` |
| `sdk/sif/` | EE/IOP command, RPC, heap, module loading and reboot support | `sceSifInitCmd` at `0x00129660`, `sceSifInitRpc` at `0x00129D90`, `sceSifInitIopHeap` at `0x0012C1B8` |
| `sdk/fileio/` | IOP-backed file access | `sceFsInit` at `0x0012B068`; `sceOpen`, `sceRead`, `sceWrite` |
| `sdk/cdvd/` | Disc access and drive control | `sceCdCallback` at `0x00136DA8`; `sceCdInit`, `sceCdRead`, `sceCdSync` |
| `sdk/graph/` | GS setup, drawing environments and transfers | `sceGsResetGraph` at `0x00138350`; also `sceGsResetPath` at `0x00131968` before libm |
| `sdk/dma/` | DMA channel setup/control | `sceDmaGetChan` at `0x00139AB8`; `sceDmaSend`, `sceDmaPause` |
| `sdk/mc/` | Memory-card access | `sceMcInit` at `0x00139EC8`; `sceMcRead`, `sceMcWrite`, `sceMcGetDir` |
| `sdk/mtap/` | Multitap support | `sceMtapSetWorkAddr` at `0x0013AE98`; `sceMtapPortOpen` |
| `sdk/pad/` | Controller support | `scePadInit` at `0x0013B1D0`; `scePadRead`, `scePadSetActDirect` |
| `sdk/vu0/` | VU0 matrix/math helpers | `sceVu0UnitMatrix` at `0x0013C478`; `sceVu0RotMatrixX/Y/Z` |
| `sdk/mpeg/` | MPEG decoding and PSS demultiplexing | `_dualPrimeVector` at `0x0013C750`; `sceMpegCreate`, `sceMpegGetPicture`, `sceMpegDemuxPssRing` |
| `sdk/ipu/` | IPU hardware control | `sceIpuStopDMA` at `0x001467C0`, `sceIpuInit` at `0x00146AD8` |
| `sdk/scf/` | Console settings and clock conversion | `sceScfGetLanguage` at `0x001555C0`; `sceScfGetAspect`, `sceScfGetLocalTimefromRTC` |
| `nellymoser/` | Voice encoding/decoding, FFT and speech processing | `NellyFftCenter512` at `0x00146E68`; `NellyEncodeSC`, `nciEncodeSase3200`, `nciTripleDecodeSase3200` |
| `logitech/audio/` | Logitech audio/headset interface | `lgAudInit` at `0x001518C8`; `lgAudRead`, `lgAudStartRecording` |
| `logitech/kbm/` | Logitech keyboard/mouse interface | `lgKbdOpen` at `0x00154270`, `lgMouseClose` at `0x00154F70` |

The SDK folder names here describe functionality; adjacent routines and unnamed
labels require individual ownership checks before splitting. Some kernel, VU and
compiler-runtime routines may be original hand-written assembly, so they should
not automatically be treated as recoverable C functions. The `sn_*` math routines
near the start of `lib.cpp` also need separate provenance; libm's completed
37-function block does not include them.

The aggregates additionally contain SVO/browser adapters and destructors starting
with `__dt__CDrawContextBase` at `0x00156390`. These may be library-generated stubs
or game integration code; classify them before assigning a new folder. The
934-function SVO3 completion figure is scoped to `code/svo3/`, not this unclassified
aggregate tail. `KM_GetSoftwareID`/`KM_GetSoftwareKeyPair` likewise need provenance
before assigning them to a vendor library.

## Other configured areas needing classification

* `vutext/000000` is a raw textbin block at VRAM `0x00100080`, ROM `0x000000`.
  It is a candidate for a VU microcode inventory, not an identified C library.
* `crt0` is an assembly startup entry at VRAM `0x001574E8`, ROM `0x057468`.
  It is runtime startup rather than a missing middleware library.
* `net.nostomp/4E5380` is an assembly split at VRAM `0x01F31380`, ROM `0x4E5380`,
  spanning `0x6C20` bytes to the configuration's end. Its contents and ownership
  need inspection before calling it another library or counting functions.
* `core.data`, `core.rdata`, `core.lit`, `lit`, `data`, `patch.data` and the
  `lvl.*vtbl` sections are data groupings. `junk/` denotes retained padding or
  remnants. Their names are not evidence of additional undecompiled libraries.

## SDK version and layout follow-up

The [SDK survey](SDK_LAYOUT.md) now records actual boot-ELF version stamps,
public PS2SDK revision comparisons, and MC/pad/multitap protocol differences.
The [SDK directory map](../../code/sdk/README.md) makes the proposed destinations
visible from `code/sdk/`. An additional `PsIIlibmrpc 3000` stamp at `0x0016FC30`
identifies another RPC library lead; no new split or decompilation is claimed.

## Suggested next work

The clearest additional source-based targets are `newlib/libc` and `libgcc`,
following the completed libm investigation. For a smaller Sony module, investigate
DMA, multitap or system settings. Nellymoser and Logitech are separate substantial
backlogs. This prioritization reflects the visible grouping and source-family
leads; no compiler match or exact module boundary has been established here.

Before moving any block: confirm retail function/data boundaries and original
source ownership, preserve entry addresses and padding, update durable YAML and
manifest inputs, then split serially and compare the rebuilt loaded bytes.

DMA implementation follow-up: the boot range `0x001399E0..0x00139EC8` now belongs to `sdk/dma/libdma.c`; all eight real functions are exact C. The following aggregate is `game/lib_after_dma.cpp`. See [DMA verification](SDK_DMA.md).

Broader boot SDK tracking: **36/387 identified functions (9.30%)** are decompiled and byte-matching; this is an incomplete named-function inventory, not an all-SDK census. See [inventory](SDK_BOOT_INVENTORY.md) and [multitap verification](SDK_MTAP.md).
