#!/bin/bash
git submodule update --init ../External/src/glm
mkdir -p ../build/glm
cd  ../build/glm
cmake -G "MinGW Makefiles" -DCMAKE_INSTALL_PREFIX=../../External ../../External/src/glm
make install

