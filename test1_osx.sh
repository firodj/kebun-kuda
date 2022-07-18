#!/bin/bash

mkdir build
cd build

cmake -DKEBUNKUDA_UNICORN=1 ..
cmake --build . --target multiple_hook_mem_unaligned -- -j4

./multiple_hook_mem_unaligned