#ifndef _GRAPHIC_ENGINE_PHYSICS_H
#define _GRAPHIC_ENGINE_PHYSICS_H

#include "utils.h"
#include "environment.h"
#include "raytracer.h"

class RT_Physics {
public:
    /**
     * Computes light intensity for given point in space
     * @param p world coordinates for the position
     * @param n normal vector of the surface where the point is
     * @param incomingRay vector with the direction with wich the ray hits the surface on point p
     * @param ambientIntensity vector with light intensity of ambient space in RGB components
     * @param lights list of light sources present in the scene
     * @return vector with RGB components of the light intensity in given space position
     * @remark formula explained here http://rodolphe-vaillant.fr/?e=85
     */
    static Vector
    computePhongIllumination(Vector p, Vector n, Vector incomingRay, Vector ambientIntensity, std::list<Light> lights, ApparenceProperties properties);
};


#endif //_GRAPHIC_ENGINE_PHYSICS_H
