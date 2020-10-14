#include "RT_RayEnvIntersector.h"
#include <config.h>


RT_RayEnvIntersector::RT_RayEnvIntersector(Environment *env) {
    this->environment = env;
}

struct RT_RayIntersectionResult RT_RayEnvIntersector::RT_RayFindIntersection(Point3D origin, Vector direction) {
    return {};
}

bool RT_RayEnvIntersector::checkForSingleIntersection(Vector origin, Vector dir, Tessel tessel, Vector *intersectionPoint, double *distance) {
    Vector x0 = tessel.summmits[0];
    Vector x1 = tessel.summmits[1];
    Vector x2 = tessel.summmits[2];
    double a0 = Vector::crossProduct(x1 - origin, x2 - origin)->dot(dir) * 0.5;
    double a1 = Vector::crossProduct(x2 - origin, x0 - origin)->dot(dir) * 0.5;
    double a2 = Vector::crossProduct(x0 - origin, x1 - origin)->dot(dir) * 0.5;

    if (likely(a0 < 0 && a1 < 0 && a2 < 0)) {
        return false;
    }

    //TODO


    return true;
}


