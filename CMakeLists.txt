cmake_minimum_required (VERSION 3.11.0)

# Compiler
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER g++)

# Project name
set(this_project tradingbot)

project(${this_project} CXX)

set(sources
    src/Algo.cpp
    src/AlgoOrders.cpp
)

include_directories ( include )

add_executable(${this_project} src/Main.cpp ${sources} ${headers})


# Tests
set(UNIT_TEST tests)
add_executable( tests tests/UnitTests.cpp ${sources} )


