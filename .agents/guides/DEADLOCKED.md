# Deadlocked AI contributor workflow

[Shared rules for every game](GAME_WORKFLOW.md) require exact
executable matching. Current Deadlocked C replacements are nonmatching work in
progress; the existing slot audit does not satisfy that requirement.

Read the repository-root [AGENTS.md](../../AGENTS.md) first. It routes to
three focused skills under `.agents/skills`. Any assistant can read these files;
a proprietary skill loader is not required. `CLAUDE.md` and
`.github/copilot-instructions.md` point to the same rules rather than maintaining
separate versions. If your assistant does not discover instructions, start with:

> Read AGENTS.md and the relevant linked skill. Inspect this checkout before
> editing. Complete the requested change and its relevant validation, preserving
> the retail layout and reporting what was actually tested.

## Environment and authoritative inputs

Paths below are relative to the Git root, unless explicitly container paths.
The host checkout need not have the original author's drive/directory names.

| Item | Location / purpose |
| --- | --- |
| Docker build/compose setup | `src/games/Dockerfile`, `src/games/docker-compose.yml` |
| Container mount | `src/games` becomes `/ProjectRYNO` |
| Deadlocked working directory | `/ProjectRYNO/dl` |
| Original extracted ELF | `src/games/assets/dl/boot.elf` (reference input) |
| Main configuration | `src/games/dl/config/SCUS_974.65.yaml` |
| Compiled replacements and bounds | `src/games/dl/config/decompiled_functions.yaml` |
| Handwritten code/headers | `src/games/dl/code` (excluding generated `asm`) |
| Shared build tools | `src/games/tools` |
| Compiled ELF / map | `src/games/dl/build/boot_elf.elf`, `build/SCUS_974.65.map` |
| Packed ISO | `src/games/dl/build/new_dl.iso` |
| Tests | Git tracks `src/games/dl/TESTS`; some Windows worktrees use `tests` |

Check Docker and asset availability before a build. Build the image from
`src/games` with `docker compose build projectryno`, then enter a shell with
`docker compose run --rm projectryno`. Inspect existing containers before starting
or stopping one; never assume another contributor's container can be reused.
`make ps2dev` supplies the native Linux compiler used by Deadlocked (EE GCC 3.2.3).
Native executable extraction and boot-only ISO packing now use the sibling
ratchet-ps2-cli checkout; see [the integration guide](../../docs/build/RATCHET_PS2_CLI.md).
The Docker image builds the sibling CLI checkout as a self-contained Linux executable.
The image opens Bash directly; no Wine or Windows compiler installation is needed.
Keep the established image/toolchain versions unless toolchain work is requested.

The original ISO, extracted assets, prototype tree, and Ghidra project are local
inputs, not guaranteed to exist in a clone. Obtain their locations from the user
when needed; do not commit disc/ELF dumps or invent missing reference evidence.
The prototype input normally contains `game_dl`, `989snd`, `dltypes.txt`,
`dlglobals.txt`, and `dlfuncs.txt` (check the actual filenames). A previous local
location was `D:/PS2/ISOs/deadlocked-proto-decomp`; it is an example, not a dependency.

When Ghidra is available, confirm the selected executable/revision and language
before analysis. The established retail program was
`/Ratchet 4/PS2/NTSC-U/Retail_scus_974.65.elf`, R5900 little-endian 32-bit.
Use explicit program/address-space parameters. Discover available read tools such
as decompile_function, audit_global, get_struct_layout, and search_data_types.
A local bridge formerly used port 8089; discover the configured connection instead
of assuming that port or requiring a specific vendor integration. If unavailable,
use the extracted retail ELF/disassembly and record that limitation. Source files,
not unsaved GUI annotations, must contain everything necessary for a rebuild.

## Build stages: run sequentially

Inside the container, from `/ProjectRYNO/dl`, stop at the first failing command.
For a shell script, use `set -e`; with logging through a pipe, also use `pipefail`.

```sh
set -e
# Only if assets have not been extracted; ISO must be mounted/readable here:
# Export with ratchet-ps2 map export-executables on the host; see docs/build/RATCHET_PS2_CLI.md.
make ps2dev
make rom
make split
make -B -j8 elf
```

Existing source-only edits usually need just `make elf`; use a forced rebuild for
header, included assembly, or compiler-flag changes. Changes to splitting, symbols,
or manifest placement require a new split followed by forced compilation. Do not
combine split and elf as parallel make goals. Keep `ALLOW_NONMATCHING=0`.

The splitter preserves substantive handwritten C/C++ but regenerates assembly-only
wrappers. Confirm new implementations survive splitting. Edit configuration/tools
for durable generated-output fixes. Keep generated reports in a task-specific
`build/` directory, remembering that `clean` deletes that entire directory plus
assembly/includes/cache; `full-clean` additionally deletes the ROM. Preserve any
needed baseline/evidence outside a directory you intend to clean.

## Choose validation by the change

The following commands run inside `/ProjectRYNO/dl`. Resolve the test directory
once per shell so commands work on both case-sensitive and Windows-mounted trees:

```sh
if [ -d TESTS ]; then test_dir=TESTS; else test_dir=tests; fi
```

| Change | Checks |
| --- | --- |
| Documentation or cosmetic formatting | Review diff, links/paths, skill validation if applicable; no full build |
| C/C++ function behavior or placement | Rebuild, strict comparison, slot audit, focused behavior/differential checks |
| Globals / symbol bindings | Split, forced rebuild, global-address check, ELF audit |
| Struct layout / typed field access | EE layout check, forced rebuild of users, affected behavior checks, ELF audit |
| Splitter / link placement / extraction tools | Tool regression and linker-guard tests, isolated clean build, ELF audit |
| ISO packaging | Build/audit ELF first, pack, verify ELF source and packed payload |

Strict matching is required for a completed executable change:

```sh
python3 ../tools/compare_elf.py ../assets/dl/boot.elf build/boot_elf.elf
```

Additional diagnostics (choose those relevant to the task):

```sh
python3 "$test_dir/check_main_elf.py" ../assets/dl/boot.elf build/boot_elf.elf build/code/game/boot.o
python3 "$test_dir/check_global_map.py" build/boot_elf.elf
python3 "$test_dir/check_type_layouts.py"
python3 "$test_dir/test_989snd_wrappers.py" ../assets/dl/boot.elf build/boot_elf.elf
python3 "$test_dir/test_989snd_state.py" ../assets/dl/boot.elf build/boot_elf.elf
python3 "$test_dir/check_iksemel.py" ../assets/dl/boot.elf build/boot_elf.elf
python3 "$test_dir/check_svo_string.py" ../assets/dl/boot.elf build/boot_elf.elf
python3 "$test_dir/check_svo_core.py" ../assets/dl/boot.elf build/boot_elf.elf
python3 "$test_dir/check_svo_input.py" ../assets/dl/boot.elf build/boot_elf.elf
python3 "$test_dir/check_svo_memory.py" ../assets/dl/boot.elf build/boot_elf.elf
python3 "$test_dir/check_svo_config.py" ../assets/dl/boot.elf build/boot_elf.elf
python3 "$test_dir/check_main_link_guards.py"
python3 ../tools/test_elf_tools.py
```

Despite its historical name, `check_main_elf.py` audits all manifest-registered
replacements. It checks actual compiled definitions, placement, runtime headers,
and unchanged loaded bytes outside the slots. Do not widen slots to accept drift.
`compare_elf.py ORIGINAL REBUILT` is a stricter loaded-byte comparison: a nonzero
exit means the build is not 1:1, even when all changed bytes belong to C slots.
The current historical C replacements fail this gate; retain the failure in the
report rather than treating a slot-audit pass as matching. Examine the differences, not just
an ELF file hash. Original baseline: entry 0x001574E8 and two load segments; current
sizes and bounds come from the extracted ELF and configuration, not copied docs.

For boot changes, use a host g++ compiler (not EE g++) for behavior tests. A fresh
build image may need a host compiler installed; that is a test prerequisite, not
a game-build requirement. These tests suppress assembly with PERMUTER only:

```sh
g++ -std=c++98 -O2 -fno-builtin -Icode/include "$test_dir/boot_main_test.cpp" -o /tmp/boot-main-test
/tmp/boot-main-test
g++ -std=c++98 -O2 -fno-builtin -DPERMUTER -Dmain=tested_boot_main -Icode/include -ffunction-sections -fsanitize=address,undefined -c code/game/boot.cpp -o /tmp/boot-options.o
g++ -std=c++98 -O2 -fsanitize=address,undefined -Wl,--gc-sections "$test_dir/boot_options_test.cpp" /tmp/boot-options.o -o /tmp/boot-options-test
/tmp/boot-options-test
```

Do not add SND_HOST_TEST or compile-time test typedefs to production headers.
Update external layout inventories and checks when adding types. An ABI check
proves compiler layout; it does not establish the correctness of prototype fields.

## Isolated full-clean verification

Use the read-only-source container command in
[the CLI integration guide](../../docs/build/RATCHET_PS2_CLI.md).
`TESTS/clean_main_build.py --iso /isos/disc.iso` creates a fresh source snapshot,
extracts through the CLI, performs full-clean through compilation sequentially,
audits the executable, and builds/verifies a new ISO. `/reports` retains the logs,
strict matching result, ELF, and ISO. The active host build is never cleaned.

## ISO and emulator evidence

`make iso` now depends on `elf` and invokes `ratchet-ps2 map build-boot` with
`assets/dl/config.ini`. The host `build_dl_cli.ps1` wrapper uses the same Docker
CLI; `-SkipCompile` packages an already-built ELF. Configured paths are container
paths, including the original ISO under `/isos`. Only the boot executable is
replaced; edited level overlays are not installed by this workflow.

Use `tools/verify_boot_iso.py ORIGINAL_ISO OUTPUT_ISO COMPILED_ELF` to compare the
installed ELF and verify all original disc bytes except boot extent/size and
volume-size fields. Record strict executable matching separately: current
nonmatching C development is permitted but must not be described as byte-exact.

The user reported the earlier CLI-built ISO booted and worked on 2026-10-07.
That observation applies to that tested ISO, not every subsequent clean build.
Record emulator version, ISO/ELF hash, reached stage, and actual gameplay coverage
for further runtime claims.

## Review and handoff

Check the diff for generated artifacts, unrelated changes, duplicate globals,
removed safeguards, and lost includes. Keep locally extracted assets out of commits.
A useful handoff states the retail function/data address and module, evidence for
names/types, files changed, commands/checks and their results, output paths, and
any remaining uncertainties or deferred candidates. Put reusable findings in DOCS
and update the relevant skill if its mechanism changed. Do not leave critical
instructions only in a conversation or a soon-to-be-deleted build log.

Further detail: [ELF reconstruction history](../../src/games/dl/DOCS/build/ELF_REBUILD.md),
[989snd](../../src/games/dl/DOCS/sound/989SND_REUSE.md), [global names](../../src/games/dl/DOCS/symbols/GLOBAL_VARIABLES.md),
[recovered types](../../src/games/dl/DOCS/types/RECOVERED_TYPES.md), [source style](../../src/games/dl/DOCS/types/STYLE.md).

Current platform/matching results: [PLATFORM_VERIFICATION.md](../../docs/build/PLATFORM_VERIFICATION.md).

## Verification entry point

Use `python3 ../tools/verify.py dl` from `/ProjectRYNO/dl` for a forced build and
separate diagnostic/matching results. See [options and exit codes](../../docs/build/VERIFICATION.md).
Use the [progress tracker](../../src/games/dl/DOCS/progress/README.md) to select the next function.
