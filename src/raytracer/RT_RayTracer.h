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
    Environment* env{};
    struct RT_RayConfig default_ray;
    RT_RayEnvIntersector* envIntersector{};
    RT_OutputManager* ray_out_manager{};
public:
    explicit RT_RayTracer();

    explicit RT_RayTracer(struct RT_RayConfig);

    void renderScene(std::string out_file, Environment* environment) override;

    void setMode(RT_RayRenderMode mode);

    void setMaxBounces(int max);

    void enableReflexions() override;

    void enableRefractions();

    void enableDiffusivity();

    void enableTransparency();

    void enableDepthOfField();

    void disableReflexions() override;

    void disableRefractions();

    void disableDiffusivity();

    void disableTransparency();

    void disableDepthOfField();
};

#endif //GRAPHIC_ENGINE_RAYTRACER_H
