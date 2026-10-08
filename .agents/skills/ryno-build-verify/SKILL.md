---
name: ryno-build-verify
description: Split, compile, audit, clean-build, and package ProjectRYNO ELF/ISO outputs, or diagnose build failures while preserving the retail memory layout.
---

# Build and verify a game

Use [the shared game workflow](../../guides/GAME_WORKFLOW.md) for every game.
The concrete manifests, symbols, tools, and tests below describe Deadlocked;
verify or implement equivalents for the selected game rather than copying its
addresses. Require strict executable matching before calling a change complete.

Read [AGENTS.md](../../../AGENTS.md) and use the actual commands in
[AI_WORKFLOW.md](../../guides/DEADLOCKED.md). Inspect current
Makefile/tool behavior when it differs from historical documentation.

Identify the checkout, container/mount, extracted asset ELF, and intended game
revision. Preserve existing user work and diagnostic evidence. Use a separate
container/output directory for clean-build experiments. Do not assume a previous
assistant's container name, drive paths, Ghidra port, or generated reports exist.

Run pipeline stages sequentially. Use -j8 for independent compilation jobs only.
After split/config/manifest/symbol changes, complete `make split` before forced
compilation. After header/include/flag changes, invalidate affected objects or
use `make -B -j8 elf`. The image may not have EE GCC until `make ps2dev` succeeds.
Stop a failing pipeline; later successful commands must not hide its exit code.

Run the ELF audit for executable changes, then the checks relevant to the changed
subsystem. Keep original-versus-compiled comparison separate from comparing two
builds of the same source. The strict comparison must pass even inside declared
C slots. The existing
slot-aware audit is a diagnostic for historical nonmatching work, not a substitute
for matching. Do not waive a mismatch because behavioral tests passed. File hashes
alone cannot distinguish executable differences
from symbol tables and other non-runtime metadata.

## Diagnose from the first failure

* Old D_ references after renaming: resplit, then force recompilation; headers and
  included assembly are not fully tracked. Do not add fallback aliases to hide a
  stale object without checking it.
* Entry/slot/section mismatch: inspect the map, object sections, symbol sizes,
  manifest, and generated layout. Do not relax the assertions or widen slots.
* Changes outside replacement slots: investigate ROM packing, alignment,
  relocation pairs, object ordering, and generated padding. See
  [ELF_REBUILD.md](../../../src/games/dl/DOCS/build/ELF_REBUILD.md) for known failure modes.
* 989snd size/behavior regression: preserve its object-specific compiler flags
  and retained remnant sections; examine compiler output and run both sound suites.
* R5900 short-loop or RWX-segment warnings: these occur in the existing build;
  distinguish them from actual errors, but investigate new warnings in context.
* Linux-only failures: inspect exact path/filename case. Existing tracked tests
  may use `TESTS` while local Windows commands historically used `tests`; use the
  actual checkout's names and report/fix a portability issue within task scope.

For ISO work, audit the ELF and run `make iso`. It depends on `elf` and uses
`assets/dl/config.ini` with the container's ratchet-ps2 CLI. Verify the installed
ELF and preserved source-disc bytes using `tools/verify_boot_iso.py`.

For emulator verification, record the ELF/ISO used, relevant configuration, log,
and furthest observed stage. A boot through initialization is not gameplay or
sound correctness. Report compile, audit, clean-build, pack, boot, and gameplay
results separately; never claim a check that was not performed.

For CLI extraction and boot-only packaging, see
[ratchet-ps2-cli integration](../../../docs/build/RATCHET_PS2_CLI.md).
`src/games/tools/build_dl_cli.ps1` builds the ELF and reads `assets/dl/config.ini`
for packaging; `-SkipCompile` packages an already-built ELF. It preserves original
ISO assets and replaces only the boot executable, not edited level overlays.
Keep the same ELF audits and avoid overlapping compilation in a shared DL tree.
The native reference ELF is `src/games/assets/dl/boot.elf`; level overlays use
`assets/dl/levels/<four-digit ID>/code/overlay.elf`. The compiled output remains
`dl/build/boot_elf.elf`. Historical reference files may coexist but are not the
inputs to the current ROM, verifier, or progress tools.

Use [the verification entry point](../../../docs/build/VERIFICATION.md) for combined
checks and machine-readable results. Nonmatching development output remains usable;
only the optional strict gate treats byte differences alone as a failing exit.
