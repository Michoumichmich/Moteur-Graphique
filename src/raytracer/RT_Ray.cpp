#include "RT_Ray.h"
#include <utils.h>

RT_Ray::RT_Ray(Vector vec, Point3D orig, unsigned int counter) : dir(vec), origin(orig), bouncesLeftCounter(counter)
{
}
void RT_Ray::RT_ComputeRay(RT_RayEnvIntersector *intersector, OutputPictureManager *pic)
{
//TODO Computes the ray recursively
  struct RT_RayIntersectionResult res = intersector->RT_RayFindIntersection(origin, dir);
  if (!res.intersectsSometing)
    {
      /**
       * Le rayon est parti dans le vide
       */
      pic->writePixel(Color(BLACK), x, y);
    }
  else
    {
      if (res.type == MAPPED_TEXTURE)
        {
          /**
           * On a touché une texture, on affiche la couleur du pixel
           */
          pic->writePixel(res.texture->getPixelAtCoordinates(res.intersectionPoint), x, y);
        }
      //TODO les autres cas.
    }

}
