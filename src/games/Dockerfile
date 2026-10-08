# The named context is supplied by docker-compose.yml from the sibling CLI checkout.
FROM mcr.microsoft.com/dotnet/sdk:10.0 AS cli-build
WORKDIR /src
COPY --from=ratchet_cli global.json ./
COPY --from=ratchet_cli src ./src
RUN dotnet publish src/RatchetPs2.Cli/RatchetPs2.Cli.csproj \
    -c Release -r linux-x64 --self-contained true -o /cli

FROM debian:13-slim
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        make curl ca-certificates unzip g++ python3 python3-pip python-is-python3 \
        binutils-mips-linux-gnu libicu76 libssl3t64 zlib1g \
    && rm -rf /var/lib/apt/lists/*
COPY --from=cli-build /cli /opt/ratchet-ps2
ENV PATH="/opt/ratchet-ps2:${PATH}"
WORKDIR /ProjectRYNO
COPY requirements.txt .
RUN pip3 install --no-cache-dir --break-system-packages -r requirements.txt
CMD ["/bin/bash"]
