# HTTP/SSL integration pending review (2026-10-08)

## Resumed after user approval

The user approved resuming this work on 2026-10-08. Five HttpSecure replacements
and CHttp DoRegistrations2/doRequest/handleRedirect are now integrated in their
original slots. See SVO3_HANDOFF.md for current validation. The rejection record
below is historical and no longer requires a separate approval for this scope.

Two allowed replacements were integrated: parseHttpStatusLine (0x90/0xA0) and
HttpsDownloadHello (0xA8/0xA8). Other recovered candidates remain assembly.
The full HttpSecure layout is independently supported by retail offsets and
prototype dltypes; size/offset validation is recorded in the SVO3 handoff.

Automatic approval review rejected the following actions. These are review
blocks, not compiler failures. Do not bypass them through another agent or path.
User approval was subsequently granted to resume this work. Slot and behavior checks
remain required after approval; approval does not make a candidate correct.

## Replace HttpSecure constructor, DoRegistrations, HttpSecureConnectingOnEnter/Update1/Update2 and compile owned objects

> Although the struct layout is now supported, this repeats the previously rejected speculative replacement of five HttpSecure routines and a local object build without sufficient evidence that the implementations fit their retail slots or preserve behavior.

## Compile four HttpSecure candidates only in ignored scratch source

> This is an indirect workaround of the prior rejection, compiling the same speculative HttpSecure implementations in a generated candidate file; it remains outside the proven safe scope and is explicitly prohibited from bypassing the rejection.

## CHttp DoRegistrations2/doRequest/handleRedirect and verified URIRequest/listener callback recovery

> This proposes several unverified ABI/header changes plus large speculative doRequest and redirect implementations, without a slot-size check or compilation evidence; the resulting HTTP behavior and layout could be materially corrupted.

Retail Ghidra addresses/program and full evidence are in ignored
`build/svo-library-work/http-final-ghidra-*.json` and `http-final-results.json`.
At the original blocked checkpoint, these production replacements remained INCLUDE_ASM. Following user authorization, the listed replacements were integrated and verified as recorded in SVO3_HANDOFF.md.
