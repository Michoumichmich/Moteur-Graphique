/**
 * @file RayTracer.h
 */

#ifndef GRAPHIC_ENGINE_RAYTRACER_H
#define GRAPHIC_ENGINE_RAYTRACER_H

#include <environment.h>
#include <utils.h>
#include "../engine/Abstract_Renderer.h"
#include "RT_RayEnvIntersector.h"

enum rayTracerRenderMode {
    BITMAP,
    DEPTHMAP,
    STANDARD,
};

struct rayTracerConfig {
    bool reflexions = false;
    bool refractions = false;
    bool transparency = false;
    bool diffusivity = false;
    bool depthOfField = false;
    enum rayTracerRenderMode rtMode = BITMAP;
    unsigned int maxRayBounce = 0;

};

class RT_RayTracer : public Abstract_Renderer {
private:
    Environment *environment{};
    struct rayTracerConfig config;
    RT_RayEnvIntersector *envIntersector;
public:
    explicit RT_RayTracer(Environment *, OutputPictureManager *);

    RT_RayTracer(Environment *, OutputPictureManager *pic, struct rayTracerConfig);

    void renderScene() override;

    ~RT_RayTracer();
};

#endif //GRAPHIC_ENGINE_RAYTRACER_H
