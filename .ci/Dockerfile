FROM ubuntu:bionic

ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
  build-essential \
  cmake \
  ninja-build \
  git \
  libssl-dev \
  ca-certificates

RUN mkdir /build && cd /build && git clone https://github.com/opencv/opencv.git && \
  cd opencv && mkdir build && cd build && cmake .. -GNinja && \
  ninja && ninja install

RUN apt-get install -y --no-install-recommends \
  libboost-all-dev libeigen3-dev gcc-8 g++-8 \
  git-lfs ssh

ENV CC /usr/bin/gcc-8

ENV CXX /usr/bin/g++-8

