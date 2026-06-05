# =============================================================================
# Stage 1: Build Wrench
# =============================================================================

FROM debian:12 AS wrench-builder

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        ca-certificates \
        git \
        cmake \
        build-essential \
        pkg-config \
        python3 \
        zlib1g-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /build

RUN git clone --recursive https://github.com/chaoticgd/wrench.git

WORKDIR /build/wrench

RUN cmake -B build \
    -DCMAKE_BUILD_TYPE=Release \
    -DGLFW_BUILD_WAYLAND=OFF \
    -DGLFW_BUILD_X11=OFF

# RUN cmake --build build -j$(nproc)
RUN cmake --build build --target wrenchbuild -j$(nproc)

# =============================================================================
# Stage 2: Runtime image
# =============================================================================

FROM debian:12-slim

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
    && rm -rf /var/lib/apt/lists/*

# ── Install Wrench ────────────────────────────────────────────────────────────

RUN mkdir -p /opt/wrench

COPY --from=wrench-builder \
    /build/wrench/build/wrenchbuild \
    /opt/wrench/wrenchbuild

RUN chmod +x /opt/wrench/wrenchbuild

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