cmake_minimum_required(VERSION 3.1)
project(multiple_hook_mem_unaligned)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)

# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/../cmake/")
# find_package(Unicorn REQUIRED)

include_directories(SYSTEM
  ${UNICORN_DIR}/include
)

add_executable(test
  test.cpp
)

target_link_libraries(test
  unicorn_static
)

target_compile_definitions(test PUBLIC  -D_CRT_SECURE_NO_WARNINGS)
