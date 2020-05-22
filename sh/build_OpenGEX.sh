#!/bin/bash
git submodule update --init ../External/src/OpenGEX
mkdir -p ../External/build/OpenGEX
cd ../External/build/OpenGEX
cmake -DCMAKE_INSTALL_PREFIX=../../ ../../src/OpenGEX
cmake --build . --config debug --target install

