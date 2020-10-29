cmake_minimum_required(VERSION 3.13)
project(main CXX)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -Wno-unused -mavx2 ")

add_executable(exec main.cpp Vector.cpp Vector.h)
