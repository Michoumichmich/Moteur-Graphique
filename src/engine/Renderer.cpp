#include "Renderer.h"

Renderer::Renderer()
{
  this->type = RAYTRACER;
}
void Renderer::SetRendererResolution(unsigned int width, unsigned int height)
{
  this->width = width;
  this->height = height;
}

Renderer::Renderer(enum renderer_type type) : Renderer()
{
  this->type = type;
}
void Renderer::SetEnvironment(Environment *env)
{
  this->environment = env;
}

