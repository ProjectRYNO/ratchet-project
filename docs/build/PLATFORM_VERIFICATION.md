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
* The entrypoint stops on failed download/extraction and verifies the legacy
  compiler executable instead of reporting a false successful installation.
* The clean-build helper copies tests from its actual script directory. Git tracks
  TESTS; the isolated build uses tests consistently. Ignore exceptions now follow
  the tracked uppercase spelling.
* Bash invocation is documented explicitly because the tracked launcher has mode
  100644. Existing `.gitattributes` keeps shell scripts LF-terminated.
* `requirements.txt` pins the validated splitter stack. An unrestricted fresh
  install selected splat64 0.50.0 / spimdisasm 1.42.4, unlike the validated
  0.41.0 / 1.41.0 stack. The final fresh-image build uses the pinned versions.
* `.dockerignore` limits the image context to Dockerfile, requirements, and
  entrypoint inputs. Game assets and large ISOs are bind-mounted, not sent into
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
