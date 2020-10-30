#!/bin/bash
git submodule update --init ../External/src/freetype
mkdir -p ../build/freetype
cd  ../build/freetype
cmake -G "MinGW Makefiles" -DCMAKE_INSTALL_PREFIX=../../External ../../External/src/freetype
make install