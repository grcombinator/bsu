cmake_minimum_required(VERSION 3.14)
project(SortingApp)

set(CMAKE_CXX_STANDARD 17)

# Добавляем Google Test
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_executable(
    Parent 
    Parent.cpp
)

add_executable(
    Child 
    Child.cpp
)

add_executable(
    runTests 
    tests/quicksort_test.cpp
)

target_link_libraries(runTests PRIVATE gtest gtest_main pthread)