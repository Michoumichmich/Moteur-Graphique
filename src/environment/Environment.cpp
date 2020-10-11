#include "Environment.h"

#include <utility>
#include "RegularObjects/Sphere.h"

Environment::Environment(std::string name) {
    this->envName = std::move(name);
    /*
    Object *sph = new  Sphere();
    this->allOjects.push_back(sph);
    sph->Tesselate();
    */
}

Environment::Environment() = default;
