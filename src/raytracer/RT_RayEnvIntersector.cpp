#include "RT_RayEnvIntersector.h"
#include <config.h>


RT_RayEnvIntersector::RT_RayEnvIntersector(Environment *env) {
    this->environment = env;
}

struct RT_RayIntersectionResult RT_RayEnvIntersector::RT_RayFindIntersection(Vector origin, Vector direction) {
    Tessel * closest;
    double distanceMin;
    double distance;
    Vector *intersection = nullptr;

    std::list<Tessel> tessels = this->environment->getTessels();
    std::list<Tessel>::iterator aTessel;
    for (aTessel = tessels.begin(); aTessel != tessels.end(); aTessel++) {
        /**
         * Here some multithreading could be useful
         */
//TODO
        checkForSingleIntersection(origin, direction, *aTessel, intersection, &distance);


    }



    return {};
}

bool RT_RayEnvIntersector::checkForSingleIntersection(Vector origin, Vector dir, Tessel tessel, Vector *intersectionPoint, double *distance) {
    Vector x0 = tessel.summmits[0];
    Vector x1 = tessel.summmits[1];
    Vector x2 = tessel.summmits[2];
    double a0 = Vector::crossProduct(x1 - origin, x2 - origin).dot(dir) * 0.5;
    double a1 = Vector::crossProduct(x2 - origin, x0 - origin).dot(dir) * 0.5;
    double a2 = Vector::crossProduct(x0 - origin, x1 - origin).dot(dir) * 0.5;


    /**
     * There's an intersection if all ai non positive or all ai non negativs while not all null
     */
    if (unlikely(((a0 >= 0 && a1 >= 0 && a2 >= 0) || (a0 <= 0 && a1 <= 0 && a2 <= 0)) && !(a0 == 0 && a1 == 0 && a2 == 0))) {
        /**
         * Now we compute the intersection point.
         */
        double a = a0 + a1 + a2;

        Vector intersection = Vector(x0 * (a0 / a) + x1 * (a1 / a) + x2 * (a2 / a));
        intersectionPoint->x = intersection.x;
        intersectionPoint->y = intersection.y;
        intersectionPoint->z = intersection.z;
        *distance = (origin - intersection).norm();
        return true;
    }
    return false;
}


