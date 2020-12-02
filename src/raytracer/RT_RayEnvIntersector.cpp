#include "RT_RayEnvIntersector.h"
#include <config.h>
#include <cmath>

RT_RayEnvIntersector::RT_RayEnvIntersector(Environment *env) {
    this->environment = env;
}

struct RT_IntersectorResult RT_RayEnvIntersector::RT_RayFindIntersection(Point3D origin, Vector direction) const {
    Tessel closest;
    double distanceMinTessel = -1;
    double distanceMinTexture = -1;
    double distance;
    Vector intersection = Vector();
    struct RT_IntersectorResult result;
    std::list<Tessel *> *tessels = this->environment->getTessels();
    std::list<Tessel *>::iterator aTessel;
    for (aTessel = tessels->begin(); aTessel != tessels->end(); aTessel++) {
        if (checkForSingleIntersection(origin, direction, *aTessel, &intersection, &distance) && (distance < distanceMinTessel || distanceMinTessel < 0)) {
            closest = **aTessel;
            result.ortho_dist = std::sqrt(this->environment->currCam()->getCamViewCenter().dot(intersection-origin));
            distanceMinTessel = distance;
            result.tessel = closest;
            result.intersectionPoint = intersection;
            result.distance = distance;
            result.intersectsSometing = true;
            result.type = RT_RayIntersectionType::TESSEL;
        }
    }

    // Then we check for textures.
    return result;
}

/**
 * Réecrire la même pour les rectangles ie textures, on casse le rectangle en deux et on l'appelle deux fois.
 * @param origin
 * @param dir
 * @param tessel
 * @param intersectionPoint
 * @param distance
 * @return
 */
bool RT_RayEnvIntersector::checkForSingleIntersection(Point3D origin, Vector dir, Tessel *tessel, Vector *intersectionPoint, double *distance) {
    Vector x0_orig = tessel->summmits[0] - origin;
    Vector x1_orig = tessel->summmits[1] - origin;
    Vector x2_orig = tessel->summmits[2] - origin;
    double a0 = (x1_orig).cross(x2_orig).dot(dir);
    double a1 = (x2_orig).cross(x0_orig).dot(dir);

    if (unlikely(a0 < 0 && a1 < 0) || (a0 > 0 && a1 > 0)) {
        double a2 = (x0_orig).cross(x1_orig).dot(dir);
        /**
         * There's an intersection if all ai non positive or all ai non negativs while not all null
         * We already know that a0 and a1 are of the same sign
         */
        if ((a1 >= 0 && a2 >= 0) || (a1 <= 0 && a2 <= 0))//&& !(a0 == 0 && a1 == 0 && a2 == 0)))
        {
            /**
             * Now we compute the intersection point.
             */
            Vector intersection = (tessel->summmits[0] * a0 + tessel->summmits[1] * a1 + tessel->summmits[2] * a2) / (a0 + a1 + a2);
            /**
             * To check wether the vectors are in the right direction
             */
            if (likely((intersection - origin).dot(dir) >= 0)) {
                *intersectionPoint = intersection;
                *distance = (origin - intersection).length();
                return true;
            }
        }
    }
    return false;
}



