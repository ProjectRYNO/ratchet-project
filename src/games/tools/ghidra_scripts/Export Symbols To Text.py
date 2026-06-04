#@author
#@category Export

outfile = askFile("Save symbols.txt", "Save")

with open(outfile.getAbsolutePath(), "w") as f:
    fm = currentProgram.getFunctionManager()

    for func in fm.getFunctions(True):
        addr = func.getEntryPoint().getOffset()
        name = func.getName()

        size = func.getBody().getMaxAddress().subtract(
            func.getEntryPoint()
        ) + 1

        f.write("%s = 0x%08x;  // type:func\n" % (
            name,
            addr
            # size
        ))

print("Exported functions to: %s" % outfile.getAbsolutePath())
