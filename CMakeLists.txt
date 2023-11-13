cmake_minimum_required(VERSION 3.24)
project(mouse)

set(CMAKE_CXX_STANDARD 17)
add_executable(mouse main.cpp event.cpp event.h)
target_link_libraries(mouse PRIVATE ws2_32)
