#!/bin/bash
git submodule update --init ../External/src/glfw
mkdir -p ../External/build/glfw
cd ../External/build/glfw
cmake -DCMAKE_INSTALL_PREFIX=../../ ../../src/glfw
cmake --build . --config debug --target install

