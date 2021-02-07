#/usr/bin/bash

$CXX -fPIC -std=c++17 -shared -o DemoModule.so DemoModule.cpp -I../include
