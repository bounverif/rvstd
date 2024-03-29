# Follow commands below to build and run the container
#
# > docker build . -t ghcr.io/bounverif/rvstd:latest
# > docker run -it --rm -v $(PWD):/workspaces/rvstd bounverif/rvstd
FROM ubuntu:22.04

ARG BOOST_VERSION=1.84.0
ARG CATCH_VERSION=3.5.3

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
  && apt-get -y install \
    sudo \
    git \
    build-essential \
    tar curl wget zip unzip gnupg2 \
    cmake \
    ninja-build \
    python3-all-dev \
    python3-pip \
    python-is-python3 \
  && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/*

RUN git clone -j$(nproc) --recursive --depth 1 --branch boost-${BOOST_VERSION} https://github.com/boostorg/boost.git /tmp/boost \
  && cd /tmp/boost \
  && ./bootstrap.sh --prefix=/usr/local --without-libraries=python \
  && ./b2 -j$(nproc) install \
  && cd / && rm -rf /tmp/boost

RUN git clone --depth 1 --branch v${CATCH_VERSION} https://github.com/catchorg/Catch2.git /tmp/catch2 \
  && cmake -S/tmp/catch2 -B/tmp/catch2/build \
    -DBUILD_TESTING=OFF \
    -DCATCH_INSTALL_DOCS=OFF \
  && cmake --build /tmp/catch2/build/ --target install -j$(nproc) \
  && rm -rf /tmp/catch2

RUN git clone --depth 1 --branch 3.2.7 https://github.com/taocpp/PEGTL.git /tmp/pegtl \
  && mkdir -p /tmp/pegtl/build && cd /tmp/pegtl/build \
  && cmake -S/tmp/pegtl -B/tmp/pegtl/build \
    -DPEGTL_BUILD_TESTS=OFF \
    -DPEGTL_BUILD_EXAMPLES=OFF \
    -DPEGTL_INSTALL_CMAKE_DIR=/usr/local/lib/cmake/pegtl \
  && cmake --build /tmp/pegtl/build/ --target install -j$(nproc) \
  && rm -rf /tmp/pegtl

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
  && apt-get -y install \
    clang \
    clangd \
    clang-format \
    clang-tidy \
    clang-tools \
    shellcheck \
  && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/*

# Add a container user (good practice)
RUN groupadd work -g 1000 \
  && useradd -ms /bin/bash bounverif -g 1000 -u 1000 \
  && printf "bounverif:bounverif" | chpasswd \
  && printf "bounverif ALL= NOPASSWD: ALL\\n" >> /etc/sudoers

USER bounverif

RUN python -m pip install --user \
  pre-commit \
  cmakelang[YAML] \
  gcovr \
  pybind11

ENV PATH "/home/bounverif/.local/bin:${PATH}"
