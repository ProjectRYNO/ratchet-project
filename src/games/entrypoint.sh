#!/bin/bash

# ── EE GCC compiler ───────────────────────────────────────────────────────────
if [ ! -f "/ProjectRYNO/tools/cc/bin/ee-gcc.exe" ]; then
    echo "[Project RYNO] EE GCC compiler not found, downloading..."
    curl -L -o /tmp/ee-gcc.tar.gz https://bordplate.no/ee-gcc2.95.2-SN-v2.73a.tar.gz && \
    tar -xzf /tmp/ee-gcc.tar.gz -C /ProjectRYNO/tools/ && \
    rm /tmp/ee-gcc.tar.gz
    echo "[Project RYNO] EE GCC compiler installed."
else
    echo "[Project RYNO] EE GCC compiler already present."
fi

# ── Wrench ────────────────────────────────────────────────────────────────────
if [ ! -x "/opt/wrench/wrenchbuild" ]; then
    echo "[Project RYNO] ERROR: Wrench not installed."
    exit 1
fi
echo "[Project RYNO] Wrench installed."

# ── Fix build.asset ELF path for Wine ─────────────────────────────────────────
if [ -f "/ProjectRYNO/assets/dl/build.asset" ]; then
    if grep -q '"./build/boot_elf.elf"' /ProjectRYNO/assets/dl/build.asset; then
        echo "[Project RYNO] Fixing build.asset ELF path for Wine..."
        sed -i 's|src: "./build/boot_elf.elf"|src: "../build/boot_elf.elf"|' /ProjectRYNO/assets/dl/build.asset
    fi
fi

exec /bin/bash