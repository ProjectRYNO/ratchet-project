# Shared game decompilation and build rules

[AGENTS.md](../../AGENTS.md) is the main rule set for every game in ProjectRYNO.
Use the same skills for `rac`, `gc`, `uya`, and `dl`; select the game-specific
configuration and evidence before running commands. Deadlocked is the current
worked example, not a source of universal addresses, compiler flags, or bounds.

## Required result: exact executable matching and behavior

A completed build must reproduce the original executable bytes and runtime
memory layout for the selected game/revision and preserve in-game behavior.
Compare every PT_LOAD byte, zero-filled memory, entry point, and runtime header.
There are no exemptions for decompiled-function slots. The strict gate is:

```sh
python3 ../tools/compare_elf.py ../assets/GAME/boot.elf build/boot_elf.elf
```

Run from `/ProjectRYNO/GAME`, replacing GAME with the selected game directory.
A zero exit code is required. The comparator supports little-endian ELF32; inspect
other formats before using it. File offsets, debug/symbol/section tables, and disc
packing metadata are not executable bytes. A full-file hash measures a separate,
stronger claim; report it separately when required. Never describe an ISO as a
byte-identical disc based only on its executable comparison.

Functional tests and a slot-aware audit are useful diagnostics, but do not waive
strict matching. If a function compiles to different instructions, it remains a
nonmatching work in progress even if it passes behavior tests. Investigate the
original compiler/version/options, ABI, code generation, and assembly. Do not
copy original machine words into a supposedly decompiled function, link a fallback
at the original address, restore original assembly invisibly, or widen audit
allowances to manufacture a pass. Remaining explicit INCLUDE_ASM functions are
legitimate split assembly, not completed C decompilations.

Executable matching is also not a claim that gameplay was tested. Verify boot,
controls, affected behavior, saves/state, and audio as relevant, and state the
observed coverage. Known legacy behavioral changes require reconciliation with
the matching goal; do not treat them as newly approved exceptions.

## Starting another game

1. Identify title, region, revision, source ELF hash, entry point, load segments,
   SDK/compiler evidence, and original disc. Keep each game's assets separate.
2. Inspect that game's YAML, symbols, source grouping, available build targets,
   and existing progress. Establish a split/assemble/link baseline that passes
   strict comparison before accepting C replacements.
3. Derive ROM packing from that ELF and YAML rather than using flat objcopy or
   transplanting Deadlocked's offsets. Derive entry/GP addresses and memory bounds
   from the selected game. Do not copy Deadlocked's Makefile and assume it works.
4. Use the shared Docker environment on Windows and Linux, with identical inputs
   and toolchain. `src/games/requirements.txt` pins the validated splitter stack. Verify a fresh case-sensitive checkout, LF shell scripts, exact
   include/source filename case, and serial split/build stages.
5. Introduce C/C++ functions with original module ownership and correct ABI;
   preserve exact public placement and loaded bytes. Add appropriate tests and a
   manifest/placement mechanism for that game if missing. Keep implementation
   changes to build tooling justified and small.
6. Run strict matching and relevant behavior tests after executable changes;
   use an isolated clean build to validate the pipeline. Package only a verified
   executable for a release described as matching. Experimental nonmatching builds
   must be explicitly labeled as such.

## Current support, not assumed support

| Directory | Configuration | Build status at this review |
| --- | --- | --- |
| rac | SCUS_971.99.yaml | Configuration/source scaffolding; no game Makefile yet |
| gc | SCUS_972.68.yaml | Configuration/source scaffolding; no game Makefile yet |
| uya | SCUS_973.53.yaml | Configuration/source scaffolding; no game Makefile yet |
| dl | SCUS_974.65.yaml | Mixed C/assembly build and audits; existing C replacements are nonmatching |

The current Deadlocked code predates the exact-matching requirement. Its
slot-aware audit allows deliberate C instruction changes, and its boot options
include documented deterministic-padding/bounds changes. These are a matching
backlog, not proof of a 1:1 result. Do not present a slot-audit PASS as strict PASS.
Use the live comparator results instead of historical byte counts.

## Source organization and handoff

Follow [shared source conventions](../../docs/decompilation/STYLE.md) for all games. Recover names/layouts
from the selected game's retail evidence; prototype layouts and same-named types
in another game can differ. Keep build inputs, tests, and provenance in version
control and locally supplied disc/ELF assets out of it.

Use [Deadlocked's workflow](DEADLOCKED.md) for its concrete
commands and tests. When another game becomes buildable, add its own concise
profile and verification evidence without duplicating or weakening these rules.
Record the host/toolchain, exact inputs, strict comparison result, behavior-test
coverage, and any failures in the handoff. Windows/Linux equivalence requires
comparing the rebuilt loaded images, not merely two successful exit codes.

For the latest platform checks and known matching backlog, see
[PLATFORM_VERIFICATION.md](../../docs/build/PLATFORM_VERIFICATION.md).
