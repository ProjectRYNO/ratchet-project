## PRoject RYNO
Reverse Ya a New One

## Description
This project is the start of decompiling the Ratchet and Clank PS2 games.  I am not here to do a complete matching of the assembly code, but to match functionality.

Due to the games being built from one another, I have decided to start from Ratchet: Deadlocked, and work backwards.

The environment for the decompilation of the games is very much inspired by [bordplates RC1](https://codeberg.org/bordplate/RC1) environment for building.

This project is to eventually become silmiliar in style of the [openGOAL/jak Project](https://github.com/open-goal/jak-project/tree/master).

## Build
1. Start Container:
```
cd games
./docker-init.ps1 [-args]
```
Windows args are a single dash (-help), while Linux/mac is a double dash (--help)
Container Arguments:
```
No argument: run container.  If container alredy exists, use existing container.
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
Deadlocked rebuilds from split assembly, three decompiled C++ boot functions, and 59 decompiled C sound functions. See [ELF rebuild notes](src/games/dl/DOCS/ELF_REBUILD.md) and [989snd progress](src/games/dl/DOCS/989SND_REUSE.md) for the verified workflow and validation limits.

Follow the [decompilation source conventions](src/games/dl/DOCS/DECOMP_STYLE.md) for header guards, struct layouts, and source-file grouping.

The [retail global-variable map](src/games/dl/DOCS/GLOBAL_VARIABLES.md) provides recovered names, addresses, prototype declarations, and an unmapped research backlog.

The [recovered data types](src/games/dl/DOCS/RECOVERED_TYPES.md) document module headers, PS2 layouts, evidence levels, and the distinction between packed boot options and runtime settings.

6. Build the new elf!
```
make
```

7. Build the new ISO to test!  This step will take awhile.
Once completed, the iso will be in the `build/` folder.
```
make iso
```

## Other Make Commands
 - `make clean`: Cleans the current game folder, but keeps the .rom file..
 - `make full-clean` Cleans the current game folder, deletes the .rom file.
