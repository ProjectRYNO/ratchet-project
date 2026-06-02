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
...more work is still done to do this.  Current state is unbuildable.

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