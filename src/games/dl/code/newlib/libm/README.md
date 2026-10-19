# Deadlocked newlib/libm

Working source baseline: **newlib 1.9.0**, with `common/s_rint.c` taken verbatim
from **1.8.1**. Both come from the [official release archive](https://sourceware.org/ftp/newlib/).
The exact original SDK snapshot is not uniquely established.

`upstream/` preserves the 37 relevant C sources and fdlibm header with original
copyright notices and `COPYING.NEWLIB`. It is excluded from standalone compilation.
The `math/` and `common/` wrappers retain the original source grouping and select
upstream C with original-address placement or explicit assembly for unfinished work.

**31/37 functions compile and match exactly (83.78%)**, using Sony GCC
**2.9-ee-991111-01**. Six IEEE float kernels remain assembly: asin, exp, log,
log10, pow, and sqrt. Their upstream C remains available as research candidates.
The full linked library, its compiled constant pools, and original padding match retail.

See [evidence, compiler settings, and verification](../../../DOCS/libraries/NEWLIB_LIBM.md)
and [progress](../../../DOCS/progress/LIBM.json). Do not build upstream copies
independently or enable candidates without linked-byte verification.
