#include "Abstract_Renderer.h"
#include <iostream>

Abstract_Renderer::Abstract_Renderer() {
    this->type = RAYTRACER;
}


Abstract_Renderer::Abstract_Renderer(enum renderer_type type) : Abstract_Renderer() {
    this->type = type;
}

Abstract_Renderer::~Abstract_Renderer() = default;
