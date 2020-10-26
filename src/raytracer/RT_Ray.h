/**
 * Here's going to be the core challenge of the raytracer, computing the rays.
 * @file RT_Ray.h
 */

#ifndef _RT_RAY_H_
#define _RT_RAY_H_

#include <environment.h>
#include "RT_RayEnvIntersector.h"

/**
 * Used to define the type of rendering.
 */
enum class RT_RayRenderingMode {
  RT_BITMAP,
  RT_DEPTHMAP,
  RT_STANDARD,
};

/**
 * The configuration of the renderer and the ray
 * //TODO split the global renderer config and the ray's one to avoid duplicating data
 */
struct RT_RayConfig {
    bool reflexions = false;
    bool refractions = false;
    bool transparency = false;
    bool diffusivity = false;
    bool depthOfField = false;
    RT_RayRenderingMode rtMode = RT_RayRenderingMode::RT_DEPTHMAP;
    unsigned int bouncesLeft = MAX_BOUNCES;
    double intensity = 1;
};

/**
 * Data outputed by the ray launched by the cam.
 * The distance between the ray and the first tessel it touched. If the ray goes to infinity we return -1
 * It's going to be useful to compute the bitmap and deph map, furthermore it can be used to create volumetric effet
 * it applying some filter depending on the distance between the camera and the ray for the primary rays
 * For the others, we can still apply some kind of ray extinction
 */
struct RT_RayOutput {
    Color resultColor;
    double distance;
    double intensity;
};

/**
 * @class RT_Ray
 * Contains everything to create and compute a ray.
 */
class RT_Ray {
 private:
  Vector dir;
  Vector origin;
  RT_RayConfig config;

  static struct RT_RayOutput RT_ComputeRecurseRay(Vector dir, Point3D origin, struct RT_RayConfig config, RT_RayEnvIntersector *intersector);

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
  void RT_ComputePrimaryRay(RT_RayEnvIntersector *, OutputPictureManager *);

  /**
   * When the ray is casted we can find where the color goes in the picture
   */
  const unsigned int x = 0;
  const unsigned int y = 0;
};

#endif //_RT_RAY_H_
