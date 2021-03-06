cmake_minimum_required(VERSION 3.13)
project(GraphicsEngine CXX)
set(CMAKE_CXX_STANDARD 20)

set(DEF_FLAGS "-Wall -Wextra -Winit-self -march=native -mtune=native -msse4.1 -Wno-unused")
set(EXTRA_FLAGS "-Wuninitialized -Wmissing-declarations -Wno-unused -pedantic -Woverloaded-virtual -Werror")

set(PROF_USE "-fprofile-use -Wno-coverage-mismatch -Wno-missing-profile -Wno-error=coverage-mismatch -fprofile-correction ")#-fprofile-partial-training")
set(PROF_GEN "-fprofile-generate")

set(RUNTIME_CHECKS "-fsanitize=undefined -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=address -D_GLIBCXX_ASSERTIONS -D_FORTIFY_SOURCE=2 -Werror ")


set(CMAKE_CXX_FLAGS_RELEASE "${DEF_FLAGS} -Ofast -flto -fopenmp ${PROF_USE} -DBENCHMARK ")
set(CMAKE_CXX_FLAGS_DEBUG "${DEF_FLAGS} ${EXTRA_FLAGS} ${RUNTIME_CHECKS}")
#set(CMAKE_CXX_FLAGS_BENCHMARK "${ARCH_FLAGS} -fopenmp -Ofast -DBENCHMARK")


include_directories(src/include)
add_executable(main src/main.cpp src/include/config.h src/utils/Vector.cpp
        src/utils/Vector.h src/raytracer/RT_RayTracer.cpp src/raytracer/RT_RayTracer.h src/environment/Environment.cpp src/environment/Environment.h
        src/environment/Camera.cpp src/environment/Camera.h src/environment/Tessel.cpp src/environment/Tessel.h src/environment/Object.cpp
        src/environment/Object.h src/include/environment.h src/include/raytracer.h src/raytracer/RT_RayCaster.cpp src/raytracer/RT_RayCaster.h
        src/userInterface/CommandLineInterface.cpp src/userInterface/CommandLineInterface.h src/userInterface/GraphicalUserInterface.cpp
        src/userInterface/GraphicalUserInterface.h src/include/utils.h src/utils/Color.cpp
        src/environment/Meshes/PlyObjectMesh.cpp src/environment/Meshes/PlyObjectMesh.h
        src/utils/Color.h src/environment/ApparenceProperties.cpp src/environment/ApparenceProperties.h src/include/ui.h src/engine/GraphicsEngine.cpp
        src/engine/GraphicsEngine.h src/engine/Abstract_Renderer.h src/utils/io/OutputPictureManager.cpp src/utils/io/OutputPictureManager.h
        src/include/graphicsEngine.h src/engine/Abstract_Renderer.cpp
        src/environment/RegularObjects/Sphere.cpp src/environment/RegularObjects/Sphere.h src/raytracer/RT_Ray.cpp src/raytracer/RT_Ray.h
        src/raytracer/RT_RayEnvIntersector.cpp src/raytracer/RT_RayEnvIntersector.h src/environment/MappedTexture.cpp src/environment/MappedTexture.h
        src/environment/CoordinatesHandler.cpp src/environment/CoordinatesHandler.h src/environment/RegularObjects/Cube.cpp src/environment/RegularObjects/Cube.h
        src/utils/ColorMapper.cpp src/utils/ColorMapper.h src/raytracer/RT_OutputManager.cpp src/raytracer/RT_OutputManager.h src/raytracer/RT_Commons.h
        src/raytracer/RT_Physics.cpp src/raytracer/RT_Physics.h src/environment/Light.cpp src/environment/Light.h src/utils/Chrono.hpp
        src/utils/Serializable.cpp src/utils/Serializable.h src/samples.hpp src/environment/RegularObjects/Plane.cpp src/environment/RegularObjects/Plane.h
        src/environment/RegularObjects/Pyramid.cpp src/environment/RegularObjects/Pyramid.h src/environment/Meshes/UglySphere.cpp
        src/environment/Meshes/UglySphere.h src/environment/Meshes/MeshObject.cpp src/environment/Meshes/MeshObject.h src/environment/Animated.cpp
        src/environment/Animated.h src/utils/io/PlyParser.hpp src/environment/RegularObjects/PlyObject.cpp src/environment/RegularObjects/PlyObject.h)


if (CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_CONFIGURATION_TYPES Debug Release BENCHMARK)
endif ()

MARK_AS_ADVANCED(
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_BENCHMARK)