#!/bin/bash

# g++ -E -std=c++11 main.cc -I../../include -o main.E
g++ -std=c++11 main.cc -I../../include -lpthread -o main
