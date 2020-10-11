cmake_minimum_required(VERSION 3.13)
project(Graphic_Engine CXX)
set(CMAKE_CXX_STANDARD 11)


set(COMPILE_OPTIONS PRIVATE -v -flto=full -Wall -Wextra)


#find_package(MPI) #make it REQUIRED, if you want
#include_directories(SYSTEM ${MPI_INCLUDE_PATH})
include_directories(src/include)
add_executable(main src/main.cpp src/include/config.h src/utils/Vector.cpp
        src/utils/Vector.h src/raytracer/RayTracer.cpp src/raytracer/RayTracer.h src/environment/Environment.cpp src/environment/Environment.h
        src/environment/Camera.cpp src/environment/Camera.h src/environment/Tessel.cpp src/environment/Tessel.h src/environment/Object.cpp
        src/environment/Object.h src/include/environment.h src/include/raytracer.h src/raytracer/RayCaster.cpp src/raytracer/RayCaster.h
        src/userInterface/CommandLineInterface.cpp src/userInterface/CommandLineInterface.h src/userInterface/GraphicalUserInterface.cpp
        src/userInterface/GraphicalUserInterface.h src/utils/Point3D.cpp src/utils/Point3D.h src/include/utils.h src/utils/Color.cpp
        src/utils/Color.h src/environment/ApparenceProperties.cpp src/environment/ApparenceProperties.h src/include/ui.h src/engine/GraphicEngine.cpp
        src/engine/GraphicEngine.h src/include/Renderer.h src/utils/OutputPictureManager.cpp src/utils/OutputPictureManager.h)
#target_link_libraries(main ${MPI_CXX_LIBRARIES})


