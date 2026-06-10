import re
from pathlib import Path


TESTS = Path(__file__).resolve().parent
INPUT = TESTS / "PROTOTYPE FUNCTIONS.txt"


def main():
    text = INPUT.read_text(errors="replace")
    blocks = re.split(r"(?=^@function\s+[0-9a-fA-F]+)", text, flags=re.MULTILINE)
    rows = []
    for block in blocks:
        header = re.match(r"@function\s+([0-9a-fA-F]+)", block)
        if not header:
            continue
        addr = int(header.group(1), 16)
        path_match = re.search(r"/\*\s*(X:\\rcb\\code\\stable\\[^*]+?)\s*\*/", block)
        signature = ""
        for line in block.splitlines()[1:]:
            stripped = line.strip()
            if stripped and not stripped.startswith("/*") and not stripped.startswith("//"):
                signature = stripped
                break
        if path_match:
            windows_path = path_match.group(1)
            relative = windows_path.split(r"X:\rcb\code\stable\\", 1)[-1]
            relative = relative.replace("\\", "/")
        else:
            windows_path = ""
            relative = ""
        rows.append((addr, relative, signature))

    with_path = [row for row in rows if row[1]]
    output = [
        "proto_addr,source_path,signature",
        *[
            f"0x{addr:08x},{path},{signature.replace(',', ';')}"
            for addr, path, signature in rows
        ],
    ]
    (TESTS / "prototype_function_paths.csv").write_text("\n".join(output) + "\n")

    print(f"functions: {len(rows)}")
    print(f"with_source_path: {len(with_path)}")
    for addr, path, signature in with_path[:20]:
        print(f"0x{addr:08x} {path} :: {signature}")


if __name__ == "__main__":
    main()
