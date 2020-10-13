#ifndef GRAPHIC_ENGINE_OBJECT_H
#define GRAPHIC_ENGINE_OBJECT_H

#include <list>
#include <utils.h>
#include "Tessel.h"
#include "ApparenceProperties.h"

class Object {
 protected:
  Point3D absoluteCenterPosition;
  double xRotation;
  double yRotation;
  double zRotation;
  std::list<Tessel *> tessels;
  ApparenceProperties properties;
 public:
  virtual void Tesselate();
};

#endif //GRAPHIC_ENGINE_OBJECT_H
