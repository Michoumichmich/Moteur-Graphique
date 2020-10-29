#include "RT_RayCaster.h"

std::list<RT_Ray> RT_RayCaster::generateFirstRays(RT_RayConfig config, Camera *cam, int pixel_height_count, int pixel_width_count)
{
  std::list<RT_Ray> Rays;

  if (cam->mode == ORTHOGRAPHIC)
    {
      /**
       * The direction in which we look is constant
       */
      Vector direction = cam->getCamViewCenter();
      for (int x = 0; x < pixel_width_count; x++)
        {
          for (int y = 0; y < pixel_height_count; y++)
            {
              Vector shift = Vector(cam->target, cam->getPixelTargetInEnv(x, y));
              Point3D originFromInfinite = cam->origin + shift;
#ifdef DEBUG
              //std::cout << "[RT_RayCaster] dir: " << direction << " origin from inf: " << originFromInfinite << std::endl;
#endif
              Rays.emplace_back(direction, originFromInfinite, config, x, y);
            }
        }
    }
  else if (cam->mode == PERSPECTIVE)
    {
      for (int x = 0; x < pixel_width_count; x++)
        {
          for (int y = 0; y < pixel_height_count; y++)
            {
              Vector direction = Vector(cam->origin, cam->getPixelTargetInEnv(x, y));
#ifdef DEBUG
              //std::cout << "[RT_RayCaster] dir: " << direction << " origin: " << cam->origin << std::endl;
#endif
              Rays.emplace_back(direction, cam->origin, config, x, y);
            }
        }
    }
  return Rays;
}
