from __future__ import annotations

import argparse
import bisect
import re
import struct
from pathlib import Path


N_SO = 0x64
N_SOL = 0x84
N_FUN = 0x24


def cstr(buf: bytes, off: int) -> str:
    end = buf.find(b"\0", off)
    if end < 0:
        end = len(buf)
    return buf[off:end].decode("utf-8", errors="replace")


def extract_source_dirs(buf: bytes) -> list[str]:
    text = buf.decode("latin1", errors="ignore")
    dirs = set()
    for match in re.finditer(r"(/(?:public|home)/[^\x00]*/|[A-Za-z]:\\[^\x00]*[\\/])", text):
        value = match.group(1).replace("\\", "/")
        if value.endswith("/"):
            dirs.add(value)
    return sorted(dirs, key=len, reverse=True)


def complete_source_path(source: str, source_dirs: list[str]) -> str:
    if not source or "/" in source:
        return source
    suffix = source.lower()
    candidates = [d + source for d in source_dirs if suffix.endswith(".cpp") and d.endswith("/client/core/")]
    if len(candidates) == 1:
        return candidates[0]
    return source


def read_sections(elf: bytes) -> dict[str, tuple[int, int, int]]:
    if elf[:4] != b"\x7fELF" or elf[4] != 1 or elf[5] != 1:
        raise ValueError("expected 32-bit little-endian ELF")

    e_shoff = struct.unpack_from("<I", elf, 0x20)[0]
    e_shentsize = struct.unpack_from("<H", elf, 0x2E)[0]
    e_shnum = struct.unpack_from("<H", elf, 0x30)[0]
    e_shstrndx = struct.unpack_from("<H", elf, 0x32)[0]

    shstr_hdr = e_shoff + e_shstrndx * e_shentsize
    shstr_off = struct.unpack_from("<I", elf, shstr_hdr + 0x10)[0]

    sections: dict[str, tuple[int, int, int]] = {}
    for i in range(e_shnum):
        sh = e_shoff + i * e_shentsize
        name_off = struct.unpack_from("<I", elf, sh)[0]
        addr = struct.unpack_from("<I", elf, sh + 0x0C)[0]
        off = struct.unpack_from("<I", elf, sh + 0x10)[0]
        size = struct.unpack_from("<I", elf, sh + 0x14)[0]
        sections[cstr(elf, shstr_off + name_off)] = (addr, off, size)
    return sections


def normalize_path(base_dir: str, name: str) -> str:
    if not name:
        return ""
    if re.match(r"^[A-Za-z]:[\\/]", name) or name.startswith("/"):
        return name.replace("\\", "/")
    return (base_dir + name).replace("\\", "/")


def canonical_name(name: str) -> str:
    name = re.sub(r"___dupe\d+$", "", name)
    if "__" in name and not name.startswith("__"):
        name = name.split("__", 1)[0]
    return name


def parse_stabs(elf_path: Path) -> list[dict[str, object]]:
    elf = elf_path.read_bytes()
    sections = read_sections(elf)
    _stab_addr, stab_off, stab_size = sections[".stab"]
    _stabstr_addr, stabstr_off, stabstr_size = sections[".stabstr"]
    stab = elf[stab_off : stab_off + stab_size]
    stabstr = elf[stabstr_off : stabstr_off + stabstr_size]

    base_dir = ""
    current_file = ""
    funcs: list[dict[str, object]] = []

    for off in range(0, len(stab), 12):
        n_strx, n_type, _n_other, _n_desc, n_value = struct.unpack_from("<IBBHI", stab, off)
        text = cstr(stabstr, n_strx) if n_strx else ""

        if n_type == N_SO:
            if not text:
                current_file = ""
                continue
            if text.endswith(("/", "\\")):
                base_dir = text.replace("\\", "/")
            else:
                current_file = normalize_path(base_dir, text)
            continue

        if n_type == N_SOL:
            current_file = normalize_path(base_dir, text)
            continue

        if n_type == N_FUN and text:
            raw_name = text.split(":", 1)[0]
            funcs.append(
                {
                    "addr": n_value,
                    "name": raw_name,
                    "canon": canonical_name(raw_name),
                    "source": current_file,
                    "comment": Path(current_file).name if current_file else "",
                }
            )

    funcs.sort(key=lambda item: (int(item["addr"]), str(item["name"])))
    return funcs


def parse_mdebug(elf_path: Path) -> list[dict[str, object]]:
    elf = elf_path.read_bytes()
    sections = read_sections(elf)
    _mdebug_addr, mdebug_off, mdebug_size = sections[".mdebug"]
    _mdebug_end = mdebug_off + mdebug_size
    source_dirs = extract_source_dirs(elf)

    hdr_fmt = "<hh23i"
    hdr = struct.unpack_from(hdr_fmt, elf, mdebug_off)
    keys = [
        "magic",
        "vstamp",
        "ilineMax",
        "cbLine",
        "cbLineOffset",
        "idnMax",
        "cbDnOffset",
        "ipdMax",
        "cbPdOffset",
        "isymMax",
        "cbSymOffset",
        "ioptMax",
        "cbOptOffset",
        "iauxMax",
        "cbAuxOffset",
        "issMax",
        "cbSsOffset",
        "issExtMax",
        "cbSsExtOffset",
        "ifdMax",
        "cbFdOffset",
        "crfd",
        "cbRfdOffset",
        "iextMax",
        "cbExtOffset",
    ]
    h = dict(zip(keys, hdr))

    def string_at(offset: int) -> str:
        if offset < 0 or offset >= h["issMax"]:
            return ""
        return cstr(elf, h["cbSsOffset"] + offset)

    fdr_size = 72
    pdr_size = 52
    sym_size = 12
    funcs: list[dict[str, object]] = []

    for ifd in range(h["ifdMax"]):
        foff = h["cbFdOffset"] + ifd * fdr_size
        fdr = struct.unpack_from("<10IHH7I", elf, foff)
        adr, rss, iss_base, _cb_ss, isym_base, csym = fdr[:6]
        ipd_first, cpd = fdr[10], fdr[11]
        source = string_at(rss) or string_at(iss_base)
        source = source.replace("\\", "/")
        source = complete_source_path(source, source_dirs)

        for i in range(cpd):
            poff = h["cbPdOffset"] + (ipd_first + i) * pdr_size
            pdr = struct.unpack_from("<9IHH3I", elf, poff)
            p_addr, p_isym = pdr[0], pdr[1]
            raw_name = ""
            abs_isym = isym_base + p_isym
            if 0 <= abs_isym < h["isymMax"]:
                soff = h["cbSymOffset"] + abs_isym * sym_size
                iss, _value, _packed, _index = struct.unpack_from("<iiHH", elf, soff)
                raw_name = string_at(iss_base + iss) or string_at(iss)
            abs_addr = adr + p_addr if p_addr and p_addr < 0x100000 else (p_addr if p_addr else adr)
            funcs.append(
                {
                    "addr": abs_addr,
                    "name": raw_name,
                    "canon": canonical_name(raw_name),
                    "source": source,
                    "comment": Path(source).name if source else "",
                    "ifd": ifd,
                    "sc": "",
                    "index": abs_isym,
                    "kind": "pdr",
                }
            )

        for i in range(csym):
            soff = h["cbSymOffset"] + (isym_base + i) * sym_size
            iss, value, packed, index = struct.unpack_from("<iiHH", elf, soff)
            st = packed & 0x3F
            sc = (packed >> 6) & 0x1F
            if st != 6:
                continue
            raw_name = string_at(iss_base + iss) or string_at(iss)
            if not raw_name:
                continue
            funcs.append(
                {
                    "addr": value if value else adr,
                    "name": raw_name,
                    "canon": canonical_name(raw_name),
                    "source": source,
                    "comment": Path(source).name if source else "",
                    "ifd": ifd,
                    "sc": sc,
                    "index": index,
                    "kind": "sym",
                }
            )

    funcs.sort(key=lambda item: (int(item["addr"]), str(item["name"])))
    return funcs


def parse_symbols(path: Path) -> list[tuple[str, int, str]]:
    out: list[tuple[str, int, str]] = []
    pat = re.compile(r"^\s*([A-Za-z_~][A-Za-z0-9_~.]*)\s*=\s*(0x[0-9A-Fa-f]+);")
    for line in path.read_text().splitlines():
        m = pat.match(line)
        if m:
            out.append((m.group(1), int(m.group(2), 16), line))
    return out


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--elf", type=Path, default=Path("keep/proto_elf.elf"))
    parser.add_argument("--symbols", type=Path, default=Path("../config/symbols_net.text.txt"))
    parser.add_argument("--out", type=Path, default=Path("net_function_sources.tsv"))
    parser.add_argument("--list-sections", action="store_true")
    parser.add_argument("--dump-mdebug-header", action="store_true")
    parser.add_argument("--find-debug-name")
    parser.add_argument("--start-name", default="ezNetCnfInit")
    parser.add_argument("--end-name", default="GetLastContentType")
    args = parser.parse_args()

    if args.list_sections:
        elf = args.elf.read_bytes()
        for name, (addr, off, size) in read_sections(elf).items():
            print(f"{name}\taddr=0x{addr:x}\toff=0x{off:x}\tsize=0x{size:x}")
        return

    if args.dump_mdebug_header:
        elf = args.elf.read_bytes()
        sections = read_sections(elf)
        _mdebug_addr, mdebug_off, mdebug_size = sections[".mdebug"]
        mdebug = elf[mdebug_off : mdebug_off + mdebug_size]
        hdr_fmt = "<hh23i"
        hdr = struct.unpack_from(hdr_fmt, mdebug, 0)
        print(hdr)
        print(f".mdebug off=0x{mdebug_off:x} size=0x{mdebug_size:x}")
        return

    try:
        funcs = parse_stabs(args.elf)
    except KeyError:
        funcs = parse_mdebug(args.elf)

    if args.find_debug_name:
        needle = args.find_debug_name
        for f in funcs:
            if needle in str(f["name"]):
                print(
                    f"0x{int(f['addr']):08x}\t{f['name']}\t{f['comment']}\t{f['source']}"
                )
        return
    symbols = parse_symbols(args.symbols)

    start_i = next(i for i, (name, _addr, _line) in enumerate(symbols) if name == args.start_name)
    end_i = next(i for i, (name, _addr, _line) in enumerate(symbols) if name == args.end_name)
    wanted = symbols[start_i : end_i + 1]

    by_name: dict[str, list[dict[str, object]]] = {}
    for f in funcs:
        canon = str(f.get("canon") or f["name"])
        if canon:
            by_name.setdefault(canon, []).append(f)
    for matches in by_name.values():
        matches.sort(key=lambda item: int(item["addr"]))

    proto_addrs = [int(f["addr"]) for f in funcs]
    rows = [
        "# function\tretail_addr\tproto_addr\tcomment_block\tfile\tmatch",
    ]
    exact = fallback = missing = 0

    for name, retail_addr, _line in wanted:
        canon = canonical_name(name)
        matches = by_name.get(canon, [])
        chosen: dict[str, object] | None = None
        match_kind = "missing"
        if len(matches) == 1:
            chosen = matches[0]
            match_kind = "name" if str(chosen["name"]) == name else "canonical_name"
            exact += 1
        elif len(matches) > 1:
            chosen = min(matches, key=lambda m: abs(int(m["addr"]) - retail_addr))
            match_kind = "duplicate_canonical_nearest_addr"
            exact += 1
        else:
            pos = bisect.bisect_right(proto_addrs, retail_addr) - 1
            if pos >= 0:
                chosen = funcs[pos]
                match_kind = "nearest_prior_addr"
                fallback += 1
            else:
                missing += 1

        if chosen is None:
            rows.append(f"{name}\t0x{retail_addr:08x}\t\t\t\t{match_kind}")
        else:
            rows.append(
                f"{name}\t0x{retail_addr:08x}\t0x{int(chosen['addr']):08x}\t"
                f"{chosen['comment']}\t{chosen['source']}\t{match_kind}"
            )

    args.out.write_text("\n".join(rows) + "\n")
    print(f"wrote {args.out}")
    print(f"rows: {len(wanted)} name_matches: {exact} fallback_addr_matches: {fallback} missing: {missing}")


if __name__ == "__main__":
    main()
