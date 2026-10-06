## PRoject RYNO
Reverse Ya a New One

## Description
This project is the start of decompiling the Ratchet and Clank PS2 games.  The acceptance goal is identical executable bytes and runtime layout, with the same in-game behavior. Existing nonmatching C replacements are work in progress, not a completed 1:1 build.

Due to the games being built from one another, I have decided to start from Ratchet: Deadlocked, and work backwards.

The environment for the decompilation of the games is very much inspired by [bordplates RC1](https://codeberg.org/bordplate/RC1) environment for building.

This project is to eventually become silmiliar in style of the [openGOAL/jak Project](https://github.com/open-goal/jak-project/tree/master).

## Documentation

Browse [technical documentation](docs/README.md) or [AI instructions and skills](.agents/README.md).

## Working with an AI assistant

Start with [AGENTS.md](AGENTS.md), the main rule set for all games.
Read [the shared game workflow](.agents/guides/GAME_WORKFLOW.md) before bringing up another title. It links reusable skills for decompilation,
global/type recovery, and build verification. The [AI contributor workflow](.agents/guides/DEADLOCKED.md)
contains setup, commands, validation expectations, and clean-build instructions.
Assistants without skill support can read each `SKILL.md` directly.

## Build
1. Start Container:
```
cd src/games
# Windows PowerShell:
./docker-init.ps1 [-args]
# Linux/macOS (the tracked script need not have an executable bit):
bash ./docker-init.sh [--args]
```
Windows args are a single dash (-help); the Bash launcher uses a double dash (--help).
The verified environments are Windows Docker Desktop and Linux/x86-64 containers.
Container Arguments:
```
No argument: reuse the image (build if missing), then open a new container shell.
-help: Show Help
-rebuild: Rebuilds container.
-delete: Deletes container(s)
```

2. Dump ELF and assets.  This will take awhile.
```
# cd into your game
cd dl

# dump your game ISO
make dump iso=/path/to/game.iso
```

3. Create .ROM.  the .rom file goes into the `<game>/config/` folder.
```
make rom
```

4. Split the assembly!
This will create a `code/` folder that has all the assembly.s files you'll need for functions you have yet to decompile.
```
make split
```

5. Start decomping the code!
Deadlocked rebuilds from split assembly, three decompiled C++ boot functions, and 59 decompiled C sound functions. See [ELF rebuild notes](src/games/dl/DOCS/build/ELF_REBUILD.md) and [989snd progress](src/games/dl/DOCS/sound/989SND_REUSE.md) for the verified workflow and validation limits.

Follow the [decompilation source conventions](src/games/dl/DOCS/types/STYLE.md) for header guards, struct layouts, and source-file grouping.

The [retail global-variable map](src/games/dl/DOCS/symbols/GLOBAL_VARIABLES.md) provides recovered names, addresses, prototype declarations, and an unmapped research backlog.

The [recovered data types](src/games/dl/DOCS/types/RECOVERED_TYPES.md) document module headers, PS2 layouts, evidence levels, and the distinction between packed boot options and runtime settings.

6. Build the new elf!
```
make
python3 ../tools/compare_elf.py ../assets/dl/boot_elf.elf build/boot_elf.elf
```

The current Deadlocked C replacements fail strict matching; a successful compile
or slot audit does not yet make them a 1:1 build. Other games currently have
scaffolding but no game Makefile, so these build commands are Deadlocked-specific.

7. Build the new ISO to test!  This step will take awhile.
Once completed, the iso will be in the `build/` folder.
```
make iso
```

## Other Make Commands
 - `make clean`: Cleans the current game folder, but keeps the .rom file..
 - `make full-clean` Cleans the current game folder, deletes the .rom file.
