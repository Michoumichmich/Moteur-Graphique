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
#include <string>

#include "Abstract_Renderer.h"

/**
 * @class GraphicsEngine
 * Class used to manage the renders, the environment and everything. Ideally all the interactions should go through that class.
 */
class GraphicsEngine {
private:
    std::list<Environment *> environments;
    Abstract_Renderer *renderer{};
    Environment *currentEnv{};
    OutputPictureManager *picManager;
public:
    void launchRender(const std::string &outName);

    GraphicsEngine();

    void createEnvironment(std::string name);

    void switchEnvironment(std::string name);

    Environment *getCurrentEnvironment();

    void setRenderer(Abstract_Renderer *);

    OutputPictureManager *getPicManager();

    ~GraphicsEngine();

};

#endif //GRAPHIC_ENGINE_GRAPHICSENGINE_H
