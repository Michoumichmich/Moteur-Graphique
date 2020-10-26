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
  unsigned int width = DEFAULT_WIDTH;
  unsigned int height = DEFAULT_HEIGHT;
  Environment *environment;
  OutputPictureManager *picManager;
 public:
  Abstract_Renderer();

  void SetRendererResolution(unsigned int, unsigned int);

  void SetEnvironment(Environment *);

  virtual void renderScene(std::string string) = 0;
};

#endif //GRAPHIC_ENGINE_RENDERER_H
