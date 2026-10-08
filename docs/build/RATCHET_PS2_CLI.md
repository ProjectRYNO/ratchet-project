# Deadlocked CLI build workflow

All executable extraction and boot ISO packaging use ratchet-ps2-cli. The Docker
image builds the sibling CLI checkout as a self-contained Linux executable; a
host .NET installation is not required. Rebuild the image after CLI changes.

From `src/games`:

```sh
docker compose build projectryno
docker compose run --rm projectryno
```

The build context defaults to the sibling `ratchet-ps2-cli` checkout. Set
`RATCHET_CLI_SOURCE` to override it. `RYNO_ISO_DIRECTORY` selects the host directory
mounted read-only at `/isos` (default matches this workspace's `D:/PS2/ISOs`).
Use Compose to build, or supply `--build-context ratchet_cli=/path/to/cli` when
invoking `docker build` directly.

Inside the container, for an empty `assets/dl` extraction directory (an empty `.gitkeep` file is allowed):

```sh
cd /ProjectRYNO/dl
make dump iso='/isos/SCUS_974.65.Ratchet Deadlocked.iso'
make ps2dev
make rom
make split
make -j8 elf
make iso
```

Run stages serially. `make dump` exports `boot.elf`, 47
`levels/<four-digit ID>/code/overlay.elf` files, and `config.ini`. It refuses to
overwrite a nonempty output directory. For an existing extraction, retain it and
use its config. `make iso` depends on `elf` and invokes the CLI config-driven
builder; it never edits an asset-bank descriptor.

The default generated config points at the compiler output and `build/new_dl.iso`:

```ini
[build]
source_iso=/isos/SCUS_974.65.Ratchet Deadlocked.iso
boot_elf=../../dl/build/boot_elf.elf
output_iso=../../dl/build/new_dl.iso
```

Paths resolve relative to config.ini. The existing local config may use
`new_dl_cli.iso` to preserve earlier test discs; the config determines the output.
Container config paths must be visible inside the container. Spaces need no quotes.
The builder preserves the input ISO and replaces its boot executable only; it does
not repack edited level overlays, textures, models, or gameplay.

From the project root, the PowerShell shortcut uses this same container CLI:

```powershell
./src/games/tools/build_dl_cli.ps1
./src/games/tools/build_dl_cli.ps1 -SkipCompile
```

`-Config` accepts an alternative config within `src/games`. Initialize ROM/split
output before ordinary compilation and never overlap builds in the same game
folder. Compiler output remains `build/boot_elf.elf`; reference readers use
`assets/dl/boot.elf`.

## Isolated full-clean verification

The harness mounts the checkout read-only, copies a source snapshot into a fresh
container, and runs full-clean, CLI extraction, toolchain installation, ROM
extraction, split, compilation, ELF/slot/global/type/sound checks, strict matching,
ISO packing, and a full-disc preservation comparison. It preserves reports and
built artifacts on the host. Nonmatching C bytes are reported separately from
build and packaging failures.

```powershell
$games = (Resolve-Path src/games).Path
$reports = (New-Item -ItemType Directory -Force build/clean-cli).FullName
$isos = 'D:\PS2\ISOs'
docker run --rm --mount "type=bind,source=$games,target=/reference,readonly" `
  --mount "type=bind,source=$reports,target=/reports" `
  --mount "type=bind,source=$isos,target=/isos,readonly" `
  --entrypoint python3 projectryno /reference/dl/TESTS/clean_main_build.py `
  --iso '/isos/SCUS_974.65.Ratchet Deadlocked.iso'
```

Check the exit code and `summary.json`. Reports include `exact-matching.log`,
`verify-iso.log`, `boot_elf.elf`, and `new_dl_clean.iso`. Automated packaging checks
are separate from emulator/gameplay verification.
