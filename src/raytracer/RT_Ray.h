/**
 * Here's going to be the core challenge of the raytracer, computing the rays.
 * @file RT_Ray.h
 */

#ifndef _RT_RAY_H_
#define _RT_RAY_H_

#include <environment.h>
#include "RT_RayEnvIntersector.h"
#include "RT_OutputManager.h"
#include "RT_Commons.h"

/**
 * @class RT_Ray
 * Contains everything to create and compute a ray.
 */
class RT_Ray {
private:
    Vector dir;
    Vector origin;
    RT_RayConfig ray_conf;

    std::list<std::shared_ptr<RT_Ray>> RT_PrepareRays(RT_IntersectorResult result);

    static Color RT_ComputePreparedRays(const std::list<std::shared_ptr<RT_Ray>>& rays, RT_RayEnvIntersector* intersector);

public :
    /**
     * Will be used to generate the secondary rays
     */
    RT_Ray(Vector direction, Point3D origin, struct RT_RayConfig config);

    /**
     * Should be used for the first rays only. The ray needs to hold the data on where it should be displayed as
     * the rays are not computed at the same time they're launched
     * @param x smaller that the width
     * @param y smaller than the height
     */
    RT_Ray(Vector direction, Point3D origin, struct RT_RayConfig config, unsigned x, unsigned y);

    /**
     * Recursively computes a ray.
     * First it looks for the closest tessel in the env that's on its path
     * Then it computes all reflections/refractions
     * It launches the rays and decrements the bounces counter in the new rays -> the recursion must end at some point
     * If the ray hits a light object, it returns its color
     * When a ray goes through an tessel, we must not forget to take in account the object's color
     * La fonction est une procédure ce qui permettra de la lancer en parallèle sans s'embêter avec la valeur de retour. Elle enverra son résultat au PictureManager.
     */
    void RT_ComputePrimaryRay(RT_RayEnvIntersector*, RT_OutputManager*);

    struct RT_RayOutput RT_ComputeRay(RT_RayEnvIntersector* intersector);

/**
     * When the ray is casted we can find where the color goes in the picture
     */
    const unsigned int x = 0;
    const unsigned int y = 0;
};

#endif //_RT_RAY_H_
