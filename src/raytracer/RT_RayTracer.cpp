#include "RT_RayTracer.h"
#include <iostream>
#include <utils.h>
#include "RT_Ray.h"
#include "RT_RayCaster.h"

RT_RayTracer::RT_RayTracer()
{
    default_ray.bouncesLeft = MAX_BOUNCES;
    default_ray.rtMode = RT_RayRenderMode::RT_DEPTHMAP;
    default_ray.reflexions = true;
    default_ray.refractions = false;
    default_ray.depthOfField = false;
    default_ray.diffusivity = false;
    default_ray.transparency = false;
}

RT_RayTracer::RT_RayTracer(struct RT_RayConfig conf)
        :default_ray(conf)
{
}

/**
 * Main function of the Ray tracer
 * @param out_file
 */
void RT_RayTracer::renderScene(std::string out_file, Environment* environment)
{
    this->env = environment;
    default_ray.env = env;
    ray_out_manager = new RT_OutputManager(default_ray, env->currCam()->pxWidthCount(), env->currCam()->pxHeightCount());
    envIntersector = new RT_RayEnvIntersector(env);
    default_ray.cam_view_center = env->currCam()->getCamViewCenter();
    std::list<RT_Ray> primaryRays = RT_RayCaster::generateFirstRays(default_ray, env->currCam());
#ifdef _OPENMP
#ifdef DEBUG // DEBUG AND OPENMP special case needed to share std::cout
#warning "THAT'S STUPID, DON'T MIX DEBUG PRINTFSs AND OPENMP!"
#pragma omp parallel default(none) shared(envIntersector, ray_out_manager, primaryRays, std::cout)
#else
#pragma omp parallel default(none) shared(envIntersector, ray_out_manager, primaryRays)
#endif
#endif
    for (auto & primaryRay : primaryRays) {
#ifdef DEBUG // Regardless of openmp we print the coordinates
        std::cout << aRay->x << ' ' << aRay->y << std::endl;
#endif
#ifdef _OPENMP
#pragma omp single nowait
#endif
        primaryRay.RT_ComputePrimaryRay(envIntersector, ray_out_manager);
    }
    ray_out_manager->apply_global_operations();
    ray_out_manager->export_picture(out_file);
    delete envIntersector;
    delete ray_out_manager;
}

void RT_RayTracer::setMode(RT_RayRenderMode mode)
{
    default_ray.rtMode = mode;
}

void RT_RayTracer::setMaxBounces(int max)
{
    default_ray.bouncesLeft = max;
}

void RT_RayTracer::enableReflexions()
{
    default_ray.reflexions = true;
}

void RT_RayTracer::enableDiffusivity()
{
    default_ray.diffusivity = true;
}

void RT_RayTracer::enableRefractions()
{
    default_ray.refractions = true;
}

void RT_RayTracer::enableTransparency()
{
    default_ray.transparency = true;
}

void RT_RayTracer::enableDepthOfField()
{
    default_ray.depthOfField = true;
}

void RT_RayTracer::disableDiffusivity()
{
    default_ray.diffusivity = false;
}

void RT_RayTracer::disableReflexions()
{
    default_ray.reflexions = false;
}

void RT_RayTracer::disableTransparency()
{
    default_ray.transparency = false;
}

void RT_RayTracer::disableRefractions()
{
    default_ray.refractions = false;
}

void RT_RayTracer::disableDepthOfField()
{
    default_ray.depthOfField = false;
}
