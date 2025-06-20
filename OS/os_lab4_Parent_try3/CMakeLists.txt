cmake_minimum_required(VERSION 3.14)
project(ProcessSyncLab)

set(CMAKE_CXX_STANDARD 17)

# Подключение Google Test
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

# Исполняемые файлы
add_executable(Parent Parent.cpp utils.cpp)
add_executable(Child Child.cpp utils.cpp)

# Тесты
add_executable(RunTests tests/logic_tests.cpp utils.cpp)
target_link_libraries(RunTests PRIVATE gtest gtest_main pthread)