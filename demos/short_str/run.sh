#!/bin/bash

# [1]
cmake . -B build
cmake --build build
cmake --build build --target test # run test code

# [2] g++ compile
# $(pkg-config --cflags gtest) 插入了 Google Test 的编译标志。
# $(pkg-config --libs gtest) 插入了 Google Test 的链接标志。
# -pthread 用于支持多线程，通常与 Google Test 一起使用。
# g++ -std=c++11 -I../../include $(pkg-config --cflags gtest) main.cc $(pkg-config --libs gtest) -o main
