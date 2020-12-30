#include "RT_RayEnvIntersector.h"
#include <config.h>
#include <cmath>

RT_RayEnvIntersector::RT_RayEnvIntersector(Environment *env) {
    this->environment = env;
}

struct RT_IntersectorResult RT_RayEnvIntersector::RT_RayFindIntersection(const Point3D origin, const Vector direction) const {
    Tessel closest;
    double distanceMinTessel = -1;
    double distanceMinTexture = -1;
    double distance;
    Vector intersection = Vector();
    struct RT_IntersectorResult result;
    auto tessels = this->environment->getTessels();
    for (const Tessel &aTessel : *tessels) {
        if (checkForSingleIntersection(origin, direction, &aTessel, &intersection, &distance) && (distance < distanceMinTessel || distanceMinTessel < 0) && distance > MIN_RAY_LENGTH) {
            closest = aTessel;
            result.ortho_dist = std::sqrt(this->environment->currCam()->getCamViewCenter().dot(intersection - origin));
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
bool RT_RayEnvIntersector::checkForSingleIntersection(const Point3D &origin, const Vector &dir, const Tessel *tessel, Vector *intersectionPoint, double *distance) {
    Vector x0_orig = tessel->summmits[0] - origin;
    Vector x1_orig = tessel->summmits[1] - origin;
    Vector x2_orig = tessel->summmits[2] - origin;
    float a0 = (x1_orig).cross(x2_orig).dot(dir);
    float a1 = (x2_orig).cross(x0_orig).dot(dir);

    if ((a0 < 0 && a1 < 0) || (a0 > 0 && a1 > 0)) {
    float a2 = (x0_orig).cross(x1_orig).dot(dir);
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
    if (((intersection - origin).dot(dir) >= 0)) {
    *intersectionPoint = intersection;
    *distance = (origin - intersection).length();
                return true;
            }
        }
    }
    return false;
}



