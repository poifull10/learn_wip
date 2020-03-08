#!/bin/bash

set -eux

# pull submodule
git submodule update --init

# download dataset
FILE_ID="1M5rIQc8CLvZrrSPa7SQ0T0ID2oVFA-1j"
FILE_NAME=dataset.zip
curl -sc /tmp/cookie "https://drive.google.com/uc?export=download&id=${FILE_ID}" > /dev/null
CODE="$(awk '/_warning_/ {print $NF}' /tmp/cookie)"
curl -Lb /tmp/cookie "https://drive.google.com/uc?export=download&confirm=${CODE}&id=${FILE_ID}" -o ${FILE_NAME}
unzip dataset.zip

# build
mkdir build
cd build
cmake ..
make -j$(nproc)

# test
./tests/tester

