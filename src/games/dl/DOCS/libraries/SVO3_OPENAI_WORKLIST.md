# SVO3 work list for a second agent (2026-10-19)

Goal: make each function below byte-exact against retail. SVO3 is at 907/934 exact; this list is
every remaining function **outside `code/svo3/CPage.cpp`**. Another agent is editing CPage.cpp at
the same time, so do not edit that file.

## Ownership and rules

- Edit only the `.cpp` files named in the table, and only the listed functions (plus helper
  structs or `static inline` helpers placed directly above them). Do not edit `CPage.cpp`,
  headers, `config/`, the Makefile or `src/games/tools/`; note anything you need there instead.
- Follow `.agents/INSTRUCTIONS.md`: `ALLOW_NONMATCHING=0`; never widen slots; no fallback
  symbols; never embed retail machine words or bytes; no commits or pushes.
- No inline asm in these functions (the four patched CPage functions are the only approved
  exception, and they are not on this list).
- Keep behaviour identical unless retail clearly differs; report every behaviour change.
- Do not run `make split`, `make elf` or `build/svo-library-work/ck4.sh`; the lead runs full
  builds. Per-function checks below compile one module in the container.

## Tools (run from `src/games/dl`; container `projectryno-svo75`)

- `bash build/svo-library-work/show.sh <Module> <fn>`: writes the current body to
  `build/svo-library-work/b/cur_<fn>.v` and prints a side-by-side diff (`!!` = differing line;
  left retail, right ours).
- `python build/svo-library-work/perm.py <Module> <fn> <body-file> [-q]`: compiles the module with
  that body and prints `BEST ... N diff lines, size ... FITS/OVER`. 0 diff lines + FITS = exact.
- `python build/svo-library-work/install.py <Module>`: installs the last perm.py candidate. Always
  run perm.py on the exact body immediately before install.py.
- `python build/svo-library-work/vary.py <Module> <fn> <base.v> <pairs.py>` scores replacement
  variants; `climb.py` hill-climbs statement order (check it keeps behaviour).
- Retail assembly: `code/asm/matchings/svo3/<Module>/<fn>.s`.
- `sbs.py` shows retail `.word 0x46…` (cvt.w.s) against our `trunc.w.s` as `!!`; the encodings
  are identical, so ignore those lines (affects `draw___dupe2`).
- Use a `cx_` prefix for scratch files in `build/svo-library-work/b/`.

## Functions

| File | Function | Diff bytes | Known residual |
|---|---|---|---|
| CDrawContextBase.cpp | `DrawGridScrollbars` | 12 | Order of `move $10,$0` / `mov.s $f16,$f20` argument moves in two calls. |
| CHttp.cpp | `downloadBody` | 4 | gcse hoists `m_sock`, `buffer.data`, `&received` out of the identical ternary arms; retail's `lw m_sock` precedes `addiu &received`. |
| CHttp.cpp | `parseHttpHeaderLine` | 8 | At the `'&'` compare, char load and constant 38 in swapped registers (store, then `lb`, then `li` in retail). |
| CreateGameTagModule.cpp | `ScanTags___dupe7` | 1 | Only `beql` (retail) vs `beqz`. |
| GenericListBoxTag.cpp | `addHandle` | 27 | Retail places `li $2,1` after the stores. |
| GridTag.cpp | `Draw___dupe23` | 32 | DrawGridHeader argument/vtable-load order; final DrawGridScrollbars float-load order. |
| HttpUtils.cpp | `decodeEntityChar` | 6 | Retail loads `lb val` before the `*position` store (store in the delay slot). |
| HttpUtils.cpp | `parseFullyQualifiedPath` | 20 | `port` gets `$7` instead of `$3` (local-alloc of the `m_server` pointer). |
| ListBoxTag.cpp | `addItem` | 8 | `$3`/`$4` register swap. |
| SVDownloadManager.cpp | `NotifySystemContextOfFailure` | 4 | `name` vs `partialDownloadInfo` stack stores swapped (sched2 anti-dependence through reused `$4`). |
| SVDownloadManager.cpp | `draw___dupe2` | 6 | Argument-move order `$10=0` / `mov.s $f16`. |
| SelectTag.cpp | `DefaultInit___dupe9` | 4 | One store pair swapped. |
| SelectTag.cpp | `HandleInput___dupe40` | 4 | Branch-likely choices only. |
| TextAreaTag.cpp | `GetNextWord` | 230 | Pointer/register allocation and layout. |
| TextAreaTag.cpp | `ParseText` | 10 | `lines`/`text` swapped between `$20`/`$21`. |
| TextInputTag.cpp | `defaultInit` | 60 | Store order (retail plain source order). |
| TextInputTag.cpp | `drawCursor` | 54 | Retail puts `lw draw->vtable` in a `bne` delay slot. |

## Patterns that have worked (see SVO3_HANDOFF.md for the full list)

- Store order: 2.96 emits the last of an independent store group first; for retail order
  X1..Xn write X2..Xn, X1. Stores can also be moved across a call (GridTag `DefaultInit___dupe18`).
- C++ reference locals (`int &p = tag->field;` declared just before use; declaration order sets
  the register/stack split) fixed the GridTag constructor.
- Duplicate an assignment into each predecessor branch to raise a variable's register
  priority; reuse one variable for two jobs; a separate local that ends a variable's live range
  early (CPage `doRequest`: `histPath`).
- Count-up loops `for (i = 0; i < n; i++)` that 2.96 reverses; index loops
  `for (i = 0; i < N && a[i]; i++)`; `if (a[0]) for (...)` entry tests.
- `static inline int F(T *p) { return p->x != 0; }` changes branch-likely choices when the
  condition feeds a combined test.
- Real C++ constructors (`struct XCtor { char data[sizeof(X)]; XCtor() __asm__("X"); };`) and
  `do { ... } while (0)` around a final call to stop a tail call.
- Not the answer: global compiler flags (`-fno-strict-aliasing`, `-fno-schedule-insns` and others
  were measured and are worse overall).

## Report back

For each function: exact or not, final diff lines, the source shape that worked or what was
tried, and any behaviour change. Note anything needed outside the owned files.
