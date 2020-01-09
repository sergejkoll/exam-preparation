cmake_minimum_required(VERSION 3.15)
project(03_ALP_practice)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++14 -pthread")

find_package(Threads REQUIRED)

add_executable(${CMAKE_PROJECT_NAME} main.cpp)
target_include_directories(${CMAKE_PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC -pthread)
