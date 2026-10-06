# ProjectRYNO: instructions for AI contributors

Read this file before editing. It is the main rule set for every game in this
repository: rac, gc, uya, and dl. Game-specific examples must be adapted using
that game's own verified configuration; do not transplant Deadlocked addresses.
Follow the user's current scope and preserve unrelated work. These instructions
support authorized work; they do not create extra approval gates or authorize
publishing, deleting someone else's work, or changing unrelated tools.

## Start here

* Locate the Git root (the parent of this file's `.agents` directory). A surrounding
  workspace may also be called ProjectRYNO. Run `git status --short` here.
* Read [source conventions](../docs/decompilation/STYLE.md) before code edits.
* Read [the shared game workflow](guides/GAME_WORKFLOW.md) for strict matching and
  bringing up another game.
* For Deadlocked, read [AI workflow and commands](guides/DEADLOCKED.md) for environment
  setup, validation choices, clean builds, ISO packaging, and handoff requirements.
* Load only the relevant skills below. They are ordinary Markdown instructions;
  assistants without a skill loader should read the indicated `SKILL.md` directly.

| Task | Repository skill |
| --- | --- |
| Replace an INCLUDE_ASM function with C/C++ | [.agents/skills/ryno-decompile/SKILL.md](skills/ryno-decompile/SKILL.md) |
| Recover global names, declarations, structs, or headers | [.agents/skills/ryno-symbols-types/SKILL.md](skills/ryno-symbols-types/SKILL.md) |
| Split, compile, diagnose builds, audit an ELF, or pack an ISO | [.agents/skills/ryno-build-verify/SKILL.md](skills/ryno-build-verify/SKILL.md) |

## Invariants

1. Require identical executable bytes, retail runtime layout, and in-game behavior.
   Run the strict loaded-byte/header comparison; functional tests and allowed-slot
   audits alone do not establish 1:1 matching. Build output must genuinely
   come from compiled source and remaining split assembly, not a copied original
   ELF or executable bytes substituted for the function being decompiled.
2. Original public entry addresses, data addresses, load segments, and bytes
   inside and outside replacement slots must match for a completed build. Existing
   nonmatching replacements remain unfinished under this requirement. For the
   Deadlocked placement mechanism, register replacements
   in `config/decompiled_functions.yaml`; never hide failures by widening allowed
   ranges, restoring fallback symbols, removing assertions, or suppressing tests.
3. Keep Makefile/linker changes minimal. Fix source, symbols, manifest, or splitter
   inputs where appropriate. Generated `config/*.ld`, `code/asm`, and `build/`
   are not durable places for fixes. Read the generator before changing its output.
4. Finish `make split` before compiling. Never run `make -j8 split elf`, overlap
   splitting with compilation, or run two builds in the same output directory.
   `-j8` parallelizes jobs within a target; it does not enforce pipeline ordering.
5. Headers and INCLUDE_ASM files are not fully tracked as dependencies. After
   changing them, force the affected objects to rebuild; `make -B -j8 elf` is the
   straightforward full rebuild. After symbol/manifest/split changes, split first.
6. In Deadlocked, keep `ALLOW_NONMATCHING=0` (the default). Setting it to 1 suppresses assembly
   still needed by this mixed C/assembly build. PERMUTER is for host tests only.
7. Retail instructions determine behavior and addresses. Ghidra pseudocode,
   prototype sources, `dltypes.txt`, `dlglobals.txt`, and external ports are
   evidence, not interchangeable versions of the retail executable.
8. Name existing storage with ordinary `extern` declarations and symbol-file
   mappings. Do not allocate a duplicate global, invent a prototype-to-retail
   address delta, or guess layouts to make the compiler accept a declaration.
9. Use the original module grouping. In Deadlocked, keep boot-option functions in `boot.cpp`.
   Preserve per-function section attributes required by the fixed-address slots,
   even though ordinary organization should otherwise be at file/module level.
10. Keep tests outside production headers/source; do not restore SND_HOST_TEST
    branches or header size-check typedefs. Extend external ABI/behavior checks
    for meaningful new behavior. A cosmetic/documentation edit needs no ELF build.

## Nonmatching development builds

The user permits building, packing, and running nonmatching development builds
while working toward exact matching. Report their strict-comparison failures
clearly; do not block ordinary compile/test work merely because C output differs.
A slot-audit pass remains different from an exact-matching pass.

## Reliable completion

Inspect the relevant source, manifest, and tool implementation before editing.
Record uncertain identifications separately; retain assembly when a function's
behavior or placement has not been established. Use the smallest meaningful
validation for the change, and investigate failures rather than relaxing checks.
Report what changed, what passed, and what was not exercised. Successful linking,
ELF auditing, ISO packing, emulator boot, and gameplay are separate claims.
Maintain the workflow/skills when changing the mechanism they describe. Historical
counts, compiler output sizes, and generated report paths in older docs are not
proof of the current checkout's behavior.
