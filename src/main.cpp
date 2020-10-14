#include <graphicsEngine.h>
#include <ui.h>

int main(int argc, char **argv) {
    /**
     * Example using the CLI
     */
    auto *cli = new CommandLineInterface();
    //cli->main_loop();
    delete cli;

    /**
     * hardcoded example without the CLI
     */
    auto *gr = new GraphicsEngine();
    gr->createEnvironment("firstEnv");
    RT_RayTracer *renderer = new RT_RayTracer(gr->getCurrentEnvironment(), gr->getPicManager());
    gr->setRenderer(renderer);

    delete gr;
    delete renderer;

    Vector v = Vector(0, 0, 0);
    Vector prod = Vector::crossProduct(v, v);


    return 0;
}
