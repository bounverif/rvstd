# Follow commands below to build and run the container
#
# > docker build . -t ghcr.io/bounverif/cppdevel:latest
# > docker run -it --rm -v $(PWD):/workspaces/cppdevel bounverif/cppdevel
#
FROM debian:12

ARG CATCH_VERSION=3.5.3

ENV PIP_BREAK_SYSTEM_PACKAGES 1
ENV CMAKE_GENERATOR=Ninja

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
  && apt-get -y install \
    sudo \
    git \
    pre-commit \
    build-essential \
    tar curl wget zip unzip gnupg2 \
    cmake \
    ninja-build \
    python3 \
    python3-pip \
    python-is-python3 \
    ansible-core \
  && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/*

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
  && apt-get -y install \
    clang \
    clangd \
    clang-format \
    clang-tidy \
    clang-tools \
    googletest \
    google-mock \
    cppcheck \
    shellcheck \
    valgrind \
  && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/*

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
  && apt-get -y install \
    libcapstone-dev \
    libprotobuf-dev \
    libre2-dev \
    zlib1g-dev \
  && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/*

RUN git clone --depth 1 --branch v${CATCH_VERSION} https://github.com/catchorg/Catch2.git /tmp/catch2 \
  && cmake -S/tmp/catch2 -B/tmp/catch2/build \
    -DBUILD_TESTING=OFF \
    -DCATCH_INSTALL_DOCS=OFF \
  && cmake --build /tmp/catch2/build/ --target install -j$(nproc) \
  && rm -rf /tmp/catch2

RUN git clone --depth 1 --recursive https://github.com/google/bloaty.git /tmp/bloaty \
  && cmake -S/tmp/bloaty -B/tmp/bloaty/build \
    -DBUILD_TESTING=OFF \
    -DCATCH_INSTALL_DOCS=OFF \
  && cmake --build /tmp/bloaty/build/ --target install -j$(nproc) \
  && rm -rf /tmp/bloaty
