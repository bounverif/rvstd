ARG RVSTD_BASE_IMAGE=docker.io/library/debian
ARG RVSTD_BASE_IMAGE_VERSION=12
ARG RVSTD_IMAGE_NAME=localhost/rvstd
ARG RVSTD_VERSION=latest

FROM ${RVSTD_BASE_IMAGE}:${RVSTD_BASE_IMAGE_VERSION} AS rvstd-builder
ARG TARGETARCH TARGETOS TARGETPLATFORM TARGETVARIANT

ARG BOOST_VERSION=1.87.0
ARG CATCH_VERSION=3.8.0
ARG PEGTL_VERSION=3.2.8

ENV PIP_BREAK_SYSTEM_PACKAGES=1
ENV CMAKE_GENERATOR=Ninja

# hadolint ignore=DL3008
RUN --mount=type=cache,target=/var/cache/apt,sharing=locked,id=${TARGETPLATFORM}/var/cache/apt \
    export DEBIAN_FRONTEND=noninteractive && \
    apt-get update -qq && \
    apt-get install -qy --no-install-recommends \
      sudo \
      git \
      pre-commit \
      build-essential \
      tar curl wget zip unzip gnupg2 \
      cmake \
      ninja-build \
      python3-minimal \
      python3-pip \
      python-is-python3 \
      ansible-core \
    && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/*

# hadolint ignore=DL3008
RUN --mount=type=cache,target=/var/cache/apt,sharing=locked,id=${TARGETPLATFORM}/var/cache/apt \
    export DEBIAN_FRONTEND=noninteractive && \
    apt-get update -qq && \
    apt-get install -qy --no-install-recommends \
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
      zlib1g-dev \
    && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/*

RUN git clone --depth 1 --branch v${CATCH_VERSION} "https://github.com/catchorg/Catch2.git" /tmp/catch2 \
    && cmake -S/tmp/catch2 -B/tmp/catch2/build \
      -DBUILD_TESTING=OFF \
      -DCATCH_INSTALL_DOCS=OFF \
    && cmake --build /tmp/catch2/build/ --target install -j$(nproc) \
    && rm -rf /tmp/catch2

RUN git clone --depth 1 --recursive "https://github.com/google/bloaty.git" /tmp/bloaty
RUN cmake -S/tmp/bloaty -B/tmp/bloaty/build \
      -DBUILD_TESTING=OFF \
      -DCATCH_INSTALL_DOCS=OFF \
    && cmake --build /tmp/bloaty/build/ --target install -j$(nproc) \
    && rm -rf /tmp/bloaty

RUN git clone -j$(nproc) --recursive --depth 1 --branch boost-${BOOST_VERSION} "https://github.com/boostorg/boost.git" /tmp/boost \
  && cd /tmp/boost \
  && ./bootstrap.sh --prefix=/usr/local --without-libraries=python \
  && ./b2 -j$(nproc) install \
  && cd / && rm -rf /tmp/boost

  RUN --mount=type=cache,target=/var/cache/apt,sharing=locked,id=${TARGETPLATFORM}/var/cache/apt \
      export DEBIAN_FRONTEND=noninteractive && \
      apt-get update -qq && \
      apt-get install -qy --no-install-recommends \
        libcapstone-dev \
        libprotobuf-dev \
        libre2-dev \
        zlib1g-dev \
      && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/*

RUN git clone --depth 1 --branch ${PEGTL_VERSION} https://github.com/taocpp/PEGTL.git /tmp/pegtl \
    && mkdir -p /tmp/pegtl/build && cd /tmp/pegtl/build \
    && cmake -S/tmp/pegtl -B/tmp/pegtl/build \
        -DPEGTL_BUILD_TESTS=OFF \
        -DPEGTL_BUILD_EXAMPLES=OFF \
        -DPEGTL_INSTALL_CMAKE_DIR=/usr/local/lib/cmake/pegtl \
    && cmake --build /tmp/pegtl/build/ --target install -j$(nproc) \
    && rm -rf /tmp/pegtl

FROM ${RVSTD_IMAGE_NAME}:${RVSTD_VERSION}-builder AS rvstd-devel
ARG TARGETARCH TARGETOS TARGETPLATFORM TARGETVARIANT

ARG USER=bounverif
ARG USER_GROUP=${USER}
ARG USER_UID=1000
ARG USER_GID=${USER_UID}

# Add a container user (good practice)
RUN groupadd ${USER_GROUP} -g ${USER_GID} \
    && useradd -ms /bin/bash ${USER} -g ${USER_GID} -u ${USER_UID} \
    && printf "${USER}:${USER}" | chpasswd \
    && printf "${USER} ALL= NOPASSWD: ALL\\n" >> /etc/sudoers

USER ${USER}

RUN python -m pip install --user gcovr pybind11

ENV PATH "/home/${USER}/.local/bin:${PATH}"
