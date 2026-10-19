# Deadlocked newlib/libm

Working baseline: **newlib 1.9.0**, from the [official release archive](https://sourceware.org/ftp/newlib/newlib-1.9.0.tar.gz).
The exact original release is not uniquely established; matching evidence points
to the older 1.8.2/1.9.0 source family.

`upstream/` preserves the 37 relevant C sources and fdlibm header verbatim.
Copyright notices and `COPYING.NEWLIB` are retained. It is excluded from standalone
compilation. The corresponding `math/` and `common/` wrappers select either the
upstream implementation with an original-address section, or explicit retail
assembly when matching remains unfinished.

**14/37 functions are compiled and byte-exact (37.84%).** The other 23 upstream
sources are candidates only. The full linked library still matches retail because
those unfinished functions retain assembly.

See [evidence, compiler settings, and verification](../../../DOCS/libraries/NEWLIB_LIBM.md)
and [progress](../../../DOCS/progress/LIBM.json). Do not build upstream copies
independently or enable all candidates without linked-byte verification.
