FROM ubuntu:24.04

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    graphviz \
    libboost-graph-dev \
    make \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /work

CMD ["bash"]
