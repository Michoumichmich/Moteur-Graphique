#include "RT_RayEnvIntersector.h"
#include <config.h>

RT_RayEnvIntersector::RT_RayEnvIntersector(Environment *env)
{
  this->environment = env;
}

struct RT_RayIntersectionResult RT_RayEnvIntersector::RT_RayFindIntersection(Point3D origin, Vector direction) const
{
  Tessel closest;
  double distanceMinTessel = -1;
  double distanceMinTexture = -1;
  double distance;
  Vector intersection = Vector();
  struct RT_RayIntersectionResult result;
  std::list<Tessel *> *tessels = this->environment->getTessels();
  std::list<Tessel *>::iterator aTessel;
  for (aTessel = tessels->begin(); aTessel != tessels->end(); aTessel++)
    {
      if (checkForSingleIntersection(origin, direction, *aTessel, &intersection, &distance) && (distance < distanceMinTessel || distanceMinTessel < 0))
        {
          closest = **aTessel;
          distanceMinTessel = distance;
          result.tessel = closest;
          result.intersectionPoint = intersection;
          result.distanceMin = distance;
          result.intersectsSometing = true;
          result.type = RT_RayIntersectionType::TESSEL;
        }
    }
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
bool RT_RayEnvIntersector::checkForSingleIntersection(Point3D orig, Vector dir, Tessel *tessel, Vector *intersectionPoint, double *distance)
{
  Vector x0 = Vector(tessel->summmits[0]);
  Vector x1 = Vector(tessel->summmits[1]);
  Vector x2 = Vector(tessel->summmits[2]);
  Vector origin = Vector(orig);
  double a0 = (x1 - origin).cross(x2 - origin).dot(dir) * 0.5;
  double a1 = (x2 - origin).cross(x0 - origin).dot(dir) * 0.5;
  if ((a0 < 0 && a1 > 0) || (a0 > 0 && a1 < 0))
    {
      return false;
    }
  double a2 = (x0 - origin).cross(x1 - origin).dot(dir) * 0.5;

  /**
   * There's an intersection if all ai non positive or all ai non negativs while not all null
   */
  if (unlikely(((a0 >= 0 && a1 >= 0 && a2 >= 0) || (a0 <= 0 && a1 <= 0 && a2 <= 0)) && !(a0 == 0 && a1 == 0 && a2 == 0)))
    {
      /**
       * Now we compute the intersection point.
       */
      double a = a0 + a1 + a2;
      Vector intersection = Vector(x0 * (a0 / a) + x1 * (a1 / a) + x2 * (a2 / a));
      /**
       * To check wether the vectors are in the right direction
       */
      if ((intersection - origin).dot(dir) >= 0)
        {
          intersectionPoint->x = intersection.x;
          intersectionPoint->y = intersection.y;
          intersectionPoint->z = intersection.z;
          *distance = (origin - intersection).length();
          return true;
        }
    }
  return false;
}


