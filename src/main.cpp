/**
 * DEBUG can be set with -D DEBUG, it's used to produce a more verbose code
 * DEBUG can't be used with OPENMP
 * CHRONO is obvious I guess...
 */


#include <graphicsEngine.h>
#include <ui.h>
#include <iostream>

#ifdef CHRONO

#include <chrono>

#endif

int main(int argc, char **argv)
{
  /**
   * Example using the CLI
   */
    auto *cli = new CommandLineInterface();
    //cli->main_loop();
    delete cli;

    /**
     * hardcoded example without the CLI
     */
    GraphicsEngine *gr = new GraphicsEngine();
    gr->createEnvironment("firstEnv");
    gr->addObjInEnv(new Sphere(1 / 1.42));
    gr->addObjInEnv(new Cube(1));

    OutputPictureManager *pm = new OutputPictureManager;
    pm->setColorMapper(new ColorMapper(LINEAR, 2, 3));
    RT_RayTracer *renderer = new RT_RayTracer(pm);
    gr->setRenderer(renderer);

#ifdef CHRONO
  auto start = std::chrono::high_resolution_clock::now();
#endif
  gr->launchRender("test.bmp");
#ifdef CHRONO
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "temps " << duration.count() / 1000000.0 << std::endl;
#endif
  return 0;
}
