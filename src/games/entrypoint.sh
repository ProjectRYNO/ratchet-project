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
if [ ! -f "/opt/wrench/wrenchbuild.exe" ]; then
    echo "[Project RYNO] Wrench not found, downloading latest Windows release..."

    WRENCH_URL=$(curl -s https://api.github.com/repos/chaoticgd/wrench/releases/latest \
        | python3 -c "
import sys, json
assets = json.load(sys.stdin)['assets']
for a in assets:
    if 'windows' in a['name'].lower() and a['name'].endswith('.zip'):
        print(a['browser_download_url'])
        break
")

    if [ -z "$WRENCH_URL" ]; then
        echo "[Project RYNO] ERROR: Could not find a Windows release for Wrench. Check https://github.com/chaoticgd/wrench/releases"
        exec /bin/bash
    fi

    echo "[Project RYNO] Downloading Wrench from: $WRENCH_URL"
    curl -L -o /tmp/wrench.zip "$WRENCH_URL" && \
    mkdir -p /tmp/wrench-extract && \
    unzip -o /tmp/wrench.zip -d /tmp/wrench-extract && \
    mkdir -p /opt/wrench && \
    mv /tmp/wrench-extract/*/* /opt/wrench/ && \
    rm -rf /tmp/wrench.zip /tmp/wrench-extract
    echo "[Project RYNO] Wrench installed."
else
    echo "[Project RYNO] Wrench already present."
fi

# ── Fix build.asset ELF path for Wine ─────────────────────────────────────────
if [ -f "/ProjectRYNO/assets/dl/build.asset" ]; then
    if grep -q '"./build/boot_elf.elf"' /ProjectRYNO/assets/dl/build.asset; then
        echo "[Project RYNO] Fixing build.asset ELF path for Wine..."
        sed -i 's|src: "./build/boot_elf.elf"|src: "../build/boot_elf.elf"|' /ProjectRYNO/assets/dl/build.asset
    fi
fi

exec /bin/bash