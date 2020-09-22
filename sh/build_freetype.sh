#!/bin/bash
git submodule update --init ../External/src/freetype
cp -f -R ../External/src/freetype/include ../External/Windows/
cp -f -R ../External/src/freetype/win32/freetype.lib ../External/Windows/lib

