#ifndef GRAPHIC_ENGINE_GRAPHICSENGINE_H
#define GRAPHIC_ENGINE_GRAPHICSENGINE_H

#include <list>
#include <string>
#include <environment.h>
#include <raytracer.h>
#include <utils.h>
#include <string>

#include "Renderer.h"

/**
 * Where we manage the environments and we can launch a render
 */
class GraphicsEngine {
private:
    std::list<Environment *> environments;
    Renderer *renderer{};
    Environment *currentEnv{};
    OutputPictureManager picManager;
public:
    void launchRender(const std::string &outName);

    GraphicsEngine();

    void createEnvironment(std::string name);

    void switchEnvironment(std::string name);

    void setRenderer(enum renderer_type = RAYTRACER);
};


#endif //GRAPHIC_ENGINE_GRAPHICSENGINE_H
