#include <graphicsEngine.h>
#include <ui.h>
#include <chrono>
#include <iostream>

int main(int argc, char **argv) {
    /**
     * Example using the CLI
     */
    auto *cli = new CommandLineInterface();
    cli->main_loop();
    delete cli;

    /**
     * hardcoded example without the CLI
     */
    auto *gr = new GraphicsEngine();
    gr->createEnvironment("firstEnv");
    OutputPictureManager * pm = new OutputPictureManager;
    pm->setColorMapper(new ColorMapper(COLORING_MODE, 1, 1.8));
    RT_RayTracer *renderer = new RT_RayTracer(gr->getCurrentEnvironment(), pm);
    gr->setRenderer(renderer);
    auto start = std::chrono::high_resolution_clock::now();
    gr->launchRender("test.bmp");
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout <<"temps " << duration.count()/1000000.0 << std::endl;

    return 0;
}
