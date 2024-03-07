cmake_minimum_required(VERSION 3.2)
project(ThreadPool VERSION 1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Example example.cpp)

find_package(Catch2 3 REQUIRED)

add_executable(Test test.cpp)
target_link_libraries(Test PRIVATE Catch2::Catch2WithMain)


