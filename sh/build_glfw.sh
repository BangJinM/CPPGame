#!/bin/bash
git submodule update --init ../External/src/glfw
mkdir -p ../build/glfw
cd  ../build/glfw
cmake -G "MinGW Makefiles" -DCMAKE_INSTALL_PREFIX=../../External ../../External/src/glfw
make install

