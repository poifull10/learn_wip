#!/bin/bash

set -eux

# pull submodule
git submodule update --init

# build
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
