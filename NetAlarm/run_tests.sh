#!/bin/sh
set -eu

make tests
cd tests 
LD_LIBRARY_PATH=../build ./tests
