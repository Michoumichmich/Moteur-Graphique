#ifndef GRAPHICSENGINE_SPHERE_H
#define GRAPHICSENGINE_SPHERE_H

#include "../Object.h"

class Sphere : public Object {
 public:
  void Tesselate() override;
};

#endif //GRAPHICSENGINE_SPHERE_H
