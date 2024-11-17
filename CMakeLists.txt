cmake_minimum_required (VERSION 3.11)

project (ciarcpp)

add_compile_options (-Wall -Wextra -Wpedantic -O3)

SET (CMAKE_CXX_STANDARD 20)
SET (CMAKE_CXX_STANDARD_REQUIRED ON)

include (FetchContent)

add_subdirectory (src)
add_subdirectory (tests)