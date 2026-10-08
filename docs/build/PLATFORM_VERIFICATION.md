# Platform and build verification

## CLI migration and full clean build (2026-10-07)

The project Docker image now builds the sibling ratchet-ps2-cli checkout and
contains the self-contained Linux CLI. Compose supplies the named build context
and mounts the source ISO directory read-only at `/isos`. Both launch scripts
build through Compose. Extraction and packing Makefile targets invoke the CLI.

An isolated container ran the current source snapshot from scratch:

| Stage | Result |
| --- | --- |
| Full-clean, fresh CLI ISO extraction, toolchain setup | PASS |
| ROM extraction, serial split, compilation | PASS |
| Handwritten-source preservation across splitting | PASS |
| ELF runtime layout and compiled-function slots | PASS |
| Global addresses and type layouts | PASS |
| Sound wrapper and sound state checks | PASS |
| Strict executable comparison | NONMATCH: 29,445 changed bytes in registered compiled slots; runtime headers match |
| Config-driven ISO packing | PASS |
| Installed ELF and full-disc preservation comparison | PASS |
| Emulator/gameplay for this clean ISO | NOT RUN |

Reports and artifacts are in `build/cli-migration/clean/`:
`summary.json`, per-stage logs, `boot_elf.elf`, and `new_dl_clean.iso`.
The ISO is 4,363,116,544 bytes. Its installed ELF SHA-256 is
`0089e0d595103e369779a08f67b22f394253448999cefb4fe9ad039559c0d25e`.
The entire original disc is preserved except the boot directory extent/size and
volume-size fields, with the new compiled ELF appended.

This confirms the clean build and packaging workflow. It does not turn existing
nonmatching decompiled functions into byte-exact replacements. The source snapshot
is recorded in `source-hashes.json`; later concurrent decompilation edits are not
implicitly covered by these results.

The user reported that the earlier CLI-built test ISO worked correctly. That
runtime observation belongs to the earlier artifact, not this clean-build ISO.

The superseded extraction tree and previous platform notes were preserved outside
the repository in `../migration-archive/dl-assets-20261007/`. Current references use
`assets/dl/boot.elf` and numeric level directories. See
[RATCHET_PS2_CLI.md](RATCHET_PS2_CLI.md) for reproducible commands.
