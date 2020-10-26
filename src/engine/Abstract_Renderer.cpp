#include "Abstract_Renderer.h"
#include <iostream>

Abstract_Renderer::Abstract_Renderer()
{
  this->type = RAYTRACER;
}

void Abstract_Renderer::SetRendererResolution(unsigned int width, unsigned int height)
{
  this->width = width;
  this->height = height;
}

Abstract_Renderer::Abstract_Renderer(enum renderer_type type) : Abstract_Renderer()
{
  this->type = type;
}
