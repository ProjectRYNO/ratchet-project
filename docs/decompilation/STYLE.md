# Decompilation source conventions (all games)

* Header guards follow the filename, with a distinguishing suffix if needed,
  and no `RYNO_` prefix. For filenames starting with digits, use a valid
  identifier instead: `989snd.h` uses `SND_EE_H`.
* Put every struct member on its own line, repeating the type for each member.
* Omit redundant tags in typedef structs. Keep a tag only when needed, such as
  for self-references, forward declarations, or existing `struct Tag` uses.
* Add the PS2 structure size after the opening declaration, and the byte offset
  before each member, following `dltypes.txt`:

```c
typedef struct { // 0x08
    /* 0x00 */ int a;
    /* 0x04 */ int b;
} Example;
```

Sizes and offsets describe the original PS2 ABI, not the host compiler's ABI.
Keep recovered functions in their original source-file grouping. In Deadlocked, the boot-option
encoder and decoder belong in `code/game/boot.cpp`.

Recovered globals use ordinary `extern` declarations. Register their retail
addresses in the selected game's symbol configuration. In Deadlocked, use
`config/symbols_core.text.txt`, which is already consumed by the
splitter and symbol generator, rather than attaching `__asm__("D_...")` aliases
to C/C++ declarations. For example:

```text
sndLocBusy = 0x001A4878;
```

```c
extern const char sndLocBusy[];
```

These entries name the existing data; do not add another C definition just to
name it. Run splitting before rebuilding so generated assembly uses the names.
The current Makefile does not track header dependencies. After changing a
header's symbol bindings, remove the affected generated object or clean before
rebuilding; otherwise it may still reference the old names. For the sound
header, the affected object is `build/code/989snd/ee/989snd.o`.

Current exception to file-level section placement: compiled replacements use
individual section attributes because their sizes differ from the original
functions. The linker places each section at its original public entry address
and rejects overruns. A single section for the whole file would not preserve
those entry addresses. Keep these attributes until the build supports another
way to preserve each entry point.
