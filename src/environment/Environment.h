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
    std::list<MappedTexture *> allTMapped;
    Camera *currentCam;
    int tesselResolution = 30;
public:
    std::string envName;
    Color backgroundColor = Color(24, 179, 220);
    Vector ambientIntensity;
    std::list<Light *> allLights;

    explicit Environment(std::string name);

    Environment();

    Camera *currCam();

    void addCamera(Camera *);

    void addLight(Light *);

    std::list<std::string> listCameras();

    bool switchCamera(const std::string &camName);

    std::list<Tessel *> *getTessels();

    void tesselate();

    void addObject(Object *);

    ~Environment() override;

    void serialize(std::stringstream &stream) override;

    void deserialize(std::istream &stream) override;

    [[nodiscard]] int getResolution() const;

    void setResolution(int n);

    void reset();
};

#endif //GRAPHIC_ENGINE_ENVIRONMENT_H
