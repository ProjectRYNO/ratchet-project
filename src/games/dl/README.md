# Ratchet: Deadlocked

Decompilation of the NTSC-U retail boot ELF (`SCUS_974.65`).
See the [documentation index](DOCS/README.md) for build instructions, library
research, recovered types, and verification records.

## Boot ELF decompilation progress

Snapshot: **2026-10-19**. Percentages are by tracked function count, not code size.
**Decompiled** means implemented in C/C++; **byte-matching** counts only compiled
functions verified against retail. Retained assembly does not count as decompiled.

| Section | Tracked functions / entries | Decompiled | Recorded byte-matching |
| --- | ---: | ---: | ---: |
| [Boot and startup](code/game/boot.cpp) | 15 | 3 / 15 (20.00%) | 0 / 15 (0.00%) |
| [Game and engine](code/game) — excluding boot and library aggregates | 4,718 | 0 / 4,718 (0.00%) | 0 / 4,718 (0.00%) |
| Other runtime and SDK code — [lib.cpp](code/game/lib.cpp), [lib_after_libm.cpp](code/game/lib_after_libm.cpp) | 1,314 | 0 / 1,314 (0.00%) | 0 / 1,314 (0.00%) |
| [989snd audio client](DOCS/sound/989SND_MATCHING.md) | 59 | 59 / 59 (100.00%) | 59 / 59 (100.00%) |
| [SDK networking/localization](DOCS/libraries/SDK.md) (`code/sdk/`) | 20 | 20 / 20 (100.00%) | 20 / 20 (100.00%) |
| [Medius networking](DOCS/libraries/MEDIUS.md) | 1,462 | 37 / 1,462 (2.53%) | 37 / 1,462 (2.53%) |
| [SVO3](DOCS/libraries/SVO3.md) | 934 | 934 / 934 (100.00%) | 899 / 934 (96.25%) |
| [iksemel XML](DOCS/libraries/IKSEMEL.md) | 40 | 40 / 40 (100.00%) | 40 / 40 (100.00%) |
| [newlib/libm mathematics](DOCS/libraries/NEWLIB_LIBM.md) | 37 | 37 / 37 (100.00%) | 37 / 37 (100.00%) |
| **Boot ELF tracked total** | **8,599** | **1,130 / 8,599 (13.14%)** | **1,092 / 8,599 (12.70%)** |

**Level overlays are outside this table and have not been started.** Boot ELF
completion does not represent completion of the entire game.

The game/runtime rows still contain unidentified assembly entries, some of which
may prove to be padding or fragments. These are source-inventory estimates, not
an exhaustive, fully classified retail function census. The two known SDK
instruction fragments are excluded; the SDK row covers `code/sdk/` only, not all
Sony library code elsewhere in the executable. Explicit textbin padding and data
are not functions and do not contribute to these percentages.

See the [library-folder survey](DOCS/libraries/BOOT_LIBRARY_INVENTORY.md) for
additional runtime, Sony SDK, Nellymoser and Logitech code still bundled in the
aggregate library files, plus unclassified configuration blocks.

### Evidence and updates

Implementation counts come from current `INCLUDE_ASM` entries plus
[registered compiled functions](config/decompiled_functions.yaml), excluding
`code/asm/` and duplicate `newlib/libm/upstream/` sources. Matching counts use the
latest module reports: [989snd](DOCS/progress/989SND.json),
[SDK](DOCS/progress/SDK.json), [iksemel](DOCS/progress/IKSEMEL.json),
[libm](DOCS/progress/LIBM.json), and the linked Medius/SVO3 notes. The SVO3 figure
is its 2026-10-18 report; 35 compiled functions remain nonmatching. All three
compiled boot functions also remain nonmatching.

These reports describe different verification snapshots, including ongoing local
SVO3 work. Their combined total is a progress summary, not a new whole-ELF match
claim or gameplay test. The general [function tracker](DOCS/progress/README.md)
and its older summary have not yet been refreshed for all recent library work.
When updating this table, recount current sources, use each module's latest
verified matching result, and preserve the distinction between implementation
and matching progress.
