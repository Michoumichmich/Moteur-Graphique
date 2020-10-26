#ifndef _MAPPEDTEXTURE_H_
#define _MAPPEDTEXTURE_H_

#include <utils.h>
#include "Object.h"
#include "CoordinatesHandler.h"

/**
 * @class ImageTexture
 * Its a sort of object thats not going to be tesselated. It's just a rectangle on wich we can map a texture
 */
class MappedTexture {
 private:
  std::string picturePath;
  struct transformations transfo;

  /**
   * We must compute those values when placing the object in the global environment given the
   * fact that the intersection point's coordinates are going to be in that referential.
   */
  Point3D absoluteBottomLeft;
  Point3D absoluteBottomRight;
  Point3D absoluteTopLeft;
  Point3D absoluteTopRight;
 public:
  /**
   * If a ray intersects this object, we want to know the color of the pixel at that intersection point
   * Just some basic maths to convert the Point3D
   * @return
   */
  Color getPixelAtCoordinates(Point3D);
};

#endif //_MAPPEDTEXTURE_H_
