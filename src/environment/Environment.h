#ifndef GRAPHIC_ENGINE_ENVIRONMENT_H
#define GRAPHIC_ENGINE_ENVIRONMENT_H

#include <list>
#include <string>

#include "Camera.h"
#include "Object.h"
#include "MappedTexture.h"
#include "Light.h"

class Environment : public Serializable {
private:
    std::list<Camera *> cameras;
    std::list<Tessel *> allTessels;
    std::list<Object *> allObjects;
    std::list<Light *> allLights;
    std::list<MappedTexture *> allTMapped;
    Camera *currentCam;
    int tesselResolution = 30;
public:
    std::string envName;
    Color backgroundColor = Color(24, 179, 220);

    explicit Environment(std::string name);

    Environment();

    Camera *getCurrentCam();

    std::list<std::string> listCameras();

    void switchCamera(std::string camName);

    std::list<Tessel *> *getTessels();

    void tesselate();

    void addObject(Object *);

    ~Environment();

    void serialize(std::ostream &stream) override;

    void deserialize(std::istream &stream) override;

};

#endif //GRAPHIC_ENGINE_ENVIRONMENT_H
