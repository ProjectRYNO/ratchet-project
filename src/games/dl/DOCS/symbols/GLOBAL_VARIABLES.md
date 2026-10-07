# Retail global-variable map

The symbol files now name **806 additional globals**, alongside the 54 globals
already recovered for boot and 989snd. No Makefile or linker-code changes are
needed. The added names live in the marked `RECOVERED RETAIL GLOBALS` block at
the end of `config/symbols_core.text.txt`.

| Examples | Retail address |
| --- | --- |
| `g_RandSeed` | `0x0021DC80` |
| `gFrameHz` | `0x0021DDA0` |
| `gNumLocalHeroes` | `0x0021DDA4` |
| `gameMode` | `0x0021DDB4` |
| `Level` | `0x0021DE10` |
| `screenMode` | `0x0021EDC8` |
| `g_gameType` | `0x0021EDD4` |
| `CollOutput` | `0x00239740` |
| `g_Hero` | `0x003367B8` |

Use ordinary `extern` declarations when decompiling references to these names.
For example, `extern unsigned int g_RandSeed;` resolves to the existing retail
storage. Do not add another definition/allocation to name that storage.

## Evidence and scope

The source of every address is the open Ghidra program
`DL_Retail_BootELF_974.65.elf` (`/Ratchet 4/PS2/NTSC-U/Retail_scus_974.65.elf`).
Names were cross-checked against `dlglobals.txt` and matching declarations in
`D:/PS2/ISOs/deadlocked-proto-decomp`. **No prototype addresses or presumed
version-wide address offsets were used.**

[GLOBAL_VARIABLES.csv](GLOBAL_VARIABLES.csv) records each retail label's
address, section, Ghidra type and reference count, prototype declaration,
original source file, `dlglobals.txt` line, matching prototype source line,
and mapping/deferment reason. Prototype declarations are reference material:
their type sizes, array lengths, and layouts still need retail validation before
being used in production headers. This pass names storage; it does not decompile
the data initializers or generate unverified struct layouts.

The accepted entries have a unique plain identifier and retail address, at
least one retail reference, an address in an allocated non-code section, and
matching prototype declaration/source evidence. Existing symbols are preserved.

The inventory contains 1,522 retail data labels: 806 newly mapped, 20 already
mapped by the same name, six already mapped under another name, and 690 deferred.
Hardware registers/out-of-image labels, namespace/mangled identifiers, missing
prototype declarations, unreferenced labels, and ambiguous duplicates were not
blindly imported. In particular, Ghidra's `M9454_Sparkles` label at `0x0022597F`
coincides with `_gp`; that is not sufficient evidence of an object at that address.
Two `__clz_tab` addresses and the shared `_fbss`/`errno` address also need review.

[GLOBALS_UNMAPPED.csv](GLOBALS_UNMAPPED.csv) records 1,926 prototype declarations
without an exact named retail counterpart. These are a research backlog, not
proof that all those variables exist in retail. Some names are class-scoped,
version-specific, or require matching references in a known retail function.

## Updating and checking

`../tools/map_dl_globals.py` inventories a fresh Ghidra `list_globals` text
export against the prototype tree and existing symbol files. It writes reports
and candidates, but never changes build inputs automatically. Example from the
game directory:

```sh
python3 ../tools/map_dl_globals.py --ghidra build/global-map/ghidra-named.txt --prototype /path/to/deadlocked-proto-decomp --game . --elf ../assets/dl/boot_elf.elf --output build/global-map
```

After editing symbol mappings, regenerate assembly and force object compilation:

```sh
make split
make -B -j8 elf
python3 tests/check_global_map.py build/boot_elf.elf
python3 tests/check_main_elf.py ../assets/dl/boot_elf.elf build/boot_elf.elf build/code/game/boot.o
```

The forced rebuild matters: the current Makefile does not track header or
`INCLUDE_ASM` dependencies. Cached objects can otherwise retain old `D_...`
references even after splitting regenerated the assembly with named globals.

Build and validation reports for this pass are under `build/global-map`.
The independent full-clean build passes the compiled-function/layout audit and
all 3,013 sound differential cases. The global-name audit confirms all 806 linked
addresses, and comparison with the pre-mapping ELF finds identical runtime
headers and all 5,158,456 loaded bytes. These checks establish that adding the
names did not change the executable's loaded contents.

The SVO3 library/tag-module batch names 115 existing string, vtable, singleton and
timer locations. [SVO3_GLOBALS.csv](SVO3_GLOBALS.csv) records owners and retail
reference evidence for these additions. They are aliases in symbols_core.text.txt,
with ordinary extern declarations and no new storage allocations. The rebuilt ELF
placement audit confirms all loaded bytes outside compiled function slots remain
unchanged; new behavior tests were deferred for this batch.
