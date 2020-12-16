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
    std::shared_ptr<std::list<Tessel>> allTessels;
    std::list<std::shared_ptr<Object>> allObjects;
    std::list<std::shared_ptr<MappedTexture>> allTMapped;
    std::shared_ptr<Camera> currentCam;
    int tesselResolution = 30;
public:
    std::string envName;
    Color backgroundColor = Color(135, 206, 250);
    bool show_background_color = false;
    Vector ambientIntensity;
    std::list<Light *> allLights;
    double haze_intensity = 0;


    explicit Environment(std::string name);

    Environment();

    void setBackgroundAppearence(bool val);

    std::shared_ptr<Camera> currCam();

    /* A value between 0 and 1. */
    void setHazeIntensity(double d);

    void addCamera(const std::shared_ptr<Camera> &camera);

    void addLight(Light *);

    std::list<std::string> listCameras();

    bool switchCamera(const std::string &camName);

    std::shared_ptr<std::list<Tessel>> getTessels();

    std::list<std::shared_ptr<Object>> getObjects();

    std::list<std::shared_ptr<Camera>> getCameras();

    void tesselate();

    void addObject(const std::shared_ptr<Object>& obj);

    void serialize(std::stringstream& stream) override;

    void deserialize(std::istream& stream) override;

    [[nodiscard]] int getResolution() const;

    void setResolution(int n);

    std::ostream& print_objects(std::ostream& str);

    void reset();
};

#endif //GRAPHIC_ENGINE_ENVIRONMENT_H
