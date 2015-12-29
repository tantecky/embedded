#!/bin/sh
set -eu

make tests
cd tests 
./tests
