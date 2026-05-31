FROM debian:12-slim

ENV DEBIAN_FRONTEND=noninteractive

# ── System packages ───────────────────────────────────────────────────────────
RUN dpkg --add-architecture i386 && \
    apt-get update && \
    apt-get install -y --no-install-recommends \
        make \
        curl \
        ca-certificates \
        unzip \
        python3 \
        python3-pip \
        python-is-python3 \
        wine32 \
        wine64 \
        binutils-mips-linux-gnu \
    && rm -rf /var/lib/apt/lists/*

# ── Python dependencies ───────────────────────────────────────────────────────
WORKDIR /ProjectRYNO
COPY requirements.txt .
RUN pip3 install --no-cache-dir --break-system-packages -r requirements.txt

# ── Wine first-run init ───────────────────────────────────────────────────────
RUN wineboot --init 2>/dev/null || true

# ── Entrypoint ────────────────────────────────────────────────────────────────
COPY entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh

CMD ["/entrypoint.sh"]