# Platform and matching verification

## Scope (2026-10-06)

Verified Windows PowerShell launch behavior and Linux/x86-64 Docker builds.
A Linux container filesystem was populated using Git's tracked filename casing
and current working-tree file contents, with separately supplied original ELF
input. This avoids Windows masking TESTS/tests and source/include case mistakes.
The build was repeated in a newly built image, not only the existing cached image.
This does not claim a native, non-container Linux toolchain or other CPU support.

Reference Deadlocked ELF SHA-256:
`2c537a7f7a69663c60ba943f2c0d265178c0680e203d9b1284f94bc33c43ae4a`.

## Results

* Fresh image construction and actual entrypoint startup/download: passed.
* Isolated Linux full-clean, toolchain install, ROM extraction, split, compilation:
  passed with the expected existing assembler/link warnings.
* Existing-image Linux build and fresh-image Linux build versus the Windows
  workspace's rebuilt ELF: all 5,158,456 loaded bytes and runtime headers match.
* Compiled-function/slot audit: passed. This is not the strict matching gate.
* 806 global-address checks, 737 type size/offset checks, independent header
  includes, and ten EE bit-field vectors: passed.
* 2,720 sound-wrapper cases and 293 stateful sound cases: passed.
* Four extraction/layout regressions: passed.
* Seven launcher cases on both Windows PowerShell and Linux Bash: passed using
  fake Docker commands, so failure-path tests do not delete or change containers.
* No new ISO pack, emulator run, or gameplay session was performed in this pass.

**Strict comparison to the original ELF fails: 5,130 loaded bytes differ.**
They are inside existing C replacement slots; all other bytes and runtime headers
match. The C replacements predate the exact-matching requirement and remain a
matching backlog. Functional tests and platform reproducibility do not turn that
failure into a 1:1 pass. No C functions were replaced with original assembly or
copied executable words to hide the result.

## Portability fixes

* Both launchers use their script directory for the Docker build context and
  propagate build/compose failures. Help works without contacting Docker.
* The earlier entrypoint download checks have been superseded by the native-only
  image cleanup below.
* The clean-build helper copies tests from its actual script directory. Git tracks
  TESTS; the isolated build uses tests consistently. Ignore exceptions now follow
  the tracked uppercase spelling.
* Bash invocation is documented explicitly because the tracked launcher has mode
  100644. Existing `.gitattributes` keeps shell scripts LF-terminated.
* `requirements.txt` pins the validated splitter stack. An unrestricted fresh
  install selected splat64 0.50.0 / spimdisasm 1.42.4, unlike the validated
  0.41.0 / 1.41.0 stack. The final fresh-image build uses the pinned versions.
* `.dockerignore` limits the image context to Dockerfile and requirements inputs. Game assets and large ISOs are bind-mounted, not sent into
  the image build context.

Run `python src/games/tools/test_launchers.py` on Windows or Linux to repeat the
launcher checks. The test substitutes Docker only; it does not establish that a
real image builds. Use the clean-build commands in
[the Deadlocked profile](../../.agents/guides/DEADLOCKED.md) for that check, and
always run the strict comparator separately.

Generated logs/ELFs for this session are under
`src/games/dl/build/linux-audit`, including `fresh-image`, `startup.log`, and
`image-build.log`. They are temporary and removed by a working-tree clean.
Other games do not yet have game Makefiles and were not claimed to build; their
onboarding follows [GAME_WORKFLOW.md](../../.agents/guides/GAME_WORKFLOW.md).


## Native-only image cleanup (2026-10-06)

Removed Wine, i386 package architecture, the Wine initialization/Windows EE GCC
download script, and the unused GCC 2.95.2 include path. Docker now opens Bash
directly. Deadlocked still installs native EE GCC 3.2.3 with `make ps2dev`;
Wrench remains the same native Linux v0.5 release. Unused Makefile Windows
command definitions and obsolete variables/comments were removed.

The old toolchain ignore rules remain so existing local downloads cannot
accidentally enter source control. Existing containers retain their old image;
start a new container after rebuilding with `docker compose build projectryno`
from `src/games`. Windows and Linux launchers remain supported.

Validation used a freshly built `projectryno-native-check` image, with no Wine,
Wine boot command, foreign package architecture, old entrypoint, or Windows
compiler directory. Default Bash startup and native Wrench help passed, as did
all seven launcher cases on each host shell. An isolated full-clean build
installed PS2DEV, extracted the ROM, split sources, and compiled successfully.
ELF/slot, global-address, type-layout, and both sound differential audits passed.
Its runtime headers and all 5,158,456 loaded bytes match the previous build.
This preserves the existing nonmatching development output; it does not make
the current C replacements byte-identical to retail.

Reports: `src/games/dl/build/native-image-build.log`, `native-startup.log`, and
`native-clean/`. No ISO repack or emulator/gameplay run was performed for this
cleanup.


## Wrench validation after native cleanup (2026-10-06)

Native Wrench v0.5 (commit `6c743e54a7087633887709acbc9b42552dac02e6`)
was tested in the Wine-free image:

* Full original US retail ISO extraction: passed, exit 0.
* Full ISO packing from existing assets with the current compiled ELF: passed,
  exit 0; output size 4,339,949,568 bytes.
* Boot ELF extracted from that ISO matches the compiled input byte-for-byte:
  SHA-256 `e7f4497d121104655b4281f63866ed1364377df1c86607e796051f0b66837742`.
* Full unpack of the rebuilt ISO: FAILED at `dl.misc.debug_font`, with
  "Tried to read past end of substream of size 800 from suboffset 420."
  The previous rebuilt ISO fails identically, while retail extraction succeeds.
  This is an existing asset round-trip issue, not a Wine-removal regression;
  its underlying packing/asset cause has not been established.

The new ISO, logs, partial rebuilt-ISO extraction, and `summary.json` are in
`src/games/dl/build/wrench-native-check`. Reference assets and the previous ISO
were mounted read-only. The original retail extraction used disposable
container-local storage. No emulator or gameplay test was performed.
