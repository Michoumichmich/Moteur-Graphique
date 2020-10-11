#include "Renderer.h"

Renderer::Renderer() {
    this->type = RAYTRACER;
}

Renderer::Renderer(enum renderer_type) : Renderer() {
}
