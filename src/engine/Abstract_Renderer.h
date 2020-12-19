#ifndef GRAPHIC_ENGINE_RENDERER_H
#define GRAPHIC_ENGINE_RENDERER_H

#include <config.h>
#include <environment.h>

enum renderer_type {
    RAYTRACER,
};

class Abstract_Renderer {
protected:
    explicit Abstract_Renderer(renderer_type);

    enum renderer_type type;
    Environment *environment{};
    OutputPictureManager *picManager{};
public:
    Abstract_Renderer();

    virtual ~Abstract_Renderer();

    virtual void renderScene(std::string string, Environment *env) = 0;

    virtual void enableReflexions() = 0; // TODO remove that

    virtual void disableReflexions() = 0;
};

#endif //GRAPHIC_ENGINE_RENDERER_H
