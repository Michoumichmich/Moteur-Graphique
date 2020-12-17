#ifndef GRAPHICSENGINE_CODE_BITS_HPP
#define GRAPHICSENGINE_CODE_BITS_HPP

#include <graphicsEngine.h>
#include <memory>

static inline std::shared_ptr<Cube> cube_generator() {

    double size = ((double) rand() / (double) RAND_MAX) * 0.05 + 0.09;

    double cube_light = (double) rand() / (double) RAND_MAX;

    auto cube = std::make_shared<Cube>(size);
    struct transformations transfo;
    transfo.rotX = rand() % 90;
    transfo.rotY = rand() % 45;
    transfo.rotZ = rand() % 45;
    double rand1 = (double) rand() / (double) RAND_MAX;
    double rand2 = (double) rand() / (double) RAND_MAX;
    double rand3 = (double) rand() / (double) RAND_MAX;
    transfo.pt = Vector(-4 + rand1 * 8, -4 + rand2 * 8, -4 + rand3 * 8);
    cube->setTransformation(transfo);
    cube->setColor(Color(rand() % 256, rand() % 256, rand() % 256));
    cube->setLightIntensity(.01);
    cube->setReflexivity(0.8);
    return cube;
}

static void inline default_test() {
    /**
     * hardcoded example without the CLI
     */
    std::unique_ptr<GraphicsEngine> gr = std::make_unique<GraphicsEngine>();
    gr->createEnvironment("firstEnv");

    std::shared_ptr<Cube> cube_center = std::make_shared<Cube>(1);
    cube_center->setColor(Color(200, 200, 200));
    cube_center->setLightIntensity(0.99);
    cube_center->setReflexivity(0);
    //  cube_center->setTransformation({0.5, 0, 20, 45, Vector(-1.2, 0.25, -0.25)})->setColor(Color(138, 26, 70));
    gr->addObjInEnv(cube_center);

    std::shared_ptr<Cube> cube_left = std::make_shared<Cube>(1);
    cube_left->setReflexivity(0.51);
    cube_left->setLightIntensity(0);
    cube_left->setTransformation({0.5, 0, 20, 45, Vector(-1.2, 0.25, -0.25)})->setColor(Color(138, 26, 70));
    gr->addObjInEnv((cube_left));

    std::shared_ptr<Cube> cube_right = std::make_shared<Cube>(1);
    cube_right->setReflexivity(0.8)->setColor(Color(0, 85, 108));
    cube_right->setLightIntensity(0);
    cube_right->setTransformation({0.5, 0, 20, 45, Vector(1.2, 0.25, -0.25)});
    gr->addObjInEnv(cube_right);

    std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(1 / 1.42);
    sphere->setLightIntensity(0);
    sphere->setColor(Color(0.2, 0.0, 0.5));
    sphere->setReflexivity(0.8);
    gr->addObjInEnv(sphere);

    for (int i = 0; i < 450; i++) gr->addObjInEnv(cube_generator());

    auto plane = std::make_shared<Plane>(30, 30);
    plane->setColor(Color(0));
    plane->setTransformation({1, -25, 0, 0, Vector(0, 0, -1)});
    gr->addObjInEnv(plane);

    auto plane_top = std::make_shared<Plane>(30, 30);
    plane_top->setColor(Color(1));
    plane_top->setTransformation({1, -25, 0, 0, Vector(0, 10, 10)});
    gr->addObjInEnv(plane_top);


    auto raytracer = new RT_RayTracer();
    raytracer->setMode(RT_RayRenderMode::RT_STANDARD);
    raytracer->setMaxBounces(6);
    gr->setRenderer(raytracer);

    std::shared_ptr<Camera> cam = std::make_shared<Camera>("Face");
    cam->setMode(PERSPECTIVE);
    cam->setResolution(8000, 4000);
    cam->setDownSamplingFactor(3);
    cam->setViewDimensions(10, 5);
    cam->setDirection(Point3D(0.01, 5.01, -2.01), Point3D(0, 0, 0));

    gr->currEnv()->addCamera(cam);
    gr->currEnv()->setResolution(30);

    gr->currEnv()->setHazeIntensity(0.4);
    gr->currEnv()->setBackgroundAppearence(true); // HERE

    gr->currEnv()->switchCamera("Face");
    gr->currEnv()->print_objects(std::cout);
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
}

#endif //GRAPHICSENGINE_CODE_BITS_HPP
