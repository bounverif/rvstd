FROM ubuntu:22.04

ARG BOOST_VERSION=1.82.0

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

RUN git clone --depth 1 --branch v3.3.2 https://github.com/catchorg/Catch2.git /tmp/catch2 \
  && cmake -S/tmp/catch2 -B/tmp/catch2/build \
  -DBUILD_TESTING=OFF \
  -DCATCH_INSTALL_DOCS=OFF \
  && cmake --build /tmp/catch2/build/ --target install -j$(nproc) \
  && rm -rf /tmp/catch2


