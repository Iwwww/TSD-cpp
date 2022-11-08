#!/bin/sh

g++ test.cpp MyNumber.cpp -o test.out $1 &&
    ./test.out
