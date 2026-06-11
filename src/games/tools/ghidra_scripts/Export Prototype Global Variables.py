#@author
#@category Export

from ghidra.program.model.symbol import SourceType
from java.io import File


DEFAULT_OUTPUT = r"D:\Repos\ProjectRYNO\ratchet-project\src\games\dl\TESTS\proto_global_variables.txt"


def sanitize(value):
    if value is None:
        return ""
    return str(value).replace("\t", " ").replace("\r", " ").replace("\n", " ")


def is_default_name(name):
    if name is None:
        return True
    return (
        name == "(unnamed)" or
        name.startswith("DAT_") or
        name.startswith("PTR_") or
        name.startswith("BYTE_") or
        name.startswith("WORD_") or
        name.startswith("DWORD_") or
        name.startswith("QWORD_") or
        name.startswith("FLOAT_") or
        name.startswith("DOUBLE_") or
        name.startswith("LAB_") or
        name.startswith("switchdataD_")
    )


def get_block_name(addr):
    block = currentProgram.getMemory().getBlock(addr)
    if block is None:
        return ""
    return block.getName()


def choose_output_file():
    default_file = File(DEFAULT_OUTPUT)
    parent = default_file.getParentFile()
    if parent is not None and parent.exists():
        return default_file
    return askFile("Save prototype globals", "Save")


listing = currentProgram.getListing()
symbols = currentProgram.getSymbolTable()
outfile = choose_output_file()

rows = []
seen = set()

data_iter = listing.getDefinedData(True)
while data_iter.hasNext():
    data = data_iter.next()

    # Only export top-level data items. Structure fields and array elements inherit
    # their parent global and would otherwise create a lot of duplicate noise.
    if data.getParent() is not None:
        continue

    addr = data.getAddress()
    data_type = data.getDataType()
    data_type_name = data_type.getDisplayName() if data_type is not None else ""
    length = data.getLength()
    block_name = get_block_name(addr)

    sym_iter = symbols.getSymbols(addr)
    while sym_iter.hasNext():
        sym = sym_iter.next()
        name = sym.getName(True)
        short_name = sym.getName()
        source = sym.getSource()

        if source == SourceType.DEFAULT and is_default_name(short_name):
            continue
        if is_default_name(short_name):
            continue

        namespace = sym.getParentNamespace().getName(True)
        key = (addr.getOffset(), name)
        if key in seen:
            continue
        seen.add(key)

        declaration = "%s %s;" % (data_type_name, name)
        rows.append((
            addr.getOffset(),
            name,
            data_type_name,
            length,
            namespace,
            source,
            block_name,
            declaration,
        ))

rows.sort(key=lambda row: (row[0], row[1]))

with open(outfile.getAbsolutePath(), "w") as f:
    f.write("# Prototype global variables exported from active Ghidra program\n")
    f.write("# Program: %s\n" % sanitize(currentProgram.getName()))
    f.write("# Count: %d\n" % len(rows))
    f.write("# Columns: address\tname\tdatatype\tlength\tnamespace\tsource\tsection\tdeclaration\n")

    for addr, name, data_type_name, length, namespace, source, block_name, declaration in rows:
        f.write("0x%08X\t%s\t%s\t%d\t%s\t%s\t%s\t%s\n" % (
            addr,
            sanitize(name),
            sanitize(data_type_name),
            length,
            sanitize(namespace),
            sanitize(source),
            sanitize(block_name),
            sanitize(declaration),
        ))

print("Exported %d prototype globals to: %s" % (len(rows), outfile.getAbsolutePath()))
