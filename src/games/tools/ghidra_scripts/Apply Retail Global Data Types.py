# Applies data types to retail globals from generated ProjectRYNO mapping files.
#
# This intentionally types base globals instead of naming interior field addresses.
# It expects useful game structs to be present in the current program or an open
# datatype archive imported from the prototype.

from ghidra.app.script import GhidraScript
from ghidra.app.services import DataTypeManagerService
from ghidra.program.model.data import ArrayDataType, PointerDataType, DataTypeConflictHandler
from ghidra.program.model.listing import CodeUnit
from ghidra.program.model.symbol import SourceType
from ghidra.util.task import ConsoleTaskMonitor

import os
import re


ROOT = r"D:\Repos\ProjectRYNO\ratchet-project\src\games\dl\TESTS"
INPUT_FILES = [
    "retail_globals_from_proto_combined_all_refs.txt",
    "retail_globals_startlevel_manual.txt",
    "retail_globals_general_refs_strong.txt",
]
FIELDS_FILE = "retail_globals_general_refs_fields.txt"
REPORT_FILE = "apply_retail_global_data_types_report.txt"


ROW_RE = re.compile(r"^([A-Za-z_][A-Za-z0-9_]*)\s*=\s*0x([0-9a-fA-F]+);\s*//\s*(.*)$")


def parse_meta(comment, key):
    match = re.search(r"(?:^|\s)%s:([^ ](?:.*?))(?=\s+[A-Za-z_][A-Za-z0-9_]*:|$)" % re.escape(key), comment)
    return match.group(1).strip() if match else ""


def parse_rows():
    rows = {}
    for filename in INPUT_FILES:
        path = os.path.join(ROOT, filename)
        if not os.path.exists(path):
            continue
        for raw in open(path, "r").read().splitlines():
            match = ROW_RE.match(raw.strip())
            if not match:
                continue
            name, addr_text, comment = match.groups()
            decl = parse_meta(comment, "decl")
            if not decl:
                continue
            rows[name] = {
                "name": name,
                "address": int(addr_text, 16),
                "decl": decl,
                "source": filename,
                "raw": raw.strip(),
            }
    return rows


def parse_field_bases():
    bases = set()
    path = os.path.join(ROOT, FIELDS_FILE)
    if not os.path.exists(path):
        return bases
    for raw in open(path, "r").read().splitlines():
        match = re.match(r"^([A-Za-z_][A-Za-z0-9_]*)\+0x[0-9a-fA-F]+:", raw.strip())
        if match:
            bases.add(match.group(1))
    return bases


def strip_decl_name(decl, name):
    text = decl.strip().rstrip(";").strip()
    text = re.sub(r"\s+", " ", text)
    text = re.sub(r"\[[^\]]*\]", "", text)
    patterns = [
        r"\(\s*\*\s*%s\s*\)" % re.escape(name),
        r"\*\s*%s\b" % re.escape(name),
        r"&\s*%s\b" % re.escape(name),
        r"\b%s\b" % re.escape(name),
    ]
    for pattern in patterns:
        new_text, count = re.subn(pattern, "", text, count=1)
        if count:
            return new_text.strip()
    return ""


def parse_array_dims(decl, name):
    text = decl.strip().rstrip(";").strip()
    match = re.search(r"\b%s\b((?:\s*\[[^\]]*\])+)" % re.escape(name), text)
    if not match:
        return []
    dims = []
    for dim in re.findall(r"\[([^\]]*)\]", match.group(1)):
        dim = dim.strip()
        if not dim:
            return []
        try:
            dims.append(int(dim, 0))
        except Exception:
            return []
    return dims


def parse_type_request(decl, name):
    if "(*" in decl:
        return None, [], "function pointer declaration skipped"
    dims = parse_array_dims(decl, name)
    type_text = strip_decl_name(decl, name)
    if not type_text:
        return None, [], "could not parse declaration"
    pointer_count = type_text.count("*")
    type_name = type_text.replace("*", " ")
    type_name = type_name.replace("const ", " ").replace("volatile ", " ")
    type_name = re.sub(r"\s+", " ", type_name).strip()
    if type_name.endswith("&"):
        type_name = type_name[:-1].strip()
    return (type_name, pointer_count), dims, ""


def all_data_type_managers(state):
    managers = [currentProgram.getDataTypeManager()]
    service = state.getTool().getService(DataTypeManagerService)
    if service:
        for manager in service.getDataTypeManagers():
            if manager not in managers:
                managers.append(manager)
    return managers


def find_data_type(type_name, managers):
    aliases = {
        "char": "char",
        "signed char": "char",
        "unsigned char": "uchar",
        "short": "short",
        "short int": "short",
        "short unsigned int": "ushort",
        "unsigned short": "ushort",
        "int": "int",
        "unsigned int": "uint",
        "long": "long",
        "long int": "long",
        "long unsigned int": "ulong",
        "unsigned long": "ulong",
        "float": "float",
        "double": "double",
        "bool": "bool",
        "void": "void",
        "uint64": "uint64_t",
        "int64": "int64_t",
        "u_int": "uint",
        "size_t": "size_t",
    }
    candidates = [type_name]
    if type_name in aliases:
        candidates.append(aliases[type_name])
    if type_name.startswith("struct "):
        candidates.append(type_name[7:])
    if type_name.startswith("enum "):
        candidates.append(type_name[5:])

    for candidate in candidates:
        for manager in managers:
            found = []
            manager.findDataTypes(candidate, found)
            exact = [dt for dt in found if dt.getName() == candidate or dt.getDisplayName() == candidate]
            if exact:
                exact.sort(key=lambda dt: len(str(dt.getCategoryPath())))
                return exact[0]
            if found:
                found.sort(key=lambda dt: len(dt.getName()))
                return found[0]
    return None


def build_data_type(base_type, pointer_count, dims, managers):
    dt = find_data_type(base_type, managers)
    if dt is None:
        return None
    for _ in range(pointer_count):
        dt = PointerDataType(dt, currentProgram.getDataTypeManager())
    for dim in reversed(dims):
        dt = ArrayDataType(dt, dim, dt.getLength())
    return dt


def clear_existing_data(address, length):
    listing = currentProgram.getListing()
    end = address.add(max(length - 1, 0))
    clearListing(address, end)
    return listing


def main():
    rows_by_name = parse_rows()
    field_bases = parse_field_bases()
    managers = all_data_type_managers(state)
    af = currentProgram.getAddressFactory()
    listing = currentProgram.getListing()
    symbol_table = currentProgram.getSymbolTable()

    targets = [rows_by_name[name] for name in sorted(field_bases) if name in rows_by_name]
    applied = []
    skipped = []
    failed = []

    monitor = ConsoleTaskMonitor()
    tx = currentProgram.startTransaction("Apply retail global data types")
    commit = False
    try:
        for row in targets:
            request, dims, reason = parse_type_request(row["decl"], row["name"])
            if request is None:
                skipped.append("%s: %s | %s" % (row["name"], reason, row["decl"]))
                continue
            base_type, pointer_count = request
            dt = build_data_type(base_type, pointer_count, dims, managers)
            if dt is None:
                skipped.append("%s: datatype not found: %s | %s" % (row["name"], base_type, row["decl"]))
                continue
            address = af.getDefaultAddressSpace().getAddress(row["address"])
            try:
                symbol_table.createLabel(address, row["name"], SourceType.USER_DEFINED)
            except Exception:
                pass
            try:
                existing = listing.getDataAt(address)
                if existing is not None and existing.getDataType().isEquivalent(dt):
                    applied.append("%s 0x%08x already %s" % (row["name"], row["address"], dt.getDisplayName()))
                    continue
                clear_existing_data(address, dt.getLength())
                listing.createData(address, dt)
                code_unit = listing.getCodeUnitAt(address)
                if code_unit:
                    code_unit.setComment(CodeUnit.PLATE_COMMENT, "typed from %s\n%s" % (row["source"], row["decl"]))
                applied.append("%s 0x%08x %s" % (row["name"], row["address"], dt.getDisplayName()))
            except Exception as exc:
                failed.append("%s 0x%08x %s: %s" % (row["name"], row["address"], dt.getDisplayName(), exc))
        commit = True
    finally:
        currentProgram.endTransaction(tx, commit)

    report = []
    report.append("Apply retail global data types report")
    report.append("field_bases: %d" % len(field_bases))
    report.append("targets_with_decls: %d" % len(targets))
    report.append("applied_or_already: %d" % len(applied))
    report.append("skipped: %d" % len(skipped))
    report.append("failed: %d" % len(failed))
    report.append("")
    report.append("Applied:")
    report.extend(applied)
    report.append("")
    report.append("Skipped:")
    report.extend(skipped)
    report.append("")
    report.append("Failed:")
    report.extend(failed)

    out_path = os.path.join(ROOT, REPORT_FILE)
    f = open(out_path, "w")
    f.write("\n".join(report))
    f.close()
    print("\n".join(report[:8]))
    print("Wrote " + out_path)


main()
