#include "RT_RayEnvIntersector.h"

RT_RayEnvIntersector::RT_RayEnvIntersector(Environment *env)
{
  this->environment = env;
}
struct RT_RayIntersectionResult RT_RayEnvIntersector::RT_RayFindIntersection(Point3D origin, Vector direction)
{
  return {};
}
