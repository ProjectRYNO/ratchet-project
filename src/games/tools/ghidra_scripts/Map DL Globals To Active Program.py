#@author
#@category Export

import re
from java.io import File


GLOBALS_TXT = r"D:\Repos\ProjectRYNO\ratchet-project\src\games\dl\TESTS\dlglobals.txt"
OUT_TXT = r"D:\Repos\ProjectRYNO\ratchet-project\src\games\dl\TESTS\proto_globals_symbols_ghidra.txt"
REPORT_TXT = r"D:\Repos\ProjectRYNO\ratchet-project\src\games\dl\TESTS\proto_globals_symbols_ghidra_report.txt"


def extract_name(line):
    line = re.sub(r"//.*$", "", line).strip()
    if not line.endswith(";"):
        return None
    line = line[:-1].strip()
    if not line or line.startswith("#"):
        return None
    line = re.sub(r"\s*=.*$", "", line).strip()
    match = re.search(r"\(\s*\*\s*([A-Za-z_][A-Za-z0-9_]*)\s*\)", line)
    if match:
        return match.group(1)
    line = re.sub(r"\[[^\]]*\]", " ", line).strip()
    match = re.search(r"([A-Za-z_][A-Za-z0-9_]*)\s*$", line)
    return match.group(1) if match else None


def clean_decl(line):
    return re.sub(r"\s+", " ", line.strip())


def block_name(addr):
    block = currentProgram.getMemory().getBlock(addr)
    return block.getName() if block is not None else ""


def data_type_at(addr):
    data = currentProgram.getListing().getDataAt(addr)
    if data is None:
        return "", 0
    data_type = data.getDataType()
    type_name = data_type.getDisplayName() if data_type is not None else ""
    return type_name, data.getLength()


def parse_declarations(path):
    rows = []
    current_file = ""
    with open(path, "r") as f:
        for raw in f:
            line = raw.strip()
            file_match = re.match(r"^// FILE --\s*(.*)$", line)
            if file_match:
                current_file = file_match.group(1).strip()
                continue
            name = extract_name(line)
            if name:
                rows.append((name, clean_decl(line), current_file))
    return rows


def choose_symbol(symbols):
    candidates = []
    for symbol in symbols:
        addr = symbol.getAddress()
        if addr is None or not addr.isMemoryAddress():
            continue
        block = currentProgram.getMemory().getBlock(addr)
        if block is None:
            continue
        name = block.getName()
        if re.search(r"text|vutext|EXTERNAL|debug|symtab|strtab|shstrtab|reginfo|mdebug", name, re.I):
            continue
        candidates.append(symbol)
    if not candidates:
        return None
    candidates.sort(key=lambda symbol: symbol.getAddress().getOffset())
    return candidates[0]


decls = parse_declarations(GLOBALS_TXT)
symbol_table = currentProgram.getSymbolTable()

rows = []
missing = []
duplicates = []
emitted = set()

for name, declaration, source_file in decls:
    symbols = list(symbol_table.getGlobalSymbols(name))
    chosen = choose_symbol(symbols)
    if chosen is None:
        missing.append((name, declaration, source_file))
        continue

    data_symbols = []
    for symbol in symbols:
        if choose_symbol([symbol]) is not None:
            data_symbols.append(symbol)
    addrs = sorted(set([symbol.getAddress().getOffset() for symbol in data_symbols]))
    if len(addrs) > 1:
        duplicates.append((name, addrs, declaration, source_file))

    addr = chosen.getAddress()
    offset = addr.getOffset()
    key = (name, offset)
    if key in emitted:
        continue
    emitted.add(key)

    ghidra_type, length = data_type_at(addr)
    metadata = [
        "type:data",
        "section:%s" % block_name(addr),
        "ghidra_type:%s" % ghidra_type,
        "size:0x%x" % length,
        "decl:%s" % declaration,
    ]
    if source_file:
        metadata.append("file:%s" % source_file)

    rows.append((offset, "%s = 0x%08x;  // %s" % (name, offset, " ".join(metadata))))

rows.sort(key=lambda row: (row[0], row[1]))

with open(OUT_TXT, "w") as f:
    f.write("// Prototype globals mapped from dlglobals.txt to active Ghidra program symbols\n")
    f.write("// Program: %s\n" % currentProgram.getName())
    f.write("// declarations: %d\n" % len(decls))
    f.write("// matched: %d\n" % len(rows))
    f.write("// missing: %d\n" % len(missing))
    f.write("// duplicate_name_multi_addr: %d\n\n" % len(duplicates))
    for _, line in rows:
        f.write(line + "\n")

with open(REPORT_TXT, "w") as f:
    f.write("declarations: %d\n" % len(decls))
    f.write("matched: %d\n" % len(rows))
    f.write("missing: %d\n" % len(missing))
    f.write("duplicate_name_multi_addr: %d\n\n" % len(duplicates))
    f.write("[missing]\n")
    for name, declaration, source_file in missing:
        f.write("%s\t%s\t%s\n" % (name, declaration, source_file))
    f.write("\n[duplicate_name_multi_addr]\n")
    for name, addrs, declaration, source_file in duplicates:
        f.write("%s\t%s\t%s\t%s\n" % (
            name,
            ",".join(["0x%08x" % addr for addr in addrs]),
            declaration,
            source_file,
        ))

print("Exported %d globals to: %s" % (len(rows), OUT_TXT))
print("Missing %d globals; report: %s" % (len(missing), REPORT_TXT))
