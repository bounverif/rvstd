# Follow commands below to build and run the container
#
# > docker build . -t ghcr.io/bounverif/cppdevel:latest
# > docker run -it --rm -v $(PWD):/workspaces/cppdevel bounverif/cppdevel
#
FROM bounverif/cppdevel:latest

ARG BOOST_VERSION=1.84.0

RUN git clone -j$(nproc) --recursive --depth 1 --branch boost-${BOOST_VERSION} https://github.com/boostorg/boost.git /tmp/boost \
  && cd /tmp/boost \
  && ./bootstrap.sh --prefix=/usr/local --without-libraries=python \
  && ./b2 -j$(nproc) install \
  && cd / && rm -rf /tmp/boost
