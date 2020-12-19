/**
 * @file GraphicsEngine.h
 */

#ifndef GRAPHIC_ENGINE_GRAPHICSENGINE_H
#define GRAPHIC_ENGINE_GRAPHICSENGINE_H

#include <list>
#include <string>
#include <environment.h>
#include <raytracer.h>
#include <utils.h>
#include <vector>
#include <memory>

#include "Abstract_Renderer.h"

/**
 * @class GraphicsEngine
 * Class used to manage the renders, the environment and everything. Ideally all the interactions should go through that class.
 */
class GraphicsEngine : public Serializable {
private:
    std::list<Environment *> environments{};
    Abstract_Renderer *renderer{};
    Environment *currentEnv{};
public:
    void launchRender(const std::string &outName);

    GraphicsEngine();

    void createEnvironment(std::string name);

    bool switchEnvironment(const std::string &name);

    void addObjInEnv(const std::shared_ptr<Object> &obj);

    Environment *currEnv();

    Abstract_Renderer *getRenderer();

    void setRenderer(Abstract_Renderer *);

    std::list<Environment *> getEnvironments();

    std::vector<std::string> environmentsName();

    void deserialize(std::istream &stream) override;

    void serialize(std::stringstream &stream) override;

    ~GraphicsEngine() override;

};

#endif //GRAPHIC_ENGINE_GRAPHICSENGINE_H
