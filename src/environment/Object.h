#ifndef GRAPHIC_ENGINE_OBJECT_H
#define GRAPHIC_ENGINE_OBJECT_H

#include <list>
#include <utils.h>
#include "Tessel.h"
#include "ApparenceProperties.h"

class Object {
private:
    Point3D absoluteCenterPosition;
    std::list<Tessel> tessels;
    ApparenceProperties properties;
public:
    /**
     * sets the list of tessels
     */
    //virtual void Tesselate();
};

#endif //GRAPHIC_ENGINE_OBJECT_H
