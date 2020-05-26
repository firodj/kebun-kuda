cmake_minimum_required(VERSION 3.1)
project(kebun_kuda)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)
set(UNICORN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/unicorn)

if (KEBUNKUDA_UNICORN)
  add_subdirectory(unicorn)
  add_subdirectory(multiple_hook_mem_unaligned)
endif ()

if (KEBUNKUDA_KEYSTONE)
  add_subdirectory(keystone)
endif ()

if (KEBUNKUDA_CAPSTONE)
  add_subdirectory(capstone)
endif ()
