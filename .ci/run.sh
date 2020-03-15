#!/bin/bash

set -eux

# pull submodule
git submodule update --init

# download dataset
FILE_ID=${FILEID}
FILE_NAME=dataset.zip
curl -sc /tmp/cookie "https://drive.google.com/uc?export=download&id=${FILE_ID}" > /dev/null
CODE="$(awk '/_warning_/ {print $NF}' /tmp/cookie)"
curl -Lb /tmp/cookie "https://drive.google.com/uc?export=download&confirm=${CODE}&id=${FILE_ID}" -o ${FILE_NAME}
unzip -o dataset.zip -d data

# build
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)

# run example
./examples/example --dir ../data -d
