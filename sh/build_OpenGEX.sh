#!/bin/bash
git submodule update --init ../External/src/OpenGEX
mkdir -p ../build/OpenGEX
cd  ../build/OpenGEX
cmake -G "MinGW Makefiles" -DCMAKE_INSTALL_PREFIX=../../External ../../External/src/OpenGEX
make install

