cmake_minimum_required(VERSION 3.14)
project(ThreadedLab6)

set(CMAKE_CXX_STANDARD 17)

# Подключение Google Test
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

# Основной проект
add_executable(Lab6 main.cpp utils.cpp)

# Тесты
add_executable(RunTests tests/logic_tests.cpp utils.cpp)
target_link_libraries(RunTests PRIVATE gtest gtest_main pthread)