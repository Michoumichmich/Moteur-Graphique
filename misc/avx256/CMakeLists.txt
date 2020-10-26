cmake_minimum_required(VERSION 3.13)
project(GraphicsEngine CXX)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_RELEASE "-Wall -Wextra -Wno-unused -flto -O3 -ffast-math -fopenmp -DCHRONO -mavx2")
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -Wno-unused -Og -g3 -DCHRONO -DDEBUG -mavx2 ")

include_directories(src/include)
add_executable(main main.c Vector.c Vector.h)