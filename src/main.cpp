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
#include "code_bits.hpp"

int main(int argc, char** argv)
{
    /**
     * Example using the CLI
     */
    CommandLineInterface cli;
    cli.main_loop();


 /*   std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(1/1.42);
    sphere->setLightIntensity(1);
    sphere->setColor(Color(0.2, 0.0, 0.5));
    sphere->setReflexivity(0.40);
    auto obj = std::shared_ptr<Object>(dynamic_cast<Object*>(sphere.get()));
    std::cout << *obj << std::endl;*/


//    default_test();

    exit(0);
}
