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

    /**
     * Test intersection
     */
    Vector dir = Vector(0, 0, -1);
    Vector orig = Vector(0, 0, 2.5);
    Environment * env = gr->getCurrentEnvironment();
    RT_RayEnvIntersector intersector = RT_RayEnvIntersector(env);
    struct RT_RayIntersectionResult res = intersector.RT_RayFindIntersection(orig, dir);

    return 0;
}
