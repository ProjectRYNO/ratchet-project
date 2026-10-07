# =============================================================================
# Runtime image
# =============================================================================

FROM debian:13-slim

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        make \
        curl \
        ca-certificates \
        unzip \
        python3 \
        python3-pip \
        python-is-python3 \
        binutils-mips-linux-gnu \
    && rm -rf /var/lib/apt/lists/*

# ── Install Wrench ────────────────────────────────────────────────────────────

# Latest Linux nightly checked 2026-10-06; pin the artifact and SHA-256.
RUN curl -fsSL \
        "https://github.com/chaoticgd/wrench/releases/download/unstable/wrench_2026-10-05-7638b99_linux-glibc2.39-0ubuntu8.9.zip" \
        -o /tmp/wrench.zip && \
    echo "09aaf19e366280c25ee492eec0fd70b0d240cc705fe7b6989825ee3747626b92  /tmp/wrench.zip" | sha256sum -c - && \
    unzip /tmp/wrench.zip -d /tmp/wrench_extract && \
    mv /tmp/wrench_extract/wrench_2026-10-05-7638b99_linux-glibc2.39-0ubuntu8.9 /opt/wrench && \
    rm -rf /tmp/wrench.zip /tmp/wrench_extract && \
    chmod +x /opt/wrench

# ── Python dependencies ───────────────────────────────────────────────────────

WORKDIR /ProjectRYNO

COPY requirements.txt .

RUN pip3 install --no-cache-dir --break-system-packages -r requirements.txt

# Start directly in the native Linux build shell.
CMD ["/bin/bash"]
