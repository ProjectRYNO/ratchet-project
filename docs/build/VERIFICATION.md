# One-command verification

Run inside the project build container after extracting the original assets:

```sh
cd /ProjectRYNO/dl
python3 ../tools/verify.py dl
```

This forces an ELF rebuild, then checks loaded bytes/runtime headers, compiled
function placement, global addresses, PS2 type layouts, both sound differential
suites, iksemel and SVO3 library checks, and the function progress inventory.
It writes individual logs and
`summary.json` under a fresh `build/verification/<UTC timestamp>/` directory.
The JSON records original/output ELF hashes, commands, return codes, skipped
checks, and timestamps. It is a record of that run, not a permanent guarantee.

| Option | Use |
| --- | --- |
| `--split` | Run ps2dev, rom, and split serially before the forced build; use after configuration/symbol/manifest changes or on a fresh extraction |
| `--host-tests` | Also compile/run boot host behavior tests, including option sanitizers; requires host g++ in the container |
| `--no-build` | Check existing artifacts; explicitly does not establish source freshness |
| `--require-matching` | Treat nonmatching executable bytes as a failed strict gate |
| `--jobs 8` | Number of ELF compile jobs; never parallelizes split against compile |
| `--output PATH` | Use a new or empty report directory; relative paths are relative to the caller's directory |

A full setup-and-check command is `python3 ../tools/verify.py dl --split --host-tests`.
If a stage fails, the command does not continue to audit an old ELF as a successful
new build. Other independent audits continue after an audit failure so the report
can show more than one issue. Missing tools, corrupt ELF files, runtime-layout
changes, and failed tests are hard failures, not permissible nonmatching results.

## Exit codes and claims

* **0:** requested checks passed. The executable can still be **NONMATCHING**;
  the console and JSON identify that explicitly. Development testing is allowed.
* **1:** build, parsing, layout, placement, or test failure. Investigate it.
* **2:** diagnostics passed but `--require-matching` rejected differing bytes.
* Command-line usage errors also return 2 with an argparse message and no new report.

A skipped boot-host check is printed as SKIP, not PASS. The command does not pack
an ISO, perform an isolated full-clean build, or run an emulator. Use the
[Deadlocked guide](../../.agents/guides/DEADLOCKED.md) for those separate operations
and the [smoke checklist](EMULATOR_SMOKE_TEST.md) for runtime evidence.
Only Deadlocked currently has a verified command profile. Other game selections
fail clearly rather than applying Deadlocked addresses/tests to another title.

The [function tracker](../../src/games/dl/DOCS/progress/README.md) is also generated
inside each report. It records measured compiled-slot byte equality separately
from source-language status and configured test coverage.

Regression checks for the verifier itself:

```sh
python3 /ProjectRYNO/tools/test_verify.py
```

These fixture tests exercise exit classification, malformed/truncated ELF handling,
layout failure, build failure without stale-artifact checks, and stage ordering.
They mock subprocesses; the game-specific suites execute the real artifacts.
