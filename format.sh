#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

rm -rf .format
mkdir -p .format
cd .format
cmake ../source
make VERBOSE=1 format
cd ..
git checkout source/grammar/*
