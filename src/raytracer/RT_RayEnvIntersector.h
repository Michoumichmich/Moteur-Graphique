/**
 * @file RT_RayEnvIntersector.h
 * @see : https://www.iue.tuwien.ac.at/phd/ertl/node114.html
  */

#ifndef _RT_RAYENVINTERSECTOR_H_
#define _RT_RAYENVINTERSECTOR_H_

#include <environment.h>
#include <utils.h>

enum class RT_RayIntersectionType {
    INF,
    TESSEL,
    MAPPED_TEXTURE
};

struct RT_IntersectorResult {
  bool intersectsSometing = false;
  double distance = -1;
  double ortho_dist = -1;
  Vector intersectionPoint = Vector();
  Tessel tessel{};
  MappedTexture texture{};
  RT_RayIntersectionType type = RT_RayIntersectionType::INF;
  //TODO Add an Object to the result, so that surface characteristics are accessible
};

/**
 * @class RT_RayEnvIntersector
 * Finds the closest tessel that intersects with a given ray
 */
class RT_RayEnvIntersector {
public:
    Environment* environment;

    static bool checkForSingleIntersection(const Point3D &origin, const Vector & dir, const Tessel* tessel, Vector* intersectionPoint, double* distance) ;

public:
    /**
     * Instantiates the environment prober once.
     * For now it might seem useless. But with a smarter implementation later it could be useful
     * We could split the environment in small zones thus reducing the number of tesssels we're checking.
     * Or something like that...
     */
    explicit RT_RayEnvIntersector(Environment*);

    /**
     * Its easy. This functions takes an origin and a direction and returns the struct
     * to know whether the ray hit something or not, what and where.
     * @param origin
     * @param direction
     * @return
     */
    [[nodiscard]] struct RT_IntersectorResult RT_RayFindIntersection(Point3D origin,Vector direction) const;
};

#endif //_RT_RAYENVINTERSECTOR_H_
