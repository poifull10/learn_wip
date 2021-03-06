#!/bin/bash

set -eux

# pull submodule
git submodule update --init

# build
mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make -j$(nproc)
