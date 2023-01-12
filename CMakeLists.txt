cmake_minimum_required(VERSION 3.21)
project(Heap_Allocate_CPP)

set(CMAKE_CXX_STANDARD 23)

include_directories(./include ./extern)
add_executable(Heap_Allocate_CPP main.cpp src/realtime_heap_allocate.cpp include/first_layer_index.hpp)