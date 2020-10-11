#ifndef GRAPHIC_ENGINE_RENDERER_H
#define GRAPHIC_ENGINE_RENDERER_H

#include <raytracer.h>


enum renderer_type {
    RAYTRACER = 0
};

class Renderer {
private:
    enum renderer_type type;
    RayTracer *rayTracer = new RayTracer;
public:
    Renderer();

    Renderer(enum renderer_type);

};




#endif //GRAPHIC_ENGINE_RENDERER_H
