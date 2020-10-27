#include "RT_RayCaster.h"

std::list<RT_Ray> RT_RayCaster::generateFirstRays(RT_RayConfig config, Camera *cam, unsigned int pixel_height_count, unsigned int pixel_width_count)
{
  std::list<RT_Ray> Rays;

  if (cam->mode == ORTHOGRAPHIC)
    {
      for (unsigned i = 0; i < pixel_width_count; i += 1 / pixel_height_count)
        {
          for (unsigned j = 0; j < pixel_width_count; j += 1 / pixel_width_count)
            {
              Rays.push_back(RT_Ray(Vector(cam->origin, cam->target), cam->origin, config, i, j));
            }
        }
    }
  else if (cam->mode == PERSPECTIVE)
    {
      double pixel_width = cam->viewportWidth / pixel_width_count;
      double pixel_height = cam->viewportHeight / pixel_height_count;
      Vector view = Vector(cam->target, cam->origin);
      Vector up_unit = (cam->viewUp - view.normalize() * (view.normalize().dot(cam->viewUp))).normalize();
      // double dot = view.normalize().dot(cam->viewUp);
      Vector right_unit = up_unit.cross(view).normalize();
      Point3D bottomLeft = Vector(cam->target) - up_unit * (cam->viewportHeight / 2.0) - right_unit * (cam->viewportWidth / 2.0);

      for (unsigned x = 0; x < pixel_width_count; x++)
        {
          for (unsigned y = 0; y < pixel_height_count; y++)
            {
              Vector target = Vector(bottomLeft) + up_unit * (y * pixel_height) + right_unit * (x * pixel_width);
              Rays.emplace_back(target - cam->origin, cam->origin, config, x, y);
            }
        }
    }

  return Rays;
}
