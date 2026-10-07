# Deadlocked documentation

| Folder | Documents and data |
| --- | --- |
| progress | [Function tracker, byte status, and research notes](progress/README.md) |
| build | [ELF reconstruction and build history](build/ELF_REBUILD.md) |
| sound | [989snd decompilation notes](sound/989SND_REUSE.md), [function inventory](sound/989SND_INVENTORY.csv) |
| libraries | [iksemel decompilation and validation](libraries/IKSEMEL.md), [SVO3](libraries/SVO3.md) |
| symbols | [Global mapping notes](symbols/GLOBAL_VARIABLES.md), [retail inventory](symbols/GLOBAL_VARIABLES.csv), [unmapped prototype globals](symbols/GLOBALS_UNMAPPED.csv) |
| types | [Recovered layouts](types/RECOVERED_TYPES.md), [machine-readable inventory](types/RECOVERED_TYPES.json), [style reference](types/STYLE.md) |

AI instructions and skills are grouped in [.agents](../../../../.agents/README.md).
The [Deadlocked AI guide](../../../../.agents/guides/DEADLOCKED.md) contains current
build and test commands. Shared technical documents start at
[docs/README.md](../../../../docs/README.md).

The CSV/JSON files under symbols and types are also inputs to verification tools.
When moving or renaming them, update the readers and clean-build copy paths.
