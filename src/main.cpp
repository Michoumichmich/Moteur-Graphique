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

#ifdef BENCHMARK

#include <chrono>

#endif

int main(int argc, char **argv)
{
  /**
   * Example using the CLI
   */
    auto *cli = new CommandLineInterface();
    cli->main_loop();
    delete cli;

  /**
   * hardcoded example without the CLI
   */
//  GraphicsEngine *gr = new GraphicsEngine();
//  gr->createEnvironment("firstEnv");
//
//  Cube *cube_center = new Cube(1);
//  Cube *cube_left = new Cube(1);
//  Cube *cube_right = new Cube(1);
//  cube_right->setTransformation({0.5, 0, 45, 0, Vector(-1.2, 0.25, -0.25)});
//  cube_left->setTransformation({0.5, 0, 0, 45, Vector(1.2, 0.25, -0.25)})->setColor(Color(138, 26, 70, 255));
//  gr->addObjInEnv(cube_left);
//  gr->addObjInEnv(cube_center);
//  gr->addObjInEnv(cube_right->setColor(Color(0, 85, 108, 255)));
//  gr->addObjInEnv(new Sphere(1 / 1.42));
//
//  gr->getCurrentEnvironment()->setResolution(30);
//  RT_RayTracer *renderer = new RT_RayTracer();
//  gr->setRenderer(renderer);
//
//#ifdef BENCHMARK
//  int lap_count = 1;
//  double avg = 0;
//  for (int i = 0; i < lap_count; i++)
//    {
//      auto start = std::chrono::high_resolution_clock::now();
//#endif
//    gr->launchRender("test.bmp");
//#ifdef BENCHMARK
//    auto end = std::chrono::high_resolution_clock::now();
//    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//    std::cout << "time " << duration.count() / 1000000.0 << "s" << std::endl;
//    avg += duration.count();
//}
//  std::cout << "avg time " << avg / (1000000.0 * lap_count) << "s" << std::endl;
//#endif

//    std::stringstream ss;
//    gr->serialize(ss);
//    std::cout << ss.str() << std::endl;
//    delete gr;
//
//
//    auto *sph = new Sphere(1);
//    sph->serialize(std::cout);


    return 0;
}
