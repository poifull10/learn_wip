FROM ubuntu:disco

LABEL "name"="learn_wip" \
  "maintainer"="poifull10 <poifull10@gmail.com>" \
  "com.github.actions.icon"="code" \
  "com.github.actions.color"="green-dark" \
  "com.github.actions.name"="cpp"

ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
  build-essential cmake ninja-build git \
  libssl-dev ca-certificates curl unzip \
  libboost-all-dev libeigen3-dev gcc-8 g++-8

RUN mkdir /build && cd /build && git clone https://github.com/opencv/opencv.git && \
  cd opencv && mkdir build && cd build && cmake .. -GNinja && \
  ninja && ninja install

ENV CC /usr/bin/gcc-8

ENV CXX /usr/bin/g++-8

