/**
 * Here's going to be the core challenge of the raytracer, computing the rays.
 * @file RT_Ray.h
 */

#ifndef _RT_RAY_H_
#define _RT_RAY_H_

#include <environment.h>
#include "RT_RayEnvIntersector.h"

struct RT_RayOutput {
    Color resultColor;

    /**
     * The distance between the ray and the first tessel it touched. If the ray goes to infinity we return -1
     * It's going to be useful to compute the bitmap and deph map, furthermore it can be used to create volumetric effet
     * it applying some filter depending on the distance between the camera and the ray for the primary rays
     * For the others, we can still apply some kind of ray extinction
     */
    double distance;
    double rayIntensity;
};

class RT_Ray {
private:
    Vector dir;
    Vector origin;
    unsigned int bouncesLeftCounter;
    double rayIntensity;

    struct RT_RayOutput RT_ComputeDescendingRay(Vector, Vector, unsigned int, RT_RayEnvIntersector *);

public :
    RT_Ray(Vector, Point3D, unsigned int);

    /**
     * Recursively computes a ray.
     * First it looks for the closest tessel in the env that's on its path
     * Then it computes all reflections/refractions
     * It launches the rays and decrements the bounces counter in the new rays -> the recursion must end at some point
     * If the ray hits a light object, it returns its color
     * When a ray goes through an tessel, we must not forget to take in account the object's color
     * La fonction est une procédure ce qui permettra de la lancer en parallèle sans s'embêter avec la valeur de retour. Elle enverra son résultat au PictureManager.
     */
    void RT_ComputePrimaryRay(RT_RayEnvIntersector *, OutputPictureManager *);

    /**
     * When the ray is casted we can find where the color goes in the picture
     */
    const unsigned int x = 0;
    const unsigned int y = 0;
};

#endif //_RT_RAY_H_
