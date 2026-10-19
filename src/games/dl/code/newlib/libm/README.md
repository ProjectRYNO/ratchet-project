# Deadlocked newlib/libm

**37/37 functions (100%) compile from C and match retail byte-for-byte.**
All original `common/` and `math/` source-file splits are preserved. No math
function uses an assembly fallback.

Sources are verbatim newlib **1.9.0**, except `math/ef_asin.c` from **1.8.2** and
`common/s_rint.c` from **1.8.1**, obtained from the
[official archive](https://sourceware.org/ftp/newlib/). Copyrights and
`COPYING.NEWLIB` remain. `upstream/` is excluded from standalone compilation;
the wrappers add only original-address placement declarations.

The Makefile pins **`ee-gcc2.9-991111-01.tar.xz`**. The similarly named
`ee-gcc2.9-991111a.tar.xz` reports the same version but does not reproduce the
remaining float divisions. No inline assembly or instruction rewriting is used.

See [source/compiler evidence and verification](../../../DOCS/libraries/NEWLIB_LIBM.md)
and [progress](../../../DOCS/progress/LIBM.json). Library code, compiled constants,
and original padding match; the exact original SDK source release is not uniquely identified.
