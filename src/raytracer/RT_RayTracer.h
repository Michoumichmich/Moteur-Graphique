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
  RT_RayEnvIntersector *envIntersector{};
    RT_OutputManager *ray_out_manager;
 public:
  explicit RT_RayTracer(OutputPictureManager *);

  RT_RayTracer(OutputPictureManager *pic, struct RT_RayConfig);

  void renderScene(std::string string, Environment *env) override;

  ~RT_RayTracer() override;
};

#endif //GRAPHIC_ENGINE_RAYTRACER_H
