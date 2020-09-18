#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

rm -rf .tidy
mkdir -p .tidy
cd .tidy
export CXX=clang++-10
export CC=clang-10
export CLANG_TIDY="clang-tidy-10"
cmake ../source
make VERBOSE=1 sources
