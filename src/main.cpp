#include <graphicsEngine.h>
#include <ui.h>


int main(int argc, char **argv) {
    /**
     * Example using the CLI
     */
    auto *cli = new CommandLineInterface();
    cli->main_loop();

    /**
     * hardcoded example without
     */
    auto *gr = new GraphicsEngine();
    gr->createEnvironment("firstEnv");
    gr->setRenderer(RAYTRACER);

    return 0;
}
