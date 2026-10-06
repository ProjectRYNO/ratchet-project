# AI task handoff

Use for sustained decompilation/build work or when another contributor will resume.
Fill with observed facts; use NOT RUN / UNKNOWN rather than guessing. A cosmetic
edit does not need a separate handoff file. Do not overwrite another task's notes.

```text
Task / intended result:
Game, region, revision:
Source revision and relevant uncommitted changes:

Function/data names, retail addresses, owning source files:
Evidence used (Ghidra program/address space, prototype/dump lines, disassembly):
Confirmed facts:
Uncertain identifications / open questions:

Files changed and why:
Build/symbol/manifest/type impacts:
Relevant decision/issue IDs:

Verification command and report path:
Original ELF hash / rebuilt ELF or ISO hash:
Build and placement:
Exact matching (PASS/NONMATCH/FAIL; differences):
Behavior tests (what ran, what was mocked):
Emulator/gameplay observations:
NOT RUN and reasons:

Remaining failure / reproduction:
Next concrete action:
Progress/decision documents updated:
Temporary artifacts/container names worth retaining:
```

Keep reusable findings in the [decision log](../../docs/decompilation/DECISIONS.md)
and game tracker rather than only in temporary build logs. Do not equate a passing
slot audit with a byte match, or a byte match with a newly performed gameplay test.
