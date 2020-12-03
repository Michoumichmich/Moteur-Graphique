#ifndef GRAPHICSENGINE_RT_COMMONS_H
#define GRAPHICSENGINE_RT_COMMONS_H

#include "environment.h"

/**
 * Used to define the type of rendering.
 */
enum class RT_RayRenderMode {
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
    RT_RayRenderMode rtMode = RT_RayRenderMode::RT_DEPTHMAP;
    int bouncesLeft = MAX_BOUNCES;
    double intensity = 1;
    Vector cam_view_center = Vector();
    Environment *env = nullptr;
};


/**
 * Data outputed by the ray launched by the cam.
 * The distance between the ray and the first tessel it touched. If the ray goes to infinity we return -1
 * It's going to be useful to compute the bitmap and deph map, furthermore it can be used to create volumetric effet
 * it applying some filter depending on the distance between the camera and the ray for the primary rays
 * For the others, we can still apply some kind of ray extinction
 */
struct RT_RayOutput {
    Color resultColor = Color(0);
  Point3D rayTesselIntersection;
    double distance{};
  double ortho_distance{};
  double intensity = 1;
};

#endif //GRAPHICSENGINE_RT_COMMONS_H
