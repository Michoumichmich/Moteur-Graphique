#include "RT_Ray.h"
#include <utils.h>
#include <cmath>

RT_Ray::RT_Ray(Vector dir, Point3D orig, struct RT_RayConfig config) : dir(dir), origin(orig), config(config)
{
}

RT_Ray::RT_Ray(Vector dir, Point3D orig, struct RT_RayConfig config, unsigned int x, unsigned int y) : dir(dir), origin(orig), config(config), x(x), y(y)
{
}

/**
 * Takes a primary ray ie from the camera, computes it given its configuration and writes it using the
 * picture manager to a file.
 * @param intersector
 * @param pic
 */
void RT_Ray::RT_ComputePrimaryRay(RT_RayEnvIntersector *intersector, RT_OutputManager *pic) {

    struct RT_RayOutput rayOutput = RT_ComputeRecurseRay(dir, origin, config, intersector);
    pic->RT_SaveRay(rayOutput, x, y);
}

/**
 * Recursively (if needed) computes a ray.
 * @param dir
 * @param origin
 * @param config
 * @param intersector
 * @return the ray's color, distance to the first object and intensity.
 */
struct RT_RayOutput RT_Ray::RT_ComputeRecurseRay(Vector dir, Point3D origin, struct RT_RayConfig config, RT_RayEnvIntersector *intersector)
{

  if (config.bouncesLeft == 0)
    {
      return RT_RayOutput{Color(0.0), Vector{}, 0.0, 0.0, 1};
    }

  /**
   * No reflexions or whatsoever, we return directly the result.
   */
  if (config.rtMode == RT_RayRenderingMode::RT_BITMAP || config.rtMode == RT_RayRenderingMode::RT_DEPTHMAP)
    {
      struct RT_RayIntersectionResult res = intersector->RT_RayFindIntersection(origin, dir);
      /**
       * Distance TO THE PLANE where is the intersection point, for the DOF etc, depth mapping, etc
       */
      double ortho_dist = std::sqrt(config.cam_view_center.dot(res.intersectionPoint - origin));
      if (res.intersectsSometing)
        {
          return RT_RayOutput{res.tessel.properties.color, res.intersectionPoint, res.distance, ortho_dist, 1};
        }
      else
        {
          return RT_RayOutput{Color(0.0), res.intersectionPoint, res.distance, ortho_dist, 1};
        }
    }

  struct RT_RayIntersectionResult res = intersector->RT_RayFindIntersection(origin, dir);
  if (!res.intersectsSometing || res.type == RT_RayIntersectionType::INF)
    {
      return RT_RayOutput{Color(), res.intersectionPoint, -1, 1};
    }

  if (res.type == RT_RayIntersectionType::MAPPED_TEXTURE)
    {
      /**
       * On a touché une texture, on affiche la couleur du pixel
       */
      return RT_RayOutput{res.texture.getPixelAtCoordinates(res.intersectionPoint), res.intersectionPoint, (origin - res.intersectionPoint).length(), 1};
    }

  if (res.type == RT_RayIntersectionType::TESSEL)
    {
      // TODO Ca se complique, et on se rappelle récursivement jusqu'à l'extinction du rayon.
    }

  return RT_RayOutput();
}
