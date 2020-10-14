#ifndef GRAPHIC_ENGINE_ENVIRONMENT_H
#define GRAPHIC_ENGINE_ENVIRONMENT_H

#include <list>
#include <string>

#include "Camera.h"
#include "Object.h"
#include "MappedTexture.h"

class Environment {
private:
    std::list<Camera *> cameras;
    std::list<Tessel *> allTessels;
    std::list<Object *> allOjects;
    std::list<MappedTexture *> allTMapped;
    Camera *currentCam;
public:
    std::string envName;

    Environment(std::string name);

    Environment();

    Camera *getCurrentCam();

    std::list<std::string> listCameras();

    void switchCamera(std::string camName);
};

#endif //GRAPHIC_ENGINE_ENVIRONMENT_H
