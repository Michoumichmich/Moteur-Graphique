#ifndef GRAPHIC_ENGINE_RAYTRACER_H
#define GRAPHIC_ENGINE_RAYTRACER_H

#include <environment.h>
#include <utils.h>

#include <Renderer.h>

class RayTracer : Renderer {
private:
    Environment environment;
public:
    explicit RayTracer(Environment);
};

#endif //GRAPHIC_ENGINE_RAYTRACER_H
