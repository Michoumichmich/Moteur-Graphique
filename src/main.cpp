/**
 * DEBUG can be set with -D DEBUG, it's used to produce a more verbose code like a lot so
 * reduce the size of the image else it's going to be really slow
 * DEBUG can't be used with OPENMP
 * -DBENCHMARK computes a few time the same picture and and the avg time of exec
 * NB : the tesselation does not happen every time
 */


#include "samples.hpp"
#include <graphicsEngine.h>
#include <ui.h>
#include <iostream>

int main(int argc, char **argv) {
    /**
     * Uncomment one of the next items to render a scene
     */

//    teapot_scene("../misc/teapot.ply");
//    illuminati_scene();
//    night_scene();


    /**
     * Example using the CLI
     */
    CommandLineInterface cli;
    cli.main_loop();

    exit(0);
}
