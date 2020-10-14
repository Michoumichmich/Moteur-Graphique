#ifndef GRAPHIC_ENGINE_TESSEL_H
#define GRAPHIC_ENGINE_TESSEL_H

#include <utils.h>

#include "ApparenceProperties.h"

class Tessel {
public:
    Tessel();
    Tessel(Point3D, Point3D, Point3D);
    Point3D summmits[3];
    ApparenceProperties properties;
};

#endif //GRAPHIC_ENGINE_TESSEL_H
