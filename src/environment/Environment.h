#ifndef GRAPHIC_ENGINE_ENVIRONMENT_H
#define GRAPHIC_ENGINE_ENVIRONMENT_H

#include <list>
#include <string>

#include "Camera.h"
#include "Object.h"
#include "MappedTexture.h"
#include "Light.h"
#include <memory>

class Environment : public Serializable {
private:
    std::list<std::shared_ptr<Camera>> cameras;
    std::list<Tessel *> allTessels;
    std::list<std::shared_ptr<Object>> allObjects;
    std::list<std::shared_ptr<MappedTexture>> allTMapped;
    std::shared_ptr<Camera>currentCam;
    int tesselResolution = 30;
public:
    std::string envName;
    Color backgroundColor = Color(24, 179, 220);
    Vector ambientIntensity;
    std::list<Light *> allLights;

    explicit Environment(std::string name);

    Environment();

    std::shared_ptr<Camera> currCam();

    void addCamera(const std::shared_ptr<Camera>& camera);

    void addLight(Light *);

    std::list<std::string> listCameras();

    bool switchCamera(const std::string &camName);

    std::list<Tessel *> *getTessels();

    std::list<std::shared_ptr<Object>> getObjects();

    std::list<std::shared_ptr<Camera>> getCameras();

    void tesselate();

    void addObject(const std::shared_ptr<Object>& obj);

    ~Environment() override;

    void serialize(std::stringstream &stream) override;

    void deserialize(std::istream &stream) override;

    [[nodiscard]] int getResolution() const;

    void setResolution(int n);

    void reset();
};

#endif //GRAPHIC_ENGINE_ENVIRONMENT_H
