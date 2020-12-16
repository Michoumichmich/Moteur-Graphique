cmake_minimum_required(VERSION 3.13)
project(GraphicsEngine CXX)
set(CMAKE_CXX_STANDARD 20)


set(ARCH_FLAGS "-Wall -Wextra -Winit-self -Wuninitialized -Wmissing-declarations -ansi -Woverloaded-virtual -march=native -mtune=native")

set(CMAKE_CXX_FLAGS_RELEASE "${ARCH_FLAGS} -Wno-unused -fopenmp -O2 -flto -s -DBENCHMARK")
set(CMAKE_CXX_FLAGS "${ARCH_FLAGS}")
set(CMAKE_CXX_FLAGS_BENCHMARK "${ARCH_FLAGS} -fopenmp -Ofast -DBENCHMARK")


include_directories(src/include)
add_executable(main src/main.cpp src/include/config.h src/utils/Vector.cpp
        src/utils/Vector.h src/raytracer/RT_RayTracer.cpp src/raytracer/RT_RayTracer.h src/environment/Environment.cpp src/environment/Environment.h
        src/environment/Camera.cpp src/environment/Camera.h src/environment/Tessel.cpp src/environment/Tessel.h src/environment/Object.cpp
        src/environment/Object.h src/include/environment.h src/include/raytracer.h src/raytracer/RT_RayCaster.cpp src/raytracer/RT_RayCaster.h
        src/userInterface/CommandLineInterface.cpp src/userInterface/CommandLineInterface.h src/userInterface/GraphicalUserInterface.cpp
        src/userInterface/GraphicalUserInterface.h src/include/utils.h src/utils/Color.cpp
        src/utils/Color.h src/environment/ApparenceProperties.cpp src/environment/ApparenceProperties.h src/include/ui.h src/engine/GraphicsEngine.cpp
        src/engine/GraphicsEngine.h src/engine/Abstract_Renderer.h src/utils/OutputPictureManager.cpp src/utils/OutputPictureManager.h src/include/graphicsEngine.h src/engine/Abstract_Renderer.cpp
        src/environment/RegularObjects/Sphere.cpp src/environment/RegularObjects/Sphere.h src/raytracer/RT_Ray.cpp src/raytracer/RT_Ray.h
        src/raytracer/RT_RayEnvIntersector.cpp src/raytracer/RT_RayEnvIntersector.h src/environment/MappedTexture.cpp src/environment/MappedTexture.h
        src/environment/CoordinatesHandler.cpp src/environment/CoordinatesHandler.h src/environment/RegularObjects/Cube.cpp src/environment/RegularObjects/Cube.h
        src/utils/ColorMapper.cpp src/utils/ColorMapper.h src/raytracer/RT_OutputManager.cpp src/raytracer/RT_OutputManager.h src/raytracer/RT_Commons.h
        src/raytracer/RT_Physics.cpp src/raytracer/RT_Physics.h src/environment/Light.cpp src/environment/Light.h src/utils/Chrono.hpp
        src/utils/Serializable.cpp src/utils/Serializable.h src/code_bits.hpp)


if (CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_CONFIGURATION_TYPES Debug Release BENCHMARK)
endif ()

MARK_AS_ADVANCED(
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_BENCHMARK)