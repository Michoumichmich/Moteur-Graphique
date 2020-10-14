/**
 * @file RT_RayEnvIntersector.h
 * @see : https://www.iue.tuwien.ac.at/phd/ertl/node114.html
  */

#ifndef _RT_RAYENVINTERSECTOR_H_
#define _RT_RAYENVINTERSECTOR_H_

#include <environment.h>
#include <utils.h>

enum RT_RayIntersectionType {
    INF,
    TESSEL,
    MAPPED_TEXTURE
};

struct RT_RayIntersectionResult {
    bool intersectsSometing{};
    Point3D intersectionPoint;
    Tessel *tessel{};
    MappedTexture *texture{};
    enum RT_RayIntersectionType type;
};


/**
 * @class RT_RayEnvIntersector
 * Finds the closest tessel that intersects with a given ray
 */
class RT_RayEnvIntersector {
private:
    Environment *environment;

    bool checkForSingleIntersection(Vector origin, Vector dir, Tessel tessel, Vector *intersectionPoint, double *distance);

public:
    /**
     * Instantiates the environment prober once.
     * For now it might seem useless. But with a smarter implementation later it could be useful
     * We could split the environment in small zones thus reducing the number of tesssels we're checking.
     * Or something like that...
     */
    explicit RT_RayEnvIntersector(Environment *);

    /**
     * Its easy. This functions takes an origin and a direction and returns the struct
     * to know whether the ray hit something or not, what and where.
     * @param origin
     * @param direction
     * @return
     */
    struct RT_RayIntersectionResult RT_RayFindIntersection(Point3D origin, Vector direction);
};

#endif //_RT_RAYENVINTERSECTOR_H_
