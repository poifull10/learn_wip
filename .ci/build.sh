#!/bin/bash

set -eux

# pull submodule
git submodule update --init

# build
mkdir build
cd build
cmake ..
make -j$(nproc)
