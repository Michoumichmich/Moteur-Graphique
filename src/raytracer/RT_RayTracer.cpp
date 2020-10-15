#include "RT_RayTracer.h"

#include <utils.h>
#include "RT_Ray.h"
#include "RT_RayCaster.h"

#include <iostream>

RT_RayTracer::RT_RayTracer(Environment *env, OutputPictureManager *pic) {
    this->picManager = pic;
    this->environment = env;
    this->envIntersector = new RT_RayEnvIntersector(env);
}

RT_RayTracer::RT_RayTracer(Environment *env, OutputPictureManager *pic, struct RT_RayConfig conf) : config(conf) {
    this->envIntersector = new RT_RayEnvIntersector(env);
    this->picManager = pic;
    this->environment = env;
}

RT_RayTracer::~RT_RayTracer() {
    delete envIntersector;
    delete picManager;
}

/**
 * Main function of the Ray tracer
 * @param string
 */
void RT_RayTracer::renderScene(const std::string string) {
    std::list<RT_Ray> primaryRays = RT_RayCaster::generateFirstRays(config, environment->getCurrentCam());

    this->picManager = new OutputPictureManager(string); //TODO SHOUDLNT BE THERE
    picManager->setColorMapper(new ColorMapper(LINEAR, 1, 1.8)); //TODO SHOUDLNT BE THERE

    std::list<RT_Ray>::iterator aRay;
    for (aRay = primaryRays.begin(); aRay != primaryRays.end(); aRay++) {
        /**
         * Here some multithreading could be useful
         */
        std::cout << aRay->x << ' ' << aRay->y << std::endl;
        aRay->RT_ComputePrimaryRay(envIntersector, picManager);
    }
    picManager->savePicture();
}
