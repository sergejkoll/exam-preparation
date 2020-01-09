cmake_minimum_required(VERSION 3.10.2)
project(03_ALP_practice)

set(CMAKE_CXX_STANDARD 17)

find_package(Threads REQUIRED)

add_executable(${CMAKE_PROJECT_NAME} main.cpp)
target_include_directories(${CMAKE_PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/
)