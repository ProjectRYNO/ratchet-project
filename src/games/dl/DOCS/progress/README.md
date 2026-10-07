# Function progress

[FUNCTIONS.csv](FUNCTIONS.csv) inventories source INCLUDE_ASM entries and the
registered compiled replacements. [SUMMARY.json](SUMMARY.json) records counts,
time, and original/rebuilt ELF hashes for this snapshot. This is not the entire
Ghidra symbol table: retained remnant word arrays are not labeled completed C
functions, and source assembly entries may include padding/unknown routines.

Read the columns separately:

* `implementation`: assembly or compiled, inferred from source and manifest.
* `address`: a unique configured address, or a func_HEX address; blank when unresolved.
* `slot_match`: measured equality for a compiled function's entire allocation,
  including padding. Assembly entries say not_measured, not automatically matching.
* `compiled_size` and `slot_end`: measured linked size and configured bound.
* `test_scope`: names available suites, **not proof they passed in a new run**.
* `question`: default next investigation; `notes`: maintained research context.

The initial snapshot has 8,534 assembly entries and 62 compiled replacements;
6 compiled slots match and 56 do not. Regenerate for current results rather than
assuming those counts remain true. Equal slot bytes do not establish whole-ELF
matching or new in-game test coverage. File metadata hashes can differ even when
all loaded bytes match.

Keep manual notes in [FUNCTION_NOTES.json](FUNCTION_NOTES.json), keyed as
`code/path/file.cpp:function_name`. The generator preserves this input; it rewrites
only FUNCTIONS.csv and SUMMARY.json. Update notes with addresses/evidence and
specific unresolved questions rather than marking untested work complete.

Refresh the tracked snapshot inside `/ProjectRYNO/dl` after a verified rebuild:

```sh
python3 ../tools/function_progress.py dl --output DOCS/progress
```

The [verification command](../../../../../docs/build/VERIFICATION.md) also writes a
separate progress snapshot beside each verification report. Prefer that report
when deciding what a particular tested ELF contains. Commit tracked snapshot
updates only with the source/evidence they describe.


The 2026-10-07 iksemel batch adds six byte-matching C accessors: the refreshed
snapshot has 8,528 assembly entries, 68 compiled functions, 12 matching slots,
and 56 nonmatching slots. See [library notes](../libraries/IKSEMEL.md).
