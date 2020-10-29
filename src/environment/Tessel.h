#ifndef GRAPHIC_ENGINE_TESSEL_H
#define GRAPHIC_ENGINE_TESSEL_H

#include <utils.h>

#include "ApparenceProperties.h"

class Tessel {
 public:
  Point3D summmits[3];
  ApparenceProperties properties;

  Tessel();

  Tessel(Point3D, Point3D, Point3D);

  Tessel(Point3D, Point3D, Point3D, ApparenceProperties);

  /**
   * Computes the normal vector
   * @return
   */
  Vector getNormalVector();

  /**
   * Computes a reflexion vector using a normal vector
   * @param direction the ray arriving on the tessel
   * @return
   */
  Vector getReflexionVector(Vector direction);
};

#endif //GRAPHIC_ENGINE_TESSEL_H
