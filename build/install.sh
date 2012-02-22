#!/bin/bash

cmake ..
mkdir bin
make
mv bin/* ../bin/
rmdir bin

rm CMakeCache.txt cmake_install.cmake Makefile
rm -r CMakeFiles
