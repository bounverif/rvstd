# Follow commands below to build and run the container
#
# > docker build . -t bounverif/rvstd:latest
# > docker run -it --rm -v $(PWD):/workspaces/rvstd bounverif/rvstd

FROM ghcr.io/bounverif/boostdev:1.82.0

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
