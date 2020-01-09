cmake_minimum_required(VERSION 3.15)
project(exam)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

add_executable(exam main.cpp)
target_include_directories(exam PUBLIC
        optional/
        safeQueue/
        safeStack/
        smartPointers/
        guards/
        algorithms/
        containers/
)
