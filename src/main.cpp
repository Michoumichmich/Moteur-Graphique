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

    /**
     * Test intersection
     */
    Vector dir = Vector(0, 11, 11);
    Vector orig = Vector(0, 0, 1.1);
    Environment *env = gr->getCurrentEnvironment();
    Sphere *sph = new Sphere(1.0);
    env->addObject(sph);
    sph->Tesselate();

    RT_RayEnvIntersector intersector = RT_RayEnvIntersector(env);
    struct RT_RayIntersectionResult res = intersector.RT_RayFindIntersection(orig, dir);

    OutputPictureManager pm = OutputPictureManager();
    pm.savePicture();
    delete gr;
    delete renderer;


    /**
     * Test rotation
     */
    double x = 1;
    double y = 0;
    CoordinatesHandler::rotate(x, y, 45);
    std::cout << x << ' ' << y << std::endl;

    return 0;
}
