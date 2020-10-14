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
    Vector dir = Vector(0, 0, 1);
    Vector orig = Vector(0, 0, 0);
    Vector tes0 = Vector(-1, -1, 1);
    Vector tes1 = Vector(1, -1, 1);
    Vector tes2 = Vector(0, 1, 1);
    Tessel tessel = Tessel();
    tessel.summmits[0] = tes0;
    tessel.summmits[1] = tes1;
    tessel.summmits[2] = tes2;
    double distance;
    Vector * out = new Vector();
    RT_RayEnvIntersector::checkForSingleIntersection(orig, dir, tessel, out, &distance );


    return 0;
}
