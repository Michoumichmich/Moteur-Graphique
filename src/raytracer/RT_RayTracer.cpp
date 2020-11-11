#include "RT_RayTracer.h"
#include <iostream>
#include <utils.h>
#include "RT_Ray.h"
#include "RT_RayCaster.h"

#ifdef _OPENMP

#include <omp.h>

#endif

RT_RayTracer::RT_RayTracer(OutputPictureManager *pic) {
    this->picManager = pic;
    this->ray_out_manager = new RT_OutputManager(this->config);
}

RT_RayTracer::RT_RayTracer(OutputPictureManager *pic, struct RT_RayConfig conf) : config(conf) {
    this->picManager = pic;
    this->ray_out_manager = new RT_OutputManager(conf);
}

RT_RayTracer::~RT_RayTracer() {
    delete envIntersector;
    delete picManager;
}

/**
 * Main function of the Ray tracer
 * @param string
 */
void RT_RayTracer::renderScene(std::string string, Environment *env) {
    this->environment = env;
    this->envIntersector = new RT_RayEnvIntersector(env);
    this->config.cam_view_center = environment->getCurrentCam()->getCamViewCenter();
    std::list<RT_Ray> primaryRays = RT_RayCaster::generateFirstRays(config, environment->getCurrentCam());
    std::list<RT_Ray>::iterator aRay;
    picManager->setOutFile(string);

#ifdef _OPENMP
#ifdef DEBUG // DEBUG AND OPENMP special case needed to share std::cout
#warning "THAT'S STUPID, DON'T MIX DEBUG PRINTFSs AND OPENMP!"
#pragma omp parallel default(none) private(aRay) shared(envIntersector, picManager, primaryRays, std::cout)
#else
#pragma omp parallel default(none) private(aRay) shared(envIntersector, ray_out_manager, primaryRays)
#endif
#endif
    for (aRay = primaryRays.begin(); aRay != primaryRays.end(); aRay++) {
#ifdef DEBUG // Regardless of openmp we print the coordinates
        std::cout << aRay->x << ' ' << aRay->y << std::endl;
#endif
#ifdef _OPENMP
#pragma omp single nowait
#endif
        aRay->RT_ComputePrimaryRay(envIntersector, ray_out_manager);
    }
    ray_out_manager->apply_global_transformations();
    ray_out_manager->export_picture(picManager);
}
