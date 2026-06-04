from collections import defaultdict

MAX_LINES_TO_CHECK = 50

output_file = askFile("Save Output", "Save")

fm = currentProgram.getFunctionManager()

files = defaultdict(list)

for func in fm.getFunctions(True):

    comment = getPlateComment(func.getEntryPoint())
    if not comment:
        continue

    source_file = None

    lines = comment.splitlines()

    for line in lines[:MAX_LINES_TO_CHECK]:

        line = line.strip()

        if line.startswith("X:\\rcb\\"):
            source_file = line
            break

    if source_file is None:
        continue

    entry = func.getEntryPoint().getOffset()
    size = func.getBody().getNumAddresses()

    files[source_file].append(
        (entry, size, func.getName(True))
    )

with open(output_file.absolutePath, "w") as f:

    for source_file in sorted(files.keys()):

        funcs = sorted(files[source_file], key=lambda x: x[0])

        f.write(source_file + "\n")
        f.write("=" * len(source_file) + "\n")

        for addr, size, name in funcs:
            f.write(" %08X %s\n" % (
                addr,
                size,
                name
            ))

        f.write("\n\n")

print("Found %d source files" % len(files))