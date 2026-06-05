# =============================================================================
# Runtime image
# =============================================================================

FROM debian:13-slim

ENV DEBIAN_FRONTEND=noninteractive

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
        libwine:i386 \
        libc6:i386 \
        libstdc++6:i386 \
        libgcc-s1:i386 \
        winbind \
    && rm -rf /var/lib/apt/lists/*

# ── Install Wrench ────────────────────────────────────────────────────────────

RUN curl -fsSL \
        "https://github.com/chaoticgd/wrench/releases/download/v0.5/wrench_v0.5_linux-glibc2.39-0ubuntu8.5.zip" \
        -o /tmp/wrench.zip && \
    unzip /tmp/wrench.zip -d /tmp/wrench_extract && \
    mv /tmp/wrench_extract/wrench_v0.5_linux-glibc2.39-0ubuntu8.5 /opt/wrench && \
    rm -rf /tmp/wrench.zip /tmp/wrench_extract && \
    chmod +x /opt/wrench

# ── Python dependencies ───────────────────────────────────────────────────────

WORKDIR /ProjectRYNO

COPY requirements.txt .

RUN pip3 install --no-cache-dir --break-system-packages -r requirements.txt

# ── Wine init ─────────────────────────────────────────────────────────────────

RUN wineboot --init 2>/dev/null || true

# ── Entrypoint ────────────────────────────────────────────────────────────────

COPY entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh

CMD ["/entrypoint.sh"]