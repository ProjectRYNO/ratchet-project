# Medius type placement

The reference dump is `D:/PS2/ISOs/deadlocked-proto-decomp/dltypes.txt`.
Keep it as reference evidence. Recovered declarations belong in module-owned
headers under `src/games/dl/code/medius/`, following the prototype Medius tree.
The prototype has 85 candidate headers; none currently exists in the retail
Medius source tree. These generated prototype headers provide ownership clues,
not independent proof of the original SDK header organization or retail ABI.

[MEDIUS_HEADER_MAP.csv](MEDIUS_HEADER_MAP.csv) lists all 85 proposed destinations.
Paths in the table below are relative to `src/games/dl/code/medius/`.

| Definition | Proposed header | dltypes.txt reference |
| --- | --- | --- |
| RT_MEMORY_ALIGNED | rt_util/rt_memory.h | Definition ends at line 22258 |
| RT_CIRC_BUF | rt_util/rt_circ_buf.h | Definition ends at line 24032 |
| RT_PACK_BUFFER and RT_PACK_MODE | rt_util/rt_pack.h | Definitions end at lines 25290 and 25282 |
| MediusAccountUpdateStatsRequest and client request/report types | MediusClientLibrary/src/MediusClient.h | Example ends at line 17808 |
| MediusDType interfaces and field metadata | MediusDList/src/MediusDType.h | FieldSpec/FieldMap end at lines 29017/29023; prototype header groups DType interfaces |
| DME client/object types | dme_client/src/ and dme_object/src/ owning headers | Resolve each declaration against its prototype module |
| Transport, cryptography, message, and stream types | rt_comm/, rt_udp/, rt_crypt/, rt_msg/, StreamMedia/ owning headers | Preserve existing component ownership |

Shared scalar aliases and shared result codes can live in a small new
`code/medius/rt_types.h` included by component headers, after resolving their
actual declarations. This is a proposed shared header, not a recovered original
filename. For example, `RT_U4BYTE` is `unsigned int` at dump line 21883 and
`RT_BOOL` aliases it at line 21889. `RT_RESULT` appears at least twice (definitions
ending at lines 22249 and 30584); compare their contents/dependencies before
selecting a common declaration. Do not import unrelated game or system types
into this header.

## Validation before production use

Follow `.agents/skills/ryno-symbols-types/SKILL.md`: preserve dump size/offset
comments, one typed field per line, filename-derived guards, and original module
ownership. Record imported types and their evidence in `RECOVERED_TYPES.json`,
then extend `TESTS/check_type_layouts.py` using the actual EE compiler. Keep
prototype-only evidence distinct from retail instruction-confirmed offsets.
Do not mark candidate mappings as verified recovered types before this work.

The prototype `rt_memory.h` demonstrates why wholesale copying is inappropriate:
its callback typedefs contain `parameters unknown`. Recover those signatures
from retail callers before exposing them to C. Likewise, imported Ghidra layouts
alone do not independently validate a struct against retail instructions.

Begin with `RT_MEMORY_ALIGNED`, `RT_PACK_BUFFER`, and `RT_CIRC_BUF`, which support
the next utility functions. The previously inspected retail pack initializer
uses the expected offsets 0/4/8/12/16; importing the complete declaration still
requires documenting the field evidence and checking its 20-byte EE layout.

This inventory adds no production declarations or decompiled functions.
Medius function progress remains **3/1,462 (0.21%)**, all three byte-matching.
