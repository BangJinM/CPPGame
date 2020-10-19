#!/bin/bash
git submodule update --init ../External/src/crossguid
mkdir -p ../build/crossguid
cd  ../build/crossguid
cmake -G "MinGW Makefiles" -DCMAKE_INSTALL_PREFIX=../../External ../../External/src/crossguid
make install

