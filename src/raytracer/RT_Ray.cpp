#include "RT_Ray.h"
#include <utils.h>

RT_Ray::RT_Ray(Vector dir, Point3D orig, struct RT_RayConfig config) : dir(dir), origin(orig), config(config) {
}

RT_Ray::RT_Ray(Vector dir, Point3D orig, struct RT_RayConfig config, unsigned int x, unsigned int y) : dir(dir), origin(orig), config(config), x(x), y(y) {
}

/**
 * Takes a primary ray ie from the camera, computes it given its configuration and writes it using the
 * picture manager to a file.
 * @param intersector
 * @param pic
 */
void RT_Ray::RT_ComputePrimaryRay(RT_RayEnvIntersector *intersector, OutputPictureManager *pic) {

    struct RT_RayOutput rayOutput = RT_ComputeRecurseRay(dir, origin, config, intersector);

    if (config.rtMode == RT_RayRenderingMode::RT_BITMAP && rayOutput.distance >= 0) {
        pic->writePixel(Color(1), x, y);
    } else if (config.rtMode == RT_RayRenderingMode::RT_DEPTHMAP && rayOutput.distance >= 0) {
        pic->writePixel(rayOutput.distance, x, y);
    } else if (config.rtMode == RT_RayRenderingMode::RT_STANDARD && rayOutput.distance >= 0) {
        pic->writePixel(rayOutput.resultColor, x, y);
    } else {
        pic->writePixel(Color(0), x, y);
    }
}


/**
 * Recursively (if needed) computes a ray.
 * @param dir
 * @param origin
 * @param config
 * @param intersector
 * @return the ray's color, distance to the first object and intensity.
 */
struct RT_RayOutput RT_Ray::RT_ComputeRecurseRay(Vector dir, Point3D origin, struct RT_RayConfig config, RT_RayEnvIntersector *intersector) {

    /**
     * No reflexions or whatsoever, we return directly the result.
     */
    if (config.rtMode == RT_RayRenderingMode::RT_BITMAP || config.rtMode == RT_RayRenderingMode::RT_DEPTHMAP) {
        struct RT_RayIntersectionResult res = intersector->RT_RayFindIntersection(origin, dir);
        if (res.intersectsSometing) {
            return RT_RayOutput{Color(1.0), res.distanceMin, 1};
        } else {
            return RT_RayOutput{Color(0.0), res.distanceMin, 1};
        }
    }

    if (config.intensity == 0 || config.bouncesLeft == 0) {
        // TODO  return what ?
    }

    struct RT_RayIntersectionResult res = intersector->RT_RayFindIntersection(origin, dir);
    if (!res.intersectsSometing || res.type == RT_RayIntersectionType::INF) {
        return RT_RayOutput{Color(), -1, 1};
    }

    if (res.type == RT_RayIntersectionType::MAPPED_TEXTURE) {
        /**
         * On a touché une texture, on affiche la couleur du pixel
         */
        return RT_RayOutput{res.texture.getPixelAtCoordinates(res.intersectionPoint), Point3D::distance(origin, res.intersectionPoint), 1};
    }

    if (res.type == RT_RayIntersectionType::TESSEL) {
        // TODO Ca se complique, et on se rappelle récursivement jusqu'à l'extinction du rayon.
    }

    return RT_RayOutput();
}
