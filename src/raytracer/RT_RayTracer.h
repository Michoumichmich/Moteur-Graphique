/**
 * @file RayTracer.h
 */

#ifndef GRAPHIC_ENGINE_RAYTRACER_H
#define GRAPHIC_ENGINE_RAYTRACER_H

#include <environment.h>
#include <utils.h>
#include "../engine/Abstract_Renderer.h"
#include "RT_RayEnvIntersector.h"
#include "RT_Ray.h"


class RT_RayTracer : public Abstract_Renderer {
private:
    Environment *environment{};
    struct RT_RayConfig config;
    RT_RayEnvIntersector *envIntersector;
public:
    explicit RT_RayTracer(Environment *, OutputPictureManager *);

    RT_RayTracer(Environment *, OutputPictureManager *pic, struct RT_RayConfig);

    void renderScene(std::string string) override;

    ~RT_RayTracer();
};

#endif //GRAPHIC_ENGINE_RAYTRACER_H
