#ifndef GRAPHIC_ENGINE_GRAPHICENGINE_H
#define GRAPHIC_ENGINE_GRAPHICENGINE_H

#include <list>
#include <string>
#include <environment.h>
#include <raytracer.h>
#include <utils.h>

/**
 * Where we manage the environments and we can launch a render
 */
class GraphicEngine {
private:
    std::list<Environment> environments;
    Renderer renderer = renderer;
    Environment currentEnv;
    OutputPictureManager picManager;
public:
    void launchRender(const std::string &outName);
};


#endif //GRAPHIC_ENGINE_GRAPHICENGINE_H
