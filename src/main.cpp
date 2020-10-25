#include <graphicsEngine.h>
#include <ui.h>

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
    gr->launchRender("test.bmp");
    delete gr;
    delete renderer;


    return 0;
}
