cmake_minimum_required(VERSION 3.13)
project(3D_Renderer CXX)
set(CMAKE_CXX_STANDARD 11)


set(COMPILE_OPTIONS PRIVATE -v -flto=full -Wall -Wextra -O3)

find_package(MPI REQUIRED) #make it REQUIRED, if you want
include_directories(SYSTEM ${MPI_INCLUDE_PATH})
add_executable(demo business_card_demo.cpp)
target_link_libraries(demo ${MPI_CXX_LIBRARIES})


