#include "RT_Ray.h"
#include <utils.h>

RT_Ray::RT_Ray(Vector dir, Point3D orig, unsigned int counter, bool isBitmap) : dir(dir), origin(orig), bouncesLeftCounter(counter), isBitmap(isBitmap) {
}

RT_Ray::RT_Ray(Vector dir, Point3D orig, unsigned int counter, bool isBitmap, unsigned int x, unsigned int y) : dir(dir), origin(orig),
                                                                                                                bouncesLeftCounter(counter), isBitmap(isBitmap),
                                                                                                                x(x), y(y) {
}


void RT_Ray::RT_ComputePrimaryRay(RT_RayEnvIntersector *intersector, OutputPictureManager *pic) {

    struct RT_RayOutput rayOutput = RT_ComputeDescendingRay(dir, origin, bouncesLeftCounter, intersector);
    isBitmap = false,
            isDepthmap = true;

    if (isBitmap && rayOutput.distance >= 0) {
        pic->writePixel(Color(1), x, y);
    } else if (isDepthmap && rayOutput.distance >= 0) {
        pic->writePixel(rayOutput.distance, x, y);
    } else if (rayOutput.distance >= 0) {
        pic->writePixel(rayOutput.resultColor, x, y);
    } else {
        pic->writePixel(Color(0), x, y);
    }
}

struct RT_RayOutput RT_Ray::RT_ComputeDescendingRay(Vector dir, Point3D origin, unsigned int bouncingsLeft, RT_RayEnvIntersector *intersector) const {

    /**
     * No reflexions or whatsoever, we return directly the result.
     */
    if (isBitmap || isDepthmap) {
        struct RT_RayIntersectionResult res = intersector->RT_RayFindIntersection(origin, dir);
        if (res.intersectsSometing) {
            return RT_RayOutput{Color(1.0), res.distanceMin, 1};
        } else {
            return RT_RayOutput{Color(0.0), res.distanceMin, 1};
        }
    }

    if (rayIntensity == 0 | bouncingsLeft == 0) {
        // TODO  return what ?
    }

    struct RT_RayIntersectionResult res = intersector->RT_RayFindIntersection(origin, dir);
    if (!res.intersectsSometing || res.type == INF) {
        return RT_RayOutput{Color(), -1, 1};
    }

    if (res.type == MAPPED_TEXTURE) {
        /**
         * On a touché une texture, on affiche la couleur du pixel
         */
        return RT_RayOutput{res.texture.getPixelAtCoordinates(res.intersectionPoint), Point3D::distance(origin, res.intersectionPoint)};
    }

    if (res.type == TESSEL) {
        // TODO Ca se complique, et on se rappelle récursivement jusqu'à l'extinction du rayon.
    }

    return RT_RayOutput();
}
