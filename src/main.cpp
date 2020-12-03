/**
 * DEBUG can be set with -D DEBUG, it's used to produce a more verbose code like a lot so
 * reduce the size of the image else it's going to be really slow
 * DEBUG can't be used with OPENMP
 * -DBENCHMARK computes a few time the same picture and and the avg time of exec
 * NB : the tesselation does not happen every time
 */


#include <graphicsEngine.h>
#include <ui.h>
#include <iostream>
#include <memory>

#ifdef BENCHMARK

#include <chrono>

#endif

int main(int argc, char **argv) {
    /**
     * Example using the CLI
     */
    auto cli = std::make_unique<CommandLineInterface>();
    //cli->main_loop();

    /**
     * hardcoded example without the CLI
     */
    std::unique_ptr<GraphicsEngine> gr = std::make_unique<GraphicsEngine>();
    gr->createEnvironment("firstEnv");

    std::shared_ptr<Cube> cube_center = std::make_shared<Cube>(1);
    cube_center->setColor(Color(255, 255, 255));
    cube_center->setLightIntensity(1);
    cube_center->setReflexivity(0.9);


    std::shared_ptr<Cube> cube_left = std::make_shared<Cube>(1);
    std::shared_ptr<Cube> cube_right = std::make_shared<Cube>(1);
    cube_left->setReflexivity(1);
    cube_right->setReflexivity(0.9)->setColor(Color(0, 85, 108));
    cube_left->setLightIntensity(1);
    cube_right->setTransformation({0.5, 20, 45, 0, Vector(-1.2, 0.25, -0.25)});
    cube_left->setTransformation({0.5, 0, 20, 45, Vector(1.2, 0.25, -0.25)})->setColor(Color(138, 26, 70));

    std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(1/1.42);
    sphere->setLightIntensity(0.2);
    sphere->setColor(Color(0.2, 0.0, 0.5));
    sphere->setReflexivity(0.2);

    gr->addObjInEnv(cube_left);
    gr->addObjInEnv(cube_center);
    gr->addObjInEnv(cube_right);
    gr->addObjInEnv(sphere);
    gr->currEnv()->setResolution(10);

    auto raytracer = new RT_RayTracer();
    raytracer->setMode(RT_RayRenderMode::RT_STANDARD);
    raytracer->setMaxBounces(2);
    gr->setRenderer(raytracer);

    auto cam = std::make_shared<Camera>("Face");
    cam->setMode(PERSPECTIVE);
    cam->setResolution(4001, 2001);
    cam->setViewDimensions(4, 2);
    cam->setDirection(Point3D(0.01, 5.01, -2.01), Point3D(0, 0, 0));
    gr->currEnv()->addCamera(cam);
    gr->currEnv()->switchCamera("Face");
    gr->launchRender("test_face.bmp");

    gr->currEnv()->switchCamera("Default");
 //   gr->launchRender("test_default.bmp");

//#ifdef BENCHMARK
//    int lap_count = 1;
//    double avg = 0;
//    for (int i = 0; i < lap_count; i++) {
//        auto start = std::chrono::high_resolution_clock::now();
//#endif
//        gr->launchRender("test.bmp");
//#ifdef BENCHMARK
//        auto end = std::chrono::high_resolution_clock::now();
//        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//        std::cout << "time " << duration.count() / 1000000.0 << "s" << std::endl;
//        avg += duration.count();
//    }
//    std::cout << "avg time " << avg / (1000000.0 * lap_count) << "s" << std::endl;
//#endif
//
//    std::stringstream ss;
//    gr->serialize(ss);
//    std::cout << ss.str() << std::endl;

    exit(0);
}
