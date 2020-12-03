#ifndef GRAPHICSENGINE_CUBES_GENERATOR_H
#define GRAPHICSENGINE_CUBES_GENERATOR_H

#include <graphicsEngine.h>
#include <memory>
#include <stdlib.h>

static inline std::shared_ptr<Cube> cube_generator()
{

    double size = ((double)rand()/(double)RAND_MAX)*0.05 +0.09;

    double cube_light = (double)rand()/(double)RAND_MAX;

    auto cube = std::make_shared<Cube>(size);
    struct transformations transfo;
    transfo.rotX = rand()%90;
    transfo.rotY = rand()%45;
    transfo.rotZ = rand()%45;
    double rand1 = (double) rand()/(double) RAND_MAX;
    double rand2 = (double) rand()/(double) RAND_MAX;
    double rand3 = (double) rand()/(double) RAND_MAX;
    transfo.pt = Vector(-4+rand1*8, -2+rand2*4, -2+rand3*4);
    cube->setTransformation(transfo);
    cube->setColor(Color(rand()%256, rand()%256, rand()%256));
    cube->setLightIntensity(1);
    cube->setReflexivity(0.3);
    return cube;
}

#endif //GRAPHICSENGINE_CUBES_GENERATOR_H
