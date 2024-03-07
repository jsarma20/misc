cmake_minimum_required(VERSION 3.2)
project(Server VERSION 1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SRC 
    ${CMAKE_CURRENT_SOURCE_DIR}/server.cpp
)

set(THREAD_POOL_INCLUDE_DIR

    ${CMAKE_CURRENT_SOURCE_DIR}/../thread-pool/
)

set(LOGGER_INCLUDE_DIR

    ${CMAKE_CURRENT_SOURCE_DIR}/../SimpleLogger/
)

add_subdirectory(/Users/janas/work/GitHub/cpp-mini-projects/SimpleLogger loggerbin)

add_executable(Server test.cpp ${SRC})
include_directories(${THREAD_POOL_INCLUDE_DIR} ${LOGGER_INCLUDE_DIR})
target_link_libraries(Server PUBLIC SimpleLogger)

