#!/bin/bash

rm -rf build &&
mkdir build &&
cd build &&
cmake -DCMAKE_BUILD_TYPE=Release .. &&
make -j$(nproc) &&
cd .. &&
rm -rf libmaze &&
mkdir libmaze &&
cp build/libmaze.so libmaze/ &&
mkdir -p libmaze/include/maze &&
cp -r src/* libmaze/include/maze/ &&
find libmaze/include/maze -name "*.cpp" -type f -delete &&
echo "Done. Result in 'libmaze/'."
