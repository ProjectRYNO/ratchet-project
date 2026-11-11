# VU microcode (.vutext)

`.vutext` (`0x00100080`-`0x0011a180`) holds the VIF DMA chains that upload the game's VU
microprograms: DMA tags and VIF codes (framing) around 62 MPG uploads, 13,231 VU instructions in
all. VU microcode was written in VU assembly, not C, so its recovered form is VU assembly that
PS2SDK's `dvp-as` assembles back to the retail bytes.

## How it is built

* `make split` runs splat, then `tools/split_dl.py` calls `tools/vu_split.py` on the extracted
  segment (`assets/vutext/000000.textbin.bin`). It writes `code/asm/build/vutext/vutext.vsm` and
  points the segment's wrapper, `code/asm/build/vutext/000000.s`, at `build/vu/vutext.bin`.
* The Makefile assembles `vutext.vsm` with `$(PS2DEV_DIR)/dvp/bin/dvp-as` and extracts `.vutext`
  with `dvp-objcopy -O binary` into `build/vu/vutext.bin`. The wrapper includes that file.
* Like the rest of `code/asm`, `vutext.vsm` is generated and not committed. `vu_split.py` assembles
  what it writes and fails the split unless the result equals the extracted segment, and the
  strict ELF comparison checks the linked bytes.
* After changing `vu_split.py`, run `python3 ../tools/test_vu_split.py` (from `/ProjectRYNO/dl`;
  it needs the dvp binutils), then split and rebuild.

## Reading vutext.vsm

* Each line is `upper<TAB><TAB>lower`, in `dvp-objdump`'s spelling. Framing is `.word` data with
  the decoded DMA tag or VIF code in a `;` comment.
* A microprogram is a run of MPG uploads to consecutive micro addresses. It is labelled
  `mpg_XXXXXXXX`, the EE address of its first MPG code. That is also the function name the
  [Ghidra EE extension](https://github.com/Metroynome/ghidra-emotionengine-reloaded)'s
  "PS2 VU Microcode" analyzer gives it, so the source and Ghidra's `vu0_*`/`vu1_*` overlays line
  up. Branch targets are `mpg_XXXXXXXX_YYYY`, where `YYYY` is the micro address.
* Uploads over 2 KB are split into several MPG commands with VIF codes between them, so a label in
  a later upload would be at the wrong distance. A branch into another upload of its program, or
  out of its program, keeps its numeric offset field `(target - (pc + 8)) / 8`, with the target in
  a comment. Branches out of a program wrap around micro memory, whose size depends on the unit
  (VU0 4 KB, VU1 16 KB); the comment gives both.
* `loi` immediates are written as hex bit patterns, since the printed float is rounded.
* Any instruction `dvp-as` would not reassemble exactly is written as a `.word` pair with the
  disassembly in a comment. The retail segment currently needs none.

Editing: change `vu_split.py`'s output rules, not `vutext.vsm`, for anything that should survive
the next split. Hand changes to microcode belong in a mod build, which no longer matches retail.
