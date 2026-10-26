# Deadlocked SDK source map

Implemented here: `libezcnf.c`, `libezctl.c`, `i18n.c`, `i18n_inet.c`, `dma/libdma.c`, `mtap/libmtap.c`, `pad/libpad.c`, `mc/libmc.c` and `kernel/libkernel.c` (the last three are split by retail range and keep unrecovered entries as retained assembly). **175 SDK functions compile to exact retail bytes**: memory card 17/17, pad 17/22, kernel/SIF/file I/O 105 of the range. Networking/localization is 20/20; [DMA](../../DOCS/libraries/SDK_DMA.md) is 8/8.

The boot ELF also contains the following runtime components, mostly retained under `code/game/lib.cpp`, `lib_after_libm.cpp`, and `lib_after_dma.cpp`. This table is a destination map for future verified splits, not a claim that these directories or decompiled implementations already exist. Folder names describe functionality, not recovered original archive-member names.

| Proposed sdk/ directory | Scope | Public PS2SDK comparison path | Retail evidence |
|---|---|---|---|
| kernel/ | Kernel calls, threads, semaphores, cache | ee/kernel | SetGsCrt, CreateThread, CreateSema |
| sif/ | EE/IOP command, RPC, heap, loader | ee/kernel | sceSif* (46 named entries, including mrpc) |
| fileio/ | IOP file access | ee/kernel; ee/rpc/filexio is a different extended API | sceFsInit, sceOpen, sceRead |
| cdvd/ | Disc and drive RPC | ee/rpc/cdvd | sceCd* (14 named entries) |
| graph/ | GS setup, environments and transfers | ee/graph; current ee/libgs | sceGs* (15 named entries, in separated regions) |
| dma/ (split and complete) | DMA channel control; 8/8 exact C functions | ee/dma (present in 2005 snapshot) | sceDma* (5 named entries plus helpers) |
| mc/ | Memory-card RPC and synchronization | ee/rpc/memorycard, XMC variant | sceMc* (14 named entries plus helpers) |
| mtap/ (split and complete) | Multitap RPC; 8/8 exact C functions | ee/rpc/multitap (different RPC service IDs) | sceMtap* (7 named entries) |
| pad/ | Controller RPC and DMA snapshots | 2004/2005 ee/rpc/padx; current ee/rpc/pad | scePad* (20 named entries plus helpers) |
| vu0/ | VU0 matrix routines | ee/math3d; current ee/libvux, not direct equivalents | sceVu0* (4 named entries) |
| mpeg/ | MPEG decoding and PSS demultiplexing | current ee/mpeg; not established for older snapshots | sceMpeg*, _dualPrimeVector |
| ipu/ | IPU hardware helpers | inspect current ee/mpeg; no matching module proven | sceIpu* (4 named entries) |
| scf/ | Console configuration and RTC conversion | ee/kernel configuration helpers | sceScf* (5 named entries) |
| mrpc/ | Additional SIF RPC helpers | ee/kernel SIF RPC is only a starting lead | PsIIlibmrpc 3000; sceSifMCallRpc |

Counts are named symbol entries from `symbols_core.text.txt`; unnamed/internal routines are additional. They are not the total SDK function count.

Do not populate this tree by copying the whole public SDK: EE/IOP boundaries, link-selected functions, data ownership and implementation versions differ. IOP drivers are separate modules and are not automatically part of the EE boot executable. Newlib libc/libm, libgcc, Nellymoser and Logitech should retain separate ownership.

Declarations for C code that calls the SDK: Medius objects compile with the open-source PS2SDK headers from the image (`PS2SDK_FLAGS` in the Makefile), so `kernel.h`, `libcdvd-common.h` and similar supply prototypes and structs. Retail Sony calls that PS2SDK does not declare (currently `sceDevctl` and `sceScfGetLocalTimefromRTC`) live in [sce_missing.h](sce_missing.h), with their retail-derived signatures and first user. These headers only declare; they are not reimplementations and do not change what is linked.

Provenance constraint for this work: use the user-supplied retail executable and appropriately licensed public references; do not obtain or import official Sony SDK sources. PS2SDK is a separate homebrew project, not an open-source release of the Sony SDK.

See [version evidence and comparison results](../../DOCS/libraries/SDK_LAYOUT.md) before implementing or moving any block. The strongest starting reference for pad is historical `padx`; MC uses the extended RPC family. Neither is a byte-matching drop-in. Preserve original addresses, behavior and padding, and verify each new split before claiming progress.

Broader boot SDK tracking: **175/387 identified functions (45.22%)** are decompiled and byte-matching; this is an incomplete named-function inventory, not an all-SDK census. See [inventory](../../DOCS/libraries/SDK_BOOT_INVENTORY.md) and [multitap verification](../../DOCS/libraries/SDK_MTAP.md).
