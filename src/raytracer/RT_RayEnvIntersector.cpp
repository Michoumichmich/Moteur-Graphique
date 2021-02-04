#include "RT_RayEnvIntersector.h"
#include <config.h>
#include <cmath>
#include <optional>

RT_RayEnvIntersector::RT_RayEnvIntersector(Environment *env) {
    this->environment = env;
}


std::optional<struct RT_IntersectorResult> RT_RayEnvIntersector::RT_RayFindIntersection(const Point3D origin, const Vector direction) const {
    double distanceMinTessel = 0;
    Vector min_intersection;
    Tessel min_tessel;
    bool found = false;

    std::shared_ptr<std::vector<Tessel>> tessels = this->environment->getTessels();
    for (const Tessel &aTessel : *tessels) {
        if (auto res = checkForSingleIntersection(origin, direction, aTessel)) {
            auto[intersection, distance] = res.value();
            if (!found || distance < distanceMinTessel) {
                found = true;
                min_tessel = aTessel;
                distanceMinTessel = distance;
                min_intersection = intersection;
            }
        }
    }

    if (found) {
        struct RT_IntersectorResult result;
        result.ortho_dist = std::sqrt(this->environment->currCam()->getCamViewCenter().dot(min_intersection - origin));
        result.tessel = min_tessel;
        result.intersectionPoint = min_intersection;
        result.distance = distanceMinTessel;
        result.intersectsSometing = true;
        result.type = RT_RayIntersectionType::TESSEL;
        return result;
    }
    return std::nullopt;
}

/**
 * Réecrire la même pour les rectangles ie textures, on casse le rectangle en deux et on l'appelle deux fois.
 * @param origin
 * @param dir
 * @param tessel
 * @param out_intersectionPoint
 * @param out_distance
 * @return
 */
std::optional<std::tuple<Vector, double>> RT_RayEnvIntersector::checkForSingleIntersection(const Point3D &origin, const Vector &dir, const Tessel &tessel) {
    Vector x0_orig = tessel.summmits[0] - origin;
    Vector x1_orig = tessel.summmits[1] - origin;
    Vector x2_orig = tessel.summmits[2] - origin;
    float a0 = (x1_orig).cross(x2_orig).dot(dir);
    float a1 = (x2_orig).cross(x0_orig).dot(dir);

    if ((a0 < 0 && a1 < 0) || (a0 > 0 && a1 > 0)) {
        float a2 = x0_orig.cross(x1_orig).dot(dir);
        /**
         * There's an intersection if all ai non positive or all ai non negativs while not all null
         * We already know that a0 and a1 are of the same sign
         */
        if ((a1 >= 0 && a2 >= 0) || (a1 <= 0 && a2 <= 0))//&& !(a0 == 0 && a1 == 0 && a2 == 0)))
        {
            /**
             * Now we compute the intersection point.
             */
            Vector intersection = (tessel.summmits[0] * a0 + tessel.summmits[1] * a1 + tessel.summmits[2] * a2) / (a0 + a1 + a2);
            /**
             * To check wether the vectors are in the right direction
             */
            if ((intersection - origin).dot(dir) >= 0) {
                double out_distance = (origin - intersection).length();
                if (out_distance > MIN_RAY_LENGTH)
                    return std::make_tuple(intersection, out_distance);
                else
                    return std::nullopt;
            }
        }
    }
    return std::nullopt;
}



