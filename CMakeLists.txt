cmake_minimum_required(VERSION 3.5)

add_library(Flags INTERFACE)
target_compile_options(Flags INTERFACE
    -Wall
    -Werror
    # -Wpedantic
    -march=native
    -std=c++17
    )

add_library(Catch2 INTERFACE)
target_include_directories(Catch2 INTERFACE third_party)

add_executable(unittests
    src/unit_test_main.cpp
    src/test_factorial.cpp
    src/pair_sum.cpp
    src/zero_sum.cpp
    )
target_link_libraries(unittests PUBLIC
    Flags
    Catch2
    )
