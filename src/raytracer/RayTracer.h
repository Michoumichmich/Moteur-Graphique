/**
 * @file RayTracer.h
 */

#ifndef GRAPHIC_ENGINE_RAYTRACER_H
#define GRAPHIC_ENGINE_RAYTRACER_H

#include <environment.h>
#include <utils.h>
#include "../engine/Renderer.h"
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

class RayTracer : public Renderer {
 private:
  Environment *environment{};
  struct rayTracerConfig config;
  RT_RayEnvIntersector *envIntersector;
 public:
  explicit RayTracer(Environment *, OutputPictureManager *);
  RayTracer(Environment *, OutputPictureManager *pic, struct rayTracerConfig);
  void renderScene() override;
};

#endif //GRAPHIC_ENGINE_RAYTRACER_H
