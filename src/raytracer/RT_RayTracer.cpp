#include "RT_RayTracer.h"
#include <iostream>
#include <utils.h>
#include "RT_Ray.h"
#include "RT_RayCaster.h"

RT_RayTracer::RT_RayTracer() {
    def_ray_conf.bouncesLeft = MAX_BOUNCES;
    def_ray_conf.rtMode = RT_RayRenderMode::RT_DEPTHMAP;
    def_ray_conf.reflexions = true;
    def_ray_conf.refractions = false;
    def_ray_conf.depthOfField = false;
    def_ray_conf.diffusivity = false;
    def_ray_conf.transparency = false;
}

RT_RayTracer::RT_RayTracer(struct RT_RayConfig conf)
        : def_ray_conf(conf) {
}

/**
 * Main function of the Ray tracer
 * @param out_file
 */
void RT_RayTracer::renderScene(std::string out_file, Environment *environment) {
    this->env = environment;
    def_ray_conf.env = env;
    ray_out_manager = new RT_OutputManager(def_ray_conf, env->currCam()->pxWidthCount(), env->currCam()->pxHeightCount());
    envIntersector = new RT_RayEnvIntersector(env);
    def_ray_conf.cam_view_center = env->currCam()->getCamViewCenter();
    auto primaryRays = RT_RayCaster::generateFirstRays(def_ray_conf, env->currCam(), 128);
#ifdef _OPENMP
#ifdef DEBUG // DEBUG AND OPENMP special case needed to share std::cout
#warning "THAT'S STUPID, DON'T MIX DEBUG PRINTFSs AND OPENMP!"
#pragma omp parallel default(none) shared(envIntersector, ray_out_manager, primaryRays, std::cout)
#else
#pragma omp parallel default(none) shared(envIntersector, ray_out_manager, primaryRays)
#endif
#endif
    for (auto &pool : primaryRays) {
#ifdef _OPENMP
#pragma omp single nowait
#endif
        for (auto &aRay : pool) {
#ifdef DEBUG // Regardless of openmp we print the coordinates
            std::cout << aRay->x << ' ' << aRay->y << std::endl;
#endif
            aRay.RT_ComputePrimaryRay(envIntersector, ray_out_manager);
        }
    }
    ray_out_manager->apply_global_operations();
    ray_out_manager->export_picture(out_file);
    delete envIntersector;
    delete ray_out_manager;
}

void RT_RayTracer::setMode(RT_RayRenderMode mode) {
    def_ray_conf.rtMode = mode;
}

void RT_RayTracer::setMaxBounces(int max) {
    def_ray_conf.bouncesLeft = max;
}

void RT_RayTracer::enableReflexions() {
    def_ray_conf.reflexions = true;
}

void RT_RayTracer::enableDiffusivity() {
    def_ray_conf.diffusivity = true;
}

void RT_RayTracer::enableRefractions() {
    def_ray_conf.refractions = true;
}

void RT_RayTracer::enableTransparency() {
    def_ray_conf.transparency = true;
}

void RT_RayTracer::enableDepthOfField() {
    def_ray_conf.depthOfField = true;
}

void RT_RayTracer::disableDiffusivity() {
    def_ray_conf.diffusivity = false;
}

void RT_RayTracer::disableReflexions() {
    def_ray_conf.reflexions = false;
}

void RT_RayTracer::disableTransparency() {
    def_ray_conf.transparency = false;
}

void RT_RayTracer::disableRefractions() {
    def_ray_conf.refractions = false;
}

void RT_RayTracer::disableDepthOfField() {
    def_ray_conf.depthOfField = false;
}
