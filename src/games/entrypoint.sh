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

exec /bin/bash