#include "RayTracer.h"

#include <utility>

RayTracer::RayTracer(Environment env) {
    this->environment = std::move(env);
}
