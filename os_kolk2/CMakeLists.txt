cmake_minimum_required(VERSION 3.10)
project(ModernSingleton)

set(CMAKE_CXX_STANDARD 17)

# Основная библиотека
add_library(SingletonCore 
    include/Singleton.h
    include/CreationPolicies.h
    include/LifetimePolicies.h
    include/ThreadingPolicies.h
)

# Пример использования
add_executable(SingletonExample src/example.cpp)
target_link_libraries(SingletonExample SingletonCore)

# Тесты (если нужно)
enable_testing()
add_executable(SingletonTests test/SingletonTest.cpp)
target_link_libraries(SingletonTests SingletonCore)
add_test(NAME SingletonTests COMMAND SingletonTests)
