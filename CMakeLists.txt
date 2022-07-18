cmake_minimum_required(VERSION 3.1)

# Workaround to fix wrong compiler on macos. (for Unicorn)
if ((APPLE) AND (NOT CMAKE_C_COMPILER))
    set(CMAKE_C_COMPILER "/usr/bin/cc")
endif()

project(kebun_kuda C)

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
