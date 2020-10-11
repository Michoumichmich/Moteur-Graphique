#ifndef GRAPHIC_ENGINE_ENVIRONMENT_H
#define GRAPHIC_ENGINE_ENVIRONMENT_H

#include <list>
#include <string>

#include "Camera.h"
#include "Object.h"

class Environment {
private:
    std::list<Camera> cameras;
    std::list<Tessel> allTessels;
    std::list<Object> allOjects;
public:
    std::string envName;
};


#endif //GRAPHIC_ENGINE_ENVIRONMENT_H
