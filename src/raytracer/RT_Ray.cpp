#include "RT_Ray.h"
#include <utils.h>

RT_Ray::RT_Ray(Vector vec, Point3D orig, unsigned int counter, bool isBitmap) : dir(vec), origin(orig), bouncesLeftCounter(counter), isBitmap(isBitmap) {
}

void RT_Ray::RT_ComputePrimaryRay(RT_RayEnvIntersector *intersector, OutputPictureManager *pic) {
    struct RT_RayOutput res = RT_ComputeDescendingRay(dir, origin, bouncesLeftCounter, intersector);
    pic->writePixel(res.resultColor, x, y);
}

struct RT_RayOutput RT_Ray::RT_ComputeDescendingRay(Vector dir, Point3D origin, unsigned int bouncingsLeft, RT_RayEnvIntersector *intersector) {

    if (isBitmap) {
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
    //TODO Computes the ray recursively
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
